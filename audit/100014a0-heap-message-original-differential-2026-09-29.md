# `100014a0` heap-owned exception-message differential — 2026-09-29

## Result

The expanded test passed in 10 fresh PE32/x86 processes, 64 cases each
(640 total), with no observed mismatch. Each case first constructs a real
heap-owned `std::exception` message by calling the original image's constructor
at `0x100102c3`, then invokes original `100014a0` and the compiled candidate
object on separate destinations. It compares returned destination pointers,
the original bad_alloc vtable (`0x10022250`), candidate relocation alias,
ownership flags, deep-copy pointer inequality, and exact message contents.
Each destination and source is destroyed through the original image's
exception destructor, so the test also checks that those heap allocations are
releasable through the original helper chain.

To make the manually mapped original's allocator usable, this test-only
harness binds only the Ghidra-confirmed `HeapAlloc`/`HeapFree` IAT slots
(`0x10022040`/`0x10022044`) to the current process APIs and sets the original
CRT heap global `0x10039b90` to `GetProcessHeap()`. These edits are to the
in-memory mapping only; the original ASI file is unchanged. The candidate's
external exception-copy helper in the harness forwards to the same original
`0x10010351` helper used by the original function. This isolates the target
function's ABI/dispatch/vtable behavior while exercising the actual original
exception copy, string allocation, and destruction helpers.

## Ghidra evidence

- `ghidra_exports/100014a0.json`: target calls `0x10010351`, overwrites the
  vtable with `0x10022250`, returns `this`, and uses `ret 4`.
- `ghidra_exports/10010351.json` and `ghidra_exports/100102ea.json`: base
  exception copy construction and assignment behavior.
- `ghidra_exports/10010265.json`: `_Copy_str` obtains storage with `_malloc`,
  copies the message, and sets ownership byte at offset 8.
- `ghidra_exports/100102a5.json`: `_Tidy` releases owned storage through
  `_free` and clears the message/ownership fields.
- `ghidra_exports/100115b7.json` and `ghidra_exports/100116db.json`: allocator
  wrappers use the `HeapAlloc` and `HeapFree` imports bound by the harness.

## Reproducibility and integrity

- Original ASI SHA-256: `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`
- Candidate source SHA-256: `E87AC172D9974DE4CD2A865F1165D7B0D77AD07B9721E8CC43F9A69ECC0BED65`
- Candidate object SHA-256: `FC90C7C83512DF7539F3160171386CC683F33FD2D15833709328A7331117BF11`
- Harness source SHA-256: `7D05A9AA42C4B9DC8E683A4705CC8E3A79E3560DD1BAD8582D468AAE89C6339F`
- Harness executable SHA-256 (final 10-process rerun): `203362D365B1E23317B056D518CE7209E3A3EE0A7781E481615CD7A78D88DBB0`
- Runner: `scripts/test-100014a0-original-binary-differential.ps1`

The candidate source was not changed. The x86 harness compiled under VS 2022
with `/O1 /W4 /WX /MT /arch:IA32 /GS-` and ran against the pinned original.

## Remaining boundary

The candidate's unresolved base-copy helper is forwarded to the original
helper, so this is not a comparison of two independently reimplemented CRT
helper bodies. The mapping binds only the two allocator imports needed by this
path; it does not perform general PE import/relocation loading. Allocation
failure, malformed inputs, full production linking/section placement, and live
GTA behavior remain unverified. This single-function evidence does not certify
the rest of the 705-function set.
