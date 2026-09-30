# Exception-method call relocation pass (2026-09-28)

Reviewed remaining in-image call operands for the reconstructed MSVC `std::exception` storage helpers. Replaced fixed preferred-base calls with typed candidate member calls for constructor (`0x100102c3`), copy constructor (`0x10010351`), tidy (`0x100102a5`), and `_Copy_str` wrapper (`0x10010265`) across the caller translation units `1000d400`, `100101a5`, `100101c2`, `100101f2`, `100102c3`, `100102ea`, `1001031f`, `1001032a`, `10010893`, `1001d906`, and `10020870`. `10010351`'s implementation also now calls the candidate assignment method directly. The `BadAllocStorage` global retains its original linker-visible type; only its receiver is viewed as the ABI-compatible `ExceptionStorage` for the copy-constructor call.

The five initial edits and seven follow-up caller edits each have adjacent `.pre-relocatable-exception-methods-20260928.bak` backups. A normal link first caught an external-symbol type mismatch on `DAT_100399e0`; this was corrected by preserving the original global symbol type and rebuilding all objects. Final evidence:

- MSVC x86 `/O2 /W4 /WX /MT`: 705/705 TUs passed (`build/strict-all-post-relocatable-exception-calls-linkfix-20260928.json`).
- ReAgent structural objective: 705 PASS / 0 FAIL / 0 UNKNOWN (`audit/objective-post-exception-calls-linkfix-2026-09-28.json`).
- ReAgent 0.4.0 parity: 705 GREEN / 0 YELLOW / 0 RED (`build/parity-post-exception-calls-linkfix-20260928.json`).
- The current 705-object x86 diagnostic link succeeded: `build/link-probe/strict-704-historical-sdk/ImVehFt-reloc-exception-calls-final-diagnostic-not-ASI.dll` (724,480 bytes). Its map resolves `ExceptionStorage::construct`, `copy_construct`, `tidy`, and `CopyStr_this::invoke` to candidate object symbols.
- The fresh preferred-image literal inventory is 34 occurrences / 33 unique `.text` addresses, 17 exact candidate entries and 16 non-entry addresses (`audit/candidate-internal-image-address-literals-v13-2026-09-28.json`). Each residual address still needs per-use classification.

These checks establish compileability, structural/parity status, and a successful diagnostic link only. The DLL is not a game-loadable `.asi`; original PE layout/relocation, complete startup/import/hook integration, runtime behavior, and gameplay remain unverified. The source fingerprint refresh was attempted but Windows denied atomic replacement of `audit/function-name-map.csv`; do not treat the old manifest as refreshed until that file is safely updated and both manifests are independently checked.
