#!/usr/bin/env python3
"""Plan current 705-set API CALL rel32 fields against a supplied code layout.

This emits a JSON callsite plan only. It does not patch COFF objects, write an
ASI, or serialize a base-relocation directory.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from collections import Counter
from pathlib import Path


PINNED_ASI_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def read(path: Path) -> tuple[bytes, dict]:
    data = path.read_bytes()
    return data, json.loads(data)


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--original", type=Path, required=True)
    p.add_argument("--objects", type=Path, required=True)
    p.add_argument("--candidate-references", type=Path, required=True)
    p.add_argument("--placement-plan", type=Path, required=True)
    p.add_argument("--payload-census", type=Path, required=True)
    p.add_argument("--layout-report", type=Path, required=True)
    p.add_argument("--iat-crosswalk", type=Path, required=True)
    p.add_argument("--thunk-verification", type=Path, required=True)
    p.add_argument("--output", type=Path, required=True)
    a = p.parse_args()
    if a.output.exists():
        raise FileExistsError(f"refusing to overwrite {a.output}")

    original = a.original.read_bytes()
    original_sha = sha(original)
    if original_sha != PINNED_ASI_SHA256:
        raise ValueError(f"original ASI hash mismatch: {original_sha}")
    peoff = struct.unpack_from("<I", original, 0x3C)[0]
    image_base = struct.unpack_from("<I", original, peoff + 24 + 28)[0]

    ref_bytes, refs = read(a.candidate_references)
    plan_bytes, plan = read(a.placement_plan)
    payload_bytes, payload = read(a.payload_census)
    layout_bytes, layout = read(a.layout_report)
    crosswalk_bytes, crosswalk = read(a.iat_crosswalk)
    verify_bytes, verify = read(a.thunk_verification)
    if refs.get("candidate_object_count") != 705 or plan.get("candidate_count") != 705:
        raise ValueError("candidate reference inventory and placement must cover 705 functions")
    thunk_rows = [r for r in plan["entries"] if r["placement_mode"] == "jmp-rel32-thunk"]
    if payload.get("candidate_entries") != 705 or payload.get("thunk_entries") != len(thunk_rows):
        raise ValueError("payload census does not match the current placement")
    if len(payload.get("entries", [])) != len(thunk_rows):
        raise ValueError("payload body rows do not cover every thunked entry")
    code_rva = int(payload["provisional_appended_rva"], 16)
    api_offset = int(layout["api_thunk_payload_offset_in_code_section"])
    prior_end = int(layout["code_bytes_before_bridge_alignment"])
    if int(layout["provisional_appended_rva"], 16) != code_rva:
        raise ValueError("payload and layout disagree on appended code RVA")
    if int(layout["root_code_bytes_with_body_alignment"]) != int(payload["payload_bytes_with_16_byte_body_alignment"]):
        raise ValueError("payload body alignment differs from the layout report")
    if api_offset < int(payload["combined_code_and_rdata_payload_bytes"]):
        raise ValueError("API thunk block overlaps the root code/rdata payload")

    iat = {r["coff_code_symbol"]: r for r in crosswalk["imports"]
           if r.get("status") == "exact-original-iat-match"}
    verified = {r["code_symbol"]: r for r in verify["results"]}
    thunk_count = int(verify.get("thunk_count", -1))
    if (thunk_count <= 0 or verify.get("code_bytes") != thunk_count * 6
            or len(verified) != thunk_count or not verify.get("all_thunks_exact_ff25")
            or set(iat) != set(verified)):
        raise ValueError("the exact IAT mappings and dynamic FF25 thunk verification must agree")
    thunk_bytes = bytearray(int(verify["code_bytes"]))
    thunk_va_by_symbol: dict[str, int] = {}
    thunk_rows_out = []
    for symbol, row in sorted(verified.items(), key=lambda item: int(item[1]["code_offset"], 16)):
        offset = int(row["code_offset"], 16)
        iat_va = int(iat[symbol]["iat_va"], 16)
        if row["bytes"].replace(" ", "").upper() != "FF2500000000":
            raise ValueError(f"non-FF25 template for {symbol}")
        thunk_bytes[offset:offset + 6] = b"\xff\x25" + struct.pack("<I", iat_va)
        thunk_va = image_base + code_rva + api_offset + offset
        thunk_va_by_symbol[symbol] = thunk_va
        thunk_rows_out.append({"symbol": symbol, "iat_va": f"0x{iat_va:08X}",
                               "code_offset": offset, "thunk_va": f"0x{thunk_va:08X}",
                               "bytes": thunk_bytes[offset:offset + 6].hex(" ").upper()})
    if sha(bytes(thunk_bytes)) != layout["api_thunk_payload_sha256_after_iat_fixups"]:
        raise ValueError("reconstructed API thunk bytes differ from the supplied code layout")

    placements = {int(r["address"], 16): r for r in plan["entries"]}
    appended = {int(r["entry_va"], 16): r for r in payload["entries"]}
    patches = []
    modes: Counter[str] = Counter()
    disp_values = []
    for row in refs["rel32_references"]:
        entry = int(row["candidate_entry"], 16)
        place = placements.get(entry)
        if place is None:
            raise ValueError(f"missing placement for {entry:#x}")
        object_path = a.objects / f"{entry:08X}.obj"
        object_hash = sha(object_path.read_bytes())
        if object_hash != row["object_sha256"]:
            raise ValueError(f"stale reference/object hash at {entry:#x}")
        if row["bytes_around_relocation_field"] != "E8 00 00 00 00":
            raise ValueError(f"expected zero-addend CALL rel32 at {entry:#x}")
        symbol = row["target_code_symbol"]
        if symbol not in thunk_va_by_symbol:
            raise ValueError(f"no verified original-IAT thunk for {symbol}")
        site = int(row["relocation_site_offset"], 16)
        if place["placement_mode"] == "body-at-entry":
            callsite_rva = entry - image_base + site
            klass = "in-place-body"
        elif place["placement_mode"] == "jmp-rel32-thunk":
            if entry not in appended:
                raise ValueError(f"no appended payload row for {entry:#x}")
            callsite_rva = code_rva + int(appended[entry]["provisional_payload_offset"]) + site
            klass = "appended-body"
        else:
            raise ValueError(f"unsupported placement mode at {entry:#x}")
        callsite_va = image_base + callsite_rva
        target_va = thunk_va_by_symbol[symbol]
        displacement = target_va - (callsite_va + 4)
        if not -(1 << 31) <= displacement < (1 << 31):
            raise ValueError(f"CALL rel32 out of range at {entry:#x}+{site:#x}")
        modes[klass] += 1
        disp_values.append(displacement)
        patches.append({"candidate_entry": f"0x{entry:08X}", "placement_mode": place["placement_mode"],
                        "callsite_class": klass, "candidate_callsite_rva": f"0x{callsite_rva:08X}",
                        "candidate_callsite_va": f"0x{callsite_va:08X}",
                        "relocation_field_rva": f"0x{callsite_rva:08X}",
                        "target_api_symbol": symbol,
                        "replacement_thunk_symbol": row["replacement_thunk_symbol"],
                        "replacement_thunk_va": f"0x{target_va:08X}",
                        "rel32_displacement": displacement,
                        "rel32_displacement_u32": f"0x{displacement & 0xFFFFFFFF:08X}",
                        "original_instruction": "E8 rel32", "object_sha256": object_hash})

    if len(patches) != refs.get("rel32_reference_count"):
        raise ValueError("not all current API CALL rel32 references were planned")
    report = {
        "scope": "Callsite-only provisional REL32 plan for the current 705-object set; no fixup fields, relocation blob, PE, or ASI is written.",
        "original_sha256": original_sha,
        "candidate_reference_inventory": str(a.candidate_references.resolve()),
        "candidate_reference_sha256": sha(ref_bytes),
        "placement_plan": str(a.placement_plan.resolve()),
        "placement_plan_sha256": sha(plan_bytes),
        "payload_census": str(a.payload_census.resolve()),
        "payload_census_sha256": sha(payload_bytes),
        "layout_report": str(a.layout_report.resolve()),
        "layout_report_sha256": sha(layout_bytes),
        "iat_crosswalk": str(a.iat_crosswalk.resolve()),
        "iat_crosswalk_sha256": sha(crosswalk_bytes),
        "thunk_verification": str(a.thunk_verification.resolve()),
        "thunk_verification_sha256": sha(verify_bytes),
        "candidate_object_directory": str(a.objects.resolve()),
        "candidate_object_count": 705,
        "provisional_appended_section_rva": f"0x{code_rva:08X}",
        "api_thunk_payload_offset": api_offset,
        "api_thunk_payload_bytes": len(thunk_bytes),
        "api_thunk_payload_sha256": sha(bytes(thunk_bytes)),
        "api_thunks": thunk_rows_out,
        "thunks": [
            {"api_code_symbol": row["symbol"], "iat_va": row["iat_va"],
             "thunk_va": row["thunk_va"], "payload_offset": row["code_offset"]}
            for row in thunk_rows_out
        ],
        "candidate_api_rel32_patch_count": len(patches),
        "callsites_by_placement": dict(sorted(modes.items())),
        "rel32_min_displacement": min(disp_values) if disp_values else None,
        "rel32_max_displacement": max(disp_values) if disp_values else None,
        "all_rel32_displacements_in_range": True,
        "rel32_patches": patches,
        "limitations": [
            "The API thunks and CALL displacements are only planned; no COFF bytes are patched.",
            "The provisional code layout is not a final PE section layout; changes require recomputation.",
            "This report does not prove imported API behavior, loader/startup behavior, or GTA gameplay.",
            "Base relocation coverage for API thunk immediates is intentionally not assessed here.",
        ],
    }
    a.output.parent.mkdir(parents=True, exist_ok=True)
    with a.output.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    print(json.dumps({"api_thunk_count": len(thunk_rows_out),
                      "api_callsite_fixups": len(patches),
                      "callsites_by_placement": dict(sorted(modes.items())),
                      "all_rel32_displacements_in_range": True}, indent=2))
    print(f"report={a.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
