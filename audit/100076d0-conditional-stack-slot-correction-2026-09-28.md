# `100076d0` conditional stack-slot correction (2026-09-28)

## Finding and correction

The source previously declared `local_c = 0`, adding an unconditional entry
write absent from Ghidra. That was a real mismatch hidden behind the earlier
ordinary-dispatch argument: the global is re-read after callback-capable paths,
so it is not safe to assume it cannot change during the function.

The candidate now leaves `local_c` unwritten at entry. When later control flow
re-reads `DAT_1003c1fc` and the value is nonzero, a small x86 inline-assembly
sequence snapshots the raw stack slot before using its fields. This preserves
the original machine-level behavior even for a path where the global becomes
nonzero after the entry check, without asking C++ to evaluate an indeterminate
scalar. The other `local_c = 0` is retained: it initializes the later palette
index loop, matching the later Ghidra store at `0x10007e22`.

The non-volatile, uninitialized declaration by itself failed `/W4 /WX` with
C4701 at a guarded later use. The final version avoids suppressing that
warning: raw stack reads are expressed explicitly in inline assembly, and the
complete translation unit compiles with `/O2 /W4 /WX /MT`.

## Evidence and verification

- Ghidra export: `C:/Users/caner/OneDrive/Documents/ImVehFt/ghidra_exports/100076d0.json`.
- Ghidra stores the vehicle-context value at `[EBP-8]` only on the nonzero-entry
  path (`0x1000770e`), reads it at `0x10007970` and `0x10007c54`, and later
  reuses the slot for a separately initialized palette index at `0x10007e22`.
- Fresh MSVC x86 `/O2` object: `build/recheck/strict-all-post-conditional-slot-20260928/100076d0.obj`.
  The entry path has no unconditional zero store to the context slot; its first
  context write follows the nonzero guard. The later raw-slot loads are also
  guarded by the global checks. The later palette-loop zero/store remains.
- Fresh full strict compile: `build/strict-all-post-conditional-slot-20260928.json`
  reports 705/705 passed, 0 failed.
- Fresh local ReAgent parity: `build/parity-post-100076d0-cond-stack-slot-20260928.json`
  reports 705 GREEN, 0 YELLOW, 0 RED.
- Fresh independent structural objective audit:
  `audit/objective-post-100076d0-cond-stack-slot-2026-09-28.json` reports
  PASS=705, FAIL=0, UNKNOWN=0.
- Pre-edit source backup:
  `src/functions/100076d0.cpp.pre-conditional-stack-slot-20260928.bak`.

## Limits

This is evidence that the candidate now models the observed conditional stack
slot and that the compiler preserves the intended conditional accesses. It
does not verify real callback-target values, live re-entry frequency, all
runtime state, whole-image relocation/loader integration, or in-game behavior.
The parity result is not a runtime certification.
