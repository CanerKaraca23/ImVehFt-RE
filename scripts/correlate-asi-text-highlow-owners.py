#!/usr/bin/env python3
"""Join original .text HIGHLOW sites/targets to read-only Ghidra owner exports."""
from __future__ import annotations

import csv
import json
from collections import Counter
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
AUDIT = ROOT / "audit"


def read_csv(path: Path) -> list[dict[str, str]]:
    with path.open(newline="", encoding="utf-8-sig") as stream:
        return list(csv.DictReader(stream))


def addr(value: str | None) -> str:
    if not value:
        return ""
    return f"{int(value, 16):08x}"


def main() -> None:
    inventory = json.loads(
        (AUDIT / "asi-base-relocations-full-site-inventory-2026-09-27.json").read_text(
            encoding="utf-8"
        )
    )
    source_rows = {
        addr(row["address"]): row
        for row in read_csv(AUDIT / "asi-text-highlow-source-owners-2026-09-27.csv")
    }
    unit_rows = {
        addr(row["address"]): row
        for row in read_csv(AUDIT / "asi-text-highlow-source-sites-with-units-2026-09-27.csv")
    }
    target_rows = {
        addr(row["address"]): row
        for row in read_csv(AUDIT / "asi-text-highlow-ghidra-owners-2026-09-27.csv")
    }
    data_xrefs = {
        addr(row["address"]): row
        for row in read_csv(AUDIT / "asi-text-highlow-ownerless-data-xrefs-2026-09-27.csv")
    }
    candidates = {
        addr(row["address"]): row
        for row in read_csv(AUDIT / "function-name-map.csv")
    }

    joined: list[dict[str, str]] = []
    owner_counts: Counter[tuple[str, str, str]] = Counter()
    section_counts: Counter[tuple[str, str]] = Counter()
    for item in inventory["all_highlow_relocations"]:
        site = addr(item["site_va"])
        if item["site_section"] != ".text":
            continue
        src = source_rows.get(site, {})
        unit = unit_rows.get(site, {})
        xref = data_xrefs.get(site, {})
        dst = target_rows.get(addr(item["stored_va"]), {}) if item["target_section"] == ".text" else {}
        source_entry = addr(src.get("containing_function_entry", ""))
        source_candidate = candidates.get(source_entry, {})
        source_name = src.get("containing_function_name", "")
        target_name = dst.get("containing_function_name", "")
        row = {
            "site_va": item["site_va"],
            "stored_target_va": item["stored_va"],
            "target_section": item["target_section"],
            "source_owner_entry": src.get("containing_function_entry", ""),
            "source_owner_name": source_name,
            "source_owner_is_candidate": "yes" if source_candidate else "no",
            "source_offset_from_entry": src.get("offset_from_entry", ""),
            "source_code_unit_kind": unit.get("code_unit_kind", ""),
            "source_code_unit_min": unit.get("code_unit_min", ""),
            "source_code_unit_max": unit.get("code_unit_max", ""),
            "source_instruction": unit.get("instruction_text", ""),
            "source_symbols": unit.get("symbols", ""),
            "source_incoming_references": xref.get("incoming_references", ""),
            "target_owner_entry": dst.get("containing_function_entry", ""),
            "target_owner_name": target_name,
            "target_owner_symbol": dst.get("symbols", ""),
        }
        joined.append(row)
        owner_counts[(source_entry, source_name, row["source_owner_is_candidate"])] += 1
        section_counts[(item["site_section"], item["target_section"])] += 1

    csv_path = AUDIT / "asi-text-highlow-site-owner-correlation-2026-09-27.csv"
    fields = list(joined[0]) if joined else []
    with csv_path.open("w", newline="", encoding="utf-8") as stream:
        writer = csv.DictWriter(stream, fieldnames=fields)
        writer.writeheader()
        writer.writerows(joined)

    mapped = sum(bool(row["source_owner_entry"]) for row in joined)
    candidate_mapped = sum(row["source_owner_is_candidate"] == "yes" for row in joined)
    ownerless_units = Counter(
        row["source_code_unit_kind"] or "missing"
        for row in joined if not row["source_owner_entry"]
    )
    ownerless_symbol_counts = Counter(
        row["source_symbols"] or "(no symbol)"
        for row in joined
        if not row["source_owner_entry"] and row["source_code_unit_kind"] == "DataDB"
    )
    ownerless_data = [
        row for row in joined
        if not row["source_owner_entry"] and row["source_code_unit_kind"] == "DataDB"
    ]
    xref_functions = set()
    for row in ownerless_data:
        for reference in row["source_incoming_references"].split("|"):
            if "@" in reference:
                xref_functions.add(reference.split("@", 1)[1].split(":", 1)[0])
    report = {
        "scope": "original PE .text HIGHLOW relocation source sites",
        "site_count": len(joined),
        "source_owner_mapped_sites": mapped,
        "source_owner_unmapped_sites": len(joined) - mapped,
        "candidate_owned_sites": candidate_mapped,
        "candidate_owner_count": len({
            row["source_owner_entry"] for row in joined
            if row["source_owner_is_candidate"] == "yes"
        }),
        "ownerless_code_unit_counts": dict(sorted(ownerless_units.items())),
        "ownerless_data_top_symbols": [
            {"symbol": symbol, "sites": count}
            for symbol, count in ownerless_symbol_counts.most_common(20)
        ],
        "ownerless_data_sites": len(ownerless_data),
        "ownerless_data_sites_with_xrefs": sum(bool(row["source_incoming_references"]) for row in ownerless_data),
        "ownerless_data_sites_without_xrefs": sum(not row["source_incoming_references"] for row in ownerless_data),
        "ownerless_data_switch_label_sites": sum("switchdataD" in row["source_symbols"] for row in ownerless_data),
        "ownerless_data_ptr_case_label_sites": sum("PTR_caseD" in row["source_symbols"] for row in ownerless_data),
        "ownerless_data_ptr_lab_label_sites": sum("PTR_LAB" in row["source_symbols"] for row in ownerless_data),
        "ownerless_data_xref_source_functions": sorted(xref_functions),
        "site_target_section_counts": [
            {"site_section": key[0], "target_section": key[1], "count": count}
            for key, count in sorted(section_counts.items())
        ],
        "top_source_owners": [
            {"entry": key[0], "name": key[1], "candidate": key[2], "sites": count}
            for key, count in owner_counts.most_common(30)
        ],
        "limits": [
        "Ownership means the relocation operand site is inside a Ghidra function body; it does not prove the reconstructed C++ emits a correct or position-independent equivalent.",
            "Ownerless InstructionDB/DataDB classifications come from the current read-only Ghidra listing; data labels indicate likely table/constant storage but require xref/consumer analysis before being called a switch table.",
            "This is an inventory and correlation report, not a relocation engine, production link, or loadable ASI.",
        ],
        "csv": str(csv_path.relative_to(ROOT)).replace("\\", "/"),
    }
    json_path = AUDIT / "asi-text-highlow-site-owner-correlation-2026-09-27.json"
    json_path.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"csv": str(csv_path), "json": str(json_path), **{k: report[k] for k in (
        "site_count", "source_owner_mapped_sites", "source_owner_unmapped_sites",
        "candidate_owned_sites", "candidate_owner_count", "site_target_section_counts"
    )}}, indent=2))


if __name__ == "__main__":
    main()
