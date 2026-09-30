#!/usr/bin/env python3
"""Create a non-loadable single-function patch probe from a pinned PE and COFF object."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import struct
from pathlib import Path


EXPECTED_IMAGE_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"
IMAGE_SCN_CNT_CODE = 0x00000020
IMAGE_SCN_MEM_EXECUTE = 0x20000000
IMAGE_REL_I386_DIR32 = 0x0006


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def parse_address(value: str) -> int:
    return int(value.strip().strip('"').removeprefix("0x"), 16)


def csv_rows(path: Path) -> list[dict[str, str]]:
    with path.open(encoding="utf-8-sig", newline="") as stream:
        return list(csv.DictReader(stream))


def read_coff_function(path: Path, symbol_name: str) -> tuple[bytes, dict[str, object]]:
    data = path.read_bytes()
    if len(data) < 20:
        raise ValueError("truncated COFF object")
    machine, section_count, _, symbol_offset, symbol_count, optional_size, _ = struct.unpack_from(
        "<HHIIIHH", data
    )
    if machine != 0x14C:
        raise ValueError(f"expected i386 COFF, got machine {machine:#x}")
    section_table = 20 + optional_size
    sections: list[dict[str, int | str]] = []
    for index in range(section_count):
        offset = section_table + index * 40
        if offset + 40 > len(data):
            raise ValueError("truncated COFF section table")
        name, _, _, raw_size, raw_offset, reloc_offset, _, reloc_count, _, flags = struct.unpack_from(
            "<8sIIIIIIHHI", data, offset
        )
        sections.append({
            "name": name.split(b"\0", 1)[0].decode("ascii", errors="replace"),
            "raw_size": raw_size,
            "raw_offset": raw_offset,
            "reloc_offset": reloc_offset,
            "reloc_count": reloc_count,
            "flags": flags,
        })
    string_offset = symbol_offset + symbol_count * 18
    if string_offset + 4 > len(data):
        raise ValueError("truncated COFF symbol/string table")
    strings_size = struct.unpack_from("<I", data, string_offset)[0]
    strings = data[string_offset : string_offset + strings_size]
    index = 0
    cursor = symbol_offset
    match: tuple[int, int, int] | None = None
    while index < symbol_count:
        entry = data[cursor : cursor + 18]
        if len(entry) != 18:
            raise ValueError("truncated COFF symbol")
        name_bytes = entry[:8]
        if name_bytes[:4] == b"\0\0\0\0":
            name_offset = struct.unpack_from("<I", name_bytes, 4)[0]
            end = strings.find(b"\0", name_offset)
            name = strings[name_offset:end].decode("utf-8", errors="replace") if end >= 0 else ""
        else:
            name = name_bytes.split(b"\0", 1)[0].decode("utf-8", errors="replace")
        value, section_number, symbol_type, storage_class, aux_count = struct.unpack_from("<IhHBB", entry, 8)
        if name == symbol_name:
            if match is not None:
                raise ValueError(f"duplicate symbol {symbol_name}")
            match = (value, section_number, symbol_type)
        index += 1 + aux_count
        cursor += (1 + aux_count) * 18
    if match is None:
        raise ValueError(f"COFF symbol not found: {symbol_name}")
    value, section_number, symbol_type = match
    if section_number <= 0 or section_number > len(sections):
        raise ValueError("function symbol is not defined in a section")
    section = sections[section_number - 1]
    if section["name"] != ".xcode" or value != 0:
        raise ValueError(f"expected entry symbol at start of .xcode COMDAT, got {section} value={value}")
    flags = int(section["flags"])
    if flags & (IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_EXECUTE) != (IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_EXECUTE):
        raise ValueError("candidate COMDAT is not executable code")
    raw_size = int(section["raw_size"])
    raw_offset = int(section["raw_offset"])
    if raw_size <= 0 or raw_offset + raw_size > len(data):
        raise ValueError("candidate COMDAT raw bytes are missing or truncated")
    reloc_offset = int(section["reloc_offset"])
    reloc_count = int(section["reloc_count"])
    relocations = []
    for rel_index in range(reloc_count):
        at = reloc_offset + rel_index * 10
        if at + 10 > len(data):
            raise ValueError("truncated COFF relocation table")
        site, symbol_index, kind = struct.unpack_from("<IIH", data, at)
        relocations.append({"site": site, "symbol_index": symbol_index, "type": kind})
    if relocations:
        raise ValueError(f"refusing in-place probe with unresolved COFF relocations: {relocations}")
    return data[raw_offset : raw_offset + raw_size], {
        "object_sha256": sha256(data),
        "symbol": symbol_name,
        "symbol_type": symbol_type,
        "comdat_section_number": section_number,
        "comdat_section": section["name"],
        "comdat_size": raw_size,
        "coff_relocation_count": reloc_count,
    }


def locate_pe_text(image: bytes) -> dict[str, int]:
    if image[:2] != b"MZ":
        raise ValueError("image has no MZ signature")
    pe = struct.unpack_from("<I", image, 0x3C)[0]
    if image[pe : pe + 4] != b"PE\0\0":
        raise ValueError("image has no PE signature")
    section_count = struct.unpack_from("<H", image, pe + 6)[0]
    optional_size = struct.unpack_from("<H", image, pe + 20)[0]
    optional = pe + 24
    if struct.unpack_from("<H", image, optional)[0] != 0x10B:
        raise ValueError("expected PE32 image")
    image_base = struct.unpack_from("<I", image, optional + 28)[0]
    table = optional + optional_size
    for index in range(section_count):
        offset = table + index * 40
        name = image[offset : offset + 8].split(b"\0", 1)[0]
        if name == b".text":
            virtual_size, rva, raw_size, raw_offset = struct.unpack_from("<IIII", image, offset + 8)
            return {"image_base": image_base, "text_va": image_base + rva,
                    "text_virtual_size": virtual_size, "text_raw_size": raw_size,
                    "text_raw_offset": raw_offset, "pe_offset": pe,
                    "section_count": section_count}
    raise ValueError("image has no .text section")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--reference-pe", type=Path, required=True)
    parser.add_argument("--candidate-object", type=Path, required=True)
    parser.add_argument("--symbol", required=True)
    parser.add_argument("--entry", type=lambda value: int(value, 0), required=True)
    parser.add_argument("--function-map", type=Path, required=True)
    parser.add_argument("--text-relocation-sites", type=Path, required=True)
    parser.add_argument("--ghidra-xrefs", type=Path, action="append", required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--report", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists() or args.report.exists():
        raise FileExistsError("refusing to overwrite a probe image or report")

    image = args.reference_pe.read_bytes()
    original_hash = sha256(image)
    if original_hash != EXPECTED_IMAGE_SHA256:
        raise ValueError(f"reference PE hash mismatch: {original_hash}")
    candidate, coff = read_coff_function(args.candidate_object, args.symbol)
    pe = locate_pe_text(image)
    offset = args.entry - pe["text_va"]
    if offset < 0 or offset + len(candidate) > pe["text_raw_size"]:
        raise ValueError("candidate range is outside file-backed .text")

    map_rows = sorted(parse_address(row["address"]) for row in csv_rows(args.function_map))
    if len(map_rows) != 705 or len(set(map_rows)) != 705 or args.entry not in map_rows:
        raise ValueError("function map must contain 705 unique entries including the target")
    next_entries = [entry for entry in map_rows if entry > args.entry]
    if not next_entries:
        raise ValueError("target has no independently mapped following entry")
    gap = next_entries[0] - args.entry
    if len(candidate) > gap:
        raise ValueError(f"candidate body ({len(candidate)}) exceeds next-entry gap ({gap})")

    fixups = [parse_address(row["address"]) for row in csv_rows(args.text_relocation_sites)]
    patch_start, patch_end = args.entry, args.entry + len(candidate)
    overlaps = [site for site in fixups if max(site, patch_start) < min(site + 4, patch_end)]
    if overlaps:
        raise ValueError(f"original HIGHLOW fields overlap candidate bytes: {[hex(x) for x in overlaps]}")

    xrefs = [row for path in args.ghidra_xrefs for row in csv_rows(path)]
    body_max_values = {parse_address(row["body_max"]) for row in xrefs if row.get("body_max")}
    if body_max_values != {0x100180C4} or args.entry != 0x10018090:
        raise ValueError("Ghidra xref inputs do not describe the expected complete target function body")
    target_rows: dict[int, dict[str, str]] = {}
    for row in xrefs:
        target_rows[parse_address(row["address"])] = row
    body_end = 0x100180C4
    if not set(range(args.entry, body_end + 1)).issubset(target_rows):
        raise ValueError("Ghidra xref export does not cover every byte in the original function body")
    external_interior_refs = []
    for address, row in target_rows.items():
        source_text = row.get("incoming_ref_from", "").strip()
        if not source_text or address == args.entry:
            continue
        source = parse_address(source_text)
        if patch_start <= source < patch_end:
            continue
        if address < patch_end:
            external_interior_refs.append({"target": hex(address), "source": hex(source)})
        elif address <= body_end:
            external_interior_refs.append({"target": hex(address), "source": hex(source)})
    if external_interior_refs:
        raise ValueError(f"Ghidra shows incoming refs into overwritten/tail bytes: {external_interior_refs}")

    patched = bytearray(image)
    original_range = image[pe["text_raw_offset"] + offset : pe["text_raw_offset"] + offset + len(candidate)]
    patched[pe["text_raw_offset"] + offset : pe["text_raw_offset"] + offset + len(candidate)] = candidate
    changed = [index for index, (before, after) in enumerate(zip(image, patched)) if before != after]
    expected_changed = set(range(pe["text_raw_offset"] + offset, pe["text_raw_offset"] + offset + len(candidate)))
    if not set(changed).issubset(expected_changed) or not changed:
        raise AssertionError("probe differs outside intended .text patch window")
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("xb") as stream:
        stream.write(patched)
    output_data = args.output.read_bytes()
    output_pe = locate_pe_text(output_data)
    if output_pe != pe or len(output_data) != len(image):
        raise AssertionError("PE layout changed unexpectedly")
    if output_data[: pe["text_raw_offset"] + offset] != image[: pe["text_raw_offset"] + offset] or \
       output_data[pe["text_raw_offset"] + offset + len(candidate) :] != image[pe["text_raw_offset"] + offset + len(candidate) :]:
        raise AssertionError("probe changed bytes outside the selected function")

    report = {
        "scope": "One-function in-place patch mechanism probe only; output is not a production ASI and was not loaded.",
        "reference_pe": str(args.reference_pe.resolve()),
        "reference_sha256": original_hash,
        "candidate_object": str(args.candidate_object.resolve()),
        "candidate": coff,
        "entry_va": f"0x{args.entry:08x}",
        "candidate_size": len(candidate),
        "next_mapped_entry_gap": gap,
        "original_highlow_overlap_count": 0,
        "ghidra_function_body_end": f"0x{body_end:08x}",
        "ghidra_incoming_interior_refs_outside_replaced_bytes": 0,
        "original_entry_bytes_sha256": sha256(original_range),
        "candidate_bytes_sha256": sha256(candidate),
        "changed_file_byte_count": len(changed),
        "changed_file_offset_start": f"0x{min(changed):x}",
        "changed_file_offset_end_exclusive": f"0x{max(changed) + 1:x}",
        "output": str(args.output.resolve()),
        "output_sha256": sha256(output_data),
        "limitations": [
            "This exercises only one known zero-relocation CRT function in its original VA; it does not validate the other 704 candidates.",
            "Ghidra decompilation/xrefs and bounded placement checks are not proof of semantic equivalence.",
            "The probe was not loaded as a DLL/ASI, is not a game test, and does not validate initialization or whole-image behavior.",
        ],
    }
    args.report.parent.mkdir(parents=True, exist_ok=True)
    with args.report.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    print(f"target={args.entry:#010x} candidate={len(candidate)} gap={gap} reloc=0 xref_interior=0 changed={len(changed)}")
    print(f"probe={args.output} sha256={report['output_sha256']}")
    print(f"report={args.report}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
