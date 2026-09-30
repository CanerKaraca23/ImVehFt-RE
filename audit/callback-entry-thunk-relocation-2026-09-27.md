# Callback entry thunk relocation (2026-09-27)

## Finding and change

The 705-source literal inventory identified five code pointers at
`0x1000cd20` through `0x1000cd60` in `FUN_1000c1a0`, and five more at
`0x1000cd70` through `0x1000cdb0` in `FUN_1000c2e0`. A read-only Ghidra
listing shows each target is a seven-byte callback entry consisting of
`PUSH ECX; CALL <candidate>; RET`; the target calls are respectively
`1000fc20`, `1000fca0`, `1000fd20`, `1000fda0`, `1000fe20`, `1000fea0`,
`1000ff20`, `1000ffa0`, `10010020`, and `100100a0`.

The candidate dispatchers now take the addresses of public `LAB_*` labels
instead of preferred-image constants. The labels are defined by
`src/hook_shims/x86_callback_entry_thunks.asm`, where each `CALL` targets the
candidate's decorated x86 symbol and is left for the linker to resolve as a
COFF `REL32` relocation. Backups of the pre-edit `1000c1a0` and `1000c2e0`
sources are retained adjacent to those source files. A second Ghidra-confirmed
group of 15 entries at `0x1000cc30`–`0x1000cd10` was added to the same thunk
object; see [`callback-call-thunk-relocation-2026-09-27.md`](callback-call-thunk-relocation-2026-09-27.md).

## Evidence and checks

- Read-only Ghidra listing for the first group: `candidate-code-literal-window-1000cd10-2026-09-27.txt`.
- Read-only Ghidra listing for the second group: `candidate-code-literal-window-1000cd70-2026-09-27.txt`.
- `scripts/verify-callback-entry-thunks.py` verifies all 25 exact 7-byte bodies, their label offsets, and 25 COFF `REL32` fixups to the expected candidate symbols. Fresh MASM assembly passes.
- The two fresh candidate COFF objects have undefined references to the exact ten `_LAB_*` names, and the thunk object defines those same ten symbols; no C++/MASM decoration mismatch is present.
- `scripts/build-hook-shims.ps1` passes all 12 existing bounded hook-body byte comparisons and the 25 callback thunk byte/relocation checks.
- Fresh aggregate MSVC 2022 x86 `/O2 /W4 /WX /MT /c` compile: 705/705 (`build/strict-callback-relocations-v3-20260927.json`).
- Independent ReAgent objective: 705 PASS / 0 FAIL / 0 UNKNOWN (`audit/objective-callback-relocations-v3-2026-09-27.json`).
- ReAgent 0.4.0 parity: 704 GREEN / 1 YELLOW / 0 RED (`build/parity-callback-relocations-v3-20260927.json`). The YELLOW remains `0x100076d0`; it is not waived.
- The fresh scoped call-count audit has 13/13 adjudication records and zero audit errors (`audit/manual-parity-call-counts-callback-relocations-v3-2026-09-27.json`); this is only a call-count cross-check, not semantic proof.
- Source hash and name-map manifests were refreshed with backups and have zero hash mismatches. Updated literal inventory: `candidate-internal-image-address-literals-v7-2026-09-27.json/.csv`; 81 occurrences remain, across 63 unique addresses.

## Limits

The combined callback batches now cover 95 source-referenced code pointers
(25 `PUSH/CALL/RET` entries and 70 `JMP rel32` entries), plus the separate 12
bounded hook streams. They do not complete general `.text` relocation,
original PE layout, startup/CRT integration, imports, hook installation or
production linking. No rebuilt `.asi` or GTA runtime test is produced by these
checks.

## Newly mapped adjacent targets

A further read-only listing, `candidate-code-literal-window-1000c8b0-2026-09-27.txt`,
showed six additional groups of five source-referenced code labels from
`0x1000c8c0` through `0x1000ca90`. Each is a five-byte `JMP rel32` to a
candidate callback body; the corresponding dispatchers are
`1000b460`, `1000b5a0`, `1000b6e0`, `1000b8e0`, `1000bae0`, and `1000bb60`.
The full 70-label range, including the earlier `0x1000c640`–`0x1000c6f0`
group, has now been converted and verified. The additional 15 PUSH/CALL/RET
labels at `0x1000cc30`–`0x1000cd10` are also converted; see the linked
callback-call and callback-JMP audit reports above.
