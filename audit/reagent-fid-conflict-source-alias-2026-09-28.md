# ReAgent FID-conflict source-name alias — 2026-09-28

## Diagnosis and change

The sole RED in the previous full parity report was `0x100189f5`, reported as `FID_conflict:__sopen_helper`. The original hook CSV was correct for Ghidra, and the C++ candidate body existed as `FID_conflict___sopen_helper` in the exact address-named TU. ReAgent `SourceIndexer.find_in_candidate_translation_unit()` only searched for a literal identifier and therefore could not resolve Ghidra's pseudo-name spelling.

ReAgent now converts the narrowly scoped `FID_conflict:<C-identifier>` form to the corresponding single C identifier by replacing the separator colon with an underscore, and resolves it only in the exact address-named TU. It does not rewrite hook data or perform a workspace-wide fuzzy search. Regression coverage is in `reagent/tests/test_parity/test_source_indexer.py`. Pre-edit snapshots of the already locally modified files are:

- `reagent/src/re_agent/parity/source_indexer.py.pre-fid-conflict-alias-20260928.bak`
- `reagent/tests/test_parity/test_source_indexer.py.pre-fid-conflict-alias-20260928.bak`

The authoritative original hook CSV was not changed (SHA-256 `371C349669FA528896ECE638279EC97AF5C0514C6532C4CC5F563C35433BE077`).

## Fresh evidence

- ReAgent `test_source_indexer.py`: **21 passed**.
- ReAgent `test_audit_regressions.py` after the Doctor wording regression: **30 passed, 12 skipped**.
- ReAgent tests excluding LLM/Ghidra-marked integrations after both fixes: **224 passed, 15 skipped**; no model calls were made.
- Full ReAgent 0.4.0 parity with the unmodified original 705-hook CSV: **705 GREEN / 0 YELLOW / 0 RED**, report `build/parity-fid-conflict-sourceindexer-fix-20260928.json`.
- Fresh independent ReAgent objective verifier: **705 PASS / 0 FAIL / 0 UNKNOWN**, report `audit/objective-post-fid-conflict-sourceindexer-2026-09-28.json` (structural only).

`re-agent doctor` returned `ready: true` and now explicitly says `Validation gates are disabled; doctor checks setup/evidence only`. This target config has `validation.enabled: false`, empty build/test/runtime command lists, and `require_build/tests/runtime: false`; therefore Doctor's ready bit is **not** evidence that the 705 candidates passed build, test, or runtime validation. The wording fix is in `reagent/src/re_agent/cli/cmd_doctor.py` with regression coverage in `reagent/tests/test_audit_regressions.py`; backups are adjacent `.pre-doctor-validation-disabled-note-20260928.bak` files.

This removes a false-negative caused by source-name indexing. A green parity verdict is still static evidence; it does not establish whole-program semantic equivalence, correct loading, or correct in-game behavior. The prior 705/705 compile and 705 structural objective PASS still do not replace the missing original ImVehFt project/source or successful game test.
