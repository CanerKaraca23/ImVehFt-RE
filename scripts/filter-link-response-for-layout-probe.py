#!/usr/bin/env python3
"""Create a unique diagnostic link response with selected probe objects removed."""

from __future__ import annotations

import argparse
import re
from pathlib import Path


DEFAULT_EXCLUDES = (
    "exception_abi_probe.obj",
    "crt_abi_alias_probe.obj",
    "internal_data_alias_probe.obj",
    "internal_rdata_alias_probe.obj",
)


def replace_exactly(text: str, old: str, new: str, expected: int, label: str) -> str:
    pattern = re.compile(re.escape(old), re.IGNORECASE)
    updated, count = pattern.subn(lambda _: new, text)
    if count != expected:
        raise ValueError(f"expected {expected} {label} occurrence(s), found {count}")
    return updated


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--input", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    parser.add_argument("--old-object-directory", required=True)
    parser.add_argument("--new-object-directory", required=True)
    parser.add_argument("--old-pe", required=True)
    parser.add_argument("--new-pe", required=True)
    parser.add_argument("--old-map", required=True)
    parser.add_argument("--new-map", required=True)
    parser.add_argument("--exclude-basename", action="append", default=[])
    parser.add_argument(
        "--keep-probes", action="store_true",
        help="retain all probe entries in the response instead of applying default exclusions",
    )
    args = parser.parse_args()

    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")
    source = args.input.read_text(encoding="utf-8-sig")
    source = replace_exactly(
        source, args.old_object_directory, args.new_object_directory, 705,
        "candidate-object directory",
    )
    source = replace_exactly(source, args.old_pe, args.new_pe, 1, "output PE")
    source = replace_exactly(source, args.old_map, args.new_map, 1, "map output")

    excluded = () if args.keep_probes else tuple(args.exclude_basename or DEFAULT_EXCLUDES)
    lines = source.splitlines()
    for basename in excluded:
        hits = [line for line in lines if Path(line.strip().strip('"')).name.lower() == basename.lower()]
        if len(hits) != 1:
            raise ValueError(f"expected one response entry for {basename}, found {len(hits)}")
        lines = [line for line in lines if line not in hits]

    candidate_paths = []
    for line in lines:
        stripped = line.strip()
        if not (stripped.startswith('"') and stripped.lower().endswith('.obj"')):
            continue
        path = Path(stripped[1:-1])
        if str(Path(args.new_object_directory)).lower() in str(path).lower():
            if not path.is_file():
                raise FileNotFoundError(path)
            candidate_paths.append(path)
    if len(candidate_paths) != 705 or len({path.name.lower() for path in candidate_paths}) != 705:
        raise ValueError(f"expected 705 unique current candidate objects, found {len(candidate_paths)}")
    if any(Path(line.strip().strip('"')).name.lower() in {x.lower() for x in excluded} for line in lines):
        raise AssertionError("an excluded probe object remains in the response")

    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("x", encoding="utf-8", newline="\n") as stream:
        stream.write("\n".join(lines) + "\n")
    print(f"candidate_objects={len(candidate_paths)} excluded={len(excluded)} response={args.output.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
