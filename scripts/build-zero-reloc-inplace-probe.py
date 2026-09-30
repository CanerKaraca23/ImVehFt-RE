#!/usr/bin/env python3
"""Patch one evidence-screened, relocation-free candidate into a disposable ASI copy."""

from __future__ import annotations

import argparse
import csv
import hashlib
import importlib.util
import json
import struct
from pathlib import Path

import capstone
from capstone import x86


EXPECTED_ASI_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def load_coff_parser(repo: Path):
    path = repo / "scripts" / "audit-inplace-candidate-relocations.py"
    spec = importlib.util.spec_from_file_location("inplace_candidate_relocations", path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot load COFF parser: {path}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module.parse_coff


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--repo", type=Path, required=True)
    parser.add_argument("--reference", type=Path, required=True)
    parser.add_argument("--entry", required=True, help="candidate entry VA, e.g. 0x10003fe0")
    parser.add_argument("--output", type=Path, required=True, help="new .bin probe path")
    args = parser.parse_args()
    repo = args.repo.resolve()
    entry = int(args.entry, 16)
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")
    original = args.reference.read_bytes()
    if sha256(original) != EXPECTED_ASI_SHA256:
        raise ValueError("reference ASI SHA-256 does not match the pinned original")

    report_path = repo / "audit" / "inplace-candidate-relocation-coverage-current-2026-09-28.json"
    report = json.loads(report_path.read_text(encoding="utf-8"))
    rows = [row for row in report["results"] if int(row["entry_va"], 16) == entry]
    if len(rows) != 1:
        raise ValueError(f"expected one placement record for {entry:#x}")
    row = rows[0]
    if row["placement_class"] != "fits-no-coff-relocations" or row["original_highlow_overlap_count"] != 0:
        raise ValueError("candidate is not proven relocation-free and clear of original HIGHLOW fields")
    if not row["body_fits_gap"]:
        raise ValueError("candidate does not fit its bounded original entry gap")

    size = int(row["candidate_body_size"])
    end = entry + size
    object_path = repo / "build" / "recheck" / "strict-xcode-current-20260928-3" / f"{entry:08x}.obj"
    code, info = load_coff_parser(repo)(object_path, row["symbol"])
    if len(code) != size or info["object_sha256"] != row["object_sha256"] or info["relocations"]:
        raise ValueError("COFF bytes/relocations disagree with the audited placement manifest")

    refs = []
    for batch in sorted((repo / "audit").glob("inplace-lowreloc-fullrefs-batch*-2026-09-28.csv")):
        with batch.open(encoding="utf-8-sig", newline="") as stream:
            refs.extend(x for x in csv.DictReader(stream) if int(x["function_entry"], 16) == entry)
    if not refs:
        raise ValueError("full-span Ghidra reference audit is missing for this candidate")
    original_body_end = max(int(x["body_max"], 16) for x in refs)
    external_interior_refs = []
    for ref in refs:
        if not ref["incoming_ref_from"]:
            continue
        target, source = int(ref["address"], 16), int(ref["incoming_ref_from"], 16)
        if entry < target < end and not entry <= source < end:
            external_interior_refs.append(ref)
    if external_interior_refs:
        raise ValueError(f"external reference enters overwritten interior: {external_interior_refs[0]}")

    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, entry))
    if sum(instruction.size for instruction in instructions) != size:
        raise ValueError("candidate .xcode does not decode continuously as 32-bit x86 instructions")
    instruction_starts = {instruction.address for instruction in instructions}
    branch_targets = []
    for instruction in instructions:
        for operand in instruction.operands:
            if operand.type == x86.X86_OP_MEM and operand.mem.base == 0 and operand.mem.index == 0:
                absolute = operand.mem.disp & 0xFFFFFFFF
                if entry <= absolute <= original_body_end:
                    raise ValueError(f"candidate directly references original function bytes: {instruction.mnemonic} {instruction.op_str}")
        if instruction.group(capstone.CS_GRP_CALL) or instruction.group(capstone.CS_GRP_JUMP):
            target_operands = [operand.imm & 0xFFFFFFFF for operand in instruction.operands
                               if operand.type == x86.X86_OP_IMM]
            for target in target_operands:
                branch_targets.append(f"0x{target:08X}")
                if entry <= target < end and target not in instruction_starts:
                    raise ValueError(f"candidate control flow targets a non-instruction byte: {target:#x}")
                if end <= target <= original_body_end:
                    raise ValueError(f"candidate branch enters preserved original function tail: {target:#x}")

    pe = struct.unpack_from("<I", original, 0x3C)[0]
    if original[pe : pe + 4] != b"PE\0\0":
        raise ValueError("reference is not a valid PE image")
    sections = struct.unpack_from("<H", original, pe + 6)[0]
    optional_size = struct.unpack_from("<H", original, pe + 20)[0]
    optional = pe + 24
    if struct.unpack_from("<H", original, optional)[0] != 0x10B:
        raise ValueError("expected a PE32 image")
    image_base = struct.unpack_from("<I", original, optional + 28)[0]
    section_table = optional + optional_size
    raw_offset = None
    for index in range(sections):
        at = section_table + index * 40
        name = original[at : at + 8].split(b"\0", 1)[0]
        virtual_size, rva, raw_size, raw = struct.unpack_from("<IIII", original, at + 8)
        if name == b".text" and image_base + rva <= entry < image_base + rva + max(virtual_size, raw_size):
            relative = entry - (image_base + rva)
            if relative + size > raw_size:
                raise ValueError("candidate bytes exceed initialized .text raw data")
            raw_offset = raw + relative
            break
    if raw_offset is None:
        raise ValueError("candidate entry does not map into original .text")

    patched = bytearray(original)
    patched[raw_offset : raw_offset + size] = code
    if bytes(patched[:raw_offset]) != original[:raw_offset] or bytes(patched[raw_offset + size :]) != original[raw_offset + size :]:
        raise AssertionError("probe differs outside the selected candidate byte span")
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("xb") as stream:
        stream.write(patched)
    summary = {
        "scope": "single relocation-free function in-place probe; not a loadable or runtime-validated ASI",
        "entry_va": f"0x{entry:08X}",
        "symbol": row["symbol"],
        "candidate_size": size,
        "raw_offset": raw_offset,
        "reference_sha256": sha256(original),
        "probe_sha256": sha256(patched),
        "object_sha256": info["object_sha256"],
        "object_relocations": 0,
        "full_span_ghidra_rows": len(refs),
        "ghidra_body_end": f"0x{original_body_end:08X}",
        "candidate_decoded_instruction_count": len(instructions),
        "candidate_direct_control_flow_targets": branch_targets,
        "different_bytes": sum(a != b for a, b in zip(original, patched)),
        "output": str(args.output.resolve()),
    }
    report_out = args.output.with_suffix(args.output.suffix + ".json")
    with report_out.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(summary, stream, indent=2)
        stream.write("\n")
    print(json.dumps(summary, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
