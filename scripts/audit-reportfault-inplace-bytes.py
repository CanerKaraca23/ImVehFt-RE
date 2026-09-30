#!/usr/bin/env python3
"""Resolve 10011724 COFF relocations at the original VA and compare its full body."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import struct
from pathlib import Path

ENTRY = 0x10011724
SIZE = 0x129
BASE = 0x10000000
REF_SHA = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"
TARGETS = {
    "_DAT_10029490": 0x10029490,
    "_FUN_100172cd@0": 0x100172CD,
    "__memset": 0x10016740,
    "_DAT_1002207C": 0x1002207C,
    "_DAT_10022078": 0x10022078,
    "_DAT_10022074": 0x10022074,
    "@__security_check_cookie@4": 0x100172D5,
}


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def parse_coff(data: bytes) -> tuple[bytearray, list[tuple[int, str, int]]]:
    machine, count, _, sym_at, sym_count, optional, _ = struct.unpack_from("<HHIIIHH", data)
    if machine != 0x14C or optional:
        raise ValueError("expected standard x86 COFF object")
    sections = []
    for i in range(count):
        at = 20 + i * 40
        name = data[at:at + 8].split(b"\0", 1)[0].decode("ascii")
        raw_size, raw_at, rel_at = struct.unpack_from("<III", data, at + 16)
        rel_count = struct.unpack_from("<H", data, at + 32)[0]
        sections.append((name, raw_size, raw_at, rel_at, rel_count))
    section = next(row for row in sections if row[0] == ".xcode")
    strings_at = sym_at + sym_count * 18
    strings = data[strings_at:strings_at + struct.unpack_from("<I", data, strings_at)[0]]
    names: dict[int, str] = {}
    i, at = 0, sym_at
    while i < sym_count:
        ent = data[at:at + 18]
        zero, value = struct.unpack_from("<II", ent)
        if zero == 0:
            end = strings.find(b"\0", value)
            name = strings[value:end].decode("ascii")
        else:
            name = ent[:8].split(b"\0", 1)[0].decode("ascii")
        names[i] = name
        aux = ent[17]
        i += 1 + aux
        at += (1 + aux) * 18
    relocs = []
    for i in range(section[4]):
        site, symbol, kind = struct.unpack_from("<IIH", data, section[3] + i * 10)
        relocs.append((site, names[symbol], kind))
    return bytearray(data[section[2]:section[2] + section[1]]), relocs


def original_span(pe: bytes) -> bytes:
    nt = struct.unpack_from("<I", pe, 0x3C)[0]
    nsects = struct.unpack_from("<H", pe, nt + 6)[0]
    opt_size = struct.unpack_from("<H", pe, nt + 20)[0]
    opt = nt + 24
    if pe[nt:nt + 4] != b"PE\0\0" or struct.unpack_from("<H", pe, opt)[0] != 0x10B:
        raise ValueError("expected PE32 reference image")
    image_base = struct.unpack_from("<I", pe, opt + 28)[0]
    table = opt + opt_size
    for i in range(nsects):
        at = table + i * 40
        name = pe[at:at + 8].split(b"\0", 1)[0]
        _, rva, raw_size, raw = struct.unpack_from("<IIII", pe, at + 8)
        if name == b".text":
            off = ENTRY - (image_base + rva)
            if off < 0 or off + SIZE > raw_size:
                raise ValueError("function body is outside initialized .text")
            return pe[raw + off:raw + off + SIZE]
    raise ValueError(".text section missing")


def main() -> int:
    root = Path(__file__).resolve().parents[1]
    owner = root.parents[1]
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--object", required=True, type=Path)
    p.add_argument("--reference", type=Path, default=owner / "ImVehFt.asi")
    p.add_argument("--highlow-sites", type=Path, default=root / "audit/asi-text-highlow-site-owner-correlation-2026-09-27.csv")
    p.add_argument("--output", required=True, type=Path)
    a = p.parse_args()
    if a.output.exists():
        raise FileExistsError(f"refusing to overwrite {a.output}")
    image = a.reference.read_bytes()
    if digest(image) != REF_SHA:
        raise ValueError("reference ASI SHA-256 does not match pinned input")
    body, relocs = parse_coff(a.object.read_bytes())
    if len(body) != SIZE:
        raise ValueError(f"candidate .xcode size {len(body):#x} != expected {SIZE:#x}")
    sites = []
    for offset, symbol, kind in relocs:
        if symbol not in TARGETS:
            raise ValueError(f"unmapped COFF relocation symbol {symbol}")
        target = TARGETS[symbol]
        if kind == 0x0006:  # IMAGE_REL_I386_DIR32
            struct.pack_into("<I", body, offset, target)
        elif kind == 0x0014:  # IMAGE_REL_I386_REL32
            addend = struct.unpack_from("<i", body, offset)[0]
            struct.pack_into("<i", body, offset, target + addend - (ENTRY + offset + 4))
        else:
            raise ValueError(f"unsupported relocation type {kind:#x} at {offset:#x}")
        sites.append({"site_va": f"0x{ENTRY + offset:08X}", "symbol": symbol, "target_va": f"0x{target:08X}", "type": f"0x{kind:04X}"})
    with a.highlow_sites.open(encoding="utf-8-sig", newline="") as stream:
        rows = [r for r in csv.DictReader(stream) if r.get("source_owner_entry", "").lower() == "10011724" and r.get("source_owner_is_candidate", "").lower() == "yes"]
    expected_highlow = sorted(int(r["site_va"], 16) for r in rows)
    actual_highlow = sorted(int(s["site_va"], 16) for s in sites if s["type"] == "0x0006")
    if actual_highlow != expected_highlow:
        raise ValueError(f"HIGHLOW sites differ: candidate={actual_highlow!r} reference={expected_highlow!r}")
    original = original_span(image)
    mismatches = [i for i, (candidate, reference) in enumerate(zip(body, original)) if candidate != reference]
    report = {
        "scope": "single-function COFF relocation resolution and exact in-place byte comparison; not runtime or gameplay proof",
        "reference_sha256": digest(image),
        "entry_va": f"0x{ENTRY:08X}",
        "body_size": len(body),
        "candidate_resolved_sha256": digest(body),
        "original_body_sha256": digest(original),
        "byte_identical": body == original,
        "mismatch_offsets": [f"0x{x:03X}" for x in mismatches],
        "relocations": sites,
        "original_highlow_sites": [f"0x{x:08X}" for x in expected_highlow],
    }
    a.output.parent.mkdir(parents=True, exist_ok=True)
    a.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(f"10011724 byte-identical={report['byte_identical']} size=0x{len(body):X} relocs={len(sites)}")
    print(f"report={a.output}")
    return 0 if report["byte_identical"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
