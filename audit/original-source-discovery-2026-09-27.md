# Original ImVehFt source/build-project discovery

Date: 2026-09-27. This records a limited public-source search for the
original ImVehFt C++ source and its historical build project. It is not proof
that no private, unindexed, or removed copy exists.

## Search performed

Queries covered `ImVehFt source code`, `ImVehFt.asi source`, DK22Pac plus
ImVehFt source, GitHub-indexed matches, and the original GTAForums topic. The
search returned release/download pages and downstream mods or compatibility
reports, but no authoritative ImVehFt source repository, source archive, or
`.sln`/`.vcxproj`. DK22Pac's public blog lists old ImVehFt 2.0.x release files
and a Plugin-SDK download; the indexed page does not expose an ImVehFt source
tree. The supplied official GTAForums topic could not be opened by the web
reader (HTTP 403), so its complete attachment/history contents were not
checked.

References checked:

- [DK22Pac's blog](https://dk22pac.blogspot.com/) — historical project and SDK
  download listing; not a source archive.
- [Original GTAForums ImVehFt topic](https://gtaforums.com/topic/528175/improved-vehicle-features/) — unavailable to the web reader during this pass.

### Follow-up public search (2026-09-27)

A fresh indexed web search for the mod name plus source/C++/GitHub terms again
returned release, compatibility, and community pages rather than an
authoritative ImVehFt source tree or historical Visual Studio project. The
primary-authored DK22Pac blog page that was retrievable lists packaged 2.0.2
and 2.0.1 ASI releases (plus unrelated mod files), not an ImVehFt source
archive. This is evidence about that indexed release page only; it does not
prove that no source was ever published or that no unindexed attachment
exists. The GTAForums topic remains inaccessible to the web reader in this
pass. The source/build-input blocker therefore remains unchanged.

## Local build-input state

The local 2014 Plugin-SDK snapshot exists, but the local ImVehFt directories
previously searched contain no original mod `.sln`/`.vcxproj`; discovered
project files are diagnostic probes. The exact original compiler/linker flags,
CRT, project ordering, and source files therefore remain unknown. Continue
binary-first Ghidra analysis without PDB. Do not treat this limited search as
proof that the original project is permanently unavailable.

### Follow-up: user-supplied modloader path

Recursively checked `GTA San Andreas\modloader\My Scripts\.ImVehFt` and its
nested `.ImVehFt\ImVehFt` resource directory. The nested directory has 41 files
(25 PNG, 8 EML, 6 DDS, 1 FX, and 1 INI; 10,657,226 bytes); it contains runtime
assets/configuration, not C/C++ sources or a Visual Studio project. No `.sln`,
`.vcxproj`, `.vcxproj.filters`, `.props`, or `.targets` were found in the
supplied modloader folder. The supplied `Downloads\SA Plugin SDK` path is
currently absent; the usable historical snapshot is
`_sdk_history\snapshot-2014-04-27`. The source-build blocker therefore
remains, although private or unindexed original materials may still exist.

The modloader's `ImVehFt.asi` and the binary under the reverse-engineering
workspace are both 247,296 bytes with identical SHA-256
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`. This
confirms the installed copy is the exact binary being analyzed; it does not
provide original source or make a reconstructed build loadable.
