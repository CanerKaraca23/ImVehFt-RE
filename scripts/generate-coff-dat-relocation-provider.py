#!/usr/bin/env python3
"""Generate a diagnostic data provider with relocatable PE data pointers.

Data-to-data sites and exact candidate-function entry targets become MASM
`DD OFFSET` expressions. Other code targets remain at their preferred-base
values and are explicitly reported as unresolved. This is a diagnostic
object, not a complete PE relocation solution.
"""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import struct
from collections import Counter, defaultdict
from pathlib import Path
from reloc_local_code_stubs import STUBS as LOCAL_CODE_STUBS


def parse_pe(path: Path) -> tuple[bytes, int, dict[str, dict[str, int]]]:
    image = path.read_bytes()
    if image[:2] != b"MZ":
        raise ValueError("input has no MZ signature")
    pe_offset = struct.unpack_from("<I", image, 0x3C)[0]
    if image[pe_offset : pe_offset + 4] != b"PE\0\0":
        raise ValueError("input has no PE signature")
    machine, count = struct.unpack_from("<HH", image, pe_offset + 4)
    optional_size = struct.unpack_from("<H", image, pe_offset + 20)[0]
    optional = pe_offset + 24
    if machine != 0x14C or struct.unpack_from("<H", image, optional)[0] != 0x10B:
        raise ValueError("expected x86 PE32")
    image_base = struct.unpack_from("<I", image, optional + 28)[0]
    table = optional + optional_size
    sections: dict[str, dict[str, int]] = {}
    for index in range(count):
        offset = table + index * 40
        name = image[offset : offset + 8].split(b"\0", 1)[0].decode("ascii")
        virtual_size, rva, raw_size, raw_offset = struct.unpack_from("<IIII", image, offset + 8)
        sections[name] = {
            "virtual_size": virtual_size,
            "rva": rva,
            "raw_size": raw_size,
            "raw_offset": raw_offset,
        }
    return image, image_base, sections


def emit_data(lines: list[str], data: bytes) -> None:
    for start in range(0, len(data), 16):
        lines.append("    DB " + ", ".join(f"0{byte:02X}h" for byte in data[start : start + 16]))


def external_code_symbol(obj_path: Path, address: str) -> str:
    """Find the unique public code symbol at offset zero in an address-named TU."""
    obj = obj_path.read_bytes()
    machine, section_count, _, symbol_ptr, symbol_count, optional_size, _ = struct.unpack_from(
        "<HHIIIHH", obj, 0
    )
    if machine != 0x14C or optional_size:
        raise ValueError(f"expected x86 COFF object: {obj_path}")
    section_names = {
        number + 1: obj[20 + number * 40 : 28 + number * 40].split(b"\0", 1)[0].decode("ascii")
        for number in range(section_count)
    }
    strings_at = symbol_ptr + symbol_count * 18
    string_size = struct.unpack_from("<I", obj, strings_at)[0]
    strings = obj[strings_at : strings_at + string_size]
    matches: set[str] = set()
    symbol_index = 0
    while symbol_index < symbol_count:
        at = symbol_ptr + symbol_index * 18
        raw_name = obj[at : at + 8]
        if raw_name[:4] == b"\0\0\0\0":
            string_offset = struct.unpack_from("<I", raw_name, 4)[0]
            end = strings.find(b"\0", string_offset)
            name = strings[string_offset:end].decode("ascii")
        else:
            name = raw_name.split(b"\0", 1)[0].decode("ascii")
        value, section_no = struct.unpack_from("<Ih", obj, at + 8)
        storage_class, aux_count = obj[at + 16], obj[at + 17]
        if (
            storage_class == 2
            and value == 0
            and section_names.get(section_no, "").startswith(".text")
            and address.lower() in name.lower()
        ):
            matches.add(name)
        symbol_index += 1 + aux_count
    if len(matches) != 1:
        raise ValueError(f"expected one public code symbol for {address} in {obj_path}, found {sorted(matches)}")
    return matches.pop()


