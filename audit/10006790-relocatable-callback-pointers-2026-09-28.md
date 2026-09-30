# Relocatable callbacks in `FUN_10006790` (2026-09-28)

Ghidra's `10006790.json` shows four registrations at `0x10006833..0x10006877`:
the GTA routines at `0x7f1200` and `0x7f0dc0` receive ImVehFt callbacks
`0x10003fe0` and `0x10003fb0`, respectively. Each callback pair is registered
in both the enable and disable branches. The candidate had embedded those
preferred ImVehFt addresses directly.

Both targets are recovered candidate functions. Their Ghidra signatures and
candidate declarations were checked: `FUN_10003fe0(int,int)` returns void;
`FUN_10003fb0(uint32_t,uint32_t)` returns `uint32_t`. `10006790.cpp` now
converts correctly typed function pointers through `uintptr_t` for the GTA
callback API instead of embedding `0x10003fe0`/`0x10003fb0`.

Backup: `src/functions/10006790.cpp.pre-relocatable-callback-pointers-20260928.bak`.

The strict x86 MSVC object emits four `DIR32` relocations (two per callback
symbol) and no longer contains either fixed ImVehFt callback VA. Full current
tree checks:

- strict `/O2 /W4 /WX /MT`: **705/705**;
- independent objective verifier: **705 PASS / 0 FAIL / 0 UNKNOWN**;
- ReAgent 0.4.0 parity: **705 GREEN / 0 YELLOW / 0 RED**;
- source SHA-256 manifest: **705 rows / 0 mismatches**;
- normal diagnostic link: all **705** current candidate objects, no linker
  diagnostics.

The latest original-ImVehFt VA inventory is v10: **58 occurrences**, **43
unique `.text` VAs**, **24 exact candidate entries**, and **19 non-entry VAs**.
It is a literal inventory, not a semantic classification. The `0x7f1200` and
`0x7f0dc0` callees are still version-specific GTA executable preferred VAs;
the diagnostic output remains a DLL with non-original PE layout, not a
test-ready ASI. Loader/hook integration and in-game behavior remain unverified.
