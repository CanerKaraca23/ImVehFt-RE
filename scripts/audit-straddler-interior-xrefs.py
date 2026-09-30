#!/usr/bin/env python3
"""Cross-reference Ghidra's saved non-entry xrefs against boundary-straddler spans."""

from __future__ import annotations

import argparse
import csv
import json
from collections import Counter
from pathlib import Path


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--straddlers", type=Path, required=True)
    ap.add_argument("--ghidra-references", type=Path, required=True)
    ap.add_argument("--output", type=Path, required=True)
    a = ap.parse_args()
    if a.output.exists():
        raise FileExistsError(f"refusing to overwrite {a.output}")
    boundaries = json.loads(a.straddlers.read_text(encoding="utf-8"))["results"]
    spans = {
        int(row["entry_va"], 16): (
            int(row["entry_va"], 16), int(row["candidate_body_end_exclusive"], 16)
        ) for row in boundaries
    }
    refs = list(csv.DictReader(a.ghidra_references.open(encoding="utf-8-sig", newline="")))
    matched = []
    by_entry: dict[int, list[dict[str, str]]] = {entry: [] for entry in spans}
    for ref in refs:
        target = int(ref["target_va"], 16)
        for entry, (start, end) in spans.items():
            if start + 5 <= target < end:
                row = dict(ref)
                row["target_offset_from_entry"] = str(target - entry)
                by_entry[entry].append(row)
                matched.append(row)
    result_rows = []
    for entry in sorted(spans):
        items = by_entry[entry]
        result_rows.append({
            "entry_va": f"0x{entry:08x}",
            "candidate_body_end_exclusive": f"0x{spans[entry][1]:08x}",
            "ghidra_nonentry_references_after_five_byte_thunk_window": items,
        })
    type_counts = Counter(r["reference_type"] for r in matched)
    report = {
        "straddler_report": str(a.straddlers.resolve()),
        "ghidra_reference_csv": str(a.ghidra_references.resolve()),
        "saved_ghidra_nonentry_reference_rows": len(refs),
        "straddler_entry_count": len(spans),
        "nonentry_references_inside_candidate_spans_after_entry_patch_window": len(matched),
        "entries_with_such_references": sum(bool(v) for v in by_entry.values()),
        "reference_type_counts": dict(type_counts),
        "limitations": [
            "This uses the saved Ghidra reference export and its reference types; absence of a static xref does not exclude computed/runtime references.",
            "DATA references may be jump-table/data references embedded in .text; this report does not decide runtime reachability or whether old code must remain.",
            "No PE bytes are modified; this is not validation of a thunked full image.",
        ],
        "entries": result_rows,
    }
    a.output.parent.mkdir(parents=True, exist_ok=True)
    with a.output.open("x", encoding="utf-8", newline="\n") as f:
        json.dump(report, f, indent=2)
        f.write("\n")
    print(f"straddlers={len(spans)} interior_nonentry_refs={len(matched)} entries_hit={report['entries_with_such_references']} types={dict(type_counts)}")
    print(f"report={a.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
