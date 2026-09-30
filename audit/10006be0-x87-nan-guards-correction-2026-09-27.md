# `10006be0` x87 unordered guard follow-up

Date: 2026-09-27. Follow-up to
[`10006be0-x87-unordered-range-correction-2026-09-27.md`](10006be0-x87-unordered-range-correction-2026-09-27.md).

## Additional mismatches found

Re-reading every `FCOM`/`FNSTSW` block at the start and common exit of
`10006be0` against the current optimized candidate object found three further
NaN-sensitive decision mismatches:

1. At entry, Ghidra compares zero with `param_8`; if `param_8` is not positive
   (including unordered), it also compares zero with `param_10`, returning
   when that value is also not positive/unordered. The old C++ expression
   `param_8 <= 0 && param_10 <= 0` treated unordered comparisons as false and
   could skip the return. It is now written
   `!(param_8 > 0) && !(param_10 > 0)`.
2. In the non-special alpha path, Ghidra's `FCOM ST(2)` plus
   `TEST AH,0x41` takes the `<= 0` exit for an unordered local alpha value.
   The old C++ `local <= 0` did not. It is now `!(local > 0)`.
3. At the common exit, Ghidra's `FCOM` plus `TEST AH,0x41` returns when
   `param_10` is unordered as well as nonpositive. The old C++ `param_10 <= 0`
   did not. It is now `!(param_10 > 0)`.

The optimized MSVC x86 object emits `COMISS` followed by `JA` for the positive
tests and `JBE` for their negated forms; `JBE` is taken on unordered COMISS
results. The x87 range decision corrected in the companion report remains
emitted as `FCOM`/`FNSTSW`/`TEST AH,5`/`SETP`, with the second compare short-
circuited when the first already selects the fallback.

Each source state before these edits is preserved beside
`src/functions/10006be0.cpp` in the `pre-x87-entry-unordered` and
`pre-x87-followup-guards` backups. Current source SHA-256:
`c52ec53e57feafb6224511651d5bb29b5ef12502631030989d9aafb8950a1336`.

## Validation

- Full strict MSVC x86 compile: **705/705**, `/O2 /W4 /WX /MT`, report
  `build/strict-x87-nan-guards-20260927.json`.
- ReAgent objective verifier: **705 PASS / 0 FAIL / 0 UNKNOWN**, report
  `audit/objective-x87-nan-guards-2026-09-27.json`.
- ReAgent full parity: **704 GREEN / 1 YELLOW / 0 RED**, report
  `build/parity-x87-nan-guards-705-20260927.json`; the remaining yellow is
  `100076d0`.

These are not proof of all x87 exception flags, extended-precision rounding,
complete semantic equivalence, production linking, or gameplay. No game test
was run.
