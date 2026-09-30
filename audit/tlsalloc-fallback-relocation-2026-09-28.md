# `__mtinit` legacy `FlsAlloc` fallback relocation

Ghidra export `ghidra_exports/10014fa7.json` and original-ASI disassembly show the fallback `FlsAlloc` callback at `0x10014c49` is exactly `call dword ptr [0x100220d0]` followed by `ret 4`: it ignores the callback argument, invokes `TlsAlloc`, and uses the stdcall one-argument cleanup expected by `FlsAlloc`.

Replaced that preferred-base code pointer in `src/functions/10014fa7.cpp` with `ImVehFt_Recovered_TlsAllocShim`, declared `DWORD WINAPI` with the callback parameter intentionally unnamed and returning `TlsAlloc()`. Fresh MSVC x86 object inspection emits the same two instructions (`call [__imp__TlsAlloc@0]`, `ret 4`) and a `DIR32` relocation from `__mtinit` to the shim. The 705-object link map resolves the shim to `10014fa7.obj` and the import to `kernel32:KERNEL32.dll`. Backup: `src/functions/10014fa7.cpp.pre-relocatable-tlsalloc-shim-20260928.bak`.

After this change: strict MSVC x86 **705/705**, independent objective **705 PASS / 0 FAIL / 0 UNKNOWN**, ReAgent parity **705 GREEN / 0 YELLOW / 0 RED**, and the normal 705-object diagnostic link succeeds. Both 705-row source manifests were refreshed with backups. Literal inventory v25 has **14 occurrences / 13 unique addresses**, all `.text`; the `0x10014c49` absolute callback address is gone.

This remains static/object/link evidence only. The output is a diagnostic DLL, not a game-loadable ASI; original-image layout, complete startup/hook integration, and runtime/game execution are still unverified.
