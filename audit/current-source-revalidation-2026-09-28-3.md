# Current-source validation rerun 3

Date: 2026-09-28. This rerun validates the present 705 translation units in
`src/functions`; all reports and binaries were written to fresh, non-overwriting
paths. It made no candidate-source edits and used no model/API calls.

## Results

- Strict MSVC 14.44 x86 compile: **705/705 passed, 0 failed**, with
  `/std:c++20 /O2 /W4 /WX /MT /arch:IA32 /c`. Report:
  `build/strict-705-live-20260928-3.json`; object set:
  `build/recheck/strict-705-live-20260928-3/`.
- Independent ReAgent objective verifier: **705 PASS / 0 FAIL / 0 UNKNOWN**.
  Report: `audit/objective-independent-live-2026-09-28-3.json`.
- Local modified ReAgent 0.4.0 parity, run against the current source root and
  705-entry hooks list: **705 GREEN / 0 YELLOW / 0 RED**. Report:
  `build/parity-705-live-20260928-3.json`. This remains a structural check.
- Fresh candidate-object/original-binary differential for `100076d0`: the
  object produced by the just-completed whole-set strict compile was tested
  against the installed ASI in **10/10 fresh PE32 processes**. The original
  reference hash matched
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`;
  candidate object SHA-256:
  `09D9FEAC544FDB560931C71A80DC73BB4E44237E72F2EF3938DAA5DE84F8C6EF`;
  harness SHA-256:
  `A45DFAB3B202996503457B8D078F6B310752B318C97895660DC8B0585E3C1B0F`.
  Executable: `build/abi-harness/100076d0-current-source-original-diff-20260928-3.exe`.

## Evidence boundary

The `100076d0` harness compares the compiled candidate with the original
function bytes for the cases encoded in
`tests/runtime_100076d0_model_info_harness.cpp`. Fixed game addresses and
RenderWare callback/lookup behavior are redirected to controlled test state;
it is not an initialized GTA/RenderWare session. Therefore the fresh rerun
confirms current-source consistency and the scoped differential only. The
live texture/raster callback target, external-mod/driver behavior, complete
705-function semantic equivalence, production linking/image layout, and
gameplay behavior remain unverified. Do not interpret 705 green/compile/objective
passes as closure of those gaps.
