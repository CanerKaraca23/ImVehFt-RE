# `0x10003fb0` callback-body differential — 2026-09-29

## Ghidra contract

The hash-pinned Ghidra export identifies `FUN_10003fb0` as a two-argument
`__cdecl` function. Its assembly saves ESI/EDI, forwards `(arg1, 0x10003fe0,
arg2)` to the API at `0x7f1200`, then `(arg1, 0x10003fb0, arg2)` to the API at
`0x7f0dc0`, returns `arg1` in EAX, and restores the callee-saved registers.
The direct callers include `0x10003f80`, `0x10006790`, and `0x10006ad0`.

## Differential test

The test maps the pinned original ASI without startup initialization and links
candidate objects `10003f80.obj`, `10003fb0.obj`, and `10003fe0.obj` from the
fresh strict 705-object build. Both hard-coded API targets in the wrapper and
callback bodies are redirected to deterministic recorders. The callback body
is invoked using its actual `__cdecl(arg1,arg2)` contract, with fixed ESI/EDI
sentinels. Each of 512 cases compares API call count/order, callback identities,
both arguments, EAX, ESI/EDI preservation, and stack delta.

Result: **512/512 callback-body cases and 512/512 wrapper cases passed.** The
harness uses MSVC x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-`. Pinned ASI SHA-256:
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
Harness-source SHA-256: `1D24E7C6672BEDD623C2D60EEB0687EABA97C63E49E91844DBAB10C109B0A970`.
Executable SHA-256:
`26EB56A46A1AA169225037951E11B52793FB494F208803F7696708BD7C5CDFEA`.

Artifacts: `build/abi-harness/10003f80-and-10003fb0-differential-live-20260929g/`.
The previous harness source is preserved as
`tests/runtime_10003f80_callback_abi.cpp.pre-direct-10003fb0-differential-20260929.bak`;
additional iteration backups preserve later test-harness corrections.

## Limits

The tests replace GTA APIs with recorders. They prove this forwarding/ABI
contract under the tested values, not downstream GTA side effects, DllMain or
startup behavior, production PE layout/relocation, or gameplay. Candidate
production sources were not changed in this test iteration.
