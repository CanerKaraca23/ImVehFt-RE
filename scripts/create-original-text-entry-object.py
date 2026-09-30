#!/usr/bin/env python3
"""Wrap the hash-pinned original ImVehFt .text bytes in a minimal x86 COFF object."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path


EXPECTED_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"
ENTRY_SYMBOL = "_IVF_ORIGINAL_TEXT_ENTRY_IMAGE"


def extract_text(path: Path) -> tuple[bytes, dict[str, int | str]]:
    image = path.read_bytes()
    actual_hash = hashlib.sha256(image).hexdigest().upper()
    if actual_hash != EXPECTED_SHA256:
        raise ValueError(f"Unexpected original ASI SHA-256: {actual_hash}")
    if image[:2] != b"MZ":
        raise ValueError("Original image has no MZ header")
    pe = struct.unpack_from("<I", image, 0x3C)[0]
    if image[pe : pe + 4] != b"PE\0\0":
        raise ValueError("Original image has no PE signature")
    machine, count = struct.unpack_from("<HH", image, pe + 4)
    optional_size = struct.unpack_from("<H", image, pe + 20)[0]
    optional = pe + 24
    if machine != 0x14C or struct.unpack_from("<H", image, optional)[0] != 0x10B:
        raise ValueError("Expected PE32/x86 input")
    image_base = struct.unpack_from("<I", image, optional + 28)[0]
    section_table = optional + optional_size
    for index in range(count):
        at = section_table + index * 40
        name = image[at : at + 8].split(b"\0", 1)[0].decode("ascii")
        if name != ".text":
            continue
        virtual_size, rva, raw_size, raw_offset = struct.unpack_from("<IIII", image, at + 8)
        raw = image[raw_offset : raw_offset + raw_size]
        if len(raw) != raw_size:
            raise ValueError("Truncated original .text data")
        return raw, {
            "original_sha256": actual_hash,
            "image_base": image_base,
            "section_va": image_base + rva,
            "virtual_size": virtual_size,
            "raw_size": raw_size,
            "raw_sha256": hashlib.sha256(raw).hexdigest().upper(),
        }
    raise ValueError("Original image has no .text section")


def make_object(raw: bytes) -> bytes:
    section_name = b".entry\0\0"
    section_flags = 0x60500020  # CODE | EXECUTE | READ | 16-byte alignment
    file_header_size = 20
    section_header_size = 40
    raw_offset = file_header_size + section_header_size
    symbol_offset = raw_offset + len(raw)
    symbol_count = 3  # section symbol + its aux record + public anchor
    strings = ENTRY_SYMBOL.encode("ascii") + b"\0"
    string_table = struct.pack("<I", 4 + len(strings)) + strings

    file_header = struct.pack(
        "<HHIIIHH",
        0x14C,
        1,
        0,
        symbol_offset,
        symbol_count,
        0,
        0,
    )
    section_header = struct.pack(
        "<8sIIIIIIHHI",
        section_name,
        0,
        0,
        len(raw),
        raw_offset,
        0,
        0,
        0,
        0,
        section_flags,
    )
    section_symbol = struct.pack("<8sIhHBB", section_name, 0, 1, 0, 3, 1)
    section_aux = struct.pack("<IHHI HBB", len(raw), 0, 0, 0, 0, 0, 0) + bytes(2)
    public_name = struct.pack("<II", 0, 4)
    public_symbol = struct.pack("<8sIhHBB", public_name, 0, 1, 0, 2, 0)
    return file_header + section_header + raw + section_symbol + section_aux + public_symbol + string_table


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--image", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--report", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists() or args.report.exists():
        raise FileExistsError("Refusing to overwrite the COFF output or report")
    raw, facts = extract_text(args.image)
    obj = make_object(raw)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_bytes(obj)
    report = {
        "scope": "Exact original .text raw bytes wrapped as one executable COFF contribution; not patched or linked as a production ASI.",
        "section_name": ".entry",
        "public_anchor": ENTRY_SYMBOL,
        **facts,
        "coff_sha256": hashlib.sha256(obj).hexdigest().upper(),
        "output": str(args.output.resolve()),
    }
    args.report.parent.mkdir(parents=True, exist_ok=True)
    with args.report.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    print(f"section=.entry original_va={facts['section_va']:#010x} raw_size={len(raw):#x} coff_sha256={report['coff_sha256']}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
