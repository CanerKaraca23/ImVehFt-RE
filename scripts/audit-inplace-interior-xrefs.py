#!/usr/bin/env python3
"""Audit saved Ghidra non-entry references landing inside planned in-place candidate bodies."""

from __future__ import annotations

import argparse
import csv
import json
from collections import Counter
from pathlib import Path


def load_csv(path: Path):
    with path.open(encoding="utf-8-sig", newline="") as f:
        return list(csv.DictReader(f))


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--placement-plan", type=Path, required=True)
    ap.add_argument("--nonentry-xrefs", type=Path, required=True)
    ap.add_argument("--codeunit-context", type=Path, required=True)
    ap.add_argument("--output", type=Path, required=True)
    a = ap.parse_args()
    if a.output.exists():
        raise FileExistsError(f"refusing to overwrite {a.output}")
    plan_bytes = a.placement_plan.read_bytes()
    plan = json.loads(plan_bytes)
    if plan.get("candidate_count") != 705:
        raise ValueError("expected full 705-entry plan")
    direct = {int(r["address"], 16): int(r["candidate_body_size"])
              for r in plan["entries"] if r["placement_mode"] == "body-at-entry"}
    refs = load_csv(a.nonentry_xrefs)
    contexts = load_csv(a.codeunit_context)
    context_index = {}
    for row in contexts:
        context_index.setdefault((row["target_va"].lower(), row["source_va"].lower()), row)
    by_entry = {entry: [] for entry in direct}
    for ref in refs:
        target = int(ref["target_va"], 16)
        for entry, size in direct.items():
            if entry <= target < entry + size:
                context = context_index.get((ref["target_va"].lower(), ref["source_va"].lower()))
                by_entry[entry].append({
                    **ref,
                    "target_offset_from_entry": target - entry,
                    "reference_origin": "self" if entry <= int(ref["source_va"], 16) < entry + size else "external",
                    "target_unit_type": context["target_unit_type"] if context else None,
                    "target_unit": context["target_unit"] if context else None,
                    "source_unit_type": context["source_unit_type"] if context else None,
                    "source_unit": context["source_unit"] if context else None,
                })
    results = [{
        "entry_va": f"0x{entry:08x}", "candidate_body_size": direct[entry],
        "interior_reference_count": len(by_entry[entry]),
        "references": by_entry[entry],
    } for entry in sorted(direct)]
    all_refs = [ref for refs_for_entry in by_entry.values() for ref in refs_for_entry]
    report = {
        "scope": "Saved Ghidra non-entry reference crosswalk against all candidate bodies still assigned direct in-place replacement.",
        "placement_plan": str(a.placement_plan.resolve()),
        "placement_plan_sha256": __import__("hashlib").sha256(plan_bytes).hexdigest().upper(),
        "nonentry_xref_export": str(a.nonentry_xrefs.resolve()),
        "codeunit_context_export": str(a.codeunit_context.resolve()),
        "direct_candidate_bodies": len(direct),
        "interior_reference_count": len(all_refs),
        "candidate_bodies_with_interior_references": sum(bool(v) for v in by_entry.values()),
        "reference_types": dict(Counter(r["reference_type"] for r in all_refs)),
        "reference_origins": dict(Counter(r["reference_origin"] for r in all_refs)),
        "target_unit_types": dict(Counter(str(r["target_unit_type"]) for r in all_refs)),
        "source_unit_types": dict(Counter(str(r["source_unit_type"]) for r in all_refs)),
        "limitations": [
            "Only saved static Ghidra non-entry xrefs are represented; runtime-computed/external references can be absent.",
            "A reference into a replaced span is not automatically unsafe if equivalent behavior is preserved, but it requires explicit redirection or byte/semantic adjudication.",
            "No PE bytes are modified and no loader/runtime behavior is tested.",
        ],
        "entries": results,
    }
    a.output.parent.mkdir(parents=True, exist_ok=True)
    with a.output.open("x", encoding="utf-8", newline="\n") as f:
        json.dump(report, f, indent=2)
        f.write("\n")
    print(json.dumps({k: report[k] for k in (
        "direct_candidate_bodies", "interior_reference_count",
        "candidate_bodies_with_interior_references", "reference_types",
        "reference_origins", "target_unit_types", "source_unit_types"
    )}, indent=2))
    print(f"report={a.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
