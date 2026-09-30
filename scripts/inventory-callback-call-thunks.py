#!/usr/bin/env python3
"""Map five-byte-spaced PUSH ECX/CALL/RET callback entries from Ghidra listing."""

from __future__ import annotations

import argparse
import csv
import re
from pathlib import Path


ENTRY = re.compile(
    r"^(?P<address>1000c[0-9a-f]{3})\s+PUSH ECX\s+FUNCTION=<none>"
    r"(?:\s+XREF=(?P<xref>[0-9a-f]+):(?P<refkind>\w+))?"
)
CALL = re.compile(r"^(?P<address>1000c[0-9a-f]{3})\s+CALL 0x(?P<target>[0-9a-f]+)\s+FUNCTION=<none>")
RET = re.compile(r"^(?P<address>1000c[0-9a-f]{3})\s+RET\s+FUNCTION=<none>")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--listing", type=Path, required=True)
    parser.add_argument("--literal-inventory", type=Path, required=True)
    parser.add_argument("--candidate-object-dir", type=Path, required=True)
    parser.add_argument("--manifest", type=Path, required=True)
    parser.add_argument("--expected-count", type=int, default=15)
    args = parser.parse_args()

    listing = args.listing.read_text(encoding="utf-8").splitlines()
    records: dict[str, tuple[str, str]] = {}
    for index, line in enumerate(listing):
        entry = ENTRY.match(line)
        if not entry:
            continue
        address = entry.group("address").lower()
        if not 0x1000CC30 <= int(address, 16) <= 0x1000CD10:
            continue
        if index + 2 >= len(listing):
            raise SystemExit(f"truncated callback entry at {address}")
        call = CALL.match(listing[index + 1])
        ret = RET.match(listing[index + 2])
        if (
            not call
            or int(call.group("address"), 16) != int(address, 16) + 1
            or not ret
            or int(ret.group("address"), 16) != int(address, 16) + 6
        ):
            raise SystemExit(f"Ghidra sequence at {address} is not PUSH ECX; CALL rel32; RET")
        target = call.group("target").lower()
        if not (args.candidate_object_dir / f"{target}.obj").is_file():
            raise SystemExit(f"missing candidate object for callback target {target}")
        records[address] = (target, entry.group("xref") or "")

    if len(records) != args.expected_count:
        raise SystemExit(f"expected {args.expected_count} callback entries, found {len(records)}")
    with args.literal_inventory.open(encoding="utf-8-sig", newline="") as stream:
        inventory = list(csv.DictReader(stream))
    literals = {
        row["address"].lower().removeprefix("0x"): row
        for row in inventory
        if 0x1000CC30 <= int(row["address"], 16) <= 0x1000CD10
    }
    if set(literals) != set(records):
        raise SystemExit(
            f"Ghidra/source address mismatch: missing={sorted(set(literals)-set(records))}, "
            f"unreferenced={sorted(set(records)-set(literals))}"
        )
    if args.manifest.exists():
        raise SystemExit(f"refusing to overwrite manifest: {args.manifest}")
    args.manifest.parent.mkdir(parents=True, exist_ok=True)
    with args.manifest.open("x", encoding="utf-8", newline="") as stream:
        writer = csv.DictWriter(
            stream,
            fieldnames=["label_address", "target_address", "target_symbol", "xref", "source", "line", "encoding"],
            lineterminator="\n",
        )
        writer.writeheader()
        for address, (target, xref) in sorted(records.items()):
            row = literals[address]
            writer.writerow(
                {
                    "label_address": "0x" + address,
                    "target_address": "0x" + target,
                    "target_symbol": f"?FUN_{target}@@YGII@Z",
                    "xref": "0x" + xref if xref else "",
                    "source": row["source"],
                    "line": row["line"],
                    "encoding": "PUSH ECX; CALL rel32; RET",
                }
            )
    print(f"mapped {len(records)} Ghidra callback entries to 705-set targets: {args.manifest}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
