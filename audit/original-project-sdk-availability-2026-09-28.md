# Original project and historical SDK availability

Date: 2026-09-28

## Local evidence

- The specified `Downloads/SA Plugin SDK` directory is absent in the current
  Windows profile. However, the repository workspace contains
  `_sdk_history/snapshot-2014-04-27`, a local `DK22Pac/plugin-sdk` clone at
  commit `888a67c1587ece1053a05f0cb6219a0c6c4dad0a` (`2014-04-27T18:30:39-03:00`).
- Its `build-msvc-x86-20260923/compile-report.json` records **91/91 SDK
  translation units compiled successfully**; `Plugin2014.lib` exists at
  1,379,326 bytes. This establishes that a historical SDK snapshot and a
  compiled static library are locally available. It does not establish that
  this was the exact SDK/build configuration used for ImVehFt.
- That SDK worktree has a modified tracked file
  `src/sdk/plugin/internal/CallbackResetDevice.hpp` and an untracked
  `build-msvc-x86-20260923/` directory. They pre-existed this audit and were
  left untouched.
- The supplied `.ImVehFt/ImVehFt` folder contains assets/configuration
  (`.png`, `.dds`, `.fx`, `.ini`, `.eml`) but no C/C++ source or project file.
- The reverse-engineering workspace has 40 Visual Studio project files; they
  are named `ImVehFtLinkProbe*.vcxproj` and live in buildcheck directories.
  There is no original `.sln` or original ImVehFt project/build recipe among
  the project files found by the workspace inventory.

## Consequence

The 2014 plugin-SDK snapshot is usable as a historical compile input for
controlled tests, but the original ImVehFt project sources, exact project
configuration, and startup/link recipe have not been found in the inspected
locations. The current 705-candidate code can be compile/link-probed, but a
like-for-like production build and its runtime initialization path cannot yet
be asserted from this evidence. Preserve the SDK worktree's pre-existing
changes; do not clean or reset it.
