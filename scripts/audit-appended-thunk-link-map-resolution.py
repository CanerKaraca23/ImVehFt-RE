#!/usr/bin/env python3
"""Join thunk-body undefined COFF targets to a successful diagnostic linker map."""

from __future__ import annotations

import argparse
import hashlib
import json
import re
from collections import Counter
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_RELOCS = ROOT / "audit/appended-thunk-relocation-targets-v2-2026-09-29.json"
DEFAULT_MAP = ROOT / "build/link-probe/entry-current-1001c5b8-1001cb37-20260929/ImVehFt-current-boundary-check-not-ASI.map"
DEFAULT_IMAGE = ROOT / "build/link-probe/entry-current-1001c5b8-1001cb37-20260929/ImVehFt-current-boundary-check-not-ASI.dll"
SECTION_LINE = re.compile(r"^\s*([0-9A-Fa-f]{4}):([0-9A-Fa-f]{8})\s+([0-9A-Fa-f]{8})H?\s+(\S+)\s+(\S+)")
SYMBOL_LINE = re.compile(r"^\s*([0-9A-Fa-f]{4}):([0-9A-Fa-f]{8})\s+(\S+)\s+([0-9A-Fa-f]{8})(?:\s+f)?(?:\s+(.*))?$")
ENCODED_VA = re.compile(r"(?:PTR_)?DAT_([0-9A-Fa-f]{8})", re.IGNORECASE)


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--relocations", type=Path, default=DEFAULT_RELOCS)
    p.add_argument("--map", type=Path, default=DEFAULT_MAP)
    p.add_argument("--image", type=Path, default=DEFAULT_IMAGE)
    p.add_argument("--extra-relocations", type=Path, action="append", default=[],
                   help="additional JSON containing sections[].relocations with undefined-external targets")
    p.add_argument("--output", type=Path, required=True)
    a = p.parse_args()
    if a.output.exists():
        raise FileExistsError(f"refusing to overwrite {a.output}")
    relocation_bytes = a.relocations.read_bytes()
    map_bytes = a.map.read_bytes()
    image_bytes = a.image.read_bytes()
    relocations = json.loads(relocation_bytes)
    map_text = map_bytes.decode("utf-8", errors="replace")
    nt = int.from_bytes(image_bytes[0x3C:0x40], "little")
    if image_bytes[nt:nt + 4] != b"PE\0\0":
        raise ValueError("diagnostic image has no PE signature")
    nsects = int.from_bytes(image_bytes[nt + 6:nt + 8], "little")
    opt_size = int.from_bytes(image_bytes[nt + 20:nt + 22], "little")
    opt = nt + 24
    image_base = int.from_bytes(image_bytes[opt + 28:opt + 32], "little")
    sect_table = opt + opt_size
    pe_sections = []
    for i in range(nsects):
        at = sect_table + i * 40
        name = image_bytes[at:at + 8].split(b"\0", 1)[0].decode("ascii", errors="replace")
        virtual_size = int.from_bytes(image_bytes[at + 8:at + 12], "little")
        rva = int.from_bytes(image_bytes[at + 12:at + 16], "little")
        raw_size = int.from_bytes(image_bytes[at + 16:at + 20], "little")
        pe_sections.append({"name": name, "start": image_base + rva,
                            "end": image_base + rva + max(virtual_size, raw_size)})

    segments: dict[str, dict[str, str]] = {}
    symbols: dict[str, list[dict[str, str]]] = {}
    for line in map_text.splitlines():
        section_match = SECTION_LINE.match(line)
        if section_match:
            seg, _, _, section, section_class = section_match.groups()
            segments[seg.upper()] = {"section": section, "class": section_class}
            continue
        symbol_match = SYMBOL_LINE.match(line)
        if not symbol_match:
            continue
        seg, offset, name, address, tail = symbol_match.groups()
        segment = segments.get(seg.upper(), {})
        symbols.setdefault(name, []).append({
            "va": f"0x{int(address, 16):08X}", "segment": seg.upper(),
            "segment_offset": f"0x{int(offset, 16):08X}",
            "section": segment.get("section", "unknown"),
            "section_class": segment.get("class", "unknown"),
            "module": (tail or "").strip(),
        })

    occurrences: Counter[tuple[str, str]] = Counter()
    for row in relocations["relocations"]:
        if row["target_class"] == "unresolved-external-or-alias":
            occurrences[(str(row["type"]), str(row["target_symbol"]))] += 1
    extra_hashes = []
    for extra_path in a.extra_relocations:
        extra_bytes = extra_path.read_bytes()
        extra_hashes.append({"path": str(extra_path.resolve()), "sha256": sha256(extra_bytes)})
        extra = json.loads(extra_bytes)
        for section in extra.get("sections", []):
            for row in section.get("relocations", []):
                if row.get("target_class") == "undefined-external":
                    occurrences[(str(row["type"]), str(row["target_symbol"]))] += 1

    unique_rows = []
    class_occurrences: Counter[str] = Counter()
    class_symbols: Counter[str] = Counter()
    for (kind, name), count in sorted(occurrences.items()):
        matches = symbols.get(name, [])
        encoded = ENCODED_VA.search(name)
        encoded_va = int(encoded.group(1), 16) if encoded else None
        if not matches:
            classification = "not-found-by-exact-name-in-diagnostic-map"
        elif encoded_va is not None and any(int(row["va"], 16) == encoded_va for row in matches):
            classification = "map-address-matches-address-encoded-in-symbol"
        elif encoded_va is not None:
            classification = "diagnostic-map-displaces-address-encoded-in-symbol"
        elif name.startswith("__imp_"):
            classification = "diagnostic-import-slot"
        elif all(next((section["name"] for section in pe_sections
                       if section["start"] <= int(row["va"], 16) < section["end"]), "unmapped") in {".xcode", ".text"}
                 for row in matches):
            classification = "diagnostic-code-symbol"
        else:
            classification = "diagnostic-provider-or-runtime-data"
        class_occurrences[classification] += count
        class_symbols[classification] += 1
        unique_rows.append({
            "relocation_type": kind, "symbol": name, "occurrences": count,
            "address_encoded_in_symbol": f"0x{encoded_va:08X}" if encoded_va is not None else None,
            "classification": classification, "map_matches": matches,
        })

    report = {
        "scope": "Exact-name join between undefined symbols in appended-body COFF relocations and the successful diagnostic map. Diagnostic addresses are not treated as final production addresses.",
        "relocation_report": str(a.relocations.resolve()),
        "relocation_report_sha256": sha256(relocation_bytes),
        "link_map": str(a.map.resolve()),
        "link_map_sha256": sha256(map_bytes),
        "diagnostic_image": str(a.image.resolve()),
        "diagnostic_image_sha256": sha256(image_bytes),
        "additional_relocation_inputs": extra_hashes,
        "unique_undefined_symbol_type_pairs": len(unique_rows),
        "undefined_relocation_occurrences": sum(occurrences.values()),
        "occurrences_by_map_class": dict(sorted(class_occurrences.items())),
        "unique_symbols_by_map_class": dict(sorted(class_symbols.items())),
        "limitations": [
            "This proves only diagnostic-link symbol resolution, not correct placement/addressing in the original ImVehFt image.",
            "Names encoding original VAs are compared to those values; a displaced diagnostic provider does not prove the final VA fixup is correct.",
            "Import names are not crosswalked to original PE IAT slot RVAs in this report.",
            "No bytes are modified and no PE/ASI is produced.",
        ],
        "symbols": unique_rows,
    }
    a.output.parent.mkdir(parents=True, exist_ok=True)
    a.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({k: report[k] for k in (
        "unique_undefined_symbol_type_pairs", "undefined_relocation_occurrences",
        "occurrences_by_map_class", "unique_symbols_by_map_class"
    )}, indent=2))
    print(f"report={a.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
