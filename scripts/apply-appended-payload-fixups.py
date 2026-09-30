#!/usr/bin/env python3
"""Apply the audited appended-root fixup manifest to copied section payloads."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path


IMAGE_BASE = 0x10000000
SECTION_BASES = {".xcode": 0x43000, ".rdata": 0x5C000, ".data": 0x5D000}
PINNED_ASI_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def parse_hex(value: str) -> int:
    return int(value, 16)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--original-asi", required=True, type=Path)
    ap.add_argument("--xcode", required=True, type=Path)
    ap.add_argument("--xcode-report", required=True, type=Path)
    ap.add_argument("--rdata", required=True, type=Path)
    ap.add_argument("--data", required=True, type=Path)
    ap.add_argument("--data-report", required=True, type=Path)
    ap.add_argument("--fixups", required=True, type=Path)
    ap.add_argument("--output-xcode", required=True, type=Path)
    ap.add_argument("--output-rdata", required=True, type=Path)
    ap.add_argument("--output-data", required=True, type=Path)
    ap.add_argument("--output-report", required=True, type=Path)
    args = ap.parse_args()
    for output in (args.output_xcode, args.output_rdata, args.output_data, args.output_report):
        if output.exists():
            raise FileExistsError(f"refusing to overwrite {output}")

    original_hash = digest(args.original_asi.read_bytes())
    fixup_bytes = args.fixups.read_bytes()
    if original_hash != PINNED_ASI_SHA256:
        raise ValueError("original ASI does not match pinned reference")
    xcode = bytearray(args.xcode.read_bytes())
    rdata = bytearray(args.rdata.read_bytes())
    data = bytearray(args.data.read_bytes())
    xcode_report = json.loads(args.xcode_report.read_text(encoding="utf-8"))
    data_report = json.loads(args.data_report.read_text(encoding="utf-8"))
    fixups_report = json.loads(fixup_bytes)
    if digest(xcode) != xcode_report.get("code_payload_sha256"):
        raise ValueError("input .xcode payload hash differs from its manifest")
    if digest(rdata) != data_report.get("rdata_sha256") or digest(data) != data_report.get("data_sha256"):
        raise ValueError("input .rdata/.data payload hashes differ from their manifest")
    if fixups_report.get("inputs", {}).get("original_asi") != original_hash:
        raise ValueError("fixup manifest is not based on the pinned original ASI")
    summary = fixups_report.get("summary", {})
    if (len(fixups_report.get("fixups", [])) != summary.get("unique_sites")
            or summary.get("fixups_computed") != summary.get("unique_sites")
            or not fixups_report["summary"].get("all_rel32_in_range")):
        raise ValueError("fixup report is incomplete or fails its REL32 range gate")

    sections = {".xcode": xcode, ".rdata": rdata, ".data": data}
    applied = {"DIR32": 0, "REL32": 0}
    rows = []
    seen: set[tuple[str, int]] = set()
    for row in fixups_report["fixups"]:
        section_name = row["source_section"]
        if section_name not in sections:
            raise ValueError(f"unexpected source section {section_name!r}")
        base_rva = SECTION_BASES[section_name]
        site_rva = parse_hex(row["site_rva"])
        offset = site_rva - base_rva
        target = sections[section_name]
        if offset < 0 or offset + 4 > len(target):
            raise ValueError(f"fixup {row['site_rva']} falls outside {section_name}")
        key = (section_name, offset)
        if key in seen:
            raise ValueError(f"duplicate fixup field {row['site_rva']}")
        seen.add(key)
        kind = row["type"]
        if kind not in applied:
            raise ValueError(f"unsupported relocation type {kind}")
        raw_addend = int(row["raw_addend"])
        expected_original = raw_addend & 0xFFFFFFFF
        observed_original = struct.unpack_from("<I", target, offset)[0]
        if observed_original != expected_original:
            raise ValueError(
                f"raw addend mismatch at {row['site_rva']}: "
                f"payload={observed_original:#010x}, manifest={expected_original:#010x}"
            )
        target_va = parse_hex(row["target_va"])
        if kind == "DIR32":
            value = (target_va + raw_addend) & 0xFFFFFFFF
        else:
            displacement = target_va + raw_addend - (IMAGE_BASE + site_rva + 4)
            if not -(1 << 31) <= displacement < (1 << 31):
                raise ValueError(f"REL32 at {row['site_rva']} is out of signed range")
            value = displacement & 0xFFFFFFFF
        if value != parse_hex(row["computed_field_value"]):
            raise ValueError(f"computed fixup mismatch at {row['site_rva']}")
        struct.pack_into("<I", target, offset, value)
        applied[kind] += 1
        rows.append({"site_rva": row["site_rva"], "section": section_name,
                     "offset": offset, "type": kind, "value": f"0x{value:08X}",
                     "target_class": row["target_class"]})

    expected_counts = {"DIR32": summary.get("dir32_count"), "REL32": summary.get("rel32_count")}
    if applied != expected_counts:
        raise ValueError(f"unexpected applied fixup totals: {applied}")
    report = {
        "scope": f"Applied {len(seen)} audited appended-root/closure/helper fields to copied section payloads only.",
        "original_asi_sha256": original_hash,
        "fixup_manifest_sha256": digest(fixup_bytes),
        "input_xcode_sha256": xcode_report["code_payload_sha256"],
        "input_rdata_sha256": data_report["rdata_sha256"],
        "input_data_sha256": data_report["data_sha256"],
        "applied_dir32": applied["DIR32"], "applied_rel32": applied["REL32"],
        "applied_unique_fields": len(seen),
        "all_raw_addends_matched": True,
        "all_computed_values_rederived": True,
        "output_xcode_sha256": digest(xcode),
        "output_rdata_sha256": digest(rdata),
        "output_data_sha256": digest(data),
        "limitations": [
            "Only the 3,085-field appended plan is applied; direct-body/closure fixups remain separate.",
            "These are section payloads, not a PE/ASI image; PE headers and original entry patches are absent.",
            "No loader or in-game validation has been performed.",
        ],
        "fixups": rows,
    }
    for path, content in ((args.output_xcode, xcode), (args.output_rdata, rdata), (args.output_data, data)):
        path.parent.mkdir(parents=True, exist_ok=True)
        with path.open("xb") as stream:
            stream.write(content)
    args.output_report.parent.mkdir(parents=True, exist_ok=True)
    with args.output_report.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    print(json.dumps({k: report[k] for k in (
        "applied_dir32", "applied_rel32", "applied_unique_fields",
        "all_raw_addends_matched", "all_computed_values_rederived",
        "output_xcode_sha256", "output_data_sha256"
    )}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
