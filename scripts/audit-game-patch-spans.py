#!/usr/bin/env python3
"""Map FUN_10002210 VirtualProtect write spans into a GTA SA PE image.

This verifies file-backed PE section mapping only. It does not validate patch
signatures, instruction boundaries, game-version compatibility, or behavior.
Uses Python's standard library only.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import struct
import sys
from collections import Counter
from pathlib import Path


SPAN_RE = re.compile(
    r"VP\(\s*(0x[0-9A-Fa-f]+)\s*,\s*([^,]+?)\s*,\s*0x40\s*,"
)


def read_pe(path: Path) -> tuple[bytes, int, int, list[dict[str, int | str]]]:
    data = path.read_bytes()
    if len(data) < 0x40 or data[:2] != b"MZ":
        raise ValueError("input is not a DOS/PE executable")
    pe_offset = struct.unpack_from("<I", data, 0x3C)[0]
    if data[pe_offset : pe_offset + 4] != b"PE\0\0":
        raise ValueError("missing PE signature")

    coff = pe_offset + 4
    machine, section_count = struct.unpack_from("<HH", data, coff)
    optional_size = struct.unpack_from("<H", data, coff + 16)[0]
    optional = coff + 20
    magic = struct.unpack_from("<H", data, optional)[0]
    if magic == 0x10B:
        image_base = struct.unpack_from("<I", data, optional + 28)[0]
    elif magic == 0x20B:
        image_base = struct.unpack_from("<Q", data, optional + 24)[0]
    else:
        raise ValueError(f"unsupported optional-header magic {magic:#x}")

    section_table = optional + optional_size
    sections = []
    for index in range(section_count):
        offset = section_table + index * 40
        name = data[offset : offset + 8].rstrip(b"\0").decode("ascii", "replace")
        virtual_size, virtual_address, raw_size, raw_offset = struct.unpack_from(
            "<IIII", data, offset + 8
        )
        sections.append(
            {
                "name": name,
                "va": virtual_address,
                "virtual_size": virtual_size,
                "raw_size": raw_size,
                "raw_offset": raw_offset,
            }
        )
    return data, machine, image_base, sections


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--exe", required=True, type=Path, help="target gta_sa.exe")
    parser.add_argument(
        "--source",
        type=Path,
        default=Path(__file__).resolve().parents[1] / "src/functions/10002210.cpp",
        help="FUN_10002210 candidate source",
    )
    args = parser.parse_args()

    data, machine, image_base, sections = read_pe(args.exe)
    source = args.source.read_text(encoding="utf-8-sig")
    matches = list(SPAN_RE.finditer(source))
    spans: dict[int, int] = {}
    for match in matches:
        address = int(match.group(1), 16)
        size_text = match.group(2).strip()
        try:
            size = int(size_text, 0)
        except ValueError as exc:
            raise ValueError(
                f"unsupported non-literal span size {size_text!r} at {address:#x}"
            ) from exc
        if size <= 0:
            raise ValueError(f"non-positive span size at {address:#x}")
        if address in spans and spans[address] != size:
            raise ValueError(f"conflicting span sizes at {address:#x}")
        spans[address] = size

    records = []
    counts: Counter[str] = Counter()
    for address, size in sorted(spans.items()):
        rva = address - image_base
        section = next(
            (
                section
                for section in sections
                if section["va"] <= rva
                and rva + size <= section["va"] + section["raw_size"]
                and int(section["raw_offset"]) + rva - int(section["va"]) + size
                <= len(data)
            ),
            None,
        )
        record: dict[str, int | str | bool] = {
            "address": f"0x{address:08X}",
            "size": size,
            "file_backed": section is not None,
        }
        if section is not None:
            file_offset = int(section["raw_offset"]) + rva - int(section["va"])
            record["section"] = str(section["name"])
            record["bytes_hex"] = data[file_offset : file_offset + size].hex(" ")
            counts[str(section["name"])] += 1
        else:
            record["section"] = "OUTSIDE_FILE_BACKED_SECTION"
        records.append(record)

    result = {
        "exe": str(args.exe.resolve()),
        "exe_size": len(data),
        "exe_sha256": hashlib.sha256(data).hexdigest().upper(),
        "machine": f"0x{machine:04X}",
        "image_base": f"0x{image_base:X}",
        "source": str(args.source.resolve()),
        "protection_enable_calls": len(matches),
        "unique_write_spans": len(spans),
        "file_backed_span_counts": dict(sorted(counts.items())),
        "all_spans_file_backed": all(bool(row["file_backed"]) for row in records),
        "scope": "PE section mapping only; not signature, semantic, version, or runtime validation",
        "spans": records,
    }
    print(json.dumps(result, indent=2))
    return 0 if result["all_spans_file_backed"] else 2


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, ValueError, struct.error) as error:
        print(f"error: {error}", file=sys.stderr)
        raise SystemExit(2)
