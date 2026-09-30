# `0x100074d0` mapped global-state differential — 2026-09-30

## Finding and correction

The first full mapped caller run caught an output mismatch after the third
lookup returned nonzero. Ghidra stores `2` to byte `0x1003aee1` (the second
byte of `DAT_1003aee0`); the candidate only updated that dword's high byte.
For a controlled case, the original output was
`DAT_1003aee0=0x02220245`, while the candidate left byte 1 as `0x33`
(`0x02223345`). The candidate now aliases `DAT_1003aee0+1` and writes `2` on
that branch. The pre-fix source is preserved at
`src/functions/100074d0.cpp.pre-aee1-query2-global-differential-20260930.bak`
(SHA-256 `5519D3428353E6A3864042057033B8EEF1520D3516DE962B7C7CCD8794D93E31`).

## Dynamic evidence

The x86 harness maps the pinned original ASI at its preferred base and compares
the mapped `0x100074d0` against the candidate across **24 cases**:

- statuses 0, 1, 2, and 0xB;
- vehicle flag bytes 0x00, 0x05, and 0x0F;
- all-false and mixed lookup-result sets.

It compares lookup receiver/EDX/selector/result, global output bytes/dwords,
x87 float presented to the hash helper, integer register inputs, downstream
call order/arguments, return value, stack balance, and preserved registers.
All **24/24** cases pass. The same executable also reruns the mapped
`0x10006ad0` checks (12/12); aggregate selected-path coverage is **5,815
differential cases**. Current harness source SHA-256:
`6F3A7439ADBF5B8CE903150635BEDAF863B0EEB6C014E038741E2DFD82AA2A90`;
final executable SHA-256:
`4BD25AE7C195B6B9F4496528E6BD78837422F64EAC2E50B1153B224BDEBC9488`.
Pinned input ASI SHA-256:
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

The caller's downstream helper bodies and external query/hash behavior are
deterministic recorders in this harness; this is not validation of those
helpers' internal logic or live GTA effects.

## Current full-set checks

- Strict MSVC x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-`: **705/705 compiled**;
  `build/strict-xcode-nogs-o1-100074d0-aee1-global-20260930.json`.
- Independent objective: **705 PASS / 0 FAIL / 0 UNKNOWN**;
  `audit/objective-independent-100074d0-aee1-global-2026-09-30.json`.
- ReAgent parity: **705 GREEN / 0 YELLOW / 0 RED**;
  `build/parity-100074d0-aee1-global-20260930.json`.
- Both source manifests independently checked: **1,410/1,410 rows match**.
- Current candidate source SHA-256:
  `5E26411FC496E88765C73B9933AB64D7AC0FFFF354997CC49D70D465784C0DFE`.
- Current candidate object SHA-256:
  `18CBD495816C21BBA88102C799DAB39860CDD215CC240ED23B5E822D00DA5E71`.

This is selected mapped caller coverage, not all-caller proof. Production ASI
link/layout, startup/relocations, true downstream helper interactions, live
GTA side effects, and gameplay remain unverified.
