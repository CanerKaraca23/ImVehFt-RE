#!/usr/bin/env python3
"""Reclassify candidate bodies whose proposed in-place end cuts an original instruction."""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--feasibility", type=Path, required=True)
    ap.add_argument("--boundary-audit", type=Path, required=True)
    ap.add_argument("--output", type=Path, required=True)
    a = ap.parse_args()
    if a.output.exists():
        raise FileExistsError(f"refusing to overwrite {a.output}")
    feas_bytes = a.feasibility.read_bytes()
    feas = json.loads(feas_bytes)
    boundary_bytes = a.boundary_audit.read_bytes()
    boundary = json.loads(boundary_bytes)
    if feas.get("candidate_count") != 705 or len(feas.get("entries", [])) != 705:
        raise ValueError("expected exactly 705 feasibility entries")
    if boundary.get("boundary_straddler_count") != 44:
        raise ValueError("expected the 44-row current boundary audit")
    entries = {int(row["address"], 16): row for row in feas["entries"]}
    if len(entries) != 705:
        raise ValueError("duplicate feasibility entry address")
    changed = []
    for result in boundary["results"]:
        if not result["site_fully_inside_one_decoded_instruction"]:
            raise ValueError(f"{result['entry_va']}: HIGHLOW not contained in one decoded instruction")
        cross = result["original_instruction_crosses_candidate_end"]
        if not cross:
            raise ValueError(f"{result['entry_va']}: expected original instruction to cross proposed end")
        entry = int(result["entry_va"], 16)
        row = entries[entry]
        if row["placement_mode"] != "body-at-entry":
            raise ValueError(f"{entry:#x}: expected unsafe direct-body placement, got {row['placement_mode']}")
        if int(row["candidate_body_size"]) != int(result["candidate_body_size"]):
            raise ValueError(f"{entry:#x}: feasibility and boundary body sizes differ")
        if int(row["available_until_next_entry_or_text_end"]) < 5:
            raise ValueError(f"{entry:#x}: fewer than five original bytes for E9 entry patch")
        target = int(row["current_diagnostic_body_va"], 16)
        displacement = target - (entry + 5)
        if not -(1 << 31) <= displacement < (1 << 31) or not row["target_is_executable"]:
            raise ValueError(f"{entry:#x}: invalid/executable-range rel32 target")
        row["placement_mode"] = "jmp-rel32-thunk"
        row["rel32_displacement"] = displacement
        row["placement_reason"] = "original HIGHLOW-bearing instruction crosses candidate body end; preserve old body and redirect at entry"
        changed.append(row)
    if len(changed) != 44:
        raise ValueError(f"expected 44 reclassified entries, got {len(changed)}")
    modes = [row["placement_mode"] for row in feas["entries"]]
    thunk_count = modes.count("jmp-rel32-thunk")
    direct_count = modes.count("body-at-entry")
    if thunk_count != 191 or direct_count != 514:
        raise ValueError(f"unexpected resulting placement counts: direct={direct_count} thunk={thunk_count}")
    feas["scope"] = (
        "Instruction-boundary-adjusted placement plan based on current strict COFF bodies and original-image disassembly. "
        "The 44 candidates whose proposed in-place span cuts an original instruction are redirected through entry thunks. "
        "This is a placement plan only; no PE is emitted or modified."
    )
    feas["whole_bodies_fit_bounded_entry_gaps"] = direct_count
    feas["rel32_thunks_required"] = thunk_count
    feas["minimum_gap_for_thunked_entries"] = min(
        int(row["available_until_next_entry_or_text_end"])
        for row in feas["entries"] if row["placement_mode"] == "jmp-rel32-thunk"
    )
    feas["thunked_entries_with_gap_below_5"] = sum(
        int(row["available_until_next_entry_or_text_end"]) < 5
        for row in feas["entries"] if row["placement_mode"] == "jmp-rel32-thunk"
    )
    feas["inputs"]["original_instruction_boundary_audit"] = str(a.boundary_audit.resolve())
    feas["inputs"]["original_instruction_boundary_audit_sha256"] = sha256(boundary_bytes)
    feas["inputs"]["base_feasibility_sha256"] = sha256(feas_bytes)
    feas["limitations"].append(
        "The 44 reclassified entries still require fresh interior-reference, base-relocation, local-rdata, loader, and runtime reconciliation for the expanded thunk set."
    )
    a.output.parent.mkdir(parents=True, exist_ok=True)
    with a.output.open("x", encoding="utf-8", newline="\n") as f:
        json.dump(feas, f, indent=2)
        f.write("\n")
    print(f"direct_bodies={direct_count} thunk_bodies={thunk_count} reclassified={len(changed)}")
    print(f"plan={a.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
