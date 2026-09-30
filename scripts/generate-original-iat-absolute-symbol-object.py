#!/usr/bin/env python3
"""Generate a symbol-only IA32 COFF provider for original IAT slot VAs."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--crosswalk", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--manifest", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists() or args.manifest.exists():
        raise FileExistsError("refusing to overwrite COFF object or manifest")

    report_bytes = args.crosswalk.read_bytes()
    report = json.loads(report_bytes)
    rows = [row for row in report["imports"] if row["status"] == "exact-original-iat-match"]
    if len(rows) != report["candidate_direct_api_symbol_count"]:
        raise ValueError("crosswalk includes unmatched/ambiguous imports")

    symbols: list[tuple[str, int]] = []
    seen = set()
    for row in rows:
        name = "__imp_" + str(row["coff_code_symbol"])
        address = int(str(row["iat_va"]), 16)
        if name in seen or not 0x10000000 <= address <= 0xFFFFFFFF:
            raise ValueError(f"duplicate symbol or invalid IAT VA: {name}={address:#x}")
        seen.add(name)
        symbols.append((name, address))

    strings = bytearray()
    records = []
    for name, address in symbols:
        encoded = name.encode("ascii")
        if len(encoded) <= 8:
            name_field = encoded.ljust(8, b"\0")
        else:
            offset = 4 + len(strings)
            name_field = b"\0\0\0\0" + struct.pack("<I", offset)
            strings.extend(encoded + b"\0")
        # Absolute-section externals carry the preferred VA as their value.
        records.append(name_field + struct.pack("<IhHBB", address, -1, 0, 2, 0))
    symbol_bytes = b"".join(records)
    string_table = struct.pack("<I", 4 + len(strings)) + strings
    header = struct.pack("<HHIIIHH", 0x14C, 0, 0, 20, len(records), 0, 0)
    blob = header + symbol_bytes + string_table
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.manifest.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_bytes(blob)

    manifest = {
        "scope": "COFF absolute external symbol table only; no PE section/body emitted. Symbols point at pinned original-IAT preferred VAs and require compatible final image base relocation handling.",
        "crosswalk": str(args.crosswalk.resolve()),
        "crosswalk_sha256": hashlib.sha256(report_bytes).hexdigest().upper(),
        "object": str(args.output.resolve()),
        "object_sha256": hashlib.sha256(blob).hexdigest().upper(),
        "machine": "i386",
        "section_count": 0,
        "absolute_external_symbol_count": len(symbols),
        "symbols": [{"name": name, "preferred_va": f"0x{address:08X}"} for name, address in symbols],
        "limitations": [
            "This object is for a bounded linker probe, not a standalone plugin.",
            "Call-thunk COFF DIR32 relocations and final PE HIGHLOW relocations still need image-layout integration.",
            "No loader or GTA runtime test is performed.",
        ],
    }
    args.manifest.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({
        "absolute_external_symbol_count": len(symbols),
        "object_bytes": len(blob),
        "object_sha256": manifest["object_sha256"],
        "object": str(args.output.resolve()),
    }, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
