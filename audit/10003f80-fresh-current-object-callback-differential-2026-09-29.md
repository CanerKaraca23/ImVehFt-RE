# `0x10003f80` fresh current-object callback differential — 2026-09-29

## Setup and pinned input

The test maps the pinned original `ImVehFt.asi` without running its startup
code and links the current candidate objects for `0x10003f80`, `0x10003fb0`,
and `0x10003fe0` from the fresh whole-set build
`build/recheck/strict-xcode-nogs-o1-live-20260929b/`. The pinned ASI SHA-256
is `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

The harness replaces the two hard-coded GTA callback destinations with
recorders in both original and candidate bodies, then compares the two
invocations. It checks call count and order, callback identity, context and
mode arguments, EAX result, ESI/EDI preservation, and ESP delta for 512
deterministic input cases. Candidate callback identities are compared against
their respective original/candidate entry addresses.

## Result

**512/512 differential cases passed.** The harness was compiled with MSVC x86
`/O1 /W4 /WX /MT /arch:IA32 /GS-` and linked using the three object files from
the fresh 705-object compile. Harness source SHA-256:
`53942FF2A3E0D2F7B2F5B8263BDF03C377C6135370F660E93AF4197958D39120`.
Executable SHA-256:
`4A93407073F4535C36E6A0215B6297A92BE076101230F91DF3577A3D333BC17B`.

Artifacts are in `build/abi-harness/10003f80-callback-abi-live-20260929b/`.

## Limits

This compares the callback-dispatch wrapper under test recorders, not live GTA
API behavior. It does not validate either callback's downstream game effects,
startup/initialization, production image placement, or in-game behavior. The
result is focused ABI/control-flow evidence, not proof for all 705 functions.
