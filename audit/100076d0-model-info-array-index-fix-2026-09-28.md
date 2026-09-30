# `100076d0` model-info array index correction

Date: 2026-09-28. Target image SHA-256:
`409F0DF7AE579841DB05C3EC6AD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Discrepancy found

Re-reading `ghidra_exports/100076d0.json` against the current C++ and x86
object exposed a concrete semantic mismatch that ReAgent parity had not
reported. In the final model-info branch, Ghidra counts the texture/model
selector into ECX, stores it to `[EBP-8]` at `0x10007e22`, loads the per-model
pointer from `record + 0x28 + DAT_1003c248`, then selects the indexed item at
`pointer + 0x354 + index * 0x14`. The pre-fix candidate stopped at
`record + 0x28 + base`: it did not dereference that field and did not add the
`0x354 + index * 0x14` item offset before reading fields at `+0x0c` and `+0x09`.

## Correction and emitted-code evidence

`src/functions/100076d0.cpp` now dereferences the model-info pointer and applies
the indexed `0x354 + local_c * 0x14` offset. The MSVC x86 `/arch:IA32` object
disassembly contains the matching operations: load `[eax+edi+28h]`, scale the
selector by five, then access `[esi+edi*4+360h]` (the `0x354 + index*0x14 +
0x0c` field) and test `[esi+edi*4+35Dh]` (the corresponding `+0x09` byte).

The same review found the reused `[EBP-8]` local also holds the selector index.
The naked x86 entry bridge now begins with the target's exact frame setup
(`push ebp; mov ebp,esp; sub esp,30h; push edi`), passes the physical
`[EBP-8]` slot into the C++ implementation, and writes the loop index there
before the subsequent model-info lookup. This preserves the target stack slot
across the conditional entry-context write and later reuse. Source backup:
`src/functions/100076d0.cpp.pre-model-info-array-index-fix-20260928.bak`.

## Fresh checks

- Targeted MSVC x86 `/O2 /W4 /WX /MT /arch:IA32` compile passed; inspected
  object sequence matches the Ghidra pointer/index accesses.
- Full strict compile: **705/705**,
  `../build/strict-all-model-info-array-index-20260928.json`.
- Independent objective verifier: **705 PASS / 0 FAIL / 0 UNKNOWN**,
  `objective-model-info-array-index-2026-09-28.json`.
- ReAgent parity: **705 GREEN / 0 YELLOW / 0 RED**,
  `../build/parity-model-info-array-index-20260928.json`. This structural
  parity gate missed the discrepancy before the manual Ghidra/object review;
  it is not semantic proof.
- Fresh link from all 705 new objects succeeded to
  `../build/link-probe/strict-704-historical-sdk/ImVehFt-model-info-array-index-diagnostic-not-ASI.dll`.
- Scoped manual call-count re-audit: **13/13 checks, zero errors** using the
  current full object set. For `100076d0`, Ghidra has 21 CALLs and the target
  plus implementation COFF symbols have 28: seven modern `/GS` cookie checks,
  one bridge-to-implementation call, and one fewer texture-lookup call site
  due to mutually exclusive tails being merged. Report:
  `manual-parity-model-info-array-index-2026-09-28.json`. This checks call
  accounting only, not behavior.

This resolves the identified static model-info pointer/index discrepancy. It
does not settle `100076d0`'s remaining live RenderWare callback/re-entry
uncertainty, nor provide gameplay validation. The diagnostic DLL is not a
loadable ASI; no semantic/runtime completion claim is made.
