#!/usr/bin/env python3
"""Extract unresolved COFF names whose embedded VA lands in PE data.

This produces a reviewable alias inventory only. An address-bearing name is
not by itself proof that the symbol's type, extent, or runtime relocations are
correct; consumers must inspect the emitted inventory and provider limitations.
"""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import re
import struct
from collections import Counter
from pathlib import Path


def parse_sections(image: bytes) -> tuple[int, dict[str, dict[str, int]]]:
    if image[:2] != b"MZ":
        raise ValueError("input has no MZ signature")
    pe = struct.unpack_from("<I", image, 0x3C)[0]
    if image[pe : pe + 4] != b"PE\0\0":
        raise ValueError("input has no PE signature")
    machine, count = struct.unpack_from("<HH", image, pe + 4)
    optional_size = struct.unpack_from("<H", image, pe + 20)[0]
    optional = pe + 24
    if machine != 0x14C or struct.unpack_from("<H", image, optional)[0] != 0x10B:
        raise ValueError("expected x86 PE32")
    base = struct.unpack_from("<I", image, optional + 28)[0]
    table = optional + optional_size
    sections: dict[str, dict[str, int]] = {}
    for i in range(count):
        at = table + i * 40
        name = image[at : at + 8].split(b"\0", 1)[0].decode("ascii")
        virtual_size, rva, raw_size, raw_offset = struct.unpack_from("<IIII", image, at + 8)
        sections[name] = {
            "rva": rva,
            "virtual_size": virtual_size,
            "raw_size": raw_size,
            "raw_offset": raw_offset,
        }
    return base, sections


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("link_log", type=Path)
    parser.add_argument("image", type=Path)
    parser.add_argument("--csv", type=Path, required=True)
    parser.add_argument("--manifest", type=Path, required=True)
    args = parser.parse_args()
    if args.csv.exists() or args.manifest.exists():
        parser.error("refusing to overwrite existing output")

    log = args.link_log.read_bytes().decode("mbcs", errors="replace")
    # Scan linker messages for decorated and C-style external-name tokens.
    # Restrict matching to text after the object-name colon so addresses in
    # object filenames cannot be mistaken for symbols.
    occurrences: Counter[str] = Counter()
    for line in log.splitlines():
        _, separator, message = line.partition(":")
        if not separator:
            continue
        occurrences.update(re.findall(r"[?A-Za-z_$][?A-Za-z0-9_$@]*", message))
    image = args.image.read_bytes()
    base, sections = parse_sections(image)
    aliases: list[dict[str, str | int]] = []
    rejected: list[dict[str, str]] = []
    for symbol, count in sorted(occurrences.items()):
        addresses = set(re.findall(r"(?<![0-9A-Fa-f])([0-9A-Fa-f]{8})(?![0-9A-Fa-f])", symbol))
        if len(addresses) != 1:
            continue
        va = int(next(iter(addresses)), 16)
        target = None
        offset = 0
        for section_name in (".rdata", ".data"):
            section = sections.get(section_name)
            if section is None:
                continue
            offset = va - (base + section["rva"])
            extent = max(section["virtual_size"], section["raw_size"])
            if 0 <= offset < extent:
                target = (section_name, section, offset)
                break
        if target is None:
            continue
        section_name, section, offset = target
        if offset < section["raw_size"]:
            file_offset = section["raw_offset"] + offset
            initial = image[file_offset : file_offset + min(16, section["raw_size"] - offset)].hex(" ").upper()
            storage = "raw-backed"
        else:
            initial = ""
            storage = "virtual-zero-fill"
        aliases.append(
            {
                "address": f"0x{va:08X}",
                "symbol": symbol,
                "section": section_name,
                "offset": f"0x{offset:X}",
                "storage_class": storage,
                "initial_bytes": initial,
                "link_diagnostic_count": count,
            }
        )

    args.csv.parent.mkdir(parents=True, exist_ok=True)
    args.manifest.parent.mkdir(parents=True, exist_ok=True)
    with args.csv.open("x", encoding="utf-8", newline="") as stream:
        writer = csv.DictWriter(stream, fieldnames=list(aliases[0]) if aliases else ["address", "symbol"])
        writer.writeheader()
        writer.writerows(aliases)
    manifest = {
        "scope": "review inventory of unresolved decorated names whose embedded VA falls inside original .rdata/.data; not proof of ABI or runtime relocation correctness",
        "link_log": str(args.link_log.resolve()),
        "link_log_sha256": hashlib.sha256(args.link_log.read_bytes()).hexdigest(),
        "reference_image": str(args.image.resolve()),
        "reference_image_sha256": hashlib.sha256(image).hexdigest(),
        "unique_linker_message_tokens_scanned": len(occurrences),
        "exact_address_bearing_data_aliases": len(aliases),
        "aliases_by_section": dict(Counter(row["section"] for row in aliases)),
        "tokens_without_an_exact_data_alias": len(occurrences) - len(aliases),
    }
    with args.manifest.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(manifest, stream, indent=2)
        stream.write("\n")
    print(json.dumps(manifest, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
