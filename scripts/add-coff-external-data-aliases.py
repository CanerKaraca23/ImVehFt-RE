#!/usr/bin/env python3
"""Add exact external aliases to data addresses in a copy of an IA32 COFF object.

The object bytes and section contents are preserved. Only COFF external symbol
records and the string table are extended; the input object is never modified.
This is intended for diagnostic linking, not as a claim of runtime validity.
"""

from __future__ import annotations

import argparse
import csv
import hashlib
import struct
from pathlib import Path


COFF_HEADER_SIZE = 20
SECTION_HEADER_SIZE = 40
SYMBOL_SIZE = 18
IMAGE_SCN_CNT_INITIALIZED_DATA = 0x00000040


def read_pe_sections(path: Path) -> tuple[int, dict[str, tuple[int, int]]]:
    data = path.read_bytes()
    if data[:2] != b"MZ":
        raise ValueError("input image is not a PE")
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    if data[pe : pe + 4] != b"PE\0\0":
        raise ValueError("invalid PE signature")
    section_count = struct.unpack_from("<H", data, pe + 6)[0]
    optional_size = struct.unpack_from("<H", data, pe + 20)[0]
    optional = pe + 24
    if struct.unpack_from("<H", data, optional)[0] != 0x10B:
        raise ValueError("only PE32 images are supported")
    image_base = struct.unpack_from("<I", data, optional + 28)[0]
    section_table = optional + optional_size
    sections: dict[str, tuple[int, int]] = {}
    for index in range(section_count):
        off = section_table + index * SECTION_HEADER_SIZE
        name = data[off : off + 8].split(b"\0", 1)[0].decode("ascii")
        virtual_size, rva, raw_size = struct.unpack_from("<III", data, off + 8)
        sections[name] = (rva, max(virtual_size, raw_size))
    return image_base, sections


def coff_name(raw: bytes, strings: bytes) -> str:
    if raw[:4] == b"\0\0\0\0":
        offset = struct.unpack_from("<I", raw, 4)[0]
        if offset < 4 or offset >= len(strings):
            raise ValueError(f"invalid COFF string-table offset: {offset}")
        end = strings.find(b"\0", offset)
        if end < 0:
            raise ValueError("unterminated COFF string")
        return strings[offset:end].decode("utf-8")
    return raw.split(b"\0", 1)[0].decode("utf-8")


