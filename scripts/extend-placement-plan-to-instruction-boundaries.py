#!/usr/bin/env python3
"""Move every remaining in-place body with a non-boundary end to an entry thunk."""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--placement-plan", type=Path, required=True)
    ap.add_argument("--boundary-audit", type=Path, required=True)
    ap.add_argument("--output", type=Path, required=True)
    a = ap.parse_args()
    if a.output.exists():
        raise FileExistsError(f"refusing to overwrite {a.output}")
    plan_bytes = a.placement_plan.read_bytes()
    plan = json.loads(plan_bytes)
    boundary_bytes = a.boundary_audit.read_bytes()
    boundary = json.loads(boundary_bytes)
    if boundary.get("placement_plan_sha256") != sha256(plan_bytes):
        raise ValueError("boundary audit was not generated from this exact placement plan")
    rows = {int(row["address"], 16): row for row in plan["entries"]}
    if len(rows) != 705 or plan.get("candidate_count") != 705:
        raise ValueError("expected 705 unique placement entries")
    changed = 0
    for audit_row in boundary["results"]:
        entry = int(audit_row["entry_va"], 16)
        row = rows[entry]
        if row["placement_mode"] != "body-at-entry":
            raise ValueError(f"{entry:#x}: boundary audit unexpectedly covers non-in-place entry")
        if audit_row["classification"] == "instruction-boundary":
            continue
        if int(row["candidate_body_size"]) != int(audit_row["candidate_body_size"]):
            raise ValueError(f"{entry:#x}: stale candidate body size")
        if int(row["available_until_next_entry_or_text_end"]) < 5:
            raise ValueError(f"{entry:#x}: no five-byte patch slot")
        target = int(row["current_diagnostic_body_va"], 16)
        displacement = target - (entry + 5)
        if not -(1 << 31) <= displacement < (1 << 31) or not row["target_is_executable"]:
            raise ValueError(f"{entry:#x}: out-of-range or non-executable target")
        row["placement_mode"] = "jmp-rel32-thunk"
        row["rel32_displacement"] = displacement
        row["placement_reason"] = "candidate body end is not an original x86 instruction boundary"
        changed += 1
    direct = sum(row["placement_mode"] == "body-at-entry" for row in plan["entries"])
    thunks = sum(row["placement_mode"] == "jmp-rel32-thunk" for row in plan["entries"])
    exact = sum(r["classification"] == "instruction-boundary" for r in boundary["results"])
    if changed != len(boundary["results"]) - exact or direct != exact or direct + thunks != 705:
        raise ValueError("post-audit placement counts are not internally consistent")
    plan["scope"] = (
        "Instruction-boundary-safe placement plan: all remaining body-at-entry spans end at a linear-decoded "
        "original x86 instruction boundary; every other candidate is assigned a 5-byte entry thunk. "
        "This remains a placement plan, not a patched or loader-tested PE."
    )
    plan["whole_bodies_fit_bounded_entry_gaps"] = direct
    plan["rel32_thunks_required"] = thunks
    plan["minimum_gap_for_thunked_entries"] = min(
        int(row["available_until_next_entry_or_text_end"])
        for row in plan["entries"] if row["placement_mode"] == "jmp-rel32-thunk"
    )
    plan["thunked_entries_with_gap_below_5"] = sum(
        int(row["available_until_next_entry_or_text_end"]) < 5
        for row in plan["entries"] if row["placement_mode"] == "jmp-rel32-thunk"
    )
    plan["inputs"]["all_remaining_inplace_instruction_boundary_audit"] = str(a.boundary_audit.resolve())
    plan["inputs"]["all_remaining_inplace_instruction_boundary_audit_sha256"] = sha256(boundary_bytes)
    plan["inputs"]["pre_extension_plan_sha256"] = sha256(plan_bytes)
    plan["limitations"].append(
        "Instruction-boundary alignment is only one in-place safety condition; original code/data xrefs, relocation patch overlaps, imports/startup, and runtime behavior remain to be checked."
    )
    a.output.parent.mkdir(parents=True, exist_ok=True)
    with a.output.open("x", encoding="utf-8", newline="\n") as f:
        json.dump(plan, f, indent=2)
        f.write("\n")
    print(f"instruction_aligned_direct_bodies={direct} appended_thunk_bodies={thunks} newly_reclassified={changed}")
    print(f"plan={a.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
