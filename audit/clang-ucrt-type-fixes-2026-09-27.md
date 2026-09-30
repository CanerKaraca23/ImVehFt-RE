# Clang x86 compatibility follow-up

Date: 2026-09-27. This records a secondary-toolchain check for the existing
705 candidate translation units. It does not change the reference binary or
claim semantic/runtime verification.

## Source fixes and evidence

Three declaration/type-only issues discovered by Clang were corrected, with
pre-edit backups retained beside each candidate source:

- `10003810`: removed hand-written CRT declarations conflicting with UCRT;
  use the declared `FILE*` type and standard `fopen` signature.
- `100119f1`: corrected the function-pointer alias and cast syntax.
- `1001eb27`: renamed the local `_LDBL12` alias that collided with the UCRT
  typedef.

Each changed translation unit compiled with VS2022 x86 `/O2 /W4 /WX /MT` and
with Clang x86 `/O2 /FI locale.h`. MSVC object disassembly before/after the
changes was instruction-identical for all three units, so these portability
fixes did not alter their emitted MSVC instruction streams. Their three rows
in `audit/source-sha256.csv` were refreshed from the current sources (with the
previous manifest backed up); a recomputation over all 705 rows found zero
missing files, hash mismatches, or length mismatches.

## Whole-set results

- Fresh VS2022 x86 strict compile: **705/705 passed**, report
  `build/strict-post-clang-type-fixes-20260927.json`.
- Fresh Clang 22.1.8 x86 compile: **704/705 passed**, report
  `build/clang-x86-post-crt-type-fixes-20260927.json`.
- Clang's only remaining failure is `1001d06f`: the Clang frontend raises an
  access violation while parsing the MSVC naked/SEH `CallCatchBlock`; it
  emits a compiler crash report rather than a source diagnostic. This TU
  compiles in the VS2022 strict set. No source rewrite was made to work around
  a compiler crash in this target-specific assembly routine.
- Source inspection confirms the failing body is explicitly
  `__declspec(naked)` and contains an MSVC `__asm` x86 sequence that manually
  sets up EH4 scope metadata and calls `__SEH_prolog4`; this is not ordinary
  C++ rejected by a second independent compiler. The checked machine has only
  LLVM Clang 22.1.8 available at the tested standard/Visual Studio paths; no
  alternate Clang release was present for a version cross-check.
- Fresh independent ReAgent objective: **705 PASS / 0 FAIL / 0 UNKNOWN**,
  `audit/objective-post-clang-type-fixes-2026-09-27.json`.
- Fresh whole-set ReAgent parity: **704 GREEN / 1 YELLOW / 0 RED**,
  `build/parity-post-clang-type-fixes-20260927.json`. The waiver guard confirms
  13 scoped call-count-only adjudications and preserves the `100076d0`
  semantic warning.

The objective result checks structure, not behavior. The parity yellow and
the open original-project/link and in-game validation gaps remain unchanged.
