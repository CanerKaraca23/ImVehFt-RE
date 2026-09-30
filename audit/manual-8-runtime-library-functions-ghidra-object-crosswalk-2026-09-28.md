# Eight exception/type_info function crosswalk

Date: 2026-09-28. Compared the exact-address Ghidra JSON listings/decompiles,
candidate source, and fresh MSVC x86 `/O2 /W4 /WX /MT /arch:IA32` COFF object
disassembly/relocations for the eight library candidates left in the
single-public-symbol inference group. No candidate source was changed.

| Address | Ghidra function | Ghidra behavior checked against source/object |
|---|---|---|
| `10010265` | `std::exception::_Copy_str` | Null-input branch; `_strlen`, allocate `length+1`, store pointer at `this+4`, conditional safe copy, set ownership byte at `this+8` only after successful allocation. COFF relocations target strlen, malloc, and strcpy_s. |
| `100102a5` | `std::exception::_Tidy` | Free only when ownership byte at `+8` is nonzero; clear pointer at `+4` and ownership byte. Relocation targets free. |
| `100102c3` | `std::exception` string constructor | Initialize pointer/ownership state and vtable `0x10022228`; call `_Copy_str` with the dereferenced input pointer; return `this`. The object has the corresponding vtable-provider and copy-helper relocations. |
| `100102ea` | `std::exception::operator=` | Self-assignment is a no-op; otherwise tidy destination, deep-copy an owned source or shallow-copy a non-owned pointer, preserve `this` as return. Relocations target the audited tidy/copy routines. |
| `10010351` | `std::exception` copy constructor | Initialize pointer/ownership/vtable, call assignment, return `this`; object relocation targets the assignment routine. |
| `10010761` | `type_info::~type_info` | Write vtable `0x10022248`, then call `_Type_info_dtor`; object has the matching provider and destructor-call relocations. |
| `10010771` | `type_info` scalar-deleting destructor | Call destructor; free through `FUN_10010756` only when `flags & 1`; return `this`. Both call relocations are present. |
| `10010792` | `type_info::operator==` | Compare type-name strings beginning at `this+9` and `other+9`; return true only for equal names. Object relocation targets `strcmp`. |

The fresh object files are from `build/recheck/strict-all-live-20260928-1/`;
their full-set compile report is `build/strict-all-live-20260928-1.json`.
Ghidra evidence is under `C:/Users/caner/OneDrive/Documents/ImVehFt/ghidra_exports/`.

## Validation boundary

This is a bounded manual static crosswalk for eight functions, not proof of
all 705 functions. The object compiler is MSVC 14.44, not the unavailable
original VS2010 project toolchain; C++ layout/calling behavior and runtime
library edge cases remain unexecuted in the target game. The nine
single-public-symbol COMDAT classifications (these eight plus the `RtlUnwind`
thunk), full PE layout/startup, and in-game validation remain open.
