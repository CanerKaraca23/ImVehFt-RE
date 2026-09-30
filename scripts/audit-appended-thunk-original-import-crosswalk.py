#!/usr/bin/env python3
"""Crosswalk diagnostic-link __imp_* symbols to the pinned original ASI IAT."""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import struct
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_SYMBOL_REPORT = ROOT / "audit/appended-thunk-link-map-resolution-v4-2026-09-29.json"
DEFAULT_ORIGINAL = Path(r"C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi")
EXPECTED_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def cstring(data: bytes, offset: int) -> str:
    end = data.find(b"\0", offset)
    if end < 0:
        raise ValueError("unterminated PE string")
    return data[offset:end].decode("ascii", errors="replace")


def imports_pe32(data: bytes) -> dict[str, list[dict[str, object]]]:
    nt = struct.unpack_from("<I", data, 0x3C)[0]
    if data[nt:nt + 4] != b"PE\0\0":
        raise ValueError("invalid PE signature")
    nsects = struct.unpack_from("<H", data, nt + 6)[0]
    opt_size = struct.unpack_from("<H", data, nt + 20)[0]
    opt = nt + 24
    if struct.unpack_from("<H", data, opt)[0] != 0x10B:
        raise ValueError("expected PE32")
    image_base = struct.unpack_from("<I", data, opt + 28)[0]
    n_dirs = struct.unpack_from("<I", data, opt + 92)[0]
    if n_dirs <= 1:
        raise ValueError("missing import data directory")
    import_rva, import_size = struct.unpack_from("<II", data, opt + 96 + 8)
    section_table = opt + opt_size
    sections = []
    for i in range(nsects):
        at = section_table + i * 40
        name = data[at:at + 8].split(b"\0", 1)[0].decode("ascii", errors="replace")
        vsize, rva, raw_size, raw = struct.unpack_from("<IIII", data, at + 8)
        sections.append((name, rva, max(vsize, raw_size), raw_size, raw))

    def rva_offset(rva: int) -> int:
        for _, start, size, raw_size, raw in sections:
            if start <= rva < start + size:
                delta = rva - start
                if delta >= raw_size:
                    raise ValueError(f"RVA {rva:#x} is not raw-backed")
                return raw + delta
        raise ValueError(f"RVA {rva:#x} is outside mapped sections")

    result: dict[str, list[dict[str, object]]] = {}
    for i in range(import_size // 20 + 1):
        at = rva_offset(import_rva + i * 20)
        oft, timestamp, forwarder, name_rva, first_thunk = struct.unpack_from("<IIIII", data, at)
        if not any((oft, timestamp, forwarder, name_rva, first_thunk)):
            break
        dll = cstring(data, rva_offset(name_rva))
        lookup = oft or first_thunk
        for index in range(1 << 16):
            thunk_at = rva_offset(lookup + index * 4)
            thunk = struct.unpack_from("<I", data, thunk_at)[0]
            if thunk == 0:
                break
            if thunk & 0x80000000:
                function = f"#ORD{thunk & 0xFFFF}"
            else:
                function = cstring(data, rva_offset(thunk) + 2)
            iat_va = image_base + first_thunk + index * 4
            result.setdefault(function.lower(), []).append({"dll": dll, "name": function,
                                                            "iat_va": f"0x{iat_va:08X}"})
        else:
            raise ValueError(f"unterminated import thunk table for {dll}")
    return result


def decorated_import_name(symbol: str) -> str:
    raw = symbol.removeprefix("__imp_")
    match = re.match(r"^_?([^@]+)(?:@\d+)?$", raw)
    return match.group(1).lower() if match else raw.lower()


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--symbols", type=Path, default=DEFAULT_SYMBOL_REPORT)
    p.add_argument("--original", type=Path, default=DEFAULT_ORIGINAL)
    p.add_argument("--output", type=Path, required=True)
    a = p.parse_args()
    if a.output.exists():
        raise FileExistsError(f"refusing to overwrite {a.output}")
    original_bytes = a.original.read_bytes()
    original_sha = sha256(original_bytes)
    if original_sha != EXPECTED_SHA256:
        raise ValueError("original ASI hash does not match the pinned input")
    symbols_bytes = a.symbols.read_bytes()
    symbols_report = json.loads(symbols_bytes)
    imports = imports_pe32(original_bytes)
    rows = []
    for row in symbols_report["symbols"]:
        name = str(row["symbol"])
        if not name.startswith("__imp_"):
            continue
        api = decorated_import_name(name)
        matches = imports.get(api, [])
        map_matches = row.get("map_matches", [])
        provider = map_matches[0].get("module", "") if map_matches else ""
        diagnostic_dll = provider.rsplit(":", 1)[-1] if ":" in provider else ""
        dll_matches = [item for item in matches
                       if diagnostic_dll and str(item["dll"]).lower() == diagnostic_dll.lower()]
        rows.append({"coff_import_symbol": name, "api_name": api,
                     "relocation_types": [row["relocation_type"]],
                     "reference_occurrences": row["occurrences"],
                     "diagnostic_provider": provider,
                     "original_iat_matches_by_name": matches,
                     "original_iat_matches_by_name_and_dll": dll_matches})
    matched = sum(bool(row["original_iat_matches_by_name_and_dll"]) for row in rows)
    report = {
        "scope": "Name-based import-slot crosswalk for __imp_* COFF symbols referenced by the 147 thunk bodies.",
        "pinned_original_asi": str(a.original.resolve()),
        "original_sha256": original_sha,
        "symbol_report": str(a.symbols.resolve()),
        "symbol_report_sha256": sha256(symbols_bytes),
        "original_imported_function_count": sum(len(v) for v in imports.values()),
        "candidate_import_symbol_count": len(rows),
        "matched_candidate_import_symbols": matched,
        "candidate_symbols_absent_from_original_iat": [r for r in rows if not r["original_iat_matches_by_name"]],
        "candidate_symbols_with_dll_mismatch_or_unknown": [r for r in rows if r["original_iat_matches_by_name"] and not r["original_iat_matches_by_name_and_dll"]],
        "limitations": [
            "This joins diagnostic import-provider DLL identity and API name to the original PE import table; ordinals and forwarded imports are not present in the candidate subset checked here.",
            "The IAT slot VAs are from the original image and are the relevant fixed-address targets; this does not patch the appended body.",
            "Non-import external aliases, CRT code/data, base-relocation generation, and loader/runtime behavior are not covered.",
        ],
        "imports": rows,
    }
    a.output.parent.mkdir(parents=True, exist_ok=True)
    a.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({k: report[k] for k in (
        "original_imported_function_count", "candidate_import_symbol_count",
        "matched_candidate_import_symbols", "candidate_symbols_absent_from_original_iat"
    )}, indent=2))
    print(f"report={a.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
