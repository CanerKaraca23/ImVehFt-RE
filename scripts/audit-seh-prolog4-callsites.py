#!/usr/bin/env python3
"""Compare Ghidra __SEH_prolog4 call stacks with current COFF callers."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path


REL32 = 0x0014
DIR32 = 0x0006


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def cstring(table: bytes, offset: int) -> str:
    end = table.find(b"\0", offset)
    if end < 0:
        raise ValueError("unterminated COFF symbol string")
    return table[offset:end].decode("utf-8", errors="replace")


def parse_entry_object(path: Path, expected_symbol: str) -> tuple[bytes, list[dict], str]:
    data = path.read_bytes()
    if len(data) < 20:
        raise ValueError("truncated COFF header")
    machine, section_count, _, symbol_pointer, symbol_count, optional_size, _ = struct.unpack_from(
        "<HHIIIHH", data, 0
    )
    if machine != 0x14C:
        raise ValueError(f"unexpected COFF machine {machine:#x}")
    section_table = 20 + optional_size
    sections = []
    for index in range(section_count):
        offset = section_table + index * 40
        name, _, _, raw_size, raw_pointer, reloc_pointer, _, reloc_count, _, flags = struct.unpack_from(
            "<8sIIIIIIHHI", data, offset
        )
        sections.append({
            "name": name.split(b"\0", 1)[0].decode("ascii", errors="replace"),
            "size": raw_size, "raw": raw_pointer, "reloc": reloc_pointer,
            "reloc_count": reloc_count, "flags": flags,
        })
    strings_offset = symbol_pointer + symbol_count * 18
    strings_size = struct.unpack_from("<I", data, strings_offset)[0]
    strings = data[strings_offset:strings_offset + strings_size]
    symbols: dict[int, dict] = {}
    root = None
    index, cursor = 0, symbol_pointer
    while index < symbol_count:
        row = data[cursor:cursor + 18]
        if len(row) != 18:
            raise ValueError("truncated COFF symbol")
        name_field = row[:8]
        name = cstring(strings, struct.unpack_from("<I", name_field, 4)[0]) if name_field[:4] == b"\0\0\0\0" else name_field.split(b"\0", 1)[0].decode("utf-8", errors="replace")
        value, section_number, sym_type, storage, aux_count = struct.unpack_from("<IhHBB", row, 8)
        symbols[index] = {"name": name, "value": value, "section": section_number,
                          "type": sym_type, "storage": storage}
        if name == expected_symbol:
            if root is not None:
                raise ValueError(f"duplicate entry symbol {expected_symbol}")
            root = symbols[index]
        index += 1 + aux_count
        cursor += (1 + aux_count) * 18
    if root is None or root["section"] <= 0 or root["section"] > len(sections):
        raise ValueError(f"entry symbol missing or undefined: {expected_symbol}")
    section = sections[root["section"] - 1]
    if section["name"] != ".xcode":
        raise ValueError(f"entry symbol is not in .xcode: {section['name']}")
    body = data[section["raw"]:section["raw"] + section["size"]]
    relocs = []
    for i in range(section["reloc_count"]):
        offset = section["reloc"] + i * 10
        site, symbol_index, kind = struct.unpack_from("<IIH", data, offset)
        target = symbols.get(symbol_index, {}).get("name", f"symbol-index-{symbol_index}")
        relocs.append({"site": site, "type": kind, "target": target})
    return body, relocs, sha(data)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--repo", type=Path, required=True)
    ap.add_argument("--objects", type=Path, required=True)
    ap.add_argument("--ghidra-export", type=Path, required=True)
    ap.add_argument("--placement", type=Path, required=True)
    ap.add_argument("--output", type=Path, required=True)
    args = ap.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")

    placement = json.loads(args.placement.read_text(encoding="utf-8"))
    symbols = {row["address"].lower().removeprefix("0x"): row["entry_symbol"]
               for row in placement["entries"]}
    rows = []
    for export in sorted(args.ghidra_export.glob("*.json")):
        try:
            ghidra = json.loads(export.read_text(encoding="utf-8"))
        except (UnicodeDecodeError, json.JSONDecodeError):
            continue
        address = str(ghidra.get("address", "")).lower().removeprefix("0x")
        assembly = ghidra.get("assembly") or []
        calls = [i for i, line in enumerate(assembly) if "CALL 0X10012E20" in line.upper()]
        if not calls:
            continue
        if address not in symbols:
            rows.append({"address": f"0x{address}", "name": ghidra.get("name"),
                         "error": "Ghidra caller has no candidate translation unit"})
            continue
        source_path = args.repo / "src/functions" / f"{address}.cpp"
        object_path = args.objects / f"{address}.obj"
        source = source_path.read_text(encoding="utf-8", errors="replace") if source_path.exists() else ""
        source_hash = sha(source_path.read_bytes()) if source_path.exists() else None
        ghidra_hash = sha(export.read_bytes())
        try:
            body, relocations, object_hash = parse_entry_object(object_path, symbols[address])
        except Exception as exc:  # reported as an audit row so the rest of the callers remain inspectable
            rows.append({"address": f"0x{address}", "name": ghidra.get("name"), "error": str(exc)})
            continue
        for call_index in calls:
            call_line = assembly[call_index]
            before = assembly[max(0, call_index - 2):call_index]
            expected = []
            for line in before:
                if "PUSH" not in line.upper():
                    continue
                try:
                    expected.append(int(line.rsplit(" ", 1)[-1], 16))
                except ValueError:
                    expected.append(None)
            helper_relocs = [r for r in relocations if r["type"] == REL32 and "SEH_prolog4" in r["target"]]
            if len(helper_relocs) != len(calls):
                rows.append({
                    "address": f"0x{address}", "name": ghidra.get("name"),
                    "source": str(source_path.relative_to(args.repo)).replace("\\", "/"),
                    "source_sha256": source_hash,
                    "ghidra_export_sha256": ghidra_hash,
                    "object_sha256": object_hash,
                    "ghidra_call": call_line,
                    "ghidra_pushes_in_order": expected,
                    "object_helper_relocation_count": len(helper_relocs),
                    "source_mentions_helper": "__SEH_prolog4" in source,
                    "source_naked": "__declspec(naked)" in source,
                    "source_has_asm": "__asm" in source,
                    "object_entry_prefix": body[:24].hex(" ").upper(),
                    "error": "COFF body does not contain the Ghidra __SEH_prolog4 call count",
                })
                continue
            helper = helper_relocs[calls.index(call_index)]
            call_start = helper["site"] - 1
            scope_field = call_start - 4
            scope_reloc = next((r for r in relocations if r["site"] == scope_field and r["type"] == DIR32), None)
            actual_frame = None
            if call_start >= 7 and body[call_start - 7] == 0x6A:
                actual_frame = body[call_start - 6]
            frame_match = len(expected) >= 2 and expected[-2] == actual_frame
            scope_match = (scope_reloc is not None and
                           f"{expected[-1]:08X}" in scope_reloc["target"]
                           if len(expected) >= 2 and expected[-1] is not None else False)
            rows.append({
                "address": f"0x{address}", "name": ghidra.get("name"),
                "source": str(source_path.relative_to(args.repo)).replace("\\", "/"),
                "source_sha256": source_hash,
                "ghidra_export_sha256": ghidra_hash,
                "object_sha256": object_hash,
                "ghidra_call": call_line,
                "ghidra_pushes_in_order": expected,
                "object_helper_call_offset": call_start,
                "object_helper_call_relocation": helper,
                "object_frame_size_push": actual_frame,
                "object_scope_relocation": scope_reloc,
                "object_scope_relocation_present": scope_reloc is not None,
                "source_naked": "__declspec(naked)" in source,
                "source_has_asm": "__asm" in source,
                "frame_size_matches": frame_match,
                "scope_table_relocation_matches": scope_match,
                "expected_prolog_bytes_at_entry": call_start == 7,
                "object_entry_prefix": body[:min(call_start + 5, 20)].hex(" ").upper(),
            })

    summary = {
        "ghidra_callsite_count": len(rows),
        "ghidra_caller_count": len({row["address"] for row in rows}),
        "missing_or_count_mismatched_object_calls": sum(
            row.get("error") == "COFF body does not contain the Ghidra __SEH_prolog4 call count"
            for row in rows
        ),
        "coff_parse_errors": sum(
            "error" in row and row.get("error") != "COFF body does not contain the Ghidra __SEH_prolog4 call count"
            for row in rows
        ),
        "frame_size_matches": sum(row.get("frame_size_matches") is True for row in rows),
        "scope_alias_matches": sum(row.get("scope_table_relocation_matches") is True for row in rows),
        "scope_relocation_present": sum(row.get("object_scope_relocation_present") is True for row in rows),
        "entry_prolog_shape_matches": sum(row.get("expected_prolog_bytes_at_entry") is True for row in rows),
        "current_sources_naked": sum(row.get("source_naked") is True for row in rows),
    }
    report = {
        "scope": "Ghidra callsite versus current x86 COFF entry/prolog comparison; not a semantic or runtime proof.",
        "ghidra_export": str(args.ghidra_export.resolve()),
        "objects_directory": str(args.objects.resolve()),
        "placement_sha256": sha(args.placement.read_bytes()),
        "summary": summary,
        "callsites": rows,
        "limitations": [
            "Scope-table matching recognizes relocatable IVF_RELOC_TARGET_<address> references only; local reconstructed scope tables require manual content comparison.",
            "Instruction shape and argument checks do not prove scope-table contents, EH funclet correctness, or runtime safety.",
        ],
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"summary": summary, "report": str(args.output.resolve())}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
