# Current-source validation and PE-layout follow-up — 2026-09-29

## Fresh current-tree checks

- Fresh VS 2022 x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-` compile: **705/705**.
  Report and objects: `build/strict-xcode-nogs-o1-active-20260929.json` and
  `build/recheck/strict-xcode-nogs-o1-active-20260929/`.
- Independent ReAgent objective check: **705 PASS / 0 FAIL / 0 UNKNOWN**;
  `audit/objective-independent-nogs-o1-active-2026-09-29.json`.
- ReAgent 0.4.0 Ghidra-backed parity: **705 GREEN / 0 YELLOW / 0 RED**;
  `build/parity-nogs-o1-active-20260929.json`. No model/API call was needed.
- A fresh x86 diagnostic link using the exact original `.text` template and all
  705 just-built objects succeeded:
  `build/link-probe/entry-exact-nogs-o1-active-20260929/ImVehFt-entry-xcode-layout-nogs-o1-active-diagnostic-not-ASI.dll`.
  It remains explicitly **not an ASI**.

## Entry placement and reference evidence

Using exact current COFF body sizes, current linker map, and original entry
slots, `audit/entry-trampoline-feasibility-nogs-o1-active-2026-09-29-exact-coff.json`
reports 705/705 executable targets resolved, 556 bodies fitting their bounded
slots, and 148 requiring 5-byte `E9 rel32` thunks. All thunk gaps are at least
8 bytes; all target displacements are in range. This establishes geometry and
reachability only, not a safe image patch.

The saved Ghidra reference export contains 437 non-entry `.text` reference
rows. Cross-checking those rows against the exact placement intervals found no
recorded external reference into bytes replaced by a directly placed body.
Two thunked functions have recorded references into their preserved old tails:
`0x10016f49` (one reference into `0x1001704c`) and `0x1001ae25` (15 references
into `0x1001af2b`). These bytes are not overwritten by the 5-byte entry
thunks. The raw inputs are under `C:\Users\caner\OneDrive\Documents\ImVehFt\ghidra_exports\`:
`text-nonentry-reference-audit-20260929.csv` and
`text-nonentry-codeunit-context-20260929.csv`. This is limited to references
recorded in the current Ghidra database; runtime-computed pointers and
undiscovered code/data edges remain possible.

## Relocation inventory for current objects

- Current 556 fitting bodies overlap **1,868** original `.text` HIGHLOW fields.
- Their COFF bodies contain **1,712 DIR32** and **1,515 REL32** fixups.
- The address-only crosswalk finds 198 exact old/new DIR32 sites, 875 shifted
  partial-overlap pairs, and 44 old HIGHLOW fields straddling candidate-body
  boundaries. These counts do not decide whether a fixup is semantically
  equivalent or whether it should be removed/replaced.
- The combined diagnostic link has **6,101** PE HIGHLOW records. A raw DWORD
  scan finds 6,275 values that look like section targets, of which 177 lack an
  exact-site HIGHLOW record (147 are in `.data`). These require classification;
  raw-value matches alone may include integers that are not pointers.
- All **4,442** current candidate COFF relocations resolve uniquely in the
  current diagnostic map (2,389 DIR32 and 2,053 REL32); this is a map-resolution
  result, not final-image relocation proof.

Reports: `audit/inplace-candidate-relocation-coverage-nogs-o1-active-2026-09-29.json`,
`audit/inplace-base-relocation-reconciliation-nogs-o1-active-2026-09-29.json`,
`audit/diagnostic-relocation-move-coverage-nogs-o1-active-2026-09-29.json`, and
`audit/candidate-relocation-symbol-targets-nogs-o1-active-2026-09-29.json`.

## PE layout blocker

The diagnostic PE's `.entry` raw bytes exactly match the pinned original
`.text` bytes (SHA-256 `BD691CB790F42EBB2ADBEE6D9761B7D03E46093C28DEC59C719845B342DB4CF7`).
However, its `.xcode` currently starts at RVA `0x22000` and spans through
`0x40691`, while the original `.rdata` and `.data` occupy RVAs `0x22000` through
`0x3d55c`. Copying that `.xcode` into the original PE at its diagnostic RVA
would therefore overwrite original data. The linked diagnostic also has its
own moved `.text`, `.rdata`, `.data`, imports, and relocation directory; it is
not a drop-in replacement for those original sections.

The next valid image experiment must preserve the original `.text`, `.rdata`,
and `.data` address ranges (or prove every affected consumer has been
redirected), place candidate code beyond the original `SizeOfImage` with a new
link layout, then recompute candidate COFF fixups, original HIGHLOW records,
imports/startup, and PE metadata. No original binary bytes were modified and
no `.asi` or game-load test was produced in this audit.
