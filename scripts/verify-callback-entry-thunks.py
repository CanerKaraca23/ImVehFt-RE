#!/usr/bin/env python3
"""Verify Ghidra-derived callback thunk bytes and their x86 COFF REL32 targets."""

from __future__ import annotations

import argparse
import struct
from pathlib import Path


THUNKS = {
    "_LAB_1000cd20": "?FUN_1000fc20@@YGII@Z",
    "_LAB_1000cd30": "?FUN_1000fca0@@YGII@Z",
    "_LAB_1000cd40": "?FUN_1000fd20@@YGII@Z",
    "_LAB_1000cd50": "?FUN_1000fda0@@YGII@Z",
    "_LAB_1000cd60": "?FUN_1000fe20@@YGII@Z",
    "_LAB_1000cd70": "?FUN_1000fea0@@YGII@Z",
    "_LAB_1000cd80": "?FUN_1000ff20@@YGII@Z",
    "_LAB_1000cd90": "?FUN_1000ffa0@@YGII@Z",
    "_LAB_1000cda0": "?FUN_10010020@@YGII@Z",
    "_LAB_1000cdb0": "?FUN_100100a0@@YGII@Z",
    "_LAB_1000cc30": "?FUN_1000f4a0@@YGII@Z",
    "_LAB_1000cc40": "?FUN_1000f520@@YGII@Z",
    "_LAB_1000cc50": "?FUN_1000f5a0@@YGII@Z",
    "_LAB_1000cc60": "?FUN_1000f620@@YGII@Z",
    "_LAB_1000cc70": "?FUN_1000f6a0@@YGII@Z",
    "_LAB_1000cc80": "?FUN_1000f720@@YGII@Z",
    "_LAB_1000cc90": "?FUN_1000f7a0@@YGII@Z",
    "_LAB_1000cca0": "?FUN_1000f820@@YGII@Z",
    "_LAB_1000ccb0": "?FUN_1000f8a0@@YGII@Z",
    "_LAB_1000ccc0": "?FUN_1000f920@@YGII@Z",
    "_LAB_1000ccd0": "?FUN_1000f9a0@@YGII@Z",
    "_LAB_1000cce0": "?FUN_1000fa20@@YGII@Z",
    "_LAB_1000ccf0": "?FUN_1000faa0@@YGII@Z",
    "_LAB_1000cd00": "?FUN_1000fb20@@YGII@Z",
    "_LAB_1000cd10": "?FUN_1000fba0@@YGII@Z",
}
EXPECTED = b"\x51\xe8\x00\x00\x00\x00\xc3" * len(THUNKS)


def coff_name(record: bytes, strings: bytes) -> str:
    if record[:4] == b"\0\0\0\0":
        offset = struct.unpack_from("<L", record, 4)[0]
        end = strings.find(b"\0", offset)
        if end < 0:
            raise ValueError("unterminated COFF string-table symbol")
        return strings[offset:end].decode("ascii")
    return record[:8].rstrip(b"\0").decode("ascii")


