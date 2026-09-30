#!/usr/bin/env python3
"""Join virtual-only COFF targets to the pinned Ghidra global xref export."""

from __future__ import annotations

import argparse
import csv
import json
import re
from collections import Counter
from pathlib import Path


REF = re.compile(r"^(?P<site>[0-9a-fA-F]{8}):(?P<kind>READ_WRITE|READ|WRITE|DATA)@(?P<function>[0-9a-fA-F]{8}):(?P<name>.*)$")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--targets", type=Path, required=True,
                        help="address-encoded target audit JSON")
    parser.add_argument("--ghidra-xrefs", type=Path, required=True)
    parser.add_argument("--function-map", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")

    target_report = json.loads(args.targets.read_text(encoding="utf-8"))
    target_vas = {int(row["va"], 16): row for row in target_report["mapped_targets"]
                  if row["backing"] == "virtual-only"}
    ghidra: dict[int, dict[str, str]] = {}
    with args.ghidra_xrefs.open("r", encoding="utf-8-sig", newline="") as stream:
        for row in csv.DictReader(stream):
            va = int(row["address"], 16)
            if va in target_vas:
                if va in ghidra:
                    raise ValueError(f"duplicate Ghidra global row for {va:#x}")
                ghidra[va] = row

    candidate_entries: set[int] = set()
    with args.function_map.open("r", encoding="utf-8-sig", newline="") as stream:
        for row in csv.DictReader(stream):
            candidate_entries.add(int(row["address"], 16))

    details = []
    totals: Counter[str] = Counter()
    by_source: Counter[str] = Counter()
    missing = []
    for va, target in sorted(target_vas.items()):
        xref = ghidra.get(va)
        if xref is None:
            missing.append(f"0x{va:08X}")
            details.append({"va": f"0x{va:08X}", "symbol": target["symbol"],
                            "coff_reference_occurrences": target["occurrences"],
                            "ghidra_xref_row": False})
            continue
        refs = []
        for token in filter(None, xref["incoming_references"].split("|")):
            match = REF.match(token)
            if not match:
                continue
            kind = match["kind"]
            function_va = int(match["function"], 16)
            source_class = "candidate-entry" if function_va in candidate_entries else "other-or-interior-code"
            refs.append({"site": f"0x{int(match['site'], 16):08X}",
                         "kind": kind, "function_va": f"0x{function_va:08X}",
                         "function_name": match["name"], "source_class": source_class})
            totals[kind] += 1
            by_source[f"{source_class}:{kind}"] += 1
        kinds = Counter(ref["kind"] for ref in refs)
        details.append({
            "va": f"0x{va:08X}", "symbol": target["symbol"],
            "coff_reference_occurrences": int(target["occurrences"]),
            "ghidra_xref_row": True,
            "ghidra_memory_block": xref["memory_block"],
            "ghidra_data_or_code_unit": xref["data_or_code_unit"],
            "read_reference_count": kinds["READ"] + kinds["READ_WRITE"],
            "write_reference_count": kinds["WRITE"] + kinds["READ_WRITE"],
            "read_write_reference_count": kinds["READ_WRITE"],
            "other_data_reference_count": kinds["DATA"],
            "references": refs,
        })

    report = {
        "scope": "Joins original-VA targets in the virtual-only .data tail to a saved Ghidra xref export and marks source entry addresses in the current function map. Static references only; no runtime initialization proof.",
        "target_report": str(args.targets.resolve()),
        "ghidra_xref_export": str(args.ghidra_xrefs.resolve()),
        "function_map": str(args.function_map.resolve()),
        "virtual_only_target_va_count": len(target_vas),
        "matched_ghidra_rows": len(ghidra),
        "missing_ghidra_rows": missing,
        "targets_with_write_xrefs": sum(1 for row in details if row.get("write_reference_count", 0)),
        "targets_with_read_xrefs": sum(1 for row in details if row.get("read_reference_count", 0)),
        "reference_counts_by_kind": dict(sorted(totals.items())),
        "reference_counts_by_source_class_and_kind": dict(sorted(by_source.items())),
        "targets": details,
        "limitations": [
            "Ghidra READ/WRITE labels do not establish dynamic reachability or that every control-flow path executes.",
            "A write xref does not prove the value, order, or successful completion of initialization.",
            "The function map is used only to identify exact 705 entry sources; unlisted addresses may be interior code, support code, or other binary code.",
            "No candidate PE/ASI was loaded and no GTA runtime behavior was tested.",
        ],
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({key: report[key] for key in (
        "virtual_only_target_va_count", "matched_ghidra_rows", "missing_ghidra_rows",
        "targets_with_write_xrefs", "targets_with_read_xrefs",
        "reference_counts_by_kind", "reference_counts_by_source_class_and_kind")}, indent=2))
    print(f"report={args.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
