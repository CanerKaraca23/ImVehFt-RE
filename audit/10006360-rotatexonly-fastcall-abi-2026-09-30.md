# `0x10006360` rotate-X call ABI correction — 2026-09-30

## Finding

Ghidra's pinned listing at `ghidra_exports/10006360.json` shows seven calls to
the absolute target `0x0059b020`. At these sites the original establishes the
matrix receiver in `ECX`, clears `EDX`, places the angle in the stack slot,
and makes an indirect call. For example, `0x10006407..0x1000640f` stores the
angle, sets `EDX=0`, computes `ECX=ESI+0x10`, then calls `EAX`; later sites use
the equivalent `EBX`/`ESI` receiver already pointing at the matrix subobject.
The prior candidate declared the function as `__cdecl(float)` and its compiled
object did not set either register, so it could not preserve the original
call contract.

The candidate now declares the target as `__fastcall(receiver, zero, angle)`
and passes the destination matrix subobject (`destination + 0x10`), zero, and
the narrowed angle. Previous source is preserved at
`src/functions/10006360.cpp.pre-59b020-fastcall-abi-20260930.bak` (SHA-256
`BF662C620E338DDE76A64AD7396CF854EBFA800D925A5963C5D41FCCB09EE041`).

## Object-code evidence

Fresh MSVC x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-` object disassembly shows the
corresponding sequence at every one of the candidate's seven `0x59b020` calls:
`EDX=0`, `ECX=destination+0x10`, float stored in `[ESP]`, indirect `CALL EAX`.
The targeted object SHA-256 is
`2362E9F2DF4D1940D098F8F5845F75001335CDDEA33E4926FF1C399DB8EC0F77`.
This verifies the call-site ABI setup against the Ghidra listing; it does not
verify the callee's internal behavior or the entire function's runtime effects.

## Refreshed broad gates

- Strict MSVC x86 compile: **705/705 passed**, 0 failed;
  `build/strict-xcode-nogs-o1-10006360-fastcall-full-20260930.json`.
- ReAgent objective verifier: **705 PASS / 0 FAIL / 0 UNKNOWN**;
  `audit/objective-independent-10006360-fastcall-2026-09-30.json`.
- ReAgent parity: **705 GREEN / 0 YELLOW / 0 RED**;
  `build/parity-10006360-fastcall-20260930.json`.
- Both 705-row source manifests refreshed and backed up with suffix
  `.pre-10006360-fastcall-abi-20260930.bak`.

The latter three are compile/structural gates, not semantic equivalence proof.
The targeted helper bodies now have additional mapped runtime evidence below;
production ASI layout/link, full GTA startup, other untested helper paths, and
in-game behavior remain unverified.

## Mapped caller differential

A Windows x86 harness maps the pinned ASI at `0x10000000` and compares the
original function with the compiled candidate across **1,059 cases**:
all 64 paired source-null masks and four target-null masks for statuses 0, 1,
2, and 0xB; the special 9/10 paths; and unsupported-state early returns.
The test executes the original and candidate `0x10010120` wrappers plus the
real GTA code for `0x53cc70`, `0x59b020`, and `0x7f18b0`. The game executable is
hash-pinned at `F01A00CE950FA40CA1ED59DF0E789848C6EDCF6405456274965885D0929343AC`.
Its relocations are stripped, so the harness maps its image at an available
address and rebases only the audited helper data operands: `0x53cc70` has six
absolute-data targets with instruction-use counts 7/2/4/2/2/1; `0x7f18b0`
has one each for `0xc979bc` and `0xc97b24`; `0x59b020` has no absolute-data
references. Relative branches remain unchanged. The matrix helper's two
flagged copy branches were both executed (1,584 and 1,536 recorded invocations
across original/candidate runs); its indirect fallback branch was deliberately
not taken.

All **1,059/1,059** cases matched helper call order/arguments and the full
0x100-byte target objects. The original and candidate `0x10010120` wrappers
call the actual mapped angle helper; the actual x87 sine/cosine rotate helper
and both matrix-helper copy branches execute. `0x10009360` remains a controlled
pool-manager fixture. The `ECX=destination+0x10`, `EDX=0` rotate call contract
is additionally verified in the candidate's strict object disassembly against
Ghidra. Harness source SHA-256
`E19A2BA918D88858D4240CB3FF4EEBD40EDA07ACB4ED6D0A76059D0FA8EBD7F4`;
final executable SHA-256
`91B24FCFB21A3317394DA6332B762BCE34150E5765D580E8373F8F33A9BCE94A`.
Runner: `scripts/test-10006360-original-binary-differential.ps1`; captured
executable: `build/abi-harness/10006360-real-gta-math-differential-final-20260930/runtime_10006360_original_binary_differential.exe`.

This is strong selected-function/helper differential evidence, not production
ASI validation: the plugin pool manager is synthetic, the game process is not
started, and the matrix helper's indirect fallback path plus actual gameplay
effects remain untested.
