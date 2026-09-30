# `10001010` vtable/destructor original-binary differential — 2026-09-29

Ten fresh PE32/x86 processes passed, with 128 original-vs-candidate paired
cases per process (1,280 pairs total), zero mismatches. Each of 64 seeds ran
both `param_1 == 0` and `param_1 == 1` paths. The test records the target's
vtable at the base-destructor call boundary, checks the return pointer and
post-destructor bytes, and verifies that the flagged self-delete path frees
each exact input pointer once with the expected pre-free object contents.

Ghidra basis: `ghidra_exports/10001010.json` shows the store of
`0x10022250` at `0x10001016`, the base-destructor call at `0x1000101c`, the
optional free branch at `0x10001021`/`0x10001027`, and return of `this`.
`1001031f.json` confirms the base destructor writes vtable `0x10022228` and
then tidies the message fields; `10010756.json` confirms the optional free
wrapper. In the test image, only the original's verified destructor call is
redirected in memory to a capture-and-forward shim; the shim records the
transient vtable and then runs the original helper. The linked candidate's
helper symbol uses that same shim. The candidate's relocatable vtable alias
is compared with its harness-resolved symbol address, not incorrectly equated
to the original image's fixed VA. Both paths finish with `0x10022228`.

The `param_1 == 1` object is allocated by `HeapAlloc(GetProcessHeap())`. The
test-only mapped-image `HeapFree` IAT slot and heap-handle global are bound to
the same process heap, and a shim snapshots the object before forwarding the
real `HeapFree`. Only the in-memory mapped image is modified; the original ASI
file remains unchanged.

## Pinned artifacts

- Original ASI SHA-256: `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`
- Candidate source SHA-256: `53DDEE3B7841FB2C70BDD331A84E9FAB8B3208675435A121E39C8042B59C2BB7`
- Candidate object SHA-256: `AA5FB7F60DE50E8CFF6BDA475908428029B15933DB524778CAF6D3809B7DDEF4`
- Harness source SHA-256: `45E9F032813FEA3E147A03732E6EE6F56EC22D00A4BA7010D3C584A7A241CBC3`
- Harness executable SHA-256: `4DE501BB8A8CD8E9AAF6EE44DDF2CBF476E9385CE4F269413B0AB02B4C20C99F`
- Reproduction: `scripts/test-10001010-vtable-original-binary-differential.ps1 -Repetitions 10`

The candidate source was not changed. The current exact source and object were
strict-compiled as part of the refreshed 705-TU run in
`audit/current-705-source-hash-refresh-and-rerun-2026-09-29.md`.

## Limits

This directly addresses the specific vtable-value blind spot demonstrated by
the ReAgent negative control, but does not make ReAgent an equivalence proof.
The harness redirects the one observed destructor call and binds a single
test-only allocator import; general PE imports/relocations, production
image-layout, all exception paths, and live GTA behavior remain unverified.
