#!/usr/bin/env python3
"""Recompute appended-object local-section fixups in the extended PE layout.

This targets only symbols defined in the same candidate object. It does not
resolve undefined externals or emit/patch PE bytes.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path

import pefile


PINNED_ASI_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"


def read_json(path: Path) -> dict:
    return json.loads(path.read_text(encoding="utf-8"))


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest().upper()


def parse_raw_addend(raw: str, kind: str) -> int:
    data = bytes(int(byte, 16) for byte in raw.split())
    if len(data) != 4:
        raise ValueError(f"expected 4-byte addend, got {raw!r}")
    return int.from_bytes(data, "little", signed=kind == "REL32")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--original-asi", type=Path, required=True)
    parser.add_argument("--symbols", type=Path, required=True)
    parser.add_argument("--payload-census", type=Path, required=True)
    parser.add_argument("--root-relocations", type=Path, required=True)
    parser.add_argument("--closure", type=Path, required=True)
    parser.add_argument("--bridge-layout", type=Path, required=True)
    parser.add_argument("--extended-layout", type=Path, required=True)
    parser.add_argument("--base-relocations", type=Path, required=True)
    parser.add_argument("--base-reloc-directory-bin", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()

    if sha256(args.original_asi) != PINNED_ASI_SHA256:
        raise SystemExit("original ASI hash differs from pinned target")
    symbols = read_json(args.symbols)
    census = read_json(args.payload_census)
    roots = read_json(args.root_relocations)
    closure = read_json(args.closure)
    bridge = read_json(args.bridge_layout)
    extended = read_json(args.extended_layout)
    base_relocs = read_json(args.base_relocations)
    pe = pefile.PE(str(args.original_asi), fast_load=False)
    image_base = int(pe.OPTIONAL_HEADER.ImageBase)
    section_alignment = int(pe.OPTIONAL_HEADER.SectionAlignment)
    old_code_end = int(bridge["bridge_payload_offset"]) + int(bridge["bridge_payload_bytes"])
    old_rdata_rva = (int(bridge["provisional_appended_rva"], 16) + old_code_end + section_alignment - 1) & ~(section_alignment - 1)
    old_data_rva = (
        old_rdata_rva + int(bridge["rdata_payload_bytes_before_file_alignment"])
        + section_alignment - 1
    ) & ~(section_alignment - 1)

    if extended["inputs"]["original_asi_sha256"] != PINNED_ASI_SHA256:
        raise SystemExit("extended layout is not based on pinned ASI")
    root_count = int(census["thunk_entries"])
    if roots["relocation_count"] != len(roots["relocations"]):
        raise SystemExit("appended root relocation count disagrees with relocation rows")
    if root_count != len(census["entries"]):
        raise SystemExit("appended root count disagrees with payload entries")
    if census["local_sections_report_sha256"] != sha256(args.root_relocations):
        raise SystemExit("root relocation inventory hash mismatch")
    if Path(closure["relocation_target_report"]).resolve() != args.root_relocations.resolve():
        raise SystemExit("local closure was inventoried from a different root report")
    if sha256(args.bridge_layout) != extended["inputs"]["appended_layout_sha256"]:
        raise SystemExit("extended layout does not reference this bridge layout")
    if sha256(args.payload_census) != bridge["payload_census_sha256"]:
        raise SystemExit("bridge layout references a different appended payload census")

    objects_dir = Path(symbols["inputs"]["objects"])
    functions = {int(row["entry_va"], 16): row for row in symbols["functions"]}
    census_entries = {int(row["entry_va"], 16): row for row in census["entries"]}
    if len(census_entries) != root_count:
        raise SystemExit(f"expected {root_count} thunk entries, got {len(census_entries)}")
    for section in closure["sections"]:
        owner = int(section["source_entry"], 16)
        object_path = objects_dir / f"{owner:08X}.obj"
        if sha256(object_path) != section["object_sha256"]:
            raise SystemExit(f"closure owner object hash mismatch: {object_path}")
        if section["inventory_hash_is_materialized_section_content"]:
            object_bytes = object_path.read_bytes()
            begin = int(section["section_raw_pointer"])
            end = begin + int(section["section_bytes"])
            if end > len(object_bytes):
                raise SystemExit(f"closure section escapes object: {owner:#x} #{section['section_number']}")
            actual = hashlib.sha256(object_bytes[begin:end]).hexdigest().upper()
            if actual != section["section_sha256"]:
                raise SystemExit(f"closure section byte hash mismatch: {owner:#x} #{section['section_number']}")

    # Map each source object's section number to its copied payload placement.
    section_layout: dict[tuple[int, int], dict] = {}
    for row in bridge["rdata_layout"]:
        key = (int(row["source_entry"], 16), int(row["section_number"]))
        section_layout[key] = {**row, "section_name": ".rdata", "rva": int(extended["layout"]["appended_rdata_rva_after_code_extension"], 16)}
    for row in bridge["local_xcode_layout"]:
        key = (int(row["source_entry"], 16), int(row["section_number"]))
        section_layout[key] = {**row, "section_name": ".xcode", "rva": int(extended["layout"]["appended_code_rva"], 16)}
    for row in bridge["data_local_layout"]:
        key = (int(row["source_entry"], 16), int(row["section_number"]))
        section_layout[key] = {**row, "rva": int(extended["layout"]["appended_data_rva_after_rdata_extension"], 16)}
    for row in extended["local_section_layout"]:
        if row["section_name"] != ".rdata":
            continue
        key = (int(row["source_entry_va"], 16), int(row["section_number"]))
        if key in section_layout:
            raise SystemExit(f"duplicate appended local section identity: {key}")
        section_layout[key] = {
            **row,
            "source_entry": row["source_entry_va"],
            "rva": int(extended["layout"]["appended_rdata_rva_after_code_extension"], 16),
        }

    # The earlier non-.rdata closure census did not copy literals referenced
    # only by a local .xcode section. Discover such sections directly in the
    # verified COFF objects and append them after the already planned rdata.
    missing_closure_rdata: dict[tuple[int, int], dict] = {}
    for section in closure["sections"]:
        owner = int(section["source_entry"], 16)
        for reloc in section["relocations"]:
            if reloc["target_class"] != "same-object-section" or reloc["target_section"] != ".rdata":
                continue
            key = (owner, int(reloc["target_section_number"]))
            if key not in section_layout:
                missing_closure_rdata[key] = {"owner": owner, "number": key[1]}
    rdata_cursor = int(extended["layout"]["extended_rdata_virtual_size"])
    rdata_rva = int(extended["layout"]["appended_rdata_rva_after_code_extension"], 16)
    closure_owners = {
        int(row["source_entry"], 16): row for row in closure["sections"]
    }
    additional_rdata_sections: list[dict] = []
    for key in sorted(missing_closure_rdata):
        owner, number = key
        owner_row = closure_owners.get(owner)
        if owner_row is None:
            raise SystemExit(f"rdata target object absent from closure object census: {owner:#x}")
        object_path = objects_dir / f"{owner:08X}.obj"
        if sha256(object_path) != owner_row["object_sha256"]:
            raise SystemExit(f"closure object hash mismatch: {object_path}")
        data = object_path.read_bytes()
        machine, section_count, _, _, _, optional_size, _ = struct.unpack_from("<HHIIIHH", data)
        if machine != 0x14C or not 1 <= number <= section_count:
            raise SystemExit(f"invalid COFF section identity {key}")
        header_offset = 20 + optional_size + (number - 1) * 40
        name, _, _, raw_size, raw_offset, _, _, reloc_count, _, flags = struct.unpack_from(
            "<8sIIIIIIHHI", data, header_offset
        )
        section_name = name.split(b"\0", 1)[0].decode("ascii", errors="replace")
        if section_name != ".rdata" or reloc_count:
            raise SystemExit(f"unexpected relocation-bearing closure literal section {key}: {section_name}, {reloc_count} relocs")
        if raw_offset + raw_size > len(data):
            raise SystemExit(f"COFF .rdata raw section escapes object: {key}")
        section_bytes = data[raw_offset:raw_offset + raw_size]
        alignment_code = (flags >> 20) & 0xF
        alignment = 1 << (alignment_code - 1) if alignment_code else 1
        rdata_cursor = (rdata_cursor + alignment - 1) & ~(alignment - 1)
        extra = {
            "source_entry": hex(owner),
            "section_number": number,
            "section_name": section_name,
            "size": raw_size,
            "alignment": alignment,
            "payload_offset": rdata_cursor,
            "section_sha256": hashlib.sha256(section_bytes).hexdigest().upper(),
            "object_sha256": owner_row["object_sha256"],
            "relocation_count": reloc_count,
            "rva": rdata_rva,
        }
        section_layout[key] = extra
        additional_rdata_sections.append(extra)
        rdata_cursor += raw_size
    final_rdata_virtual_size = rdata_cursor
    final_data_rva = (
        rdata_rva + final_rdata_virtual_size + section_alignment - 1
    ) & ~(section_alignment - 1)
    data_section_shift = final_data_rva != int(extended["layout"]["appended_data_rva_after_rdata_extension"], 16)
    if data_section_shift:
        for row in bridge["data_local_layout"]:
            key = (int(row["source_entry"], 16), int(row["section_number"]))
            section_layout[key]["rva"] = final_data_rva

    fixups: list[dict] = []
    site_rvas: set[int] = set()

    def add_fixup(owner: int, source_rva: int, site: int, kind: str, symbol: str,
                  target_va: int, addend: int, origin: str) -> None:
        site_rva = source_rva + site
        rel32_fits = True
        if kind == "DIR32":
            value = target_va + addend
            if not 0 <= value <= 0xFFFFFFFF:
                raise SystemExit(f"DIR32 overflow at {site_rva:#x}")
        elif kind == "REL32":
            value = target_va + addend - (image_base + site_rva + 4)
            rel32_fits = -(1 << 31) <= value < (1 << 31)
            if not rel32_fits:
                raise SystemExit(f"REL32 out of range at {site_rva:#x}")
        else:
            raise SystemExit(f"unsupported relocation type {kind}")
        if site_rva in site_rvas:
            raise SystemExit(f"duplicate fixup site {site_rva:#x}")
        site_rvas.add(site_rva)
        fixups.append({
            "origin": origin,
            "owner_entry_va": hex(owner),
            "site_rva": hex(site_rva),
            "type": kind,
            "symbol": symbol,
            "target_va": hex(target_va),
            "raw_addend": addend,
            "computed_field_value": hex(value & 0xFFFFFFFF),
            "rel32_fits_signed_range": rel32_fits,
        })

    # Recompute every root-body reference to sections copied from its own
    # COFF object (rdata/data/bss/xcode).
    root_fixups = 0
    for row in roots["relocations"]:
        if row["target_class"] != "defined-in-same-object-section":
            continue
        owner = int(row["source_entry"], 16)
        function = functions.get(owner)
        entry = census_entries.get(owner)
        if function is None or entry is None:
            raise SystemExit(f"same-object root owner missing: {owner:#x}")
        obj_path = objects_dir / f"{owner:08X}.obj"
        if sha256(obj_path) != entry["object_sha256"]:
            raise SystemExit(f"root object hash mismatch: {obj_path}")
        matches = [
            reloc for reloc in function["relocations"]
            if int(reloc["offset"]) == int(row["site"])
            and reloc["type"] == row["type"]
            and reloc["symbol"] == row["target_symbol"]
            and reloc["symbol_defined_in_object"]
        ]
        if len(matches) != 1:
            raise SystemExit(f"root COFF relocation does not uniquely join at {owner:#x}+{row['site']:#x}")
        reloc = matches[0]
        key = (owner, int(row["target_section_number"]))
        target_section = section_layout.get(key)
        if target_section is None or target_section["section_name"] != row["target_section"]:
            raise SystemExit(f"root local target section not placed: {key} {row['target_section']}")
        target_va = image_base + int(target_section["rva"]) + int(target_section["payload_offset"]) + int(row["target_value"])
        source_rva = int(bridge["provisional_appended_rva"], 16) + int(entry["provisional_payload_offset"])
        add_fixup(owner, source_rva, int(row["site"]), row["type"], row["target_symbol"],
                  target_va, int(reloc["raw_addend"], 16), "appended-root-to-own-local-section")
        root_fixups += 1
    expected_root_fixups = sum(
        row["target_class"] == "defined-in-same-object-section"
        for row in roots["relocations"]
    )
    if root_fixups != expected_root_fixups:
        raise SystemExit(f"root local-section join count mismatch: {root_fixups} != {expected_root_fixups}")

    # Recompute the 26 local-closure relocations that target another section
    # from the same source object. Independently inventory every DIR32 field
    # in these copied sections; loader HIGHLOW sites are required even where
    # the target is an unresolved external whose final value is handled later.
    closure_fixups = 0
    closure_dir32_sites: set[int] = set()
    for section in closure["sections"]:
        owner = int(section["source_entry"], 16)
        source_key = (owner, int(section["section_number"]))
        source_section = section_layout.get(source_key)
        if source_section is None or source_section["section_name"] != section["section_name"]:
            raise SystemExit(f"closure source section not placed: {source_key}")
        source_rva = int(source_section["rva"]) + int(source_section["payload_offset"])
        for reloc in section["relocations"]:
            if reloc["type"] == "DIR32":
                site_rva = source_rva + int(reloc["site"])
                if site_rva in closure_dir32_sites:
                    raise SystemExit(f"duplicate closure DIR32 site {site_rva:#x}")
                closure_dir32_sites.add(site_rva)
            if reloc["target_class"] != "same-object-section":
                continue
            target_key = (owner, int(reloc["target_section_number"]))
            target_section = section_layout.get(target_key)
            if target_section is None or target_section["section_name"] != reloc["target_section"]:
                raise SystemExit(f"closure target section not placed: {target_key}")
            target_va = image_base + int(target_section["rva"]) + int(target_section["payload_offset"]) + int(reloc["target_value"])
            add_fixup(owner, source_rva, int(reloc["site"]), reloc["type"], reloc["target_symbol"],
                      target_va, parse_raw_addend(reloc["raw_field_bytes"], reloc["type"]),
                      "appended-local-section-to-same-object-section")
            closure_fixups += 1
    expected_closure_fixups = sum(
        reloc["target_class"] == "same-object-section"
        for section in closure["sections"] for reloc in section["relocations"]
    )
    expected_closure_dir32 = sum(
        reloc["type"] == "DIR32"
        for section in closure["sections"] for reloc in section["relocations"]
    )
    if closure_fixups != expected_closure_fixups:
        raise SystemExit(f"closure internal join count mismatch: {closure_fixups} != {expected_closure_fixups}")
    if len(closure_dir32_sites) != expected_closure_dir32:
        raise SystemExit(f"closure DIR32 count mismatch: {len(closure_dir32_sites)} != {expected_closure_dir32}")

    reloc_blob = args.base_reloc_directory_bin.read_bytes()
    if len(reloc_blob) != int(base_relocs["encoded_directory_bytes"]):
        raise SystemExit("base relocation blob size disagrees with report")
    reloc_sites: set[int] = set()
    cursor = 0
    while cursor < len(reloc_blob):
        if cursor + 8 > len(reloc_blob):
            raise SystemExit("truncated base relocation block")
        page = int.from_bytes(reloc_blob[cursor:cursor + 4], "little")
        size = int.from_bytes(reloc_blob[cursor + 4:cursor + 8], "little")
        if size < 8 or cursor + size > len(reloc_blob) or (size - 8) % 2:
            raise SystemExit("invalid base relocation block")
        for pos in range(cursor + 8, cursor + size, 2):
            entry = int.from_bytes(reloc_blob[pos:pos + 2], "little")
            if entry >> 12 == 3:
                reloc_sites.add(page + (entry & 0xFFF))
        cursor += size
    dir32_sites = {int(row["site_rva"], 16) for row in fixups if row["type"] == "DIR32"}
    all_known_dir32_sites = dir32_sites | closure_dir32_sites
    missing_dir32_sites = all_known_dir32_sites - reloc_sites
    direct_extension_sites = {int(value, 16) for value in extended["new_highlow_site_rvas"]}
    api_extension_sites = {
        int(row["highlow_site_rva"], 16) for row in extended["direct_api_thunks"]
    }
    if len(direct_extension_sites) != len(set(extended["new_highlow_site_rvas"])):
        raise SystemExit("duplicate direct local-closure HIGHLOW sites")
    if len(api_extension_sites) != len(extended["direct_api_thunks"]):
        raise SystemExit("direct API-thunk HIGHLOW site count mismatch")
    if (direct_extension_sites | api_extension_sites) & reloc_sites:
        raise SystemExit("extended direct-body sites overlap existing relocation directory")
    if direct_extension_sites & api_extension_sites:
        raise SystemExit("direct closure and API thunk HIGHLOW sites overlap")
    if (direct_extension_sites | api_extension_sites) & missing_dir32_sites:
        raise SystemExit("direct extension sites overlap appended-root closure fixups")

    def serialize_highlow(sites: set[int]) -> bytes:
        pages: dict[int, list[int]] = {}
        for rva in sites:
            pages.setdefault(rva & ~0xFFF, []).append(rva & 0xFFF)
        encoded = bytearray()
        for page, offsets in sorted(pages.items()):
            entries = [0x3000 | offset for offset in sorted(offsets)]
            if len(entries) % 2:
                entries.append(0)  # IMAGE_REL_BASED_ABSOLUTE padding
            block_size = 8 + 2 * len(entries)
            encoded.extend(struct.pack("<II", page, block_size))
            encoded.extend(struct.pack("<" + "H" * len(entries), *entries))
        return bytes(encoded)

    if len(reloc_sites) != int(base_relocs["final_highlow_sites"]):
        raise SystemExit("base relocation site count differs from authoritative report")
    if serialize_highlow(reloc_sites) != reloc_blob:
        raise SystemExit("base relocation serializer did not reproduce the authoritative directory")
    expanded_sites = reloc_sites | all_known_dir32_sites | direct_extension_sites | api_extension_sites
    expanded_blob = serialize_highlow(expanded_sites)
    roundtrip_sites: set[int] = set()
    cursor = 0
    while cursor < len(expanded_blob):
        page = int.from_bytes(expanded_blob[cursor:cursor + 4], "little")
        size = int.from_bytes(expanded_blob[cursor + 4:cursor + 8], "little")
        if size < 8 or cursor + size > len(expanded_blob) or (size - 8) % 2:
            raise SystemExit("expanded relocation serialization is malformed")
        for pos in range(cursor + 8, cursor + size, 2):
            entry = int.from_bytes(expanded_blob[pos:pos + 2], "little")
            if entry >> 12 == 3:
                roundtrip_sites.add(page + (entry & 0xFFF))
        cursor += size
    if roundtrip_sites != expanded_sites:
        raise SystemExit("expanded relocation serialize/parse site set mismatch")
    reloc_section_capacity = next(
        int(section.SizeOfRawData) for section in pe.sections
        if section.Name.rstrip(b"\0") == b".reloc"
    )
    if len(expanded_blob) > reloc_section_capacity:
        raise SystemExit("expanded relocation directory exceeds original .reloc capacity")

    output = {
        "scope": "Recomputed appended-root and appended-local-section same-object fixups and inventoried all copied-closure DIR32 sites in the extended layout; no PE fields were written.",
        "inputs": {
            "original_asi_sha256": PINNED_ASI_SHA256,
            "payload_census_sha256": sha256(args.payload_census),
            "root_relocations_sha256": sha256(args.root_relocations),
            "closure_sha256": sha256(args.closure),
            "extended_layout_sha256": sha256(args.extended_layout),
            "base_relocation_report_sha256": sha256(args.base_relocations),
            "base_relocation_blob_sha256": sha256(args.base_reloc_directory_bin),
        },
        "summary": {
            "appended_root_count": len(census_entries),
            "root_same_object_section_fixups": root_fixups,
            "local_closure_same_object_fixups": closure_fixups,
            "local_closure_dir32_fields": len(closure_dir32_sites),
            "total_fixups_recomputed": len(fixups),
            "counts_by_origin_and_type": {
                f"{origin}:{kind}": sum(1 for row in fixups if row["origin"] == origin and row["type"] == kind)
                for origin, kind in sorted({(row["origin"], row["type"]) for row in fixups})
            },
            "unique_sites": len(site_rvas),
            "dir32_sites_present_in_base_relocation_table": len(all_known_dir32_sites & reloc_sites),
            "missing_dir32_sites_added": len(missing_dir32_sites),
            "direct_body_closure_highlow_sites_added": len(direct_extension_sites),
            "direct_api_thunk_highlow_sites_added": len(api_extension_sites),
            "base_relocation_site_count": len(reloc_sites),
            "expanded_relocation_site_count": len(expanded_sites),
            "expanded_relocation_blob_bytes": len(expanded_blob),
            "original_reloc_section_capacity": reloc_section_capacity,
            "expanded_relocation_fits": len(expanded_blob) <= reloc_section_capacity,
            "expanded_relocation_roundtrip_exact": roundtrip_sites == expanded_sites,
            "recomputed_same_object_rel32_in_range": all(row["rel32_fits_signed_range"] for row in fixups),
            "additional_closure_rdata_sections": len(additional_rdata_sections),
            "additional_closure_rdata_bytes": sum(row["size"] for row in additional_rdata_sections),
            "final_rdata_virtual_size": final_rdata_virtual_size,
            "data_rva_moved_beyond_extended_layout": data_section_shift,
        },
        "layout": {
            "old_rdata_rva": hex(old_rdata_rva),
            "new_rdata_rva": extended["layout"]["appended_rdata_rva_after_code_extension"],
            "old_data_rva": hex(old_data_rva),
            "new_data_rva": hex(final_data_rva),
            "code_rva_unchanged": extended["layout"]["appended_code_rva"],
        },
        "additional_closure_rdata_sections": additional_rdata_sections,
        "added_highlow_site_rvas": [hex(site) for site in sorted(missing_dir32_sites)],
        "limitations": [
            "Undefined external/runtime/provider/IAT and installer fixups are not recomputed by this focused report.",
            "The report does not construct, patch, load, or game-test a PE/ASI.",
        ],
        "fixups": fixups,
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(output, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(output["summary"], indent=2))
    print(json.dumps(output["layout"], indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
