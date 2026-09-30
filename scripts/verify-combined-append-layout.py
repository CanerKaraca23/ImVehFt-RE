#!/usr/bin/env python3
"""Cross-check separately generated direct/appended placement plans together.

This is a metadata/layout audit only. It does not write fixups or PE bytes,
and cannot establish target semantics, initialization, loader behavior, or
GTA runtime compatibility.
"""

from __future__ import annotations

import argparse
import json
from pathlib import Path


PINNED_ASI = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"


def read_json(path: Path) -> dict:
    return json.loads(path.read_text(encoding="utf-8-sig"))


def parse_rva(row: dict) -> int:
    value = row.get("site_rva", row.get("field_rva"))
    if value is None:
        raise ValueError(f"fixup has no site_rva/field_rva: {row}")
    return int(value, 16) if isinstance(value, str) else int(value)


def align(value: int, boundary: int) -> int:
    return (value + boundary - 1) & ~(boundary - 1)


def main() -> int:
    repo = Path(__file__).resolve().parents[1]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--output",
        type=Path,
        default=repo / "audit/combined-append-layout-crosscheck-2026-09-30.json",
    )
    args = parser.parse_args()
    if args.output.exists():
        raise SystemExit(f"refusing to overwrite existing report: {args.output}")

    direct = read_json(repo / "audit/inplace-candidate-function-symbol-fixups-ghidra-positive-2026-09-30-v6.json")
    direct_sections = read_json(repo / "audit/inplace-local-section-closure-extended-layout-2026-09-30-v2.json")
    appended = read_json(repo / "audit/appended-all-fixups-extended-layout-2026-09-30-v2.json")
    appended_sections = read_json(repo / "audit/appended-local-section-rva-shifts-extended-layout-2026-09-30-v3.json")
    helpers = read_json(repo / "audit/appended-cross-object-code-sections-extended-layout-2026-09-30.json")
    bridge = read_json(repo / "audit/crt-original-helper-bridge-three-section-rel32-fixups-2026-09-30-v2.json")
    relocation_base = read_json(repo / "audit/all-705-candidate-code-relocation-directory-conservative-current-2026-09-30-v3.json")
    direct_closure_externals = read_json(repo / "audit/inplace-local-closure-external-targets-ghidra-positive-2026-09-30.json")
    direct_closure_coff = read_json(repo / "audit/inplace-candidate-local-section-closure-ghidra-positive-2026-09-30-v2.json")

    checks: dict[str, bool] = {}
    checks["all_plans_pin_same_original_asi"] = (
        direct["original_image_sha256"] == PINNED_ASI
        and direct_sections["inputs"]["original_asi_sha256"] == PINNED_ASI
        and appended["inputs"]["original_asi"] == PINNED_ASI
        and appended_sections["inputs"]["original_asi_sha256"] == PINNED_ASI
        and helpers["inputs"]["original_asi_sha256"] == PINNED_ASI
        and bridge["original_asi_sha256"] == PINNED_ASI
        and relocation_base["original_sha256"] == PINNED_ASI
    )

    direct_layout = direct_sections["layout"]
    root_code_end = int(bridge["bridge_payload_offset"]) + int(bridge["bridge_payload_bytes"])
    api_start = int(direct_layout["direct_api_thunk_payload_offset"])
    api_end = api_start + int(direct_layout["direct_api_thunk_payload_bytes"])
    local_code_start = int(direct_layout["local_xcode_payload_start_offset"])
    local_xcode = [
        row for row in direct_sections["local_section_layout"]
        if row["section_name"] == ".xcode"
    ]
    code_ranges = sorted(
        (int(row["payload_offset"]), int(row["payload_offset"]) + int(row["size"]))
        for row in local_xcode
    )
    local_code_end = max((end for _, end in code_ranges), default=local_code_start)
    code_ranges_disjoint = all(
        code_ranges[index][1] <= code_ranges[index + 1][0]
        for index in range(len(code_ranges) - 1)
    )
    helper_ranges = sorted(
        (int(row["payload_offset"]), int(row["payload_offset"]) + int(row["size"]))
        for row in helpers["new_xcode_sections"]
    )
    helper_start = min(start for start, _ in helper_ranges)
    full_code_end = max(end for _, end in helper_ranges)
    checks["root_payload_ends_where_direct_api_thunks_begin"] = root_code_end == api_start
    checks["direct_api_thunks_end_where_local_xcode_begins"] = api_end == local_code_start
    checks["direct_local_xcode_ranges_are_disjoint"] = code_ranges_disjoint
    checks["cross_object_helpers_follow_direct_closure_without_overlap"] = (
        local_code_end == helper_start
        and all(code_ranges[-1][1] <= start for start, _ in helper_ranges)
    )
    checks["final_code_virtual_and_raw_sizes_match"] = (
        local_code_end == int(direct_layout["extended_code_virtual_size"])
        and int(helpers["summary"]["extended_code_virtual_size"]) == full_code_end
        and align(full_code_end, 0x200) == int(helpers["summary"]["estimated_code_raw_size"])
    )
    checks["appended_rdata_and_data_rvas_agree"] = (
        int(direct_layout["appended_rdata_rva_after_code_extension"], 16)
        == int(appended_sections["layout"]["new_rdata_rva"], 16)
        and int(direct_layout["appended_data_rva_after_rdata_extension"], 16)
        == int(appended_sections["layout"]["new_data_rva"], 16)
    )
    checks["rdata_growth_includes_late_literal_sections"] = (
        int(direct_layout["extended_rdata_virtual_size"])
        + int(appended_sections["summary"]["additional_closure_rdata_bytes"])
        == int(appended_sections["summary"]["final_rdata_virtual_size"])
    )

    fixup_sets: dict[str, set[int]] = {}
    fixup_rows = {
        "direct_body": direct["fixups"],
        "direct_local_closure_and_api_thunks": direct_sections["fixups"],
        "appended_roots_and_closures": appended["fixups"],
    }
    for name, rows in fixup_rows.items():
        sites = [parse_rva(row) for row in rows]
        fixup_sets[name] = set(sites)
        checks[f"{name}_fixup_sites_unique"] = len(sites) == len(set(sites))
    combined_sites = set().union(*fixup_sets.values())
    overlap_pairs = {
        f"{left}/{right}": sorted(fixup_sets[left] & fixup_sets[right])
        for index, left in enumerate(fixup_sets)
        for right in list(fixup_sets)[index + 1:]
    }
    checks["separately_planned_fixup_sets_do_not_overlap"] = all(
        not sites for sites in overlap_pairs.values()
    )
    checks["expected_fixup_inventory_counts_match"] = (
        len(fixup_rows["direct_body"]) == 1213
        and len(fixup_rows["direct_local_closure_and_api_thunks"]) == 240
        and len(fixup_rows["appended_roots_and_closures"]) == 3085
        and len(combined_sites) == 4538
    )

    reloc = appended_sections["summary"]
    expected_highlow = (
        relocation_base["final_highlow_sites"]
        + reloc["missing_dir32_sites_added"]
        + reloc["direct_body_closure_highlow_sites_added"]
        + reloc["direct_api_thunk_highlow_sites_added"]
    )
    checks["expanded_highlow_count_and_capacity_reconcile"] = (
        expected_highlow == reloc["expanded_relocation_site_count"] == 6389
        and reloc["expanded_relocation_blob_bytes"] == 13412
        and reloc["expanded_relocation_blob_bytes"] <= reloc["original_reloc_section_capacity"]
        and reloc["expanded_relocation_roundtrip_exact"]
    )
    direct_closure_dir32 = {
        parse_rva(row) for row in direct_sections["fixups"]
        if row["origin"] == "same-object-local-section-closure"
        and row["relocation_type"] == "DIR32"
    }
    direct_closure_highlow = {
        int(value, 16) for value in direct_sections["new_highlow_site_rvas"]
    }
    late_appended_closure_highlow = {
        int(value, 16) for value in appended_sections["added_highlow_site_rvas"]
    }
    appended_dir32 = {
        parse_rva(row) for row in appended["fixups"] if row["type"] == "DIR32"
    }
    direct_api_thunk_highlow = {
        int(row["highlow_site_rva"], 16) for row in direct_sections["direct_api_thunks"]
    }
    checks["direct_closure_dir32_fields_have_highlow_entries"] = (
        len(direct_closure_dir32) == 113
        and direct_closure_dir32 <= direct_closure_highlow
        and direct_closure_dir32 == direct_closure_highlow
    )
    checks["late_appended_closure_dir32_fields_are_in_full_fixup_manifest"] = (
        len(late_appended_closure_highlow) == 128
        and late_appended_closure_highlow <= appended_dir32
    )
    checks["direct_api_thunk_absolute_operands_are_all_relocation_sites"] = (
        len(direct_api_thunk_highlow) == 12
        and len(direct_api_thunk_highlow) == len(direct_sections["direct_api_thunks"])
    )
    checks["all_relocation_plans_report_signed_rel32_fit"] = (
        direct["summary"]["all_rel32_in_signed_range"]
        and direct_sections["summary"]["all_rel32_fit_signed_range"]
        and appended["summary"]["all_rel32_in_range"]
        and helpers["summary"]["helper_rel32_all_in_range"]
    )
    closure_rows = [
        row for row in direct_sections["fixups"]
        if row["origin"] == "same-object-local-section-closure"
    ]
    closure_occurrences: dict[tuple[str, str, str], list[dict]] = {}
    for row in closure_rows:
        key = (row["owner_entry_va"].lower(), row["symbol"], row["relocation_type"])
        closure_occurrences.setdefault(key, []).append(row)
    external_mismatches = []
    external_occurrence_total = 0
    for row in direct_closure_externals["resolved_targets"]:
        key = (row["source_entry_va"].lower(), row["symbol"], row["relocation_type"])
        expected_count = int(row["occurrences_in_source_entry"])
        external_occurrence_total += expected_count
        candidates = closure_occurrences.get(key, [])
        if len(candidates) != expected_count or any(
            int(candidate["target_va"], 16) != int(row["target_va"], 16)
            for candidate in candidates
        ):
            external_mismatches.append({"key": key, "expected": expected_count, "planned": len(candidates)})
    checks["direct_closure_external_fixups_match_target_crosswalk"] = (
        external_occurrence_total == 130
        and not external_mismatches
        and direct_closure_externals["summary"]["unresolved_relocation_occurrences"] == 0
    )
    raw_relocations = {}
    for section in direct_closure_coff["sections"]:
        for row in section["relocations"]:
            key = (
                section["source_entry_va"].lower(), int(section["section_number"]),
                int(row["site"]), row["type"], row["target_symbol"],
            )
            raw_relocations[key] = row
    raw_addend_mismatches = []
    checked_raw_addends = 0
    for row in closure_rows:
        section = row["source_section"]
        key = (
            row["owner_entry_va"].lower(), int(section["section_number"]),
            int(row["site_offset"]), row["relocation_type"], row["symbol"],
        )
        raw = raw_relocations.get(key)
        if raw is None:
            raw_addend_mismatches.append({"key": key, "issue": "no source COFF relocation"})
            continue
        raw_value = int.from_bytes(
            bytes.fromhex(raw["raw_field_bytes"]),
            "little",
            signed=row["relocation_type"] == "REL32",
        )
        planned_value = int(row["raw_addend"], 16) if isinstance(row["raw_addend"], str) else int(row["raw_addend"])
        checked_raw_addends += 1
        if raw_value != planned_value:
            raw_addend_mismatches.append({
                "key": key, "source_raw_addend": raw_value,
                "planned_raw_addend": planned_value,
            })
    checks["direct_closure_fixup_addends_match_raw_coff_bytes"] = (
        checked_raw_addends == 155 and not raw_addend_mismatches
    )

    report = {
        "scope": "cross-plan placement/fixup-site consistency only; no fixup bytes or PE/ASI are emitted",
        "pinned_original_asi_sha256": PINNED_ASI,
        "candidate_placement": {
            "direct_body_candidates": direct["summary"]["direct_body_count"],
            "appended_root_candidates": appended["summary"]["appended_roots"],
        },
        "code_layout_offsets": {
            "bridge_and_root_payload_end": root_code_end,
            "direct_api_thunk_range": [api_start, api_end],
            "direct_local_xcode_start_end": [local_code_start, local_code_end],
            "cross_object_helper_range": [helper_start, full_code_end],
            "final_code_virtual_size": full_code_end,
            "pre-helper_code_raw_size": int(direct_layout["extended_code_raw_size"]),
            "final_code_raw_size": int(helpers["summary"]["estimated_code_raw_size"]),
        },
        "data_layout": {
            "appended_rdata_rva": direct_layout["appended_rdata_rva_after_code_extension"],
            "appended_data_rva": direct_layout["appended_data_rva_after_rdata_extension"],
            "rdata_size_after_late_literals": appended_sections["summary"]["final_rdata_virtual_size"],
        },
        "fixups": {
            "counts": {name: len(rows) for name, rows in fixup_rows.items()},
            "unique_combined_sites": len(combined_sites),
            "overlap_counts": {name: len(sites) for name, sites in overlap_pairs.items()},
            "direct_closure_external_target_occurrences": external_occurrence_total,
            "direct_closure_external_target_groups": len(direct_closure_externals["resolved_targets"]),
            "direct_closure_external_mismatches": external_mismatches,
            "direct_closure_raw_addends_checked": checked_raw_addends,
            "direct_closure_raw_addend_mismatches": raw_addend_mismatches,
        },
        "highlow_relocations": {
            "base": relocation_base["final_highlow_sites"],
            "expanded": reloc["expanded_relocation_site_count"],
            "serialized_bytes": reloc["expanded_relocation_blob_bytes"],
            "original_raw_capacity": reloc["original_reloc_section_capacity"],
            "direct_closure_DIR32_sites_matched": len(direct_closure_dir32),
            "late_appended_closure_DIR32_sites_matched": len(late_appended_closure_highlow),
            "direct_IAT_thunk_absolute_sites": len(direct_api_thunk_highlow),
        },
        "checks": checks,
        "all_checks_pass": all(checks.values()),
        "limitations": [
            "A resolved site inventory does not prove every target's semantic identity, lifetime, or initialization.",
            "No COFF field, original PE byte, section header, entry hook, or installer target is patched by this verifier.",
            "The result is not a loadable ASI and provides no loader, startup, or in-game validation.",
        ],
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    print(json.dumps({"all_checks_pass": report["all_checks_pass"], "checks": checks}, indent=2))
    print(f"report={args.output.resolve()}")
    return 0 if report["all_checks_pass"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
