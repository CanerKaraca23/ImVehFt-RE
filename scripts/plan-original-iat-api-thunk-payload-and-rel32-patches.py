#!/usr/bin/env python3
"""Place the verified IAT call thunks and plan all candidate API REL32 fixups."""

from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
import struct
from collections import Counter
from pathlib import Path

import pefile


ROOT = Path(__file__).resolve().parents[1]
RELOC_BUILDER = ROOT / "scripts/build-appended-relocation-directory-probe.py"
PINNED_ASI_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"


def read_text_section(obj: bytes) -> tuple[bytes, dict[str, object]]:
    machine, section_count, _, symbol_at, symbol_count, optional_size, _ = struct.unpack_from("<HHIIIHH", obj)
    if machine != 0x14C or optional_size:
        raise ValueError("expected IA32 COFF object without optional header")
    for index in range(section_count):
        at = 20 + index * 40
        name, _, _, raw_size, raw_at, reloc_at, _, reloc_count, _, _ = struct.unpack_from("<8sIIIIIIHHI", obj, at)
        section_name = name.split(b"\0", 1)[0].decode("ascii", errors="replace")
        if section_name.startswith(".text"):
            return obj[raw_at:raw_at + raw_size], {
                "name": section_name, "raw_size": raw_size, "raw_at": raw_at,
                "reloc_at": reloc_at, "reloc_count": reloc_count,
            }
    raise ValueError("API-thunk COFF object has no .text section")


