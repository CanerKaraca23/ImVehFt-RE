# Fixed legacy-section / separate candidate-code linker probe

Date: 2026-09-29. This is an isolated MSVC 14.44 x86 linker experiment for a
possible layout in which the original image sections retain their legacy VAs
and reconstructed function bodies live in a separate executable section.
Nothing in the installed ASI or current candidate diagnostic DLL was modified.

## Original image facts

The hash-pinned installed `ImVehFt.asi` is
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`, PE32/x86,
image base `0x10000000`, `SizeOfImage=0x43000`, entrypoint `0x100111B3`.
Its relevant sections are:

| Section | VA | Virtual size | Raw size |
|---|---:|---:|---:|
| `.text` | `0x10001000` | `0x2027B` | `0x20400` |
| `.rdata` | `0x10022000` | `0x6F44` | `0x7000` |
| `.data` | `0x10029000` | `0x1455C` | `0x10A00` |
| `.rsrc` | `0x1003E000` | `0x2B8` | `0x400` |
| `.reloc` | `0x1003F000` | `0x3F44` | `0x4000` |

## Entry-stub space check

Using all 705 mapped candidate entries and the original `.text` end as the
final boundary (`0x1002127B`, the section virtual end): 703 entries can reserve a five-byte `E9 rel32`
stub; two entries three bytes apart instead use non-overlapping two-byte
`EB rel8` stubs and individual five-byte relays at `0x10018F9C` and
`0x10020453`. The last entry is `0x10021267`, leaving `0x14` bytes before the
`.text` virtual end, so it has a bounded five-byte slot. Both rel8 displacements are
in range; relay intervals do not overlap any modeled entry stub. The 12
Ghidra hook CFG spans from `audit/asi-hook-target-cfg-2026-09-27.csv` intersect
zero of these modeled stubs. This only checks address intervals, not all
undocumented code/data owners or hook execution semantics.

## Actual linker experiment

The probe source is `tests/layout_probe/section_order_probe.c`; section
reservations are in adjacent MASM/resource files. VS 2022 Build Tools 14.44
linked PE32/x86 output
`build/layout-probe/section-order-20260929-v15/probe.dll`, SHA-256
`58999E2B97D56EE1DDA1AA00C8F5EFF70BC877034129F67606997F39CC49E42B`.
The output has `.text` at `0x10001000` (virtual/raw size `0x20400`) and the
simple candidate body in executable `.xcode` at `0x1003F000`. A resource
section is emitted after it at `0x10040000`. This proves a separate executable
candidate section can be linked after a legacy-sized `.text` range.

The full original section map is still **not** preserved. `.rdata` starts at
`0x10022000` but ends at virtual offset `0x7028`; `.data` therefore starts at
`0x1002A000`, not `0x10029000`. The map identifies the linker-generated
`.rdata$voltmd` (`0x18`) and `.rdata$zzzdbg` (`0xB0`) pieces; the PE Debug
Directory itself is `0x1C`. I also confirmed the last candidate entry at
`0x10021267` remains within the original `.text` virtual end `0x1002127B`.
The probe sections contain placeholder data, the only candidate body is a
trivial return-value function, its resource is synthetic, and `/FIXED` strips
base relocations. Original resources/relocations, CRT/TLS state, hooks, and
all 705 bodies are absent. This DLL is not an ASI and must not be installed.

## Consequence

The earlier body-overlap problem has a plausible architectural route: keep the
legacy image area for original bytes plus entry stubs, and place rebuilt
bodies separately. The small-entry relay issue and final-entry boundary are
now bounded. The remaining concrete blocker is fitting linker-generated
read-only/debug metadata into the original `.rdata` padding (or relocating it
with correct directory updates) so `.data` returns to its original VA, then
integrating original base relocations, resources, CRT/TLS/startup, hook shims,
and all 705 bodies. Full-image linking, semantic validation, installer
execution, and GTA runtime validation remain open.
