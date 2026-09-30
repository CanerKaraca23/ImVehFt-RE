#!/usr/bin/env python3
"""Compare original Ghidra cookie-check calls with default-GS and no-GS COFFs."""

from __future__ import annotations

import argparse
import importlib.util
import json
import re
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
GHIDRA_CALL = re.compile(r"\bCALL\s+0x100172d5\b", re.IGNORECASE)
CHECK_SYMBOL = "@__security_check_cookie@4"
COOKIE_SYMBOLS = {"___security_cookie", "___security_cookie_complement"}


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--ghidra-dir",
        type=Path,
        default=ROOT.parents[1] / "ghidra_exports",
    )
    parser.add_argument(
        "--placement-report",
        type=Path,
        default=ROOT / "audit/inplace-candidate-relocation-coverage-entry-exact-2026-09-29.json",
    )
    parser.add_argument(
        "--default-gs-dir",
        type=Path,
        default=ROOT / "build/recheck/strict-xcode-entry-exact-ehcookie-20260929",
    )
    parser.add_argument(
        "--no-gs-dir",
        type=Path,
        default=ROOT / "build/recheck/strict-xcode-nogs-ehcookie-20260929",
    )
    parser.add_argument(
        "--output",
        type=Path,
        default=ROOT / "audit/gs-callsite-reconciliation-2026-09-29.json",
    )
    args = parser.parse_args()
    if args.output.exists():
        parser.error(f"refusing to overwrite {args.output}")

    helper_path = Path(__file__).with_name("audit-candidate-relocation-symbol-targets.py")
    spec = importlib.util.spec_from_file_location("coff_audit", helper_path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot load COFF parser: {helper_path}")
    coff_audit = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(coff_audit)

    placements = json.loads(args.placement_report.read_text(encoding="utf-8"))["results"]
    if len(placements) != 705:
        raise ValueError(f"expected 705 candidate entries, got {len(placements)}")

    rows: list[dict[str, object]] = []
    for placement in placements:
        address = placement["entry_va"][2:].lower()
        symbol = placement["symbol"]
        export = json.loads((args.ghidra_dir / f"{address}.json").read_text(encoding="utf-8"))
        original_calls = sum(bool(GHIDRA_CALL.search(line)) for line in export.get("assembly", []))
        object_rows = []
        for variant, directory in (("default_gs", args.default_gs_dir), ("no_gs", args.no_gs_dir)):
            obj = coff_audit.read_object(directory / f"{address}.obj", symbol)
            relocs = obj["relocations"]
            object_rows.append(
                {
                    "variant": variant,
                    "check_call_relocations": sum(r["symbol"] == CHECK_SYMBOL for r in relocs),
                    "compiler_cookie_relocations": sum(r["symbol"] in COOKIE_SYMBOLS for r in relocs),
                }
            )
        rows.append(
            {
                "address": "0x" + address,
                "ghidra_name": export["name"],
                "original_check_call_sites": original_calls,
                "coff_variants": object_rows,
            }
        )

    summaries: dict[str, dict[str, int]] = {}
    for variant in ("default_gs", "no_gs"):
        calls = [
            next(v["check_call_relocations"] for v in row["coff_variants"] if v["variant"] == variant)
            for row in rows
        ]
        cookies = [
            next(v["compiler_cookie_relocations"] for v in row["coff_variants"] if v["variant"] == variant)
            for row in rows
        ]
        summaries[variant] = {
            "check_call_relocations": sum(calls),
            "functions_with_check_call_relocations": sum(value > 0 for value in calls),
            "compiler_cookie_relocations": sum(cookies),
            "functions_with_compiler_cookie_relocations": sum(value > 0 for value in cookies),
        }
    summaries["original_ghidra"] = {
        "check_call_sites": sum(row["original_check_call_sites"] for row in rows),
        "functions_with_check_call_sites": sum(row["original_check_call_sites"] > 0 for row in rows),
    }

    report = {
        "scope": "Static call-site/COFF relocation reconciliation only; not path-equivalence, runtime, or production-link proof.",
        "inputs": {
            "ghidra_exports": str(args.ghidra_dir.resolve()),
            "placement_report": str(args.placement_report.resolve()),
            "default_gs_objects": str(args.default_gs_dir.resolve()),
            "no_gs_objects": str(args.no_gs_dir.resolve()),
        },
        "summary": summaries,
        "functions": rows,
    }
    with args.output.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")

    print(f"functions={len(rows)} original_calls={summaries['original_ghidra']['check_call_sites']}")
    print(f"default_gs={summaries['default_gs']}")
    print(f"no_gs={summaries['no_gs']}")
    print(f"report={args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
