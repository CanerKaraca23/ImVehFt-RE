#!/usr/bin/env python3
"""Emit relocatable MASM versions of the bounded Ghidra hook-shim streams."""

from __future__ import annotations

import argparse
import csv
import json
import struct
from collections import defaultdict
from pathlib import Path


def coff_name(obj: bytes, raw: bytes, strings: bytes) -> str:
    if raw[:4] == b"\0\0\0\0":
        offset = struct.unpack_from("<I", raw, 4)[0]
        end = strings.find(b"\0", offset)
        return strings[offset:end].decode("ascii")
    return raw.split(b"\0", 1)[0].decode("ascii")


def public_code_entry(path: Path) -> str:
    obj = path.read_bytes()
    machine, section_count, _, symbol_ptr, symbol_count, optional_size, _ = struct.unpack_from(
        "<HHIIIHH", obj, 0
    )
    if machine != 0x14C or optional_size:
        raise ValueError(f"not an x86 COFF object: {path}")
    sections = {
        number + 1: obj[20 + number * 40 : 28 + number * 40]
        .split(b"\0", 1)[0]
        .decode("ascii")
        for number in range(section_count)
    }
    strings_at = symbol_ptr + symbol_count * 18
    strings_size = struct.unpack_from("<I", obj, strings_at)[0]
    strings = obj[strings_at : strings_at + strings_size]
    matches: set[str] = set()
    index = 0
    while index < symbol_count:
        at = symbol_ptr + index * 18
        name = coff_name(obj, obj[at : at + 8], strings)
        value, section_no = struct.unpack_from("<Ih", obj, at + 8)
        storage_class, aux_count = obj[at + 16], obj[at + 17]
        if (
            storage_class == 2
            and value == 0
            and sections.get(section_no, "").startswith(".text")
        ):
            matches.add(name)
        index += 1 + aux_count
    if len(matches) != 1:
        raise ValueError(f"expected one public text entry in {path}; found {sorted(matches)}")
    return matches.pop()


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--cfg", type=Path, default=Path("audit/asi-hook-target-cfg-2026-09-27.csv"))
    parser.add_argument("--fixups", type=Path, default=Path("audit/hook-shim-fixups-2026-09-27.json"))
    parser.add_argument("--objects-dir", type=Path, required=True)
    parser.add_argument("--asm", type=Path, required=True)
    parser.add_argument("--manifest", type=Path, required=True)
    args = parser.parse_args()
    if args.asm.exists() or args.manifest.exists():
        parser.error("refusing to overwrite existing outputs")

    groups: dict[int, list[dict[str, str]]] = defaultdict(list)
    with args.cfg.open(encoding="utf-8-sig", newline="") as stream:
        for row in csv.DictReader(stream):
            groups[int(row["target"], 16)].append(row)
    fixup_doc = json.loads(args.fixups.read_text(encoding="utf-8"))
    by_instruction: dict[int, list[dict[str, object]]] = defaultdict(list)
    for fixup in fixup_doc["fixups"]:
        by_instruction[int(fixup["instruction_va"], 16)].append(fixup)

    function_symbols: dict[int, str] = {}
    for fixup in fixup_doc["fixups"]:
        if fixup["kind"] != "candidate-function-rel32-call":
            continue
        target = int(fixup["original_target"], 16)
        if target not in function_symbols:
            function_symbols[target] = public_code_entry(
                args.objects_dir / f"{target:08x}.obj"
            )

    lines = [".386", ".model flat", "option casemap:none", ""]
    data_targets = sorted(
        {
            int(fixup["original_target"], 16)
            for fixup in fixup_doc["fixups"]
            if fixup["kind"] in {
                "absolute-image-memory-reference",
                "absolute-image-pointer-immediate",
            }
        }
    )
    for target in data_targets:
        lines.append(f"EXTERN IVF_RELOC_TARGET_{target:08X}:BYTE")
    for symbol in sorted(function_symbols.values()):
        lines.append(f"EXTERN {symbol}:PROC")
    lines.extend(["", ".code", ""])

    expected_fixups: list[dict[str, object]] = []
    for target, rows in sorted(groups.items()):
        rows.sort(key=lambda row: int(row["instruction_address"], 16))
        start = int(rows[0]["instruction_address"], 16)
        label = f"_ImVehFtHook_{target:08X}"
        lines.extend([f"PUBLIC {label}", f"{label} LABEL BYTE"])
        cursor = start
        for row in rows:
            address = int(row["instruction_address"], 16)
            code = bytes.fromhex(row["bytes_hex"])
            if address != cursor:
                raise ValueError(f"non-contiguous Ghidra stream at {address:#x}, expected {cursor:#x}")
            cursor += len(code)
            fixups = sorted(by_instruction.get(address, []), key=lambda item: int(item["field_offset"]))
            if not fixups:
                lines.append("    DB " + ",".join(f"0{byte:02X}h" for byte in code))
                continue
            if len(fixups) != 1:
                raise ValueError(f"multiple fixups in one instruction at {address:#x} need review")
            fixup = fixups[0]
            offset = int(fixup["field_offset"])
            width = int(fixup["width"])
            if width != 4 or offset + width > len(code):
                raise ValueError(f"unexpected fixup width at {address:#x}: {fixup}")
            kind = str(fixup["kind"])
            if kind == "candidate-function-rel32-call":
                if code != b"\xE8" + code[1:] or len(code) != 5 or offset != 1:
                    raise ValueError(f"not a direct rel32 CALL at {address:#x}")
                call_target = int(fixup["original_target"], 16)
                symbol = function_symbols[call_target]
                lines.append(f"    CALL {symbol}")
                relocation_kind = "REL32"
                expected_symbol = symbol
            elif kind in {
                "absolute-image-memory-reference",
                "absolute-image-pointer-immediate",
            }:
                before = code[:offset]
                after = code[offset + width :]
                if before:
                    lines.append("    DB " + ",".join(f"0{byte:02X}h" for byte in before))
                data_symbol = f"IVF_RELOC_TARGET_{int(fixup['original_target'], 16):08X}"
                lines.append(f"    DD OFFSET {data_symbol}")
                if after:
                    lines.append("    DB " + ",".join(f"0{byte:02X}h" for byte in after))
                relocation_kind = "DIR32"
                expected_symbol = data_symbol
            else:
                raise ValueError(f"unsupported fixup kind {kind} at {address:#x}")
            expected_fixups.append(
                {
                    "shim": f"0x{target:08X}",
                    "instruction_va": f"0x{address:08X}",
                    "field_offset": offset,
                    "kind": relocation_kind,
                    "target_symbol": expected_symbol,
                    "original_target": fixup["original_target"],
                }
            )
        lines.append("")
    lines.extend(["END", ""])

    args.asm.parent.mkdir(parents=True, exist_ok=True)
    args.asm.write_text("\n".join(lines), encoding="ascii", newline="\n")
    manifest = {
        "scope": "Ghidra CFG shim instruction streams with image-internal operands converted to COFF relocations; does not install hooks or build a plugin",
        "shim_count": len(groups),
        "instruction_count": sum(len(rows) for rows in groups.values()),
        "fixup_count": len(expected_fixups),
        "distinct_candidate_call_targets": {
            f"0x{address:08X}": symbol for address, symbol in sorted(function_symbols.items())
        },
        "fixups": expected_fixups,
    }
    args.manifest.parent.mkdir(parents=True, exist_ok=True)
    args.manifest.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    print(
        f"shims={len(groups)} instructions={manifest['instruction_count']} "
        f"COFF-fixups={len(expected_fixups)} output={args.asm}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
