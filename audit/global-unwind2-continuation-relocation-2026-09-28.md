# `__global_unwind2` continuation relocation

Ghidra export `ghidra_exports/10018e60.json` shows `__global_unwind2` pushing its continuation at `0x10018e78` for the `RtlUnwind` call, then restoring EBP/EDI/ESI/EBX and returning at that continuation. The former C++ body embedded the preferred-base continuation address directly.

Replaced the body of `src/functions/10018e60.cpp` with an MSVC x86 naked implementation that passes a local `unwind_continuation` label and calls the uniquely named recovered `RtlUnwind` thunk. Backup: `src/functions/10018e60.cpp.pre-relocatable-unwind-continuation-20260928.bak`.

The newly compiled candidate object was inspected with `dumpbin /disasm /relocations`. Its 32-byte instruction sequence matches Ghidra's sequence at `0x10018e60` instruction-for-instruction after relocation, including the saved EBP slot, all four stdcall arguments, and the epilogue. COFF contains `DIR32` to `$unwind_continuation$3` and `REL32` to `_ImVehFt_Recovered_RtlUnwind@16`; the final diagnostic map resolves the latter to candidate `1001b2b2.obj`.

Fresh whole-set checks after the edit: MSVC x86 strict compile **705/705**, independent structural objective **705 PASS / 0 FAIL / 0 UNKNOWN**, ReAgent parity **705 GREEN / 0 YELLOW / 0 RED**, and normal x86 diagnostic link of all 705 candidate objects succeeds. Source manifests were refreshed with backups. The literal inventory moved from v21's 18 occurrences / 17 unique addresses to v22's 17 / 16 (16 `.text`, one `.rdata`).

This is still not an ASI build or runtime proof. The diagnostic DLL does not recreate the original PE layout, all relocation/load-startup integration, or game behavior. The `.rdata` EH4 scope table passed to `__SEH_prolog4` remains a live relocation issue; it contains four relocated interior-code pointers and needs exact table/control-flow reconstruction, not a guessed C++ initializer.
