#!/usr/bin/env python3
"""Assemble the audited candidate code-section chunks without applying fixups."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path


EXPECTED_ASI = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def read_coff_section(path: Path, wanted: int) -> tuple[bytes, str]:
    data = path.read_bytes()
    machine, count, _, _, _, optional_size, _ = struct.unpack_from("<HHIIIHH", data)
    if machine != 0x14C or not 1 <= wanted <= count:
        raise ValueError(f"{path.name}: invalid i386 COFF section request #{wanted}")
    at = 20 + optional_size + (wanted - 1) * 40
    raw_size = struct.unpack_from("<I", data, at + 16)[0]
    raw_offset = struct.unpack_from("<I", data, at + 20)[0]
    if raw_offset + raw_size > len(data):
        raise ValueError(f"{path.name}: section #{wanted} exceeds object size")
    return data[raw_offset:raw_offset + raw_size], digest(data)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--original-asi", required=True, type=Path)
    ap.add_argument("--root-payload", required=True, type=Path)
    ap.add_argument("--root-payload-report", required=True, type=Path)
    ap.add_argument("--bridge-layout", required=True, type=Path)
    ap.add_argument("--root-closure", required=True, type=Path)
    ap.add_argument("--direct-layout", required=True, type=Path)
    ap.add_argument("--cross-object-helpers", required=True, type=Path)
    ap.add_argument("--output-bin", required=True, type=Path)
    ap.add_argument("--output-report", required=True, type=Path)
    args = ap.parse_args()
    for out in (args.output_bin, args.output_report):
        if out.exists():
            raise FileExistsError(f"refusing to overwrite {out}")

    original_hash = digest(args.original_asi.read_bytes())
    if original_hash != EXPECTED_ASI:
        raise ValueError(f"pinned original ASI hash mismatch: {original_hash}")
    root_report = json.loads(args.root_payload_report.read_text(encoding="utf-8"))
    root_payload = args.root_payload.read_bytes()
    bridge_bytes = args.bridge_layout.read_bytes()
    bridge = json.loads(bridge_bytes)
    root_closure = json.loads(args.root_closure.read_text(encoding="utf-8"))
    direct = json.loads(args.direct_layout.read_text(encoding="utf-8"))
    helper_bytes = args.cross_object_helpers.read_bytes()
    helpers = json.loads(helper_bytes)
    if digest(root_payload) != root_report["payload_sha256"]:
        raise ValueError("root payload hash differs from its manifest")
    if root_report.get("fixups_applied") is not False:
        raise ValueError("expected explicitly unrelocated root payload")
    if bridge.get("original_asi_sha256") != EXPECTED_ASI:
        raise ValueError("bridge layout is not pinned to the original ASI")
    if direct.get("inputs", {}).get("original_asi_sha256") != EXPECTED_ASI:
        raise ValueError("direct closure layout is not pinned to the original ASI")

    code_size = int(helpers["summary"]["extended_code_virtual_size"])
    if code_size <= 0 or int(bridge["root_code_bytes_with_body_alignment"]) != len(root_payload):
        raise ValueError("unexpected combined code geometry")
    image = bytearray(code_size)
    written: list[tuple[int, int, str]] = []
    chunks: list[dict[str, object]] = []

    def place(offset: int, content: bytes, label: str, expected_hash: str | None = None) -> None:
        end = offset + len(content)
        if offset < 0 or end > code_size:
            raise ValueError(f"{label}: range {offset:#x}..{end:#x} exceeds xcode")
        if any(max(offset, lo) < min(end, hi) for lo, hi, _ in written):
            raise ValueError(f"{label}: overlaps an existing xcode chunk")
        actual = digest(content)
        if expected_hash and actual != expected_hash.upper():
            raise ValueError(f"{label}: section bytes hash mismatch ({actual})")
        image[offset:end] = content
        written.append((offset, end, label))
        chunks.append({"label": label, "offset": offset, "size": len(content), "sha256": actual})

    place(0, root_payload, f"{root_report['root_count']} appended root bodies", root_report["payload_sha256"])
    objects = Path(bridge["payload_census_sha256"] and root_report["object_directory"])
    root_closure_map = {
        (int(row["source_entry"], 16), int(row["section_number"])): row
        for row in root_closure["sections"]
    }
    for row in bridge["local_xcode_layout"]:
        entry = int(row["source_entry"], 16)
        closure_row = root_closure_map.get((entry, int(row["section_number"])))
        if closure_row is None:
            raise ValueError(f"{entry:#x}: root local-xcode section missing from closure inventory")
        obj = objects / f"{entry:08x}.obj"
        section, obj_hash = read_coff_section(obj, int(row["section_number"]))
        if obj_hash != closure_row["object_sha256"]:
            raise ValueError(f"{entry:#x}: root closure object hash mismatch")
        if len(section) != int(row["size"]):
            raise ValueError(f"{entry:#x}: root closure section size mismatch")
        place(int(row["payload_offset"]), section, f"root-local-xcode:{entry:#010x}", row["sha256"])

    api_path = Path(bridge["api_thunk_payload_file"])
    api_bytes = api_path.read_bytes()
    if len(api_bytes) != int(bridge["api_thunk_payload_bytes"]):
        raise ValueError("root API thunk payload size differs from bridge layout")
    if digest(api_bytes) != bridge["api_thunk_payload_sha256_after_iat_fixups"]:
        raise ValueError("root API thunk payload hash differs from bridge layout")
    place(int(bridge["api_thunk_payload_offset_in_code_section"]), api_bytes,
          f"{bridge['api_thunk_count']} original-IAT API thunks")

    bridge_path = Path(bridge["bridge_payload_file"])
    bridge_payload = bridge_path.read_bytes()
    if len(bridge_payload) != int(bridge["bridge_payload_bytes"]):
        raise ValueError("CRT bridge payload size differs from layout")
    if digest(bridge_payload) != bridge["bridge_payload_sha256_after_original_helper_rel32_fixups"]:
        raise ValueError("CRT bridge hash differs from layout")
    place(int(bridge["bridge_payload_offset"]), bridge_payload, "original CRT helper bridge")

    for thunk in direct["direct_api_thunks"]:
        iat = int(thunk["iat_va"], 16)
        stub = b"\xff\x25" + struct.pack("<I", iat)
        place(int(thunk["payload_offset"]), stub, f"direct-IAT:{thunk['api_name']}")

    for row in direct["local_section_layout"]:
        if row["section_name"] != ".xcode":
            continue
        entry = int(row["source_entry_va"], 16)
        obj = objects / f"{entry:08x}.obj"
        section, obj_hash = read_coff_section(obj, int(row["section_number"]))
        if obj_hash != row["object_sha256"] or len(section) != int(row["size"]):
            raise ValueError(f"{entry:#x}: direct closure object/section mismatch")
        place(int(row["payload_offset"]), section, f"direct-local-xcode:{entry:#010x}", row["section_sha256"])

    for row in helpers["new_xcode_sections"]:
        content = bytes.fromhex(row["bytes_hex"])
        place(int(row["payload_offset"]), content,
              f"cross-object-helper:{row['source_entry']}:{row['section_number']}", row["section_sha256"])

    expected_root_local = len(bridge["local_xcode_layout"])
    expected_direct_local = sum(row["section_name"] == ".xcode" for row in direct["local_section_layout"])
    if len([x for x in chunks if x["label"].startswith("root-local-xcode:")]) != expected_root_local:
        raise ValueError("appended-root local xcode sections are incomplete")
    if len([x for x in chunks if x["label"].startswith("direct-local-xcode:")]) != expected_direct_local:
        raise ValueError("direct-body local xcode sections are incomplete")
    if len(helpers["new_xcode_sections"]) != int(helpers["summary"]["new_xcode_sections"]):
        raise ValueError("cross-object helper section inventory is inconsistent")
    if len([x for x in chunks if x["label"].startswith("direct-IAT:")]) != len(direct["direct_api_thunks"]):
        raise ValueError("direct IAT thunk inventory was not fully materialized")
    if sorted(written)[0][0] != 0 or max(hi for _, hi, _ in written) != code_size:
        raise ValueError("combined code payload does not cover expected outer bounds")

    report = {
        "scope": "Combined planned .xcode raw bytes only; candidate COFF body/closure relocation fields remain unapplied.",
        "original_asi_sha256": original_hash,
        "root_payload_sha256": digest(root_payload),
        "bridge_layout_sha256": digest(bridge_bytes),
        "root_closure_sha256": digest(args.root_closure.read_bytes()),
        "direct_layout_sha256": digest(args.direct_layout.read_bytes()),
        "cross_object_helpers_sha256": digest(helper_bytes),
        "code_virtual_size": code_size,
        "code_payload_sha256": digest(image),
        "verified_chunk_count": len(chunks),
        "gap_bytes_zero_filled": True,
        "coff_fixups_applied": False,
        "chunks": chunks,
        "limitations": [
            "This is a code-section payload, not a complete PE/ASI image.",
            "The copied object relocation fields remain at raw COFF addends.",
            "The companion .rdata/.data payloads and in-place body/entry patches are not included.",
            "No loader or in-game validation has been run.",
        ],
    }
    args.output_bin.parent.mkdir(parents=True, exist_ok=True)
    with args.output_bin.open("xb") as stream:
        stream.write(image)
    with args.output_report.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    print(json.dumps({k: report[k] for k in (
        "code_virtual_size", "code_payload_sha256", "verified_chunk_count", "coff_fixups_applied"
    )}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
