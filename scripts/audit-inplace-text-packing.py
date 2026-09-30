#!/usr/bin/env python3
"""Read-only heuristic: test whether oversized candidate bodies fit current .text slack."""

from __future__ import annotations

import argparse
import json
import struct
from pathlib import Path


def pe_text_section(path: Path) -> tuple[int, int, int]:
    data = path.read_bytes()
    peoff = struct.unpack_from("<I", data, 0x3C)[0]
    if data[peoff : peoff + 4] != b"PE\0\0":
        raise ValueError("invalid PE signature")
    sections = struct.unpack_from("<H", data, peoff + 6)[0]
    optional_size = struct.unpack_from("<H", data, peoff + 20)[0]
    optional = peoff + 24
    magic = struct.unpack_from("<H", data, optional)[0]
    if magic != 0x10B:
        raise ValueError(f"expected PE32, got optional-header magic 0x{magic:04x}")
    image_base = struct.unpack_from("<I", data, optional + 28)[0]
    table = optional + optional_size
    for index in range(sections):
        offset = table + index * 40
        name = data[offset : offset + 8].split(b"\0", 1)[0].decode("ascii")
        if name == ".text":
            virtual_size, rva, raw_size = struct.unpack_from("<III", data, offset + 8)
            return image_base + rva, virtual_size, raw_size
    raise ValueError("PE has no .text section")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--reference-pe", required=True, type=Path)
    parser.add_argument("--feasibility-report", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()

    text_start, text_size, text_raw_size = pe_text_section(args.reference_pe)
    report = json.loads(args.feasibility_report.read_text(encoding="utf-8"))
    entries = sorted(report["entries"], key=lambda item: int(item["address"], 16))
    if len(entries) != report["candidate_count"]:
        raise ValueError("entry count does not match report candidate_count")
    text_end = text_start + text_size

    free: list[dict[str, int | str]] = []
    direct: list[dict[str, int | str]] = []
    thunked: list[dict[str, int | str]] = []
    body_bytes = 0
    for index, entry in enumerate(entries):
        va = int(entry["address"], 16)
        end = int(entries[index + 1]["address"], 16) if index + 1 < len(entries) else text_end
        body_size = int(entry["candidate_body_size"])
        gap = end - va
        if not (text_start <= va < end <= text_end):
            raise ValueError(f"entry slot outside .text: {entry['address']}")
        body_bytes += body_size
        if body_size <= gap:
            direct.append({"address": va, "size": body_size})
            if body_size < gap:
                free.append({"start": va + body_size, "end": end, "size": gap - body_size})
        else:
            thunked.append({"address": va, "size": body_size})
            if gap < 5:
                raise ValueError(f"no room for E9 thunk at {entry['address']}")
            if gap > 5:
                free.append({"start": va + 5, "end": end, "size": gap - 5})

    if entries and int(entries[0]["address"], 16) > text_start:
        first = int(entries[0]["address"], 16)
        free.append({"start": text_start, "end": first, "size": first - text_start})

    unplaced: list[dict[str, int | str]] = []
    placements: list[dict[str, int | str]] = []
    for entry in sorted(thunked, key=lambda item: int(item["size"]), reverse=True):
        need = int(entry["size"])
        fits = [i for i, interval in enumerate(free) if int(interval["size"]) >= need]
        if not fits:
            unplaced.append(entry)
            continue
        index = min(fits, key=lambda i: int(free[i]["size"]))
        interval = free[index]
        start = int(interval["start"])
        placements.append({"entry": entry["address"], "planned_va": start, "size": need})
        interval["start"] = start + need
        interval["size"] = int(interval["size"]) - need
        if int(interval["size"]) == 0:
            free.pop(index)

    largest_unplaced = max(unplaced, key=lambda item: int(item["size"])) if unplaced else None
    result = {
        "scope": "Heuristic capacity/contiguous-gap simulation only; no bytes or relocations are changed.",
        "reference_pe": str(args.reference_pe),
        "feasibility_report": str(args.feasibility_report),
        "text_start": hex(text_start),
        "text_virtual_size": text_size,
        "text_raw_size": text_raw_size,
        "entry_count": len(entries),
        "candidate_body_bytes": body_bytes,
        "candidate_body_bytes_plus_5_byte_thunks": body_bytes + 5 * len(thunked),
        "direct_entries": len(direct),
        "thunk_entries": len(thunked),
        "oversized_bodies_placed_in_remaining_gaps": len(placements),
        "oversized_bodies_unplaced": len(unplaced),
        "largest_unplaced": (
            {"entry": hex(int(largest_unplaced["address"])), "size": int(largest_unplaced["size"])}
            if largest_unplaced else None
        ),
        "max_remaining_gap": max((int(interval["size"]) for interval in free), default=0),
        "remaining_free_bytes": sum(int(interval["size"]) for interval in free),
        "placements": [{**item, "entry": hex(int(item["entry"])), "planned_va": hex(int(item["planned_va"]))} for item in placements],
        "unplaced": [{**item, "address": hex(int(item["address"]))} for item in unplaced],
        "limitations": [
            "Direct-fit functions are held at their original entries; only their trailing slack is reused.",
            "Oversized functions are tried largest-first in the smallest available contiguous gap; this is a heuristic, not an exhaustive global allocator.",
            "No interior code/data references, instruction boundaries, base relocations, COFF relocations, imports, startup, or runtime behavior are validated.",
            "A packing success would be capacity evidence only, not proof of a correct or loadable PE/ASI.",
        ],
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({key: result[key] for key in (
        "entry_count", "candidate_body_bytes", "candidate_body_bytes_plus_5_byte_thunks",
        "direct_entries", "thunk_entries", "oversized_bodies_placed_in_remaining_gaps",
        "oversized_bodies_unplaced", "largest_unplaced", "max_remaining_gap", "remaining_free_bytes",
    )}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
