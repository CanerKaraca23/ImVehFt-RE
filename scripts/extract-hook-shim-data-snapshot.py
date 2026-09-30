#!/usr/bin/env python3
"""Extract PE startup bytes for data addresses referenced by recovered hook shims."""

from __future__ import annotations

import argparse
import csv
import struct
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def read_pe(path: Path) -> tuple[int, bytes, list[dict[str, int | str]]]:
    image = path.read_bytes()
    if image[:2] != b"MZ":
        raise ValueError(f"Not an MZ image: {path}")
    pe = struct.unpack_from("<I", image, 0x3C)[0]
    if image[pe : pe + 4] != b"PE\0\0":
        raise ValueError(f"Missing PE signature: {path}")
    machine, section_count = struct.unpack_from("<HH", image, pe + 4)
    optional_size = struct.unpack_from("<H", image, pe + 20)[0]
    if machine != 0x14C:
        raise ValueError(f"Expected x86 PE, found machine {machine:#x}")
    optional = pe + 24
    if struct.unpack_from("<H", image, optional)[0] != 0x10B:
        raise ValueError("Expected PE32 optional header")
    image_base = struct.unpack_from("<I", image, optional + 28)[0]
    section_table = optional + optional_size
    sections: list[dict[str, int | str]] = []
    for index in range(section_count):
        offset = section_table + index * 40
        name = image[offset : offset + 8].split(b"\0", 1)[0].decode("ascii")
        virtual_size, rva, raw_size, raw_offset = struct.unpack_from(
            "<IIII", image, offset + 8
        )
        sections.append(
            {
                "name": name,
                "virtual_size": virtual_size,
                "rva": rva,
                "raw_size": raw_size,
                "raw_offset": raw_offset,
            }
        )
    return image_base, image, sections


def snapshot(
    image: bytes,
    image_base: int,
    sections: list[dict[str, int | str]],
    address: int,
    length: int,
) -> tuple[str, str, str, str]:
    rva = address - image_base
    for section in sections:
        delta = rva - int(section["rva"])
        extent = max(int(section["virtual_size"]), int(section["raw_size"]))
        if delta < 0 or delta >= extent:
            continue
        count = min(length, extent - delta)
        file_count = max(0, min(count, int(section["raw_size"]) - delta))
        offset = int(section["raw_offset"]) + delta
        data = image[offset : offset + file_count] + bytes(count - file_count)
        return (
            str(section["name"]),
            f"0x{offset:08X}" if file_count else "",
            data.hex(" ").upper(),
            f"{file_count}/{count}",
        )
    raise ValueError(f"Address {address:#010x} does not map to a PE section")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--asi",
        type=Path,
        default=Path(
            r"C:\Users\caner\OneDrive\Documents\GTA San Andreas\modloader\My Scripts\.ImVehFt\ImVehFt.asi"
        ),
    )
    parser.add_argument(
        "--manifest",
        type=Path,
        default=ROOT / "audit/hook-shim-fixups-2026-09-27.json",
    )
    parser.add_argument(
        "--references",
        type=Path,
        default=ROOT / "audit/hook-shim-external-reference-inventory-2026-09-27.csv",
    )
    parser.add_argument(
        "--xrefs",
        type=Path,
        default=ROOT / "audit/hook-shim-ghidra-symbol-xrefs-2026-09-27.csv",
    )
    parser.add_argument(
        "--source-root", type=Path, default=ROOT / "src/functions"
    )
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--bytes", type=int, default=16)
    args = parser.parse_args()
    if args.bytes < 1 or args.bytes > 64:
        parser.error("--bytes must be between 1 and 64")

    image_base, image, sections = read_pe(args.asi)
    with args.manifest.open(encoding="utf-8") as stream:
        manifest = __import__("json").load(stream)
    with args.references.open(encoding="utf-8-sig", newline="") as stream:
        references = {row["address"].lower(): row for row in csv.DictReader(stream)}
    with args.xrefs.open(encoding="utf-8-sig", newline="") as stream:
        xrefs = {
            row["address"].lower(): row
            for row in csv.DictReader(stream)
        }
    source_files = sorted(args.source_root.glob("*.cpp"))
    source_text = {
        path.name: path.read_text(encoding="utf-8", errors="replace").lower()
        for path in source_files
    }

    addresses = sorted(
        {
            item["original_target"].lower()
            for item in manifest["fixups"]
            if item["kind"]
            in {"absolute-image-memory-reference", "absolute-image-pointer-immediate"}
        },
        key=lambda value: int(value, 16),
    )
    args.output.parent.mkdir(parents=True, exist_ok=True)
    fields = [
        "address",
        "section",
        "classification",
        "candidate_global_names",
        "ghidra_symbols",
        "data_or_code_unit",
        "candidate_source_identifier_hits",
        "candidate_source_files_with_address_or_alias",
        "reference_count",
        "targets",
        "reference_sites",
        "incoming_references",
        "file_offset",
        "initial_bytes_hex",
        "file_backed_bytes",
    ]
    with args.output.open("w", encoding="utf-8", newline="") as stream:
        writer = csv.DictWriter(stream, fieldnames=fields)
        writer.writeheader()
        for address in addresses:
            ref = references.get(address, {})
            xref = xrefs.get(address.removeprefix("0x"), {})
            aliases = [
                alias.lower()
                for alias in ref.get("ghidra_aliases", "").split("|")
                if alias
            ]
            aliases.extend([address.lower(), address.removeprefix("0x").lower()])
            identifier_hits = sorted(
                {
                    alias
                    for alias in aliases
                    if any(alias in text for text in source_text.values())
                }
            )
            source_hits = [
                name
                for name, text in source_text.items()
                if any(alias in text for alias in aliases)
            ]
            section, offset, raw, backed = snapshot(
                image, image_base, sections, int(address, 16), args.bytes
            )
            writer.writerow(
                {
                    "address": address,
                    "section": section,
                    "classification": ref.get("classification", "unclassified"),
                    "candidate_global_names": ref.get("candidate_global_names", ""),
                    "ghidra_symbols": xref.get("symbols", ""),
                    "data_or_code_unit": xref.get("data_or_code_unit", ""),
                    "candidate_source_identifier_hits": "|".join(identifier_hits),
                    "candidate_source_files_with_address_or_alias": "|".join(source_hits),
                    "reference_count": ref.get("reference_count", ""),
                    "targets": ref.get("targets", ""),
                    "reference_sites": ref.get("reference_sites", ""),
                    "incoming_references": xref.get("incoming_references", ""),
                    "file_offset": offset,
                    "initial_bytes_hex": raw,
                    "file_backed_bytes": backed,
                }
            )
    print(
        f"image_base=0x{image_base:08X} referenced_data_addresses={len(addresses)} "
        f"output={args.output}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
