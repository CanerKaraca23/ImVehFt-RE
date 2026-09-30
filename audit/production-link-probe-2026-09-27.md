# Production link probe (2026-09-27)

## Purpose and safety

This was a diagnostic x86 link attempt only. It used `/DLL /NOENTRY` and
`/WHOLEARCHIVE` so the linker would expose unresolved references from the
candidate archive. The output was named `Candidates-plus-provider-not-ASI-probe.dll`;
the link failed and **no DLL or ASI was produced**. Even a successful result
would not by itself be a loadable or validated ImVehFt plugin.

## Inputs verified on this machine

- Original reference: `C:\Users\caner\OneDrive\Documents\GTA San Andreas\modloader\My Scripts\.ImVehFt\ImVehFt.asi` (247,296 bytes).
- Candidate archive: `build/ImVehFtCandidates.lib`.
- MSVC 2022 x86 compiler/linker and MASM are installed (toolset 14.44.35207).
- A Plugin-SDK checkout exists at
  `C:\Users\caner\OneDrive\Documents\plugin-sdk-sa`, not at the earlier
  `Downloads\SA Plugin SDK` path. It is an x86 SDK fork, commit
  `b55e89b336a81448c1aa1a5b188431c9845ebaa9` dated 2026-09-09. The local Git
  checkout is shallow (one commit), so it does not establish which historical
  SDK revision ImVehFt originally used. It has a prebuilt `output/lib/Plugin.lib`.
- The reverse-engineering checkout contains no `.sln`, `.vcxproj`, CMake, or
  Makefile. The SDK's presence does not supply the missing ImVehFt image,
  startup, and section-layout integration.
- The historical SDK snapshot is present in the shared workspace at
  `C:\Users\caner\OneDrive\Documents\ImVehFt\_sdk_history\snapshot-2014-04-27`
  (commit `888a67c1587ece1053a05f0cb6219a0c6c4dad0a`, 2014-04-27), with a
  prebuilt `build-msvc-x86-20260923/Plugin2014.lib`. It is outside this
  publish-repository checkout. Its Git worktree currently has a modified
  `src/sdk/plugin/internal/CallbackResetDevice.hpp` and an untracked
  `build-msvc-x86-20260923/`; neither was changed during this pass.
- The older 704-object diagnostic DLL is also present outside this checkout at
  `C:\Users\caner\OneDrive\Documents\ImVehFt\reports\re-agent\buildcheck\old-sdk-plugin-lib-probe-20260923\out-704-candidates-entrypoint-correctimport\ImVehFtLinkProbeCurrentCandidates.dll`
  (660,992 bytes, timestamp 2026-09-26 22:57). Its hash and failed hook/layout
  audit are recorded in `audit/diagnostic-link-hook-layout-2026-09-27.md`.
  It is not game-valid and must not be loaded. There is still no `.asi` in the
  current publish checkout.

## Link outcomes

1. Whole-archive link with only `ImVehFtCandidates.lib`: exit 1120, 1,476
   linker diagnostic lines; no output image.
2. Repeated with the latest generated data-provider object, four existing
   hook/callback shim objects, and the local SDK `Plugin.lib`: exit 1120, 608
   linker diagnostic lines and 129 distinct decorated unresolved symbols; no
   output image.
3. Repeated the second probe with explicit Windows system libraries
   (`kernel32`, `user32`, `gdi32`, `advapi32`, `shell32`, `ole32`, `oleaut32`,
   `winmm`, `ws2_32`, `comctl32`, `shlwapi`, and `version`): exit 1120, 405
   linker diagnostic lines and 126 distinct decorated unresolved names; no
   output image. Thus ordinary project-level system-library defaults account
   for part of the earlier failures, but do not make the candidate linkable.
4. Repeated with all 705 objects from the fresh strict report, rather than the
   older `build/ImVehFtCandidates.lib`, plus the same provider, hook shims,
   current SDK library, and explicit Windows libraries: exit 1120, 424 linker
   diagnostic lines and 127 distinct decorated names; no output image. This
   newer-object probe still uses the current SDK library, not the absent 2014
   snapshot, and does not reproduce the historical diagnostic link.
5. Repeated with 704 fresh strict objects (omitting the documented
   `1001b2b2` RtlUnwind collision), the 2014 `Plugin2014.lib`, the full
   original-byte `.data/.rdata` diagnostic provider, CRT compatibility inputs,
   and current installer/callback/hook-shim objects. The link still fails
   (`LNK1120`): **84 linker error lines, 78 parsed unresolved symbols**, no DLL.
   This is the best current linker baseline: the generated installer branch
   thunks, callback-entry/JMP thunks, and supplemental hook-object references
   resolve when included. Correctly parsed, the remaining 78 names are
   dominated by address-backed global/RDATA aliases (including vftable and
   CRT-state objects), plus one legacy CRT conversion routine. Response file:
   `build/link-probe/strict-704-historical-sdk/strict-704-link-full-data-provider.rsp`.

The earlier provisional “distinct decorated symbol” counts were not reliable:
their parser also captured referring-function names. The latest unresolved-name
count instead extracts the symbol following the localized linker phrase for
“unresolved external”; it remains diagnostic, not a semantic classification.
The best current probe still lacks a complete set of typed data/RDATA aliases
and compatible CRT providers. It also does not establish final section/base-
relocation tables or game behavior. No game test was performed.

## Status

The source-only checks remain separate from production linking. The sole
ReAgent semantic warning remains `0x100076d0`; the yellow must not be waived
based on this link probe. Next linker work should classify/fix symbols by
origin, starting with missing game-address thunks and candidate ABI/linkage
references, then rerun the same probe and preserve each result.
