#!/usr/bin/env python3
"""Find original PE HIGHLOW fixups intersected by planned 5-byte entry thunks."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import struct
from pathlib import Path


EXPECTED_IMAGE_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"
EXPECTED_TEXT_HIGHLOW_COUNT = 3160
THUNK_SIZE = 5
HIGHLOW_WIDTH = 4


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def parse_pe(data: bytes) -> tuple[int, list[dict[str, int | str]], int, int]:
    if len(data) < 0x40 or data[:2] != b"MZ":
        raise ValueError("reference is not an MZ/PE image")
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    if data[pe : pe + 4] != b"PE\0\0":
        raise ValueError("invalid PE signature")
    section_count = struct.unpack_from("<H", data, pe + 6)[0]
    optional_size = struct.unpack_from("<H", data, pe + 20)[0]
    optional = pe + 24
    if struct.unpack_from("<H", data, optional)[0] != 0x10B:
        raise ValueError("expected PE32 image")
    image_base = struct.unpack_from("<I", data, optional + 28)[0]
    directories = optional + 96
    reloc_rva, reloc_size = struct.unpack_from("<II", data, directories + 5 * 8)
    table = optional + optional_size
    sections: list[dict[str, int | str]] = []
    for index in range(section_count):
        at = table + index * 40
        name = data[at : at + 8].split(b"\0", 1)[0].decode("ascii", errors="replace")
        virtual_size, rva, raw_size, raw_offset = struct.unpack_from("<IIII", data, at + 8)
        sections.append({
            "name": name,
            "rva": rva,
            "va": image_base + rva,
            "virtual_size": virtual_size,
            "raw_size": raw_size,
            "raw_offset": raw_offset,
        })
    return image_base, sections, reloc_rva, reloc_size


def rva_to_offset(rva: int, size: int, sections: list[dict[str, int | str]]) -> int:
    for section in sections:
        start = int(section["rva"])
        raw_size = int(section["raw_size"])
        if start <= rva and rva + size <= start + raw_size:
            return int(section["raw_offset"]) + rva - start
    raise ValueError(f"RVA range 0x{rva:x}..0x{rva + size:x} is not file-backed")


def highlow_sites(
    data: bytes,
    image_base: int,
    sections: list[dict[str, int | str]],
    reloc_rva: int,
    reloc_size: int,
) -> list[int]:
    text = next(section for section in sections if section["name"] == ".text")
    text_start = int(text["va"])
    text_end = text_start + max(int(text["virtual_size"]), int(text["raw_size"]))
    offset = rva_to_offset(reloc_rva, reloc_size, sections)
    end = offset + reloc_size
    sites: list[int] = []
    while offset < end:
        if offset + 8 > end:
            raise ValueError("truncated base-relocation block header")
        page_rva, block_size = struct.unpack_from("<II", data, offset)
        if block_size < 8 or block_size % 2 or offset + block_size > end:
            raise ValueError(f"invalid base-relocation block size {block_size} at file offset {offset:#x}")
        for item_at in range(offset + 8, offset + block_size, 2):
            item = struct.unpack_from("<H", data, item_at)[0]
            kind, within_page = item >> 12, item & 0x0FFF
            if kind == 3:
                site = image_base + page_rva + within_page
                if text_start <= site and site + HIGHLOW_WIDTH <= text_end:
                    sites.append(site)
        offset += block_size
    return sorted(sites)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--reference-pe", required=True, type=Path)
    parser.add_argument("--function-map", required=True, type=Path)
    parser.add_argument("--feasibility", type=Path, help="limit analysis to entries currently requiring a rel32 thunk")
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")

    image = args.reference_pe.read_bytes()
    image_hash = sha256(image)
    if image_hash != EXPECTED_IMAGE_SHA256:
        raise ValueError(f"unexpected reference ASI SHA-256: {image_hash}")
    image_base, sections, reloc_rva, reloc_size = parse_pe(image)
    text = next(section for section in sections if section["name"] == ".text")
    text_start = int(text["va"])
    text_end = text_start + int(text["virtual_size"])
    sites = highlow_sites(image, image_base, sections, reloc_rva, reloc_size)
    if len(sites) != EXPECTED_TEXT_HIGHLOW_COUNT:
        raise ValueError(f"expected {EXPECTED_TEXT_HIGHLOW_COUNT} .text HIGHLOW sites, found {len(sites)}")

    with args.function_map.open(encoding="utf-8-sig", newline="") as stream:
        rows = list(csv.DictReader(stream))
    all_entries = sorted({int(row["address"], 16) for row in rows})
    if len(rows) != 705 or len(all_entries) != 705:
        raise ValueError(f"expected 705 unique entry addresses, found {len(all_entries)}")
    if args.feasibility:
        feasibility = json.loads(args.feasibility.read_text(encoding="utf-8"))
        entries = sorted(
            int(row["address"], 16)
            for row in feasibility["entries"]
            if row["placement_mode"] == "jmp-rel32-thunk"
        )
        if not entries or not set(entries).issubset(all_entries):
            raise ValueError("feasibility report has no valid thunk entries in the 705-function map")
    else:
        entries = all_entries
    for entry in entries:
        if not text_start <= entry or entry + THUNK_SIZE > text_end:
            raise ValueError(f"entry patch window at 0x{entry:08x} is outside original .text")

    hits: list[dict[str, int | str]] = []
    for site in sites:
        for entry in entries:
            overlap_start = max(site, entry)
            overlap_end = min(site + HIGHLOW_WIDTH, entry + THUNK_SIZE)
            if overlap_start < overlap_end:
                hits.append({
                    "relocation_site_va": f"0x{site:08x}",
                    "relocation_site_offset_from_entry": site - entry,
                    "entry_va": f"0x{entry:08x}",
                    "overlap_bytes": overlap_end - overlap_start,
                    "fixup_bytes_fully_overwritten": overlap_start == site and overlap_end == site + HIGHLOW_WIDTH,
                })
                break

    report = {
        "scope": "Original .text HIGHLOW relocation DWORD ranges intersecting 5-byte E9 rel32 entry patch windows.",
        "reference_pe": str(args.reference_pe.resolve()),
        "reference_sha256": image_hash,
        "function_map": str(args.function_map.resolve()),
        "function_map_sha256": sha256(args.function_map.read_bytes()),
        "feasibility_report": str(args.feasibility.resolve()) if args.feasibility else None,
        "thunk_entries_selected_from_feasibility": len(entries) if args.feasibility else None,
        "image_base": f"0x{image_base:08x}",
        "text_start": f"0x{text_start:08x}",
        "text_end_exclusive": f"0x{text_end:08x}",
        "original_text_highlow_site_count": len(sites),
        "entry_count": len(entries),
        "entry_thunk_size": THUNK_SIZE,
        "overlapping_relocation_count": len(hits),
        "relocation_sites_to_remove_from_base_relocation_directory": len(hits),
        "fully_overwritten_fixup_count": sum(bool(hit["fixup_bytes_fully_overwritten"]) for hit in hits),
        "partially_overwritten_fixup_count": sum(not bool(hit["fixup_bytes_fully_overwritten"]) for hit in hits),
        "overlaps": hits,
        "limitations": [
            "This identifies relocation entries whose 4-byte patch field intersects a planned entry thunk; it does not emit or patch a PE.",
            "It does not validate original instruction/control-flow boundaries, data references, startup/import behavior, or runtime semantics.",
            "A combined-image builder must omit these original fixup records and correctly merge all remaining original and candidate relocation entries.",
        ],
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(
        f"entries={len(entries)} .text_HIGHLOW={len(sites)} overlap={len(hits)} "
        f"fully_overwritten={report['fully_overwritten_fixup_count']} "
        f"partial={report['partially_overwritten_fixup_count']}"
    )
    print(f"report={args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
