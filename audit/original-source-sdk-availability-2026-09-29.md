# Original source / SDK availability check — 2026-09-29

## Local files

- The user-provided `...\GTA San Andreas\modloader\My Scripts\.ImVehFt` directory contains 45 files: 25 `.png`, 8 `.eml`, 6 `.dds`, two `.asi`, two `.log`, one `.fx`, and one `.ini`. It contains no C/C++ source or project/build file. Both `ImVehFt.asi` and the separate `ImVehFtFix.asi` are present; the primary pinned ASI remains SHA-256 `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
- The formerly named `C:\Users\caner\Downloads\SA Plugin SDK` and `C:\Users\caner\Downloads\ghidra\_12.1.3\_PUBLIC` paths no longer exist. The SDK history checkout is `C:\Users\caner\OneDrive\Documents\ImVehFt\_sdk_history`; the installed Ghidra directory is now `C:\Users\caner\Downloads\ghidra_12.1.3_PUBLIC` (`ghidraRun.bat` present). The supplied JDK is available at `C:\Users\caner\OneDrive\Documents\jdk-26.0.2.1\bin\java.exe`.
- The latest Plugin-SDK commit before the pinned ASI's 2014-10-19 timestamp is `e686428d6213a09adaf370b5c7f6be8ce03e0e83` dated 2014-09-15 (`Fixed vehicle pool`). Its tree has 294 paths and no `ImVehFt` source or `.sln`/`.vcxproj`/`.vcproj` project. The local `snapshot-2014-04-27` is SDK material, not the ImVehFt source or build recipe.
- Read-only status inspection of `_sdk_history` reported 3,456 tracked paths missing and `snapshot-2014-04-27` untracked. This audit did not restore, remove, or modify anything in that SDK checkout; its status should be treated as existing user/worktree state, not an action taken here.

## Public-source lookup

The author's 2013 ImVehFt blog page lists binary downloads for 2.0.2 and 2.0.1, but the page exposes no source-code download. A later MixMods page says ImVehFt was not open source. Searches of GitHub and the original release/forum references did not locate an authoritative ImVehFt source repository. These searches cannot rule out a private or unindexed archive.

- Author's release page: https://dk22pac.blogspot.com/2013/05/imvehft-improved-vehicle-features-202.html
- Later community note on source availability: https://www.mixmods.com.br/2017/12/em-breve-vehfuncs/

## Validation consequence

The historical Plugin-SDK is available as reference material and may support ABI/API investigation, but it is not the missing ImVehFt project. The original source, project settings, and build recipe remain unavailable locally and were not found in the searched public references. Therefore original-project reproduction and production game validation remain unproven; current MSVC/ReAgent/object checks are reverse-engineered-candidate checks only. No ASI was built or loaded in this availability audit.
