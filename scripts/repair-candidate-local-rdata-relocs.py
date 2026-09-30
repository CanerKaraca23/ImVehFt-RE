#!/usr/bin/env python3
"""Repair the three stale local-rdata HIGHLOW sites in the experimental PE candidate.

This narrowly scoped follow-up preserves the input candidate and emits a new
candidate. It places the two exact local terminate helpers at the end of .xcode,
resolves their one REL32 call, patches the three corresponding .xrdata DIR32
fields, and moves the three loader HIGHLOW records to their final RVAs.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path

import pefile

BASE = 0x10000000
INPUT_SHA256 = "A0513334C7DE0D5E174FE417E19B886EB6882EFF70C41A3DA34B098476F6B2F4"
OBJECT_SHA256 = "84D12391D08A738B2DF64F7B30CEF90F98AA801F19F420BCC67ADD52DE515A82"
RDATA_SECTION_SHA256 = "D3F60EAB5DC5EB892B162AB4A22E972FB73C4D05DD3ACF0660357D8D1C80D84A"
OLD_SITES = {0x586A8, 0x586A9, 0x586AC}
NEW_SITES = {0x5C6A0, 0x5C818, 0x5C81C}
ABORT_ENTRY = 0x1001705C


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def align(value: int, boundary: int) -> int:
    return (value + boundary - 1) & ~(boundary - 1)


def checksum(data: bytearray, field: int) -> int:
    total = 0
    for off in range(0, len(data) - len(data) % 2, 2):
        if field <= off < field + 4:
            word = 0
        else:
            word = data[off] | (data[off + 1] << 8)
        total = (total & 0xFFFF) + word + (total >> 16)
    if len(data) & 1:
        total = (total & 0xFFFF) + data[-1] + (total >> 16)
    total = (total & 0xFFFF) + (total >> 16)
    total = (total & 0xFFFF) + (total >> 16)
    return (total + len(data)) & 0xFFFFFFFF


def parse_coff_sections(path: Path) -> list[dict]:
    blob = path.read_bytes()
    if sha(blob) != OBJECT_SHA256:
        raise ValueError("10017DDE object hash differs from the audited object")
    machine, count, _, _, _, opt_size, _ = struct.unpack_from("<HHIIIHH", blob)
    if machine != 0x14C or opt_size:
        raise ValueError("expected i386 COFF object")
    out = []
    for number in range(1, count + 1):
        at = 20 + (number - 1) * 40
        name, _, _, size, ptr, _, _, reloc_count, _, flags = struct.unpack_from("<8sIIIIIIHHI", blob, at)
        section_name = name.split(b"\0", 1)[0].decode("ascii")
        raw = blob[ptr:ptr + size]
        if len(raw) != size:
            raise ValueError("truncated COFF section")
        out.append({"number": number, "name": section_name, "bytes": raw,
                    "reloc_count": reloc_count, "flags": flags})
    return out


def reloc_sites(pe: pefile.PE) -> set[int]:
    return {entry.rva for block in pe.DIRECTORY_ENTRY_BASERELOC
            for entry in block.entries if entry.type == 3}


def serialize_relocs(sites: set[int]) -> bytes:
    by_page: dict[int, list[int]] = {}
    for site in sites:
        by_page.setdefault(site & ~0xFFF, []).append(site & 0xFFF)
    out = bytearray()
    for page, offsets in sorted(by_page.items()):
        entries = [0x3000 | offset for offset in sorted(offsets)]
        if len(entries) & 1:
            entries.append(0)
        out.extend(struct.pack("<II", page, 8 + 2 * len(entries)))
        out.extend(struct.pack(f"<{len(entries)}H", *entries))
    return bytes(out)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--candidate", type=Path, required=True)
    ap.add_argument("--object", type=Path, required=True)
    ap.add_argument("--output-asi", type=Path, required=True)
    ap.add_argument("--output-report", type=Path, required=True)
    args = ap.parse_args()
    for output in (args.output_asi, args.output_report):
        if output.exists():
            raise FileExistsError(f"refusing to overwrite {output}")

    image = bytearray(args.candidate.read_bytes())
    if sha(image) != INPUT_SHA256:
        raise ValueError("input candidate hash does not match the audited v5")
    pe = pefile.PE(data=bytes(image), fast_load=False)
    if pe.OPTIONAL_HEADER.ImageBase != BASE:
        raise ValueError("unexpected image base")
    sections = {s.Name.rstrip(b"\0").decode("ascii"): s for s in pe.sections}
    if not {".xcode", ".xrdata", ".reloc"} <= sections.keys():
        raise ValueError("candidate lacks audited appended sections")
    xcode, xrdata, relsec = sections[".xcode"], sections[".xrdata"], sections[".reloc"]
    obj_sections = parse_coff_sections(args.object)
    filt, handler, table = (obj_sections[i - 1] for i in (3, 4, 5))
    if [(filt["name"], len(filt["bytes"]), filt["reloc_count"]),
        (handler["name"], len(handler["bytes"]), handler["reloc_count"]),
        (table["name"], len(table["bytes"]), table["reloc_count"])] != [
            (".xcode", 4, 0), (".xcode", 16, 1), (".rdata", 28, 2)]:
        raise ValueError("terminate helper/table COFF section shapes changed")
    if sha(table["bytes"]) != RDATA_SECTION_SHA256:
        raise ValueError("terminate scope-table bytes differ from audited COFF section")

    xbytes = xcode.get_data()
    xsize = xcode.Misc_VirtualSize
    if len(xbytes) < xsize or xsize != 101243:
        raise ValueError("unexpected current .xcode payload size")
    filter_off = xsize
    handler_off = filter_off + len(filt["bytes"])
    handler_va = BASE + xcode.VirtualAddress + handler_off
    filter_va = BASE + xcode.VirtualAddress + filter_off
    # Section 4 has a single REL32 call at byte offset 12, to _abort at its
    # original entry thunk/body, which remains callable in the candidate text.
    handler_bytes = bytearray(handler["bytes"])
    call_disp = ABORT_ENTRY - (handler_va + 16)
    if not -(1 << 31) <= call_disp < (1 << 31):
        raise ValueError("terminate landing-pad call is outside REL32 reach")
    struct.pack_into("<i", handler_bytes, 12, call_disp)

    reloc_directory = pe.OPTIONAL_HEADER.DATA_DIRECTORY[5]
    reloc_off = pe.get_offset_from_rva(reloc_directory.VirtualAddress)
    old_reloc = bytes(image[reloc_off:reloc_off + reloc_directory.Size])
    old_sites = reloc_sites(pe)
    if not OLD_SITES <= old_sites or old_sites & NEW_SITES:
        raise ValueError("input relocation directory is not the audited pre-repair state")
    new_sites = (old_sites - OLD_SITES) | NEW_SITES
    reloc_blob = serialize_relocs(new_sites)
    if len(reloc_blob) > relsec.SizeOfRawData:
        raise ValueError("repaired relocation directory exceeds the original .reloc raw allocation")

    xraw = xcode.PointerToRawData
    rraw = xrdata.PointerToRawData
    rdata_offset = xrdata.VirtualAddress
    if (rdata_offset + 1672 + 24, rdata_offset + 2052 + 20,
            rdata_offset + 2052 + 24) != tuple(sorted(NEW_SITES)):
        raise ValueError("local-rdata field RVA derivation disagrees with final layout")
    data = bytearray(xrdata.get_data())
    fields = ((1672 + 24, BASE + 0x1072A),
              (2052 + 20, filter_va), (2052 + 24, handler_va))
    for offset, value in fields:
        if data[offset:offset + 4] != b"\0\0\0\0":
            raise ValueError(f"expected unresolved local DIR32 field at .xrdata+{offset:#x}")
        struct.pack_into("<I", data, offset, value)

    if xraw + xsize + 20 > xraw + xcode.SizeOfRawData:
        raise ValueError("local helper sections do not fit existing .xcode raw allocation")
    image[xraw + filter_off:xraw + handler_off] = filt["bytes"]
    image[xraw + handler_off:xraw + handler_off + len(handler_bytes)] = handler_bytes
    image[rraw:rraw + len(data)] = data
    struct.pack_into("<I", image, xcode.get_file_offset() + 8, xsize + 20)
    image[reloc_off:reloc_off + len(reloc_blob)] = reloc_blob
    if len(old_reloc) > len(reloc_blob):
        image[reloc_off + len(reloc_blob):reloc_off + len(old_reloc)] = bytes(len(old_reloc) - len(reloc_blob))
    struct.pack_into("<I", image, relsec.get_file_offset() + 8, len(reloc_blob))
    opt = pe.OPTIONAL_HEADER.get_file_offset()
    struct.pack_into("<II", image, opt + 96 + 5 * 8, reloc_directory.VirtualAddress, len(reloc_blob))
    checksum_off = opt + 64
    struct.pack_into("<I", image, checksum_off, 0)
    struct.pack_into("<I", image, checksum_off, checksum(image, checksum_off))

    parsed = pefile.PE(data=bytes(image), fast_load=False)
    actual_sites = reloc_sites(parsed)
    if actual_sites != new_sites or len(actual_sites) != 6389:
        raise ValueError("post-repair relocation-site set failed exact round-trip")
    parsed_sections = {s.Name.rstrip(b"\0").decode("ascii"): s for s in parsed.sections}
    pxcode, pxrdata = parsed_sections[".xcode"], parsed_sections[".xrdata"]
    mapped_xcode = pxcode.get_data()
    mapped_rdata = pxrdata.get_data()
    if (pxcode.Misc_VirtualSize != xsize + 20
            or mapped_xcode[:xsize] != xbytes[:xsize]
            or mapped_xcode[filter_off:handler_off] != filt["bytes"]
            or mapped_xcode[handler_off:handler_off + 16] != bytes(handler_bytes)):
        raise ValueError("post-emission .xcode payload/header differs from expected helper insertion")
    for offset, value in fields:
        if struct.unpack_from("<I", mapped_rdata, offset)[0] != value:
            raise ValueError(f"post-emission .xrdata field mismatch at {offset:#x}")
    if parsed_sections[".reloc"].Misc_VirtualSize != len(reloc_blob):
        raise ValueError("post-emission .reloc virtual size differs from serialized directory")
    out = bytes(image)
    report = {
        "scope": "Narrow repair of local-rdata relocations/helper placement in experimental v5; not game/runtime validation.",
        "input_sha256": INPUT_SHA256, "output_sha256": sha(out),
        "original_asi_sha256": "409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3",
        "removed_stale_sites": [hex(x) for x in sorted(OLD_SITES)],
        "added_final_local_rdata_sites": [hex(x) for x in sorted(NEW_SITES)],
        "local_data_fields": [{"site_rva": hex(xcode.VirtualAddress + off if off < 0 else xrdata.VirtualAddress + off),
                               "value": hex(value)} for off, value in fields],
        "filter_va": hex(filter_va), "handler_va": hex(handler_va),
        "abort_call_target_va": hex(ABORT_ENTRY), "abort_rel32": call_disp,
        "relocation_sites": len(actual_sites), "relocation_directory_bytes": len(reloc_blob),
        "sections": {sec.Name.rstrip(b"\0").decode("ascii"): {
            "rva": hex(sec.VirtualAddress), "virtual_size": sec.Misc_VirtualSize,
            "raw_size": sec.SizeOfRawData} for sec in parsed.sections},
        "validation": "PE section bytes/headers and relocation directory round-trip; run the separate nonpreferred-base mapped-memory differential before accepting.",
    }
    args.output_asi.write_bytes(out)
    args.output_report.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
