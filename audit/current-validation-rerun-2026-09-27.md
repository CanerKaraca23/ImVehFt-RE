# Current-tree validation rerun

Date: 2026-09-27. All checks below were run against the current 705-file
`src/functions` tree. No candidate source file was changed in this rerun.

## Results

- VS 2022 x86 strict compile: **705/705 pass, 0 fail**, `/std:c++20 /O2
  /W4 /WX /MT /c`. Fresh objects and report:
  `build/recheck/strict-live-rerun-20260927/` and
  `build/strict-live-rerun-20260927.json`.
- Independent ReAgent structural objective: **705 PASS / 0 FAIL / 0 UNKNOWN**.
  Report: `audit/objective-current-rerun-2026-09-27.json`. This verifier checks
  structural heuristics; it does not prove semantic equivalence.
- ReAgent 0.4.0 parity: **704 GREEN / 1 YELLOW / 0 RED**, strict-exit returned
  0. The sole yellow is `0x100076d0`, whose conditional stack-slot/global
  invariant and indirect re-entry behavior remain unresolved. Report:
  `build/parity-current-rerun-20260927.json`.
- The 705-row `audit/source-sha256.csv` was recomputed against the live source
  tree: **0 mismatches**.
- `re-agent --config build/re-agent-publish-config.yaml doctor` returned
  `ready: true`. This only confirms the configured tool/evidence checks; the
  config has `validation.enabled: false`, so this is not a production build or
  runtime pass.
- ReAgent repository tests (`py -3.13 -m pytest -q`): **222 passed, 15
  skipped**. The skipped cases remain skipped; this is not coverage of ImVehFt
  runtime behavior.

## Project and runtime boundary

The ImVehFt work area contains diagnostic link-probe `.vcxproj` files under
`reports/re-agent/buildcheck`, but no original `.sln`, `.vcxproj`, `.vcproj`,
`.dsp`, or `.dsw` build project was found outside diagnostic/report trees. The
available historical SDK is `_sdk_history/snapshot-2014-04-27`; the separately
mentioned `C:\Users\caner\Downloads\SA Plugin SDK` path is not currently
present. No complete original source/build inputs were found, and the GTA SA
process was not running during the checks.

Accordingly, these results establish current-tree compilation and structural
parity only. They do **not** establish a linked production ASI, installer/hook
relocation correctness, full behavioral equivalence, or in-game validation.
The 705-function objective remains open; the latest parity yellow and the
supplemental hook-shim integration gap remain explicit blockers.
