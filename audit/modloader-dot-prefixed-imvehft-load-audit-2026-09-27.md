# Mod Loader dot-prefixed folder load audit

Date: 2026-09-27. This checks whether the installed Mod Loader can discover the
original ImVehFt ASI in the configured path; it does not execute GTA or alter
the mod installation.

## Finding

The installed Mod Loader log identifies version `0.3.10`. The active profile
is `samp`, and the ASI is located at:

`modloader/My Scripts/.ImVehFt/ImVehFt.asi`

The exact upstream `v0.3.10` source confirms `FilesWalk` ignores every entry
whose filename begins with `.` (`include/modloader/util/path.hpp`, tagged
source: <https://github.com/thelink2012/modloader/blob/v0.3.10/include/modloader/util/path.hpp#L233-L263>).
`FolderInformation::Scan` uses that walker to enumerate child mod directories
(`src/core/folder.cpp`). Consequently `.ImVehFt` is skipped before its contents
are examined; the configured profile's include/ignore settings do not override
this walker rule.

The latest local `modloader.log` (2026-09-27 14:10:49) records scanning
`modloader\\my scripts\\` but no `.ImVehFt` entry. This is consistent with the
tagged source. The game process is not currently running, so no live module
list was available. The `ImVehFt.log` timestamp (2026-09-11) is historical
execution evidence only, not evidence that the ASI was loaded in the latest
session. The 64-file ASI/DLL byte inventory finding the file likewise proves
presence, not loader discovery or successful load.

## Consequence and limit

Do not treat the original ASI at this dot-prefixed path as a current runtime
baseline. A future controlled original-mod test would first need a
non-dot-prefixed Mod Loader folder and confirmation in a fresh Mod Loader log
that `ImVehFt.asi` was found/loaded. No folder was renamed or copied here.
This finding does not make the reconstructed image testable: the production
replacement still lacks a valid link/layout and relocatable hook/global state.
