# `fopen` linkage repair and fresh 705-set rerun (2026-09-29)

## Change and evidence

- Hash-pinned original `ghidra_exports/10010734.json` identifies the function as
  VS2010 `_fopen`, `__cdecl`, taking filename and mode and forwarding to
  `__fsopen(..., 0x40)`.
- `src/functions/10010734.cpp` now emits the C-linkage `_fopen` symbol and
  retains an MSVC `/alternatename` directive from the old decorated candidate
  spelling to `_fopen`. A pre-change source copy is retained next to the source.
- Fresh MSVC x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-` output pushes `0x40`, then
  mode and filename in cdecl order, calls the recovered `__fsopen` candidate,
  removes 12 argument bytes, and returns. COFF has a `REL32` relocation to
  `?__fsopen@@YAPAU_iobuf@@PAD0H@Z`; the link map resolves both `_fopen` and
  the legacy decorated spelling to the same candidate address.
- This is source/decompile/COFF/link evidence. The optimized object omits the
  original frame-pointer prolog and uses ESP-relative operands; no dedicated
  original-binary runtime differential was run for this target.

## Fresh full-set checks

- Strict MSVC x86 build report: `build/strict-xcode-nogs-o1-fopen-linkage-alias-final-20260929.json`, 705/705 translation units compiled.
- Independent ReAgent objective rerun: `audit/objective-independent-fresh-705-2026-09-29-fopen.json`, 705 PASS, 0 FAIL, 0 UNKNOWN.
- ReAgent 0.4.0 parity rerun: `build/parity-independent-fresh-705-2026-09-29-fopen.json`, 705 GREEN, 0 YELLOW, 0 RED.
- These gates are structural and do not establish semantic equivalence or runtime correctness. Existing negative-control evidence demonstrates that a broken candidate can still receive structural green status.

## Link and runtime boundary

- The latest combined link is
  `build/link-probe/entry-exact-nogs-o1-fopen-linker-alias-no-original-text-20260929/ImVehFt-entry-xcode-single-provider-fopen-linker-alias-no-original-text-not-ASI.dll` (SHA-256 `A7B97135EEA9BD007B00F6A5316B31C06DCC25B2573E7538E6208D5988BD8005`).
- The file is explicitly a diagnostic DLL, not an installable `.asi`. Its PE
  section placement/entry point do not restore the original image layout. No
  GTA launch or in-game test was performed.
- Fresh rerun report hashes: objective `D1B07D154481810D15B66B37AF0153F2636A09709ABD5B00F00FA21405F271F3`; parity `3C5B947F86CEB4D844C7AE1AABDAFEB1FED458190C0E034A0F3C078020B118DF`.
