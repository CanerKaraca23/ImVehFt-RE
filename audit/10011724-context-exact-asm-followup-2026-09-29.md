# 10011724 context-record correction

The earlier C++ candidate for `__call_reportfault` pointed `EXCEPTION_POINTERS.ContextRecord` at a single `DWORD` marker. This did not match the pinned x86 implementation, which reserves a `0x328`-byte frame and populates the x86 `CONTEXT` register, segment, flags, instruction-pointer, stack-pointer, and frame-pointer fields before calling `UnhandledExceptionFilter`.

The candidate is now a naked x86 assembly transcription of the Ghidra instruction stream. The source edit retained the previous source as `src/functions/10011724.cpp.pre-ghidra-context-exact-20260929.bak`. A dedicated resolver, `scripts/audit-reportfault-inplace-bytes.py`, applies the eight COFF fixups at the original image base, checks the four HIGHLOW sites against the recorded original relocation inventory, pins the reference ASI SHA-256, and compares the complete 0x129-byte body.

## Evidence

- Original input SHA-256: `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
- Exact in-place comparison: `audit/10011724-inplace-byte-reconstruction-context-asm-final-2026-09-29.json` reports byte-identical, 0x129 bytes, eight resolved COFF relocations, and matching four HIGHLOW sites.
- Isolated x86 strict compilation: `build/recheck/reportfault-context-asm-isolated5-20260929/10011724.obj`.
- Final-source 705-unit strict compile: `build/strict-reportfault-context-asm-linked-20260929.json` reports 705/705 with `/O1 /W4 /WX /MT /arch:IA32 /GS-`.
- Final-source objective audit: `audit/objective-reportfault-context-asm-linked-2026-09-29.json` reports 704 PASS / 1 FAIL / 0 UNKNOWN. The only finding is that its source-level ASM call counter sees four symbolic calls rather than the seven calls in Ghidra because it does not count the three indirect IAT calls. This finding is not hidden or rewritten; exact post-fixup byte comparison independently establishes the complete instruction body and its call sites.
- Final-source ReAgent 0.4.0 parity: `build/parity-reportfault-context-asm-linked-20260929.json` reports 705 GREEN / 0 YELLOW / 0 RED; this remains structural evidence, not semantic/runtime proof for the other functions.
- Final-source placement report: `audit/original-entry-slot-fit-reportfault-context-asm-linked-2026-09-29.json` places this body in a 297-byte gap with a 297-byte COMDAT.
- Fresh full-set diagnostic link succeeded, with stale `/ORDER` LNK4037 warnings: `build/link-probe/entry-cookie-check-exact-rep-ret-20260929/ImVehFt-reportfault-context-linked-not-ASI.dll`. It is explicitly a diagnostic DLL, not an ASI.
- The ReAgent structural parity engine reports this function green. The independent objective verifier flags only `ASM call mismatch: disassembly has 7 relevant calls, candidate has 4`; it does not recognize the three indirect IAT calls in inline assembly. The byte-for-byte in-place result independently adjudicates this parser limitation for this exact body; the verifier output itself remains a 704/705 PASS result and is not relabeled.

## Scope limits

Exact body identity at the original VA proves this candidate function emits the same bytes after fixups. It does not make the entire 705-function set semantically or dynamically verified, nor validate a complete PE/ASI, startup, loader integration, or GTA gameplay. The diagnostic DLLs are not production-loadable artifacts.
