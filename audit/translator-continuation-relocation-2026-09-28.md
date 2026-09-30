# `_CallSETranslator` interior continuation relocation

Ghidra export `C:\Users\caner\OneDrive\Documents\ImVehFt\ghidra_exports\1001b750.json` shows that the special `param_1 == 0x123` path stores `0x1001b7fb` through `param_2`. The target is not a function entry: it is the continuation after the translator callback, where the original function checks its SEH state, restores `FS:[0]`, and returns. The callback path reaches the same continuation after clearing its return-state local. Replacing this with a normal function address would change exception-chain semantics.

Replaced the decompiled C body in `src/functions/1001b750.cpp` with naked x86 assembly preserving the observed prologue, stack frame, registration-node layout, callback ABI, both special/normal branches, and the exception-chain restore block. The target is now `OFFSET translator_exception_chain_restore`, a local label at offset `+0xab` after the hotpatch `mov edi,edi`, rather than a preferred-image VA. `TranslatorGuardHandler`, `DAT_10029490`, and `__getptd` are emitted as symbol relocations.

Evidence and checks:

- Fresh MSVC x86 object disassembly places the continuation label at offset `0xab`, matching Ghidra's `0x1001b7fb - 0x1001b750`; the special branch's DIR32 relocation targets that local label.
- Object relocations include candidate `TranslatorGuardHandler`, `DAT_10029490`, and `__getptd` references. The 705-object diagnostic link map resolves `_CallSETranslator` to `1001b750.obj` and the handler to `1001b827.obj`.
- Strict MSVC compile: 705/705; independent objective verifier: 705 PASS, 0 FAIL, 0 UNKNOWN; ReAgent parity: 705 GREEN, 0 YELLOW, 0 RED.
- The linked artifact is `build/link-probe/strict-704-historical-sdk/ImVehFt-translator-continuation-diagnostic-not-ASI.dll`. It is only a diagnostic DLL, not a loadable ASI. This change has not received game/runtime validation.
- Source SHA-256 manifests were refreshed for all 705 translation units; pre-refresh copies are retained with `.pre-translator-continuation-20260928.bak` suffixes. The edited source also has an adjacent pre-edit backup.
