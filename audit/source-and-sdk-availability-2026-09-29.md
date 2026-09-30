# Original project and SDK availability — 2026-09-29

## Available SDK material

- The historical plugin-sdk snapshot exists at
  `C:\Users\caner\OneDrive\Documents\ImVehFt\_sdk_history\snapshot-2014-04-27`.
  Its Git commit is `888a67c1587ece1053a05f0cb6219a0c6c4dad0a`, dated
  `2014-04-27T18:30:39-03:00`, before the pinned ImVehFt binary's filesystem
  timestamp (`2014-10-19`). It contains SDK sources/CMake metadata and the
  available x86 `Plugin2014.lib` build at
  `build-msvc-x86-20260923/Plugin2014.lib`.
- A separate, modern checkout exists at
  `C:\Users\caner\OneDrive\Documents\plugin-sdk-sa`, currently at
  `b55e89b336a81448c1aa1a5b188431c9845ebaa9` (2026-09-09). Its project files
  are not evidence of the original ImVehFt build configuration.
- The earlier user-provided path
  `C:\Users\caner\Downloads\SA Plugin SDK` is absent. The historical snapshot
  above is the usable old SDK material currently wired into the diagnostic
  link response.

## Original mod project/source

Read-only extension scans found no `.c`, `.cc`, `.cpp`, `.h`, `.hpp`, `.sln`,
`.vcxproj`, `.vcproj`, or `CMakeLists.txt` in the user's installed
`.ImVehFt` directory. That folder contains the 2014 `ImVehFt.asi`, assets/logs,
and the separate ImVehFtFix files; the latter are not treated as source or as
part of this target. The candidate reverse-engineering repository has no
solution/project/CMake entry point either; it contains the 705 address-mapped
candidate translation units and diagnostic support artifacts.

The public MixMods page describes the unofficial 2014-era 2.1.1 binary and
links back to the GTAForums primary thread, but does not publish original
source. The thread fetch is currently denied with HTTP 403 by the web reader;
the linked page cannot establish whether the original author privately
released source elsewhere. See
[MixMods ImVehFt page](https://www.mixmods.com.br/2020/01/imvehft-improved-vehicle-features/)
and [GTAForums primary thread](https://gtaforums.com/topic/528175-improved-vehicle-features/).

## Validation consequence

The historical SDK is available and has already been used by diagnostic
linking. The missing prerequisite is the original ImVehFt project/build
definition (including its exact compiler/linker/runtime configuration), not
the SDK alone. Therefore a true upstream-project rebuild and official project
comparison cannot currently be performed. The diagnostic DLL, mapped function
tests, and static 705-function gates remain useful evidence but do not establish
production `.asi` layout/startup or GTA gameplay compatibility.
