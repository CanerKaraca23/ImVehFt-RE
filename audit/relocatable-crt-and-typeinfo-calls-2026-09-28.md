# Relocatable CRT and type_info calls (2026-09-28)

Replaced five remaining preferred-base call operands in four candidate translation units with candidate symbols:

- `100102a5`: `_Tidy` now calls `_free` directly. Ghidra export `ghidra_exports/100102a5.json` identifies `_free` at `0x100116db` and shows the guarded free followed by clearing the pointer and flag.
- `10010761`: the type_info destructor now calls candidate `_Type_info_dtor` directly. `ghidra_exports/10010761.json` confirms the call occurs after installing the type_info vtable and after preserving ECX for the argument.
- `10010771`: scalar-deleting destructor now calls the candidate `TypeInfoStorage::destroy` member and `FUN_10010756` wrapper. `ghidra_exports/10010771.json` confirms destructor then optional free when flags bit 0 is set.
- `10010792`: type_info equality now calls candidate `_strcmp` directly; the existing name pointers at object offset `+9` remain unchanged. The target is also corroborated as `_strcmp` by Ghidra xrefs, including `ghidra_exports/1001cd5e.json`.

Backups are adjacent to each edited source as `.pre-relocatable-crt-calls-20260928.bak`. Fresh MSVC x86 `/O2 /W4 /WX /MT` compilation passed 705/705 (`build/strict-all-post-relocatable-crt-calls-20260928.json`). ReAgent objective passed 705/705 (`audit/objective-post-relocatable-crt-calls-2026-09-28.json`), and ReAgent parity was 705 GREEN / 0 YELLOW / 0 RED (`build/parity-post-relocatable-crt-calls-20260928.json`). The normal 705-object diagnostic DLL link succeeded (`build/link-probe/strict-704-historical-sdk/ImVehFt-reloc-crt-calls-diagnostic-not-ASI.dll`); changed COFF objects contain REL32 symbol relocations for `_free`, `_Type_info_dtor`, `TypeInfoStorage::destroy`, `FUN_10010756`, and `_strcmp`.

The preferred-image literal inventory is now 29 occurrences / 28 unique `.text` addresses, including 12 exact candidate-entry addresses and 16 interior/non-entry addresses (`audit/candidate-internal-image-address-literals-v14-2026-09-28.json`). This inventory does not classify every remaining use as erroneous. Both 705-row source fingerprint manifests were refreshed and verified with zero mismatches.

This is compile, structural/parity, and diagnostic-link evidence only. The DLL is not a game-loadable `.asi`; image layout/relocation reconstruction, complete startup/import/hook integration, and runtime/gameplay validation remain open.
