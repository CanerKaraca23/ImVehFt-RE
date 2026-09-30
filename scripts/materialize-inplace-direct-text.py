#!/usr/bin/env python3
"""Patch copied .text bytes with the direct bodies and verified raw-COFF fixups."""

from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
import struct
from pathlib import Path


PINNED_ASI = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"
IMAGE_BASE = 0x10000000
PARSER = Path(__file__).resolve().with_name("audit-inplace-candidate-relocations.py")


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def parse_pe(data: bytes) -> tuple[int, list[dict[str, int | str]]]:
    if data[:2] != b"MZ":
        raise ValueError("reference is not PE")
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    if data[pe:pe + 4] != b"PE\0\0":
        raise ValueError("bad PE signature")
    count = struct.unpack_from("<H", data, pe + 6)[0]
    optional_size = struct.unpack_from("<H", data, pe + 20)[0]
    optional = pe + 24
    image_base = struct.unpack_from("<I", data, optional + 28)[0]
    table = optional + optional_size
    sections = []
    for i in range(count):
        at = table + i * 40
        name = data[at:at + 8].split(b"\0", 1)[0].decode("ascii")
        vsize, rva, raw_size, raw = struct.unpack_from("<IIII", data, at + 8)
        sections.append({"name": name, "virtual_size": vsize, "rva": rva,
                         "raw_size": raw_size, "raw_offset": raw})
    return image_base, sections


