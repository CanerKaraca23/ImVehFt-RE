#!/usr/bin/env python3
"""Generate relocatable tail-jump labels for the installer's 22 rel32 hooks."""

from __future__ import annotations

import argparse
import csv
import json
import re
import struct
from pathlib import Path


INVENTORY_ROW = re.compile(
    r"\|\s*(E8|E9)\s*\|\s*`(0x[0-9A-Fa-f]+)`\s*\|\s*`(0x[0-9A-Fa-f]+)`\s*\|\s*`(0x[0-9A-Fa-f]+)`\s*\|"
)


def public_code_entry(path: Path) -> str:
    obj = path.read_bytes()
    machine, section_count, _, symbol_ptr, symbol_count, optional_size, _ = struct.unpack_from(
        "<HHIIIHH", obj, 0
    )
    if machine != 0x14C or optional_size:
        raise ValueError(f"not an x86 COFF object: {path}")
    section_names = {
        i + 1: obj[20 + i * 40 : 28 + i * 40].split(b"\0", 1)[0].decode("ascii")
        for i in range(section_count)
    }
    strings_at = symbol_ptr + symbol_count * 18
    strings_size = struct.unpack_from("<I", obj, strings_at)[0]
    strings = obj[strings_at : strings_at + strings_size]
    matches: set[str] = set()
    index = 0
    while index < symbol_count:
        at = symbol_ptr + index * 18
        name_field = obj[at : at + 8]
        if name_field[:4] == b"\0\0\0\0":
            offset = struct.unpack_from("<I", name_field, 4)[0]
            end = strings.find(b"\0", offset)
            name = strings[offset:end].decode("ascii")
        else:
            name = name_field.split(b"\0", 1)[0].decode("ascii")
        value, section_no = struct.unpack_from("<Ih", obj, at + 8)
        storage_class, aux_count = obj[at + 16], obj[at + 17]
        if (
            storage_class == 2
            and value == 0
            and section_names.get(section_no, "").startswith(".text")
        ):
            matches.add(name)
        index += 1 + aux_count
    address_tag = path.stem.lower()
    matches = {name for name in matches if address_tag in name.lower()}
    if not matches:
        raise ValueError(f"expected an address-named external code entry in {path}; found none")
    shortest = min(map(len, matches))
    matches = {name for name in matches if len(name) == shortest}
    if len(matches) != 1:
        raise ValueError(f"ambiguous address-named external code entry in {path}; found {sorted(matches)}")
    return matches.pop()


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--inventory", type=Path,
        default=Path("audit/installer-rel32-target-inventory-2026-09-27.md"),
    )
    parser.add_argument("--function-map", type=Path, default=Path("audit/function-name-map.csv"))
    parser.add_argument("--hook-cfg", type=Path, default=Path("audit/asi-hook-target-cfg-2026-09-27.csv"))
    parser.add_argument("--objects-dir", type=Path, required=True)
    parser.add_argument("--asm", type=Path, required=True)
    parser.add_argument("--manifest", type=Path, required=True)
    args = parser.parse_args()
    if args.asm.exists() or args.manifest.exists():
        parser.error("refusing to overwrite existing outputs")

    inventory = args.inventory.read_text(encoding="utf-8-sig")
    raw_patches = [
        (int(site, 16) + 1, int(displacement, 16), int(target, 16))
        for _opcode, site, displacement, target in INVENTORY_ROW.findall(inventory)
    ]
    hook_targets: set[int] = set()
    with args.hook_cfg.open(encoding="utf-8-sig", newline="") as stream:
        hook_targets = {int(row["target"], 16) for row in csv.DictReader(stream)}
    function_addresses: set[int] = set()
    with args.function_map.open(encoding="utf-8-sig", newline="") as stream:
        function_rows = list(csv.DictReader(stream))
        function_addresses = {int(row["address"], 16) for row in function_rows}
    raw_patches = [item for item in raw_patches if item[2] in function_addresses or item[2] in hook_targets]
    if len(raw_patches) != 22:
        raise ValueError(f"expected 22 resolved rel32 stores in installer; found {len(raw_patches)}")
    target_addresses = {target for _, _, target in raw_patches}
    functions = {
        int(row["address"], 16): public_code_entry(args.objects_dir / f"{row['address'].lower()}.obj")
        for row in function_rows if int(row["address"], 16) in target_addresses
    }

    patches: list[dict[str, object]] = []
    for field, displacement, target in raw_patches:
        if target in functions:
            target_symbol = functions[target]
            target_kind = "candidate-function"
        elif target in hook_targets:
            target_symbol = f"_ImVehFtHook_{target:08X}"
            target_kind = "supplemental-hook-shim"
        else:
            raise ValueError(f"installer rel32 at {field:#010x} targets unmapped {target:#010x}")
        patches.append(
            {
                "field_address": f"0x{field:08X}",
                "opcode_address": f"0x{field - 1:08X}",
                "original_displacement": f"0x{displacement:08X}",
                "target_address": f"0x{target:08X}",
                "target_kind": target_kind,
                "target_symbol": target_symbol,
                "wrapper_symbol": f"_IVF_INSTALL_TARGET_{target:08X}",
            }
        )
    if len(patches) != 22:
        raise ValueError(f"expected all 22 rel32 stores to resolve; found {len(patches)}")

    by_target: dict[int, dict[str, object]] = {}
    for patch in patches:
        target = int(str(patch["target_address"]), 16)
        existing = by_target.get(target)
        if existing and existing["target_symbol"] != patch["target_symbol"]:
            raise ValueError(f"conflicting target symbol mappings for {target:#010x}")
        by_target[target] = patch

    lines = [".386", ".model flat", "option casemap:none", ""]
    for target, item in sorted(by_target.items()):
        lines.append(f"EXTERN {item['target_symbol']}:PROC")
    lines.extend(["", ".code", ""])
    for target, item in sorted(by_target.items()):
        wrapper = str(item["wrapper_symbol"])
        target_symbol = str(item["target_symbol"])
        lines.extend(
            [f"PUBLIC {wrapper}", f"{wrapper} LABEL BYTE", f"    JMP {target_symbol}", ""]
        )
    lines.extend(["END", ""])

    args.asm.parent.mkdir(parents=True, exist_ok=True)
    args.asm.write_text("\n".join(lines), encoding="ascii", newline="\n")
    manifest = {
        "scope": "22 original installer rel32 sites from the preserved target inventory mapped to relocatable C-linkage tail-jump wrappers",
        "patch_site_count": len(patches),
        "unique_destination_count": len(by_target),
        "patches": patches,
    }
    args.manifest.parent.mkdir(parents=True, exist_ok=True)
    args.manifest.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    print(
        f"patch_sites={len(patches)} unique_targets={len(by_target)} "
        f"candidate_targets={sum(p['target_kind'] == 'candidate-function' for p in by_target.values())} "
        f"shim_targets={sum(p['target_kind'] == 'supplemental-hook-shim' for p in by_target.values())} "
        f"output={args.asm}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
