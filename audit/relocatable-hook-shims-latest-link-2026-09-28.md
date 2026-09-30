# Relocatable hook-shim integration into the full diagnostic link

Date: 2026-09-28. Target ImVehFt image SHA-256:
`409F0DF7AE579841DB05C3EC6AD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Fresh shim-object evidence

The earlier integration blocker documented 12 bounded Ghidra hook bodies and
139 image-address operands. Re-generated the MASM object using the current
705-object strict build, including the `10006be0` ABI bridge revision. The
independent verifier passes:

`PASS shims=12 instruction_stream_bytes=1449 verified_nonfixup_bytes=893 relocations=139 DIR32=128 REL32=11`.

The verified generation outputs are:

- `build/recheck/relocatable-hook-shims-abi-bridge-20260928.asm`
- `build/recheck/relocatable-hook-shims-abi-bridge-20260928.obj`
- `audit/relocatable-hook-shims-abi-bridge-2026-09-28.json`

## Full diagnostic-link integration

Created a new response file from the current full diagnostic-link recipe. It
removes the two raw supplemental hook-body objects and includes the single
relocatable shim object instead. The 705 candidate objects and support objects
then link successfully with no unresolved symbol or relocation diagnostics.
The link map resolves all 12 `_ImVehFtHook_*` labels to the new relocatable
object; their linked addresses are in `0x10024E10..0x1002518E`. This
demonstrates object-level integration of the 139 fixups with the current
candidate/data-provider link inputs.

Output:

- `build/link-probe/strict-704-historical-sdk/ImVehFt-relocatable-hook-shims-diagnostic-not-ASI.dll`
- SHA-256: `7C80DCBF062A91D3E1C00F49D700E70F5D87300BA7ED69E52B3F09415C901978`
- PE32 image base `0x10000000`, image size `0xC4000`.

## Remaining blocker

This is still only a diagnostic DLL. The map places candidate `FUN_100076d0`
at `0x10008D20` rather than original VA `0x100076D0`; the image size also
extends far beyond the original ASI's `0x43000` image. Other candidate,
installer, CRT, import, and startup layout requirements are not proven by
successful symbol resolution. The link must not be installed or loaded. No
production `.asi` or in-game validation is claimed.
