#!/usr/bin/env python3
"""Crosswalk diagnostic provider aliases to original preferred-base PE VAs."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import re
from pathlib import Path

import pefile


PINNED_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"


def csv_by_symbol(path: Path) -> dict[str, dict[str, str]]:
    with path.open("r", encoding="utf-8-sig", newline="") as stream:
        rows = list(csv.DictReader(stream))
    result = {row["symbol"]: row for row in rows if row.get("symbol")}
    if len(result) != len([row for row in rows if row.get("symbol")]):
        raise ValueError(f"duplicate symbols in {path}")
    return result


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--symbols", type=Path, required=True)
    parser.add_argument("--original", type=Path, required=True)
    parser.add_argument("--vftable-crosswalk", type=Path, required=True)
    parser.add_argument("--clean-aliases", type=Path, required=True)
    parser.add_argument("--cinit-aliases", type=Path, required=True)
    parser.add_argument("--relocation-aliases", type=Path)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")

    image = args.original.read_bytes()
    image_sha = hashlib.sha256(image).hexdigest().upper()
    if image_sha != PINNED_SHA256:
        raise ValueError(f"pinned original hash mismatch: {image_sha}")
    pe = pefile.PE(data=image, fast_load=True)
    base = pe.OPTIONAL_HEADER.ImageBase
    sections = []
    for section in pe.sections:
        name = section.Name.rstrip(b"\0").decode("ascii", errors="replace")
        sections.append({
            "name": name,
            "rva": int(section.VirtualAddress),
            "virtual_size": int(section.Misc_VirtualSize),
            "raw_size": int(section.SizeOfRawData),
        })

    report_bytes = args.symbols.read_bytes()
    symbol_report = json.loads(report_bytes)
    rows = [row for row in symbol_report["symbols"]
            if row.get("classification") == "diagnostic-provider-or-runtime-data"]
    vftables = csv_by_symbol(args.vftable_crosswalk)
    clean_aliases = csv_by_symbol(args.clean_aliases)
    cinit_aliases = csv_by_symbol(args.cinit_aliases)
    relocation_aliases = (
        csv_by_symbol(args.relocation_aliases) if args.relocation_aliases else {}
    )
    if args.relocation_aliases:
        alias_report_path = args.relocation_aliases.with_suffix(".json")
        alias_report = json.loads(alias_report_path.read_text(encoding="utf-8"))
        if alias_report.get("image_sha256", "").upper() != image_sha:
            raise ValueError("relocation-alias inventory was derived from a different original image")
        if int(alias_report.get("alias_count", -1)) != len(relocation_aliases):
            raise ValueError("relocation-alias inventory count does not match its audit report")
    mapped = []
    unmapped = []
    for row in rows:
        symbol = str(row["symbol"])
        module = str(row.get("map_matches", [{}])[0].get("module", ""))
        evidence = ""
        if module.startswith("callback-vftable-crosswalk-provider-"):
            source = vftables.get(symbol)
            if source is None:
                unmapped.append({"symbol": symbol, "reason": "no exact symbol in Ghidra vftable crosswalk"})
                continue
            va = int(source["address"], 16)
            evidence = "exact vftable symbol/address crosswalk"
        elif module.startswith("current-clean-link-address-alias-provider-"):
            source = clean_aliases.get(symbol)
            if source is None:
                unmapped.append({"symbol": symbol, "reason": "no exact symbol in PE address-alias inventory"})
                continue
            va = int(source["address"], 16)
            evidence = "exact decorated symbol/address PE alias inventory"
        elif module.startswith("current-cinit-stdcall-unresolved-data-aliases-"):
            source = cinit_aliases.get(symbol)
            if source:
                va = int(source["address"], 16)
                evidence = "exact cinit symbol/address inventory"
            else:
                match = re.search(r"(100[0-9A-Fa-f]{5})(?=$|@@)", symbol)
                if not match:
                    unmapped.append({"symbol": symbol, "reason": "no exact cinit alias or encoded VA"})
                    continue
                va = int(match.group(1), 16)
                evidence = "original preferred-base VA encoded in cinit alias"
        elif module.startswith("reloc-aware-dat-provider-"):
            match = re.search(r"IVF_RELOC_TARGET_(100[0-9A-Fa-f]{5})$", symbol)
            if not match:
                unmapped.append({"symbol": symbol, "reason": "relocation-target alias lacks original VA"})
                continue
            va = int(match.group(1), 16)
            evidence = "original preferred-base target encoded in generated relocation alias"
        elif module.startswith("seh-frame-fix-diagnostic-aliases-"):
            source = relocation_aliases.get(symbol)
            if source is None:
                unmapped.append({"symbol": symbol, "reason": "no exact symbol in pinned relocation-alias inventory"})
                continue
            va = int(source["address"], 16)
            match = re.search(r"IVF_RELOC_TARGET_(100[0-9A-Fa-f]{5})$", symbol)
            if not match or int(match.group(1), 16) != va:
                unmapped.append({"symbol": symbol, "va": f"0x{va:08X}", "reason": "alias label and audited VA disagree"})
                continue
            evidence = "exact symbol/VA in pinned relocation-alias inventory"
        else:
            unmapped.append({"symbol": symbol, "reason": f"unrecognized provider module {module}"})
            continue

        rva = va - base
        section = next((item for item in sections
                        if item["rva"] <= rva < item["rva"] + max(item["virtual_size"], item["raw_size"])), None)
        if section is None:
            unmapped.append({"symbol": symbol, "va": f"0x{va:08X}", "reason": "VA outside original PE sections"})
            continue
        offset = rva - section["rva"]
        mapped.append({
            "symbol": symbol,
            "occurrences": int(row["occurrences"]),
            "relocation_type": row["relocation_type"],
            "provider_module": module,
            "original_target_va": f"0x{va:08X}",
            "original_section": section["name"],
            "section_offset": f"0x{offset:08X}",
            "backing": "raw-backed" if offset < section["raw_size"] else "virtual-only",
            "resolution_evidence": evidence,
        })

    report = {
        "scope": "Maps only diagnostic provider/runtime-data aliases to original preferred-base addresses using exact crosswalks or generated address-bearing labels, then verifies PE section membership. This does not prove type/lifetime/initialization or apply the fixups.",
        "original_sha256": image_sha,
        "symbol_report": str(args.symbols.resolve()),
        "symbol_report_sha256": hashlib.sha256(report_bytes).hexdigest().upper(),
        "provider_symbol_count": len(rows),
        "provider_occurrences": sum(int(row["occurrences"]) for row in rows),
        "mapped_symbol_count": len(mapped),
        "mapped_occurrences": sum(row["occurrences"] for row in mapped),
        "unmapped_symbol_count": len(unmapped),
        "unmapped_occurrences": sum(
            int(next((row["occurrences"] for row in rows if row["symbol"] == item["symbol"]), 0))
            for item in unmapped
        ),
        "mapped_targets": mapped,
        "unmapped": unmapped,
        "limitations": [
            "Mapped target addresses are not validated for C/C++ type, object lifetime, initializer order, or semantic suitability.",
            "Virtual-only original data requires correct PE zero-fill and startup behavior.",
            "No COFF relocation was patched and no production PE/ASI or game was tested.",
        ],
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({key: report[key] for key in (
        "provider_symbol_count", "provider_occurrences", "mapped_symbol_count",
        "mapped_occurrences", "unmapped_symbol_count", "unmapped_occurrences",
    )}, indent=2))
    print(f"report={args.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
