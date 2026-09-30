#!/usr/bin/env python3
"""Copy COFF objects without CodeView sections and prove code/relocs unchanged."""

from __future__ import annotations

import argparse
import csv
import hashlib
import struct
import subprocess
from pathlib import Path


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def coff(path: Path) -> tuple[dict[str, tuple[bytes, int, list[tuple[int, str, int]]]], list[tuple[str, int, str]]]:
    image = path.read_bytes()
    if len(image) < 20:
        raise ValueError(f"Not a COFF object: {path}")
    machine, section_count = struct.unpack_from("<HH", image, 0)
    if machine != 0x14C:
        raise ValueError(f"Expected x86 COFF in {path}, found machine {machine:#x}")
    symbol_at, symbol_count = struct.unpack_from("<II", image, 8)
    optional_size = struct.unpack_from("<H", image, 16)[0]
    section_table = 20 + optional_size
    string_at = symbol_at + symbol_count * 18
    string_size = struct.unpack_from("<I", image, string_at)[0] if string_at + 4 <= len(image) else 4
    strings = image[string_at : string_at + string_size]

    def string(offset: int) -> str:
        end = strings.find(b"\0", offset)
        if offset < 4 or end < 0:
            raise ValueError(f"Invalid COFF string-table offset in {path}: {offset}")
        return strings[offset:end].decode("utf-8", errors="replace")

    section_names: list[str] = []
    section_rows: list[tuple[int, int, int, int, int, int, int]] = []
    for index in range(section_count):
        at = section_table + index * 40
        raw_name = image[at : at + 8]
        if raw_name.startswith(b"/\0") or raw_name.startswith(b"/"):
            name = string(int(raw_name[1:].split(b"\0", 1)[0]))
        else:
            name = raw_name.split(b"\0", 1)[0].decode("ascii", errors="replace")
        raw_size, raw_at, reloc_at = struct.unpack_from("<III", image, at + 16)
        reloc_count = struct.unpack_from("<H", image, at + 32)[0]
        characteristics = struct.unpack_from("<I", image, at + 36)[0]
        section_names.append(name)
        section_rows.append((raw_size, raw_at, reloc_at, reloc_count, characteristics, at, index + 1))

    symbols: dict[int, tuple[str, int, int, int]] = {}
    defined_externals: list[tuple[str, int, str]] = []
    index = 0
    while index < symbol_count:
        at = symbol_at + index * 18
        raw_name = image[at : at + 8]
        if raw_name[:4] == b"\0\0\0\0":
            name = string(struct.unpack_from("<I", raw_name, 4)[0])
        else:
            name = raw_name.split(b"\0", 1)[0].decode("utf-8", errors="replace")
        value = struct.unpack_from("<I", image, at + 8)[0]
        section_number = struct.unpack_from("<h", image, at + 12)[0]
        symbol_type = struct.unpack_from("<H", image, at + 14)[0]
        storage_class, aux_count = struct.unpack_from("<BB", image, at + 16)
        symbols[index] = (name, value, section_number, symbol_type)
        if storage_class == 2 and 0 < section_number <= len(section_names):
            section_name = section_names[section_number - 1]
            if not section_name.startswith(".debug$"):
                defined_externals.append((name, value, section_name))
        index += 1 + aux_count

    sections: dict[str, tuple[bytes, int, list[tuple[int, str, int]]]] = {}
    for name, (raw_size, raw_at, reloc_at, reloc_count, characteristics, _at, _number) in zip(section_names, section_rows):
        # Uninitialized COFF sections (for example .bss) can report a virtual
        # size while their raw-data pointer is zero; don't hash the file header.
        raw = (
            image[raw_at : raw_at + raw_size]
            if raw_size and raw_at and not (characteristics & 0x00000080)
            else b""
        )
        relocs: list[tuple[int, str, int]] = []
        for rel_index in range(reloc_count):
            va, symbol_index, kind = struct.unpack_from("<IIH", image, reloc_at + rel_index * 10)
            if symbol_index not in symbols:
                raise ValueError(f"Bad relocation symbol index in {path}: {symbol_index}")
            relocs.append((va, symbols[symbol_index][0], kind))
        sections[name] = (raw, characteristics, relocs)
    return sections, defined_externals


def verify_pair(source: Path, output: Path) -> list[str]:
    source_sections, source_symbols = coff(source)
    output_sections, output_symbols = coff(output)
    debug_names = [name for name in source_sections if name.startswith(".debug$")]
    if not debug_names:
        raise ValueError(f"No .debug$ sections found in {source.name}")
    if any(name.startswith(".debug$") for name in output_sections):
        raise ValueError(f"Debug sections remain in {output}")
    expected = {name: data for name, data in source_sections.items() if not name.startswith(".debug$")}
    if expected != output_sections:
        raise ValueError(f"Non-debug section bytes/flags/relocations changed in {source.name}")
    if sorted(source_symbols) != sorted(output_symbols):
        raise ValueError(f"Defined external symbols changed in {source.name}")
    return sorted(debug_names)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--input-dir", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    parser.add_argument("--objcopy", type=Path, required=True)
    parser.add_argument("--expected-count", type=int, default=705)
    args = parser.parse_args()
    sources = sorted(args.input_dir.glob("*.obj"))
    if len(sources) != args.expected_count:
        raise ValueError(f"Expected {args.expected_count} objects, found {len(sources)}")
    if not args.objcopy.is_file():
        raise FileNotFoundError(args.objcopy)
    args.output_dir.mkdir(parents=True, exist_ok=False)
    manifest_rows = []
    removed_count = 0
    for source in sources:
        output = args.output_dir / source.name
        section_names = [name for name in coff(source)[0] if name.startswith(".debug$")]
        command = [str(args.objcopy), *[f"--remove-section={name}" for name in section_names], str(source), str(output)]
        subprocess.run(command, check=True, capture_output=True, text=True)
        removed = verify_pair(source, output)
        removed_count += len(removed)
        manifest_rows.append(
            {
                "object": source.name,
                "source_sha256": sha256(source),
                "output_sha256": sha256(output),
                "removed_sections": ";".join(removed),
            }
        )
    manifest = args.output_dir / "stripped-coff-manifest.csv"
    with manifest.open("x", encoding="utf-8", newline="") as stream:
        writer = csv.DictWriter(stream, fieldnames=manifest_rows[0].keys())
        writer.writeheader()
        writer.writerows(manifest_rows)
    print(f"objects={len(sources)} debug_sections_removed={removed_count} nondebug_bytes_flags_relocations_symbols=UNCHANGED")
    print(f"manifest={manifest.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
