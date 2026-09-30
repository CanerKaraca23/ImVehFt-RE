# Targeted installer runtime harness

Date: 2026-09-28. This verifies the actual candidate object for
`FUN_10002210` against a private in-process image-section fixture initialized
from the installed GTA executable. It is not a real game run.

## Current result

The fresh MSVC 14.44 x86 harness executed
`build/recheck/strict-all-live-20260928-2/10002210.obj` and passed:

- 22/22 rel32 hook patches decode to the expected linked wrappers;
- all 3 function-pointer patch values match their intended candidate functions;
- the mode-dispatch callback was exercised 3 times;
- the candidate called the real Windows `VirtualProtect` API on the fixture.

Two fresh runs passed: `build/runtime-check/20260928-112829-788/result.json`
and `build/runtime-check/20260928-112957-031/result.json`, both exit code 0.
The second harness executable SHA-256 is
`93359B348373993796264A4DC33BDE2DD60ADEDED5E3E3D80A7601CB48D1B704`.
The source GTA executable was read-only input, SHA-256
`F01A00CE950FA40CA1ED59DF0E789848C6EDCF6405456274965885D0929343AC`.

The harness reserves a writable `.gta` section in its own PE image at the
original 32-bit address range, seeds the 15 touched pages by mapping the
corresponding raw sections from the installed GTA PE, then executes the actual
installer object. It neither loads GTA nor writes to the game's executable.
The earlier fixed-address `VirtualAlloc` approach failed because Windows had
already reserved that range in the harness process; the linked image section
removed that test-fixture collision.

## Interpreting original opcode bytes

The harness table's `patchedOpcode` is the value the installer is supposed to
write, not an expected pre-patch byte. The installed executable has other
bytes at several sites by design (for example, `0x68` at `0x005D5BC7` is
replaced by the configured `E9` jump). An intermediate precondition check
incorrectly compared these before/after values and stopped. That check was
removed; the current test verifies post-patch opcode and rel32 targets instead.
The intermediate result is not evidence of an unsupported game version.

## Limits

This is targeted execution of one installer object, not execution of the GTA
program, its loader, or the reconstructed ASI. Selected ImVehFt callbacks are
stubs, and other plugin initialization and callback semantics remain outside
this test. The synthetic fixture does not prove full game behavior or the
equivalence of all 705 function bodies. The original `.asi` and GTA executable
were not modified.
