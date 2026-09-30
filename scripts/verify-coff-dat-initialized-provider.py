#!/usr/bin/env python3
"""Compare initialized DAT provider COFF section bytes to the original PE."""

from __future__ import annotations

import argparse
import hashlib
import struct
from pathlib import Path


def pe_data(path: Path) -> dict[str, bytes]:
    image = path.read_bytes()
    pe_offset = struct.unpack_from("<I", image, 0x3C)[0]
    if image[:2] != b"MZ" or image[pe_offset : pe_offset + 4] != b"PE\0\0":
        raise ValueError("invalid PE image")
    section_count = struct.unpack_from("<H", image, pe_offset + 6)[0]
    optional_size = struct.unpack_from("<H", image, pe_offset + 20)[0]
    optional = pe_offset + 24
    if struct.unpack_from("<H", image, optional)[0] != 0x10B:
        raise ValueError("expected PE32")
    sections: dict[str, bytes] = {}
    table = optional + optional_size
    for index in range(section_count):
        offset = table + index * 40
        name = image[offset : offset + 8].split(b"\0", 1)[0].decode("ascii")
        virtual_size, _, raw_size, raw_offset = struct.unpack_from("<IIII", image, offset + 8)
        if name in {".rdata", ".data"}:
            raw = image[raw_offset : raw_offset + raw_size]
            sections[name] = raw + bytes(max(0, virtual_size - raw_size))
    return sections


def coff_sections(path: Path) -> dict[str, tuple[bytes, int]]:
    data = path.read_bytes()
    if len(data) < 20:
        raise ValueError("truncated COFF object")
    _, count, _, _, _, optional_size, _ = struct.unpack_from("<HHIIIHH", data, 0)
    table = 20 + optional_size
    sections: dict[str, tuple[bytes, int]] = {}
    for index in range(count):
        offset = table + index * 40
        name = data[offset : offset + 8].split(b"\0", 1)[0].decode("ascii")
        raw_size, raw_ptr, reloc_ptr = struct.unpack_from("<III", data, offset + 16)
        reloc_count = struct.unpack_from("<H", data, offset + 32)[0]
        if name in {".rdata", ".data"}:
            raw = data[raw_ptr : raw_ptr + raw_size] if raw_size else b""
            if len(raw) != raw_size:
                raise ValueError(f"truncated COFF section {name}")
            if name in sections:
                raise ValueError(f"duplicate COFF section {name}; COMDAT/merge needs review")
            sections[name] = (raw, reloc_count)
    return sections


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("image", type=Path)
    parser.add_argument("object", type=Path)
    args = parser.parse_args()
    expected = pe_data(args.image)
    actual = coff_sections(args.object)
    failures: list[str] = []
    for name in (".rdata", ".data"):
        if name not in expected or name not in actual:
            failures.append(f"{name}: missing from PE or COFF object")
            continue
        target = expected[name]
        got, reloc_count = actual[name]
        if got != target:
            mismatch = next(
                (index for index, (a, b) in enumerate(zip(got, target)) if a != b),
                min(len(got), len(target)),
            )
            failures.append(
                f"{name}: byte mismatch at +0x{mismatch:X}; object={len(got):#x}, expected={len(target):#x}"
            )
        if reloc_count:
            failures.append(f"{name}: {reloc_count} COFF relocations present; this probe expects raw bytes only")
        print(
            f"{name}: {'PASS' if got == target else 'FAIL'} bytes={len(got):#x} "
            f"sha256={hashlib.sha256(got).hexdigest()} COFF_relocations={reloc_count}"
        )
    if failures:
        for failure in failures:
            print(failure)
        return 1
    print("2/2 section byte streams exactly match preferred-base PE bytes plus loader zero-fill.")
    print("This does not retarget embedded pointers or establish a loadable image.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
