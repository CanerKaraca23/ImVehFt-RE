#!/usr/bin/env python3
"""Inventory original-ImVehFt-image VAs embedded in reconstructed sources."""

from __future__ import annotations

import argparse
import csv
import json
import re
import struct
from collections import Counter
from pathlib import Path


LITERAL = re.compile(r"(?<![A-Za-z0-9_])0[xX]([0-9A-Fa-f]{7,8})(?=[uUlL]*\b)")
CSV_FIELDS = [
    "address",
    "section",
    "exact_function_entry",
    "source",
    "line",
    "literal",
    "source_line",
]


def mask_comments_and_literals(text: str) -> str:
    """Replace C++ comments and quoted literal contents with spaces, keeping lines."""
    chars = list(text)
    i = 0
    state = "code"
    while i < len(chars):
        ch = chars[i]
        nxt = chars[i + 1] if i + 1 < len(chars) else ""
        if state == "code":
            if ch == "/" and nxt == "/":
                chars[i] = chars[i + 1] = " "
                i += 2
                state = "line_comment"
                continue
            if ch == "/" and nxt == "*":
                chars[i] = chars[i + 1] = " "
                i += 2
                state = "block_comment"
                continue
            if ch in ("\"", "'"):
                state = "string" if ch == "\"" else "character"
                chars[i] = " "
        elif state == "line_comment":
            if ch == "\n":
                state = "code"
            else:
                chars[i] = " "
        elif state == "block_comment":
            if ch == "*" and nxt == "/":
                chars[i] = chars[i + 1] = " "
                i += 2
                state = "code"
                continue
            if ch != "\n":
                chars[i] = " "
        else:
            quote = "\"" if state == "string" else "'"
            if ch == "\\":
                chars[i] = " "
                if nxt and nxt != "\n":
                    chars[i + 1] = " "
                    i += 2
                    continue
            elif ch == quote:
                chars[i] = " "
                state = "code"
            elif ch != "\n":
                chars[i] = " "
        i += 1
    return "".join(chars)


def pe_sections(image: bytes) -> tuple[int, dict[str, tuple[int, int]]]:
    pe = struct.unpack_from("<I", image, 0x3C)[0]
    section_count = struct.unpack_from("<H", image, pe + 6)[0]
    optional_size = struct.unpack_from("<H", image, pe + 20)[0]
    optional = pe + 24
    if image[pe : pe + 4] != b"PE\0\0" or struct.unpack_from("<H", image, optional)[0] != 0x10B:
        raise ValueError("expected an x86 PE32 image")
    image_base = struct.unpack_from("<I", image, optional + 28)[0]
    section_table = optional + optional_size
    sections: dict[str, tuple[int, int]] = {}
    for i in range(section_count):
        at = section_table + 40 * i
        name = image[at : at + 8].split(b"\0", 1)[0].decode("ascii")
        virtual_size, rva, raw_size = struct.unpack_from("<III", image, at + 8)
        sections[name] = (image_base + rva, image_base + rva + max(virtual_size, raw_size))
    return image_base, sections


def main() -> int:
    root = Path(__file__).resolve().parents[1]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("image", type=Path)
    parser.add_argument("--source-root", type=Path, default=root / "src/functions")
    parser.add_argument("--function-map", type=Path, default=root / "audit/function-name-map.csv")
    parser.add_argument("--csv", type=Path, required=True)
    parser.add_argument("--summary", type=Path, required=True)
    args = parser.parse_args()
    for output in (args.csv, args.summary):
        if output.exists():
            parser.error(f"refusing to overwrite existing output: {output}")

    _, sections = pe_sections(args.image.read_bytes())
    with args.function_map.open(encoding="utf-8-sig", newline="") as stream:
        names = {int(row["address"], 16): row["ghidra_name"] for row in csv.DictReader(stream)}

    records: list[dict[str, object]] = []
    for source in sorted(args.source_root.glob("*.cpp")):
        source_lines = source.read_text(encoding="utf-8-sig").splitlines()
        code = mask_comments_and_literals("\n".join(source_lines))
        for line_no, line in enumerate(code.splitlines(), 1):
            for match in LITERAL.finditer(line):
                address = int(match.group(1), 16)
                section = next(
                    (name for name, (start, end) in sections.items() if start <= address < end),
                    "outside-image-sections",
                )
                if section == "outside-image-sections":
                    continue
                records.append(
                    {
                        "address": f"0x{address:08X}",
                        "section": section,
                        "exact_function_entry": names.get(address, ""),
                        "source": source.relative_to(root).as_posix(),
                        "line": line_no,
                        "literal": match.group(0),
                        "source_line": source_lines[line_no - 1].strip(),
                    }
                )

    args.csv.parent.mkdir(parents=True, exist_ok=True)
    with args.csv.open("x", encoding="utf-8", newline="") as stream:
        writer = csv.DictWriter(stream, fieldnames=CSV_FIELDS)
        writer.writeheader()
        writer.writerows(records)
    counts = Counter(record["section"] for record in records)
    unique = {record["address"] for record in records}
    exact_targets = {record["address"] for record in records if record["exact_function_entry"]}
    summary = {
        "scope": "literal original-image VAs present in the 705 candidate source files, located against original PE virtual sections; not a semantic adjudication",
        "image": str(args.image.resolve()),
        "candidate_translation_units": len(list(args.source_root.glob("*.cpp"))),
        "occurrences": len(records),
        "unique_addresses": len(unique),
        "unique_exact_candidate_function_entries": len(exact_targets),
        "occurrences_by_section": dict(sorted(counts.items())),
        "addresses_without_exact_candidate_entry": len(unique - exact_targets),
        "csv": str(args.csv.resolve()),
        "limitations": [
            "comments and quoted string/character literals are excluded; address literals in executable code may still be function pointers, interior code labels, globals, tables, or intentional preferred-base references and require instruction/data-flow review",
            "the inventory does not prove a literal is incorrect and does not modify candidate sources",
        ],
    }
    args.summary.parent.mkdir(parents=True, exist_ok=True)
    with args.summary.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(summary, stream, indent=2)
        stream.write("\n")
    print(
        f"occurrences={len(records)} unique={len(unique)} "
        f"exact_candidate_entries={len(exact_targets)} sections={dict(counts)}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
