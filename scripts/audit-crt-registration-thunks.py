#!/usr/bin/env python3
"""Map the original .rdata startup pointers to their atexit callback targets."""

from __future__ import annotations

import argparse
import csv
import re
from pathlib import Path


def read_csv(path: Path) -> list[dict[str, str]]:
    with path.open(encoding="utf-8-sig", newline="") as stream:
        return list(csv.DictReader(stream))


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("site_inventory", type=Path)
    parser.add_argument("target_disassembly", type=Path)
    parser.add_argument("function_map", type=Path)
    parser.add_argument("--csv", type=Path, required=True)
    args = parser.parse_args()

    entries = []
    for row in read_csv(args.site_inventory):
        if row["address"].lower() < "1002215c" or row["address"].lower() > "100221b0":
            continue
        match = re.search(r"addr\s+(0x)?([0-9a-fA-F]{8})", row["data_or_code_unit"])
        if match:
            entries.append((row["address"], match.group(2).lower()))

    instructions: dict[str, list[dict[str, str]]] = {}
    for row in read_csv(args.target_disassembly):
        instructions.setdefault(row["target_va"].lower(), []).append(row)
    functions = {row["address"].lower(): row for row in read_csv(args.function_map)}

    output_rows = []
    for site, target in entries:
        body = sorted(instructions.get(target, []), key=lambda row: int(row["instruction_va"], 16))
        callback = ""
        registration_call = ""
        for index, instruction in enumerate(body):
            if instruction["instruction"].upper().startswith("CALL 0X10010529"):
                registration_call = instruction["instruction_va"]
                for prior in reversed(body[:index]):
                    pushed = re.fullmatch(r"PUSH\s+0x([0-9a-fA-F]{8})", prior["instruction"], re.I)
                    if pushed:
                        callback = pushed.group(1).lower()
                        break
                break
        function = functions.get(callback, {})
        output_rows.append(
            {
                "table_site_va": site,
                "startup_thunk_va": target,
                "registration_call_va": registration_call,
                "callback_va": callback,
                "callback_candidate_source": function.get("source_path", ""),
                "candidate_objective_verdict": function.get("objective_verdict", ""),
            }
        )

    args.csv.parent.mkdir(parents=True, exist_ok=True)
    with args.csv.open("x", encoding="utf-8", newline="") as stream:
        writer = csv.DictWriter(stream, fieldnames=list(output_rows[0]), lineterminator="\n")
        writer.writeheader()
        writer.writerows(output_rows)
    mapped = sum(bool(row["callback_candidate_source"]) for row in output_rows)
    print(f"startup table entries: {len(output_rows)}; callbacks mapped to candidates: {mapped}")
    print(f"CSV: {args.csv.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
