#!/usr/bin/env python3
"""Run the installed ReAgent parity engine on this repo's current 705 TUs."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import sys
from pathlib import Path


def main() -> int:
    root = Path(__file__).resolve().parents[1]
    owner = root.parents[1]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--output",
        type=Path,
        default=root / "build/parity-current-705-sourcehash-refresh-20260929.json",
    )
    parser.add_argument(
        "--reagent-source", type=Path, default=owner / "reagent/src"
    )
    parser.add_argument(
        "--config", type=Path, default=owner / "re-agent.yaml"
    )
    parser.add_argument(
        "--ghidra-export", type=Path, default=owner / "ghidra_exports"
    )
    args = parser.parse_args()
    if args.output.exists():
        parser.error(f"refusing to overwrite report: {args.output}")
    if not args.reagent_source.is_dir():
        parser.error(f"ReAgent source not found: {args.reagent_source}")

    sys.path.insert(0, str(args.reagent_source.resolve()))
    from re_agent.backend.exports import GhidraExportsBackend
    from re_agent.config.loader import load_config
    from re_agent.core.models import HookEntry, ParityStatus
    from re_agent.parity.engine import run_parity

    config = load_config(args.config.resolve())
    config.project_profile.source_root = str((root / "src/functions").resolve())
    config.project_profile.source_extensions = [".cpp"]
    config.backend.type = "ghidra-json"
    config.backend.export_dir = str(args.ghidra_export.resolve())
    config.parity.manual_checks_file = str(
        (owner / "reports/re-agent/manual-parity-checks.md").resolve()
    )
    config.parity.semantic_rules_file = str(
        (owner / "reports/re-agent/semantic-rules.json").resolve()
    )

    manifest = root / "audit/function-name-map.csv"
    manifest_bytes = manifest.read_bytes()
    hooks: list[HookEntry] = []
    with manifest.open(encoding="utf-8-sig", newline="") as stream:
        for row in csv.DictReader(stream):
            hooks.append(
                HookEntry(
                    class_path="",
                    fn_name=row["ghidra_name"],
                    address="0x" + row["address"],
                    reversed=True,
                    locked=False,
                    is_virtual=False,
                )
            )
    if len(hooks) != 705:
        parser.error(f"expected 705 function-map rows, got {len(hooks)}")

    backend = GhidraExportsBackend(config.backend.export_dir)
    results = run_parity(hooks, Path(config.project_profile.source_root), config, backend)
    counts = {status.value: 0 for status in ParityStatus}
    records = []
    for result in results:
        status = result["status"]
        status_value = status.value if isinstance(status, ParityStatus) else str(status)
        counts[status_value] = counts.get(status_value, 0) + 1
        hook = result["hook"]
        source = result.get("source")
        records.append(
            {
                "address": hook.address,
                "symbol": hook.symbol,
                "status": status_value,
                "source_path": getattr(source, "path", None),
                "findings": [
                    {"level": finding.level, "reason": finding.reason}
                    for finding in result.get("findings", [])
                ],
            }
        )

    report = {
        "scope": "ReAgent parity engine; current candidate TUs, Ghidra JSON, structural only",
        "reagent_source": str(args.reagent_source.resolve()),
        "candidate_source_root": str((root / "src/functions").resolve()),
        "function_map_sha256": hashlib.sha256(manifest_bytes).hexdigest(),
        "candidate_translation_units": len(results),
        "counts": counts,
        "results": records,
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    print(
        f"ReAgent parity: {len(results)} targets; "
        f"GREEN={counts.get('green', 0)} YELLOW={counts.get('yellow', 0)} "
        f"RED={counts.get('red', 0)}"
    )
    print(f"Report: {args.output.resolve()}")
    return 0 if len(results) == 705 and counts.get("red", 0) == 0 else 1


if __name__ == "__main__":
    raise SystemExit(main())
