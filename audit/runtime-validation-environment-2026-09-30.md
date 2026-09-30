# Runtime validation environment inventory — 2026-09-30

## Confirmed on this host

- GTA San Andreas directory exists at `C:\Users\caner\OneDrive\Documents\GTA San Andreas`; `gta_sa.exe` is present (14,383,616 bytes).
- `modloader.asi` and a ModLoader tree are present. The installation contains many additional `.asi` plugins; this is not a clean test profile.
- The active-looking ModLoader entry `modloader\My Scripts\.ImVehFt\ImVehFt.asi` hashes to `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`, identical to the pinned original at `C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi`.
- The separate `ImVehFtFix.asi` hashes to `D659FED57AB8527595A5F3E2D82E8F2BADD81D74DFF1803EEC38A70CC4F5EDB9`; it is distinct and was not changed.
- The previously supplied SDK directory `C:\Users\caner\Downloads\SA Plugin SDK` is absent. A separate 2014-04-27 Plugin-SDK source snapshot exists at `C:\Users\caner\OneDrive\Documents\ImVehFt\_sdk_history\snapshot-2014-04-27`; prior audit records say its 91 SDK units compiled as a static library. It is not established as the exact custom SDK/build input used for ImVehFt.
- No `gta_sa.exe` process was running during this inventory.

## Validation boundary

The candidate v7 is still an experimental PE. Replacing the active ModLoader ASI in this multi-plugin profile would expose the user's normal game setup to an unverified binary and would not isolate crashes or behavior. No replacement, launch, or game test was performed. The original ModLoader ASI and separate ImVehFtFix remain untouched.

The host has a game executable and ModLoader, so a real test is not impossible in principle. It requires an isolated, recoverable test profile and the candidate must first be judged safe for normal `LoadLibrary`/DllMain execution. The available 2014 SDK snapshot is useful corroboration, but the original ImVehFt project/build files and exact custom SDK revision remain unavailable, preventing a faithful historical native-project rebuild. Until those gates are met, the status is **host inventory confirmed; candidate game-runtime validation not performed**.
