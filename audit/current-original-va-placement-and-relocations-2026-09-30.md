# Fresh current-object original-VA placement and relocation audit — 2026-09-30

> **Superseded by the current conservative Ghidra-positive plan.** The 283-direct/422-thunk figures and 6,115-site table below describe the earlier placement and omit the 21 absolute-IAT API thunk fixups. Current figures are 284 direct / 421 thunked and 6,136 sites / 12,872 bytes, including those API references. See `placement-plan-conservative-ghidra-positive-2026-09-30.json`, `inplace-base-relocation-reconciliation-conservative-current-2026-09-30-v2.json`, and `all-705-candidate-code-relocation-directory-conservative-current-2026-09-30-v3.json`. This is still an inventory, not an emitted or load-tested PE.

## Current object set and placement

Recomputed placement from the fresh 705-object strict build
`build/recheck/strict-xcode-nogs-o1-10006360-fastcall-full-20260930/`, the
hash-pinned original ImVehFt ASI, its saved Ghidra exports, and the fresh
current-set diagnostic link/map. This supersedes the 2026-09-29 `280 direct /
425 thunk` plan; no original PE bytes were changed.

- Current COFF entry-slot census: 559 candidate bodies fit between bounded
  neighboring entry VAs, 145 exceed that gap, and the final entry fits the
  original `.text` tail. All 705 diagnostic bodies map to executable code and
  have in-range rel32 destinations. See
  `audit/entry-slot-fit-fresh-current-2026-09-30.json` and
  `audit/entry-trampoline-feasibility-fresh-coff-current-2026-09-30.json`.
- Linear disassembly of all 560 initially direct-capable candidates found 286
  ends on original instruction boundaries and 274 that cut an instruction.
  Moving those 274 to entry thunks yields 286 provisional direct bodies / 419
  thunked bodies.
- The Ghidra non-entry xref audit found four references into three of those
  286 candidate spans (two DATA references and two unconditional branches).
  Preserving those original bodies increases the conservative plan to **283
  direct bodies and 422 appended/thunk bodies**. No saved direct branch in the
  exported function assemblies targets the interior bytes `entry+1..entry+4`
  of the 422 thunk windows. This is a static-xref result, not proof against
  computed/runtime references.
- Of the 422 thunk windows, 64 intersect original `.text` HIGHLOW DWORD fields
  (24 fully and 40 partially overwritten); those old relocation records must
  be removed when applying the thunk patches.

## Relocation-directory and payload census

The direct-body reconciliation finds 886 original HIGHLOW fields overlapped
by the 283 direct candidate bodies, 800 new direct DIR32 sites, and zero old
HIGHLOW fields straddling a direct-body end. Combined with the 422 appended
bodies and their same-object `.rdata`, the exact site-set builder removes 950
original HIGHLOW sites across direct-body and thunk-patch ranges, adds 800
direct and 1,584 appended-code/data DIR32 sites, and serializes **6,115** final
HIGHLOW sites to **12,820 bytes**. The serialized directory reparses exactly
and fits the pinned original `.reloc` section. Report:
`audit/all-705-candidate-code-relocation-directory-conservative-current-2026-09-30.json`;
binary site-table probe:
`build/pe-layout-probe/candidate-code-relocs-conservative-current-20260930.bin`.

The 422-body payload census totals 82,818 code bytes and 87,963 bytes including
referenced local `.rdata`; with 512-byte file alignment it is 88,064 bytes.
Its provisional append begins at RVA `0x43000` / raw offset `0x3C600` and ends
at raw offset `0x51E00`. This is sizing only; it does not account for all final
headers, support providers, imports, startup, or complete data-layout needs.

## Remaining address and integration work

Joining the 422-body COFF fixups to the successful diagnostic link map
classified 1,504 undefined-external/alias relocation occurrences: 286 mapped
to diagnostic code symbols, 116 to diagnostic import slots, 952 to symbols
whose names encode original VAs but whose diagnostic providers are displaced,
and 150 to diagnostic providers/runtime data. Diagnostic addresses are not
valid final addresses. All candidate DIR32/REL32 values, same-object data,
external IAT references and provider aliases still need final-address
resolution and application. The 12 supplemental hook shims/installer, CRT
startup, final PE header/section construction, loader test and GTA gameplay
remain unintegrated or unverified. The zero-unresolved diagnostic DLL is not
the production image.

Placement and relocation reports:

- `audit/entry-slot-fit-fresh-current-2026-09-30.json`
- `audit/inplace-candidate-relocations-fresh-current-2026-09-30.json`
- `audit/entry-trampoline-feasibility-fresh-coff-current-2026-09-30.json`
- `audit/inplace-candidate-original-instruction-boundaries-fresh-2026-09-30.json`
- `audit/direct-candidate-interior-ghidra-xrefs-fresh-2026-09-30.json`
- `audit/placement-plan-conservative-current-2026-09-30.json`
- `audit/entry-thunk-relocation-overlap-conservative-current-2026-09-30.json`
- `audit/thunk-entry-window-ghidra-relocation-audit-conservative-current-2026-09-30.json`
- `audit/inplace-base-relocation-reconciliation-conservative-current-2026-09-30.json`
- `audit/appended-thunk-relocation-targets-conservative-current-2026-09-30.json`
- `audit/appended-thunk-payload-census-conservative-current-2026-09-30.json`
- `audit/appended-thunk-link-map-resolution-conservative-current-2026-09-30.json`

Two audit helpers had obsolete hard-coded `148` thunk / `280+425` plan
counts. Their generic validations now accept a consistent 705-entry plan;
pre-edit scripts are retained with `.pre-dynamic-*-20260930.bak` suffixes.
Their fresh runs produced the reports above. Neither helper nor the placement
plan emits or patches an ASI.
