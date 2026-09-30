# Ghidra-backed exception and callback vtable correction — 2026-09-29

## Callback-manager vtable crosswalk

`scripts/extract-ghidra-vftable-address-crosswalk.py` generated
`callback-vftable-exact-address-crosswalk-v2-2026-09-29.csv` and its JSON
manifest. It maps **21** callback-manager external vftable names to original
`.rdata` targets. The evidence includes 20 global initializer stores plus the
constructor-only `10009c10` case, which writes `0x10024CE0` directly to `[ESI]`.
Across the crosswalk, original Ghidra assembly, raw instruction bytes, and
original PE HIGHLOW records agree. The constructor’s Ghidra decompilation also
identifies the corresponding `BasicCallbackManager<5487649,...>::vftable`.

## Candidate corrections

Backups with suffix
`.pre-ghidra-vftable-crosswalk-20260929.bak` were created before editing the
six affected candidates:

- `10001010`, `10001430`, `100014a0`, `1001023b`, `1001cd37`, `10020870` now
  use Ghidra-backed exception vtable targets through existing relocatable
  `IVF_IMAGE_ADDRESS_*` aliases rather than unsupported vftable external names.
- `10001430` now calls the already implemented `ExceptionStorage::construct`
  body at `100102c3` with a matching C++ declaration instead of leaving an
  artificial `ExceptionAbi::construct` external.
- `100014a0` now calls the existing `ExceptionStorage::copy_construct` body
  at `10010351`, matching the Ghidra-proven `std::exception` copy constructor
  call, rather than declaring a second unresolved method name.
- Ghidra confirms the corresponding fixed vtable targets: `std::exception`
  `0x10022228`, `std::bad_alloc` `0x10022250`, and `std::bad_exception`
  `0x100261E8`.

## Fresh validation

- Strict current-source x86 build: **705/705**, `/O1 /W4 /WX /MT /arch:IA32
  /GS-`; report `build/strict-xcode-nogs-o1-exception-fix-20260929.json`.
- Independent ReAgent objective verifier: **705 PASS / 0 FAIL / 0 UNKNOWN**;
  `audit/objective-independent-exception-vftable-fix-2026-09-29.json`.
- ReAgent Ghidra parity: **705 GREEN / 0 YELLOW / 0 RED**;
  `build/parity-exception-vftable-fix-20260929.json`.
- A diagnostic link using the fresh 705-object set, current CRT aliases, exact
  original-data aliases, and the Ghidra crosswalk provider completed without
  linker errors. Output:
  `build/link-probe/entry-exact-nogs-o1-exception-fix-20260929/ImVehFt-entry-xcode-all-data-aliases-diagnostic-not-ASI.dll`.
- A separately named repeat produced the same 890,880-byte diagnostic image
  with linker exit code 0:
  `build/link-probe/entry-exact-nogs-o1-exception-fix-20260929/ImVehFt-entry-xcode-all-data-aliases-diagnostic-rerun-not-ASI.dll`.
- Its `.entry` raw bytes match all `0x20400` original `.text` bytes exactly.
  Its `.xcode` still starts at RVA `0x22000`, overlapping the original
  `.rdata`. The diagnostic import table also differs from the original: it adds
  ten Kernel32 imports (`FlsGetValue`, `FlsSetValue`, `FreeLibrary`,
  `GetConsoleOutputCP`, `GetFileSizeEx`, `GetModuleHandleExW`,
  `InitializeCriticalSectionEx`, `LoadLibraryExW`, `ReadConsoleW`,
  `SetFilePointerEx`) and lacks `GetCommandLineA` and `InterlockedIncrement`.
  DLL imports by name otherwise remain `d3dx9_43.dll`, `USER32.dll`, and
  `KERNEL32.dll`. This is further evidence that a successful link is not yet
  proof of matching loader/startup behavior.

## Still not a production ASI

The successful output is expressly diagnostic. Its `.xcode` section begins at
RVA `0x22000`, where the original image has `.rdata`; it therefore cannot be
installed or loaded as the rebuilt plugin. Link success proves name resolution
for this diagnostic input set only. PE section placement, the original and
candidate relocation reconciliation, startup/import semantics, and in-game
testing remain open. Both copies of the original ASI were rehashed as
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`; neither
was modified.

The publish repository currently has no project/solution/build definition
outside historical `reports`/`build` artifacts, the expected original solution
path `C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.sln` is absent, and
the earlier supplied SDK directory `C:\Users\caner\Downloads\SA Plugin SDK`
is not present at this check. The installed mod directory is present, but this
turn did not install or run a binary in GTA.
