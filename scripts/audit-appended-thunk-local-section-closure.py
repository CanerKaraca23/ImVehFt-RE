#!/usr/bin/env python3
"""Inventory non-.rdata same-object sections required by appended thunk roots."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from collections import Counter
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
RELOC_NAMES = {0x0006: "DIR32", 0x0014: "REL32", 0x000A: "SECTION", 0x000B: "SECREL"}


def read_name(data: bytes, strings_at: int, field: bytes) -> str:
    if field[:4] != b"\0\0\0\0":
        return field.split(b"\0", 1)[0].decode("utf-8", errors="replace")
    offset = struct.unpack_from("<I", field, 4)[0]
    end = data.find(b"\0", strings_at + offset)
    if end < 0:
        raise ValueError("unterminated COFF string")
    return data[strings_at + offset:end].decode("utf-8", errors="replace")


def inspect_object(path: Path, section_number: int) -> dict[str, object]:
    data = path.read_bytes()
    machine, nsections, _, sym_at, nsymbols, optional, _ = struct.unpack_from("<HHIIIHH", data)
    if machine != 0x14C or optional or not 1 <= section_number <= nsections:
        raise ValueError(f"{path.name}: expected IA-32 COFF and a valid section number")
    sections = []
    for i in range(nsections):
        at = 20 + i * 40
        name, _, _, size, raw, reloc, _, nreloc, _, flags = struct.unpack_from("<8sIIIIIIHHI", data, at)
        sections.append({"name": name.split(b"\0", 1)[0].decode("ascii", errors="replace"),
                         "size": size, "raw": raw, "reloc": reloc, "nreloc": nreloc,
                         "flags": flags})
    strings_at = sym_at + nsymbols * 18
    symbols: dict[int, dict[str, object]] = {}
    i, at = 0, sym_at
    while i < nsymbols:
        rec = data[at:at + 18]
        name = read_name(data, strings_at, rec[:8])
        value, sec, _, storage, aux = struct.unpack_from("<IhHBB", rec, 8)
        symbols[i] = {"name": name, "value": value, "section_number": sec, "storage_class": storage}
        i += 1 + aux
        at += (1 + aux) * 18
    sec = sections[section_number - 1]
    raw = int(sec["raw"])
    size = int(sec["size"])
    uninitialized = bool(int(sec["flags"]) & 0x00000080)
    blob = bytes(size) if uninitialized and raw == 0 else data[raw:raw + size]
    if len(blob) != size:
        raise ValueError(f"{path.name}: section {section_number} raw data is truncated")
    relocs = []
    type_counts: Counter[str] = Counter()
    target_classes: Counter[str] = Counter()
    for ri in range(int(sec["nreloc"])):
        loc, sym_index, kind = struct.unpack_from("<IIH", data, int(sec["reloc"]) + ri * 10)
        target = symbols.get(sym_index)
        if target is None or loc + 4 > size:
            raise ValueError(f"{path.name}: invalid relocation in section {section_number}")
        target_sec = int(target["section_number"])
        target_name = "UNDEFINED" if target_sec == 0 else "ABSOLUTE" if target_sec == -1 else sections[target_sec - 1]["name"]
        kind_name = RELOC_NAMES.get(kind, f"0x{kind:04X}")
        cls = "undefined-external" if target_sec == 0 else "absolute" if target_sec == -1 else "same-object-section"
        type_counts[kind_name] += 1
        target_classes[cls] += 1
        relocs.append({"site": loc, "type": kind_name, "target_symbol": target["name"],
                       "target_value": target["value"], "target_section_number": target_sec,
                       "target_section": target_name, "target_class": cls,
                       "raw_field_bytes": blob[loc:loc + 4].hex(" ").upper()})
    return {"object_sha256": hashlib.sha256(data).hexdigest().upper(),
            "section_number": section_number, "section_name": sec["name"],
            "section_bytes": size, "section_raw_pointer": raw,
            "section_flags": f"0x{int(sec['flags']):08X}",
            "section_sha256": hashlib.sha256(blob).hexdigest().upper(),
            "relocation_count": len(relocs), "relocation_counts_by_type": dict(sorted(type_counts.items())),
            "relocation_target_classes": dict(sorted(target_classes.items())),
            "relocations": relocs}


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--census", type=Path, default=ROOT / "audit/appended-thunk-payload-census-conservative-current-2026-09-30.json")
    p.add_argument("--target-report", type=Path, default=ROOT / "audit/appended-thunk-relocation-targets-conservative-current-2026-09-30.json")
    p.add_argument("--root-link-map", type=Path, default=ROOT / "audit/appended-thunk-link-map-resolution-conservative-current-2026-09-30.json")
    p.add_argument("--output", type=Path, required=True)
    a = p.parse_args()
    if a.output.exists():
        raise FileExistsError(f"refusing to overwrite {a.output}")
    census = json.loads(a.census.read_text(encoding="utf-8"))
    targets = json.loads(a.target_report.read_text(encoding="utf-8"))
    root_links = json.loads(a.root_link_map.read_text(encoding="utf-8"))
    if census["thunk_entries"] != targets["thunk_bodies"] or census["candidate_entries"] != 705:
        raise ValueError("payload census and target report disagree")
    objects = Path(census["objects_directory"])
    requested = [x for x in targets["same_object_sections_referenced"] if x["section"] != ".rdata"]
    unique = {(x["source_entry"], int(x["section_number"])): x for x in requested}
    if len(unique) != len(requested):
        raise ValueError("duplicate local-section references in target inventory")
    rows = []
    for (entry, secnum), meta in sorted(unique.items()):
        path = objects / f"{int(entry, 16):08x}.obj"
        got = inspect_object(path, secnum)
        if got["section_name"] != meta["section"] or got["section_bytes"] != meta["raw_size"]:
            raise ValueError(f"{entry} section {secnum}: inventory section metadata mismatch")
        if got["section_sha256"] != meta["raw_bytes_sha256"] and got["section_name"] != ".bss":
            raise ValueError(f"{entry} section {secnum}: inventory bytes hash mismatch")
        rows.append({"source_entry": entry,
                     "inventory_reported_sha256": meta["raw_bytes_sha256"],
                     "inventory_hash_is_materialized_section_content": got["section_sha256"] == meta["raw_bytes_sha256"],
                     **got})
    section_counts = Counter(x["section_name"] for x in rows)
    thunk_count = int(census["thunk_entries"])
    payload_bytes = int(census["combined_code_and_rdata_payload_bytes"])
    known_root_symbols = {(x["symbol"], x["relocation_type"]): x for x in root_links["symbols"]}
    extra_externals = [r for section in rows for r in section["relocations"]
                       if r["target_class"] == "undefined-external"]
    extra_by_known_class: Counter[str] = Counter()
    missing_symbols: dict[tuple[str, str], int] = {}
    for relocation in extra_externals:
        key = (str(relocation["target_symbol"]), str(relocation["type"]))
        match = known_root_symbols.get(key)
        if match:
            extra_by_known_class[str(match["classification"])] += 1
        else:
            missing_symbols[key] = missing_symbols.get(key, 0) + 1
    report = {
        "scope": f"Read-only closure audit of same-object non-.rdata sections referenced by the current {thunk_count} appended root bodies.",
        "original_sha256": "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3",
        "payload_census": str(a.census.resolve()),
        "relocation_target_report": str(a.target_report.resolve()),
        "root_thunk_count": census["thunk_entries"],
        "referenced_non_rdata_section_count": len(rows),
        "sections_by_name": dict(sorted(section_counts.items())),
        "total_section_bytes_including_bss_virtual_extent": sum(int(x["section_bytes"]) for x in rows),
        "total_relocations_in_these_sections": sum(int(x["relocation_count"]) for x in rows),
        "relocation_counts_by_type": dict(sorted(sum_counters(rows, "relocation_counts_by_type").items())),
        "relocation_target_classes": dict(sorted(sum_counters(rows, "relocation_target_classes").items())),
        "undefined_external_occurrences_in_local_sections": len(extra_externals),
        "local_external_occurrences_matching_root_symbol_inventory_by_class": dict(sorted(extra_by_known_class.items())),
        "unique_local_external_symbol_type_pairs_missing_from_root_inventory": len(missing_symbols),
        "local_external_symbols_missing_from_root_inventory": [
            {"symbol": symbol, "type": kind, "occurrences": count}
            for (symbol, kind), count in sorted(missing_symbols.items())
        ],
        "payload_census_included_these_sections": False,
        "conclusion": (f"The current {payload_bytes:,}-byte code+rdata payload census includes the {thunk_count} root bodies and "
                       f"{census['referenced_same_object_rdata_section_count']} referenced .rdata sections, but not these referenced local .xcode/.data/.bss sections. "
                       "Their code/data closure and relocation targets must be placed and fixed before the CRT helper offsets or a final PE layout can be considered authoritative."),
        "data_hygiene_note": "The source census hashes four bytes at file offset zero for the .bss section because its COFF raw pointer is zero. This equals neither materialized BSS contents nor an on-disk section payload; this audit instead models the section's four zero-initialized bytes and records both hashes.",
        "limitations": [
            "This audit inventories exact bytes and section relocations; it does not resolve or apply them.",
            "Executable .xcode auxiliaries may require distinct placement; .data/.bss require writable storage and initialization/lifetime review.",
            "No candidate object, PE, ASI, or game state is modified or validated."
        ],
        "sections": rows,
    }
    a.output.parent.mkdir(parents=True, exist_ok=True)
    a.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({k: report[k] for k in ("referenced_non_rdata_section_count", "sections_by_name",
                   "total_section_bytes_including_bss_virtual_extent", "total_relocations_in_these_sections",
                   "relocation_counts_by_type", "relocation_target_classes",
                   "undefined_external_occurrences_in_local_sections",
                   "unique_local_external_symbol_type_pairs_missing_from_root_inventory")}, indent=2))
    print(f"report={a.output.resolve()}")
    return 0


def sum_counters(rows: list[dict[str, object]], key: str) -> Counter[str]:
    total: Counter[str] = Counter()
    for row in rows:
        total.update(row[key])
    return total


if __name__ == "__main__":
    raise SystemExit(main())