def public_code_entry(obj_path: Path) -> str:
    """Return the unique external code symbol at offset zero in a candidate TU."""
    obj = obj_path.read_bytes()
    machine, section_count, _, symbol_ptr, symbol_count, optional_size, _ = struct.unpack_from(
        "<HHIIIHH", obj, 0
    )
    if machine != 0x14C or optional_size:
        raise ValueError(f"expected x86 COFF object: {obj_path}")
    section_names = {
        number + 1: obj[20 + number * 40 : 28 + number * 40].split(b"\0", 1)[0].decode("ascii")
        for number in range(section_count)
    }
    strings_at = symbol_ptr + symbol_count * 18
    string_size = struct.unpack_from("<I", obj, strings_at)[0]
    strings = obj[strings_at : strings_at + string_size]
    matches: set[str] = set()
    index = 0
    while index < symbol_count:
        at = symbol_ptr + index * 18
        raw_name = obj[at : at + 8]
        if raw_name[:4] == b"\0\0\0\0":
            string_offset = struct.unpack_from("<I", raw_name, 4)[0]
            end = strings.find(b"\0", string_offset)
            name = strings[string_offset:end].decode("ascii")
        else:
            name = raw_name.split(b"\0", 1)[0].decode("ascii")
        value, section_no = struct.unpack_from("<Ih", obj, at + 8)
        storage_class, aux_count = obj[at + 16], obj[at + 17]
        if storage_class == 2 and value == 0 and section_names.get(section_no, "").startswith(".text"):
            matches.add(name)
        index += 1 + aux_count
    if len(matches) != 1:
        raise ValueError(f"expected one public code entry in {obj_path}, found {sorted(matches)}")
    return matches.pop()


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("image", type=Path)
    parser.add_argument("inventory", type=Path, help="current COFF DAT inventory CSV")
    parser.add_argument("storage", type=Path, help="current PE storage-class CSV")
    parser.add_argument("relocations", type=Path, help=".rdata/.data relocation coverage CSV")
    parser.add_argument("--objects-dir", type=Path, help="fresh address-named candidate COFF objects")
    parser.add_argument("--hook-shim-fixups", type=Path, help="Ghidra-derived supplemental hook-shim fixup inventory")
    parser.add_argument(
        "--public-data-address", action="append", default=[], type=lambda value: int(value, 0),
        help="export an original .rdata/.data address as IVF_RELOC_TARGET_<VA>; repeatable",
    )
    parser.add_argument(
        "--public-data-address-inventory", type=Path,
        help="CSV of candidate source literals; export rows in .rdata/.data",
    )
    parser.add_argument(
        "--public-symbol-alias-inventory", type=Path,
        help="CSV with address,symbol rows; define exact external symbol labels at verified PE data addresses",
    )
    parser.add_argument("--init-array-crosswalk", type=Path, help="verified CRT initializer/exit-callback crosswalk")
    parser.add_argument("--unmapped-target-disassembly", type=Path, help="Ghidra disassembly CSV for known noncandidate helpers")
    parser.add_argument("--initterm-e-disassembly", type=Path, help="Ghidra disassembly CSV for _initterm_e initializer entries")
    parser.add_argument("--initterm-e-branch-disassembly", type=Path, help="Ghidra branch-tail CSV for _initterm_e allocation callbacks")
    parser.add_argument("--initterm-e-size-tail-disassembly", type=Path, help="Ghidra size-tail CSV for _initterm_e state-table callback")
    parser.add_argument("--initterm-e-allocation-cleanup-disassembly", type=Path, help="Ghidra allocation-loop/cleanup CSV for _initterm_e state-table callback")
    parser.add_argument("--asm", type=Path, required=True)
    parser.add_argument("--manifest", type=Path, required=True)
    args = parser.parse_args()
    if args.asm.exists() or args.manifest.exists():
        parser.error("refusing to overwrite an existing output")

    image, image_base, pe_sections = parse_pe(args.image)
    pe_names = (".rdata", ".data")
    segment_for = {".rdata": ".const", ".data": ".data"}
    contents: dict[str, bytearray] = {}
    for pe_name in pe_names:
        section = pe_sections[pe_name]
        extent = max(section["virtual_size"], section["raw_size"])
        raw = image[section["raw_offset"] : section["raw_offset"] + section["raw_size"]]
        if len(raw) != section["raw_size"]:
            raise ValueError(f"truncated section {pe_name}")
        contents[pe_name] = bytearray(raw + bytes(max(0, extent - len(raw))))

    with args.storage.open("r", encoding="utf-8-sig", newline="") as stream:
        storage = {row["address"].upper(): row for row in csv.DictReader(stream)}
    labels: dict[str, dict[int, set[str]]] = {
        ".const": defaultdict(set),
        ".data": defaultdict(set),
    }
    public_hook_shim_labels: set[str] = set()
    if args.hook_shim_fixups:
        shim_fixup_doc = json.loads(args.hook_shim_fixups.read_text(encoding="utf-8"))
        for fixup in shim_fixup_doc["fixups"]:
            if fixup["kind"] not in (
                "absolute-image-memory-reference",
                "absolute-image-pointer-immediate",
            ):
                continue
            target_va = int(fixup["original_target"], 16)
            target_rva = target_va - image_base
            for pe_name in pe_names:
                offset = target_rva - pe_sections[pe_name]["rva"]
                if 0 <= offset < len(contents[pe_name]):
                    label = f"IVF_RELOC_TARGET_{target_va:08X}"
                    labels[segment_for[pe_name]][offset].add(label)
                    public_hook_shim_labels.add(label)
                    break
            else:
                raise ValueError(
                    f"hook-shim data operand is not in .rdata/.data: {target_va:#010x}"
                )
    public_data_addresses = set(args.public_data_address)
    if args.public_data_address_inventory:
        with args.public_data_address_inventory.open("r", encoding="utf-8-sig", newline="") as stream:
            for row in csv.DictReader(stream):
                if row.get("section") in (".rdata", ".data"):
                    public_data_addresses.add(int(row["address"], 16))
    for target_va in sorted(public_data_addresses):
        target_rva = target_va - image_base
        for pe_name in pe_names:
            offset = target_rva - pe_sections[pe_name]["rva"]
            if 0 <= offset < len(contents[pe_name]):
                label = f"IVF_RELOC_TARGET_{target_va:08X}"
                labels[segment_for[pe_name]][offset].add(label)
                public_hook_shim_labels.add(label)
                break
        else:
            raise ValueError(
                f"requested public address is not in .rdata/.data: {target_va:#010x}"
            )
    public_symbol_aliases: dict[str, int] = {}
    if args.public_symbol_alias_inventory:
        with args.public_symbol_alias_inventory.open("r", encoding="utf-8-sig", newline="") as stream:
            for row in csv.DictReader(stream):
                target_va = int(row["address"], 0)
                symbol = row["symbol"].strip()
                if not symbol or any(char.isspace() for char in symbol) or any(char in symbol for char in ":\r\n"):
                    raise ValueError(f"invalid COFF symbol alias: {symbol!r}")
                previous = public_symbol_aliases.get(symbol)
                if previous is not None and previous != target_va:
                    raise ValueError(
                        f"COFF symbol alias maps to multiple addresses: {symbol}: {previous:#x}, {target_va:#x}"
                    )
                rva = target_va - image_base
                for pe_name in pe_names:
                    offset = rva - pe_sections[pe_name]["rva"]
                    if 0 <= offset < len(contents[pe_name]):
                        labels[segment_for[pe_name]][offset].add(symbol)
                        public_symbol_aliases[symbol] = target_va
                        break
                else:
                    raise ValueError(
                        f"COFF symbol alias address is not in .rdata/.data: {symbol} at {target_va:#010x}"
                    )
    unresolved_names: set[str] = set()
    dat_names_by_address: dict[str, set[str]] = defaultdict(set)
    with args.inventory.open("r", encoding="utf-8-sig", newline="") as stream:
        for row in csv.DictReader(stream):
            address = row["address"].upper()
            item = storage.get(address)
            if item is None:
                raise ValueError(f"missing storage row for {address}")
            pe_name = item["section"]
            if pe_name not in contents:
                raise ValueError(f"unsupported DAT section {pe_name} for {address}")
            offset = int(item["rva_in_section"], 16)
            section = pe_sections[pe_name]
            if int(address, 16) != image_base + section["rva"] + offset:
                raise ValueError(f"DAT address/section mismatch for {address}")
            if item["storage_class"] == "raw-backed":
                file_offset = int(item["file_offset"], 16)
                initial = bytes.fromhex(item["initial_bytes"])
                if file_offset != section["raw_offset"] + offset or image[file_offset : file_offset + len(initial)] != initial:
                    raise ValueError(f"DAT original byte/file mapping mismatch for {address}")
            elif item["storage_class"] != "virtual-zero-fill" or any(contents[pe_name][offset : offset + 4]):
                raise ValueError(f"invalid zero-fill mapping for {address}")
            segment = segment_for[pe_name]
            defined = {name for name in row["defined_symbols"].split(" | ") if name}
            dat_names_by_address[address].update(defined)
            for name in (name for name in row["undefined_symbols"].split(" | ") if name):
                dat_names_by_address[address].add(name)
                if name not in defined:
                    labels[segment][offset].add(name)
                    unresolved_names.add(name)

    reloc_sites: dict[str, dict[int, dict[str, str]]] = {".rdata": {}, ".data": {}}
    target_labels: dict[str, str] = {}
    target_counts: Counter[tuple[str, str]] = Counter()
    unresolved_code_sites: list[dict[str, str]] = []
    candidate_code_sites: dict[str, dict[int, str]] = {".rdata": {}, ".data": {}}
    candidate_code_symbols: set[str] = set()
    startup_thunks: dict[int, tuple[str, str]] = {}
    helper_stubs: dict[int, tuple[str, str]] = {}
    cleanup_stubs: dict[int, tuple[str, tuple[str, str, str]]] = {}
    entry_stubs: dict[int, tuple[str, str]] = {}
    simple_code_targets: dict[int, str] = {}
    initterm_stubs: dict[int, tuple[str, int]] = {}
    external_data_symbols: set[str] = set()
    if args.init_array_crosswalk:
        if not args.objects_dir:
            parser.error("--init-array-crosswalk requires --objects-dir")
        with args.init_array_crosswalk.open("r", encoding="utf-8-sig", newline="") as stream:
            for row in csv.DictReader(stream):
                entry = row["entry_target_va"].lower()
                callback_source = row["exit_callback_source"]
                if not entry.startswith("0x") or entry == "0x00000000" or not callback_source:
                    continue
                entry_va = int(entry, 16)
                callback_obj = args.objects_dir / f"{Path(callback_source).stem.lower()}.obj"
                callback_symbol = public_code_entry(callback_obj)
                startup_thunks[entry_va] = (
                    f"IVF_CRT_INIT_THUNK_{entry_va:08X}",
                    callback_symbol,
                )
                candidate_code_symbols.add(callback_symbol)
        atexit_symbol = public_code_entry(args.objects_dir / "10010529.obj")
        if startup_thunks:
            candidate_code_symbols.add(atexit_symbol)
        complex_init_symbol = public_code_entry(args.objects_dir / "1000a090.obj")
        candidate_code_symbols.add(complex_init_symbol)
    else:
        atexit_symbol = ""
    if args.unmapped_target_disassembly:
        if not args.objects_dir:
            parser.error("--unmapped-target-disassembly requires --objects-dir")
        with args.unmapped_target_disassembly.open("r", encoding="utf-8-sig", newline="") as stream:
            all_unmapped_rows = list(csv.DictReader(stream))
        entry_rows = [row for row in all_unmapped_rows if int(row["target_va"], 16) == 0x10001000]
        entry_instructions = [row["instruction"].strip().upper() for row in sorted(entry_rows, key=lambda row: int(row["instruction_va"], 16))]
        if entry_instructions != ["MOV DWORD PTR [ECX],0X10022250", "JMP 0X1001031F"]:
            raise ValueError(f"unexpected Ghidra PE-entry shim at 0x10001000: {entry_instructions}")
        entry_symbol = public_code_entry(args.objects_dir / "1001031f.obj")
        candidate_code_symbols.add(entry_symbol)
        entry_stubs[0x10001000] = ("IVF_CONTEXT_SHIM_10001000", entry_symbol)
        entry_rva = 0x10022250 - image_base
        for pe_name in pe_names:
            entry_offset = entry_rva - pe_sections[pe_name]["rva"]
            if 0 <= entry_offset < len(contents[pe_name]):
                labels[segment_for[pe_name]][entry_offset].add("IVF_RELOC_TARGET_10022250")
                break
        else:
            raise ValueError("PE-entry global 0x10022250 is outside .data/.rdata")
        text_section = pe_sections[".text"]
        for stub in LOCAL_CODE_STUBS:
            label = stub["label"]
            resolved: dict[str, str] = {}
            all_fixups = list(stub["fixups"])
            for block in stub.get("blocks", ()):
                all_fixups.extend(block["fixups"])
            for _, kind, target_va in all_fixups:
                if kind == "REL32":
                    symbol = simple_code_targets.get(target_va)
                    if symbol is None:
                        symbol = public_code_entry(args.objects_dir / f"{target_va:08x}.obj")
                        candidate_code_symbols.add(symbol)
                    resolved[f"CODE_{target_va:08X}"] = symbol
                elif kind == "DIR32":
                    rva = target_va - image_base
                    for pe_name in pe_names:
                        data_offset = rva - pe_sections[pe_name]["rva"]
                        if 0 <= data_offset < len(contents[pe_name]):
                            labels[segment_for[pe_name]][data_offset].add(f"IVF_RELOC_TARGET_{target_va:08X}")
                            break
                    else:
                        raise ValueError(f"micro-stub data target outside .data/.rdata: {target_va:#x}")
            for target_va in stub["targets"]:
                address_rva = target_va - image_base
                original_offset = text_section["raw_offset"] + address_rva - text_section["rva"]
                original_bytes = bytearray(image[original_offset:original_offset + len(stub["body"])])
                if len(original_bytes) != len(stub["body"]):
                    raise ValueError(f"micro-stub target outside original .text: {target_va:#x}")
                for fixup_offset, kind, expected_target in stub["fixups"]:
                    if kind == "DIR32":
                        actual_target = struct.unpack_from("<I", original_bytes, fixup_offset)[0]
                    elif kind == "REL32":
                        displacement = struct.unpack_from("<i", original_bytes, fixup_offset)[0]
                        actual_target = target_va + fixup_offset + 4 + displacement
                    else:
                        displacement = struct.unpack_from("<b", original_bytes, fixup_offset)[0]
                        actual_target = target_va + fixup_offset + 1 + displacement
                    if actual_target != expected_target:
                        raise ValueError(f"micro-stub source fixup at {target_va + fixup_offset:#x} targets {actual_target:#x}, expected {expected_target:#x}")
                    width = 1 if kind == "REL8" else 4
                    original_bytes[fixup_offset:fixup_offset + width] = bytes(width)
                if bytes(original_bytes) != stub["body"]:
                    raise ValueError(f"micro-stub source bytes differ from template at {target_va:#x}")
                simple_code_targets[target_va] = label
            for block in stub.get("blocks", ()):
                source_va = block["source_va"]
                source_rva = source_va - image_base
                source_offset = text_section["raw_offset"] + source_rva - text_section["rva"]
                original_bytes = bytearray(image[source_offset:source_offset + len(block["body"])])
                if len(original_bytes) != len(block["body"]):
                    raise ValueError(f"micro-stub continuation outside original .text: {source_va:#x}")
                for fixup_offset, kind, expected_target in block["fixups"]:
                    if kind == "DIR32":
                        actual_target = struct.unpack_from("<I", original_bytes, fixup_offset)[0]
                    elif kind == "REL32":
                        displacement = struct.unpack_from("<i", original_bytes, fixup_offset)[0]
                        actual_target = source_va + fixup_offset + 4 + displacement
                    else:
                        displacement = struct.unpack_from("<b", original_bytes, fixup_offset)[0]
                        actual_target = source_va + fixup_offset + 1 + displacement
                    if actual_target != expected_target:
                        raise ValueError(f"micro-stub continuation fixup at {source_va + fixup_offset:#x} targets {actual_target:#x}, expected {expected_target:#x}")
                    width = 1 if kind == "REL8" else 4
                    original_bytes[fixup_offset:fixup_offset + width] = bytes(width)
                if bytes(original_bytes) != block["body"]:
                    raise ValueError(f"micro-stub continuation bytes differ from template at {source_va:#x}")
        rows = [row for row in all_unmapped_rows if row["target_va"].lower() == "1001af2b"]
        instructions = [
            row["instruction"].strip().upper()
            for row in sorted(rows, key=lambda row: int(row["instruction_va"], 16))
        ]
        if instructions != ["PUSH 0X2", "CALL 0X10012E01", "POP ECX", "RET"]:
            raise ValueError(f"unexpected Ghidra instruction window for 0x1001af2b: {instructions}")
        helper_symbol = public_code_entry(args.objects_dir / "10012e01.obj")
        candidate_code_symbols.add(helper_symbol)
        helper_stubs[0x1001AF2B] = ("IVF_CFLTCVT_FALLBACK_1001AF2B", helper_symbol)
        cleanup_rows = [row for row in all_unmapped_rows if int(row["target_va"], 16) == 0x100130D6]
        cleanup_instructions = [row["instruction"].strip().upper() for row in sorted(cleanup_rows, key=lambda row: int(row["instruction_va"], 16))]
        cleanup_expected = ["CALL 0X10013EF3", "CMP BYTE PTR [0X10039A34],0X0", "JZ 0X100130E9", "CALL 0X100181DC", "PUSH DWORD PTR [0X1003C520]", "CALL 0X100116DB", "POP ECX", "RET"]
        if cleanup_instructions != cleanup_expected:
            raise ValueError(f"unexpected Ghidra CRT cleanup callback at 0x100130d6: {cleanup_instructions}")
        cleanup_symbols = (
            public_code_entry(args.objects_dir / "10013ef3.obj"),
            public_code_entry(args.objects_dir / "100181dc.obj"),
            public_code_entry(args.objects_dir / "100116db.obj"),
        )
        candidate_code_symbols.update(cleanup_symbols)
        cleanup_stubs[0x100130D6] = ("IVF_CRT_CLEANUP_100130D6", cleanup_symbols)
    if args.initterm_e_disassembly:
        expected = {
            0x1001704C: (
                ["PUSH 0XA", "CALL DWORD PTR [0X1002210C]", "MOV [0X1003C414],EAX", "XOR EAX,EAX", "RET"],
                0x1003C414,
            ),
            0x1001C5E0: (
                ["PUSH 0XA", "CALL DWORD PTR [0X1002210C]", "MOV [0X1003C40C],EAX", "XOR EAX,EAX", "RET"],
                0x1003C40C,
            ),
        }
        with args.initterm_e_disassembly.open("r", encoding="utf-8-sig", newline="") as stream:
            all_rows = list(csv.DictReader(stream))
        for address, (expected_instructions, global_address) in expected.items():
            rows = [row for row in all_rows if int(row["target_va"], 16) == address]
            instructions = [
                row["instruction"].strip().upper()
                for row in sorted(rows, key=lambda row: int(row["instruction_va"], 16))
            ]
            if instructions != expected_instructions:
                raise ValueError(f"unexpected Ghidra _initterm_e sequence at {address:#x}: {instructions}")
            initterm_stubs[address] = (f"IVF_INITTERM_E_{address:08X}", global_address)
        external_data_symbols.add("__imp__IsProcessorFeaturePresent@4")
        allocation_entry = 0x100104BC
        allocation_expected = [
            "MOV EDI,EDI", "PUSH ESI", "PUSH 0X4", "PUSH 0X20", "CALL 0X10012A3A",
            "POP ECX", "POP ECX", "MOV ESI,EAX", "PUSH ESI", "CALL DWORD PTR [0X1002205C]",
            "MOV [0X1003D54C],EAX", "MOV [0X1003D548],EAX", "TEST ESI,ESI", "JNZ 0X100104E6",
            "PUSH 0X18", "POP EAX", "POP ESI", "RET",
        ]
        allocation_rows = [row for row in all_rows if int(row["target_va"], 16) == allocation_entry]
        allocation_instructions = [
            row["instruction"].strip().upper()
            for row in sorted(allocation_rows, key=lambda row: int(row["instruction_va"], 16))
        ]
        if allocation_instructions != allocation_expected:
            raise ValueError(f"unexpected Ghidra _initterm_e allocation sequence: {allocation_instructions}")
        if not args.initterm_e_branch_disassembly:
            raise ValueError("the Ghidra branch-tail CSV is required for the allocation callback")
        with args.initterm_e_branch_disassembly.open("r", encoding="utf-8-sig", newline="") as stream:
            tail_rows = [row for row in csv.DictReader(stream) if int(row["target_va"], 16) == 0x100104E6]
        tail_instructions = [row["instruction"].strip().upper() for row in sorted(tail_rows, key=lambda row: int(row["instruction_va"], 16))]
        if tail_instructions != ["AND DWORD PTR [ESI],0X0", "XOR EAX,EAX", "POP ESI", "RET"]:
            raise ValueError(f"unexpected Ghidra _initterm_e allocation success tail: {tail_instructions}")
        calloc_symbol = public_code_entry(args.objects_dir / "10012a3a.obj")
        candidate_code_symbols.add(calloc_symbol)
        initterm_stubs[allocation_entry] = (f"IVF_INITTERM_E_{allocation_entry:08X}", 0x1003D54C)
        external_data_symbols.add("__imp__EncodePointer@4")
        state_entry = 0x10013025
        with args.initterm_e_branch_disassembly.open("r", encoding="utf-8-sig", newline="") as stream:
            state_rows = list(csv.DictReader(stream))
        if not args.initterm_e_size_tail_disassembly or not args.initterm_e_allocation_cleanup_disassembly:
            raise ValueError("the Ghidra _initterm_e size-tail and allocation-cleanup CSVs are required for the state-table callback")
        with args.initterm_e_size_tail_disassembly.open("r", encoding="utf-8-sig", newline="") as stream:
            state_tail_rows = list(csv.DictReader(stream))
        with args.initterm_e_allocation_cleanup_disassembly.open("r", encoding="utf-8-sig", newline="") as stream:
            state_tail_rows.extend(csv.DictReader(stream))
        state_head_rows = [row for row in all_rows if int(row["target_va"], 16) == state_entry]
        state_branch_rows = [row for row in state_rows if int(row["target_va"], 16) in (0x10013039, 0x1001303F, 0x10013075)]
        state_rows_by_va = {int(row["instruction_va"], 16): row for row in state_head_rows + state_branch_rows + state_tail_rows}
        state_required_vas = [0x10013025, 0x1001302A, 0x1001302B, 0x1001302D, 0x1001302E, 0x10013030, 0x10013032, 0x10013037, 0x10013039, 0x1001303F, 0x10013075, 0x10013083, 0x100130D5]
        missing_state_vas = [va for va in state_required_vas if va not in state_rows_by_va]
        if missing_state_vas:
            raise ValueError(f"incomplete Ghidra _initterm_e state-table instruction evidence: {[hex(va) for va in missing_state_vas]}")
        # Ghidra's temporary body omitted the five-byte loop-head load at 0x1001307e.
        # Confirm those exact bytes directly against the hashed source PE before reconstructing it.
        text_section = pe_sections[".text"]
        missing_rva = 0x1001307E - image_base
        missing_offset = text_section["raw_offset"] + missing_rva - text_section["rva"]
        if image[missing_offset:missing_offset + 5] != bytes.fromhex("A1 20 C5 03 10"):
            raise ValueError("unseen _initterm_e loop-head bytes at 0x1001307e differ from expected MOV EAX,[0x1003c520]")
        initterm_stubs[state_entry] = (f"IVF_INITTERM_E_{state_entry:08X}", 0x1003C520)
        for address in (0x1003D540, 0x1003C520, 0x1003C420, 0x100291D0, 0x10029450, 0x100291E0, 0x10029240):
            rva = address - image_base
            for pe_name in pe_names:
                offset = rva - pe_sections[pe_name]["rva"]
                if 0 <= offset < len(contents[pe_name]):
                    labels[segment_for[pe_name]][offset].add(f"IVF_RELOC_TARGET_{address:08X}")
                    break
            else:
                raise ValueError(f"_initterm_e state-table target outside .data/.rdata: {address:#x}")
        cleanup_global = 0x10039A34
        cleanup_rva = cleanup_global - image_base
        for pe_name in pe_names:
            cleanup_offset = cleanup_rva - pe_sections[pe_name]["rva"]
            if 0 <= cleanup_offset < len(contents[pe_name]):
                labels[segment_for[pe_name]][cleanup_offset].add(f"IVF_RELOC_TARGET_{cleanup_global:08X}")
                break
        else:
            raise ValueError("CRT cleanup flag 0x10039a34 is outside .data/.rdata")
    with args.relocations.open("r", encoding="utf-8-sig", newline="") as stream:
        for row in csv.DictReader(stream):
            site_section = row["site_section"]
            target_section = row["target_section"]
            if site_section not in reloc_sites:
                continue
            site_va = int(row["site_va"], 16)
            stored_va = int(row["stored_va"], 16)
            site_meta = pe_sections[site_section]
            site_offset = site_va - (image_base + site_meta["rva"])
            if site_offset < 0 or site_offset + 4 > len(contents[site_section]):
                raise ValueError(f"relocation site outside {site_section}: {site_va:#x}")
            original = struct.unpack_from("<I", contents[site_section], site_offset)[0]
            if original != stored_va:
                raise ValueError(f"relocation input does not match PE bytes at {site_va:#x}")
            target_counts[(site_section, target_section)] += 1
            if target_section not in contents:
                initterm_stub = initterm_stubs.get(stored_va)
                if initterm_stub:
                    candidate_code_sites[site_section][site_offset] = initterm_stub[0]
                    continue
                cleanup_stub = cleanup_stubs.get(stored_va)
                if cleanup_stub:
                    candidate_code_sites[site_section][site_offset] = cleanup_stub[0]
                    continue
                entry_stub = entry_stubs.get(stored_va)
                if entry_stub:
                    candidate_code_sites[site_section][site_offset] = entry_stub[0]
                    continue
                simple_stub = simple_code_targets.get(stored_va)
                if simple_stub:
                    candidate_code_sites[site_section][site_offset] = simple_stub
                    continue
                helper_stub = helper_stubs.get(stored_va)
                if helper_stub:
                    candidate_code_sites[site_section][site_offset] = helper_stub[0]
                    continue
                thunk = startup_thunks.get(stored_va)
                if thunk:
                    candidate_code_sites[site_section][site_offset] = thunk[0]
                    continue
                function_name = row.get("exact_candidate_function", "")
                if args.objects_dir and function_name:
                    target_obj = args.objects_dir / f"{stored_va:08x}.obj"
                    symbol = public_code_entry(target_obj)
                    candidate_code_sites[site_section][site_offset] = symbol
                    candidate_code_symbols.add(symbol)
                    continue
                unresolved_code_sites.append({"site_va": row["site_va"], "stored_va": row["stored_va"]})
                continue
            target_meta = pe_sections[target_section]
            target_offset = stored_va - (image_base + target_meta["rva"])
            if target_offset < 0 or target_offset >= len(contents[target_section]):
                raise ValueError(f"target outside {target_section}: {stored_va:#x}")
            label = target_labels.setdefault(
                stored_va, f"IVF_RELOC_TARGET_{stored_va:08X}"
            )
            labels[segment_for[target_section]][target_offset].add(label)
            if site_offset in reloc_sites[site_section]:
                raise ValueError(f"duplicate relocation site {site_va:#x}")
            reloc_sites[site_section][site_offset] = {
                "target_va": stored_va,
                "label": label,
            }

    special_data_symbols = dat_names_by_address.get("0X1003C328", set())
    stateful_data_labels = {
        address: f"IVF_RELOC_TARGET_{address:08X}"
        for address in (0x1003C38C, 0x1003C3E8, 0x1003C3EC, 0x1003C3FC)
    }
    if startup_thunks and 0x100208D0 in startup_thunks:
        for address, label in stateful_data_labels.items():
            rva = address - image_base
            for pe_name in pe_names:
                offset = rva - pe_sections[pe_name]["rva"]
                if 0 <= offset < len(contents[pe_name]):
                    labels[segment_for[pe_name]][offset].add(label)
                    break
            else:
                raise ValueError(f"stateful initializer data target outside .data/.rdata: {address:#x}")
    for _, global_address in initterm_stubs.values():
        global_rva = global_address - image_base
        for pe_name in pe_names:
            offset = global_rva - pe_sections[pe_name]["rva"]
            if 0 <= offset < len(contents[pe_name]):
                labels[segment_for[pe_name]][offset].add(f"IVF_RELOC_TARGET_{global_address:08X}")
                break
        else:
                raise ValueError(f"_initterm_e global target outside .data/.rdata: {global_address:#x}")
    if 0x100104BC in initterm_stubs:
        for global_address in (0x1003D548,):
            global_rva = global_address - image_base
            for pe_name in pe_names:
                offset = global_rva - pe_sections[pe_name]["rva"]
                if 0 <= offset < len(contents[pe_name]):
                    labels[segment_for[pe_name]][offset].add(f"IVF_RELOC_TARGET_{global_address:08X}")
                    break
            else:
                raise ValueError(f"_initterm_e global target outside .data/.rdata: {global_address:#x}")
    if startup_thunks and 0x100209F0 in startup_thunks:
        if len(special_data_symbols) != 1:
            raise ValueError(f"expected one DAT symbol at 0x1003c328, found {sorted(special_data_symbols)}")
        special_va = 0x10024C74
        special_rva = special_va - image_base
        for pe_name in pe_names:
            delta = special_rva - pe_sections[pe_name]["rva"]
            if 0 <= delta < len(contents[pe_name]):
                labels[segment_for[pe_name]][delta].add(f"IVF_RELOC_TARGET_{special_va:08X}")
                break
        else:
            raise ValueError("special initializer target 0x10024c74 is outside .data/.rdata")

    lines = [
        "; Diagnostic provider: exact original PE bytes plus data-to-data COFF fixups.",
        "; .text-target pointers remain preferred-base constants; not loadable.",
        ".386",
        ".model flat",
        "option casemap:none",
        "",
    ]
    lines.extend(f"EXTERN {symbol}:PROC" for symbol in sorted(candidate_code_symbols))
    lines.extend(f"EXTERN {symbol}:DWORD" for symbol in sorted(external_data_symbols))
    if candidate_code_symbols:
        lines.append("")
    if startup_thunks or helper_stubs or initterm_stubs or cleanup_stubs or entry_stubs or simple_code_targets:
        lines.append(".code")
    if startup_thunks:
        for entry_va, (thunk_label, callback_symbol) in sorted(startup_thunks.items()):
            lines.extend([f"PUBLIC {thunk_label}", f"{thunk_label} PROC"])
            if entry_va == 0x100208D0:
                done_label = f"IVF_CRT_INIT_DONE_{entry_va:08X}"
                lines.extend(
                    [
                        "    mov eax, 1",
                        f"    test BYTE PTR [{stateful_data_labels[0x1003C3FC]}], al",
                        f"    jnz {done_label}",
                        f"    or DWORD PTR [{stateful_data_labels[0x1003C3FC]}], eax",
                        "    xor eax, eax",
                        f"    push OFFSET {callback_symbol}",
                        f"    mov DWORD PTR [{stateful_data_labels[0x1003C3E8]}], eax",
                        f"    mov DWORD PTR [{stateful_data_labels[0x1003C3EC]}], eax",
                        f"    call {atexit_symbol}",
                        "    add esp, 4",
                        f"{done_label}:",
                        f"    mov DWORD PTR [{stateful_data_labels[0x1003C38C]}], OFFSET {stateful_data_labels[0x1003C3E8]}",
                        "    ret",
                    ]
                )
            elif entry_va == 0x100209F0:
                lines.extend(
                    [
                        f"    call {complex_init_symbol}",
                        f"    push OFFSET {callback_symbol}",
                        f"    mov DWORD PTR [{next(iter(special_data_symbols))}], OFFSET IVF_RELOC_TARGET_10024C74",
                        f"    call {atexit_symbol}",
                        "    pop ecx",
                        "    ret",
                    ]
                )
            else:
                lines.extend(
                    [
                        f"    push OFFSET {callback_symbol}",
                        f"    call {atexit_symbol}",
                        "    pop ecx",
                        "    ret",
                    ]
                )
            lines.extend([f"{thunk_label} ENDP", ""])
    for _, (stub_label, helper_symbol) in sorted(helper_stubs.items()):
        lines.extend(
            [
                f"PUBLIC {stub_label}",
                f"{stub_label} PROC",
                "    push 2",
                f"    call {helper_symbol}",
                "    pop ecx",
                "    ret",
                f"{stub_label} ENDP",
                "",
            ]
        )
    for address, (stub_label, cleanup_symbols) in sorted(cleanup_stubs.items()):
        flushall_symbol, fcloseall_symbol, free_symbol = cleanup_symbols
        lines.extend([
            f"PUBLIC {stub_label}", f"{stub_label} PROC", f"    call {flushall_symbol}",
            "    cmp BYTE PTR [IVF_RELOC_TARGET_10039A34], 0", f"    jz {stub_label}_skip_fcloseall",
            f"    call {fcloseall_symbol}", f"{stub_label}_skip_fcloseall:",
            "    push DWORD PTR [IVF_RELOC_TARGET_1003C520]", f"    call {free_symbol}",
            "    pop ecx", "    ret", f"{stub_label} ENDP", "",
        ])
    for address, (stub_label, entry_symbol) in sorted(entry_stubs.items()):
        lines.extend([
            f"PUBLIC {stub_label}", f"{stub_label} PROC",
            "    mov DWORD PTR [ecx], OFFSET IVF_RELOC_TARGET_10022250",
            f"    jmp {entry_symbol}", f"{stub_label} ENDP", "",
        ])
    emitted_simple_labels: set[str] = set()
    for stub in LOCAL_CODE_STUBS:
        label = stub["label"]
        if label in emitted_simple_labels or not any(target in simple_code_targets for target in stub["targets"]):
            continue
        emitted_simple_labels.add(label)
        resolved = {}
        all_fixups = list(stub["fixups"])
        for block in stub.get("blocks", ()):
            all_fixups.extend(block["fixups"])
        for _, kind, target_va in all_fixups:
            if kind == "REL32":
                symbol = simple_code_targets.get(target_va)
                if symbol is None:
                    symbol = public_code_entry(args.objects_dir / f"{target_va:08x}.obj")
                resolved[f"CODE_{target_va:08X}"] = symbol
        tail_jump = stub.get("tail_jump")
        if tail_jump is not None:
            tail_symbol = public_code_entry(args.objects_dir / f"{tail_jump:08x}.obj")
            candidate_code_symbols.add(tail_symbol)
            resolved[f"TAIL_CODE_{tail_jump:08X}"] = tail_symbol
        for block in stub.get("blocks", ()):
            lines.append(f"PUBLIC {block['label']}")
        for local_label in stub.get("local_labels", {}).values():
            lines.append(f"PUBLIC {local_label}")
        lines.extend([f"PUBLIC {label}", f"{label} PROC"])
        lines.extend(f"    {line.format(**resolved)}" for line in stub["asm"])
        if tail_jump is not None:
            lines.append(f"    jmp {resolved[f'TAIL_CODE_{tail_jump:08X}']}")
        lines.extend([f"{label} ENDP", ""])
        for block in stub.get("blocks", ()):
            block_label = block["label"]
            lines.extend([f"{block_label} PROC"])
            lines.extend(f"    {line.format(**resolved)}" for line in block["asm"])
            lines.extend([f"{block_label} ENDP", ""])
    for address, (stub_label, global_address) in sorted(initterm_stubs.items()):
        if address == 0x100104BC:
            lines.extend([
                f"PUBLIC {stub_label}", f"{stub_label} PROC", "    push esi", "    push 4", "    push 20h",
                f"    call {calloc_symbol}", "    add esp, 8", "    mov esi, eax", "    push esi",
                "    call DWORD PTR [__imp__EncodePointer@4]",
                "    mov DWORD PTR [IVF_RELOC_TARGET_1003D54C], eax",
                "    mov DWORD PTR [IVF_RELOC_TARGET_1003D548], eax", "    test esi, esi", f"    jnz {stub_label}_allocated",
                "    mov eax, 18h", "    pop esi", "    ret", f"{stub_label}_allocated:", "    and DWORD PTR [esi], 0",
                "    xor eax, eax", "    pop esi", "    ret", f"{stub_label} ENDP", "",
            ])
            continue
        if address == 0x10013025:
            labels_for_state = {va: f"IVF_RELOC_TARGET_{va:08X}" for va in (0x1003D540, 0x1003C520, 0x1003C420, 0x100291D0, 0x10029450, 0x100291E0, 0x10029240)}
            lines.extend([
                f"PUBLIC {stub_label}", f"{stub_label} PROC",
                f"    mov eax, DWORD PTR [{labels_for_state[0x1003D540]}]", "    push esi", "    push 14h", "    pop esi", "    test eax, eax", f"    jnz {stub_label}_count_ready", "    mov eax, 200h", f"    jmp {stub_label}_allocate",
                f"{stub_label}_count_ready:", "    cmp eax, esi", f"    jge {stub_label}_allocate", "    mov eax, esi", f"{stub_label}_allocate:", f"    mov DWORD PTR [{labels_for_state[0x1003D540]}], eax",
                "    push 4", "    push eax", f"    call {calloc_symbol}", "    pop ecx", "    pop ecx", f"    mov DWORD PTR [{labels_for_state[0x1003C520]}], eax", "    test eax, eax", f"    jnz {stub_label}_tables_ready",
                "    push 4", "    push esi", f"    mov DWORD PTR [{labels_for_state[0x1003D540]}], esi", f"    call {calloc_symbol}", "    pop ecx", "    pop ecx", f"    mov DWORD PTR [{labels_for_state[0x1003C520]}], eax", "    test eax, eax", f"    jnz {stub_label}_tables_ready", "    mov eax, 1Ah", "    pop esi", "    ret",
                f"{stub_label}_tables_ready:", "    xor edx, edx", f"    mov ecx, OFFSET {labels_for_state[0x100291D0]}", f"{stub_label}_table_loop:", "    mov DWORD PTR [edx + eax], ecx", "    add ecx, 20h", "    add edx, 4", f"    cmp ecx, OFFSET {labels_for_state[0x10029450]}", f"    jl {stub_label}_table_loop",
                "    push -2", "    pop esi", "    xor edx, edx", f"    mov ecx, OFFSET {labels_for_state[0x100291E0]}", "    push edi", f"{stub_label}_state_loop:", "    mov eax, edx", "    sar eax, 5", f"    mov eax, DWORD PTR [eax * 4 + {labels_for_state[0x1003C420]}]", "    mov edi, edx", "    and edi, 1Fh", "    shl edi, 6", "    mov eax, DWORD PTR [edi + eax]", "    cmp eax, -1", f"    jz {stub_label}_state_store", "    cmp eax, esi", f"    jz {stub_label}_state_store", "    test eax, eax", f"    jnz {stub_label}_state_next", f"{stub_label}_state_store:", "    mov DWORD PTR [ecx], esi", f"{stub_label}_state_next:", "    add ecx, 20h", "    inc edx", f"    cmp ecx, OFFSET {labels_for_state[0x10029240]}", f"    jl {stub_label}_state_loop", "    pop edi", "    xor eax, eax", "    pop esi", "    ret", f"{stub_label} ENDP", "",
            ])
            continue
        lines.extend(
            [
                f"PUBLIC {stub_label}",
                f"{stub_label} PROC",
                "    push 10",
                "    call DWORD PTR [__imp__IsProcessorFeaturePresent@4]",
                f"    mov DWORD PTR [IVF_RELOC_TARGET_{global_address:08X}], eax",
                "    xor eax, eax",
                "    ret",
                f"{stub_label} ENDP",
                "",
            ]
        )
    for pe_name, segment in ((".rdata", ".const"), (".data", ".data")):
        data = contents[pe_name]
        section_labels = labels[segment]
        sites = reloc_sites[pe_name]
        code_sites = candidate_code_sites[pe_name]
        events = sorted(set(section_labels) | set(sites) | set(code_sites))
        cursor = 0
        lines.append(segment)
        for offset in events:
            if offset < cursor or offset >= len(data):
                raise ValueError(f"event outside {pe_name}: {offset:#x}")
            emit_data(lines, bytes(data[cursor:offset]))
            for label in sorted(section_labels.get(offset, set())):
                if label.startswith("IVF_RELOC_TARGET_"):
                    if label in public_hook_shim_labels:
                        lines.append(f"PUBLIC {label}")
                        lines.append(f"PUBLIC _{label}")
                        lines.append(f"_{label} LABEL BYTE")
                    lines.append(f"{label} LABEL BYTE")
                else:
                    lines.append(f"    PUBLIC {label}")
                    lines.append(f"{label} LABEL BYTE")
            relocation = sites.get(offset)
            code_symbol = code_sites.get(offset)
            if relocation is not None:
                lines.append(f"    DD OFFSET {relocation['label']}")
                cursor = offset + 4
            elif code_symbol is not None:
                lines.append(f"    DD OFFSET {code_symbol}")
                cursor = offset + 4
            else:
                cursor = offset
        emit_data(lines, bytes(data[cursor:]))
        lines.append("")
    lines.append("END")

    args.asm.parent.mkdir(parents=True, exist_ok=True)
    args.manifest.parent.mkdir(parents=True, exist_ok=True)
    with args.asm.open("x", encoding="ascii", newline="\n") as stream:
        stream.write("\n".join(lines) + "\n")
    matrix = {
        f"{site} -> {target}": count
        for (site, target), count in sorted(target_counts.items())
    }
    manifest = {
        "scope": "original .rdata/.data bytes, data-to-data fixups, exact candidate-function fixups, 22 CRT initializer thunks, CRT fallback helper, 18 byte-template local code stubs for 21 pointer targets, context shim and CRT cleanup callback, and four _initterm_e stubs; not a loadable image",
        "image": str(args.image.resolve()),
        "image_sha256": hashlib.sha256(image).hexdigest(),
        "unresolved_dat_names_defined": len(unresolved_names),
        "relocation_sites_by_site_and_target_section": matrix,
        "data_to_data_sites_emitted_as_offset_relocations": sum(len(x) for x in reloc_sites.values()),
        "code_target_sites_emitted_as_offset_relocations": sum(len(x) for x in candidate_code_sites.values()),
        "unique_candidate_function_external_symbols": len(candidate_code_symbols),
        "crt_initializer_registration_thunks_reconstructed": len(startup_thunks),
        "crt_fallback_helper_stubs_reconstructed": len(helper_stubs),
        "crt_cleanup_stubs_reconstructed": len(cleanup_stubs),
        "context_shims_reconstructed": len(entry_stubs),
        "simple_local_code_stubs_reconstructed": len({simple_code_targets[x] for x in simple_code_targets}),
        "initterm_e_stubs_reconstructed": len(initterm_stubs),
        "initterm_e_processor_feature_stubs_reconstructed": sum(1 for address in initterm_stubs if address in (0x1001704C, 0x1001C5E0)),
        "initterm_e_allocation_stub_reconstructed": 0x100104BC in initterm_stubs,
        "initterm_e_state_table_stub_reconstructed": 0x10013025 in initterm_stubs,
        "text_target_sites_left_unresolved": len(unresolved_code_sites),
        "text_target_sites": unresolved_code_sites,
        "unique_synthetic_data_target_labels": len(target_labels),
        "public_hook_shim_data_aliases": len(public_hook_shim_labels),
        "public_exact_symbol_aliases": len(public_symbol_aliases),
        "assembly_sha256": hashlib.sha256(args.asm.read_bytes()).hexdigest(),
        "limitations": [
            "noncandidate text-target pointers stay at preferred-base values",
            "the original .text contains a Ghidra-verified state-table stub, but reconstructed code/data remain diagnostic and are not loader-integrated",
            "the original .text has 3160 additional HIGHLOW relocations not represented here",
            "section RVAs, function layout, hook shim fixups, CRT tables, and PE image layout are not reconstructed",
        ],
    }
    with args.manifest.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(manifest, stream, indent=2)
        stream.write("\n")
    print(f"missing DAT names defined: {len(unresolved_names)}")
    print(f"data-to-data relocation sites emitted: {manifest['data_to_data_sites_emitted_as_offset_relocations']}")
    print(f".text-target relocations retained unresolved: {len(unresolved_code_sites)}")
    print(f"MASM: {args.asm.resolve()}")
    print(f"manifest: {args.manifest.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
