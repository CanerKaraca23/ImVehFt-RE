#!/usr/bin/env python3
"""Verify appended-root raw COFF relocation coverage against the fixup plan."""

from __future__ import annotations

import argparse
import collections
import hashlib
import json
import struct
from pathlib import Path


RELOC_NAMES = {0x0006: "DIR32", 0x0014: "REL32", 0x000A: "SECTION", 0x000B: "SECREL"}


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def read_root_relocations(path: Path, entry_symbol: str) -> tuple[str, list[dict[str, object]]]:
    data = path.read_bytes()
    machine, section_count, _, symbol_offset, symbol_count, optional_size, _ = struct.unpack_from(
        "<HHIIIHH", data
    )
    if machine != 0x14C or optional_size != 0:
        raise ValueError(f"{path.name}: expected i386 COFF")
    sections = [
        struct.unpack_from("<8sIIIIIIHHI", data, 20 + index * 40)
        for index in range(section_count)
    ]
    strings_offset = symbol_offset + symbol_count * 18
    strings_size = struct.unpack_from("<I", data, strings_offset)[0]
    strings = data[strings_offset : strings_offset + strings_size]
    symbols: list[tuple[str, int, int] | None] = [None] * symbol_count
    entry_section = None
    index = 0
    cursor = symbol_offset
    while index < symbol_count:
        item = data[cursor : cursor + 18]
        raw_name = item[:8]
        if raw_name[:4] == b"\0\0\0\0":
            name_offset = struct.unpack_from("<I", raw_name, 4)[0]
            end = strings.find(b"\0", name_offset)
            name = strings[name_offset:end].decode("utf-8", errors="replace")
        else:
            name = raw_name.split(b"\0", 1)[0].decode("utf-8", errors="replace")
        value, section_number, _, _, aux_count = struct.unpack_from("<IhHBB", item, 8)
        symbols[index] = (name, value, section_number)
        if name == entry_symbol:
            entry_section = section_number
        index += 1 + aux_count
        cursor += (1 + aux_count) * 18
    if entry_section is None or not 1 <= entry_section <= section_count:
        raise ValueError(f"{path.name}: root entry symbol missing")
    section = sections[entry_section - 1]
    if section[0].split(b"\0", 1)[0] != b".xcode":
        raise ValueError(f"{path.name}: entry symbol is not in .xcode")
    relocations = []
    for reloc_index in range(section[7]):
        site, symbol_index, kind = struct.unpack_from("<IIH", data, section[5] + reloc_index * 10)
        target = symbols[symbol_index]
        if target is None:
            raise ValueError(f"{path.name}: relocation references an auxiliary symbol")
        relocations.append({
            "site": site,
            "type": RELOC_NAMES.get(kind, f"0x{kind:04X}"),
            "target_symbol": target[0],
            "raw_addend": struct.unpack_from("<I", data, section[4] + site)[0],
        })
    return sha256(data), relocations


