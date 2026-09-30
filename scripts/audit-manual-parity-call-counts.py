#!/usr/bin/env python3
"""Cross-check scoped manual parity call-count notes against Ghidra and COFF."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import re
import shutil
import subprocess
from pathlib import Path


MANUAL_RE = re.compile(r"^\s*-\s*\[[xX]\]\s*(0x[0-9a-fA-F]+)\b(.*)$")


def target_call_count(disassembly: str, target_name: str) -> tuple[int | None, str | None, int]:
    """Count CALLs across a target block, ignoring MSVC's local $LN labels."""
    target = re.sub(r"[^a-z0-9]", "", target_name.lower()).lstrip("_")
    blocks: list[tuple[str, list[str]]] = []
    header: str | None = None
    body: list[str] = []
    for line in disassembly.splitlines():
        if line and not line[0].isspace() and line.rstrip().endswith(":"):
            candidate = line.rstrip()[:-1].strip()
            # dumpbin emits labels such as $LN44 inside a function. They are
            # branch labels, not boundaries between COFF function symbols.
            if candidate.startswith("$"):
                continue
            if header is not None:
                blocks.append((header, body))
            header, body = candidate, []
        elif header is not None:
            body.append(line)
    if header is not None:
        blocks.append((header, body))

    exact: list[tuple[int, str]] = []
    fuzzy: list[tuple[int, str]] = []
    for symbol, instructions in blocks:
        normalized = re.sub(r"[^a-z0-9]", "", symbol.lower()).lstrip("_")
        if normalized == target or normalized.startswith(target + "@"):
            exact.append((sum(bool(re.search(r"\bcall\b", line, re.IGNORECASE)) for line in instructions), symbol))
        elif target and target in normalized:
            fuzzy.append((sum(bool(re.search(r"\bcall\b", line, re.IGNORECASE)) for line in instructions), symbol))

    matches = exact or fuzzy
    # Address-named candidates sometimes split one recovered function between
    # an ABI wrapper and a source-level implementation helper. The existing
    # manual adjudication explicitly describes that expansion (e.g.
    # FUN_1001bc9e + FUN_1001bc9e_impl); report its aggregate, but retain the
    # individual headers so the sum is auditable.
    impl = [
        item for item in blocks
        if re.sub(r"[^a-z0-9]", "", item[0].lower()).lstrip("_").startswith(target + "impl")
    ]
    if exact and impl:
        wrapper_count = exact[0][0]
        impl_count = sum(bool(re.search(r"\bcall\b", line, re.IGNORECASE)) for line in impl[0][1])
        return wrapper_count + impl_count, f"{exact[0][1]} + {impl[0][0]}", 1
    if len(matches) != 1:
        return (matches[0][0], matches[0][1], len(matches)) if matches else (None, None, 0)
    return matches[0][0], matches[0][1], 1


def main() -> int:
    repo = Path(__file__).resolve().parents[1]
    owner = repo.parents[1]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--manual-checks", type=Path, default=owner / "reports/re-agent/manual-parity-checks.md")
    parser.add_argument("--ghidra-export", type=Path, default=owner / "ghidra_exports")
    parser.add_argument("--objects", type=Path, default=repo / "build/recheck/strict-all-post-raster-20260927")
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()

    dumpbin = shutil.which("dumpbin.exe") or shutil.which("dumpbin")
    if not dumpbin:
        parser.error("dumpbin not found; run from a VS 2022 Developer environment")

    with (repo / "audit/function-name-map.csv").open(encoding="utf-8-sig", newline="") as stream:
        name_map = {row["address"].lower(): row for row in csv.DictReader(stream)}
    manual_rows = []
    for line_number, line in enumerate(args.manual_checks.read_text(encoding="utf-8").splitlines(), 1):
        match = MANUAL_RE.match(line)
        if not match:
            continue
        note = match.group(2).strip(" -|")
        if not note.lower().startswith("scope=call-count-only;"):
            continue
        address = match.group(1)[2:].lower()
        manual_rows.append((line_number, address, note))

    if not manual_rows:
        parser.error("no scoped call-count-only manual checks found")
    if args.output.exists():
        parser.error(f"refusing to overwrite report: {args.output}")

    results = []
    errors = []
    for line_number, address, note in manual_rows:
        row = name_map.get(address)
        if row is None:
            errors.append(f"{address}: no function-name-map.csv row")
            continue
        export_path = args.ghidra_export / f"{address}.json"
        object_path = args.objects / f"{address}.obj"
        if not export_path.is_file() or not object_path.is_file():
            errors.append(f"{address}: missing Ghidra export or COFF object")
            continue
        ghidra = json.loads(export_path.read_text(encoding="utf-8"))
        ghidra_calls = sum("CALL " in ins.upper() for ins in ghidra.get("assembly", []))
        proc = subprocess.run(
            [dumpbin, "/nologo", "/disasm", str(object_path)],
            capture_output=True,
            text=True,
            check=False,
        )
        if proc.returncode:
            errors.append(f"{address}: dumpbin failed: {proc.stderr.strip()}")
            continue
        object_calls, header, matches = target_call_count(proc.stdout, row["ghidra_name"])
        if matches != 1:
            errors.append(f"{address}: expected one target symbol block for {row['ghidra_name']}; got {matches}")
        results.append({
            "address": "0x" + address,
            "ghidra_name": row["ghidra_name"],
            "source": row["source_path"],
            "manual_check_line": line_number,
            "ghidra_call_count": ghidra_calls,
            "coff_target_call_count": object_calls,
            "coff_symbol_header": header,
            "target_symbol_blocks": matches,
            "object_sha256": hashlib.sha256(object_path.read_bytes()).hexdigest(),
            "scope": "call-count-only; this report does not validate other semantics or runtime behavior",
            "manual_note": note,
        })

    report = {
        "scope": "independent Ghidra assembly vs target-symbol COFF CALL counts for scoped manual parity checks only",
        "manual_check_count": len(manual_rows),
        "result_count": len(results),
        "errors": errors,
        "results": results,
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    print(f"manual checks={len(manual_rows)} results={len(results)} errors={len(errors)}")
    for result in results:
        print(
            f"{result['address']} {result['ghidra_name']}: "
            f"Ghidra={result['ghidra_call_count']} COFF={result['coff_target_call_count']}"
        )
    for error in errors:
        print("ERROR:", error)
    print(f"Report: {args.output.resolve()}")
    return 1 if errors else 0


if __name__ == "__main__":
    raise SystemExit(main())
