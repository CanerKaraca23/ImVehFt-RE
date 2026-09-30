# Current `100014a0` O1 object differential — 2026-09-29

## Result

Ten fresh PE32/x86 harness processes passed, each running 64 cases (640 total)
against the hash-pinned original `ImVehFt.asi`. The original function executes
from an in-memory preferred-base mapping and its real `std::exception` copy
constructor/helper chain. The candidate function executes from the current
`/O1 /GS-` COFF object. The candidate's unresolved base-copy helper is modeled
by a bounded stub for the non-owning short-message case (`_DoFree == 0`).

Compared results: each implementation returned its own destination address;
the original wrote vtable `0x10022250`; the candidate wrote its harness-resolved
relocation alias; and the exception payload, ownership byte, and adjacent
bytes matched for varied inputs and seeded destination storage.

## Ghidra basis

`C:\Users\caner\OneDrive\Documents\ImVehFt\ghidra_exports\100014a0.json`
records the target's call to `0x10010351`, overwrite with bad_alloc vtable
`0x10022250`, return of `this`, and `ret 4`. The export for `0x10010351`
shows base exception initialization followed by assignment; the assignment
export shows the `_DoFree == 0` path copies the message pointer/value without
allocation. The harness's first draft incorrectly cleared a whole DWORD where
the original writes one byte at offset 8; assembly inspection exposed this
test-model bug. The corrected harness models the byte store and then passed.

## Reproducibility and integrity

- Original ASI SHA-256: `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`
- Candidate source SHA-256: `E87AC172D9974DE4CD2A865F1165D7B0D77AD07B9721E8CC43F9A69ECC0BED65`
- Candidate object: `build/recheck/strict-xcode-nogs-o1-exception-fix-20260929/100014a0.obj`
- Candidate object SHA-256: `FC90C7C83512DF7539F3160171386CC683F33FD2D15833709328A7331117BF11`
- Harness source SHA-256: `DA9990FFE5E8768BC5115F8025493E3507711E1A16A88F3887FA49D47E453566`
- Harness executable SHA-256: `C37DE52B45F179DF26B5E4CAACE2F55878181D4289C61A79936D36C23087C1C2`
- Runner: `scripts/test-100014a0-original-binary-differential.ps1`

The original file was not modified. The candidate C++ source was not changed
for this test. The executable was built with VS 2022 x86 tools under `/O1 /W4
/WX /MT /arch:IA32 /GS-`.

## Remaining boundary

This does not exercise `_DoFree != 0`, long/heap-owned exception messages,
allocation failure, arbitrary invalid pointers, or the broader exception
runtime. The copy helper's modeled path is deliberately bounded to the
non-owning case. It also does not establish production PE/ASI section and
relocation correctness or live GTA behavior. Full-set compile/objective/parity
remain structural checks, not semantic/runtime proof.
