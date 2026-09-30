#!/usr/bin/env python3
"""Resolve direct-fit candidate COFF relocation symbols against a diagnostic link map.

The report classifies current diagnostic targets; it does not decide final
production addresses and never patches a PE image.
"""

from __future__ import annotations

import argparse
import json
import re
import struct
from collections import Counter
from pathlib import Path


MAP_SYMBOL = re.compile(
    r"^\s*[0-9A-Fa-f]{4}:[0-9A-Fa-f]{8}\s+(\S+)\s+([0-9A-Fa-f]{8})\b"
)


def symbol_name(raw: bytes, strings: bytes) -> str:
    if raw[:4] == b"\0\0\0\0":
        offset = struct.unpack_from("<I", raw, 4)[0]
        end = strings.find(b"\0", offset)
        if end < 0:
            return "<invalid-string-offset>"
        return strings[offset:end].decode("utf-8", errors="replace")
    return raw.split(b"\0", 1)[0].decode("utf-8", errors="replace")


def read_object(path: Path, expected_symbol: str) -> dict[str, object]:
    data = path.read_bytes()
    machine, section_count, _, symbol_offset, symbol_count, optional_size, _ = struct.unpack_from(
        "<HHIIIHH", data, 0
    )
    if machine != 0x14C or optional_size != 0:
        raise ValueError(f"{path.name}: expected 32-bit x86 COFF object")
    sections: list[dict[str, object]] = []
    for index in range(section_count):
        at = 20 + index * 40
        (raw_name, _, _, raw_size, raw_offset, reloc_offset, _, reloc_count,
         _, _) = struct.unpack_from("<8sIIIIIIHHI", data, at)
        sections.append(
            {
                "name": raw_name.split(b"\0", 1)[0].decode("ascii", errors="replace"),
                "size": raw_size,
                "raw": raw_offset,
                "reloc": reloc_offset,
                "reloc_count": reloc_count,
            }
        )

    string_offset = symbol_offset + symbol_count * 18
    string_size = struct.unpack_from("<I", data, string_offset)[0]
    strings = data[string_offset : string_offset + string_size]
    symbols: dict[int, dict[str, object]] = {}
    by_name: dict[str, list[dict[str, object]]] = {}
    index = 0
    cursor = symbol_offset
    while index < symbol_count:
        record = data[cursor : cursor + 18]
        name = symbol_name(record[:8], strings)
        value, section_number, symbol_type, storage_class, aux_count = struct.unpack_from(
            "<IhHBB", record, 8
        )
        item = {
            "index": index,
            "name": name,
            "value": value,
            "section_number": section_number,
            "section_name": sections[section_number - 1]["name"] if 0 < section_number <= len(sections) else None,
            "type": symbol_type,
            "storage_class": storage_class,
            "aux_count": aux_count,
        }
        symbols[index] = item
        by_name.setdefault(name, []).append(item)
        index += 1 + aux_count
        cursor += (1 + aux_count) * 18

    entries = by_name.get(expected_symbol, [])
    if len(entries) != 1:
        raise ValueError(f"{path.name}: expected unique entry {expected_symbol}, found {len(entries)}")
    entry_symbol = entries[0]
    section_number = int(entry_symbol["section_number"])
    if section_number <= 0:
        raise ValueError(f"{path.name}: candidate entry is undefined")
    section = sections[section_number - 1]
    if section["name"] != ".xcode" or int(entry_symbol["value"]) != 0:
        raise ValueError(f"{path.name}: candidate entry is not at .xcode offset zero")

    relocations = []
    for relocation_index in range(int(section["reloc_count"])):
        at = int(section["reloc"]) + relocation_index * 10
        site, target_index, kind = struct.unpack_from("<IIH", data, at)
        target = symbols.get(target_index)
        if target is None:
            raise ValueError(f"{path.name}: relocation uses invalid symbol index {target_index}")
        addend = struct.unpack_from("<I", data, int(section["raw"]) + site)[0]
        relocations.append(
            {
                "offset": site,
                "type": {0x0006: "DIR32", 0x0014: "REL32"}.get(kind, f"0x{kind:04x}"),
                "symbol_index": target_index,
                "symbol": target["name"],
                "symbol_defined_in_object": int(target["section_number"]) > 0,
                "symbol_section_number": target["section_number"],
                "symbol_section": target["section_name"],
                "symbol_value": target["value"],
                "symbol_storage_class": target["storage_class"],
                "raw_addend": f"0x{addend:08x}",
            }
        )
    return {
        "entry_symbol": expected_symbol,
        "entry_section_number": section_number,
        "body_size": int(section["size"]),
        "relocations": relocations,
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--objects", type=Path, required=True)
    parser.add_argument("--inplace-report", type=Path, required=True)
    parser.add_argument("--map", dest="map_path", type=Path, required=True)
    parser.add_argument("--diagnostic-relocation-report", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")

    inplace = json.loads(args.inplace_report.read_text(encoding="utf-8"))
    diagnostic = json.loads(args.diagnostic_relocation_report.read_text(encoding="utf-8"))
    if inplace["summary"]["candidate_entries"] != 705:
        raise ValueError("expected current 705-entry placement report")
    if int(diagnostic["image_base"]) != 0x10000000:
        raise ValueError("unexpected diagnostic image base")

    section_ranges = []
    for section in diagnostic["sections"]:
        start = int(section["va"])
        size = max(int(section.get("virtual_size", 0)), int(section.get("raw_size", 0)))
        section_ranges.append((start, start + size, section["name"]))

    map_targets: dict[str, set[int]] = {}
    for line in args.map_path.read_text(encoding="utf-8", errors="replace").splitlines():
        match = MAP_SYMBOL.match(line)
        if match:
            map_targets.setdefault(match.group(1), set()).add(int(match.group(2), 16))

    candidate_symbol_to_entry = {
        row["symbol"]: int(row["entry_va"], 16)
        for row in json.loads(
            args.inplace_report.read_text(encoding="utf-8")
        ).get("results", [])
    }
    by_target_class: Counter[str] = Counter()
    by_relocation_type: Counter[str] = Counter()
    function_rows = []
    ambiguous = 0
    unresolved = 0
    total = 0
    candidate_symbol_bindings = 0
    ambiguous_candidate_bindings = 0

    for placement in inplace["results"]:
        entry = int(placement["entry_va"], 16)
        object_info = read_object(args.objects / f"{entry:08x}.obj", placement["symbol"])
        relocations = []
        for relocation in object_info["relocations"]:
            total += 1
            kind = str(relocation["type"])
            by_relocation_type[kind] += 1
            name = str(relocation["symbol"])
            candidate_entry_va = candidate_symbol_to_entry.get(name)
            if candidate_entry_va is not None:
                candidate_symbol_bindings += 1
            targets = map_targets.get(name, set())
            resolved_va = None
            target_section = None
            entry_targets = map_targets.get(str(placement["symbol"]), set())
            local_in_body = (
                bool(relocation["symbol_defined_in_object"])
                and int(relocation["symbol_section_number"])
                == int(object_info["entry_section_number"])
            )
            if local_in_body and len(entry_targets) == 1:
                resolved_va = next(iter(entry_targets)) + int(relocation["symbol_value"])
                target_section = ".xcode"
                target_class = "local_symbol_in_candidate_body"
            elif len(targets) == 1:
                resolved_va = next(iter(targets))
                target_section = next(
                    (section_name for start, end, section_name in section_ranges if start <= resolved_va < end),
                    "outside-diagnostic-sections",
                )
                if name in candidate_symbol_to_entry:
                    target_class = "candidate_function_entry"
                elif target_section == ".entry":
                    target_class = "original_image_code_template"
                elif target_section in {".rdata", ".data", ".fptable"}:
                    target_class = "diagnostic_data_contribution"
                elif target_section in {".xcode", ".text"}:
                    target_class = "diagnostic_executable_contribution"
                elif target_section == ".reloc":
                    target_class = "relocation_metadata"
                else:
                    target_class = "mapped_external_or_other"
            elif len(targets) > 1:
                target_class = "ambiguous_duplicate_map_symbol"
                ambiguous += 1
                if candidate_entry_va is not None:
                    ambiguous_candidate_bindings += 1
            else:
                target_class = "not_found_in_link_map"
                unresolved += 1
            by_target_class[target_class] += 1
            relocations.append(
                {
                    **relocation,
                    "diagnostic_target_va": f"0x{resolved_va:08x}" if resolved_va is not None else None,
                    "diagnostic_target_section": target_section,
                    "target_class": target_class,
                    # This is an object-set crosswalk, not a diagnostic-link VA:
                    # when the exact undefined symbol is defined by one of the
                    # 705 candidate objects, its intended candidate entry is
                    # independently available even if the diagnostic map has
                    # duplicate providers with the same decorated name.
                    "candidate_target_entry_va": (
                        f"0x{candidate_entry_va:08x}"
                        if candidate_entry_va is not None else None
                    ),
                    "candidate_symbol_definition_present": candidate_entry_va is not None,
                    "diagnostic_symbol_addresses": [f"0x{x:08x}" for x in sorted(targets)],
                }
            )
        function_rows.append(
            {
                "entry_va": placement["entry_va"],
                "symbol": placement["symbol"],
                "body_fits_gap": placement["body_fits_gap"],
                "body_size": object_info["body_size"],
                "relocations": relocations,
            }
        )

    report = {
        "scope": "Symbol/section crosswalk for COFF relocations against the current diagnostic link; no preferred production target or PE bytes are changed.",
        "inputs": {
            "objects": str(args.objects.resolve()),
            "placement_report": str(args.inplace_report.resolve()),
            "diagnostic_map": str(args.map_path.resolve()),
            "diagnostic_relocation_report": str(args.diagnostic_relocation_report.resolve()),
        },
        "summary": {
            "candidate_functions": len(function_rows),
            "coff_relocations": total,
            "relocation_types": dict(sorted(by_relocation_type.items())),
            "current_diagnostic_target_classes": dict(sorted(by_target_class.items())),
            "ambiguous_map_targets": ambiguous,
            "candidate_defined_symbol_bindings": candidate_symbol_bindings,
            "ambiguous_map_targets_with_candidate_definition": ambiguous_candidate_bindings,
            "targets_missing_from_map": unresolved,
            "limitations": [
                "Diagnostic map addresses are not production target addresses.",
                "A symbol absent from the public map may be a local/section symbol; no unresolved target is presumed safe.",
                "DIR32 raw addends and resolved symbols still require instruction-level target verification before base-relocation edits.",
                "This does not reconcile non-fitting bodies, copied data contents, imports/initialization, or gameplay behavior.",
                "No PE bytes are modified.",
            ],
        },
        "functions": function_rows,
    }
    with args.output.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    print(
        f"functions={len(function_rows)} relocations={total} "
        f"map_ambiguous={ambiguous} map_missing={unresolved} "
        f"candidate_symbol_bindings={candidate_symbol_bindings} "
        f"ambiguous_but_candidate_bound={ambiguous_candidate_bindings} "
        f"classes={json.dumps(dict(sorted(by_target_class.items())))}"
    )
    print(f"report={args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
