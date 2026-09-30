#!/usr/bin/env python3
"""Resolve targets of same-object closure relocations from direct candidate bodies."""

from __future__ import annotations

import argparse
import hashlib
import json
import re
from collections import Counter
from pathlib import Path

import pefile


PINNED_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"
ADDRESS_PATTERNS = (
    ("IVF_RELOC_TARGET", re.compile(r"IVF_RELOC_TARGET_([0-9A-Fa-f]{8})")),
    ("DAT", re.compile(r"DAT_([0-9A-Fa-f]{8})")),
    ("PTR_vftable", re.compile(r"PTR_vftable_([0-9A-Fa-f]{8})")),
    ("PTR_LAB", re.compile(r"PTR_LAB_([0-9A-Fa-f]{8})")),
    ("PNG", re.compile(r"PNG_([0-9A-Fa-f]{8})")),
    ("s_ImVehFt", re.compile(r"s_ImVehFt_([0-9A-Fa-f]{8})")),
)
GHIDRA_ALIAS_TARGETS = {
    "_FID_conflict__sscanf": 0x100103E4,
    "_strncmp": 0x10010D8B,
}


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--closure-report", type=Path, required=True)
    parser.add_argument("--placement-plan", type=Path, required=True)
    parser.add_argument("--original", type=Path, required=True)
    parser.add_argument("--ghidra-export", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")

    closure_bytes = args.closure_report.read_bytes()
    plan_bytes = args.placement_plan.read_bytes()
    closure = json.loads(closure_bytes)
    plan = json.loads(plan_bytes)
    image = args.original.read_bytes()
    image_hash = sha256(image)
    if image_hash != PINNED_SHA256:
        raise ValueError(f"pinned original image hash mismatch: {image_hash}")
    pe = pefile.PE(data=image, fast_load=True)
    image_base = int(pe.OPTIONAL_HEADER.ImageBase)
    sections = []
    for sec in pe.sections:
        start = image_base + int(sec.VirtualAddress)
        sections.append({
            "name": sec.Name.rstrip(b"\0").decode("ascii", errors="replace"),
            "start": start,
            "end": start + max(int(sec.Misc_VirtualSize), int(sec.SizeOfRawData)),
            "raw_size": int(sec.SizeOfRawData),
        })

    plan_by_va = {int(row["address"], 16): row for row in plan["entries"]}
    if len(plan_by_va) != 705:
        raise ValueError("expected the complete 705-entry placement plan")
    definitions: dict[str, list[dict[str, object]]] = {}
    for row in closure["candidate_object_external_symbol_definitions"]:
        for definition in row["candidate_object_definitions"]:
            definitions.setdefault(str(row["symbol"]), []).append(definition)

    occurrence_rows: list[dict[str, object]] = []
    grouped_external: Counter[tuple[str, str, str]] = Counter()
    for section in closure["sections"]:
        for relocation in section["relocations"]:
            if relocation["target_class"] != "undefined-external":
                continue
            entry = int(section["source_entry_va"], 16)
            symbol = str(relocation["target_symbol"])
            kind = str(relocation["type"])
            grouped_external[(symbol, kind, section["source_entry_va"])] += 1

    for (symbol, kind, owner_va_text), count in sorted(grouped_external.items()):
        owner_va = int(owner_va_text, 16)
        matches = definitions.get(symbol, [])
        resolved_va = None
        evidence_class = None
        evidence: dict[str, object] = {}
        if len(matches) == 1:
            definition = matches[0]
            provider_entry = int(Path(str(definition["object"])).stem, 16)
            if (
                definition["section_name"] == ".xcode"
                and int(definition["value"]) == 0
                and provider_entry in plan_by_va
            ):
                resolved_va = provider_entry
                evidence_class = "unique-candidate-function-definition"
                evidence = {
                    "provider_object": definition["object"],
                    "provider_section": definition["section_name"],
                    "provider_symbol_value": int(definition["value"]),
                    "target_placement": plan_by_va[provider_entry]["placement_mode"],
                }

        if resolved_va is None and not matches:
            for pattern_name, pattern in ADDRESS_PATTERNS:
                match = pattern.search(symbol)
                if not match:
                    continue
                candidate_va = int(match.group(1), 16)
                owner = next((s for s in sections if s["start"] <= candidate_va < s["end"]), None)
                if owner is None:
                    evidence_class = "address-encoded-but-unmapped"
                    evidence = {"encoding_pattern": pattern_name, "encoded_va": f"0x{candidate_va:08x}"}
                    break
                delta = candidate_va - owner["start"]
                resolved_va = candidate_va
                evidence_class = "address-encoded-in-original-image"
                evidence = {
                    "encoding_pattern": pattern_name,
                    "original_section": owner["name"],
                    "original_section_offset": f"0x{delta:08x}",
                    "backing": "raw-backed" if delta < owner["raw_size"] else "virtual-only",
                }
                break

        if resolved_va is None and not matches and symbol in GHIDRA_ALIAS_TARGETS:
            candidate_va = GHIDRA_ALIAS_TARGETS[symbol]
            export_path = args.ghidra_export / f"{owner_va:08x}.json"
            if not export_path.exists():
                raise ValueError(f"missing Ghidra export for alias owner {owner_va:#x}")
            owner_export = json.loads(export_path.read_text(encoding="utf-8"))
            callee_exists = any(int(row["addr"], 16) == candidate_va for row in owner_export.get("callees", []))
            call_count = sum(
                1 for line in owner_export.get("assembly", [])
                if re.search(rf"\bCALL\s+0x{candidate_va:08x}\b", str(line), re.IGNORECASE)
            )
            if not callee_exists or call_count < count:
                raise ValueError(
                    f"Ghidra does not support alias {symbol} from {owner_va:#x} to {candidate_va:#x}"
                )
            if candidate_va not in plan_by_va:
                raise ValueError(f"Ghidra alias target {candidate_va:#x} is not a candidate entry")
            resolved_va = candidate_va
            evidence_class = "ghidra-callee-alias-to-candidate-entry"
            evidence = {
                "ghidra_export": str(export_path.resolve()),
                "callee_name": next(
                    row["name"] for row in owner_export["callees"]
                    if int(row["addr"], 16) == candidate_va
                ),
                "ghidra_call_instruction_count": call_count,
                "target_placement": plan_by_va[candidate_va]["placement_mode"],
            }

        occurrence_rows.append({
            "symbol": symbol,
            "relocation_type": kind,
            "source_entry_va": owner_va_text,
            "occurrences_in_source_entry": count,
            "target_va": f"0x{resolved_va:08x}" if resolved_va is not None else None,
            "resolution_class": evidence_class or "unresolved-or-ambiguous",
            "evidence": evidence,
            "candidate_definition_count": len(matches),
        })

    class_counts: Counter[str] = Counter()
    unresolved = []
    total_occurrences = 0
    for row in occurrence_rows:
        cls = str(row["resolution_class"])
        occurrences = int(row["occurrences_in_source_entry"])
        class_counts[cls] += occurrences
        total_occurrences += occurrences
        if row["target_va"] is None:
            unresolved.append(row)

    report = {
        "scope": "Preferred-base target resolution for undefined externals in the recursive local-section closure of 284 direct candidate bodies. Source section placement and encoded fixup values are not included.",
        "closure_report": str(args.closure_report.resolve()),
        "closure_report_sha256": sha256(closure_bytes),
        "placement_plan": str(args.placement_plan.resolve()),
        "placement_plan_sha256": hashlib.sha256(plan_bytes).hexdigest().upper(),
        "original_image": str(args.original.resolve()),
        "original_image_sha256": image_hash,
        "ghidra_export_directory": str(args.ghidra_export.resolve()),
        "summary": {
            "undefined_external_symbol_owner_groups": len(occurrence_rows),
            "undefined_external_relocation_occurrences": total_occurrences,
            "occurrences_by_resolution_class": dict(sorted(class_counts.items())),
            "unresolved_owner_symbol_groups": len(unresolved),
            "unresolved_relocation_occurrences": sum(int(row["occurrences_in_source_entry"]) for row in unresolved),
        },
        "limitations": [
            "Address-encoded names establish a preferred-base address and section membership, not data type, initialization, or lifetime.",
            "Candidate function bindings establish target entry VAs; REL32 values still depend on final section placement.",
            "Ghidra alias adjudications prove the original call target for the listed owner, not the behavior of the reconstructed full image.",
            "No target value is written into a PE; no ASI, loader, or GTA runtime test is performed.",
        ],
        "resolved_targets": occurrence_rows,
        "unresolved_targets": unresolved,
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    print(json.dumps(report["summary"], indent=2))
    print(f"report={args.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
