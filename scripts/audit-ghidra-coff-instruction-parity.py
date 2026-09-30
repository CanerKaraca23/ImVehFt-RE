#!/usr/bin/env python3
"""Compare instruction/control-flow shape in a Ghidra JSON export and MSVC COFF object.

This is a bounded structural audit: direct call destinations and absolute data
addresses are normalized because COFF represents those through relocations.
It is not a proof of runtime behavior or of relocation target correctness.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import subprocess
from pathlib import Path


GHIDRA_LINE = re.compile(r"^\s*[0-9a-fA-F]+\s+([A-Za-z][A-Za-z0-9]*)\s*(.*?)\s*$")
COFF_LINE = re.compile(
    r"^\s*([0-9a-fA-F]{8}):\s+(?:(?:[0-9a-fA-F]{2}\s+)+)"
    r"([A-Za-z][A-Za-z0-9]*)\s*(.*?)\s*$"
)
BRANCHES = {
    "ja", "jae", "jb", "jbe", "jc", "jcxz", "je", "jg", "jge",
    "jl", "jle", "jna", "jnae", "jnb", "jnbe", "jnc", "jne", "jng",
    "jnge", "jnl", "jnle", "jno", "jnp", "jns", "jnz", "jo", "jp",
    "jpe", "jpo", "js", "jz", "jmp",
}
COND_ALIASES = {"jz": "je", "jnz": "jne"}


def normalize_numbers(text: str) -> str:
    text = re.sub(r"offset_?IVF_RELOC_TARGET_([0-9a-fA-F]{8})",
                  lambda m: str(int(m.group(1), 16)), text, flags=re.I)
    text = re.sub(r"0x([0-9a-fA-F]+)", lambda m: str(int(m.group(1), 16)), text, flags=re.I)
    text = re.sub(r"(?<![A-Za-z0-9_])([0-9][0-9a-fA-F]*)h\b",
                  lambda m: str(int(m.group(1), 16)), text, flags=re.I)
    text = re.sub(r"(?<![A-Za-z0-9_])([0-9a-fA-F]{6,})(?![A-Za-z0-9_])",
                  lambda m: str(int(m.group(1), 16)), text)
    text = re.sub(r"\[([^\]]+)\]", lambda m: "[" + re.sub(r"\+-(\d+)", r"-\1", m.group(1)) + "]", text)
    text = text.replace("+-", "-")
    return text


def parse_ghidra(path: Path) -> list[tuple[int, str, str]]:
    payload = json.loads(path.read_text(encoding="utf-8"))
    result = []
    for row in payload["assembly"]:
        match = GHIDRA_LINE.match(row)
        if not match:
            raise ValueError(f"unparsed Ghidra instruction: {row}")
        # Ghidra exports are VA-prefixed; keep the address for branch mapping.
        address = int(row.strip().split(None, 1)[0], 16)
        result.append((address, match.group(1).lower(), match.group(2)))
    return result


def parse_coff(dumpbin: str, obj: Path) -> list[tuple[int, str, str]]:
    output = subprocess.run(
        [dumpbin, "/nologo", "/disasm", str(obj)], check=True,
        capture_output=True, text=True, encoding="utf-8", errors="replace",
    ).stdout
    result = []
    for row in output.splitlines():
        match = COFF_LINE.match(row)
        if match:
            result.append((int(match.group(1), 16), match.group(2).lower(), match.group(3)))
    if not result:
        raise ValueError(f"no disassembly instructions parsed from {obj}")
    return result


def branch_index(operand: str, addresses: dict[int, int], *, ghidra: bool) -> str:
    match = re.search(r"(?:0x)?([0-9a-fA-F]+)\s*$", operand)
    if not match:
        raise ValueError(f"unrecognized branch target: {operand}")
    target = int(match.group(1), 16)
    # COFF local branches use section offsets. Ghidra branches use VAs.
    if target not in addresses:
        raise ValueError(f"branch target {target:#x} is not an instruction boundary")
    return f"<bb{addresses[target]:03d}>"


def canonical(rows: list[tuple[int, str, str]], *, ghidra: bool) -> list[str]:
    addr_to_index = {address: index for index, (address, _, _) in enumerate(rows)}
    normalized = []
    for _, raw_mnemonic, raw_operands in rows:
        mnemonic = COND_ALIASES.get(raw_mnemonic.lower(), raw_mnemonic.lower())
        operands = raw_operands.strip()
        if mnemonic in BRANCHES:
            operands = branch_index(operands, addr_to_index, ghidra=ghidra)
        elif mnemonic == "call":
            # Keep indirect register/memory calls distinct; normalize direct
            # symbol/VA calls whose final destinations are checked separately.
            if re.match(r"^(?:dword ptr\s+)?\[", operands, re.I):
                operands = re.sub(r"\[[^\]]+\]", "[ABS]", operands)
                operands = re.sub(r"\s+", " ", operands.lower())
            elif re.fullmatch(r"(?:e?[abcd]x|e?[sd]i|e?[sb]p)", operands, re.I):
                operands = operands.lower()
            else:
                operands = "DIRECT"
        else:
            operands = re.sub(r"\[[^\]]+\]", lambda m: m.group(0) if re.search(r"\b(?:e?bp|e?sp|e?si|e?di|e?[abcd]x)\b", m.group(0), re.I) else "[ABS]", operands)
            operands = re.sub(r"\b(?:dword|byte|word)\s+ptr\s+", "", operands, flags=re.I)
            operands = re.sub(r"\s+", "", operands.lower())
            operands = normalize_numbers(operands)
        normalized.append(f"{mnemonic} {operands}".rstrip())
    return normalized


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--ghidra", required=True, type=Path)
    ap.add_argument("--object", required=True, type=Path)
    ap.add_argument("--dumpbin", required=True)
    ap.add_argument("--report", type=Path)
    args = ap.parse_args()
    ghidra = canonical(parse_ghidra(args.ghidra), ghidra=True)
    coff = canonical(parse_coff(args.dumpbin, args.object), ghidra=False)
    limit = max(len(ghidra), len(coff))
    differences = [
        {"index": index, "ghidra": ghidra[index] if index < len(ghidra) else None,
         "coff": coff[index] if index < len(coff) else None}
        for index in range(limit)
        if index >= len(ghidra) or index >= len(coff) or ghidra[index] != coff[index]
    ]
    report = {
        "scope": "Normalized instruction-stream comparison; direct call destinations and absolute data addresses are intentionally not verified here.",
        "ghidra_export": str(args.ghidra),
        "object": str(args.object),
        "ghidra_sha256": hashlib.sha256(args.ghidra.read_bytes()).hexdigest().upper(),
        "object_sha256": hashlib.sha256(args.object.read_bytes()).hexdigest().upper(),
        "ghidra_instruction_count": len(ghidra),
        "coff_instruction_count": len(coff),
        "normalized_instruction_stream_matches": not differences,
        "differences": differences,
    }
    rendered = json.dumps(report, indent=2)
    if args.report:
        args.report.parent.mkdir(parents=True, exist_ok=True)
        args.report.write_text(rendered + "\n", encoding="utf-8", newline="\n")
    print(rendered)
    return 0 if not differences else 1


if __name__ == "__main__":
    raise SystemExit(main())
