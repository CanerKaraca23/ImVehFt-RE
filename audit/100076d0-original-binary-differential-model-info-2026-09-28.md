# `100076d0` original-binary differential: model-info routes

Date: 2026-09-28.

## Result

The current candidate COFF for `FUN_100076d0` was executed against the
installed 2014 ImVehFt image in a PE32/x86 harness. Across ten fresh harness
processes, both the original function and candidate matched on all 16
selectors (`0xFF` through `0xF0`) in both the generic-context and synthetic
vehicle-context routes, plus the nonzero `vehiclelights` lookup followed by
the `vehiclelights_dam` replacement path, nested callback re-entry, and a
callback-time global-flip case with a seeded `[EBP-8]` slot: **350 paired
invocations, zero mismatches** (320 selector cases and 10 each of the three
additional cases).

For every pair, the harness compared the return pointer, the complete 24-byte
input record, all four write-slot values, cursor advance, and deltas for
generic-context, vehicle-system, texture-lookup, and texture-callback stub
calls. It also compares lookup argument IDs and names for the damaged-lights
case. The 16 model-info entries carried unique word/byte sentinels, so every
selector's indexed data transfer was distinguishable. The model-info fixtures
take the zero-texture-id path and return after those writes. The additional
lookup fixture returns deterministic synthetic values for both lookup names.
For the stack-slot case, separate x86 entry wrappers seed `[EBP-8]` in the
candidate and original frames. A controlled callback stub changes
`DAT_1003c1fc` from zero to a synthetic vehicle context; return value, complete
input record, write slots, cursor, callback arguments, palette bytes, and
stub-call deltas are compared. In the separate nested-reentry case, the stub
re-enters the candidate during candidate execution and the original function
during original execution; both nested and outer results are checked.

## Reproduction and provenance

- Original reference: `C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi`
- Original SHA-256: `409F0DF7AE579841DB05C3EC6AD0A9AFC579194632874962E1BDEE0CCF020D3`
- Candidate object: `build/recheck/strict-all-live-20260928-2/100076d0.obj`
- Candidate object SHA-256: `A227D6163003883A003FD20606F571E8482552252F8AB261C7903BA116DDCB4E`
- Candidate source SHA-256: `149AE0C88160BA6DFDBDF6097853373074DEC2133BC5ADF066EB6DD8A84EEEAD`; it matches `audit/source-sha256.csv` and the source set used by the latest recorded 705-unit validation.
- Harness executable: `build/abi-harness/100076d0-model-info-harness-20260928-152830-160.exe`
- Harness SHA-256: `AE91B3875B601CA69B91DFBAEAEF181B9E9758C660E75569BE7FE3DBBD6E28D6`
- Harness source SHA-256: `95C52B64E9CD85EDF6959BF1929842EF30270256BD2B03B603F1C8B201B2BD6F`
- Reproduction: initialize VS 2022 x86 tools, then run
  `scripts/test-100076d0-model-info-harness.ps1 -ObjectPath build/recheck/strict-all-live-20260928-2/100076d0.obj -Repetitions 10`.
- Compiler flags: MSVC x86 `/std:c++20 /O2 /W4 /WX /MT /GS`; the script hashes
  the reference image and fails closed on mismatched operand/call counts.

The first attempt exposed a counting-model mismatch: a Ghidra reference count
and a byte-window scan are not equivalent. Targeted `dumpbin /disasm` over the
original function confirmed four executable immediate loads of `0x007F39F0`
(at `0x10007A16`, `0x10007D61`, `0x10007DA0`, and `0x10007F27`); the harness
now expects and redirects the four observed references. The source and
candidate COFF were not modified by the harness.

The callback differential also caught and corrected two harness-fixture
problems before it passed: the original's indexed `0x1003C1A8` data was mapped
to a pointer cell instead of the synthetic array itself, and the comparison
used the candidate callback count as the original count's baseline despite
resetting that counter. Address-operand discovery is now two-pass (count and
validate first, then patch recorded sites) so edits cannot create additional
matches while the scan is running. The successful 10-process rerun includes
all four differential groups above.

Harness-source backups were preserved before the corrections and differential
extensions, including
`tests/runtime_100076d0_model_info_harness.cpp.pre-original-nested-reentry-differential-20260928.bak`.

## Scope limits

This is bounded original-vs-candidate differential evidence, stronger than
candidate-only synthetic tests, but it does not close the whole function or
project. The test maps the original PE at its preferred base, redirects its
fixed-address globals/API references and selected internal calls to shared
synthetic fixture storage/stubs. The model-info cases use zero texture IDs;
the damaged-lights case uses deterministic synthetic lookup results and does
not validate GTA's texture dictionary. The stack-slot case forces a context
change in a synthetic stub; it checks original/candidate behavior only under
those constructed conditions, not whether a real RenderWare/driver path can
cause them. The nested re-entry test is also a controlled stub-triggered
re-entry, not proof that the real texture/raster destroy chain re-enters this
function. Live GTA state, plugin initialization, and gameplay remain untested.
It does not prove byte-identical output, recover original source, produce a
production `.asi`, or validate all 705 functions. Keep the broader
semantic/runtime status open.
