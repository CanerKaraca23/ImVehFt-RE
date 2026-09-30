#!/usr/bin/env python3
"""Generate a source-address-ordered MSVC /ORDER list from candidate COFFs."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import re
import struct
from pathlib import Path


def coff_name(raw: bytes, strings: bytes) -> str:
    if raw[:4] == b"\0\0\0\0":
        offset = struct.unpack_from("<I", raw, 4)[0]
        end = strings.find(b"\0", offset)
        if end < 0:
            raise ValueError("unterminated COFF symbol string")
        return strings[offset:end].decode("ascii")
    return raw.split(b"\0", 1)[0].decode("ascii")


def code_symbols(path: Path) -> list[tuple[str, int]]:
    data = path.read_bytes()
    if len(data) < 20:
        raise ValueError(f"short COFF object: {path}")
    machine, section_count, _, symbol_ptr, symbol_count, optional_size, _ = struct.unpack_from(
        "<HHIIIHH", data, 0
    )
    if machine != 0x14C or optional_size:
        raise ValueError(f"expected x86 COFF object without optional header: {path}")
    sections = {
        index + 1: data[20 + index * 40 : 28 + index * 40].split(b"\0", 1)[0].decode("ascii")
        for index in range(section_count)
    }
    strings_at = symbol_ptr + symbol_count * 18
    string_size = struct.unpack_from("<I", data, strings_at)[0]
    strings = data[strings_at : strings_at + string_size]
    symbols: list[tuple[str, int]] = []
    index = 0
    while index < symbol_count:
        at = symbol_ptr + index * 18
        name = coff_name(data[at : at + 8], strings)
        _, section_no = struct.unpack_from("<Ih", data, at + 8)
        storage_class, aux_count = data[at + 16], data[at + 17]
        if (
            storage_class == 2
            and section_no > 0
            and sections.get(section_no, "").startswith(".text")
        ):
            symbols.append((name, section_no))
        index += 1 + aux_count
    return symbols


def is_candidate_entry(symbol: str, ghidra_name: str, signature: str = "") -> bool:
    name = ghidra_name.strip()
    if re.fullmatch(r"FUN_[0-9a-fA-F]{8}", name):
        folded_symbol = symbol.casefold()
        folded_name = name.casefold()
        return (
            symbol.lstrip("_").casefold() == folded_name
            or symbol.lstrip("_").casefold().startswith(folded_name + "@")
            or folded_symbol.startswith("?" + folded_name + "@")
            or folded_symbol.startswith("?" + folded_name + "@@")
            or folded_symbol.startswith("@" + folded_name + "@")
        ) and not any(
            suffix in symbol.lower()
            for suffix in ("_impl", "_call_bridge", "_relocatable_entry", "_usercall")
        )
    base = name[1:] if name.startswith("_") else name
    if name == "_LocaleUpdate" and "localeinfo_struct" in signature:
        return "localeinfo_struct" in symbol
    decorated_bases = {name, base, name.replace(":", "_").replace("$", "_")}
    return symbol == name or symbol == "_" + name or any(
        symbol.lstrip("_") == candidate for candidate in decorated_bases
    ) or any(
        symbol.startswith(prefix + candidate + delimiter)
        for candidate in decorated_bases
        for prefix, delimiter in (("?", "@"), ("?", "@@"), ("@", "@"))
    ) or any(symbol.startswith("_" + candidate + "@") for candidate in decorated_bases)


def is_address_bound_cpp_entry_alias(symbol: str, ghidra_name: str) -> bool:
    """Recognize the generated this::invoke symbol carrying the exact Ghidra address."""
    name = ghidra_name.strip()
    if not re.fullmatch(r"FUN_[0-9a-fA-F]{8}", name):
        return False
    pattern = rf"(?:^|[@?]){re.escape(name.casefold())}_this(?:@@|@)"
    return re.search(pattern, symbol.casefold()) is not None


def is_address_named_coff_alias(symbol: str, address: int) -> bool:
    """Recognize a public candidate symbol carrying its exact address label."""
    folded = symbol.casefold()
    if any(
        suffix in folded
        for suffix in ("_impl", "_call_bridge", "_relocatable_entry", "_usercall")
    ):
        return False
    token = f"fun_{address:08x}"
    return re.search(rf"(?<![a-z0-9]){re.escape(token)}(?![a-z0-9])", folded) is not None


def is_stdcall_name_sanitization_alias(
    symbol: str, ghidra_name: str, signature: str
) -> bool:
    """Match source identifiers that replace Ghidra's @ with _ before stdcall decoration."""
    name = ghidra_name.strip()
    if "__stdcall" not in signature.casefold() or "@" not in name:
        return False
    source_spelling = name.replace("@", "_")
    pattern = rf"_{re.escape(source_spelling)}@\d+"
    return re.fullmatch(pattern, symbol, flags=re.IGNORECASE) is not None


def is_verified_recovered_import_thunk_alias(
    symbol: str, ghidra_name: str, signature: str
) -> bool:
    """Exact alias for the Ghidra- and original-IAT-verified RtlUnwind thunk."""
    return (
        ghidra_name.strip() == "RtlUnwind"
        and "__stdcall" in signature.casefold()
        and symbol.casefold() == "_imvehft_recovered_rtlunwind@16"
    )


