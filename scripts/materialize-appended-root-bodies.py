#!/usr/bin/env python3
"""Materialize the planned appended root bodies without applying fixups."""

from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
PARSER_PATH = ROOT / "scripts/audit-inplace-candidate-relocations.py"
EXPECTED_ASI = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"
EXPECTED_CENSUS = "2169C616A721047D0A4F278CB8E35A470DC3F4F184DC8CECEC1B15CDE5C72036"


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def load_parser():
    spec = importlib.util.spec_from_file_location("inplace_coff_parser", PARSER_PATH)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot load COFF parser: {PARSER_PATH}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module.parse_coff


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--original-asi", required=True, type=Path)
    parser.add_argument("--census", required=True, type=Path)
    parser.add_argument("--output-bin", required=True, type=Path)
    parser.add_argument("--output-report", required=True, type=Path)
    args = parser.parse_args()
    for output in (args.output_bin, args.output_report):
        if output.exists():
            raise FileExistsError(f"refusing to overwrite {output}")

    original_hash = digest(args.original_asi.read_bytes())
    if original_hash != EXPECTED_ASI:
        raise ValueError(f"original ASI hash mismatch: {original_hash}")
    census_bytes = args.census.read_bytes()
    if digest(census_bytes) != EXPECTED_CENSUS:
        raise ValueError("payload census differs from audited exact-linkmap 285/420 version")
    census = json.loads(census_bytes)
    expected_count = census.get("thunk_entries")
    if (not isinstance(expected_count, int) or expected_count < 1
            or len(census.get("entries", [])) != expected_count
            or census.get("candidate_entries") != 705):
        raise ValueError("appended root census count/schema is inconsistent")

    objects = Path(census["objects_directory"])
    payload_size = int(census["payload_bytes_with_16_byte_body_alignment"])
    payload = bytearray(payload_size)
    parse_coff = load_parser()
    rows = []
    occupied: list[tuple[int, int]] = []
    for row in census["entries"]:
        entry = int(row["entry_va"], 16)
        object_path = objects / f"{entry:08x}.obj"
        body, info = parse_coff(object_path, row["symbol"])
        offset = int(row["provisional_payload_offset"])
        expected_size = int(row["body_size"])
        end = offset + expected_size
        if digest(object_path.read_bytes()) != row["object_sha256"]:
            raise ValueError(f"{entry:#x}: COFF object hash mismatch")
        if len(body) != expected_size or end > payload_size:
            raise ValueError(f"{entry:#x}: body size/range differs from census")
        if any(max(offset, lo) < min(end, hi) for lo, hi in occupied):
            raise ValueError(f"{entry:#x}: root-body placement overlaps another body")
        payload[offset:end] = body
        occupied.append((offset, end))
        rows.append({
            "entry_va": f"0x{entry:08X}",
            "symbol": row["symbol"],
            "object_sha256": info["object_sha256"],
            "payload_offset": offset,
            "body_size": len(body),
            "coff_relocation_count": len(info["relocations"]),
            "body_sha256": digest(body),
        })

    if len(rows) != expected_count or len(occupied) != expected_count:
        raise AssertionError("not all planned root bodies were materialized")
    report = {
        "scope": f"Raw, unrelocated .xcode bodies for {expected_count} appended roots; alignment gaps are zero-filled.",
        "original_asi_sha256": original_hash,
        "census_sha256": digest(census_bytes),
        "object_directory": str(objects),
        "root_count": len(rows),
        "payload_bytes": len(payload),
        "payload_sha256": digest(payload),
        "objects_and_body_ranges_verified": True,
        "fixups_applied": False,
        "limitations": [
            "COFF relocation fields retain raw object addends and are not executable as placed.",
            "This payload excludes local closure sections, support/runtime code, and PE headers.",
            "This is not a PE/ASI image and has not been loaded or game-tested.",
        ],
        "entries": rows,
    }
    args.output_bin.parent.mkdir(parents=True, exist_ok=True)
    with args.output_bin.open("xb") as stream:
        stream.write(payload)
    with args.output_report.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    print(json.dumps({key: report[key] for key in (
        "root_count", "payload_bytes", "payload_sha256", "objects_and_body_ranges_verified",
        "fixups_applied"
    )}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
