# `0x10006ad0` query helper ABI correction — 2026-09-29

## Superseded ABI note

This initial correction captured the ECX receiver and stack selector, but
omitted the zeroed EDX argument visible at both Ghidra call sites. The current
candidate uses `__fastcall(receiver, nullptr, selector)` and is documented in
[`10006ad0-query-fastcall-differential-2026-09-30.md`](10006ad0-query-fastcall-differential-2026-09-30.md).
The remainder of this file records historical, superseded verification and
must not be treated as evidence for the current candidate source.

## Initial evidence and change

The pinned Ghidra listing shows both query call sites pass one byte on the
stack while explicitly setting `ECX = EDI + 0x5A0`:

- `0x10006b4b`: `LEA ECX,[EDI+0x5A0]`, then call `0x6c2230`;
- `0x10006b85`: `LEA ECX,[EDI+0x5A0]`, then call `0x6c2180`.

The candidate had typed both addresses as `char (__cdecl*)(uint8_t)` and called
them with only the byte argument. It now uses
`char (__thiscall*)(void*, uint8_t)` and passes the explicit receiver
`unaff_EDI + 0x5A0`. Its strict optimized COFF output correspondingly loads the
EDI-derived receiver into ECX, pushes the selector, calls the fixed address,
and does not emit caller-side argument cleanup, matching the observed
callee-cleaned thiscall boundary.

The pre-edit candidate source is preserved at
`src/functions/10006ad0.cpp.pre-ecx-thiscall-query-correction-20260929.bak`
(SHA-256 `BF5A04168E7AEC2311A6594970073C76F656114417D79874AEEE74EF579D33BA`).

## Verification and boundary

- Strict MSVC x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-`: **705/705 compiled**;
  `build/strict-xcode-nogs-o1-10006ad0-thiscall-final-20260929.json`.
- Independent ReAgent objective: **705 PASS / 0 FAIL / 0 UNKNOWN**;
  `audit/objective-independent-10006ad0-thiscall-final-2026-09-29.json`.
- ReAgent parity: **705 GREEN / 0 YELLOW / 0 RED**;
  `build/parity-10006ad0-thiscall-final-20260929.json`.
- Both 705-row source manifests were refreshed with pre-refresh backups.
- Corrected source SHA-256:
  `BEABD378B44198A234DAD38079948BB901EED0A2E9A0607E11B0CC6839BCE950`.
- Corrected COFF object SHA-256:
  `B35CC6AD50657A71ECAE194970092BB9FF6756407D636FD44CDED8E1EFA161EF`.

This is strong call-ABI evidence from Ghidra plus the generated object code,
not a mapped dynamic differential for `0x10006ad0`. Its full branch effects,
live GTA queries/registrations, surrounding caller state, initialization,
production linking/layout, and gameplay remain unverified. The aggregate
705-function gates are structural/build checks, not semantic proof.
