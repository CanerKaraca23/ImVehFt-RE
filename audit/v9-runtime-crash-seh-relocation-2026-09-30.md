# v9 runtime crash: SEH handler relocation

## Finding

The v9 candidate is strongly implicated in the 2026-09-30 GTA test crash. The captured unhandled exception is `0xC0000005`, reading address zero, with EIP `0x10012E90`. In the dump, `eax.dll` occupies `0x10000000..0x10030000`, while the candidate ASI was loaded at `0x67EF0000` because its preferred base was unavailable.

The candidate's `___SEH_prolog4` body at RVA `0x4BD90` pushed the fixed address `0x10012E90` and loaded the fixed address `0x10029490`. The old v9 PE has no HIGHLOW relocation records at the immediate fields `0x4BD91` and `0x4BDAE`. Thus after rebasing, those operands still point into `eax.dll` rather than the candidate image. The crash EIP coincides exactly with the first stale target. This is a high-confidence root-cause diagnosis, not yet a runtime-confirmed repair.

## Corrective source change and static checks

In `src/functions/10012e20.cpp`, both inline-assembly constants were changed to symbol references: `OFFSET __except_handler4` and `OFFSET DAT_10029490`. The source backup is `src/functions/10012e20.cpp.pre-dump-seh-relocation-fix-20260930.bak` (same SHA-256 as the pre-edit source: `BB202C4181BA44EA2D4ABF3FE9E3C83EF6204E1A31DCFB5FC4C81FBAE3DD7B12`).

A standalone MSVC x86 compile of the edited function produced COFF `DIR32` relocations at offsets `0x1` and `0x1E`, targeting `___except_handler4` and `_DAT_10029490`. The full strict `/O1 /W4 /WX /MT /arch:IA32 /GS-` build then passed `705/705`. Fresh ReAgent structural parity is `705 GREEN / 0 YELLOW / 0 RED`; the independent objective verifier is `705 PASS / 0 FAIL / 0 UNKNOWN`.

The regenerated 420-root census maps these two fields to candidate RVAs `0x4BD91` and `0x4BDAE`. The candidate-code relocation builder now includes 1,585 appended root HIGHLOW sites (up from 1,583), and its combined base table contains 6,149 sites. These checks establish the relocation metadata needed by a rebuilt candidate, but do not establish that a new PE has been emitted or that it runs correctly.

## Still open

- Rebuild the complete PE using the fresh 705-object set and regenerated relocation/fixup manifests; do not reuse v9's relocation directory.
- Independently inspect the rebuilt image to confirm both relocation fields are present and rebase them in a loader-level check.
- Retest only in the isolated GTA clone. The original ASI remains unchanged; the clone was restored to the original SHA-256 `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
- Even a successful startup test is not proof of all 705 functions' semantic equivalence.
