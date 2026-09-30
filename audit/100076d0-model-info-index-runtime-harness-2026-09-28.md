# `100076d0` model-info index: isolated x86 execution

Date: 2026-09-28. Reference ImVehFt image SHA-256:
`409F0DF7AE579841DB05C3EC6AD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Result

The fresh MSVC x86 COFF object for `src/functions/100076d0.cpp` was linked
directly into `build/abi-harness/100076d0-model-info-live-20260928.exe` and
executed in a PE32 harness. Two control-flow routes were exercised: generic
model context (`DAT_1003c1fc == 0`) and vehicle context with a synthetic vehicle
pool/record (`DAT_1003c1fc != 0`). For each route all 16 selectors `0xFF`
through `0xF0` selected indices 0 through 15. Every array item pointed to a
distinct synthetic texture record with distinct `+8` word and `+10` byte
values; the candidate copied the matching pair. The harness checked the
returned pointer, route-specific context-call counts, write-slot address and
saved value, expected cursor advance (one slot for generic, two for vehicle),
and the vehicle path's second color slot. A third case selected the
`vehiclegrunge256` callback branch, checked both callback cdecl arguments,
then re-entered the candidate exactly once from the synthetic callback; both
nested and outer calls completed their expected model-info data/slot checks.
The executable returned zero in 10 fresh-process repetitions, each covering 32
route/selector cases plus the callback/re-entry case.

### Additional lookup-branch execution (2026-09-28)

The reproduction harness was extended, without changing the candidate source
or COFF, to execute the nonzero `vehiclelights` lookup followed by the
`vehiclelights_dam` replacement path. It asserts model-id and lookup-name
order, the emitted two write-slot records/cursor, and installation of the
synthetic replacement pointer. A fresh MSVC x86 PE32 harness passed **10/10**
processes using the same candidate object SHA recorded below. Executable:
`build/abi-harness/100076d0-damaged-lights-harness-20260928.exe`, SHA-256
`1A9103309A819016F71BEEF00AB029AFD8D1A0A92F3E3BD85E26BD49553FB2F3`.
This extends only the isolated candidate-object test; the lookup routine and
returned texture remain deterministic synthetic values.

### Callback-time context flip and entry-slot preservation (2026-09-28)

A second controlled edge case sets `DAT_1003c1fc` to zero at function entry,
seeds the target entry frame's `[EBP-8]` with a valid synthetic vehicle-record
pointer from a naked x86 caller, and has the texture callback change the global
to nonzero. Execution then reaches the palette branch and asserts that it reads
the seeded slot's custom palette data. This checks the candidate's raw
conditional stack-slot bridge and late global reread for this deliberately
constructed scenario. It does not prove that GTA's live RenderWare/COM callback
changes this global or that the original binary behaves identically on a live
driver path.

Fresh MSVC x86 PE32 harness: **10/10** processes passed. Executable:
`build/abi-harness/100076d0-stack-slot-flip-final-20260928.exe`, SHA-256
`DEAF2B9D514C3504010ADF1CC872107A2F38A4D7331F201C298E6F2F9C6379E8`.
Candidate object SHA-256 is unchanged at
`A227D6163003883A003FD20606F571E8482552252F8AB261C7903BA116DDCB4E`.

Inputs used model id 1, a zero texture-id lookup, valid synthetic
context/model-info and vehicle-pool structures, and item flag `+9 == 0` so the
function returned immediately after the indexed data transfer. In the vehicle
route, a synthetic texture name and lookup cell route execution through the
vehicle-specific model-info branch. The texture lookup function stub was not
invoked.

## Address redirection and integrity

The candidate directly references GTA fixed VAs `0x00C8800C`, `0x00B74494`,
`0x00B4E47C`, `0x00B4E68C`, `0x00B4E690`, the texture lookup routine at
`0x007F39F0`, and the texture callback at `0x0074DBC0`.
Windows had already committed private memory over the required low-address
ranges in the harness process, so the harness does not overwrite those ranges.
Instead, after linking the actual candidate object, the temporary PE32 test
image redirects exact 32-bit occurrences in its executable section to
synthetic test globals and stubs. In address order `0x007F39F0`, `0x00C8800C`,
`0x00B74494`, `0x0074DBC0`, `0x00B4E47C`, `0x00B4E68C`, `0x00B4E690`, the
scanner requires occurrence counts `4, 2, 4, 5, 4, 3, 2` and fails closed on
any count mismatch. These are test-image-only mutations; neither candidate
source nor the saved COFF object is patched. The two model-info selector routes
use zero texture id; the additional damaged-lights case uses deterministic
lookup results, and the grunge callback is replaced with a deterministic test
callback.

- Candidate COFF: `build/recheck/strict-all-live-20260928-2/100076d0.obj`
  SHA-256 `A227D6163003883A003FD20606F571E8482552252F8AB261C7903BA116DDCB4E`.
- Test image: PE32 / x86,
  `build/abi-harness/100076d0-model-info-harness-20260928-101119-574.exe`
  SHA-256 `3A189556011B3FEC5FC83B958798119EDFB5DCC30CD5FAE0974D0DC44127E130`.
- Harness source: `tests/runtime_100076d0_model_info_harness.cpp`.
- Reproduction script: `scripts/test-100076d0-model-info-harness.ps1`.
- Build: MSVC x86, `/std:c++20 /O2 /W4 /WX /MT /GS`; linked the candidate COFF
  object directly.
- Repetitions: 10/10 fresh processes passed; each process exercises both routes
  across all 16 selector/index cases and the controlled callback/re-entry case.

## Limits

This is bounded execution evidence for the compiled candidate's generic and
vehicle-context model-info selector paths, indexed address calculation, data
transfer, write slots, and return on synthetic state. It is not an
unmodified-address execution of the original object: the test PE redirects
fixed-address operands. Only one synthetic nonzero texture-lookup branch is
covered; this does not validate real GTA texture lookup results, live
vehicle-pool state, the real RenderWare callback, real callback re-entry, the
original GTA process, installer patches, or gameplay. The synthetic callback
checks the candidate's cdecl call setup and bounded nested invocation only.
The latest saved full ReAgent parity
report (`build/parity-live-20260928-1.json`, 2026-09-28 08:56) reports **705
GREEN / 0 YELLOW / 0 RED**; older README/status notes saying 704/1 are stale for
that run. A newer same-tree strict/objective rerun is recorded in
`audit/fresh-705-validation-rerun-2026-09-28-2.md`. The independent
callback/re-entry semantic risk for `100076d0`
remains an open audit item despite the ReAgent GREEN result. This does not
validate all 705 functions or produce a loadable `.asi`.
