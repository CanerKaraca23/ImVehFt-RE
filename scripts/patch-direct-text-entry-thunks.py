#!/usr/bin/env python3
"""Add planned E9 entry thunks to the copied, direct-body-patched .text."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import struct
from pathlib import Path


IMAGE_BASE = 0x10000000
CODE_RVA = 0x43000
PINNED_ASI = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--original-asi", required=True, type=Path)
    ap.add_argument("--direct-text", required=True, type=Path)
    ap.add_argument("--direct-text-report", required=True, type=Path)
    ap.add_argument("--placement-plan", required=True, type=Path)
    ap.add_argument("--root-census", required=True, type=Path)
    ap.add_argument("--ghidra-entry-xrefs", required=True, type=Path)
    ap.add_argument("--thunk-relocation-audit", required=True, type=Path)
    ap.add_argument("--output-text", required=True, type=Path)
    ap.add_argument("--output-report", required=True, type=Path)
    args = ap.parse_args()
    for output in (args.output_text, args.output_report):
        if output.exists():
            raise FileExistsError(f"refusing to overwrite {output}")

    image = args.original_asi.read_bytes()
    if digest(image) != PINNED_ASI:
        raise ValueError("original ASI hash mismatch")
    plan_bytes = args.placement_plan.read_bytes()
    xref_bytes = args.ghidra_entry_xrefs.read_bytes()
    census_bytes = args.root_census.read_bytes()
    plan = json.loads(plan_bytes)
    census = json.loads(census_bytes)
    direct_report = json.loads(args.direct_text_report.read_text(encoding="utf-8"))
    overlap = json.loads(args.thunk_relocation_audit.read_text(encoding="utf-8"))
    text = bytearray(args.direct_text.read_bytes())
    if digest(text) != direct_report.get("output_text_sha256"):
        raise ValueError("direct-text input hash differs from its report")
    plan_hash = digest(plan_bytes)
    thunk_count = int(plan.get("rel32_thunks_required", -1))
    direct_count = int(plan.get("whole_bodies_fit_bounded_entry_gaps", -1))
    if (plan_hash != census.get("feasibility_sha256")
            or census.get("candidate_entries") != plan.get("candidate_count")
            or census.get("thunk_entries") != thunk_count):
        raise ValueError("placement plan and appended-body census do not match")
    if (direct_report.get("placement_plan_sha256") != plan_hash
            or direct_report.get("direct_body_count") != direct_count
            or direct_report.get("thunk_entry_count_not_patched") != thunk_count):
        raise ValueError("direct-text report does not match the current placement plan")
    if (overlap.get("reference_sha256") != PINNED_ASI
            or overlap.get("entry_count") != thunk_count
            or overlap.get("feasibility_report") is None
            or digest(Path(overlap["feasibility_report"]).read_bytes()) != plan_hash):
        raise ValueError("thunk relocation audit does not describe current placement windows")

    thunks = {int(row["address"], 16): row for row in plan["entries"]
              if row["placement_mode"] == "jmp-rel32-thunk"}
    roots = {int(row["entry_va"], 16): row for row in census["entries"]}
    if len(thunks) != thunk_count or set(thunks) != set(roots):
        raise ValueError("current thunk entries do not match appended root bodies")

    with args.ghidra_entry_xrefs.open(encoding="utf-8-sig", newline="") as stream:
        xrefs = list(csv.DictReader(stream))
    interior = [row for row in xrefs
                if int(row["entry_va"], 16) in thunks and 1 <= int(row["entry_offset"]) <= 4]
    if interior:
        raise ValueError(f"Ghidra snapshot has {len(interior)} interior references into thunk windows")

    pe = struct.unpack_from("<I", image, 0x3C)[0]
    count = struct.unpack_from("<H", image, pe + 6)[0]
    optional_size = struct.unpack_from("<H", image, pe + 20)[0]
    table = pe + 24 + optional_size
    sections = []
    for i in range(count):
        at = table + i * 40
        name = image[at:at + 8].split(b"\0", 1)[0]
        if name == b".text":
            virtual_size, text_rva, raw_size, raw_offset = struct.unpack_from("<IIII", image, at + 8)
            sections.append((text_rva, virtual_size, raw_size, raw_offset))
    if len(sections) != 1:
        raise ValueError("could not identify unique original .text section")
    text_rva, virtual_size, raw_size, raw_offset = sections[0]
    if text_rva != 0x1000 or len(text) != raw_size:
        raise ValueError("direct-text section geometry differs from pinned original")

    direct_ranges = []
    for row in plan["entries"]:
        if row["placement_mode"] != "body-at-entry":
            continue
        lo = int(row["address"], 16) - IMAGE_BASE - text_rva
        hi = lo + int(row["candidate_body_size"])
        direct_ranges.append((lo, hi, row["address"]))

    patched = []
    for entry, row in sorted(thunks.items()):
        site = entry - IMAGE_BASE - text_rva
        body = roots[entry]
        target = IMAGE_BASE + CODE_RVA + int(body["provisional_payload_offset"])
        displacement = target - (entry + 5)
        if not -(1 << 31) <= displacement < (1 << 31):
            raise ValueError(f"E9 target out of range for {entry:#x}")
        if site < 0 or site + 5 > len(text):
            raise ValueError(f"entry thunk at {entry:#x} is outside original .text")
        if any(max(site, lo) < min(site + 5, hi) for lo, hi, _ in direct_ranges):
            raise ValueError(f"entry thunk at {entry:#x} overlaps a direct body")
        original_bytes = bytes(image[raw_offset + site:raw_offset + site + 5])
        text[site:site + 5] = b"\xE9" + struct.pack("<i", displacement)
        patched.append({"entry_va": f"0x{entry:08X}",
                        "target_va": f"0x{target:08X}",
                        "displacement": displacement,
                        "original_bytes": original_bytes.hex(" ").upper(),
                        "text_offset": site})

    report = {
        "scope": f"Copied original .text after {direct_count} direct bodies/{direct_report['direct_fixup_count']} fixups plus {len(patched)} E9 thunks; not a full PE.",
        "original_asi_sha256": PINNED_ASI,
        "placement_plan_sha256": digest(plan_bytes),
        "ghidra_xref_export_sha256": digest(xref_bytes),
        "root_census_sha256": digest(census_bytes),
        "thunk_relocation_audit_sha256": digest(args.thunk_relocation_audit.read_bytes()),
        "direct_body_count": direct_count,
        "entry_thunk_count": len(patched),
        "interior_ghidra_xref_count_in_current_thunks": len(interior),
        "original_text_highlow_overlaps_to_remove_from_reloc_directory": overlap["overlapping_relocation_count"],
        "output_text_sha256": digest(text),
        "limitations": [
            "The Ghidra xref data is a static saved-project snapshot, not proof against runtime-computed references.",
            "This section needs the appended code/data sections and updated base-relocation directory.",
            "No PE/ASI file is emitted and this .text-only artifact must not be loaded into the game.",
        ],
        "entry_thunks": patched,
    }
    args.output_text.parent.mkdir(parents=True, exist_ok=True)
    with args.output_text.open("xb") as stream:
        stream.write(text)
    args.output_report.parent.mkdir(parents=True, exist_ok=True)
    with args.output_report.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    print(json.dumps({k: report[k] for k in (
        "direct_body_count", "entry_thunk_count", "interior_ghidra_xref_count_in_current_thunks",
        "original_text_highlow_overlaps_to_remove_from_reloc_directory", "output_text_sha256"
    )}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
