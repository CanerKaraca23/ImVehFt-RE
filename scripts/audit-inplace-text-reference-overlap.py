#!/usr/bin/env python3
"""Flag planned in-place code placements that cover recorded Ghidra xref targets."""

from __future__ import annotations

import argparse
import csv
import json
from collections import Counter, defaultdict
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--packing-report", required=True, type=Path)
    parser.add_argument("--ghidra-xrefs", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()

    packing = json.loads(args.packing_report.read_text(encoding="utf-8"))
    with args.ghidra_xrefs.open(encoding="utf-8-sig", newline="") as stream:
        references = list(csv.DictReader(stream))

    target_rows: dict[int, list[dict[str, str]]] = defaultdict(list)
    for row in references:
        target_rows[int(row["target_va"], 16)].append(row)

    overlaps: list[dict[str, object]] = []
    covering_entries: Counter[str] = Counter()
    overlapping_targets: set[int] = set()
    for placement in packing["placements"]:
        start = int(placement["planned_va"], 16)
        end = start + int(placement["size"])
        for target, rows in target_rows.items():
            if start <= target < end:
                overlapping_targets.add(target)
                covering_entries[str(placement["entry"])] += len(rows)
                for row in rows:
                    overlaps.append({
                        "target_va": f"0x{target:08x}",
                        "planned_candidate_entry": placement["entry"],
                        "planned_candidate_start": placement["planned_va"],
                        "planned_candidate_size": placement["size"],
                        "offset_in_placed_body": f"0x{target - start:x}",
                        "source_va": f"0x{int(row['source_va'], 16):08x}",
                        "source_function_va": row["source_function_va"],
                        "source_function": row["source_function"],
                        "target_function_va": row["target_function_va"],
                        "target_function": row["target_function"],
                        "reference_type": row["reference_type"],
                    })

    result = {
        "scope": "Exact-byte overlap of Ghidra-recorded non-entry .text reference destinations with heuristic moved-body intervals.",
        "packing_report": str(args.packing_report),
        "ghidra_xrefs": str(args.ghidra_xrefs),
        "ghidra_nonentry_reference_records": len(references),
        "unique_reference_target_bytes": len(target_rows),
        "heuristic_moved_body_count": len(packing["placements"]),
        "overlapping_unique_target_bytes": len(overlapping_targets),
        "overlapping_reference_records": len(overlaps),
        "covering_candidate_entries_with_overlap_records": len(covering_entries),
        "overlaps": overlaps,
        "limitations": [
            "A destination-byte overlap is a conservative warning; it does not decide whether the original target is code, data, or safely redirectable.",
            "Only exact recorded reference destination bytes are checked; referenced instruction/data extents and undiscovered/indirect references are not included.",
            "No bytes, relocation fields, or project state are modified.",
        ],
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({key: result[key] for key in (
        "ghidra_nonentry_reference_records", "unique_reference_target_bytes",
        "heuristic_moved_body_count", "overlapping_unique_target_bytes",
        "overlapping_reference_records", "covering_candidate_entries_with_overlap_records",
    )}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
