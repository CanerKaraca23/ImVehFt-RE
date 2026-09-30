#!/usr/bin/env python3
"""Verify /volatileMetadata- preserved all 705 candidate runtime sections except .voltbl metadata."""

from __future__ import annotations

import argparse
import importlib.util
from pathlib import Path

HELPER = Path(__file__).with_name("strip-coff-debug-sections.py")
SPEC = importlib.util.spec_from_file_location("coff_helpers", HELPER)
if SPEC is None or SPEC.loader is None:
    raise RuntimeError(f"Cannot load COFF parser: {HELPER}")
COFF = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(COFF)


def norm_section(name: str) -> str:
    return ".candidate_code" if name.startswith((".text", ".xcode")) else name


def norm_relocs(rows: list[tuple[int, str, int]]) -> list[tuple[int, str, int]]:
    return [(offset, norm_section(symbol), kind) for offset, symbol, kind in rows]


def compare(reference: Path, candidate: Path) -> bool:
    old_sections, old_symbols = COFF.coff(reference)
    new_sections, new_symbols = COFF.coff(candidate)
    old_code = [v for n, v in old_sections.items() if n.startswith(".xcode")]
    new_code = [v for n, v in new_sections.items() if n.startswith(".xcode")]
    if len(old_code) != 1 or len(new_code) != 1:
        raise ValueError(f"Expected one .xcode section in {reference.name}")
    if (old_code[0][0], old_code[0][1], norm_relocs(old_code[0][2])) != (
        new_code[0][0], new_code[0][1], norm_relocs(new_code[0][2])
    ):
        raise ValueError(f"Executable code bytes/flags/relocations changed: {reference.name}")

    excluded = {".chks64", ".voltbl"}
    old_runtime = {
        n: v for n, v in old_sections.items()
        if n not in excluded and not n.startswith(".debug$")
    }
    new_runtime = {
        n: v for n, v in new_sections.items()
        if n not in excluded and not n.startswith(".debug$")
    }
    old_runtime = {n: (r, f, norm_relocs(x)) for n, (r, f, x) in old_runtime.items()}
    new_runtime = {n: (r, f, norm_relocs(x)) for n, (r, f, x) in new_runtime.items()}
    if old_runtime != new_runtime:
        raise ValueError(f"Non-metadata runtime sections changed: {reference.name}")

    old_symbols = sorted(
        (n, v, norm_section(s)) for n, v, s in old_symbols
        if s not in excluded and not s.startswith(".debug$")
    )
    new_symbols = sorted(
        (n, v, norm_section(s)) for n, v, s in new_symbols
        if s not in excluded and not s.startswith(".debug$")
    )
    if old_symbols != new_symbols:
        raise ValueError(f"Non-metadata defined symbols changed: {reference.name}")

    old_metadata = old_sections.get(".voltbl")
    new_metadata = new_sections.get(".voltbl")
    if new_metadata is not None:
        raise ValueError(f"/volatileMetadata- object still contains .voltbl: {reference.name}")
    return old_metadata is not None


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--reference-dir", type=Path, required=True)
    parser.add_argument("--candidate-dir", type=Path, required=True)
    parser.add_argument("--expected-count", type=int, default=705)
    args = parser.parse_args()
    reference = {p.name: p for p in args.reference_dir.glob("*.obj")}
    candidate = {p.name: p for p in args.candidate_dir.glob("*.obj")}
    if len(reference) != args.expected_count or len(candidate) != args.expected_count:
        raise ValueError(f"Expected {args.expected_count} objects per side; got {len(reference)} and {len(candidate)}")
    if reference.keys() != candidate.keys():
        raise ValueError("Object filename sets differ")
    removed = sum(compare(reference[name], candidate[name]) for name in sorted(reference))
    print(f"{args.expected_count}/{args.expected_count} objects preserve code, relocations, other runtime sections, and public symbols.")
    print(f".voltbl metadata removed: {removed}/{args.expected_count} objects.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
