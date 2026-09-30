# Additional candidate/CRT fallback target relocations (2026-09-27)

## New mappings

The v8 provider left Ghidra-named code entries such as `__purecall`,
`___initmbctable`, `__fpmath`, `exception`, and `Unwind@...` unresolved because
the generator only accepted address-shaped `FUN_...` names. Cross-checking the
target VA against the address-named fresh COFF object showed these are
represented by exact public code entries in the 705 candidate object set. The
v9 provider now maps those entries by their actual public COFF symbol and
object, adding **28 pointer sites** (including the 21 `__purecall` table
entries) without guessing a neighboring function.

The remaining ten `.data` pointers target the four-instruction helper at
`0x1001af2b`, identified in the saved Ghidra window as `PUSH 2; CALL
0x10012e01; POP ECX; RET`. The call destination is the candidate
`__amsg_exit(int)` at `0x10012e01`; its fresh object contains one public code
entry. V9 emits the equivalent helper as a separate COFF code symbol and
retargets all **10** fallback table slots to it.

## Fresh verification

- MASM x86 `/coff` assembly succeeded.
- Ghidra-backed thunk check remains **22/22**.
- COFF verifier passes **1,473/1,473** data/code pointer fixups: 1,322
  data-to-data, 119 exact candidate-code targets, 22 CRT initializer thunk
  targets, and 10 fallback-helper targets; zero mismatches.
- All **54** emitted `.text` code relocations pass symbol/type/site checks,
  including all 53 CRT-thunk references and the fallback helper's call to the
  candidate `__amsg_exit` symbol.
- All **48** residual code-target pointer sites remain unresolved.

The generator and verifier are
[`scripts/generate-coff-dat-relocation-provider.py`](../scripts/generate-coff-dat-relocation-provider.py)
and [`scripts/verify-coff-dat-relocation-provider.py`](../scripts/verify-coff-dat-relocation-provider.py).
The exact Ghidra evidence for the fallback helper is
[`pe-relocation-unmapped-code-target-instruction-windows-recheck-2026-09-27.csv`](pe-relocation-unmapped-code-target-instruction-windows-recheck-2026-09-27.csv);
the candidate target mapping is in
[`function-name-map.csv`](function-name-map.csv) and its strict object is
`build/recheck/strict-fresh-after-source-discovery-20260927/10012e01.obj`.

## Limits

This remains a diagnostic provider, not a complete project link or testable
`.asi`. The remaining 48 sites include four `_initterm_e` CRT callbacks and
exception/funclet/runtime targets. The original `.text` still has 3,160 HIGHLOW
relocations not reconstructed here; global/function image layout, all hook
retargeting, complete startup integration, production linking, and in-game
validation remain open. Do not load this object.
