#!/usr/bin/env python3
"""Plan 9 CRT arithmetic call fixups through byte-identical original CRT helpers.

This computes a provisional contiguous appended-payload layout only. It does
not emit or patch a PE; later section/relocation/startup integration must retain
the recorded offsets or recompute every displacement.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path

import pefile


PINNED_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"
ROOT_SYMBOLS = {
    "__alldiv": "_ivf_crt_alldiv_from_alldvrm@16",
    "__allrem": "_ivf_crt_allrem_from_alldvrm@16",
    "__aulldiv": "_ivf_crt_aulldiv_from_aulldvrm@16",
}
ORIGINAL_HELPERS = {
    "___alldvrm@16": (0x1001DDA0, "signed"),
    "___aulldvrm@16": (0x1001A900, "unsigned"),
}
RELOC_NAMES = {0x0006: "DIR32", 0x0014: "REL32"}


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def read_name(data: bytes, strings_at: int, field: bytes) -> str:
    if field[:4] != b"\0\0\0\0":
        return field.split(b"\0", 1)[0].decode("ascii", errors="replace")
    offset = struct.unpack_from("<I", field, 4)[0]
    end = data.find(b"\0", strings_at + offset)
    if end < 0:
        raise ValueError("unterminated COFF symbol name")
    return data[strings_at + offset:end].decode("ascii", errors="replace")


def parse_coff(path: Path) -> dict[str, object]:
    data = path.read_bytes()
    machine, count, _, sym_at, sym_count, optional, _ = struct.unpack_from("<HHIIIHH", data)
    if machine != 0x14C or optional:
        raise ValueError(f"{path}: expected IA-32 COFF without optional header")
    sections = []
    for index in range(count):
        at = 20 + index * 40
        name, _, _, size, raw, reloc_at, _, reloc_count, _, flags = struct.unpack_from(
            "<8sIIIIIIHHI", data, at
        )
        code = (flags >> 20) & 0xF
        sections.append({
            "name": name.split(b"\0", 1)[0].decode("ascii", errors="replace"),
            "size": size, "raw": raw, "reloc_at": reloc_at,
            "reloc_count": reloc_count, "flags": flags,
            "alignment": 1 if code == 0 else 1 << (code - 1),
        })
    strings_at = sym_at + sym_count * 18
    strings_size = struct.unpack_from("<I", data, strings_at)[0]
    strings = data[strings_at:strings_at + strings_size]
    symbols: dict[int, dict[str, object]] = {}
    defined: dict[str, dict[str, object]] = {}
    index = 0
    cursor = sym_at
    while index < sym_count:
        record = data[cursor:cursor + 18]
        name = read_name(data, strings_at, record[:8])
        value, section_no, kind, storage, aux = struct.unpack_from("<IhHBB", record, 8)
        item = {"name": name, "value": value, "section": section_no,
                "kind": kind, "storage": storage}
        symbols[index] = item
        if section_no > 0 and storage == 2:
            if name in defined:
                raise ValueError(f"{path}: duplicate defined symbol {name}")
            defined[name] = item
        index += 1 + aux
        cursor += (1 + aux) * 18
    for section_no, section in enumerate(sections, start=1):
        raw = int(section["raw"])
        size = int(section["size"])
        uninitialized = bool(int(section["flags"]) & 0x80)
        blob = bytes(size) if uninitialized else data[raw:raw + size]
        if len(blob) != size:
            raise ValueError(f"{path}: truncated section {section_no}")
        section["bytes"] = blob
        relocs = []
        for rindex in range(int(section["reloc_count"])):
            at = int(section["reloc_at"]) + rindex * 10
            site, symbol_index, kind = struct.unpack_from("<IIH", data, at)
            target = symbols.get(symbol_index)
            if target is None or site + 4 > size:
                raise ValueError(f"{path}: invalid relocation in {section['name']}")
            relocs.append({"site": site, "type": kind,
                           "type_name": RELOC_NAMES.get(kind, f"0x{kind:04X}"),
                           "target": str(target["name"]),
                           "target_section": int(target["section"])})
        section["relocations"] = relocs
    return {"path": path, "bytes": data, "sha256": sha(data),
            "sections": sections, "defined": defined}


def rel32(target: int, site_va: int, addend: int) -> int:
    displacement = target + addend - (site_va + 4)
    if not -(1 << 31) <= displacement < (1 << 31):
        raise ValueError(f"REL32 out of range: target={target:#x}, site={site_va:#x}")
    return displacement


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--objects", type=Path, required=True)
    parser.add_argument("--root-relocations", type=Path, required=True)
    parser.add_argument("--placement-plan", type=Path, required=True)
    parser.add_argument("--payload-census", type=Path, required=True)
    parser.add_argument("--local-closure", type=Path, required=True)
    parser.add_argument("--bridge-object", type=Path, required=True)
    parser.add_argument("--api-thunk-verification", type=Path, required=True)
    parser.add_argument("--original", type=Path, required=True)
    parser.add_argument("--signed-helper-proof", type=Path, required=True)
    parser.add_argument("--unsigned-helper-proof", type=Path, required=True)
    parser.add_argument("--bridge-payload", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    for path in (args.bridge_payload, args.output):
        if path.exists():
            raise FileExistsError(f"refusing to overwrite {path}")

    original_bytes = args.original.read_bytes()
    original_sha = sha(original_bytes)
    if original_sha != PINNED_SHA256:
        raise ValueError(f"pinned original ASI hash mismatch: {original_sha}")
    pe = pefile.PE(data=original_bytes, fast_load=True)
    image_base = int(pe.OPTIONAL_HEADER.ImageBase)

    placement_bytes = args.placement_plan.read_bytes()
    placement = json.loads(placement_bytes)
    payload_bytes = args.payload_census.read_bytes()
    payload = json.loads(payload_bytes)
    closure_bytes = args.local_closure.read_bytes()
    closure = json.loads(closure_bytes)
    api_bytes = args.api_thunk_verification.read_bytes()
    api = json.loads(api_bytes)
    root_report = json.loads(args.root_relocations.read_text(encoding="utf-8"))
    if placement.get("candidate_count") != 705:
        raise ValueError("expected the complete 705-entry placement")
    thunk_count = int(placement["rel32_thunks_required"])
    if (payload.get("candidate_entries") != 705
            or payload.get("thunk_entries") != thunk_count
            or closure.get("root_thunk_count") != thunk_count
            or root_report.get("thunk_bodies") != thunk_count):
        raise ValueError(
            "placement, root payload, local closure, and relocation inventory "
            "must cover the same current thunk count"
        )

    placement_by_entry = {int(row["address"], 16): row for row in placement["entries"]}
    payload_by_entry = {int(row["entry_va"], 16): row for row in payload["entries"]}
    rva_base = int(payload["provisional_appended_rva"], 16)
    code_cursor = int(payload["payload_bytes_with_16_byte_body_alignment"])
    code_local_layout = []
    data_cursor = 0
    data_local_layout = []
    for item in sorted(closure["sections"],
                       key=lambda row: (int(row["source_entry"], 16), int(row["section_number"]))):
        entry = int(item["source_entry"], 16)
        object_info = parse_coff(args.objects / f"{entry:08x}.obj")
        if object_info["sha256"] != item["object_sha256"]:
            raise ValueError(f"{entry:#x}: stale local-section object hash")
        section_no = int(item["section_number"])
        section = object_info["sections"][section_no - 1]
        blob = bytes(section["bytes"])
        if section["name"] != item["section_name"] or len(blob) != int(item["section_bytes"]):
            raise ValueError(f"{entry:#x}: local-section identity/size mismatch")
        if sha(blob) != item["section_sha256"]:
            raise ValueError(f"{entry:#x}: local-section content hash mismatch")
        alignment = int(section["alignment"])
        is_code = str(section["name"]).startswith(".xcode")
        segment_cursor = code_cursor if is_code else data_cursor
        segment_cursor = (segment_cursor + alignment - 1) & ~(alignment - 1)
        row = {
            "source_entry": item["source_entry"], "section_number": section_no,
            "section_name": section["name"], "alignment": alignment,
            "size": len(blob), "payload_offset": segment_cursor,
            "sha256": sha(blob), "relocation_count": len(section["relocations"]),
        }
        if is_code:
            code_local_layout.append(row)
            code_cursor = segment_cursor + len(blob)
        else:
            data_local_layout.append(row)
            data_cursor = segment_cursor + len(blob)

    rdata_cursor = 0
    rdata_layout = []
    for row in sorted(payload["local_rdata_payload_map"],
                      key=lambda item: (int(item["source_entry"], 16), int(item["section_number"]))):
        align_code = int(row["alignment_log2"])
        if not 1 <= align_code <= 14:
            raise ValueError(f"unsupported COFF rdata alignment code {align_code}")
        alignment = 1 << (align_code - 1)
        rdata_cursor = (rdata_cursor + alignment - 1) & ~(alignment - 1)
        rdata_layout.append({
            "source_entry": row["source_entry"], "section_number": row["section_number"],
            "alignment": alignment, "size": int(row["raw_size"]),
            "payload_offset": rdata_cursor, "sha256": row["raw_bytes_sha256"],
        })
        rdata_cursor += int(row["raw_size"])

    api_count = int(api.get("thunk_count", -1))
    if (api_count <= 0 or int(api.get("code_bytes", -1)) != api_count * 6
            or len(api.get("results", [])) != api_count
            or not api.get("all_thunks_exact_ff25")):
        raise ValueError("API thunk evidence must verify a contiguous count of exact six-byte FF25 thunks")
    api_thunk_body = bytearray(int(api["code_bytes"]))
    for row in api["results"]:
        offset = int(row["code_offset"], 16)
        template = bytes.fromhex(str(row["bytes"]).replace(" ", ""))
        if template != b"\xFF\x25\0\0\0\0":
            raise ValueError(f"unexpected API thunk template for {row['code_symbol']}")
        if offset + 6 > len(api_thunk_body):
            raise ValueError("API thunk offset is outside its payload")
        api_thunk_body[offset:offset + 6] = template
        struct.pack_into("<I", api_thunk_body, offset + 2, int(row["iat_va"], 16))
    local_xcode_end = code_cursor
    api_thunk_offset = (code_cursor + 15) & ~15
    code_cursor = api_thunk_offset + len(api_thunk_body)
    bridge_offset = (code_cursor + 15) & ~15

    bridge_info = parse_coff(args.bridge_object)
    bridge_sections = [(i, section) for i, section in enumerate(bridge_info["sections"], start=1)
                       if str(section["name"]).startswith(".text")]
    if len(bridge_sections) != 1:
        raise ValueError("bridge object must contain one .text section")
    bridge_section_no, bridge_section = bridge_sections[0]
    bridge_body = bytearray(bridge_section["bytes"])
    bridge_va = image_base + rva_base + bridge_offset
    bridge_symbols = {
        name: int(item["value"])
        for name, item in bridge_info["defined"].items()
        if int(item["section"]) == bridge_section_no
    }
    for target_name, (target_va, _) in ORIGINAL_HELPERS.items():
        if target_name not in {str(r["target"]) for r in bridge_section["relocations"]}:
            raise ValueError(f"bridge object lacks expected target {target_name}")
    helper_fixups = []
    for relocation in bridge_section["relocations"]:
        if relocation["type"] != 0x0014:
            raise ValueError("bridge uses an unsupported/non-REL32 relocation")
        target_name = str(relocation["target"])
        if target_name not in ORIGINAL_HELPERS:
            raise ValueError(f"unmapped bridge helper target {target_name}")
        target_va, helper_kind = ORIGINAL_HELPERS[target_name]
        site = int(relocation["site"])
        addend = struct.unpack_from("<i", bridge_body, site)[0]
        if addend != 0:
            raise ValueError(f"unexpected nonzero bridge REL32 addend at {site:#x}")
        displacement = rel32(target_va, bridge_va + site, addend)
        struct.pack_into("<i", bridge_body, site, displacement)
        helper_fixups.append({
            "site_offset_in_bridge": site, "symbol": target_name,
            "original_helper_va": f"0x{target_va:08X}", "helper_kind": helper_kind,
            "displacement": displacement,
        })

    expected_helpers = {"___alldvrm@16": 2, "___aulldvrm@16": 1}
    actual_helpers = {name: sum(row["target"] == name for row in bridge_section["relocations"])
                      for name in expected_helpers}
    if actual_helpers != expected_helpers or len(helper_fixups) != 3:
        raise ValueError(f"unexpected bridge helper-call inventory: {actual_helpers}")
    for proof_path, expected_entry in ((args.signed_helper_proof, 0x1001DDA0),
                                       (args.unsigned_helper_proof, 0x1001A900)):
        proof = json.loads(proof_path.read_text(encoding="utf-8"))
        if (not proof.get("byte_identical") or int(proof["entry_va"], 16) != expected_entry
                or proof.get("reference_sha256") != original_sha):
            raise ValueError(f"helper byte-identity proof is invalid: {proof_path}")

    root_calls = [row for row in root_report["relocations"]
                  if row.get("target_symbol") in ROOT_SYMBOLS]
    expected_counts = {"__alldiv": 4, "__allrem": 4, "__aulldiv": 1}
    actual_counts = {name: sum(row["target_symbol"] == name for row in root_calls)
                     for name in expected_counts}
    if actual_counts != expected_counts or len(root_calls) != 9:
        raise ValueError(f"unexpected CRT callsite inventory: {actual_counts}")

    caller_fixups = []
    for row in root_calls:
        entry = int(row["source_entry"], 16)
        if entry not in payload_by_entry or placement_by_entry[entry]["placement_mode"] != "jmp-rel32-thunk":
            raise ValueError(f"{entry:#x}: CRT caller is not in the appended-thunk payload")
        body_row = payload_by_entry[entry]
        source_object = parse_coff(args.objects / f"{entry:08x}.obj")
        root_xcode = next((section for section in source_object["sections"]
                           if section["name"] == ".xcode" and
                           int(section["size"]) == int(body_row["body_size"])), None)
        if root_xcode is None:
            raise ValueError(f"{entry:#x}: could not identify root .xcode COMDAT")
        site = int(row["site"])
        matching = [r for r in root_xcode["relocations"]
                    if int(r["site"]) == site and r["target"] == row["target_symbol"]
                    and r["type"] == 0x0014]
        if len(matching) != 1:
            raise ValueError(f"{entry:#x}+{site:#x}: relocation/object mismatch")
        addend = struct.unpack_from("<i", bytes(root_xcode["bytes"]), site)[0]
        if addend != 0:
            raise ValueError(f"{entry:#x}+{site:#x}: unexpected call-rel32 addend")
        bridge_symbol = ROOT_SYMBOLS[str(row["target_symbol"])]
        if bridge_symbol not in bridge_symbols:
            raise ValueError(f"bridge object lacks {bridge_symbol}")
        bridge_target = bridge_va + bridge_symbols[bridge_symbol]
        body_va = image_base + rva_base + int(body_row["provisional_payload_offset"])
        site_va = body_va + site
        displacement = rel32(bridge_target, site_va, addend)
        caller_fixups.append({
            "source_entry": f"0x{entry:08X}", "source_symbol": str(row.get("source_symbol", "")),
            "site_offset_in_body": site, "target_symbol": str(row["target_symbol"]),
            "bridge_symbol": bridge_symbol, "source_site_va_if_layout_retained": f"0x{site_va:08X}",
            "bridge_target_va_if_layout_retained": f"0x{bridge_target:08X}",
            "displacement": displacement,
        })

    args.bridge_payload.parent.mkdir(parents=True, exist_ok=True)
    args.bridge_payload.write_bytes(bridge_body)
    report = {
        "scope": "Unapplied helper bridge and nine caller REL32 fixups using byte-identical original CRT helper entries; provisional contiguous payload layout only.",
        "original_asi_sha256": original_sha,
        "placement_plan_sha256": sha(placement_bytes),
        "payload_census_sha256": sha(payload_bytes),
        "local_closure_sha256": sha(closure_bytes),
        "bridge_object_sha256": bridge_info["sha256"],
        "provisional_appended_rva": f"0x{rva_base:08X}",
        "section_layout_model": "three distinct appended PE sections: executable code, read-only data, writable data; all RVAs remain provisional until a PE is emitted and re-opened",
        "root_code_bytes_with_body_alignment": int(payload["payload_bytes_with_16_byte_body_alignment"]),
        "local_xcode_section_count": len(code_local_layout),
        "local_xcode_bytes_including_alignment": local_xcode_end - int(payload["payload_bytes_with_16_byte_body_alignment"]),
        "local_xcode_layout": code_local_layout,
        "api_thunk_count": int(api["thunk_count"]),
        "api_thunk_payload_offset_in_code_section": api_thunk_offset,
        "api_thunk_payload_bytes": len(api_thunk_body),
        "api_thunk_payload_sha256_after_iat_fixups": sha(api_thunk_body),
        "rdata_payload_bytes_before_file_alignment": rdata_cursor,
        "rdata_layout": rdata_layout,
        "data_payload_virtual_bytes": data_cursor,
        "data_local_section_count": len(data_local_layout),
        "data_local_layout": data_local_layout,
        "code_bytes_before_bridge_alignment": code_cursor,
        "bridge_payload_offset": bridge_offset,
        "bridge_payload_va_if_layout_retained": f"0x{bridge_va:08X}",
        "bridge_payload_bytes": len(bridge_body),
        "bridge_payload_sha256_after_original_helper_rel32_fixups": sha(bridge_body),
        "bridge_payload_file": str(args.bridge_payload.resolve()),
        "bridge_symbols": {name: {"offset": value, "va_if_layout_retained": f"0x{bridge_va + value:08X}"}
                           for name, value in bridge_symbols.items() if name in ROOT_SYMBOLS.values()},
        "bridge_helper_fixups": helper_fixups,
        "candidate_caller_fixups": caller_fixups,
        "call_counts": actual_counts,
        "helper_byte_identity_proofs": [str(args.signed_helper_proof.resolve()),
                                         str(args.unsigned_helper_proof.resolve())],
        "limitations": [
            "No PE/ASI bytes are patched or emitted.",
            "The appended section's final RVA, PE section permissions, full external-symbol integration, base-relocation directory, import/startup behavior, and other payload sections are not yet finalized.",
            "All recorded VAs/displacements are provisional and must be recomputed if any prior payload section, alignment, or order changes.",
            "The bridge test validates its x86 ABI/results against the candidate's byte-identical helper bodies, not loader or GTA behavior.",
        ],
    }
    api_path = args.output.with_name("api-thunk-payload-three-section.bin")
    api_path.parent.mkdir(parents=True, exist_ok=True)
    api_path.write_bytes(api_thunk_body)
    report["api_thunk_payload_file"] = str(api_path.resolve())
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(f"planned {len(caller_fixups)} caller fixups; bridge={len(bridge_body)} bytes; local code/data sections={len(code_local_layout) + len(data_local_layout)}")
    print(f"bridge_va_if_layout_retained={bridge_va:#010x}; unresolved CRT references are redirected in this plan")
    print(f"report={args.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
