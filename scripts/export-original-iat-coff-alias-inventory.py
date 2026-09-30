#!/usr/bin/env python3
"""Export verified original-IAT symbols as address,symbol CSV aliases."""

from __future__ import annotations

import argparse
import csv
import json
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--crosswalk", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")
    report = json.loads(args.crosswalk.read_text(encoding="utf-8"))
    rows = [row for row in report["imports"] if row["status"] == "exact-original-iat-match"]
    if len(rows) != report["candidate_direct_api_symbol_count"]:
        raise ValueError("crosswalk includes unmatched or ambiguous imports")
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("x", encoding="utf-8", newline="") as stream:
        writer = csv.DictWriter(stream, fieldnames=("address", "symbol"), lineterminator="\n")
        writer.writeheader()
        for row in rows:
            writer.writerow({
                "address": row["iat_va"],
                "symbol": "__imp_" + row["coff_code_symbol"],
            })
    print(f"aliases={len(rows)} csv={args.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
