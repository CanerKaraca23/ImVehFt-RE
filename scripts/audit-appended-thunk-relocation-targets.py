#!/usr/bin/env python3
"""Classify COFF fixup targets in current 147 thunk-required entry bodies."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from collections import Counter, defaultdict
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_OBJECTS = ROOT / "build/recheck/strict-xcode-nogs-o1-1001cb37-add-esp-20260929"
DEFAULT_FEASIBILITY = ROOT / "audit/entry-trampoline-feasibility-final-current-2026-09-29.json"
RELOC_NAMES = {0x0006: "DIR32", 0x0014: "REL32", 0x000A: "SECTION", 0x000B: "SECREL"}


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def cstr(data: bytes) -> str:
    return data.split(b"\0", 1)[0].decode("utf-8", errors="replace")


def read_coff(path: Path, entry_symbol: str) -> tuple[dict[str, object], list[dict[str, object]]]:
    data = path.read_bytes()
    machine, section_count, _, symbol_offset, symbol_count, optional_size, _ = struct.unpack_from("<HHIIIHH", data)
    if machine != 0x14C:
        raise ValueError(f"{path}: not i386 COFF")
    section_table = 20 + optional_size
    sections = []
    for i in range(section_count):
        at = section_table + i * 40
        name, _, _, raw_size, raw_offset, reloc_offset, _, reloc_count, _, flags = struct.unpack_from("<8sIIIIIIHHI", data, at)
        raw_bytes = data[raw_offset:raw_offset + raw_size] if raw_size else b""
        sections.append({"number": i + 1, "name": cstr(name), "size": raw_size, "raw": raw_offset,
                         "reloc": reloc_offset, "reloc_count": reloc_count, "flags": flags,
                         "alignment_log2": (flags >> 20) & 0xF,
                         "content_sha256": sha256(raw_bytes)})
    string_at = symbol_offset + symbol_count * 18
    string_size = struct.unpack_from("<I", data, string_at)[0]
    strings = data[string_at:string_at + string_size]

    symbols: dict[int, dict[str, object]] = {}
    i = 0
    at = symbol_offset
    while i < symbol_count:
        raw = data[at:at + 18]
        name_field = raw[:8]
        if name_field[:4] == b"\0\0\0\0":
            name_offset = struct.unpack_from("<I", name_field, 4)[0]
            end = strings.find(b"\0", name_offset)
            name = strings[name_offset:end].decode("utf-8", errors="replace") if end >= 0 else ""
        else:
            name = cstr(name_field)
        value, section_num, sym_type, storage, aux = struct.unpack_from("<IhHBB", raw, 8)
        symbols[i] = {"name": name, "value": value, "section_number": section_num,
                      "type": sym_type, "storage_class": storage}
        i += 1 + aux
        at += (1 + aux) * 18

    definitions = [s for s in symbols.values() if s["name"] == entry_symbol]
    if len(definitions) != 1:
        raise ValueError(f"{path.name}: expected one root symbol {entry_symbol!r}")
    root = definitions[0]
    if root["section_number"] <= 0 or root["value"] != 0:
        raise ValueError(f"{path.name}: root symbol is not section offset zero")
    root_section = sections[int(root["section_number"]) - 1]
    if root_section["name"] != ".xcode":
        raise ValueError(f"{path.name}: expected root in .xcode, got {root_section['name']}")

    relocations: list[dict[str, object]] = []
    for ri in range(int(root_section["reloc_count"])):
        r_at = int(root_section["reloc"]) + ri * 10
        site, symbol_index, kind = struct.unpack_from("<IIH", data, r_at)
        if symbol_index not in symbols:
            raise ValueError(f"{path.name}: relocation references missing symbol index {symbol_index}")
        target = symbols[symbol_index]
        sec_num = int(target["section_number"])
        target_section = "UNDEFINED" if sec_num == 0 else "ABSOLUTE" if sec_num == -1 else sections[sec_num - 1]["name"]
        target_meta = sections[sec_num - 1] if sec_num > 0 else {}
        relocations.append({"site": site, "type": RELOC_NAMES.get(kind, f"0x{kind:04X}"),
                            "symbol_index": symbol_index, "target_symbol": target["name"],
                            "target_value": target["value"], "target_section_number": sec_num,
                            "target_section": target_section,
                            "target_section_size": target_meta.get("size"),
                            "target_section_relocation_count": target_meta.get("reloc_count"),
                            "target_section_sha256": target_meta.get("content_sha256")})
    referenced_rdata_numbers = {int(r["target_section_number"]) for r in relocations
                                if r["target_section"] == ".rdata"}
    local_rdata_sections = []
    for section_number in sorted(referenced_rdata_numbers):
        section = sections[section_number - 1]
        section_relocations = []
        for ri in range(int(section["reloc_count"])):
            r_at = int(section["reloc"]) + ri * 10
            site, symbol_index, kind = struct.unpack_from("<IIH", data, r_at)
            target = symbols.get(symbol_index)
            if target is None:
                raise ValueError(f"{path.name}: .rdata relocation references missing symbol {symbol_index}")
            sec_num = int(target["section_number"])
            section_relocations.append({
                "site": site, "type": RELOC_NAMES.get(kind, f"0x{kind:04X}"),
                "target_symbol": target["name"], "target_value": target["value"],
                "target_section_number": sec_num,
                "target_section": "UNDEFINED" if sec_num == 0 else "ABSOLUTE" if sec_num == -1 else sections[sec_num - 1]["name"],
            })
        local_rdata_sections.append({
            "section_number": section_number, "raw_size": section["size"],
            "alignment_log2": section["alignment_log2"],
            "raw_bytes_sha256": section["content_sha256"],
            "relocations": section_relocations,
        })
    definitions = []
    for sym_index, symbol in symbols.items():
        if symbol["section_number"] > 0 and symbol["storage_class"] == 2:
            sec = sections[int(symbol["section_number"]) - 1]
            definitions.append({"name": symbol["name"], "value": symbol["value"],
                                "section": sec["name"]})
    return {"object_sha256": sha256(data), "body_size": root_section["size"],
            "definitions": definitions, "local_rdata_sections": local_rdata_sections}, relocations


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--objects", type=Path, default=DEFAULT_OBJECTS)
    p.add_argument("--feasibility", type=Path, default=DEFAULT_FEASIBILITY)
    p.add_argument("--output", type=Path, required=True)
    p.add_argument("--expected-thunk-count", type=int, default=147)
    a = p.parse_args()
    if a.output.exists():
        raise FileExistsError(f"refusing to overwrite {a.output}")
    feasibility_bytes = a.feasibility.read_bytes()
    feasibility = json.loads(feasibility_bytes)
    if feasibility.get("candidate_count") != 705:
        raise ValueError("expected current full-set feasibility report")
    entry_symbols = {row["entry_symbol"] for row in feasibility["entries"]}
    selected = [row for row in feasibility["entries"] if row["placement_mode"] == "jmp-rel32-thunk"]
    if len(entry_symbols) != 705 or len(selected) != a.expected_thunk_count:
        raise ValueError(f"expected 705 unique roots and {a.expected_thunk_count} thunk bodies")

    by_type_class: Counter[tuple[str, str]] = Counter()
    unresolved_by_type: dict[str, Counter[str]] = defaultdict(Counter)
    reloc_rows = []
    local_target_sections: dict[tuple[str, int], dict[str, object]] = {}
    object_hashes = hashlib.sha256()
    definitions: dict[str, list[dict[str, str]]] = defaultdict(list)
    parsed: dict[int, tuple[dict[str, object], list[dict[str, object]]]] = {}
    for entry in feasibility["entries"]:
        va = int(entry["address"], 16)
        info, relocs = read_coff(a.objects / f"{va:08x}.obj", entry["entry_symbol"])
        if info["body_size"] != entry["candidate_body_size"]:
            raise ValueError(f"{va:#x}: stale COFF body size")
        if entry["placement_mode"] == "jmp-rel32-thunk":
            object_hashes.update(bytes.fromhex(str(info["object_sha256"])))
            parsed[va] = (info, relocs)
        for definition in info["definitions"]:
            definitions[str(definition["name"])].append({
                "entry": entry["address"], "section": str(definition["section"]),
                "value": str(definition["value"]),
            })

    for entry in selected:
        va = int(entry["address"], 16)
        info, relocs = parsed[va]
        for reloc in relocs:
            target_name = str(reloc["target_symbol"])
            if target_name in entry_symbols:
                target_class = "candidate-root"
            elif reloc["target_section"] == "UNDEFINED" and target_name in definitions:
                target_class = "defined-by-other-candidate-object"
                reloc["candidate_object_definitions"] = definitions[target_name]
            elif reloc["target_section"] == "UNDEFINED":
                target_class = "unresolved-external-or-alias"
                unresolved_by_type[str(reloc["type"])][target_name] += 1
            else:
                target_class = "defined-in-same-object-section"
            by_type_class[(str(reloc["type"]), target_class)] += 1
            reloc_rows.append({"source_entry": entry["address"], **reloc,
                               "target_class": target_class})
            if target_class == "defined-in-same-object-section":
                key = (str(entry["address"]), int(reloc["target_section_number"]))
                local_target_sections[key] = {
                    "source_entry": entry["address"],
                    "section_number": reloc["target_section_number"],
                    "section": reloc["target_section"],
                    "raw_size": reloc["target_section_size"],
                    "coff_relocation_count": reloc["target_section_relocation_count"],
                    "raw_bytes_sha256": reloc["target_section_sha256"],
                }

    local_rdata_sections = []
    for entry in selected:
        va = int(entry["address"], 16)
        info, _ = parsed[va]
        for section in info["local_rdata_sections"]:
            local_rdata_sections.append({"source_entry": entry["address"], **section})

    summary = {
        "scope": "Current-object COFF symbol-target classification only; no final PE symbol resolution or patching.",
        "feasibility_sha256": sha256(feasibility_bytes),
        "ordered_object_set_sha256": object_hashes.hexdigest().upper(),
        "candidate_roots": len(entry_symbols),
        "candidate_objects_scanned_for_definitions": len(feasibility["entries"]),
        "thunk_bodies": len(selected),
        "relocation_count": len(reloc_rows),
        "counts_by_type_and_target_class": [
            {"type": kind, "target_class": target_class, "count": count}
            for (kind, target_class), count in sorted(by_type_class.items())
        ],
        "unresolved_external_or_alias_symbols_by_type": {
            kind: dict(sorted(counts.items())) for kind, counts in sorted(unresolved_by_type.items())
        },
        "same_object_sections_referenced": list(local_target_sections.values()),
        "same_object_section_raw_bytes_total_if_copied_per_object": sum(
            int(row["raw_size"] or 0) for row in local_target_sections.values()
        ),
        "same_object_rdata_sections_referenced": local_rdata_sections,
        "same_object_rdata_raw_bytes_total_if_copied_per_object": sum(
            int(row["raw_size"] or 0) for row in local_rdata_sections
        ),
        "same_object_rdata_relocation_count": sum(
            len(row["relocations"]) for row in local_rdata_sections
        ),
        "limitations": [
            "A COFF undefined symbol is not resolved here; the diagnostic PE/map or explicit alias providers must supply its final VA.",
            "Candidate-root classification uses the exact 705 current entry symbols; same-object static data and helper sections require their own placement handling.",
            "DIR32 values need correct preferred-base fixups and HIGHLOW directory records; REL32 values must be rewritten for final addresses.",
            "This audit does not establish import/startup correctness, PE loader acceptance, or game behavior.",
        ],
        "relocations": reloc_rows,
    }
    a.output.parent.mkdir(parents=True, exist_ok=True)
    a.output.write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({k: summary[k] for k in ("candidate_roots", "thunk_bodies", "relocation_count", "counts_by_type_and_target_class")}, indent=2))
    print(f"report={a.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
