#!/usr/bin/env python3
"""Check Ghidra-mapped callback JMP stubs and their COFF REL32 targets."""

from __future__ import annotations

import argparse
import csv
import struct
from pathlib import Path


def name_of(record: bytes, strings: bytes) -> str:
    if record[:4] == b"\0\0\0\0":
        offset = struct.unpack_from("<L", record, 4)[0]
        end = strings.find(b"\0", offset)
        if end < 0:
            raise ValueError("unterminated COFF symbol name")
        return strings[offset:end].decode("ascii")
    return record[:8].rstrip(b"\0").decode("ascii")


def verify(obj: Path, manifest: Path) -> None:
    with manifest.open(encoding="utf-8-sig", newline="") as stream:
        rows = sorted(csv.DictReader(stream), key=lambda row: row["label_address"])
    if not rows:
        raise ValueError("empty callback JMP manifest")
    thunk_count = len(rows)
    data = obj.read_bytes()
    machine, section_count, _, symbol_offset, symbol_count, optional_size, _ = struct.unpack_from(
        "<HHLLLHH", data, 0
    )
    if machine != 0x14C:
        raise ValueError(f"expected i386 COFF object, got {machine:#x}")
    section_table = 20 + optional_size
    sections = []
    for section_index in range(section_count):
        header = data[section_table + section_index * 40 : section_table + (section_index + 1) * 40]
        section_name = header[:8].rstrip(b"\0").decode("ascii", errors="replace")
        raw_size, raw_offset = struct.unpack_from("<LL", header, 16)
        reloc_offset = struct.unpack_from("<L", header, 24)[0]
        reloc_count = struct.unpack_from("<H", header, 32)[0]
        raw = data[raw_offset : raw_offset + raw_size]
        if len(raw) != raw_size:
            raise ValueError(f"truncated section {section_name}")
        sections.append((section_name, raw, reloc_offset, reloc_count))

    string_offset = symbol_offset + symbol_count * 18
    string_size = struct.unpack_from("<L", data, string_offset)[0]
    strings = data[string_offset : string_offset + string_size]
    if len(strings) != string_size:
        raise ValueError("truncated COFF string table")
    symbols: list[dict[str, int | str]] = []
    by_index: dict[int, dict[str, int | str]] = {}
    index = 0
    while index < symbol_count:
        record = data[symbol_offset + index * 18 : symbol_offset + (index + 1) * 18]
        if len(record) != 18:
            raise ValueError("truncated COFF symbol table")
        name = name_of(record, strings)
        value, section_number = struct.unpack_from("<Lh", record, 8)
        symbol = {"name": name, "value": value, "section": section_number, "index": index}
        symbols.append(symbol)
        by_index[index] = symbol
        index += 1 + record[17]

    labels = {"_LAB_" + row["label_address"].removeprefix("0x"): i for i, row in enumerate(rows)}
    target_symbols = {row["target_symbol"] for row in rows}
    defined = [symbol for symbol in symbols if symbol["name"] in labels and symbol["section"] > 0]
    if len(defined) != thunk_count:
        raise ValueError(f"expected {thunk_count} defined public thunk symbols, found {len(defined)}")
    section_numbers = {int(symbol["section"]) for symbol in defined}
    if len(section_numbers) != 1:
        raise ValueError("thunk labels span multiple sections")
    section_number = section_numbers.pop()
    section_name, raw, reloc_offset, reloc_count = sections[section_number - 1]
    if not section_name.startswith(".text"):
        raise ValueError(f"thunks are not in a text section: {section_name}")
    expected_bytes = b"\xe9\0\0\0\0" * thunk_count
    if raw != expected_bytes:
        raise ValueError(f"expected 290 bytes of E9 rel32 JMP stubs, got {len(raw)} bytes")

    symbol_map = {str(symbol["name"]): symbol for symbol in symbols}
    for label, position in labels.items():
        symbol = symbol_map.get(label)
        if symbol is None or symbol["section"] != section_number or symbol["value"] != position * 5:
            raise ValueError(f"wrong COFF offset for {label}")
    missing_targets = target_symbols - symbol_map.keys()
    if missing_targets:
        raise ValueError("missing external candidate targets: " + ", ".join(sorted(missing_targets)))
    for target in target_symbols:
        if symbol_map[target]["section"] != 0:
            raise ValueError(f"target is not left as a linker-resolved external: {target}")

    relocations: list[tuple[int, str, int]] = []
    for reloc_index in range(reloc_count):
        offset = reloc_offset + reloc_index * 10
        record = data[offset : offset + 10]
        if len(record) != 10:
            raise ValueError("truncated COFF relocation")
        address, symbol_index, relocation_type = struct.unpack("<LLH", record)
        if symbol_index not in by_index:
            raise ValueError(f"bad COFF relocation symbol index {symbol_index}")
        relocations.append((address, str(by_index[symbol_index]["name"]), relocation_type))
    expected_relocations = [
        (index * 5 + 1, row["target_symbol"], 0x0014)
        for index, row in enumerate(rows)
    ]
    if sorted(relocations) != sorted(expected_relocations):
        raise ValueError("REL32 relocation sites/targets do not match the Ghidra manifest")
    print(
        f"PASS {obj}: exact {thunk_count} five-byte Ghidra JMP entries and "
        f"{thunk_count} target REL32 relocations"
    )


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--object", type=Path, required=True)
    parser.add_argument("--manifest", type=Path, required=True)
    args = parser.parse_args()
    verify(args.object, args.manifest)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
