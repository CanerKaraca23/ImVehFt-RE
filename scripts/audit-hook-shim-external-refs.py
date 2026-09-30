#!/usr/bin/env python3
"""Inventory original-image absolute addresses used outside the 12 hook spans."""

from __future__ import annotations

import argparse
import csv
import re
from collections import defaultdict
from pathlib import Path


ADDRESS = re.compile(r"0x[0-9a-fA-F]{8}")
GLOBAL_NAME = re.compile(r"\b_?(?:DAT|UNK)_(100[0-9a-fA-F]{5})\b")
GHIDRA_ALIAS = re.compile(r"\b(?:_?(?:DAT|UNK)_|[A-Za-z]Ram)(100[0-9a-fA-F]{5})\b")
IMAGE_LOW = 0x10000000
IMAGE_HIGH = 0x10042FFF
SECTIONS = (
    (0x10001000, 0x10021FFF, ".text"),
    (0x10022000, 0x10028FFF, ".rdata"),
    (0x10029000, 0x10042FFF, ".data"),
)


def load_csv(path: Path) -> list[dict[str, str]]:
    with path.open(encoding="utf-8-sig", newline="") as stream:
        return list(csv.DictReader(stream))


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--cfg", type=Path,
        default=Path("audit/asi-hook-target-cfg-2026-09-27.csv"),
    )
    parser.add_argument(
        "--function-map", type=Path,
        default=Path("audit/function-name-map.csv"),
    )
    parser.add_argument("--source-root", type=Path, default=Path("src/functions"))
    parser.add_argument(
        "--decomp-source", type=Path, action="append",
        default=[
            Path("audit/hook-cfg-function-recovery-2026-09-27.c"),
            Path("audit/hook-destination-recovery-2026-09-27.c"),
            Path("audit/100076d0-bounded-cfg-2026-09-27.c"),
        ],
    )
    parser.add_argument(
        "--output", type=Path,
        default=Path("audit/hook-shim-external-reference-inventory-2026-09-27.csv"),
    )
    args = parser.parse_args()

    cfg = load_csv(args.cfg)
    function_map = load_csv(args.function_map)
    spans: list[tuple[int, int]] = []
    by_target: dict[str, list[int]] = defaultdict(list)
    for row in cfg:
        by_target[row["target"].lower()].append(
            int(row["instruction_address"], 16)
        )
    for addresses in by_target.values():
        spans.append((min(addresses), max(addresses)))

    functions = {
        int(row["address"], 16): row["ghidra_name"] for row in function_map
    }
    global_names: dict[int, set[str]] = defaultdict(set)
    for source in sorted(args.source_root.glob("*.cpp")):
        for match in GLOBAL_NAME.finditer(source.read_text(encoding="utf-8-sig")):
            global_names[int(match.group(1), 16)].add(match.group(0).lstrip("_"))
    ghidra_aliases: dict[int, set[str]] = defaultdict(set)
    for decomp in args.decomp_source:
        if not decomp.is_file():
            continue
        for match in GHIDRA_ALIAS.finditer(decomp.read_text(encoding="utf-8-sig")):
            address = int(match.group(1), 16)
            prefix = match.group(0)[: match.start(1) - match.start()]
            ghidra_aliases[address].add(prefix + match.group(1))
    refs: dict[int, list[tuple[str, str, str]]] = defaultdict(list)
    for row in cfg:
        for match in ADDRESS.finditer(row["mnemonic"]):
            address = int(match.group(), 16)
            if not IMAGE_LOW <= address <= IMAGE_HIGH:
                continue
            if any(low <= address <= high for low, high in spans):
                continue
            refs[address].append(
                (row["target"], row["instruction_address"], row["mnemonic"])
            )

    args.output.parent.mkdir(parents=True, exist_ok=True)
    fields = [
        "address", "section", "classification", "candidate_entry",
        "candidate_global_names", "ghidra_aliases", "reference_count", "targets", "reference_sites",
    ]
    with args.output.open("w", encoding="utf-8", newline="") as stream:
        writer = csv.DictWriter(stream, fieldnames=fields, lineterminator="\n")
        writer.writeheader()
        for address, sites in sorted(refs.items()):
            section = next(
                (name for low, high, name in SECTIONS if low <= address <= high),
                "outside-declared-sections",
            )
            if address in functions:
                classification = "candidate-function-entry"
            elif section == ".text":
                classification = "unresolved-text-address-or-interior"
            elif section == ".rdata":
                classification = "readonly-data/string/constant"
            elif section == ".data":
                classification = "mutable-plugin-state"
            else:
                classification = "unclassified-image-address"
            writer.writerow(
                {
                    "address": f"0x{address:08x}",
                    "section": section,
                    "classification": classification,
                    "candidate_entry": functions.get(address, ""),
                    "candidate_global_names": "|".join(sorted(global_names[address])),
                    "ghidra_aliases": "|".join(sorted(ghidra_aliases[address])),
                    "reference_count": len(sites),
                    "targets": "|".join(sorted({site[0] for site in sites})),
                    "reference_sites": "|".join(
                        f"{target}@{instruction}: {mnemonic}"
                        for target, instruction, mnemonic in sites
                    ),
                }
            )

    counts: dict[str, int] = defaultdict(int)
    for address in refs:
        section = next(
            (name for low, high, name in SECTIONS if low <= address <= high),
            "outside-declared-sections",
        )
        if address in functions:
            category = "candidate-function-entry"
        elif section == ".text":
            category = "unresolved-text-address-or-interior"
        elif section == ".rdata":
            category = "readonly-data/string/constant"
        elif section == ".data":
            category = "mutable-plugin-state"
        else:
            category = "unclassified-image-address"
        counts[category] += 1
    print(f"external unique image addresses: {len(refs)}")
    print(
        "mutable data addresses with candidate DAT_/UNK_ identifiers: "
        f"{sum(1 for address in refs if 0x10029000 <= address <= 0x10042FFF and global_names.get(address))}"
    )
    print(
        "mutable data addresses with bounded-Ghidra pseudocode aliases: "
        f"{sum(1 for address in refs if 0x10029000 <= address <= 0x10042FFF and ghidra_aliases.get(address))}"
    )
    for category, count in sorted(counts.items()):
        print(f"{category}: {count}")
    print(f"wrote {args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
