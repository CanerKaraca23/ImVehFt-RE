#!/usr/bin/env python3
"""Cross-reference linked UCRT/VCRuntime publics with named recovered candidates."""

from __future__ import annotations

import argparse
import csv
import re
from collections import defaultdict
from pathlib import Path


MAP_PUBLIC = re.compile(
    r"^\s+(?P<section>[0-9A-Fa-f]{4}):[0-9A-Fa-f]{8}\s+"
    r"(?P<symbol>\S+)\s+[0-9A-Fa-f]{8}\s+f\s+(?P<module>.+?)\s*$"
)
ADDRESS_OBJECT = re.compile(r"(?P<address>10[0-9a-fA-F]{6})\.obj$")


def normalize(name: str) -> str:
    return name.casefold().lstrip("_")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--map", required=True, type=Path)
    parser.add_argument("--function-name-map", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()
    if args.output.exists():
        parser.error(f"refusing to overwrite {args.output}")

    candidates: dict[str, list[dict[str, str]]] = defaultdict(list)
    with args.function_name_map.open("r", encoding="utf-8-sig", newline="") as stream:
        for row in csv.DictReader(stream):
            if row["original_name_status"] == "auto-generated-address-label":
                continue
            candidates[normalize(row["ghidra_name"])].append(row)

    symbols_by_address: dict[str, set[str]] = defaultdict(set)
    selected_runtime: dict[str, set[str]] = defaultdict(set)
    for line in args.map.read_text(encoding="utf-8", errors="replace").splitlines():
        match = MAP_PUBLIC.match(line)
        if not match:
            continue
        section = match.group("section").upper()
        symbol = match.group("symbol")
        module = match.group("module").strip()
        if section == "0001":
            address_match = ADDRESS_OBJECT.search(module)
            if address_match:
                symbols_by_address[address_match.group("address").lower()].add(symbol)
        elif section == "0002" and any(
            library in module.casefold() for library in ("ucrt", "vcruntime")
        ):
            selected_runtime[symbol].add(module)

    output_rows: list[dict[str, str]] = []
    for symbol in sorted(selected_runtime, key=str.casefold):
        matches = candidates.get(normalize(symbol), [])
        for row in matches:
            address = row["address"].lower()
            object_symbols = sorted(symbols_by_address.get(address, set()))
            output_rows.append(
                {
                    "linked_crt_symbol": symbol,
                    "linked_crt_modules": " | ".join(sorted(selected_runtime[symbol])),
                    "candidate_address": row["address"],
                    "candidate_ghidra_name": row["ghidra_name"],
                    "candidate_name_status": row["original_name_status"],
                    "candidate_coff_symbols": " | ".join(object_symbols),
                    "exact_coff_symbol_match": str(symbol in object_symbols).lower(),
                    "candidate_signature": row["signature"],
                }
            )

    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("x", encoding="utf-8", newline="") as stream:
        writer = csv.DictWriter(stream, fieldnames=list(output_rows[0]) if output_rows else [
            "linked_crt_symbol", "linked_crt_modules", "candidate_address",
            "candidate_ghidra_name", "candidate_name_status", "candidate_coff_symbols",
            "exact_coff_symbol_match", "candidate_signature",
        ])
        writer.writeheader()
        writer.writerows(output_rows)
    print(f"linked UCRT/VCRuntime publics: {len(selected_runtime)}")
    print(f"named candidate overlaps: {len(output_rows)}")
    print(
        "exact COFF symbol matches: "
        f"{sum(row['exact_coff_symbol_match'] == 'true' for row in output_rows)}"
    )
    print(f"CSV: {args.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
