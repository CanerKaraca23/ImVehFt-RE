# `10008d20` x87 and shared RDATA width correction (2026-09-28)

## Finding

The prior C++ reconstruction of `FUN_10008d20` compiled under MSVC `/O2` to a
30-byte stub containing only the callback call and return. The loop and
conditional visible in the source were optimized away. This contradicted the
Ghidra export `ghidra_exports/10008d20.json`, whose listing spans
`0x10008d20`–`0x10008d93` and includes x87 comparisons, the conditional branch,
the `+360` loop, and both epilogues. The independent ReAgent parity result had
called this function GREEN, so that status was not sufficient evidence of
machine-code fidelity.

The same Ghidra listing loads 8-byte values from `0x10024e68`, `0x10024e70`,
and `0x10024e78`. The original `.rdata` provider shows these as contiguous
double-sized constants. `10004bb0.cpp` and `10008d20.cpp` previously declared
`0x10024e70/78` as `float`; the `0x10024e68` symbol was also previously
declared as an integer-sized `_PTR_*`. `100073f0.cpp` independently declares
`0x10024e70` as `double`.

## Correction and evidence

- Source backups: `src/functions/10004bb0.cpp.pre-rdata-double-widths-20260928.bak`
  and `src/functions/10008d20.cpp.pre-x87-inline-20260928.bak`. Earlier
  snapshots of the pre-`0x10024e68` type correction are also preserved beside
  those files.
- `10008d20.cpp` now expresses the Ghidra x87 sequence in MSVC x86 inline
  assembly. Its fresh `/O2 /W4 /WX /MT` object has a `.text$mn` length of
  `0x74`; `dumpbin /disasm` matches the Ghidra instruction order and branch
  destinations, and its three memory operands use `DIR32` COFF relocations to
  the named data symbols. This avoids relying on optimizer-sensitive C++ loop
  semantics.
- `10004bb0.cpp` now uses double-width declarations for the same RDATA
  constants. The generated diagnostic data-provider variant exposes their
  C-linkage aliases at the audited `.rdata` offsets; it also resolves the two
  remaining `.data` names at offsets `0x126f8` and `0x131e8`.
- Fresh full-set gates: strict compile `705/705`; independent objective
  `705 PASS / 0 FAIL / 0 UNKNOWN`; ReAgent parity `704 GREEN / 1 YELLOW /
  0 RED`, with `0x100076d0` still the only YELLOW.
- The refreshed function/source hash manifests have separate pre-refresh
  backups ending in `.pre-x87-rdata-width-refresh-20260928.bak`.

## Link and remaining limits

The current linker probe succeeds with 704 candidate objects and emits
`build/link-probe/strict-704-historical-sdk/ImVehFt-x87-rdata-widths-diagnostic-not-ASI.dll`
(781,312 bytes). It is a linker diagnostic, not a production plugin: the
`1001b2b2` object remains excluded from this probe, original `.text` HIGHLOW
relocations and final PE/startup/import/hook layout are not integrated, and
no game test was performed. Do not load this DLL or rename it to `.asi`.
There is still no test-ready `.asi`.
