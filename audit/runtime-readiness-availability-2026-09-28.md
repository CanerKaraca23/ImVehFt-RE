# Runtime-readiness input inventory

Date checked: 2026-09-28. Read-only availability check for the remaining
production-build/game-validation prerequisites.

## Evidence

- The target `C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi` and
  installed modloader copy
  `C:\Users\caner\OneDrive\Documents\GTA San Andreas\modloader\My Scripts\.ImVehFt\ImVehFt.asi`
  are both 247,296 bytes and SHA-256
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
  The separate `ImVehFtFix.asi` is 247,808 bytes and has a different hash; it
  remains outside the target scope.
- The user-provided `.ImVehFt` folder currently has 45 files: texture/shadow
  assets, eight `.eml` files, logs/config, and the two `.asi` files above. A
  filename scan finds no `.cpp`, `.h`, `.hpp`, `.sln`, `.vcxproj`, `.vcproj`,
  `.dsp`, or `.dsw` project/source files in that folder.
- The exact path `C:\Users\caner\Downloads\SA Plugin SDK` is absent. An
  archived SDK snapshot is available at
  `C:\Users\caner\OneDrive\Documents\ImVehFt\_sdk_history\snapshot-2014-04-27`,
  Git commit `888a67c1587ece1053a05f0cb6219a0c6c4dad0a`, dated 2014-04-27,
  including `build-msvc-x86-20260923\Plugin2014.lib`. The separate current
  `plugin-sdk-sa` checkout exists at commit
  `b55e89b336a81448c1aa1a5b188431c9845ebaa9` (2026-09-09) and has
  `output\lib\Plugin.lib`. SDKs/libraries are therefore available, but neither
  establishes the missing original ImVehFt project files, exact project
  settings, or full production link inputs.
- The current candidate build artifact remains
  `ImVehFt-implicit-x87-alpha-diagnostic-not-ASI.dll`, linked from 705 object
  files. It is not a loadable ASI. No `gta_sa` process was running during this
  check, and no game/runtime validation was performed.

## Readiness conclusion

The 705 candidate sources can be strictly compiled, structurally checked,
compared by ReAgent parity, and linked into a diagnostic DLL. The original
source project and a complete, proven-compatible production build recipe are
not present in the inspected inputs, so production `.asi` generation and
gameplay validation remain unverified. The matching target binary and asset
folder are preserved; no user files were changed by this inventory.
