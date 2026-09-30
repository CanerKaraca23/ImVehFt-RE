#!/usr/bin/env python3
"""Merge independently sourced target evidence for all 1,565 direct-body fields."""

from __future__ import annotations

import argparse
import hashlib
import json
from collections import Counter
from pathlib import Path


PINNED = {
    "original": "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3",
    "function": "D5FB08DDACD25ECFE2A9D22FA53FB91B47BFBC11D5BDA3E4FB48E05F0A86FB05",
    "body": "DDE0CC1F7D27CE133DAD0418C07EEDF61387786A8F54FCA70FD77E4F8B282AE7",
    "closure": "7A55587B41EB0396A07C0A75AD35C10EB44283CF95BAA717B20847D3A192A3C9",
}


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest().upper()


def as_int(value: int | str) -> int:
    return int(value, 16) if isinstance(value, str) and value.lower().startswith("0x") else int(value)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--original-asi", required=True, type=Path)
    ap.add_argument("--function-fixups", required=True, type=Path)
    ap.add_argument("--body-audit", required=True, type=Path)
    ap.add_argument("--direct-closure", required=True, type=Path)
    ap.add_argument("--output", required=True, type=Path)
    args = ap.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")
    if sha(args.original_asi) != PINNED["original"]:
        raise ValueError("original ASI hash mismatch")
    if sha(args.function_fixups) != PINNED["function"]:
        raise ValueError("function-fixup input hash mismatch")
    if sha(args.body_audit) != PINNED["body"]:
        raise ValueError("direct-body audit input hash mismatch")
    if sha(args.direct_closure) != PINNED["closure"]:
        raise ValueError("direct closure layout input hash mismatch")

    functions = json.loads(args.function_fixups.read_text(encoding="utf-8"))
    body = json.loads(args.body_audit.read_text(encoding="utf-8"))
    closure = json.loads(args.direct_closure.read_text(encoding="utf-8"))
    if functions.get("original_image_sha256") != PINNED["original"]:
        raise ValueError("function fixups are not based on pinned original")
    if body.get("all_raw_sites_accounted") is not True or body.get("all_source_hashes_match") is not True:
        raise ValueError("raw direct-body relocation audit is not clean")

    merged: dict[int, dict[str, object]] = {}

    def add(rva: int, kind: str, addend: int, value: int, source: str,
            owner: str, symbol: str = "", target_va: int | None = None) -> None:
        if kind not in ("DIR32", "REL32"):
            raise ValueError(f"unsupported direct fixup type {kind}")
        field = merged.get(rva)
        candidate = {"type": kind, "raw_addend": addend, "value": value & 0xFFFFFFFF}
        if field is None:
            merged[rva] = {
                "field_rva": rva, "type": kind, "raw_addend": addend,
                "computed_field_value": value & 0xFFFFFFFF,
                "owner_entry_va": owner, "symbol": symbol,
                "target_va": f"0x{target_va:08X}" if target_va is not None else None,
                "evidence_sources": [source],
            }
            return
        existing = {"type": field["type"], "raw_addend": field["raw_addend"],
                    "value": field["computed_field_value"]}
        if candidate != existing:
            raise ValueError(f"conflicting fixup evidence at RVA {rva:#x}: {existing} vs {candidate}")
        field["evidence_sources"].append(source)

    for row in functions["fixups"]:
        add(int(row["field_rva"], 16), row["relocation_type"],
            int(row["raw_addend"], 16), int(row["encoded_value"], 16),
            "candidate-function-symbol-crosswalk", row["caller_entry_va"], row["target_symbol"],
            int(row["candidate_target_entry_va"], 16) if row.get("candidate_target_entry_va") else None)

    for row in body["executable_target_value_checks"]:
        owner = int(row["owner_entry_va"], 16)
        rva = owner - 0x10000000 + int(row["field_offset"])
        add(rva, row["relocation_type"], int(row["raw_addend"], 16),
            int(row["computed_field_value"], 16), "raw-body-executable-target-audit",
            row["owner_entry_va"], target_va=int(row["target_va"], 16))

    for row in closure["fixups"]:
        if row.get("source_section", {}).get("section_name") != ".text":
            continue
        value = int(row["computed_field_value"])
        add(int(row["site_rva"], 16), row["relocation_type"], as_int(row["raw_addend"]),
            value, "direct-closure-placement-crosswalk", row["owner_entry_va"],
            row.get("symbol", ""), int(row["target_va"], 16))

    for row in body["exact_original_iat_sites"]:
        add(int(row["field_rva"], 16), row["type"], int(row["raw_addend"], 16),
            int(row["computed_preferred_value"], 16), "exact-original-IAT-crosswalk",
            row["owner_entry_va"], row["target_symbol"], int(row["preferred_iat_va"], 16))

    for row in body["exact_ghidra_vftable_sites"]:
        add(int(row["field_rva"], 16), row["type"], int(row["raw_addend"], 16),
            int(row["computed_preferred_value"], 16), "Ghidra-vftable-crosswalk",
            row["owner_entry_va"], row["target_symbol"], int(row["preferred_vftable_va"], 16))

    counts = Counter(row["type"] for row in merged.values())
    if len(merged) != 1565 or counts != {"DIR32": 800, "REL32": 765}:
        raise ValueError(f"direct fixup coverage mismatch: {len(merged)} fields {dict(counts)}")
    for row in merged.values():
        if row["type"] == "REL32":
            signed = row["computed_field_value"] if row["computed_field_value"] < 0x80000000 else row["computed_field_value"] - 0x100000000
            if not -(1 << 31) <= signed < (1 << 31):
                raise ValueError(f"REL32 field out of range at {row['field_rva']:#x}")
    report = {
        "scope": "Unified, site-keyed preferred-base values for all 1,565 direct-body COFF relocation fields.",
        "original_asi_sha256": PINNED["original"],
        "input_sha256": {"function_fixups": sha(args.function_fixups),
                         "body_audit": sha(args.body_audit), "direct_closure": sha(args.direct_closure)},
        "unique_fields": len(merged), "counts_by_type": dict(counts),
        "all_raw_sites_accounted": True, "all_conflicting_sources_agree": True,
        "candidate_dir32_highlow_sites": sum(1 for row in merged.values() if row["type"] == "DIR32"),
        "limitations": [
            "This is a preferred-base fixup manifest; it does not patch the original or a PE image.",
            "GTA executable targets are classified from the recorded Ghidra/original-image evidence; runtime ABI remains a separate gate.",
        ],
        "fixups": [merged[key] for key in sorted(merged)],
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    print(json.dumps({key: report[key] for key in (
        "unique_fields", "counts_by_type", "all_raw_sites_accounted", "all_conflicting_sources_agree"
    )}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
