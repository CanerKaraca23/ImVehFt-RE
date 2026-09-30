#!/usr/bin/env python3
"""Check original-VA E9 slots against current linked candidate COMDAT ranges."""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--trampolines", required=True, type=Path)
    parser.add_argument("--fit-report", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()
    if args.output.exists():
        raise FileExistsError(f"refusing to overwrite {args.output}")

    trampoline_report = json.loads(args.trampolines.read_text(encoding="utf-8"))
    fit_report = json.loads(args.fit_report.read_text(encoding="utf-8"))
    entries = trampoline_report["entries"]
    fit_rows = fit_report["results"]
    if len(entries) != 705 or len(fit_rows) != 705:
        raise ValueError(f"expected 705 entries in both reports; got {len(entries)} and {len(fit_rows)}")

    fit_by_address = {row["address"].lower(): row for row in fit_rows}
    if len(fit_by_address) != 705:
        raise ValueError("fit report has duplicate addresses")

    bodies: list[dict[str, int | str]] = []
    patches: list[dict[str, int | str]] = []
    for entry in entries:
        address = entry["address"].lower()
        current_va = entry["current_diagnostic_body_va"]
        if current_va is None:
            raise ValueError(f"unresolved current body target for {address}")
        row = fit_by_address.get(address)
        if row is None:
            raise ValueError(f"missing fit row for {address}")
        symbol_offset = int(row["symbol_offset_in_comdat"])
        section_size = int(row["coff_text_comdat_size"])
        body_size = section_size - symbol_offset
        if body_size <= 0:
            raise ValueError(f"invalid COMDAT body size for {address}: {body_size}")
        current_start = int(current_va, 16)
        entry_va = int(address, 16)
        bodies.append(
            {
                "address": address,
                "entry_symbol": entry["entry_symbol"],
                "start": current_start,
                "end": current_start + body_size,
                "size": body_size,
            }
        )
        if current_start != entry_va:
            patches.append(
                {
                    "address": address,
                    "entry_symbol": entry["entry_symbol"],
                    "patch_start": entry_va,
                    "patch_end": entry_va + 5,
                    "target_va": current_start,
                }
            )

    overlaps: list[dict[str, object]] = []
    patches_with_overlap: set[str] = set()
    foreign_patch_slots: set[str] = set()
    self_patch_slots: set[str] = set()
    touched_bodies: set[str] = set()
    for patch in patches:
        for body in bodies:
            if int(patch["patch_start"]) < int(body["end"]) and int(patch["patch_end"]) > int(body["start"]):
                is_self = patch["address"] == body["address"]
                patches_with_overlap.add(str(patch["address"]))
                touched_bodies.add(str(body["address"]))
                (self_patch_slots if is_self else foreign_patch_slots).add(str(patch["address"]))
                overlaps.append(
                    {
                        "patch_address": patch["address"],
                        "target_va": f"0x{int(patch['target_va']):08x}",
                        "overlapped_body_address": body["address"],
                        "body_start": f"0x{int(body['start']):08x}",
                        "body_end_exclusive": f"0x{int(body['end']):08x}",
                        "same_candidate": is_self,
                    }
                )

    report = {
        "scope": "In-place 5-byte E9 rel32 patch slots versus current linked candidate COMDAT ranges only; no PE modified.",
        "candidate_count": len(entries),
        "displaced_entries_requiring_trampolines": len(patches),
        "candidate_comdat_count": len(bodies),
        "patch_body_intersection_pairs": len(overlaps),
        "distinct_patch_slots_intersecting_candidate_code": len(patches_with_overlap),
        "distinct_slots_intersecting_foreign_candidate_bodies": len(foreign_patch_slots),
        "distinct_slots_intersecting_own_candidate_bodies": len(self_patch_slots),
        "distinct_slots_without_candidate_comdat_overlap": len(patches) - len(patches_with_overlap),
        "distinct_candidate_bodies_touched": len(touched_bodies),
        "overlaps": overlaps,
        "limitations": [
            "COFF COMDAT ranges are reconstructed from the public entry symbol offset and section size.",
            "This does not inventory support-library code or supplemental hook-shim ranges; collision counts are a lower bound.",
            "A next-entry fit report is not a proof of original function extent.",
            "No trampoline bytes are emitted and no PE image is modified.",
        ],
        "inputs": {
            "trampoline_report": str(args.trampolines.resolve()),
            "trampoline_report_sha256": sha256(args.trampolines),
            "fit_report": str(args.fit_report.resolve()),
            "fit_report_sha256": sha256(args.fit_report),
        },
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(
        f"entries={len(entries)} displaced={len(patches)} collision_pairs={len(overlaps)} "
        f"patch_slots_overlapping_candidate_code={len(patches_with_overlap)} "
        f"foreign_slots={len(foreign_patch_slots)} self_slots={len(self_patch_slots)}"
    )
    print(f"report={args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
