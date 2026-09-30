#!/usr/bin/env python3
"""Cluster ownerless .text HIGHLOW sites and correlate them to audited hook CFGs."""
from __future__ import annotations

import csv
import json
from collections import Counter, defaultdict
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
AUDIT = ROOT / "audit"
MAX_GAP = 0x40  # heuristic grouping radius only; not a function-boundary claim


def read_csv(path: Path) -> list[dict[str, str]]:
    with path.open(newline="", encoding="utf-8-sig") as stream:
        return list(csv.DictReader(stream))


def norm(value: str) -> int:
    return int(value, 16)


def hx(value: int) -> str:
    return f"0x{value:08X}"


def main() -> None:
    inventory = json.loads(
        (AUDIT / "asi-base-relocations-full-site-inventory-2026-09-27.json").read_text(encoding="utf-8")
    )
    reloc_by_site = {
        norm(row["site_va"]): row for row in inventory["all_highlow_relocations"]
    }
    sites = [
        row for row in read_csv(AUDIT / "asi-text-highlow-source-sites-with-units-2026-09-27.csv")
        if not row["containing_function_entry"] and row["code_unit_kind"] == "InstructionDB"
    ]
    shim_manifest = json.loads((AUDIT / "hook-shim-fixups-2026-09-27.json").read_text(encoding="utf-8"))
    shim_fixups: dict[int, list[dict[str, str]]] = defaultdict(list)
    shim_fixups_by_site: dict[int, list[dict[str, str]]] = defaultdict(list)
    for fixup in shim_manifest["fixups"]:
        shim_fixups[norm(fixup["instruction_va"])].append(fixup)
        shim_fixups_by_site[norm(fixup["instruction_va"]) + int(fixup["field_offset"])].append(fixup)
    cfg_shims = {
        norm(row["instruction_address"]): row["target"]
        for row in read_csv(AUDIT / "asi-hook-target-cfg-2026-09-27.csv")
    }

    enriched = []
    for row in sites:
        instruction = norm(row["code_unit_min"])
        fixups = shim_fixups.get(instruction, [])
        relocation = reloc_by_site[norm(row["address"])]
        exact_site_fixups = shim_fixups_by_site.get(norm(row["address"]), [])
        enriched.append({
            "relocation_site": hx(norm(row["address"])),
            "instruction_va": hx(instruction),
            "instruction_end": hx(norm(row["code_unit_max"])),
            "instruction": row["instruction_text"],
            "stored_target_va": relocation["stored_va"],
            "target_section": relocation["target_section"],
            "hook_cfg_target": cfg_shims.get(instruction, ""),
            "audited_shim_fixup_count": len(exact_site_fixups),
            "audited_shim_fixup_kinds": ";".join(sorted({f["kind"] for f in exact_site_fixups})),
            "instruction_has_other_audited_fixups": len(fixups) > len(exact_site_fixups),
        })
    enriched.sort(key=lambda row: norm(row["instruction_va"]))

    clusters: list[dict[str, object]] = []
    group: list[dict[str, str]] = []
    last_start = -1
    for row in enriched:
        start = norm(row["instruction_va"])
        if group and start - last_start > MAX_GAP:
            clusters.append(summarize(len(clusters) + 1, group))
            group = []
        group.append(row)
        last_start = start
    if group:
        clusters.append(summarize(len(clusters) + 1, group))

    per_shim: dict[str, dict[str, object]] = {}
    for shim in sorted({target for target in cfg_shims.values()}):
        rows = [row for row in enriched if row["hook_cfg_target"] == shim]
        if rows:
            per_shim[shim] = {
                "ownerless_relocation_site_count": len(rows),
                "instruction_addresses": sorted({r["instruction_va"] for r in rows}),
                "site_addresses": [r["relocation_site"] for r in rows],
            }

    csv_path = AUDIT / "asi-text-highlow-ownerless-instruction-sites-2026-09-27.csv"
    with csv_path.open("w", newline="", encoding="utf-8") as stream:
        writer = csv.DictWriter(stream, fieldnames=list(enriched[0]))
        writer.writeheader()
        writer.writerows(enriched)
    result = {
        "scope": "200 .text HIGHLOW sites whose source instruction has no containing Ghidra function",
        "site_count": len(enriched),
        "cluster_gap_heuristic_bytes": MAX_GAP,
        "cluster_count": len(clusters),
        "clusters": clusters,
        "sites_matching_audited_hook_target_cfg": sum(bool(r["hook_cfg_target"]) for r in enriched),
        "sites_matching_audited_shim_relocation_fixups_exact_site_and_field": sum(bool(r["audited_shim_fixup_count"]) for r in enriched),
        "sites_not_matching_audited_shim_relocation_fixups": sum(not r["audited_shim_fixup_count"] for r in enriched),
        "matched_hook_shims": per_shim,
        "limits": [
            "Address proximity is only a triage heuristic and is not a function boundary.",
            "A hook-CFG match identifies an instruction visited by the bounded hook audit; it does not prove the replacement shim/link layout or runtime behavior.",
            "A relocation site's containing Ghidra instruction is evidence for original bytes only; all sites still need correct new-image fixups or exact table reconstruction.",
        ],
        "csv": str(csv_path.relative_to(ROOT)).replace("\\", "/"),
    }
    json_path = AUDIT / "asi-text-highlow-ownerless-instruction-clusters-2026-09-27.json"
    json_path.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({
        "sites": len(enriched), "clusters": len(clusters),
        "hook_cfg_matches": result["sites_matching_audited_hook_target_cfg"],
        "shim_fixup_matches": result["sites_matching_audited_shim_relocation_fixups_exact_site_and_field"],
        "shim_targets": {key: value["ownerless_relocation_site_count"] for key, value in per_shim.items()},
        "json": str(json_path), "csv": str(csv_path),
    }, indent=2))


def summarize(index: int, rows: list[dict[str, str]]) -> dict[str, object]:
    sections = Counter(row["target_section"] for row in rows)
    return {
        "cluster": index,
        "first_instruction": rows[0]["instruction_va"],
        "last_instruction": rows[-1]["instruction_va"],
        "site_count": len(rows),
        "instruction_count": len({row["instruction_va"] for row in rows}),
        "target_section_counts": dict(sorted(sections.items())),
        "hook_cfg_targets": sorted({row["hook_cfg_target"] for row in rows if row["hook_cfg_target"]}),
        "shim_fixup_site_count": sum(bool(row["audited_shim_fixup_count"]) for row in rows),
        "sites": [row["relocation_site"] for row in rows],
    }


if __name__ == "__main__":
    main()
