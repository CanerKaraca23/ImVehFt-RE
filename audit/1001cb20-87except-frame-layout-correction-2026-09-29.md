# `0x1001cb20` `__87except` frame/x87 correction

## Ghidra evidence and defect found

The prior `src/functions/1001cb20.cpp` was a normal C++ wrapper. Its `/O1 /GS-` object (`0x21` bytes) saved ST(0) with `FST` at `[EBP-0x0c]`, passed `&local_24` at `[EBP-4]` to `__87except`, reloaded the double, and returned without the x87 control-word restore seen in the adjacent CRT handler.

Ghidra exports show `0x1001cb20` allocating a `0x20`-byte frame, saving EAX at `[EBP-0x20]`, copying arguments from `[EBP+0x18]` and `[EBP+0x1c]`, then jumping to `0x1001cb40`. That address is the shared tail of `__startOneArgErrorHandling` at `0x1001cb37`: `FSTP [EBP-8]`, fill the remaining record fields, pass `EDX`, `EBP-0x20`, and `EBP+8` to `__87except`, reload the saved double, compare the control word to `0x027f`, conditionally `FLDCW`, then `LEAVE; RET`.

This frame is required by the current `1001defe.cpp` candidate: `__87except` reads `*param_2`, reads the saved double at `param_2+6`, and passes `param_2+2` to `__raise_exc`. With `param_2 = EBP-4`, the prior wrapper would instead make `param_2+6` point above the caller frame. The old C++ temporaries did not force the binary's required contiguous layout.

## Correction and verification

The replacement in `src/functions/1001cb20.cpp` uses naked MSVC x86 assembly to reconstruct the Ghidra prologue and common handler tail in one body. Its COFF symbol remains `?FUN_1001cb20@@YIOIHGIIIII@Z`, matching the expected entry symbol. The focused strict compile succeeds; disassembly now has the `0x20` frame, `FSTP [EBP-8]`, `LEA ECX,[EBP-0x20]`, the same three-argument call setup, `FLD [EBP-8]`, `FLDCW [EBP+8]`, and `LEAVE; RET`. Object code grows from 33 to 72 bytes, so it still needs an entry thunk for the 23-byte original gap.

The old source was preserved as `src/functions/1001cb20.cpp.pre-87except-frame-layout-fix-20260929.bak`; both source-hash manifests were backed up and refreshed. Fresh checks on the current 705-source set:

- Strict MSVC x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-`: `build/strict-xcode-nogs-o1-thunk-audit-20260929.json`, **705/705**.
- Independent ReAgent objective verifier: `audit/objective-independent-nogs-o1-thunk-audit-2026-09-29.json`, **705 PASS / 0 FAIL / 0 UNKNOWN**.
- Local ReAgent 0.4.0 parity against Ghidra JSON: `build/parity-nogs-o1-thunk-audit-2026-09-29.json`, **705 GREEN / 0 YELLOW / 0 RED**. This is structural parity, not semantic proof.
- Fresh 705-object diagnostic link and current-size placement: `build/link-probe/strict-704-historical-sdk/ImVehFt-o1-x87-frame-diagnostic-not-ASI.dll` (not an installable ASI); the refreshed COFF audit remains **556 direct-fit / 148 thunked**, with all 705 diagnostic code targets executable and rel32-reachable.
- Fresh relocation-target audit: `audit/candidate-relocation-symbol-targets-o1-x87-frame-coff-exact-2026-09-29.json`, 4,442 relocations resolve uniquely in the diagnostic map. Those map addresses are not production targets.

## Still open

## Ghidra-derived x86 ABI harness follow-up

Added `tests/1001cb20_x87_frame_abi_harness.cpp`, compiled it as a 32-bit MSVC executable with the current candidate object, and ran both a reference body transcribed from Ghidra's `0x1001cb20` prologue plus `0x1001cb40` common tail and the compiled candidate. Both passed two cases (`[EBP+8]` control word `0x027f` and `0x037f`): `__87except` received the expected seven-word frame plus saved double, return bits matched `3.25`, x87 TOP was zero after consuming the return, and the control word followed the conditional restore path (`0x0b7f` or `0x037f`).

Negative control: linked the same harness against the previous `1001cb20.obj`. The reference cases passed; the old candidate failed both cases: frame check false, x87 TOP remained 7 then 6, and the restore case incorrectly left CW `0x0b7f`. The negative-control executable exited 1 as expected. This establishes that the harness detects the specific prior defect.

This is an ABI/stack harness against a controlled `__87except` test double and a Ghidra-transcribed reference, **not execution of the original ASI bytes**, not validation of the real `__87except` interactions, and not GTA gameplay validation. A production-compatible PE and game load/test remain open. Four thunk entries with no recorded saved-project incoming xrefs remain unexplained; indirect/runtime-computed dispatch is not excluded. ReAgent green and compile/objective passes do not close those risks.

## Original-image byte corroboration and fresh rerun (2026-09-29)

Re-hashed the pinned original `ImVehFt.asi`: `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`. PE section mapping places VA `0x1001cb20` at file offset `0x1bf20`. The 83 bytes from that offset begin with the Ghidra-observed `55 8B EC 83 C4 E0 89 45 E0 ... EB 09` prologue/shared-tail jump, contain the shared tail's `DD 5D F8` save, `E8 9E 13 00 00` call at VA `0x1001cb5b` (resolving to `0x1001defe`), and end with the conditional `74 03 D9 6D 08 C9 C3`. This corroborates the Ghidra instruction transcription against the pinned PE bytes; it is still not a direct runtime comparison.

Rebuilt and reran the harness from the checked-in source using the current candidate object. Both Ghidra-reference cases and both candidate cases passed; this source includes the additional `control_word_slot - argument_block == 0x28` frame-layout assertion. Fresh executable: `build/abi-harness/rerun-20260929/1001cb20-x87-frame-abi-current.exe` (SHA-256 `ABF9E0AF6AC72A4A300DF5B36BA82DFA1380524EF9B194B6D75442D8E6F3CE3E`). Rebuilt the negative control against the previous object: both reference cases passed, both old-candidate cases failed the frame/TOP/control-word checks, and process exit was 1 as expected (`.../1001cb20-x87-frame-abi-old-negative.exe`, SHA-256 `5BA88C79D0E7D788611D1AF440FCF252976F47CF1A75D13B772A471338E19ECC`).
