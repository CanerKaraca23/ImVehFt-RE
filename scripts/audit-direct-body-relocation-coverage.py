#!/usr/bin/env python3
"""Join direct-body COFF relocation sites to the current fixup inventories.

This is a coverage audit only. It does not resolve or apply missing fields.
"""

from __future__ import annotations

import argparse
import collections
import csv
import hashlib
import json
import struct
from pathlib import Path

import pefile


RELOC_NAMES = {0x0006: "DIR32", 0x0014: "REL32", 0x000A: "SECTION", 0x000B: "SECREL"}


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def parse_entry_relocations(path: Path, entry_symbol: str) -> tuple[str, list[dict[str, object]]]:
    data = path.read_bytes()
    machine, section_count, _, symbol_offset, symbol_count, optional_size, _ = struct.unpack_from(
        "<HHIIIHH", data
    )
    if machine != 0x14C or optional_size != 0:
        raise ValueError(f"{path.name}: expected i386 COFF with no optional header")
    section_table = 20
    sections = [
        struct.unpack_from("<8sIIIIIIHHI", data, section_table + index * 40)
        for index in range(section_count)
    ]
    string_offset = symbol_offset + symbol_count * 18
    string_size = struct.unpack_from("<I", data, string_offset)[0]
    strings = data[string_offset : string_offset + string_size]
    symbols: list[tuple[str, int, int] | None] = [None] * symbol_count
    entry_section = None
    index = 0
    cursor = symbol_offset
    while index < symbol_count:
        entry = data[cursor : cursor + 18]
        raw_name = entry[:8]
        if raw_name[:4] == b"\0\0\0\0":
            name_offset = struct.unpack_from("<I", raw_name, 4)[0]
            end = strings.find(b"\0", name_offset)
            name = strings[name_offset:end].decode("utf-8", errors="replace")
        else:
            name = raw_name.split(b"\0", 1)[0].decode("utf-8", errors="replace")
        value, section_number, _, _, aux_count = struct.unpack_from("<IhHBB", entry, 8)
        symbols[index] = (name, value, section_number)
        if name == entry_symbol:
            entry_section = section_number
        index += 1 + aux_count
        cursor += (1 + aux_count) * 18
    if entry_section is None or not 1 <= entry_section <= section_count:
        raise ValueError(f"{path.name}: entry symbol not found in COFF symbol table")
    section = sections[entry_section - 1]
    if section[0].split(b"\0", 1)[0] != b".xcode" or section[3] == 0:
        raise ValueError(f"{path.name}: entry symbol does not define a nonempty .xcode section")
    relocations = []
    for reloc_index in range(section[7]):
        site, symbol_index, kind = struct.unpack_from("<IIH", data, section[5] + reloc_index * 10)
        target = symbols[symbol_index]
        if target is None:
            raise ValueError(f"{path.name}: relocation references an auxiliary COFF symbol")
        relocations.append({
            "site": site,
            "type": RELOC_NAMES.get(kind, f"0x{kind:04X}"),
            "target_symbol": target[0],
            "target_value": target[1],
            "target_section": target[2],
            "raw_addend": struct.unpack_from("<I", data, section[4] + site)[0],
        })
    return digest(data), relocations


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--repo", type=Path, required=True)
    parser.add_argument("--original-asi", type=Path, required=True)
    parser.add_argument("--objects", type=Path, required=True)
    parser.add_argument("--placement", type=Path, required=True)
    parser.add_argument("--raw-report", type=Path, required=True)
    parser.add_argument("--body-fixups", type=Path, required=True)
    parser.add_argument("--executable-targets", type=Path, required=True)
    parser.add_argument("--local-layout", type=Path, required=True)
    parser.add_argument("--api-plan", type=Path, required=True)
    parser.add_argument("--relocation-reconciliation", type=Path, required=True)
    parser.add_argument("--vftable-provider", type=Path, required=True)
    parser.add_argument("--vftable-crosswalk", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    repo = args.repo.resolve()
    placement = json.loads(args.placement.read_text(encoding="utf-8"))
    raw_report = json.loads(args.raw_report.read_text(encoding="utf-8"))
    body_fixups = json.loads(args.body_fixups.read_text(encoding="utf-8"))
    executable = json.loads(args.executable_targets.read_text(encoding="utf-8"))
    local_layout = json.loads(args.local_layout.read_text(encoding="utf-8"))
    api_plan = json.loads(args.api_plan.read_text(encoding="utf-8"))
    relocation_reconciliation = json.loads(args.relocation_reconciliation.read_text(encoding="utf-8"))
    vftable_provider = json.loads(args.vftable_provider.read_text(encoding="utf-8"))
    with args.vftable_crosswalk.open(encoding="utf-8-sig", newline="") as stream:
        vftable_crosswalk = {row["symbol"]: int(row["address"], 16) for row in csv.DictReader(stream)}
    candidates = {row["address"].lower(): row for row in placement["entries"]
                  if row["placement_mode"] == "body-at-entry"}
    authoritative = {row["entry_va"].lower(): row for row in raw_report["results"]}
    accounted = {
        (row["caller_entry_va"].lower(), int(row["field_offset"]))
        for row in body_fixups["fixups"]
    }
    accounted.update(
        (row["owner_entry_va"].lower(), int(row["field_offset"]))
        for row in executable["rows"]
    )
    accounted.update(
        (row["owner_entry_va"].lower(), int(row["site_offset"]))
        for row in local_layout["fixups"]
        if row["origin"].startswith("direct-body-")
    )

    sites = []
    object_hash_mismatches = []
    for entry, row in sorted(candidates.items()):
        object_path = args.objects / f"{int(entry, 16):08X}.obj"
        object_hash, relocations = parse_entry_relocations(object_path, row["entry_symbol"])
        expected = authoritative[entry]
        if object_hash != expected["object_sha256"]:
            object_hash_mismatches.append(entry)
        if len(relocations) != int(expected["coff_relocation_count"]):
            raise ValueError(f"{entry}: relocation count disagrees with hash-pinned source inventory")
        for relocation in relocations:
            sites.append({"owner_entry_va": entry, **relocation})

    keys = [(row["owner_entry_va"], row["site"]) for row in sites]
    if len(keys) != len(set(keys)):
        raise ValueError("duplicate raw relocation site across direct bodies")
    missing = [row for row in sites if (row["owner_entry_va"], row["site"]) not in accounted]
    stale = sorted(accounted - set(keys))
    type_counts = collections.Counter(row["type"] for row in sites)
    missing_types = collections.Counter(row["type"] for row in missing)
    missing_symbols = collections.Counter(row["target_symbol"] for row in missing)
    image = pefile.PE(str(args.original_asi), fast_load=False)
    imported_slots = {}
    for descriptor in getattr(image, "DIRECTORY_ENTRY_IMPORT", []):
        dll = descriptor.dll.decode("ascii", errors="replace")
        for imported in descriptor.imports:
            if imported.name:
                imported_slots[imported.name.decode("ascii", errors="replace").lower()] = {
                    "dll": dll,
                    "iat_va": int(imported.address),
                }
    original_highlow_rvas = {
        int(block.struct.VirtualAddress) + int(item.rva)
        for block in getattr(image, "DIRECTORY_ENTRY_BASERELOC", [])
        for item in block.entries
        if int(item.type) == pefile.RELOCATION_TYPE['IMAGE_REL_BASED_HIGHLOW']
    }
    candidate_dir32_vas = {
        int(site, 16)
        for body in relocation_reconciliation["results"]
        for site in body["candidate_dir32_sites"]
    }
    raw_by_key = {(row["owner_entry_va"], int(row["site"])): row for row in sites}
    function_fixups = {
        (row["caller_entry_va"].lower(), int(row["field_offset"])): row
        for row in body_fixups["fixups"]
    }
    local_fixups = {
        (row["owner_entry_va"].lower(), int(row["site_offset"])): row
        for row in local_layout["fixups"]
        if row["origin"].startswith("direct-body-")
    }
    api_fixups = {}
    for row in api_plan["rel32_patches"]:
        if row["callsite_class"] != "in-place-body":
            continue
        owner = row["candidate_entry"].lower()
        offset = int(row["relocation_field_rva"], 16) - (int(row["candidate_entry"], 16) - int(image.OPTIONAL_HEADER.ImageBase))
        api_fixups[(owner, offset)] = row
    executable_value_checks = []
    executable_value_mismatches = []
    executable_target_source_counts: collections.Counter[str] = collections.Counter()
    body_fixup_raw_mismatches = []
    local_fixup_raw_mismatches = []
    for key, fixup in function_fixups.items():
        raw = raw_by_key.get(key)
        if raw is None or raw["type"] != fixup["relocation_type"] or int(fixup["raw_addend"], 16) != int(raw["raw_addend"]):
            body_fixup_raw_mismatches.append({"key": key, "reason": "function-symbol fixup type/raw addend differs from COFF"})
    for key, fixup in local_fixups.items():
        raw = raw_by_key.get(key)
        if raw is None or raw["type"] != fixup["relocation_type"] or int(fixup["raw_addend"]) != int(raw["raw_addend"]):
            local_fixup_raw_mismatches.append({"key": key, "reason": "local-layout fixup type/raw addend differs from COFF"})
    executable_target_map = {(row["owner_entry_va"].lower(), int(row["field_offset"])): row for row in executable["rows"]}
    for key, row in executable_target_map.items():
        raw = raw_by_key.get(key)
        if raw is None:
            executable_value_mismatches.append({"key": key, "reason": "raw COFF relocation site missing"})
            continue
        api = api_fixups.get(key)
        local = local_fixups.get(key)
        if api is not None:
            target_va = int(api["replacement_thunk_va"], 16)
            target_source = "verified-api-thunk-patch-plan"
            expected_rel32 = int(api["rel32_displacement"])
        elif local is not None:
            target_va = int(local["target_va"], 16)
            target_source = str(local["origin"])
            expected_rel32 = None
        else:
            evidence = row.get("target", {})
            target_text = evidence.get("preferred_va") or evidence.get("iat_va")
            if not target_text:
                executable_value_mismatches.append({"key": key, "reason": "no final target address in target evidence or placement plans"})
                continue
            target_va = int(target_text, 16)
            target_source = "Ghidra/original-image target evidence"
            expected_rel32 = None
        if row["relocation_type"] != raw["type"]:
            executable_value_mismatches.append({"key": key, "reason": "relocation type mismatch", "COFF": raw["type"], "target_report": row["relocation_type"]})
        if local is not None and local["relocation_type"] != raw["type"]:
            executable_value_mismatches.append({"key": key, "reason": "local-layout relocation type mismatch"})
        field_va = int(row["owner_entry_va"], 16) + int(row["field_offset"])
        addend = int(raw["raw_addend"])
        if raw["type"] == "REL32":
            value = target_va + addend - (field_va + 4)
            fits = -(1 << 31) <= value < (1 << 31)
            if not fits or (expected_rel32 is not None and value != expected_rel32):
                executable_value_mismatches.append({"key": key, "reason": "REL32 computation mismatch/out of range", "computed": value, "api_plan": expected_rel32})
        elif raw["type"] == "DIR32":
            value = target_va + addend
            fits = 0 <= value <= 0xFFFFFFFF
            if not fits:
                executable_value_mismatches.append({"key": key, "reason": "DIR32 computation overflow", "computed": value})
            if field_va not in candidate_dir32_vas:
                executable_value_mismatches.append({"key": key, "reason": "DIR32 site absent from candidate HIGHLOW manifest"})
        else:
            executable_value_mismatches.append({"key": key, "reason": "unsupported relocation type", "type": raw["type"]})
            value, fits = 0, False
        if local is not None:
            local_addend = int(local["raw_addend"])
            if local_addend != addend:
                executable_value_mismatches.append({"key": key, "reason": "raw addend differs from local-layout audit", "COFF": addend, "plan": local_addend})
            if raw["type"] == "REL32" and (int(local["computed_field_value"]) & 0xFFFFFFFF) != (value & 0xFFFFFFFF):
                executable_value_mismatches.append({"key": key, "reason": "computed displacement differs from local-layout audit"})
        executable_target_source_counts[target_source] += 1
        executable_value_checks.append({
            "owner_entry_va": row["owner_entry_va"],
            "field_offset": row["field_offset"],
            "relocation_type": raw["type"],
            "raw_addend": f"0x{addend:08X}",
            "target_va": f"0x{target_va:08X}",
            "target_source": target_source,
            "computed_field_value": f"0x{value & 0xFFFFFFFF:08X}",
            "rel32_in_signed_range_or_dir32_fits": fits,
        })
    resolved_iat = []
    resolved_vftables = []
    unresolved_external = []
    for row in missing:
        symbol = str(row["target_symbol"])
        if not symbol.startswith("__imp_"):
            if int(row["target_section"]) == 0:
                unresolved_external.append(row)
            continue
        decorated = symbol[len("__imp_") :]
        undecorated = decorated[1:] if decorated.startswith("_") else decorated
        api_name = undecorated.split("@", 1)[0].lower()
        target = imported_slots.get(api_name)
        if target is None:
            unresolved_external.append(row)
            continue
        field_va = int(row["owner_entry_va"], 16) + int(row["site"])
        field_rva = field_va - int(image.OPTIONAL_HEADER.ImageBase)
        resolved_iat.append({
            **row,
            "import_dll": target["dll"],
            "import_name": api_name,
            "preferred_iat_va": f"0x{target['iat_va']:08X}",
            "computed_preferred_value": f"0x{target['iat_va'] + int(row['raw_addend']):08X}",
            "raw_addend": f"0x{int(row['raw_addend']):08X}",
            "field_rva": f"0x{field_rva:08X}",
            "field_has_original_highlow": field_rva in original_highlow_rvas,
            "field_in_direct_body_candidate_dir32_manifest": field_va in candidate_dir32_vas,
        })
    section_ranges = {
        section.Name.rstrip(b"\0").decode("ascii", errors="replace"): (
            int(image.OPTIONAL_HEADER.ImageBase) + int(section.VirtualAddress),
            int(section.Misc_VirtualSize or section.SizeOfRawData),
        )
        for section in image.sections
    }
    for row in missing:
        symbol = str(row["target_symbol"])
        if symbol.startswith("__imp_"):
            continue
        if symbol not in vftable_crosswalk:
            if int(row["target_section"]) == 0:
                unresolved_external.append(row)
            continue
        field_va = int(row["owner_entry_va"], 16) + int(row["site"])
        field_rva = field_va - int(image.OPTIONAL_HEADER.ImageBase)
        target_va = vftable_crosswalk[symbol] + int(row["raw_addend"])
        rdata_va, rdata_size = section_ranges[".rdata"]
        resolved_vftables.append({
            **row,
            "preferred_vftable_va": f"0x{vftable_crosswalk[symbol]:08X}",
            "computed_preferred_value": f"0x{target_va:08X}",
            "raw_addend": f"0x{int(row['raw_addend']):08X}",
            "field_rva": f"0x{field_rva:08X}",
            "field_in_direct_body_candidate_dir32_manifest": field_va in candidate_dir32_vas,
            "target_within_original_rdata": rdata_va <= target_va < rdata_va + rdata_size,
        })
    if digest(args.original_asi.read_bytes()) != vftable_provider["image_sha256"].upper():
        raise ValueError("vftable address crosswalk is pinned to a different original ASI")
    if len(vftable_crosswalk) != int(vftable_provider["alias_count"]):
        raise ValueError("vftable crosswalk row count differs from its provider manifest")
    resolved_keys = {
        (row["owner_entry_va"], int(row["site"]))
        for row in [*resolved_iat, *resolved_vftables]
    }
    if resolved_keys & accounted:
        raise ValueError("a resolved external relocation unexpectedly overlaps an accounted site")
    final_unresolved = [row for row in missing if (row["owner_entry_va"], row["site"]) not in resolved_keys]
    report = {
        "scope": f"Exact site coverage join for relocations in the {len(candidates)} direct-body .xcode sections; no target values or PE bytes are written.",
        "inputs": {
            "pinned_original_asi_sha256": body_fixups["original_image_sha256"],
            "object_directory": body_fixups["objects_directory"],
            "raw_object_inventory": str(args.raw_report.resolve()),
            "body_fixup_inventory": str(args.body_fixups.resolve()),
            "executable_target_inventory": str(args.executable_targets.resolve()),
            "local_layout_inventory": str(args.local_layout.resolve()),
            "api_plan": str(args.api_plan.resolve()),
            "relocation_reconciliation": str(args.relocation_reconciliation.resolve()),
            "vftable_provider": str(args.vftable_provider.resolve()),
            "vftable_crosswalk": str(args.vftable_crosswalk.resolve()),
        },
        "counts": {
            "direct_body_count": len(candidates),
            "raw_relocation_sites": len(sites),
            "raw_relocations_by_type": dict(sorted(type_counts.items())),
            "accounted_unique_sites": len(accounted),
            "accounted_raw_sites": len(set(keys) & accounted),
            "uncovered_raw_sites": len(missing),
            "uncovered_by_type": dict(sorted(missing_types.items())),
            "unresolved_external_sites_after_exact_iat_join": len(unresolved_external),
            "unresolved_external_sites_after_iat_and_vftable_crosswalks": len(final_unresolved),
            "exact_original_iat_sites": len(resolved_iat),
            "exact_ghidra_vftable_sites": len(resolved_vftables),
            "vftable_targets_inside_original_rdata": sum(row["target_within_original_rdata"] for row in resolved_vftables),
            "exact_original_iat_sites_already_in_base_relocations": sum(row["field_has_original_highlow"] for row in resolved_iat),
            "exact_original_iat_sites_requiring_new_base_relocations": sum(not row["field_has_original_highlow"] for row in resolved_iat),
            "exact_original_iat_sites_in_direct_body_candidate_dir32_manifest": sum(row["field_in_direct_body_candidate_dir32_manifest"] for row in resolved_iat),
            "exact_original_iat_sites_missing_from_direct_body_candidate_dir32_manifest": sum(not row["field_in_direct_body_candidate_dir32_manifest"] for row in resolved_iat),
            "stale_accounted_sites": len(stale),
            "object_hash_mismatches": len(object_hash_mismatches),
            "function_fixup_type_or_addend_mismatches": len(body_fixup_raw_mismatches),
            "local_layout_type_or_addend_mismatches": len(local_fixup_raw_mismatches),
            "executable_target_fields_recomputed_from_raw_coff": len(executable_value_checks),
            "executable_target_value_mismatches": len(executable_value_mismatches),
        },
        "uncovered_target_symbol_counts": dict(missing_symbols.most_common()),
        "uncovered_sites": missing,
        "executable_target_value_checks": executable_value_checks,
        "executable_target_source_counts": dict(sorted(executable_target_source_counts.items())),
        "executable_target_value_mismatches": executable_value_mismatches,
        "function_fixup_raw_mismatches": body_fixup_raw_mismatches,
        "local_layout_raw_mismatches": local_fixup_raw_mismatches,
        "exact_original_iat_sites": resolved_iat,
        "exact_ghidra_vftable_sites": resolved_vftables,
        "unresolved_external_sites_after_crosswalks": final_unresolved,
        "stale_accounted_sites": stale,
        "object_hash_mismatch_entries": object_hash_mismatches,
        "all_source_hashes_match": not object_hash_mismatches,
        "all_raw_sites_accounted": (
            len(final_unresolved) == 0
            and not stale
            and len(accounted) + len(resolved_keys) == len(set(keys))
            and all(row["field_in_direct_body_candidate_dir32_manifest"] for row in resolved_iat)
            and all(row["field_in_direct_body_candidate_dir32_manifest"] and row["target_within_original_rdata"] for row in resolved_vftables)
        ),
        "all_executable_targets_recomputed_and_in_range": len(executable_value_checks) == len(executable["rows"]) and not executable_value_mismatches,
        "all_function_and_local_fixup_addends_match_raw_coff": not body_fixup_raw_mismatches and not local_fixup_raw_mismatches,
        "limitations": [
            "A covered relocation site is not proof that its target identity or initialization is correct.",
            "Exact import-name matching and Ghidra vftable crosswalks establish preferred-base targets only; they do not apply the resulting fixups.",
            "The candidate DIR32 manifest is a planned relocation inventory, not an emitted relocation directory.",
            "This is not a PE/ASI emitter and gives no loader or game validation.",
        ],
    }
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"output": str(args.output), **report["counts"],
                      "all_raw_sites_accounted": report["all_raw_sites_accounted"]}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
