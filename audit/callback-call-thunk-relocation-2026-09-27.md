# Callback CALL thunk relocation (2026-09-27)

## Evidence and change

The read-only Ghidra listing `candidate-code-literal-window-1000c8b0-2026-09-27.txt`
shows 15 code labels from `0x1000cc30` through `0x1000cd10`. Each is exactly
`PUSH ECX; CALL <candidate>; RET`, with the `CALL` targeting one of the
address-named candidate functions `1000f4a0`, `1000f520`, `1000f5a0`,
`1000f620`, `1000f6a0`, `1000f720`, `1000f7a0`, `1000f820`, `1000f8a0`,
`1000f920`, `1000f9a0`, `1000fa20`, `1000faa0`, `1000fb20`, and `1000fba0`.

`scripts/inventory-callback-call-thunks.py` cross-matches the instruction
sequences to the 705-source literal inventory and records the decorated
candidate target names in `candidate-callback-call-thunks-v1-2026-09-27.csv`.
The three owning dispatchers now use C-linkage thunk labels rather than fixed
preferred-image constants; the existing callback entry MASM object contains
all 25 verified `PUSH/CALL/RET` thunks (the prior ten plus these 15).

## Validation

- The call-thunk mapping regenerates byte-for-byte from the saved Ghidra listing and inventory.
- `scripts/build-hook-shims.ps1` checks the exact 7-byte bodies and all 25 COFF `REL32` relocations, alongside 70 JMP thunks and 12 other hook streams.
- Candidate objects reference all 15 new `_LAB_*` names; the MASM thunk object defines all 15.
- Fresh whole-set gates: strict compile 705/705 (`build/strict-callback-relocations-v3-20260927.json`), objective 705 PASS / 0 FAIL / 0 UNKNOWN (`audit/objective-callback-relocations-v3-2026-09-27.json`), ReAgent parity 704 GREEN / 1 YELLOW / 0 RED (`build/parity-callback-relocations-v3-20260927.json`). The only YELLOW is `0x100076d0`.
- The updated source-literal inventory has 81 occurrences / 63 unique `.text` addresses. This batch removed 15 pointer literals; remaining values still need per-use Ghidra classification.

## Limits

These small callback thunks do not supply a complete PE image or full original
`.text` relocation. Production linking, complete startup/import/hook
integration, and GTA runtime tests remain outstanding; no `.asi` was emitted.
