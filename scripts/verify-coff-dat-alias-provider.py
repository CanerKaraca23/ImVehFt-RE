#!/usr/bin/env python3
"""Verify generated MASM DAT aliases against COFF inventory and PE offsets."""

from __future__ import annotations

import argparse
import csv
import re
import subprocess
import sys
from pathlib import Path


SYMBOL_LINE = re.compile(
    r"^\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)\s+(SECT\d+)\s+"
    r"\S+(?:\s+\(\))?\s+External\s+\|\s+(\S+)"
)
SECTION_HEADER = re.compile(r"^SECTION HEADER #(\d+)$")
SECTION_NAME = re.compile(r"^\s+(\.\w+) name$")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("inventory", type=Path)
    parser.add_argument("storage", type=Path)
    parser.add_argument("object", type=Path)
    parser.add_argument("--dumpbin", type=Path, required=True)
    args = parser.parse_args()
    if not args.object.is_file() or not args.dumpbin.is_file():
        parser.error("object or dumpbin executable does not exist")

    headers = subprocess.run(
        [str(args.dumpbin), "/headers", str(args.object)],
        check=False,
        capture_output=True,
        text=True,
        encoding="utf-8",
        errors="replace",
    )
    symbols = subprocess.run(
        [str(args.dumpbin), "/symbols", str(args.object)],
        check=False,
        capture_output=True,
        text=True,
        encoding="utf-8",
        errors="replace",
    )
    if headers.returncode or symbols.returncode:
        sys.stderr.write(headers.stderr + symbols.stderr)
        return headers.returncode or symbols.returncode

    section_numbers: dict[str, str] = {}
    pending: str | None = None
    for line in headers.stdout.splitlines():
        match = SECTION_HEADER.match(line.strip())
        if match:
            pending = match.group(1)
            continue
        match = SECTION_NAME.match(line)
        if pending is not None and match:
            section_numbers[match.group(1)] = pending
            pending = None

    storage_rows: dict[str, dict[str, str]] = {}
    with args.storage.open("r", encoding="utf-8-sig", newline="") as stream:
        storage_rows = {row["address"].upper(): row for row in csv.DictReader(stream)}

    expected: dict[str, tuple[str, int, str]] = {}
    with args.inventory.open("r", encoding="utf-8-sig", newline="") as stream:
        for row in csv.DictReader(stream):
            address = row["address"].upper()
            section = storage_rows[address]["section"]
            expected_section = section_numbers.get(section)
            if expected_section is None:
                raise ValueError(f"provider object lacks section {section}")
            offset = int(storage_rows[address]["rva_in_section"], 16)
            defined = {name for name in row["defined_symbols"].split(" | ") if name}
            for name in (name for name in row["undefined_symbols"].split(" | ") if name):
                if name in defined:
                    continue
                location = (expected_section, offset, address)
                previous = expected.get(name)
                if previous is not None and previous != location:
                    raise ValueError(f"inventory maps {name} to multiple locations")
                expected[name] = location

    actual: dict[str, tuple[str, int]] = {}
    for line in symbols.stdout.splitlines():
        match = SYMBOL_LINE.match(line)
        if not match:
            continue
        offset, section, name = match.groups()
        if name.startswith(("_DAT_", "?DAT_", "?_DAT_")):
            actual[name] = (section.removeprefix("SECT"), int(offset, 16))

    mismatches = []
    for name, (section, offset, address) in expected.items():
        if actual.get(name) != (section, offset):
            mismatches.append(
                f"{name}: expected {section}+0x{offset:X} ({address}), got {actual.get(name)}"
            )
    extras = sorted(set(actual) - set(expected))
    missing = sorted(set(expected) - set(actual))
    print(
        f"expected names={len(expected)}; provider names={len(actual)}; "
        f"missing={len(missing)}; extras={len(extras)}; offset/section mismatches={len(mismatches)}"
    )
    for item in (missing + extras + mismatches)[:20]:
        print(item)
    return 1 if missing or extras or mismatches else 0


if __name__ == "__main__":
    raise SystemExit(main())
