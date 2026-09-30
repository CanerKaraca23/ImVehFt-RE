# `10003f80` callback registration ABI correction — 2026-09-29

## Evidence and correction

The Ghidra disassembly at `ghidra_exports/10003f80.json` shows the entry
receives its context and mode through `ESI` and `EDI`. It calls `0x7f1200`
with `(ESI, 0x10003fe0, EDI)`, then `0x7f0dc0` with
`(ESI, 0x10003fb0, EDI)`, caller-cleans `0x18` bytes, returns `ESI` in
`EAX`, and uses plain `RET`. Its callers in `10006790.json` load `ESI` and
`EDI` immediately before the call.

The previous C++ body invoked both GTA APIs with no arguments. It therefore
did not register either candidate callback or preserve the observed stack and
return behavior. The source is now a naked x86 bridge spelling the observed
instruction sequence. Callback addresses use `OFFSET FUN_...` relocations,
not fixed ImVehFt preferred-base addresses.

## Verification

- MSVC 2022 x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-` compilation of this TU
  succeeds. Its COFF body is 34 bytes and follows the Ghidra instruction
  sequence; its relocations are `DIR32` references to `_FUN_10003fe0` and
  `_FUN_10003fb0`.
- Fresh full-set strict compile after the change: **705/705**; report
  `build/strict-xcode-nogs-o1-10003f80-fix-20260929.json`.
- Fresh source manifest refresh: **705 rows, zero hash mismatches**; backups
  use suffix `.pre-10003f80-callback-abi-20260929.bak`.
- Fresh ReAgent objective: **704 PASS / 1 FAIL / 0 UNKNOWN**. The remaining
  structural failure is `100110bd`, whose small tail-jump entry is not followed
  by the analyzer. ReAgent parity: **704 GREEN / 0 YELLOW / 1 RED**, same
  address. These are structural gates, not behavior equivalence proofs.

No original-vs-candidate runtime differential has yet been run for
`10003f80` against the live GTA process. A focused mapped-original x86
differential was subsequently added at
`tests/runtime_10003f80_callback_abi.cpp`, run by
`scripts/test-10003f80-callback-abi.ps1`. It maps the original ASI at its
preferred base after the runner verifies SHA-256
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`, then
redirects the two observed GTA API calls in the test image and candidate
object to recording stubs. Across five fresh x86 processes x 512 cases
(2,560 pairs), callback ordering/identity, context and mode arguments, EAX,
ESI/EDI preservation, and ESP delta matched exactly. Harness SHA-256 is
`53942FF2A3E0D2F7B2F5B8263BDF03C377C6135370F660E93AF4197958D39120`; the
tested executable SHA-256 is
`DA9FD2375CE2AA9F00B414DBADBED4AEFD4AB44268F20C11D388A5581A1CB054`.

The stubs do not reproduce GTA's real API side effects. This focused result
does not prove complete `10003f80` integration under the game, nor production
ASI layout/loading or whole-set semantic equivalence.

## Additional current-source verification (2026-09-29)

The current final strict object was independently rechecked after the later
`10011724` source edit. `scripts/audit-entry-inplace-bytes.py` resolves both
callback COFF `DIR32` relocations to their Ghidra-mapped original VAs and
compares all 34 bytes against the pinned ASI. The result is byte-identical:
`audit/10003f80-inplace-byte-reconstruction-2026-09-29.json`.

The controlled ABI differential was also rerun against the same current 705
object directory: 512 reference/candidate calls matched callback order and
identity, context/mode arguments, EAX, ESI/EDI preservation, and ESP delta.
Harness SHA-256 remains
`53942FF2A3E0D2F7B2F5B8263BDF03C377C6135370F660E93AF4197958D39120`; this
fresh executable SHA-256 is
`1DB59ECB455472850D810CF7E912DECD3EFEFFCBCE393BF7074FF4840104BE6D`.
The API targets remain recorders, so this is still not a live GTA side-effect
or whole-plugin test.
