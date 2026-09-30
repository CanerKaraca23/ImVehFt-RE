#!/usr/bin/env python3
"""Crosswalk uncovered direct-body REL32 symbols to exact original IAT names.

This is a read-only name/DLL crosswalk. It does not prove call-site ABI or
write an API thunk, relocation, PE, or ASI.
"""

from __future__ import annotations

import argparse
import collections
import hashlib
import json
from pathlib import Path

import pefile


PINNED = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest().upper()


def api_name(symbol: str) -> str | None:
    # COFF import-library code symbols use _Name@stack_bytes. Do not strip
    # C++ decorations or guess names for compiler-generated aliases.
    if not symbol.startswith("_") or symbol.startswith("__"):
        return None
    name = symbol[1:].split("@", 1)[0]
    return name or None


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--original-asi", required=True, type=Path)
    parser.add_argument("--direct-coverage", required=True, type=Path)
    parser.add_argument("--existing-crosswalk", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")
    original_sha = sha(args.original_asi)
    if original_sha != PINNED:
        raise ValueError(f"original ASI hash differs from pinned target: {original_sha}")

    coverage_bytes = args.direct_coverage.read_bytes()
    coverage = json.loads(coverage_bytes)
    prior_bytes = args.existing_crosswalk.read_bytes()
    prior = json.loads(prior_bytes)
    if coverage.get("inputs", {}).get("pinned_original_asi_sha256", "").upper() != PINNED:
        raise ValueError("direct coverage report is not tied to the pinned original")
    if prior.get("original_sha256", "").upper() != PINNED:
        raise ValueError("existing API crosswalk is not tied to the pinned original")

    pe = pefile.PE(str(args.original_asi), fast_load=False)
    imports: dict[str, list[dict[str, str]]] = collections.defaultdict(list)
    for descriptor in getattr(pe, "DIRECTORY_ENTRY_IMPORT", []):
        dll = descriptor.dll.decode("ascii", errors="replace")
        for imported in descriptor.imports:
            if imported.name:
                imports[imported.name.decode("ascii", errors="replace").casefold()].append({
                    "dll": dll,
                    "name": imported.name.decode("ascii", errors="replace"),
                    "iat_va": f"0x{int(imported.address):08X}",
                })

    existing = {
        row["coff_code_symbol"]: row
        for row in prior.get("imports", [])
        if row.get("status") == "exact-original-iat-match"
    }
    counts = collections.Counter(
        (row["target_symbol"], row["type"])
        for row in coverage.get("unresolved_external_sites_after_crosswalks", [])
        if row.get("type") == "REL32"
    )
    rows = []
    for (symbol, kind), occurrences in sorted(counts.items()):
        normalized = api_name(symbol)
        matches = imports.get(normalized.casefold(), []) if normalized else []
        prior_row = existing.get(symbol)
        if prior_row:
            status = "already-in-existing-exact-IAT-crosswalk"
            selected = prior_row.get("original_iat_matches_by_name_and_dll", [])
        elif len(matches) == 1:
            status = "exact-unique-original-IAT-name-match"
            selected = matches
        elif len(matches) > 1:
            status = "ambiguous-original-IAT-name-match"
            selected = matches
        else:
            status = "no-original-IAT-name-match"
            selected = []
        rows.append({
            "coff_code_symbol": symbol,
            "relocation_type": kind,
            "unresolved_occurrences": occurrences,
            "normalized_api_name": normalized,
            "status": status,
            "original_iat_matches_by_name": matches,
            "selected_matches": selected,
        })

    added_imports = []
    for row in rows:
        if row["status"] != "exact-unique-original-IAT-name-match":
            continue
        match = row["selected_matches"][0]
        added_imports.append({
            "coff_code_symbol": row["coff_code_symbol"],
            "api_name": row["normalized_api_name"].casefold(),
            "reference_occurrences": row["unresolved_occurrences"],
            "diagnostic_provider_dlls": [],
            "original_iat_matches_by_name": row["original_iat_matches_by_name"],
            "original_iat_matches_by_name_and_dll": row["original_iat_matches_by_name"],
            "status": "exact-original-iat-match",
            "iat_va": match["iat_va"],
            "requires_rel32_compatible_call_thunk": True,
        })
    merged_imports = [*prior.get("imports", []), *added_imports]
    if len({row["coff_code_symbol"] for row in merged_imports}) != len(merged_imports):
        raise ValueError("expanded original-IAT crosswalk contains duplicate COFF code symbols")

    output = {
        "scope": "Exact symbol-name to pinned original PE IAT crosswalk for currently uncovered direct-body REL32 sites; no code-target ABI validation or binary writes.",
        "original_asi": str(args.original_asi.resolve()),
        "original_sha256": original_sha,
        "direct_coverage_report": str(args.direct_coverage.resolve()),
        "direct_coverage_sha256": hashlib.sha256(coverage_bytes).hexdigest().upper(),
        "existing_crosswalk": str(args.existing_crosswalk.resolve()),
        "existing_crosswalk_sha256": hashlib.sha256(prior_bytes).hexdigest().upper(),
        "summary": {
            "unique_unresolved_rel32_symbols": len(rows),
            "unresolved_rel32_occurrences": sum(counts.values()),
            "new_unique_exact_iat_symbols": sum(row["status"] == "exact-unique-original-IAT-name-match" for row in rows),
            "new_exact_iat_occurrences": sum(row["unresolved_occurrences"] for row in rows if row["status"] == "exact-unique-original-IAT-name-match"),
            "ambiguous_symbols": sum(row["status"] == "ambiguous-original-IAT-name-match" for row in rows),
            "no_match_symbols": sum(row["status"] == "no-original-IAT-name-match" for row in rows),
            "expanded_exact_iat_code_symbol_count": len(merged_imports),
        },
        "limitations": [
            "Matching an IAT name does not prove the source call ABI or identify its exact instruction semantics.",
            "A CALL rel32 still requires a reachable FF 25 thunk and a recomputed site displacement.",
            "This report does not alter the existing crosswalk or any binary.",
        ],
        "symbols": rows,
        "imports": merged_imports,
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(output, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(output["summary"], indent=2))
    print(f"report={args.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
