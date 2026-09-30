#!/usr/bin/env python3
"""Run ReAgent's non-LLM objective verifier against all address-named TUs."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import sys
from pathlib import Path


def main() -> int:
    repo_root = Path(__file__).resolve().parents[1]
    owner_root = repo_root.parents[1]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--reagent-source", type=Path, default=owner_root / "reagent" / "src")
    parser.add_argument("--ghidra-export", type=Path, default=owner_root / "ghidra_exports")
    parser.add_argument(
        "--output",
        type=Path,
        default=repo_root / "audit" / "objective-independent-rerun-2026-09-27.json",
    )
    args = parser.parse_args()

    reagent_source = args.reagent_source.resolve()
    if not reagent_source.is_dir():
        parser.error(f"ReAgent source directory not found: {reagent_source}")
    sys.path.insert(0, str(reagent_source))

    from re_agent.backend.exports import GhidraExportsBackend
    from re_agent.core.models import FunctionTarget
    from re_agent.verification.objective import verify_candidate

    if args.output.exists():
        parser.error(f"Refusing to overwrite existing report: {args.output}")

    backend = GhidraExportsBackend(str(args.ghidra_export.resolve()))
    manifest = repo_root / "audit" / "function-name-map.csv"
    results: list[dict[str, object]] = []
    with manifest.open(encoding="utf-8-sig", newline="") as stream:
        for row in csv.DictReader(stream):
            source_path = repo_root / row["source_path"]
            source_bytes = source_path.read_bytes()
            target = FunctionTarget(
                address="0x" + row["address"],
                class_name="",
                function_name=row["ghidra_name"],
            )
            verdict = verify_candidate(
                source_bytes.decode("utf-8", errors="replace"),
                target,
                backend,
                call_count_tolerance=3,
                control_flow_tolerance=2,
            )
            results.append(
                {
                    "address": row["address"].lower(),
                    "source": row["source_path"],
                    "source_sha256": hashlib.sha256(source_bytes).hexdigest(),
                    "verdict": verdict.verdict.value,
                    "summary": verdict.summary,
                    "findings": verdict.findings,
                }
            )

    counts = {
        verdict: sum(result["verdict"] == verdict for result in results)
        for verdict in ("PASS", "FAIL", "UNKNOWN")
    }
    report = {
        "scope": "structural ReAgent objective verifier only; not semantic equivalence or runtime proof",
        "reagent_source": str(reagent_source),
        "ghidra_export": str(args.ghidra_export.resolve()),
        "candidate_translation_units": len(results),
        "counts": counts,
        "results": results,
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")

    print(
        f"Objective verifier: {len(results)} targets; "
        f"PASS={counts['PASS']} FAIL={counts['FAIL']} UNKNOWN={counts['UNKNOWN']}"
    )
    print(f"Report: {args.output.resolve()}")
    return 0 if len(results) == 705 and counts["FAIL"] == 0 and counts["UNKNOWN"] == 0 else 1


if __name__ == "__main__":
    raise SystemExit(main())
