#!/usr/bin/env python3
"""Compare 705 strict COFF executable bodies/relocations, ignoring container metadata."""

from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def load_parser(repo: Path):
    path = repo / "scripts" / "audit-inplace-candidate-relocations.py"
    spec = importlib.util.spec_from_file_location("inplace_candidate_relocations", path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot load COFF parser: {path}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module.parse_coff


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--repo", type=Path, required=True)
    parser.add_argument("--manifest", type=Path, required=True,
                        help="705-entry placement manifest with exact COFF symbols")
    parser.add_argument("--first-objects", type=Path, required=True)
    parser.add_argument("--second-objects", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")
    repo = args.repo.resolve()
    parse_coff = load_parser(repo)
    manifest = json.loads(args.manifest.read_text(encoding="utf-8"))
    results = []
    for row in manifest["results"]:
        entry = int(row["entry_va"], 16)
        name = f"{entry:08x}.obj"
        old_code, old_info = parse_coff(args.first_objects / name, row["symbol"])
        new_code, new_info = parse_coff(args.second_objects / name, row["symbol"])
        old_relocs = old_info["relocations"]
        new_relocs = new_info["relocations"]
        results.append({
            "entry_va": row["entry_va"],
            "symbol": row["symbol"],
            "body_size_first": len(old_code),
            "body_size_second": len(new_code),
            "body_bytes_identical": old_code == new_code,
            "body_sha256_first": sha256(old_code),
            "body_sha256_second": sha256(new_code),
            "relocations_identical": old_relocs == new_relocs,
            "section_number_identical": old_info["section_number"] == new_info["section_number"],
        })
    output = {
        "scope": "COFF .xcode bytes, section identity, and relocation records only; object container metadata intentionally excluded",
        "candidate_count": len(results),
        "body_byte_mismatches": sum(not row["body_bytes_identical"] for row in results),
        "relocation_mismatches": sum(not row["relocations_identical"] for row in results),
        "section_number_mismatches": sum(not row["section_number_identical"] for row in results),
        "results": results,
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(output, stream, indent=2)
        stream.write("\n")
    print(json.dumps({key: value for key, value in output.items() if key != "results"}, indent=2))
    print(f"report={args.output.resolve()}")
    if output["candidate_count"] != 705 or output["body_byte_mismatches"] or output["relocation_mismatches"] or output["section_number_mismatches"]:
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
