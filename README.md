# ImVehFt-RE

An evidence-led, work-in-progress reconstruction of 705 functions from the local ImVehFt binary. This repository contains reconstructed candidate translation units, not the original ImVehFt source tree.

**Status as of 2026-09-24:** all 705 candidate translation units are exported from the latest local ReAgent progress snapshot with real UTF-8 line breaks. After five evidence-backed type/call-site corrections, they compiled individually with MSVC 2022 x86, C++20, `/O2`; the five changed units passed `/W4 /WX /MT` compilation. The open `100076d0` C4701/data-flow risk remains documented and is not considered resolved by compilation. This is an object/static-archive build only. It is **not** a completed ImVehFt plugin, proof of source equivalence, or a passing in-game test.

## Build the candidate archive

Requirements:

- Windows x86 target
- Visual Studio 2022 or Build Tools with the C++ x86 toolchain and Windows SDK
- Run from **x86 Native Tools PowerShell for VS 2022** so `cl.exe` and `lib.exe` are on `PATH`

```powershell
./scripts/build-objects.ps1
```

The script compiles each file in `src/functions/` independently with `/std:c++20 /O2 /c`, then packages the resulting objects into `build/ImVehFtCandidates.lib`. It supports Windows PowerShell 5.1 and PowerShell 7 when launched from an x86 VS 2022 developer environment. The archive is useful for repeatable compilation and inspection; it deliberately does not pretend to link a working `.asi`.

## Verification status

- MSVC 2022 x86 `/O2`: **705/705 translation units compiled**.
- Previous standalone MSVC `/O2 /W4 /WX` audit: **705/705** passed; after the five current edits, those changed units separately compiled with `/W4 /WX /MT` and the remaining 700 are unchanged. `100076d0` still has the C4701 concern described below; compilation under `/WX` alone must not be read as resolving it.
- Clang x86 `/O2`: **701/705** in the recorded audit; four toolchain/target incompatibilities remain.
- ReAgent objective/parity report: 705/705 recorded as passing/green, with 11 scope-limited manual call-count adjudications. These checks do not establish semantic correctness.
- The latest historical-SDK diagnostic probe against the updated 705 object set has 199 unresolved externals; it produced no DLL and is not a production plugin project. Details and limitations are in [`audit/candidate-correction-100074d0.md`](audit/candidate-correction-100074d0.md).
- Targeted ReAgent 0.4.0 parity for the five corrected functions is green (5/5); this is a local consistency check, not behavioral/runtime validation. The previously recorded 705/705 objective/parity counts predate these five candidate edits.
- The ReAgent 0.4.0 non-LLM objective verifier was rerun for the five edited candidates: **5/5 PASS** with no structural failures. It is a structural gate, not semantic equivalence or runtime proof; the parity report still carries the scoped `local_c` C4701 concern.
- Full original-project link, plugin-sdk integration, and GTA San Andreas runtime testing: **not completed**.

See [`audit/status.json`](audit/status.json) for the recorded counts and scope limits, and [`audit/source-sha256.csv`](audit/source-sha256.csv) for the candidate source fingerprints. A green compile or parity score is not equivalent to a behaviorally verified function.

## Source and evidence

- `src/functions/`: the 705 candidate C++ translation units used by the latest MSVC `/O2` audit.
- `audit/`: compact verification summary, per-function SHA-256 inventory, and `function-name-map.csv` mapping addresses to names/signatures observed by Ghidra.
- `audit/sdk-provenance.md`: historical SDK comparison and why the 2014 static Plugin-SDK line is a better candidate than the local 2013 import-library snapshot.
- `audit/global-address-crosswalk-2026-09-24.md`: exact GTA SA global-address matches from Plugin-SDK and candidate declaration/use mismatches that still affect confidence and linking.
- `audit/candidate-correction-10003ba0-10003e60.md`: Ghidra/SDK evidence, edits, and targeted build/parity/link results for the raster-lock buffer pair.
- `audit/candidate-correction-100076d0.md`: Ghidra/Plugin-SDK address evidence and the remaining warning/validation limits for the texture-global correction.
- `audit/candidate-correction-100099f0.md`: Ghidra/Plugin-SDK evidence, x86 object confirmation, and validation limits for the frame-counter global correction.
- `audit/candidate-correction-100074d0.md`: Ghidra/Plugin-SDK pool-layout evidence, x86 object confirmation, and scoped validation limits for the vehicle-pool correction.
- The original `ImVehFt.asi`, GTA files, generated object files, and large historical progress backups are intentionally not included.

The reference binary was SHA-256 `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3` when recorded locally. This fingerprint is included for traceability; it does not imply that the original binary is distributed here.

## Names and formatting

The binary does not contain the original source filenames. Address-based names such as `10001040.cpp` are stable identifiers, not claims about the developer's original naming. `audit/function-name-map.csv` preserves the Ghidra-observed function name and signature for every candidate. Names such as `FUN_...` are automatic Ghidra labels; recognized library/ABI names are marked separately, but they are not assumed to be the original author names.

The candidate files are stored with actual line breaks. Older generated exports may display literal `\\n` sequences; those are serialization artifacts and are not used by the current `src/functions/` set.

## Rights and use

The original mod's source and redistribution license have not been established in this work. No license grant for ImVehFt, GTA San Andreas, or third-party SDK/runtime code is made by this repository. Do not redistribute the original binary or assume that this reconstruction is authorized for reuse; resolve the relevant rights with the original rights holders first.
