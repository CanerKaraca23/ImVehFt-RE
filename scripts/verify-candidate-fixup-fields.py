#!/usr/bin/env python3
"""Verify every accounted direct/appended PE fixup against candidate v7 bytes."""
from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path

import pefile

PINNED_ORIGINAL = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"
PINNED_CANDIDATE = "041B0CD18AFF3F7872AA4BC8EA8D1BBA96181B98C8D231D08FC9BBDAED74E320"
LOCAL_FIELDS = {0x5C6A0: 0x1001072A, 0x5C818: 0x1005BB7B, 0x5C81C: 0x1005BB7F}


def sha(blob: bytes) -> str:
    return hashlib.sha256(blob).hexdigest().upper()


def load(path: Path) -> dict:
    return json.loads(path.read_text(encoding="utf-8"))


def as_site(value: int | str) -> int:
    return int(value, 16) if isinstance(value, str) else int(value)


def as_u32(value: int | str) -> int:
    parsed = int(value, 16) if isinstance(value, str) else int(value)
    return parsed & 0xFFFFFFFF


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--original", type=Path, required=True)
    ap.add_argument("--candidate", type=Path, required=True)
    ap.add_argument("--direct-fixups", type=Path, required=True)
    ap.add_argument("--appended-fixups", type=Path, required=True)
    ap.add_argument("--closure-fixups", type=Path, required=True)
    ap.add_argument("--text-report", type=Path, required=True)
    ap.add_argument("--objective-report", type=Path, required=True)
    ap.add_argument("--output", type=Path, required=True)
    args = ap.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")
    original_hash, candidate_hash = sha(args.original.read_bytes()), sha(args.candidate.read_bytes())
    if original_hash != PINNED_ORIGINAL or candidate_hash != PINNED_CANDIDATE:
        raise ValueError("input/or candidate hash differs from the pinned v7 test")
    image = args.candidate.read_bytes()
    pe = pefile.PE(data=image, fast_load=False)
    direct, appended, closure = (load(p) for p in (args.direct_fixups, args.appended_fixups, args.closure_fixups))
    text_report, objective = load(args.text_report), load(args.objective_report)
    if not objective.get("all_raw_sites_accounted") or not objective.get("all_executable_targets_recomputed_and_in_range"):
        raise ValueError("direct COFF relocation coverage report is not fully green")
    if not appended.get("all_raw_addends_matched") or not appended.get("all_computed_values_rederived"):
        raise ValueError("appended payload fixups are not fully rederived")
    if not closure.get("all_raw_addends_matched") or not closure.get("all_values_rederived"):
        raise ValueError("direct closure fixups are not fully rederived")

    candidate_sections = {s.Name.rstrip(b"\0").decode("ascii"): s for s in pe.sections}
    text_sec = candidate_sections[".text"]
    text_raw = image[text_sec.PointerToRawData:text_sec.PointerToRawData + text_sec.SizeOfRawData]
    if sha(text_raw) != text_report["output_text_sha256"]:
        raise ValueError("candidate .text bytes differ from the 284-body/421-thunk manifest")

    groups = []
    for label, rows, site_key, value_key in (
        ("inplace-direct-body", direct["fixups"], "field_rva", "computed_field_value"),
        ("appended-root-and-support", appended["fixups"], "site_rva", "value"),
        ("direct-local-closure", closure["fixups"], "site_rva", "computed_field_value"),
    ):
        fields = []
        for row in rows:
            site, expected = as_site(row[site_key]), as_u32(row[value_key])
            offset = pe.get_offset_from_rva(site)
            actual = struct.unpack_from("<I", image, offset)[0]
            fields.append({"site_rva": site, "expected": expected, "actual": actual})
        groups.append((label, fields))
    groups.append(("late-local-rdata", [
        {"site_rva": site, "expected": expected,
         "actual": struct.unpack_from("<I", image, pe.get_offset_from_rva(site))[0]}
        for site, expected in LOCAL_FIELDS.items()
    ]))

    seen: set[int] = set()
    summaries = []
    mismatch_examples = []
    for label, fields in groups:
        mismatches = []
        for row in fields:
            site = row["site_rva"]
            if site in seen:
                raise ValueError(f"fixup inventories overlap at {site:#x}")
            seen.add(site)
            if row["actual"] != row["expected"]:
                mismatches.append({"rva": hex(site), "expected": hex(row["expected"]),
                                   "actual": hex(row["actual"])})
        summaries.append({"inventory": label, "fields": len(fields), "mismatches": len(mismatches)})
        mismatch_examples.extend(mismatches[:10])
    if mismatch_examples:
        raise ValueError(f"candidate PE fixup field mismatch: {mismatch_examples[:10]}")

    xcode = candidate_sections[".xcode"]
    xcode_bytes = image[xcode.PointerToRawData:xcode.PointerToRawData + 101263]
    if xcode.Misc_VirtualSize != 101263 or xcode_bytes[101243:101247] != bytes.fromhex("33 c0 40 c3"):
        raise ValueError("final .xcode extent/filter helper bytes mismatch")
    # The landing pad is 16 bytes; its sole REL32 call must target the
    # independently pinned body-at-entry _abort candidate at 0x1001705C.
    handler = bytearray.fromhex("8b 65 e8 c7 45 fc fe ff ff ff e8 00 00 00 00 cc")
    handler_va = 0x1005BB7F
    rel32 = 0x1001705C - (handler_va + 16)
    struct.pack_into("<i", handler, 12, rel32)
    if xcode_bytes[101247:101263] != bytes(handler):
        raise ValueError("final .xcode terminate landing-pad helper bytes/call mismatch")
    if candidate_sections[".xrdata"].Misc_VirtualSize != 3490:
        raise ValueError("candidate .xrdata size differs from current audited layout")

    report = {
        "scope": "Byte-level final-PE check of all inventoried code/data fixups; not semantic/runtime/game proof.",
        "original_sha256": original_hash, "candidate_sha256": candidate_hash,
        "direct_text_sha256_matches_manifest": True,
        "fixup_inventories": summaries,
        "unique_fixup_fields_checked": len(seen),
        "field_value_mismatches": 0,
        "local_terminate_helpers_match_expected_bytes": True,
        "all_input_fixup_manifests_report_rederived_addends_and_values": True,
        "limitations": ["Static fixup target values do not prove semantic correctness of all targets.",
                        "Imports, CRT/DllMain execution, plugin loading, GTA, and gameplay were not tested."],
    }
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(report, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
