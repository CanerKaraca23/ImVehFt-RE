#!/usr/bin/env python3
"""Join original relocation overlaps to Ghidra listing/xrefs and entry gaps."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
from pathlib import Path


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest().upper()


def va(value: str) -> int:
    return int(value.strip().strip('"').removeprefix("0x"), 16)


def read_csv(path: Path) -> list[dict[str, str]]:
    with path.open(encoding="utf-8-sig", newline="") as stream:
        return list(csv.DictReader(stream))


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--overlap-report", type=Path, required=True)
    parser.add_argument("--ghidra-units", type=Path, required=True)
    parser.add_argument("--ghidra-xrefs", type=Path, required=True)
    parser.add_argument("--function-map", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")

    overlaps = json.loads(args.overlap_report.read_text(encoding="utf-8"))["overlaps"]
    units = {va(row["address"]): row for row in read_csv(args.ghidra_units)}
    xrefs = read_csv(args.ghidra_xrefs)
    mapped = sorted(va(row["address"]) for row in read_csv(args.function_map))
    if len(mapped) != 705 or len(set(mapped)) != 705:
        raise ValueError("function map must contain 705 unique entries")

    gaps = [
        {"entry_va": f"0x{left:08x}", "next_entry_va": f"0x{right:08x}", "gap": right - left}
        for left, right in zip(mapped, mapped[1:])
        if right - left < 5
    ]
    if [(int(row["entry_va"], 16), int(row["gap"])) for row in gaps] != [
        (0x10018F94, 3), (0x1002044B, 3)
    ]:
        raise ValueError(f"unexpected sub-five-byte entry gaps: {gaps}")

    detailed = []
    missing = []
    for item in overlaps:
        site = va(item["relocation_site_va"])
        row = units.get(site)
        if row is None:
            missing.append(f"0x{site:08x}")
            continue
        detailed.append({**item, "ghidra_code_unit_kind": row["code_unit_kind"],
                         "ghidra_code_unit_start": f"0x{va(row['code_unit_min']):08x}",
                         "ghidra_code_unit_max": f"0x{va(row['code_unit_max']):08x}",
                         "ghidra_instruction_text": row["instruction_text"],
                         "containing_function_entry": row["containing_function_entry"],
                         "containing_function_name": row["containing_function_name"]})
    if missing or len(detailed) != 97:
        raise ValueError(f"could not join all 97 overlap sites; missing={missing}")
    if any(row["ghidra_code_unit_kind"] != "InstructionDB" for row in detailed):
        raise ValueError("one or more overlapping relocations did not join to an instruction")

    interior_refs = [
        row for row in xrefs
        if int(row["entry_offset"], 10) > 0
        and row["reference_type"] not in {"DATA"}
    ]
    expected = {(0x10018F94, 3, 0x10018F97), (0x1002044B, 3, 0x1002044E)}
    found = {(va(row["entry_va"]), int(row["entry_offset"]), va(row["target_va"])) for row in interior_refs}
    if found != expected:
        raise ValueError(f"unexpected control-flow references into thunk interiors: {found}")

    report = {
        "scope": "Cross-evidence audit of proposed 5-byte original-entry E9 patch windows; analysis only, no PE bytes changed.",
        "inputs": {
            "overlap_report_sha256": sha256(args.overlap_report),
            "ghidra_units_sha256": sha256(args.ghidra_units),
            "ghidra_xrefs_sha256": sha256(args.ghidra_xrefs),
            "function_map_sha256": sha256(args.function_map),
        },
        "summary": {
            "candidate_entries": len(mapped),
            "relocation_overlaps": len(detailed),
            "overlaps_joined_to_ghidra_instruction_units": len(detailed),
            "sub_five_byte_entry_gaps": len(gaps),
            "non_data_xrefs_into_entry_patch_interiors": len(interior_refs),
        },
        "short_gaps": gaps,
        "interior_control_flow_references": interior_refs,
        "relocation_overlaps": detailed,
        "interpretation_limits": [
            "Ghidra listing join establishes that each overlapping HIGHLOW site lies in an instruction code unit, not that a proposed final image is correct.",
            "If an entry instruction is replaced by a branch, its original base-relocation record must not be applied to the branch displacement; the final relocation directory must be rebuilt and independently parsed.",
            "The two three-byte gaps need the separately modeled short-entry/relay design, and the final entry addresses and relay bytes must be verified in an emitted PE.",
            "No final PE/ASI, loader behavior, startup, callback behavior, or in-game semantics are validated by this report.",
        ],
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print("entries=705 relocation_instruction_joins=97 short_gaps=2 interior_control_refs=2")
    print(f"report={args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
