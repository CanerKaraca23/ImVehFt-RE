#!/usr/bin/env python3
"""Crosswalk direct external API calls to the pinned original ASI IAT."""

from __future__ import annotations

import argparse
import importlib.util
import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
ORIGINAL = Path(r"C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi")
EXPECTED_SHA256 = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"


def load_import_audit_helpers():
    path = ROOT / "scripts" / "audit-appended-thunk-original-import-crosswalk.py"
    spec = importlib.util.spec_from_file_location("original_import_crosswalk", path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot load PE import parser: {path}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--classification", type=Path, required=True)
    parser.add_argument("--original", type=Path, default=ORIGINAL)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")

    helpers = load_import_audit_helpers()
    original = args.original.read_bytes()
    original_sha = helpers.sha256(original)
    if original_sha != EXPECTED_SHA256:
        raise ValueError("original ASI hash does not match the pinned input")
    imports = helpers.imports_pe32(original)
    classification = json.loads(args.classification.read_text(encoding="utf-8"))
    rows = []
    for symbol_row in classification["unresolved_symbols"]:
        if symbol_row.get("status") != "import-or-system-api":
            continue
        symbol = str(symbol_row["symbol"])
        api = helpers.decorated_import_name(symbol)
        modules = symbol_row.get("diagnostic_modules", [])
        matches = imports.get(api, [])
        dlls = sorted({str(module).rsplit(":", 1)[-1].lower() for module in modules})
        exact = [item for item in matches if str(item["dll"]).lower() in dlls]
        if len(exact) == 1:
            status = "exact-original-iat-match"
            iat_va = exact[0]["iat_va"]
        elif not matches:
            status = "absent-from-original-iat"
            iat_va = None
        elif not exact:
            status = "dll-mismatch"
            iat_va = None
        else:
            status = "ambiguous-original-iat-match"
            iat_va = None
        rows.append({
            "coff_code_symbol": symbol,
            "api_name": api,
            "reference_occurrences": int(symbol_row.get("occurrences", 0)),
            "diagnostic_provider_dlls": modules,
            "original_iat_matches_by_name": matches,
            "original_iat_matches_by_name_and_dll": exact,
            "status": status,
            "iat_va": iat_va,
            "requires_rel32_compatible_call_thunk": True,
        })

    report = {
        "scope": (
            "Name-and-DLL crosswalk for direct external API code symbols in the "
            "appended-candidate set. Matching an original IAT slot does not resolve "
            "the REL32 code call; a code thunk and final-image relocation are still required."
        ),
        "original_asi": str(args.original.resolve()),
        "original_sha256": original_sha,
        "classification_report": str(args.classification.resolve()),
        "classification_report_sha256": helpers.sha256(args.classification.read_bytes()),
        "original_imported_function_count": sum(len(values) for values in imports.values()),
        "candidate_direct_api_symbol_count": len(rows),
        "exact_original_iat_match_count": sum(row["status"] == "exact-original-iat-match" for row in rows),
        "reference_occurrences": sum(row["reference_occurrences"] for row in rows),
        "unmatched_or_ambiguous": [row for row in rows if row["status"] != "exact-original-iat-match"],
        "limitations": [
            "No executable call thunk is emitted by this audit.",
            "No candidate COFF REL32 fixup is applied.",
            "The pinned IAT addresses require the original image layout and loader state.",
            "No production PE/ASI or GTA runtime test is performed.",
        ],
        "imports": rows,
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({key: report[key] for key in (
        "candidate_direct_api_symbol_count", "exact_original_iat_match_count",
        "reference_occurrences", "unmatched_or_ambiguous",
    )}, indent=2))
    print(f"report={args.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
