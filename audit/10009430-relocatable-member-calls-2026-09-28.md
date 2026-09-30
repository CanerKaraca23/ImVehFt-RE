# Relocatable calls to `FUN_10009430` (2026-09-28)

## Change

Ghidra exports for `0x1000c420` and `0x1000cf80` show direct calls at
`0x1000c45b` and `0x1000cfbb` to `0x10009430`. The target export identifies
`FUN_10009430` as `__thiscall(void*, char)`; the candidate definition is the
member `FUN_10009430_this::FUN_10009430(char)`. Both callers previously cast
the fixed preferred VA `0x10009430` to a function pointer. They now cast the
existing global-state address to `FUN_10009430_this*` and call that member,
which keeps the `this`/ECX and one-byte argument ABI while emitting a normal
COFF reference to the target method.

Backups made before editing:

- `src/functions/1000c420.cpp.pre-relocatable-call-10009430-20260928.bak`
- `src/functions/1000cf80.cpp.pre-relocatable-call-10009430-20260928.bak`

## Verification

- Fresh strict MSVC x86 compile: **705/705** (`build/strict-all-relocatable-10009430-20260928.json`).
- `dumpbin /symbols` for both callers shows undefined external
  `?FUN_10009430@FUN_10009430_this@@QAEHD@Z`; the absolute call literal is
  gone from those two sources.
- ReAgent parity: **705 GREEN / 0 YELLOW / 0 RED**
  (`build/parity-post-relocatable-10009430-20260928.json`).
- Independent structural objective: **705 PASS / 0 FAIL / 0 UNKNOWN**
  (`audit/objective-post-relocatable-10009430-2026-09-28.json`).
- Relocation provider verifies **1,521/1,521**, zero mismatches
  (`build/recheck/reloc-aware-dat-provider-relocatable-10009430-20260928.obj`).
- Normal link exits 0 with no diagnostics using all **705 current candidate
  objects**; output remains a diagnostic DLL, not a production/game-testable
  ASI (`build/link-probe/strict-704-historical-sdk/ImVehFt-relocatable-10009430-link-not-ASI.dll`).

The literal inventory was refreshed after this edit:
`audit/candidate-internal-image-address-literals-v8-2026-09-28.csv/.json` now
reports 79 occurrences, 62 unique original `.text` VAs, and 27 exact candidate
function-entry addresses (down from 81/63/28 in v7). The 35 non-entry addresses
still require per-use classification. None of these static checks establishes
runtime or in-game equivalence.
