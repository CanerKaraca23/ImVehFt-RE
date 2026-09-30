#!/usr/bin/env python3
"""Keep original function bytes where saved Ghidra xrefs target candidate interiors."""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--placement-plan", type=Path, required=True)
    ap.add_argument("--interior-xref-audit", type=Path, required=True)
    ap.add_argument("--output", type=Path, required=True)
    a = ap.parse_args()
    if a.output.exists():
        raise FileExistsError(f"refusing to overwrite {a.output}")
    plan_bytes = a.placement_plan.read_bytes()
    plan = json.loads(plan_bytes)
    audit_bytes = a.interior_xref_audit.read_bytes()
    audit = json.loads(audit_bytes)
    if plan.get("candidate_count") != 705 or audit.get("placement_plan_sha256") != hashlib.sha256(plan_bytes).hexdigest().upper():
        raise ValueError("interior-xref audit does not match the exact placement plan")
    rows = {int(r["address"], 16): r for r in plan["entries"]}
    original_direct = sum(r["placement_mode"] == "body-at-entry" for r in plan["entries"])
    moved = 0
    for result in audit["entries"]:
        if not result["references"]:
            continue
        entry = int(result["entry_va"], 16)
        row = rows[entry]
        if row["placement_mode"] != "body-at-entry":
            raise ValueError(f"{entry:#x}: xref audit unexpectedly covers a thunk entry")
        if int(row["candidate_body_size"]) != int(result["candidate_body_size"]):
            raise ValueError(f"{entry:#x}: candidate body size mismatch")
        if int(row["available_until_next_entry_or_text_end"]) < 5:
            raise ValueError(f"{entry:#x}: five-byte entry patch does not fit")
        target = int(row["current_diagnostic_body_va"], 16)
        displacement = target - (entry + 5)
        if not -(1 << 31) <= displacement < (1 << 31) or not row["target_is_executable"]:
            raise ValueError(f"{entry:#x}: invalid rel32 destination")
        row["placement_mode"] = "jmp-rel32-thunk"
        row["rel32_displacement"] = displacement
        row["placement_reason"] = "saved Ghidra xref targets original bytes inside candidate body; preserve original span"
        moved += 1
    direct = sum(r["placement_mode"] == "body-at-entry" for r in plan["entries"])
    thunks = sum(r["placement_mode"] == "jmp-rel32-thunk" for r in plan["entries"])
    if (
        moved != audit["candidate_bodies_with_interior_references"]
        or direct + thunks != 705
        or direct != original_direct - moved
        or thunks != 705 - direct
    ):
        raise ValueError(
            f"placement totals do not reconcile: moved={moved}, direct={direct}, thunks={thunks}"
        )
    plan["scope"] = (
        "Conservative placement plan: candidate bodies replace original bytes in place only where the proposed end is "
        "an original instruction boundary and the saved Ghidra non-entry xref export records no interior target. "
        "All other candidates use a five-byte entry thunk, preserving the old body. This is not a patched PE."
    )
    plan["whole_bodies_fit_bounded_entry_gaps"] = direct
    plan["rel32_thunks_required"] = thunks
    plan["inputs"]["direct_body_interior_ghidra_xref_audit"] = str(a.interior_xref_audit.resolve())
    plan["inputs"]["direct_body_interior_ghidra_xref_audit_sha256"] = hashlib.sha256(audit_bytes).hexdigest().upper()
    plan["inputs"]["pre_xref_extension_plan_sha256"] = hashlib.sha256(plan_bytes).hexdigest().upper()
    plan["limitations"].append(
        "Static Ghidra xref absence does not rule out computed/runtime references; preserved original bodies can still be reached by unrecorded paths."
    )
    with a.output.open("x", encoding="utf-8", newline="\n") as f:
        json.dump(plan, f, indent=2)
        f.write("\n")
    print(f"direct_bodies={direct} thunk_bodies={thunks} interior_xref_bodies_preserved={moved}")
    print(f"plan={a.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
