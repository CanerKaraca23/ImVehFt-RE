#!/usr/bin/env python3
"""Audit planned thunk entry bytes against saved Ghidra xrefs and old HIGHLOW sites."""

from __future__ import annotations

import argparse
import csv
import json
from collections import Counter
from pathlib import Path


def read_rows(path: Path):
    with path.open(encoding="utf-8-sig", newline="") as f:
        return list(csv.DictReader(f))


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--placement-plan", type=Path, required=True)
    ap.add_argument("--entry-xrefs", type=Path, required=True)
    ap.add_argument("--nonentry-xrefs", type=Path, required=True)
    ap.add_argument("--text-highlow-sites", type=Path, required=True)
    ap.add_argument("--output", type=Path, required=True)
    a = ap.parse_args()
    if a.output.exists():
        raise FileExistsError(f"refusing to overwrite {a.output}")
    plan = json.loads(a.placement_plan.read_text(encoding="utf-8"))
    thunks = [r for r in plan["entries"] if r["placement_mode"] == "jmp-rel32-thunk"]
    if plan.get("candidate_count") != 705:
        raise ValueError("expected complete 705-entry plan")
    entry_refs = read_rows(a.entry_xrefs)
    nonentry_refs = read_rows(a.nonentry_xrefs)
    fixups = sorted(int(r["address"], 16) for r in read_rows(a.text_highlow_sites))
    refs_by_entry: dict[int, list[dict[str, str]]] = {int(r["address"], 16): [] for r in thunks}
    for ref in entry_refs:
        entry = int(ref["entry_va"], 16)
        if entry in refs_by_entry:
            refs_by_entry[entry].append(ref)
    nonentry_by_entry: dict[int, list[dict[str, str]]] = {e: [] for e in refs_by_entry}
    body_by_entry = {int(r["address"], 16): int(r["candidate_body_size"]) for r in thunks}
    for ref in nonentry_refs:
        try:
            target, entry = int(ref["target_va"], 16), int(ref["target_function_va"], 16)
        except (TypeError, ValueError):
            continue
        if entry in body_by_entry and entry + 5 <= target < entry + body_by_entry[entry]:
            item = dict(ref)
            item["target_offset_from_entry"] = str(target - entry)
            nonentry_by_entry[entry].append(item)
    results = []
    all_interior_refs = []
    all_fixups = []
    offsets = Counter()
    for row in thunks:
        entry = int(row["address"], 16)
        window_refs = refs_by_entry[entry]
        interior_window = [r for r in window_refs if entry < int(r["target_va"], 16) < entry + 5]
        overlaps = [s for s in fixups if s < entry + 5 and s + 4 > entry]
        body_refs = nonentry_by_entry[entry]
        all_interior_refs.extend(body_refs)
        all_fixups.extend((entry, s) for s in overlaps)
        offsets.update(s - entry for s in overlaps)
        results.append({
            "entry_va": f"0x{entry:08x}",
            "original_gap_bytes": row["available_until_next_entry_or_text_end"],
            "entry_byte_xref_count": sum(int(r["target_va"], 16) == entry for r in window_refs),
            "entry_patch_interior_xrefs_offsets_1_to_4": [
                {**r, "offset": int(r["target_va"], 16) - entry} for r in interior_window
            ],
            "old_text_highlow_sites_overlapping_five_byte_patch": [
                {"site_va": f"0x{s:08x}", "offset": s - entry,
                 "bytes_intersecting_patch": min(s + 4, entry + 5) - max(s, entry)}
                for s in overlaps
            ],
            "saved_nonentry_xrefs_into_preserved_old_body_after_patch_window": body_refs,
        })
    report = {
        "scope": "Saved static Ghidra reference and original .text HIGHLOW overlap audit for all thunk windows in the supplied 705-entry plan.",
        "placement_plan": str(a.placement_plan.resolve()),
        "entry_xref_export": str(a.entry_xrefs.resolve()),
        "nonentry_xref_export": str(a.nonentry_xrefs.resolve()),
        "highlow_site_export": str(a.text_highlow_sites.resolve()),
        "thunk_windows": len(thunks),
        "entry_windows_with_saved_xref_to_offset_1_to_4": sum(bool(r["entry_patch_interior_xrefs_offsets_1_to_4"]) for r in results),
        "saved_xrefs_into_offset_1_to_4_total": sum(len(r["entry_patch_interior_xrefs_offsets_1_to_4"]) for r in results),
        "original_text_highlow_sites_overlapping_thunk_windows": len(all_fixups),
        "overlap_offset_counts": dict(sorted(offsets.items())),
        "thunk_bodies_with_saved_nonentry_xrefs_after_patch_window": sum(bool(r["saved_nonentry_xrefs_into_preserved_old_body_after_patch_window"]) for r in results),
        "saved_nonentry_xref_count_after_patch_window": len(all_interior_refs),
        "nonentry_reference_type_counts": dict(Counter(r["reference_type"] for r in all_interior_refs)),
        "limitations": [
            "Ghidra exports are a saved static analysis snapshot; no static xref does not exclude computed or external fixed-address references.",
            "The HIGHLOW sites listed must be removed from the final base-relocation set when their bytes are replaced by E9 rel32, then the complete directory must be regenerated.",
            "Interior non-entry references can point to data or alternate code entries; their meaning must be reviewed before relying on entry redirection.",
            "This report does not build a patched PE or prove loader/game behavior.",
        ],
        "entries": results,
    }
    a.output.parent.mkdir(parents=True, exist_ok=True)
    with a.output.open("x", encoding="utf-8", newline="\n") as f:
        json.dump(report, f, indent=2)
        f.write("\n")
    print(json.dumps({k: report[k] for k in (
        "thunk_windows", "entry_windows_with_saved_xref_to_offset_1_to_4",
        "original_text_highlow_sites_overlapping_thunk_windows",
        "overlap_offset_counts", "thunk_bodies_with_saved_nonentry_xrefs_after_patch_window",
        "saved_nonentry_xref_count_after_patch_window", "nonentry_reference_type_counts"
    )}, indent=2))
    print(f"report={a.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
