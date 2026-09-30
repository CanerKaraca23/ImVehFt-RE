#!/usr/bin/env python3
"""Generate COFF callback JMP thunks from read-only Ghidra listing evidence."""

from __future__ import annotations

import argparse
import csv
import re
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
LABEL_RE = re.compile(
    r"^(?P<label>1000c[0-9a-f]{3})\s+JMP\s+0x(?P<target>[0-9a-f]+)\s+"
    r"FUNCTION=<none>(?:\s+XREF=(?P<xref>[0-9a-f]+):(?P<refkind>\w+))?"
)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--listing", action="append", type=Path, required=True)
    parser.add_argument("--literal-inventory", type=Path, action="append", required=True)
    parser.add_argument(
        "--address-range",
        action="append",
        nargs=2,
        metavar=("START", "END"),
        help="inclusive hexadecimal address range; may be repeated (default: 1000c700..1000ca90)",
    )
    parser.add_argument("--candidate-object-dir", type=Path, required=True)
    parser.add_argument("--manifest", type=Path, required=True)
    parser.add_argument("--assembly", type=Path, required=True)
    args = parser.parse_args()

    targets: dict[str, tuple[str, str, str]] = {}
    for listing in args.listing:
        for line in listing.read_text(encoding="utf-8").splitlines():
            match = LABEL_RE.match(line)
            if not match:
                continue
            label = match.group("label").lower()
            target = match.group("target").lower()
            symbol = f"?FUN_{target}@@YGIXZ"
            if not (args.candidate_object_dir / f"{target}.obj").is_file():
                raise SystemExit(f"missing candidate COFF object for JMP target {target}")
            evidence = (target, symbol, match.group("xref") or "")
            if label in targets and targets[label] != evidence:
                raise SystemExit(f"conflicting Ghidra evidence for duplicate label {label}")
            targets[label] = evidence

    inventory: list[dict[str, str]] = []
    for inventory_path in args.literal_inventory:
        with inventory_path.open(encoding="utf-8-sig", newline="") as stream:
            inventory.extend(csv.DictReader(stream))
    ranges = args.address_range or [["0x1000c700", "0x1000ca90"]]
    parsed_ranges = [(int(start, 16), int(end, 16)) for start, end in ranges]
    if any(start > end for start, end in parsed_ranges):
        parser.error("address-range START must not exceed END")
    source_rows = [
        row
        for row in inventory
        if any(start <= int(row["address"], 16) <= end for start, end in parsed_ranges)
    ]
    source_labels = {row["address"].lower().removeprefix("0x"): row for row in source_rows}
    if set(source_labels) != set(targets):
        missing = sorted(set(source_labels) - set(targets))
        extra = sorted(set(targets) - set(source_labels))
        raise SystemExit(
            f"Ghidra/inventory label mismatch: missing listing={missing}; "
            f"no source literal={extra}"
        )
    if len(targets) != len(source_labels):
        raise SystemExit(f"expected one Ghidra JMP listing per source literal, found {len(targets)}")
    for label, (target, _, _) in targets.items():
        target_file = ROOT / "src/functions" / f"{target}.cpp"
        if not target_file.is_file():
            raise SystemExit(f"JMP target is not an address-named candidate TU: {target}")

    if args.manifest.exists() or args.assembly.exists():
        raise SystemExit("refusing to overwrite an existing manifest or assembly file")
    ordered = sorted(targets.items())
    args.manifest.parent.mkdir(parents=True, exist_ok=True)
    with args.manifest.open("x", encoding="utf-8", newline="") as stream:
        writer = csv.DictWriter(
            stream,
            fieldnames=["label_address", "target_address", "target_symbol", "xref", "source", "line", "encoding"],
            lineterminator="\n",
        )
        writer.writeheader()
        for label, (target, symbol, xref) in ordered:
            source = source_labels[label]
            writer.writerow(
                {
                    "label_address": "0x" + label,
                    "target_address": "0x" + target,
                    "target_symbol": symbol,
                    "xref": "0x" + xref if xref else "",
                    "source": source["source"],
                    "line": source["line"],
                    "encoding": "E9 rel32",
                }
            )

    lines = [
        ".386",
        ".model flat",
        "option casemap:none",
        "",
    ]
    lines.extend(f"EXTERN {symbol}:PROC" for _, (_, symbol, _) in ordered)
    lines.extend(["", ".code", ""])
    for label, (_, symbol, _) in ordered:
        lines.extend(
            [
                f"PUBLIC _LAB_{label}",
                f"_LAB_{label} LABEL BYTE",
                f"    JMP {symbol}",
                "",
            ]
        )
    lines.append("END")
    args.assembly.write_text("\n".join(lines) + "\n", encoding="ascii", newline="\n")
    print(f"generated {len(targets)} Ghidra-backed JMP thunks; manifest={args.manifest}; assembly={args.assembly}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
