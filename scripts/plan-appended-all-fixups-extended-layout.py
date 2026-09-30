#!/usr/bin/env python3
"""Resolve and compute every COFF fixup in the planned appended roots/closures.

The result is a provisional fixup manifest for an extended layout. It does
not write object fields, PE bytes, or an ASI.
"""

from __future__ import annotations

import argparse
import hashlib
import json
from collections import defaultdict
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


def raw_addend(value: str, kind: str) -> int:
    return int(value, 16) if isinstance(value, str) else int(value)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--original-asi", type=Path, required=True)
    parser.add_argument("--symbols", type=Path, required=True)
    parser.add_argument("--payload-census", type=Path, required=True)
    parser.add_argument("--root-relocations", type=Path, required=True)
    parser.add_argument("--closure", type=Path, required=True)
    parser.add_argument("--bridge-layout", type=Path, required=True)
    parser.add_argument("--extended-layout", type=Path, required=True)
    parser.add_argument("--local-section-audit", type=Path, required=True)
    parser.add_argument("--cross-object-sections", type=Path, required=True)
    parser.add_argument("--encoded-addresses", type=Path, required=True)
    parser.add_argument("--closure-encoded-addresses", type=Path, required=True)
    parser.add_argument("--provider-addresses", type=Path, required=True)
    parser.add_argument("--closure-provider-addresses", type=Path, required=True)
    parser.add_argument("--imports", type=Path, required=True)
    parser.add_argument("--closure-imports", type=Path, required=True)
    parser.add_argument("--api-crosswalk", type=Path, required=True)
    parser.add_argument("--root-code-targets", type=Path, required=True)
    parser.add_argument("--closure-code-targets", type=Path, required=True)
    parser.add_argument("--api-thunks", type=Path, required=True)
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
    local_audit = read_json(args.local_section_audit)
    cross_sections = read_json(args.cross_object_sections)
    encoded = read_json(args.encoded_addresses)
    closure_encoded = read_json(args.closure_encoded_addresses)
    provider = read_json(args.provider_addresses)
    closure_provider = read_json(args.closure_provider_addresses)
    imports = read_json(args.imports)
    closure_imports = read_json(args.closure_imports)
    api_crosswalk = read_json(args.api_crosswalk)
    root_code = read_json(args.root_code_targets)
    closure_code = read_json(args.closure_code_targets)
    api_thunks = read_json(args.api_thunks)
    base_relocs = read_json(args.base_relocations)
    pe = pefile.PE(str(args.original_asi), fast_load=False)
    image_base = int(pe.OPTIONAL_HEADER.ImageBase)

    checks = [
        (sha256(args.bridge_layout), extended["inputs"]["appended_layout_sha256"], "bridge layout"),
        (sha256(args.payload_census), bridge["payload_census_sha256"], "payload census"),
        (sha256(args.root_relocations), census["local_sections_report_sha256"], "root relocations"),
        (Path(closure["relocation_target_report"]).resolve(), args.root_relocations.resolve(), "closure root report"),
        (sha256(args.extended_layout), local_audit["inputs"]["extended_layout_sha256"], "extended layout"),
        (sha256(args.root_relocations), cross_sections["inputs"]["root_relocations_sha256"], "cross-object root report"),
        (sha256(args.bridge_layout), cross_sections["inputs"]["bridge_layout_sha256"], "cross-object bridge layout"),
        (sha256(args.extended_layout), cross_sections["inputs"]["extended_layout_sha256"], "cross-object extended layout"),
        (sha256(args.base_reloc_directory_bin), local_audit["inputs"]["base_relocation_blob_sha256"], "base relocation blob"),
    ]
    for actual, expected, label in checks:
        if actual != expected:
            raise SystemExit(f"{label} input does not match its dependent report")
    if len(census["entries"]) != int(census["thunk_entries"]):
        raise SystemExit("appended-root census entry count disagrees with thunk_entries")
    if len(roots["relocations"]) != int(roots["relocation_count"]):
        raise SystemExit("appended-root relocation count disagrees with relocation rows")

    objects_dir = Path(symbols["inputs"]["objects"])
    functions = {int(row["entry_va"], 16): row for row in symbols["functions"]}
    roots_by_va = {int(row["entry_va"], 16): row for row in census["entries"]}
    if len(roots_by_va) != int(census["thunk_entries"]):
        raise SystemExit("duplicate/missing appended-root entry")
    for owner, entry in roots_by_va.items():
        obj = objects_dir / f"{owner:08X}.obj"
        if sha256(obj) != entry["object_sha256"]:
            raise SystemExit(f"appended root object hash mismatch: {obj}")
    for section in closure["sections"]:
        owner = int(section["source_entry"], 16)
        obj = objects_dir / f"{owner:08X}.obj"
        if sha256(obj) != section["object_sha256"]:
            raise SystemExit(f"closure object hash mismatch: {obj}")

    # Merge every materialized local section placement. The two closure-only
    # literal sections were extracted and hash-verified by the preceding audit.
    sections: dict[tuple[int, int], dict] = {}
    for row in bridge["rdata_layout"]:
        key = (int(row["source_entry"], 16), int(row["section_number"]))
        sections[key] = {**row, "section_name": ".rdata", "rva": int(extended["layout"]["appended_rdata_rva_after_code_extension"], 16)}
    for row in bridge["local_xcode_layout"]:
        key = (int(row["source_entry"], 16), int(row["section_number"]))
        sections[key] = {**row, "section_name": ".xcode", "rva": int(extended["layout"]["appended_code_rva"], 16)}
    for row in bridge["data_local_layout"]:
        key = (int(row["source_entry"], 16), int(row["section_number"]))
        sections[key] = {**row, "rva": int(local_audit["layout"]["new_data_rva"], 16)}
    for row in extended["local_section_layout"]:
        key = (int(row["source_entry_va"], 16), int(row["section_number"]))
        if key in sections:
            raise SystemExit(f"duplicate copied section {key}")
        sections[key] = {
            **row,
            "section_name": row["section_name"],
            "source_entry": row["source_entry_va"],
            "rva": int(extended["layout"]["appended_code_rva" if row["section_name"] == ".xcode" else "appended_rdata_rva_after_code_extension"], 16),
        }
    for row in local_audit["additional_closure_rdata_sections"]:
        key = (int(row["source_entry"], 16), int(row["section_number"]))
        if key in sections:
            raise SystemExit(f"duplicate closure literal section {key}")
        sections[key] = row
    for row in cross_sections["new_xcode_sections"]:
        key = (int(row["source_entry"], 16), int(row["section_number"]))
        if key in sections:
            raise SystemExit(f"duplicate cross-object helper section {key}")
        sections[key] = {
            **row, "rva": int(extended["layout"]["appended_code_rva"], 16),
            "section_name": ".xcode",
        }
    cross_targets = {
        (int(row["source_entry"], 16), int(row["site"]), row["symbol"]): int(row["target_va"], 16)
        for row in cross_sections["cross_object_target_callsites"]
    }

    # Field-level symbol evidence, normalised by decorated symbol/type.
    code_maps: dict[str, dict[tuple[str, str], list[dict]]] = {
        "root": defaultdict(list), "closure": defaultdict(list)
    }
    for row in root_code["rows"]:
        code_maps["root"][(row["symbol"], row["relocation_type"])].append(row)
    for row in closure_code["rows"]:
        code_maps["closure"][(row["symbol"], row["relocation_type"])].append(row)
    encoded_map: dict[str, set[int]] = defaultdict(set)
    for report in [encoded, closure_encoded]:
        for row in report["mapped_targets"]:
            encoded_map[row["symbol"]].add(int(row["va"], 16))
    provider_map: dict[tuple[str, str], set[int]] = defaultdict(set)
    for row in provider["mapped_targets"] + closure_provider["mapped_targets"]:
        provider_map[(row["symbol"], row["relocation_type"])].add(int(row["original_target_va"], 16))
    import_map: dict[str, set[int]] = defaultdict(set)
    for row in imports["imports"] + closure_imports["imports"]:
        for match in row["original_iat_matches_by_name_and_dll"]:
            import_map[row["coff_import_symbol"]].add(int(match["iat_va"], 16))
    api_iat_by_symbol: dict[str, int] = {}
    for row in api_crosswalk["imports"]:
        if row["status"] != "exact-original-iat-match":
            continue
        api_iat_by_symbol[row["coff_code_symbol"]] = int(row["iat_va"], 16)
    api_thunk_by_symbol = {row["code_symbol"]: row for row in api_thunks["results"]}
    bridge_callers = bridge["candidate_caller_fixups"]

    def unique(values: set[int], label: str) -> int:
        if len(values) != 1:
            raise SystemExit(f"{label} target is not unique: {sorted(hex(v) for v in values)}")
        return next(iter(values))

    fixups: list[dict] = []
    site_rvas: set[int] = set()
    target_classes: dict[str, int] = defaultdict(int)

    def emit(owner: int, site: int, kind: str, symbol: str, source_rva: int,
             target_va: int, addend: int, classification: str, source_section: str) -> None:
        site_rva = source_rva + site
        source_va = image_base + site_rva
        if site_rva in site_rvas:
            raise SystemExit(f"duplicate full-fixup site {site_rva:#x}")
        site_rvas.add(site_rva)
        if kind == "DIR32":
            value = target_va + addend
            if not 0 <= value <= 0xFFFFFFFF:
                raise SystemExit(f"DIR32 value overflow at {site_rva:#x}")
            rel32_fits = True
        elif kind == "REL32":
            value = target_va + addend - (source_va + 4)
            rel32_fits = -(1 << 31) <= value < (1 << 31)
            if not rel32_fits:
                raise SystemExit(f"REL32 out of range at {site_rva:#x}")
        else:
            raise SystemExit(f"unsupported COFF relocation type {kind}")
        fixups.append({
            "owner_entry_va": hex(owner), "site_rva": hex(site_rva),
            "source_section": source_section, "type": kind, "symbol": symbol,
            "target_va": hex(target_va), "raw_addend": addend,
            "computed_field_value": hex(value & 0xFFFFFFFF),
            "target_class": classification, "rel32_fits_signed_range": rel32_fits,
        })
        target_classes[classification] += 1

    def local_target(owner: int, section_number: int, section_name: str, value: int) -> int:
        target = sections.get((owner, section_number))
        if target is None or target["section_name"] != section_name:
            raise SystemExit(f"local target not laid out: {owner:#x} #{section_number} {section_name}")
        return image_base + int(target["rva"]) + int(target["payload_offset"]) + value

    # Root and local-closure rows are independently processed so every COFF
    # relocation field must join exactly once to current source bytes.
    inventory: list[dict] = []
    for row in roots["relocations"]:
        inventory.append({"owner": int(row["source_entry"], 16), "site": int(row["site"]),
                          "type": row["type"], "symbol": row["target_symbol"],
                          "target_class": row["target_class"], "target_value": int(row["target_value"]),
                          "target_section_number": int(row["target_section_number"]),
                          "target_section": row["target_section"], "candidate_object_definitions": row.get("candidate_object_definitions"),
                          "source_kind": "root"})
    for section in closure["sections"]:
        owner = int(section["source_entry"], 16)
        for row in section["relocations"]:
            inventory.append({"owner": owner, "site": int(row["site"]), "type": row["type"],
                              "symbol": row["target_symbol"], "target_class": row["target_class"],
                              "target_value": int(row["target_value"]),
                              "target_section_number": int(row["target_section_number"]),
                              "target_section": row["target_section"], "raw_field_bytes": row["raw_field_bytes"],
                              "source_section_number": int(section["section_number"]),
                              "source_section": section["section_name"], "source_kind": "closure"})
    for row in cross_sections["helper_fixups"]:
        inventory.append({"owner": int(row["source_entry"], 16), "site": int(row["site"]),
                          "type": row["type"], "symbol": row["target_symbol"],
                          "target_class": "cross-object-helper-to-root", "target_value": 0,
                          "source_section_number": int(row["source_section_number"]),
                          "source_section": ".xcode", "source_kind": "cross-shim",
                          "resolved_target_va": int(row["target_va"], 16),
                          "raw_field_bytes": row["raw_addend"]})
    expected_inventory = (
        len(roots["relocations"])
        + sum(len(section["relocations"]) for section in closure["sections"])
        + len(cross_sections["helper_fixups"])
    )
    if len(inventory) != expected_inventory:
        raise SystemExit(f"root+closure+cross-shim inventory mismatch: {len(inventory)} != {expected_inventory}")

    for row in inventory:
        owner, site, kind, symbol = row["owner"], row["site"], row["type"], row["symbol"]
        source_kind = row["source_kind"]
        if source_kind == "root":
            entry = roots_by_va.get(owner)
            function = functions.get(owner)
            if entry is None or function is None:
                raise SystemExit(f"root owner absent from candidate maps: {owner:#x}")
            source_rva = int(bridge["provisional_appended_rva"], 16) + int(entry["provisional_payload_offset"])
            source_section_name = ".xcode"
            matches = [r for r in function["relocations"] if int(r["offset"]) == site and r["type"] == kind and r["symbol"] == symbol]
            if len(matches) != 1:
                raise SystemExit(f"root COFF relocation join not unique at {owner:#x}+{site:#x}")
            raw = matches[0]["raw_addend"]
        elif source_kind == "closure":
            source_key = (owner, row["source_section_number"])
            source_section = sections.get(source_key)
            if source_section is None or source_section["section_name"] != row["source_section"]:
                raise SystemExit(f"closure source not laid out: {source_key}")
            source_rva = int(source_section["rva"]) + int(source_section["payload_offset"])
            source_section_name = row["source_section"]
            raw = row["raw_field_bytes"]
        else:
            source_key = (owner, row["source_section_number"])
            source_section = sections.get(source_key)
            if source_section is None:
                raise SystemExit(f"cross-shim source section not laid out: {source_key}")
            source_rva = int(source_section["rva"]) + int(source_section["payload_offset"])
            source_section_name = ".xcode"
            raw = row["raw_field_bytes"]
        addend = int(raw) if isinstance(raw, int) else (raw_addend(raw, kind) if " " not in raw else int.from_bytes(bytes(int(b,16) for b in raw.split()), "little", signed=kind == "REL32"))

        classification = row["target_class"]
        if classification == "cross-object-helper-to-root":
            target_va = row["resolved_target_va"]
            classification = "cross-object-helper-to-candidate-root"
        elif classification in {"defined-in-same-object-section", "same-object-section"}:
            target_va = local_target(owner, row["target_section_number"], row["target_section"], row["target_value"])
        elif classification == "candidate-root":
            match = matches[0]
            if not match.get("candidate_target_entry_va"):
                raise SystemExit(f"candidate-root target lacks entry VA: {owner:#x}+{site:#x} {symbol}")
            target_va = int(match["candidate_target_entry_va"], 16)
            classification = "candidate-entry"
        elif classification == "defined-by-other-candidate-object":
            target_va = cross_targets.get((owner, site, symbol))
            if target_va is None:
                raise SystemExit(f"cross-object target section is not precisely placed at {owner:#x}+{site:#x}")
            classification = "cross-object-local-section"
        elif classification == "unresolved-external-or-alias" or classification == "undefined-external":
            code_rows = code_maps[source_kind].get((symbol, kind), [])
            statuses = {(item["status"], item.get("target_va")) for item in code_rows}
            if len(statuses) > 1:
                raise SystemExit(f"code target class is ambiguous: {symbol} {kind} {statuses}")
            status, code_va = next(iter(statuses)) if statuses else (None, None)
            if status == "static-crt-runtime":
                matches_bridge = [b for b in bridge_callers if int(b["source_entry"],16) == owner and int(b["site_offset_in_body"]) == site and b["target_symbol"] == symbol]
                if len(matches_bridge) != 1:
                    raise SystemExit(f"CRT bridge fixup missing/ambiguous at {owner:#x}+{site:#x}")
                bridge_symbol = matches_bridge[0]["bridge_symbol"]
                bridge_va = bridge["bridge_symbols"][bridge_symbol]["va_if_layout_retained"]
                target_va = int(bridge_va, 16)
                classification = "verified-original-crt-helper-bridge"
            elif status == "import-or-system-api":
                if kind == "DIR32" and symbol.startswith("__imp_"):
                    target_va = unique(import_map[symbol], f"IAT {symbol}")
                    classification = "exact-original-IAT-slot"
                elif kind == "REL32":
                    if symbol not in api_iat_by_symbol or symbol not in api_thunk_by_symbol:
                        raise SystemExit(f"REL32 API has no verified original-IAT thunk: {symbol}")
                    thunk = api_thunk_by_symbol[symbol]
                    if int(thunk["iat_va"],16) != api_iat_by_symbol[symbol]:
                        raise SystemExit(f"API IAT evidence disagrees for {symbol}")
                    payload = Path(bridge["api_thunk_payload_file"]).read_bytes()
                    offset = int(thunk["code_offset"],16)
                    if payload[offset:offset+2] != b"\xFF\x25" or int.from_bytes(payload[offset+2:offset+6],"little") != api_iat_by_symbol[symbol]:
                        raise SystemExit(f"API thunk bytes/IAT mismatch for {symbol}")
                    target_va = image_base + int(bridge["provisional_appended_rva"],16) + int(bridge["api_thunk_payload_offset_in_code_section"]) + offset
                    classification = "exact-original-IAT-call-thunk"
                else:
                    raise SystemExit(f"unexpected relocation type for imported API {symbol}: {kind}")
            elif code_va:
                target_va = int(code_va, 16)
                classification = status or "code-target"
            elif provider_map.get((symbol, kind)):
                target_va = unique(provider_map[(symbol, kind)], f"provider {symbol}/{kind}")
                classification = "original-provider-address"
            elif encoded_map.get(symbol):
                target_va = unique(encoded_map[symbol], f"encoded address {symbol}")
                classification = "original-image-encoded-address"
            elif import_map.get(symbol):
                target_va = unique(import_map[symbol], f"original IAT {symbol}")
                classification = "exact-original-IAT-slot"
            else:
                raise SystemExit(f"unresolved target evidence: {owner:#x}+{site:#x} {kind} {symbol}")
        else:
            raise SystemExit(f"unsupported source target class {classification}: {symbol}")

        emit(owner, site, kind, symbol, source_rva, target_va, addend, classification, source_section_name)

    if len(fixups) != expected_inventory or len(site_rvas) != expected_inventory:
        raise SystemExit("not every root/closure relocation produced exactly one fixup")

    output = {
        "scope": f"Field-level provisional fixup values for all {len(roots_by_va)} appended roots and their copied local sections. No object/PE bytes are written.",
        "inputs": {
            name: sha256(path) for name, path in [
                ("original_asi", args.original_asi), ("symbols", args.symbols),
                ("payload_census", args.payload_census), ("root_relocations", args.root_relocations),
                ("closure", args.closure), ("bridge_layout", args.bridge_layout),
                ("extended_layout", args.extended_layout), ("local_section_audit", args.local_section_audit),
                ("cross_object_sections", args.cross_object_sections),
                ("encoded_addresses", args.encoded_addresses), ("closure_encoded_addresses", args.closure_encoded_addresses),
                ("provider_addresses", args.provider_addresses), ("closure_provider_addresses", args.closure_provider_addresses),
                ("imports", args.imports), ("closure_imports", args.closure_imports), ("api_crosswalk", args.api_crosswalk),
                ("root_code_targets", args.root_code_targets), ("closure_code_targets", args.closure_code_targets),
                ("api_thunks", args.api_thunks), ("base_relocations", args.base_relocations),
            ]
        },
        "summary": {
            "appended_roots": len(roots_by_va), "local_closure_sections": len(closure["sections"]),
            "relocations_inventoried": len(inventory), "fixups_computed": len(fixups),
            "target_classes": dict(sorted(target_classes.items())),
            "unique_sites": len(site_rvas),
            "dir32_count": sum(1 for row in fixups if row["type"] == "DIR32"),
            "rel32_count": sum(1 for row in fixups if row["type"] == "REL32"),
            "all_rel32_in_range": all(row["rel32_fits_signed_range"] for row in fixups),
        },
        "limitations": [
            "GTA .text targets are validated by section membership, not complete function identity/ABI.",
            "Original-image data targets still need lifetime, initialization, and loader-context validation.",
            "Installer/startup integration, PE emission, loader execution, and gameplay remain untested.",
        ],
        "fixups": fixups,
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(output, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(output["summary"], indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
