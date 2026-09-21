# ImVehFt-RE

An evidence-led, work-in-progress reconstruction of 705 functions from the local ImVehFt binary. This repository contains reconstructed candidate translation units, not the original ImVehFt source tree.

**Status as of 2026-09-22:** all 705 candidate translation units compiled individually with MSVC 2022 x86, C++20, `/O2`. This is an object/static-archive build only. It is **not** a completed ImVehFt plugin, a successful full link, proof of source equivalence, or a passing in-game test.

## Build the candidate archive

Requirements:

- Windows x86 target
- Visual Studio 2022 or Build Tools with the C++ x86 toolchain and Windows SDK
- Run from **x86 Native Tools PowerShell for VS 2022** so `cl.exe` and `lib.exe` are on `PATH`

```powershell
./scripts/build-objects.ps1
```

The script compiles each file in `src/functions/` independently with `/std:c++20 /O2 /c`, then packages the resulting objects into `build/ImVehFtCandidates.lib`. The archive is useful for repeatable compilation and inspection; it deliberately does not pretend to link a working `.asi`.

## Verification status

- MSVC 2022 x86 `/O2`: **705/705 translation units compiled**.
- MSVC `/O2 /W4 /WX`: **700/705**; five diagnostics remain at `10003810`, `100076d0`, `10012e65`, `1001b65a`, and `1001e03d`. They are not suppressed or guessed away.
- Clang x86 `/O2`: **701/705** in the recorded audit; four toolchain/target incompatibilities remain.
- ReAgent objective/parity report: 705/705 recorded as passing/green, with 11 scope-limited manual call-count adjudications. These checks do not establish semantic correctness.
- Full COFF inventory: 1,012 unique unresolved symbols (1,552 object-symbol references) remain, including reconstructed image data, CRT/Windows/SDK dependencies, and absent project globals.
- Full original-project link, plugin-sdk integration, and GTA San Andreas runtime testing: **not completed**.

See [`audit/status.json`](audit/status.json) for the recorded counts and scope limits, and [`audit/source-sha256.csv`](audit/source-sha256.csv) for the candidate source fingerprints. A green compile or parity score is not equivalent to a behaviorally verified function.

## Source and evidence

- `src/functions/`: the 705 candidate C++ translation units used by the latest MSVC `/O2` audit.
- `audit/`: compact verification summary and per-function SHA-256 inventory.
- The original `ImVehFt.asi`, GTA files, generated object files, and large historical progress backups are intentionally not included.

The reference binary was SHA-256 `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3` when recorded locally. This fingerprint is included for traceability; it does not imply that the original binary is distributed here.

## Rights and use

The original mod's source and redistribution license have not been established in this work. No license grant for ImVehFt, GTA San Andreas, or third-party SDK/runtime code is made by this repository. Do not redistribute the original binary or assume that this reconstruction is authorized for reuse; resolve the relevant rights with the original rights holders first.
