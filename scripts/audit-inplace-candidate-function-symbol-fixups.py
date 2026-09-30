#!/usr/bin/env python3
"""Compute preferred-base fixups for candidate-function symbols in direct bodies.

This is a target-specific inventory only. It does not patch a PE or resolve
non-candidate symbols, and it does not prove runtime behavior.
"""

from __future__ import annotations

import argparse
import csv
import hashlib
import importlib.util
import json
import re
import struct
from pathlib import Path

import pefile


ROOT = Path(__file__).resolve().parents[1]
SYMBOL_AUDIT = ROOT / "scripts/audit-candidate-relocation-symbol-targets.py"
RELOC_BUILDER = ROOT / "scripts/build-appended-relocation-directory-probe.py"
PINNED_ORIGINAL_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"
PINNED_GAME_SHA256 = "F01A00CE950FA40CA1ED59DF0E789848C6EDCF6405456274965885D0929343AC"
GHIDRA_CRT_NAME_ALIASES = {
    "_strcpy_s": ("_strcpy_s", 0x10010A19, "errno_t __cdecl _strcpy_s(char * _Dst, rsize_t _SizeInBytes, char * _Src)"),
    "_strcat_s": ("_strcat_s", 0x10010AAD, "errno_t __cdecl _strcat_s(char * _Dst, rsize_t _SizeInBytes, char * _Src)"),
    "_strncmp": ("_strncmp", 0x10010D8B, "int __cdecl _strncmp(char * _Str1, char * _Str2, size_t _MaxCount)"),
    "_atexit": ("_atexit", 0x10010529, "int __cdecl _atexit(_func_4879 * param_1)"),
    "_terminate": ("terminate", 0x10017DDE, "noreturn void __cdecl terminate(void)"),
    "__strnicmp_l": ("__strnicmp_l", 0x10010BA1, "int __cdecl __strnicmp_l(char * _Str1, char * _Str2, size_t _MaxCount, _locale_t _Locale)"),
    "_FID_conflict__sscanf": ("FID_conflict:_sscanf", 0x100103E4, "int __cdecl FID_conflict:_sscanf(char * _Src, char * _Format, ...)"),
    "@___DllMainCRTStartup@12": ("___DllMainCRTStartup", 0x100110BD, "int __fastcall ___DllMainCRTStartup(int param_1, int param_2, undefined4 param_3)"),
}
GAME_FUN_SYMBOL = re.compile(r"FUN_([0-9A-Fa-f]{6,8})")
ADDRESS_SYMBOL_PATTERNS = (
    ("IVF_INSTALL_TARGET", re.compile(r"IVF_INSTALL_TARGET_([0-9A-Fa-f]{8})")),
    ("IVF_EH_HANDLER", re.compile(r"IVF_EH_HANDLER_([0-9A-Fa-f]{8})")),
    ("ImVehFt_FUN", re.compile(r"(?:^|[^0-9A-Za-z])(?:_?thunk_)?_?FUN_(100[0-9A-Fa-f]{5})")),
    ("IVF_RELOC_TARGET", re.compile(r"IVF_RELOC_TARGET_([0-9A-Fa-f]{8})")),
    ("DAT", re.compile(r"DAT_([0-9A-Fa-f]{8})")),
    ("PTR_vftable", re.compile(r"PTR_vftable_([0-9A-Fa-f]{8})")),
    ("PTR_LAB", re.compile(r"PTR_LAB_([0-9A-Fa-f]{8})")),
    ("PNG", re.compile(r"PNG_([0-9A-Fa-f]{8})")),
    ("s_ImVehFt", re.compile(r"s_ImVehFt_([0-9A-Fa-f]{8})")),
)


