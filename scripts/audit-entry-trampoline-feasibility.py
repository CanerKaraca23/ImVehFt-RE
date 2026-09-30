#!/usr/bin/env python3
"""Check whether mapped entry slots can hold bodies or 5-byte x86 trampolines."""

from __future__ import annotations

import argparse
import json
import re
import struct
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_FIT_REPORT = ROOT / "audit/original-entry-slot-fit-2026-09-28.json"
DEFAULT_MAP = ROOT / "build/link-probe/strict-704-historical-sdk/ImVehFt-relocatable-hook-shims-diagnostic-not-ASI.map"
DEFAULT_DIAGNOSTIC_PE = ROOT / "build/link-probe/strict-704-historical-sdk/ImVehFt-relocatable-hook-shims-diagnostic-not-ASI.dll"
DEFAULT_REFERENCE_PE = Path(r"C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi")


def pe_sections(path: Path) -> tuple[int, list[dict[str, int | str]]]:
    data = path.read_bytes()
    if len(data) < 0x40 or data[:2] != b"MZ":
        raise ValueError(f"not a PE image: {path}")
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    if pe + 24 > len(data) or data[pe : pe + 4] != b"PE\0\0":
        raise ValueError(f"invalid PE signature: {path}")
    section_count = struct.unpack_from("<H", data, pe + 6)[0]
    optional_size = struct.unpack_from("<H", data, pe + 20)[0]
    optional = pe + 24
    magic = struct.unpack_from("<H", data, optional)[0]
    if magic != 0x10B:
        raise ValueError(f"expected PE32 image: {path}")
    image_base = struct.unpack_from("<I", data, optional + 28)[0]
    table = optional + optional_size
    sections: list[dict[str, int | str]] = []
    for index in range(section_count):
        off = table + index * 40
        raw_name = data[off : off + 8].split(b"\0", 1)[0]
        name = raw_name.decode("ascii", errors="replace")
        virtual_size, rva, raw_size, _ = struct.unpack_from("<IIII", data, off + 8)
        characteristics = struct.unpack_from("<I", data, off + 36)[0]
        sections.append(
            {
                "name": name,
                "va": image_base + rva,
                "end": image_base + rva + max(virtual_size, raw_size),
                "virtual_end": image_base + rva + virtual_size,
                "characteristics": characteristics,
            }
        )
    return image_base, sections


