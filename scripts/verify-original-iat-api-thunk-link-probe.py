#!/usr/bin/env python3
"""Verify linked API thunks preserve original .rdata offsets and HIGHLOWs."""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import struct
from pathlib import Path

import pefile


EXPECTED_ORIGINAL_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"
IMAGE_REL_BASED_HIGHLOW = 3


def section(image: pefile.PE, name: bytes):
    found = [item for item in image.sections if item.Name.rstrip(b"\0") == name]
    if len(found) != 1:
        raise ValueError(f"expected exactly one {name.decode()} section")
    return found[0]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--probe", type=Path, required=True)
    parser.add_argument("--map", type=Path, required=True)
    parser.add_argument("--original", type=Path, required=True)
    parser.add_argument("--crosswalk", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")

    original_bytes = args.original.read_bytes()
    original_hash = hashlib.sha256(original_bytes).hexdigest().upper()
    if original_hash != EXPECTED_ORIGINAL_SHA256:
        raise ValueError("original ASI hash does not match the pinned input")
    original = pefile.PE(data=original_bytes, fast_load=True)
    linked = pefile.PE(str(args.probe), fast_load=False)
    original_rdata = section(original, b".rdata")
    linked_rdata = section(linked, b".rdata")
    map_text = args.map.read_text(encoding="utf-8", errors="replace")
    crosswalk = json.loads(args.crosswalk.read_text(encoding="utf-8"))
    rows = [row for row in crosswalk["imports"] if row["status"] == "exact-original-iat-match"]
    highlow_sites = {
        entry.rva
        for block in getattr(linked, "DIRECTORY_ENTRY_BASERELOC", [])
        for entry in block.entries
        if entry.type == IMAGE_REL_BASED_HIGHLOW
    }
    results = []
    for row in rows:
        code_symbol = row["coff_code_symbol"]
        api, stack = code_symbol[1:].rsplit("@", 1)
        thunk_symbol = f"IVF_API_CALL_{api}_{stack}"
        thunk_match = re.search(
            rf"\b{re.escape(thunk_symbol)}\s+([0-9A-Fa-f]{{8}})\s+f\s+x86_original_iat_api_thunks\.obj\b",
            map_text,
        )
        imp_symbol = "__imp_" + code_symbol
        imp_match = re.search(
            rf"\b{re.escape(imp_symbol)}\s+([0-9A-Fa-f]{{8}})\s+original-iat-data-provider\.obj\b",
            map_text,
        )
        if not thunk_match or not imp_match:
            raise ValueError(f"link map is missing {thunk_symbol} or {imp_symbol}")
        thunk_va = int(thunk_match.group(1), 16)
        linked_iat_va = int(imp_match.group(1), 16)
        thunk_rva = thunk_va - linked.OPTIONAL_HEADER.ImageBase
        code = linked.get_data(thunk_rva, 6)
        if len(code) != 6 or code[:2] != b"\xFF\x25":
            raise ValueError(f"linked bytes are not an indirect JMP for {thunk_symbol}: {code.hex()}")
        encoded_target = struct.unpack_from("<I", code, 2)[0]
        original_iat_va = int(row["iat_va"], 16)
        original_rdata_va = original.OPTIONAL_HEADER.ImageBase + original_rdata.VirtualAddress
        linked_rdata_va = linked.OPTIONAL_HEADER.ImageBase + linked_rdata.VirtualAddress
        original_offset = original_iat_va - original_rdata_va
        linked_offset = linked_iat_va - linked_rdata_va
        fixup_rva = thunk_rva + 2
        if encoded_target != linked_iat_va:
            raise ValueError(f"linked thunk operand does not target its IAT symbol: {thunk_symbol}")
        if original_offset != linked_offset:
            raise ValueError(f"linked IAT alias moved from the original .rdata offset: {imp_symbol}")
        if fixup_rva not in highlow_sites:
            raise ValueError(f"missing HIGHLOW base relocation at {fixup_rva:#x} for {thunk_symbol}")
        results.append({
            "code_symbol_crosswalk": code_symbol,
            "unique_thunk_symbol": thunk_symbol,
            "thunk_va_in_probe": f"0x{thunk_va:08X}",
            "linked_iat_symbol": imp_symbol,
            "original_iat_va": f"0x{original_iat_va:08X}",
            "linked_iat_va_in_probe": f"0x{linked_iat_va:08X}",
            "original_and_linked_rdata_offset": f"0x{original_offset:04X}",
            "thunk_bytes": code.hex(" ").upper(),
            "highlow_site_rva": f"0x{fixup_rva:08X}",
        })

    if len(results) != crosswalk["candidate_direct_api_symbol_count"]:
        raise ValueError("crosswalk and linked thunk counts differ")
    if not linked.OPTIONAL_HEADER.DllCharacteristics & 0x40:
        raise ValueError("probe image is not marked DYNAMICBASE")
    report = {
        "scope": "Isolated diagnostic DLL only: verifies section-relative IAT aliases, exact indirect-JMP encoding, and loader HIGHLOW sites. It does not bind candidate calls or represent a production ImVehFt PE/ASI.",
        "original_asi": str(args.original.resolve()),
        "original_sha256": original_hash,
        "probe": str(args.probe.resolve()),
        "probe_sha256": hashlib.sha256(args.probe.read_bytes()).hexdigest().upper(),
        "link_map": str(args.map.resolve()),
        "candidate_symbol_crosswalk": str(args.crosswalk.resolve()),
        "thunk_count": len(results),
        "correct_section_offset_count": len(results),
        "highlow_fixup_count": len(results),
        "results": results,
        "limitations": [
            "Probe .text/.rdata RVAs differ from the original ASI; only each IAT symbol's offset within .rdata is compared.",
            "The 705 candidate call relocations are not redirected to these unique thunk symbols by the ordinary diagnostic linker.",
            "No final PE layout, production import directory, loader execution, or GTA runtime test is produced.",
        ],
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({key: report[key] for key in (
        "thunk_count", "correct_section_offset_count", "highlow_fixup_count",
    )}, indent=2))
    print(f"report={args.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
