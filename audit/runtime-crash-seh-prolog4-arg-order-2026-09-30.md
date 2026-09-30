# Runtime crash and `__SEH_prolog4` argument-order correction

## Runtime evidence

Candidate v7 (`build/pe-layout-probe/ImVehFt-candidate-705-static-20260930-v7.asi`, SHA-256 `041B0CD18AFF3F7872AA4BC8EA8D1BBA96181B98C8D231D08FC9BBDAED74E320`) was copied only into the isolated test clone at `C:\GTASA-ImVehFt-Test-20260930\modloader\My Scripts\ImVehFt-RE-Test\ImVehFt.asi`. ModLoader's log showed it installing that plugin. The clone's GTA process terminated after an access violation; the original ModLoader installation and original ASI were not replaced.

Windows Application Error/WER evidence identifies `gta_sa.exe`, fault module `imvehft.asi`, exception `0xC0000005`, and module offset `0x4BE6A`. The candidate image base is `0x10000000`, so this is RVA `0x4BE6A`, within `.xcode` at RVA `0x43000`, offset `0x8E6A`. The current appended-body census places `___SEH_prolog4` at payload offset `0x8E50`; the fault is `+0x1A`, at its `push ebx` after `sub esp,eax`.

## Initial hypothesis: `_Type_info_dtor` argument order

Ghidra export `ghidra_exports/10013ad2.json` for `_Type_info_dtor` records this call sequence:

```asm
PUSH 0xc
PUSH 0x10028308
CALL 0x10012e20
```

The old C++ call expressed the arguments as `(0x0C, 0x10028308)`. Since `__SEH_prolog4` is cdecl, that source order generates `push 0x10028308`, then `push 0x0C`, reversing Ghidra's observed order. The source edit to `(0x10028308, 0x0C)` generates `push 0x0C`, then `push 0x10028308`, as expected. This is a valid local correction for `_Type_info_dtor`, but the later v8 runtime test proves it is not sufficient to resolve the startup crash. Its pre-edit version is preserved at `src/functions/10013ad2.cpp.pre-seh-prolog4-arg-order-20260930.bak`.

Fresh MSVC object evidence from `build/recheck/strict-xcode-nogs-o1-seh-arg-fix-20260930/10013ad2.obj` shows the source edit emits `push 0Ch`, `push offset _IVF_RELOC_TARGET_10028308`, `call ___SEH_prolog4`. This matches Ghidra for that one caller but does not identify the startup crash caller.

```asm
push esi
push 0Ch
push offset _IVF_RELOC_TARGET_10028308
call ___SEH_prolog4
```

## Follow-up runtime test: hypothesis insufficient; startup callsite mismatch found

An experimental v8 was created from v7 by patching only `_Type_info_dtor`'s first eight bytes and moving its corresponding HIGHLOW record from RVA `0x13AD4` to `0x13AD6`. Its SHA-256 is `73A9A04DDEA5C38B092EB7D22C2932836F80505A28738ABA280EDD5C825C9CCC`. The candidate preserved all **6,389** base relocations in a nonpreferred-base map test with **0 mismatches**, and static startup/import checks passed (82 imports unchanged). A first attempted launch accidentally loaded the preserved v7 copy from the clone root; that run is invalid for v8. After moving that copy outside the game directory, a fresh launch definitively loaded v8 from `modloader\My Scripts\ImVehFt-RE-Test\ImVehFt.asi`; WER again recorded `0xC0000005` at module offset `0x4BE6A`. Therefore the `_Type_info_dtor` patch does **not** resolve the observed startup crash.

The next stronger lead is the first startup caller, `___DllMainCRTStartup` at `0x100110BD`. Ghidra shows its first instructions as `PUSH 0x0C; PUSH 0x100282A8; CALL 0x10012E20`. The current source instead calls `__SEH_prolog4()` with no arguments, and the fresh object `build/recheck/strict-xcode-nogs-o1-seh-arg-fix-20260930/100110bd.obj` begins with compiler-generated `push ebp; mov ebp,esp; ...` and then calls the helper without pushing either argument. This is a concrete source/object-to-Ghidra mismatch at the loader entry path and is consistent with the crash occurring in `sub esp,eax`; it has not yet been repaired or re-tested. Ghidra lists 31 callsites to this helper, so they must be audited individually rather than assuming one caller is the only defect. Full details: [`runtime-seh-prolog4-followup-v8-2026-09-30.md`](runtime-seh-prolog4-followup-v8-2026-09-30.md).

## Fresh gates and remaining validation

- Strict x86 compile: 705/705 passed, 0 failed (`build/strict-xcode-nogs-o1-seh-arg-fix-20260930.json`).
- Independent structural objective audit: 705 PASS, 0 FAIL, 0 UNKNOWN (`audit/objective-seh-prolog4-arg-fix-705-2026-09-30.json`).
- ReAgent parity: 705 GREEN, 0 YELLOW, 0 RED (`build/parity-seh-prolog4-arg-fix-20260930.json`).
- These are source/object/structural checks, not proof that the corrected function is semantically exact or that a complete candidate PE runs.
- Candidate v8 reproduced the same helper-offset crash and was moved out of the clone; its copy is preserved under `build/pe-layout-probe`. The startup-path source mismatch in `___DllMainCRTStartup` has since been corrected with Ghidra-matching naked x86 assembly and passed fresh 705/705 compile/objective/parity gates, but it has not yet been emitted into a candidate PE or runtime-tested. The other `__SEH_prolog4` callers also remain to be audited. Original `ImVehFt.asi` remains untouched; full startup and gameplay validation remain open.
- Original `ImVehFt.asi` remains untouched; the candidate and clone are experimental.
