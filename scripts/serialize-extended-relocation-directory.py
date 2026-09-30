#!/usr/bin/env python3
"""Serialize and independently verify a current extended HIGHLOW plan.

This writes only a relocation-table blob and JSON manifest. It does not patch
the original ASI or emit a PE/ASI image.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from collections import defaultdict
from pathlib import Path


PINNED_ASI_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def parse_sites(blob: bytes) -> set[int]:
    result: set[int] = set()
    cursor = 0
    while cursor < len(blob):
        if cursor + 8 > len(blob):
            raise ValueError("truncated relocation block")
        page, size = struct.unpack_from("<II", blob, cursor)
        if size < 8 or size % 4 or cursor + size > len(blob):
            raise ValueError("invalid relocation block size")
        for pos in range(cursor + 8, cursor + size, 2):
            item = struct.unpack_from("<H", blob, pos)[0]
            kind, offset = item >> 12, item & 0xFFF
            if kind == 0:
                continue
            if kind != 3:
                raise ValueError(f"unexpected relocation type {kind}")
            site = page + offset
            if site in result:
                raise ValueError(f"duplicate relocation site {site:#x}")
            result.add(site)
        cursor += size
    return result


def encode_sites(sites: set[int]) -> bytes:
    by_page: dict[int, list[int]] = defaultdict(list)
    for site in sites:
        by_page[site & ~0xFFF].append(site & 0xFFF)
    result = bytearray()
    for page, offsets in sorted(by_page.items()):
        entries = sorted(0x3000 | offset for offset in offsets)
        if len(entries) % 2:
            entries.append(0)
        result.extend(struct.pack("<II", page, 8 + 2 * len(entries)))
        result.extend(struct.pack(f"<{len(entries)}H", *entries))
    return bytes(result)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--original-asi", required=True, type=Path)
    parser.add_argument("--base-blob", required=True, type=Path)
    parser.add_argument("--base-report", required=True, type=Path)
    parser.add_argument("--direct-closure-report", required=True, type=Path)
    parser.add_argument("--appended-relocation-report", required=True, type=Path)
    parser.add_argument("--output-bin", required=True, type=Path)
    parser.add_argument("--output-report", required=True, type=Path)
    args = parser.parse_args()

    for path in (args.output_bin, args.output_report):
        if path.exists():
            raise FileExistsError(f"refusing to overwrite {path}")
    image_hash = hashlib.sha256(args.original_asi.read_bytes()).hexdigest().upper()
    if image_hash != PINNED_ASI_SHA256:
        raise ValueError(f"original ASI hash mismatch: {image_hash}")

    base_bytes = args.base_blob.read_bytes()
    base_report = json.loads(args.base_report.read_text(encoding="utf-8"))
    base_report_bytes = args.base_report.read_bytes()
    direct_bytes = args.direct_closure_report.read_bytes()
    direct = json.loads(direct_bytes)
    appended = json.loads(args.appended_relocation_report.read_text(encoding="utf-8"))
    if base_report.get("encoded_directory_sha256") != sha256(base_bytes):
        raise ValueError("base blob hash does not match its report")
    if appended["inputs"].get("base_relocation_report_sha256") != sha256(base_report_bytes):
        raise ValueError("extended layout references a different base relocation report")
    if appended["inputs"].get("extended_layout_sha256") != sha256(direct_bytes):
        raise ValueError("appended and direct closure plans reference different extended layouts")
    summary = appended["summary"]
    base_count = int(base_report["final_highlow_sites"])
    if (summary.get("base_relocation_site_count") != base_count
            or not summary.get("expanded_relocation_roundtrip_exact")
            or not summary.get("expanded_relocation_fits")):
        raise ValueError("extended layout report does not attest a consistent complete table")

    base_sites = parse_sites(base_bytes)
    added_sites = {int(value, 16) for value in appended["added_highlow_site_rvas"]}
    direct_sites = {int(value, 16) for value in direct["new_highlow_site_rvas"]}
    api_sites = {int(row["highlow_site_rva"], 16) for row in direct["direct_api_thunks"]}
    if len(base_sites) != base_count:
        raise ValueError("base relocation site count differs from its report")
    if (base_sites & added_sites or base_sites & direct_sites or base_sites & api_sites
            or added_sites & direct_sites or added_sites & api_sites or direct_sites & api_sites):
        raise ValueError("relocation-site sets overlap")
    final_sites = base_sites | added_sites | direct_sites | api_sites
    if len(final_sites) != int(summary["expanded_relocation_site_count"]):
        raise ValueError(f"expected {summary['expanded_relocation_site_count']} unique sites, got {len(final_sites)}")

    blob = encode_sites(final_sites)
    if (len(blob) != int(summary["expanded_relocation_blob_bytes"])
            or parse_sites(blob) != final_sites):
        raise ValueError("serialized relocation directory failed exact round-trip")
    capacity = int(summary["original_reloc_section_capacity"])
    if len(blob) > capacity:
        raise ValueError("serialized directory exceeds original .reloc raw capacity")

    report = {
        "scope": "Standalone serialization of the audited extended HIGHLOW site set; no PE/ASI bytes are patched.",
        "original_asi_sha256": image_hash,
        "base_blob_sha256": sha256(base_bytes),
        "direct_closure_report_sha256": sha256(direct_bytes),
        "appended_relocation_report_sha256": sha256(args.appended_relocation_report.read_bytes()),
        "base_site_count": len(base_sites),
        "added_appended_closure_site_count": len(added_sites),
        "added_direct_closure_site_count": len(direct_sites),
        "added_direct_api_thunk_site_count": len(api_sites),
        "unique_site_count": len(final_sites),
        "serialized_bytes": len(blob),
        "sha256": sha256(blob),
        "roundtrip_exact": True,
        "fits_original_reloc_raw_capacity": len(blob) <= capacity,
        "original_reloc_raw_capacity": capacity,
        "limitations": [
            "This is relocation metadata only, not a patched PE or loadable ASI.",
            "It does not validate imports, startup, loader behavior, or in-game semantics.",
        ],
    }
    args.output_bin.parent.mkdir(parents=True, exist_ok=True)
    with args.output_bin.open("xb") as stream:
        stream.write(blob)
    with args.output_report.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    print(json.dumps(report, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
