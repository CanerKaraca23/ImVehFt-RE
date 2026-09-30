# Candidate crash experiments vs recovered source purity (2026-09-30)

## Question

Did the v7/v8/v9/v10 crash work alter the recovered 705-function source in a
way that compromises the original-code reconstruction?

## Findings

- The v8 `_Type_info_dtor` argument-order correction was applied by
  `scripts/patch-candidate-seh-prolog4-arg-order.py` to a disposable v7 PE
  candidate. The script verifies the pinned input image and exact object bytes,
  then writes a new candidate. It does not edit a file under `src/functions/`.
- The v10 SEH rebase probe adds two HIGHLOW records to a disposable v9 image;
  it copies the rest of the image bytes unchanged. It does not alter the
  recovered source or instruction bytes.
- The source reconstructions of `___DllMainCRTStartup` (`100110BD`) and
  `__CRT_INIT_12` (`10010F59`) were changed after earlier crashes, but their
  purpose was to follow the Ghidra-derived original instruction and control
  flow rather than to invent new behavior. Independent normalized COFF
  instruction comparisons report 87/87 and 99/99 instructions matching the
  corresponding Ghidra exports. Reverting these to the prior high-level C++
  versions would reintroduce compiler prologues and lose that original-code
  evidence, so they are retained in the pure reconstruction source.
- The v1 first-chance crash investigation found the immediate fault in the
  cloned install's `eax.dll` at `AAM 0`, called from ImVehFt startup. Candidate
  bytes in `_getSystemCP` (`0x100144EA`) contain an absolute immediate for
  `_LocaleUpdate` at `0x10010B1A`; the emitted PE relocation set lacks a
  HIGHLOW record at candidate RVA `0x4CE20`. This points to an image-relocation
  omission, not a reason to rewrite the recovered function's semantics. No
  source fix for this crash was applied after the run.
- Runtime tests used `C:\GTASA-ImVehFt-Test-20260930`, a clone of the user's
  modded installation. Its game executable hash matches the installed game;
  the clone contains CLEO, SAMP/OMP, ModLoader and other plugins/mods. It is
  not a clean-game test, and a crash there cannot alone prove candidate-only
  behavior.

## Publication boundary

Publish the reconstructed sources, reproducible source/object audits and the
honest status of the failed experiment. Do not publish the experimental v7,
v8, v9, v10, or v1 ASI as a release. Build products and dumps remain local;
the installed original ASI remains untouched. The reverse-engineering set is
not complete: the experimental candidate failed startup, clean-game testing
is unavailable, and semantic equivalence of all 705 functions is unproven.