def verify(path: Path) -> None:
    data = path.read_bytes()
    if len(data) < 20:
        raise ValueError("truncated COFF header")
    machine, section_count, _, symbol_offset, symbol_count, optional_size, _ = struct.unpack_from(
        "<HHLLLHH", data, 0
    )
    if machine != 0x14C:
        raise ValueError(f"expected i386 COFF (0x14c), got {machine:#x}")

    section_table = 20 + optional_size
    sections: list[dict[str, int | bytes | str]] = []
    for index in range(section_count):
        header_offset = section_table + index * 40
        header = data[header_offset : header_offset + 40]
        if len(header) != 40:
            raise ValueError("truncated COFF section header")
        name = header[:8].rstrip(b"\0").decode("ascii", errors="replace")
        raw_size, raw_offset = struct.unpack_from("<LL", header, 16)
        reloc_offset = struct.unpack_from("<L", header, 24)[0]
        reloc_count = struct.unpack_from("<H", header, 32)[0]
        raw = data[raw_offset : raw_offset + raw_size] if raw_size else b""
        if len(raw) != raw_size:
            raise ValueError(f"truncated section data in {name}")
        sections.append({"name": name, "raw": raw, "reloc_offset": reloc_offset, "reloc_count": reloc_count})

    string_table_offset = symbol_offset + symbol_count * 18
    if string_table_offset + 4 > len(data):
        raise ValueError("missing COFF string table")
    string_table_size = struct.unpack_from("<L", data, string_table_offset)[0]
    strings = data[string_table_offset : string_table_offset + string_table_size]
    if len(strings) != string_table_size:
        raise ValueError("truncated COFF string table")

    symbols: list[dict[str, int | str]] = []
    symbols_by_raw_index: dict[int, dict[str, int | str]] = {}
    index = 0
    while index < symbol_count:
        offset = symbol_offset + index * 18
        record = data[offset : offset + 18]
        if len(record) != 18:
            raise ValueError("truncated COFF symbol")
        name = coff_name(record, strings)
        value, section_number = struct.unpack_from("<Lh", record, 8)
        storage_class, auxiliary_count = record[16], record[17]
        symbol = {"name": name, "value": value, "section": section_number, "storage": storage_class, "index": index}
        symbols.append(symbol)
        symbols_by_raw_index[index] = symbol
        index += 1 + auxiliary_count

    expected_symbols = set(THUNKS) | set(THUNKS.values())
    missing = expected_symbols - {str(item["name"]) for item in symbols}
    if missing:
        raise ValueError("missing COFF symbols: " + ", ".join(sorted(missing)))

    defined = [item for item in symbols if item["name"] in THUNKS and item["section"] > 0]
    if len(defined) != len(THUNKS):
        raise ValueError("expected exactly five defined callback labels")
    section_numbers = {int(item["section"]) for item in defined}
    if len(section_numbers) != 1:
        raise ValueError("callback labels do not share one section")
    section_number = section_numbers.pop()
    section = sections[section_number - 1]
    raw = bytes(section["raw"])
    if not str(section["name"]).startswith(".text"):
        raise ValueError(f"callback bytes are not in a code section: {section['name']}")
    if raw != EXPECTED:
        raise ValueError(f"expected exact 35-byte stream {EXPECTED.hex(' ')}, got {raw.hex(' ')}")

    labels = {str(item["name"]): int(item["value"]) for item in defined}
    for number, (label, target) in enumerate(THUNKS.items()):
        start = number * 7
        if labels[label] != start:
            raise ValueError(f"{label} expected at +{start:#x}, got {labels[label]:#x}")
        target_symbol = next(item for item in symbols if item["name"] == target)
        if target_symbol["section"] != 0:
            raise ValueError(f"target {target} is unexpectedly defined in the thunk object")

    relocations: list[tuple[int, str, int]] = []
    reloc_count = int(section["reloc_count"])
    reloc_offset = int(section["reloc_offset"])
    for index in range(reloc_count):
        offset = reloc_offset + index * 10
        record = data[offset : offset + 10]
        if len(record) != 10:
            raise ValueError("truncated COFF relocation")
        virtual_address, symbol_index, relocation_type = struct.unpack("<LLH", record)
        if symbol_index not in symbols_by_raw_index:
            raise ValueError(f"bad relocation symbol-table index {symbol_index}")
        relocations.append((virtual_address, str(symbols_by_raw_index[symbol_index]["name"]), relocation_type))

    expected_relocations = [
        (number * 7 + 2, target, 0x0014)
        for number, target in enumerate(THUNKS.values())
    ]
    if sorted(relocations) != sorted(expected_relocations):
        raise ValueError(
            "REL32 relocation mismatch; expected "
            f"{expected_relocations!r}, got {relocations!r}"
        )
    print(
        f"PASS {path}: exact {len(THUNKS)} 7-byte Ghidra thunk bodies and "
        f"{len(relocations)} target REL32 relocations"
    )


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--object", required=True, type=Path)
    args = parser.parse_args()
    verify(args.object)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