def order_name(symbol: str) -> str:
    # LINK prepends the x86 C leading underscore; C++ and fastcall names are
    # already decorated and must remain untouched.
    if symbol.startswith(("?", "@")):
        return symbol
    return symbol[1:] if symbol.startswith("_") else symbol


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("objects_dir", type=Path)
    parser.add_argument("function_map", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("--report", type=Path, required=True)
    args = parser.parse_args()

    rows: dict[int, dict[str, str]] = {}
    with args.function_map.open("r", encoding="utf-8-sig", newline="") as stream:
        for row in csv.DictReader(stream):
            address = int(row["address"], 16)
            if address in rows:
                raise ValueError(f"duplicate candidate address {address:#x}")
            rows[address] = row
    if len(rows) != 705:
        raise ValueError(f"expected 705 function-map rows, found {len(rows)}")

    ordered: list[str] = []
    classified = 0
    address_bound_aliases = 0
    address_named_aliases = 0
    stdcall_aliases = 0
    recovered_thunk_aliases = 0
    fallback: list[str] = []
    unique_symbol_entries = 0
    ambiguous_entries: list[str] = []
    public_symbol_count = 0
    for address, row in sorted(rows.items()):
        obj = args.objects_dir / f"{address:08x}.obj"
        symbols = code_symbols(obj)
        if not symbols:
            raise ValueError(f"candidate has no public .text symbol: {obj}")
        entry_symbols = [
            name
            for name, _ in symbols
            if is_candidate_entry(name, row["ghidra_name"], row["signature"])
        ]
        if entry_symbols:
            classified += 1
        else:
            entry_symbols = [
                name for name, _ in symbols
                if is_address_bound_cpp_entry_alias(name, row["ghidra_name"])
            ]
            if entry_symbols:
                address_bound_aliases += 1
            else:
                entry_symbols = [name for name, _ in symbols if is_address_named_coff_alias(name, address)]
                if entry_symbols:
                    address_named_aliases += 1
                else:
                    entry_symbols = [
                        name for name, _ in symbols
                        if is_stdcall_name_sanitization_alias(
                            name, row["ghidra_name"], row["signature"]
                        )
                    ]
                    if entry_symbols:
                        stdcall_aliases += 1
                    else:
                        entry_symbols = [
                            name for name, _ in symbols
                            if is_verified_recovered_import_thunk_alias(
                                name, row["ghidra_name"], row["signature"]
                            )
                        ]
                        if entry_symbols:
                            recovered_thunk_aliases += 1
                        else:
                            fallback.append(f"{address:08x}:{row['ghidra_name']}")
                            if len(symbols) == 1:
                                entry_symbols = [symbols[0][0]]
                                unique_symbol_entries += 1
                            else:
                                ambiguous_entries.append(f"{address:08x}:{row['ghidra_name']}")
        symbols_sorted = sorted(symbols, key=lambda item: (item[1], item[0]))
        priority = list(dict.fromkeys(entry_symbols))
        ordered.extend(priority)
        ordered.extend(name for name, _ in symbols_sorted if name not in set(priority))
        public_symbol_count += len(set(name for name, _ in symbols))

    normalized = [order_name(name) for name in ordered]
    unique: list[str] = []
    seen: set[str] = set()
    for name in normalized:
        if name not in seen:
            seen.add(name)
            unique.append(name)
    if len(unique) < 705:
        raise ValueError(f"only {len(unique)} unique order symbols for 705 candidates")
    for path in (args.output, args.report):
        if path.exists():
            raise FileExistsError(f"refusing to overwrite {path}")
        path.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text("\n".join(unique) + "\n", encoding="ascii", newline="\n")
    report = {
        "candidate_count": len(rows),
        "objects_with_matched_entry_name": classified,
        "objects_with_address_bound_cpp_entry_alias": address_bound_aliases,
        "objects_with_address_named_coff_alias": address_named_aliases,
        "objects_with_stdcall_name_sanitization_alias": stdcall_aliases,
        "objects_with_verified_recovered_import_thunk_alias": recovered_thunk_aliases,
        "objects_with_unique_public_code_symbol_inferred_entry": unique_symbol_entries,
        "entry_name_unmatched_candidate_count": len(fallback),
        "entry_name_unmatched_candidates": fallback,
        "ambiguous_entry_candidates": ambiguous_entries,
        "distinct_public_text_symbol_count": public_symbol_count,
        "order_symbol_count": len(unique),
        "order_file_sha256": hashlib.sha256(args.output.read_bytes()).hexdigest().upper(),
        "object_scope": str(args.objects_dir),
        "function_map": str(args.function_map),
        "limitations": [
            "The order file controls public COMDAT symbols only; static functions are not orderable with LINK /ORDER.",
            "A successful ordered link does not establish original RVA, semantic, startup, or runtime equivalence.",
        ],
    }
    args.report.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(
        f"PASS candidates={len(rows)} matched_entries={classified} address_bound_aliases={address_bound_aliases} "
        f"address_named_aliases={address_named_aliases} "
        f"stdcall_aliases={stdcall_aliases} "
        f"verified_import_thunk_aliases={recovered_thunk_aliases} "
        f"unique_symbol_inferred={unique_symbol_entries} "
        f"ambiguous_entries={len(ambiguous_entries)} "
        f"public_text_symbols={public_symbol_count} order_symbols={len(unique)}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
