#!/usr/bin/env python3
"""Check address-encoded unresolved COFF targets against original PE sections."""

from __future__ import annotations

import argparse
import hashlib
import json
from collections import Counter
from pathlib import Path

import pefile


PINNED_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--symbols", type=Path, required=True,
                        help="appended-thunk-link-map-resolution JSON")
    parser.add_argument("--original", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")

    image = args.original.read_bytes()
    image_sha = hashlib.sha256(image).hexdigest().upper()
    if image_sha != PINNED_SHA256:
        raise ValueError(f"pinned original hash mismatch: {image_sha}")
    pe = pefile.PE(data=image, fast_load=True)
    image_base = pe.OPTIONAL_HEADER.ImageBase
    section_metadata = {}
    for section in pe.sections:
        name = section.Name.rstrip(b"\0").decode("ascii", errors="replace")
        section_metadata[name] = {
            "virtual_address": f"0x{section.VirtualAddress:08X}",
            "virtual_size": f"0x{section.Misc_VirtualSize:08X}",
            "raw_offset": f"0x{section.PointerToRawData:08X}",
            "raw_size": f"0x{section.SizeOfRawData:08X}",
            "characteristics": f"0x{section.Characteristics:08X}",
        }
    rows = json.loads(args.symbols.read_text(encoding="utf-8"))["symbols"]
    targets = [row for row in rows if row.get("address_encoded_in_symbol")]
    counts: Counter[tuple[str, str]] = Counter()
    unmapped: list[dict[str, object]] = []
    mapped_rows = []
    for row in targets:
        va = int(row["address_encoded_in_symbol"], 16)
        rva = va - image_base
        section = next((s for s in pe.sections
                        if s.VirtualAddress <= rva < s.VirtualAddress + max(s.Misc_VirtualSize, s.SizeOfRawData)), None)
        if section is None:
            unmapped.append({"symbol": row["symbol"], "va": row["address_encoded_in_symbol"],
                             "occurrences": row["occurrences"]})
            continue
        name = section.Name.rstrip(b"\0").decode("ascii", errors="replace")
        delta = rva - section.VirtualAddress
        backing = "raw-backed" if delta < section.SizeOfRawData else "virtual-only"
        counts[(name, backing)] += int(row["occurrences"])
        mapped_rows.append({"symbol": row["symbol"], "va": row["address_encoded_in_symbol"],
                            "section": name, "section_offset": f"0x{delta:08X}",
                            "backing": backing, "occurrences": row["occurrences"]})

    report = {
        "scope": "Checks only the original-VA addresses encoded in symbols from the diagnostic relocation crosswalk; does not patch or validate runtime data semantics.",
        "symbols_report": str(args.symbols.resolve()),
        "original_image": str(args.original.resolve()),
        "original_sha256": image_sha,
        "image_base": f"0x{image_base:08X}",
        "target_section_headers": {name: section_metadata[name]
                                    for name in (".rdata", ".data") if name in section_metadata},
        "encoded_symbol_count": len(targets),
        "encoded_reference_occurrences": sum(int(row["occurrences"]) for row in targets),
        "occurrences_by_original_section_and_backing": {
            f"{name}:{backing}": count for (name, backing), count in sorted(counts.items())
        },
        "unmapped_symbol_count": len(unmapped),
        "unmapped_occurrences": sum(int(row["occurrences"]) for row in unmapped),
        "unmapped": unmapped,
        "mapped_targets": mapped_rows,
        "limitations": [
            "A section-mapped VA is not proof that the target has the required type, initialization, or lifetime.",
            "Virtual-only .data addresses have no raw file bytes and depend on PE zero-fill and later initialization.",
            "No candidate fixup was applied and no production PE/ASI or GTA runtime behavior was tested.",
        ],
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({key: report[key] for key in (
        "encoded_symbol_count", "encoded_reference_occurrences",
        "occurrences_by_original_section_and_backing", "unmapped_symbol_count",
        "unmapped_occurrences")}, indent=2))
    print(f"report={args.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
