#!/usr/bin/env python3
"""Verify six raw DWORD scan hits are copied bytes from original .data."""

from __future__ import annotations

import argparse
import hashlib
import struct
from pathlib import Path


EXPECTED_ORIGINAL_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"
SOURCE_VAS = (0x10031CB9, 0x10034E51, 0x10036D02)
OBJECT_OFFSETS = {
    "reloc-aware-dat-provider": (0x8CB9, 0xBE51, 0xDD02),
    "png-provider": (0x7D51, 0xAEE9, 0xCD9A),
}


def pe_data_bytes(path: Path, source_va: int) -> bytes:
    image = path.read_bytes()
    if hashlib.sha256(image).hexdigest().upper() != EXPECTED_ORIGINAL_SHA256:
        raise ValueError("original ASI SHA-256 differs from the pinned reference")
    pe = struct.unpack_from("<I", image, 0x3C)[0]
    if image[pe : pe + 4] != b"PE\0\0":
        raise ValueError("missing PE signature")
    optional = pe + 24
    image_base = struct.unpack_from("<I", image, optional + 28)[0]
    section_count = struct.unpack_from("<H", image, pe + 6)[0]
    optional_size = struct.unpack_from("<H", image, pe + 20)[0]
    table = optional + optional_size
    for index in range(section_count):
        at = table + index * 40
        name = image[at : at + 8].split(b"\0", 1)[0]
        if name != b".data":
            continue
        _, rva, raw_size, raw_offset = struct.unpack_from("<IIII", image, at + 8)
        section_va = image_base + rva
        offset = source_va - section_va
        if offset < 0 or offset + 4 > raw_size:
            raise ValueError(f"source VA 0x{source_va:08X} is not backed by original .data raw bytes")
        return image[raw_offset + offset : raw_offset + offset + 4]
    raise ValueError("original PE has no .data section")


def object_data_bytes(path: Path, section_offset: int) -> bytes:
    obj = path.read_bytes()
    if len(obj) < 20:
        raise ValueError(f"truncated COFF object: {path}")
    section_count = struct.unpack_from("<H", obj, 2)[0]
    for index in range(section_count):
        at = 20 + index * 40
        name = obj[at : at + 8].split(b"\0", 1)[0]
        raw_size, raw_offset = struct.unpack_from("<II", obj, at + 16)
        if name != b".data":
            continue
        if section_offset < 0 or section_offset + 4 > raw_size:
            raise ValueError(f"offset 0x{section_offset:X} exceeds {path.name} .data")
        return obj[raw_offset + section_offset : raw_offset + section_offset + 4]
    raise ValueError(f"{path.name} has no .data section")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("original_asi", type=Path)
    parser.add_argument("reloc_aware_provider_obj", type=Path)
    parser.add_argument("png_provider_obj", type=Path)
    args = parser.parse_args()
    objects = {
        "reloc-aware-dat-provider": args.reloc_aware_provider_obj,
        "png-provider": args.png_provider_obj,
    }
    for label, path in objects.items():
        data_offsets = OBJECT_OFFSETS[label]
        for source_va, object_offset in zip(SOURCE_VAS, data_offsets, strict=True):
            original = pe_data_bytes(args.original_asi, source_va)
            copied = object_data_bytes(path, object_offset)
            if copied != original:
                raise SystemExit(
                    f"FAIL {label} obj+0x{object_offset:X} -> VA 0x{source_va:08X}: "
                    f"obj={copied.hex()} original={original.hex()}"
                )
            value = struct.unpack("<I", copied)[0]
            print(
                f"PASS {label} obj+0x{object_offset:X} -> "
                f"original VA 0x{source_va:08X}: 0x{value:08X}"
            )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
