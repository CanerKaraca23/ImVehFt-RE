# `0x10006ad0` query ABI and mapped differential — 2026-09-30

## Correction

The first ABI correction captured `ECX = EDI + 0x5A0` and the stack selector,
but did not represent the zeroed `EDX` observed immediately before both calls
in the pinned Ghidra assembly (`0x10006b51..0x10006b58` and
`0x10006b85..0x10006b92`). The candidate now types both query targets as
`__fastcall(receiver, nullptr, selector)`. Fresh optimized COFF emits the
receiver in ECX, zero in EDX, the selector on the stack, and the call; both
sites match the observed register/stack shape. The older
`10006ad0-query-thiscall-abi-correction-2026-09-29.md` is superseded on this
point.

The candidate source before this correction is preserved at
`src/functions/10006ad0.cpp.pre-edx-fastcall-abi-correction-20260930.bak`.
Current source SHA-256:
`6D9B953F5AACE52525C87B115F57E69526CFEF5141C2815F0EDA932B13F03E08`.
Candidate COFF SHA-256:
`5A658FE8A2D2F4A2CAFF6FA5F3058C74B32847AC985E9941A252887B7D73D9AB`.

## Verification

- Strict MSVC x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-`: **705/705 compiled**;
  report `build/strict-xcode-nogs-o1-10006ad0-fastcall-edx-20260930.json`.
- Independent ReAgent objective: **705 PASS / 0 FAIL / 0 UNKNOWN**;
  report `audit/objective-independent-10006ad0-fastcall-edx-2026-09-30.json`.
- ReAgent parity: **705 GREEN / 0 YELLOW / 0 RED**;
  report `build/parity-10006ad0-fastcall-edx-20260930.json`.
- Both 705-row source manifests match current source bytes: **1,410/1,410**;
  backup suffix `.pre-edx-fastcall-abi-correction-20260930.bak`.
- Mapped original-ASi versus candidate x86 differential: **5,791 paired
  executions** across the existing state-2/state-3 arithmetic and registration
  coverage, the `0x10003f80` wrapper paths, the `0x100069e0` caller path, and
  12 `0x10006ad0` combinations (vehicle status 0/1/0xB/2 × query result 0/1/2).
  The `0x10006ad0` tests compare four eligible file types, query receiver and
  selector, query result, registration API sequence/context/
  callbacks/mode, stack balance, and preserved registers. Harness source SHA:
  `57D5D2491BC37EF6C6E77A02E16DDD387F01222F9A570F279A9B712AA73BF9CD`;
  reproducible-run executable SHA:
  `FADCEEB78D92D87903493AE59AC9B0A434566CFFEC7A692364D9F08AF825CD39`.
  Pinned original ASI SHA-256:
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

The zero-valued EDX register argument is verified by the pinned Ghidra assembly
and candidate COFF disassembly (`XOR EDX,EDX` at both lookup call sites); the
runtime query recorder compares ECX receiver, stack selector, return value,
and resulting registration calls, but does not independently record EDX.

## Limits

The query and registration APIs are deterministic recorders, and matrix API
recording is used for the earlier mapped paths. This proves selected mapped
control-flow/ABI equivalence, not every caller or behavior. Production ASI
linking/layout, real GTA side effects, initialization, and in-game behavior
remain unverified; no original project build files/SDK have been found in the
candidate repository.
