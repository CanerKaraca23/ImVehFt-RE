# ReAgent negative-control check — 2026-09-29

## Purpose

Tested whether the current green gates detect a plainly wrong data value while
the candidate's control flow and calls remain unchanged. This is a validator
calibration experiment, not a finding that the real candidate contains the
mutated value.

## Negative control

Target: `0x10001010`, source `src/functions/10001010.cpp`. Ghidra identifies
the constructor's vtable setup; the current body stores the relocatable alias
`IVF_IMAGE_ADDRESS_10022250` before calling its exception-base initializer.
For the test only, in-memory source strings replaced that address alias with
integer zero. No workspace candidate or Ghidra export was edited, and the
negative-control source was not compiled or installed.

The actual current ReAgent 0.4.0 source was imported from
`C:\Users\caner\OneDrive\Documents\ImVehFt\reagent\src`, and the actual
Ghidra function export was read from `ghidra_exports`. Results:

| Check | Current candidate | In-memory wrong-vtable control |
|---|---|---|
| Objective verifier (`verify_candidate`) | PASS | **PASS** |
| Parity engine (`score_single`, actual Ghidra export/config/rules) | GREEN | **GREEN** |

The tested function has Ghidra decompile and ASM evidence (15 instructions,
2 calls); the address has no manual-check override. Both checkers returned no
findings for either version.

The in-memory experiment is reproducible with
`python scripts/test-reagent-semantic-negative-control.py`; it exits zero
only when both current and mutated cases receive the expected PASS/GREEN
results. It verifies that this specific negative control is not detected; it
is not an all-target semantic validator.

## Interpretation

The result is consistent with the inspected implementations: the objective
verifier compares selected call/control-flow counts and only compares literal
return values in a narrow constant-return case; parity signals check such
features as source presence, suspicious stubs, body length, floating-point
tokens, and call-count deltas. Neither gate compares this constructor's
vtable-pointer value against the Ghidra store. Thus `705 PASS / 705 GREEN`
cannot establish constant/data-reference semantics for all 705 functions.

This does **not** invalidate the current `10001010` candidate, whose value is
separately backed by Ghidra/raw-PE relocation evidence. It proves that the
aggregate green gates alone would not catch this specific semantic regression.
Per-function evidence must therefore include relevant constants, memory
offsets, branch predicates, and call targets—not only compilation and these
structural scores.

No candidate source edit or backup, candidate build, ASI generation, or GTA
runtime test was made for this negative control. The new script is a
read-only validator-calibration test and never writes its mutated source to
disk.