def encode_coff_name(name: str, string_offset: int) -> bytes:
    encoded = name.encode("utf-8")
    if len(encoded) <= 8:
        return encoded.ljust(8, b"\0")
    return b"\0\0\0\0" + struct.pack("<I", string_offset)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", required=True, type=Path)
    parser.add_argument("--image", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    parser.add_argument("--inventory", action="append", required=True, type=Path)
    args = parser.parse_args()
    if args.output.exists():
        parser.error(f"refusing to overwrite output: {args.output}")

    original = args.object.read_bytes()
    if len(original) < COFF_HEADER_SIZE:
        raise ValueError("truncated COFF object")
    machine, section_count, _, symbol_offset, symbol_count = struct.unpack_from(
        "<HHIII", original, 0
    )
    if machine != 0x014C:
        raise ValueError(f"expected IA32 COFF, got machine {machine:#06x}")
    if not symbol_offset or symbol_offset + symbol_count * SYMBOL_SIZE + 4 > len(original):
        raise ValueError("invalid COFF symbol-table bounds")

    section_headers: dict[str, tuple[int, int]] = {}
    for index in range(section_count):
        off = COFF_HEADER_SIZE + index * SECTION_HEADER_SIZE
        raw_name = original[off : off + 8].split(b"\0", 1)[0]
        name = raw_name.decode("ascii")
        raw_size = struct.unpack_from("<I", original, off + 16)[0]
        characteristics = struct.unpack_from("<I", original, off + 36)[0]
        section_headers[name] = (index + 1, raw_size)
        if name not in (".data", ".rdata") and characteristics & IMAGE_SCN_CNT_INITIALIZED_DATA:
            continue
    if ".data" not in section_headers or ".rdata" not in section_headers:
        raise ValueError("COFF object must contain .data and .rdata sections")

    image_base, pe_sections = read_pe_sections(args.image)
    image_data_sections = {name: pe_sections[name] for name in (".data", ".rdata")}
    strings_offset = symbol_offset + symbol_count * SYMBOL_SIZE
    strings = original[strings_offset:]
    string_size = struct.unpack_from("<I", strings, 0)[0]
    if string_size < 4 or string_size > len(strings):
        raise ValueError("invalid COFF string table")
    strings = strings[:string_size]

    existing: dict[str, tuple[int, int, int]] = {}
    symbol_index = 0
    while symbol_index < symbol_count:
        off = symbol_offset + symbol_index * SYMBOL_SIZE
        name = coff_name(original[off : off + 8], strings)
        value, section_number, _type, storage_class, aux_count = struct.unpack_from(
            "<IhHBB", original, off + 8
        )
        if storage_class == 2 and section_number > 0:
            existing[name] = (section_number, value, storage_class)
        symbol_index += 1 + aux_count
    if symbol_index != symbol_count:
        raise ValueError("COFF auxiliary symbol records exceed symbol count")

    aliases: dict[str, tuple[str, int]] = {}
    for inventory in args.inventory:
        with inventory.open("r", encoding="utf-8-sig", newline="") as stream:
            reader = csv.DictReader(stream)
            if not reader.fieldnames or not {"address", "symbol"}.issubset(reader.fieldnames):
                raise ValueError(f"inventory requires address,symbol columns: {inventory}")
            for row in reader:
                address_text = row["address"].strip()
                address = int(address_text, 0)
                name = row["symbol"].strip()
                if not name or any(ch.isspace() for ch in name):
                    raise ValueError(f"invalid COFF symbol name in {inventory}: {name!r}")
                rva = address - image_base
                match = None
                for section_name, (section_rva, extent) in image_data_sections.items():
                    offset = rva - section_rva
                    if 0 <= offset < extent:
                        match = (section_name, offset)
                        break
                if match is None:
                    raise ValueError(f"alias outside PE .rdata/.data: {name} at {address:#x}")
                previous = aliases.get(name)
                if previous is not None and previous != match:
                    raise ValueError(f"alias maps to multiple locations: {name}")
                aliases[name] = match

    new_records: list[bytes] = []
    new_strings = bytearray()
    already_present = 0
    for name, (section_name, value) in sorted(aliases.items()):
        section_number, raw_size = section_headers[section_name]
        if value >= raw_size:
            raise ValueError(f"alias outside raw COFF section: {name} {section_name}+{value:#x}")
        prior = existing.get(name)
        if prior is not None:
            if prior[:2] != (section_number, value):
                raise ValueError(f"existing external symbol has a different address: {name}")
            already_present += 1
            continue
        name_bytes = name.encode("utf-8")
        if len(name_bytes) <= 8:
            name_field = name_bytes.ljust(8, b"\0")
        else:
            string_offset = string_size + len(new_strings)
            name_field = b"\0\0\0\0" + struct.pack("<I", string_offset)
            new_strings.extend(name_bytes + b"\0")
        new_records.append(
            name_field + struct.pack("<IhHBB", value, section_number, 0, 2, 0)
        )

    new_symbol_bytes = b"".join(new_records)
    new_string_table = struct.pack("<I", string_size + len(new_strings)) + strings[4:] + new_strings
    output = bytearray(
        original[:strings_offset] + new_symbol_bytes + new_string_table
    )
    struct.pack_into("<I", output, 12, symbol_count + len(new_records))

    # Ensure no image bytes or section headers were altered.
    if output[:12] != original[:12] or output[16:symbol_offset] != original[16:symbol_offset]:
        raise AssertionError("object header or section payload changed")
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_bytes(output)
    print(f"Aliases requested: {len(aliases)}")
    print(f"Aliases already external at exact address: {already_present}")
    print(f"External symbols appended: {len(new_records)}")
    print(f"Input SHA-256: {hashlib.sha256(original).hexdigest()}")
    print(f"Output SHA-256: {hashlib.sha256(output).hexdigest()}")
    print(f"Output object: {args.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
