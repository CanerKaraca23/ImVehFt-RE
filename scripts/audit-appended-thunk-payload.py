#!/usr/bin/env python3
"""Read-only census of bodies that need entry thunks if stored in a new PE section."""

from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from collections import Counter
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
FEASIBILITY = ROOT / "audit/entry-trampoline-feasibility-final-current-2026-09-29.json"
OBJECTS = ROOT / "build/recheck/strict-xcode-nogs-o1-1001cb37-add-esp-20260929"
HELPER = ROOT / "scripts/audit-inplace-candidate-relocations.py"
LOCAL_SECTIONS = ROOT / "audit/appended-thunk-relocation-targets-v5-2026-09-29.json"


def load_parser():
    spec = importlib.util.spec_from_file_location("inplace_coff_audit", HELPER)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot load {HELPER}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module.parse_coff


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--objects", type=Path, default=OBJECTS)
    p.add_argument("--feasibility", type=Path, default=FEASIBILITY)
    p.add_argument("--local-sections", type=Path, default=LOCAL_SECTIONS)
    p.add_argument("--output", type=Path, required=True)
    p.add_argument("--expected-thunk-count", type=int, default=147)
    a = p.parse_args()
    if a.output.exists():
        raise FileExistsError(f"refusing to overwrite {a.output}")

    feasibility_bytes = a.feasibility.read_bytes()
    feasibility = json.loads(feasibility_bytes)
    if feasibility.get("candidate_count") != 705:
        raise ValueError("feasibility input is not the complete 705-entry set")
    selected = [row for row in feasibility["entries"] if row["placement_mode"] == "jmp-rel32-thunk"]
    if len(selected) != a.expected_thunk_count:
        raise ValueError(f"expected {a.expected_thunk_count} thunk entries, found {len(selected)}")

    parse_coff = load_parser()
    reloc_types: Counter[str] = Counter()
    body_bytes = 0
    payload_bytes = 0
    object_hashes = hashlib.sha256()
    rows = []
    cursor = 0
    for row in selected:
        entry = int(row["address"], 16)
        object_path = a.objects / f"{entry:08x}.obj"
        body, info = parse_coff(object_path, row["entry_symbol"])
        if len(body) != row["candidate_body_size"]:
            raise ValueError(f"{entry:#x}: COFF size differs from current feasibility input")
        cursor = (cursor + 15) & ~15
        start = cursor
        cursor += len(body)
        body_bytes += len(body)
        for relocation in info["relocations"]:
            reloc_types[relocation["type_name"]] += 1
        object_hashes.update(bytes.fromhex(info["object_sha256"]))
        rows.append({
            "entry_va": f"0x{entry:08X}",
            "symbol": row["entry_symbol"],
            "body_size": len(body),
            "provisional_payload_offset": start,
            "coff_relocation_counts": dict(Counter(x["type_name"] for x in info["relocations"])),
            "dir32_sites": [x["site"] for x in info["relocations"] if x["type_name"] == "DIR32"],
            "rel32_sites": [x["site"] for x in info["relocations"] if x["type_name"] == "REL32"],
            "object_sha256": info["object_sha256"],
        })
    payload_bytes = cursor

    local_sections_bytes = a.local_sections.read_bytes()
    local_sections = json.loads(local_sections_bytes)
    if local_sections.get("thunk_bodies") != a.expected_thunk_count:
        raise ValueError("local section report does not cover the expected thunk bodies")
    data_cursor = payload_bytes
    for section in sorted(local_sections["same_object_rdata_sections_referenced"],
                          key=lambda item: (int(item["source_entry"], 16), int(item["section_number"]))):
        align_log2 = int(section["alignment_log2"])
        if not 1 <= align_log2 <= 14:
            raise ValueError(f"unsupported COFF section alignment encoding {align_log2}")
        alignment = 1 << (align_log2 - 1)
        data_cursor = (data_cursor + alignment - 1) & ~(alignment - 1)
        section["provisional_data_offset"] = data_cursor
        for relocation in section["relocations"]:
            relocation["provisional_payload_site_offset"] = data_cursor + int(relocation["site"])
        data_cursor += int(section["raw_size"])
    total_payload_bytes = data_cursor
    raw_aligned = (total_payload_bytes + 511) & ~511
    section_rva = 0x43000
    section_raw = 0x3C600
    highlow_sites = []
    for row in rows:
        for site in row["dir32_sites"]:
            highlow_sites.append({"rva": f"0x{section_rva + row['provisional_payload_offset'] + site:08X}",
                                  "kind": "body-dir32", "source_entry": row["entry_va"],
                                  "site_offset": site})
    for section in local_sections["same_object_rdata_sections_referenced"]:
        for relocation in section["relocations"]:
            if relocation["type"] == "DIR32":
                offset = int(section["provisional_data_offset"]) + int(relocation["site"])
                highlow_sites.append({"rva": f"0x{section_rva + offset:08X}",
                                      "kind": "local-rdata-dir32", "source_entry": section["source_entry"],
                                      "section_number": section["section_number"],
                                      "site_offset": relocation["site"],
                                      "target_symbol": relocation["target_symbol"]})
    highlow_rvas = [int(row["rva"], 16) for row in highlow_sites]
    if len(highlow_rvas) != len(set(highlow_rvas)):
        raise ValueError("duplicate provisional DIR32 base-relocation site")

    report = {
        "scope": f"Read-only payload and COFF-relocation census for the {len(selected)} entries assigned to appended bodies; this is not a PE builder or relocation verifier.",
        "feasibility_report": str(a.feasibility.resolve()),
        "feasibility_sha256": sha256(feasibility_bytes),
        "objects_directory": str(a.objects.resolve()),
        "local_sections_report": str(a.local_sections.resolve()),
        "local_sections_report_sha256": sha256(local_sections_bytes),
        "object_set_sha256_ordered_by_entry": object_hashes.hexdigest().upper(),
        "candidate_entries": feasibility["candidate_count"],
        "thunk_entries": len(selected),
        "sum_body_bytes": body_bytes,
        "payload_bytes_with_16_byte_body_alignment": payload_bytes,
        "referenced_same_object_rdata_section_count": len(local_sections["same_object_rdata_sections_referenced"]),
        "same_object_rdata_raw_bytes": local_sections["same_object_rdata_raw_bytes_total_if_copied_per_object"],
        "same_object_rdata_alignment_padding_bytes": total_payload_bytes - payload_bytes - int(local_sections["same_object_rdata_raw_bytes_total_if_copied_per_object"]),
        "combined_code_and_rdata_payload_bytes": total_payload_bytes,
        "file_alignment_512_raw_bytes": raw_aligned,
        "provisional_appended_raw_offset": f"0x{section_raw:08X}",
        "provisional_appended_raw_end": f"0x{section_raw + raw_aligned:08X}",
        "provisional_appended_rva": f"0x{section_rva:08X}",
        "estimated_size_of_image_if_payload_only": f"0x{((section_rva + total_payload_bytes + 0xFFF) & ~0xFFF):08X}",
        "coff_body_relocation_type_counts": dict(sorted(reloc_types.items())),
        "local_rdata_relocation_count": local_sections["same_object_rdata_relocation_count"],
        "candidate_highlow_site_count_for_payload": len(highlow_sites),
        "candidate_highlow_sites_for_payload": highlow_sites,
        "local_rdata_payload_map": local_sections["same_object_rdata_sections_referenced"],
        "limitations": [
            "Payload ordering is by ascending original entry VA and is only a deterministic sizing convention.",
            "COFF relocations still need resolving against actual appended symbol addresses and original-image targets.",
            "DIR32 sites require complete HIGHLOW directory entries; original thunk-window relocations must be reconciled.",
            "No PE bytes, source, objects, or original ASI are modified; this does not validate a loadable image.",
        ],
        "entries": rows,
    }
    a.output.parent.mkdir(parents=True, exist_ok=True)
    a.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({k: report[k] for k in (
        "thunk_entries", "sum_body_bytes", "payload_bytes_with_16_byte_body_alignment",
        "referenced_same_object_rdata_section_count", "same_object_rdata_raw_bytes",
        "same_object_rdata_alignment_padding_bytes", "combined_code_and_rdata_payload_bytes",
        "file_alignment_512_raw_bytes", "coff_body_relocation_type_counts",
        "local_rdata_relocation_count", "provisional_appended_raw_end",
        "estimated_size_of_image_if_payload_only", "output"
    ) if k != "output"}, indent=2))
    print(f"report={a.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
