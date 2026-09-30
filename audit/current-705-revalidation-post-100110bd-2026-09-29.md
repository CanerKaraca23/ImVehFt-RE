# Current 705-set revalidation after `100110bd` — 2026-09-29

## Exact current-set checks

The 705-row `audit/source-sha256.csv` was reread against the working C++ files:
705 rows, zero source/hash mismatches. `audit/function-name-map.csv` also has
705 rows. The fresh independent objective report includes a SHA-256 per source;
all 705 hashes match the source manifest.

- Strict MSVC 2022 x86 `/O1 /W4 /WX /MT /arch:IA32 /GS-`: **705/705**, 0
  failed. Report:
  `build/strict-xcode-nogs-o1-100110bd-root-impl-20260929.json`, SHA-256
  `17DF93C9FC7EE872D34DA93FE3D0AAEB78F30FB8FFDE92FD6773BF2995763DE7`.
  All 705 listed object paths exist and report exit code 0. The report is from
  08:15 local; the newest candidate source timestamp is 08:13, so no candidate
  source file is newer than this compile.
- Independent ReAgent objective verifier: **705 PASS / 0 FAIL / 0 UNKNOWN**.
  Report: `audit/objective-independent-current-705-20260929-post-100110bd.json`,
  SHA-256 `8C94B706E2B3FEA0E5D43986B921C29002B5835E9F8A1B9C64508F51947E869F`.
- Fresh ReAgent 0.4.0 parity: **705 GREEN / 0 YELLOW / 0 RED**.
  Report: `build/parity-current-705-20260929-post-100110bd.json`, SHA-256
  `B9F5ABD66574AF7B36C03B82042C71D049F367523FF849E26D26BF46B31655CD`.
- Scoped manual parity guard: 705 unique results, exactly 13 scoped
  call-count-only waivers, 100076d0 callback/re-entry warning still present.
  Ghidra-vs-COFF check: 13/13 inspected, zero audit errors. Report:
  `audit/manual-parity-call-counts-current-705-20260929-post-100110bd.json`,
  SHA-256 `6E0A318E0FABA27516705487AE0A16B7EDD4AC0A1CF5F46F8BBBDE527EC76E16`.

The objective/parity reports were generated from the current source tree and
current Ghidra exports. The compile report is tied to the same source state by
its complete 705-object success list and the source timestamp/hash checks
above. All four checks are reproducible, but their scope remains compile or
structural/call-count auditing.

## Boundary — not semantic/game validation

The local ReAgent negative-control audit already demonstrates that a vtable
address replaced with zero can still pass its objective check and show GREEN
parity. Consequently these 705 green/pass totals do not establish 705-way
semantic equivalence. `100076d0` retains the separate OPEN callback/re-entry
finding (`audit/100076d0-mext-owned-texture-lifecycle-2026-09-29.md`). There is
still no production-layout/loadable ImVehFt candidate ASI and no live GTA game
test. No candidate source was modified for this revalidation.
