#!/usr/bin/env python3
"""Mechanically replace the mapped callback JMP preferred VAs with linker labels."""

from __future__ import annotations

import argparse
import csv
import re
import shutil
from pathlib import Path


def main() -> int:
    root = Path(__file__).resolve().parents[1]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--manifest", type=Path, required=True)
    parser.add_argument("--backup-suffix", default=".pre-relocatable-callback-jmp-thunks-20260927.bak")
    args = parser.parse_args()

    with args.manifest.open(encoding="utf-8-sig", newline="") as stream:
        rows = list(csv.DictReader(stream))
    if not rows:
        parser.error("the Ghidra-backed replacement manifest is empty")
    grouped: dict[str, list[dict[str, str]]] = {}
    for row in rows:
        grouped.setdefault(row["source"], []).append(row)

    edits: list[tuple[Path, str, str]] = []
    for relative, source_rows in grouped.items():
        path = root / relative
        text = path.read_text(encoding="utf-8")
        original = text
        missing_declarations: list[str] = []
        changed = False
        for row in source_rows:
            address = row["label_address"].removeprefix("0x")
            pattern = re.compile(rf"0x{address}u\b", re.IGNORECASE)
            replacement_marker = f"&LAB_{address}"
            if len(pattern.findall(text)) == 0 and replacement_marker in text:
                continue
            replacement = (
                "static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>("
                f"&LAB_{address}))"
            )
            text, count = pattern.subn(replacement, text)
            if count != 1:
                raise SystemExit(f"{relative}: expected one 0x{address}u literal, found {count}")
            changed = True
            declaration = re.compile(
                rf"^extern (?:(?:\"C\") )?(?P<type>std::uint8_t|unsigned char) "
                rf"LAB_{address}(?P<array>\[\])?;$",
                re.MULTILINE,
            )
            matches = list(declaration.finditer(text))
            if len(matches) > 1:
                raise SystemExit(f"{relative}: ambiguous LAB_{address} declaration count {len(matches)}")
            if matches:
                text = declaration.sub(
                    lambda match: f'extern "C" {match.group("type")} '
                    f'LAB_{address}{match.group("array") or ""};',
                    text,
                    count=1,
                )
            else:
                function_declaration = re.compile(
                    rf'^extern "C" void LAB_{address}\(\);$', re.MULTILINE
                )
                if not function_declaration.search(text):
                    missing_declarations.append(f'extern "C" std::uint8_t LAB_{address};')
        if missing_declarations:
            includes = list(re.finditer(r"(?m)^#include[^\r\n]*(?:\r?\n|$)", text))
            insertion = includes[-1].end() if includes else 0
            text = (
                text[:insertion]
                + "\n"
                + "\n".join(missing_declarations)
                + "\n\n"
                + text[insertion:].lstrip("\r\n")
            )
            changed = True
        if not changed:
            continue
        backup = path.with_name(path.name + args.backup_suffix)
        if backup.exists():
            raise SystemExit(f"refusing to overwrite backup: {backup}")
        edits.append((path, text, original))

    for path, text, original in edits:
        backup = path.with_name(path.name + args.backup_suffix)
        shutil.copy2(path, backup)
        temporary = path.with_suffix(path.suffix + ".callback-jmp.tmp")
        if temporary.exists():
            raise SystemExit(f"refusing to overwrite temporary file: {temporary}")
        temporary.write_text(text, encoding="utf-8", newline="")
        temporary.replace(path)
    print(f"updated {sum(len(rows) for rows in grouped.values())} mapped rows; changed and backed up {len(edits)} TUs")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
