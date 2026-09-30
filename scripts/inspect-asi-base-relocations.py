#!/usr/bin/env python3
"""Summarize x86 PE base relocations in the original ImVehFt ASI."""

from __future__ import annotations

import argparse
import json
import struct
from collections import Counter
from pathlib import Path


DEFAULT_ASI = Path(
    r"C:\Users\caner\OneDrive\Documents\GTA San Andreas\modloader\My Scripts\.ImVehFt\ImVehFt.asi"
)


def parse_pe(path: Path) -> dict[str, object]:
    image = path.read_bytes()
    if image[:2] != b"MZ":
        raise ValueError("Input has no MZ signature")
    pe_offset = struct.unpack_from("<I", image, 0x3C)[0]
    if image[pe_offset : pe_offset + 4] != b"PE\0\0":
        raise ValueError("Input has no PE signature")
    machine, section_count = struct.unpack_from("<HH", image, pe_offset + 4)
    optional_size = struct.unpack_from("<H", image, pe_offset + 20)[0]
    if machine != 0x14C:
        raise ValueError(f"Expected x86 machine 0x14c, got {machine:#x}")
    optional = pe_offset + 24
    if struct.unpack_from("<H", image, optional)[0] != 0x10B:
        raise ValueError("Expected PE32 optional header")
    image_base = struct.unpack_from("<I", image, optional + 28)[0]
    size_of_image = struct.unpack_from("<I", image, optional + 56)[0]
    directory_count = struct.unpack_from("<I", image, optional + 92)[0]
    if directory_count <= 5:
        raise ValueError("PE has no base-relocation data-directory entry")
    directory = optional + 96 + 5 * 8
    reloc_rva, reloc_size = struct.unpack_from("<II", image, directory)

    section_table = optional + optional_size
    sections: list[dict[str, int | str]] = []
    for index in range(section_count):
        offset = section_table + index * 40
        name = image[offset : offset + 8].split(b"\0", 1)[0].decode("ascii")
        virtual_size, rva, raw_size, raw_offset = struct.unpack_from(
            "<IIII", image, offset + 8
        )
        sections.append(
            {
                "name": name,
                "virtual_size": virtual_size,
                "rva": rva,
                "raw_size": raw_size,
                "raw_offset": raw_offset,
            }
        )

    def section_for_rva(rva: int) -> dict[str, int | str] | None:
        for section in sections:
            delta = rva - int(section["rva"])
            extent = max(int(section["virtual_size"]), int(section["raw_size"]))
            if 0 <= delta < extent:
                return section
        return None

    def file_offset_for_rva(rva: int, width: int = 1) -> int:
        section = section_for_rva(rva)
        if section is None:
            raise ValueError(f"RVA {rva:#x} is not in a section")
        delta = rva - int(section["rva"])
        if delta + width > int(section["raw_size"]):
            raise ValueError(f"RVA {rva:#x} is not file-backed for {width} bytes")
        return int(section["raw_offset"]) + delta

    reloc_offset = file_offset_for_rva(reloc_rva)
    cursor = reloc_offset
    end = reloc_offset + reloc_size
    counts: Counter[tuple[str, int]] = Counter()
    internal_targets: Counter[str] = Counter()
    highlow_target_sections: Counter[tuple[str, str]] = Counter()
    all_highlow_entries: list[dict[str, str]] = []
    data_entries: list[dict[str, str]] = []
    data_section_entries: list[dict[str, str]] = []
    total = 0
    while cursor < end:
        if cursor + 8 > end:
            raise ValueError("Truncated relocation block header")
        page_rva, block_size = struct.unpack_from("<II", image, cursor)
        if block_size < 8 or block_size % 2 or cursor + block_size > end:
            raise ValueError(f"Invalid relocation block size {block_size:#x}")
        count = (block_size - 8) // 2
        entry_cursor = cursor + 8
        for _ in range(count):
            entry = struct.unpack_from("<H", image, entry_cursor)[0]
            entry_cursor += 2
            reloc_type = entry >> 12
            site_rva = page_rva + (entry & 0x0FFF)
            section = section_for_rva(site_rva)
            section_name = str(section["name"]) if section else "<unmapped>"
            counts[(section_name, reloc_type)] += 1
            total += 1
            if reloc_type != 3:
                continue
            value = struct.unpack_from("<I", image, file_offset_for_rva(site_rva, 4))[0]
            site_va = image_base + site_rva
            target_is_internal = image_base <= value < image_base + size_of_image
            target_section = (
                section_for_rva(value - image_base) if target_is_internal else None
            )
            if target_is_internal:
                internal_targets[section_name] += 1
            if reloc_type == 3:
                target_section_name = (
                    str(target_section["name"]) if target_section else "<external-or-unmapped>"
                )
                highlow_target_sections[(section_name, target_section_name)] += 1
                all_highlow_entries.append(
                    {
                        "site_va": f"0x{site_va:08X}",
                        "site_section": section_name,
                        "stored_va": f"0x{value:08X}",
                        "target_section": target_section_name,
                        "stored_value_points_inside_image": str(target_is_internal).lower(),
                    }
                )
            if section_name in {".rdata", ".data"}:
                data_section_entries.append(
                    {
                        "site_va": f"0x{site_va:08X}",
                        "site_section": section_name,
                        "stored_va": f"0x{value:08X}",
                        "target_section": (
                            str(target_section["name"])
                            if target_section
                            else "<unmapped>"
                        ),
                        "stored_value_points_inside_image": str(
                            target_is_internal
                        ).lower(),
                    }
                )
            if section_name == ".data":
                data_entries.append(
                    {
                        "site_va": f"0x{site_va:08X}",
                        "stored_va": f"0x{value:08X}",
                        "stored_value_points_inside_image": str(
                            image_base <= value < image_base + size_of_image
                        ).lower(),
                    }
                )
        cursor += block_size
    if cursor != end:
        raise ValueError("Relocation block walk did not end on the directory boundary")

    section_summary = []
    for section in sections:
        section_summary.append(
            {
                "name": section["name"],
                "rva": f"0x{int(section['rva']):08X}",
                "virtual_size": f"0x{int(section['virtual_size']):X}",
                "raw_size": f"0x{int(section['raw_size']):X}",
                "zero_fill_tail": f"0x{max(0, int(section['virtual_size']) - int(section['raw_size'])):X}",
            }
        )
    return {
        "input": str(path),
        "file_size": len(image),
        "image_base": f"0x{image_base:08X}",
        "size_of_image": f"0x{size_of_image:X}",
        "relocation_directory_rva": f"0x{reloc_rva:X}",
        "relocation_directory_size": f"0x{reloc_size:X}",
        "relocation_entry_count_including_padding": total,
        "relocation_counts_by_section_and_type": [
            {"section": section, "type": reloc_type, "count": count}
            for (section, reloc_type), count in sorted(counts.items())
        ],
        "highlow_values_pointing_inside_image_by_section": dict(
            sorted(internal_targets.items())
        ),
        "highlow_target_counts_by_site_and_target_section": [
            {"site_section": site_section, "target_section": target_section, "count": count}
            for (site_section, target_section), count in sorted(highlow_target_sections.items())
        ],
        "all_highlow_relocations": all_highlow_entries,
        "data_highlow_relocations": data_entries,
        "data_section_highlow_relocations": data_section_entries,
        "sections": section_summary,
        "scope_limit": "PE relocation-table inventory only; does not verify a rebuilt image or loader behavior.",
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--asi", type=Path, default=DEFAULT_ASI)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    result = parse_pe(args.asi)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(
        "relocations={relocation_entry_count_including_padding} "
        "data_HIGHLOW={data_highlow_count} output={output}".format(
            relocation_entry_count_including_padding=result[
                "relocation_entry_count_including_padding"
            ],
            data_highlow_count=len(result["data_highlow_relocations"]),
            output=args.output,
        )
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
