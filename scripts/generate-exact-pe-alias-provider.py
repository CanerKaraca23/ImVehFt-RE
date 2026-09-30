#!/usr/bin/env python3
"""Emit original PE section bytes with only explicitly inventoried aliases."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import struct
from collections import defaultdict
from pathlib import Path


def pe_layout(data: bytes) -> tuple[int, dict[str, dict[str, int]]]:
    if data[:2] != b"MZ":
        raise ValueError("input has no MZ signature")
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    if data[pe : pe + 4] != b"PE\0\0":
        raise ValueError("input has no PE signature")
    machine, count = struct.unpack_from("<HH", data, pe + 4)
    optional_size = struct.unpack_from("<H", data, pe + 20)[0]
    optional = pe + 24
    if machine != 0x14C or struct.unpack_from("<H", data, optional)[0] != 0x10B:
        raise ValueError("expected x86 PE32")
    base = struct.unpack_from("<I", data, optional + 28)[0]
    table = optional + optional_size
    sections: dict[str, dict[str, int]] = {}
    for index in range(count):
        at = table + index * 40
        name = data[at : at + 8].split(b"\0", 1)[0].decode("ascii")
        virtual_size, rva, raw_size, raw_offset = struct.unpack_from("<IIII", data, at + 8)
        sections[name] = {
            "rva": rva,
            "virtual_size": virtual_size,
            "raw_size": raw_size,
            "raw_offset": raw_offset,
        }
    return base, sections


def emit_bytes(lines: list[str], data: bytes) -> None:
    for start in range(0, len(data), 16):
        lines.append("    DB " + ", ".join(f"0{byte:02X}h" for byte in data[start : start + 16]))


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("image", type=Path)
    parser.add_argument("aliases", type=Path, help="CSV with address,symbol columns")
    parser.add_argument("--asm", type=Path, required=True)
    parser.add_argument("--manifest", type=Path, required=True)
    args = parser.parse_args()
    if args.asm.exists() or args.manifest.exists():
        parser.error("refusing to overwrite existing output")

    image = args.image.read_bytes()
    base, sections = pe_layout(image)
    pe_names = (".rdata", ".data")
    masm_names = {".rdata": ".const", ".data": ".data"}
    contents: dict[str, bytes] = {}
    labels: dict[str, dict[int, set[str]]] = {".const": defaultdict(set), ".data": defaultdict(set)}
    for name in pe_names:
        section = sections[name]
        extent = max(section["virtual_size"], section["raw_size"])
        raw = image[section["raw_offset"] : section["raw_offset"] + section["raw_size"]]
        if len(raw) != section["raw_size"]:
            raise ValueError(f"truncated raw section {name}")
        contents[name] = raw + bytes(max(0, extent - len(raw)))

    seen: dict[str, int] = {}
    alias_sections: dict[str, int] = defaultdict(int)
    with args.aliases.open("r", encoding="utf-8-sig", newline="") as stream:
        for row in csv.DictReader(stream):
            va, symbol = int(row["address"], 0), row["symbol"].strip()
            if not symbol or any(char.isspace() for char in symbol) or any(char in symbol for char in ":\r\n"):
                raise ValueError(f"invalid COFF symbol {symbol!r}")
            if symbol in seen and seen[symbol] != va:
                raise ValueError(f"symbol maps to multiple VAs: {symbol}")
            if symbol in seen:
                continue
            for name in pe_names:
                section = sections[name]
                offset = va - (base + section["rva"])
                if 0 <= offset < len(contents[name]):
                    labels[masm_names[name]][offset].add(symbol)
                    seen[symbol] = va
                    alias_sections[name] += 1
                    break
            else:
                raise ValueError(f"alias address is outside original .rdata/.data: {symbol} at {va:#x}")

    if not seen:
        raise ValueError("no valid aliases supplied")
    lines = ["; Diagnostic aliases at exact preferred-base locations in reference PE bytes.",
             "; This object does not reconstruct PE relocations or a loadable image.",
             ".386", ".model flat", "option casemap:none", ""]
    for pe_name in pe_names:
        segment = masm_names[pe_name]
        lines.append(segment)
        cursor = 0
        for offset, names in sorted(labels[segment].items()):
            emit_bytes(lines, contents[pe_name][cursor:offset])
            for symbol in sorted(names):
                lines.extend((f"    PUBLIC {symbol}", f"{symbol} LABEL BYTE"))
            cursor = offset
        emit_bytes(lines, contents[pe_name][cursor:])
        lines.append("")
    lines.append("END")

    args.asm.parent.mkdir(parents=True, exist_ok=True)
    args.manifest.parent.mkdir(parents=True, exist_ok=True)
    with args.asm.open("x", encoding="ascii", newline="\n") as stream:
        stream.write("\n".join(lines) + "\n")
    manifest = {
        "scope": "address aliases from input inventory at original preferred-base locations and reference PE bytes; no COFF relocations, runtime image proof, or vtable/ABI proof",
        "image": str(args.image.resolve()),
        "image_sha256": hashlib.sha256(image).hexdigest(),
        "alias_inventory": str(args.aliases.resolve()),
        "alias_count": len(seen),
        "aliases_by_section": dict(alias_sections),
        "section_bytes_sha256": {
            name: hashlib.sha256(contents[name]).hexdigest() for name in pe_names
        },
        "assembly_sha256": hashlib.sha256(args.asm.read_bytes()).hexdigest(),
    }
    with args.manifest.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(manifest, stream, indent=2)
        stream.write("\n")
    print(json.dumps(manifest, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
