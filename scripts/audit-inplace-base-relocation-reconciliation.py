#!/usr/bin/env python3
"""Crosswalk original .text HIGHLOW fields with candidate DIR32 fixups.

This is an inventory only: it never patches a PE image.
"""

from __future__ import annotations

import argparse
import csv
import importlib.util
import json
from collections import Counter
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
HELPER = ROOT / "scripts/audit-inplace-candidate-relocations.py"


def load_helper():
    spec = importlib.util.spec_from_file_location("inplace_audit", HELPER)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot import {HELPER}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--objects", type=Path, required=True)
    source = parser.add_mutually_exclusive_group(required=True)
    source.add_argument("--inplace-report", type=Path)
    source.add_argument("--placement-plan", type=Path)
    parser.add_argument("--text-highlow-sites", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")

    helper = load_helper()
    if args.placement_plan:
        plan = json.loads(args.placement_plan.read_text(encoding="utf-8"))
        if plan.get("candidate_count") != 705 or len(plan.get("entries", [])) != 705:
            raise ValueError("expected a complete 705-entry placement plan")
        helper_rows = {
            helper.va(row["address"]): {
                "body_fits_gap": row["placement_mode"] == "body-at-entry",
                "symbol": row["entry_symbol"],
            }
            for row in plan["entries"]
        }
        if len(helper_rows) != 705:
            raise ValueError("placement plan contains duplicate entry addresses")
    else:
        inplace = json.loads(args.inplace_report.read_text(encoding="utf-8"))
        reported_count = inplace.get("summary", {}).get("candidate_entries", len(inplace.get("results", [])))
        if reported_count != 705:
            raise ValueError("expected a fresh 705-entry in-place relocation report")
        helper_rows = {helper.va(r["entry_va"]): r for r in inplace["results"]}
    fixups = sorted(
        helper.va(row["address"])
        for row in csv.DictReader(
            args.text_highlow_sites.open(encoding="utf-8-sig", newline="")
        )
    )
    if len(fixups) != 3160:
        raise ValueError(f"expected 3160 original .text HIGHLOW sites, got {len(fixups)}")

    rows: list[dict[str, object]] = []
    old_touched: set[int] = set()
    new_dir32_sites: set[int] = set()
    exact_reuse: set[int] = set()
    intersecting_old: set[int] = set()
    intersecting_new: set[int] = set()
    exact_pairs: set[tuple[int, int]] = set()
    shifted_pairs: set[tuple[int, int]] = set()
    partial_old: set[int] = set()
    candidate_reloc_counts: Counter[str] = Counter()
    for entry, result in sorted(helper_rows.items()):
        if not result["body_fits_gap"]:
            continue
        symbol = result["symbol"]
        body, info = helper.parse_coff(args.objects / f"{entry:08x}.obj", symbol)
        end = entry + len(body)
        old_here = [site for site in fixups if max(site, entry) < min(site + 4, end)]
        dirs = [
            entry + int(rel["site"])
            for rel in info["relocations"]
            if rel["type_name"] == "DIR32"
        ]
        for rel in info["relocations"]:
            candidate_reloc_counts[str(rel["type_name"])] += 1
            if int(rel["site"]) < 0 or int(rel["site"]) + 4 > len(body):
                raise ValueError(f"{entry:#x}: relocation field lies outside body")
        for site in old_here:
            if not (site >= entry and site + 4 <= end):
                partial_old.add(site)
        old_touched.update(old_here)
        new_dir32_sites.update(dirs)
        exact = sorted(set(old_here).intersection(dirs))
        exact_reuse.update(exact)
        for old_site in old_here:
            for new_site in dirs:
                if max(old_site, new_site) < min(old_site + 4, new_site + 4):
                    intersecting_old.add(old_site)
                    intersecting_new.add(new_site)
                    if old_site == new_site:
                        exact_pairs.add((old_site, new_site))
                    else:
                        shifted_pairs.add((old_site, new_site))
        rows.append(
            {
                "entry_va": f"0x{entry:08x}",
                "symbol": symbol,
                "body_size": len(body),
                "body_end_exclusive": f"0x{end:08x}",
                "original_highlow_sites_touched": [f"0x{x:08x}" for x in old_here],
                "candidate_dir32_sites": [f"0x{x:08x}" for x in dirs],
                "exact_site_matches": [f"0x{x:08x}" for x in exact],
                "old_fields_intersecting_candidate_dir32": [
                    {
                        "old_highlow": f"0x{old_site:08x}",
                        "candidate_dir32": f"0x{new_site:08x}",
                        "exact_start": old_site == new_site,
                    }
                    for old_site in old_here
                    for new_site in dirs
                    if max(old_site, new_site) < min(old_site + 4, new_site + 4)
                ],
                "old_sites_without_intersecting_candidate_dir32": [
                    f"0x{x:08x}" for x in old_here if x not in intersecting_old
                ],
                "new_dir32_without_intersecting_old_highlow": [
                    f"0x{x:08x}" for x in dirs if x not in intersecting_new
                ],
                "old_fields_straddling_candidate_body_boundary": [
                    f"0x{x:08x}"
                    for x in old_here
                    if not (x >= entry and x + 4 <= end)
                ],
                "candidate_relocations": info["relocations"],
            }
        )

    summary = {
        "placement_plan": str(args.placement_plan.resolve()) if args.placement_plan else None,
        "inplace_report": str(args.inplace_report.resolve()) if args.inplace_report else None,
        "fitting_candidate_bodies": len(rows),
        "original_text_highlow_sites": len(fixups),
        "unique_old_highlow_sites_touched": len(old_touched),
        "candidate_dir32_sites_for_fitting_bodies": len(new_dir32_sites),
        "exact_old_highlow_candidate_dir32_site_matches": len(exact_reuse),
        "old_sites_without_intersecting_candidate_dir32": len(old_touched - intersecting_old),
        "new_dir32_sites_without_intersecting_old_highlow": len(new_dir32_sites - intersecting_new),
        "old_sites_intersecting_any_candidate_dir32": len(intersecting_old),
        "new_dir32_sites_intersecting_any_old_highlow": len(intersecting_new),
        "exact_start_overlap_pairs": len(exact_pairs),
        "shifted_partial_overlap_pairs": len(shifted_pairs),
        "old_highlow_fields_straddling_candidate_body_boundaries": len(partial_old),
        "candidate_relocations_in_fitting_bodies": dict(sorted(candidate_reloc_counts.items())),
        "limitations": [
            "Exact field-site overlap is not proof that the relocated DWORD target value is correct.",
            "Old sites without candidate DIR32 require removal only if the replacement bytes no longer contain that absolute field; inspect instruction semantics before patching.",
            "New DIR32 fields require final preferred-base target resolution and PE base-relocation entries.",
            "Non-fitting bodies, appended-code placement, original data relocation rewriting, imports, PE startup, and runtime behavior are out of scope.",
            "No PE bytes are modified by this audit.",
        ],
        "results": rows,
    }
    with args.output.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(summary, stream, indent=2)
        stream.write("\n")
    print(
        "fitting_bodies={fitting_candidate_bodies} old_touched={unique_old_highlow_sites_touched} "
        "new_DIR32={candidate_dir32_sites_for_fitting_bodies} exact_site_matches={exact_old_highlow_candidate_dir32_site_matches} "
        "old_without_intersection={old_sites_without_intersecting_candidate_dir32} new_without_intersection={new_dir32_sites_without_intersecting_old_highlow} "
        "shifted_overlap_pairs={shifted_partial_overlap_pairs} "
        "boundary_straddlers={old_highlow_fields_straddling_candidate_body_boundaries}".format(**summary)
    )
    print(f"report={args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
