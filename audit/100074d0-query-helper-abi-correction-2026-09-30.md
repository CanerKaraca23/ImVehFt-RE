# `0x100074d0` query-helper ABI correction — 2026-09-30

This report describes the earlier query-call correction before the later
implicit x87 `ST(0)` call-input correction. Current source hashes and full-set
gate results are recorded in
[`100074d0-x87-st0-call-correction-2026-09-30.md`](100074d0-x87-st0-call-correction-2026-09-30.md).

## Evidence and change

The Ghidra assembly for `0x100074d0` makes four calls to `0x6c2130`. At each
site it loads `ECX = param_1 + 0x5A0`, clears `EDX`, pushes selector 1/0/2/3,
then calls the helper. There is no caller-side `ADD ESP,4`; the callee consumes
the stack selector. The previous candidate inline assembly only pushed the
selector and then added four to ESP, omitting both register inputs and using
the wrong cleanup side.

All four candidate sites now set ECX and EDX exactly as Ghidra shows, push the
same selector, call `0x6c2130`, retain AL and the resulting EDX, and do not
clean the selector in the caller. Fresh strict optimized COFF disassembly
confirms the sequence at all four sites.

The previous source is preserved at
`src/functions/100074d0.cpp.pre-6c2130-fastcall-abi-correction-20260930.bak`
(SHA-256 `CBB83EE5699E73388A4A40F9B9A1F56A62D119FBC043BC8AAFCD206D48F344D5`).
Current source SHA-256:
`49B15F2C099EA0810657A5A10645F8ABDD07BCED3C21AD0EE2B22A71BD4C8645`.
Candidate COFF SHA-256:
`69FA84F5E227BA2A22FC4461243A3B499A2B13AE28B5D1CDD4F24761226E534D`.

## Verification

- Strict MSVC x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-`: **705/705 compiled**;
  `build/strict-xcode-nogs-o1-100074d0-fastcall-edx-20260930.json`.
- Independent ReAgent objective: **705 PASS / 0 FAIL / 0 UNKNOWN**;
  `audit/objective-independent-100074d0-fastcall-edx-2026-09-30.json`.
- ReAgent parity: **705 GREEN / 0 YELLOW / 0 RED**;
  `build/parity-100074d0-fastcall-edx-20260930.json`.
- Source manifests refreshed and independently checked: **1,410/1,410 rows
  match** current source bytes; backup suffix
  `.pre-100074d0-6c2130-fastcall-20260930.bak`.

This correction has static Ghidra-to-object-code ABI evidence, not a dynamic
original-vs-candidate execution of the full `0x100074d0` caller. Its global
state effects, all downstream helper interactions, production ASI
link/layout, and in-game behavior remain unverified. The separate mapped
`0x10006ad0` helper differential is documented in
[`10006ad0-query-fastcall-differential-2026-09-30.md`](10006ad0-query-fastcall-differential-2026-09-30.md).
