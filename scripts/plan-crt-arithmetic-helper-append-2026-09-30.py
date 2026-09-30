#!/usr/bin/env python3
"""Plan exact append/REL32 targets for the nine remaining x86 CRT arithmetic calls.

This emits a sidecar tail payload and an unapplied callsite patch plan. It does
not modify candidate objects, the pinned ASI, or any PE image.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
PINNED_ASI_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"
EXPECTED = {
    "__alldiv": ("lldiv.obj", 170),
    "__allrem": ("llrem.obj", 178),
    "__aulldiv": ("ulldiv.obj", 104),
}


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def coff_name(data: bytes, strings_at: int, field: bytes) -> str:
    if field[:4] != b"\0\0\0\0":
        return field.split(b"\0", 1)[0].decode("utf-8", errors="replace")
    offset = struct.unpack_from("<I", field, 4)[0]
    end = data.find(b"\0", strings_at + offset)
    if end < 0:
        raise ValueError("unterminated COFF string")
    return data[strings_at + offset:end].decode("utf-8", errors="replace")


def parse_coff(data: bytes) -> tuple[list[dict[str, object]], dict[int, dict[str, object]]]:
    machine, nsections, _, sym_at, nsymbols, optional, _ = struct.unpack_from("<HHIIIHH", data)
    if machine != 0x14C or optional:
        raise ValueError("expected IA-32 relocatable COFF")
    sections = []
    for i in range(nsections):
        at = 20 + i * 40
        name, _, _, size, raw, reloc, _, nreloc, _, flags = struct.unpack_from("<8sIIIIIIHHI", data, at)
        sections.append({"number": i + 1, "name": name.split(b"\0", 1)[0].decode(),
                         "size": size, "raw": raw, "reloc": reloc,
                         "nreloc": nreloc, "flags": flags})
    strings_at = sym_at + nsymbols * 18
    symbols: dict[int, dict[str, object]] = {}
    index = 0
    at = sym_at
    while index < nsymbols:
        rec = data[at:at + 18]
        name = coff_name(data, strings_at, rec[:8])
        value, section, _, storage, aux = struct.unpack_from("<IhHBB", rec, 8)
        symbols[index] = {"name": name, "value": value, "section": section, "storage": storage}
        index += 1 + aux
        at += (1 + aux) * 18
    return sections, symbols


def helper_body(path: Path, symbol: str, expected_size: int) -> tuple[bytes, dict[str, object]]:
    data = path.read_bytes()
    sections, symbols = parse_coff(data)
    defs = [s for s in symbols.values() if s["name"] == symbol and s["section"] > 0]
    if len(defs) != 1:
        raise ValueError(f"{path.name}: expected one definition for {symbol}")
    root = defs[0]
    section = sections[int(root["section"]) - 1]
    if section["name"] != ".text$mn" or int(root["value"]) != 0:
        raise ValueError(f"{path.name}: unexpected helper section/symbol layout")
    if int(section["size"]) != expected_size or int(section["nreloc"]):
        raise ValueError(f"{path.name}: code size/relocation mismatch")
    body = data[int(section["raw"]):int(section["raw"]) + expected_size]
    if len(body) != expected_size:
        raise ValueError(f"{path.name}: truncated helper body")
    return body, {"object": str(path.resolve()), "symbol": symbol,
                  "object_sha256": sha256(data), "code_bytes": len(body),
                  "code_relocations": 0, "body_sha256": sha256(body)}


def candidate_calls(obj_path: Path, wanted: set[str]) -> list[dict[str, object]]:
    data = obj_path.read_bytes()
    sections, symbols = parse_coff(data)
    root_name = obj_path.stem
    roots = [s for s in symbols.values() if s["name"].lower().endswith(root_name.lower())
             and s["section"] > 0 and sections[int(s["section"]) - 1]["name"] == ".xcode"]
    # Address-named candidate roots can have decorated names; section offset zero
    # uniquely identifies the per-function COMDAT root in these objects.
    roots = [s for s in roots if int(s["value"]) == 0]
    if len(roots) != 1:
        roots = [s for s in symbols.values() if s["section"] > 0
                 and sections[int(s["section"]) - 1]["name"] == ".xcode"
                 and int(s["value"]) == 0 and s["storage"] == 2]
    if len(roots) != 1:
        raise ValueError(f"{obj_path.name}: cannot identify unique .xcode root")
    section = sections[int(roots[0]["section"]) - 1]
    body = data[int(section["raw"]):int(section["raw"]) + int(section["size"])]
    found = []
    for ri in range(int(section["nreloc"])):
        site, sym_index, kind = struct.unpack_from("<IIH", data, int(section["reloc"]) + ri * 10)
        target = symbols[sym_index]
        name = str(target["name"])
        if name not in wanted:
            continue
        if kind != 0x0014 or site == 0 or body[site - 1:site + 4] != b"\xE8\0\0\0\0":
            raise ValueError(f"{obj_path.name}+{site:#x}: expected zero-addend CALL REL32 to {name}")
        found.append({"entry_va": "0x" + obj_path.stem.upper(), "candidate_entry": int(obj_path.stem, 16),
                      "object_sha256": sha256(data), "site_offset": site, "symbol": name})
    return found


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--original", type=Path, default=ROOT.parent.parent / "ImVehFt.asi")
    p.add_argument("--objects", type=Path, default=ROOT / "build/recheck/strict-xcode-nogs-o1-10006360-fastcall-full-20260930")
    p.add_argument("--crt-objects", type=Path, default=ROOT / "build/crt-arithmetic-extract-20260930")
    p.add_argument("--placement", type=Path, default=ROOT / "audit/placement-plan-conservative-current-2026-09-30.json")
    p.add_argument("--payload-census", type=Path, default=ROOT / "audit/appended-thunk-payload-census-conservative-current-2026-09-30.json")
    p.add_argument("--api-thunks", type=Path, default=ROOT / "build/pe-layout-probe/current-api-call-thunk-payload-20260930.bin")
    p.add_argument("--api-report", type=Path, default=ROOT / "audit/current-api-call-rel32-patch-plan-2026-09-30.json")
    p.add_argument("--output-tail", type=Path, required=True)
    p.add_argument("--output-report", type=Path, required=True)
    a = p.parse_args()
    if a.output_tail.exists() or a.output_report.exists():
        raise FileExistsError("refusing to overwrite an existing output")
    original_sha = sha256(a.original.read_bytes())
    if original_sha != PINNED_ASI_SHA256:
        raise ValueError("original ASI hash differs from the pinned input")
    placement = json.loads(a.placement.read_text(encoding="utf-8"))
    census = json.loads(a.payload_census.read_text(encoding="utf-8"))
    api_report = json.loads(a.api_report.read_text(encoding="utf-8"))
    if placement.get("candidate_count") != 705 or api_report.get("original_sha256") != original_sha:
        raise ValueError("stale placement plan or API patch plan")
    placements = {int(r["address"], 16): r for r in placement["entries"]}
    appended = {int(r["entry_va"], 16): r for r in census["entries"]}
    if api_report["candidate_object_count"] != 705:
        raise ValueError("API plan does not cover 705 candidate functions")

    tail = bytearray(a.api_thunks.read_bytes())
    base_offset = int(api_report["api_thunk_payload_offset"])
    if len(tail) != api_report["api_thunk_payload_bytes"] or base_offset != 87968:
        raise ValueError("unexpected verified API thunk payload geometry")
    current_end = base_offset + len(tail)
    helper_offsets: dict[str, int] = {}
    helper_meta = {}
    for symbol, (filename, size) in EXPECTED.items():
        aligned = (current_end + 15) & ~15
        tail.extend(b"\0" * (aligned - current_end))
        body, meta = helper_body(a.crt_objects / filename, symbol, size)
        helper_offsets[symbol] = aligned
        helper_meta[symbol] = {**meta, "payload_offset": aligned}
        tail.extend(body)
        current_end = aligned + len(body)

    calls = []
    for entry in (0x10014003, 0x1001BEE6):
        path = a.objects / f"{entry:08X}.obj"
        calls.extend(candidate_calls(path, set(EXPECTED)))
    if len(calls) != 9 or {r["symbol"] for r in calls} != set(EXPECTED):
        raise ValueError(f"expected all nine arithmetic calls, found {len(calls)}")
    section_rva = int(api_report["provisional_appended_section_rva"], 16)
    pe_offset = struct.unpack_from("<I", a.original.read_bytes(), 0x3C)[0]
    image_base = struct.unpack_from("<I", a.original.read_bytes(), pe_offset + 4 + 20 + 28)[0]
    patches = []
    for row in calls:
        entry = int(row["candidate_entry"])
        placement_row = placements.get(entry)
        payload_row = appended.get(entry)
        if not placement_row or placement_row["placement_mode"] != "jmp-rel32-thunk" or not payload_row:
            raise ValueError(f"unexpected placement for {entry:#x}")
        if row["object_sha256"] != payload_row["object_sha256"]:
            raise ValueError(f"candidate object hash mismatch for {entry:#x}")
        callsite = int(payload_row["provisional_payload_offset"]) + int(row["site_offset"])
        target = helper_offsets[str(row["symbol"])]
        disp = (section_rva + target) - (section_rva + callsite + 4)
        if not -(1 << 31) <= disp < (1 << 31):
            raise ValueError("helper call target outside signed REL32 range")
        patches.append({"candidate_entry": row["entry_va"], "object_sha256": row["object_sha256"],
                        "target_helper": row["symbol"], "relocation_site_offset": f"0x{row['site_offset']:X}",
                        "call_instruction_rva": f"0x{section_rva + callsite - 1:08X}",
                        "relocation_field_rva": f"0x{section_rva + callsite:08X}",
                        "helper_payload_offset": target, "helper_va": f"0x{image_base + section_rva + target:08X}",
                        "rel32_displacement": disp,
                        "rel32_displacement_u32": f"0x{disp & 0xFFFFFFFF:08X}",
                        "expected_current_bytes": "E8 00 00 00 00"})
    a.output_tail.parent.mkdir(parents=True, exist_ok=True)
    a.output_report.parent.mkdir(parents=True, exist_ok=True)
    a.output_tail.write_bytes(tail)
    raw_size = (current_end + 511) & ~511
    report = {
        "scope": "Unapplied placement and REL32 plan for nine static CRT arithmetic calls; sidecar tail only, not a PE/ASI.",
        "original_asi_sha256": original_sha,
        "candidate_object_directory": str(a.objects.resolve()),
        "candidate_functions": 705,
        "arithmetic_call_count": len(patches),
        "calls_by_symbol": {sym: sum(r["target_helper"] == sym for r in patches) for sym in EXPECTED},
        "arithmetic_helpers": helper_meta,
        "existing_api_thunk_offset": base_offset,
        "existing_api_thunk_bytes": len(a.api_thunks.read_bytes()),
        "tail_payload_start_offset": base_offset,
        "tail_payload_bytes": len(tail),
        "combined_appended_payload_bytes": current_end,
        "appended_section_rva": f"0x{section_rva:08X}",
        "appended_section_raw_offset": api_report["provisional_appended_section_raw_offset"],
        "file_aligned_appended_raw_bytes": raw_size,
        "provisional_appended_raw_end": f"0x{int(api_report['provisional_appended_section_raw_offset'], 16) + raw_size:08X}",
        "all_call_displacements_in_range": True,
        "patches": patches,
        "limitations": [
            "Patch plan and sidecar tail are not applied to candidate objects or any image.",
            "Arithmetic implementations are extracted from MSVC 14.44 libcmt, not proven to be the original 2014 compiler runtime.",
            "No full PE builder, loader validation, ASI output, or live GTA test is included."
        ]
    }
    a.output_report.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(f"PASS: planned {len(patches)} call fixups; tail={len(tail)} bytes; helpers have zero .text relocations")
    print(f"WROTE: {a.output_tail}")
    print(f"WROTE: {a.output_report}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
