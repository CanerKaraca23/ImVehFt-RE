#!/usr/bin/env python3
"""Read-only PE header/section-capacity estimate for unresolved moved code bodies."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path

EXPECTED_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"


def align(value: int, unit: int) -> int:
    return (value + unit - 1) // unit * unit


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--reference-pe", required=True, type=Path)
    p.add_argument("--packing-report", required=True, type=Path)
    p.add_argument("--output", required=True, type=Path)
    a = p.parse_args()
    if a.output.exists():
        raise FileExistsError(f"refusing to overwrite {a.output}")
    image = a.reference_pe.read_bytes()
    image_sha = hashlib.sha256(image).hexdigest().upper()
    if image_sha != EXPECTED_SHA256:
        raise ValueError("reference PE SHA-256 does not match pinned ImVehFt.asi")
    nt = struct.unpack_from("<I", image, 0x3C)[0]
    if image[nt:nt + 4] != b"PE\0\0":
        raise ValueError("invalid PE signature")
    section_count = struct.unpack_from("<H", image, nt + 6)[0]
    optional_size = struct.unpack_from("<H", image, nt + 20)[0]
    optional = nt + 24
    if struct.unpack_from("<H", image, optional)[0] != 0x10B:
        raise ValueError("expected PE32")
    section_alignment, file_alignment = struct.unpack_from("<II", image, optional + 32)
    size_image, size_headers = struct.unpack_from("<II", image, optional + 56)
    directories = optional + 96
    number_directories = struct.unpack_from("<I", image, optional + 92)[0]
    security_offset = security_size = 0
    if number_directories > 4:
        security_offset, security_size = struct.unpack_from("<II", image, directories + 4 * 8)
    section_table = optional + optional_size
    sections = []
    first_raw = len(image)
    raw_ends = []
    virtual_ends = []
    for i in range(section_count):
        at = section_table + i * 40
        name = image[at:at + 8].split(b"\0", 1)[0].decode("ascii", errors="replace")
        virtual_size, rva, raw_size, raw_offset = struct.unpack_from("<IIII", image, at + 8)
        if raw_size:
            first_raw = min(first_raw, raw_offset)
            raw_ends.append(raw_offset + raw_size)
        virtual_ends.append(rva + max(virtual_size, raw_size))
        sections.append({
            "name": name, "rva": f"0x{rva:08X}", "virtual_size": virtual_size,
            "raw_size": raw_size, "raw_offset": f"0x{raw_offset:08X}",
        })
    header_end = section_table + section_count * 40
    header_slack = first_raw - header_end
    packing = json.loads(a.packing_report.read_text(encoding="utf-8"))
    unplaced = packing.get("unplaced", [])
    required_bytes = sum(int(row["size"]) for row in unplaced)
    required_raw = align(required_bytes, file_alignment) if required_bytes else 0
    raw_end = max(raw_ends, default=len(image))
    overlay_bytes = max(0, len(image) - raw_end)
    append_raw = align(len(image), file_alignment)
    append_rva = align(max(size_image, max(virtual_ends, default=0)), section_alignment)
    new_size_image = align(append_rva + max(required_bytes, required_raw), section_alignment)
    header_slot_count = header_slack // 40
    report = {
        "scope": "read-only capacity estimate for appending one executable section; does not patch or validate a PE",
        "reference_path": str(a.reference_pe.resolve()),
        "reference_sha256": image_sha,
        "image_bytes": len(image),
        "section_count": section_count,
        "sections": sections,
        "section_alignment": section_alignment,
        "file_alignment": file_alignment,
        "size_of_headers": size_headers,
        "section_table_end": header_end,
        "header_slack_before_first_raw_section": header_slack,
        "additional_40_byte_section_headers_that_fit": header_slot_count,
        "size_of_image_before": size_image,
        "highest_raw_section_end": raw_end,
        "overlay_bytes_after_last_raw_section": overlay_bytes,
        "security_directory_file_offset": security_offset,
        "security_directory_size": security_size,
        "packing_unplaced_entry_count": len(unplaced),
        "packing_unplaced_entries": unplaced,
        "combined_candidate_body_bytes_required": required_bytes,
        "aligned_new_section_raw_size": required_raw,
        "estimated_appended_raw_offset": append_raw,
        "estimated_appended_section_rva": f"0x{append_rva:08X}",
        "estimated_size_of_image_after": f"0x{new_size_image:08X}",
        "one_new_section_header_fits": header_slot_count >= 1,
        "capacity_estimate_succeeded": header_slot_count >= 1 and append_raw >= raw_end and overlay_bytes == 0,
        "limitations": [
            "An available header slot and appended raw range do not prove a loader-valid section-table edit.",
            "The moved functions still need code/data reference, COFF relocation, base-relocation, import, and calling-convention reconciliation.",
            "No bytes, checksum, data directories, or PE fields are modified by this audit.",
        ],
    }
    a.output.parent.mkdir(parents=True, exist_ok=True)
    a.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(f"new_header_slot={report['one_new_section_header_fits']} unplaced_code={required_bytes} aligned_raw={required_raw} append_rva={report['estimated_appended_section_rva']} overlay={overlay_bytes}")
    print(f"report={a.output}")
    return 0 if report["capacity_estimate_succeeded"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
