# Relocatable `_LocaleUpdate` constructor calls (2026-09-28)

Ghidra identifies `0x10010b1a` as
`_LocaleUpdate::_LocaleUpdate(localeinfo_struct*)`, `__thiscall`, ending in
`RET 4`. Three candidate callers used that fixed VA:

- `1001a785`, call site `0x1001a7d8`;
- `1001aa4f`, call site `0x1001aa5d`;
- `1001bb5f`, call site `0x1001bb6e`.

At each site Ghidra loads the constructor object's address into `ECX`, pushes
one locale pointer, and calls the constructor. The candidate constructor is
present in `10010b1a.cpp` with COFF symbol
`??0_LocaleUpdate@@QAE@PAUlocaleinfo_struct@@@Z`.

The three fixed-address function-pointer calls have been replaced by explicit
MSVC x86 register/stack sequences calling
`IVF_LocaleUpdate_ctor_relocatable`. The new
`src/functions/locale_update_ctor_bridge.hpp` emits a linker `/alternatename`
from that C symbol to the exact constructor symbol. `dumpbin` verifies each
caller contains a `REL32` relocation to the bridge; the successful full link
map places both bridge and constructor at the same address, `0x10010d40` in the
diagnostic image. The constructor still performs callee cleanup of the single
stack argument.

Backups made before the edits:

- `src/functions/1001a785.cpp.pre-relocatable-localeupdate-20260928.bak`
- `src/functions/1001aa4f.cpp.pre-relocatable-localeupdate-20260928.bak`
- `src/functions/1001bb5f.cpp.pre-relocatable-localeupdate-20260928.bak`

Fresh full-set checks:

- MSVC x86 `/O2 /W4 /WX /MT`: **705/705**;
- independent ReAgent objective: **705 PASS / 0 FAIL / 0 UNKNOWN**;
- ReAgent 0.4.0 parity: **705 GREEN / 0 YELLOW / 0 RED**;
- source manifest: **705 rows / 0 mismatches**;
- diagnostic link: all **705** current candidate objects, no diagnostics.

The current internal-VA inventory is v11: **49 occurrences / 39 unique `.text`
VAs**, of which 23 are exact candidate function entries and 16 are non-entry
addresses. These gates remain static/source-object checks. The output is still
a diagnostic DLL, not a production/test-ready ASI; PE layout, loader/hook
integration, and in-game behavior have not been validated.