def parse_map(path: Path) -> dict[str, int]:
    symbols: dict[str, int] = {}
    pattern = re.compile(
        r"^\s*[0-9A-Fa-f]{4}:[0-9A-Fa-f]{8}\s+(\S+)\s+([0-9A-Fa-f]{8})\s+f\s"
    )
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        match = pattern.match(line)
        if match:
            symbols[match.group(1)] = int(match.group(2), 16)
    return symbols


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--fit-report", type=Path, default=DEFAULT_FIT_REPORT)
    parser.add_argument("--body-report", type=Path, help="COFF inventory with authoritative candidate body sizes")
    parser.add_argument("--map", dest="map_path", type=Path, default=DEFAULT_MAP)
    parser.add_argument("--diagnostic-pe", type=Path, default=DEFAULT_DIAGNOSTIC_PE)
    parser.add_argument("--reference-pe", type=Path, default=DEFAULT_REFERENCE_PE)
    parser.add_argument(
        "--output",
        type=Path,
        default=ROOT / "audit/entry-trampoline-feasibility-2026-09-28.json",
    )
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")

    fit_report = json.loads(args.fit_report.read_text(encoding="utf-8"))
    body_report = json.loads(args.body_report.read_text(encoding="utf-8")) if args.body_report else None
    _, reference_sections = pe_sections(args.reference_pe)
    _, diagnostic_sections = pe_sections(args.diagnostic_pe)
    text_sections = [section for section in reference_sections if section["name"] == ".text"]
    if len(text_sections) != 1:
        raise ValueError("expected exactly one .text section in the reference image")
    reference_text = text_sections[0]
    executable = [
        section
        for section in diagnostic_sections
        if int(section["characteristics"]) & 0x20000000
    ]
    symbols = parse_map(args.map_path)
    body_rows = {row["entry_va"]: row for row in body_report["results"]} if body_report else {}
    if body_report and len(body_rows) != fit_report["candidate_count"]:
        raise ValueError("body report must contain one unique row per candidate entry")

    results: list[dict[str, object]] = []
    unresolved: list[str] = []
    outside_exec: list[str] = []
    bad_rel32: list[str] = []
    bodies_fit = 0
    last_body_fit = False
    trampoline_gaps: list[int] = []
    trampoline_count = 0

    for row in fit_report["results"]:
        entry = int(row["address"], 16)
        map_body_extent = int(row["symbol_offset_in_comdat"]) + int(
            row["coff_text_comdat_size"]
        )
        exact_row = body_rows.get(row["address"])
        body_size = int(exact_row["candidate_body_size"]) if exact_row else map_body_extent
        next_entry = row["next_mapped_candidate_address"]
        if next_entry is None:
            available = int(reference_text["virtual_end"]) - entry
            body_fits = body_size <= available
            last_body_fit = body_fits
            mode = "body-at-entry" if body_fits else "unresolved-last-entry"
            gap = available
        else:
            gap = int(next_entry, 16) - entry
            body_fits = body_size <= gap
            if body_fits:
                bodies_fit += 1
                mode = "body-at-entry"
            elif gap >= 5:
                mode = "jmp-rel32-thunk"
                trampoline_count += 1
                trampoline_gaps.append(gap)
            else:
                mode = "no-5-byte-thunk-slot"

        target = symbols.get(row["entry_symbol"])
        if target is None:
            unresolved.append(row["entry_symbol"])
            rel32 = None
            target_executable = False
        else:
            rel32 = target - (entry + 5)
            target_executable = any(
                int(section["va"]) <= target < int(section["end"])
                for section in executable
            )
            if not target_executable:
                outside_exec.append(row["entry_symbol"])
            if not (-(1 << 31) <= rel32 < (1 << 31)):
                bad_rel32.append(row["entry_symbol"])

        results.append(
            {
                "address": row["address"],
                "entry_symbol": row["entry_symbol"],
                "candidate_body_size": body_size,
                "diagnostic_map_body_extent": map_body_extent,
                "available_until_next_entry_or_text_end": gap,
                "placement_mode": mode,
                "current_diagnostic_body_va": f"0x{target:08x}" if target is not None else None,
                "rel32_displacement": rel32,
                "target_is_executable": target_executable,
            }
        )

    safe = (
        len(results) == fit_report["candidate_count"]
        and not unresolved
        and not outside_exec
        and not bad_rel32
        and all(item["placement_mode"] != "no-5-byte-thunk-slot" for item in results)
        and last_body_fit
    )
    report = {
        "scope": "Feasibility of direct entry placement or a 5-byte E9 rel32 thunk using the reference .text entry slots and current diagnostic-link body targets; no PE is emitted or modified.",
        "body_size_source": "COFF .xcode raw section size" if body_report else "linker-map COMDAT extent",
        "candidate_count": len(results),
        "whole_bodies_fit_bounded_entry_gaps": bodies_fit,
        "last_body_fits_reference_text_tail": last_body_fit,
        "rel32_thunks_required": trampoline_count,
        "minimum_gap_for_thunked_entries": min(trampoline_gaps) if trampoline_gaps else None,
        "thunked_entries_with_gap_below_5": sum(gap < 5 for gap in trampoline_gaps),
        "resolved_executable_body_targets": len(results) - len(unresolved) - len(outside_exec),
        "unresolved_symbols": unresolved,
        "targets_outside_executable_sections": outside_exec,
        "out_of_range_rel32_targets": bad_rel32,
        "feasibility_check_passed": safe,
        "limitations": [
            "The next mapped entry is only an upper-bound slot, not a verified original function extent.",
            "This checks space and reachability only; it does not generate or validate trampolines in a PE.",
            "It does not solve original .rdata/.data placement, base relocations, import/CRT startup, installer hook interactions, section layout, or GTA runtime behavior.",
            "The source bodies are validated candidates, not the unavailable original source/build recipe.",
        ],
        "inputs": {
            "entry_fit_report": str(args.fit_report),
            "authoritative_coff_body_report": str(args.body_report) if args.body_report else None,
            "diagnostic_map": str(args.map_path),
            "diagnostic_pe": str(args.diagnostic_pe),
            "reference_pe": str(args.reference_pe),
        },
        "entries": results,
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(
        f"entries={len(results)} body-fit={bodies_fit} last-tail-fit={last_body_fit} "
        f"rel32-thunks={trampoline_count} min-thunk-gap={min(trampoline_gaps)} "
        f"targets={len(results)-len(unresolved)-len(outside_exec)} "
        f"rel32-out-of-range={len(bad_rel32)} passed={safe}"
    )
    print(f"report={args.output}")
    return 0 if safe else 1


if __name__ == "__main__":
    raise SystemExit(main())
