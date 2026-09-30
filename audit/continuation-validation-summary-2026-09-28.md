# 2026-09-28 continuation validation snapshot

This records additional evidence gathered during the active 705-function
reverse-engineering task. It does not redefine completion as a smaller subset.

## Fresh whole-set structural gates

- Strict MSVC x86 C++20 `/O2 /W4 /WX /MT /arch:IA32` compile: **705/705**,
  `build/strict-xcode-continuation-20260928.json`.
- Independent ReAgent objective verifier: **705 PASS / 0 FAIL / 0 UNKNOWN**,
  `audit/objective-independent-continuation-2026-09-28.json`.
- ReAgent **0.4.0** full parity: **705 GREEN / 0 YELLOW / 0 RED**,
  `build/parity-independent-continuation-20260928.json`. The independent
  call-count-waiver guard confirmed all 13 adjudications remain call-count
  only and the `0x100076d0` callback/re-entry limitation remains explicit.
- Compared the fresh strict build against the previous strict build at the
  parsed COFF-section level: **705/705 `.xcode` byte bodies, relocation
  records, and section identities match**. Report:
  `audit/strict-xcode-body-recheck-2026-09-28.json`. COFF container hashes
  differ between runs; this comparison intentionally evaluates function bytes
  and relocation records instead of treating the whole object file as code.

## Candidate evidence

For the 28 body-fit candidates with no COFF relocations and no intersecting
original HIGHLOW field, **15 complete candidate bodies are byte-identical to
the original at the same VA; 13 differ**. See
`audit/reloc-free-original-byte-matches-2026-09-28.md` and its JSON report.

Focused mapped-original-vs-candidate differential harnesses now cover
`0x10003fe0`, `0x100099e0`, `0x10011650` (`_strlen`), `0x10018090`
(`__ValidateImageBase`), `0x100180d0` (`__FindPESection`), `0x1001ad68`
(`_wcslen`), `0x1001ca18`, `0x1001cf82` (`___AdjustPointer`), `0x1001e073`
(`_ValidateRead`), `0x1001fb89` (`___hw_cw_sse2`), and `0x1002044e`
(`___statfp`). Detailed test domains and hashes are recorded in each
function-specific audit note. **Ten of the 13 differing low-relocation
bodies have such targeted behavioral tests; the callback bridge test adds one
targeted test of a byte-identical body.** The remaining differing entries in this subset
are the two stack-probe routines and `___mtold12`.

## Still not achieved

- The original ImVehFt source/build project was not found in the supplied
  `.ImVehFt` folder; the named old SDK download path is absent. A historical
  SDK tree exists, but it does not supply the missing ImVehFt project.
- There is still no reconstructed, loadable full-mod `.asi`; the function
  probes are disposable `.bin` copies and must not be installed as mods.
- No GTA process was running during this check; no gameplay validation has
  passed. Whole-set compile/objective/parity greens remain structural evidence,
  not semantic equivalence or runtime proof.