def load_symbol_audit():
    spec = importlib.util.spec_from_file_location("candidate_symbol_audit", SYMBOL_AUDIT)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot load {SYMBOL_AUDIT}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def load_reloc_builder():
    spec = importlib.util.spec_from_file_location("reloc_directory_builder", RELOC_BUILDER)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot load {RELOC_BUILDER}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest().upper()


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--objects", type=Path, required=True)
    parser.add_argument("--placement-plan", type=Path, required=True)
    parser.add_argument("--symbol-crosswalk", type=Path, required=True)
    parser.add_argument("--relocation-directory", type=Path)
    parser.add_argument("--ghidra-function-map", type=Path, default=ROOT / "audit/function-name-map.csv")
    parser.add_argument("--game-exe", type=Path)
    parser.add_argument("--cross-object-sections", type=Path)
    parser.add_argument("--original", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")

    plan_bytes = args.placement_plan.read_bytes()
    crosswalk_bytes = args.symbol_crosswalk.read_bytes()
    plan = json.loads(plan_bytes)
    crosswalk = json.loads(crosswalk_bytes)
    if plan.get("candidate_count") != 705 or crosswalk["summary"].get("candidate_functions") != 705:
        raise ValueError("expected the complete 705-candidate placement and symbol reports")

    candidate_entries = {
        row["entry_symbol"]: int(row["address"], 16)
        for row in plan["entries"]
    }
    plan_by_va = {int(row["address"], 16): row for row in plan["entries"]}
    if len(candidate_entries) != 705 or len(plan_by_va) != 705:
        raise ValueError("candidate symbols or addresses are not unique")

    direct_vas = {
        int(row["address"], 16)
        for row in plan["entries"]
        if row["placement_mode"] == "body-at-entry"
    }
    functions_by_va = {int(row["entry_va"], 16): row for row in crosswalk["functions"]}
    if len(functions_by_va) != 705 or not direct_vas.issubset(functions_by_va):
        raise ValueError("symbol crosswalk does not cover all candidates")
    crosswalk_objects = Path(crosswalk["inputs"]["objects"]).resolve()
    if args.objects.resolve() != crosswalk_objects:
        raise ValueError("object directory differs from the one used by the symbol crosswalk")
    inplace_report_path = Path(crosswalk["inputs"]["placement_report"])
    inplace_report = json.loads(inplace_report_path.read_text(encoding="utf-8"))
    inplace_by_va = {int(row["entry_va"], 16): row for row in inplace_report["results"]}

    ghidra_map: dict[str, list[dict[str, str]]] = {}
    with args.ghidra_function_map.open(encoding="utf-8-sig", newline="") as stream:
        for map_row in csv.DictReader(stream):
            ghidra_map.setdefault(map_row["ghidra_name"], []).append(map_row)
    ghidra_aliases: dict[str, dict[str, object]] = {}
    for coff_symbol, (ghidra_name, expected_va, expected_prototype) in GHIDRA_CRT_NAME_ALIASES.items():
        matches = ghidra_map.get(ghidra_name, [])
        if len(matches) != 1:
            raise ValueError(f"Ghidra function map must contain exactly one {ghidra_name} row")
        map_row = matches[0]
        if (int(map_row["address"], 16) != expected_va
                or map_row["signature"] != expected_prototype
                or map_row["objective_verdict"] != "PASS"):
            raise ValueError(f"Ghidra alias evidence changed for {coff_symbol}: {map_row}")
        if expected_va not in candidate_entries.values():
            raise ValueError(f"Ghidra target for {coff_symbol} is not one of the 705 candidate entries")
        ghidra_aliases[coff_symbol] = {
            "target_va": expected_va, "ghidra_name": ghidra_name,
            "prototype": expected_prototype, "map_source": str(args.ghidra_function_map.resolve()),
        }

    coff = load_symbol_audit()
    original_hash = sha256(args.original)
    if original_hash != PINNED_ORIGINAL_SHA256:
        raise ValueError(f"original ASI hash mismatch: {original_hash}")
    image = args.original.read_bytes()
    pe = pefile.PE(data=image, fast_load=True)
    image_base = int(pe.OPTIONAL_HEADER.ImageBase)
    original_sections = []
    for section in pe.sections:
        original_sections.append(
            {
                "name": section.Name.rstrip(b"\0").decode("ascii", errors="replace"),
                "va_start": image_base + int(section.VirtualAddress),
                "va_end": image_base + int(section.VirtualAddress) + max(
                    int(section.Misc_VirtualSize), int(section.SizeOfRawData)
                ),
                "raw_size": int(section.SizeOfRawData),
                "virtual_size": int(section.Misc_VirtualSize),
            }
        )
    game_hash = None
    game_text_ranges: list[tuple[int, int, str]] = []
    if args.game_exe:
        game_hash = sha256(args.game_exe)
        if game_hash != PINNED_GAME_SHA256:
            raise ValueError(f"pinned GTA SA executable hash mismatch: {game_hash}")
        game_pe = pefile.PE(str(args.game_exe), fast_load=True)
        game_base = int(game_pe.OPTIONAL_HEADER.ImageBase)
        for section in game_pe.sections:
            name = section.Name.rstrip(b"\0").decode("ascii", errors="replace")
            if name == ".text":
                start = game_base + int(section.VirtualAddress)
                end = start + max(int(section.Misc_VirtualSize), int(section.SizeOfRawData))
                game_text_ranges.append((start, end, name))
    locale_helper_target = None
    locale_section_evidence = None
    if args.cross_object_sections:
        cross_object_report = json.loads(args.cross_object_sections.read_text(encoding="utf-8"))
        section_rows = [row for row in cross_object_report["new_xcode_sections"]
                        if int(row["source_entry"], 16) == 0x10010B1A
                        and int(row["section_number"]) == 3]
        helper_rows = [row for row in cross_object_report["helper_fixups"]
                       if int(row["source_entry"], 16) == 0x10010B1A
                       and int(row["source_section_number"]) == 3]
        if len(section_rows) != 1 or len(helper_rows) != 1:
            raise ValueError("expected one exact _LocaleUpdate local helper section and its root call")
        local_section = section_rows[0]
        helper_fixup = helper_rows[0]
        section_bytes = bytes.fromhex(local_section["bytes_hex"])
        object_path = args.objects / "10010B1A.obj"
        if (local_section["section_name"] != ".xcode" or len(section_bytes) != 18
                or hashlib.sha256(section_bytes).hexdigest().upper() != local_section["section_sha256"]
                or sha256(object_path) != local_section["object_sha256"]
                or helper_fixup["target_symbol"] != "??0_LocaleUpdate@@QAE@PAUlocaleinfo_struct@@@Z"
                or int(helper_fixup["target_va"], 16) != 0x10010B1A
                or not helper_fixup["rel32_fits_signed_range"]):
            raise ValueError("_LocaleUpdate helper-section or constructor-target evidence failed integrity checks")
        locale_helper_target = int(local_section["preferred_va"], 16)
        locale_section_evidence = {
            "source_entry": local_section["source_entry"],
            "section_number": local_section["section_number"],
            "preferred_va": local_section["preferred_va"],
            "size": local_section["size"],
            "section_sha256": local_section["section_sha256"],
            "object_sha256": local_section["object_sha256"],
            "report": str(args.cross_object_sections.resolve()),
            "helper_target_va": helper_fixup["target_va"],
        }
    locale_alias_header = (ROOT / "src/functions/locale_update_ctor_bridge.hpp").read_text(encoding="utf-8")
    if "/alternatename:_IVF_LocaleUpdate_ctor_relocatable=??0_LocaleUpdate@@QAE@PAUlocaleinfo_struct@@@Z" not in locale_alias_header:
        raise ValueError("_LocaleUpdate linker alias evidence changed")
    full_pe = pefile.PE(data=image, fast_load=False)
    imported_slots: dict[str, list[dict[str, object]]] = {}
    for descriptor in getattr(full_pe, "DIRECTORY_ENTRY_IMPORT", []):
        dll = descriptor.dll.decode("ascii", errors="replace")
        for imported in descriptor.imports:
            if imported.name:
                name = imported.name.decode("ascii", errors="replace")
                imported_slots.setdefault(name.casefold(), []).append({
                    "name": name, "dll": dll, "iat_va": int(imported.address),
                })
    rows: list[dict[str, object]] = []
    sites: set[int] = set()
    kind_counts: dict[str, int] = {"DIR32": 0, "REL32": 0}
    binding_counts: dict[str, int] = {
        "candidate_function_symbol": 0,
        "candidate_ghidra_name_crosswalk": 0,
        "candidate_address_encoded_entry": 0,
        "exact_original_iat_slot": 0,
        "external_game_text_symbol": 0,
        "candidate_linker_alternatename": 0,
        "cross_object_local_code_section": 0,
        "local_symbol_same_code_section": 0,
        "original_address_encoded_symbol": 0,
    }
    addend_verified = 0
    object_hashes_verified = 0
    unmapped_address_symbols: list[dict[str, object]] = []
    for entry in sorted(direct_vas):
        candidate = plan_by_va[entry]
        function = functions_by_va[entry]
        obj_path = args.objects / f"{entry:08x}.obj"
        expected_object_hash = inplace_by_va[entry]["object_sha256"].upper()
        if sha256(obj_path) != expected_object_hash:
            raise ValueError(f"{obj_path.name}: object hash differs from the authoritative 705-entry audit")
        object_hashes_verified += 1
        parsed = coff.read_object(obj_path, candidate["entry_symbol"])
        object_relocs = parsed["relocations"]
        by_key: dict[tuple[int, str, str], list[dict[str, object]]] = {}
        for relocation in object_relocs:
            by_key.setdefault(
                (int(relocation["offset"]), str(relocation["type"]), str(relocation["symbol"])), []
            ).append(relocation)

        relevant = 0
        for item in function["relocations"]:
            target_name = str(item["symbol"])
            target_va = None
            binding_kind = "candidate_function_symbol"
            original_target_section = None
            original_target_backing = None
            obj_reloc = None
            if item.get("symbol_defined_in_object"):
                key = (int(item["offset"]), str(item["type"]), target_name)
                local_matches = by_key.get(key, [])
                if len(local_matches) != 1:
                    raise ValueError(f"{entry:#x}: cannot uniquely match object-defined relocation {key}")
                obj_reloc = local_matches[0]
                if int(obj_reloc["symbol_section_number"]) == int(parsed["entry_section_number"]):
                    target_va = entry + int(obj_reloc["symbol_value"])
                    binding_kind = "local_symbol_same_code_section"
            if target_va is None and not item.get("symbol_defined_in_object"):
                target_va = candidate_entries.get(target_name)
            if target_va is None and not item.get("symbol_defined_in_object") and target_name in ghidra_aliases:
                target_va = int(ghidra_aliases[target_name]["target_va"])
                binding_kind = "candidate_ghidra_name_crosswalk"
            if target_va is None and not item.get("symbol_defined_in_object") and target_name == "_IVF_LocaleUpdate_ctor_relocatable":
                target_va = 0x10010B1A
                binding_kind = "candidate_linker_alternatename"
            if (target_va is None and not item.get("symbol_defined_in_object")
                    and target_name == "??0_LocaleUpdate@@QAE@PAU__crt_locale_pointers@@@Z"
                    and locale_helper_target is not None):
                target_va = locale_helper_target
                binding_kind = "cross_object_local_code_section"
            if target_va is None and not item.get("symbol_defined_in_object") and target_name.startswith("__imp__"):
                import_match = re.fullmatch(r"__imp__(.+?)(?:@\d+)?", target_name)
                if import_match:
                    matches = imported_slots.get(import_match.group(1).casefold(), [])
                    if len(matches) == 1:
                        target_va = int(matches[0]["iat_va"])
                        binding_kind = "exact_original_iat_slot"
                        original_target_section = f"IAT:{matches[0]['dll']}!{matches[0]['name']}"
            if target_va is None and not item.get("symbol_defined_in_object"):
                for pattern_name, pattern in ADDRESS_SYMBOL_PATTERNS:
                    match = pattern.search(target_name)
                    if match:
                        encoded_va = int(match.group(1), 16)
                        target_section = next(
                            (s for s in original_sections if s["va_start"] <= encoded_va < s["va_end"]),
                            None,
                        )
                        if target_section is None:
                            unmapped_address_symbols.append(
                                {
                                    "caller_entry_va": f"0x{entry:08x}",
                                    "field_offset": int(item["offset"]),
                                    "symbol": target_name,
                                    "encoded_va": f"0x{encoded_va:08x}",
                                    "encoding_pattern": pattern_name,
                                }
                            )
                            break
                        target_va = encoded_va
                        original_target_section = target_section["name"]
                        delta = encoded_va - target_section["va_start"]
                        original_target_backing = (
                            "raw-backed" if delta < target_section["raw_size"] else "virtual-only"
                        )
                        binding_kind = (
                            "candidate_address_encoded_entry"
                            if encoded_va in plan_by_va else "original_address_encoded_symbol"
                        )
                        break
            if target_va is None and not item.get("symbol_defined_in_object") and args.game_exe:
                game_match = GAME_FUN_SYMBOL.search(target_name)
                if game_match:
                    encoded_va = int(game_match.group(1), 16)
                    containing = [(start, end, name) for start, end, name in game_text_ranges
                                  if start <= encoded_va < end]
                    if len(containing) == 1:
                        target_va = encoded_va
                        binding_kind = "external_game_text_symbol"
                        original_target_section = containing[0][2]
            if target_va is None:
                continue
            offset = int(item["offset"])
            kind = str(item["type"])
            key = (offset, kind, target_name)
            matches = by_key.get(key, [])
            if len(matches) != 1:
                raise ValueError(f"{entry:#x}+{offset:#x}: expected one matching COFF relocation, got {len(matches)}")
            obj_reloc = matches[0]
            raw = int(str(obj_reloc["raw_addend"]), 16)
            if str(item["raw_addend"]).lower() != f"0x{raw:08x}":
                raise ValueError(f"{entry:#x}+{offset:#x}: audit/object addend mismatch")
            body_size = int(parsed["body_size"])
            if offset < 0 or offset + 4 > body_size:
                raise ValueError(f"{entry:#x}+{offset:#x}: relocation lies outside candidate body")
            site_va = entry + offset
            site_rva = site_va - 0x10000000
            if site_rva in sites:
                raise ValueError(f"duplicate in-place fixup site RVA {site_rva:#x}")
            sites.add(site_rva)

            if kind == "DIR32":
                value = (target_va + raw) & 0xFFFFFFFF
                required_base_relocation = True
            elif kind == "REL32":
                signed_addend = struct.unpack("<i", struct.pack("<I", raw))[0]
                value = target_va + signed_addend - (site_va + 4)
                if not -(1 << 31) <= value < (1 << 31):
                    raise ValueError(f"{entry:#x}+{offset:#x}: REL32 out of range ({value})")
                required_base_relocation = False
            else:
                raise ValueError(f"unexpected candidate-function relocation type {kind}")

            relevant += 1
            addend_verified += 1
            kind_counts[kind] += 1
            binding_counts[binding_kind] += 1
            rows.append(
                {
                    "caller_entry_va": f"0x{entry:08x}",
                    "caller_placement": "body-at-entry",
                    "field_offset": offset,
                    "field_va": f"0x{site_va:08x}",
                    "field_rva": f"0x{site_rva:08x}",
                    "relocation_type": kind,
                    "raw_addend": f"0x{raw:08x}",
                    "target_symbol": target_name,
                    "target_binding_kind": binding_kind,
                    "original_target_section": original_target_section,
                    "original_target_backing": original_target_backing,
                    "candidate_target_entry_va": (
                        f"0x{target_va:08x}"
                        if binding_kind.startswith("candidate_") else None
                    ),
                    "target_preferred_va": f"0x{target_va:08x}",
                    "target_placement": (
                        plan_by_va[target_va]["placement_mode"]
                        if binding_kind in {"candidate_function_symbol", "candidate_ghidra_name_crosswalk", "candidate_address_encoded_entry", "candidate_linker_alternatename"}
                        else ("external-GTA-.text" if binding_kind == "external_game_text_symbol"
                              else ("original-image" if binding_kind == "original_address_encoded_symbol"
                                    else ("appended-local-code-section" if binding_kind == "cross_object_local_code_section"
                                          else "within-direct-body")))
                    ),
                    "ghidra_name_evidence": ghidra_aliases.get(target_name),
                    "cross_object_section_evidence": (
                        locale_section_evidence if binding_kind == "cross_object_local_code_section" else None
                    ),
                    "encoded_value": f"0x{value & 0xffffffff:08x}",
                    "base_relocation_required_at_field": required_base_relocation,
                }
            )
        if relevant == 0:
            continue

    report = {
        "scope": "Computed preferred-base fixup values for direct candidate bodies using exact candidate symbols, explicit Ghidra aliases, pinned-IAT names, and address-encoded targets; target-specific inventory only, no PE patch emitted.",
        "image_base": "0x10000000",
        "placement_plan": str(args.placement_plan.resolve()),
        "placement_plan_sha256": hashlib.sha256(plan_bytes).hexdigest().upper(),
        "symbol_crosswalk": str(args.symbol_crosswalk.resolve()),
        "symbol_crosswalk_sha256": hashlib.sha256(crosswalk_bytes).hexdigest().upper(),
        "objects_directory": str(args.objects.resolve()),
        "original_image": str(args.original.resolve()),
        "original_image_sha256": original_hash,
        "game_executable": str(args.game_exe.resolve()) if args.game_exe else None,
        "game_executable_sha256": game_hash,
        "cross_object_sections_report": str(args.cross_object_sections.resolve()) if args.cross_object_sections else None,
        "locale_constructor_local_section_evidence": locale_section_evidence,
        "object_hash_reference": str(inplace_report_path.resolve()),
        "relocation_directory": str(args.relocation_directory.resolve()) if args.relocation_directory else None,
        "summary": {
            "candidate_count": 705,
            "direct_body_count": len(direct_vas),
        "candidate_function_symbol_fixups": binding_counts["candidate_function_symbol"],
            "candidate_ghidra_name_crosswalk_fixups": binding_counts["candidate_ghidra_name_crosswalk"],
            "candidate_address_encoded_entry_fixups": binding_counts["candidate_address_encoded_entry"],
            "exact_original_iat_slot_fixups": binding_counts["exact_original_iat_slot"],
            "local_same_code_section_fixups": binding_counts["local_symbol_same_code_section"],
            "original_address_encoded_symbol_fixups": binding_counts.get("original_address_encoded_symbol", 0),
            "resolved_fixups_total": len(rows),
            "fixups_by_type": kind_counts,
            "object_addends_independently_rechecked": addend_verified,
            "object_hashes_matched_authoritative_audit": object_hashes_verified,
            "unique_fixup_field_rvas": len(sites),
            "all_rel32_in_signed_range": True,
            "dir32_sites_requiring_highlow": kind_counts["DIR32"],
            "unmapped_address_encoded_symbols": len(unmapped_address_symbols),
        },
        "limitations": [
            "The inventory includes exact decorated candidate symbols, three explicit Ghidra-name CRT aliases, encoded target addresses validated against original image sections, and uniquely named imports resolved against the pinned original IAT.",
            "This does not resolve unencoded CRT externals or non-fitting body relocations.",
            "GTA FUN_ address symbols are checked only for membership in exactly one .text section of the pinned executable; semantic and ABI equivalence remain separate checks.",
            "The 284-body placement plan still has separate xref/semantic and runtime limits.",
            "No relocation values are written into a PE; no loader or game validation is performed.",
        ],
        "fixups": rows,
        "unmapped_address_encoded_symbols": unmapped_address_symbols,
    }
    if args.relocation_directory:
        relocation_data = args.relocation_directory.read_bytes()
        relocation_sites = load_reloc_builder().parse_relocs(relocation_data)
        candidate_dir32_rvas = {
            int(row["field_rva"], 16)
            for row in rows
            if row["relocation_type"] == "DIR32"
        }
        missing_sites = sorted(candidate_dir32_rvas - relocation_sites)
        if missing_sites:
            raise ValueError(f"{len(missing_sites)} candidate DIR32 fixups are absent from base-relocation directory")
        report["relocation_directory_sha256"] = sha256(args.relocation_directory)
        report["summary"]["dir32_sites_in_base_relocation_directory"] = len(candidate_dir32_rvas)
        report["summary"]["all_candidate_dir32_sites_present_in_base_relocations"] = True
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    print(json.dumps(report["summary"], indent=2))
    print(f"report={args.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
