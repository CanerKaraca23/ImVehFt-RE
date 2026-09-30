# `1001ba40` original-binary differential

Date: 2026-09-28. This isolated test directly executes the exact
`FUN_1001ba40` machine-code bytes extracted from the installed 2014
`ImVehFt.asi`, alongside a fresh compile of the current candidate function.
It does not modify the candidate source or installed plugin.

## Binary provenance and harness construction

- Original ASI SHA-256:
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
- Ghidra entry VA `0x1001ba40` maps to file offset `0x1ae40`. The 171 bytes
  through the terminal `RET` at `0x1001baea` are embedded in
  `tests/runtime_1001ba40_binary_differential.cpp`; an independent `pefile`
  extraction verified that all embedded bytes exactly match the original
  file range.
- The original instructions are copied into a fresh x86 process's executable
  page. Relative branches remain unchanged because the complete code span is
  relocated as a unit. The two absolute operands referring to
  `DAT_1003c414` are redirected to a private test page. The candidate object
  reads its own separately defined test global.
- Reproduction:
  `scripts/test-1001ba40-binary-differential.ps1`, run from a VS 2022 x86
  Developer PowerShell. With no `-OutputDirectory` argument it chooses a new
  timestamped path instead of overwriting prior test evidence. It compiles the
  harness and current candidate helper with
  `/std:c++20 /O2 /W4 /WX /MT`, links a PE32 executable, and executes it.

## Comparison and result

The original and candidate results matched for **12,000,264/12,000,264** cases
in the latest large run, across:

- 22 inputs including signed zero, half/tie values, neighbors of half,
  int32-boundary and overflow values, large finite values, subnormal, NaNs,
  and positive/negative infinity;
- three global modes (`0`, `1`, and `0x12345678`);
- all four x87 rounding-control settings; and
- 1,000,000 deterministic xorshift64* random 64-bit input patterns for each
  of the 12 mode/rounding-control combinations (12,000,000 random cases, in
  addition to the 264 directed cases). The earlier 4,096-pattern run matched
  49,416/49,416 before this larger run.

For every case the harness compared both halves of the return value
(`EDX:EAX`), x87 status word, x87 control word, and MXCSR. Three builds of the
initial harness matched all of those values. The updated harness also captures
and compares the FXSAVE abridged x87 tag word to detect differing live x87
stack occupancy. The directed and 4,096-pattern runs passed as recorded below.
The million-pattern harness was run twice (the build-script run and then the
same executable directly); both runs reported 12,000,264/12,000,264 matched:

- `build/abi-harness/1001ba40-original-binary-diff-20260928-v5/1001ba40-original-binary-differential.exe`,
  SHA-256 `1EED107A3FECEF71670000F6211906583B5201345087694D045386E31050C391`.
- `build/abi-harness/1001ba40-original-binary-diff-20260928-v6/1001ba40-original-binary-differential.exe`,
  SHA-256 `237EED3D06D9D3D976C9720907950F574E1892DF28275D706E00716F53B0CCBE`.
- `build/abi-harness/1001ba40-original-binary-diff-20260928-125250-593/1001ba40-original-binary-differential.exe`,
  SHA-256 `4F3671092E517C929B3B55CA1129EC7DC2BDD66D0BAE5F8C4460370050B075C7`.
- `build/abi-harness/1001ba40-original-binary-diff-20260928-125740-791/1001ba40-original-binary-differential.exe`,
  SHA-256 `74ADD92F357BF41B37851D78573A2D15AAAEAB2E469AF1C0FD6A3A8D9FE4DFF4`;
  rerun output: `49,416/49,416 matched; 0 mismatches`.
- `build/abi-harness/1001ba40-original-binary-diff-20260928-130438-660/1001ba40-original-binary-differential.exe`,
  SHA-256 `8970829713C1440AC152FC361A7E05A76FE857351E818B337FA412E63A18052E`;
  two executions each reported `12,000,264/12,000,264 matched; 0 mismatches`.
- Afterward, the updated reproduction script was also run with its default
  4,096-pattern setting:
  `build/abi-harness/1001ba40-original-binary-diff-20260928-130618-149/1001ba40-original-binary-differential.exe`,
  SHA-256 `DF107090A1EBD6BDDC6DB2981F6B5A0BFB3343BC114D6103C4DF78E9BF66F6EE`;
  result `49,416/49,416 matched; 0 mismatches`.

The latest test harness source SHA-256 is
`50E18C41A8C4C413C65DBA40CB926D218F2BAA8BEAB2FE71BBF9C51D04ADC0BA`; its
reproduction script SHA-256 is
`9944DAB0AC52075EFE15B9739C0CB1BA26362365B49AED0DC6C58AA307CE62ED`.
The candidate helper source SHA-256 is
`973DD0053E4680B0185F3C5695109B9DA0A328A7B5C5D31C97324FD8E7FBDBE4`.

## Scope limits

This is strong differential runtime evidence for this helper over the tested
directed and deterministic random inputs and FP modes. It compares x87 stack occupancy, not the contents of inactive
registers or every possible extended-precision payload. It is not a GTA
process/gameplay test, does not validate callers' argument setup in every
context, and does not prove the 705-function set equivalent. The helper's
`DAT_1003c414` state is controlled by the test; the harness does not reproduce
every possible process-level initialization path.

## Fresh rebuild and million-pattern rerun (2026-09-28 16:19 local)

Rebuilt the harness and candidate helper from the current checkout with MSVC
14.44 x86 `/O2 /W4 /WX /MT`, setting
`IVF_RANDOM_PATTERN_COUNT=1000000`. The result was **12,000,264/12,000,264
matched, zero mismatches**: 22 directed patterns plus one million deterministic
64-bit patterns under each of three controlled global modes and four x87
rounding modes. Compared state includes EDX:EAX, x87 status/control words,
MXCSR, and FXSAVE abridged x87 tag occupancy.

Current candidate SHA-256
`973DD0053E4680B0185F3C5695109B9DA0A328A7B5C5D31C97324FD8E7FBDBE4` matches
its manifest row. Harness source SHA-256 is
`50E18C41A8C4C413C65DBA40CB926D218F2BAA8BEAB2FE71BBF9C51D04ADC0BA`; fresh
executable SHA-256 is
`093751906BD5E958744F15700658F2737D16C3781E294F70FDDCBD43A98F651D` at
`build/abi-harness/1001ba40-original-binary-diff-20260928-161919-448/`.
This strengthens only this helper's bounded differential evidence; controlled
global state, other caller contexts, the other 703+ functions, and game/runtime
integration remain outside its proof scope.
