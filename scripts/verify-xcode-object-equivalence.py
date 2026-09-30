#!/usr/bin/env python3
"""Compare baseline and forced-.xcode COFF objects while ignoring debug metadata."""

from __future__ import annotations

import argparse
import importlib.util
from pathlib import Path


HELPER = Path(__file__).with_name("strip-coff-debug-sections.py")
SPEC = importlib.util.spec_from_file_location("coff_helpers", HELPER)
if SPEC is None or SPEC.loader is None:
    raise RuntimeError(f"Cannot load COFF parser: {HELPER}")
COFF_HELPERS = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(COFF_HELPERS)


def normalized_section_name(name: str) -> str:
    return ".candidate_code" if name.startswith((".text", ".xcode")) else name


def normalized_relocations(rows: list[tuple[int, str, int]]) -> list[tuple[int, str, int]]:
    return [(offset, normalized_section_name(symbol), kind) for offset, symbol, kind in rows]


def compare(reference: Path, candidate: Path) -> None:
    old_sections, old_symbols = COFF_HELPERS.coff(reference)
    new_sections, new_symbols = COFF_HELPERS.coff(candidate)
    old_code = [value for name, value in old_sections.items() if name.startswith(".text")]
    new_code = [value for name, value in new_sections.items() if name.startswith(".xcode")]
    if len(old_code) != 1 or len(new_code) != 1:
        raise ValueError(f"Expected one candidate code section in {reference.name}")
    old_raw, old_flags, old_relocs = old_code[0]
    new_raw, new_flags, new_relocs = new_code[0]
    if (old_raw, old_flags, normalized_relocations(old_relocs)) != (
        new_raw,
        new_flags,
        normalized_relocations(new_relocs),
    ):
        raise ValueError(f"Candidate code bytes/flags/relocations differ: {reference.name}")

    old_other = {name: value for name, value in old_sections.items() if not name.startswith(".text") and name != ".chks64"}
    new_other = {name: value for name, value in new_sections.items() if not name.startswith(".xcode") and name != ".chks64"}
    old_other = {
        name: (raw, flags, normalized_relocations(relocs))
        for name, (raw, flags, relocs) in old_other.items()
    }
    new_other = {
        name: (raw, flags, normalized_relocations(relocs))
        for name, (raw, flags, relocs) in new_other.items()
    }
    if old_other != new_other:
        raise ValueError(f"Non-code runtime section bytes/flags/relocations differ: {reference.name}")

    old_symbols = sorted((name, value, normalized_section_name(section)) for name, value, section in old_symbols)
    new_symbols = sorted((name, value, normalized_section_name(section)) for name, value, section in new_symbols)
    if old_symbols != new_symbols:
        raise ValueError(f"Defined external symbols differ: {reference.name}")

    for sections in (old_sections, new_sections):
        if ".chks64" in sections and (sections[".chks64"][1] & 0xA00) != 0xA00:
            raise ValueError(f"Unexpected non-discardable .chks64 section in {reference.name}")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--reference-dir", type=Path, required=True)
    parser.add_argument("--candidate-dir", type=Path, required=True)
    parser.add_argument("--expected-count", type=int, default=705)
    args = parser.parse_args()
    references = {path.name: path for path in args.reference_dir.glob("*.obj")}
    candidates = {path.name: path for path in args.candidate_dir.glob("*.obj")}
    if len(references) != args.expected_count or len(candidates) != args.expected_count:
        raise ValueError(
            f"Expected {args.expected_count} objects in each directory; "
            f"got {len(references)} and {len(candidates)}"
        )
    if references.keys() != candidates.keys():
        raise ValueError("Object filename sets differ")
    for name in sorted(references):
        compare(references[name], candidates[name])
    print(
        f"objects={len(references)} exact candidate code bytes/flags/relocations, "
        "non-code runtime sections, and defined external symbols=PASS; "
        ".chks64 discardable linker metadata excluded"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
