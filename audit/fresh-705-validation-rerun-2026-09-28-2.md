# Fresh whole-set validation rerun 2

Date: 2026-09-28. This rerun was performed after the `100076d0` isolated
execution work. No candidate `.cpp` files changed during the rerun.

## Results

- Fresh strict MSVC x86 compile: **705/705 passed, 0 failed**, with
  `/std:c++20 /O2 /W4 /WX /MT /arch:IA32 /c` under Visual Studio 2022 Build
  Tools MSVC 14.44.35207. Report:
  `build/strict-all-live-20260928-2.json`; objects:
  `build/recheck/strict-all-live-20260928-2/`.
- Fresh independent ReAgent objective verifier: **705 PASS / 0 FAIL / 0
  UNKNOWN**. Report: `audit/objective-live-2026-09-28-2.json`.
- Candidate-source integrity: all **705/705** source SHA-256 values in the
  current objective report matched both `audit/source-sha256.csv` and the
  preceding objective report (`objective-live-2026-09-28-1.json`); zero
  mismatches.
- ReAgent parity: the latest saved full run remains
  `build/parity-live-20260928-1.json`, **705 GREEN / 0 YELLOW / 0 RED**. The
  objective source hashes for this rerun match the objective hashes associated
  with that parity run, so the candidate source set is identical. ReAgent was
  at commit `d12cea338c61898b06a86fe8adb25275fa9d5615` with 42 modified
  tracked files; this is a locally modified 0.4.0 checkout, not pristine
  upstream ReAgent. This parity result is structural and does not prove
  semantic equivalence.
- The reproduction script
  `scripts/test-100076d0-model-info-harness.ps1` compiled the fresh
  `100076d0.obj` and passed **10/10 fresh PE32 processes**. The final test image
  is `build/abi-harness/100076d0-model-info-harness-20260928-101119-574.exe`,
  SHA-256 `3A189556011B3FEC5FC83B958798119EDFB5DCC30CD5FAE0974D0DC44127E130`.
  Each process covered both model-info routes for selectors `0xFF..0xF0` plus
  one controlled callback/re-entry case. Harness-specific caveats are in
  `audit/100076d0-model-info-index-runtime-harness-2026-09-28.md`.

## Validation boundary

These results reconfirm compilation, the structural objective gate, source
hash integrity, ReAgent parity, and the scoped synthetic harness. They do not
prove all-function semantic equivalence, the live RenderWare callback graph,
the original ImVehFt build configuration, production image layout/hook
integration, or in-game behavior. The only produced DLLs remain diagnostic;
no loadable `.asi` or gameplay validation is established.
