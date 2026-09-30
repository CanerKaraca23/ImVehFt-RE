#!/usr/bin/env python3
"""Export unique .text HIGHLOW source VAs for a read-only Ghidra owner query."""

from __future__ import annotations

import argparse
import csv
import json
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("inventory", type=Path)
    parser.add_argument("output", type=Path)
    args = parser.parse_args()

    inventory = json.loads(args.inventory.read_text(encoding="utf-8"))
    addresses = sorted(
        {
            row["site_va"]
            for row in inventory["all_highlow_relocations"]
            if row["site_section"] == ".text"
        },
        key=lambda value: int(value, 16),
    )
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("x", encoding="utf-8", newline="") as stream:
        writer = csv.writer(stream, lineterminator="\n")
        writer.writerow(["address"])
        writer.writerows([[address] for address in addresses])
    print(f"Exported {len(addresses)} unique .text HIGHLOW sites to {args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
