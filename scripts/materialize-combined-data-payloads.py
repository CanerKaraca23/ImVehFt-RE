#!/usr/bin/env python3
"""Materialize planned .rdata/.data bytes from audited candidate COFF sections."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path


EXPECTED_ASI = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"
EXPECTED_CENSUS = "2169C616A721047D0A4F278CB8E35A470DC3F4F184DC8CECEC1B15CDE5C72036"


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def read_section(path: Path, wanted: int) -> tuple[bytes, bytes, int, int, int]:
    data = path.read_bytes()
    machine, count, _, _, _, optional_size, _ = struct.unpack_from("<HHIIIHH", data)
    if machine != 0x14C or not 1 <= wanted <= count:
        raise ValueError(f"{path.name}: invalid i386 COFF section request #{wanted}")
    at = 20 + optional_size + (wanted - 1) * 40
    virtual_size = struct.unpack_from("<I", data, at + 8)[0]
    raw_size, raw_offset = struct.unpack_from("<II", data, at + 16)
    flags = struct.unpack_from("<I", data, at + 36)[0]
    is_bss = bool(flags & 0x00000080)
    if is_bss and raw_offset != 0:
        raise ValueError(f"{path.name}: uninitialized section unexpectedly has raw data")
    if raw_size and not is_bss and raw_offset + raw_size > len(data):
        raise ValueError(f"{path.name}: section #{wanted} exceeds object size")
    raw = data[raw_offset:raw_offset + raw_size] if raw_size and not is_bss else b""
    return data, raw, virtual_size, raw_size, flags


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--original-asi", required=True, type=Path)
    ap.add_argument("--root-census", required=True, type=Path)
    ap.add_argument("--bridge-layout", required=True, type=Path)
    ap.add_argument("--root-closure", required=True, type=Path)
    ap.add_argument("--appended-rdata-layout", required=True, type=Path)
    ap.add_argument("--direct-layout", required=True, type=Path)
    ap.add_argument("--output-rdata", required=True, type=Path)
    ap.add_argument("--output-data", required=True, type=Path)
    ap.add_argument("--output-report", required=True, type=Path)
    args = ap.parse_args()
    for out in (args.output_rdata, args.output_data, args.output_report):
        if out.exists():
            raise FileExistsError(f"refusing to overwrite {out}")
    if digest(args.original_asi.read_bytes()) != EXPECTED_ASI:
        raise ValueError("original ASI hash differs from pinned input")

    census_bytes = args.root_census.read_bytes()
    if digest(census_bytes) != EXPECTED_CENSUS:
        raise ValueError("root census differs from the pinned exact-linkmap 285/420 report")
    census = json.loads(census_bytes)
    bridge = json.loads(args.bridge_layout.read_text(encoding="utf-8"))
    root_closure = json.loads(args.root_closure.read_text(encoding="utf-8"))
    appended = json.loads(args.appended_rdata_layout.read_text(encoding="utf-8"))
    direct = json.loads(args.direct_layout.read_text(encoding="utf-8"))
    if bridge.get("original_asi_sha256") != EXPECTED_ASI:
        raise ValueError("bridge layout is not pinned to the original image")
    if root_closure.get("root_thunk_count") != census.get("thunk_entries"):
        raise ValueError("root local-section closure count differs from current census")
    objects = Path(census["objects_directory"])
    root_object_hashes = {
        int(row["entry_va"], 16): row["object_sha256"] for row in census["entries"]
    }

    rdata_size = int(appended["summary"]["final_rdata_virtual_size"])
    data_size = int(bridge["data_payload_virtual_bytes"])
    expected_rdata_size = int(appended["summary"]["final_rdata_virtual_size"])
    expected_data_size = int(bridge["data_payload_virtual_bytes"])
    if (rdata_size, data_size) != (expected_rdata_size, expected_data_size):
        raise ValueError(f"layout reports .rdata/.data sizes {expected_rdata_size}/{expected_data_size}, got {rdata_size}/{data_size}")
    rdata = bytearray(rdata_size)
    data = bytearray(data_size)
    ranges: dict[str, list[tuple[int, int, str]]] = {".rdata": [], ".data": []}
    chunks: list[dict[str, object]] = []

    def place(section_name: str, offset: int, content: bytes, label: str, expected_hash: str) -> None:
        target = rdata if section_name == ".rdata" else data
        end = offset + len(content)
        if offset < 0 or end > len(target):
            raise ValueError(f"{label}: {section_name} range exceeds final virtual size")
        if any(max(offset, lo) < min(end, hi) for lo, hi, _ in ranges[section_name]):
            raise ValueError(f"{label}: overlaps another {section_name} contribution")
        actual = digest(content)
        if actual != expected_hash.upper():
            raise ValueError(f"{label}: section byte hash mismatch {actual} != {expected_hash}")
        target[offset:end] = content
        ranges[section_name].append((offset, end, label))
        chunks.append({"section": section_name, "label": label, "offset": offset,
                       "size": len(content), "sha256": actual})

    # Root-owned read-only sections share the same object inventory as the roots.
    for row in bridge["rdata_layout"]:
        entry = int(row["source_entry"], 16)
        obj, raw, virtual_size, raw_size, flags = read_section(objects / f"{entry:08x}.obj", int(row["section_number"]))
        if digest(obj) != root_object_hashes.get(entry):
            raise ValueError(f"{entry:#x}: root .rdata object hash mismatch")
        if len(raw) != int(row["size"]) or raw_size != len(raw):
            raise ValueError(f"{entry:#x}: root .rdata raw size mismatch")
        place(".rdata", int(row["payload_offset"]), raw,
              f"root-rdata:{entry:#010x}:{row['section_number']}", row["sha256"])

    # Direct-body local closure contains both code and read-only sections.
    for row in direct["local_section_layout"]:
        if row["section_name"] != ".rdata":
            continue
        entry = int(row["source_entry_va"], 16)
        obj, raw, _, raw_size, _ = read_section(objects / f"{entry:08x}.obj", int(row["section_number"]))
        if digest(obj) != row["object_sha256"] or raw_size != int(row["size"]):
            raise ValueError(f"{entry:#x}: direct .rdata object/size mismatch")
        place(".rdata", int(row["payload_offset"]), raw,
              f"direct-rdata:{entry:#010x}:{row['section_number']}", row["section_sha256"])

    # Two late-discovered literal sections extend rdata after earlier closure bytes.
    for row in appended["additional_closure_rdata_sections"]:
        entry = int(row["source_entry"], 16)
        obj, raw, _, raw_size, _ = read_section(objects / f"{entry:08x}.obj", int(row["section_number"]))
        if digest(obj) != row["object_sha256"] or raw_size != int(row["size"]):
            raise ValueError(f"{entry:#x}: late literal object/size mismatch")
        place(".rdata", int(row["payload_offset"]), raw,
              f"late-rdata:{entry:#010x}:{row['section_number']}", row["section_sha256"])

    for row in bridge["data_local_layout"]:
        entry = int(row["source_entry"], 16)
        obj, raw, virtual_size, raw_size, flags = read_section(objects / f"{entry:08x}.obj", int(row["section_number"]))
        size = int(row["size"])
        if digest(obj) != root_object_hashes.get(entry):
            raise ValueError(f"{entry:#x}: .data/.bss object hash mismatch")
        if row["section_name"] == ".bss":
            if not (flags & 0x80) or raw_size != size or virtual_size != 0:
                raise ValueError(f"{entry:#x}: expected {size}-byte zero-fill BSS")
            content = bytes(size)
        else:
            if raw_size != size:
                raise ValueError(f"{entry:#x}: initialized .data raw size mismatch")
            content = raw
        place(".data", int(row["payload_offset"]), content,
              f"root-{row['section_name']}:{entry:#010x}:{row['section_number']}", row["sha256"])

    expected_root_rdata = len(bridge["rdata_layout"])
    expected_direct_rdata = sum(
        row["section_name"] == ".rdata" for row in direct["local_section_layout"]
    )
    actual_root_rdata = len([x for x in chunks if x["section"] == ".rdata" and x["label"].startswith("root-rdata:")])
    actual_direct_rdata = len([x for x in chunks if x["section"] == ".rdata" and x["label"].startswith("direct-rdata:")])
    if actual_root_rdata != expected_root_rdata:
        raise ValueError(f"expected {expected_root_rdata} appended-root .rdata sections, got {actual_root_rdata}")
    if actual_direct_rdata != expected_direct_rdata:
        raise ValueError(f"expected {expected_direct_rdata} direct-closure .rdata sections, got {actual_direct_rdata}")
    if len([x for x in chunks if x["section"] == ".data" and x["label"].startswith("root-.bss:")]) != 1:
        raise ValueError("expected one zero-filled BSS contribution")
    if len([x for x in chunks if x["section"] == ".data" and x["label"].startswith("root-.data:")]) != 1:
        raise ValueError("expected one initialized .data contribution")

    report = {
        "scope": "Combined planned .rdata/.data contents only; COFF relocation fields are unmodified.",
        "original_asi_sha256": EXPECTED_ASI,
        "rdata_virtual_size": len(rdata), "rdata_sha256": digest(rdata),
        "data_virtual_size": len(data), "data_sha256": digest(data),
        "rdata_chunk_count": len(ranges[".rdata"]), "data_chunk_count": len(ranges[".data"]),
        "all_chunks_non_overlapping": True, "bss_zero_filled": True,
        "coff_fixups_applied": False, "chunks": chunks,
        "limitations": [
            "These are virtual section payloads, not PE/ASI bytes.",
            "Relocations in .rdata/.data are not applied.",
            "No loader or in-game test has been performed.",
        ],
    }
    for path, content in ((args.output_rdata, rdata), (args.output_data, data)):
        path.parent.mkdir(parents=True, exist_ok=True)
        with path.open("xb") as stream:
            stream.write(content)
    args.output_report.parent.mkdir(parents=True, exist_ok=True)
    with args.output_report.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    print(json.dumps({k: report[k] for k in (
        "rdata_virtual_size", "rdata_sha256", "data_virtual_size", "data_sha256",
        "rdata_chunk_count", "data_chunk_count", "coff_fixups_applied"
    )}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
