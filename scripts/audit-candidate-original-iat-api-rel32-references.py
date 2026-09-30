#!/usr/bin/env python3
"""Inventory all 705 candidate COFF references to APIs in the pinned IAT map."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from collections import Counter
from pathlib import Path


REL32 = 0x0014
DIR32 = 0x0006
IMAGE_SCN_MEM_EXECUTE = 0x20000000


def read_name(data: bytes, string_base: int, field: bytes) -> str:
    if field[:4] != b"\0\0\0\0":
        return field.split(b"\0", 1)[0].decode("utf-8", errors="replace")
    offset = struct.unpack_from("<I", field, 4)[0]
    start = string_base + offset
    end = data.find(b"\0", start)
    if end < 0:
        raise ValueError("unterminated COFF name")
    return data[start:end].decode("utf-8", errors="replace")


def read_object(path: Path, api_symbols: set[str]) -> tuple[list[dict[str, object]], list[dict[str, object]], str]:
    data = path.read_bytes()
    if len(data) < 20:
        raise ValueError(f"truncated COFF object: {path}")
    machine, section_count, _, symbol_at, symbol_count, optional_size, _ = struct.unpack_from("<HHIIIHH", data)
    if machine != 0x14C or optional_size != 0:
        raise ValueError(f"expected IA32 COFF object without optional header: {path}")
    sections = []
    for section_index in range(section_count):
        at = 20 + section_index * 40
        name, _, _, raw_size, raw_at, reloc_at, _, reloc_count, _, flags = struct.unpack_from("<8sIIIIIIHHI", data, at)
        sections.append({"name": name.split(b"\0", 1)[0].decode("ascii", errors="replace"),
                         "raw_size": raw_size, "raw_at": raw_at, "reloc_at": reloc_at,
                         "reloc_count": reloc_count, "flags": flags})
    strings_at = symbol_at + symbol_count * 18
    symbols: dict[int, dict[str, object]] = {}
    index = 0
    cursor = symbol_at
    while index < symbol_count:
        record = data[cursor:cursor + 18]
        name = read_name(data, strings_at, record[:8])
        value, section_number, _, storage, aux_count = struct.unpack_from("<IhHBB", record, 8)
        symbols[index] = {"name": name, "value": value, "section": section_number, "storage": storage}
        index += 1 + aux_count
        cursor += (1 + aux_count) * 18

    refs = []
    non_rel32 = []
    for section_number, section in enumerate(sections, start=1):
        if not int(section["flags"]) & IMAGE_SCN_MEM_EXECUTE:
            continue
        for reloc_index in range(int(section["reloc_count"])):
            at = int(section["reloc_at"]) + reloc_index * 10
            site, symbol_index, kind = struct.unpack_from("<IIH", data, at)
            target = symbols.get(symbol_index)
            if target is None or target["name"] not in api_symbols:
                continue
            start = int(section["raw_at"]) + site
            window = data[max(int(section["raw_at"]), start - 1):min(int(section["raw_at"]) + int(section["raw_size"]), start + 4)]
            row = {
                "candidate_entry": path.stem.lower(),
                "coff_section": section["name"],
                "coff_section_number": section_number,
                "relocation_site_offset": f"0x{site:08X}",
                "relocation_type": "REL32" if kind == REL32 else ("DIR32" if kind == DIR32 else f"0x{kind:04X}"),
                "target_code_symbol": target["name"],
                "replacement_thunk_symbol": None,
                "bytes_around_relocation_field": window.hex(" ").upper(),
                "object_sha256": hashlib.sha256(data).hexdigest().upper(),
            }
            if kind == REL32:
                api, stack = target["name"][1:].rsplit("@", 1)
                row["replacement_thunk_symbol"] = f"IVF_API_CALL_{api}_{stack}"
                refs.append(row)
            else:
                non_rel32.append(row)
    return refs, non_rel32, hashlib.sha256(data).hexdigest().upper()


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--objects", type=Path, required=True)
    parser.add_argument("--crosswalk", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")
    crosswalk = json.loads(args.crosswalk.read_text(encoding="utf-8"))
    api_symbols = {row["coff_code_symbol"] for row in crosswalk["imports"]
                   if row["status"] == "exact-original-iat-match"}
    objects = sorted(args.objects.glob("*.obj"))
    if len(objects) != 705:
        raise ValueError(f"expected 705 candidate objects, found {len(objects)}")

    references = []
    other_relocations = []
    object_digests = hashlib.sha256()
    for path in objects:
        refs, other, digest = read_object(path, api_symbols)
        object_digests.update(bytes.fromhex(digest))
        references.extend(refs)
        other_relocations.extend(other)
    by_symbol = Counter(row["target_code_symbol"] for row in references)
    by_entry = Counter(row["candidate_entry"] for row in references)
    report = {
        "scope": "Raw COFF relocation inventory for all current candidate executable sections; no REL32 values are rewritten and no image is emitted.",
        "candidate_object_directory": str(args.objects.resolve()),
        "candidate_object_count": len(objects),
        "ordered_object_hash_digest": object_digests.hexdigest().upper(),
        "api_iat_crosswalk": str(args.crosswalk.resolve()),
        "eligible_api_symbol_count": len(api_symbols),
        "rel32_reference_count": len(references),
        "unique_api_symbols_referenced_by_rel32": len(by_symbol),
        "candidate_functions_with_api_rel32_references": len(by_entry),
        "other_relocation_count_to_api_code_symbols": len(other_relocations),
        "rel32_by_api_symbol": dict(sorted(by_symbol.items())),
        "other_relocations": other_relocations,
        "rel32_references": references,
        "limitations": [
            "REL32 sites still require their final target to be the corresponding unique thunk address.",
            "The thunk payload's final RVA and distance from every in-place/appended callsite are not assigned here.",
            "IAT, original .rdata, PE section layout, and production HIGHLOW directory integration are not emitted.",
            "No semantic or runtime behavior is tested.",
        ],
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({key: report[key] for key in (
        "candidate_object_count", "rel32_reference_count", "unique_api_symbols_referenced_by_rel32",
        "candidate_functions_with_api_rel32_references", "other_relocation_count_to_api_code_symbols",
    )}, indent=2))
    print(f"report={args.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
