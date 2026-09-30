#!/usr/bin/env python3
"""Resolve the fputs COFF calls at its original VA and compare the full body."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import struct
from pathlib import Path


REFERENCE_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"
OBJECT_SHA256 = "2604C67C9972909FBFD92F5A84E4B612AD3D18E18378CECE4A5753FEADA59D45"
ENTRY = 0x10010913
IMAGE_BASE = 0x10000000
EXPECTED_FIXUP_NAMES = {
    "___SEH_prolog4": "__SEH_prolog4",
    "___SEH_epilog4@0": "__SEH_epilog4",
    "___errno": "__errno",
    "_FUN_1001189f@0": "FUN_1001189f",
    "?__fileno@@YAHPAU_iobuf@@@Z": "__fileno",
    "__strlen": "_strlen",
    "?__lock_file@@YAXPAU_iobuf@@@Z": "__lock_file",
    "___stbuf": "__stbuf",
    "?__fwrite_nolock@@YAIPAXIIPAU_iobuf@@@Z": "__fwrite_nolock",
    "___ftbuf": "__ftbuf",
    "_FUN_10010a11@0": "FUN_10010a11",
}
EXPECTED_HIGHLOW_SITES = [0x10010916, 0x10010978, 0x1001097F, 0x100109A1, 0x100109A8]


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def coff_text(path: Path) -> tuple[bytearray, list[tuple[int, str, int]]]:
    data = path.read_bytes()
    if sha256(data) != OBJECT_SHA256:
        raise ValueError("candidate object hash differs from the audited strict object")
    machine, section_count, _, symbol_at, symbol_count, optional_size, _ = struct.unpack_from(
        "<HHIIIHH", data, 0
    )
    if machine != 0x14C or optional_size != 0:
        raise ValueError("expected a standard x86 COFF object")
    sections = []
    for index in range(section_count):
        at = 20 + index * 40
        name = data[at : at + 8].split(b"\0", 1)[0].decode("ascii")
        raw_size, raw_at, rel_at = struct.unpack_from("<III", data, at + 16)
        rel_count = struct.unpack_from("<H", data, at + 32)[0]
        sections.append((name, raw_size, raw_at, rel_at, rel_count))
    text = next(section for section in sections if section[0] == ".xcode")

    string_at = symbol_at + symbol_count * 18
    string_size = struct.unpack_from("<I", data, string_at)[0]
    string_table = data[string_at : string_at + string_size]
    symbols: dict[int, str] = {}
    index = 0
    cursor = symbol_at
    while index < symbol_count:
        entry = data[cursor : cursor + 18]
        name_prefix, name_suffix = struct.unpack_from("<II", entry, 0)
        if name_prefix == 0:
            end = string_table.find(b"\0", name_suffix)
            name = string_table[name_suffix:end].decode("ascii")
        else:
            name = entry[:8].split(b"\0", 1)[0].decode("ascii")
        aux_count = entry[17]
        symbols[index] = name
        index += 1 + aux_count
        cursor += (1 + aux_count) * 18

    body = bytearray(data[text[2] : text[2] + text[1]])
    relocations = []
    for rel_index in range(text[4]):
        site, symbol_index, kind = struct.unpack_from("<IIH", data, text[3] + rel_index * 10)
        if kind != 0x14:
            raise ValueError(f"unexpected non-REL32 COFF relocation at {site:#x}: {kind:#x}")
        if symbol_index not in symbols:
            raise ValueError(f"relocation refers to unknown COFF symbol index {symbol_index}")
        relocations.append((site, symbols[symbol_index], kind))
    return body, relocations


def original_text_span(image: bytes) -> tuple[bytes, int]:
    pe = struct.unpack_from("<I", image, 0x3C)[0]
    if image[pe : pe + 4] != b"PE\0\0":
        raise ValueError("reference is not a PE image")
    section_count = struct.unpack_from("<H", image, pe + 6)[0]
    optional_size = struct.unpack_from("<H", image, pe + 20)[0]
    optional = pe + 24
    if struct.unpack_from("<H", image, optional)[0] != 0x10B:
        raise ValueError("expected PE32")
    base = struct.unpack_from("<I", image, optional + 28)[0]
    section_table = optional + optional_size
    for index in range(section_count):
        at = section_table + index * 40
        name = image[at : at + 8].split(b"\0", 1)[0]
        virtual_size, rva, raw_size, raw_at = struct.unpack_from("<IIII", image, at + 8)
        if name == b".text":
            rva_offset = ENTRY - (base + rva)
            if rva_offset < 0 or rva_offset > raw_size:
                raise ValueError("fputs entry does not lie in initialized .text")
            return image[raw_at + rva_offset : raw_at + rva_offset + 0x1000], base
    raise ValueError("reference .text section not found")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path, required=True)
    parser.add_argument("--reference", type=Path, required=True)
    parser.add_argument("--ghidra", type=Path, required=True)
    parser.add_argument("--highlow-sites", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")

    reference = args.reference.read_bytes()
    if sha256(reference) != REFERENCE_SHA256:
        raise ValueError("reference ASI SHA-256 differs from the pinned original")
    ghidra = json.loads(args.ghidra.read_text(encoding="utf-8"))
    callees = {row["name"]: int(row["addr"], 16) for row in ghidra["callees"]}
    body, relocations = coff_text(args.object)
    if len(body) != 251 or len(relocations) != 11:
        raise ValueError(f"unexpected fputs body/fixup count: {len(body)}/{len(relocations)}")

    resolved = []
    for site, symbol, _ in relocations:
        if symbol not in EXPECTED_FIXUP_NAMES:
            raise ValueError(f"no Ghidra target mapping for candidate symbol {symbol!r}")
        ghidra_name = EXPECTED_FIXUP_NAMES[symbol]
        if ghidra_name not in callees:
            raise ValueError(f"{ghidra_name} is not listed as a Ghidra callee")
        target = callees[ghidra_name]
        displacement = target - (ENTRY + site + 4)
        struct.pack_into("<i", body, site, displacement)
        resolved.append({"site": f"0x{site:02X}", "coff_symbol": symbol,
                         "ghidra_target": ghidra_name, "target_va": f"0x{target:08X}",
                         "rel32": displacement})

    reference_span, base = original_text_span(reference)
    if base != IMAGE_BASE:
        raise ValueError(f"unexpected preferred image base: {base:#x}")
    original_body = reference_span[:len(body)]
    mismatch_offsets = [i for i, (left, right) in enumerate(zip(original_body, body))
                        if left != right]

    with args.highlow_sites.open(encoding="utf-8-sig", newline="") as stream:
        highlow = sorted(int(row["address"], 16) for row in csv.DictReader(stream)
                         if ENTRY <= int(row["address"], 16) < ENTRY + len(body))
    if highlow != EXPECTED_HIGHLOW_SITES:
        raise ValueError(f"unexpected HIGHLOW entries in fputs span: {[hex(x) for x in highlow]}")

    report = {
        "scope": "in-memory application of Ghidra-addressed REL32 fixups to the candidate COMDAT, then full raw-byte comparison at the original VA; does not write or load a patched ASI",
        "reference_sha256": sha256(reference),
        "candidate_object_sha256": sha256(args.object.read_bytes()),
        "entry_va": f"0x{ENTRY:08X}",
        "body_size": len(body),
        "rel32_fixup_count": len(resolved),
        "resolved_fixups": resolved,
        "original_highlow_sites_preserved_at_entry": [f"0x{x:08X}" for x in highlow],
        "full_body_exact_match_after_rel32_resolution": not mismatch_offsets,
        "mismatch_offsets": mismatch_offsets,
        "interpretation": "an in-place patch that retains the original relocation directory preserves these five existing HIGHLOW entries because the corresponding absolute-operand bytes occupy the same VAs; relocation-directory retention must still be verified by any final PE writer",
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    print(json.dumps({key: value for key, value in report.items()
                      if key not in {"resolved_fixups", "mismatch_offsets"}}, indent=2))
    print(f"report={args.output.resolve()}")
    return 0 if not mismatch_offsets else 1


if __name__ == "__main__":
    raise SystemExit(main())
