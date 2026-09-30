#!/usr/bin/env python3
"""Join direct-body executable fixups to existing pinned-image target evidence.

This is a read-only audit. Diagnostic linker addresses are never accepted as
production targets. Each row is classified only by an owner+relocation-field
join to an existing API call plan, exact imported IAT name/DLL, an original
candidate entry encoded in a vetted alias, or membership in installed GTA
SA's .text. Other references remain explicitly unresolved.
"""

from __future__ import annotations

import argparse
import collections
import hashlib
import json
import re
from pathlib import Path

import pefile


PINNED_ASI_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"


def load_json(path: Path) -> dict:
    return json.loads(path.read_text(encoding="utf-8"))


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest().upper()


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--symbols", type=Path, required=True)
    ap.add_argument("--placement-plan", type=Path, required=True)
    ap.add_argument("--api-plan", type=Path, required=True)
    ap.add_argument("--function-fixups", type=Path, required=True)
    ap.add_argument("--iat-slots", type=Path, required=True)
    ap.add_argument("--installer-target-map", type=Path, required=True)
    ap.add_argument("--local-stubs", type=Path, required=True)
    ap.add_argument("--ghidra-export-dir", type=Path, required=True)
    ap.add_argument("--original-asi", type=Path, required=True)
    ap.add_argument("--game-exe", type=Path, required=True)
    ap.add_argument("--output", type=Path, required=True)
    args = ap.parse_args()

    original_hash = sha256(args.original_asi)
    if original_hash != PINNED_ASI_SHA256:
        raise SystemExit(f"pinned ASI hash mismatch: {original_hash}")
    symbols = load_json(args.symbols)
    placement_plan = load_json(args.placement_plan)
    api_plan = load_json(args.api_plan)
    function_fixups = load_json(args.function_fixups)
    iat_report = load_json(args.iat_slots)
    installer_targets = load_json(args.installer_target_map)
    local_stub_text = args.local_stubs.read_text(encoding="utf-8")
    placements = {int(row["address"], 16): row for row in placement_plan["entries"]}
    direct_entries = {
        va: row for va, row in placements.items()
        if row["placement_mode"] == "body-at-entry"
    }

    # These are exact field-level matches, not symbol-count extrapolations.
    api_sites: dict[tuple[int, int], dict] = {}
    for patch in api_plan["rel32_patches"]:
        if patch["callsite_class"] != "in-place-body":
            continue
        owner = int(patch["candidate_entry"], 16)
        field_va = int(patch["candidate_callsite_va"], 16)
        key = (owner, field_va - owner)
        if key in api_sites:
            raise SystemExit(f"duplicate API patch site: {key}")
        api_sites[key] = patch
    seen_api_sites: set[tuple[int, int]] = set()
    function_fixups_by_site = {
        (int(row["caller_entry_va"], 16), int(row["field_offset"])): row
        for row in function_fixups["fixups"]
        if row.get("target_binding_kind") == "cross_object_local_code_section"
    }

    iat_by_import_symbol: dict[str, list[dict]] = collections.defaultdict(list)
    for item in iat_report["imports"]:
        iat_by_import_symbol[item["coff_import_symbol"]].append(item)
    installer_by_wrapper = {
        item["wrapper_symbol"].lstrip("_"): item
        for item in installer_targets.get("patches", [])
    }

    original_pe = pefile.PE(str(args.original_asi), fast_load=False)
    original_imports: dict[str, list[dict]] = collections.defaultdict(list)
    for descriptor in original_pe.DIRECTORY_ENTRY_IMPORT:
        dll = descriptor.dll.decode("ascii", errors="replace")
        for imported in descriptor.imports:
            if imported.name is None:
                continue
            name = imported.name.decode("ascii", errors="replace")
            original_imports[name.casefold()].append({
                "dll": dll,
                "name": name,
                "iat_va": hex(int(imported.address)),
            })

    original_text = []
    for section in original_pe.sections:
        name = section.Name.rstrip(b"\0").decode("ascii", errors="replace")
        if name == ".text":
            start = int(original_pe.OPTIONAL_HEADER.ImageBase) + int(section.VirtualAddress)
            end = start + max(int(section.Misc_VirtualSize), int(section.SizeOfRawData))
            original_text.append((start, end))

    def normalize_symbol(name: str) -> str:
        name = re.sub(r"@\d+$", "", name)
        return re.sub(r"[^0-9a-z]", "", name.casefold())

    game = pefile.PE(str(args.game_exe), fast_load=True)
    game_base = int(game.OPTIONAL_HEADER.ImageBase)
    game_sections = []
    for section in game.sections:
        name = section.Name.rstrip(b"\0").decode("ascii", errors="replace")
        start = game_base + int(section.VirtualAddress)
        end = start + max(int(section.Misc_VirtualSize), int(section.SizeOfRawData))
        game_sections.append((name, start, end))

    rows: list[dict] = []
    for function in symbols["functions"]:
        owner = int(function["entry_va"], 16)
        if owner not in direct_entries:
            continue
        for reloc in function["relocations"]:
            symbol = reloc["symbol"]
            kind = reloc["type"]
            field_offset = int(reloc["offset"])
            api_patch = api_sites.get((owner, field_offset))
            if (reloc["target_class"] not in {
                    "diagnostic_executable_contribution",
                    "candidate_function_entry",
                    "local_symbol_in_candidate_body",
                }
                    and api_patch is None):
                continue
            target = None
            evidence = None

            if api_patch is not None:
                if kind != "REL32" or api_patch["target_api_symbol"] != symbol:
                    raise SystemExit(
                        f"API plan/site mismatch at {function['entry_va']}+{field_offset:#x}"
                    )
                seen_api_sites.add((owner, field_offset))
                target = {
                    "preferred_va": api_patch["replacement_thunk_va"],
                    "iat_va": next(
                        t["iat_va"] for t in api_plan["thunks"]
                        if t["api_code_symbol"] == symbol
                    ),
                    "thunk_symbol": api_patch["replacement_thunk_symbol"],
                }
                evidence = "exact-owner-and-relocation-field-API-thunk-plan"
            elif (reloc["target_class"] == "local_symbol_in_candidate_body"
                    and reloc.get("symbol_section") == ".xcode"):
                symbol_offset = int(reloc.get("symbol_value", -1))
                body_size = int(placements[owner]["candidate_body_size"])
                if 0 <= symbol_offset < body_size:
                    target = {
                        "preferred_va": hex(owner + symbol_offset),
                        "coff_section": ".xcode",
                        "symbol_offset": symbol_offset,
                        "candidate_placement_mode": placements[owner]["placement_mode"],
                    }
                    evidence = "same-object-local-code-section-at-original-entry-va"
            elif (reloc["target_class"] != "candidate_function_entry"
                    and bool(reloc["symbol_defined_in_object"])
                    and reloc.get("symbol_section") in {".xcode", ".text"}):
                # A COFF definition in another code section of this same
                # object is authoritative over a coincidentally matching
                # Ghidra/address alias. Its final address comes from section
                # placement, not from the function's entry VA.
                target = {
                    "coff_defined_section": reloc["symbol_section"],
                    "final_va": None,
                    "final_rva_status": "pending-section-layout",
                }
                evidence = "known-same-object-code-symbol-awaiting-section-placement"
            elif reloc["target_class"] == "candidate_function_entry":
                encoded_target = reloc.get("candidate_target_entry_va")
                candidate_target = int(encoded_target, 16) if encoded_target else None
                if candidate_target in placements:
                    target = {
                        "preferred_va": hex(candidate_target),
                        "candidate_placement_mode": placements[candidate_target]["placement_mode"],
                    }
                    evidence = "exact-diagnostic-map-to-candidate-entry-crosswalk"
            else:
                installer = installer_by_wrapper.get(symbol.lstrip("_"))
                if installer is not None and installer["target_symbol"]:
                    target = {
                        "preferred_va": installer["target_address"],
                        "target_symbol": installer["target_symbol"],
                        "target_kind": installer["target_kind"],
                    }
                    evidence = "preserved-installer-target-manifest"

                imported = iat_by_import_symbol.get("__imp_" + symbol, [])
                exact = []
                for item in imported:
                    exact.extend(item.get("original_iat_matches_by_name_and_dll", []))
                # Direct code relocations use decorated COFF function names,
                # while the original PE import table stores undecorated names.
                code_api = re.fullmatch(r"_([A-Za-z][A-Za-z0-9_]*)@\d+", symbol)
                if not exact and code_api:
                    exact.extend(original_imports.get(code_api.group(1).casefold(), []))
                if target is None and len(exact) == 1:
                    target = {
                        "iat_va": exact[0]["iat_va"],
                        "dll": exact[0]["dll"],
                        "api_name": exact[0]["name"],
                    }
                    evidence = "exact-import-name-and-dll-to-original-iat"
                elif target is None:
                    handler = re.search(r"IVF_EH_HANDLER_(100[0-9A-Fa-f]{5})$", symbol)
                    if handler:
                        handler_va = int(handler.group(1), 16)
                        stub_pattern = (
                            rf'add\(\(0x{handler_va:08x},\),\s*"{re.escape(symbol)}",'
                        )
                        if re.search(stub_pattern, local_stub_text, re.IGNORECASE):
                            target = {
                                "preferred_va": hex(handler_va),
                                "local_stub_definition": str(args.local_stubs.resolve()),
                                "local_stub_script_sha256": sha256(args.local_stubs),
                            }
                            evidence = "exact-generated-local-EH-funclet-stub"

                    alias = re.search(r"IVF_INSTALL_TARGET_((?:10)?[0-9A-Fa-f]{6,8})$", symbol)
                    encoded = int(alias.group(1), 16) if alias else None
                    if target is None and encoded in placements:
                        target = {
                            "preferred_va": hex(encoded),
                            "placement_mode": placements[encoded]["placement_mode"],
                        }
                        evidence = "encoded-alias-to-candidate-entry"
                    elif target is None:
                        image_entry = re.search(r"(?<![0-9A-Fa-f])(100[0-9A-Fa-f]{5})(?![0-9A-Fa-f])", symbol)
                        entry_va = int(image_entry.group(1), 16) if image_entry else None
                        if entry_va in placements:
                            target = {
                                "preferred_va": hex(entry_va),
                                "placement_mode": placements[entry_va]["placement_mode"],
                            }
                            evidence = "encoded-symbol-to-candidate-entry"
                    if target is None:
                        export_path = args.ghidra_export_dir / f"{owner:08x}.json"
                        if export_path.is_file():
                            export = load_json(export_path)
                            normalized = normalize_symbol(symbol)
                            matches = [
                                callee for callee in export.get("callees", [])
                                if (
                                    normalize_symbol(str(callee.get("name", ""))) == normalized
                                    or (
                                        "localeupdate" in symbol.casefold()
                                        and normalize_symbol(str(callee.get("name", ""))) == "localeupdate"
                                    )
                                )
                                and re.fullmatch(r"[0-9A-Fa-f]{8}", str(callee.get("addr", "")))
                            ]
                            match_addresses = {int(item["addr"], 16) for item in matches}
                            if len(match_addresses) == 1:
                                callee_va = next(iter(match_addresses))
                                if any(lo <= callee_va < hi for lo, hi in original_text):
                                    target = {
                                        "preferred_va": hex(callee_va),
                                        "ghidra_name": matches[0]["name"],
                                        "ghidra_export": str(export_path.resolve()),
                                        "ghidra_export_sha256": sha256(export_path),
                                        "candidate_placement_mode": (
                                            placements[callee_va]["placement_mode"]
                                            if callee_va in placements else None
                                        ),
                                    }
                                    evidence = "owner-specific-ghidra-callee-name-and-original-text-va"
                            if target is None:
                                for instruction in export.get("assembly", []):
                                    literals = re.finditer(
                                        r"(?<![0-9A-Fa-f])(?:0x)?(100[0-9A-Fa-f]{5})(?![0-9A-Fa-f])",
                                        instruction, re.IGNORECASE,
                                    )
                                    for literal in literals:
                                        literal_va = int(literal.group(1), 16)
                                        target_export_path = args.ghidra_export_dir / f"{literal_va:08x}.json"
                                        if not target_export_path.is_file():
                                            continue
                                        target_export = load_json(target_export_path)
                                        if normalize_symbol(str(target_export.get("name", ""))) == normalized:
                                            target = {
                                                "preferred_va": hex(literal_va),
                                                "ghidra_name": target_export["name"],
                                                "ghidra_export": str(target_export_path.resolve()),
                                                "ghidra_export_sha256": sha256(target_export_path),
                                                "candidate_placement_mode": (
                                                    placements[literal_va]["placement_mode"]
                                                    if literal_va in placements else None
                                                ),
                                            }
                                            evidence = "owner-assembly-literal-to-exact-ghidra-function"
                                            break
                                    if target is not None:
                                        break
                        if target is None and bool(reloc["symbol_defined_in_object"]):
                            section_name = reloc.get("symbol_section")
                            if section_name in {".xcode", ".text"}:
                                target = {
                                    "coff_defined_section": section_name,
                                    "final_va": None,
                                    "final_rva_status": "pending-section-layout",
                                }
                                evidence = "known-same-object-code-symbol-awaiting-section-placement"
                    if target is None:
                        game_match = re.search(r"FUN_([0-9A-Fa-f]{6,8})", symbol)
                        game_va = int(game_match.group(1), 16) if game_match else None
                        if game_va is not None:
                            section = next(
                                (name for name, lo, hi in game_sections if lo <= game_va < hi),
                                None,
                            )
                            if section == ".text":
                                target = {"preferred_va": hex(game_va), "section": section}
                                evidence = "address-encoded-gta-executable-text"

            cross_object = function_fixups_by_site.get((owner, field_offset))
            if cross_object is not None:
                if (cross_object["target_symbol"] != symbol
                        or cross_object["relocation_type"] != kind):
                    raise SystemExit(
                        f"cross-object fixup does not match direct COFF site "
                        f"{function['entry_va']}+{field_offset:#x}"
                    )
                target = {
                    "preferred_va": cross_object["target_preferred_va"],
                    "target_section_owner": cross_object["cross_object_section_evidence"]["source_entry"],
                    "target_section_number": cross_object["cross_object_section_evidence"]["section_number"],
                    "target_section_sha256": cross_object["cross_object_section_evidence"]["section_sha256"],
                }
                evidence = "exact-cross-object-local-code-section-fixup"

            rows.append({
                "owner_entry_va": function["entry_va"],
                "field_offset": field_offset,
                "field_va": hex(owner + field_offset),
                "symbol": symbol,
                "relocation_type": kind,
                "object_defined": bool(reloc["symbol_defined_in_object"]),
                "object_section": reloc.get("symbol_section"),
                "classification": evidence or "unresolved-requires-specific-target-evidence",
                "target": target,
            })

    if seen_api_sites != set(api_sites):
        missing = sorted(set(api_sites) - seen_api_sites)
        raise SystemExit(f"API call-plan sites missing from direct-body relocations: {missing[:8]}")

    counts = collections.Counter(row["classification"] for row in rows)
    result = {
        "scope": (
            f"Executable-symbol relocations in the {len(direct_entries)} direct-body candidate objects. "
            "Reports target evidence only; does not write PE fixups, choose final local "
            "section RVAs, or validate behavior/runtime."
        ),
        "inputs": {
            "symbols": str(args.symbols.resolve()),
            "placement_plan": str(args.placement_plan.resolve()),
            "api_plan": str(args.api_plan.resolve()),
            "function_fixups": str(args.function_fixups.resolve()),
            "iat_slots": str(args.iat_slots.resolve()),
            "installer_target_map": str(args.installer_target_map.resolve()),
            "local_stubs": str(args.local_stubs.resolve()),
            "ghidra_export_dir": str(args.ghidra_export_dir.resolve()),
            "original_asi": str(args.original_asi.resolve()),
            "original_asi_sha256": original_hash,
            "game_exe": str(args.game_exe.resolve()),
            "game_exe_sha256": sha256(args.game_exe),
        },
        "summary": {
            "direct_body_count": len(direct_entries),
            "executable_relocation_occurrences": len(rows),
            "occurrences_by_classification": dict(sorted(counts.items())),
            "unresolved_occurrences": sum(1 for row in rows if row["target"] is None),
            "known_local_symbols_awaiting_final_rva": sum(
                1 for row in rows
                if row["classification"] == "known-same-object-code-symbol-awaiting-section-placement"
            ),
            "api_plan_sites_joined_exactly": len(seen_api_sites),
            "api_plan_sites_expected": len(api_sites),
            "all_api_plan_sites_joined_exactly": seen_api_sites == set(api_sites),
        },
        "limitations": [
            "An IAT target classification does not generate a REL32 thunk or patch its callsite.",
            "A candidate entry target does not prove code or object semantics.",
            "GTA .text section membership confirms image range, not function identity or ABI.",
            "Same-object local executable sections still need final placement and relocation application.",
            "No PE/ASI bytes are written; no loader or GTA runtime test is performed.",
        ],
        "rows": rows,
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(result["summary"], indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
