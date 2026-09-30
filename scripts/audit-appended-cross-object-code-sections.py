#!/usr/bin/env python3
"""Place cross-object .xcode sections referenced by appended roots.

Reads COFF definitions/bytes/relocations and assigns provisional code offsets.
It does not patch a PE or emit an ASI.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path

import pefile


PINNED = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"
REL_TYPES = {0x0006: "DIR32", 0x0014: "REL32"}


def read_json(path: Path) -> dict:
    return json.loads(path.read_text(encoding="utf-8"))


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def file_digest(path: Path) -> str:
    return digest(path.read_bytes())


def coff(path: Path) -> tuple[list[dict], dict[str, list[dict]]]:
    data = path.read_bytes()
    machine, count, _, symbol_offset, symbol_count, optional_size, _ = struct.unpack_from("<HHIIIHH", data)
    if machine != 0x14C:
        raise SystemExit(f"not an i386 COFF object: {path}")
    section_table = 20 + optional_size
    headers = []
    for index in range(count):
        h = struct.unpack_from("<8sIIIIIIHHI", data, section_table + 40 * index)
        name = h[0].split(b"\0", 1)[0].decode("ascii", errors="replace")
        headers.append({"number": index + 1, "name": name, "size": h[3], "raw": h[4],
                        "reloc": h[5], "reloc_count": h[7], "flags": h[9]})
    string_table_offset = symbol_offset + symbol_count * 18
    string_size = struct.unpack_from("<I", data, string_table_offset)[0]
    strings = data[string_table_offset:string_table_offset + string_size]

    def name(raw: bytes) -> str:
        if raw[:4] == b"\0\0\0\0":
            start = struct.unpack_from("<I", raw, 4)[0]
            end = strings.find(b"\0", start)
            return strings[start:end].decode("ascii", errors="replace")
        return raw.rstrip(b"\0").decode("ascii", errors="replace")

    symbols_by_index: dict[int, dict] = {}
    symbols_by_name: dict[str, list[dict]] = {}
    cursor, index = symbol_offset, 0
    while index < symbol_count:
        entry = data[cursor:cursor + 18]
        symbol_name = name(entry[:8])
        value, section_number, _, storage, aux = struct.unpack_from("<IhHBB", entry, 8)
        symbol = {"index": index, "name": symbol_name, "value": value,
                  "section_number": section_number, "storage_class": storage}
        symbols_by_index[index] = symbol
        if symbol_name:
            symbols_by_name.setdefault(symbol_name, []).append(symbol)
        cursor += 18 * (1 + aux)
        index += 1 + aux

    for section in headers:
        raw, size, reloc_offset, reloc_count = section["raw"], section["size"], section["reloc"], section["reloc_count"]
        if raw + size > len(data):
            raise SystemExit(f"section raw data escapes object: {path} #{section['number']}")
        section["bytes"] = data[raw:raw + size]
        section["relocations"] = []
        for i in range(reloc_count):
            site, symbol_index, reloc_type = struct.unpack_from("<IIH", data, reloc_offset + i * 10)
            if symbol_index not in symbols_by_index:
                raise SystemExit(f"relocation refers to missing COFF symbol index {symbol_index}")
            section["relocations"].append({"site": site, "type": REL_TYPES.get(reloc_type, hex(reloc_type)),
                                           "symbol": symbols_by_index[symbol_index]})
    return headers, symbols_by_name


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--original-asi", type=Path, required=True)
    p.add_argument("--symbols", type=Path, required=True)
    p.add_argument("--payload-census", type=Path, required=True)
    p.add_argument("--placement-plan", type=Path, required=True)
    p.add_argument("--root-relocations", type=Path, required=True)
    p.add_argument("--bridge-layout", type=Path, required=True)
    p.add_argument("--extended-layout", type=Path, required=True)
    p.add_argument("--output", type=Path, required=True)
    a = p.parse_args()
    if file_digest(a.original_asi) != PINNED:
        raise SystemExit("pinned original ASI hash mismatch")
    symbols, census, placement, roots, bridge, extended = (read_json(x) for x in (
        a.symbols, a.payload_census, a.placement_plan, a.root_relocations, a.bridge_layout, a.extended_layout
    ))
    if file_digest(a.bridge_layout) != extended["inputs"]["appended_layout_sha256"]:
        raise SystemExit("bridge-layout hash does not match extended-layout evidence")
    if file_digest(a.payload_census) != bridge["payload_census_sha256"]:
        raise SystemExit("payload-census hash does not match bridge-layout evidence")
    objects = Path(symbols["inputs"]["objects"])
    root_entries = {int(row["entry_va"], 16): row for row in census["entries"]}

    existing: dict[tuple[int, int], dict] = {}
    for row in bridge["rdata_layout"]:
        existing[(int(row["source_entry"], 16), int(row["section_number"]))] = {
            **row, "section_name": ".rdata",
            "rva": int(extended["layout"]["appended_rdata_rva_after_code_extension"], 16),
        }
    for row in bridge["local_xcode_layout"]:
        existing[(int(row["source_entry"], 16), int(row["section_number"]))] = {
            **row, "section_name": ".xcode", "rva": int(extended["layout"]["appended_code_rva"], 16)
        }
    for row in bridge["data_local_layout"]:
        existing[(int(row["source_entry"], 16), int(row["section_number"]))] = {
            **row, "section_name": row["section_name"],
            "rva": int(extended["layout"]["appended_data_rva_after_rdata_extension"], 16),
        }
    for row in extended["local_section_layout"]:
        existing[(int(row["source_entry_va"], 16), int(row["section_number"]))] = row

    cross_rows = [row for row in roots["relocations"] if row["target_class"] == "defined-by-other-candidate-object"]
    requested: dict[tuple[int, int], dict] = {}
    definition_sections: dict[tuple[int, str], int] = {}
    for row in cross_rows:
        definitions = row.get("candidate_object_definitions") or []
        if len(definitions) != 1:
            raise SystemExit(f"ambiguous cross-object definition: {row}")
        definition = definitions[0]
        owner = int(definition["entry"], 16)
        obj = objects / f"{owner:08X}.obj"
        if not obj.is_file():
            raise SystemExit(f"cross-object target file missing: {obj}")
        obj_hash = file_digest(obj)
        owner_info = root_entries.get(owner)
        if owner_info and obj_hash != owner_info["object_sha256"]:
            raise SystemExit(f"cross-object target hash mismatch: {obj}")
        headers, names = coff(obj)
        matches = [s for s in names.get(row["target_symbol"], [])
                   if s["section_number"] > 0 and s["section_number"] <= len(headers)]
        if len(matches) != 1:
            raise SystemExit(f"target symbol is missing/ambiguous in {obj}: {row['target_symbol']}")
        symbol = matches[0]
        target_section = headers[symbol["section_number"] - 1]
        if (target_section["name"], symbol["value"]) != (definition["section"], int(definition["value"])):
            raise SystemExit(f"cross-object definition disagrees with COFF: {row['target_symbol']}")
        key = (owner, symbol["section_number"])
        definition_sections[(owner, row["target_symbol"])] = symbol["section_number"]
        if key not in existing:
            requested[key] = {"owner": owner, "number": symbol["section_number"],
                              "symbol": row["target_symbol"], "object": obj,
                              "object_sha256": obj_hash, "section": target_section}

    image_base = int(pefile.PE(str(a.original_asi)).OPTIONAL_HEADER.ImageBase)
    section_alignment = int(pefile.PE(str(a.original_asi)).OPTIONAL_HEADER.SectionAlignment)
    code_rva = int(extended["layout"]["appended_code_rva"], 16)
    code_cursor = int(extended["layout"]["extended_code_virtual_size"])
    roots_by_owner = root_entries
    placements = {int(row["address"], 16): row for row in placement["entries"]}
    appended_sections = []
    section_targets = dict(existing)
    for key, requested_section in sorted(requested.items()):
        section = requested_section["section"]
        if section["name"] != ".xcode":
            raise SystemExit(f"unplaced cross-object target is not executable: {key} {section['name']}")
        flags = section["flags"]
        align_code = (flags >> 20) & 0xF
        alignment = 1 << (align_code - 1) if align_code else 1
        code_cursor = (code_cursor + alignment - 1) & ~(alignment - 1)
        payload_offset = code_cursor
        code_cursor += section["size"]
        placed = {
            "source_entry": hex(key[0]), "section_number": key[1], "section_name": ".xcode",
            "size": section["size"], "alignment": alignment, "payload_offset": payload_offset,
            "preferred_va": hex(image_base + code_rva + payload_offset),
            "object_sha256": requested_section["object_sha256"],
            "section_sha256": digest(section["bytes"]), "relocation_count": section["reloc_count"],
        }
        section_targets[key] = {**placed, "rva": code_rva}
        appended_sections.append({**placed, "bytes_hex": section["bytes"].hex(" ")})

    # Every new helper section relocation must resolve to an already placed
    # section or to the candidate's actual appended root body.
    helper_fixups = []
    for placed in appended_sections:
        owner = int(placed["source_entry"], 16)
        obj = objects / f"{owner:08X}.obj"
        headers, names = coff(obj)
        source = headers[placed["section_number"] - 1]
        for reloc in source["relocations"]:
            kind = reloc["type"]
            if kind not in {"DIR32", "REL32"}:
                raise SystemExit(f"unsupported cross-object helper relocation {kind}")
            target_symbol = reloc["symbol"]
            target_owner = owner
            if target_symbol["section_number"] > 0:
                target_section_number = target_symbol["section_number"]
                target = section_targets.get((owner, target_section_number))
                if target is None:
                    root = roots_by_owner.get(owner)
                    placement_row = placements.get(owner)
                    expected_symbol = root["symbol"] if root else (placement_row or {}).get("entry_symbol")
                    if expected_symbol is None or target_symbol["name"] != expected_symbol:
                        raise SystemExit(f"helper dependency section missing: {owner:#x} {target_symbol}")
                    if root:
                        target_rva = code_rva + int(root["provisional_payload_offset"]) + target_symbol["value"]
                        target_identity = "appended-root-body"
                    elif placement_row["placement_mode"] == "body-at-entry":
                        target_rva = owner - image_base + target_symbol["value"]
                        target_identity = "inplace-root-body"
                    else:
                        raise SystemExit(f"thunked candidate root missing from appended payload census: {owner:#x}")
                else:
                    target_rva = int(target["rva"]) + int(target["payload_offset"]) + target_symbol["value"]
                    target_identity = "placed-local-section"
            else:
                raise SystemExit(f"cross-object helper has unresolved external: {owner:#x} {target_symbol['name']}")
            site = int(reloc["site"])
            addend = int.from_bytes(source["bytes"][site:site + 4], "little", signed=kind == "REL32")
            source_rva = code_rva + int(placed["payload_offset"])
            if kind == "REL32":
                value = image_base + target_rva + addend - (image_base + source_rva + site + 4)
                if not -(1 << 31) <= value < (1 << 31):
                    raise SystemExit(f"cross-object helper REL32 out of range: {owner:#x}+{site:#x}")
            else:
                value = image_base + target_rva + addend
                if not 0 <= value <= 0xFFFFFFFF:
                    raise SystemExit(f"cross-object helper DIR32 overflow: {owner:#x}+{site:#x}")
            helper_fixups.append({
                "source_entry": hex(owner), "source_section_number": placed["section_number"],
                "site": site, "type": kind, "target_symbol": target_symbol["name"],
                "target_va": hex(image_base + target_rva), "target_identity": target_identity,
                "raw_addend": addend, "computed_field_value": hex(value & 0xFFFFFFFF),
                "rel32_fits_signed_range": kind != "REL32" or -(1 << 31) <= value < (1 << 31),
            })

    root_target_rows = []
    for row in cross_rows:
        definition = row["candidate_object_definitions"][0]
        owner, number = int(definition["entry"], 16), None
        target_number = definition_sections[(owner, row["target_symbol"])]
        matches = [(owner, target_number)] if (owner, target_number) in section_targets else []
        # Cross-object .xcode definitions are symbol-resolved above; .bss is
        # already represented in the appended writable-data layout.
        if len(matches) != 1:
            raise SystemExit(f"cross-object target placement is missing/ambiguous: {definition} {matches}")
        target = section_targets[matches[0]]
        target_va = image_base + int(target.get("rva", extended["layout"]["appended_data_rva_after_rdata_extension"])) + int(target["payload_offset"]) + int(definition["value"])
        root_target_rows.append({
            "source_entry": row["source_entry"], "site": row["site"], "type": row["type"],
            "symbol": row["target_symbol"], "target_section_owner": hex(owner),
            "target_section_number": matches[0][1], "target_va": hex(target_va),
            "placement": target["preferred_va"] if "preferred_va" in target else hex(target_va),
        })

    end_rva = code_rva + code_cursor
    new_rdata_rva = (end_rva + section_alignment - 1) & ~(section_alignment - 1)
    old_rdata_rva = int(extended["layout"]["appended_rdata_rva_after_code_extension"], 16)
    if new_rdata_rva != old_rdata_rva:
        raise SystemExit("cross-object helpers move the already audited .rdata RVA; full layout must be recomputed")
    output = {
        "scope": "COFF-backed placement of cross-object local code sections needed by appended roots.",
        "inputs": {
            "original_asi_sha256": PINNED,
            "root_relocations_sha256": file_digest(a.root_relocations),
            "bridge_layout_sha256": file_digest(a.bridge_layout),
            "extended_layout_sha256": file_digest(a.extended_layout),
        },
        "summary": {
            "cross_object_references": len(cross_rows),
            "unique_target_sections": len(requested),
            "new_xcode_sections": len(appended_sections),
            "new_xcode_bytes": sum(row["size"] for row in appended_sections),
            "helper_section_relocations": len(helper_fixups),
            "helper_rel32_all_in_range": all(row["rel32_fits_signed_range"] for row in helper_fixups),
            "extended_code_virtual_size": code_cursor,
            "estimated_code_raw_size": (code_cursor + int(pefile.PE(str(a.original_asi)).OPTIONAL_HEADER.FileAlignment) - 1) & ~(int(pefile.PE(str(a.original_asi)).OPTIONAL_HEADER.FileAlignment) - 1),
            "appended_rdata_rva_unchanged": new_rdata_rva == old_rdata_rva,
        },
        "new_xcode_sections": appended_sections,
        "helper_fixups": helper_fixups,
        "cross_object_target_callsites": root_target_rows,
        "limitations": ["This only resolves the 29 cross-object candidate section references and their local helper edges.",
                        "It does not write fields, patch/emit a PE, or validate loader/game behavior."],
    }
    a.output.parent.mkdir(parents=True, exist_ok=True)
    a.output.write_text(json.dumps(output, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(output["summary"], indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
