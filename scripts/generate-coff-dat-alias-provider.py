#!/usr/bin/env python3
"""Generate a MASM alias-only probe for the audited ImVehFt DAT symbols.

The output deliberately contains zero padding only. It is a link-resolution
probe, not a runtime data image or a production plugin component.
"""

from __future__ import annotations

import argparse
import csv
from collections import defaultdict
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("inventory", type=Path, help="COFF DAT inventory CSV")
    parser.add_argument("storage", type=Path, help="PE storage classification CSV")
    parser.add_argument("--asm", type=Path, required=True, help="New MASM source path")
    args = parser.parse_args()

    with args.storage.open("r", encoding="utf-8-sig", newline="") as stream:
        storage = {row["address"].upper(): row for row in csv.DictReader(stream)}

    labels: dict[str, dict[int, list[str]]] = {
        ".const": defaultdict(list),
        ".data": defaultdict(list),
    }
    symbol_locations: dict[str, tuple[str, int]] = {}
    expected = 0
    with args.inventory.open("r", encoding="utf-8-sig", newline="") as stream:
        for row in csv.DictReader(stream):
            address = row["address"].upper()
            if address not in storage:
                raise ValueError(f"no PE storage mapping for {address}")
            item = storage[address]
            section = item["section"]
            segment = {".rdata": ".const", ".data": ".data"}.get(section)
            if segment is None:
                raise ValueError(f"unsupported PE section for {address}: {section}")
            offset = int(item["rva_in_section"], 16)
            undefined = [name for name in row["undefined_symbols"].split(" | ") if name]
            defined = {name for name in row["defined_symbols"].split(" | ") if name}
            for name in undefined:
                if name in defined:
                    continue
                previous = symbol_locations.get(name)
                location = (segment, offset)
                if previous is not None and previous != location:
                    raise ValueError(f"COFF external {name} maps to two addresses")
                symbol_locations[name] = location
                labels[segment][offset].append(name)
                expected += 1

    if expected == 0:
        raise ValueError("inventory contains no undefined DAT symbols")

    lines = [
        "; Generated alias-resolution probe; all storage bytes are zero.",
        "; Not a runtime image. Regenerate from the audited CSV inputs.",
        ".386",
        ".model flat",
        "option casemap:none",
        "",
    ]
    for segment in (".const", ".data"):
        lines.extend((segment,))
        cursor = 0
        for offset in sorted(labels[segment]):
            if offset < cursor:
                raise ValueError(f"non-monotonic label offset in {segment}")
            lines.append(f"    ORG 0{offset:X}h")
            for name in sorted(set(labels[segment][offset])):
                lines.append(f"PUBLIC {name}")
                lines.append(f"{name} LABEL BYTE")
            cursor = offset
        lines.append("    DB 0")
        lines.append("")
    lines.append("END")

    args.asm.parent.mkdir(parents=True, exist_ok=True)
    with args.asm.open("x", encoding="ascii", newline="\n") as stream:
        stream.write("\n".join(lines) + "\n")
    print(f"unique undefined decorated names: {len(symbol_locations)}")
    print(f"undefined name/address associations: {expected}")
    print(f"MASM source: {args.asm.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
