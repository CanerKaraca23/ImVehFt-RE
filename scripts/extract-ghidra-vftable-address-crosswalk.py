#!/usr/bin/env python3
"""Crosswalk callback-manager vtable externals to Ghidra initializer immediates."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import re
import struct
from pathlib import Path


def parse_image(data: bytes) -> tuple[int, dict[str, dict[str, int]]]:
    if data[:2] != b"MZ":
        raise ValueError("input has no MZ signature")
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    if data[pe : pe + 4] != b"PE\0\0":
        raise ValueError("input has no PE signature")
    machine, count = struct.unpack_from("<HH", data, pe + 4)
    optional_size = struct.unpack_from("<H", data, pe + 20)[0]
    optional = pe + 24
    if machine != 0x14C or struct.unpack_from("<H", data, optional)[0] != 0x10B:
        raise ValueError("expected x86 PE32")
    base = struct.unpack_from("<I", data, optional + 28)[0]
    table = optional + optional_size
    sections: dict[str, dict[str, int]] = {}
    for index in range(count):
        at = table + index * 40
        name = data[at : at + 8].split(b"\0", 1)[0].decode("ascii")
        virtual_size, rva, raw_size, raw_offset = struct.unpack_from("<IIII", data, at + 8)
        sections[name] = {
            "rva": rva,
            "virtual_size": virtual_size,
            "raw_size": raw_size,
            "raw_offset": raw_offset,
        }
    return base, sections


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("image", type=Path)
    parser.add_argument("source_dir", type=Path)
    parser.add_argument("ghidra_dir", type=Path)
    parser.add_argument("relocation_report", type=Path)
    parser.add_argument("--csv", type=Path, required=True, help="provider input: address,symbol")
    parser.add_argument("--manifest", type=Path, required=True)
    args = parser.parse_args()
    if args.csv.exists() or args.manifest.exists():
        parser.error("refusing to overwrite existing output")

    image = args.image.read_bytes()
    base, sections = parse_image(image)
    relocation_report = json.loads(args.relocation_report.read_text(encoding="utf-8"))
    relocations = {
        int(row["site_va"], 16): int(row["stored_va"], 16)
        for row in relocation_report["all_highlow_relocations"]
        if row["site_section"] == ".text"
    }
    rows: list[dict[str, str]] = []
    evidence: list[dict[str, str]] = []
    seen: dict[str, int] = {}

    for source in sorted(args.source_dir.glob("1002*.cpp")):
        text = source.read_text(encoding="utf-8", errors="replace")
        assignments = re.findall(
            r"PTR_vftable_([0-9A-Fa-f]{8})\s*=\s*(BasicCallbackManager_[A-Za-z0-9_]+_vftable)\s*;",
            text,
        )
        if not assignments:
            continue
        if len(assignments) != 1:
            raise ValueError(f"expected one callback vtable assignment in {source}")
        destination = int(assignments[0][0], 16)
        symbol = assignments[0][1]
        ghidra_path = args.ghidra_dir / f"{source.stem}.json"
        ghidra = json.loads(ghidra_path.read_text(encoding="utf-8"))
        if int(ghidra["address"], 16) != int(source.stem, 16):
            raise ValueError(f"Ghidra export address mismatch for {source.stem}")
        instructions = []
        for line in ghidra.get("assembly", []):
            match = re.fullmatch(
                r"\s*([0-9A-Fa-f]{8})\s+MOV dword ptr \[0x([0-9A-Fa-f]{8})\],0x([0-9A-Fa-f]{8})\s*",
                line,
            )
            if match and int(match.group(2), 16) == destination:
                instructions.append((int(match.group(1), 16), int(match.group(3), 16)))
        if len(instructions) != 1:
            raise ValueError(f"expected one Ghidra absolute vtable store to {destination:#x} in {source.stem}")
        instruction, target = instructions[0]

        # C7 05 disp32 imm32: the original PE HIGHLOW entries must independently
        # confirm both the absolute global destination and the vtable target.
        destination_fixup = instruction + 2
        target_fixup = instruction + 6
        if relocations.get(destination_fixup) != destination:
            raise ValueError(f"missing/mismatched HIGHLOW destination fixup at {destination_fixup:#x}")
        if relocations.get(target_fixup) != target:
            raise ValueError(f"missing/mismatched HIGHLOW vtable-target fixup at {target_fixup:#x}")

        def file_offset(va: int, width: int) -> tuple[str, int]:
            for name in (".text", ".rdata", ".data"):
                section = sections[name]
                offset = va - (base + section["rva"])
                if 0 <= offset and offset + width <= section["raw_size"]:
                    return name, section["raw_offset"] + offset
            raise ValueError(f"address is not raw-backed in .rdata/.data: {va:#x}")

        target_section, target_offset = file_offset(target, 1)
        if target_section != ".rdata":
            raise ValueError(f"callback-manager vtable target is not in .rdata: {target:#x} ({target_section})")
        instruction_section, instruction_offset = file_offset(instruction, 10)
        if instruction_section != ".text":
            raise ValueError(f"initializer instruction is not in .text: {instruction:#x}")
        encoded_destination = struct.unpack_from("<I", image, instruction_offset + 2)[0]
        encoded_target = struct.unpack_from("<I", image, instruction_offset + 6)[0]
        if (encoded_destination, encoded_target) != (destination, target):
            raise ValueError(f"raw instruction bytes disagree at {instruction:#x}")
        if symbol in seen and seen[symbol] != target:
            raise ValueError(f"vtable symbol maps to multiple target VAs: {symbol}")
        if symbol in seen:
            continue
        seen[symbol] = target
        rows.append({"address": f"0x{target:08X}", "symbol": f"?{symbol}@@3PAXA"})
        evidence.append(
            {
                "evidence_type": "global-vftable-initializer",
                "source_function": source.stem,
                "symbol_source_name": symbol,
                "global_destination_va": f"0x{destination:08X}",
                "ghidra_instruction_va": f"0x{instruction:08X}",
                "vtable_target_va": f"0x{target:08X}",
                "vtable_target_section": target_section,
                "destination_fixup_site": f"0x{destination_fixup:08X}",
                "target_fixup_site": f"0x{target_fixup:08X}",
                "evidence": "Ghidra original MOV absolute store + matching original PE HIGHLOW records + raw instruction-byte agreement",
            }
        )

    # Constructors provide a second, direct Ghidra observation: their first
    # vtable store is MOV [ESI], imm32. Include constructor-only vtables that
    # have no separate global initializer and require agreement with any
    # matching initializer crosswalk above.
    for source in sorted(args.source_dir.glob("*.cpp")):
        text = source.read_text(encoding="utf-8", errors="replace")
        symbols = set(re.findall(r"(BasicCallbackManager_[A-Za-z0-9_]+_vftable)", text))
        if len(symbols) != 1:
            continue
        symbol = next(iter(symbols))
        ghidra_path = args.ghidra_dir / f"{source.stem}.json"
        ghidra = json.loads(ghidra_path.read_text(encoding="utf-8"))
        symbol_numbers = re.match(r"BasicCallbackManager_((?:\d+_)+)", symbol)
        if not symbol_numbers:
            continue
        normalized_numbers = ",".join(symbol_numbers.group(1).strip("_").split("_"))
        if normalized_numbers not in ghidra.get("decompiled", ""):
            continue
        constructor_stores = []
        for line in ghidra.get("assembly", []):
            match = re.fullmatch(
                r"\s*([0-9A-Fa-f]{8})\s+MOV dword ptr \[ESI\],0x([0-9A-Fa-f]{8})\s*",
                line,
            )
            if match:
                constructor_stores.append((int(match.group(1), 16), int(match.group(2), 16)))
        if not constructor_stores:
            continue
        if len(constructor_stores) != 1:
            raise ValueError(f"expected one constructor vtable store in {source.stem}")
        instruction, target = constructor_stores[0]
        target_section, _ = file_offset(target, 1)
        if target_section != ".rdata":
            raise ValueError(f"constructor vtable target is not in .rdata: {target:#x}")
        fixup = instruction + 2
        if relocations.get(fixup) != target:
            raise ValueError(f"missing/mismatched constructor vtable HIGHLOW at {fixup:#x}")
        instruction_section, instruction_offset = file_offset(instruction, 6)
        if instruction_section != ".text":
            raise ValueError(f"constructor vtable store is not in .text: {instruction:#x}")
        if image[instruction_offset : instruction_offset + 2] != b"\xC7\x06":
            raise ValueError(f"constructor raw opcode is not MOV dword ptr [ESI],imm32 at {instruction:#x}")
        if struct.unpack_from("<I", image, instruction_offset + 2)[0] != target:
            raise ValueError(f"constructor raw immediate disagrees at {instruction:#x}")
        previous = seen.get(symbol)
        if previous is not None and previous != target:
            raise ValueError(f"constructor and global initializer disagree for {symbol}")
        if previous is None:
            seen[symbol] = target
            rows.append({"address": f"0x{target:08X}", "symbol": f"?{symbol}@@3PAXA"})
        evidence.append(
            {
                "evidence_type": "constructor-vftable-store",
                "source_function": source.stem,
                "symbol_source_name": symbol,
                "global_destination_va": "this+0",
                "ghidra_instruction_va": f"0x{instruction:08X}",
                "vtable_target_va": f"0x{target:08X}",
                "vtable_target_section": target_section,
                "destination_fixup_site": "not-applicable-register-indirect-store",
                "target_fixup_site": f"0x{fixup:08X}",
                "evidence": "Ghidra decompilation identifies this class vftable + original MOV [ESI],imm32 + matching PE HIGHLOW + raw opcode/immediate agreement",
            }
        )

    args.csv.parent.mkdir(parents=True, exist_ok=True)
    args.manifest.parent.mkdir(parents=True, exist_ok=True)
    with args.csv.open("x", encoding="utf-8", newline="") as stream:
        writer = csv.DictWriter(stream, fieldnames=("address", "symbol"))
        writer.writeheader()
        writer.writerows(rows)
    manifest = {
        "scope": "Ghidra-initializer-derived exact callback-manager vtable target aliases; independently checked against original instruction bytes and original PE HIGHLOW records",
        "image": str(args.image.resolve()),
        "image_sha256": hashlib.sha256(image).hexdigest(),
        "relocation_report": str(args.relocation_report.resolve()),
        "crosswalk_count": len(evidence),
        "evidence": evidence,
        "limitations": [
            "does not prove complete C++ vtable extent or all virtual entries",
            "does not repair candidate relocation or PE layout",
            "does not establish runtime/game behavior",
        ],
    }
    with args.manifest.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(manifest, stream, indent=2)
        stream.write("\n")
    print(json.dumps({"crosswalk_count": len(evidence), "aliases": rows}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
