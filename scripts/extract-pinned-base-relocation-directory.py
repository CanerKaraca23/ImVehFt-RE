#!/usr/bin/env python3
"""Extract and verify the exact base-relocation directory from the pinned ASI."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path

import pefile


PINNED_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--asi", type=Path, required=True)
    parser.add_argument("--output-bin", type=Path, required=True)
    parser.add_argument("--output-report", type=Path, required=True)
    args = parser.parse_args()
    for output in (args.output_bin, args.output_report):
        if output.exists():
            raise FileExistsError(f"refusing to overwrite {output}")

    image = args.asi.read_bytes()
    image_sha = sha256(image)
    if image_sha != PINNED_SHA256:
        raise ValueError(f"pinned ASI SHA-256 mismatch: {image_sha}")
    pe = pefile.PE(data=image, fast_load=True)
    if pe.FILE_HEADER.Machine != 0x14C or pe.OPTIONAL_HEADER.Magic != 0x10B:
        raise ValueError("expected pinned PE32 x86 image")
    directory = pe.OPTIONAL_HEADER.DATA_DIRECTORY[5]
    rva, size = int(directory.VirtualAddress), int(directory.Size)
    if not rva or not size:
        raise ValueError("base-relocation directory is absent")
    file_offset = int(pe.get_offset_from_rva(rva))
    blob = image[file_offset:file_offset + size]
    if len(blob) != size:
        raise ValueError("truncated raw-backed base-relocation directory")

    sites: set[int] = set()
    cursor = 0
    entry_count = 0
    while cursor < len(blob):
        if cursor + 8 > len(blob):
            raise ValueError("truncated relocation block")
        page, block_size = struct.unpack_from("<II", blob, cursor)
        if block_size < 8 or block_size % 4 or cursor + block_size > len(blob):
            raise ValueError("invalid relocation block size")
        for at in range(cursor + 8, cursor + block_size, 2):
            item = struct.unpack_from("<H", blob, at)[0]
            kind, offset = item >> 12, item & 0xFFF
            entry_count += 1
            if kind == 0:
                continue
            if kind != 3:
                raise ValueError(f"unsupported original relocation type {kind}")
            site = page + offset
            if site in sites:
                raise ValueError(f"duplicate original HIGHLOW site {site:#x}")
            sites.add(site)
        cursor += block_size
    if cursor != size or len(sites) != 4681:
        raise ValueError(f"unexpected original relocation inventory: {len(sites)} HIGHLOW sites")

    reloc_section = next(
        (section for section in pe.sections if section.Name.rstrip(b"\0") == b".reloc"),
        None,
    )
    if reloc_section is None or size > int(reloc_section.SizeOfRawData):
        raise ValueError("directory does not fit the original .reloc raw section")
    report = {
        "scope": "Exact original base-relocation directory bytes extracted from the pinned ASI; no PE bytes modified.",
        "original_asi_sha256": image_sha,
        "directory_rva": f"0x{rva:08X}",
        "encoded_directory_bytes": size,
        "encoded_directory_sha256": sha256(blob),
        "final_highlow_sites": len(sites),
        "relocation_entries_including_padding": entry_count,
        "original_reloc_section_virtual_size": int(reloc_section.Misc_VirtualSize),
        "original_reloc_section_raw_size": int(reloc_section.SizeOfRawData),
        "raw_file_offset": f"0x{file_offset:08X}",
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
