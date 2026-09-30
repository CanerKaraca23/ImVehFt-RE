# `0x10006790` state-2..4 wrapper integration differential — 2026-09-29

## Ghidra findings and candidate fixes

Integrating the actual candidate `0x10003f80` wrapper into the mapped original
versus candidate test exposed two further mismatches in `src/functions/10006790.cpp`:

1. Original assembly explicitly sets `ESI = [EBX]` and `EDI = 1` before the
   `FUN_10003f80` registration call, or `EDI = 0` on the alternate path. The
   candidate's ordinary no-argument C call left those implicit wrapper inputs
   unspecified. Candidate API observations initially showed the query object
   as the registration context and garbage as the mode. The candidate now
   establishes the Ghidra-prescribed ESI/EDI values before each wrapper call.
2. Original assembly passes `[EBX+5]` to each `0x6c2230` lookup. The candidate
   incorrectly passed the state byte `[EBX+0x14]`. Both candidate lookups now
   pass `bytes[5]`.

The pre-edit source snapshots are preserved:

- `src/functions/10006790.cpp.pre-state234-esiedi-discrepancy-20260929.bak`
  (SHA-256 `840FD4C239AC6727DCC68449240979F29C5FE375E83B197DD4FC80FA5C136180`)
- `src/functions/10006790.cpp.pre-state234-known-query-byte-20260929.bak`
  (SHA-256 `11E42EFA0D668D76A0FCD2C260F51F40F8C3DCC89AAD9C79D25970287417E706`)

## Mapped original-vs-candidate evidence

The harness maps the pinned ASI without startup and links the actual candidate
objects for `0x10006790`, `0x10003f80`, `0x10003fb0`, and `0x10003fe0`. It
compares:

- 5,760 state-2/state-3 arithmetic cases, exact matrix receiver/angle bits,
  record bytes, stack balance, and callee-saved registers;
- 4 direct `bytes[4] == 0` registration cases;
- 12 `bytes[4] == 2..4` cases across file types 2, 3, and 4, covering first
  lookup result 0, second lookup result 1, an unrecognized result with no
  transition, and the mode-0 wrapper path.

Result: **5,776/5,776 paired cases passed**. The test checks query context and
selector, lookup count, actual wrapper API order/context/callback pointers/mode,
state-record bytes, CMatrix arguments, ESP balance, and EBX/ESI/EDI preservation.
Both lookup targets and both GTA API targets are deterministic recorders; the
matrix operation is also recorded rather than dispatched to GTA.

Artifacts:

- Harness: `tests/runtime_10006790_cmatrix_setrotatexonly_differential.cpp`
- Runner: `scripts/test-10006790-cmatrix-setrotatexonly-differential.ps1`
- Object set: `build/recheck/strict-xcode-nogs-o1-10006790-state234-final-20260929/`
- Run: `build/abi-harness/10006790-state234-final-20260929/`
- Harness SHA-256: `7F674CCD97672AD0D98910B6E5F49695AEFB218F10DB3873E7EC89380F236157`
- Executable SHA-256: `5BF392E0E5AFE29EFB72D61E165A955814799F634D34741570EB6EEBDA524B15`
- Candidate source SHA-256: `131C4F75972E12567F27724D4EE7D91DFD961C6FDB07D2922E961AFC616069EC`
- Candidate object SHA-256: `2CC3674BDC7E8D9FAF1476FDA59839F366CAC1A680A3420EF49FE3E52DA375FE`

## Whole-set gates after the source correction

- Strict MSVC x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-`: **705/705 compiled**;
  `build/strict-xcode-nogs-o1-10006790-state234-final-20260929.json`.
- Independent ReAgent objective: **705 PASS / 0 FAIL / 0 UNKNOWN**;
  `audit/objective-independent-10006790-state234-final-2026-09-29.json`.
- ReAgent parity: **705 GREEN / 0 YELLOW / 0 RED**;
  `build/parity-10006790-state234-final-20260929.json`.
- Both source manifests refreshed for 705 entries with pre-refresh backups.

These aggregate checks are structural/build evidence, not semantic proof for all
705 functions. This differential covers selected `0x10006790` paths only; live
GTA side effects, other branches/callers, production linking/ASI layout,
initialization, and in-game behavior remain unverified.
