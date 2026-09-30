#!/usr/bin/env python3
"""Compare rebuilt-image bytes at original ImVehFt hook VAs with Ghidra CFG bytes."""

from __future__ import annotations

import argparse
import csv
import struct
from dataclasses import dataclass
from pathlib import Path


@dataclass(frozen=True)
class Section:
    name: str
    rva: int
    raw_size: int
    raw_offset: int


def read_expected_cfg(path: Path) -> dict[int, bytes]:
    rows: dict[int, list[tuple[int, bytes]]] = {}
    with path.open(encoding="utf-8-sig", newline="") as stream:
        for row in csv.DictReader(stream):
            target = int(row["target"], 16)
            instruction = int(row["instruction_address"], 16)
            encoded = bytes.fromhex(row["bytes_hex"])
            rows.setdefault(target, []).append((instruction, encoded))

    expected: dict[int, bytes] = {}
    for target, instructions in rows.items():
        instructions.sort(key=lambda item: item[0])
        cursor = target
        chunks: list[bytes] = []
        for address, encoded in instructions:
            if address != cursor:
                raise ValueError(
                    f"CFG for {target:#010x} is not contiguous: expected {cursor:#x}, got {address:#x}"
                )
            chunks.append(encoded)
            cursor += len(encoded)
        expected[target] = b"".join(chunks)
    return expected


def read_pe32(path: Path) -> tuple[int, bytes, list[Section]]:
    image = path.read_bytes()
    if image[:2] != b"MZ":
        raise ValueError("Input is not an MZ/PE image")
    pe_offset = struct.unpack_from("<I", image, 0x3C)[0]
    if image[pe_offset : pe_offset + 4] != b"PE\0\0":
        raise ValueError("Missing PE signature")
    machine, section_count = struct.unpack_from("<HH", image, pe_offset + 4)
    optional_size = struct.unpack_from("<H", image, pe_offset + 20)[0]
    if machine != 0x14C:
        raise ValueError(f"Expected x86/PE32 machine 0x14c, found {machine:#x}")
    optional_offset = pe_offset + 24
    magic = struct.unpack_from("<H", image, optional_offset)[0]
    if magic != 0x10B:
        raise ValueError(f"Expected PE32 optional-header magic 0x10b, found {magic:#x}")
    image_base = struct.unpack_from("<I", image, optional_offset + 28)[0]
    section_offset = optional_offset + optional_size
    sections: list[Section] = []
    for index in range(section_count):
        offset = section_offset + index * 40
        name = image[offset : offset + 8].split(b"\0", 1)[0].decode("ascii", errors="replace")
        rva, raw_size, raw_offset = struct.unpack_from("<III", image, offset + 12)
        sections.append(Section(name, rva, raw_size, raw_offset))
    return image_base, image, sections


def image_bytes_at_va(
    image: bytes, sections: list[Section], image_base: int, va: int, length: int
) -> tuple[Section, bytes] | None:
    rva = va - image_base
    for section in sections:
        delta = rva - section.rva
        if delta >= 0 and delta + length <= section.raw_size:
            start = section.raw_offset + delta
            return section, image[start : start + length]
    return None


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--image", required=True, type=Path, help="Rebuilt x86 PE image")
    parser.add_argument(
        "--cfg",
        type=Path,
        default=Path("audit/asi-hook-target-cfg-2026-09-27.csv"),
        help="Ghidra CFG CSV for the original ImVehFt.asi",
    )
    args = parser.parse_args()

    expected = read_expected_cfg(args.cfg)
    image_base, image, sections = read_pe32(args.image)
    mismatches = 0
    unmapped = 0
    for target in sorted(expected):
        wanted = expected[target]
        mapped = image_bytes_at_va(image, sections, image_base, target, len(wanted))
        if mapped is None:
            unmapped += 1
            print(f"UNMAPPED {target:#010x} expected={len(wanted)} bytes")
            continue
        section, actual = mapped
        if actual == wanted:
            print(f"PASS {target:#010x} exact {len(wanted)}-byte match in {section.name}")
            continue
        mismatches += 1
        first = next((i for i, pair in enumerate(zip(wanted, actual)) if pair[0] != pair[1]), None)
        print(
            f"FAIL {target:#010x} expected={len(wanted)} first_difference=+0x{first:X} "
            f"expected={wanted[:8].hex(' ').upper()} actual={actual[:8].hex(' ').upper()} "
            f"section={section.name}"
        )

    print(
        f"SUMMARY targets={len(expected)} matches={len(expected) - mismatches - unmapped} "
        f"mismatches={mismatches} unmapped={unmapped} image_base={image_base:#010x}"
    )
    return 1 if mismatches or unmapped else 0


if __name__ == "__main__":
    raise SystemExit(main())
