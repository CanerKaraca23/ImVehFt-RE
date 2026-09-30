#!/usr/bin/env python3
"""Compare the experimental PE's startup/import contract to the pinned original."""
from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path

import pefile

PINNED = "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3"
IMAGE_BASE = 0x10000000
ENTRY = 0x100111B3
STARTUP_FUNCTIONS = (0x10001DB0, 0x10010F59, 0x100110BD)


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest().upper()


def import_inventory(pe: pefile.PE) -> list[tuple[str, str | None, int | None]]:
    result = []
    for dll in getattr(pe, "DIRECTORY_ENTRY_IMPORT", []):
        dll_name = dll.dll.decode("ascii", errors="replace").lower()
        for item in dll.imports:
            result.append((dll_name,
                           item.name.decode("ascii", errors="replace") if item.name else None,
                           item.ordinal if item.name is None else None))
    return result


def call_target(image: bytes, pe: pefile.PE, function_va: int, offset: int) -> int:
    raw = pe.get_data(function_va - IMAGE_BASE + offset, 5)
    if raw[0] != 0xE8:
        raise ValueError(f"expected CALL rel32 at {function_va + offset:#x}")
    return function_va + offset + 5 + struct.unpack_from("<i", raw, 1)[0]


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--original", type=Path, required=True)
    ap.add_argument("--candidate", type=Path, required=True)
    ap.add_argument("--placement", type=Path, required=True)
    ap.add_argument("--appended-roots", type=Path, required=True)
    ap.add_argument("--output", type=Path, required=True)
    args = ap.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")
    if sha(args.original) != PINNED:
        raise ValueError("original ASI hash differs from pinned input")
    original_bytes, candidate_bytes = args.original.read_bytes(), args.candidate.read_bytes()
    original = pefile.PE(data=original_bytes, fast_load=False)
    candidate = pefile.PE(data=candidate_bytes, fast_load=False)
    plan, roots = json.loads(args.placement.read_text()), json.loads(args.appended_roots.read_text())
    plan_by_va = {int(row["address"], 16): row for row in plan["entries"]}
    root_by_va = {int(row["entry_va"], 16): row for row in roots["entries"]}

    entry_row = plan_by_va[ENTRY]
    entry_size = int(entry_row["candidate_body_size"])
    if entry_row["placement_mode"] != "body-at-entry" or entry_size != 35:
        raise ValueError("unexpected candidate entrypoint body placement/size")
    entry_original = original.get_data(ENTRY - IMAGE_BASE, entry_size)
    entry_candidate = candidate.get_data(ENTRY - IMAGE_BASE, entry_size)
    if entry_original != entry_candidate:
        raise ValueError("entrypoint function bytes differ from original")
    cookie_call = call_target(candidate_bytes, candidate, ENTRY, 11)
    dllmain_crt_call = call_target(candidate_bytes, candidate, ENTRY, 25)
    if (cookie_call != call_target(original_bytes, original, ENTRY, 11)
            or dllmain_crt_call != 0x100110BD):
        raise ValueError("entrypoint startup call targets differ from audited original")

    xcode = next(s for s in candidate.sections if s.Name.rstrip(b"\0") == b".xcode")
    thunk_rows = []
    direct_rows = []
    for va in STARTUP_FUNCTIONS:
        plan_row = plan_by_va[va]
        if plan_row["placement_mode"] == "jmp-rel32-thunk":
            root_row = root_by_va.get(va)
            if root_row is None:
                raise ValueError(f"startup thunk target body is missing from appended roots: {va:#x}")
            thunk = candidate.get_data(va - IMAGE_BASE, 5)
            if thunk[0] != 0xE9:
                raise ValueError(f"startup entry lacks E9 thunk: {va:#x}")
            target = va + 5 + struct.unpack_from("<i", thunk, 1)[0]
            expected = IMAGE_BASE + xcode.VirtualAddress + int(root_row["payload_offset"])
            if target != expected:
                raise ValueError(f"startup thunk target mismatch at {va:#x}: {target:#x} != {expected:#x}")
            thunk_rows.append({"entry_va": hex(va), "placement_mode": "jmp-rel32-thunk",
                               "target_va": hex(target), "body_size": int(root_row["body_size"]),
                               "target_in_xcode": True,
                               "candidate_body_sha256": root_row["body_sha256"]})
        elif plan_row["placement_mode"] == "body-at-entry":
            sample = candidate.get_data(va - IMAGE_BASE, min(8, int(plan_row["candidate_body_size"])))
            if len(sample) < min(8, int(plan_row["candidate_body_size"])):
                raise ValueError(f"direct startup body is not file-backed: {va:#x}")
            direct_rows.append({"entry_va": hex(va), "placement_mode": "body-at-entry",
                                "body_size": int(plan_row["candidate_body_size"]),
                                "candidate_prefix": sample.hex(" ").upper()})
        else:
            raise ValueError(f"unsupported startup placement mode at {va:#x}: {plan_row['placement_mode']}")

    original_dirs = [(d.VirtualAddress, d.Size) for d in original.OPTIONAL_HEADER.DATA_DIRECTORY]
    candidate_dirs = [(d.VirtualAddress, d.Size) for d in candidate.OPTIONAL_HEADER.DATA_DIRECTORY]
    directory_matches = all(original_dirs[i] == candidate_dirs[i]
                            for i in range(len(original_dirs)) if i != 5)
    imports_original, imports_candidate = import_inventory(original), import_inventory(candidate)
    if imports_original != imports_candidate:
        raise ValueError("candidate import inventory differs from the original ASI")
    if not directory_matches:
        raise ValueError("non-relocation data directories differ from the original")
    report = {
        "scope": "Static startup/import contract comparison only; does not invoke DllMain or GTA.",
        "original_sha256": PINNED,
        "candidate_sha256": sha(args.candidate),
        "entrypoint_rva": hex(original.OPTIONAL_HEADER.AddressOfEntryPoint),
        "entrypoint_function_size": entry_size,
        "entrypoint_body_bytes_equal": True,
        "entrypoint_cookie_call_target": hex(cookie_call),
        "entrypoint_dllmain_crt_call_target": hex(dllmain_crt_call),
        "startup_thunks": thunk_rows,
        "startup_direct_entries": direct_rows,
        "imports_equal": True,
        "import_symbol_count": len(imports_candidate),
        "nonrelocation_data_directories_equal": True,
        "dll_characteristics_equal": original.OPTIONAL_HEADER.DllCharacteristics == candidate.OPTIONAL_HEADER.DllCharacteristics,
        "limitations": ["No imports were resolved.", "DllMain/CRT initialization was not run.",
                        "No plugin loader, GTA process, or gameplay test was performed.",
                        "Static thunk targets do not establish semantic or ABI correctness of moved startup functions."],
    }
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({k: report[k] for k in ("candidate_sha256", "entrypoint_body_bytes_equal",
                                            "imports_equal", "import_symbol_count",
                                            "nonrelocation_data_directories_equal", "startup_thunks")}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
