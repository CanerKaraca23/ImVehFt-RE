#!/usr/bin/env python3
"""Compare relocation-free, slot-fit candidate bodies with original .text bytes."""

from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
import struct
from pathlib import Path


EXPECTED_ASI_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--repo", type=Path, required=True)
    parser.add_argument("--reference", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument(
        "--coverage-report",
        type=Path,
        help="Fresh COFF relocation/placement report (default: current 2026-09-28 report).",
    )
    parser.add_argument(
        "--objects",
        type=Path,
        help="Directory containing the COFF objects named by the coverage report.",
    )
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")
    repo = args.repo.resolve()
    original = args.reference.read_bytes()
    if sha256(original) != EXPECTED_ASI_SHA256:
        raise ValueError("reference ASI SHA-256 does not match the pinned original")

    parse_path = repo / "scripts" / "audit-inplace-candidate-relocations.py"
    spec = importlib.util.spec_from_file_location("inplace_candidate_relocations", parse_path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot load COFF parser: {parse_path}")
    parser_module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(parser_module)

    pe = struct.unpack_from("<I", original, 0x3C)[0]
    if original[pe : pe + 4] != b"PE\0\0":
        raise ValueError("reference is not a valid PE image")
    section_count = struct.unpack_from("<H", original, pe + 6)[0]
    optional_size = struct.unpack_from("<H", original, pe + 20)[0]
    optional = pe + 24
    if struct.unpack_from("<H", original, optional)[0] != 0x10B:
        raise ValueError("expected PE32")
    image_base = struct.unpack_from("<I", original, optional + 28)[0]
    section_table = optional + optional_size
    text_range = None
    for index in range(section_count):
        at = section_table + index * 40
        name = original[at : at + 8].split(b"\0", 1)[0]
        virtual_size, rva, raw_size, raw_offset = struct.unpack_from("<IIII", original, at + 8)
        if name == b".text":
            text_range = (image_base + rva, raw_size, raw_offset)
            break
    if text_range is None:
        raise ValueError(".text section not found")
    text_va, text_raw_size, text_raw = text_range

    report_path = args.coverage_report or (
        repo / "audit" / "inplace-candidate-relocation-coverage-current-2026-09-28.json"
    )
    objects_dir = args.objects or (
        repo / "build" / "recheck" / "strict-xcode-current-20260928-3"
    )
    report = json.loads(report_path.read_text(encoding="utf-8"))
    candidates = [row for row in report["results"]
                  if row["placement_class"] == "fits-no-coff-relocations"
                  and row["original_highlow_overlap_count"] == 0]
    results = []
    for row in candidates:
        entry = int(row["entry_va"], 16)
        size = int(row["candidate_body_size"])
        relative = entry - text_va
        if relative < 0 or relative + size > text_raw_size:
            raise ValueError(f"{entry:#x}: candidate does not fit original initialized .text")
        original_body = original[text_raw + relative : text_raw + relative + size]
        object_path = objects_dir / f"{entry:08x}.obj"
        candidate_body, info = parser_module.parse_coff(object_path, row["symbol"])
        if len(candidate_body) != size or info["object_sha256"] != row["object_sha256"]:
            raise ValueError(f"{entry:#x}: object disagrees with current placement report")
        if info["relocations"]:
            raise ValueError(f"{entry:#x}: expected no candidate COFF relocations")
        mismatch_offsets = [i for i, (left, right) in enumerate(zip(original_body, candidate_body))
                            if left != right]
        results.append({
            "entry_va": row["entry_va"],
            "symbol": row["symbol"],
            "body_size": size,
            "object_sha256": info["object_sha256"],
            "original_body_sha256": sha256(original_body),
            "candidate_body_sha256": sha256(candidate_body),
            "exact_byte_match": not mismatch_offsets,
            "mismatch_offsets": mismatch_offsets,
        })

    report_out = {
        "scope": "full byte comparison for every body-fit candidate with zero COFF relocations and zero original HIGHLOW overlap; not semantic/runtime validation",
        "reference_sha256": sha256(original),
        "candidate_count": len(results),
        "exact_byte_match_count": sum(row["exact_byte_match"] for row in results),
        "different_byte_count": sum(not row["exact_byte_match"] for row in results),
        "results": results,
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report_out, stream, indent=2)
        stream.write("\n")
    print(json.dumps({key: value for key, value in report_out.items() if key != "results"}, indent=2))
    for row in results:
        print(f"{row['entry_va']} {row['symbol']}: {'EXACT' if row['exact_byte_match'] else 'DIFFERENT'} ({row['body_size']} bytes)")
    print(f"report={args.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
