# Ghidra-driven semantic correction: `__wctomb_s_l` (`0x1001a785`)

Date: 2026-09-27. Reference ImVehFt.asi SHA-256:
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
This is binary/Ghidra/COFF analysis; no PDB or original source was used.

## Finding and correction

Ghidra's export `ghidra_exports/1001a785.json` shows the C-locale test at
`0x1001a7e0`. For `wchar <= 0xff`, the function writes the single byte; a
zero output capacity takes the `EINVAL`/report path at `0x1001a835`, while a
successful conversion cleans up and returns zero. For `wchar > 0xff`, the
branch at `0x1001a7f5` optionally clears the output and reaches `0x1001a80a`:
it writes `EILSEQ` (`0x2a`), rereads errno at `0x1001a815`, performs locale
cleanup if required, and returns. This C-locale error path does **not** call
`FUN_1001189f`.

In the pre-fix candidate (`src/functions/1001a785.cpp`, source SHA-256
`3136d3848c0244b6e97c3cf599921201ebc82e26efac22b66da82b5d2ed1bc4a`), the
`wchar > 0xff` C-locale branch instead set `EINVAL` (`0x22`), called
`FUN_1001189f`, and returned early. In addition, the successful
`WideCharToMultiByte` path with no default-character substitution fell
through to the common `EILSEQ` tail instead of returning success. Both
behavior differences were corrected: the C-locale high-character case now
branches to the shared `EILSEQ` tail, the substituted-character/failure case
uses that same tail, and successful conversion returns zero after cleanup.
The EINVAL insufficient-buffer paths remain distinct.

Backups were created before editing:

- `src/functions/1001a785.cpp.pre-wctomb-semantic-fix-20260927.bak`
- `src/functions/1001a785.cpp.pre-wctomb-flow-refactor-20260927.bak`
- `src/functions/1001a785.cpp.pre-wctomb-illegal-sequence-label-20260927.bak`
- `C:\Users\caner\OneDrive\Documents\ImVehFt\reports\re-agent\manual-parity-checks.md.pre-update-msvc-wctomb-waiver-20260927.bak`

The active candidate SHA-256 is now
`db38f77db44538da215a651d11cf7ea0df84fde150e21a1a5d6c73ff223eafb6` (5,429
bytes). Its manifest row is updated in `audit/source-sha256.csv`.

## Object and independent checks

The final full-set strict build object for this function is
`build/recheck/strict-all-post-wctomb-flowfix-20260927/1001a785.obj`, SHA-256
`7b969c0c7dff95581de35f40b81b18cdf61a32f05fad0d21569657097fca1ecc`. Its
MSVC x86 disassembly shows:

- the `wchar > 0xff` path clears the optional buffer then reaches the shared
  `errno=0x2a; errno-read` block;
- successful `WideCharToMultiByte` with no substitution writes the converted
  count, skips that error block, cleans up, and returns zero;
- insufficient-buffer failure sets `0x22`, calls the error reporter, and
  returns through cleanup.

Fresh validation against the updated 705-source tree:

- MSVC 2022 x86 `/O2 /W4 /WX /MT`: **705/705 passed**, 705 object files;
  `build/strict-all-post-wctomb-flowfix-20260927.json`.
- ReAgent objective verifier: **705 PASS / 0 FAIL / 0 UNKNOWN**; all 705
  recorded source hashes were independently recomputed with zero mismatches;
  `audit/objective-independent-post-wctomb-flowfix-2026-09-27.json`.
- ReAgent 0.4.0 parity: **704 GREEN / 1 YELLOW / 0 RED**; `1001a785` is
  GREEN under the configured static checks; the sole YELLOW remains
  `100076d0`; `audit/parity-independent-post-wctomb-note-refresh-2026-09-27.json`.
- The `1001a785` manual waiver was updated from an inadequate Clang-only
  rationale to current MSVC object evidence. Its 18 CALL instructions are
  five compiler cookie checks plus 13 non-cookie calls; the latter include
  one duplicated `__errno`/reporter pair because MSVC emits separate
  mutually-exclusive EINVAL branches that Ghidra shares. The waiver still
  suppresses only call-count heuristics. The 13-waiver guard passes on the
  fresh parity report.

The fact that ReAgent parity stayed GREEN before this correction illustrates
why parity/objective green is not semantic or runtime proof. No in-game test
or production plugin link was performed; the original ImVehFt project/build
configuration remains unavailable.
