# Evidence-backed raster-lock corrections (2026-09-24)

## Binary and SDK evidence

The reference `ImVehFt.asi` was re-hashed as `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`. The local Ghidra export for `10003ba0` shows stores to `0x00C3EF60`, `0x00C3EF64`, and `0x00C3EF68`, followed by a call through `0x7FB2D0` whose return is stored at `0x00C3EF78`. The export for `10003e60` calls `0x7FB2D0`, tests the value at `0x00C3EF78`, indexes/copies bytes from that buffer, then calls `0x7FAEC0`.

The independently checked Plugin-SDK declares `0x7FB2D0` as `RwRasterLock` returning `RwUInt8*` and `0x7FAEC0` as `RwRasterUnlock` returning `RwRaster*` ([RenderWare.cpp at the inspected SDK commit](https://github.com/DK22Pac/plugin-sdk/blob/b55e89b336a81448c1aa1a5b188431c9845ebaa9/plugin_sa/game_sa/RenderWare.cpp#L789)). This supports modeling `0x00C3EF78` as a byte pointer: the value is a raster-lock buffer, not a `Texture` object.

## Candidate changes

- `src/functions/10003ba0.cpp`: changed `_DAT_00c3ef78` from `Texture*` to `std::uint8_t*`; corrected the `0x7FB2D0` function-pointer return/argument types to the SDK's raster-lock shape.
- `src/functions/10003e60.cpp`: unified the prior differently named `DAT_00c3ef78` declaration with `_DAT_00c3ef78` as `std::uint8_t*`; replaced unresolved pseudo-function imports for `0x7FB2D0` and `0x7FAEC0` with typed calls to the evidence-backed executable addresses. A follow-up Ghidra assembly check also showed that each character is read from `param_1[i]` into `AL` before `0x6FD7C0`, while the candidate had omitted that input. The candidate now pushes the two output addresses, loads the indexed character into `AL`, and calls `0x6FD7C0` directly, matching the Ghidra instruction order and the SDK's unusual register ABI. Existing raster-copy loop and return-bit behavior are preserved.
- The pre-edit tree remains available at commit `14f3377`; the current per-file fingerprints are recorded in `audit/source-sha256.csv`.

## Verification results

- MSVC 2022 x86 C++20 `/O2`: **705/705** translation units compiled and were archived. No full production link is implied.
- MSVC x86 `/W4 /WX /MT`: **2/2** edited translation units compiled. The other 703 files are byte-identical to the preceding full-set strict-audit inputs.
- ReAgent **0.4.0** `doctor`: target evidence/config checks ready for both addresses.
- ReAgent **0.4.0** parity against the published candidate source and local Ghidra exports: **2 green, 0 yellow, 0 red**, with no parity findings. The parity run for `10003e60` was repeated after the `AL` ABI correction. This is static consistency checking, not behavioral proof.
- ReAgent **0.4.0** non-LLM objective verifier against both current candidate sources and local Ghidra exports: **2 PASS**, no structural findings.
- After the raster-lock correction, the diagnostic historical-SDK link had 205 unresolved externals. After the additional `0x6FD7C0` `AL`-register correction, a fresh link against the current 705-object set reports **204 unresolved externals**; no DLL was produced.
- After matching the `0x6FD7C0` `AL`-register call, the current 705-object diagnostic link reports **204 unresolved externals** and still produces no DLL.
- The 705-entry source-hash manifest currently verifies with zero missing or mismatched candidate files.

## Limits and next checks

These corrections are supported by exact Ghidra data-flow and SDK address/signature evidence, but they do not prove the two functions' entire semantics. The full project still lacks a production-ready link (204 unresolved externals remain), and no GTA runtime/game test has been performed. The previous 705/705 ReAgent objective/parity totals refer to the earlier snapshot; only these two functions have been rechecked in ReAgent since this edit.

The compiled `10003e60` object also shows the relevant sequence: push the row and column output addresses, load the first argument plus loop index, move its byte into `AL`, load `0x6FD7C0`, call through `EDX`, then clean the two stack arguments. This matches the order in the Ghidra listing.
