#!/usr/bin/env python3
"""Inventory RenderWare registration-wrapper address patterns in GTA modules.

This is a byte-pattern locator for absolute immediates and x86 rel32 CALL/JMP
targets in ASI/DLL files, not proof that a wrapper is called or that a module
is loaded. Confirm reported offsets in Ghidra.
"""

from __future__ import annotations

import argparse
import hashlib
import struct
import sys
from pathlib import Path


WRAPPERS = {
    0x007F3BB0: "RwTextureRegisterPlugin",
    0x007FB0B0: "RwRasterRegisterPlugin",
    0x007F1260: "RwFrameRegisterPlugin",
}


def read_pe_sections(data: bytes) -> tuple[int, int, list[tuple[str, int, int, int, int, int]]]:
    if data[:2] != b"MZ":
        raise ValueError("missing DOS MZ signature")
    pe_offset = struct.unpack_from("<I", data, 0x3C)[0]
    if data[pe_offset : pe_offset + 4] != b"PE\0\0":
        raise ValueError("missing PE signature")
    section_count = struct.unpack_from("<H", data, pe_offset + 6)[0]
    machine = struct.unpack_from("<H", data, pe_offset + 4)[0]
    optional_size = struct.unpack_from("<H", data, pe_offset + 20)[0]
    optional = pe_offset + 24
    magic = struct.unpack_from("<H", data, optional)[0]
    if magic != 0x10B:
        raise ValueError(f"expected PE32 optional header, found {magic:#x}")
    image_base = struct.unpack_from("<I", data, optional + 28)[0]
    section_table = optional + optional_size
    sections = []
    for index in range(section_count):
        offset = section_table + index * 40
        header = data[offset : offset + 40]
        name = header[:8].split(b"\0", 1)[0].decode("ascii", errors="replace")
        virtual_size, rva, raw_size, raw_offset = struct.unpack_from("<IIII", header, 8)
        characteristics = struct.unpack_from("<I", header, 36)[0]
        sections.append((name, virtual_size, rva, raw_size, raw_offset, characteristics))
    return machine, image_base, sections


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "game_root",
        nargs="?",
        type=Path,
        default=Path(r"C:\Users\caner\OneDrive\Documents\GTA San Andreas"),
    )
    args = parser.parse_args()
    if not args.game_root.is_dir():
        parser.error(f"not a directory: {args.game_root}")

    paths = sorted(
        path
        for path in args.game_root.rglob("*")
        if path.is_file() and path.suffix.lower() in {".asi", ".dll"}
        if not any(
            part.lower().startswith("_backup") or ".backup" in part.lower()
            for part in path.relative_to(args.game_root).parts
        )
    )
    print(
        f"scanned_module_candidates={len(paths)} "
        "(ASI/DLL; backup-named paths excluded; load state unverified)",
        file=sys.stderr,
    )
    print("relative_path,sha256,wrapper,match_kind,file_offset,reference_va,target_va,section,context_hex")
    for path in paths:
        data = path.read_bytes()
        digest = hashlib.sha256(data).hexdigest()
        try:
            machine, image_base, sections = read_pe_sections(data)
        except (ValueError, struct.error) as error:
            print(f"# skipped {path}: {error}")
            continue
        if machine != 0x14C:
            print(f"# skipped {path}: expected i386 PE, found machine {machine:#x}")
            continue
        for target, name in WRAPPERS.items():
            needle = struct.pack("<I", target)
            position = 0
            while True:
                file_offset = data.find(needle, position)
                if file_offset < 0:
                    break
                position = file_offset + 1
                for section_name, _, rva, raw_size, raw_offset, characteristics in sections:
                    if raw_offset <= file_offset < raw_offset + raw_size:
                        immediate_va = image_base + rva + file_offset - raw_offset
                        context = data[max(0, file_offset - 8) : file_offset + 8].hex(" ")
                        escaped = str(path.relative_to(args.game_root)).replace('"', '""')
                        print(
                            f'"{escaped}",{digest},{name},absolute-imm32,0x{file_offset:x},'
                            f'0x{immediate_va:08x},0x{target:08x},{section_name},"{context}"'
                        )
                        thunk_entry = None
                        if characteristics & 0x20000000 and file_offset >= raw_offset + 4:
                            if data[file_offset - 4 : file_offset] == b"\x55\x8b\xec\xb8":
                                thunk_entry = immediate_va - 4
                            elif (
                                data[file_offset - 1] == 0xB8
                                and data[file_offset + 4 : file_offset + 6] == b"\xff\xe0"
                            ):
                                thunk_entry = immediate_va - 1
                        if thunk_entry is not None:
                            for exec_name, _, exec_rva, exec_size, exec_offset, exec_flags in sections:
                                if not exec_flags & 0x20000000:
                                    continue
                                exec_end = min(exec_offset + exec_size, len(data))
                                for call_offset in range(exec_offset, max(exec_offset, exec_end - 4)):
                                    if data[call_offset] != 0xE8:
                                        continue
                                    relative = struct.unpack_from("<i", data, call_offset + 1)[0]
                                    call_va = image_base + exec_rva + call_offset - exec_offset
                                    if (call_va + 5 + relative) & 0xFFFFFFFF != thunk_entry:
                                        continue
                                    call_context = data[max(exec_offset, call_offset - 24) : min(exec_end, call_offset + 8)].hex(" ")
                                    print(
                                        f'"{escaped}",{digest},{name},rel32-call-to-thunk,0x{call_offset:x},'
                                        f'0x{call_va:08x},0x{thunk_entry:08x},{exec_name},"{call_context}"'
                                    )
                        break
            # Locate candidate x86 near CALL/JMP encodings targeting the wrapper.
            for section_name, _, rva, raw_size, raw_offset, characteristics in sections:
                if not characteristics & 0x20000000:  # IMAGE_SCN_MEM_EXECUTE
                    continue
                end = min(raw_offset + raw_size, len(data))
                for file_offset in range(raw_offset, max(raw_offset, end - 4)):
                    opcode = data[file_offset]
                    if opcode not in (0xE8, 0xE9):
                        continue
                    displacement = struct.unpack_from("<i", data, file_offset + 1)[0]
                    instruction_va = image_base + rva + file_offset - raw_offset
                    if (instruction_va + 5 + displacement) & 0xFFFFFFFF != target:
                        continue
                    context = data[max(raw_offset, file_offset - 8) : min(end, file_offset + 8)].hex(" ")
                    escaped = str(path.relative_to(args.game_root)).replace('"', '""')
                    kind = "rel32-call" if opcode == 0xE8 else "rel32-jump"
                    print(
                        f'"{escaped}",{digest},{name},{kind},0x{file_offset:x},'
                        f'0x{instruction_va:08x},0x{target:08x},{section_name},"{context}"'
                    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
