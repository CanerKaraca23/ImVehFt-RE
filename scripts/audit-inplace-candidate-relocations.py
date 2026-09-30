#!/usr/bin/env python3
"""Classify all 705 COFF entry bodies for bounded in-place PE placement."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import struct
from collections import Counter
from pathlib import Path


IMAGE_SCN_CNT_CODE = 0x00000020
IMAGE_SCN_MEM_EXECUTE = 0x20000000
RELOCATION_NAMES = {0x0006: "DIR32", 0x0014: "REL32", 0x000A: "SECTION", 0x000B: "SECREL"}


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def va(text: str) -> int:
    return int(text.strip().strip('"').removeprefix("0x"), 16)


def parse_coff(path: Path, expected_symbol: str) -> tuple[bytes, dict[str, object]]:
    data = path.read_bytes()
    machine, section_count, _, symbol_offset, symbol_count, optional_size, _ = struct.unpack_from(
        "<HHIIIHH", data
    )
    if machine != 0x14C:
        raise ValueError(f"{path.name}: expected i386 COFF")
    section_table = 20 + optional_size
    sections = []
    for i in range(section_count):
        off = section_table + i * 40
        name, _, _, raw_size, raw_offset, reloc_offset, _, reloc_count, _, flags = struct.unpack_from(
            "<8sIIIIIIHHI", data, off
        )
        sections.append({"name": name.split(b"\0", 1)[0].decode("ascii", errors="replace"),
                         "size": raw_size, "raw": raw_offset, "reloc": reloc_offset,
                         "reloc_count": reloc_count, "flags": flags})
    string_offset = symbol_offset + symbol_count * 18
    string_size = struct.unpack_from("<I", data, string_offset)[0]
    strings = data[string_offset : string_offset + string_size]
    symbols = []
    index = 0
    cursor = symbol_offset
    while index < symbol_count:
        entry = data[cursor : cursor + 18]
        name_bytes = entry[:8]
        if name_bytes[:4] == b"\0\0\0\0":
            name_offset = struct.unpack_from("<I", name_bytes, 4)[0]
            end = strings.find(b"\0", name_offset)
            name = strings[name_offset:end].decode("utf-8", errors="replace") if end >= 0 else ""
        else:
            name = name_bytes.split(b"\0", 1)[0].decode("utf-8", errors="replace")
        value, section_number, symbol_type, storage, aux_count = struct.unpack_from("<IhHBB", entry, 8)
        if name == expected_symbol:
            symbols.append((value, section_number, symbol_type, storage))
        index += 1 + aux_count
        cursor += (1 + aux_count) * 18
    if len(symbols) != 1:
        raise ValueError(f"{path.name}: expected one {expected_symbol}, found {len(symbols)}")
    value, section_number, symbol_type, storage = symbols[0]
    if section_number <= 0 or section_number > len(sections):
        raise ValueError(f"{path.name}: entry symbol not section-defined")
    section = sections[section_number - 1]
    if section["name"] != ".xcode" or value != 0:
        raise ValueError(f"{path.name}: entry symbol is not at .xcode offset zero")
    flags = int(section["flags"])
    if flags & (IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_EXECUTE) != (IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_EXECUTE):
        raise ValueError(f"{path.name}: entry section is not executable code")
    size = int(section["size"])
    raw = int(section["raw"])
    if size <= 0 or raw + size > len(data):
        raise ValueError(f"{path.name}: invalid executable section byte range")
    relocations = []
    for i in range(int(section["reloc_count"])):
        rel_at = int(section["reloc"]) + i * 10
        site, symbol_index, kind = struct.unpack_from("<IIH", data, rel_at)
        relocations.append({"site": site, "symbol_index": symbol_index, "type": kind,
                            "type_name": RELOCATION_NAMES.get(kind, f"0x{kind:04x}")})
    return data[raw : raw + size], {
        "object_sha256": sha256(data), "entry_symbol": expected_symbol,
        "section_number": section_number, "section_size": size,
        "relocations": relocations,
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--objects", type=Path, required=True)
    parser.add_argument("--feasibility", type=Path, required=True)
    parser.add_argument("--slot-fit", type=Path, required=True)
    parser.add_argument("--function-map", type=Path, required=True)
    parser.add_argument("--text-highlow-sites", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")

    feasibility = json.loads(args.feasibility.read_text(encoding="utf-8"))
    fit_report = json.loads(args.slot_fit.read_text(encoding="utf-8"))
    feasibility_rows = {va(row["address"]): row for row in feasibility["entries"]}
    symbols = {entry: row["entry_symbol"] for entry, row in feasibility_rows.items()}
    fits = {va(row["address"]): row for row in fit_report["results"]}
    with args.function_map.open(encoding="utf-8-sig", newline="") as stream:
        function_rows = list(csv.DictReader(stream))
    entries = sorted(va(row["address"]) for row in function_rows)
    if len(entries) != 705 or len(set(entries)) != 705 or len(symbols) != 705 or len(fits) != 705:
        raise ValueError("expected 705 unique entries and 705 feasibility/slot-fit results")
    fixup_rows = list(csv.DictReader(args.text_highlow_sites.open(encoding="utf-8-sig", newline="")))
    fixups = sorted(va(row["address"]) for row in fixup_rows)
    if len(fixups) != 3160:
        raise ValueError(f"expected 3,160 original .text HIGHLOW sites, found {len(fixups)}")

    results = []
    type_totals: Counter[str] = Counter()
    for i, entry in enumerate(entries):
        object_path = args.objects / f"{entry:08x}.obj"
        body, info = parse_coff(object_path, symbols[entry])
        mapped_body_extent = int(feasibility_rows[entry]["candidate_body_size"])
        gap = fits.get(entry, {}).get("gap_to_next_mapped_candidate_entry")
        fits_gap = gap is not None and len(body) <= int(gap)
        types = Counter(rel["type_name"] for rel in info["relocations"])
        type_totals.update(types)
        overlap_sites = [site for site in fixups if max(site, entry) < min(site + 4, entry + len(body))]
        if gap is None:
            placement_class = "last-entry-unbounded"
        elif not fits_gap:
            placement_class = "body-exceeds-gap"
        elif not info["relocations"]:
            placement_class = "fits-no-coff-relocations"
        elif set(types) <= {"REL32"}:
            placement_class = "fits-rel32-only-needs-resolution"
        elif set(types) <= {"DIR32", "REL32"}:
            placement_class = "fits-dir32-or-rel32-needs-resolution"
        else:
            placement_class = "fits-other-relocations-need-review"
        results.append({
            "entry_va": f"0x{entry:08x}",
            "symbol": symbols[entry],
            "object_sha256": info["object_sha256"],
            "candidate_body_size": len(body),
            "diagnostic_map_body_extent": mapped_body_extent,
            "next_entry_gap": gap,
            "body_fits_gap": fits_gap,
            "placement_class": placement_class,
            "coff_relocation_count": len(info["relocations"]),
            "coff_relocation_types": dict(sorted(types.items())),
            "original_highlow_fields_overlapping_body": [f"0x{x:08x}" for x in overlap_sites],
            "original_highlow_overlap_count": len(overlap_sites),
        })
    counts = Counter(row["placement_class"] for row in results)
    fitting = [row for row in results if row["body_fits_gap"]]
    fitting_fixup_sites = {
        site for row in fitting for site in row["original_highlow_fields_overlapping_body"]
    }
    report = {
        "scope": "COFF and original-image relocation feasibility inventory for in-place placement of the 705 entry bodies; no bytes are patched.",
        "inputs": {
            "objects_directory": str(args.objects.resolve()),
            "objects_directory_count": len(list(args.objects.glob("*.obj"))),
            "feasibility_sha256": sha256(args.feasibility.read_bytes()),
            "slot_fit_sha256": sha256(args.slot_fit.read_bytes()),
            "function_map_sha256": sha256(args.function_map.read_bytes()),
            "text_highlow_sites_sha256": sha256(args.text_highlow_sites.read_bytes()),
        },
        "summary": {
            "candidate_entries": len(results),
            "placement_class_counts": dict(sorted(counts.items())),
            "coff_relocation_type_occurrences": dict(sorted(type_totals.items())),
            "candidate_bodies_with_any_original_highlow_overlap": sum(bool(row["original_highlow_overlap_count"]) for row in results),
            "sum_original_highlow_overlaps_across_candidate_bodies": sum(row["original_highlow_overlap_count"] for row in results),
            "in_place_fitting_candidate_count": len(fitting),
            "in_place_fitting_bodies_with_original_highlow_overlap": sum(bool(row["original_highlow_overlap_count"]) for row in fitting),
            "in_place_fitting_highlow_overlap_instances": sum(row["original_highlow_overlap_count"] for row in fitting),
            "unique_original_highlow_sites_touched_by_fitting_bodies": len(fitting_fixup_sites),
        },
        "results": results,
        "limitations": [
            "COFF relocation categories describe requirements, not their correct final target values or base-relocation encoding.",
            "This does not prove original instruction boundaries, incoming control-flow safety, semantic equivalence, PE startup, or game behavior.",
            "The all-candidate overlap totals include bodies that exceed their available gaps; use the separately reported fitting-body counts for in-place-only estimates.",
            "A relocation site can intersect more than one fitting body if a 4-byte fixup straddles a boundary; per-body instances and unique fixup sites are reported separately.",
        ],
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    print("candidate_entries=705 classes=" + json.dumps(dict(sorted(counts.items()))) +
          f" original_highlow_overlap_instances={report['summary']['sum_original_highlow_overlaps_across_candidate_bodies']}")
    print(f"report={args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
