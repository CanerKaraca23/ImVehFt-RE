# `1001081f` recovered `_fclose` dual-linkage repair — 2026-09-29

## Finding and correction

The reconstructed function is identified by the original Ghidra/name map as
`_fclose`, but its source previously defined a C++-mangled `fclose` symbol.
Appended candidate calls therefore resolved to the VS2022 static UCRT's
`_fclose`, not this recovered candidate. A linker `/alternatename` alone did
not override the static archive definition; the diagnostic map still selected
`libucrt:fclose.obj`.

The candidate now defines `fclose` with C linkage, producing the expected
COFF `_fclose` symbol, and adds an alternate name from the prior C++ spelling
`?fclose@@YAHPAU_iobuf@@@Z` to `_fclose`. The exact C++ name and `_fclose` both
resolve to `1001081f.obj` in the successful diagnostic link map; the UCRT
`_fclose` entry is no longer selected. Pre-change copies are retained as
`src/functions/1001081f.cpp.pre-cdecl-fclose-link-alias-20260929.bak`,
`src/functions/1001081f.cpp.pre-direct-c-fclose-linkage-20260929.bak`, and
`src/functions/1001081f.cpp.pre-cxx-fclose-alias-20260929.bak`.

The candidate object's `_fclose` root body is 74 bytes, has five `REL32`
fixups, and is byte-identical to the previous C++-mangled body. The 425-thunk
placement plan refresh changes only this root-symbol name at `0x1001081f`; its
body length, placement coordinates, instruction-boundary evidence, and
relocation span are unchanged. This plan refresh does not claim those
coordinates were independently recomputed from a complete production link.

## Fresh checks and integration limits

- Strict MSVC x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-`: **705/705**.
- ReAgent 0.4.0 parity: **705 GREEN / 0 YELLOW / 0 RED**.
- Independent objective verifier: **704 PASS / 1 FAIL / 0 UNKNOWN**. The one
  failure is the previously documented `10011724` ASM call counter (four
  symbolic calls versus seven Ghidra calls; the three indirect IAT calls are
  not counted). Its byte-exact post-fixup body evidence remains documented in
  `10011724-context-exact-asm-followup-2026-09-29.md`.
- Full candidate diagnostic link succeeds with the fresh 705-object set and
  the corrected `_fclose` binding. It remains a diagnostic DLL, not an ASI.
- Refreshed 280/425 site accounting still yields 6,119 HIGHLOW sites,
  12,824 bytes, exact directory round-trip, fitting the original `.reloc`
  capacity. The regenerated report chain is named
  `*-fclose-dual-linkage-plan-*-2026-09-29`.
- Reclassified appended code symbols: 160 unique / 293 occurrences; 13 GTA
  code targets verified in the game `.text`; 12 candidate-name crosswalks / 85
  occurrences; 21 imported APIs / 57 occurrences and nine static CRT symbols
  / 20 occurrences remain for final image integration. The `_fclose` target
  now resolves directly to its candidate entry rather than being among those
  CRT leftovers.

The follow-up `__chkstk` crosswalk audit found that one of the nine apparent
static-CRT symbols is already represented by the original-image candidate at
`0x1001B220` (`__alloca_probe`). Its 43-byte candidate body has no COFF
relocations and matches the pinned original bytes exactly. Updated target
classification maps this compiler helper to that preserved entry, leaving
eight static-CRT symbols / 19 occurrences plus 21 imported APIs / 57
occurrences unresolved. The diagnostic linker still selects its CRT member;
the final image builder must explicitly apply the evidence-backed runtime
crosswalk. Details: [`chkstk-original-entry-crosswalk-2026-09-29.md`](chkstk-original-entry-crosswalk-2026-09-29.md)
and [`appended-code-target-classes-runtime-crosswalk-2026-09-29.json`](appended-code-target-classes-runtime-crosswalk-2026-09-29.json).

A separate name-and-DLL audit also matches all 21 direct external API symbols
(57 callsites) to unique imports in the pinned original ASI's KERNEL32.dll or
USER32.dll IAT. These are not yet code-resolved: each REL32 call needs a
call-compatible thunk targeting the matched IAT slot. See
[`appended-code-api-original-iat-crosswalk-2026-09-29.json`](appended-code-api-original-iat-crosswalk-2026-09-29.json).

No final PE/ASI bytes were assembled or loaded. Full import/CRT/startup/hook
integration, loader verification, and in-game GTA testing remain open. The
source was changed only to correct symbol linkage; the original pinned ASI is
unchanged.
