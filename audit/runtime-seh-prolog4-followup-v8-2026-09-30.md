# `__SEH_prolog4` runtime follow-up after experimental v8

## Candidate outcomes

- v7 (`041B0CD18AFF3F7872AA4BC8EA8D1BBA96181B98C8D231D08FC9BBDAED74E320`) crashed in `imvehft.asi` at offset `0x4BE6A` (`0xC0000005`).
- A first launch attempt after v8 staging accidentally loaded the preserved v7 `.asi` copy from the GTA clone root. WER identified `ImVehFt-candidate-v7-known-crash.asi`; this attempt is explicitly excluded as v8 evidence.
- The next launch had no `.asi` backup inside the game directory. ModLoader's log ended with installation of `modloader\my scripts\imvehft-re-test\imvehft.asi`, whose SHA-256 was v8 `73A9A04DDEA5C38B092EB7D22C2932836F80505A28738ABA280EDD5C825C9CCC`. WER then identified `imvehft.asi`, exception `0xC0000005`, module offset `0x4BE6A`. So the actual v8 run reproduced the crash.

## What the evidence changes

The v8 patch changed `_Type_info_dtor` at RVA `0x13AD2` and its HIGHLOW field site. It did not touch the candidate's startup entry function, so its repeated crash demonstrates that `_Type_info_dtor` was not a sufficient explanation for this startup failure.

The candidate entrypoint's original PE startup call chain reaches `___DllMainCRTStartup` (`0x100110BD`) before application/plugin behavior. Ghidra's `ghidra_exports/100110bd.json` says its first instructions push frame size `0x0C`, then scope table `0x100282A8`, then call `__SEH_prolog4` at `0x10012E20`. The old source called that helper with no arguments and compiled a compiler-generated prologue first. I replaced it with naked x86 assembly following the Ghidra body and added a relocatable image alias for scope table `0x100282A8`. The fresh strict object starts `push 0Ch; push offset _IVF_RELOC_TARGET_100282A8; call ___SEH_prolog4`, then follows the expected register/frame setup. Full strict compile, objective audit, and ReAgent parity were rerun after this edit: 705/705, 705 PASS, and 705 GREEN. The fix is not yet in an emitted PE or runtime-tested candidate.

Ghidra's `10012e20.json` confirms the helper loads its second formal parameter from `[esp+0x10]` after its two initial pushes, then executes `sub esp,eax`. The fault immediately after that subtraction is compatible with a bad/missing frame-size argument. WER identifies the helper offset but does not identify the caller; no usable call stack has been extracted from the crash dump.

The new COFF/Ghidra audit finds 35 direct helper call instructions across 35 caller functions. Twelve Ghidra callsites have no corresponding helper-call relocation in their current COFF bodies; among all 35, only 12 currently show the expected frame-size push. The DllMain and CRT_INIT startup callers have since been corrected at source/object level, as has the `_Type_info_dtor` push order; the other 32 require individual audit before full candidate regeneration. Full counts and limitations are in [`seh-prolog4-source-object-callsite-audit-2026-09-30.md`](seh-prolog4-source-object-callsite-audit-2026-09-30.md). The v8 plugin was moved out of the test clone after the failed test; its candidate binary copy is kept under repository build artifacts, outside the game directory.

## v8 static gates

- v8 targeted patch report: `audit/emitted-candidate-705-static-20260930-v8-seh-fix.json`.
- PE rebase probe: `audit/candidate-rebase-memory-differential-v8-seh-fix-2026-09-30.json`, 6,389 sites, zero mismatches. This validates relocation mapping only.
- Startup contract: `audit/candidate-startup-contract-v8-seh-fix-2026-09-30.json`, entrypoint/import-directory contract only.
- Installed system exports: `audit/candidate-import-resolution-v8-seh-fix-2026-09-30.json`, 82/82 names resolved. This does not execute candidate imports or initialization.
- Runtime: failed; GTA crashed at the same module offset as v7.
- Post-v8 source gates: `build/strict-xcode-nogs-o1-seh-startup-fix-20260930.json` 705/705; `audit/objective-seh-startup-fix-705-2026-09-30.json` 705 PASS; `build/parity-seh-startup-fix-20260930.json` 705 GREEN.

The v8 file is an experimental targeted patch layered on v7, not a fresh full candidate build, and is not a validated replacement. Original ASI hash remains `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
