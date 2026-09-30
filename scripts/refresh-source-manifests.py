#!/usr/bin/env python3
"""Refresh the 705-function source SHA-256 and byte-count manifests."""

from __future__ import annotations

import argparse
import csv
import hashlib
import shutil
from pathlib import Path


def read_rows(path: Path) -> tuple[list[str], list[dict[str, str]]]:
    with path.open(encoding="utf-8-sig", newline="") as stream:
        reader = csv.DictReader(stream)
        return list(reader.fieldnames or []), list(reader)


def main() -> int:
    root = Path(__file__).resolve().parents[1]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--backup-suffix", default=".pre-source-alias-hash-refresh-20260927.bak")
    args = parser.parse_args()
    manifests = [root / "audit/source-sha256.csv", root / "audit/function-name-map.csv"]
    rows_by_path: dict[Path, tuple[list[str], list[dict[str, str]]]] = {}
    for path in manifests:
        backup = path.with_name(path.name + args.backup_suffix)
        if backup.exists():
            parser.error(f"refusing to overwrite backup: {backup}")
        rows_by_path[path] = read_rows(path)

    updated = 0
    for path, (fields, rows) in rows_by_path.items():
        for row in rows:
            source_key = "source" if "source" in row else "source_path"
            source = root / row[source_key]
            data = source.read_bytes()
            digest = hashlib.sha256(data).hexdigest()
            if "sha256" in row:
                row["sha256"] = digest
                row["bytes"] = str(len(data))
            else:
                row["code_sha256"] = digest
            updated += 1
        backup = path.with_name(path.name + args.backup_suffix)
        shutil.copy2(path, backup)
        temporary = path.with_suffix(path.suffix + ".tmp")
        with temporary.open("x", encoding="utf-8", newline="") as stream:
            writer = csv.DictWriter(stream, fieldnames=fields, quoting=csv.QUOTE_ALL, lineterminator="\n")
            writer.writeheader()
            writer.writerows(rows)
        temporary.replace(path)
    print(f"manifests=2 rows_refreshed={updated} source_units_per_manifest=705")
    return 0 if updated == 1410 else 1


if __name__ == "__main__":
    raise SystemExit(main())
