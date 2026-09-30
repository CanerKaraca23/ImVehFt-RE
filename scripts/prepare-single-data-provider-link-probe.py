#!/usr/bin/env python3
"""Prepare a non-installable diagnostic link using one alias-complete data provider."""

from __future__ import annotations

import argparse
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--input", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    parser.add_argument("--old-provider", required=True)
    parser.add_argument("--new-provider", required=True)
    parser.add_argument("--old-output-token", required=True)
    parser.add_argument("--new-output-token", required=True)
    parser.add_argument("--crt-alias-object", required=True, type=Path)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite response: {args.output}")
    if not args.new_provider or not args.crt_alias_object.is_file():
        raise FileNotFoundError(args.crt_alias_object)

    text = args.input.read_text(encoding="utf-8-sig")
    if text.count(args.old_provider) != 1:
        raise ValueError("expected exactly one primary data-provider entry")
    if args.old_output_token not in text:
        raise ValueError("old output token is absent")
    text = text.replace(args.old_provider, args.new_provider, 1)
    text = text.replace(args.old_output_token, args.new_output_token)
    if args.old_provider in text or args.old_output_token in text:
        raise AssertionError("old provider or output token remains")
    text = text.rstrip() + "\n\"" + str(args.crt_alias_object.resolve()) + "\"\n"
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("x", encoding="utf-8", newline="\n") as stream:
        stream.write(text)
    print(f"response={args.output.resolve()}")
    print(f"primary_data_provider={Path(args.new_provider).name}")
    print(f"crt_alias_object={args.crt_alias_object.resolve()}")
    print("redundant full-section alias providers are intentionally omitted")
    print("output must remain diagnostic; this script does not make an ASI")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
