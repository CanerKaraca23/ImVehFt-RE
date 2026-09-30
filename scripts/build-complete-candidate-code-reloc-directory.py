#!/usr/bin/env python3
"""Serialize a PE32 HIGHLOW site set for all planned candidate code bodies."""

from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
import struct
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
BUILDER_PATH = ROOT / "scripts/build-appended-relocation-directory-probe.py"
EXPECTED_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"


def load_builder():
    spec = importlib.util.spec_from_file_location("reloc_blob_builder", BUILDER_PATH)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot import {BUILDER_PATH}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--original", type=Path, required=True)
    ap.add_argument("--placement-plan", type=Path, required=True)
    ap.add_argument("--inplace-reconciliation", type=Path, required=True)
    ap.add_argument("--appended-payload", type=Path, required=True)
    ap.add_argument("--appended-layout-report", type=Path)
    ap.add_argument("--output-bin", type=Path, required=True)
    ap.add_argument("--output-report", type=Path, required=True)
    a = ap.parse_args()
    for path in (a.output_bin, a.output_report):
        if path.exists():
            raise FileExistsError(f"refusing to overwrite {path}")
    util = load_builder()
    image = a.original.read_bytes()
    image_hash = util.sha256(image)
    if image_hash != EXPECTED_SHA256:
        raise ValueError(f"original ASI hash mismatch: {image_hash}")
    peoff = struct.unpack_from("<I", image, 0x3C)[0]
    section_count = struct.unpack_from("<H", image, peoff + 6)[0]
    optional_size = struct.unpack_from("<H", image, peoff + 20)[0]
    opt = peoff + 24
    image_base = struct.unpack_from("<I", image, opt + 28)[0]
    section_alignment, file_alignment = struct.unpack_from("<II", image, opt + 32)
    old_size_image = struct.unpack_from("<I", image, opt + 56)[0]
    reloc_dir = opt + 96 + 5 * 8
    reloc_rva, reloc_size = struct.unpack_from("<II", image, reloc_dir)
    sec_table = opt + optional_size
    sections, raw_ends, meta = [], [], []
    for i in range(section_count):
        at = sec_table + i * 40
        name = image[at:at + 8].split(b"\0", 1)[0].decode("ascii", errors="replace")
        vsize, rva, raw_size, raw_offset = struct.unpack_from("<IIII", image, at + 8)
        sections.append((rva, max(vsize, raw_size), raw_size, raw_offset))
        meta.append({"name": name, "virtual_size": vsize, "rva": rva,
                     "raw_size": raw_size, "raw_offset": raw_offset})
        if raw_size:
            raw_ends.append(raw_offset + raw_size)
    reloc_offset = util.rva_to_offset(image, reloc_rva, image_base, sections)
    original_sites = util.parse_relocs(image[reloc_offset:reloc_offset + reloc_size])
    if len(original_sites) != 4681:
        raise ValueError(f"expected 4681 original HIGHLOW sites, got {len(original_sites)}")

    plan_bytes = a.placement_plan.read_bytes()
    plan = json.loads(plan_bytes)
    inplace = json.loads(a.inplace_reconciliation.read_text(encoding="utf-8"))
    payload_bytes = a.appended_payload.read_bytes()
    payload = json.loads(payload_bytes)
    if plan.get("candidate_count") != 705 or len(plan.get("entries", [])) != 705:
        raise ValueError("expected complete 705-entry plan")
    direct = [row for row in plan["entries"] if row["placement_mode"] == "body-at-entry"]
    thunks = [row for row in plan["entries"] if row["placement_mode"] == "jmp-rel32-thunk"]
    if len(direct) + len(thunks) != 705:
        raise ValueError(f"expected 705 total candidates, got {len(direct) + len(thunks)}")
    in_rows = inplace["results"]
    direct_by_va = {int(row["address"], 16): row for row in direct}
    recon_by_va = {int(row["entry_va"], 16): row for row in in_rows}
    if len(recon_by_va) != len(direct) or set(recon_by_va) != set(direct_by_va):
        raise ValueError("in-place relocation reconciliation does not match all direct placements")
    if inplace["old_highlow_fields_straddling_candidate_body_boundaries"] != 0:
        raise ValueError("in-place bodies still have HIGHLOW fields straddling candidate body ends")
    if payload.get("thunk_entries") != len(thunks):
        raise ValueError("appended payload does not match the planned thunk set")

    def overlaps(site: int, start: int, end: int) -> bool:
        return max(site, start) < min(site + 4, end)

    modified_ranges = []
    for row in direct:
        entry = int(row["address"], 16) - image_base
        end = entry + int(row["candidate_body_size"])
        modified_ranges.append((entry, end, "candidate-body"))
    for row in thunks:
        entry = int(row["address"], 16) - image_base
        modified_ranges.append((entry, entry + 5, "entry-thunk"))
    removed = {site for site in original_sites
               if any(overlaps(site, start, end) for start, end, _ in modified_ranges)}
    added_direct = {
        int(site, 16) - image_base
        for row in in_rows for site in row["candidate_dir32_sites"]
    }
    if len(added_direct) != int(inplace["candidate_dir32_sites_for_fitting_bodies"]):
        raise ValueError("duplicate or inconsistent in-place candidate DIR32 sites")
    added_payload = {int(row["rva"], 16) for row in payload["candidate_highlow_sites_for_payload"]}
    if len(added_payload) != int(payload["candidate_highlow_site_count_for_payload"]):
        raise ValueError("duplicate or inconsistent appended candidate DIR32 sites")
    added_layout: set[int] = set()
    if a.appended_layout_report:
        layout_bytes = a.appended_layout_report.read_bytes()
        layout = json.loads(layout_bytes)
        api_count = int(layout["api_thunk_count"])
        api_offset = int(layout["api_thunk_payload_offset_in_code_section"])
        api_bytes = int(layout["api_thunk_payload_bytes"])
        code_rva = int(layout["provisional_appended_rva"], 16)
        if api_bytes != api_count * 6 or api_count <= 0:
            raise ValueError("unexpected absolute-IAT thunk payload geometry")
        api_payload_path = Path(layout["api_thunk_payload_file"])
        if not api_payload_path.is_absolute():
            api_payload_path = ROOT / api_payload_path
        api_payload = api_payload_path.read_bytes()
        if len(api_payload) != api_bytes:
            raise ValueError("API thunk payload size does not match layout report")
        for i in range(api_count):
            stub = api_payload[i * 6:(i + 1) * 6]
            if stub[:2] != b"\xff\x25":
                raise ValueError(f"API thunk {i} is not an FF 25 absolute indirect jump")
            added_layout.add(code_rva + api_offset + i * 6 + 2)
        if len(added_layout) != api_count:
            raise ValueError("duplicate absolute-IAT thunk relocation sites")
    added = added_direct | added_payload | added_layout
    if len(added) != len(added_direct) + len(added_payload) + len(added_layout):
        raise ValueError("direct and appended candidate relocation sites overlap")
    final_sites = (original_sites - removed) | added
    blob = util.encode_relocs(final_sites)
    if util.parse_relocs(blob) != final_sites:
        raise AssertionError("exact relocation-site serialize/reparse failed")
    reloc_section = next((row for row in meta if row["name"] == ".reloc"), None)
    if reloc_section is None:
        raise ValueError("original PE has no .reloc section")
    if len(blob) > reloc_section["raw_size"] or len(blob) > reloc_section["virtual_size"]:
        raise ValueError("complete candidate-code relocation directory does not fit original .reloc")

    report = {
        "scope": f"HIGHLOW site inventory for {len(direct)} in-place bodies, {len(thunks)} appended bodies/local rdata, and {len(added_layout)} absolute-IAT API thunks when a layout report is supplied; standalone table only, no PE patch emitted.",
        "original_sha256": image_hash,
        "placement_plan": str(a.placement_plan.resolve()),
        "placement_plan_sha256": hashlib.sha256(plan_bytes).hexdigest().upper(),
        "inplace_reconciliation": str(a.inplace_reconciliation.resolve()),
        "appended_payload": str(a.appended_payload.resolve()),
        "appended_layout_report": str(a.appended_layout_report.resolve()) if a.appended_layout_report else None,
        "original_highlow_sites": len(original_sites),
        "modified_original_ranges": {"inplace_candidate_bodies": len(direct), "thunk_entry_windows": len(thunks)},
        "original_highlow_sites_removed_in_modified_ranges": len(removed),
        "inplace_candidate_dir32_sites_added": len(added_direct),
        "appended_code_and_rdata_dir32_sites_added": len(added_payload),
        "absolute_iat_api_thunk_highlow_sites_added": len(added_layout),
        "candidate_highlow_sites_added_total": len(added),
        "final_highlow_sites": len(final_sites),
        "encoded_directory_bytes": len(blob),
        "encoded_directory_sha256": util.sha256(blob),
        "directory_roundtrip_exact": True,
        "original_reloc_directory_rva": f"0x{reloc_rva:08x}",
        "original_reloc_directory_size": reloc_size,
        "original_reloc_section_virtual_size": reloc_section["virtual_size"],
        "original_reloc_section_raw_size": reloc_section["raw_size"],
        "directory_fits_original_reloc_section": len(blob) <= min(reloc_section["virtual_size"], reloc_section["raw_size"]),
        "limitations": [
            "Candidate COFF DIR32 target values must still be applied/resolved at the final addresses; this audit records fixup sites only.",
            "The candidate .data/.rdata providers, import table, entry hooks/startup, PE headers, and final code/data bytes are not emitted or validated here.",
            "The placement plan checks instruction-boundary safety, not full behavioral semantics or every dynamic reference.",
            "No original PE bytes are changed; this is not a loadable ASI and no GTA runtime test was run.",
        ],
    }
    a.output_bin.parent.mkdir(parents=True, exist_ok=True)
    with a.output_bin.open("xb") as f:
        f.write(blob)
    with a.output_report.open("x", encoding="utf-8", newline="\n") as f:
        json.dump(report, f, indent=2)
        f.write("\n")
    print(json.dumps({k: report[k] for k in (
        "original_highlow_sites", "original_highlow_sites_removed_in_modified_ranges",
        "inplace_candidate_dir32_sites_added", "appended_code_and_rdata_dir32_sites_added",
        "absolute_iat_api_thunk_highlow_sites_added", "final_highlow_sites",
        "encoded_directory_bytes", "directory_fits_original_reloc_section"
    )}, indent=2))
    print(f"report={a.output_report.resolve()}")
    print(f"blob={a.output_bin.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
