#!/usr/bin/env python3
"""Resolve 100172d5 COFF fixups at its original VA and compare all bytes."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import struct
from pathlib import Path

REF_SHA = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"
OBJ_SHA = "A4AE49E3F111259D2DE6EA7BFC7B1F0F9499EC4744E8B40D29BEB8E741928AB7"
ENTRY = 0x100172D5
BASE = 0x10000000
TARGETS = {"_DAT_10029490": 0x10029490, "____report_gsfailure": 0x1001AE25}


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def candidate_body(obj: bytes) -> tuple[bytearray, list[tuple[int, str, int]]]:
    if sha(obj) != OBJ_SHA:
        raise ValueError("candidate object differs from the pinned strict object")
    machine, count, _, sym_at, sym_count, optional, _ = struct.unpack_from("<HHIIIHH", obj)
    if machine != 0x14C or optional:
        raise ValueError("expected standard x86 COFF")
    sections = []
    for i in range(count):
        at = 20 + i * 40
        name = obj[at:at + 8].split(b"\0", 1)[0].decode("ascii")
        raw_size, raw_at, rel_at = struct.unpack_from("<III", obj, at + 16)
        rel_count = struct.unpack_from("<H", obj, at + 32)[0]
        sections.append((name, raw_size, raw_at, rel_at, rel_count))
    section = next(s for s in sections if s[0] == ".xcode")
    strings_at = sym_at + sym_count * 18
    strings_size = struct.unpack_from("<I", obj, strings_at)[0]
    strings = obj[strings_at:strings_at + strings_size]
    names: dict[int, str] = {}
    i, at = 0, sym_at
    while i < sym_count:
        ent = obj[at:at + 18]
        zero, value = struct.unpack_from("<II", ent)
        if zero == 0:
            end = strings.find(b"\0", value)
            name = strings[value:end].decode("ascii")
        else:
            name = ent[:8].split(b"\0", 1)[0].decode("ascii")
        aux = ent[17]
        names[i] = name
        i += 1 + aux
        at += (1 + aux) * 18
    relocs = []
    for i in range(section[4]):
        site, sym, kind = struct.unpack_from("<IIH", obj, section[3] + 10 * i)
        if sym not in names:
            raise ValueError(f"bad COFF symbol index {sym}")
        relocs.append((site, names[sym], kind))
    return bytearray(obj[section[2]:section[2] + section[1]]), relocs


def text_span(pe: bytes) -> tuple[bytes, int]:
    nt = struct.unpack_from("<I", pe, 0x3C)[0]
    sections = struct.unpack_from("<H", pe, nt + 6)[0]
    opt_size = struct.unpack_from("<H", pe, nt + 20)[0]
    opt = nt + 24
    if pe[nt:nt + 4] != b"PE\0\0" or struct.unpack_from("<H", pe, opt)[0] != 0x10B:
        raise ValueError("expected PE32")
    base = struct.unpack_from("<I", pe, opt + 28)[0]
    table = opt + opt_size
    for i in range(sections):
        at = table + i * 40
        name = pe[at:at + 8].split(b"\0", 1)[0]
        _, rva, raw_size, raw = struct.unpack_from("<IIII", pe, at + 8)
        if name == b".text":
            offset = ENTRY - (base + rva)
            if offset < 0 or offset + 15 > raw_size:
                raise ValueError("checker is outside initialized .text")
            return pe[raw + offset:raw + offset + 15], base
    raise ValueError(".text missing")


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--object", required=True, type=Path)
    p.add_argument("--reference", required=True, type=Path)
    p.add_argument("--ghidra", required=True, type=Path)
    p.add_argument("--highlow-sites", required=True, type=Path)
    p.add_argument("--output", required=True, type=Path)
    a = p.parse_args()
    if a.output.exists():
        raise FileExistsError(f"refusing to overwrite {a.output}")
    original = a.reference.read_bytes()
    if sha(original) != REF_SHA:
        raise ValueError("reference ASI hash mismatch")
    ghidra = json.loads(a.ghidra.read_text(encoding="utf-8"))
    callees = {row["name"]: int(row["addr"], 16) for row in ghidra["callees"]}
    if callees.get("___report_gsfailure") != TARGETS["____report_gsfailure"]:
        raise ValueError("Ghidra failure-handler address does not match target map")
    body, relocs = candidate_body(a.object.read_bytes())
    if len(body) != 15 or len(relocs) != 2:
        raise ValueError(f"unexpected xcode size/fixup count {len(body)}/{len(relocs)}")
    fixups = []
    for site, symbol, kind in relocs:
        if symbol not in TARGETS:
            raise ValueError(f"unmapped symbol {symbol!r}")
        target = TARGETS[symbol]
        addend = struct.unpack_from("<i", body, site)[0]
        if kind == 0x0006:  # IMAGE_REL_I386_DIR32
            value = target + addend
            struct.pack_into("<I", body, site, value & 0xFFFFFFFF)
            kind_name = "DIR32"
        elif kind == 0x0014:  # IMAGE_REL_I386_REL32
            value = target + addend - (ENTRY + site + 4)
            struct.pack_into("<i", body, site, value)
            kind_name = "REL32"
        else:
            raise ValueError(f"unsupported relocation type {kind:#x}")
        fixups.append({"site": f"0x{site:02X}", "symbol": symbol,
                       "target_va": f"0x{target:08X}", "type": kind_name})

    original_body, base = text_span(original)
    if base != BASE:
        raise ValueError(f"unexpected image base {base:#x}")
    differences = [i for i, (x, y) in enumerate(zip(original_body, body)) if x != y]
    with a.highlow_sites.open(encoding="utf-8-sig", newline="") as stream:
        sites = sorted(int(row["address"], 16) for row in csv.DictReader(stream)
                       if ENTRY <= int(row["address"], 16) < ENTRY + len(body))
    if sites != [0x100172D7]:
        raise ValueError(f"unexpected in-body HIGHLOW sites: {sites}")
    report = {
        "scope": "resolve the candidate COFF DIR32/REL32 at the original entry VA and compare its full instruction body; no PE is written",
        "reference_sha256": sha(original),
        "object_sha256": sha(a.object.read_bytes()),
        "entry_va": f"0x{ENTRY:08X}",
        "body_size": len(body),
        "fixups": fixups,
        "original_highlow_sites": [f"0x{x:08X}" for x in sites],
        "exact_body_match": not differences,
        "mismatch_offsets": differences,
    }
    a.output.parent.mkdir(parents=True, exist_ok=True)
    with a.output.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    print(json.dumps({k: v for k, v in report.items() if k not in {"fixups", "mismatch_offsets"}}, indent=2))
    print(f"report={a.output.resolve()}")
    return 0 if not differences else 1


if __name__ == "__main__":
    raise SystemExit(main())
