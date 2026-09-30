#!/usr/bin/env python3
"""Compare selected IA32 COFF function bodies and relocations across object builds."""

from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path


def load_parser(repo: Path):
    path = repo / "scripts" / "audit-inplace-candidate-relocations.py"
    spec = importlib.util.spec_from_file_location("inplace_candidate_relocations", path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot load COFF parser: {path}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module.parse_coff


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--repo", type=Path, required=True)
    parser.add_argument("--placement-plan", type=Path, required=True)
    parser.add_argument("--first-objects", type=Path, required=True)
    parser.add_argument("--second-objects", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")
    parse_coff = load_parser(args.repo.resolve())
    plan = json.loads(args.placement_plan.read_text(encoding="utf-8"))
    if plan.get("candidate_count") != 705 or len(plan.get("entries", [])) != 705:
        raise ValueError("expected complete 705-entry placement plan")

    rows = []
    for entry in plan["entries"]:
        address = int(entry["address"], 16)
        name = f"{address:08x}.obj"
        first_bytes, first_info = parse_coff(args.first_objects / name, entry["entry_symbol"])
        second_bytes, second_info = parse_coff(args.second_objects / name, entry["entry_symbol"])
        first_relocs = first_info["relocations"]
        second_relocs = second_info["relocations"]
        rows.append({
            "entry_va": entry["address"],
            "symbol": entry["entry_symbol"],
            "first_size": len(first_bytes),
            "second_size": len(second_bytes),
            "body_bytes_identical": first_bytes == second_bytes,
            "first_body_sha256": hashlib.sha256(first_bytes).hexdigest().upper(),
            "second_body_sha256": hashlib.sha256(second_bytes).hexdigest().upper(),
            "relocations_identical": first_relocs == second_relocs,
            "section_number_identical": first_info["section_number"] == second_info["section_number"],
        })

    result = {
        "scope": "Compares the root .xcode bytes, COFF relocation records, and section identity; ignores COFF container metadata.",
        "placement_plan": str(args.placement_plan.resolve()),
        "first_objects": str(args.first_objects.resolve()),
        "second_objects": str(args.second_objects.resolve()),
        "candidate_count": len(rows),
        "body_byte_mismatches": sum(not row["body_bytes_identical"] for row in rows),
        "relocation_mismatches": sum(not row["relocations_identical"] for row in rows),
        "section_number_mismatches": sum(not row["section_number_identical"] for row in rows),
        "mismatches": [row for row in rows if not (row["body_bytes_identical"] and row["relocations_identical"] and row["section_number_identical"])],
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({key: value for key, value in result.items() if key not in ("mismatches",)}, indent=2))
    print(f"report={args.output.resolve()}")
    return 0 if (result["candidate_count"] == 705 and not result["body_byte_mismatches"]
                 and not result["relocation_mismatches"] and not result["section_number_mismatches"]) else 1


if __name__ == "__main__":
    raise SystemExit(main())
