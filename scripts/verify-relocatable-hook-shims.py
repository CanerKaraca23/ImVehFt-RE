#!/usr/bin/env python3
"""Independently check relocated COFF hook-shim bytes and DIR32/REL32 fixups."""

from __future__ import annotations

import argparse
import csv
import json
import struct
from collections import defaultdict
from pathlib import Path


def read_coff(path: Path) -> tuple[bytes, list[dict[str, object]], list[dict[str, object]]]:
    data = path.read_bytes()
    machine, section_count, _, symbol_ptr, symbol_count, optional_size, _ = struct.unpack_from(
        "<HHIIIHH", data, 0
    )
    if machine != 0x14C or optional_size:
        raise ValueError("expected x86 COFF object")
    section_table = 20 + optional_size
    sections: list[dict[str, object]] = []
    for number in range(section_count):
        at = section_table + number * 40
        header = data[at : at + 40]
        name = header[:8].split(b"\0", 1)[0].decode("ascii")
        size, raw_ptr, reloc_ptr = struct.unpack_from("<III", header, 16)
        reloc_count = struct.unpack_from("<H", header, 32)[0]
        sections.append(
            {
                "name": name,
                "size": size,
                "raw_ptr": raw_ptr,
                "reloc_ptr": reloc_ptr,
                "reloc_count": reloc_count,
                "bytes": data[raw_ptr : raw_ptr + size] if raw_size_valid(raw_ptr, size, data) else b"",
            }
        )
    strings_at = symbol_ptr + symbol_count * 18
    strings_size = struct.unpack_from("<I", data, strings_at)[0]
    strings = data[strings_at : strings_at + strings_size]

    def name_of(record: bytes) -> str:
        if record[:4] == b"\0\0\0\0":
            offset = struct.unpack_from("<I", record, 4)[0]
            end = strings.find(b"\0", offset)
            return strings[offset:end].decode("ascii")
        return record[:8].split(b"\0", 1)[0].decode("ascii")

    symbols: list[dict[str, object]] = []
    index = 0
    while index < symbol_count:
        at = symbol_ptr + index * 18
        record = data[at : at + 18]
        value, section_no = struct.unpack_from("<Ih", record, 8)
        storage_class, aux_count = record[16], record[17]
        symbols.append(
            {
                "index": index,
                "name": name_of(record),
                "value": value,
                "section": section_no,
                "storage": storage_class,
            }
        )
        index += 1 + aux_count

    return data, sections, symbols


def raw_size_valid(offset: int, size: int, data: bytes) -> bool:
    return size == 0 or (offset > 0 and offset + size <= len(data))


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path, required=True)
    parser.add_argument("--cfg", type=Path, default=Path("audit/asi-hook-target-cfg-2026-09-27.csv"))
    parser.add_argument("--manifest", type=Path, required=True)
    args = parser.parse_args()

    manifest = json.loads(args.manifest.read_text(encoding="utf-8"))
    groups: dict[int, list[tuple[int, bytes]]] = defaultdict(list)
    with args.cfg.open(encoding="utf-8-sig", newline="") as stream:
        for row in csv.DictReader(stream):
            groups[int(row["target"], 16)].append(
                (int(row["instruction_address"], 16), bytes.fromhex(row["bytes_hex"]))
            )
    fixups = {
        (int(item["shim"], 16), int(item["instruction_va"], 16)): item
        for item in manifest["fixups"]
    }
    _, sections, symbols = read_coff(args.object)
    text_sections = [i for i, section in enumerate(sections, start=1) if str(section["name"]).startswith(".text")]
    if len(text_sections) != 1:
        raise ValueError(f"expected one text section, found {text_sections}")
    text_no = text_sections[0]
    text = bytes(sections[text_no - 1]["bytes"])
    external = {int(s["index"]): str(s["name"]) for s in symbols if s["storage"] == 2}
    public = {
        str(s["name"]): int(s["value"])
        for s in symbols
        if s["storage"] == 2 and int(s["section"]) == text_no
    }

    expected_relocations: dict[int, tuple[int, str]] = {}
    expected_total_size = 0
    for target, instructions in sorted(groups.items()):
        instructions.sort(key=lambda item: item[0])
        body_start = instructions[0][0]
        body_symbol = f"_ImVehFtHook_{target:08X}"
        if public.get(body_symbol) != expected_total_size:
            raise ValueError(
                f"bad public shim position for {body_symbol}: "
                f"{public.get(body_symbol)} != {expected_total_size}"
            )
        cursor = body_start
        for address, code in instructions:
            if address != cursor:
                raise ValueError(f"non-contiguous CFG at {address:#x}, expected {cursor:#x}")
            cursor += len(code)
            item = fixups.get((target, address))
            if item is None:
                continue
            field = int(item["field_offset"])
            kind = str(item["kind"])
            symbol = str(item["target_symbol"])
            coff_type = 0x0014 if kind == "REL32" else 0x0006
            site = expected_total_size + address - body_start + field
            expected_relocations[site] = (coff_type, symbol)
        body_size = cursor - body_start
        expected = bytearray(b"".join(code for _, code in instructions))
        for (shim, address), item in fixups.items():
            if shim != target:
                continue
            relative = address - body_start + int(item["field_offset"])
            width = int(item.get("width", 4))
            expected[relative : relative + width] = bytes(width)
        actual = text[expected_total_size : expected_total_size + body_size]
        if actual != bytes(expected):
            mismatch = next(
                (i for i, pair in enumerate(zip(actual, expected)) if pair[0] != pair[1]),
                min(len(actual), len(expected)),
            )
            raise ValueError(f"{body_symbol} byte mismatch at +{mismatch:#x}")
        expected_total_size += body_size

    actual_relocations: dict[int, tuple[int, str]] = {}
    for section in sections:
        reloc_ptr = int(section["reloc_ptr"])
        reloc_count = int(section["reloc_count"])
        if not reloc_count:
            continue
        if not str(section["name"]).startswith(".text"):
            raise ValueError(f"unexpected relocations in {section['name']}")
        for index in range(reloc_count):
            at = reloc_ptr + index * 10
            site, symbol_index, reloc_type = struct.unpack_from("<IIH", args.object.read_bytes(), at)
            if symbol_index not in external:
                raise ValueError(f"relocation references unknown COFF symbol index {symbol_index}")
            actual_relocations[site] = (reloc_type, external[symbol_index])

    if actual_relocations != expected_relocations:
        missing = set(expected_relocations.items()) - set(actual_relocations.items())
        extra = set(actual_relocations.items()) - set(expected_relocations.items())
        raise ValueError(f"relocation-table mismatch; missing={len(missing)} extra={len(extra)}")
    if len(text) != expected_total_size:
        raise ValueError(f"text size {len(text)} differs from expected shim bytes {expected_total_size}")

    counts = defaultdict(int)
    for reloc_type, _ in actual_relocations.values():
        counts[reloc_type] += 1
    print(
        f"PASS shims={len(groups)} instruction_stream_bytes={expected_total_size} "
        f"verified_nonfixup_bytes={expected_total_size - 4 * len(expected_relocations)} "
        f"relocations={len(actual_relocations)} DIR32={counts[0x0006]} REL32={counts[0x0014]}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
