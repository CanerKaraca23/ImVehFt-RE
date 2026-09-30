#!/usr/bin/env python3
"""Disassemble original instructions at HIGHLOW fields crossing candidate body ends."""

from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
import struct
from pathlib import Path

from capstone import Cs, CS_ARCH_X86, CS_MODE_32


ROOT = Path(__file__).resolve().parents[1]
HELPER_PATH = ROOT / "scripts/audit-inplace-candidate-relocations.py"
EXPECTED_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"


def load_helper():
    spec = importlib.util.spec_from_file_location("inplace_audit", HELPER_PATH)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot import {HELPER_PATH}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def pe_sections(data: bytes):
    peoff = struct.unpack_from("<I", data, 0x3C)[0]
    if data[:2] != b"MZ" or data[peoff : peoff + 4] != b"PE\0\0":
        raise ValueError("invalid PE image")
    machine, nsections, _, _, _, opt_size, _ = struct.unpack_from("<HHIIIHH", data, peoff + 4)
    if machine != 0x14C:
        raise ValueError(f"expected i386 PE, got machine={machine:#x}")
    opt = peoff + 24
    if struct.unpack_from("<H", data, opt)[0] != 0x10B:
        raise ValueError("expected PE32 optional header")
    image_base = struct.unpack_from("<I", data, opt + 28)[0]
    sec_table = opt + opt_size
    sections = []
    for i in range(nsections):
        at = sec_table + i * 40
        name, vsize, va, raw_size, raw_ptr = struct.unpack_from("<8sIIII", data, at)
        sections.append((name.split(b"\0", 1)[0].decode("ascii"), vsize, va, raw_size, raw_ptr))
    return image_base, sections


def rva_to_offset(rva: int, sections) -> int:
    for _, vsize, va, raw_size, raw_ptr in sections:
        if va <= rva < va + max(vsize, raw_size):
            delta = rva - va
            if delta >= raw_size:
                raise ValueError(f"RVA {rva:#x} falls in virtual-only section bytes")
            return raw_ptr + delta
    raise ValueError(f"RVA {rva:#x} is not in a PE section")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--original", type=Path, required=True)
    ap.add_argument("--objects", type=Path, required=True)
    ap.add_argument("--reconciliation", type=Path, required=True)
    ap.add_argument("--output", type=Path, required=True)
    args = ap.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")
    image = args.original.read_bytes()
    digest = hashlib.sha256(image).hexdigest().upper()
    if digest != EXPECTED_SHA256:
        raise ValueError(f"original hash mismatch: {digest}")
    base, sections = pe_sections(image)
    text_sections = [s for s in sections if s[0] == ".text"]
    if len(text_sections) != 1:
        raise ValueError(f"expected one .text section, found {len(text_sections)}")
    _, _, text_rva, text_raw_size, _ = text_sections[0]
    rows = json.loads(args.reconciliation.read_text(encoding="utf-8"))["results"]
    helper = load_helper()
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    out = []
    for row in rows:
        sites = [int(x, 16) for x in row["old_fields_straddling_candidate_body_boundary"]]
        if not sites:
            continue
        entry = int(row["entry_va"], 16)
        end = entry + int(row["body_size"])
        obj, _ = helper.parse_coff(args.objects / f"{entry:08x}.obj", row["symbol"])
        if len(obj) != int(row["body_size"]):
            raise ValueError(f"{entry:#x}: current object size changed")
        start_rva = entry - base
        stop_rva = end - base + 12
        raw_start = rva_to_offset(start_rva, sections)
        raw_stop = rva_to_offset(stop_rva - 1, sections) + 1
        if raw_stop > len(image) or raw_start + (stop_rva - start_rva) > len(image):
            raise ValueError(f"{entry:#x}: disassembly range outside file")
        code = image[raw_start : raw_start + (stop_rva - start_rva)]
        insns = list(md.disasm(code, entry))
        for site in sites:
            containing = [i for i in insns if i.address <= site < i.address + i.size]
            field_owner = [i for i in insns if i.address <= site and site + 4 <= i.address + i.size]
            boundary_owner = [i for i in insns if i.address < end < i.address + i.size]
            start = max(entry, end - 12)
            context = [
                {"address": f"0x{i.address:08x}", "bytes": i.bytes.hex(" "),
                 "instruction": f"{i.mnemonic} {i.op_str}".strip()}
                for i in insns if start <= i.address < end + 8
            ]
            out.append({
                "entry_va": f"0x{entry:08x}", "candidate_body_size": int(row["body_size"]),
                "candidate_body_end_exclusive": f"0x{end:08x}",
                "original_highlow_site": f"0x{site:08x}",
                "site_offset_from_entry": site - entry,
                "candidate_body_overlap_bytes": max(0, min(site + 4, end) - site),
                "original_instruction_containing_site": (
                    {"address": f"0x{containing[0].address:08x}",
                     "bytes": containing[0].bytes.hex(" "),
                     "instruction": f"{containing[0].mnemonic} {containing[0].op_str}".strip()}
                    if containing else None
                ),
                "site_fully_inside_one_decoded_instruction": bool(field_owner),
                "original_instruction_crosses_candidate_end": (
                    {"address": f"0x{boundary_owner[0].address:08x}",
                     "bytes": boundary_owner[0].bytes.hex(" "),
                     "instruction": f"{boundary_owner[0].mnemonic} {boundary_owner[0].op_str}".strip(),
                     "bytes_before_candidate_end": end - boundary_owner[0].address,
                     "bytes_after_candidate_end": boundary_owner[0].address + boundary_owner[0].size - end}
                    if boundary_owner else None
                ),
                "original_disassembly_near_boundary": context,
            })
    output = {
        "original_path": str(args.original.resolve()), "original_sha256": digest,
        "image_base": f"0x{base:08x}", "text_rva": f"0x{text_rva:08x}",
        "text_raw_size": text_raw_size,
        "reconciliation_report": str(args.reconciliation.resolve()),
        "candidate_objects": str(args.objects.resolve()),
        "boundary_straddler_count": len(out), "results": out,
        "limitations": [
            "Linear disassembly begins at each function entry and uses Capstone; this does not prove reachability or ownership of tail bytes.",
            "The report identifies instruction/fixup overlap only; it does not patch the PE or prove full-image/runtime correctness.",
        ],
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("x", encoding="utf-8", newline="\n") as f:
        json.dump(output, f, indent=2)
        f.write("\n")
    crossing = sum(r["original_instruction_crosses_candidate_end"] is not None for r in out)
    fully_decoded = sum(r["site_fully_inside_one_decoded_instruction"] for r in out)
    print(f"straddlers={len(out)} fully_decoded_sites={fully_decoded} instructions_crossing_candidate_end={crossing}")
    print(f"report={args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
