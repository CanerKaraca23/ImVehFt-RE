#!/usr/bin/env python3
"""Inventory referenced same-object sections reachable from direct 705-set bodies."""

from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
import struct
from collections import Counter, deque
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SYMBOL_AUDIT = ROOT / "scripts/audit-candidate-relocation-symbol-targets.py"
SECTION_AUDIT = ROOT / "scripts/audit-appended-thunk-local-section-closure.py"


def load_module(name: str, path: Path):
    spec = importlib.util.spec_from_file_location(name, path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot load {path}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest().upper()


def defined_external_symbols(path: Path) -> list[dict[str, object]]:
    data = path.read_bytes()
    machine, section_count, _, symbol_at, symbol_count, optional_size, _ = struct.unpack_from("<HHIIIHH", data, 0)
    if machine != 0x14C or optional_size:
        raise ValueError(f"{path.name}: expected IA-32 COFF object")
    section_names = []
    for index in range(section_count):
        at = 20 + index * 40
        section_names.append(
            struct.unpack_from("<8s", data, at)[0].split(b"\0", 1)[0].decode("ascii", errors="replace")
        )
    strings_at = symbol_at + symbol_count * 18
    string_size = struct.unpack_from("<I", data, strings_at)[0]
    strings = data[strings_at:strings_at + string_size]
    result = []
    index = 0
    at = symbol_at
    while index < symbol_count:
        record = data[at:at + 18]
        name = section_audit_name(data, strings_at, record[:8])
        value, section_number, _, storage_class, auxiliary_count = struct.unpack_from("<IhHBB", record, 8)
        if section_number > 0 and storage_class == 2:
            result.append({
                "symbol": name,
                "section_number": section_number,
                "section_name": section_names[section_number - 1],
                "value": value,
                "object": path.name,
            })
        index += 1 + auxiliary_count
        at += (1 + auxiliary_count) * 18
    return result


def section_audit_name(data: bytes, strings_at: int, field: bytes) -> str:
    if field[:4] != b"\0\0\0\0":
        return field.split(b"\0", 1)[0].decode("utf-8", errors="replace")
    offset = struct.unpack_from("<I", field, 4)[0]
    end = data.find(b"\0", strings_at + offset)
    if end < 0:
        raise ValueError("unterminated COFF symbol name")
    return data[strings_at + offset:end].decode("utf-8", errors="replace")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--objects", type=Path, required=True)
    parser.add_argument("--placement-plan", type=Path, required=True)
    parser.add_argument("--symbol-crosswalk", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")

    plan_bytes = args.placement_plan.read_bytes()
    crosswalk_bytes = args.symbol_crosswalk.read_bytes()
    plan = json.loads(plan_bytes)
    crosswalk = json.loads(crosswalk_bytes)
    if plan.get("candidate_count") != 705 or crosswalk["summary"].get("candidate_functions") != 705:
        raise ValueError("expected complete 705-entry inputs")

    objects_dir = args.objects.resolve()
    if Path(crosswalk["inputs"]["objects"]).resolve() != objects_dir:
        raise ValueError("object directory differs from that used by the symbol crosswalk")
    inplace_path = Path(crosswalk["inputs"]["placement_report"])
    inplace = json.loads(inplace_path.read_text(encoding="utf-8"))
    inplace_by_va = {int(row["entry_va"], 16): row for row in inplace["results"]}
    plan_by_va = {int(row["address"], 16): row for row in plan["entries"]}
    direct_vas = {
        va for va, row in plan_by_va.items()
        if row["placement_mode"] == "body-at-entry"
    }
    funcs = {int(row["entry_va"], 16): row for row in crosswalk["functions"]}
    expected_direct = int(plan.get("whole_bodies_fit_bounded_entry_gaps", -1))
    if (len(plan_by_va) != 705 or len(funcs) != 705
            or len(direct_vas) != expected_direct):
        raise ValueError("unexpected 705 plan / direct-body census")

    coff = load_module("coff_symbol_audit", SYMBOL_AUDIT)
    section_audit = load_module("same_object_section_audit", SECTION_AUDIT)
    definition_index: dict[str, list[dict[str, object]]] = {}
    object_files = sorted(objects_dir.glob("*.obj"))
    if len(object_files) != 705:
        raise ValueError(f"expected 705 candidate objects, got {len(object_files)}")
    provider_objects_hash_verified = 0
    for object_file in object_files:
        try:
            object_entry = int(object_file.stem, 16)
        except ValueError as exc:
            raise ValueError(f"unexpected object filename: {object_file.name}") from exc
        if object_entry not in inplace_by_va or sha256(object_file) != inplace_by_va[object_entry]["object_sha256"].upper():
            raise ValueError(f"{object_file.name}: object hash differs from authoritative 705-entry audit")
        provider_objects_hash_verified += 1
        for definition in defined_external_symbols(object_file):
            definition_index.setdefault(str(definition["symbol"]), []).append(definition)
    # Each queued key is the owning candidate object plus one of its section numbers.
    requested_by: dict[tuple[int, int], set[str]] = {}
    queue: deque[tuple[int, int]] = deque()
    edges: list[dict[str, object]] = []

    def request(owner: int, secno: int, why: str) -> None:
        key = (owner, secno)
        requested_by.setdefault(key, set()).add(why)
        if key not in queued_or_done:
            queued_or_done.add(key)
            queue.append(key)

    queued_or_done: set[tuple[int, int]] = set()
    body_local_edges = 0
    verified_objects: set[int] = set()
    for entry in sorted(direct_vas):
        obj_path = objects_dir / f"{entry:08x}.obj"
        if sha256(obj_path) != inplace_by_va[entry]["object_sha256"].upper():
            raise ValueError(f"{obj_path.name}: object hash differs from authoritative report")
        verified_objects.add(entry)
        parsed = coff.read_object(obj_path, plan_by_va[entry]["entry_symbol"])
        entry_section = int(parsed["entry_section_number"])
        for relocation in funcs[entry]["relocations"]:
            if not relocation["symbol_defined_in_object"]:
                continue
            secno = int(relocation["symbol_section_number"])
            if secno <= 0 or secno == entry_section:
                continue
            request(entry, secno, f"code+0x{int(relocation['offset']):x}:{relocation['symbol']}")
            body_local_edges += 1
            edges.append({
                "source_entry_va": f"0x{entry:08x}",
                "source_section": ".xcode",
                "source_field_offset": int(relocation["offset"]),
                "target_section_number": secno,
                "target_section_name": relocation["symbol_section"],
                "target_symbol": relocation["symbol"],
                "target_symbol_offset": int(relocation["symbol_value"]),
            })

    sections: dict[tuple[int, int], dict[str, object]] = {}
    while queue:
        entry, secno = queue.popleft()
        obj_path = objects_dir / f"{entry:08x}.obj"
        section = section_audit.inspect_object(obj_path, secno)
        sections[(entry, secno)] = section
        for relocation in section["relocations"]:
            if relocation["target_class"] != "same-object-section":
                continue
            target_secno = int(relocation["target_section_number"])
            if target_secno <= 0 or target_secno == secno:
                continue
            request(entry, target_secno, f"section{secno}+0x{int(relocation['site']):x}:{relocation['target_symbol']}")
            edges.append({
                "source_entry_va": f"0x{entry:08x}",
                "source_section_number": secno,
                "source_section": section["section_name"],
                "source_field_offset": int(relocation["site"]),
                "target_section_number": target_secno,
                "target_section_name": relocation["target_section"],
                "target_symbol": relocation["target_symbol"],
                "target_symbol_offset": int(relocation["target_value"]),
            })

    rows = []
    type_counts: Counter[str] = Counter()
    class_counts: Counter[str] = Counter()
    externals: Counter[tuple[str, str]] = Counter()
    for (entry, secno), section in sorted(sections.items()):
        if section["object_sha256"] != inplace_by_va[entry]["object_sha256"].upper():
            raise ValueError(f"{entry:#x} section {secno}: section-audit object hash mismatch")
        for relocation in section["relocations"]:
            type_counts[str(relocation["type"])] += 1
            class_counts[str(relocation["target_class"])] += 1
            if relocation["target_class"] == "undefined-external":
                externals[(str(relocation["target_symbol"]), str(relocation["type"]))] += 1
        rows.append({
            "source_entry_va": f"0x{entry:08x}",
            "reasons_referenced": sorted(requested_by[(entry, secno)]),
            **section,
        })

    names = Counter(str(row["section_name"]) for row in rows)
    provider_resolution = Counter()
    provider_rows = []
    for (symbol, kind), occurrences in sorted(externals.items()):
        definitions = definition_index.get(symbol, [])
        resolution = "unique-candidate-object-definition" if len(definitions) == 1 else (
            "multiple-candidate-object-definitions" if len(definitions) > 1 else "no-candidate-object-definition"
        )
        provider_resolution[resolution] += occurrences
        provider_rows.append({
            "symbol": symbol,
            "relocation_type": kind,
            "occurrences": occurrences,
            "resolution_class": resolution,
            "candidate_object_definitions": definitions,
        })
    report = {
        "scope": f"Recursive inventory of same-object sections referenced by the {len(direct_vas)} direct-body candidates; exact bytes/relocations only, not a final data layout or PE patch.",
        "placement_plan": str(args.placement_plan.resolve()),
        "placement_plan_sha256": hashlib.sha256(plan_bytes).hexdigest().upper(),
        "symbol_crosswalk": str(args.symbol_crosswalk.resolve()),
        "symbol_crosswalk_sha256": hashlib.sha256(crosswalk_bytes).hexdigest().upper(),
        "objects_directory": str(objects_dir),
        "object_hash_reference": str(inplace_path.resolve()),
        "summary": {
            "direct_body_count": len(direct_vas),
            "body_objects_hash_verified": len(verified_objects),
            "candidate_provider_objects_hash_verified": provider_objects_hash_verified,
            "direct_code_references_to_other_same_object_sections": body_local_edges,
            "recursive_same_object_section_count": len(rows),
            "sections_by_name": dict(sorted(names.items())),
            "total_section_virtual_bytes_including_bss": sum(int(row["section_bytes"]) for row in rows),
            "section_relocation_count": sum(type_counts.values()),
            "section_relocation_counts_by_type": dict(sorted(type_counts.items())),
            "section_relocation_target_classes": dict(sorted(class_counts.items())),
            "undefined_external_occurrences": sum(externals.values()),
            "unique_undefined_external_symbol_type_pairs": len(externals),
            "undefined_external_occurrences_by_candidate_definition_class": dict(sorted(provider_resolution.items())),
        },
        "unresolved_external_symbols": [
            {"symbol": symbol, "type": kind, "occurrences": count}
            for (symbol, kind), count in sorted(externals.items())
        ],
        "candidate_object_external_symbol_definitions": provider_rows,
        "limitations": [
            "Sections are audited per object; no global COMDAT/section-merging layout is chosen.",
            "Undefined external relocations in these sections need independent preferred-base target resolution.",
            "The direct-body plan does not prove dynamic references, object initialization/lifetime, or runtime behavior.",
            "No PE or candidate object is modified; no ASI, loader, or GTA test is produced.",
        ],
        "section_edges": edges,
        "sections": rows,
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
