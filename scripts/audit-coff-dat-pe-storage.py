#!/usr/bin/env python3
"""Classify referenced DAT_* addresses as raw-backed or PE zero-fill storage."""

from __future__ import annotations

import argparse
import csv
import struct
from pathlib import Path


def u16(data: bytes, offset: int) -> int:
    return struct.unpack_from("<H", data, offset)[0]


def u32(data: bytes, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("image", type=Path, help="Original ImVehFt PE image")
    parser.add_argument("inventory", type=Path, help="COFF DAT symbol inventory CSV")
    parser.add_argument("--csv", type=Path, required=True, help="New CSV output path")
    args = parser.parse_args()

    image = args.image.read_bytes()
    if image[:2] != b"MZ":
        parser.error(f"not an MZ image: {args.image}")
    pe_offset = u32(image, 0x3C)
    if image[pe_offset : pe_offset + 4] != b"PE\0\0":
        parser.error(f"missing PE signature: {args.image}")
    section_count = u16(image, pe_offset + 6)
    optional_size = u16(image, pe_offset + 20)
    optional = pe_offset + 24
    if u16(image, optional) != 0x10B:
        parser.error("expected PE32 optional header")
    image_base = u32(image, optional + 28)
    section_table = optional + optional_size

    sections: list[dict[str, int | str]] = []
    for index in range(section_count):
        offset = section_table + index * 40
        name = image[offset : offset + 8].split(b"\0", 1)[0].decode("ascii")
        sections.append(
            {
                "name": name,
                "virtual_size": u32(image, offset + 8),
                "rva": u32(image, offset + 12),
                "raw_size": u32(image, offset + 16),
                "raw_pointer": u32(image, offset + 20),
            }
        )

    args.csv.parent.mkdir(parents=True, exist_ok=True)
    fields = (
        "address",
        "section",
        "storage_class",
        "rva_in_section",
        "virtual_size",
        "raw_size",
        "file_offset",
        "initial_bytes",
    )
    counts: dict[str, int] = {}
    with args.inventory.open("r", encoding="utf-8-sig", newline="") as source:
        with args.csv.open("x", encoding="utf-8", newline="") as output:
            reader = csv.DictReader(source)
            writer = csv.DictWriter(output, fieldnames=fields, lineterminator="\n")
            writer.writeheader()
            for row in reader:
                address = int(row["address"], 16)
                rva = address - image_base
                section = next(
                    (
                        item
                        for item in sections
                        if int(item["rva"])
                        <= rva
                        < int(item["rva"]) + int(item["virtual_size"])
                    ),
                    None,
                )
                if section is None:
                    storage_class = "outside-image-sections"
                    values: dict[str, str | int] = {
                        "section": "",
                        "rva_in_section": "",
                        "virtual_size": "",
                        "raw_size": "",
                        "file_offset": "",
                        "initial_bytes": "",
                    }
                else:
                    delta = rva - int(section["rva"])
                    virtual_left = int(section["virtual_size"]) - delta
                    raw_left = int(section["raw_size"]) - delta
                    if raw_left > 0:
                        storage_class = "raw-backed"
                        count = min(4, virtual_left, raw_left)
                        file_offset = int(section["raw_pointer"]) + delta
                        initial = image[file_offset : file_offset + count]
                        file_offset_text = f"0x{file_offset:X}"
                    else:
                        storage_class = "virtual-zero-fill"
                        count = min(4, virtual_left)
                        initial = bytes(count)
                        file_offset_text = ""
                    values = {
                        "section": str(section["name"]),
                        "rva_in_section": f"0x{delta:X}",
                        "virtual_size": f"0x{int(section['virtual_size']):X}",
                        "raw_size": f"0x{int(section['raw_size']):X}",
                        "file_offset": file_offset_text,
                        "initial_bytes": initial.hex(" ").upper(),
                    }

                counts[storage_class] = counts.get(storage_class, 0) + 1
                writer.writerow(
                    {
                        "address": f"0x{address:08X}",
                        "storage_class": storage_class,
                        **values,
                    }
                )

    print(f"image base: 0x{image_base:08X}")
    print(f"classified addresses: {sum(counts.values())}")
    for category, count in sorted(counts.items()):
        print(f"{category}: {count}")
    print(f"CSV: {args.csv.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
