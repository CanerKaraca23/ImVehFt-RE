#!/usr/bin/env python3
"""Plan RVAs/fixups for local sections referenced by current in-place bodies.

The output is an unapplied extension of the current three-section append plan.
It validates COFF bytes, computes all direct-body-to-local-section and local
closure relocations, and reports the resulting HIGHLOW directory size. It
does not emit or patch a PE; the appended .rdata/.data RVAs shift, so all
existing references to those sections must be regenerated before image build.
"""

from __future__ import annotations

import argparse
import collections
import hashlib
import json
from pathlib import Path

import pefile


PINNED_ASI_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"


def read_json(path: Path) -> dict:
    return json.loads(path.read_text(encoding="utf-8"))


def digest(path: Path) -> str:
    h = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            h.update(block)
    return h.hexdigest().upper()


def align(value: int, boundary: int) -> int:
    return (value + boundary - 1) & ~(boundary - 1)


def raw_addend(relocation: dict) -> int:
    raw = bytes(int(part, 16) for part in relocation["raw_field_bytes"].split())
    if len(raw) != 4:
        raise ValueError(f"expected 4-byte COFF addend: {relocation}")
    return int.from_bytes(raw, "little", signed=relocation["type"] == "REL32")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--original-asi", type=Path, required=True)
    ap.add_argument("--symbols", type=Path, required=True)
    ap.add_argument("--placement-plan", type=Path, required=True)
    ap.add_argument("--closure", type=Path, required=True)
    ap.add_argument("--closure-targets", type=Path, required=True)
    ap.add_argument("--direct-targets", type=Path, required=True)
    ap.add_argument("--appended-layout", type=Path, required=True)
    ap.add_argument("--appended-census", type=Path, required=True)
    ap.add_argument("--base-relocations", type=Path, required=True)
    ap.add_argument("--base-reloc-directory-bin", type=Path, required=True)
    ap.add_argument("--output", type=Path, required=True)
    args = ap.parse_args()

    original_hash = digest(args.original_asi)
    if original_hash != PINNED_ASI_SHA256:
        raise SystemExit(f"pinned ASI hash mismatch: {original_hash}")
    symbol_report = read_json(args.symbols)
    placement_plan = read_json(args.placement_plan)
    closure = read_json(args.closure)
    closure_targets = read_json(args.closure_targets)
    direct_targets = read_json(args.direct_targets)
    appended = read_json(args.appended_layout)
    census = read_json(args.appended_census)
    base_relocs = read_json(args.base_relocations)
    pe = pefile.PE(str(args.original_asi), fast_load=False)
    image_base = int(pe.OPTIONAL_HEADER.ImageBase)
    section_alignment = int(pe.OPTIONAL_HEADER.SectionAlignment)
    file_alignment = int(pe.OPTIONAL_HEADER.FileAlignment)
    object_dir = Path(closure["objects_directory"])

    # Validate the pinned prerequisite layout and its fixed inputs.
    if appended["original_asi_sha256"] != original_hash:
        raise SystemExit("appended layout was produced from a different original ASI")
    if census["objects_directory"] != closure["objects_directory"]:
        raise SystemExit("closure and appended census use different candidate objects")
    existing_reloc_blob = args.base_reloc_directory_bin.read_bytes()
    if len(existing_reloc_blob) != int(base_relocs["encoded_directory_bytes"]):
        raise SystemExit("serialized base relocation blob length mismatch")
    if hashlib.sha256(existing_reloc_blob).hexdigest().upper() != base_relocs["encoded_directory_sha256"]:
        raise SystemExit("serialized base relocation blob hash mismatch")
    existing_sites: set[int] = set()
    cursor = 0
    while cursor < len(existing_reloc_blob):
        if cursor + 8 > len(existing_reloc_blob):
            raise SystemExit("truncated existing base relocation block")
        page = int.from_bytes(existing_reloc_blob[cursor:cursor + 4], "little")
        block_size = int.from_bytes(existing_reloc_blob[cursor + 4:cursor + 8], "little")
        if block_size < 8 or cursor + block_size > len(existing_reloc_blob):
            raise SystemExit("invalid existing base relocation block size")
        for offset in range(cursor + 8, cursor + block_size, 2):
            entry = int.from_bytes(existing_reloc_blob[offset:offset + 2], "little")
            if entry >> 12 == 3:
                existing_sites.add(page + (entry & 0xFFF))
        cursor += block_size
    if len(existing_sites) != int(base_relocs["final_highlow_sites"]):
        raise SystemExit("serialized base relocation site count mismatch")

    placements = {int(row["address"], 16): row for row in placement_plan["entries"]}
    direct_entries = {
        va: row for va, row in placements.items()
        if row["placement_mode"] == "body-at-entry"
    }
    expected_direct = int(placement_plan.get("whole_bodies_fit_bounded_entry_gaps", -1))
    if len(direct_entries) != expected_direct:
        raise SystemExit(f"direct-body plan/count mismatch: {len(direct_entries)} != {expected_direct}")

    # Read and hash-verify every referenced local section from its authoritative
    # candidate object before assigning any layout address.
    section_rows = closure["sections"]
    section_by_key: dict[tuple[int, int], dict] = {}
    object_hashes: dict[int, str] = {}
    for row in section_rows:
        owner = int(row["source_entry_va"], 16)
        number = int(row["section_number"])
        key = (owner, number)
        if key in section_by_key:
            raise SystemExit(f"duplicate local section identity: {key}")
        obj_path = object_dir / f"{owner:08X}.obj"
        actual_obj_hash = digest(obj_path)
        if actual_obj_hash != row["object_sha256"]:
            raise SystemExit(f"candidate object hash mismatch: {obj_path}")
        object_hashes[owner] = actual_obj_hash
        contents = obj_path.read_bytes()
        size = int(row["section_bytes"])
        raw_start = int(row["section_raw_pointer"])
        if raw_start < 0 or raw_start + size > len(contents):
            raise SystemExit(f"section raw range outside object: {key}")
        raw = contents[raw_start:raw_start + size]
        if hashlib.sha256(raw).hexdigest().upper() != row["section_sha256"]:
            raise SystemExit(f"section bytes hash mismatch: {key}")
        flags = int(row["section_flags"], 16)
        alignment_code = (flags >> 20) & 0xF
        alignment = 1 << (alignment_code - 1) if alignment_code else 1
        if row["section_name"] not in {".xcode", ".rdata"}:
            raise SystemExit(f"unexpected direct closure section {row['section_name']}")
        section_by_key[key] = {
            **row,
            "owner": owner,
            "number": number,
            "size": size,
            "alignment": alignment,
        }

    # Extend the existing executable payload only after all its current bytes,
    # including the existing API thunks and original-helper bridge. The direct
    # bodies also contain imports not present in the 21-thunk appended-root
    # plan, so add one absolute-IAT jump stub per additional original IAT slot.
    code_base_rva = int(appended["provisional_appended_rva"], 16)
    code_tail = int(appended["bridge_payload_offset"]) + int(appended["bridge_payload_bytes"])
    if int(appended["bridge_payload_offset"]) < int(appended["code_bytes_before_bridge_alignment"]):
        raise SystemExit("bridge/code-tail size mismatch")
    direct_iat_rows = [
        row for row in direct_targets["rows"]
        if row["classification"] == "exact-import-name-and-dll-to-original-iat"
    ]
    iat_by_va: dict[int, dict] = {}
    for row in direct_iat_rows:
        iat_va = int(row["target"]["iat_va"], 16)
        descriptor = {
            "iat_va": iat_va,
            "dll": row["target"]["dll"],
            "api_name": row["target"]["api_name"],
        }
        prior = iat_by_va.setdefault(iat_va, descriptor)
        if prior != descriptor:
            raise SystemExit(f"conflicting direct-IAT identity for {iat_va:#x}")
    if len(iat_by_va) > len(direct_iat_rows):
        raise SystemExit("direct IAT slot count exceeds its callsite count")
    api_thunks = sorted(iat_by_va.values(), key=lambda row: row["iat_va"])
    api_thunk_base = code_tail
    direct_api_thunk_by_iat = {
        row["iat_va"]: api_thunk_base + index * 6
        for index, row in enumerate(api_thunks)
    }
    code_cursor = code_tail + 6 * len(api_thunks)
    for key in sorted(k for k, v in section_by_key.items() if v["section_name"] == ".xcode"):
        section = section_by_key[key]
        code_cursor = align(code_cursor, section["alignment"])
        section["payload_offset"] = code_cursor
        section["preferred_va"] = hex(image_base + code_base_rva + code_cursor)
        code_cursor += section["size"]
    code_virtual_size = code_cursor

    # Keep the root .rdata map intact and append the current in-place-root
    # local data sections after it, respecting COFF alignment.
    base_rdata_cursor = int(appended["rdata_payload_bytes_before_file_alignment"])
    base_rdata_rva = align(code_base_rva + code_virtual_size, section_alignment)
    rdata_cursor = base_rdata_cursor
    for key in sorted(k for k, v in section_by_key.items() if v["section_name"] == ".rdata"):
        section = section_by_key[key]
        rdata_cursor = align(rdata_cursor, section["alignment"])
        section["payload_offset"] = rdata_cursor
        section["preferred_va"] = hex(image_base + base_rdata_rva + rdata_cursor)
        rdata_cursor += section["size"]
    rdata_virtual_size = rdata_cursor

    data_rva = align(base_rdata_rva + rdata_virtual_size, section_alignment)
    data_virtual_size = int(appended["data_payload_virtual_bytes"])
    image_size_after = align(data_rva + data_virtual_size, section_alignment)
    code_raw_offset = int(census["provisional_appended_raw_offset"], 16)
    if args.original_asi.stat().st_size != code_raw_offset:
        raise SystemExit("original file EOF does not match the appended-layout raw offset")
    code_raw_size = align(code_virtual_size, file_alignment)
    rdata_raw_offset = code_raw_offset + code_raw_size
    rdata_raw_size = align(rdata_virtual_size, file_alignment)
    data_raw_offset = rdata_raw_offset + rdata_raw_size
    data_raw_size = align(data_virtual_size, file_alignment)
    appended_file_end = data_raw_offset + data_raw_size

    # Look up every undefined external by owner, decorated symbol and fixup
    # type. These rows contain preferred-base addresses, not diagnostic VAs.
    external_targets: dict[tuple[int, str, str], set[int]] = collections.defaultdict(set)
    for item in closure_targets["resolved_targets"]:
        external_targets[(
            int(item["source_entry_va"], 16), item["symbol"], item["relocation_type"]
        )].add(int(item["target_va"], 16))

    fixups: list[dict] = []

    def record_fixup(owner: int, section_key: tuple[int, int] | None,
                     source_rva: int, source_va: int, site: int, kind: str,
                     symbol: str, target_va: int, addend: int,
                     origin: str) -> None:
        if kind == "REL32":
            value = target_va + addend - (source_va + site + 4)
            if not -(1 << 31) <= value < (1 << 31):
                raise SystemExit(f"REL32 out of range: {owner:#x} {symbol} {value}")
            result_value = value
        elif kind == "DIR32":
            value = target_va + addend
            if not 0 <= value <= 0xFFFFFFFF:
                raise SystemExit(f"DIR32 out of range: {owner:#x} {symbol} {value:#x}")
            result_value = value
        else:
            raise SystemExit(f"unsupported COFF relocation type: {kind}")
        fixups.append({
            "origin": origin,
            "owner_entry_va": hex(owner),
            "source_section": (
                {"section_number": section_key[1],
                 "section_name": section_by_key[section_key]["section_name"]}
                if section_key else {"section_name": ".text"}
            ),
            "site_offset": site,
            "site_rva": hex(source_rva + site),
            "relocation_type": kind,
            "symbol": symbol,
            "target_va": hex(target_va),
            "raw_addend": addend,
            "computed_field_value": result_value,
            "computed_signed_rel32_fits": kind != "REL32" or -(1 << 31) <= result_value < (1 << 31),
        })

    # Route all exact original-IAT direct callsites to their local FF 25 stubs.
    # Each stub embeds its original IAT VA and therefore contributes one new
    # HIGHLOW relocation at the immediate operand (stub+2).
    functions_by_entry = {
        int(function["entry_va"], 16): function
        for function in symbol_report["functions"]
    }
    direct_api_call_fixups = 0
    for row in direct_iat_rows:
        if row["relocation_type"] != "REL32":
            raise SystemExit("direct IAT callsite is not represented by REL32")
        owner = int(row["owner_entry_va"], 16)
        iat_va = int(row["target"]["iat_va"], 16)
        function = functions_by_entry.get(owner)
        if function is None:
            raise SystemExit(f"direct IAT owner is absent from symbol report: {owner:#x}")
        matching_relocs = [
            reloc for reloc in function["relocations"]
            if int(reloc["offset"]) == int(row["field_offset"])
            and reloc["type"] == row["relocation_type"]
            and reloc["symbol"] == row["symbol"]
        ]
        if len(matching_relocs) != 1:
            raise SystemExit(
                f"direct IAT target row did not uniquely join to its COFF relocation: "
                f"{owner:#x}+{row['field_offset']:#x} {row['symbol']}"
            )
        addend = int(matching_relocs[0]["raw_addend"], 16)
        thunk_rva = code_base_rva + direct_api_thunk_by_iat[iat_va]
        record_fixup(
            owner, None, owner - image_base, owner,
            int(row["field_offset"]), "REL32", row["symbol"],
            image_base + thunk_rva, addend, "direct-body-to-added-original-IAT-thunk",
        )
        direct_api_call_fixups += 1

    # The 155 relocations in the 82-section recursive local closure.
    closure_relocation_count = 0
    for source_key, section in section_by_key.items():
        is_code = section["section_name"] == ".xcode"
        section_rva = (code_base_rva + int(section["payload_offset"])) if is_code else (
            base_rdata_rva + int(section["payload_offset"])
        )
        for reloc in section["relocations"]:
            closure_relocation_count += 1
            if reloc["target_class"] == "same-object-section":
                target_key = (section["owner"], int(reloc["target_section_number"]))
                if target_key not in section_by_key:
                    raise SystemExit(f"missing same-object section target: {target_key}")
                target_section = section_by_key[target_key]
                target_rva = (
                    code_base_rva + int(target_section["payload_offset"])
                    if target_section["section_name"] == ".xcode"
                    else base_rdata_rva + int(target_section["payload_offset"])
                )
                target_va = image_base + target_rva + int(reloc["target_value"])
            elif reloc["target_class"] == "undefined-external":
                matches = external_targets.get((section["owner"], reloc["target_symbol"], reloc["type"]), set())
                if len(matches) != 1:
                    raise SystemExit(
                        f"external target not unique for {section['source_entry_va']} "
                        f"{reloc['target_symbol']} {reloc['type']}: {matches}"
                    )
                target_va = next(iter(matches))
            else:
                raise SystemExit(f"unknown closure target class: {reloc['target_class']}")
            record_fixup(
                section["owner"], source_key, section_rva,
                image_base + section_rva, int(reloc["site"]), reloc["type"],
                reloc["target_symbol"], target_va, raw_addend(reloc),
                "same-object-local-section-closure",
            )

    # Also lay out the 62 direct .text-to-own-.rdata/.xcode section references.
    direct_body_section_refs = 0
    pending_direct_targets = {
        (int(row["owner_entry_va"], 16), int(row["field_offset"])): row
        for row in direct_targets["rows"]
        if row["classification"] == "known-same-object-code-symbol-awaiting-section-placement"
    }
    resolved_pending_direct_targets: list[dict] = []
    for function in symbol_report["functions"]:
        owner = int(function["entry_va"], 16)
        if owner not in direct_entries:
            continue
        for reloc in function["relocations"]:
            if not reloc["symbol_defined_in_object"] or reloc.get("symbol_section") not in {".rdata", ".xcode"}:
                continue
            if reloc["target_class"] == "local_symbol_in_candidate_body":
                continue
            target_key = (owner, int(reloc["symbol_section_number"]))
            if target_key not in section_by_key:
                raise SystemExit(f"direct body target section missing from closure: {target_key}")
            target_section = section_by_key[target_key]
            target_rva = (
                code_base_rva + int(target_section["payload_offset"])
                if target_section["section_name"] == ".xcode"
                else base_rdata_rva + int(target_section["payload_offset"])
            )
            target_va = image_base + target_rva + int(reloc["symbol_value"])
            field_offset = int(reloc["offset"])
            pending = pending_direct_targets.get((owner, field_offset))
            if pending:
                if pending["symbol"] != reloc["symbol"]:
                    raise SystemExit("pending direct target symbol disagrees with COFF relocation")
                resolved_pending_direct_targets.append({
                    "owner_entry_va": function["entry_va"],
                    "field_offset": field_offset,
                    "symbol": reloc["symbol"],
                    "provisional_target_va": hex(target_va),
                    "source_section_number": int(reloc["symbol_section_number"]),
                })
            record_fixup(
                owner, None, owner - image_base, owner, field_offset,
                reloc["type"], reloc["symbol"], target_va,
                int(reloc["raw_addend"], 16), "direct-body-to-local-section",
            )
            direct_body_section_refs += 1

    if closure_relocation_count != 155:
        raise SystemExit(f"expected 155 closure relocations, found {closure_relocation_count}")
    if direct_body_section_refs != 62:
        raise SystemExit(f"expected 62 direct body-to-local-section refs, found {direct_body_section_refs}")
    if len(resolved_pending_direct_targets) != len(pending_direct_targets):
        raise SystemExit(
            f"only {len(resolved_pending_direct_targets)}/{len(pending_direct_targets)} "
            "previously pending direct targets joined to local-section layout"
        )

    # Candidate body DIR32 sites are already present. Add the 113 local-closure
    # sites and each new FF 25 thunk's absolute IAT operand exactly once.
    highlow_sites = sorted(
        int(row["site_rva"], 16) for row in fixups
        if row["origin"] == "same-object-local-section-closure"
        and row["relocation_type"] == "DIR32"
    )
    if len(highlow_sites) != 113 or len(set(highlow_sites)) != 113:
        raise SystemExit(f"expected 113 unique new closure HIGHLOW sites, found {len(highlow_sites)}")
    base_sites = existing_sites
    if set(highlow_sites) & base_sites:
        raise SystemExit("new closure HIGHLOW sites overlap existing table")
    direct_body_dir32_sites = {
        int(row["site_rva"], 16) for row in fixups
        if row["origin"] == "direct-body-to-local-section"
        and row["relocation_type"] == "DIR32"
    }
    if not direct_body_dir32_sites <= base_sites:
        raise SystemExit("direct-body local-section DIR32 sites missing from existing relocation table")

    # Serialize the prospective expanded HIGHLOW table and confirm the pinned
    # original .reloc raw capacity is still sufficient.
    direct_api_thunk_highlow_sites = {
        code_base_rva + payload_offset + 2
        for payload_offset in direct_api_thunk_by_iat.values()
    }
    if len(direct_api_thunk_highlow_sites) != len(api_thunks):
        raise SystemExit("direct API thunk HIGHLOW sites are not unique")
    if direct_api_thunk_highlow_sites & base_sites or direct_api_thunk_highlow_sites & set(highlow_sites):
        raise SystemExit("direct API thunk HIGHLOW site overlaps another relocation")
    all_new_highlow_sites = set(highlow_sites) | direct_api_thunk_highlow_sites
    all_sites = sorted(base_sites | all_new_highlow_sites)
    by_page: dict[int, list[int]] = collections.defaultdict(list)
    for rva in all_sites:
        by_page[rva & ~0xFFF].append(rva & 0xFFF)
    blob = bytearray()
    for page, offsets in sorted(by_page.items()):
        entries = [(3 << 12) | offset for offset in offsets]
        if len(entries) & 1:
            entries.append(0)
        block_size = 8 + 2 * len(entries)
        blob.extend(page.to_bytes(4, "little"))
        blob.extend(block_size.to_bytes(4, "little"))
        for entry in entries:
            blob.extend(entry.to_bytes(2, "little"))
    roundtrip_sites: set[int] = set()
    cursor = 0
    while cursor < len(blob):
        page = int.from_bytes(blob[cursor:cursor + 4], "little")
        block_size = int.from_bytes(blob[cursor + 4:cursor + 8], "little")
        if block_size < 8 or cursor + block_size > len(blob):
            raise SystemExit("expanded relocation directory failed block roundtrip")
        for offset in range(cursor + 8, cursor + block_size, 2):
            entry = int.from_bytes(blob[offset:offset + 2], "little")
            if entry >> 12 == 3:
                roundtrip_sites.add(page + (entry & 0xFFF))
        cursor += block_size
    if roundtrip_sites != set(all_sites):
        raise SystemExit("expanded relocation directory site roundtrip mismatch")
    reloc_section_raw = int(base_relocs["original_reloc_section_raw_size"])
    if len(blob) > reloc_section_raw:
        raise SystemExit(f"expanded relocation directory exceeds original .reloc: {len(blob)} > {reloc_section_raw}")

    counts = collections.Counter((row["origin"], row["relocation_type"]) for row in fixups)
    output = {
        "scope": (
            f"Provisional extension of the {sum(row['placement_mode'] == 'jmp-rel32-thunk' for row in placements.values())}-root three-section append model with "
            f"all local sections referenced by the {len(direct_entries)} direct bodies. This calculates "
            "their final-within-this-model RVAs and COFF fields but does not apply them."
        ),
        "inputs": {
            "original_asi_sha256": original_hash,
            "symbols_sha256": digest(args.symbols),
            "placement_plan_sha256": digest(args.placement_plan),
            "direct_closure_sha256": digest(args.closure),
            "closure_targets_sha256": digest(args.closure_targets),
            "direct_target_report_sha256": digest(args.direct_targets),
            "appended_layout_sha256": digest(args.appended_layout),
            "base_relocation_report_sha256": digest(args.base_relocations),
            "base_relocation_blob_sha256": digest(args.base_reloc_directory_bin),
            "candidate_objects_verified": len(object_hashes),
        },
        "summary": {
            "direct_body_count": len(direct_entries),
            "local_closure_sections": len(section_by_key),
            "local_xcode_sections_added": sum(1 for s in section_by_key.values() if s["section_name"] == ".xcode"),
            "local_xcode_raw_bytes_added": sum(s["size"] for s in section_by_key.values() if s["section_name"] == ".xcode"),
            "local_rdata_sections_added": sum(1 for s in section_by_key.values() if s["section_name"] == ".rdata"),
            "local_rdata_raw_bytes_added": sum(s["size"] for s in section_by_key.values() if s["section_name"] == ".rdata"),
            "direct_body_to_local_section_fixups": direct_body_section_refs,
            "previously_pending_direct_code_targets_placed": len(resolved_pending_direct_targets),
            "local_closure_fixups": closure_relocation_count,
            "fixup_counts_by_origin_and_type": {
                f"{origin}:{kind}": count
                for (origin, kind), count in sorted(counts.items())
            },
            "all_rel32_fit_signed_range": all(
                row["relocation_type"] != "REL32" or row["computed_signed_rel32_fits"]
                for row in fixups
            ),
            "new_local_closure_highlow_sites": len(highlow_sites),
            "direct_import_callsite_count": direct_api_call_fixups,
            "direct_original_iat_thunk_count": len(api_thunks),
            "direct_original_iat_thunk_highlow_sites": len(direct_api_thunk_highlow_sites),
            "highlow_site_count_after_extension": len(all_sites),
            "relocation_blob_bytes_after_extension": len(blob),
            "original_reloc_section_raw_capacity": reloc_section_raw,
            "expanded_relocation_directory_fits": len(blob) <= reloc_section_raw,
        },
        "layout": {
            "image_base": hex(image_base),
            "section_alignment": hex(section_alignment),
            "file_alignment": hex(file_alignment),
            "appended_code_rva": hex(code_base_rva),
            "existing_code_payload_end_offset": code_tail,
            "direct_api_thunk_payload_offset": api_thunk_base,
            "direct_api_thunk_payload_bytes": 6 * len(api_thunks),
            "local_xcode_payload_start_offset": code_tail + 6 * len(api_thunks),
            "extended_code_virtual_size": code_virtual_size,
            "extended_code_raw_size": align(code_virtual_size, file_alignment),
            "appended_rdata_rva_after_code_extension": hex(base_rdata_rva),
            "extended_rdata_virtual_size": rdata_virtual_size,
            "extended_rdata_raw_size": align(rdata_virtual_size, file_alignment),
            "appended_data_rva_after_rdata_extension": hex(data_rva),
            "data_virtual_size": data_virtual_size,
            "estimated_size_of_image": hex(image_size_after),
            "appended_code_raw_offset": hex(code_raw_offset),
            "appended_code_raw_size": hex(code_raw_size),
            "appended_rdata_raw_offset": hex(rdata_raw_offset),
            "appended_rdata_raw_size": hex(rdata_raw_size),
            "appended_data_raw_offset": hex(data_raw_offset),
            "appended_data_raw_size": hex(data_raw_size),
            "estimated_file_end": hex(appended_file_end),
            "rdata_and_data_rvas_shifted_from_prior_plan": True,
        },
        "limitations": [
            "Existing relocations to the former appended .rdata/.data RVAs must be recomputed after these section shifts.",
            "No PE bytes or source functions are modified and no ASI is emitted.",
            "Target addresses classified only by GTA .text membership retain that identity/ABI limitation.",
            "This plan does not integrate installer/import/startup payloads or perform loader/game validation.",
        ],
        "new_highlow_site_rvas": [hex(site) for site in highlow_sites],
        "direct_api_thunks": [
            {
                "dll": row["dll"],
                "api_name": row["api_name"],
            "iat_va": hex(row["iat_va"]),
                "api_symbols": sorted({
                    call["symbol"] for call in direct_iat_rows
                    if int(call["target"]["iat_va"], 16) == row["iat_va"]
                }),
                "payload_offset": direct_api_thunk_by_iat[row["iat_va"]],
                "preferred_va_in_extended_model": hex(image_base + code_base_rva + direct_api_thunk_by_iat[row["iat_va"]]),
                "bytes_template": "FF 25 <absolute IAT VA>",
                "highlow_site_rva": hex(code_base_rva + direct_api_thunk_by_iat[row["iat_va"]] + 2),
            }
            for row in api_thunks
        ],
        "local_section_layout": [
            {
                "source_entry_va": row["source_entry_va"],
                "section_number": row["section_number"],
                "section_name": row["section_name"],
                "size": row["size"],
                "alignment": row["alignment"],
                "payload_offset": row["payload_offset"],
                "preferred_va_in_extended_model": row["preferred_va"],
                "object_sha256": row["object_sha256"],
                "section_sha256": row["section_sha256"],
            }
            for _, row in sorted(section_by_key.items())
        ],
        "previously_pending_direct_code_targets": resolved_pending_direct_targets,
        "fixups": fixups,
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(output, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(output["summary"], indent=2))
    print(json.dumps(output["layout"], indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
