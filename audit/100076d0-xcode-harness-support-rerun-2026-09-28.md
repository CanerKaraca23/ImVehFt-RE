# `0x100076d0` harness support for `.xcode` candidate objects

Date: 2026-09-28. The harness's fixed-address operand scanner previously
searched only executable `.text`; the fresh whole-set strict build puts
candidate bodies in executable `.xcode`, so the harness failed before running
the candidate. Updated the test harness to scan every executable PE section,
count/validate all expected operands before patching, check patch-site overlap
by virtual address, and change protection/flush instruction cache per operand.
The candidate C++ source was not changed.

## Backup and reproducible results

- Pre-edit harness backup:
  `tests/runtime_100076d0_model_info_harness.cpp.pre-xcode-executable-scan-20260928.bak`
  SHA-256 `95C52B64E9CD85EDF6959BF1929842EF30270256BD2B03B603F1C8B201B2BD6F`.
- Updated harness source SHA-256:
  `E0368E999044B0B05189B605F64804966CBCDF7E7B478CF085BFCCF289D1D411`.
- Current candidate source SHA-256:
  `149AE0C88160BA6DFDBDF6097853373074DEC2133BC5ADF066EB6DD8A84EEEAD`,
  equal to the current source-manifest entry.
- Fresh `.xcode` candidate object SHA-256:
  `DB2397B98559E44DDF385668D668622381181A7053ADA11764831ACA5646A94B`.
- `.xcode` harness:
  `build/abi-harness/100076d0-xcode-section-harness-20260928.exe`, SHA-256
  `ED403A678178458178352D3BB755D8E14E7A77378BA983515068E7A39F1139CD`;
  **10/10 fresh processes passed**.
- Legacy `.text` candidate-object harness:
  `build/abi-harness/100076d0-text-section-harness-rerun-20260928.exe`, SHA-256
  `5A9520E712E8D3724E545C97C4C7D57328CB93B2018B5E77E418715E9BD02954`;
  **10/10 fresh processes passed**.
- Both use the hash-pinned original ASI SHA-256
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

The test matrix is the established controlled original-vs-candidate set:
16 selector cases in each of generic and synthetic vehicle contexts, plus
damaged-lights lookup, controlled nested re-entry, and callback-time context
flip. Across the two object layouts this reproduces 700 paired invocations
with zero mismatches (350 for each ten-process suite).

## Limits

This resolves a test-harness section-selection problem and proves the revised
harness works with both object layouts. The fixed-address code/globals and
external APIs still use synthetic redirections; nested re-entry and callback
state changes are deliberately controlled. It does not establish live
RenderWare callback behavior, gameplay, production PE relocation/startup, or
semantic correctness of all 705 functions. The `0x100076d0` runtime finding
remains open.
