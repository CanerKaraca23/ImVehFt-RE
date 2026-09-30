#!/usr/bin/env python3
"""Prove callback-label VAs survive the current in-place/thunk entry plan."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import re
import struct
from pathlib import Path

import pefile


PINNED_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--original", type=Path, required=True)
    parser.add_argument("--jmp-map", type=Path, required=True)
    parser.add_argument("--call-map", type=Path, required=True)
    parser.add_argument("--entry-asm", type=Path, required=True)
    parser.add_argument("--placement-plan", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")

    image = args.original.read_bytes()
    image_sha = hashlib.sha256(image).hexdigest().upper()
    if image_sha != PINNED_SHA256:
        raise ValueError(f"pinned original hash mismatch: {image_sha}")
    pe = pefile.PE(data=image, fast_load=True)
    base = pe.OPTIONAL_HEADER.ImageBase
    text = next(s for s in pe.sections if s.Name.rstrip(b"\0") == b".text")
    plan = json.loads(args.placement_plan.read_text(encoding="utf-8"))
    if plan.get("candidate_count") != 705:
        raise ValueError("placement plan does not cover 705 candidate entries")

    overwritten = []
    entry_vas = set()
    for row in plan["entries"]:
        va = int(row["address"], 16)
        entry_vas.add(va)
        size = 5 if row["placement_mode"] == "jmp-rel32-thunk" else int(row["candidate_body_size"])
        overwritten.append((va, va + size, row["address"], row["placement_mode"]))

    def read_map(path: Path, expected_encoding: str) -> list[dict[str, str]]:
        with path.open("r", encoding="utf-8-sig", newline="") as stream:
            rows = list(csv.DictReader(stream))
        for row in rows:
            if row.get("encoding") != expected_encoding:
                raise ValueError(f"unexpected callback encoding in {path}: {row}")
        return rows

    jmp_mappings = read_map(args.jmp_map, "E9 rel32")
    call_map = read_map(args.call_map, "PUSH ECX; CALL rel32; RET")
    call_map_by_label = {int(row["label_address"], 16): int(row["target_address"], 16)
                         for row in call_map}
    assembly_mappings: list[dict[str, str]] = []
    active_label: int | None = None
    active_target: int | None = None
    for line in args.entry_asm.read_text(encoding="utf-8").splitlines():
        line = line.strip()
        public = re.fullmatch(r"PUBLIC _LAB_(100[0-9A-Fa-f]{5})", line)
        call = re.fullmatch(r"CALL \?FUN_(100[0-9A-Fa-f]{5})@@.*", line)
        if public:
            if active_label is not None:
                raise ValueError(f"callback entry has no completed CALL/RET: {active_label:#x}")
            active_label = int(public.group(1), 16)
            active_target = None
        elif call and active_label is not None:
            if active_target is not None:
                raise ValueError(f"callback entry has multiple calls: {active_label:#x}")
            active_target = int(call.group(1), 16)
        elif line == "RET" and active_label is not None:
            if active_target is None:
                raise ValueError(f"callback entry has no target: {active_label:#x}")
            assembly_mappings.append({
                "label_address": f"0x{active_label:08X}",
                "target_address": f"0x{active_target:08X}",
                "source": str(args.entry_asm),
                "xref": "saved MASM public label",
            })
            active_label = None
            active_target = None
    if active_label is not None or len(assembly_mappings) != 25:
        raise ValueError(f"expected 25 complete entry thunks in MASM source, found {len(assembly_mappings)}")
    for row in call_map:
        label = int(row["label_address"], 16)
        matching = [entry for entry in assembly_mappings if int(entry["label_address"], 16) == label]
        if len(matching) != 1 or int(matching[0]["target_address"], 16) != int(row["target_address"], 16):
            raise ValueError(f"saved call-thunk map differs from MASM source at {label:#x}")

    mappings = [
        ("jmp-rel32", row, 5)
        for row in jmp_mappings
    ] + [
        ("push-ecx-call-ret", row, 7)
        for row in assembly_mappings
    ]
    rows = []
    seen: set[int] = set()
    for kind, row, size in mappings:
        label = int(row["label_address"], 16)
        target = int(row["target_address"], 16)
        if label in seen:
            raise ValueError(f"duplicate callback label VA: {label:#x}")
        seen.add(label)
        if target not in entry_vas:
            raise ValueError(f"callback target is not a candidate entry: {target:#x}")
        rva = label - base
        if not (text.VirtualAddress <= rva and rva + size <= text.VirtualAddress + text.SizeOfRawData):
            raise ValueError(f"callback label is not raw-backed in original .text: {label:#x}")
        raw = text.PointerToRawData + rva - text.VirtualAddress
        body = image[raw:raw + size]
        if kind == "jmp-rel32":
            if body[0] != 0xE9:
                raise ValueError(f"original callback JMP opcode mismatch at {label:#x}: {body.hex()}")
            actual_target = label + 5 + struct.unpack_from("<i", body, 1)[0]
        else:
            if body[0] != 0x51 or body[1] != 0xE8 or body[6] != 0xC3:
                raise ValueError(f"original callback entry template mismatch at {label:#x}: {body.hex()}")
            actual_target = label + 6 + struct.unpack_from("<i", body, 2)[0]
        if actual_target != target:
            raise ValueError(
                f"original callback target mismatch at {label:#x}: "
                f"{actual_target:#x} != {target:#x}"
            )
        collisions = [
            {"entry": entry, "placement_mode": mode}
            for start, end, entry, mode in overwritten
            if label < end and start < label + size
        ]
        if collisions:
            raise ValueError(f"callback label bytes collide with candidate patches: {label:#x}: {collisions}")
        rows.append({
            "kind": kind,
            "label_va": f"0x{label:08X}",
            "target_va": f"0x{target:08X}",
            "size": size,
            "original_bytes": body.hex(" ").upper(),
            "original_transfer_matches_map": True,
            "target_is_candidate_entry": True,
            "overlaps_current_candidate_patch": False,
            "source": row.get("source"),
            "xref": row.get("xref"),
        })

    expected_counts = {"jmp-rel32": 70, "push-ecx-call-ret": 25}
    actual_counts = {kind: sum(row["kind"] == kind for row in rows) for kind in expected_counts}
    if actual_counts != expected_counts:
        raise ValueError(f"expected the verified 70+25 callback labels, got {actual_counts}")
    report = {
        "scope": "Checks the pinned original callback stub bytes against saved target maps, current 705-entry placement windows, and original raw-backed .text. Static placement evidence only; no patched image or runtime proof.",
        "original_sha256": image_sha,
        "placement_plan": str(args.placement_plan.resolve()),
        "candidate_entry_count": len(entry_vas),
        "callback_label_count": len(rows),
        "callback_labels_by_kind": actual_counts,
        "original_transfer_bytes_match_maps": True,
        "candidate_patch_collisions": 0,
        "all_targets_are_candidate_entry_vas": True,
        "labels": sorted(rows, key=lambda item: int(item["label_va"], 16)),
        "limitations": [
            "This proves the 95 original callback-label byte ranges remain outside the current candidate patches and their transfers match the saved target map.",
            "It does not validate callback behavior, ABI beyond the encoded stub form, other original-text references, final PE construction, or GTA runtime behavior.",
        ],
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({key: report[key] for key in (
        "callback_label_count", "callback_labels_by_kind",
        "candidate_patch_collisions", "all_targets_are_candidate_entry_vas",
    )}, indent=2))
    print(f"report={args.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
