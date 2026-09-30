#!/usr/bin/env python3
"""Inventory PE HIGHLOW fixups and raw DWORDs aimed at sections proposed to move."""

from __future__ import annotations

import argparse
import json
import struct
from collections import Counter
from pathlib import Path


MOVED_SECTION_NAMES = {".xcode", ".text", ".rdata", ".data", ".fptable"}


def parse_pe(path: Path) -> dict:
    image = path.read_bytes()
    if image[:2] != b"MZ":
        raise ValueError("not an MZ/PE image")
    pe = struct.unpack_from("<I", image, 0x3C)[0]
    if image[pe : pe + 4] != b"PE\0\0":
        raise ValueError("missing PE signature")
    machine, section_count = struct.unpack_from("<HH", image, pe + 4)
    optional_size = struct.unpack_from("<H", image, pe + 20)[0]
    optional = pe + 24
    magic = struct.unpack_from("<H", image, optional)[0]
    if machine != 0x14C or magic != 0x10B:
        raise ValueError("expected PE32 x86")
    image_base = struct.unpack_from("<I", image, optional + 28)[0]
    image_size = struct.unpack_from("<I", image, optional + 56)[0]
    section_alignment = struct.unpack_from("<I", image, optional + 32)[0]
    directory_table = optional + 96
    reloc_rva, reloc_size = struct.unpack_from("<II", image, directory_table + 5 * 8)
    section_table = optional + optional_size
    sections = []
    for index in range(section_count):
        offset = section_table + index * 40
        name = image[offset : offset + 8].split(b"\0", 1)[0].decode("ascii")
        virtual_size, rva, raw_size, raw_offset = struct.unpack_from("<IIII", image, offset + 8)
        sections.append(
            {
                "name": name,
                "rva": rva,
                "va": image_base + rva,
                "virtual_size": virtual_size,
                "raw_size": raw_size,
                "raw_offset": raw_offset,
            }
        )

    def rva_to_raw(rva: int) -> int:
        for section in sections:
            start = section["rva"]
            if start <= rva < start + section["raw_size"]:
                return section["raw_offset"] + rva - start
        raise ValueError(f"RVA has no raw backing: 0x{rva:X}")

    def owner(va: int) -> str:
        for section in sections:
            start = section["va"]
            if start <= va < start + section["virtual_size"]:
                return section["name"]
        return "outside"

    relocations = []
    if reloc_rva and reloc_size:
        cursor = rva_to_raw(reloc_rva)
        limit = cursor + reloc_size
        while cursor + 8 <= limit:
            page_rva, block_size = struct.unpack_from("<II", image, cursor)
            if block_size < 8 or cursor + block_size > limit:
                raise ValueError("malformed base-relocation block")
            for index in range((block_size - 8) // 2):
                entry = struct.unpack_from("<H", image, cursor + 8 + index * 2)[0]
                kind = entry >> 12
                if kind == 0:
                    continue
                site_rva = page_rva + (entry & 0x0FFF)
                site_raw = rva_to_raw(site_rva)
                value = struct.unpack_from("<I", image, site_raw)[0] if kind == 3 else None
                relocations.append(
                    {
                        "type": kind,
                        "site_rva": site_rva,
                        "site_va": image_base + site_rva,
                        "site_section": owner(image_base + site_rva),
                        "stored_value": value,
                        "stored_target_section": owner(value) if value is not None else None,
                    }
                )
            cursor += block_size

    moved_ranges = [
        (section["va"], section["va"] + section["virtual_size"])
        for section in sections
        if section["name"] in MOVED_SECTION_NAMES
    ]

    def targets_moved(value: int) -> bool:
        return any(start <= value < end for start, end in moved_ranges)

    relocated_sites = {row["site_rva"] for row in relocations if row["type"] == 3}
    raw_hits = []
    for section in sections:
        if section["name"] not in MOVED_SECTION_NAMES:
            continue
        for byte_offset in range(max(0, section["raw_size"] - 3)):
            value = struct.unpack_from("<I", image, section["raw_offset"] + byte_offset)[0]
            if not targets_moved(value):
                continue
            site_rva = section["rva"] + byte_offset
            raw_hits.append(
                {
                    "section": section["name"],
                    "site_rva": site_rva,
                    "site_va": image_base + site_rva,
                    "stored_value": value,
                    "stored_target_section": owner(value),
                    "has_highlow_fixup_at_exact_site": site_rva in relocated_sites,
                }
            )

    return {
        "input": str(path.resolve()),
        "file_size": len(image),
        "image_base": image_base,
        "size_of_image": image_size,
        "section_alignment": section_alignment,
        "relocation_directory_rva": reloc_rva,
        "relocation_directory_size": reloc_size,
        "sections": sections,
        "relocation_count_by_type": dict(Counter(str(row["type"]) for row in relocations)),
        "relocation_site_count_by_section": dict(Counter(row["site_section"] for row in relocations)),
        "highlow_target_count_by_section": dict(
            Counter(row["stored_target_section"] for row in relocations if row["type"] == 3)
        ),
        "highlow_targets_image_base": sum(
            row["type"] == 3 and row["stored_value"] == image_base for row in relocations
        ),
        "raw_dword_target_hits": len(raw_hits),
        "raw_dword_target_hits_by_section_and_fixup": {
            f"{section}|{'covered' if covered else 'uncovered'}": count
            for (section, covered), count in Counter(
                (row["section"], row["has_highlow_fixup_at_exact_site"]) for row in raw_hits
            ).items()
        },
        "uncovered_raw_dword_target_hits": [row for row in raw_hits if not row["has_highlow_fixup_at_exact_site"]],
        "limitations": [
            "A bytewise DWORD match is a candidate, not proof of a live pointer or instruction operand.",
            "Relocation records describe loader fixups, not every numeric absolute address embedded by source code.",
            "No image bytes are changed and this report does not prove PE or runtime validity.",
        ],
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("image", type=Path)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")
    report = parse_pe(args.image)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    uncovered = len(report["uncovered_raw_dword_target_hits"])
    print(
        f"HIGHLOW types={report['relocation_count_by_type']} "
        f"raw_target_hits={report['raw_dword_target_hits']} uncovered={uncovered}"
    )
    print(f"report={args.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
