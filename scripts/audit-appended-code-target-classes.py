#!/usr/bin/env python3
"""Classify appended-body code targets without trusting diagnostic VAs."""

from __future__ import annotations

import argparse
import collections
import json
import re
from pathlib import Path

import pefile


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--symbols", type=Path, required=True)
    ap.add_argument("--placement-plan", type=Path, required=True)
    ap.add_argument("--function-map", type=Path, required=True)
    ap.add_argument("--game-exe", type=Path, required=True)
    ap.add_argument("--output", type=Path, required=True)
    args = ap.parse_args()

    symbols = json.loads(args.symbols.read_text(encoding="utf-8"))["symbols"]
    plan = json.loads(args.placement_plan.read_text(encoding="utf-8"))
    placement = {int(row["address"], 16): row for row in plan["entries"]}
    # These narrow CRT aliases are backed by pinned-image evidence, not a
    # general name heuristic. A preferred address is used only if that exact
    # Ghidra name-map entry is present in the current candidate placement.
    verified_runtime_aliases = {
        "chkstk": {
            "name_key": "allocaprobe",
            "target_va": 0x1001B220,
            "detail": (
                "The diagnostic CRT spelling __chkstk crosswalks to Ghidra's "
                "__alloca_probe at 0x1001B220; its 43-byte body matches the "
                "pinned image exactly and the stack-growth helper has a "
                "controlled runtime test."
            ),
        },
        "memcpy": {
            "name_key": "fidconflictmemcpy",
            "target_va": 0x100111E0,
            "detail": (
                "The diagnostic linker selected static CRT memcpy, while "
                "Ghidra identifies two pinned-image FID_conflict:_memcpy "
                "entries. Their 244 instructions and 0x361-byte spans are "
                "identical after normalizing internal addresses; route this "
                "reference to candidate entry 0x100111E0. This static "
                "crosswalk is not a runtime equivalence test."
            ),
        },
    }
    def normalize(name: str) -> str:
        return re.sub(r"[^0-9a-z]", "", name.lower())

    with args.function_map.open(encoding="utf-8-sig", newline="") as stream:
        import csv
        name_map: dict[str, list[int]] = collections.defaultdict(list)
        for row in csv.DictReader(stream):
            name_map[normalize(row["ghidra_name"])].append(int(row["address"], 16))
    game = pefile.PE(str(args.game_exe), fast_load=True)
    game_base = game.OPTIONAL_HEADER.ImageBase
    game_sections = [
        (section.Name.rstrip(b"\0").decode("ascii", errors="replace"),
         section.VirtualAddress,
         section.VirtualAddress + max(section.Misc_VirtualSize, section.SizeOfRawData))
        for section in game.sections
    ]

    rows: list[dict[str, object]] = []
    for item in symbols:
        if item.get("classification") != "diagnostic-code-symbol":
            continue
        symbol = item["symbol"]
        modules = sorted({m.get("module", "") for m in item.get("map_matches", [])})
        match = re.search(r"FUN_([0-9A-Fa-f]{6,8})", symbol)
        if match:
            encoded = int(match.group(1), 16)
        else:
            encoded = None

        candidate_va = None
        for module in modules:
            root = re.fullmatch(r"(100[0-9A-Fa-f]{5})\.obj", module)
            if root:
                value = int(root.group(1), 16)
                if value in placement:
                    candidate_va = value
                    break
        if candidate_va is None and encoded in placement:
            candidate_va = encoded

        name_key = normalize(symbol.split("@@", 1)[0].lstrip("?_"))
        name_candidates = sorted(set(name_map.get(name_key, [])))
        runtime_alias_used = False
        if not name_candidates and name_key in verified_runtime_aliases:
            name_candidates = sorted(
                set(name_map.get(verified_runtime_aliases[name_key]["name_key"], []))
            )
            runtime_alias_used = bool(name_candidates)
        if candidate_va is None and runtime_alias_used:
            preferred_va = int(verified_runtime_aliases[name_key]["target_va"])
            if preferred_va in placement and preferred_va in name_candidates:
                candidate_va = preferred_va
        if candidate_va is None and len(name_candidates) == 1 and name_candidates[0] in placement:
            candidate_va = name_candidates[0]

        if candidate_va is not None:
            entry = placement[candidate_va]
            status = "candidate-entry-va"
            final_target = hex(candidate_va)
            detail = (
                "Candidate entry remains at its original VA; placement routes to "
                "the in-place body or its five-byte thunk."
            )
            if runtime_alias_used:
                status = "candidate-runtime-helper-crosswalk"
                detail += " " + str(verified_runtime_aliases[name_key]["detail"])
            elif name_candidates == [candidate_va] and not any(
                re.fullmatch(r"(100[0-9a-fA-F]{5})\.obj", module)
                and int(re.fullmatch(r"(100[0-9a-fA-F]{5})\.obj", module).group(1), 16) == candidate_va
                for module in modules
            ) and encoded != candidate_va:
                status = "candidate-name-crosswalk"
                detail += " The diagnostic link selected another provider; final VA comes from the Ghidra function-name map, not that provider VA."
            mode = entry["placement_mode"]
        elif encoded is not None and encoded >= game_base:
            rva = encoded - game_base
            section = next((name for name, lo, hi in game_sections if lo <= rva < hi), None)
            if section == ".text":
                status = "external-game-text-va"
                final_target = hex(encoded)
                detail = "Address encoded in the symbol lies in installed GTA SA .text."
                mode = None
            else:
                status = "external-address-not-game-text"
                final_target = None
                detail = f"Address is not in GTA SA .text (section={section!r})."
                mode = None
        elif symbol.startswith("_LAB_"):
            try:
                address = int(symbol.removeprefix("_LAB_"), 16)
            except ValueError:
                address = None
            status = "callback-helper-original-va"
            final_target = hex(address) if address is not None else None
            detail = "Address is a Ghidra-derived callback helper label; overlay and relocation audited separately."
            mode = None
        elif symbol.startswith("_IVF_PLUGIN_CALLBACK_DISPATCH_"):
            address = int(symbol.rsplit("_", 1)[1], 16)
            status = "callback-dispatch-original-va"
            final_target = hex(address)
            detail = "75-byte Ghidra-derived provider dispatcher; static overlay audit only."
            mode = None
        elif any(re.match(r"^(kernel32|user32):", m, re.I) for m in modules):
            status = "import-or-system-api"
            final_target = None
            detail = "Requires original import/IAT and final loader integration; diagnostic thunk VA is not used."
            mode = None
        elif any(re.match(r"^(libcmt|libucrt|libvcruntime|libvcruntime-without-exsup4|i legacy_stdio_definitions):", m, re.I) for m in modules):
            status = "static-crt-runtime"
            final_target = None
            detail = "Static runtime code must be laid out with its own data/unwind/relocation closure."
            mode = None
        else:
            status = "unresolved-code-target"
            final_target = None
            detail = "No evidence-backed production target class was established."
            mode = None

        rows.append({
            "symbol": symbol,
            "relocation_type": item.get("relocation_type"),
            "occurrences": item.get("occurrences", 0),
            "status": status,
            "target_va": final_target,
            "candidate_placement_mode": mode,
            "diagnostic_modules": modules,
            "detail": detail,
        })

    counts = collections.Counter(row["status"] for row in rows)
    occurrences = collections.Counter()
    for row in rows:
        occurrences[str(row["status"])] += int(row["occurrences"])
    result = {
        "scope": "Reclassifies the current appended-body diagnostic code-symbol set. Candidate and GTA addresses are resolved to preserved original entry/runtime VAs; one byte-verified __chkstk alias is routed to the original __alloca_probe entry. Remaining imports and CRT records remain unresolved for final-image integration. Does not apply COFF fixups.",
        "symbol_report": str(args.symbols.resolve()),
        "placement_plan": str(args.placement_plan.resolve()),
        "function_map": str(args.function_map.resolve()),
        "candidate_entries": len(placement),
        "game_exe": str(args.game_exe.resolve()),
        "game_image_base": hex(game_base),
        "unique_symbols": len(rows),
        "occurrences": sum(int(row["occurrences"]) for row in rows),
        "unique_by_status": dict(sorted(counts.items())),
        "occurrences_by_status": dict(sorted(occurrences.items())),
        "unresolved_symbols": [row for row in rows if row["target_va"] is None],
        "rows": rows,
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({k: result[k] for k in (
        "candidate_entries", "unique_symbols", "occurrences",
        "unique_by_status", "occurrences_by_status"
    )}, indent=2))
    print(f"unresolved unique={len(result['unresolved_symbols'])}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
