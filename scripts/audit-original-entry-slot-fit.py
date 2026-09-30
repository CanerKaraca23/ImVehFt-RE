#!/usr/bin/env python3
"""Measure whether each candidate's selected COFF COMDAT fits before the next mapped entry."""

from __future__ import annotations

import argparse
import csv
import importlib.util
import json
import struct
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
GENERATOR = ROOT / "scripts/generate-candidate-comdat-order.py"


def load_generator():
    spec = importlib.util.spec_from_file_location("candidate_order", GENERATOR)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot import {GENERATOR}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def public_text_symbols(path: Path, helper) -> tuple[list[tuple[str, int, int]], dict[int, tuple[str, int]]]:
    data = path.read_bytes()
    if len(data) < 20:
        raise ValueError(f"short COFF object: {path}")
    machine, section_count, _, symbol_ptr, symbol_count, optional_size, _ = struct.unpack_from(
        "<HHIIIHH", data, 0
    )
    if machine != 0x14C or optional_size:
        raise ValueError(f"expected x86 COFF object without optional header: {path}")
    sections: dict[int, tuple[str, int]] = {}
    for index in range(section_count):
        at = 20 + index * 40
        header = data[at : at + 40]
        name = header[:8].split(b"\0", 1)[0].decode("ascii", errors="replace")
        raw_size = struct.unpack_from("<I", header, 16)[0]
        sections[index + 1] = (name, raw_size)
    strings_at = symbol_ptr + symbol_count * 18
    strings_size = struct.unpack_from("<I", data, strings_at)[0]
    strings = data[strings_at : strings_at + strings_size]
    symbols: list[tuple[str, int, int]] = []
    index = 0
    while index < symbol_count:
        at = symbol_ptr + index * 18
        name = helper.coff_name(data[at : at + 8], strings)
        value, section_number = struct.unpack_from("<Ih", data, at + 8)
        storage_class, aux_count = data[at + 16], data[at + 17]
        if (
            storage_class == 2
            and section_number > 0
            and sections.get(section_number, ("", 0))[0].startswith((".text", ".xcode"))
        ):
            symbols.append((name, section_number, value))
        index += 1 + aux_count
    return symbols, sections


def choose_entry(symbols, address: int, row: dict[str, str], helper) -> list[tuple[str, int, int]]:
    choices = [s for s in symbols if helper.is_candidate_entry(s[0], row["ghidra_name"], row["signature"])]
    if not choices:
        choices = [s for s in symbols if helper.is_address_bound_cpp_entry_alias(s[0], row["ghidra_name"])]
    if not choices:
        choices = [s for s in symbols if helper.is_address_named_coff_alias(s[0], address)]
    if not choices:
        choices = [s for s in symbols if helper.is_stdcall_name_sanitization_alias(s[0], row["ghidra_name"], row["signature"])]
    if not choices:
        choices = [s for s in symbols if helper.is_verified_recovered_import_thunk_alias(s[0], row["ghidra_name"], row["signature"])]
    if not choices and len(symbols) == 1:
        choices = symbols
    return choices


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("objects_dir", type=Path)
    parser.add_argument("--function-map", type=Path, default=ROOT / "audit/function-name-map.csv")
    parser.add_argument("--output", type=Path, required=True, help="New JSON report; existing files are never overwritten")
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")
    helper = load_generator()
    with args.function_map.open(encoding="utf-8-sig", newline="") as stream:
        rows = list(csv.DictReader(stream))
    rows.sort(key=lambda row: int(row["address"], 16))
    if len(rows) != 705 or len({row["address"] for row in rows}) != 705:
        raise ValueError(f"expected 705 unique function-map rows, got {len(rows)}")

    results = []
    for index, row in enumerate(rows):
        address = int(row["address"], 16)
        obj = args.objects_dir / f"{address:08x}.obj"
        symbols, sections = public_text_symbols(obj, helper)
        entries = choose_entry(symbols, address, row, helper)
        if len(entries) != 1:
            raise ValueError(f"expected one selected entry for {address:#x}, found {len(entries)}")
        name, section_number, value = entries[0]
        next_address = int(rows[index + 1]["address"], 16) if index + 1 < len(rows) else None
        gap = next_address - address if next_address is not None else None
        section_size = sections[section_number][1]
        used = value + section_size
        results.append({
            "address": f"0x{address:08x}",
            "next_mapped_candidate_address": f"0x{next_address:08x}" if next_address is not None else None,
            "entry_symbol": name,
            "coff_text_comdat_size": section_size,
            "symbol_offset_in_comdat": value,
            "gap_to_next_mapped_candidate_entry": gap,
            "fits_without_crossing_next_entry": used <= gap if gap is not None else None,
        })

    fitted = sum(item["fits_without_crossing_next_entry"] is True for item in results)
    overlapped = sum(item["fits_without_crossing_next_entry"] is False for item in results)
    report = {
        "scope": "Selected public candidate COFF COMDAT size versus the address gap to the next entry in the 705-function map; a layout feasibility diagnostic only.",
        "objects_dir": str(args.objects_dir),
        "function_map": str(args.function_map),
        "candidate_count": len(results),
        "fits_before_next_entry": fitted,
        "exceeds_next_entry_gap": overlapped,
        "last_entry_without_next_boundary": len(results) - fitted - overlapped,
        "limitations": [
            "The next mapped entry gives an upper-bound slot, not a verified original function-body extent.",
            "COMDAT fit does not prove relocation completeness, semantic equivalence, PE validity, loader compatibility, or gameplay behavior.",
            "A non-fit means the selected COMDAT cannot be placed whole at its original entry without crossing the next mapped entry; it does not rule out bridges or splitting code into separate sections.",
        ],
        "results": results,
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(f"entries={len(results)} fit={fitted} exceeds-next-entry-gap={overlapped} last-without-boundary={len(results)-fitted-overlapped}")
    print(f"report={args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
