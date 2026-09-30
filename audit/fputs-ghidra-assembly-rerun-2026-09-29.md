# `0x10010913` Ghidra assembly and current-set rerun — 2026-09-29

## Change and evidence

Ghidra identifies the original `0x10010913` body as C-linkage `_fputs`, including an x86 SEH prolog call with `(scope table 0x10028268, frame size 0x10)`. The former ordinary C++ reconstruction did not encode that special prolog and its decorated C++ symbol did not satisfy the caller's C `_fputs` reference. The source now declares C linkage and transcribes the body as naked x86 assembly. Previous source versions are retained beside the source as `.bak` files.

The fresh strict object is `build/recheck/strict-fputs-asm-rerun-20260929/10010913.obj` (SHA-256 `2604C67C9972909FBFD92F5A84E4B612AD3D18E18378CECE4A5753FEADA59D45`). Its `_fputs` COMDAT is 251 bytes and has 11 COFF `REL32` call fixups. Against the pinned original ASI (`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`), every byte outside those 11 four-byte call-displacement fields matches at entry `0x10010913` (0 unmasked differences). This verifies the assembly transcription's instruction bytes, not runtime semantics.

The original image also has five `HIGHLOW` base-relocation fields inside this function, at `0x10010916`, `0x10010978`, `0x1001097f`, `0x100109a1`, and `0x100109a8`. The COFF object has no corresponding `DIR32` entries, but the operands and relocation sites are byte-identical at the original VA. `scripts/audit-fputs-inplace-byte-reconstruction.py` resolves each of the 11 COFF calls to its Ghidra-exported target, then compares the complete in-memory 251-byte candidate body at `0x10010913` with the pinned PE: **all 251 bytes match exactly**, and all five original HIGHLOW sites are retained. This supports an in-place body replacement only if the final PE writer preserves the original relocation directory and resolves the calls exactly; it does not validate any final image or moved diagnostic link.

## Fresh 705-unit checks

- Strict MSVC x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-`: **705/705** (`build/strict-fputs-asm-rerun-20260929.json`).
- Independent structural objective audit: **705 PASS / 0 FAIL / 0 UNKNOWN** (`audit/objective-fputs-asm-rerun-2026-09-29.json`).
- ReAgent 0.4.0 parity: **705 GREEN / 0 YELLOW / 0 RED** (`build/parity-fputs-asm-rerun-20260929.json`).
- Fresh 705-object diagnostic link completed to `build/link-probe/entry-fputs-asm-rerun-20260929/ImVehFt-m80-reloc-probe-not-ASI.dll`; it emitted stale `/ORDER` LNK4037 warnings (including entries for old `fputs`/SEH symbol spellings). It is diagnostic-only, not an ASI.
- Fresh placement/relocation evidence: `audit/original-entry-slot-fit-fputs-asm-rerun-2026-09-29.json` (557 bodies fit their bounded entry gaps, 147 exceed them, one final entry has no next-entry boundary); `audit/entry-trampoline-feasibility-fputs-asm-rerun-2026-09-29.json` (557 direct bodies fit, 147 need a thunk, no rel32 range failures); `audit/inplace-candidate-relocation-coverage-fputs-asm-rerun-2026-09-29.json` (705 classified; 2,774 original HIGHLOW overlap instances across the set, including five in `_fputs`).
- Relocation-free byte audit for the full set: 31 eligible bodies, 16 exact and 15 different; it intentionally excludes bodies with relocations and is not a behavioral test (`audit/reloc-free-byte-matches-fputs-asm-rerun-2026-09-29.json`).
- Both 705-row source manifests were refreshed with preserved backups after the edit.

## Controlled original-versus-candidate differential

`scripts/test-10010913-fputs-original-differential.ps1` compiles and runs `tests/runtime_10010913_fputs_original_differential.cpp` against the pinned original ASI and the fresh `_fputs` object. The harness maps the original image at its preferred base, executes the original function body, and uses the original EH4 prolog/epilog helpers for both bodies. Other CRT helpers are detoured to deterministic recorders; the stream-info table is controlled. Across **5 fresh x86 processes × 10 cases each**, return values, errno, helper call order/counts, file bytes/count, and ftbuf/flush observations matched. Cases cover null arguments, `_flag & 0x40`, valid descriptor entries 0 and 32, first- and second-stage stream flags, special descriptors -1/-2, and full/short writes. Harness SHA-256 `830AC94DD45C2BFCD09AEAB6D2D2C542C30AFA296EDA1D876443E68828890B80`.

This validates the function body against the original under controlled helper behavior, not real CRT file/lock/flush semantics, OS exception dispatch, arbitrary filesystem state, final PE relocation-directory retention/startup, or GTA gameplay.

## Still open

No production PE/ASI has been constructed or validated. The diagnostic link does not reconstruct the original sections, imports, base-relocation table, startup/installer hooks, or game integration. `_fputs` live behavior through real CRT/OS file operations and OS exception dispatch remains open, as do GTA/RenderWare gameplay validation and the unavailable original ImVehFt project/build recipe. Compile/objective/parity GREEN must not be reported as 705 functions semantically or runtime verified.
