# ReAgent objective verifier: indirect inline-assembly calls

## Finding and correction

The independent objective audit had a sole failure for `10011724`: Ghidra counted seven `CALL` instructions, while ReAgent's C++ source-call counter counted four. The candidate uses three indirect x86 calls (`call dword ptr [DAT_1002207C]`, `[DAT_10022078]`, and `[DAT_10022074]`). The local ReAgent 0.4.0 `INLINE_ASM_CALL_RE` accepted direct identifiers/immediates but not memory operands.

Extended that operand pattern to accept sized `ptr [memory]` forms. Added a regression test with three indirect memory calls and one direct call. Before editing, preserved the existing working versions as:

- `C:/Users/caner/OneDrive/Documents/ImVehFt/reagent/src/re_agent/utils/text.py.pre-inline-asm-indirect-calls-20260929.bak`
- `C:/Users/caner/OneDrive/Documents/ImVehFt/reagent/tests/test_verification/test_objective.py.pre-inline-asm-indirect-calls-20260929.bak`

No candidate function or Ghidra export was changed. All 705 candidate-source hashes still match `source-sha256.csv`.

## Verification

- Focused objective-verifier tests: **24 passed**.
- Full ReAgent test suite: **225 passed, 15 skipped**.
- Fresh independent objective audit: **705 PASS / 0 FAIL / 0 UNKNOWN**, including `10011724`: [`objective-independent-live-705-indirect-asm-fix-2026-09-29.json`](objective-independent-live-705-indirect-asm-fix-2026-09-29.json).
- Independent original-ASI comparison for `10011724`: **297/297 bytes identical** after resolving eight COFF fixups; four original HIGHLOW sites match: [`10011724-inplace-byte-reconstruction-live-2026-09-29.json`](10011724-inplace-byte-reconstruction-live-2026-09-29.json).
- The matching candidate set passes fresh strict MSVC x86 compile **705/705**. After correcting the shared call counter, reran ReAgent parity with the existing independent-parity config, Ghidra exports, manual call-count adjudications, and semantic rules: **705 GREEN / 0 YELLOW / 0 RED**; report: [`parity-objective-fix-2026-09-29.json`](../build/parity-objective-fix-2026-09-29.json). All candidate source hashes were rechecked after the verifier-only change.

## Limits

This corrects a source-analysis undercount; it is not a change to the reconstructed functions and does not independently prove semantic equivalence for the full set. There is still no production-layout `.asi`, no original ImVehFt project/build recipe, and no GTA gameplay validation.
