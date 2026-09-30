# Ghidra RET cleanup ABI sweep — 2026-09-29

## Scope and method

Compared each current Ghidra export's explicit `RET` cleanup immediate with
the selected address-entry `.xcode` COFF section from the fresh strict x86
`/O1 /W4 /WX /MT /arch:IA32 /GS-` build. COFF entry selection reused the
repository's current address/name/signature selector. This is a diagnostic
instruction scan, not a control-flow proof: candidates with tail-jump entries,
multiple sections, or indirect exits need separate inspection. The pinned
original image was not modified.

The first sweep of the pre-fix objects found three cleanup mismatches among
665 functions with at least one direct `RET` on both sides. Manual Ghidra
caller/assembly review established two real missing stack-argument cases and
one startup-wrapper ABI mismatch.

## Corrections

- `10001db0`: Ghidra ends both exits with `RET 0x0c`; its startup caller pushes
  three arguments. Candidate declaration and both caller sites now carry all
  three arguments. The final object emits `RET 0x0c`.
- `10009790`: Ghidra ends with `RET 0x14`; its inferred fastcall ABI includes
  five stack arguments in addition to ECX/EDX inputs, though those arguments
  are unused in the body. The candidate signature now models them, and the
  final object emits `RET 0x14`.
- `100110bd`: Ghidra's entry has a plain `RET`, leaving one caller-pushed
  argument for `100111b3` to pop. The candidate now exposes the original
  three-argument fastcall entry as a naked tail-jump to a C++ implementation
  with only the two register parameters; that implementation reads the
  preserved third argument at `[EBP+8]`. Fresh disassembly shows the entry
  `JMP` to the implementation and the implementation's final `RET` (no
  immediate). This matches the observed stack-cleanup convention at the
  machine-code level; a focused original-binary runtime differential for this
  startup path remains outstanding.

Backups for the changed sources are:

- `src/functions/10001db0.cpp.pre-ret12-abi-audit-20260929.bak`
- `src/functions/10009790.cpp.pre-ret20-abi-audit-20260929.bak`
- `src/functions/100110bd.cpp.pre-ret12-abi-audit-20260929.bak`
- `src/functions/100110bd.cpp.pre-naked-entry-unused-warning-20260929.bak`

The two 705-row source-hash manifests were refreshed with backups before the
final build.

## Fresh verification

- Strict MSVC 2022 x86 compile: **705/705**, report
  `build/strict-xcode-nogs-o1-ret-cleanup-final2-20260929.json`.
- RET-immediate scan: among 664 entries with a direct RET on both sides,
  **664/664 cleanup sets match**. Eight Ghidra-only and five candidate-only
  direct-RET cases remain outside this simple set comparison; no equivalence
  claim is made for them. The `100110bd` JMP-entry/RET-implementation pair was
  inspected separately.
- Independent objective check: **704 PASS / 1 FAIL / 0 UNKNOWN**. The sole
  failure is `100110bd`: the analyzer treats the address entry as a tiny stub
  and does not follow the tail-jump into its real implementation.
- ReAgent 0.4.0 parity: **704 GREEN / 0 YELLOW / 1 RED**, same `100110bd`
  wrapper/implementation split. This red is retained rather than suppressed;
  a focused runtime differential is now recorded below, but stronger analyzer
  support and broader startup-path validation remain outstanding.
- These results do not validate the complete 705-function semantics,
  production PE layout/relocations, ASI installation, or GTA gameplay.

## Original-binary runtime follow-up for `100110bd`

A focused x86 harness now maps the hash-pinned original image at its preferred
base and compares the original `0x100110bd` routine and `0x100111b3` entry with
their final candidate objects on the no-work process-detach branch. It forces
`DAT_100399f0 == 0`, passes `EDX == 0`, and stubs only the candidate-side SEH
prolog/epilog and unreachable startup helpers. Across **five fresh processes
x 256 cases per path**, the direct startup calls and full entry-to-startup
pairs each had zero return-value or ESP-delta mismatches (1,280 pairs per
path). The direct startup call left the same **-4 ESP delta** on both images,
preserving its stack argument; the complete `100111b3` entry left delta zero
on both images after the entry wrapper consumed that argument. An additional
matrix spans four DllMain reasons, the module-initialization flag, callback
presence, and callback/CRT/plugin return combinations: **128 branch
configurations per process x five fresh processes**, with exact call-order,
argument, result, and ESP-delta matches.

Evidence:

- Original image SHA-256:
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
- Candidate object SHA-256:
  `4527EE4ACE5C66C85F144DEB406A0D184F8BD4632D195D59F2C1B18FEED0A8EA`.
- Candidate `100111b3` entry object SHA-256:
  `8ACD7828EE97838AB647C18162A648B938A327EFB1247098E2EFD933D01500C0`.
- Harness source:
  `tests/runtime_100110bd_stack_cleanup_differential.cpp`, SHA-256
  `F1F217B49B0ED692F77ECC2F9786E4297F73472A6F3CD7E6FA1D143D5759EF4B`.
- Harness executable SHA-256:
  `73381FD4EA5BA7CEC90CF2D9E3D1727AC58EB9DA1EB1903C85D232C8CC2BFABD`.
- Runner:
  `scripts/test-100110bd-original-binary-stack-cleanup.ps1`.

An earlier harness version declared its naked caller-cleanup wrapper as
`__cdecl` despite emitting `RET 0x10`; its first measurements were invalid and
are superseded. The corrected wrapper is `__stdcall`. As a negative control,
the prior direct-three-argument candidate object (SHA-256
`8D0B4F7E2457CCE408C37F00755FB68AAE06FAF87517676117A3A5182EFA44F5`) left
ESP delta `0` while the original left `-4`; it does not match this branch.

These differentials cover the recorded no-work path and the 128 controlled
branch configurations with test replacements for the CRT/plugin helper
calls. They do not validate the helpers' real side effects, actual CRT
initialization, thread notifications under the live host, or exception/
unwind behavior. The objective and parity red for `100110bd` is retained
because both structural engines do not follow the tiny entry's tail jump
into the implementation; no broad green claim is made from these focused
tests.
