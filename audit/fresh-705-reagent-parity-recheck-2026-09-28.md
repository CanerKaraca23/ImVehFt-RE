# Fresh 705 ReAgent parity and guard reconciliation

Date: 2026-09-28

## Current evidence

- The saved current-source ReAgent 0.4.0 parity report
  `build/parity-live-current-20260928.json` contains 705 results: **705 green,
  0 yellow, 0 red, 0 unknown**.
- The 13 scoped manual findings remain explicitly `call-count-only`; the
  updated guard `scripts/audit-reagent-callcount-adjudications.py` passes on
  that report and rejects a missing call-count scope or suppression boundary.
- The previous 704/1 guard encoded the old `100076d0` source-pattern warning.
  That warning tracked the unconditional `[EBP-8]` initialization mismatch;
  the Ghidra-backed correction is recorded in
  `audit/100076d0-conditional-stack-slot-correction-2026-09-28.md`. Its
  disappearance is not evidence that callback behavior is settled.
- The `100076d0` finding still explicitly says indirect RenderWare callback
  and re-entry behavior is untested. The focused test report
  `audit/100076d0-model-info-index-runtime-harness-2026-09-28.md` uses
  controlled/stub callbacks, so this behavioral risk remains **OPEN** in
  `audit/status.json`.
- Independent objective evidence remains 705 PASS / 0 FAIL / 0 UNKNOWN in
  `audit/objective-live-2026-09-28-2.json`. This recheck compared the current
  tree to both that report and `audit/source-sha256.csv`: 705 entries each,
  zero SHA-256 mismatches.
- The fresh strict compile is recorded in
  `audit/fresh-705-validation-rerun-2026-09-28-2.md`: 705/705 MSVC x86 strict
  translation-unit builds. ReAgent is a locally modified 0.4.0 checkout, not
  a pristine upstream run.

## Validation boundary

ReAgent green, objective PASS, hashes, and strict compilation are not proof of
semantic equivalence. No `.asi` exists under this build tree; the linked DLLs
are diagnostic-only, and neither the original project/build recipe nor live
GTA/RenderWare validation is available. No background reverse/build process
was running when checked. Do not mark the 705-function objective complete.
