# Manual adjudication of remaining COMDAT entry aliases

Date: 2026-09-28. Resolved the nine candidates that the v9 report had called
unique-public-symbol inferences. The v14 generator now recognizes the exact
`RtlUnwind` thunk alias; the eight exception/type_info methods are manually
crosswalked to their sole public COFF code symbol below.

| Address | Ghidra target | Sole public COFF symbol | Evidence |
|---|---|---|---|
| `10010265` | `_Copy_str` | `?invoke@CopyStr_this@@QAEXPAD@Z` | Ghidra listing/body and fresh-object call relocations reviewed in `manual-8-runtime-library-functions-ghidra-object-crosswalk-2026-09-28.md`. |
| `100102a5` | `_Tidy` | `?tidy@ExceptionStorage@@QAEXXZ` | Same crosswalk; Ghidra ownership-byte branch/free/field-clears match source and object. |
| `100102c3` | `exception` | `?construct@ExceptionStorage@@QAEPAXPAPAD@Z` | Same crosswalk; Ghidra constructor stores vtable `0x10022228` and calls `_Copy_str`; COFF data/call relocations match. |
| `100102ea` | `operator=` | `?assign@ExceptionStorage@@QAEPAU1@PAU1@Z` | Same crosswalk; self-assignment, tidy, owned deep-copy and non-owned pointer-copy branches match. |
| `10010351` | `exception` | `?copy_construct@ExceptionStorage@@QAEPAU1@PAU1@Z` | Same crosswalk; constructor stores vtable/state and calls assignment. |
| `10010761` | `~type_info` | `?destroy@TypeInfoStorage@@QAEXXZ` | Same crosswalk; vtable `0x10022248` and `_Type_info_dtor` call match Ghidra/COFF. |
| `10010771` | ``scalar_deleting_destructor'` | `?scalar_deleting_destructor@TypeInfoStorage@@QAEPAU1@I@Z` | Same crosswalk; destructor call and conditional free when `flags & 1` match. |
| `10010792` | `operator==` | `?equals@TypeInfoStorage@@QBE_NPBU1@@Z` | Same crosswalk; Ghidra compares both names at `+9`; COFF calls `strcmp`. |
| `1001b2b2` | `RtlUnwind` | `_ImVehFt_Recovered_RtlUnwind@16` | Ghidra marks a thunk and shows `JMP dword ptr [0x100220b8]`; current x86 object has a DIR32 relocation to `__imp__RtlUnwind`; the original PE import table resolves `KERNEL32!RtlUnwind` IAT slot to exactly `0x100220b8`. Original ASI SHA-256: `409F0DF7AE579841DB05C3EC6AD0A9AFC579194632874962E1BDEE0CCF020D3`. |

For the eight C++ methods, current source SHA-256 values match the corresponding
rows of `audit/function-name-map.csv`, and each fresh x86 candidate object has
exactly the listed single public `.text` symbol. The reviewed Ghidra JSON files
are the exact-address exports under `C:/Users/caner/OneDrive/Documents/ImVehFt/ghidra_exports/`.

The v14 COFF-order report therefore reconciles all 705 targets as 678 literal
name matches, 7 address-bearing `this::invoke` aliases, 4 address-bearing
COFF labels, 7 stdcall identifier aliases, 1 verified import-thunk alias,
and these 8 manually reviewed C++ method aliases. There are no ambiguous or
unadjudicated single-public-symbol selections. The 746-symbol ordering file is
unchanged from successful v9 link input (SHA-256
`0EF433EE9456DB5A5596719ADEC4A345529F239E66F82637920C4420BD6FCAA9`).

## Limits

This adjudicates the **placement symbol association** for all 705 entries and
adds bounded static Ghidra/source/COFF evidence for nine. It does not prove
that all 705 C++ bodies are semantically equivalent, that their original RVAs
or complete PE layout are reproduced, or that the image starts or behaves
correctly in GTA. The successful image remains diagnostic-only, not a loadable
ASI; production build and game validation remain open.
