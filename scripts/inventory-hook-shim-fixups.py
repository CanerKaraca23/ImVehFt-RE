#!/usr/bin/env python3
"""Extract ASI-internal address fixups from the bounded Ghidra hook CFG CSV."""

from __future__ import annotations

import argparse
import csv
import json
import re
import struct
from collections import Counter
from pathlib import Path


IMAGE_BASE = 0x10000000
IMAGE_END = 0x10043000
ADDRESS = re.compile(r"0x[0-9a-fA-F]{6,8}")
DIRECT_BRANCH = re.compile(r"^(J[A-Z]+)\s+0x([0-9A-Fa-f]+)$")
DIRECT_CALL = re.compile(r"^CALL\s+0x([0-9A-Fa-f]+)$")


def signed(value: int, bits: int) -> int:
    sign = 1 << (bits - 1)
    return value - (1 << bits) if value & sign else value


def branch_destination(address: int, code: bytes) -> int:
    if len(code) == 2 and (code[0] == 0xEB or 0x70 <= code[0] <= 0x7F):
        return address + 2 + signed(code[1], 8)
    if len(code) == 5 and code[0] == 0xE9:
        return address + 5 + signed(struct.unpack_from("<I", code, 1)[0], 32)
    if len(code) == 6 and code[:1] == b"\x0f" and 0x80 <= code[1] <= 0x8F:
        return address + 6 + signed(struct.unpack_from("<I", code, 2)[0], 32)
    raise ValueError(f"Unsupported direct branch encoding at {address:#x}: {code.hex(' ')}")


def load_rows(path: Path) -> dict[str, list[dict[str, str]]]:
    grouped: dict[str, list[dict[str, str]]] = {}
    with path.open(encoding="utf-8-sig", newline="") as stream:
        for row in csv.DictReader(stream):
            grouped.setdefault(row["target"].lower(), []).append(row)
    return grouped


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--cfg", type=Path, default=Path("audit/asi-hook-target-cfg-2026-09-27.csv")
    )
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()

    groups = load_rows(args.cfg)
    fixups: list[dict[str, object]] = []
    skipped_internal_branches = 0
    for target, rows in sorted(groups.items()):
        rows.sort(key=lambda row: int(row["instruction_address"], 16))
        start = int(target, 16)
        end = int(rows[-1]["instruction_address"], 16) + len(
            bytes.fromhex(rows[-1]["bytes_hex"])
        )

        for row in rows:
            address = int(row["instruction_address"], 16)
            code = bytes.fromhex(row["bytes_hex"])
            mnemonic = row["mnemonic"]

            branch = DIRECT_BRANCH.match(mnemonic)
            if branch:
                destination = int(branch.group(2), 16)
                decoded = branch_destination(address, code)
                if decoded != destination:
                    raise ValueError(
                        f"Branch decode mismatch at {address:#x}: "
                        f"listing={destination:#x}, bytes={decoded:#x}"
                    )
                if start <= destination < end:
                    skipped_internal_branches += 1
                    continue
                if IMAGE_BASE <= destination < IMAGE_END:
                    field = 1 if code[0] == 0xE9 else 2
                    fixups.append(
                        {
                            "shim": target,
                            "instruction_va": f"0x{address:08X}",
                            "kind": "external-relative-branch",
                            "field_offset": field,
                            "width": len(code) - field,
                            "original_target": f"0x{destination:08X}",
                        }
                    )
                continue

            call = DIRECT_CALL.match(mnemonic)
            if call:
                destination = int(call.group(1), 16)
                if not (IMAGE_BASE <= destination < IMAGE_END):
                    continue
                if len(code) != 5 or code[0] != 0xE8:
                    raise ValueError(f"Unexpected direct CALL encoding at {address:#x}")
                decoded = address + 5 + signed(struct.unpack_from("<I", code, 1)[0], 32)
                if decoded != destination:
                    raise ValueError(
                        f"CALL decode mismatch at {address:#x}: "
                        f"listing={destination:#x}, bytes={decoded:#x}"
                    )
                fixups.append(
                    {
                        "shim": target,
                        "instruction_va": f"0x{address:08X}",
                        "kind": "candidate-function-rel32-call",
                        "field_offset": 1,
                        "width": 4,
                        "original_target": f"0x{destination:08X}",
                    }
                )
                continue

            for match in ADDRESS.finditer(mnemonic):
                destination = int(match.group(0), 16)
                if not (IMAGE_BASE <= destination < IMAGE_END):
                    continue
                encoded = struct.pack("<I", destination)
                offsets = [
                    offset
                    for offset in range(len(code) - 3)
                    if code[offset : offset + 4] == encoded
                ]
                if len(offsets) != 1:
                    raise ValueError(
                        f"Expected one encoded address field at {address:#x} "
                        f"for {destination:#x}; found offsets {offsets}, bytes={code.hex(' ')}"
                    )
                if "[" in mnemonic:
                    kind = "absolute-image-memory-reference"
                elif mnemonic.startswith("PUSH "):
                    kind = "absolute-image-pointer-immediate"
                else:
                    kind = "absolute-image-immediate-review"
                fixups.append(
                    {
                        "shim": target,
                        "instruction_va": f"0x{address:08X}",
                        "mnemonic": mnemonic,
                        "kind": kind,
                        "field_offset": offsets[0],
                        "width": 4,
                        "original_target": f"0x{destination:08X}",
                    }
                )

    counts = Counter(item["kind"] for item in fixups)
    unresolved = [item for item in fixups if item["kind"].endswith("review")]
    if unresolved:
        raise ValueError(f"Unclassified absolute operands remain: {unresolved}")

    result = {
        "source": str(args.cfg),
        "image_range": [f"0x{IMAGE_BASE:08X}", f"0x{IMAGE_END:08X}"],
        "shim_count": len(groups),
        "internal_position_relative_branches_verified": skipped_internal_branches,
        "fixup_count": len(fixups),
        "fixup_counts_by_kind": dict(sorted(counts.items())),
        "fixups": fixups,
        "scope_limit": (
            "Address operands decoded from bounded hook CFGs only. Does not prove "
            "the generated PE layout, target symbol mapping, runtime patching, or game behavior."
        ),
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(
        f"shims={len(groups)} internal_branches={skipped_internal_branches} "
        f"fixups={len(fixups)} kinds={dict(counts)} output={args.output}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
