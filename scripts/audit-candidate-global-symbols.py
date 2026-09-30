#!/usr/bin/env python3
"""Inventory address-named ImVehFt state symbols used by candidate TUs."""

from __future__ import annotations

import argparse
import csv
import re
from collections import defaultdict
from pathlib import Path


SYMBOL = re.compile(r"\b_?(?:DAT|UNK)_(100[0-9a-fA-F]{5})\b", re.IGNORECASE)
DECLARATION = re.compile(
    r"\bextern(?:\s+\"C\")?\s+([^;{}]*?)\b"
    r"(_?(?:DAT|UNK)_(100[0-9a-fA-F]{5}))\s*(\[[^\]]*\])?\s*;",
    re.IGNORECASE | re.DOTALL,
)
COMMENTS = re.compile(r"//[^\n]*|/\*.*?\*/", re.DOTALL)
STRINGS = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', re.DOTALL)


def mask(match: re.Match[str]) -> str:
    return "".join("\n" if char == "\n" else " " for char in match.group(0))


def csv_list(values: set[str]) -> str:
    return "|".join(sorted(values))


def section(address: int) -> str:
    if 0x10001000 <= address <= 0x10021FFF:
        return ".text"
    if 0x10022000 <= address <= 0x10028FFF:
        return ".rdata"
    if 0x10029000 <= address <= 0x10042FFF:
        return ".data"
    return "outside-known-image-sections"


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--source-root", type=Path, default=Path("src/functions"))
    parser.add_argument(
        "--output", type=Path,
        default=Path("audit/candidate-global-address-inventory-2026-09-27.csv"),
    )
    args = parser.parse_args()

    files = sorted(args.source_root.glob("*.cpp"))
    names: dict[int, set[str]] = defaultdict(set)
    occurrences: dict[int, int] = defaultdict(int)
    source_files: dict[int, set[str]] = defaultdict(set)
    declarations: dict[int, list[str]] = defaultdict(list)
    types: dict[int, set[str]] = defaultdict(set)
    uses: dict[int, list[str]] = defaultdict(list)
    use_files: dict[int, set[str]] = defaultdict(set)
    use_tus: dict[int, set[str]] = defaultdict(set)

    for source in files:
        text = source.read_text(encoding="utf-8-sig")
        relative = source.as_posix()
        declaration_view = COMMENTS.sub(mask, text)
        code_view = STRINGS.sub(mask, declaration_view)
        declaration_spans: dict[int, list[tuple[int, int]]] = defaultdict(list)
        for match in DECLARATION.finditer(declaration_view):
            address = int(match.group(3), 16)
            declaration_spans[address].append((match.start(), match.end()))
            declared_type = " ".join(match.group(1).split())
            suffix = " ".join((match.group(4) or "").split())
            if suffix:
                declared_type += suffix
            types[address].add(declared_type)
            line = declaration_view.count("\n", 0, match.start()) + 1
            declarations[address].append(
                f"{relative}:{line}:{declared_type} {match.group(2)}"
            )

        for match in SYMBOL.finditer(code_view):
            address = int(match.group(1), 16)
            names[address].add(match.group(0).lstrip("_"))
            occurrences[address] += 1
            source_files[address].add(relative)
            if any(start <= match.start() < end for start, end in declaration_spans[address]):
                continue
            line = code_view.count("\n", 0, match.start()) + 1
            uses[address].append(f"{relative}:{line}")
            use_files[address].add(relative)
            use_tus[address].add(source.stem.lower())

    args.output.parent.mkdir(parents=True, exist_ok=True)
    fields = [
        "address", "section", "symbol_spellings", "occurrence_count",
        "declaration_count", "declared_types", "distinct_declared_types",
        "source_file_count", "source_files", "declaration_sites",
        "candidate_use_count", "candidate_use_file_count", "candidate_use_tus",
        "candidate_use_sites",
    ]
    with args.output.open("w", encoding="utf-8", newline="") as stream:
        writer = csv.DictWriter(stream, fieldnames=fields, lineterminator="\n")
        writer.writeheader()
        for address in sorted(names):
            writer.writerow(
                {
                    "address": f"0x{address:08x}",
                    "section": section(address),
                    "symbol_spellings": csv_list(names[address]),
                    "occurrence_count": occurrences[address],
                    "declaration_count": len(declarations[address]),
                    "declared_types": csv_list(types[address]),
                    "distinct_declared_types": len(types[address]),
                    "source_file_count": len(source_files[address]),
                    "source_files": csv_list(source_files[address]),
                    "declaration_sites": "|".join(declarations[address]),
                    "candidate_use_count": len(uses[address]),
                    "candidate_use_file_count": len(use_files[address]),
                    "candidate_use_tus": csv_list(use_tus[address]),
                    "candidate_use_sites": "|".join(uses[address]),
                }
            )

    conflicts = sum(1 for address in names if len(types[address]) > 1)
    unreferenced_from_known_image = sum(
        1 for address in names if section(address) == "outside-known-image-sections"
    )
    print(f"candidate translation units: {len(files)}")
    print(f"unique address-named DAT_/UNK_ locations: {len(names)}")
    print(f"locations with extern declarations: {sum(bool(declarations[a]) for a in names)}")
    print(f"locations with differing source declaration spellings: {conflicts}")
    print(f"locations outside known ImVehFt image sections: {unreferenced_from_known_image}")
    print(f"wrote {args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
