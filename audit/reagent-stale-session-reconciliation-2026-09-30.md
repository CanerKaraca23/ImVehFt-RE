# ReAgent persisted-session reconciliation — 2026-09-30

## What `re-agent status` currently measures

Ran from the configured project root (`C:\Users\caner\OneDrive\Documents\ImVehFt`) with its `re-agent.yaml`:

- `re-agent status --format json`: **705 total, 696 passed, 9 failed**.
- `re-agent doctor`: ready; source root resolves to this reverse-engineering repo. Doctor also states validation gates are disabled; it checks setup/evidence, not semantic/runtime acceptance.
- The persisted `re-agent-progress.json` is **41,983,358 bytes**, last written **2026-09-22 05:49:10**. It was not modified during this follow-up.

The session JSON has 705 entries: **689 `verdict=PASS`, 16 `verdict=UNKNOWN`**. Its `success` boolean is true on seven of those UNKNOWN entries and false on the other nine, which explains the CLI's 696/9 arithmetic. Thus “9 failed” is a stale session-success count, not nine current ReAgent parity RED results; conversely, `success=true` does not turn UNKNOWN into a semantic PASS.

## Fresh checks on all 16 persisted UNKNOWN entries

The exact 16 addresses from that session were checked against the current source set with fresh ReAgent parity, in two read-only targeted runs:

- Nine entries whose persisted `success` was false: **9 GREEN / 0 YELLOW / 0 RED**, report `reagent-session-nine-parity-followup-20260930.json`.
- Seven entries whose persisted `success` was true: **7 GREEN / 0 YELLOW / 0 RED**, report `reagent-session-seven-parity-followup-20260930.json`.

The independent full-set objective report contains 705 source hashes; re-hashing the current 705 source files produced **0 mismatches** against it. The fresh full-set gates are recorded separately: strict MSVC x86 compile 705/705, objective 705 PASS/0 FAIL/0 UNKNOWN, full parity 705 GREEN/0 YELLOW/0 RED. These remain structural/compile/parity checks, not semantic or runtime proof.

Three GREEN targeted results retain scoped informational call-count adjudications (`100119f1`, `1001bc9e`, `1001d591`); these are not warnings, and their precise manual scopes are embedded in the JSON reports. They do not waive unrelated checks.

## Decision

Do not hand-edit or silently overwrite the 41.98 MB historical session to turn its nine false/UNKNOWN entries into PASS. The current evidence supports saying **fresh structural/parity checks are green for the 16 stale UNKNOWN entries**, while the persisted session still reports **696/9** and those entries remain UNKNOWN in that historical session. Full behavioral/game validation is still open.
