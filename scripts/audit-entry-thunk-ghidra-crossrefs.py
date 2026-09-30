#!/usr/bin/env python3
"""Cross-reference planned entry thunks with base relocations and Ghidra branches."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import re
from collections import Counter
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_GHIDRA = Path(r"C:\Users\caner\OneDrive\Documents\ImVehFt\ghidra_exports")
BRANCH = re.compile(r"\b(?:CALL|JMP|J[A-Z]{1,5})\s+(?:0x)?([0-9a-fA-F]{8})\b")
INSTRUCTION_ADDRESS = re.compile(r"^([0-9a-fA-F]{8})\s+")


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest().upper()


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--feasibility", type=Path, required=True)
    parser.add_argument("--overlaps", type=Path, required=True)
    parser.add_argument("--ghidra-exports", type=Path, default=DEFAULT_GHIDRA)
    parser.add_argument("--ghidra-address-csv", type=Path, help="write a GhidraReadOnlyAddressSymbols input CSV for thunk bytes")
    parser.add_argument("--ghidra-xref-csv", type=Path, help="consume read-only GhidraReadOnlyAddressSymbols output CSV")
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")

    feasibility = json.loads(args.feasibility.read_text(encoding="utf-8"))
    overlap_report = json.loads(args.overlaps.read_text(encoding="utf-8"))
    thunks = {
        int(row["address"], 16): row
        for row in feasibility["entries"]
        if row["placement_mode"] == "jmp-rel32-thunk"
    }
    if len(feasibility["entries"]) != 705 or not thunks or len(thunks) > 705:
        raise ValueError("expected 705 entries and a nonempty rel32-thunk set")
    if args.ghidra_address_csv:
        if args.ghidra_address_csv.exists():
            if not args.ghidra_xref_csv:
                raise FileExistsError(f"refusing to overwrite {args.ghidra_address_csv}")
        else:
            args.ghidra_address_csv.parent.mkdir(parents=True, exist_ok=True)
            with args.ghidra_address_csv.open("x", encoding="utf-8", newline="") as stream:
                writer = csv.writer(stream)
                writer.writerow(["address", "entry", "offset"])
                for entry in sorted(thunks):
                    for offset in range(5):
                        writer.writerow([f"0x{entry + offset:08x}", f"0x{entry:08x}", offset])

    exports: list[tuple[Path, dict[str, object]]] = []
    for path in sorted(args.ghidra_exports.glob("*.json")):
        try:
            payload = json.loads(path.read_text(encoding="utf-8"))
        except (UnicodeDecodeError, json.JSONDecodeError):
            continue
        if isinstance(payload, dict) and isinstance(payload.get("assembly"), list):
            exports.append((path, payload))

    interior_refs: list[dict[str, str]] = []
    for _, payload in exports:
        source = str(payload.get("address", "unknown"))
        for line in payload["assembly"]:
            match = BRANCH.search(str(line))
            if not match:
                continue
            target = int(match.group(1), 16)
            for entry in thunks:
                if entry < target < entry + 5:
                    interior_refs.append(
                        {
                            "source_function": source,
                            "thunk_entry": f"0x{entry:08x}",
                            "interior_target": f"0x{target:08x}",
                            "instruction": str(line),
                        }
                    )

    relocation_hits = [
        row
        for row in overlap_report["overlaps"]
        if int(row["entry_va"], 16) in thunks
    ]
    if len(overlap_report["overlaps"]) != 97:
        raise ValueError("unexpected source audit: expected 97 overlaps across all 705 entries")
    details = []
    for hit in relocation_hits:
        entry = int(hit["entry_va"], 16)
        path = args.ghidra_exports / f"{entry:08x}.json"
        payload = json.loads(path.read_text(encoding="utf-8"))
        assembly = payload.get("assembly", [])
        site = int(hit["relocation_site_va"], 16)
        parsed_instructions = []
        for instruction in assembly:
            match = INSTRUCTION_ADDRESS.match(str(instruction))
            if match:
                parsed_instructions.append((int(match.group(1), 16), str(instruction)))
        containing_instruction = next(
            (line for address, line in reversed(parsed_instructions) if address <= site),
            None,
        )
        details.append(
            {
                **hit,
                "ghidra_function_name": payload.get("name"),
                "ghidra_instruction_containing_highlow_site": containing_instruction,
                "ghidra_assembly_first_5_instructions": assembly[:5],
                "direct_branch_refs_to_thunk_interior": [
                    row for row in interior_refs if row["thunk_entry"] == hit["entry_va"]
                ],
            }
        )

    counts = Counter(
        "fully_overwritten" if row["fixup_bytes_fully_overwritten"] else "partially_intersected"
        for row in relocation_hits
    )
    xref_summary: dict[str, object] | None = None
    xref_interior_hits: list[dict[str, str]] = []
    xref_entry_unreferenced: list[str] = []
    if args.ghidra_xref_csv:
        if not args.ghidra_address_csv:
            raise ValueError("--ghidra-xref-csv requires the matching --ghidra-address-csv")
        with args.ghidra_address_csv.open(encoding="utf-8-sig", newline="") as stream:
            address_rows = {
                row["address"].lower().removeprefix("0x"): row
                for row in csv.DictReader(stream)
            }
        with args.ghidra_xref_csv.open(encoding="utf-8-sig", newline="") as stream:
            xref_rows = {
                row["address"].lower().removeprefix("0x"): row
                for row in csv.DictReader(stream)
            }
        if len(address_rows) != 740 or len(xref_rows) != 740 or address_rows.keys() != xref_rows.keys():
            raise ValueError("address and Ghidra xref CSVs must contain the same 740 unique thunk-byte addresses")
        entries_with_refs = set()
        for key, address_row in address_rows.items():
            xref_row = xref_rows[key]
            if xref_row["incoming_references"].strip():
                entry = address_row["entry"]
                if address_row["offset"] == "0":
                    entries_with_refs.add(entry)
                else:
                    xref_interior_hits.append(
                        {
                            "entry": entry,
                            "offset": address_row["offset"],
                            "address": xref_row["address"],
                            "incoming_references": xref_row["incoming_references"],
                        }
                    )
        xref_entry_unreferenced = sorted(
            f"0x{entry:08x}" for entry in thunks
            if f"0x{entry:08x}" not in entries_with_refs
        )
        xref_summary = {
            "address_count": len(xref_rows),
            "interior_byte_addresses_with_recorded_incoming_refs": len(xref_interior_hits),
            "thunk_entry_addresses_with_recorded_incoming_refs": len(entries_with_refs),
            "thunk_entries_without_recorded_incoming_refs": len(xref_entry_unreferenced),
            "xref_data_source": "existing Ghidra project via analyzeHeadless -readOnly -noanalysis",
            "xref_csv_sha256": sha256(args.ghidra_xref_csv),
            "queried_address_csv_sha256": sha256(args.ghidra_address_csv),
        }
    report = {
        "scope": f"Cross-reference of {len(thunks)} planned 5-byte entry thunk windows against original .text HIGHLOW relocation ranges and direct branch targets in available Ghidra function exports; no PE bytes are changed.",
        "inputs": {
            "feasibility_report": str(args.feasibility.resolve()),
            "feasibility_sha256": sha256(args.feasibility),
            "overlap_report": str(args.overlaps.resolve()),
            "overlap_report_sha256": sha256(args.overlaps),
            "ghidra_export_directory": str(args.ghidra_exports.resolve()),
            "ghidra_export_count_with_assembly": len(exports),
        },
        "summary": {
            "thunk_windows": len(thunks),
            "thunk_windows_intersecting_highlow": len(relocation_hits),
            "highlow_overlap_classes": dict(sorted(counts.items())),
            "direct_branch_refs_into_thunk_interior": len(interior_refs),
            "ghidra_export_functions_scanned": len(exports),
            "ghidra_project_xref_summary": xref_summary,
        },
        "limitations": [
            "No direct CALL/JMP target in the exported assembly is not proof that indirect branches, function pointers, unexported code, or data references cannot enter the overwritten bytes.",
            "Intersecting HIGHLOW entries must be reconciled by a final-image builder; this report does not prove that removing them is safe for any remaining bytes or alternate entry paths.",
            "The Ghidra export assembly is evidence from the analyzed binary, not source-level or runtime proof.",
            "An empty Ghidra ReferenceManager result means no recorded reference at that exact byte in this project snapshot; it does not exclude undiscovered indirect targets, runtime-computed addresses, or absent/undefined references.",
        ],
        "overlaps": details,
        "direct_branch_refs": interior_refs,
        "ghidra_project_interior_byte_xref_hits": xref_interior_hits,
        "thunk_entries_without_recorded_project_xrefs": xref_entry_unreferenced,
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(
        f"thunks={len(thunks)} highlow-overlap={len(relocation_hits)} "
        f"fully-overwritten={counts['fully_overwritten']} "
        f"partial={counts['partially_intersected']} "
        f"direct-interior-branches={len(interior_refs)} exports={len(exports)}"
    )
    print(f"report={args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
