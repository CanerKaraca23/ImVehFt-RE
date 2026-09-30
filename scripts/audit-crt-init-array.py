#!/usr/bin/env python3
"""Crosswalk the exact CRT initializer array to candidates and exit handlers."""

from __future__ import annotations

import argparse
import csv
import re
from pathlib import Path


def rows(path: Path) -> list[dict[str, str]]:
    with path.open(encoding="utf-8-sig", newline="") as stream:
        return list(csv.DictReader(stream))


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("ghidra_array_bytes", type=Path)
    parser.add_argument("target_disassembly", type=Path)
    parser.add_argument("function_map", type=Path)
    parser.add_argument("--start", type=lambda value: int(value, 0), default=0x10022154)
    parser.add_argument("--end", type=lambda value: int(value, 0), default=0x100221B4)
    parser.add_argument("--csv", type=Path, required=True)
    args = parser.parse_args()

    raw = {int(row["address"], 16): row for row in rows(args.ghidra_array_bytes)}
    functions = {row["address"].lower(): row for row in rows(args.function_map)}
    disassembly: dict[str, list[dict[str, str]]] = {}
    for row in rows(args.target_disassembly):
        disassembly.setdefault(row["target_va"].lower(), []).append(row)

    output = []
    for slot in range(args.start, args.end, 4):
        byte_row = raw.get(slot)
        if byte_row is None:
            parser.error(f"Ghidra byte inventory is missing initializer slot 0x{slot:08x}")
        target_text = byte_row["little_endian_u32"]
        target = int(target_text, 16)
        target_key = f"{target:08x}"
        init = functions.get(target_key, {}) if target else {}
        callback_va = ""
        body = sorted(disassembly.get(target_key, []), key=lambda row: int(row["instruction_va"], 16))
        for index, instruction in enumerate(body):
            if instruction["instruction"].upper().startswith("CALL 0X10010529"):
                for prior in reversed(body[:index]):
                    pushed = re.fullmatch(r"PUSH\s+0x([0-9a-fA-F]{8})", prior["instruction"], re.I)
                    if pushed:
                        callback_va = pushed.group(1).lower()
                        break
                break
        callback = functions.get(callback_va, {})
        output.append(
            {
                "slot_index": str((slot - args.start) // 4),
                "slot_va": f"0x{slot:08x}",
                "entry_target_va": f"0x{target:08x}",
                "entry_candidate_source": init.get("source_path", ""),
                "entry_objective_verdict": init.get("objective_verdict", ""),
                "decoded_thunk_exit_callback_va": (
                    f"0x{int(callback_va, 16):08x}" if callback_va else ""
                ),
                "exit_callback_source": callback.get("source_path", ""),
                "exit_callback_objective_verdict": callback.get("objective_verdict", ""),
            }
        )

    if args.csv.exists():
        parser.error(f"refusing to overwrite existing report: {args.csv}")
    args.csv.parent.mkdir(parents=True, exist_ok=True)
    with args.csv.open("x", encoding="utf-8", newline="") as stream:
        writer = csv.DictWriter(stream, fieldnames=list(output[0]), lineterminator="\n")
        writer.writeheader()
        writer.writerows(output)
    nonzero = [row for row in output if row["entry_target_va"] != "0x00000000"]
    exact = sum(bool(row["entry_candidate_source"]) for row in nonzero)
    exits = sum(bool(row["decoded_thunk_exit_callback_va"]) for row in output)
    print(f"CRT initializer slots: {len(output)} ({len(nonzero)} nonzero)")
    print(f"initializer entries at exact candidate starts: {exact}")
    print(f"noncandidate thunk callbacks decoded from bounded instruction windows: {exits}")
    print(f"CSV: {args.csv.resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
