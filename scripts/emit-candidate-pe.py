#!/usr/bin/env python3
"""Build a new static-test PE/ASI from the audited section payloads."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path

import pefile


PINNED_ASI = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"
IMAGE_BASE_EXPECTED = 0x10000000


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def align(value: int, boundary: int) -> int:
    return (value + boundary - 1) & ~(boundary - 1)


def parse_relocs(blob: bytes) -> set[int]:
    sites: set[int] = set()
    pos = 0
    while pos < len(blob):
        if pos + 8 > len(blob):
            raise ValueError("truncated relocation block")
        page, size = struct.unpack_from("<II", blob, pos)
        if size < 8 or size % 4 or pos + size > len(blob):
            raise ValueError("invalid relocation block bounds/alignment")
        for at in range(pos + 8, pos + size, 2):
            entry = struct.unpack_from("<H", blob, at)[0]
            kind, offset = entry >> 12, entry & 0xFFF
            if kind == 0:
                continue
            if kind != 3:
                raise ValueError(f"unexpected relocation kind {kind}")
            site = page + offset
            if site in sites:
                raise ValueError(f"duplicate HIGHLOW site {site:#x}")
            sites.add(site)
        pos += size
    return sites


def pe_headers(image: bytes) -> dict[str, object]:
    if image[:2] != b"MZ":
        raise ValueError("missing MZ signature")
    pe = struct.unpack_from("<I", image, 0x3C)[0]
    if image[pe:pe + 4] != b"PE\0\0":
        raise ValueError("bad PE signature")
    section_count = struct.unpack_from("<H", image, pe + 6)[0]
    optional_size = struct.unpack_from("<H", image, pe + 20)[0]
    optional = pe + 24
    if struct.unpack_from("<H", image, optional)[0] != 0x10B:
        raise ValueError("expected PE32")
    section_table = optional + optional_size
    sections = []
    for i in range(section_count):
        at = section_table + i * 40
        name = image[at:at + 8].split(b"\0", 1)[0].decode("ascii")
        vsize, rva, raw_size, raw_offset = struct.unpack_from("<IIII", image, at + 8)
        characteristics = struct.unpack_from("<I", image, at + 36)[0]
        sections.append({"name": name, "virtual_size": vsize, "rva": rva,
                         "raw_size": raw_size, "raw_offset": raw_offset,
                         "characteristics": characteristics, "header_offset": at})
    return {"pe": pe, "section_count": section_count, "optional": optional,
            "optional_size": optional_size, "section_table": section_table,
            "sections": sections,
            "image_base": struct.unpack_from("<I", image, optional + 28)[0],
            "section_alignment": struct.unpack_from("<I", image, optional + 32)[0],
            "file_alignment": struct.unpack_from("<I", image, optional + 36)[0],
            "size_headers": struct.unpack_from("<I", image, optional + 60)[0],
            "size_image": struct.unpack_from("<I", image, optional + 56)[0],
            "reloc_directory_offset": optional + 96 + 5 * 8}


def checksum(image: bytearray, field_offset: int) -> int:
    total = 0
    for offset in range(0, len(image), 2):
        if field_offset <= offset < field_offset + 4:
            continue
        word = image[offset]
        if offset + 1 < len(image):
            word |= image[offset + 1] << 8
        total = (total & 0xFFFF) + word + (total >> 16)
    total = (total & 0xFFFF) + (total >> 16)
    total = (total & 0xFFFF) + len(image)
    return total & 0xFFFFFFFF


def load_json(path: Path) -> dict:
    return json.loads(path.read_text(encoding="utf-8"))


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    for name in ("original-asi", "text", "text-report", "xcode", "xcode-report",
                 "rdata", "data", "data-report", "reloc", "reloc-report",
                 "appended-fixups", "direct-layout", "direct-fixups", "base-reloc",
                 "thunk-overlap-report"):
        ap.add_argument(f"--{name}", required=True, type=Path)
    ap.add_argument("--output-asi", required=True, type=Path)
    ap.add_argument("--output-report", required=True, type=Path)
    args = ap.parse_args()
    for output in (args.output_asi, args.output_report):
        if output.exists():
            raise FileExistsError(f"refusing to overwrite {output}")

    original = args.original_asi.read_bytes()
    original_hash = digest(original)
    if original_hash != PINNED_ASI:
        raise ValueError(f"original ASI hash mismatch: {original_hash}")
    text = args.text.read_bytes()
    xcode = args.xcode.read_bytes()
    rdata = args.rdata.read_bytes()
    data = args.data.read_bytes()
    reloc = args.reloc.read_bytes()
    text_report = load_json(args.text_report)
    xcode_report = load_json(args.xcode_report)
    data_report = load_json(args.data_report)
    reloc_report = load_json(args.reloc_report)
    appended_report = load_json(args.appended_fixups)
    direct_layout = load_json(args.direct_layout)
    direct_fixups = load_json(args.direct_fixups)
    thunk_overlap_report = load_json(args.thunk_overlap_report)

    if digest(text) != text_report.get("output_text_sha256"):
        raise ValueError("candidate .text differs from its manifest")
    if text_report.get("original_asi_sha256") != PINNED_ASI or text_report.get("entry_thunk_count") != len(text_report.get("entry_thunks", [])):
        raise ValueError("candidate .text report is not based on current 705 plan")
    if digest(xcode) != xcode_report.get("output_xcode_sha256"):
        raise ValueError("candidate .xcode differs from its direct-closure fixup report")
    if digest(rdata) != xcode_report.get("output_rdata_sha256"):
        raise ValueError("candidate .rdata differs from its direct-closure fixup report")
    if digest(data) != data_report.get("output_data_sha256"):
        raise ValueError("candidate .data differs from applied-fixup report")
    if digest(reloc) != reloc_report.get("sha256"):
        raise ValueError("relocation blob differs from final relocation report")
    direct_count = int(direct_fixups.get("unique_fields", -1))
    appended_count = int(appended_report.get("applied_unique_fields", -1))
    if (direct_count != len(direct_fixups.get("fixups", []))
            or appended_count != len(appended_report.get("fixups", []))
            or not appended_report.get("all_raw_addends_matched")
            or not appended_report.get("all_computed_values_rederived")):
        raise ValueError("input fixup manifests do not cover the expected fields")

    headers = pe_headers(original)
    if (headers["image_base"], headers["section_alignment"], headers["file_alignment"]) != (IMAGE_BASE_EXPECTED, 0x1000, 0x200):
        raise ValueError("unexpected original PE base/alignment")
    sections = headers["sections"]
    if len(sections) != 5 or [x["name"] for x in sections] != [".text", ".rdata", ".data", ".rsrc", ".reloc"]:
        raise ValueError("original PE section inventory differs from audited layout")
    text_section = next(x for x in sections if x["name"] == ".text")
    reloc_section = next(x for x in sections if x["name"] == ".reloc")
    if len(text) != int(text_section["raw_size"]):
        raise ValueError("candidate .text raw size mismatch")
    if len(reloc) > int(reloc_section["raw_size"]):
        raise ValueError("expanded relocation directory exceeds original .reloc section")
    if (reloc_report.get("unique_site_count") != len(parse_relocs(reloc))
            or reloc_report.get("serialized_bytes") != len(reloc)
            or not reloc_report.get("roundtrip_exact")
            or not reloc_report.get("fits_original_reloc_raw_capacity")):
        raise ValueError("final relocation table differs from its audited report")

    # Independently rebuild the complete HIGHLOW set from the 6,136-site baseline
    # plus the exact late appended-closure/direct-closure/direct-IAT additions.
    base_sites = parse_relocs(args.base_reloc.read_bytes())
    appended_sites = {int(row["site_rva"], 16) for row in appended_report["fixups"]
                      if row["type"] == "DIR32"}
    direct_closure_sites = {int(row["site_rva"], 16) for row in direct_layout["fixups"]
                            if row["source_section"]["section_name"] != ".text"
                            and row["relocation_type"] == "DIR32"}
    direct_api_sites = {int(row["highlow_site_rva"], 16) for row in direct_layout["direct_api_thunks"]}
    expected_sites = base_sites | appended_sites | direct_closure_sites | direct_api_sites
    actual_sites = parse_relocs(reloc)
    expected_appended = sum(row.get("type") == "DIR32" for row in appended_report["fixups"])
    expected_closure = sum(row.get("source_section", {}).get("section_name") != ".text"
                           and row.get("relocation_type") == "DIR32" for row in direct_layout["fixups"])
    if (len(appended_sites) != expected_appended
            or len(direct_closure_sites) != expected_closure
            or len(direct_api_sites) != len(direct_layout.get("direct_api_thunks", []))):
        raise ValueError("HIGHLOW input inventories do not match their manifests")
    if expected_sites != actual_sites or len(actual_sites) != reloc_report.get("unique_site_count"):
        raise ValueError(f"final HIGHLOW set mismatch: expected {len(expected_sites)}, got {len(actual_sites)}")

    # HIGHLOW DWORDs partially or fully replaced by E9 entry thunks must not
    # be reapplied by the loader to the new instruction/displacement bytes.
    original_pe = pefile.PE(data=original, fast_load=False)
    original_sites = {
        entry.rva
        for block in original_pe.DIRECTORY_ENTRY_BASERELOC
        for entry in block.entries
        if entry.type == 3
    }
    overwritten_sites = {
        int(row["relocation_site_va"], 16) - IMAGE_BASE_EXPECTED
        for row in thunk_overlap_report["overlaps"]
    }
    overlap_count = int(thunk_overlap_report.get("overlapping_relocation_count", -1))
    if (thunk_overlap_report.get("entry_count") != text_report.get("entry_thunk_count")
            or len(overwritten_sites) != overlap_count
            or not overwritten_sites <= original_sites
            or overwritten_sites & base_sites
            or overwritten_sites & actual_sites):
        raise ValueError("HIGHLOW sites overwritten by entry thunks are not cleanly removed")

    file_alignment = int(headers["file_alignment"])
    section_alignment = int(headers["section_alignment"])
    original_file_end = max(int(s["raw_offset"]) + int(s["raw_size"]) for s in sections)
    if original_file_end != len(original) or original_file_end % file_alignment:
        raise ValueError("original file end is not the expected aligned append point")
    xraw, rraw, draw = (align(len(xcode), file_alignment), align(len(rdata), file_alignment), align(len(data), file_alignment))
    xrva = align(max(int(s["rva"]) + max(int(s["virtual_size"]), int(s["raw_size"])) for s in sections), section_alignment)
    rrva = align(xrva + len(xcode), section_alignment)
    drva = align(rrva + len(rdata), section_alignment)
    final_image_size = align(drva + len(data), section_alignment)
    if (len(xcode) != xcode_report.get("code_virtual_size", len(xcode))
            or len(rdata) != data_report.get("rdata_virtual_size", len(rdata))
            or len(data) != data_report.get("data_virtual_size", len(data))
            or xraw != align(len(xcode), file_alignment)
            or rraw != align(len(rdata), file_alignment)
            or draw != align(len(data), file_alignment)):
        raise ValueError("combined section geometry differs from its materialization reports")
    xoff = original_file_end
    roff = xoff + xraw
    doff = roff + rraw

    section_table = int(headers["section_table"])
    new_table_end = section_table + (len(sections) + 3) * 40
    if new_table_end > int(headers["size_headers"]):
        raise ValueError("insufficient original PE header slack for three section headers")
    output = bytearray(original)
    output[int(text_section["raw_offset"]):int(text_section["raw_offset"]) + len(text)] = text
    reloc_offset = int(reloc_section["raw_offset"])
    reloc_raw_size = int(reloc_section["raw_size"])
    output[reloc_offset:reloc_offset + reloc_raw_size] = reloc + bytes(reloc_raw_size - len(reloc))
    output.extend(xcode + bytes(xraw - len(xcode)))
    output.extend(rdata + bytes(rraw - len(rdata)))
    output.extend(data + bytes(draw - len(data)))

    # Relocation directory remains in the original .reloc RVA, with a smaller
    # virtual size and an enlarged data-directory byte count.
    struct.pack_into("<I", output, int(reloc_section["header_offset"]) + 8, len(reloc))
    struct.pack_into("<II", output, int(headers["reloc_directory_offset"]), int(reloc_section["rva"]), len(reloc))

    new_sections = [
        (b".xcode", len(xcode), xrva, xraw, xoff, 0x60000020),
        (b".xrdata", len(rdata), rrva, rraw, roff, 0x40000040),
        (b".xdata", len(data), drva, draw, doff, 0xC0000040),
    ]
    for index, (name, vsize, rva, raw_size, raw_offset, flags) in enumerate(new_sections):
        at = section_table + (len(sections) + index) * 40
        output[at:at + 40] = bytes(40)
        output[at:at + 8] = name.ljust(8, b"\0")
        struct.pack_into("<IIIIIIHHI", output, at + 8,
                         vsize, rva, raw_size, raw_offset, 0, 0, 0, 0, flags)

    struct.pack_into("<H", output, int(headers["pe"]) + 6, len(sections) + 3)
    optional = int(headers["optional"])
    size_of_code = struct.unpack_from("<I", output, optional + 4)[0]
    size_of_init = struct.unpack_from("<I", output, optional + 8)[0]
    struct.pack_into("<I", output, optional + 4, size_of_code + xraw)
    struct.pack_into("<I", output, optional + 8, size_of_init + rraw + draw)
    struct.pack_into("<I", output, optional + 56, final_image_size)
    checksum_offset = optional + 64
    struct.pack_into("<I", output, checksum_offset, 0)
    struct.pack_into("<I", output, checksum_offset, checksum(output, checksum_offset))

    # Independent parse and byte-for-byte section verification before writing.
    parsed = pefile.PE(data=bytes(output), fast_load=False)
    if len(parsed.sections) != 8 or parsed.OPTIONAL_HEADER.SizeOfImage != final_image_size:
        raise ValueError("independent PE parser rejected final section count/SizeOfImage")
    if parsed.OPTIONAL_HEADER.DATA_DIRECTORY[5].Size != len(reloc):
        raise ValueError("independent parser sees wrong base-relocation directory size")
    expected_headers = {".xcode": (xrva, len(xcode), xoff, xraw),
                        ".xrdata": (rrva, len(rdata), roff, rraw),
                        ".xdata": (drva, len(data), doff, draw)}
    for section in parsed.sections:
        name = section.Name.rstrip(b"\0").decode("ascii")
        if name in expected_headers:
            expected = expected_headers[name]
            actual = (section.VirtualAddress, section.Misc_VirtualSize,
                      section.PointerToRawData, section.SizeOfRawData)
            if actual != expected:
                raise ValueError(f"independent PE parser mismatch for {name}: {actual} != {expected}")
    if parse_relocs(bytes(output[reloc_offset:reloc_offset + len(reloc)])) != expected_sites:
        raise ValueError("final image relocation bytes differ from independently rebuilt site set")

    report = {
        "scope": "New experimental PE32 candidate assembled from pinned reverse-engineering payloads; not runtime-tested.",
        "original_asi_sha256": original_hash,
        "candidate_asi_sha256": digest(output),
        "candidate_file_bytes": len(output),
        "section_count": len(parsed.sections),
        "sections": {name.decode(): {"rva": f"0x{rva:08X}", "virtual_size": vsize,
                                     "raw_offset": f"0x{raw_offset:08X}", "raw_size": raw_size}
                     for name, vsize, rva, raw_size, raw_offset, _ in new_sections},
        "text_sha256": digest(text), "xcode_sha256": digest(xcode),
        "rdata_sha256": digest(rdata), "data_sha256": digest(data),
        "relocation_sha256": digest(reloc), "highlow_sites": len(actual_sites),
        "highlow_site_set_matches_independent_union": True,
        "original_relocation_sites_overwritten_by_entry_thunks": len(overwritten_sites),
        "thunk_overwritten_relocations_present_in_final_directory": False,
        "independent_pe_parser_passed": True,
        "checksum": struct.unpack_from("<I", output, checksum_offset)[0],
        "limitations": [
            "This is a reconstructed candidate, not the author's original source build.",
            "Static PE parsing does not prove successful plugin-loader initialization or game behavior.",
            "No LoadLibrary, GTA launch, or gameplay test was run by this emitter.",
            "Original ASI was read-only input and was not modified.",
        ],
    }
    args.output_asi.parent.mkdir(parents=True, exist_ok=True)
    with args.output_asi.open("xb") as stream:
        stream.write(output)
    with args.output_report.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    # Read back the created candidate and ensure the persisted bytes match.
    persisted = args.output_asi.read_bytes()
    if digest(persisted) != report["candidate_asi_sha256"]:
        raise ValueError("persisted experimental candidate hash mismatch")
    print(json.dumps({k: report[k] for k in (
        "candidate_asi_sha256", "candidate_file_bytes", "section_count",
        "highlow_sites", "highlow_site_set_matches_independent_union",
        "independent_pe_parser_passed"
    )}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
