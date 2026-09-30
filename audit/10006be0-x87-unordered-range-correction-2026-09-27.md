# `10006be0` x87 unordered-range correction

Date: 2026-09-27

## Finding

Ghidra's ImVehFt listing at `0x10006df7`--`0x10006e16` compares the computed
float against `0x10024f28` and `0x10024f38` using x87 `FCOM`/`FCOMP`, reads
the x87 status with `FNSTSW AX`, and tests `AH & 5` before a parity branch.
For an unordered comparison (NaN), both condition bits are set, the masked
value has even parity, and the target takes the default-alpha path.

The prior optimized candidate object used SSE `COMISS` followed by `JAE` for
these range checks. With an unordered operand, `COMISS` sets CF, so `JAE`
(CF=0) is not taken; both checks could fall through into the scaling path.
That differs from the target for NaN inputs, even though ordinary finite
values follow the same range rule.

## Correction and evidence

`src/functions/10006be0.cpp` now performs the two comparisons with inline x87
operations and reproduces the target's `TEST AH,5` / parity decision. The
second comparison remains conditional on the first not selecting the default
path, matching the target's short-circuit control flow. The pre-edit source is
preserved as
`src/functions/10006be0.cpp.pre-x87-unordered-range-fix-20260927.bak`.

Fresh `/O2 /W4 /WX /MT` object disassembly at
`build/recheck/strict-x87-unordered-range-20260927/10006be0.obj` emits:

- upper bound: `FLD`, `FLD`, `FCOM ST(1)`, `FNSTSW AX`, `TEST AH,5`, `SETP`,
  then pops the two temporary comparison values;
- lower bound: `FLD`, `FCOMP m32real`, `FNSTSW AX`, `TEST AH,5`, `SETP`.

Both preserve the target's unordered decision. This local correction does not
claim identical x87 stack lifetime or all later floating-point rounding and
exception-state behavior; those remain in the broader `10006be0` semantic
review.

## Validation

- Full strict MSVC x86 compile: **705/705**, `/O2 /W4 /WX /MT`, report
  `build/strict-x87-unordered-range-20260927.json`.
- ReAgent objective verifier: **705 PASS / 0 FAIL / 0 UNKNOWN**, report
  `audit/objective-x87-unordered-range-2026-09-27.json`.
- ReAgent full-set parity: **704 GREEN / 1 YELLOW / 0 RED**, report
  `build/parity-x87-unordered-range-705-20260927.json`; this structural
  heuristic still leaves `100076d0` YELLOW and is not semantic proof.
- Updated candidate source SHA-256:
  `bf33cbd50ae8039333152555d1a87342f9f7789010e6b7835690b257cae66fca`.

No game/runtime test was run; no production DLL was linked or loaded.
