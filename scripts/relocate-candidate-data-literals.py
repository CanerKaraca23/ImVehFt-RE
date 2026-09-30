#!/usr/bin/env python3
"""Replace candidate-source .data/.rdata preferred VAs with exported symbols."""

from __future__ import annotations

import argparse
import csv
import json
import re
import shutil
from collections import Counter
from pathlib import Path


TOKEN = re.compile(r"(?<![A-Za-z0-9_])0[xX]([0-9A-Fa-f]{7,8})([uUlL]*)\b")


def relocate_code_tokens(source: str, addresses: set[int], relative: str) -> tuple[str, list[dict[str, object]]]:
    output: list[str] = []
    changes: list[dict[str, object]] = []
    i = 0
    line_no = 1
    state = "code"
    while i < len(source):
        if state == "code":
            if source.startswith("//", i):
                output.append("//")
                i += 2
                state = "line-comment"
                continue
            if source.startswith("/*", i):
                output.append("/*")
                i += 2
                state = "block-comment"
                continue
            if source[i] == '"':
                output.append(source[i])
                i += 1
                state = "string"
                continue
            if source[i] == "'":
                output.append(source[i])
                i += 1
                state = "character"
                continue
            match = TOKEN.match(source, i)
            if match:
                address = int(match.group(1), 16)
                if address in addresses:
                    macro = f"IVF_IMAGE_ADDRESS_{address:08X}"
                    changes.append(
                        {
                            "address": f"0x{address:08X}",
                            "macro": macro,
                            "source": relative,
                            "line": line_no,
                            "literal": match.group(0),
                        }
                    )
                    output.append(macro)
                    i = match.end()
                    continue
            output.append(source[i])
            if source[i] == "\n":
                line_no += 1
            i += 1
            continue
        if state == "line-comment":
            char = source[i]
            output.append(char)
            i += 1
            if char == "\n":
                line_no += 1
                state = "code"
            continue
        if state == "block-comment":
            if source.startswith("*/", i):
                output.append("*/")
                i += 2
                state = "code"
                continue
            char = source[i]
            output.append(char)
            i += 1
            if char == "\n":
                line_no += 1
            continue
        quote = '"' if state == "string" else "'"
        char = source[i]
        output.append(char)
        i += 1
        if char == "\\" and i < len(source):
            output.append(source[i])
            if source[i] == "\n":
                line_no += 1
            i += 1
        elif char == quote:
            state = "code"
        elif char == "\n":
            line_no += 1
            state = "code"
    return "".join(output), changes


def make_header(addresses: set[int]) -> str:
    lines = [
        "#pragma once",
        "",
        "#include <cstdint>",
        "",
        'extern "C" {',
    ]
    for address in sorted(addresses):
        lines.append(f"extern std::uint8_t IVF_RELOC_TARGET_{address:08X}[];")
    lines.extend(["}", ""])
    for address in sorted(addresses):
        lines.append(
            f"#define IVF_IMAGE_ADDRESS_{address:08X} "
            f"(reinterpret_cast<std::uintptr_t>(&IVF_RELOC_TARGET_{address:08X}))"
        )
    lines.append("")
    return "\n".join(lines)


def main() -> int:
    root = Path(__file__).resolve().parents[1]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("inventory", type=Path)
    parser.add_argument("--source-root", type=Path, default=root / "src/functions")
    parser.add_argument("--header", type=Path, default=root / "src/functions/imvehft_image_aliases.hpp")
    parser.add_argument("--manifest", type=Path, required=True)
    parser.add_argument("--backup-suffix", default=".pre-image-address-aliases-20260927.bak")
    parser.add_argument("--apply", action="store_true", help="write after producing a complete replacement plan")
    args = parser.parse_args()
    if args.manifest.exists():
        parser.error(f"refusing to overwrite existing manifest: {args.manifest}")

    addresses: set[int] = set()
    with args.inventory.open(encoding="utf-8-sig", newline="") as stream:
        for row in csv.DictReader(stream):
            if row["section"] in (".data", ".rdata"):
                addresses.add(int(row["address"], 16))
    plans: list[tuple[Path, str, str, list[dict[str, object]]]] = []
    for path in sorted(args.source_root.glob("*.cpp")):
        original = path.read_text(encoding="utf-8-sig")
        updated, changes = relocate_code_tokens(original, addresses, path.relative_to(root).as_posix())
        if changes:
            if '#include "imvehft_image_aliases.hpp"' not in original:
                updated = '#include "imvehft_image_aliases.hpp"\n' + updated
            plans.append((path, original, updated, changes))

    counts = Counter(change["address"] for *_, changes in plans for change in changes)
    inventory_occurrences = sum(
        1
        for row in csv.DictReader(args.inventory.open(encoding="utf-8-sig", newline=""))
        if row["section"] in (".data", ".rdata")
    )
    changed_occurrences = sum(len(plan[3]) for plan in plans)
    manifest = {
        "scope": "mechanical replacement of code-token literals in original .data/.rdata with address-preserving external aliases; review and tests required",
        "inventory": str(args.inventory.resolve()),
        "unique_alias_addresses": len(addresses),
        "inventory_occurrences": inventory_occurrences,
        "replaced_occurrences": changed_occurrences,
        "changed_files": len(plans),
        "counts_by_address": dict(sorted(counts.items())),
        "changes": [change for plan in plans for change in plan[3]],
        "applied": args.apply,
    }
    if args.apply:
        if args.header.exists():
            parser.error(f"refusing to overwrite existing header: {args.header}")
        for path, original, updated, _ in plans:
            backup = path.with_name(path.name + args.backup_suffix)
            if backup.exists():
                parser.error(f"refusing to overwrite existing source backup: {backup}")
        args.header.write_text(make_header(addresses), encoding="utf-8", newline="\n")
        for path, original, updated, _ in plans:
            shutil.copy2(path, path.with_name(path.name + args.backup_suffix))
            path.write_text(updated, encoding="utf-8", newline="\n")
    args.manifest.parent.mkdir(parents=True, exist_ok=True)
    with args.manifest.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(manifest, stream, indent=2)
        stream.write("\n")
    print(
        f"addresses={len(addresses)} inventory_occurrences={inventory_occurrences} "
        f"replaced={changed_occurrences} files={len(plans)} applied={args.apply}"
    )
    if changed_occurrences != inventory_occurrences:
        print("WARNING: lexical replacement count differs from inventory; inspect skipped comments/strings or token forms")
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
