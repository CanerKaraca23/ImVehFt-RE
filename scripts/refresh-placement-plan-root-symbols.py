#!/usr/bin/env python3
"""Refresh technical COFF root-symbol names while preserving proven body spans."""

from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
PARSER = ROOT / "scripts/audit-inplace-candidate-relocations.py"


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--plan", type=Path, required=True)
    ap.add_argument("--objects", type=Path, required=True)
    ap.add_argument("--override", action="append", default=[], metavar="VA=SYMBOL")
    ap.add_argument("--output", type=Path, required=True)
    args = ap.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")

    spec = importlib.util.spec_from_file_location("candidate_coff", PARSER)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot import {PARSER}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)

    plan_bytes = args.plan.read_bytes()
    plan = json.loads(plan_bytes)
    if plan.get("candidate_count") != 705 or len(plan.get("entries", [])) != 705:
        raise ValueError("expected a complete 705-entry placement plan")
    by_va = {row["address"].lower(): row for row in plan["entries"]}
    updates = []
    for override in args.override:
        va, symbol = override.split("=", 1)
        va = va.lower()
        if va not in by_va:
            raise ValueError(f"placement plan has no entry at {va}")
        row = by_va[va]
        obj = args.objects / f"{int(va, 16):08x}.obj"
        body, info = module.parse_coff(obj, symbol)
        if len(body) != row["candidate_body_size"]:
            raise ValueError(
                f"{va}: COFF body size {len(body)} differs from planned "
                f"{row['candidate_body_size']} bytes; rebuild placement evidence first"
            )
        old_symbol = row["entry_symbol"]
        row["entry_symbol"] = symbol
        row["current_object_sha256"] = info["object_sha256"]
        updates.append({
            "address": va,
            "old_entry_symbol": old_symbol,
            "new_entry_symbol": symbol,
            "body_size": len(body),
            "body_sha256": hashlib.sha256(body).hexdigest().upper(),
            "object_sha256": info["object_sha256"],
            "relocation_count": len(info["relocations"]),
        })

    plan["root_symbol_refresh"] = {
        "source_plan_sha256": hashlib.sha256(plan_bytes).hexdigest().upper(),
        "current_objects": str(args.objects.resolve()),
        "overrides": updates,
        "scope": "Only COFF entry-symbol names changed; each current object's body byte length was checked against the plan. Placement coordinates and instruction-boundary results are inherited, not recalculated.",
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(plan, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"overrides": updates, "output": str(args.output.resolve())}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