def read_section_relocations(path: Path, section_number: int) -> tuple[str, str, str, list[dict[str, object]]]:
    data = path.read_bytes()
    machine, section_count, _, symbol_offset, symbol_count, optional_size, _ = struct.unpack_from(
        "<HHIIIHH", data
    )
    if machine != 0x14C or optional_size != 0 or not 1 <= section_number <= section_count:
        raise ValueError(f"{path.name}: invalid i386 COFF section identity {section_number}")
    sections = [
        struct.unpack_from("<8sIIIIIIHHI", data, 20 + index * 40)
        for index in range(section_count)
    ]
    section = sections[section_number - 1]
    section_name = section[0].split(b"\0", 1)[0].decode("ascii", errors="replace")
    section_bytes = data[section[4] : section[4] + section[3]]
    section_hash = sha256(bytes(section[3])) if section_name == ".bss" and section[4] == 0 else sha256(section_bytes)
    strings_offset = symbol_offset + symbol_count * 18
    strings_size = struct.unpack_from("<I", data, strings_offset)[0]
    strings = data[strings_offset : strings_offset + strings_size]
    symbols: list[tuple[str, int, int] | None] = [None] * symbol_count
    index = 0
    cursor = symbol_offset
    while index < symbol_count:
        item = data[cursor : cursor + 18]
        raw_name = item[:8]
        if raw_name[:4] == b"\0\0\0\0":
            name_offset = struct.unpack_from("<I", raw_name, 4)[0]
            end = strings.find(b"\0", name_offset)
            name = strings[name_offset:end].decode("utf-8", errors="replace")
        else:
            name = raw_name.split(b"\0", 1)[0].decode("utf-8", errors="replace")
        value, target_section, _, _, aux_count = struct.unpack_from("<IhHBB", item, 8)
        symbols[index] = (name, value, target_section)
        index += 1 + aux_count
        cursor += (1 + aux_count) * 18
    relocations = []
    for reloc_index in range(section[7]):
        site, symbol_index, kind = struct.unpack_from("<IIH", data, section[5] + reloc_index * 10)
        target = symbols[symbol_index]
        if target is None:
            raise ValueError(f"{path.name}: relocation references an auxiliary symbol")
        relocations.append({
            "site": site,
            "type": RELOC_NAMES.get(kind, f"0x{kind:04X}"),
            "target_symbol": target[0],
            "raw_addend": struct.unpack_from("<I", data, section[4] + site)[0],
        })
    return sha256(data), section_name, section_hash, relocations


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--repo", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    repo = args.repo.resolve()
    audit = repo / "audit"
    census_path = audit / "appended-thunk-payload-census-ghidra-positive-2026-09-30.json"
    roots_path = audit / "appended-thunk-relocation-targets-ghidra-positive-2026-09-30.json"
    plan_path = audit / "appended-all-fixups-extended-layout-2026-09-30-v2.json"
    census = json.loads(census_path.read_text(encoding="utf-8"))
    roots = json.loads(roots_path.read_text(encoding="utf-8"))
    plan = json.loads(plan_path.read_text(encoding="utf-8"))
    closure_path = audit / "appended-thunk-local-section-closure-ghidra-positive-2026-09-30.json"
    closure = json.loads(closure_path.read_text(encoding="utf-8"))
    bridge_path = audit / "crt-original-helper-bridge-three-section-rel32-fixups-2026-09-30-v2.json"
    bridge = json.loads(bridge_path.read_text(encoding="utf-8"))
    extended_path = audit / "inplace-local-section-closure-extended-layout-2026-09-30-v2.json"
    extended = json.loads(extended_path.read_text(encoding="utf-8"))
    cross_path = audit / "appended-cross-object-code-sections-extended-layout-2026-09-30.json"
    cross_sections = json.loads(cross_path.read_text(encoding="utf-8"))
    provider_path = audit / "appended-thunk-provider-original-addresses-ghidra-positive-2026-09-30b.json"
    closure_provider_path = audit / "appended-thunk-local-closure-provider-original-addresses-ghidra-positive-2026-09-30b.json"
    provider = json.loads(provider_path.read_text(encoding="utf-8"))
    closure_provider = json.loads(closure_provider_path.read_text(encoding="utf-8"))
    if census["candidate_entries"] != 705 or census["thunk_entries"] != 421:
        raise ValueError("candidate census is not the expected 705/421 set")
    expected_hashes = {row["entry_va"].lower(): row["object_sha256"] for row in census["entries"]}
    planned_fixups = {
        (row["owner_entry_va"].lower(), int(row["site_rva"], 16)): row
        for row in plan["fixups"]
    }
    if len(planned_fixups) != len(plan["fixups"]):
        raise ValueError("appended fixup plan contains duplicate owner/RVA identities")
    payload_rva = int(census["provisional_appended_rva"], 16)
    raw_site_count = 0
    object_hash_mismatches = []
    missing_sites = []
    mismatch_rows = []
    section_hash_mismatches = []
    closure_site_count = 0
    closure_type_counts: collections.Counter[str] = collections.Counter()
    code_rva = int(extended["layout"]["appended_code_rva"], 16)
    data_rva = int(extended["layout"]["appended_data_rva_after_rdata_extension"], 16)
    section_layout: dict[tuple[str, int], tuple[int, str, int]] = {}
    for item in bridge["local_xcode_layout"]:
        section_layout[(item["source_entry"].lower(), int(item["section_number"]))] = (
            code_rva, ".xcode", int(item["payload_offset"])
        )
    for item in bridge["data_local_layout"]:
        if item["section_name"] != ".bss":
            section_layout[(item["source_entry"].lower(), int(item["section_number"]))] = (
                data_rva, ".data", int(item["payload_offset"])
            )
    raw_type_counts: collections.Counter[str] = collections.Counter()
    target_class_counts: collections.Counter[str] = collections.Counter()
    objects_dir = Path(census["objects_directory"])
    for entry in census["entries"]:
        va = entry["entry_va"].lower()
        object_path = objects_dir / f"{int(va, 16):08x}.obj"
        object_hash, relocations = read_root_relocations(object_path, entry["symbol"])
        if object_hash != expected_hashes[va]:
            object_hash_mismatches.append(va)
        if len(relocations) != sum(entry["coff_relocation_counts"].values()):
            raise ValueError(f"{va}: object relocation count differs from the payload census")
        payload_offset = int(entry["provisional_payload_offset"])
        for relocation in relocations:
            raw_site_count += 1
            kind = str(relocation["type"])
            raw_type_counts[kind] += 1
            site_rva = payload_rva + payload_offset + int(relocation["site"])
            planned = planned_fixups.get((va, site_rva))
            if planned is None:
                missing_sites.append({"owner_entry_va": va, "site_rva": f"0x{site_rva:08X}", **relocation})
                continue
            target_class_counts[str(planned["target_class"])] += 1
            if planned["type"] != kind or planned["raw_addend"] != relocation["raw_addend"]:
                mismatch_rows.append({
                    "owner_entry_va": va,
                    "site_rva": f"0x{site_rva:08X}",
                    "coff_type": kind,
                    "plan_type": planned["type"],
                    "coff_raw_addend": relocation["raw_addend"],
                    "plan_raw_addend": planned["raw_addend"],
                })
    # Verify the 16 copied local closure sections, including their raw bytes,
    # relocations, and exact fields in the same global fixup manifest.
    for item in closure["sections"]:
        owner = item["source_entry"].lower()
        section_number = int(item["section_number"])
        object_path = objects_dir / f"{int(owner, 16):08X}.obj"
        object_hash, section_name, section_hash, relocations = read_section_relocations(object_path, section_number)
        if object_hash != item["object_sha256"] or section_name != item["section_name"] or section_hash != item["section_sha256"]:
            section_hash_mismatches.append({"owner_entry_va": owner, "section_number": section_number})
        if item["relocation_count"] != len(relocations):
            raise ValueError(f"{owner} section {section_number}: closure relocation count differs")
        location = section_layout.get((owner, section_number))
        if relocations and location is None:
            raise ValueError(f"{owner} section {section_number}: relocation-bearing closure section has no layout")
        if location is None:
            continue
        section_rva, source_section, payload_offset = location
        for relocation in relocations:
            closure_site_count += 1
            closure_type_counts[str(relocation["type"])] += 1
            site_rva = section_rva + payload_offset + int(relocation["site"])
            planned = planned_fixups.get((owner, site_rva))
            if planned is None:
                missing_sites.append({"owner_entry_va": owner, "site_rva": f"0x{site_rva:08X}", "source_section": section_name, **relocation})
                continue
            if planned["source_section"] != source_section or planned["type"] != relocation["type"] or planned["raw_addend"] != relocation["raw_addend"]:
                mismatch_rows.append({
                    "owner_entry_va": owner,
                    "site_rva": f"0x{site_rva:08X}",
                    "coff_type": relocation["type"],
                    "plan_type": planned["type"],
                    "coff_raw_addend": relocation["raw_addend"],
                    "plan_raw_addend": planned["raw_addend"],
                    "coff_section": section_name,
                    "plan_section": planned["source_section"],
                })
    helper_site_count = 0
    for item in cross_sections["new_xcode_sections"]:
        owner = item["source_entry"].lower()
        section_number = int(item["section_number"])
        object_path = objects_dir / f"{int(owner, 16):08X}.obj"
        object_hash, section_name, section_hash, relocations = read_section_relocations(object_path, section_number)
        if object_hash != item["object_sha256"] or section_name != ".xcode" or section_hash != item["section_sha256"]:
            section_hash_mismatches.append({"owner_entry_va": owner, "section_number": section_number})
        for relocation in relocations:
            helper_site_count += 1
            site_rva = code_rva + int(item["payload_offset"]) + int(relocation["site"])
            planned = planned_fixups.get((owner, site_rva))
            if planned is None:
                missing_sites.append({"owner_entry_va": owner, "site_rva": f"0x{site_rva:08X}", "source_section": section_name, **relocation})
            elif planned["source_section"] != ".xcode" or planned["type"] != relocation["type"] or planned["raw_addend"] != relocation["raw_addend"]:
                mismatch_rows.append({"owner_entry_va": owner, "site_rva": f"0x{site_rva:08X}", "coff_type": relocation["type"], "plan_type": planned["type"], "coff_raw_addend": relocation["raw_addend"], "plan_raw_addend": planned["raw_addend"]})
    matched_root_plan_rows = sum(
        1 for row in plan["fixups"]
        if row["source_section"] == ".xcode"
        and any(
            row["owner_entry_va"].lower() == entry["entry_va"].lower()
            and int(row["site_rva"], 16) >= payload_rva + int(entry["provisional_payload_offset"])
            and int(row["site_rva"], 16) < payload_rva + int(entry["provisional_payload_offset"]) + int(entry["body_size"])
            for entry in census["entries"]
        )
    )
    unresolved_target_classes = {
        name: count for name, count in target_class_counts.items()
        if "unresolved" in name.lower() or "ambiguous" in name.lower()
    }
    all_plan_target_classes = plan["summary"]["target_classes"]
    unresolved_plan_target_classes = {
        name: count for name, count in all_plan_target_classes.items()
        if "unresolved" in name.lower() or "ambiguous" in name.lower()
    }
    report = {
        "scope": "Raw object-site/type/addend coverage for all 421 appended root bodies against the current appended fixup plan; no PE or object fields are written.",
        "inputs": {
            "original_asi_sha256": plan["inputs"]["original_asi"],
            "payload_census_sha256": sha256(census_path.read_bytes()),
            "root_relocations_sha256": sha256(roots_path.read_bytes()),
            "fixup_plan_sha256": sha256(plan_path.read_bytes()),
        },
        "counts": {
            "appended_root_bodies": len(census["entries"]),
            "raw_root_relocation_sites": raw_site_count,
            "root_relocations_by_type": dict(sorted(raw_type_counts.items())),
            "root_sites_joined_to_fixup_plan": raw_site_count - len(missing_sites),
            "closure_raw_relocation_sites": closure_site_count,
            "closure_relocations_by_type": dict(sorted(closure_type_counts.items())),
            "cross_object_helper_relocation_sites": helper_site_count,
            "missing_sites_across_roots_closures_helpers": len(missing_sites),
            "type_or_raw_addend_mismatches": len(mismatch_rows),
            "fixup_plan_total_fields": len(plan["fixups"]),
            "fixup_plan_unique_sites": plan["summary"]["unique_sites"],
            "object_hash_mismatches": len(object_hash_mismatches),
            "closure_section_or_object_hash_mismatches": len(section_hash_mismatches),
            "unresolved_or_ambiguous_target_classes_in_joined_root_sites": sum(unresolved_target_classes.values()),
            "unresolved_or_ambiguous_target_classes_in_full_plan": sum(unresolved_plan_target_classes.values()),
            "unmapped_provider_occurrences": int(provider["unmapped_occurrences"]) + int(closure_provider["unmapped_occurrences"]),
        },
        "joined_root_target_classes": dict(sorted(target_class_counts.items())),
        "full_plan_target_classes": dict(sorted(all_plan_target_classes.items())),
        "missing_sites": missing_sites,
        "field_mismatches": mismatch_rows,
        "object_hash_mismatch_entries": object_hash_mismatches,
        "closure_section_or_object_hash_mismatches": section_hash_mismatches,
        "all_root_sites_joined": matched_root_plan_rows == raw_site_count,
        "all_root_closure_and_helper_sites_joined": not missing_sites and raw_site_count + closure_site_count + helper_site_count == len(plan["fixups"]),
        "all_types_and_raw_addends_match": not mismatch_rows,
        "all_objects_match_payload_census": not object_hash_mismatches and not section_hash_mismatches,
        "all_plan_target_classes_resolved": not unresolved_plan_target_classes,
        "limitations": [
            "The joined fixup plan is not applied to a final image.",
            "A mapped target class does not independently prove target lifetime, initialization, or ABI correctness.",
            "No PE emission, Windows loader test, startup test, or in-game test is performed.",
        ],
    }
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"output": str(args.output), **report["counts"],
                      "all_root_sites_joined": report["all_root_sites_joined"],
                      "all_root_closure_and_helper_sites_joined": report["all_root_closure_and_helper_sites_joined"],
                      "all_types_and_raw_addends_match": report["all_types_and_raw_addends_match"],
                      "all_objects_match_payload_census": report["all_objects_match_payload_census"],
                      "all_plan_target_classes_resolved": report["all_plan_target_classes_resolved"]}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
