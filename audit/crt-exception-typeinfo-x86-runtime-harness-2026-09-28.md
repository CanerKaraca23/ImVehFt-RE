# Isolated x86 runtime harness: exception and type_info functions

Date: 2026-09-28. Linked the current eight candidate COFF objects directly
into a small x86 executable and ran them outside GTA. This is executable
behavior evidence for these eight functions, not for the full module.

## Tested candidate objects and paths

Objects from `build/recheck/strict-all-live-20260928-1/`:

- `10010265.obj` `_Copy_str`: copy a string, preserve state for null input,
  and handle allocation failure.
- `100102a5.obj` `_Tidy`: free owned text and clear pointer/ownership state.
- `100102c3.obj` exception string constructor: initialize vtable/state and
  copy input text.
- `100102ea.obj` exception assignment: self-assignment, assignment from an
  owned source (deep copy), and from a borrowed source (shallow copy).
- `10010351.obj` exception copy constructor: initialize then copy-assign.
- `10010761.obj` type_info destructor: restore vtable and call destructor
  hook.
- `10010771.obj` scalar-deleting destructor: test both clear and set low-bit
  flags; only the latter invokes deallocation.
- `10010792.obj` type_info equality: equal and unequal names at byte offset 9.

The executable returned **0** (all harness assertions passed). It was
confirmed PE32 machine `0x14C` (x86), compiled with MSVC 14.44, `/O2 /W4 /WX
/MT /GS`; SHA-256:
`24A7F01558C9F5F5B87EBB68286AB1A7AA25EC9A5031C642408C6BCEA75E9968`.
Source: `tests/runtime_crt_exception_typeinfo_harness.cpp`; output:
`build/abi-harness/crt-exception-typeinfo-live-20260928.exe`.

## Harness boundaries

The candidate code is the actual compiled `.obj`, not a reimplementation.
The harness supplies deterministic test doubles for allocation/free,
`strlen`, `strcmp`, `_Type_info_dtor`, the `FUN_10010756` deallocator hook,
and the two image-vtable addresses. MSVC CRT supplies `strcpy_s` and normal
process startup. This exercises the candidate instruction/calling behavior
for the listed paths, but it does not test the original CRT allocator,
exception runtime/unwinder, the real type_info vtables, all edge cases, or GTA
loader/game callbacks. It cannot validate original VS2010 build identity or
the other 697 functions. No candidate source was changed and no ASI was loaded.
