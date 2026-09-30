# Current 705-source hash refresh and independent rerun — 2026-09-29

## Why the rerun was necessary

A read-only audit found six rows in the two 705-source manifests whose hashes
did not match the current C++ files: `10001010`, `10001430`, `100014a0`,
`1001023b`, `1001cd37`, and `10020870`. No source file was missing. The
corresponding current edits replace unresolved/non-relocatable exception
vftable references with explicit image aliases. Existing aggregate reports
predated these six exact source contents, so they were not accepted as current
evidence.

Both manifests were refreshed from the current 705 files with the repository
script. Pre-refresh copies are preserved as
`audit/source-sha256.csv.pre-current-705-source-hash-refresh-20260929.bak` and
`audit/function-name-map.csv.pre-current-705-source-hash-refresh-20260929.bak`.
An independent reread found 705 rows in each and zero hash mismatches.

## Full-set checks on the refreshed exact source set

- Strict MSVC 2022 x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-`: **705/705**;
  `build/strict-xcode-nogs-o1-current-705-20260929.json` and objects under
  `build/recheck/strict-xcode-nogs-o1-current-705-20260929/`.
- ReAgent 0.4.0 independent objective verifier: **705 PASS / 0 FAIL / 0
  UNKNOWN**; `audit/objective-independent-current-705-2026-09-29.json`.
- ReAgent 0.4.0 full parity engine with current `src/functions`, the local
  Ghidra JSON exports, and configured semantic/manual rules: **705 GREEN / 0
  YELLOW / 0 RED**;
  `build/parity-current-705-sourcehash-refresh-20260929.json`.
  The reproducible runner is `scripts/run-current-705-reagent-parity.py`.

These aggregate gates are structural and remain insufficient as proof of
semantic equivalence; the previously recorded `10001010` negative control
demonstrates a specific vtable-value error that both green gates miss.

## Focused original-binary check for the vtable blind spot

The `10001010` focused vtable/destructor comparison is documented separately
in `audit/10001010-vtable-destructor-original-differential-2026-09-29.md`.

## Remaining boundary

The focused test redirects only the observed destructor call in the mapped
image and binds the test process heap for the self-free path. It does not
validate general PE loading, production image placement/relocations, all
exception/runtime paths, or actual GTA execution. The aggregate green checks
remain structural; the 705-function set is not thereby semantically proven.
