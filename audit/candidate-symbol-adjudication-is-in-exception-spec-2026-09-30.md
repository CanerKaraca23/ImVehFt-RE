# Candidate symbol adjudication: `IsInExceptionSpec` — 2026-09-30

## Decision

For the candidate image, both external relocations from `FindHandler` (`0x1001d591`) bind to candidate entry `0x1001cfab`, not to either address in the diagnostic link map. The duplicate map entries remain a true ambiguity of that diagnostic link, but they do not make the candidate object's intended entry ambiguous.

## Evidence

- The current 705-object set contains one definition of the exact decorated symbol `?IsInExceptionSpec@@YAEPAUEHExceptionRecord@@PBU_s_ESTypeList@@@Z`, in candidate object `1001cfab.obj`; the direct-fit relocation audit lists it as the entry symbol for `0x1001cfab`.
- `src/functions/1001d591.cpp` declares and calls that exact function twice (source lines 101, 242, and 409). Its COFF object has two `REL32` references to that exact undefined symbol at body offsets `0x120` and `0x2df`.
- Saved Ghidra export `1001d591.json` identifies `IsInExceptionSpec` at `0x1001cfab` as a callee and shows the original calls at `0x1001d6a4` and `0x1001d85e` targeting `0x1001cfab`.
- Saved Ghidra export `1001cfab.json` identifies the same entry/name and the expected `uchar __cdecl` two-argument signature.
- The conservative placement plan keeps `0x1001cfab` as an entry thunk (`jmp-rel32-thunk`); calls can therefore retain the original entry VA and reach the appended implementation through that thunk.
- The two diagnostic map addresses are `0x10018ead` (candidate object in the diagnostic `.xcode`) and `0x1004562c` (duplicate implementation from `libvcruntime-without-exsup4:frame.obj`). These are diagnostic-image addresses and are not production targets.

## Limits

This adjudicates only these two candidate-symbol references. It does not prove full relocation values, data/object lifetimes, PE startup, loader compatibility, semantic parity for all 705 functions, or in-game behavior. No PE bytes are changed.

Evidence fingerprints:

- Ghidra `1001d591.json`: `4E99B61268314C810B0C865E4238DCED73CC7DBE2ACE5D0B73E36FFC31266C65`
- Ghidra `1001cfab.json`: `C4F051CF8CFD734FE01C8643817B530C3ADEDCE4ACD49CF39337E7E05007F412`
- Candidate `src/functions/1001d591.cpp`: `853B5D8B7CA41F6A1BFDE0EB57D2A2315DC4305E7B901AEE6149AD8DD316C715`
- Candidate `src/functions/1001cfab.cpp`: `91980E26C5C8A199A2434CCBEE38B0A64DED122DE02B2A0E4296D5DC737B0B6F`
- Refreshed 705-object relocation crosswalk: [`candidate-relocation-symbol-targets-ghidra-positive-2026-09-30-v2.json`](candidate-relocation-symbol-targets-ghidra-positive-2026-09-30-v2.json)
