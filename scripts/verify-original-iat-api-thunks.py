#!/usr/bin/env python3
"""Verify x86 call-through-IAT thunks against the pinned IAT crosswalk."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path


IMAGE_REL_I386_DIR32 = 0x0006


def coff_string(data: bytes, strings_at: int, name_field: bytes) -> str:
    if name_field[:4] != b"\0\0\0\0":
        return name_field.split(b"\0", 1)[0].decode("utf-8", errors="replace")
    offset = struct.unpack_from("<I", name_field, 4)[0]
    at = strings_at + offset
    end = data.find(b"\0", at)
    if end < 0:
        raise ValueError("unterminated COFF string")
    return data[at:end].decode("utf-8", errors="replace")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path, required=True)
    parser.add_argument("--crosswalk", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")

    crosswalk = json.loads(args.crosswalk.read_text(encoding="utf-8"))
    expected_rows = [row for row in crosswalk["imports"] if row["status"] == "exact-original-iat-match"]
    if len(expected_rows) != crosswalk["candidate_direct_api_symbol_count"]:
        raise ValueError("crosswalk contains unmatched or ambiguous API imports")

    data = args.object.read_bytes()
    machine, section_count, _, symbol_at, symbol_count, optional_size, _ = struct.unpack_from("<HHIIIHH", data)
    if machine != 0x14C or optional_size != 0:
        raise ValueError("expected an i386 COFF object without optional header")
    sections = []
    section_table = 20 + optional_size
    for index in range(section_count):
        at = section_table + index * 40
        name, _, _, size, raw, reloc, _, reloc_count, _, flags = struct.unpack_from("<8sIIIIIIHHI", data, at)
        sections.append({"name": name.split(b"\0", 1)[0].decode("ascii"), "size": size,
                         "raw": raw, "reloc": reloc, "reloc_count": reloc_count, "flags": flags})
    text_number = next((i + 1 for i, row in enumerate(sections) if row["name"].startswith(".text")), None)
    if text_number is None:
        raise ValueError("COFF object has no .text contribution")
    text = sections[text_number - 1]
    strings_at = symbol_at + symbol_count * 18
    strings_size = struct.unpack_from("<I", data, strings_at)[0]
    if strings_at + strings_size > len(data):
        raise ValueError("invalid COFF string table")
    symbols: dict[int, dict[str, object]] = {}
    defined: dict[str, int] = {}
    index = 0
    cursor = symbol_at
    while index < symbol_count:
        record = data[cursor:cursor + 18]
        name = coff_string(data, strings_at, record[:8])
        value, section, _, storage, auxiliary_count = struct.unpack_from("<IhHBB", record, 8)
        symbols[index] = {"name": name, "value": value, "section": section, "storage": storage}
        if section == text_number and storage == 2:
            if name in defined:
                raise ValueError(f"duplicate public code symbol: {name}")
            defined[name] = value
        index += 1 + auxiliary_count
        cursor += (1 + auxiliary_count) * 18

    relocations = []
    for relocation_index in range(int(text["reloc_count"])):
        at = int(text["reloc"]) + relocation_index * 10
        site, symbol_index, kind = struct.unpack_from("<IIH", data, at)
        symbol = symbols.get(symbol_index)
        if symbol is None:
            raise ValueError(f"relocation has invalid symbol-table index {symbol_index}")
        relocations.append({"site": site, "symbol": symbol["name"], "type": kind})

    results = []
    for row in expected_rows:
        code_symbol = row["coff_code_symbol"]
        if not code_symbol.startswith("_") or "@" not in code_symbol:
            raise ValueError(f"unexpected x86 stdcall symbol spelling: {code_symbol}")
        api_name, stack_bytes = code_symbol[1:].rsplit("@", 1)
        thunk_symbol = f"IVF_API_CALL_{api_name}_{stack_bytes}"
        import_symbol = "__imp_" + code_symbol
        offset = defined.get(thunk_symbol)
        if offset is None:
            raise ValueError(f"missing public call thunk {thunk_symbol} for {code_symbol}")
        if offset + 6 > int(text["size"]):
            raise ValueError(f"thunk exceeds .text section: {code_symbol}")
        body = data[int(text["raw"]) + offset:int(text["raw"]) + offset + 6]
        if body != b"\xFF\x25\0\0\0\0":
            raise ValueError(f"unexpected thunk bytes for {code_symbol}: {body.hex()}")
        matches = [r for r in relocations if r["site"] == offset + 2]
        if len(matches) != 1 or matches[0]["type"] != IMAGE_REL_I386_DIR32 or matches[0]["symbol"] != import_symbol:
            raise ValueError(f"wrong IAT relocation for {code_symbol}: {matches!r}")
        results.append({
            "code_symbol": code_symbol,
            "unique_thunk_symbol": thunk_symbol,
            "iat_import_symbol": import_symbol,
            "iat_va": row["iat_va"],
            "provider_dll": row["original_iat_matches_by_name_and_dll"][0]["dll"],
            "code_offset": f"0x{offset:08X}",
            "bytes": body.hex(" ").upper(),
            "relocation": "DIR32 at thunk+2 to IAT symbol",
            "coff_target_symbol": matches[0]["symbol"],
        })

    if len(defined) != len(expected_rows):
        raise ValueError(f"unexpected public code symbols: {len(defined)}; expected {len(expected_rows)}")
    if len(relocations) != len(expected_rows):
        raise ValueError(f"unexpected .text relocation count: {len(relocations)}; expected {len(expected_rows)}")
    ordered = sorted(defined.values())
    if ordered != list(range(0, len(ordered) * 6, 6)):
        raise ValueError("call thunks are not a contiguous sequence of six-byte entries")

    report = {
        "scope": "COFF structure/bytes only; does not apply the IAT VA, construct a PE, or execute a call.",
        "object": str(args.object.resolve()),
        "object_sha256": hashlib.sha256(data).hexdigest().upper(),
        "crosswalk": str(args.crosswalk.resolve()),
        "thunk_count": len(results),
        "code_bytes": int(text["size"]),
        "dir32_iat_relocations": len(relocations),
        "all_thunks_exact_ff25": all(row["bytes"] == "FF 25 00 00 00 00" for row in results),
        "results": results,
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({key: report[key] for key in (
        "thunk_count", "code_bytes", "dir32_iat_relocations", "all_thunks_exact_ff25",
    )}, indent=2))
    print(f"report={args.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
