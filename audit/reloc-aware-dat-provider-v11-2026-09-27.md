# `_initterm_e` processor-feature initializer reconstruction (2026-09-27)

## Reconstructed entries

The six-slot `_initterm_e` array has five non-null callbacks. Two entries,
`0x1001704c` and `0x1001c5e0`, are short Ghidra-confirmed routines that call
`IsProcessorFeaturePresent(10)`, save EAX to `DAT_1003c414` and
`DAT_1003c40c`, then return zero. The v11 provider emits relocatable code
labels for these routines, uses the x86 import symbol
`__imp__IsProcessorFeaturePresent@4`, preserves the original data-cell
section offsets, and retargets the two array entries. The installed x86
Windows SDK `kernel32.lib` was checked and contains that import symbol.

This closes only the two processor-feature entries. The other unresolved
non-null callbacks `0x100104bc` and `0x10013025` allocate and initialize CRT
state and can return failure codes; they are intentionally still unresolved.
The fifth entry `0x100148e9` is mapped to its existing candidate object.

## Fresh verification

- MASM x86 `/coff` assembly and Python bytecode compilation succeeded.
- Ghidra-backed `.CRT$XCU` thunk matching: **22/22**.
- COFF verifier: **1,475/1,475** data/code pointer fixups, with zero
  mismatches. These comprise 1,322 data-to-data, 119 exact candidate-entry,
  22 initializer-thunk, 10 CRT-fallback, and 2 processor-feature targets.
- All **58** generated `.text` COFF relocations passed site/type/symbol checks.
- **46** code-target sites remain unresolved.

The update is diagnostic only: no candidate `.cpp` was changed, no complete
plugin link was attempted, and no game test was performed. The recorded
candidate-level checks remain 705/705 strict compile, 705 PASS structural
objective, and 704 GREEN / 1 YELLOW parity; they were not rerun in this
provider-only pass and do not prove semantic/runtime equivalence.

## Reproduction

Use `scripts/generate-coff-dat-relocation-provider.py` and
`scripts/verify-coff-dat-relocation-provider.py` with the v10 commands and add
`--initterm-e-disassembly audit/crt-initterm-e-entry-disassembly-2026-09-27.csv`.
Use `reloc-aware-dat-provider-v11-20260927` for the output stem. The evidence
and remaining `_initterm_e` limits are documented in
[`crt-initterm-e-array-crosswalk-2026-09-27.md`](crt-initterm-e-array-crosswalk-2026-09-27.md).

## Still open

The provider is not a testable `.asi`. Remaining items include the two
allocation/state-table `_initterm_e` bodies at `0x100104bc` and `0x10013025`,
44 other code-target pointer sites, 3,160 original `.text` HIGHLOW
relocations, function/global image layout, game hook retargeting, complete
production linking/import integration, and in-game validation.
