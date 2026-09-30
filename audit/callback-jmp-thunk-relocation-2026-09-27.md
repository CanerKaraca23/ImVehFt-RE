# Callback JMP thunk relocation (2026-09-27)

## Ghidra evidence and implementation

Read-only listings at `candidate-code-literal-window-1000c640-2026-09-27.txt`,
`candidate-code-literal-window-1000c700-2026-09-27.txt`,
`candidate-code-literal-window-1000c7d0-2026-09-27.txt`,
`candidate-code-literal-window-1000c7f0-2026-09-27.txt`, and
`candidate-code-literal-window-1000c8b0-2026-09-27.txt` map 70 callback labels
between `0x1000c640` and `0x1000ca90`. Each is a five-byte `JMP rel32` to one
of the address-named functions in the 705-candidate set. Their pointer literals
occur in 12 dispatcher translation units.

`scripts/generate-relocatable-callback-jmp-thunks.py` reproduces the CSV map
and MASM source from those listings and source-literal inventories v5/v6.
`scripts/relocate-callback-jmp-literals.py` replaced the 58 fixed target VAs
replaced the 70 fixed target VAs with addresses of C-linkage labels, after
backing up each newly changed TU. The
MASM object leaves all 58 target transfers as linker-resolved `REL32` entries.

## Validation

- The generated assembly and manifest reproduce byte-for-byte from the saved Ghidra listings.
- `scripts/verify-callback-jmp-thunks.py` checks all 70 labels, exact five-byte `E9 rel32` bodies, COFF offsets, and target relocation sites/symbols: 70/70.
- `dumpbin /symbols` confirms all 70 undefined `_LAB_*` references from the candidate objects are defined by the thunk object, with no missing names.
- The combined `scripts/build-hook-shims.ps1` run passes the 12 existing hook byte streams, 25 `PUSH ECX; CALL; RET` callback entries, and these 70 callback JMP entries.
- Fresh MSVC 2022 x86 `/O2 /W4 /WX /MT /c`: **705/705** (`build/strict-callback-relocations-v3-20260927.json`). The earlier 704/705 attempt is retained as a failed diagnostic; the duplicate declaration in `1000aea0` was removed while keeping the pre-edit backup, then all gates were rerun.
- Independent ReAgent objective: **705 PASS / 0 FAIL / 0 UNKNOWN** (`audit/objective-callback-relocations-v3-2026-09-27.json`).
- ReAgent 0.4.0 parity: **704 GREEN / 1 YELLOW / 0 RED** (`build/parity-callback-relocations-v3-20260927.json`). The semantic YELLOW remains `0x100076d0`.
- Scoped manual call-count cross-check: 13 records / zero audit errors (`audit/manual-parity-call-counts-callback-relocations-v3-2026-09-27.json`). Its scope is only adjudicated call-count heuristics; it does not validate semantics.
- Refreshed source manifests match all 705 TUs with zero hash mismatches. The updated literal inventory is `candidate-internal-image-address-literals-v7-2026-09-27.json/.csv`: 81 occurrences across 63 unique original `.text` addresses remain.

## Limits

These 58 stubs resolve only one mapped family of callback pointers. The rest
of `.text` relocation, complete image placement, startup/CRT and import
integration, production linking, and game testing remain open. No rebuilt
`.asi` is created by this batch.
