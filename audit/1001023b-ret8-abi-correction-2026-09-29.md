# `1001023b` stack-cleanup ABI correction — 2026-09-29

## Defect found and corrected

The prior candidate declared only one explicit stack argument. Its compiled
object ended with `ret 4`, while the original Ghidra instruction at
`0x10010255` is `RET 8`. The caller at `0x10010893` confirms two stack words:
it pushes `1`, then the pointer to the message DWORD, sets ECX to
`DAT_100399e0`, and calls `0x1001023b`. The target reads the first stack word
as a pointer, ignores the second, and still removes both words. Ghidra's
decompiler signature omits that unused cleanup argument; the assembly and
caller settle the ABI.

Before editing, the candidate was copied to
`src/functions/1001023b.cpp.pre-ret8-abi-fix-20260929.bak`. The candidate now
declares an unused second `uint32_t` stack parameter. The address-map signature
records that inferred argument; the original Ghidra export was not modified.
The newly compiled object ends with `C2 08 00` (`ret 8`) and keeps the
relocatable exception-vtable alias and field writes.

## Focused differential

The corrected object from the subsequent 705-TU strict build was executed
against the original function in a preferred-base mapping. Ten fresh x86
processes passed, each with 128 cases (1,280 paired calls total), with zero
mismatches. A naked ABI wrapper called both versions with ECX=`this`, a
pointer argument, and a varied second DWORD; it measured ESP around the call.
Both versions had zero residual stack delta, wrote their expected vtable
address and payload DWORD, zeroed only byte `this+8`, and preserved the three
adjacent bytes. The candidate's relocatable alias is compared to the
harness-resolved alias symbol; it is not compared incorrectly to the original
fixed image VA.

- Original ASI SHA-256:
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`
- Candidate source SHA-256:
  `879A941C3ECD47BC474AD4D87BB79F57EC7421C1F055320C608E9AC54CB6F63B`
- Candidate object from full strict build:
  `build/recheck/strict-xcode-nogs-o1-after-1001023b-ret8-20260929/1001023b.obj`
- Candidate object SHA-256:
  `4E73FD38C797B7627E5D9F380D3F7D1DF8A652D99A11F55C1055E1D88B7073BA`
- Harness source SHA-256:
  `23BA4247EAD06A6BB80BAB79A9C8A33BC3A596AE536587C31EB0AE284A598F08`
- Harness executable SHA-256:
  `932708E875EFC7146B86BDBB746390A9DAF67F223F28136F6F16A801995384F0`
- Runner: `scripts/test-1001023b-original-binary-differential.ps1`

## Current full-set checks

After the source and both manifests were updated (backups ending
`.pre-1001023b-ret8-abi-fix-20260929.bak`), current-source verification reports:

- Strict MSVC 2022 x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-`: 705/705;
  `build/strict-xcode-nogs-o1-after-1001023b-ret8-20260929.json`.
- Independent ReAgent objective: 705 PASS / 0 FAIL / 0 UNKNOWN;
  `audit/objective-independent-final-current-2026-09-29.json`.
- ReAgent 0.4.0 parity: 705 GREEN / 0 YELLOW / 0 RED;
  `build/parity-final-current-20260929.json`.
- Parity adjudication: 13 scoped call-count-only checks retained, with the
  `100076d0` callback/re-entry risk still explicit.
- Independent Ghidra-vs-COFF call-count report: 13/13 scoped entries processed,
  zero audit errors in
  `audit/manual-parity-call-counts-after-1001023b-ret8-2026-09-29.json`.
- Both 705-row source manifests match all current source hashes (zero
  mismatches).

The objective and parity gates remain structural. The call-count audit has
explicit scoped waivers and is not semantic proof.

## Remaining boundary

This closes a specific candidate ABI mismatch, not the full 705-function
semantic audit. General production PE import/relocation and image placement,
full plugin startup/installer integration, original project/build inputs, and
live GTA behavior remain unverified.
