#!/usr/bin/env python3
"""Generate an initialized MASM data provider from an exact ImVehFt PE.

This preserves original preferred-base .rdata/.data bytes and zero-fill
initialization while placing unresolved DAT_* COFF aliases at matching
section-relative offsets. It does not retarget internal pointers or make a
loadable plugin.
"""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import struct
from collections import defaultdict
from pathlib import Path


def parse_image(path: Path) -> tuple[bytes, int, dict[str, dict[str, int]]]:
    image = path.read_bytes()
    if image[:2] != b"MZ":
        raise ValueError("input has no MZ signature")
    pe_offset = struct.unpack_from("<I", image, 0x3C)[0]
    if image[pe_offset : pe_offset + 4] != b"PE\0\0":
        raise ValueError("input has no PE signature")
    machine, section_count = struct.unpack_from("<HH", image, pe_offset + 4)
    optional_size = struct.unpack_from("<H", image, pe_offset + 20)[0]
    optional = pe_offset + 24
    if machine != 0x14C or struct.unpack_from("<H", image, optional)[0] != 0x10B:
        raise ValueError("expected x86 PE32")
    image_base = struct.unpack_from("<I", image, optional + 28)[0]
    section_table = optional + optional_size
    sections: dict[str, dict[str, int]] = {}
    for index in range(section_count):
        offset = section_table + index * 40
        name = image[offset : offset + 8].split(b"\0", 1)[0].decode("ascii")
        virtual_size, rva, raw_size, raw_offset = struct.unpack_from("<IIII", image, offset + 8)
        sections[name] = {
            "virtual_size": virtual_size,
            "rva": rva,
            "raw_size": raw_size,
            "raw_offset": raw_offset,
        }
    return image, image_base, sections


