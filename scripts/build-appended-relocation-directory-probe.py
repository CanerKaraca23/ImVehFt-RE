#!/usr/bin/env python3
"""Build and self-verify a standalone relocation-directory blob for the 147-thunk payload probe."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from collections import defaultdict
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
ORIGINAL = Path(r"C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi")
FEASIBILITY = ROOT / "audit/entry-trampoline-feasibility-final-current-2026-09-29.json"
PAYLOAD = ROOT / "audit/appended-thunk-payload-census-v2-2026-09-29.json"
EXPECTED_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def rva_to_offset(data: bytes, rva: int, image_base: int, sections: list[tuple[int, int, int, int]]) -> int:
    relative = rva if rva < image_base else rva - image_base
    for start, extent, raw_size, raw_offset in sections:
        if start <= relative < start + extent:
            delta = relative - start
            if delta >= raw_size:
                raise ValueError(f"RVA {relative:#x} is not raw-backed")
            return raw_offset + delta
    raise ValueError(f"RVA {relative:#x} not mapped to a section")


def parse_relocs(blob: bytes) -> set[int]:
    sites: set[int] = set()
    cursor = 0
    while cursor < len(blob):
        if len(blob) - cursor < 8:
            raise ValueError("truncated relocation block header")
        page, block_size = struct.unpack_from("<II", blob, cursor)
        if block_size < 8 or block_size % 4 or cursor + block_size > len(blob):
            raise ValueError("invalid relocation block size")
        for at in range(cursor + 8, cursor + block_size, 2):
            item = struct.unpack_from("<H", blob, at)[0]
            kind, offset = item >> 12, item & 0x0FFF
            if kind == 0:
                continue
            if kind != 3:
                raise ValueError(f"unexpected relocation type {kind}")
            site = page + offset
            if site in sites:
                raise ValueError(f"duplicate HIGHLOW site {site:#x}")
            sites.add(site)
        cursor += block_size
    return sites


def encode_relocs(sites: set[int]) -> bytes:
    by_page: dict[int, list[int]] = defaultdict(list)
    for rva in sites:
        by_page[rva & ~0xFFF].append(rva & 0xFFF)
    output = bytearray()
    for page, offsets in sorted(by_page.items()):
        values = sorted((3 << 12) | offset for offset in offsets)
        if len(values) % 2:
            values.append(0)  # IMAGE_REL_BASED_ABSOLUTE alignment padding
        size = 8 + len(values) * 2
        output.extend(struct.pack("<II", page, size))
        output.extend(struct.pack(f"<{len(values)}H", *values))
    return bytes(output)


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--original", type=Path, default=ORIGINAL)
    p.add_argument("--feasibility", type=Path, default=FEASIBILITY)
    p.add_argument("--payload", type=Path, default=PAYLOAD)
    p.add_argument("--output-bin", type=Path, required=True)
    p.add_argument("--output-report", type=Path, required=True)
    p.add_argument("--expected-thunk-count", type=int, default=147)
    a = p.parse_args()
    for path in (a.output_bin, a.output_report):
        if path.exists():
            raise FileExistsError(f"refusing to overwrite {path}")

    image = a.original.read_bytes()
    image_hash = sha256(image)
    if image_hash != EXPECTED_SHA256:
        raise ValueError("original ASI SHA-256 does not match pinned input")
    nt = struct.unpack_from("<I", image, 0x3C)[0]
    if image[nt:nt + 4] != b"PE\0\0":
        raise ValueError("invalid PE signature")
    section_count = struct.unpack_from("<H", image, nt + 6)[0]
    optional_size = struct.unpack_from("<H", image, nt + 20)[0]
    optional = nt + 24
    if struct.unpack_from("<H", image, optional)[0] != 0x10B:
        raise ValueError("expected PE32")
    image_base = struct.unpack_from("<I", image, optional + 28)[0]
    section_alignment, file_alignment = struct.unpack_from("<II", image, optional + 32)
    old_size_image = struct.unpack_from("<I", image, optional + 56)[0]
    directory = optional + 96 + 5 * 8
    reloc_rva, reloc_size = struct.unpack_from("<II", image, directory)
    section_table = optional + optional_size
    sections = []
    section_meta = []
    raw_ends = []
    for index in range(section_count):
        at = section_table + index * 40
        name = image[at:at + 8].split(b"\0", 1)[0].decode("ascii", errors="replace")
        vsize, rva, raw_size, raw_offset = struct.unpack_from("<IIII", image, at + 8)
        sections.append((rva, max(vsize, raw_size), raw_size, raw_offset))
        section_meta.append({"name": name, "virtual_size": vsize, "rva": rva,
                             "raw_size": raw_size, "raw_offset": raw_offset})
        if raw_size:
            raw_ends.append(raw_offset + raw_size)
    reloc_offset = rva_to_offset(image, reloc_rva, image_base, sections)
    original_reloc_blob = image[reloc_offset:reloc_offset + reloc_size]
    old_sites = parse_relocs(original_reloc_blob)
    if len(old_sites) != 4681:
        raise ValueError(f"expected 4681 original-image HIGHLOW sites across .text/.rdata/.data, got {len(old_sites)}")

    feasibility_bytes = a.feasibility.read_bytes()
    feasibility = json.loads(feasibility_bytes)
    entries = [r for r in feasibility["entries"] if r["placement_mode"] == "jmp-rel32-thunk"]
    if len(entries) != a.expected_thunk_count:
        raise ValueError(f"expected {a.expected_thunk_count} five-byte entry thunks")
    removed = sorted(site for site in old_sites
                     if any(max(site, int(row["address"], 16) - image_base) <
                            min(site + 4, int(row["address"], 16) - image_base + 5)
                            for row in entries))
    expected_removed = {site for site in old_sites if any(
        max(image_base + site, int(row["address"], 16)) <
        min(image_base + site + 4, int(row["address"], 16) + 5) for row in entries)}
    if set(removed) != expected_removed:
        raise ValueError("removed original HIGHLOW sites do not match the thunk-window intersections")

    payload_bytes = a.payload.read_bytes()
    payload = json.loads(payload_bytes)
    added_rows = payload["candidate_highlow_sites_for_payload"]
    added = {int(row["rva"], 16) for row in added_rows}
    if len(added) != len(added_rows):
        raise ValueError("duplicate DIR32 fixup fields in code plus local data payload")
    if added & old_sites:
        raise ValueError("new payload HIGHLOW sites overlap original image sites")
    final_sites = (old_sites - set(removed)) | added
    blob = encode_relocs(final_sites)
    roundtrip_sites = parse_relocs(blob)
    if roundtrip_sites != final_sites:
        raise AssertionError("encoded relocation directory failed exact site round trip")

    align = lambda value, unit: (value + unit - 1) // unit * unit
    raw_append = align(max(raw_ends), file_alignment)
    payload_raw_size = align(int(payload["combined_code_and_rdata_payload_bytes"]), file_alignment)
    append_rva = align(old_size_image, section_alignment)
    reloc_section = next((row for row in section_meta if row["name"] == ".reloc"), None)
    if reloc_section is None or len(blob) > reloc_section["raw_size"] or len(blob) > reloc_section["virtual_size"]:
        raise ValueError("merged relocation directory does not fit the original .reloc section")
    code_data_end_rva = append_rva + int(payload["combined_code_and_rdata_payload_bytes"])
    size_image_new = align(max(old_size_image, code_data_end_rva), section_alignment)

    a.output_bin.parent.mkdir(parents=True, exist_ok=True)
    with a.output_bin.open("xb") as stream:
        stream.write(blob)
    report = {
        "scope": f"Standalone merged PE32 HIGHLOW directory for appending only the {len(entries)} assigned thunk bodies/data and replacing their five-byte entry windows; not a patched PE or full 705-function image.",
        "original_sha256": image_hash,
        "original_relocation_directory_rva": f"0x{reloc_rva:08X}",
        "original_relocation_directory_size": reloc_size,
        "original_highlow_site_count": len(old_sites),
        "original_sites_removed_at_thunk_windows": len(removed),
        "removed_site_rvas": [f"0x{site:08X}" for site in removed],
        "payload_report_sha256": sha256(payload_bytes),
        "payload_highlow_site_count_added": len(added),
        "payload_highlow_rva_count": len(roundtrip_sites),
        "final_highlow_site_count": len(final_sites),
        "encoded_relocation_directory_bytes": len(blob),
        "encoded_directory_sha256": sha256(blob),
        "directory_roundtrip_exact": roundtrip_sites == final_sites,
        "provisional_code_data_section_raw_offset": f"0x{raw_append:08X}",
        "provisional_code_data_section_raw_size": payload_raw_size,
        "relocation_directory_reuses_original_section": True,
        "relocation_directory_new_rva": f"0x{reloc_rva:08X}",
        "relocation_directory_new_size": len(blob),
        "original_reloc_section_virtual_size": reloc_section["virtual_size"],
        "original_reloc_section_raw_size": reloc_section["raw_size"],
        "original_reloc_section_raw_offset": f"0x{reloc_section['raw_offset']:08X}",
        "relocation_directory_fits_original_section": len(blob) <= min(reloc_section["virtual_size"], reloc_section["raw_size"]),
        "new_section_headers_needed_for_code_data": 1,
        "estimated_size_of_image": f"0x{size_image_new:08X}",
        "limitations": [
            f"This models only the appended {len(entries)}-body payload and its entry thunks; relocations for the remaining {705 - len(entries)} candidate bodies are not reconciled or included.",
            "The merged relocation directory is standalone; the code/data bytes and PE headers/directories are not patched or loader-tested. Support providers and imports still require final placement.",
            "No original PE bytes are modified and the standalone blob is not loadable as an ASI.",
        ],
        "output_blob": str(a.output_bin.resolve()),
    }
    a.output_report.parent.mkdir(parents=True, exist_ok=True)
    a.output_report.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({k: report[k] for k in (
        "original_highlow_site_count", "original_sites_removed_at_thunk_windows",
        "payload_highlow_site_count_added", "final_highlow_site_count",
        "encoded_relocation_directory_bytes", "directory_roundtrip_exact",
        "estimated_size_of_image"
    )}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
