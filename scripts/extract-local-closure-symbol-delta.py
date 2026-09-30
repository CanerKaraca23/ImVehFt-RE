#!/usr/bin/env python3
"""Extract closure-only undefined-symbol counts from a combined link-map join."""

from __future__ import annotations

import argparse
import json
from collections import Counter
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def counts(report: dict[str, object]) -> Counter[tuple[str, str]]:
    return Counter({(str(row["relocation_type"]), str(row["symbol"])): int(row["occurrences"])
                    for row in report["symbols"]})


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--closure", type=Path, default=ROOT / "audit/appended-thunk-local-section-closure-2026-09-30-v2.json")
    p.add_argument("--combined-link-map", type=Path, default=ROOT / "audit/appended-thunk-full-local-closure-diagnostic-link-map-2026-09-30.json")
    p.add_argument("--root-link-map", type=Path, default=ROOT / "audit/appended-thunk-link-map-resolution-conservative-current-2026-09-30.json")
    p.add_argument("--output", type=Path, required=True)
    a = p.parse_args()
    if a.output.exists():
        raise FileExistsError(f"refusing to overwrite {a.output}")
    closure = json.loads(a.closure.read_text(encoding="utf-8"))
    combined = json.loads(a.combined_link_map.read_text(encoding="utf-8"))
    roots = json.loads(a.root_link_map.read_text(encoding="utf-8"))
    extras: Counter[tuple[str, str]] = Counter()
    for section in closure["sections"]:
        for row in section["relocations"]:
            if row["target_class"] == "undefined-external":
                extras[(str(row["type"]), str(row["target_symbol"]))] += 1
    root_counts = counts(roots)
    combined_counts = counts(combined)
    joined = {(str(row["relocation_type"]), str(row["symbol"])): row for row in combined["symbols"]}
    rows = []
    for key, extra_count in sorted(extras.items()):
        delta = combined_counts[key] - root_counts[key]
        if delta != extra_count:
            raise ValueError(f"combined diagnostic count mismatch for {key}: {delta} != {extra_count}")
        row = joined.get(key)
        if row is None:
            raise ValueError(f"closure symbol not found in combined diagnostic map: {key}")
        rows.append({**row, "occurrences": extra_count})
    if sum(int(row["occurrences"]) for row in rows) != closure["undefined_external_occurrences_in_local_sections"]:
        raise ValueError("closure-only occurrence total mismatch")
    report = {
        "scope": "Closure-only undefined symbol pairs, after exact subtraction of the existing root-body link-map inventory.",
        "closure_report": str(a.closure.resolve()),
        "combined_link_map_report": str(a.combined_link_map.resolve()),
        "root_link_map_report": str(a.root_link_map.resolve()),
        "undefined_occurrences": sum(int(row["occurrences"]) for row in rows),
        "unique_symbol_type_pairs": len(rows),
        "symbols": rows,
        "limitations": ["Diagnostic symbol addresses are not production target VAs.",
                        "Classification does not resolve section placement, types, lifetimes, or initialization."]
    }
    a.output.parent.mkdir(parents=True, exist_ok=True)
    a.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(f"PASS: closure delta has {report['undefined_occurrences']} occurrences in {report['unique_symbol_type_pairs']} exact symbol/type pairs")
    print(f"report={a.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
