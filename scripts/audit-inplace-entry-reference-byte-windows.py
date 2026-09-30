#!/usr/bin/env python3
"""Compare Ghidra non-entry reference windows with current in-place candidates.

This is a triage audit only. Diagnostic-link bytes are not rebased/re-relocated
for the proposed original addresses, so byte differences are not by themselves
proof of a semantic break; matches are still useful evidence, not runtime proof.
"""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import struct
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_FEASIBILITY = ROOT / "audit/entry-trampoline-feasibility-reportfault-context-asm-linked-2026-09-29.json"
DEFAULT_XREFS = Path(r"C:\Users\caner\OneDrive\Documents\ImVehFt\ghidra_exports\text-nonentry-reference-audit-20260929.csv")
DEFAULT_CONTEXT = Path(r"C:\Users\caner\OneDrive\Documents\ImVehFt\ghidra_exports\text-nonentry-codeunit-context-20260929.csv")
DEFAULT_CANDIDATE = ROOT / "build/link-probe/entry-cookie-check-exact-rep-ret-20260929/ImVehFt-reportfault-context-linked-not-ASI.dll"
DEFAULT_ORIGINAL = Path(r"C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi")


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def load_pe(path: Path) -> tuple[bytes, int, list[dict[str, int | str]]]:
    data = path.read_bytes()
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    if data[:2] != b"MZ" or data[pe : pe + 4] != b"PE\0\0":
        raise ValueError(f"not a PE image: {path}")
    sections_count = struct.unpack_from("<H", data, pe + 6)[0]
    optional_size = struct.unpack_from("<H", data, pe + 20)[0]
    optional = pe + 24
    if struct.unpack_from("<H", data, optional)[0] != 0x10B:
        raise ValueError(f"expected PE32: {path}")
    image_base = struct.unpack_from("<I", data, optional + 28)[0]
    table = optional + optional_size
    sections = []
    for index in range(sections_count):
        off = table + index * 40
        name = data[off : off + 8].split(b"\0", 1)[0].decode("ascii", errors="replace")
        virtual_size, rva, raw_size, raw_offset = struct.unpack_from("<IIII", data, off + 8)
        sections.append({"name": name, "rva": rva, "va": image_base + rva,
                         "virtual_size": virtual_size, "raw_size": raw_size,
                         "raw_offset": raw_offset})
    return data, image_base, sections


def raw_offset(va: int, size: int, image_base: int, sections: list[dict[str, int | str]]) -> int:
    rva = va - image_base
    for section in sections:
        start = int(section["rva"])
        raw_size = int(section["raw_size"])
        if start <= rva and rva + size <= start + raw_size:
            return int(section["raw_offset"]) + rva - start
    raise ValueError(f"VA {va:#x}+{size:#x} is not backed by PE raw data")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--feasibility", type=Path, default=DEFAULT_FEASIBILITY)
    parser.add_argument("--xrefs", type=Path, default=DEFAULT_XREFS)
    parser.add_argument("--context", type=Path, default=DEFAULT_CONTEXT)
    parser.add_argument("--candidate", type=Path, default=DEFAULT_CANDIDATE)
    parser.add_argument("--original", type=Path, default=DEFAULT_ORIGINAL)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")

    feasibility = json.loads(args.feasibility.read_text(encoding="utf-8"))
    candidate, candidate_base, candidate_sections = load_pe(args.candidate)
    original, original_base, original_sections = load_pe(args.original)
    refs = list(csv.DictReader(args.xrefs.open(encoding="utf-8-sig", newline="")))
    contexts = list(csv.DictReader(args.context.open(encoding="utf-8-sig", newline="")))
    context_by_target = {int(row["target_va"], 16): row for row in contexts}

    entries = []
    for entry in feasibility["entries"]:
        start = int(entry["address"], 16)
        size = 5 if entry["placement_mode"] == "jmp-rel32-thunk" else int(entry["candidate_body_size"])
        entries.append((start, start + size, entry, size))

    overlaps = []
    for ref in refs:
        target = int(ref["target_va"], 16)
        for start, end, entry, overwrite_size in entries:
            if not start <= target < end:
                continue
            offset = target - start
            source = int(ref["source_va"], 16)
            source_owner = next((item for item in entries if item[0] <= source < item[1]), None)
            original_at = raw_offset(target, 8, original_base, original_sections)
            original_bytes = original[original_at : original_at + 8]
            if entry["placement_mode"] == "body-at-entry":
                body_va = int(entry["current_diagnostic_body_va"], 16)
                cand_at = raw_offset(body_va + offset, 8, candidate_base, candidate_sections)
                candidate_bytes = candidate[cand_at : cand_at + 8]
                proposed_bytes = candidate_bytes
                comparison = "diagnostic-linked candidate window; not rebased for in-place placement"
            else:
                destination = int(entry["current_diagnostic_body_va"], 16)
                displacement = (destination - (start + 5)) & 0xFFFFFFFF
                proposed_bytes = b"\xE9" + struct.pack("<I", displacement) + b"\x90\x90\x90"
                comparison = "hypothetical E9 thunk to diagnostic VA; final placement not built"
            context = context_by_target.get(target, {})
            overlaps.append({
                "entry_va": f"0x{start:08X}", "placement_mode": entry["placement_mode"],
                "overwritten_size": overwrite_size, "target_va": f"0x{target:08X}",
                "offset": offset, "source_va": ref["source_va"],
                "source_overwrite_owner_va": f"0x{source_owner[0]:08X}" if source_owner else None,
            "source_bytes_inside_candidate_overwrite": source_owner is not None,
                "source_and_target_same_overwrite": bool(source_owner and source_owner[0] == start),
                "reference_type": ref["reference_type"],
                "target_codeunit_type": context.get("target_unit_type"),
                "target_codeunit": context.get("target_unit"),
                "original_window_hex": original_bytes.hex(" ").upper(),
                "proposed_window_hex": proposed_bytes.hex(" ").upper(),
                "first_byte_equal": original_bytes[:1] == proposed_bytes[:1],
                "window_equal": original_bytes == proposed_bytes,
                "comparison_limit": comparison,
            })

    result = {
        "scope": "Ghidra non-entry reference destinations within actual proposed entry overwrite windows",
        "feasibility_report": str(args.feasibility),
        "original_sha256": sha256(original), "candidate_sha256": sha256(candidate),
        "ghidra_reference_rows": len(refs), "candidate_entries": len(entries),
        "overlapping_reference_rows": len(overlaps),
        "unique_overlapping_target_vas": len({row["target_va"] for row in overlaps}),
        "reference_source_bytes_inside_candidate_overwrite": sum(bool(row["source_bytes_inside_candidate_overwrite"]) for row in overlaps),
        "reference_source_bytes_outside_candidate_overwrite": sum(not row["source_bytes_inside_candidate_overwrite"] for row in overlaps),
        "exact_window_matches": sum(bool(row["window_equal"]) for row in overlaps),
        "partial_window_matches": sum(bool(row["first_byte_equal"]) and not row["window_equal"] for row in overlaps),
        "first_byte_mismatches": sum(not row["first_byte_equal"] for row in overlaps),
        "limitations": [
            "Ghidra reference export is bounded by its recorded references; indirect/dynamic references may be absent.",
            "The 8-byte code/data windows are only byte triage and may cross a codeunit boundary.",
            "Diagnostic-linked body bytes have not been relocated/rebased to the proposed original VA; byte mismatch is not a final semantic adjudication.",
            "No PE bytes were modified, and no candidate ASI or game load was produced.",
        ],
        "overlaps": overlaps,
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({key: value for key, value in result.items() if key != "overlaps"}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
