# Runtime smoke attempt and corrected image-address inventory — 2026-09-28

## Source and SDK availability

The user-provided game plugin directory `.ImVehFt` contains the installed `ImVehFt.asi`, logs, configuration, and 41 resource files; it does not contain the original C++ project or Visual Studio project. The previously mentioned `C:\Users\caner\Downloads\SA Plugin SDK` path is currently absent. A Plugin-SDK checkout does exist at `C:\Users\caner\OneDrive\Documents\ImVehFt\_sdk_history\snapshot-2014-04-27`, HEAD `15f15b60bbf74c106e1b496ff92c98764abf4605` (`2026-09-08`, “SA fix renderware”). It already has a tracked modification to `src/sdk/plugin/internal/CallbackResetDevice.hpp` and an untracked `build-msvc-x86-20260923/`; both were left untouched. Finding the SDK does not recover ImVehFt's missing source/project configuration.

## Corrected internal-image-literal scan

The previous inventory script matched numeric strings in comments. Its v28 output listed seven addresses; manual source inspection showed they were all in comments. `scripts/inventory-candidate-internal-image-literals.py` now masks C++ line/block comments and ordinary quoted string/character literals while preserving line numbers. Its backup is `scripts/inventory-candidate-internal-image-literals.py.pre-ignore-comments-and-strings-20260928.bak`. A self-test verified that comment/string addresses are excluded while code addresses remain. Fresh scan v29 against the installed original ASI and all 705 candidate TUs reports **0 executable-code occurrences / 0 addresses** (`audit/candidate-internal-image-address-literals-v29-2026-09-28.json/.csv`). This only covers 7–8 digit numeric tokens that land in the original PE's virtual sections; it does not prove semantic equivalence or rule out non-literal/address-derived issues.

## Reversible runtime smoke attempt

The diagnostic DLL and installed original plugin are both x86 PE DLLs with preferred image base `0x10000000`; their import DLL sets match (`d3dx9_43.dll`, `USER32.dll`, `KERNEL32.dll`). Their entrypoint RVAs and section layouts differ substantially (original `.text` virtual size `0x21000`, candidate `0x85000`), so PE compatibility is not equivalent to a successful plugin build.

Before a smoke attempt, the original plugin was copied to `build/game-validation/ImVehFt-installed-original-before-smoke-20260928.asi.bak` (SHA-256 `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`). The diagnostic DLL was temporarily copied to the modloader's `ImVehFt.asi` path. Two GUI launch requests timed out; process and window checks found no GTA process/window. The candidate was therefore **not loaded**. The original file was restored and its SHA-256 rechecked against the backup; it is unchanged. No in-game behavior was tested.

The 705 strict compile, 705 structural objective PASS, and test-only normalized parity results in `audit/100182c1-eax-output-abi-bridge-2026-09-28.md` remain as previously reported. There is still no successful original-project build, candidate plugin load, `.asi` runtime result, or in-game feature validation.

The v29 zero-hit CSV was headerless because the scanner emitted no records. The scanner now always writes its seven-column schema; v30 rerun `audit/candidate-internal-image-address-literals-v30-2026-09-28.csv/.json` supersedes v29 as the current machine-readable result (0 code-token hits, stable CSV header).
