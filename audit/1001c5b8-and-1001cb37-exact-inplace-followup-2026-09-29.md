# Exact in-place body corrections: `1001c5b8` and `1001cb37`

## `1001c5b8` — preserve the following CRT helper

The previous C++ body compiled to 41 bytes, one byte past the original
`__setdefaultprecision` body. The Ghidra export and original `.rdata` pointer
at `0x100221cc` identify `0x1001c5e0` as the next code target; overwriting its
first byte would corrupt that helper. The candidate is now naked x86 matching
the Ghidra instruction sequence. Its `/O1 /GS-` COFF `.xcode` body is exactly
`0x28` (40) bytes. Resolving its two REL32 calls to original targets
`0x1001de9f` and `0x1001184d` produces an exact 40/40-byte match to the
hash-pinned original, ending immediately before `0x1001c5e0`.

## `1001cb37` — match the original shared-tail setup

Ghidra and the original PE encode stack allocation as `ADD ESP,-0x20`. The
candidate's previous `SUB ESP,0x20` had identical stack result but different
machine bytes/condition flags. It was changed to the original form. Resolving
the `__87except` REL32 to `0x1001defe` now yields an exact 60/60-byte match,
including the `0x1001cb40` shared-tail target.

## Backups and current gates

- Previous `1001c5b8` source: `src/functions/1001c5b8.cpp.pre-inplace-body-boundary-20260929.bak`.
- Previous `1001cb37` source: `src/functions/1001cb37.cpp.pre-original-add-esp-exact-20260929.bak`.
- Source manifest backups use `.pre-1001c5b8-boundary-exact-20260929.bak` and
  `.pre-1001cb37-add-esp-exact-20260929.bak` suffixes.
- Fresh full set: strict MSVC x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-`
  **705/705**; ReAgent parity **705 GREEN / 0 YELLOW / 0 RED**; independent
  objective **704 PASS / 1 FAIL / 0 UNKNOWN**. The sole fail remains
  `10011724`: its Ghidra-derived inline assembly body is byte-exact, but the
  objective call counter misses three indirect IAT calls (4 counted vs 7 in
  disassembly). It is retained as a visible tool limitation, not waived.
- A fresh 705-object diagnostic DLL link succeeds with stale `/ORDER` LNK4037
  warnings. It is **not** a production ASI and was not loaded in GTA.

These corrections establish two more exact function bodies and remove the
`1001c5e0` boundary clobber. They do not resolve whole-image layout/base
relocations, original project/SDK provenance, or game runtime validation.
