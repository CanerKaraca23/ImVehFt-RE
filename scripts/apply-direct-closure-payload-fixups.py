#!/usr/bin/env python3
"""Apply the 155 appended direct-closure COFF fixups to copied sections."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from collections import Counter
from pathlib import Path


IMAGE_BASE = 0x10000000
PINNED_ASI = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"
SECTION_BASES = {".xcode": 0x43000, ".rdata": 0x5C000}


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--original-asi", required=True, type=Path)
    ap.add_argument("--xcode", required=True, type=Path)
    ap.add_argument("--rdata", required=True, type=Path)
    ap.add_argument("--appended-fixup-report", required=True, type=Path)
    ap.add_argument("--direct-layout", required=True, type=Path)
    ap.add_argument("--output-xcode", required=True, type=Path)
    ap.add_argument("--output-rdata", required=True, type=Path)
    ap.add_argument("--output-report", required=True, type=Path)
    args = ap.parse_args()
    for output in (args.output_xcode, args.output_rdata, args.output_report):
        if output.exists():
            raise FileExistsError(f"refusing to overwrite {output}")
    if digest(args.original_asi.read_bytes()) != PINNED_ASI:
        raise ValueError("original ASI hash differs from pinned input")

    appended = json.loads(args.appended_fixup_report.read_text(encoding="utf-8"))
    direct_bytes = args.direct_layout.read_bytes()
    direct = json.loads(direct_bytes)
    if direct.get("inputs", {}).get("original_asi_sha256") != PINNED_ASI:
        raise ValueError("direct closure layout is not based on pinned ASI")

    xcode = bytearray(args.xcode.read_bytes())
    rdata = bytearray(args.rdata.read_bytes())
    if digest(xcode) != appended.get("output_xcode_sha256"):
        raise ValueError(".xcode input is not the verified appended-fixup output")
    if digest(rdata) != appended.get("output_rdata_sha256"):
        raise ValueError(".rdata input differs from the appended-fixup output")

    rows = [row for row in direct["fixups"]
            if row.get("source_section", {}).get("section_name") != ".text"]
    expected_rows = int(direct.get("summary", {}).get("local_closure_fixups", len(rows)))
    if len(rows) != expected_rows:
        raise ValueError(f"appended local-closure fixup count mismatch: expected {expected_rows}, got {len(rows)}")
    sections = {".xcode": xcode, ".rdata": rdata}
    seen: set[tuple[str, int]] = set()
    counts: Counter[str] = Counter()
    applied_rows = []
    for row in rows:
        kind = row["relocation_type"]
        if kind not in ("DIR32", "REL32"):
            raise ValueError(f"unsupported fixup type {kind}")
        section = row["source_section"]["section_name"]
        if section not in sections:
            raise ValueError(f"unexpected direct-closure section {section}")
        site_rva = int(row["site_rva"], 16)
        offset = site_rva - SECTION_BASES[section]
        target = sections[section]
        if offset < 0 or offset + 4 > len(target):
            raise ValueError(f"site {site_rva:#x} is outside {section}")
        key = (section, offset)
        if key in seen:
            raise ValueError(f"duplicate direct closure fixup at {site_rva:#x}")
        seen.add(key)
        addend = int(row["raw_addend"])
        current = struct.unpack_from("<I", target, offset)[0]
        if current != (addend & 0xFFFFFFFF):
            raise ValueError(f"raw COFF addend mismatch at {site_rva:#x}")
        target_va = int(row["target_va"], 16)
        if kind == "DIR32":
            value = target_va + addend
            if not 0 <= value <= 0xFFFFFFFF:
                raise ValueError(f"DIR32 out of range at {site_rva:#x}")
        else:
            signed = target_va + addend - (IMAGE_BASE + site_rva + 4)
            if not -(1 << 31) <= signed < (1 << 31):
                raise ValueError(f"REL32 out of range at {site_rva:#x}")
            value = signed & 0xFFFFFFFF
        if value != (int(row["computed_field_value"]) & 0xFFFFFFFF):
            raise ValueError(f"recomputed direct-closure value differs at {site_rva:#x}")
        struct.pack_into("<I", target, offset, value)
        counts[kind] += 1
        applied_rows.append({"site_rva": row["site_rva"], "section": section,
                             "type": kind, "raw_addend": addend,
                             "computed_field_value": f"0x{value:08X}",
                             "origin": row["origin"]})

    expected_counts = Counter(row["relocation_type"] for row in rows)
    if counts != expected_counts:
        raise ValueError(f"unexpected closure fixup counts {dict(counts)}")
    report = {
        "scope": f"Applied the {len(seen)} direct-body local-closure source fixups to copied appended .xcode/.rdata payloads.",
        "original_asi_sha256": PINNED_ASI,
        "direct_layout_sha256": digest(direct_bytes),
        "appended_fixup_report_sha256": digest(args.appended_fixup_report.read_bytes()),
        "input_xcode_sha256": appended["output_xcode_sha256"],
        "input_rdata_sha256": appended["output_rdata_sha256"],
        "applied_unique_fields": len(seen), "counts_by_type": dict(counts),
        "all_raw_addends_matched": True, "all_values_rederived": True,
        "output_xcode_sha256": digest(xcode), "output_rdata_sha256": digest(rdata),
        "limitations": [
            "The 85 source fixups inside original .text are not included here.",
            "No direct-body bytes, PE headers, or entry thunks are patched.",
            "Outputs are section payloads, not a loadable ASI; no runtime test was run.",
        ],
        "fixups": applied_rows,
    }
    for path, content in ((args.output_xcode, xcode), (args.output_rdata, rdata)):
        path.parent.mkdir(parents=True, exist_ok=True)
        with path.open("xb") as stream:
            stream.write(content)
    args.output_report.parent.mkdir(parents=True, exist_ok=True)
    with args.output_report.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    print(json.dumps({k: report[k] for k in (
        "applied_unique_fields", "counts_by_type", "all_raw_addends_matched",
        "all_values_rederived", "output_xcode_sha256", "output_rdata_sha256"
    )}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
