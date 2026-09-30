# `10006be0` fresh candidate-object cross-check

Date: 2026-09-28. This is a focused recompile and assembly spot-check of the
current candidate, not a whole-function equivalence test. No source file was
changed.

## Reproduction

Compiled `src/functions/10006be0.cpp` with the installed Visual Studio 2022
Build Tools x86 developer environment:

```text
/std:c++20 /O2 /W4 /WX /MT /arch:IA32 /c
```

The compile succeeded with no diagnostics. The source SHA-256 is
`ace3868b0c440f04d0d81d81a1e3d33aaa87a861fed6b7218aa76fa0c29335f4`, matching
the `10006be0` row in `audit/source-sha256.csv`.

Artifacts:

- `build/recheck/followup-10006be0-20260928/10006be0.obj`, SHA-256
  `61920ff13b96a963efb648744d350d2ae652ae7c81e99d97f7445560101f82fe`.
- `build/recheck/followup-10006be0-20260928/10006be0.asm`, SHA-256
  `b3e10dfcc4e02025715b93e333b81496161d5ca96df1c89227d8978f1853dcc1`.

## Bounded comparison

The exact-binary Ghidra listing `ghidra_exports/10006be0.json` shows the
`0x006FC580` call blocks build 21 four-byte arguments and clean `0x54` bytes
after the call. In the fresh optimized candidate assembly, the mode-2
`0x006FC580` path likewise calls through the fixed address and executes
`add esp, 84` (`0x54`). The compiler output also contains the dedicated
12-stack-argument/EAX entry bridge and caller bridge described in
`audit/10006be0-register-corona-abi-bridge-2026-09-28.md`.

This confirms selected ABI/stack-shape facts in the current compiled object.
It does not compare all 21 argument values on every control-flow path, prove
the full x87/FPU environment behavior, validate the other call paths, prove
semantic equivalence, or exercise GTA. The translation unit remains only
partially verified; production `.asi` and gameplay validation are absent.