def load_reloc_helpers():
    spec = importlib.util.spec_from_file_location("reloc_builder", RELOC_BUILDER)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot load relocation utilities: {RELOC_BUILDER}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--original", type=Path, required=True)
    parser.add_argument("--candidate-references", type=Path, required=True)
    parser.add_argument("--placement-plan", type=Path, required=True)
    parser.add_argument("--appended-payload", type=Path, required=True)
    parser.add_argument("--iat-crosswalk", type=Path, required=True)
    parser.add_argument("--thunk-verification", type=Path, required=True)
    parser.add_argument("--thunk-object", type=Path, required=True)
    parser.add_argument("--base-relocation-blob", type=Path, required=True)
    parser.add_argument("--base-relocation-report", type=Path, required=True)
    parser.add_argument("--output-thunk-payload", type=Path, required=True)
    parser.add_argument("--output-relocation-blob", type=Path, required=True)
    parser.add_argument("--output-report", type=Path, required=True)
    args = parser.parse_args()
    for path in (args.output_thunk_payload, args.output_relocation_blob, args.output_report):
        if path.exists():
            raise FileExistsError(f"refusing to overwrite {path}")

    original_bytes = args.original.read_bytes()
    original_sha = hashlib.sha256(original_bytes).hexdigest().upper()
    if original_sha != PINNED_ASI_SHA256:
        raise ValueError("original ASI hash does not match the pinned input")
    pe = pefile.PE(data=original_bytes, fast_load=True)
    image_base = pe.OPTIONAL_HEADER.ImageBase
    original_rdata = next(s for s in pe.sections if s.Name.rstrip(b"\0") == b".rdata")
    original_reloc = next(s for s in pe.sections if s.Name.rstrip(b"\0") == b".reloc")

    references = json.loads(args.candidate_references.read_text(encoding="utf-8"))
    plan = json.loads(args.placement_plan.read_text(encoding="utf-8"))
    payload = json.loads(args.appended_payload.read_text(encoding="utf-8"))
    crosswalk = json.loads(args.iat_crosswalk.read_text(encoding="utf-8"))
    thunk_audit = json.loads(args.thunk_verification.read_text(encoding="utf-8"))
    reloc_audit = json.loads(args.base_relocation_report.read_text(encoding="utf-8"))

    if references["candidate_object_count"] != 705 or plan["candidate_count"] != 705:
        raise ValueError("candidate references/placement plan must cover all 705 functions")
    expected_thunk_entries = sum(
        row.get("placement_mode") == "jmp-rel32-thunk" for row in plan["entries"]
    )
    if payload["thunk_entries"] != expected_thunk_entries:
        raise ValueError(
            "appended payload thunk count does not match the supplied placement plan: "
            f"{payload['thunk_entries']} != {expected_thunk_entries}"
        )
    if len(payload["entries"]) != expected_thunk_entries:
        raise ValueError("appended payload entry rows do not match its thunk count")
    if original_sha != reloc_audit["original_sha256"]:
        raise ValueError("base relocation audit uses a different original image")
    if len(thunk_audit["results"]) != 21 or thunk_audit["dir32_iat_relocations"] != 21:
        raise ValueError("thunk COFF audit does not prove all 21 IAT thunks")

    plan_by_entry = {int(row["address"], 16): row for row in plan["entries"]}
    appended_by_entry = {int(row["entry_va"], 16): row for row in payload["entries"]}
    iat_rows = {row["coff_code_symbol"]: row for row in crosswalk["imports"]
                if row["status"] == "exact-original-iat-match"}
    verified_thunks = {row["code_symbol"]: row for row in thunk_audit["results"]}
    if set(iat_rows) != set(verified_thunks):
        raise ValueError("IAT crosswalk and verified thunk symbol sets differ")

    section_rva = int(payload["provisional_appended_rva"], 16)
    prior_payload_size = int(payload["combined_code_and_rdata_payload_bytes"])
    stub_payload_offset = (prior_payload_size + 15) & ~15
    pad = stub_payload_offset - prior_payload_size
    thunk_object = args.thunk_object.read_bytes()
    thunk_body, thunk_section = read_text_section(thunk_object)
    if len(thunk_body) != thunk_audit["code_bytes"] or len(thunk_body) != 126:
        raise ValueError("COFF thunk section size differs from verified 21 x 6-byte payload")
    thunk_payload = bytearray(thunk_body)
    thunk_rows = []
    for code_symbol, row in sorted(verified_thunks.items(), key=lambda item: int(item[1]["code_offset"], 16)):
        iat_row = iat_rows[code_symbol]
        offset = int(row["code_offset"], 16)
        template = thunk_payload[offset:offset + 6]
        if template != b"\xFF\x25\0\0\0\0":
            raise ValueError(f"unexpected thunk template for {row['unique_thunk_symbol']}")
        iat_va = int(iat_row["iat_va"], 16)
        struct.pack_into("<I", thunk_payload, offset + 2, iat_va)
        thunk_va = image_base + section_rva + stub_payload_offset + offset
        thunk_rows.append({
            "api_code_symbol": code_symbol,
            "thunk_symbol": row["unique_thunk_symbol"],
            "iat_va": f"0x{iat_va:08X}",
            "payload_offset": stub_payload_offset + offset,
            "thunk_rva": f"0x{thunk_va - image_base:08X}",
            "thunk_va": f"0x{thunk_va:08X}",
            "highlow_relocation_rva": f"0x{thunk_va - image_base + 2:08X}",
            "patched_thunk_bytes": (b"\xFF\x25" + struct.pack("<I", iat_va)).hex(" ").upper(),
        })
    thunk_va_by_symbol = {row["api_code_symbol"]: int(row["thunk_va"], 16) for row in thunk_rows}

    patches = []
    mode_counts = Counter()
    min_disp, max_disp = None, None
    for row in references["rel32_references"]:
        entry_va = int(row["candidate_entry"], 16)
        placement = plan_by_entry.get(entry_va)
        if placement is None:
            raise ValueError(f"missing placement row for {entry_va:#x}")
        entry_mode = placement["placement_mode"]
        site_offset = int(row["relocation_site_offset"], 16)
        body_size = int(placement["candidate_body_size"])
        if site_offset <= 0 or site_offset + 4 > body_size:
            raise ValueError(f"REL32 field escapes candidate function body: {entry_va:#x}+{site_offset:#x}")
        if row["bytes_around_relocation_field"] != "E8 00 00 00 00":
            raise ValueError(f"API reference is not a zero-addend CALL rel32: {entry_va:#x}+{site_offset:#x}")
        if entry_mode == "jmp-rel32-thunk":
            payload_entry = appended_by_entry.get(entry_va)
            if payload_entry is None:
                raise ValueError(f"missing appended body payload row for {entry_va:#x}")
            callsite_rva = section_rva + int(payload_entry["provisional_payload_offset"]) + site_offset
            callsite_class = "appended-body"
        elif entry_mode == "body-at-entry":
            callsite_rva = entry_va - image_base + site_offset
            callsite_class = "in-place-body"
        else:
            raise ValueError(f"unsupported function placement mode {entry_mode!r}")
        thunk_va = thunk_va_by_symbol[row["target_code_symbol"]]
        call_next_va = image_base + callsite_rva + 4
        displacement = thunk_va - call_next_va
        if not -(1 << 31) <= displacement < (1 << 31):
            raise ValueError(f"REL32 target out of range: {entry_va:#x}+{site_offset:#x}")
        min_disp = displacement if min_disp is None else min(min_disp, displacement)
        max_disp = displacement if max_disp is None else max(max_disp, displacement)
        mode_counts[callsite_class] += 1
        patches.append({
            "candidate_entry": f"0x{entry_va:08X}",
            "placement_mode": entry_mode,
            "callsite_class": callsite_class,
            "candidate_callsite_rva": f"0x{callsite_rva:08X}",
            "candidate_callsite_va": f"0x{image_base + callsite_rva:08X}",
            "relocation_field_rva": f"0x{callsite_rva:08X}",
            "target_api_symbol": row["target_code_symbol"],
            "replacement_thunk_symbol": row["replacement_thunk_symbol"],
            "replacement_thunk_va": f"0x{thunk_va:08X}",
            "rel32_displacement": displacement,
            "rel32_displacement_u32": f"0x{displacement & 0xFFFFFFFF:08X}",
            "original_instruction": "E8 rel32",
            "object_sha256": row["object_sha256"],
        })

    if len(patches) != references["rel32_reference_count"]:
        raise ValueError("not all candidate API REL32 references were planned")
    highlow_new = {int(row["highlow_relocation_rva"], 16) for row in thunk_rows}
    if len(highlow_new) != 21:
        raise ValueError("duplicate API thunk HIGHLOW relocation sites")

    helpers = load_reloc_helpers()
    base_blob = args.base_relocation_blob.read_bytes()
    if helpers.sha256(base_blob) != reloc_audit["encoded_directory_sha256"]:
        raise ValueError("base relocation blob does not match the current complete audit")
    base_sites = helpers.parse_relocs(base_blob)
    if len(base_sites) != reloc_audit["final_highlow_sites"]:
        raise ValueError("base relocation blob site count differs from its audit")
    overlap = base_sites & highlow_new
    if overlap:
        raise ValueError(f"API thunk HIGHLOW sites overlap prior table: {sorted(overlap)[:4]}")
    final_sites = base_sites | highlow_new
    final_reloc_blob = helpers.encode_relocs(final_sites)
    if helpers.parse_relocs(final_reloc_blob) != final_sites:
        raise AssertionError("expanded relocation table failed exact round-trip")
    if len(final_reloc_blob) > original_reloc.SizeOfRawData or len(final_reloc_blob) > original_reloc.Misc_VirtualSize:
        raise ValueError("expanded relocation table does not fit original .reloc capacity")

    raw_offset = int(payload["provisional_appended_raw_offset"], 16)
    original_size = len(original_bytes)
    if raw_offset != original_size:
        raise ValueError(f"provisional appended raw offset {raw_offset:#x} != original EOF {original_size:#x}")
    appended_size = stub_payload_offset + len(thunk_payload)
    raw_aligned = (appended_size + 511) & ~511
    payload_raw_end = raw_offset + raw_aligned
    report = {
        "scope": "REL32/HIGHLOW integration plan for the 21 verified IAT thunks and every API REL32 reference in the current 705 candidate objects; emits only the 126-byte thunk payload and a standalone expanded relocation blob, not a PE/ASI.",
        "original_sha256": original_sha,
        "candidate_reference_inventory": str(args.candidate_references.resolve()),
        "candidate_object_count": references["candidate_object_count"],
        "candidate_object_hash_digest": references["ordered_object_hash_digest"],
        "placement_plan": str(args.placement_plan.resolve()),
        "appended_payload_census": str(args.appended_payload.resolve()),
        "iat_crosswalk": str(args.iat_crosswalk.resolve()),
        "thunk_coff_audit": str(args.thunk_verification.resolve()),
        "provisional_appended_section_rva": f"0x{section_rva:08X}",
        "provisional_appended_section_raw_offset": f"0x{raw_offset:08X}",
        "original_file_eof": f"0x{original_size:08X}",
        "existing_code_and_rdata_payload_bytes": prior_payload_size,
        "api_thunk_alignment_padding_bytes": pad,
        "api_thunk_payload_offset": stub_payload_offset,
        "api_thunk_payload_bytes": len(thunk_payload),
        "provisional_appended_raw_end": f"0x{payload_raw_end:08X}",
        "api_thunk_count": len(thunk_rows),
        "candidate_api_rel32_patch_count": len(patches),
        "candidate_functions_with_api_rel32_references": len({row["candidate_entry"] for row in patches}),
        "callsites_by_placement": dict(sorted(mode_counts.items())),
        "rel32_min_displacement": min_disp,
        "rel32_max_displacement": max_disp,
        "all_rel32_displacements_in_range": True,
        "base_relocations_before": len(base_sites),
        "new_api_thunk_highlow_sites": len(highlow_new),
        "base_relocations_after": len(final_sites),
        "expanded_relocation_blob_bytes": len(final_reloc_blob),
        "expanded_relocation_roundtrip_exact": True,
        "expanded_relocation_fits_original_section": len(final_reloc_blob) <= min(original_reloc.SizeOfRawData, original_reloc.Misc_VirtualSize),
        "thunks": thunk_rows,
        "rel32_patches": patches,
        "limitations": [
            "Only the standalone 126-byte thunk payload is emitted; 705 candidate bodies are not emitted or patched.",
            "Callsite REL32 values are a deterministic placement plan and have not been written into candidate code bytes.",
            "The provisional appended section RVA/raw placement is inherited from the supplied payload census, not finalized in a PE section table.",
            "The IAT aliases resolve by original .rdata offsets; import-directory retention, all other CRT targets, startup/hooks, and full PE layout remain open.",
            "No ASI was written or loaded; no GTA runtime test was performed.",
        ],
    }
    args.output_thunk_payload.parent.mkdir(parents=True, exist_ok=True)
    args.output_relocation_blob.parent.mkdir(parents=True, exist_ok=True)
    args.output_report.parent.mkdir(parents=True, exist_ok=True)
    with args.output_thunk_payload.open("xb") as stream:
        stream.write(thunk_payload)
    with args.output_relocation_blob.open("xb") as stream:
        stream.write(final_reloc_blob)
    with args.output_report.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    print(json.dumps({key: report[key] for key in (
        "api_thunk_count", "candidate_api_rel32_patch_count",
        "callsites_by_placement", "base_relocations_before", "base_relocations_after",
        "expanded_relocation_blob_bytes", "expanded_relocation_fits_original_section",
    )}, indent=2))
    print(f"thunk_payload={args.output_thunk_payload.resolve()}")
    print(f"relocation_blob={args.output_relocation_blob.resolve()}")
    print(f"report={args.output_report.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
