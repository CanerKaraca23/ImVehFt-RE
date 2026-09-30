# Fresh 705-candidate validation rerun

Date: 2026-09-28. The candidate source tree was rechecked after the latest
linker experiments. No candidate `.cpp` source was edited for this rerun.

## Results

- Strict MSVC x86 compile: **705/705**, zero failures, using `/std:c++20
  /O2 /W4 /WX /MT /arch:IA32 /c`. Compiler: Visual Studio 2022 Build Tools
  MSVC 14.44.35207, HostX64 x86 compiler. Report and fresh objects:
  `build/strict-all-live-20260928-1.json` and
  `build/recheck/strict-all-live-20260928-1/`.
- Independent ReAgent objective verifier: **705 PASS / 0 FAIL / 0 UNKNOWN**.
  Report: `audit/objective-live-2026-09-28-1.json`. This is a structural
  verifier, not semantic or runtime proof.
- ReAgent **0.4.0** parity rerun against configured Ghidra JSON, hook CSV,
  manual-check notes, and semantic rules: **705 GREEN / 0 YELLOW / 0 RED**.
  Report: `build/parity-live-20260928-1.json`. Invocation used the local
  `C:/Users/caner/OneDrive/Documents/ImVehFt/reagent/src` checkout at Git
  commit `d12cea3`, with **42 modified tracked files**, including
  `parity/engine.py` and `parity/source_indexer.py`. Therefore this result is
  for the locally modified ReAgent 0.4.0 tree, not a pristine upstream 0.4.0
  run. No LLM provider or model calls are involved in this parity command.

The objective report embeds a source SHA-256 for each candidate. All 705
hashes matched both `audit/source-sha256.csv` and a fresh post-run hash of the
current source tree (zero mismatches), so the compile, objective run, and
parity rerun describe the same unchanged candidate source set.

## Validation boundary

These are reproducible compile and static/structural checks, not proof that
all 705 functions are semantically identical to the unavailable original
build or behave correctly in-game. No production `.asi` was produced or
loaded. The latest linked PE remains diagnostic-only; its startup, function
placement, image layout, and runtime compatibility are not validated. Original
ImVehFt project/build recipe and in-game validation remain open.
