# Fresh current-source 705-object diagnostic link and entry-placement audit

Date: 2026-09-28. Starting from the current successful strict x86 `.xcode`
object set, regenerated a unique link response file, linked all 705 candidate
objects, then reran the independent entry-trampoline feasibility audit against
the resulting PE and map.

## Results

- Strict compile report: `build/strict-xcode-current-20260928-3.json` —
  **705/705 passed**.
- Independent objective report:
  `audit/objective-independent-current-2026-09-28-3.json` —
  **705 PASS / 0 FAIL / 0 UNKNOWN**.
- ReAgent parity report: `build/parity-current-ghidra-recheck-20260928-3.json` —
  **705 GREEN / 0 YELLOW / 0 RED**; the independent waiver guard confirmed 13
  call-count-only adjudications and retained the open `0x100076d0` limitation.
- Diagnostic link response:
  `build/link-probe/original-entry-xcode-layout-current-20260928-4/entry-xcode-current.rsp`,
  SHA-256 `02A7C925565FB94ED2E1DB2FE138A5B7C7A621BBDC42D0758652757F0953768C`.
- Link output:
  `build/link-probe/original-entry-xcode-layout-current-20260928-4/ImVehFt-entry-xcode-layout-diagnostic-not-ASI.dll`,
  SHA-256 `BB5877F952BB84B12E6379E8042B3443552C20B954CA49B975FA7586A5AE6A10`;
  map SHA-256 `AF0FA30B9D3C1FB206A590FDD1A9334C9A0FF5DF57C6F378B42FA62727C15D6B`.
- Fresh placement report:
  `audit/entry-trampoline-feasibility-current-2026-09-28-4.json`, SHA-256
  `3E04680445AEFA4B5C7B5D1923A6E1956C705DD02BA477780D5A4DA7C4F9F031` —
  **705/705** entries resolve to executable diagnostic bodies; 429 body-fit,
  275 rel32-thunk-fit, zero out-of-range targets.

All artifacts have unique paths; no previous reports or diagnostic images were
overwritten.

## Limits

This confirms current objects link in the existing diagnostic configuration and
that all 705 entry slots remain placement-feasible in that layout. The output
is explicitly **not an ASI**. This link does not restore original section/data
layout, all 3,160 original `.text` HIGHLOW relocations, final imports/CRT/TLS
startup, installer hooks, or actual runtime semantics. It was not loaded into
GTA; all-green structural checks and entry feasibility are not semantic/game
validation. The `0x100076d0` callback/re-entry risk remains open.
