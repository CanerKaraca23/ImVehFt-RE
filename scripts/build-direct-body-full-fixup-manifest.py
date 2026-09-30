#!/usr/bin/env python3
"""Join every current direct-body COFF relocation to one independently checked target."""

from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
import struct
from collections import Counter
from pathlib import Path


PINNED_ASI = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"
COVERAGE_SCRIPT = Path(__file__).with_name("audit-direct-body-relocation-coverage.py")


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def read(path: Path) -> tuple[bytes, dict]:
    raw = path.read_bytes()
    return raw, json.loads(raw)


def load_raw_parser():
    spec = importlib.util.spec_from_file_location("direct_coverage", COVERAGE_SCRIPT)
    if spec is None or spec.loader is None:
        raise RuntimeError("cannot load the authoritative direct COFF parser")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module.parse_entry_relocations


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    for name in ("original", "placement", "objects", "raw-report", "function-fixups",
                 "executable-targets", "local-layout", "api-plan", "coverage", "output"):
        ap.add_argument("--" + name, type=Path, required=True)
    a = ap.parse_args()
    if a.output.exists():
        raise FileExistsError(f"refusing to overwrite {a.output}")
    original = a.original.read_bytes()
    if sha(original) != PINNED_ASI:
        raise ValueError("original ASI hash differs from the pinned source")
    placements = json.loads(a.placement.read_text(encoding="utf-8"))
    raw_report = json.loads(a.raw_report.read_text(encoding="utf-8"))
    body_fixups = json.loads(a.function_fixups.read_text(encoding="utf-8"))
    executable = json.loads(a.executable_targets.read_text(encoding="utf-8"))
    local_layout = json.loads(a.local_layout.read_text(encoding="utf-8"))
    api_plan = json.loads(a.api_plan.read_text(encoding="utf-8"))
    coverage = json.loads(a.coverage.read_text(encoding="utf-8"))
    image_base = int(body_fixups["image_base"], 16)
    if body_fixups["original_image_sha256"] != PINNED_ASI:
        raise ValueError("function fixups use a different original image")
    if not coverage.get("all_source_hashes_match") or coverage.get("object_hash_mismatch_entries"):
        raise ValueError("direct-body object hash gate is not clean")
    if not coverage.get("all_raw_sites_accounted"):
        raise ValueError("coverage report does not account for every direct relocation")

    direct = [r for r in placements["entries"] if r["placement_mode"] == "body-at-entry"]
    raw_by_va = {int(r["entry_va"], 16): r for r in raw_report["results"]}
    parse_relocations = load_raw_parser()
    raw_sites: dict[tuple[str, int], dict] = {}
    for place in direct:
        entry = int(place["address"], 16)
        object_path = a.objects / f"{entry:08X}.obj"
        object_hash, relocs = parse_relocations(object_path, place["entry_symbol"])
        authoritative = raw_by_va.get(entry)
        if (authoritative is None or object_hash != authoritative["object_sha256"].upper()
                or len(relocs) != int(authoritative["coff_relocation_count"])):
            raise ValueError(f"{entry:#x}: COFF bytes do not match the pinned direct inventory")
        for reloc in relocs:
            key = (f"0x{entry:08X}", int(reloc["site"]))
            if key in raw_sites:
                raise ValueError(f"duplicate raw COFF site {key}")
            raw_sites[key] = {**reloc, "owner_entry_va": key[0], "raw_addend": int(reloc["raw_addend"])}

    targets: dict[tuple[str, int], list[dict]] = {}

    def add(owner: str, offset: int, target: int, source: str, **evidence: object) -> None:
        key = (f"0x{int(owner, 16):08X}", int(offset))
        if key not in raw_sites:
            raise ValueError(f"target evidence refers to no direct COFF relocation: {key} ({source})")
        targets.setdefault(key, []).append({"target_va": int(target), "source": source, **evidence})

    api_sites: set[tuple[str, int]] = set()
    for row in api_plan["rel32_patches"]:
        if row["callsite_class"] != "in-place-body":
            continue
        owner = f"0x{int(row['candidate_entry'], 16):08X}"
        field_rva = int(row["relocation_field_rva"], 16)
        offset = field_rva - (int(owner, 16) - image_base)
        key = (owner, offset)
        api_sites.add(key)
        add(owner, offset, int(row["replacement_thunk_va"], 16), "current-verified-API-thunk-plan",
            api_symbol=row["target_api_symbol"], api_plan_sha256=sha(a.api_plan.read_bytes()))

    for row in body_fixups["fixups"]:
        add(row["caller_entry_va"], int(row["field_offset"]),
            int(row["target_preferred_va"], 16), "COFF-symbol/Ghidra/IAT crosswalk",
            target_symbol=row["target_symbol"], binding_kind=row["target_binding_kind"])
    for row in executable["rows"]:
        owner = row["owner_entry_va"]
        key = (f"0x{int(owner, 16):08X}", int(row["field_offset"]))
        if key in api_sites:
            continue  # Current API plan supersedes the stale diagnostic-plan VA in this inventory.
        target = row.get("target", {})
        target_va = target.get("preferred_va") or target.get("iat_va")
        if target_va:
            add(owner, int(row["field_offset"]), int(target_va, 16), "Ghidra/pinned-image executable-target audit",
                target_symbol=row.get("symbol"), classification=row.get("classification"))
    for row in local_layout["fixups"]:
        if not row["origin"].startswith("direct-body-"):
            continue
        add(row["owner_entry_va"], int(row["site_offset"]), int(row["target_va"], 16),
            "hash-verified direct local-section layout", target_symbol=row.get("symbol"),
            origin=row["origin"])
    for row in coverage["exact_ghidra_vftable_sites"]:
        add(row["owner_entry_va"], int(row["site"]), int(row["preferred_vftable_va"], 16),
            "exact Ghidra vftable crosswalk into pinned original .rdata",
            target_symbol=row["target_symbol"])

    rows = []
    counts: Counter[str] = Counter()
    for key, raw in sorted(raw_sites.items()):
        found = targets.get(key, [])
        if not found:
            raise ValueError(f"unresolved direct COFF relocation {key}: {raw['target_symbol']}")
        values = {int(item["target_va"]) for item in found}
        if len(values) != 1:
            raise ValueError(f"conflicting exact target evidence for {key}: {found}")
        target_va = next(iter(values))
        kind = str(raw["type"])
        addend = int(raw["raw_addend"])
        site_va = int(key[0], 16) + key[1]
        if kind == "DIR32":
            value = target_va + addend
            if not 0 <= value <= 0xFFFFFFFF:
                raise ValueError(f"DIR32 overflow at {key}")
            highlow = True
        elif kind == "REL32":
            value = target_va + struct.unpack("<i", struct.pack("<I", addend))[0] - (site_va + 4)
            if not -(1 << 31) <= value < (1 << 31):
                raise ValueError(f"REL32 out of range at {key}")
            highlow = False
        else:
            raise ValueError(f"unsupported relocation type {kind} at {key}")
        counts[kind] += 1
        rows.append({
            "owner_entry_va": key[0], "field_offset": key[1],
            "field_va": f"0x{site_va:08X}", "field_rva": f"0x{site_va - image_base:08X}",
            "relocation_type": kind, "raw_addend": f"0x{addend:08X}",
            "target_symbol": raw["target_symbol"], "target_va": f"0x{target_va:08X}",
            "computed_field_value": f"0x{value & 0xFFFFFFFF:08X}",
            "base_relocation_required_at_field": highlow,
            "target_evidence": found,
        })

    if len(rows) != len(raw_sites) or len(rows) != int(coverage["counts"]["raw_relocation_sites"]):
        raise ValueError("manifest site count differs from complete raw relocation inventory")
    report = {
        "scope": "Full preferred-base fixups for every raw relocation in the 285 current direct bodies; all source sites reread from hash-pinned COFF objects. No bytes are patched.",
        "original_asi_sha256": PINNED_ASI,
        "placement_plan_sha256": sha(a.placement.read_bytes()),
        "objects_directory": str(a.objects.resolve()),
        "raw_relocation_report": str(a.raw_report.resolve()),
        "raw_relocation_report_sha256": sha(a.raw_report.read_bytes()),
        "api_plan": str(a.api_plan.resolve()),
        "api_plan_sha256": sha(a.api_plan.read_bytes()),
        "coverage_report": str(a.coverage.resolve()),
        "coverage_report_sha256": sha(a.coverage.read_bytes()),
        "direct_body_count": len(direct),
        "unique_fields": len(rows),
        "counts_by_type": dict(sorted(counts.items())),
        "all_raw_sites_have_one_unambiguous_target": True,
        "all_rel32_in_range": True,
        "all_source_objects_match_authoritative_hashes": True,
        "fixups": rows,
        "limitations": [
            "Preferred-base fields are computed but not yet written into a PE.",
            "Address/classification evidence does not establish semantic equivalence or initialization order.",
            "This does not validate imports, DllMain, startup, or GTA gameplay.",
        ],
    }
    a.output.parent.mkdir(parents=True, exist_ok=True)
    with a.output.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    print(json.dumps({"direct_body_count": len(direct), "unique_fields": len(rows),
                      "counts_by_type": report["counts_by_type"],
                      "all_raw_sites_have_one_unambiguous_target": True,
                      "all_rel32_in_range": True}, indent=2))
    print(f"report={a.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
