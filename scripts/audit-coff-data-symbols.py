#!/usr/bin/env python3
"""Inventory unresolved/defined ImVehFt DAT_* COFF symbols in an MSVC library."""

from __future__ import annotations

import argparse
import csv
import re
import subprocess
import sys
from collections import defaultdict
from pathlib import Path


SYMBOL_LINE = re.compile(
    r"^\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+(UNDEF|SECT\d+)\s+"
    r"\S+(?:\s+\(\))?\s+External\s+\|\s+(\S+)"
)
DAT_SYMBOL = re.compile(r"^\??_?DAT_([0-9A-Fa-f]{8})")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("library", type=Path, help="MSVC COFF .lib made from the audited objects")
    parser.add_argument("--dumpbin", type=Path, required=True, help="Path to x86 dumpbin.exe")
    parser.add_argument("--csv", type=Path, required=True, help="Output per-address CSV")
    args = parser.parse_args()

    if not args.library.is_file():
        parser.error(f"library not found: {args.library}")
    if not args.dumpbin.is_file():
        parser.error(f"dumpbin not found: {args.dumpbin}")

    run = subprocess.run(
        [str(args.dumpbin), "/symbols", str(args.library)],
        check=False,
        capture_output=True,
        text=True,
        encoding="utf-8",
        errors="replace",
    )
    if run.returncode:
        sys.stderr.write(run.stderr)
        return run.returncode

    undefined: dict[str, set[str]] = defaultdict(set)
    defined: dict[str, set[str]] = defaultdict(set)
    undefined_lines: dict[str, int] = defaultdict(int)
    for line in run.stdout.splitlines():
        match = SYMBOL_LINE.match(line)
        if not match:
            continue
        section, symbol = match.groups()
        dat_match = DAT_SYMBOL.match(symbol)
        if not dat_match:
            continue
        address = dat_match.group(1).lower()
        if section == "UNDEF":
            undefined[address].add(symbol)
            undefined_lines[address] += 1
        else:
            defined[address].add(symbol)

    addresses = sorted(set(undefined) | set(defined))
    args.csv.parent.mkdir(parents=True, exist_ok=True)
    with args.csv.open("x", encoding="utf-8", newline="") as stream:
        writer = csv.DictWriter(
            stream,
            fieldnames=(
                "address",
                "undefined_symbol_count",
                "undefined_reference_lines",
                "defined_symbol_count",
                "undefined_symbols",
                "defined_symbols",
            ),
        )
        writer.writeheader()
        for address in addresses:
            writer.writerow(
                {
                    "address": f"0x{address}",
                    "undefined_symbol_count": len(undefined[address]),
                    "undefined_reference_lines": undefined_lines[address],
                    "defined_symbol_count": len(defined[address]),
                    "undefined_symbols": " | ".join(sorted(undefined[address])),
                    "defined_symbols": " | ".join(sorted(defined[address])),
                }
            )

    undefined_addresses = [address for address in addresses if undefined[address]]
    multi_typed = sum(len(undefined[address]) > 1 for address in undefined_addresses)
    undefined_names = set().union(*undefined.values()) if undefined else set()
    defined_names = set().union(*defined.values()) if defined else set()
    missing_exact_names = undefined_names - defined_names
    print(
        f"DAT addresses={len(addresses)}; undefined addresses={len(undefined_addresses)}; "
        f"unique undefined decorated names={len(undefined_names)}; "
        f"names without an exact definition={len(missing_exact_names)}; "
        f"multiple undefined names at one address={multi_typed}; "
        f"defined addresses={sum(bool(defined[address]) for address in addresses)}"
    )
    print(f"CSV: {args.csv.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
