#!/usr/bin/env python3
"""Resolve one x86 COFF body's fixups at its pinned original VA and compare PE bytes."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path

REF_SHA = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def parse_coff(data: bytes) -> tuple[bytearray, list[tuple[int, str, int]]]:
    machine, count, _, sym_at, sym_count, optional, _ = struct.unpack_from("<HHIIIHH", data)
    if machine != 0x14C or optional:
        raise ValueError("expected standard x86 COFF object")
    sections = []
    for i in range(count):
        at = 20 + i * 40
        name = data[at:at + 8].split(b"\0", 1)[0].decode("ascii")
        size, raw, reloc = struct.unpack_from("<III", data, at + 16)
        nreloc = struct.unpack_from("<H", data, at + 32)[0]
        sections.append((name, size, raw, reloc, nreloc))
    sec = next(x for x in sections if x[0] == ".xcode")
    str_at = sym_at + sym_count * 18
    strings = data[str_at:str_at + struct.unpack_from("<I", data, str_at)[0]]
    names: dict[int, str] = {}
    idx, at = 0, sym_at
    while idx < sym_count:
        ent = data[at:at + 18]
        zero, value = struct.unpack_from("<II", ent)
        if zero == 0:
            end = strings.find(b"\0", value)
            name = strings[value:end].decode("ascii")
        else:
            name = ent[:8].split(b"\0", 1)[0].decode("ascii")
        aux = ent[17]
        names[idx] = name
        idx += 1 + aux
        at += (1 + aux) * 18
    relocs = []
    for i in range(sec[4]):
        offset, symbol, kind = struct.unpack_from("<IIH", data, sec[3] + i * 10)
        relocs.append((offset, names[symbol], kind))
    return bytearray(data[sec[2]:sec[2] + sec[1]]), relocs


def pe_text(pe: bytes, entry: int, size: int) -> bytes:
    nt = struct.unpack_from("<I", pe, 0x3C)[0]
    nsections = struct.unpack_from("<H", pe, nt + 6)[0]
    opt_size = struct.unpack_from("<H", pe, nt + 20)[0]
    opt = nt + 24
    if pe[nt:nt + 4] != b"PE\0\0" or struct.unpack_from("<H", pe, opt)[0] != 0x10B:
        raise ValueError("expected PE32 reference image")
    base = struct.unpack_from("<I", pe, opt + 28)[0]
    table = opt + opt_size
    for i in range(nsections):
        at = table + i * 40
        name = pe[at:at + 8].split(b"\0", 1)[0]
        _, rva, raw_size, raw = struct.unpack_from("<IIII", pe, at + 8)
        if name == b".text":
            off = entry - (base + rva)
            if off < 0 or off + size > raw_size:
                raise ValueError("requested span is outside initialized .text")
            return pe[raw + off:raw + off + size]
    raise ValueError(".text section missing")


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--object", required=True, type=Path)
    p.add_argument("--reference", required=True, type=Path)
    p.add_argument("--entry", required=True, type=lambda x: int(x, 0))
    p.add_argument("--size", required=True, type=lambda x: int(x, 0))
    p.add_argument("--target", action="append", default=[], help="COFF_SYMBOL=0xVA; repeat per relocation target")
    p.add_argument("--output", required=True, type=Path)
    a = p.parse_args()
    if a.output.exists():
        raise FileExistsError(f"refusing to overwrite {a.output}")
    image = a.reference.read_bytes()
    if sha(image) != REF_SHA:
        raise ValueError("reference ASI SHA-256 mismatch")
    targets = {}
    for item in a.target:
        symbol, value = item.split("=", 1)
        targets[symbol] = int(value, 0)
    body, relocs = parse_coff(a.object.read_bytes())
    if len(body) != a.size:
        raise ValueError(f"candidate .xcode size {len(body):#x} != requested {a.size:#x}")
    details = []
    for offset, symbol, kind in relocs:
        if symbol not in targets:
            raise ValueError(f"unmapped COFF relocation symbol {symbol}")
        target = targets[symbol]
        if kind == 0x0006:
            struct.pack_into("<I", body, offset, target)
        elif kind == 0x0014:
            addend = struct.unpack_from("<i", body, offset)[0]
            struct.pack_into("<i", body, offset, target + addend - (a.entry + offset + 4))
        else:
            raise ValueError(f"unsupported relocation kind {kind:#x}")
        details.append({"site_va": f"0x{a.entry + offset:08X}", "symbol": symbol, "target_va": f"0x{target:08X}", "type": f"0x{kind:04X}"})
    original = pe_text(image, a.entry, a.size)
    mismatches = [i for i, (x, y) in enumerate(zip(body, original)) if x != y]
    report = {
        "scope": "single x86 function body after COFF fixup resolution; not whole-image/runtime proof",
        "reference_sha256": sha(image), "entry_va": f"0x{a.entry:08X}", "body_size": a.size,
        "candidate_resolved_sha256": sha(body), "original_body_sha256": sha(original),
        "byte_identical": body == original, "mismatch_offsets": [f"0x{x:X}" for x in mismatches],
        "relocations": details,
    }
    a.output.parent.mkdir(parents=True, exist_ok=True)
    a.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(f"{a.entry:#010x}: byte-identical={report['byte_identical']} size={a.size:#x} relocations={len(details)}")
    print(f"report={a.output}")
    return 0 if report["byte_identical"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
