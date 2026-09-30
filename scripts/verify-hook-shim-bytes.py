#!/usr/bin/env python3
"""Compare supplemental MSVC x86 hook-shim object bytes with bounded Ghidra CFG bytes."""

from __future__ import annotations

import argparse
import csv
import struct
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SHIMS = {
    "0x10003030": "_ImVehFtHook_10003030",
    "0x10007f50": "_ImVehFtHook_10007F50",
    "0x10003060": "_ImVehFtHook_10003060",
    "0x10003080": "_ImVehFtHook_10003080",
    "0x100031e0": "_ImVehFtHook_100031E0",
    "0x10003e40": "_ImVehFtHook_10003E40",
    "0x10004b10": "_ImVehFtHook_10004B10",
    "0x10007f70": "_ImVehFtHook_10007F70",
    "0x10007f90": "_ImVehFtHook_10007F90",
    "0x10008780": "_ImVehFtHook_10008780",
    "0x10008830": "_ImVehFtHook_10008830",
    "0x10008940": "_ImVehFtHook_10008940",
}


def read_cfg_bytes(path: Path, addresses: set[str]) -> dict[str, bytes]:
    rows: dict[str, list[tuple[int, bytes]]] = {address: [] for address in addresses}
    with path.open(encoding="utf-8-sig", newline="") as stream:
        for row in csv.DictReader(stream):
            target = row["target"].lower()
            if target in rows:
                rows[target].append(
                    (int(row["instruction_address"], 16), bytes.fromhex(row["bytes_hex"]))
                )

    output: dict[str, bytes] = {}
    for address, instructions in rows.items():
        instructions.sort(key=lambda item: item[0])
        if not instructions:
            raise ValueError(f"No Ghidra CFG instructions for {address}")
        cursor = instructions[0][0]
        chunks: list[bytes] = []
        for instruction_address, code in instructions:
            if instruction_address != cursor:
                raise ValueError(
                    f"Non-contiguous Ghidra bytes for {address}: expected {cursor:#x}, "
                    f"found {instruction_address:#x}"
                )
            chunks.append(code)
            cursor += len(code)
        output[address] = b"".join(chunks)
    return output


def read_coff_functions(path: Path, names: set[str]) -> dict[str, tuple[bytes, int]]:
    data = path.read_bytes()
    machine, section_count, _, symbol_offset, symbol_count, optional_size, _ = struct.unpack_from(
        "<HHLLLHH", data, 0
    )
    if machine != 0x14C:
        raise ValueError(f"Expected i386 COFF object, found machine {machine:#x}")

    section_table = 20 + optional_size
    sections: list[tuple[str, bytes, int]] = []
    for index in range(section_count):
        header = data[section_table + index * 40 : section_table + (index + 1) * 40]
        name = header[:8].rstrip(b"\0").decode("ascii", errors="replace")
        raw_size, raw_pointer = struct.unpack_from("<LL", header, 16)
        relocation_count = struct.unpack_from("<H", header, 32)[0]
        section_data = data[raw_pointer : raw_pointer + raw_size] if raw_size else b""
        sections.append((name, section_data, relocation_count))

    string_table_offset = symbol_offset + symbol_count * 18
    string_table_size = struct.unpack_from("<L", data, string_table_offset)[0]
    string_table = data[string_table_offset : string_table_offset + string_table_size]

    def symbol_name(record: bytes) -> str:
        if record[:4] == b"\0\0\0\0":
            offset = struct.unpack_from("<L", record, 4)[0]
            end = string_table.find(b"\0", offset)
            return string_table[offset:end].decode("ascii")
        return record[:8].rstrip(b"\0").decode("ascii")

    symbols: list[tuple[str, int, int]] = []
    index = 0
    while index < symbol_count:
        offset = symbol_offset + index * 18
        record = data[offset : offset + 18]
        name = symbol_name(record)
        value, section_number = struct.unpack_from("<Lh", record, 8)
        storage_class, auxiliary_count = record[16], record[17]
        if storage_class == 2 and section_number > 0:
            symbols.append((name, value, section_number))
        index += 1 + auxiliary_count

    found: dict[str, tuple[bytes, int]] = {}
    for name, value, section_number in symbols:
        if name not in names:
            continue
        section_name, section_data, relocation_count = sections[section_number - 1]
        if not section_name.startswith(".text"):
            raise ValueError(f"{name} is not in a text section: {section_name}")
        if relocation_count:
            raise ValueError(f"Unexpected relocations in {name}'s code section")
        next_values = [
            other_value
            for _, other_value, other_section in symbols
            if other_section == section_number and other_value > value
        ]
        end = min(next_values) if next_values else len(section_data)
        found[name] = (section_data[value:end], value)
    return found


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--object",
        action="append",
        type=Path,
        help="COFF object to inspect (repeatable; defaults to both shim objects)",
    )
    parser.add_argument(
        "--target",
        action="append",
        help="Limit verification to an address (repeatable; default: all 12)",
    )
    parser.add_argument(
        "--cfg",
        type=Path,
        default=ROOT / "audit/asi-hook-target-cfg-2026-09-27.csv",
    )
    args = parser.parse_args()

    selected = SHIMS if not args.target else {
        address.lower(): SHIMS[address.lower()]
        for address in args.target
        if address.lower() in SHIMS
    }
    if not selected:
        parser.error("No recognized hook target selected")

    addresses = set(selected)
    ghidra_bytes = read_cfg_bytes(args.cfg, addresses)
    object_paths = args.object or [
        ROOT / "build/hook-shims/x86_imvehft_hook_shims.obj",
        ROOT / "build/hook-shims/x86_hook_targets_remaining.obj",
    ]
    object_functions: dict[str, tuple[bytes, int]] = {}
    for object_path in object_paths:
        for name, body in read_coff_functions(object_path, set(selected.values())).items():
            if name in object_functions:
                raise SystemExit(f"Duplicate COFF function symbol: {name}")
            object_functions[name] = body
    missing = set(selected.values()) - object_functions.keys()
    if missing:
        raise SystemExit(f"Missing COFF function symbols: {', '.join(sorted(missing))}")

    for address, symbol in selected.items():
        actual = object_functions[symbol][0]
        expected = ghidra_bytes[address]
        if actual != expected:
            mismatch = next(
                (i for i, (left, right) in enumerate(zip(actual, expected)) if left != right),
                min(len(actual), len(expected)),
            )
            raise SystemExit(
                f"FAIL {address} {symbol}: byte mismatch at +{mismatch:#x}; "
                f"Ghidra ({len(expected)} bytes)={expected.hex(' ')}; "
                f"object ({len(actual)} bytes)={actual.hex(' ')}"
            )
        print(f"PASS {address} {symbol}: exact {len(expected)}-byte match")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
