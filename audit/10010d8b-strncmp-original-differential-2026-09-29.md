# `10010d8b` `_strncmp` original-binary differential (2026-09-29)

## Target and method

- Ghidra export `ghidra_exports/10010d8b.json` identifies the original target
  as `__cdecl _strncmp(char*, char*, size_t)` at `0x10010d8b`. The current
  MSVC object contains the address-mapped candidate as a self-contained
  executable COMDAT with no COFF code relocations.
- Added
  `tests/runtime_10010d8b_strncmp_original_differential.cpp`. It maps the
  hash-pinned original ASI at its preferred base, calls original code at
  `0x10010d8b` and the candidate from the latest 705-object strict build, and
  checks exact integer return plus cdecl stack cleanup for both.
- The x86 harness was built by VS 2022 with `/O1 /W4 /WX /MT /arch:IA32` and
  linked against the exact current `10010d8b.obj` from
  `strict-xcode-nogs-o1-fopen-linkage-alias-final-20260929`.

## Result

- **1,146,594** original/candidate comparisons passed:
  - 1,046,529 exhaustive ordered pairs of short NUL-terminated byte strings
    over `{0x01, 0x7f, 0x80, 0xff}`, for count limits 0 through 8;
  - 100,000 deterministic binary-buffer cases with varied pointer alignment,
    embedded NULs, high-bit bytes, and count limits 0 through 35;
  - 65 guard-page cases covering exact-count reads and early-NUL termination
    immediately before inaccessible pages.
- Return values matched exactly, including unsigned high-byte ordering. Both
  implementations left the three cdecl arguments for caller cleanup (ESP
  delta `-12` after call; `0` after cleanup).
- Original ASI SHA-256 remained
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
- Candidate source SHA-256:
  `ABD997D6A6DED796D5747921F67DD236473475DE64288242AE9CE131BA2E693B`.
  Harness source SHA-256:
  `093875146971EBE728ABBD1E9CE3639B2B8534A576056F885FCA95F47FA0AAC2`.
  Candidate object SHA-256:
  `2219D8E0967CC3573A098190EBB8DC3BCD8C744A02198B31193E3F16B1832383`.
  Harness executable SHA-256:
  `B3F5EF823DF048B394B1BEC5CA286BFEA313BF60A8AAFDD8C97FCCF80BD59F98`.

## Scope limit

This is strong bounded differential evidence for this string routine, not an
exhaustive proof over all address spaces or invalid pointers. It does not
validate any other target, PE startup/relocation/import behavior, or GTA
runtime behavior. No candidate source change was needed.