def load_parser():
    spec = importlib.util.spec_from_file_location("candidate_coff_parser", PARSER)
    if spec is None or spec.loader is None:
        raise RuntimeError("cannot load existing COFF parser")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module.parse_coff


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--original-asi", required=True, type=Path)
    ap.add_argument("--placement-plan", required=True, type=Path)
    ap.add_argument("--direct-fixups", required=True, type=Path)
    ap.add_argument("--objects-directory", required=True, type=Path)
    ap.add_argument("--direct-body-audit", required=True, type=Path)
    ap.add_argument("--output-text", required=True, type=Path)
    ap.add_argument("--output-report", required=True, type=Path)
    args = ap.parse_args()
    for out in (args.output_text, args.output_report):
        if out.exists():
            raise FileExistsError(f"refusing to overwrite {out}")

    original = args.original_asi.read_bytes()
    if digest(original) != PINNED_ASI:
        raise ValueError("original ASI hash mismatch")
    fix_bytes = args.direct_fixups.read_bytes()
    plan = json.loads(args.placement_plan.read_text(encoding="utf-8"))
    fix_report = json.loads(fix_bytes)
    body_audit = json.loads(args.direct_body_audit.read_text(encoding="utf-8"))
    if body_audit.get("all_source_hashes_match") is not True or body_audit.get("object_hash_mismatch_entries"):
        raise ValueError("authoritative direct-body object audit is not clean")
    if fix_report.get("original_asi_sha256") != PINNED_ASI:
        raise ValueError("direct fixups are not based on pinned original")
    if fix_report.get("placement_plan_sha256") != digest(args.placement_plan.read_bytes()):
        raise ValueError("direct fixup manifest and placement plan do not match")
    if (fix_report.get("all_raw_sites_have_one_unambiguous_target") is not True
            or fix_report.get("all_rel32_in_range") is not True
            or fix_report.get("all_source_objects_match_authoritative_hashes") is not True):
        raise ValueError("direct fixup manifest failed its evidence gates")

    image_base, sections = parse_pe(original)
    if image_base != IMAGE_BASE:
        raise ValueError(f"unexpected image base {image_base:#x}")
    text_section = next(row for row in sections if row["name"] == ".text")
    text_rva, text_raw, text_offset = (int(text_section[k]) for k in ("rva", "raw_size", "raw_offset"))
    text = bytearray(original[text_offset:text_offset + text_raw])
    if len(text) != text_raw:
        raise ValueError("truncated original .text raw section")

    direct = [row for row in plan["entries"] if row["placement_mode"] == "body-at-entry"]
    thunked = [row for row in plan["entries"] if row["placement_mode"] == "jmp-rel32-thunk"]
    if (len(direct), len(thunked), len(plan["entries"])) != (
            fix_report.get("direct_body_count"), plan.get("rel32_thunks_required"), plan.get("candidate_count")):
        raise ValueError("placement plan counts do not match its direct-fixup manifest")
    objects = args.objects_directory
    parse_coff = load_parser()
    occupied: list[tuple[int, int, str]] = []
    body_rows = []
    for row in direct:
        entry_va = int(row["address"], 16)
        rva = entry_va - image_base
        offset = rva - text_rva
        symbol = row["entry_symbol"]
        obj_path = objects / f"{entry_va:08x}.obj"
        body, info = parse_coff(obj_path, symbol)
        if len(body) != int(row["candidate_body_size"]):
            raise ValueError(f"{entry_va:#x}: body size differs from placement plan")
        end = offset + len(body)
        if offset < 0 or end > len(text):
            raise ValueError(f"{entry_va:#x}: body does not fit original .text")
        if any(max(offset, lo) < min(end, hi) for lo, hi, _ in occupied):
            raise ValueError(f"{entry_va:#x}: direct bodies overlap")
        text[offset:end] = body
        occupied.append((offset, end, f"body:{entry_va:#010x}"))
        body_rows.append({"entry_va": f"0x{entry_va:08X}", "symbol": symbol,
                          "text_offset": offset, "body_size": len(body),
                          "object_sha256": info["object_sha256"], "body_sha256": digest(body)})

    fixups_applied = []
    for row in fix_report["fixups"]:
        field_rva_value = row["field_rva"]
        field_rva = int(field_rva_value, 0) if isinstance(field_rva_value, str) else int(field_rva_value)
        offset = field_rva - text_rva
        if offset < 0 or offset + 4 > len(text):
            raise ValueError(f"field RVA {field_rva:#x} is not in original .text")
        owner = int(row["owner_entry_va"], 16)
        owner_offset = owner - image_base - text_rva
        if not any(lo <= owner_offset < hi and lo <= offset and offset + 4 <= hi
                   for lo, hi, _ in occupied):
            raise ValueError(f"fixup {field_rva:#x} does not lie inside its replaced direct body")
        observed = struct.unpack_from("<I", text, offset)[0]
        addend_value = row["raw_addend"]
        addend = int(addend_value, 0) if isinstance(addend_value, str) else int(addend_value)
        if observed != (addend & 0xFFFFFFFF):
            raise ValueError(f"raw addend mismatch at field RVA {field_rva:#x}")
        value_field = row["computed_field_value"]
        value = int(value_field, 0) if isinstance(value_field, str) else int(value_field)
        struct.pack_into("<I", text, offset, value & 0xFFFFFFFF)
        fixups_applied.append(field_rva)
    expected_fixups = fix_report.get("unique_fields")
    if len(fixups_applied) != expected_fixups or len(set(fixups_applied)) != expected_fixups:
        raise ValueError(f"did not apply exactly {expected_fixups} unique direct-body fixups")

    report = {
        "scope": f"Copied original .text with {len(body_rows)} in-place bodies and their {len(fixups_applied)} preferred-base fixups; no entry thunks.",
        "original_asi_sha256": PINNED_ASI,
        "placement_plan_sha256": digest(args.placement_plan.read_bytes()),
        "direct_fixup_manifest_sha256": digest(fix_bytes),
        "direct_body_count": len(body_rows), "thunk_entry_count_not_patched": len(thunked),
        "direct_fixup_count": len(fixups_applied),
        "direct_fixups_by_type": fix_report["counts_by_type"],
        "text_rva": f"0x{text_rva:08X}", "text_raw_bytes": len(text),
        "output_text_sha256": digest(text),
        "limitations": [
            f"{len(thunked)} jmp-rel32 entry windows are not patched in this artifact.",
            "References to appended code/data are not present in this .text-only payload.",
            "This is not a complete PE/ASI and must not be loaded into GTA.",
        ],
        "direct_bodies": body_rows,
    }
    args.output_text.parent.mkdir(parents=True, exist_ok=True)
    with args.output_text.open("xb") as stream:
        stream.write(text)
    args.output_report.parent.mkdir(parents=True, exist_ok=True)
    with args.output_report.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    print(json.dumps({k: report[k] for k in (
        "direct_body_count", "direct_fixup_count", "thunk_entry_count_not_patched",
        "text_raw_bytes", "output_text_sha256"
    )}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
