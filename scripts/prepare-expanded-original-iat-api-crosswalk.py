#!/usr/bin/env python3
"""Normalize a proven direct-body IAT crosswalk for the COFF thunk verifier."""

from __future__ import annotations

import argparse
import json
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--expanded-crosswalk", type=Path, required=True)
    parser.add_argument("--api-references", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")

    source = json.loads(args.expanded_crosswalk.read_text(encoding="utf-8"))
    references = json.loads(args.api_references.read_text(encoding="utf-8"))
    exact = [row for row in source["imports"]
             if row.get("status") == "exact-original-iat-match"]
    exact_by_symbol = {row["coff_code_symbol"]: row for row in exact}
    if len(exact_by_symbol) != len(exact):
        raise ValueError("expanded crosswalk repeats an exact code symbol")
    referenced = {row["target_code_symbol"] for row in references["rel32_references"]}
    if not referenced <= exact_by_symbol.keys():
        raise ValueError(f"API symbols lack an exact IAT crosswalk: {sorted(referenced - exact_by_symbol.keys())}")

    imports = []
    for symbol, row in sorted(exact_by_symbol.items()):
        matches = row["original_iat_matches_by_name_and_dll"]
        if len(matches) != 1:
            raise ValueError(f"{symbol}: expected exactly one selected IAT match")
        match = matches[0]
        imports.append({
            "coff_code_symbol": symbol,
            "status": "exact-original-iat-match",
            "iat_va": match["iat_va"],
            "original_iat_matches_by_name_and_dll": [match],
        })

    report = {
        "scope": "Normalized names and IAT VAs from an exact unique-name crosswalk; no thunk code is verified here.",
        "source_crosswalk": str(args.expanded_crosswalk.resolve()),
        "source_crosswalk_sha256": source["direct_coverage_sha256"],
        "api_references": str(args.api_references.resolve()),
        "candidate_direct_api_symbol_count": len(imports),
        "imports": imports,
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    print(json.dumps({"exact_iat_symbols": len(imports),
                      "referenced_symbols": len(referenced),
                      "all_referenced_symbols_crosswalked": True}, indent=2))
    print(f"report={args.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
