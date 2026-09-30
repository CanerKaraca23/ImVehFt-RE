#!/usr/bin/env python3
"""Independently verify emitted PE section bytes and inventoried fixup values."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path

import pefile


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def load(path: Path) -> tuple[bytes, dict]:
    raw = path.read_bytes()
    return raw, json.loads(raw)


def number(value: int | str) -> int:
    return int(value, 0) if isinstance(value, str) else int(value)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--original", type=Path, required=True)
    parser.add_argument("--candidate", type=Path, required=True)
    parser.add_argument("--direct-fixups", type=Path, required=True)
    parser.add_argument("--appended-fixups", type=Path, required=True)
    parser.add_argument("--closure-fixups", type=Path, required=True)
    parser.add_argument("--text-report", type=Path, required=True)
    parser.add_argument("--payload-report", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")

    original_hash = sha(args.original.read_bytes())
    direct_raw, direct = load(args.direct_fixups)
    appended_raw, appended = load(args.appended_fixups)
    closure_raw, closure = load(args.closure_fixups)
    text_raw, text_report = load(args.text_report)
    payload_raw, payload_report = load(args.payload_report)
    image = args.candidate.read_bytes()
    candidate_hash = sha(image)
    if direct.get("original_asi_sha256") != original_hash:
        raise ValueError("direct fixup manifest is not based on the supplied original")
    if appended.get("original_asi_sha256") != original_hash or closure.get("original_asi_sha256") != original_hash:
        raise ValueError("payload fixup reports are not based on the supplied original")
    if text_report.get("original_asi_sha256") != original_hash:
        raise ValueError("text report is not based on the supplied original")
    if not (appended.get("all_raw_addends_matched") and appended.get("all_computed_values_rederived")
            and closure.get("all_raw_addends_matched") and closure.get("all_values_rederived")):
        raise ValueError("upstream fixup reports do not attest independent value re-derivation")

    pe = pefile.PE(data=image, fast_load=False)
    sections = {s.Name.rstrip(b"\0").decode("ascii"): s for s in pe.sections}
    groups = []

    def check_group(label: str, rows: list[dict], site_key: str, value_key: str) -> None:
        checked = []
        for row in rows:
            site_rva = number(row[site_key])
            expected = number(row[value_key]) & 0xFFFFFFFF
            offset = pe.get_offset_from_rva(site_rva)
            if offset + 4 > len(image):
                raise ValueError(f"{label}: field at RVA {site_rva:#x} is not file-backed")
            actual = struct.unpack_from("<I", image, offset)[0]
            checked.append((site_rva, expected, actual))
        groups.append((label, checked))

    check_group("direct-bodies", direct["fixups"], "field_rva", "computed_field_value")
    check_group("appended-payload", appended["fixups"], "site_rva", "value")
    check_group("direct-local-closure", closure["fixups"], "site_rva", "computed_field_value")

    seen: set[int] = set()
    summaries = []
    mismatches = []
    for label, fields in groups:
        group_mismatches = []
        for site, expected, actual in fields:
            if site in seen:
                raise ValueError(f"fixup inventories overlap at RVA {site:#x}")
            seen.add(site)
            if expected != actual:
                group_mismatches.append({"rva": hex(site), "expected": hex(expected), "actual": hex(actual)})
        summaries.append({"inventory": label, "fields_checked": len(fields), "mismatches": len(group_mismatches)})
        mismatches.extend(group_mismatches[:10])
    if mismatches:
        raise ValueError(f"candidate fixup bytes differ from manifests: {mismatches[:10]}")

    expected_hashes = {
        ".text": text_report.get("output_text_sha256"),
        ".xcode": payload_report.get("output_xcode_sha256"),
        ".xrdata": payload_report.get("output_rdata_sha256"),
        ".xdata": appended.get("output_data_sha256"),
    }
    section_hashes = {}
    for name, expected_hash in expected_hashes.items():
        section = sections[name]
        raw = image[section.PointerToRawData:section.PointerToRawData + section.SizeOfRawData]
        # The text manifest hashes the complete copied raw section; appended
        # payload manifests hash their virtual content before file padding.
        actual_hash = sha(raw if name == ".text" else raw[:section.Misc_VirtualSize])
        section_hashes[name] = actual_hash
        if actual_hash != expected_hash:
            raise ValueError(f"{name} virtual bytes differ from materialization report: {actual_hash} != {expected_hash}")

    report = {
        "scope": "Independent PE byte-level verification of inventoried relocation values and emitted section payloads; not semantic or runtime validation.",
        "original_asi_sha256": original_hash,
        "candidate_asi_sha256": candidate_hash,
        "manifest_sha256": {
            "direct_fixups": sha(direct_raw), "appended_fixups": sha(appended_raw),
            "closure_fixups": sha(closure_raw), "text_report": sha(text_raw),
            "payload_report": sha(payload_raw),
        },
        "fixup_groups": summaries,
        "unique_fixup_fields_checked": len(seen),
        "field_value_mismatches": 0,
        "section_virtual_byte_sha256": section_hashes,
        "section_payloads_match_reports": True,
        "limitations": ["This does not prove semantic equivalence, successful Windows loading, plugin startup, or GTA behavior."],
    }
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({k: report[k] for k in (
        "candidate_asi_sha256", "fixup_groups", "unique_fixup_fields_checked",
        "field_value_mismatches", "section_payloads_match_reports",
    )}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
