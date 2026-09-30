#!/usr/bin/env python3
"""Check Ghidra-derived callback helper spans against the 705 placement plan."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import re
import struct
from pathlib import Path


def load_csv(path: Path) -> list[dict[str, str]]:
    with path.open(newline="", encoding="utf-8-sig") as stream:
        return list(csv.DictReader(stream))


def coff_dispatch_relocations(path: Path) -> dict[str, object]:
    data = path.read_bytes()
    machine, section_count, _, symbol_offset, symbol_count, optional_size, _ = (
        struct.unpack_from("<HHLLLHH", data, 0)
    )
    if machine != 0x14C or optional_size:
        raise ValueError("provider must be a standard i386 COFF object")
    section_table = 20
    sections: list[dict[str, object]] = []
    for index in range(section_count):
        at = section_table + index * 40
        raw = data[at : at + 40]
        name = raw[:8].split(b"\0", 1)[0].decode("ascii", errors="replace")
        raw_size, raw_offset = struct.unpack_from("<LL", raw, 16)
        reloc_offset = struct.unpack_from("<L", raw, 24)[0]
        reloc_count = struct.unpack_from("<H", raw, 32)[0]
        sections.append({"name": name, "size": raw_size, "raw": raw_offset,
                         "reloc": reloc_offset, "reloc_count": reloc_count})

    string_offset = symbol_offset + symbol_count * 18
    string_size = struct.unpack_from("<L", data, string_offset)[0]
    strings = data[string_offset : string_offset + string_size]
    names: dict[int, str] = {}
    definitions: dict[str, tuple[int, int]] = {}
    index = 0
    cursor = symbol_offset
    while index < symbol_count:
        record = data[cursor : cursor + 18]
        name_field = record[:8]
        if name_field[:4] == b"\0\0\0\0":
            name_at = struct.unpack_from("<L", name_field, 4)[0]
            end = strings.find(b"\0", name_at)
            name = strings[name_at:end].decode("utf-8", errors="replace")
        else:
            name = name_field.split(b"\0", 1)[0].decode("utf-8", errors="replace")
        value, section_number = struct.unpack_from("<Lh", record, 8)
        names[index] = name
        if section_number > 0:
            definitions[name] = (section_number, value)
        aux_count = record[17]
        index += 1 + aux_count
        cursor += (1 + aux_count) * 18

    dispatchers = []
    expected = [0x1000CAA0, 0x1000CAF0, 0x1000CB40, 0x1000CB90, 0x1000CBE0]
    for address in expected:
        name = f"_IVF_PLUGIN_CALLBACK_DISPATCH_{address:08X}"
        if name not in definitions:
            raise ValueError(f"provider is missing {name}")
        section_number, value = definitions[name]
        section = sections[section_number - 1]
        found = []
        for n in range(int(section["reloc_count"])):
            at = int(section["reloc"]) + n * 10
            site, symbol_index, kind = struct.unpack_from("<LLH", data, at)
            if value <= site < value + 0x4B:
                found.append({
                    "site_offset": site - value,
                    "type": {6: "DIR32", 20: "REL32"}.get(kind, hex(kind)),
                    "target": names.get(symbol_index, f"symbol-index-{symbol_index}"),
                })
        dispatchers.append({"symbol": name, "section": section["name"],
                             "section_offset": value, "relocations": found})
    expected_target = "IVF_RELOC_TARGET_1003C3CC"
    for row in dispatchers:
        if not any(rel["site_offset"] == 3 and rel["type"] == "DIR32"
                   and rel["target"] == expected_target for rel in row["relocations"]):
            raise ValueError(f"{row['symbol']}: missing DIR32 at +3 to {expected_target}")
    return {"path": str(path), "sha256": hashlib.sha256(data).hexdigest().upper(),
            "dispatchers": dispatchers}


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--plan", type=Path, required=True)
    parser.add_argument("--symbols", type=Path, required=True)
    parser.add_argument("--jmp-csv", type=Path, required=True)
    parser.add_argument("--entry-thunk-script", type=Path, required=True)
    parser.add_argument("--text-highlow-sites", type=Path, required=True)
    parser.add_argument("--provider-object", type=Path, required=True)
    parser.add_argument("--final-reloc-bin", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()

    plan = json.loads(args.plan.read_text(encoding="utf-8"))
    symbols = json.loads(args.symbols.read_text(encoding="utf-8"))["symbols"]
    jmp_rows = load_csv(args.jmp_csv)
    entry_script = args.entry_thunk_script.read_text(encoding="utf-8")
    call_labels = sorted(set(re.findall(r'"(_LAB_[0-9A-Fa-f]{8})"\s*:', entry_script)))

    helpers: list[dict[str, object]] = []
    for row in jmp_rows:
        helpers.append({
            "address": int(row["label_address"], 16),
            "size": 5,
            "name": f"LAB_{int(row['label_address'], 16):08X}",
            "evidence": args.jmp_csv.as_posix(),
        })
    for label in call_labels:
        address = int(label.removeprefix("_LAB_"), 16)
        helpers.append({
            "address": address,
            "size": 7,
            "name": label,
            "evidence": args.entry_thunk_script.as_posix(),
        })

    # The relocatable stub generator emits five Ghidra-confirmed 0x4b-byte
    # bodies at these ownerless callback-dispatch addresses.
    for symbol in symbols:
        match = re.fullmatch(
            r"_IVF_PLUGIN_CALLBACK_DISPATCH_([0-9A-Fa-f]{8})",
            symbol.get("symbol", ""),
        )
        if match:
            helpers.append({
                "address": int(match.group(1), 16),
                "size": 0x4B,
                "name": symbol["symbol"],
                "evidence": "scripts/reloc_local_code_stubs.py: dynamic dispatcher bodies",
            })

    if (len(jmp_rows), len(call_labels), len(helpers)) != (70, 25, 100):
        raise SystemExit(
            f"unexpected helper census: jmp={len(jmp_rows)} call={len(call_labels)} "
            f"total={len(helpers)}"
        )

    modified: list[dict[str, object]] = []
    for entry in plan["entries"]:
        start = int(entry["address"], 16)
        mode = entry["placement_mode"]
        size = entry["candidate_body_size"] if mode == "body-at-entry" else 5
        modified.append({
            "start": start,
            "end": start + size,
            "entry": entry["address"],
            "mode": mode,
        })

    text_highlow_sites = {
        int(row["address"], 16)
        for row in load_csv(args.text_highlow_sites)
    }
    helper_highlow_hits: list[dict[str, object]] = []
    for helper in helpers:
        start = int(helper["address"])
        end = start + int(helper["size"])
        for site in sorted(text_highlow_sites):
            if max(start, site) < min(end, site + 4):
                helper_highlow_hits.append({
                    "helper": helper["name"],
                    "helper_start": hex(start),
                    "site": hex(site),
                    "offset": site - start,
                    "site_inside_helper": site >= start and site + 4 <= end,
                })

    final_reloc_blob = args.final_reloc_bin.read_bytes()
    final_reloc_rvas: set[int] = set()
    cursor = 0
    while cursor < len(final_reloc_blob):
        page_rva, block_size = struct.unpack_from("<LL", final_reloc_blob, cursor)
        if block_size < 8 or block_size % 4 or cursor + block_size > len(final_reloc_blob):
            raise ValueError("malformed final PE relocation directory")
        for at in range(cursor + 8, cursor + block_size, 2):
            entry = struct.unpack_from("<H", final_reloc_blob, at)[0]
            if entry >> 12 == 3:
                final_reloc_rvas.add(page_rva + (entry & 0x0FFF))
        cursor += block_size

    helper_overlaps: list[dict[str, object]] = []
    for index, left in enumerate(helpers):
        left_start = int(left["address"])
        left_end = left_start + int(left["size"])
        for right in helpers[index + 1 :]:
            right_start = int(right["address"])
            right_end = right_start + int(right["size"])
            if left_start < right_end and right_start < left_end:
                helper_overlaps.append({
                    "left": left["name"],
                    "right": right["name"],
                    "overlap_start": hex(max(left_start, right_start)),
                    "overlap_end": hex(min(left_end, right_end)),
                })

    plan_overlaps: list[dict[str, object]] = []
    for helper in helpers:
        start = int(helper["address"])
        end = start + int(helper["size"])
        for change in modified:
            if start < int(change["end"]) and int(change["start"]) < end:
                plan_overlaps.append({
                    "helper": helper["name"],
                    "helper_span": [hex(start), hex(end)],
                    "candidate_entry": change["entry"],
                    "candidate_mode": change["mode"],
                    "overlap_start": hex(max(start, int(change["start"]))),
                    "overlap_end": hex(min(end, int(change["end"]))),
                })

    result = {
        "scope": "Static interval-overlap check of the callback helper spans against every modified span in the conservative 705-entry plan; not a PE patch or execution test.",
        "plan_entries": len(plan["entries"]),
        "candidate_modified_spans": len(modified),
        "callback_helpers": len(helpers),
        "helper_bytes": sum(int(item["size"]) for item in helpers),
        "helper_counts_by_size": {
            str(size): sum(1 for item in helpers if item["size"] == size)
            for size in sorted({int(item["size"]) for item in helpers})
        },
        "helper_helper_overlaps": helper_overlaps,
        "helper_candidate_overlaps": plan_overlaps,
        "original_text_highlow_intersections": helper_highlow_hits,
        "original_text_highlow_intersections_preserved_in_place": (
            len(helper_highlow_hits) == 5
            and all(
                hit["offset"] == 3 and hit["site_inside_helper"]
                and str(hit["helper"]).startswith("_IVF_PLUGIN_CALLBACK_DISPATCH_")
                for hit in helper_highlow_hits
            )
        ),
        "provider_coff_dispatcher_relocations": coff_dispatch_relocations(args.provider_object),
        "final_relocation_directory": {
            "path": str(args.final_reloc_bin),
            "sha256": hashlib.sha256(final_reloc_blob).hexdigest().upper(),
            "highlow_site_count": len(final_reloc_rvas),
            "dispatcher_operand_rvas_preserved": [
                {"va": hex(int(row["helper_start"], 16) + 3),
                 "rva": hex(int(row["helper_start"], 16) + 3 - 0x10000000),
                 "present": int(row["site"], 16) - 0x10000000 in final_reloc_rvas}
                for row in helper_highlow_hits
            ],
        },
        "pass": (
            not helper_overlaps
            and not plan_overlaps
            and len(helper_highlow_hits) == 5
            and all(
                hit["offset"] == 3 and hit["site_inside_helper"]
                and str(hit["helper"]).startswith("_IVF_PLUGIN_CALLBACK_DISPATCH_")
                for hit in helper_highlow_hits
            )
            and all(int(row["site"], 16) - 0x10000000 in final_reloc_rvas
                    for row in helper_highlow_hits)
        ),
        "helpers": [
            {**item, "start": hex(int(item["address"])),
             "end_exclusive": hex(int(item["address"]) + int(item["size"]))}
            for item in helpers
        ],
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(
        f"helpers={len(helpers)} bytes={result['helper_bytes']} "
        f"helper_overlaps={len(helper_overlaps)} "
        f"candidate_overlaps={len(plan_overlaps)} pass={result['pass']}"
    )
    return 0 if result["pass"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
