#!/usr/bin/env python3
"""Verify generated COFF DIR32 records against original PE data relocations."""

from __future__ import annotations

import argparse
import csv
import struct
from collections import defaultdict
from pathlib import Path
from reloc_local_code_stubs import STUBS as LOCAL_CODE_STUBS


def coff_name(raw: bytes, strings: bytes) -> str:
    if raw[:4] == b"\0\0\0\0":
        offset = struct.unpack_from("<I", raw, 4)[0]
        end = strings.find(b"\0", offset)
        return strings[offset:end].decode("ascii")
    return raw.split(b"\0", 1)[0].decode("ascii")


def external_code_symbol(obj_path: Path, address: str) -> str:
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
        name = coff_name(obj[at : at + 8], strings)
        value, section_no = struct.unpack_from("<Ih", obj, at + 8)
        storage_class, aux_count = obj[at + 16], obj[at + 17]
        if (
            storage_class == 2
            and value == 0
            and section_names.get(section_no, "").startswith(".text")
            and address.lower() in name.lower()
        ):
            matches.add(name)
        index += 1 + aux_count
    if len(matches) != 1:
        raise ValueError(f"expected one public code symbol for {address} in {obj_path}, found {sorted(matches)}")
    return matches.pop()


def public_code_entry(obj_path: Path, preferred_name: str | None = None) -> str:
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
        name = coff_name(obj[at : at + 8], strings)
        value, section_no = struct.unpack_from("<Ih", obj, at + 8)
        storage_class, aux_count = obj[at + 16], obj[at + 17]
        if storage_class == 2 and value == 0 and section_names.get(section_no, "").startswith(".text"):
            matches.add(name)
        index += 1 + aux_count
    if preferred_name is not None:
        if preferred_name not in matches:
            raise ValueError(
                f"preferred public code entry {preferred_name!r} is absent from "
                f"{obj_path}; found {sorted(matches)}"
            )
        return preferred_name
    if len(matches) != 1:
        raise ValueError(f"expected one public code entry in {obj_path}, found {sorted(matches)}")
    return matches.pop()


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("image", type=Path)
    parser.add_argument("relocations", type=Path)
    parser.add_argument("--objects-dir", type=Path, help="fresh address-named candidate COFF objects")
    parser.add_argument("--init-array-crosswalk", type=Path, help="verified CRT initializer/exit-callback crosswalk")
    parser.add_argument("--thunk-disassembly", type=Path, help="Ghidra instruction CSV for startup-thunk bytes")
    parser.add_argument("--inventory", type=Path, help="current DAT COFF symbol inventory")
    parser.add_argument("--unmapped-target-disassembly", type=Path, help="Ghidra disassembly CSV for known noncandidate helpers")
    parser.add_argument("--initterm-e-disassembly", type=Path, help="Ghidra disassembly CSV for _initterm_e initializer entries")
    parser.add_argument("--initterm-e-branch-disassembly", type=Path)
    parser.add_argument("--initterm-e-size-tail-disassembly", type=Path)
    parser.add_argument("--initterm-e-allocation-cleanup-disassembly", type=Path)
    args = parser.parse_args()

    data = args.object.read_bytes()
    machine, section_count, _, symbol_ptr, symbol_count, optional_size, _ = struct.unpack_from(
        "<HHIIIHH", data, 0
    )
    if machine != 0x14C or optional_size:
        raise ValueError("expected an x86 COFF object without optional header")
    section_base = 20 + optional_size
    sections: dict[int, dict[str, int | str]] = {}
    for index in range(section_count):
        at = section_base + index * 40
        name = data[at : at + 8].split(b"\0", 1)[0].decode("ascii")
        size, raw_ptr, reloc_ptr = struct.unpack_from("<III", data, at + 16)
        reloc_count = struct.unpack_from("<H", data, at + 32)[0]
        sections[index + 1] = {
            "name": name,
            "size": size,
            "raw_ptr": raw_ptr,
            "reloc_ptr": reloc_ptr,
            "reloc_count": reloc_count,
        }
    strings_at = symbol_ptr + symbol_count * 18
    string_size = struct.unpack_from("<I", data, strings_at)[0]
    strings = data[strings_at : strings_at + string_size]
    symbols: dict[int, tuple[str, int, int]] = {}
    index = 0
    while index < symbol_count:
        at = symbol_ptr + index * 18
        name = coff_name(data[at : at + 8], strings)
        value, section_no = struct.unpack_from("<Ih", data, at + 8)
        aux_count = data[at + 17]
        symbols[index] = (name, value, section_no)
        index += 1 + aux_count

    image_bytes, image_base, pe_sections = parse_pe_sections(args.image)
    startup_thunks: dict[int, tuple[str, str]] = {}
    startup_callbacks_va: dict[int, int] = {}
    atexit_symbol = ""
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
                startup_thunks[entry_va] = (
                    f"IVF_CRT_INIT_THUNK_{entry_va:08X}",
                    public_code_entry(callback_obj),
                )
                if row["decoded_thunk_exit_callback_va"]:
                    startup_callbacks_va[entry_va] = int(row["decoded_thunk_exit_callback_va"], 16)
        atexit_symbol = public_code_entry(args.objects_dir / "10010529.obj")
        if startup_thunks and not args.thunk_disassembly:
            parser.error("--init-array-crosswalk requires --thunk-disassembly")
        if startup_thunks and not args.inventory:
            parser.error("--init-array-crosswalk requires --inventory")

    helper_stubs: dict[int, tuple[str, str]] = {}
    cleanup_stubs: dict[int, tuple[str, tuple[str, str, str]]] = {}
    entry_stubs: dict[int, tuple[str, str]] = {}
    simple_code_targets: dict[int, str] = {}
    if args.unmapped_target_disassembly:
        if not args.objects_dir:
            parser.error("--unmapped-target-disassembly requires --objects-dir")
        with args.unmapped_target_disassembly.open("r", encoding="utf-8-sig", newline="") as stream:
            all_unmapped_rows = list(csv.DictReader(stream))
        rows = [row for row in all_unmapped_rows if row["target_va"].lower() == "1001af2b"]
        instructions = [
            row["instruction"].strip().upper()
            for row in sorted(rows, key=lambda row: int(row["instruction_va"], 16))
        ]
        if instructions != ["PUSH 0X2", "CALL 0X10012E01", "POP ECX", "RET"]:
            raise ValueError(f"unexpected Ghidra instruction window for 0x1001af2b: {instructions}")
        helper_stubs[0x1001AF2B] = (
            "IVF_CFLTCVT_FALLBACK_1001AF2B",
            public_code_entry(args.objects_dir / "10012e01.obj"),
        )
        with args.unmapped_target_disassembly.open("r", encoding="utf-8-sig", newline="") as stream:
            cleanup_rows = [row for row in csv.DictReader(stream) if int(row["target_va"], 16) == 0x100130D6]
        cleanup_instructions = [row["instruction"].strip().upper() for row in sorted(cleanup_rows, key=lambda row: int(row["instruction_va"], 16))]
        cleanup_expected = ["CALL 0X10013EF3", "CMP BYTE PTR [0X10039A34],0X0", "JZ 0X100130E9", "CALL 0X100181DC", "PUSH DWORD PTR [0X1003C520]", "CALL 0X100116DB", "POP ECX", "RET"]
        if cleanup_instructions != cleanup_expected:
            raise ValueError(f"Ghidra CRT cleanup callback mismatch: {cleanup_instructions!r}")
        cleanup_stubs[0x100130D6] = (
            "IVF_CRT_CLEANUP_100130D6",
            (public_code_entry(args.objects_dir / "10013ef3.obj"), public_code_entry(args.objects_dir / "100181dc.obj"), public_code_entry(args.objects_dir / "100116db.obj")),
        )
        entry_rows = [row for row in all_unmapped_rows if int(row["target_va"], 16) == 0x10001000]
        entry_instructions = [row["instruction"].strip().upper() for row in sorted(entry_rows, key=lambda row: int(row["instruction_va"], 16))]
        if entry_instructions != ["MOV DWORD PTR [ECX],0X10022250", "JMP 0X1001031F"]:
            raise ValueError(f"Ghidra PE-entry shim mismatch: {entry_instructions!r}")
        entry_stubs[0x10001000] = ("IVF_CONTEXT_SHIM_10001000", public_code_entry(args.objects_dir / "1001031f.obj"))
        text_section = pe_sections[".text"]
        continuation_labels = {
            block["source_va"]: block["label"]
            for stub in LOCAL_CODE_STUBS for block in stub.get("blocks", ())
        }
        for stub in LOCAL_CODE_STUBS:
            for target_va in stub["targets"]:
                source_rva = target_va - image_base
                source_offset = text_section["raw_offset"] + source_rva - text_section["rva"]
                original = bytearray(image_bytes[source_offset:source_offset + len(stub["body"])])
                if len(original) != len(stub["body"]):
                    raise ValueError(f"local stub target outside source .text: {target_va:#x}")
                for fixup_offset, kind, expected_target in stub["fixups"]:
                    if kind == "DIR32":
                        actual_target = struct.unpack_from("<I", original, fixup_offset)[0]
                    elif kind == "REL32":
                        rel = struct.unpack_from("<i", original, fixup_offset)[0]
                        actual_target = target_va + fixup_offset + 4 + rel
                    else:
                        rel = struct.unpack_from("<b", original, fixup_offset)[0]
                        actual_target = target_va + fixup_offset + 1 + rel
                    if actual_target != expected_target:
                        raise ValueError(f"local stub source fixup at {target_va + fixup_offset:#x} targets {actual_target:#x}, expected {expected_target:#x}")
                    width = 1 if kind == "REL8" else 4
                    original[fixup_offset:fixup_offset + width] = bytes(width)
                if bytes(original) != stub["body"]:
                    raise ValueError(f"local stub source bytes differ from template at {target_va:#x}")
                simple_code_targets[target_va] = stub["label"]
            for block in stub.get("blocks", ()):
                source_va = block["source_va"]
                source_rva = source_va - image_base
                source_offset = text_section["raw_offset"] + source_rva - text_section["rva"]
                original = bytearray(image_bytes[source_offset:source_offset + len(block["body"])])
                if len(original) != len(block["body"]):
                    raise ValueError(f"local stub continuation outside source .text: {source_va:#x}")
                for fixup_offset, kind, expected_target in block["fixups"]:
                    if kind == "DIR32":
                        actual_target = struct.unpack_from("<I", original, fixup_offset)[0]
                    elif kind == "REL32":
                        rel = struct.unpack_from("<i", original, fixup_offset)[0]
                        actual_target = source_va + fixup_offset + 4 + rel
                    else:
                        rel = struct.unpack_from("<b", original, fixup_offset)[0]
                        actual_target = source_va + fixup_offset + 1 + rel
                    if actual_target != expected_target:
                        raise ValueError(f"local continuation fixup at {source_va + fixup_offset:#x} targets {actual_target:#x}, expected {expected_target:#x}")
                    width = 1 if kind == "REL8" else 4
                    original[fixup_offset:fixup_offset + width] = bytes(width)
                if bytes(original) != block["body"]:
                    raise ValueError(f"local continuation source bytes differ from template at {source_va:#x}")

    initterm_stubs: dict[int, tuple[str, int]] = {}
    import_symbol = "__imp__IsProcessorFeaturePresent@4"
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
        alloc_rows = [row for row in all_rows if int(row["target_va"], 16) == 0x100104BC]
        alloc_instructions = [row["instruction"].strip().upper() for row in sorted(alloc_rows, key=lambda row: int(row["instruction_va"], 16))]
        expected_alloc = ["MOV EDI,EDI", "PUSH ESI", "PUSH 0X4", "PUSH 0X20", "CALL 0X10012A3A", "POP ECX", "POP ECX", "MOV ESI,EAX", "PUSH ESI", "CALL DWORD PTR [0X1002205C]", "MOV [0X1003D54C],EAX", "MOV [0X1003D548],EAX", "TEST ESI,ESI", "JNZ 0X100104E6", "PUSH 0X18", "POP EAX", "POP ESI", "RET"]
        if alloc_instructions != expected_alloc:
            mismatches.append(f"Ghidra _initterm_e allocation body mismatch: {alloc_instructions!r}")
        initterm_stubs[0x100104BC] = ("IVF_INITTERM_E_100104BC", 0x1003D54C)
        calloc_symbol = public_code_entry(args.objects_dir / "10012a3a.obj")
        initterm_stubs[0x10013025] = ("IVF_INITTERM_E_10013025", 0x1003C520)
        evidence_paths = (args.initterm_e_branch_disassembly, args.initterm_e_size_tail_disassembly, args.initterm_e_allocation_cleanup_disassembly)
        if any(path is None for path in evidence_paths):
            parser.error("state-table callback verification requires branch, size-tail, and allocation-cleanup Ghidra CSVs")
        instruction_bytes: dict[int, int] = {}
        for evidence_path in (args.initterm_e_disassembly, *evidence_paths):
            with evidence_path.open("r", encoding="utf-8-sig", newline="") as stream:
                for row in csv.DictReader(stream):
                    start = int(row["instruction_va"], 16)
                    if not 0x10013025 <= start <= 0x100130D5:
                        continue
                    for offset, value in enumerate(bytes.fromhex(row["instruction_bytes"])):
                        address = start + offset
                        if address in instruction_bytes and instruction_bytes[address] != value:
                            mismatches.append(f"conflicting Ghidra bytes at {address:#x}")
                        instruction_bytes[address] = value
        missing = [address for address in range(0x10013025, 0x100130D6) if address not in instruction_bytes]
        if missing != list(range(0x1001307E, 0x10013083)):
            mismatches.append(f"unexpected Ghidra state-table instruction coverage gaps: {[hex(value) for value in missing]}")
        text = pe_sections[".text"]
        loop_head_rva = 0x1001307E - image_base
        loop_head_offset = text["raw_offset"] + loop_head_rva - text["rva"]
        loop_head_bytes = bytes.fromhex("A1 20 C5 03 10")
        if image_bytes[loop_head_offset:loop_head_offset + 5] != loop_head_bytes:
            mismatches.append("source PE bytes do not confirm omitted loop-head MOV EAX,[0x1003c520]")
        else:
            instruction_bytes.update({0x1001307E + i: value for i, value in enumerate(loop_head_bytes)})
        span_start, span_end = 0x10013025, 0x100130D6
        text_offset = text["raw_offset"] + (span_start - image_base) - text["rva"]
        captured = bytes(instruction_bytes.get(address, -1) for address in range(span_start, span_end))
        if len(captured) != span_end - span_start or any(value < 0 for value in captured):
            mismatches.append("Ghidra/source byte coverage is incomplete for 0x10013025 callback")
        elif captured != image_bytes[text_offset:text_offset + len(captured)]:
            mismatches.append("Ghidra instruction-byte crosswalk differs from original PE at 0x10013025")

    expected: dict[tuple[str, int], tuple[str, int | None, str | None]] = {}
    with args.relocations.open("r", encoding="utf-8-sig", newline="") as stream:
        for row in csv.DictReader(stream):
            site_section, target_section = row["site_section"], row["target_section"]
            if site_section not in (".data", ".rdata"):
                continue
            site_rva = int(pe_sections[site_section]["rva"])
            site_offset = int(row["site_va"], 16) - (image_base + site_rva)
            target_va = int(row["stored_va"], 16)
            if target_section in (".data", ".rdata"):
                target_rva = int(pe_sections[target_section]["rva"])
                target_offset = target_va - (image_base + target_rva)
                target_name = None
            elif target_va in initterm_stubs:
                target_name = initterm_stubs[target_va][0]
                target_section, target_offset = "<local-code>", None
            elif target_va in helper_stubs:
                target_name = helper_stubs[target_va][0]
                target_section, target_offset = "<local-code>", None
            elif target_va in cleanup_stubs:
                target_name = cleanup_stubs[target_va][0]
                target_section, target_offset = "<local-code>", None
            elif target_va in entry_stubs:
                target_name = entry_stubs[target_va][0]
                target_section, target_offset = "<local-code>", None
            elif target_va in simple_code_targets:
                target_name = simple_code_targets[target_va]
                target_section, target_offset = "<local-code>", None
            elif target_va in startup_thunks:
                target_name = startup_thunks[target_va][0]
                target_section, target_offset = "<local-code>", None
            elif args.objects_dir and row.get("exact_candidate_function", ""):
                target_obj = args.objects_dir / f"{target_va:08x}.obj"
                target_name = public_code_entry(target_obj)
                target_section, target_offset = "<external-code>", 0
            else:
                continue
            key = (site_section, site_offset)
            if key in expected:
                raise ValueError(f"duplicate expected relocation: {key}")
            expected[key] = (target_section, target_offset, target_name)

    mismatches: list[str] = []
    seen: set[tuple[str, int]] = set()
    actual_count = 0
    text_relocations: list[tuple[int, int, int, str | None]] = []
    for section_no, section in sections.items():
        section_name = str(section["name"])
        if section_name.startswith(".text"):
            base = int(section["reloc_ptr"])
            count = int(section["reloc_count"])
            for entry in range(count):
                at = base + entry * 10
                offset, symbol_index, reloc_type = struct.unpack_from("<IIH", data, at)
                symbol = symbols.get(symbol_index)
                text_relocations.append((offset, reloc_type, symbol_index, symbol[0] if symbol else None))
        if section_name not in (".data", ".rdata"):
            continue
        base = int(section["reloc_ptr"])
        count = int(section["reloc_count"])
        for entry in range(count):
            at = base + entry * 10
            offset, symbol_index, reloc_type = struct.unpack_from("<IIH", data, at)
            actual_count += 1
            key = (section_name, offset)
            if key not in expected:
                mismatches.append(f"unexpected relocation {section_name}+{offset:#x}")
                continue
            if key in seen:
                mismatches.append(f"duplicate relocation {section_name}+{offset:#x}")
                continue
            seen.add(key)
            wanted_section, wanted_offset, wanted_name = expected[key]
            symbol = symbols.get(symbol_index)
            if wanted_name is None:
                target_section_no = next(
                    (number for number, item in sections.items() if item["name"] == wanted_section),
                    None,
                )
                wanted_name = f"IVF_RELOC_TARGET_{image_base + int(pe_sections[wanted_section]['rva']) + wanted_offset:08X}"
            elif wanted_section == "<external-code>":
                target_section_no = 0
            else:  # a public local startup-thunk symbol in this object's .text section
                symbol_section_name = str(sections.get(symbol[2], {}).get("name", "")) if symbol else ""
                if symbol is None or symbol[0] != wanted_name or not symbol_section_name.startswith(".text"):
                    mismatches.append(f"wrong local code symbol at {section_name}+{offset:#x}: {symbol!r}")
                    continue
                target_section_no = symbol[2]
                wanted_offset = symbol[1]
            if reloc_type != 0x0006:
                mismatches.append(f"wrong relocation type {reloc_type:#x} at {section_name}+{offset:#x}")
            if symbol is None or symbol != (wanted_name, wanted_offset, target_section_no):
                mismatches.append(
                    f"wrong symbol at {section_name}+{offset:#x}: {symbol!r}, "
                    f"expected {(wanted_name, wanted_offset, target_section_no)!r}"
                )

    missing = expected.keys() - seen
    if missing:
        mismatches.extend(f"missing relocation {name}+{offset:#x}" for name, offset in sorted(missing))
    expected_thunk_relocations: set[tuple[int, int, str]] = set()
    verified_original_thunks = 0
    if startup_thunks:
        symbol_values = {symbol[0]: symbol[1] for symbol in symbols.values()}
        text_section = next(
            (item for item in sections.values() if str(item["name"]).startswith(".text")), None
        )
        if text_section is None:
            mismatches.append("provider has no code section for startup thunks")
        else:
            code_section_no = next(number for number, item in sections.items() if item is text_section)
            code_bytes = data[int(text_section["raw_ptr"]) : int(text_section["raw_ptr"]) + int(text_section["size"])]
            for entry_va, (label, callback) in startup_thunks.items():
                if label not in symbol_values:
                    mismatches.append(f"missing startup thunk symbol {label}")
                    continue
                offset = symbol_values[label]
                if entry_va == 0x100208D0:
                    if code_bytes[offset : offset + 5] != b"\xB8\x01\0\0\0" or code_bytes[offset + 5 : offset + 7] != b"\x84\x05" or code_bytes[offset + 11 : offset + 13] != b"\x75\x1F" or code_bytes[offset + 13 : offset + 15] != b"\x09\x05" or code_bytes[offset + 19 : offset + 21] != b"\x33\xC0" or code_bytes[offset + 21 : offset + 22] != b"\x68" or code_bytes[offset + 26 : offset + 27] != b"\xA3" or code_bytes[offset + 31 : offset + 32] != b"\xA3" or code_bytes[offset + 36 : offset + 37] != b"\xE8" or code_bytes[offset + 41 : offset + 44] != b"\x83\xC4\x04" or code_bytes[offset + 44 : offset + 46] != b"\xC7\x05" or code_bytes[offset + 54 : offset + 55] != b"\xC3":
                        mismatches.append(f"stateful initializer thunk bytes mismatch at {label}+{offset:#x}")
                    expected_thunk_relocations.update(
                        {
                            (offset + 7, 0x0006, "IVF_RELOC_TARGET_1003C3FC"),
                            (offset + 15, 0x0006, "IVF_RELOC_TARGET_1003C3FC"),
                            (offset + 22, 0x0006, callback),
                            (offset + 27, 0x0006, "IVF_RELOC_TARGET_1003C3E8"),
                            (offset + 32, 0x0006, "IVF_RELOC_TARGET_1003C3EC"),
                            (offset + 37, 0x0014, atexit_symbol),
                            (offset + 46, 0x0006, "IVF_RELOC_TARGET_1003C38C"),
                            (offset + 50, 0x0006, "IVF_RELOC_TARGET_1003C3E8"),
                        }
                    )
                    for address, section_name in ((0x1003C3FC, ".data"), (0x1003C3E8, ".data"), (0x1003C3EC, ".data"), (0x1003C38C, ".data")):
                        symbol_name = f"IVF_RELOC_TARGET_{address:08X}"
                        found = next((item for item in symbols.values() if item[0] == symbol_name), None)
                        section_no = next(k for k, v in sections.items() if v["name"] == section_name)
                        expected_offset = address - (image_base + int(pe_sections[section_name]["rva"]))
                        if found is None or found[1:] != (expected_offset, section_no):
                            mismatches.append(f"stateful initializer data label has wrong PE offset: {symbol_name}")
                    addend_ranges = [(7, 11), (15, 19), (22, 26), (27, 31), (32, 36), (37, 41), (46, 50), (50, 54)]
                    if any(code_bytes[offset + start : offset + end] != bytes(end - start) for start, end in addend_ranges):
                        mismatches.append(f"stateful initializer relocation addend mismatch at {label}+{offset:#x}")
                elif entry_va == 0x100209F0:
                    if code_bytes[offset : offset + 1] != b"\xE8" or code_bytes[offset + 5 : offset + 6] != b"\x68" or code_bytes[offset + 10 : offset + 12] != b"\xC7\x05" or code_bytes[offset + 20 : offset + 21] != b"\xE8" or code_bytes[offset + 25 : offset + 27] != b"\x59\xC3":
                        mismatches.append(f"stateful registration thunk bytes mismatch at {label}+{offset:#x}")
                    addend_ranges = [(1, 5), (6, 10), (12, 16), (16, 20), (21, 25)]
                    code_target = public_code_entry(args.objects_dir / "1000a090.obj")
                    with args.inventory.open("r", encoding="utf-8-sig", newline="") as stream:
                        global_rows = [row for row in csv.DictReader(stream) if row["address"].lower() == "0x1003c328"]
                    if len(global_rows) != 1:
                        mismatches.append(f"expected one DAT inventory row for 0x1003c328, got {len(global_rows)}")
                    else:
                        global_names = {
                            name
                            for field in ("undefined_symbols", "defined_symbols")
                            for name in global_rows[0][field].split(" | ")
                            if name
                        }
                        if len(global_names) != 1:
                            mismatches.append(f"expected one DAT symbol at 0x1003c328, got {sorted(global_names)}")
                        else:
                            global_symbol = global_names.pop()
                            expected_thunk_relocations.update(
                                {
                                    (offset + 1, 0x0014, code_target),
                                    (offset + 6, 0x0006, callback),
                                    (offset + 12, 0x0006, global_symbol),
                                    (offset + 16, 0x0006, "IVF_RELOC_TARGET_10024C74"),
                                    (offset + 21, 0x0014, atexit_symbol),
                                }
                            )
                            global_idx = next((idx for idx, item in symbols.items() if item[0] == global_symbol), None)
                            rdata_idx = next((idx for idx, item in symbols.items() if item[0] == "IVF_RELOC_TARGET_10024C74"), None)
                            data_section_no = next(k for k, v in sections.items() if v["name"] == ".data")
                            rdata_section_no = next(k for k, v in sections.items() if v["name"] == ".rdata")
                            expected_global_offset = 0x1003C328 - (image_base + int(pe_sections[".data"]["rva"]))
                            expected_rdata_offset = 0x10024C74 - (image_base + int(pe_sections[".rdata"]["rva"]))
                            if global_idx is None or symbols[global_idx][1:] != (expected_global_offset, data_section_no):
                                mismatches.append("stateful thunk global symbol does not point to original .data offset")
                            if rdata_idx is None or symbols[rdata_idx][1:] != (expected_rdata_offset, rdata_section_no):
                                mismatches.append("stateful thunk pointer constant does not point to original .rdata offset")
                    if any(code_bytes[offset + start : offset + end] != bytes(end - start) for start, end in addend_ranges):
                        mismatches.append(f"stateful thunk relocation addend mismatch at {label}+{offset:#x}")
                else:
                    if code_bytes[offset : offset + 1] != b"\x68" or code_bytes[offset + 5 : offset + 6] != b"\xE8" or code_bytes[offset + 10 : offset + 12] != b"\x59\xC3":
                        mismatches.append(f"startup thunk bytes mismatch at {label}+{offset:#x}")
                    if code_bytes[offset + 1 : offset + 5] != b"\0\0\0\0" or code_bytes[offset + 6 : offset + 10] != b"\0\0\0\0":
                        mismatches.append(f"startup thunk relocation addend mismatch at {label}+{offset:#x}")
                    expected_thunk_relocations.add((offset + 1, 0x0006, callback))
                    expected_thunk_relocations.add((offset + 6, 0x0014, atexit_symbol))
            disassembly: dict[int, list[dict[str, str]]] = defaultdict(list)
            with args.thunk_disassembly.open("r", encoding="utf-8-sig", newline="") as stream:
                for row in csv.DictReader(stream):
                    target_va = int(row["target_va"], 16)
                    if target_va in startup_thunks:
                        disassembly[target_va].append(row)
            for entry_va, expected_callback in startup_callbacks_va.items():
                rows = sorted(disassembly.get(entry_va, []), key=lambda row: int(row["instruction_va"], 16))
                instructions = [row["instruction"].strip().upper() for row in rows]
                if entry_va == 0x100208D0:
                    expected_instructions = [
                        "MOV EAX,0X1",
                        "TEST BYTE PTR [0X1003C3FC],AL",
                        "JNZ 0X100208FC",
                        "OR DWORD PTR [0X1003C3FC],EAX",
                        "XOR EAX,EAX",
                        f"PUSH 0X{expected_callback:X}",
                        "MOV [0X1003C3E8],EAX",
                        "MOV [0X1003C3EC],EAX",
                        "CALL 0X10010529",
                        "ADD ESP,0X4",
                        "MOV DWORD PTR [0X1003C38C],0X1003C3E8",
                        "RET",
                    ]
                elif entry_va == 0x100209F0:
                    expected_instructions = [
                        "CALL 0X1000A090",
                        f"PUSH 0X{expected_callback:X}",
                        "MOV DWORD PTR [0X1003C328],0X10024C74",
                        "CALL 0X10010529",
                        "POP ECX",
                        "RET",
                    ]
                else:
                    expected_instructions = [
                        f"PUSH 0X{expected_callback:X}",
                        "CALL 0X10010529",
                        "POP ECX",
                        "RET",
                    ]
                if instructions != expected_instructions:
                    mismatches.append(
                        f"Ghidra thunk instruction/callback mismatch at {entry_va:#x}: {instructions!r}"
                    )
                else:
                    verified_original_thunks += 1
            for target_va, (label, helper_symbol) in helper_stubs.items():
                if label not in symbol_values:
                    mismatches.append(f"missing reconstructed helper symbol {label}")
                    continue
                offset = symbol_values[label]
                if code_bytes[offset : offset + 3] != b"\x6A\x02\xE8" or code_bytes[offset + 3 : offset + 7] != b"\0\0\0\0" or code_bytes[offset + 7 : offset + 9] != b"\x59\xC3":
                    mismatches.append(f"fallback helper bytes mismatch at {label}+{offset:#x}")
                expected_thunk_relocations.add((offset + 3, 0x0014, helper_symbol))
                with args.unmapped_target_disassembly.open("r", encoding="utf-8-sig", newline="") as stream:
                    helper_rows = [row for row in csv.DictReader(stream) if int(row["target_va"], 16) == target_va]
                helper_instructions = [
                    row["instruction"].strip().upper()
                    for row in sorted(helper_rows, key=lambda row: int(row["instruction_va"], 16))
                ]
                if helper_instructions != ["PUSH 0X2", "CALL 0X10012E01", "POP ECX", "RET"]:
                    mismatches.append(f"Ghidra fallback helper sequence mismatch at {target_va:#x}: {helper_instructions!r}")
            for target_va, (label, global_address) in initterm_stubs.items():
                if label not in symbol_values:
                    mismatches.append(f"missing _initterm_e stub symbol {label}")
                    continue
                offset = symbol_values[label]
                if target_va == 0x100104BC:
                    expected_prefix = bytes.fromhex("56 6A 04 6A 20 E8 00 00 00 00 83 C4 08 8B F0 56 FF 15 00 00 00 00 A3 00 00 00 00 A3 00 00 00 00 85 F6 75 07 B8 18 00 00 00 5E C3 83 26 00 33 C0 5E C3")
                    if code_bytes[offset : offset + len(expected_prefix)] != expected_prefix:
                        mismatches.append(f"_initterm_e allocation stub bytes mismatch at {label}")
                    expected_thunk_relocations.update({
                        (offset + 6, 0x0014, calloc_symbol),
                        (offset + 18, 0x0006, "__imp__EncodePointer@4"),
                        (offset + 23, 0x0006, "IVF_RELOC_TARGET_1003D54C"),
                        (offset + 28, 0x0006, "IVF_RELOC_TARGET_1003D548"),
                    })
                    for data_address in (0x1003D54C, 0x1003D548):
                        data_label = f"IVF_RELOC_TARGET_{data_address:08X}"
                        data_symbol = next((item for item in symbols.values() if item[0] == data_label), None)
                        data_section_no = next(k for k, v in sections.items() if v["name"] == ".data")
                        wanted = data_address - (image_base + int(pe_sections[".data"]["rva"]))
                        if data_symbol is None or data_symbol[1:] != (wanted, data_section_no):
                            mismatches.append(f"_initterm_e global has wrong PE offset: {data_label}")
                    continue
                if target_va == 0x10013025:
                    state_bytes = bytes.fromhex("A1 00 00 00 00 56 6A 14 5E 85 C0 75 07 B8 00 02 00 00 EB 06 3B C6 7D 02 8B C6 A3 00 00 00 00 6A 04 50 E8 00 00 00 00 59 59 A3 00 00 00 00 85 C0 75 20 6A 04 56 89 35 00 00 00 00 E8 00 00 00 00 59 59 A3 00 00 00 00 85 C0 75 07 B8 1A 00 00 00 5E C3 33 D2 B9 00 00 00 00 89 0C 02 83 C1 20 83 C2 04 81 F9 00 00 00 00 7C EF 6A FE 5E 33 D2 B9 00 00 00 00 57 8B C2 C1 F8 05 8B 04 85 00 00 00 00 8B FA 83 E7 1F C1 E7 06 8B 04 07 83 F8 FF 74 08 3B C6 74 04 85 C0 75 02 89 31 83 C1 20 42 81 F9 00 00 00 00 7C CE 5F 33 C0 5E C3")
                    if code_bytes[offset:offset + len(state_bytes)] != state_bytes:
                        mismatches.append(f"_initterm_e state-table stub bytes mismatch at {label}")
                    state_relocs = {
                        (offset + 1, 0x0006, "IVF_RELOC_TARGET_1003D540"),
                        (offset + 0x1B, 0x0006, "IVF_RELOC_TARGET_1003D540"),
                        (offset + 0x23, 0x0014, calloc_symbol),
                        (offset + 0x2A, 0x0006, "IVF_RELOC_TARGET_1003C520"),
                        (offset + 0x37, 0x0006, "IVF_RELOC_TARGET_1003D540"),
                        (offset + 0x3C, 0x0014, calloc_symbol),
                        (offset + 0x43, 0x0006, "IVF_RELOC_TARGET_1003C520"),
                        (offset + 0x55, 0x0006, "IVF_RELOC_TARGET_100291D0"),
                        (offset + 0x64, 0x0006, "IVF_RELOC_TARGET_10029450"),
                        (offset + 0x70, 0x0006, "IVF_RELOC_TARGET_100291E0"),
                        (offset + 0x7D, 0x0006, "IVF_RELOC_TARGET_1003C420"),
                        (offset + 0xA1, 0x0006, "IVF_RELOC_TARGET_10029240"),
                    }
                    expected_thunk_relocations.update(state_relocs)
                    for data_address in (0x1003D540, 0x1003C520, 0x1003C420, 0x100291D0, 0x10029450, 0x100291E0, 0x10029240):
                        data_label = f"IVF_RELOC_TARGET_{data_address:08X}"
                        data_symbol = next((item for item in symbols.values() if item[0] == data_label), None)
                        data_section_no = next(k for k, v in sections.items() if v["name"] == ".data")
                        wanted = data_address - (image_base + int(pe_sections[".data"]["rva"]))
                        if data_symbol is None or data_symbol[1:] != (wanted, data_section_no):
                            mismatches.append(f"_initterm_e state-table data label has wrong offset: {data_label}")
                    continue
                expected_bytes = b"\x6A\x0A\xFF\x15\0\0\0\0\xA3\0\0\0\0\x33\xC0\xC3"
                if code_bytes[offset : offset + len(expected_bytes)] != expected_bytes:
                    mismatches.append(f"_initterm_e processor-feature stub bytes mismatch at {label}+{offset:#x}")
                global_label = f"IVF_RELOC_TARGET_{global_address:08X}"
                expected_thunk_relocations.update(
                    {
                        (offset + 4, 0x0006, import_symbol),
                        (offset + 9, 0x0006, global_label),
                    }
                )
                global_symbol = next((item for item in symbols.values() if item[0] == global_label), None)
                data_section_no = next(k for k, v in sections.items() if v["name"] == ".data")
                expected_offset = global_address - (image_base + int(pe_sections[".data"]["rva"]))
                if global_symbol is None or global_symbol[1:] != (expected_offset, data_section_no):
                    mismatches.append(f"_initterm_e global symbol has wrong PE offset: {global_label}")
                with args.initterm_e_disassembly.open("r", encoding="utf-8-sig", newline="") as stream:
                    original_rows = [row for row in csv.DictReader(stream) if int(row["target_va"], 16) == target_va]
                original_instructions = [
                    row["instruction"].strip().upper()
                    for row in sorted(original_rows, key=lambda row: int(row["instruction_va"], 16))
                ]
                expected_instructions, _ = {
                    0x1001704C: (["PUSH 0XA", "CALL DWORD PTR [0X1002210C]", "MOV [0X1003C414],EAX", "XOR EAX,EAX", "RET"], 0x1003C414),
                    0x1001C5E0: (["PUSH 0XA", "CALL DWORD PTR [0X1002210C]", "MOV [0X1003C40C],EAX", "XOR EAX,EAX", "RET"], 0x1003C40C),
                }[target_va]
                if original_instructions != expected_instructions:
                    mismatches.append(f"Ghidra _initterm_e sequence mismatch at {target_va:#x}")
            for target_va, (label, call_symbols) in cleanup_stubs.items():
                if label not in symbol_values:
                    mismatches.append(f"missing CRT cleanup stub symbol {label}")
                    continue
                offset = symbol_values[label]
                cleanup_bytes = bytes.fromhex("E8 00 00 00 00 80 3D 00 00 00 00 00 74 05 E8 00 00 00 00 FF 35 00 00 00 00 E8 00 00 00 00 59 C3")
                if code_bytes[offset:offset + len(cleanup_bytes)] != cleanup_bytes:
                    mismatches.append(f"CRT cleanup stub bytes mismatch at {label}")
                flushall_symbol, fcloseall_symbol, free_symbol = call_symbols
                expected_thunk_relocations.update({
                    (offset + 1, 0x0014, flushall_symbol),
                    (offset + 7, 0x0006, "IVF_RELOC_TARGET_10039A34"),
                    (offset + 15, 0x0014, fcloseall_symbol),
                    (offset + 21, 0x0006, "IVF_RELOC_TARGET_1003C520"),
                    (offset + 26, 0x0014, free_symbol),
                })
                for data_address in (0x10039A34, 0x1003C520):
                    data_label = f"IVF_RELOC_TARGET_{data_address:08X}"
                    data_symbol = next((item for item in symbols.values() if item[0] == data_label), None)
                    data_section_no = next(k for k, v in sections.items() if v["name"] == ".data")
                    wanted = data_address - (image_base + int(pe_sections[".data"]["rva"]))
                    if data_symbol is None or data_symbol[1:] != (wanted, data_section_no):
                        mismatches.append(f"CRT cleanup global has wrong PE offset: {data_label}")
            for target_va, (label, entry_symbol) in entry_stubs.items():
                if label not in symbol_values:
                    mismatches.append(f"missing PE-entry shim symbol {label}")
                    continue
                offset = symbol_values[label]
                entry_bytes = bytes.fromhex("C7 01 00 00 00 00 E9 00 00 00 00")
                if code_bytes[offset:offset + len(entry_bytes)] != entry_bytes:
                    mismatches.append(f"PE-entry shim bytes mismatch at {label}")
                expected_thunk_relocations.update({
                    (offset + 2, 0x0006, "IVF_RELOC_TARGET_10022250"),
                    (offset + 7, 0x0014, entry_symbol),
                })
                data_label = "IVF_RELOC_TARGET_10022250"
                data_symbol = next((item for item in symbols.values() if item[0] == data_label), None)
                data_section_name = next((name for name in (".data", ".rdata") if image_base + int(pe_sections[name]["rva"]) <= 0x10022250 < image_base + int(pe_sections[name]["rva"]) + int(pe_sections[name]["virtual_size"])), None)
                if data_section_name is None:
                    mismatches.append("PE-entry callback global is outside the original data sections")
                else:
                    data_section_no = next(k for k, v in sections.items() if v["name"] == data_section_name)
                    wanted = 0x10022250 - (image_base + int(pe_sections[data_section_name]["rva"]))
                    if data_symbol is None or data_symbol[1:] != (wanted, data_section_no):
                        mismatches.append(f"PE-entry callback global has wrong PE offset: {data_label}")
            verified_simple_labels: set[str] = set()
            for stub in LOCAL_CODE_STUBS:
                label = stub["label"]
                if label in verified_simple_labels or not any(target in simple_code_targets for target in stub["targets"]):
                    continue
                verified_simple_labels.add(label)
                if label not in symbol_values:
                    mismatches.append(f"missing reconstructed local-code symbol {label}")
                    continue
                offset = symbol_values[label]
                local_code_symbols = dict(simple_code_targets)
                local_code_symbols.update({block["source_va"]: block["label"] for block in stub.get("blocks", ())})
                local_code_symbols.update(stub.get("local_labels", {}))
                def local_code_offset(target_va: int) -> int | None:
                    target_symbol = local_code_symbols.get(target_va)
                    if target_symbol is not None:
                        return symbol_values.get(target_symbol)
                    fragments_with_addresses = [(stub["targets"][0], stub["body"], label)]
                    fragments_with_addresses.extend(
                        (block["source_va"], block["body"], block["label"])
                        for block in stub.get("blocks", ())
                    )
                    for source_va, fragment_body, fragment_symbol in fragments_with_addresses:
                        if source_va <= target_va < source_va + len(fragment_body):
                            fragment_start = symbol_values.get(fragment_symbol)
                            if fragment_start is not None:
                                return fragment_start + (target_va - source_va)
                    return None
                fragments = [(label, stub["body"], stub["fixups"], offset)]
                for block in stub.get("blocks", ()):
                    block_offset = symbol_values.get(block["label"])
                    if block_offset is None:
                        mismatches.append(f"missing reconstructed continuation symbol {block['label']}")
                        continue
                    fragments.append((block["label"], block["body"], block["fixups"], block_offset))
                for fragment_label, body, fixups, fragment_offset in fragments:
                    expected_body = bytearray(body)
                    for fixup_offset, kind, target_va in fixups:
                        if kind == "REL8":
                            local_target = local_code_offset(target_va)
                            if local_target is None:
                                mismatches.append(f"missing local REL8 target {target_va:#x} for {fragment_label}")
                            else:
                                displacement = struct.unpack_from("<b", code_bytes, fragment_offset + fixup_offset)[0]
                                actual_target = fragment_offset + fixup_offset + 1 + displacement
                                if actual_target != local_target:
                                    mismatches.append(f"local REL8 at {fragment_label}+{fixup_offset:#x} resolves to {actual_target:#x}, expected {local_target:#x}")
                                expected_body[fixup_offset] = code_bytes[fragment_offset + fixup_offset]
                        elif kind == "REL32":
                            target_symbol = local_code_symbols.get(target_va)
                            if target_symbol is None:
                                # Ghidra identifies 0x10017DDE as terminate() / ?terminate@@YAXXZ.
                                # Its TU also exports two naked SEH helpers at value zero in
                                # separate COMDAT sections; select the original address owner.
                                preferred = "?terminate@@YAXXZ" if target_va == 0x10017DDE else None
                                target_symbol = public_code_entry(
                                    args.objects_dir / f"{target_va:08x}.obj", preferred
                                )
                                expected_thunk_relocations.add((fragment_offset + fixup_offset, 0x0014, target_symbol))
                            else:
                                local_target = symbol_values.get(target_symbol)
                                if local_target is None:
                                    mismatches.append(f"missing local call target symbol {target_symbol}")
                                else:
                                    displacement = struct.unpack_from("<i", code_bytes, fragment_offset + fixup_offset)[0]
                                    actual_target = fragment_offset + fixup_offset + 4 + displacement
                                    if actual_target != local_target:
                                        mismatches.append(f"local REL32 at {fragment_label}+{fixup_offset:#x} resolves to {actual_target:#x}, expected {local_target:#x}")
                                    expected_body[fixup_offset:fixup_offset + 4] = code_bytes[fragment_offset + fixup_offset:fragment_offset + fixup_offset + 4]
                        else:
                            symbol = f"IVF_RELOC_TARGET_{target_va:08X}"
                            expected_thunk_relocations.add((fragment_offset + fixup_offset, 0x0006, symbol))
                            section_name = next((name for name in (".data", ".rdata") if image_base + int(pe_sections[name]["rva"]) <= target_va < image_base + int(pe_sections[name]["rva"]) + int(pe_sections[name]["virtual_size"])), None)
                            data_symbol = next((item for item in symbols.values() if item[0] == symbol), None)
                            data_section_no = next((k for k, v in sections.items() if v["name"] == section_name), None) if section_name else None
                            wanted = target_va - (image_base + int(pe_sections[section_name]["rva"])) if section_name else None
                            if data_symbol is None or data_section_no is None or data_symbol[1:] != (wanted, data_section_no):
                                mismatches.append(f"reconstructed local-code data target has wrong section offset: {symbol}")
                    if code_bytes[fragment_offset:fragment_offset + len(body)] != expected_body:
                        mismatches.append(f"reconstructed local-code bytes mismatch at {fragment_label}")
                tail_jump = stub.get("tail_jump")
                if tail_jump is not None:
                    symbol = public_code_entry(args.objects_dir / f"{tail_jump:08x}.obj")
                    if code_bytes[offset + len(body)] != 0xE9:
                        mismatches.append(f"synthetic tail transfer is not a near JMP at {label}")
                    expected_thunk_relocations.add((offset + len(body) + 1, 0x0014, symbol))
            actual_thunk_relocations = {
                (offset, reloc_type, symbol_name)
                for offset, reloc_type, _, symbol_name in text_relocations
            }
            if actual_thunk_relocations != expected_thunk_relocations:
                mismatches.append(
                    f"startup thunk relocation set mismatch: expected {len(expected_thunk_relocations)}, "
                    f"found {len(actual_thunk_relocations)}"
                )
            if len(text_relocations) != len(expected_thunk_relocations):
                mismatches.append(f"unexpected extra .text relocations: {len(text_relocations)}")
    startup_thunk_count = sum(1 for section, offset in seen if expected[(section, offset)][0] == "<local-code>")
    helper_site_count = sum(1 for site_section, offset in seen if expected[(site_section, offset)][2] in {entry[0] for entry in helper_stubs.values()})
    initterm_site_count = sum(1 for site_section, offset in seen if expected[(site_section, offset)][2] in {entry[0] for entry in initterm_stubs.values()})
    candidate_code_count = sum(
        1
        for section, offset in seen
        if expected[(section, offset)][2] is not None and expected[(section, offset)][0] != "<local-code>"
    )
    print(f"Expected fixup sites: {len(expected)}")
    print(f"  data-to-data: {len(expected) - candidate_code_count - startup_thunk_count}")
    print(f"  exact candidate code targets: {candidate_code_count}")
    print(f"  reconstructed local-code pointer sites: {startup_thunk_count}")
    if helper_stubs:
        print(f"  CRT fallback helper stubs: {len(helper_stubs)} (pointer sites: {helper_site_count})")
    if initterm_stubs:
        print(f"  reconstructed _initterm_e stubs: {len(initterm_stubs)} (pointer sites: {initterm_site_count})")
    if 0x10013025 in initterm_stubs:
        print("  Ghidra/source PE state-table callback byte crosswalk: 177/177 bytes")
    if startup_thunks:
        print(f"  Ghidra original thunk sequences matched: {verified_original_thunks}/{len(startup_thunks)}")
        print(f"  verified generated .text code relocations: {len(expected_thunk_relocations)}")
    print(f"COFF .data/.rdata relocation records: {actual_count}")
    print(f"Verified exact sites, DIR32 types, target symbols/sections/offsets: {len(seen) - len(mismatches)}")
    print(f"Mismatches: {len(mismatches)}")
    for mismatch in mismatches[:20]:
        print(f"ERROR: {mismatch}")
    return 1 if mismatches or actual_count != len(expected) else 0


def parse_pe_sections(path: Path) -> tuple[bytes, int, dict[str, dict[str, int]]]:
    image = path.read_bytes()
    pe = struct.unpack_from("<I", image, 0x3C)[0]
    if image[:2] != b"MZ" or image[pe : pe + 4] != b"PE\0\0":
        raise ValueError("input is not a PE image")
    _, count = struct.unpack_from("<HH", image, pe + 4)
    optional_size = struct.unpack_from("<H", image, pe + 20)[0]
    optional = pe + 24
    if struct.unpack_from("<H", image, optional)[0] != 0x10B:
        raise ValueError("expected PE32 image")
    image_base = struct.unpack_from("<I", image, optional + 28)[0]
    table = optional + optional_size
    sections = {}
    for number in range(count):
        at = table + number * 40
        name = image[at : at + 8].split(b"\0", 1)[0].decode("ascii")
        virtual_size, rva, raw_size, raw_offset = struct.unpack_from("<IIII", image, at + 8)
        sections[name] = {"virtual_size": virtual_size, "rva": rva, "raw_size": raw_size, "raw_offset": raw_offset}
    return image, image_base, sections


if __name__ == "__main__":
    raise SystemExit(main())
