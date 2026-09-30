# Exact Ghidra reconstruction of `0x100172d5` — 2026-09-29

## Why the source changed

The earlier C implementation of `__security_check_cookie` passed the behavioral matrix, but its fresh object compiled to a 13-byte `JNE rel32; RET` shape. The pinned original instead has a 15-byte sequence: compare ECX with the legacy cookie, short conditional branch, `REP RET`, then a separate relative jump to `___report_gsfailure`. This distinction was exposed by `audit/cookie-checker-inplace-byte-reconstruction-2026-09-29.json` (the pre-fix C-object comparison); behavioral equality alone had hidden it.

The C source is now naked x86 assembly matching the original control flow. The prior C version is preserved as `src/functions/100172d5.cpp.pre-ghidra-exact-rep-ret-20260929.bak`.

## Focused evidence

- Fresh strict object `build/recheck/strict-cookie-check-exact-rep-ret-20260929/100172d5.obj`, SHA-256 `A4AE49E3F111259D2DE6EA7BFC7B1F0F9499EC4744E8B40D29BEB8E741928AB7`, emits a 15-byte `.xcode` body. Its `DIR32` cookie-global and `REL32` failure-handler fixups resolve to original addresses `0x10029490` and `0x1001ae25`.
- `audit/cookie-checker-inplace-byte-reconstruction-exact-rep-ret-2026-09-29.json` resolves both COFF fixups and confirms **all 15 bytes exactly match** the pinned original body at `0x100172d5`; the original HIGHLOW operand at `0x100172d7` is retained.
- `scripts/test-100172d5-cookie-checker-original-differential.ps1`: **10 fresh x86 processes × 25 saved/supplied cookie pairs** matched. The original report-failure target and candidate report-failure symbol were replaced by a returning call recorder, so this tests detection/transfer, not actual process termination or Windows fail-fast behavior. Harness SHA-256 `FE214EAE351C220427ECE52E58FB1645238F76B17532E724632F91BF97E98CEF`.
- Full current-source gates after the change: strict MSVC x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-` **705/705** (`build/strict-cookie-check-exact-rep-ret-20260929.json`); objective **705 PASS / 0 FAIL / 0 UNKNOWN** (`audit/objective-cookie-check-exact-rep-ret-2026-09-29.json`); ReAgent 0.4.0 **705 GREEN / 0 YELLOW / 0 RED** (`build/parity-cookie-check-exact-rep-ret-20260929.json`).
- Fresh 705-object diagnostic link exists at `build/link-probe/entry-cookie-check-exact-rep-ret-20260929/ImVehFt-m80-reloc-probe-not-ASI.dll`; it reports stale `/ORDER` LNK4037 warnings and is not an ASI.
- Fresh placement/relocation inventories: 557 bodies fit their bounded gaps, 147 exceed them, the final entry has no next-entry bound; 147 entries need a 5-byte thunk, with zero rel32 range failures. The full object set has 2,774 original HIGHLOW overlap instances. Reports are the `*-cookie-check-exact-rep-ret-2026-09-29.json` files in `audit/`.

## Still open

The pinned original checker body and candidate are now byte-identical after fixup resolution; controlled cookie-failure observations also match. This does not prove the original fatal-report helper's real process termination, all 29 explicit cookie callsites' path/argument correctness, default `/GS` compatibility, full PE/startup/installer behavior, or GTA gameplay. The diagnostic DLL is not production-loadable; `/O1 /GS-` remains a candidate profile, not an approved final build recipe.