def emit_bytes(lines: list[str], data: bytes) -> None:
    for start in range(0, len(data), 16):
        chunk = data[start : start + 16]
        lines.append("    DB " + ", ".join(f"0{value:02X}h" for value in chunk))


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("image", type=Path, help="exact original ImVehFt x86 PE")
    parser.add_argument("inventory", type=Path, help="dumpbin-derived DAT_* COFF inventory CSV")
    parser.add_argument("storage", type=Path, help="PE section/storage classification CSV")
    parser.add_argument("--asm", type=Path, required=True, help="new MASM source output")
    parser.add_argument("--manifest", type=Path, required=True, help="new JSON evidence manifest")
    args = parser.parse_args()
    if args.asm.exists() or args.manifest.exists():
        parser.error("refusing to overwrite an existing output")

    image, image_base, pe_sections = parse_image(args.image)
    segment_for = {".rdata": ".const", ".data": ".data"}
    contents: dict[str, bytearray] = {}
    source_hashes: dict[str, str] = {}
    for name in (".rdata", ".data"):
        section = pe_sections[name]
        extent = max(section["virtual_size"], section["raw_size"])
        raw = image[section["raw_offset"] : section["raw_offset"] + section["raw_size"]]
        if len(raw) != section["raw_size"]:
            raise ValueError(f"truncated raw section {name}")
        contents[name] = bytearray(raw + bytes(max(0, extent - len(raw))))
        source_hashes[name] = hashlib.sha256(contents[name]).hexdigest()

    with args.storage.open("r", encoding="utf-8-sig", newline="") as stream:
        storage = {row["address"].upper(): row for row in csv.DictReader(stream)}
    labels: dict[str, dict[int, set[str]]] = {
        ".const": defaultdict(set),
        ".data": defaultdict(set),
    }
    associations: dict[str, tuple[str, int]] = {}
    checked_raw_backed_addresses = 0
    with args.inventory.open("r", encoding="utf-8-sig", newline="") as stream:
        for row in csv.DictReader(stream):
            address = row["address"].upper()
            item = storage.get(address)
            if item is None:
                raise ValueError(f"no PE storage mapping for {address}")
            pe_name = item["section"]
            if pe_name not in contents:
                raise ValueError(f"unsupported PE section for {address}: {pe_name}")
            section = pe_sections[pe_name]
            offset = int(item["rva_in_section"], 16)
            va = int(address, 16)
            if va != image_base + section["rva"] + offset:
                raise ValueError(f"VA/section-offset mismatch for {address}")
            expected_file_offset = section["raw_offset"] + offset
            if item["storage_class"] == "raw-backed":
                if int(item["file_offset"], 16) != expected_file_offset:
                    raise ValueError(f"file-offset mismatch for {address}")
                initial = bytes.fromhex(item["initial_bytes"])
                actual = image[expected_file_offset : expected_file_offset + len(initial)]
                if actual != initial:
                    raise ValueError(f"stored initial bytes mismatch for {address}")
                checked_raw_backed_addresses += 1
            elif item["storage_class"] != "virtual-zero-fill":
                raise ValueError(f"unsupported storage class for {address}: {item['storage_class']}")
            elif any(contents[pe_name][offset : offset + 4]):
                raise ValueError(f"expected loader-zero-filled bytes at {address}")
            segment = segment_for[pe_name]
            undefined = [name for name in row["undefined_symbols"].split(" | ") if name]
            defined = {name for name in row["defined_symbols"].split(" | ") if name}
            for name in undefined:
                if name in defined:
                    continue
                location = (segment, offset)
                previous = associations.get(name)
                if previous is not None and previous != location:
                    raise ValueError(f"COFF external {name} maps to multiple addresses")
                associations[name] = location
                labels[segment][offset].add(name)

    if not associations:
        raise ValueError("inventory contains no unresolved DAT_* symbols")

    lines = [
        "; Generated initialized DAT_* provider from the exact reference PE.",
        "; Preserves preferred-base section bytes and zero fill only.",
        "; Internal PE pointers/relocations are NOT retargeted; not loadable.",
        ".386",
        ".model flat",
        "option casemap:none",
        "",
    ]
    manifest_sections: dict[str, dict[str, object]] = {}
    for pe_name, segment in ((".rdata", ".const"), (".data", ".data")):
        section = pe_sections[pe_name]
        data = bytes(contents[pe_name])
        mapping = labels[segment]
        lines.append(segment)
        cursor = 0
        for label_offset in sorted(mapping):
            if label_offset < cursor or label_offset >= len(data):
                raise ValueError(f"label offset outside {pe_name}: 0x{label_offset:X}")
            emit_bytes(lines, data[cursor:label_offset])
            for name in sorted(mapping[label_offset]):
                lines.append(f"    PUBLIC {name}")
                lines.append(f"{name} LABEL BYTE")
            cursor = label_offset
        emit_bytes(lines, data[cursor:])
        lines.append("")
        manifest_sections[pe_name] = {
            "segment": segment,
            "rva": f"0x{section['rva']:08X}",
            "raw_size": section["raw_size"],
            "virtual_size": section["virtual_size"],
            "emitted_size": len(data),
            "preferred_base_content_sha256": source_hashes[pe_name],
        }
    lines.append("END")

    args.asm.parent.mkdir(parents=True, exist_ok=True)
    args.manifest.parent.mkdir(parents=True, exist_ok=True)
    with args.asm.open("x", encoding="ascii", newline="\n") as stream:
        stream.write("\n".join(lines) + "\n")
    manifest = {
        "scope": "initialized original PE section bytes and DAT_* COFF aliases only; not a relocated or runtime-valid image",
        "input_image": str(args.image.resolve()),
        "input_image_sha256": hashlib.sha256(image).hexdigest(),
        "image_base": f"0x{image_base:08X}",
        "unresolved_decorated_name_count": len(associations),
        "raw_backed_addresses_cross_checked": checked_raw_backed_addresses,
        "sections": manifest_sections,
        "omitted": [
            "base relocation entries are not expressed as COFF relocations",
            "pointers to moved code/data are left at their original preferred-base values",
            "section RVAs, hook targets, entrypoint, and function layout are not reconstructed",
        ],
        "assembly_sha256": hashlib.sha256(args.asm.read_bytes()).hexdigest(),
    }
    with args.manifest.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(manifest, stream, indent=2)
        stream.write("\n")
    print(f"unresolved decorated names: {len(associations)}")
    print(f"raw-backed DAT addresses independently checked: {checked_raw_backed_addresses}")
    print(f"section emitted sizes: .rdata={len(contents['.rdata']):#x} .data={len(contents['.data']):#x}")
    print(f"MASM source: {args.asm.resolve()}")
    print(f"manifest: {args.manifest.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
