#!/usr/bin/env python3
"""Check whether each planned in-place candidate end is an original x86 instruction boundary."""

from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
import struct
from collections import Counter
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


def read_pe(data: bytes):
    peoff = struct.unpack_from("<I", data, 0x3C)[0]
    if data[:2] != b"MZ" or data[peoff:peoff + 4] != b"PE\0\0":
        raise ValueError("invalid PE image")
    machine, nsections, _, _, _, opt_size, _ = struct.unpack_from("<HHIIIHH", data, peoff + 4)
    opt = peoff + 24
    if machine != 0x14C or struct.unpack_from("<H", data, opt)[0] != 0x10B:
        raise ValueError("expected i386 PE32")
    base = struct.unpack_from("<I", data, opt + 28)[0]
    section_table = opt + opt_size
    sections = []
    for i in range(nsections):
        at = section_table + 40 * i
        name, vsize, rva, raw_size, raw = struct.unpack_from("<8sIIII", data, at)
        sections.append((name.split(b"\0", 1)[0].decode("ascii"), vsize, rva, raw_size, raw))
    text = [s for s in sections if s[0] == ".text"]
    if len(text) != 1:
        raise ValueError("expected exactly one .text section")
    return base, text[0]


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--original", type=Path, required=True)
    ap.add_argument("--objects", type=Path, required=True)
    ap.add_argument("--placement-plan", type=Path, required=True)
    ap.add_argument("--output", type=Path, required=True)
    a = ap.parse_args()
    if a.output.exists():
        raise FileExistsError(f"refusing to overwrite {a.output}")
    image = a.original.read_bytes()
    digest = hashlib.sha256(image).hexdigest().upper()
    if digest != EXPECTED_SHA256:
        raise ValueError(f"unexpected original image SHA-256 {digest}")
    base, text = read_pe(image)
    _, _, text_rva, text_raw_size, text_raw = text
    plan_bytes = a.placement_plan.read_bytes()
    plan = json.loads(plan_bytes)
    if plan.get("candidate_count") != 705:
        raise ValueError("expected current 705-entry placement plan")
    helper = load_helper()
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    result = []
    for row in plan["entries"]:
        if row["placement_mode"] != "body-at-entry":
            continue
        entry = int(row["address"], 16)
        body, _ = helper.parse_coff(a.objects / f"{entry:08x}.obj", row["entry_symbol"])
        if len(body) != int(row["candidate_body_size"]):
            raise ValueError(f"{entry:#x}: current COFF body size differs from placement plan")
        end = entry + len(body)
        start_rva, end_rva = entry - base, end - base
        if start_rva < text_rva or end_rva > text_rva + text_raw_size:
            raise ValueError(f"{entry:#x}: proposed body span escapes original .text raw bytes")
        file_at = text_raw + start_rva - text_rva
        requested = len(body) + 16
        if file_at + requested > text_raw + text_raw_size:
            requested = text_raw + text_raw_size - file_at
        insns = []
        cursor_va = entry
        for insn in md.disasm(image[file_at:file_at + requested], entry):
            if insn.address != cursor_va:
                break
            insns.append(insn)
            cursor_va += insn.size
            if cursor_va >= end:
                break
        if cursor_va == end:
            category = "instruction-boundary"
            crossing = None
        elif cursor_va > end:
            category = "cuts-original-instruction"
            last = insns[-1]
            crossing = {
                "address": f"0x{last.address:08x}", "bytes": last.bytes.hex(" "),
                "instruction": f"{last.mnemonic} {last.op_str}".strip(),
                "bytes_before_boundary": end - last.address,
                "bytes_after_boundary": last.address + last.size - end,
            }
        else:
            category = "undecodable-before-boundary"
            crossing = None
        near = [
            {"address": f"0x{i.address:08x}", "bytes": i.bytes.hex(" "),
             "instruction": f"{i.mnemonic} {i.op_str}".strip()}
            for i in insns if i.address >= end - 12
        ]
        result.append({
            "entry_va": f"0x{entry:08x}", "candidate_body_size": len(body),
            "candidate_body_end_exclusive": f"0x{end:08x}",
            "classification": category, "crossing_instruction": crossing,
            "original_disassembly_near_end": near,
        })
    counts = Counter(row["classification"] for row in result)
    report = {
        "scope": "Linear x86 disassembly boundary audit of every candidate still designated body-at-entry in the supplied plan.",
        "original_path": str(a.original.resolve()), "original_sha256": digest,
        "placement_plan": str(a.placement_plan.resolve()),
        "placement_plan_sha256": hashlib.sha256(plan_bytes).hexdigest().upper(),
        "candidate_bodies_checked": len(result), "classification_counts": dict(counts),
        "entries_requiring_reclassification": [
            row["entry_va"] for row in result if row["classification"] != "instruction-boundary"
        ],
        "limitations": [
            "Linear disassembly validates instruction boundaries only; it does not prove function semantics or references into candidate spans.",
            "Any cut or undecodable boundary is unsafe for full-span in-place replacement unless separately reconstructed and proven.",
            "No PE bytes are changed and no loader/runtime test is performed.",
        ],
        "results": result,
    }
    a.output.parent.mkdir(parents=True, exist_ok=True)
    with a.output.open("x", encoding="utf-8", newline="\n") as f:
        json.dump(report, f, indent=2)
        f.write("\n")
    print(f"checked={len(result)} classifications={dict(counts)} reclassify={len(report['entries_requiring_reclassification'])}")
    print(f"report={a.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
