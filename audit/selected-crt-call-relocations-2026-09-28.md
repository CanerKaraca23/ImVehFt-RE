# Selected CRT/callback call relocations (2026-09-28)

Removed five more fixed original-image code addresses from five caller translation units, following the Ghidra-backed CRT/type_info pass in `audit/relocatable-crt-and-typeinfo-calls-2026-09-28.md`:

- `100103e4` now passes the address of candidate `__input_l` to `vscan_fn`; Ghidra export `ghidra_exports/100103e4.json` shows this exact function-pointer dataflow. MSVC emitted a DIR32 relocation to the decorated `__input_l` symbol, and the 705-object link map resolves it to `100119f1.obj`.
- `1001bc78` now calls candidate `__forcdecpt_l` directly. `ghidra_exports/1001bc78.json` confirms the two cdecl arguments and zero locale argument; the link map resolves the external to `1001baeb.obj`.
- `100042c0` now calls candidate `_memset` directly with the existing destination, zero value, and `0x518` size. The map includes the candidate symbol from `10016740.obj` (distinct from the CRT-library `_memset`).
- `10010893` calls the candidate `FUN_1001023b_this::invoke` method for bad-allocation message construction. `ghidra_exports/10010893.json` confirms the destination and message-address arguments; the data global keeps its original linker-visible `BadAllocStorage` type.
- `10014003` calls candidate `FUN_1001189f` directly. Ghidra identifies this helper as `__stdcall`; its candidate definition and final map agree on the zero-argument stdcall target.

Each edited source has an adjacent `.pre-relocatable-crt-calls-20260928.bak`. Final full-set checks after these edits:

- MSVC x86 `/O2 /W4 /WX /MT`: 705/705 pass (`build/strict-all-post-relocatable-selected-calls-20260928.json`).
- ReAgent structural objective: 705 PASS / 0 FAIL / 0 UNKNOWN (`audit/objective-post-selected-relocatable-calls-2026-09-28.json`).
- ReAgent parity: 705 GREEN / 0 YELLOW / 0 RED (`build/parity-post-selected-relocatable-calls-20260928.json`).
- Normal link of the 705 current objects succeeds; map checks the five named destinations in `build/link-probe/strict-704-historical-sdk/ImVehFt-reloc-selected-calls-final-diagnostic-not-ASI.map`.
- Updated original-image literal scan: 24 occurrences / 23 unique `.text` addresses; 7 exact candidate entries and 16 non-entry addresses (`audit/candidate-internal-image-address-literals-v15-2026-09-28.json`). Both 705-row source fingerprint manifests independently match the current sources with zero mismatches.

These are static/source-object and diagnostic-link checks, not proof of semantic equivalence. The output is not a game-loadable `.asi`; original PE layout and relocations, startup/import/hook integration, and runtime/game validation remain incomplete.
