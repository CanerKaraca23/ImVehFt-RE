#!/usr/bin/env python3
"""Cross-reference PE .rdata/.data HIGHLOW fixups with candidate symbols."""

from __future__ import annotations

import argparse
import csv
import json
from collections import Counter, defaultdict
from pathlib import Path


def address(text: str) -> int:
    return int(text, 16)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("relocations_json", type=Path)
    parser.add_argument("function_map", type=Path)
    parser.add_argument("dat_inventory", type=Path)
    parser.add_argument("--csv", type=Path, required=True)
    args = parser.parse_args()

    relocation_data = json.loads(args.relocations_json.read_text(encoding="utf-8"))
    relocations = relocation_data.get("data_section_highlow_relocations")
    if relocations is None:
        parser.error("relocation JSON lacks data_section_highlow_relocations; rerun PE inventory")

    functions: dict[int, str] = {}
    with args.function_map.open("r", encoding="utf-8-sig", newline="") as stream:
        for row in csv.DictReader(stream):
            functions[address(row["address"])] = row["ghidra_name"]
    globals_by_va: dict[int, list[str]] = defaultdict(list)
    with args.dat_inventory.open("r", encoding="utf-8-sig", newline="") as stream:
        for row in csv.DictReader(stream):
            va = address(row["address"])
            globals_by_va[va].extend(
                name for name in row["undefined_symbols"].split(" | ") if name
            )
            globals_by_va[va].extend(
                name for name in row["defined_symbols"].split(" | ") if name
            )

    fields = (
        "site_va",
        "site_section",
        "stored_va",
        "target_section",
        "exact_candidate_function",
        "exact_candidate_global",
        "stored_value_points_inside_image",
    )
    pair_counts: Counter[tuple[str, str]] = Counter()
    pair_targets: dict[tuple[str, str], set[int]] = defaultdict(set)
    function_hit_records = 0
    function_hit_targets: set[int] = set()
    global_hit_records = 0
    global_hit_targets: set[int] = set()
    args.csv.parent.mkdir(parents=True, exist_ok=True)
    with args.csv.open("x", encoding="utf-8", newline="") as stream:
        writer = csv.DictWriter(stream, fieldnames=fields, lineterminator="\n")
        writer.writeheader()
        for row in relocations:
            target = address(row["stored_va"])
            site_section = row["site_section"]
            target_section = row["target_section"]
            function_name = functions.get(target, "")
            global_names = globals_by_va.get(target, [])
            if function_name:
                function_hit_records += 1
                function_hit_targets.add(target)
            if global_names:
                global_hit_records += 1
                global_hit_targets.add(target)
            pair = (site_section, target_section)
            pair_counts[pair] += 1
            pair_targets[pair].add(target)
            writer.writerow(
                {
                    **row,
                    "exact_candidate_function": function_name,
                    "exact_candidate_global": " | ".join(sorted(set(global_names))),
                }
            )

    print(f"rdata/data-site HIGHLOW records: {sum(pair_counts.values())}")
    for (site_section, target_section), count in sorted(pair_counts.items()):
        targets = len(pair_targets[(site_section, target_section)])
        print(f"{site_section} -> {target_section}: {count} sites, {targets} unique targets")
    print(
        "exact targets at 705 candidate function entries: "
        f"{function_hit_records} relocation records / {len(function_hit_targets)} unique targets"
    )
    print(
        "exact targets at a COFF DAT address start: "
        f"{global_hit_records} relocation records / {len(global_hit_targets)} unique targets"
    )
    print(f"CSV: {args.csv.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
