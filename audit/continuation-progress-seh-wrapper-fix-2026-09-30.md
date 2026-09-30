# Continuation progress: fresh 705-object relocation closure (2026-09-30)

This note records work performed against the fresh strict object set
`build/recheck/strict-xcode-nogs-o1-seh-frame-fix-20260930` after the
`__initptd` SEH-frame correction. The pinned original ASI is an input only; no
production candidate was emitted and no source/ASI was pushed.

## Fresh evidence generated

- Recomputed the CRT bridge/layout against the current 705 objects, current
  420-root census, and current 17-section appended closure. The plan has nine
  caller fixups, a 192-byte/32-entry IAT thunk payload, an 82-byte bridge, and
  15 appended local `.xcode` sections. It places the bridge provisionally at
  `0x1005A9A0`. This is planning evidence only; these fixups are unapplied.
  Report SHA-256:
  `62A7FB8E0EF85119FBA1033F3A02664C75ABDAE00C53B6446A5F6351628626C9`.
- Rebuilt diagnostic relocation inventory and current 705-object symbol
  crosswalk against the successful diagnostic DLL/map. It covers 4,419
  candidate relocations, with zero missing map symbols and two duplicate-map
  ambiguities (both remain explicit in the report).
- Recomputed direct-body closure for the conservative 285 direct / 420
  appended placement: 82 same-object local sections, 155 section relocations,
  and 65 unique unresolved-name/type pairs before target reconciliation.
  The Ghidra/original-image target audit resolved all 130 occurrences across
  69 owner/symbol groups: **0 unresolved**.
- Re-inventoried the 705-object import callsites: 217 REL32 references to 32
  API symbols. The fresh layout plan covers all 217 in-range callsites.
- Re-audited the 824 executable relocation occurrences in the 285 direct
  bodies. **0 unresolved**; all 162 API-plan sites joined exactly. Three
  same-object code symbols still await their final appended-section RVAs.

## Still not established

The above reports do not apply the fixups or serialize a complete image. The
appended-root/local-section externals still need exact final-address,
original-IAT, and provider reconciliation; the extended HIGHLOW table and
payload bytes must be regenerated from this layout. Then the PE emitter must
produce a fresh candidate, which must pass independent PE/startup/relocation
audits and an isolated GTA loader/runtime test with crash capture. The existing
v10 ASI does not include this SEH wrapper fix and is not a validation artifact
for it. No claim of runtime correctness or completed reverse engineering is
made here.

Key reports:

- `audit/crt-original-helper-bridge-seh-wrapper-fix-2026-09-30-fresh.json`
- `audit/candidate-relocation-symbol-targets-seh-wrapper-fix-2026-09-30.json`
- `audit/inplace-candidate-local-section-closure-seh-wrapper-fix-2026-09-30.json`
- `audit/inplace-local-closure-external-targets-seh-wrapper-fix-2026-09-30.json`
- `audit/current-api-callsite-rel32-fixups-seh-wrapper-fix-2026-09-30.json`
- `audit/inplace-direct-executable-targets-seh-wrapper-fix-2026-09-30.json`

## Further same-session progress

- Added `scripts/extract-pinned-base-relocation-directory.py`, a pinned-hash,
  bounds-checked extractor for the original PE's exact `.reloc` directory. It
  recovered and independently checked 4,681 HIGHLOW sites (9,768 input bytes)
  against the original 16,384-byte `.reloc` raw capacity. Original ASI SHA-256
  remained unchanged.
- Reconciled the fresh 285 direct-body relocation set against the original
  `.text` HIGHLOW inventory and serialized a new combined candidate-code
  relocation table: 6,143 sites / 12,896 bytes, round-trip verified and within
  capacity. This table is a generated audit artifact, not installed in a PE.
- The direct local-section extension now plans 82 copied sections, 62 direct
  body-to-section edges, 155 closure relocations, and placement of all three
  previously pending direct code targets. The resulting table model is 6,256
  HIGHLOW sites / 13,140 bytes, still within capacity; all REL32s fit.
- The appended cross-object audit located 29 cross-object references into
  three helper sections (77 bytes), with every helper REL32 in range.
- Refreshed root import/provider/code target classifications. The original-IAT
  name crosswalk matches all 63 referenced imported symbols. Remaining
  appended-root work is explicit: six provider aliases are not yet mapped to
  original addresses, 23 code-target symbols remain outside the resolved
  classes (including imports and the three CRT bridge groups), and all
  appended-root/closure fixup fields still need one complete field-level plan.

Additional reports:

- `audit/original-base-relocation-directory-seh-wrapper-fix-2026-09-30.json`
- `audit/inplace-base-relocation-reconciliation-seh-wrapper-fix-2026-09-30.json`
- `audit/candidate-code-relocation-directory-seh-wrapper-fix-fresh-2026-09-30.json`
- `audit/inplace-local-section-closure-extended-layout-seh-wrapper-fix-2026-09-30.json`
- `audit/appended-cross-object-code-sections-seh-wrapper-fix-2026-09-30.json`
- `audit/appended-thunk-provider-original-addresses-seh-wrapper-fix-2026-09-30.json`
- `audit/appended-thunk-original-import-crosswalk-seh-wrapper-fix-2026-09-30.json`
- `audit/appended-code-target-classes-seh-wrapper-fix-2026-09-30.json`

## Direct-body target conflicts and materialized section artifacts

- Fixed `scripts/audit-inplace-direct-executable-targets.py` so same-object
  code definitions in a distinct COFF section are treated as section-layout
  targets before address/name aliases. It now also consumes the independently
  checked direct function-symbol fixup report and joins exact
  cross-object-local-section targets by owner + field + symbol + relocation
  kind. This prevented two false target conflicts without suppressing genuine
  mismatches: `_FUN_10004ab0_impl` is section-placed, and `_LocaleUpdate` uses
  the hash-verified cross-object helper section at `0x1005BAA1`, not the
  original Ghidra constructor entry `0x10010B1A`.
- Fresh direct executable-target audit: 824/824 target rows classified, zero
  unresolved; 1,577 direct-body COFF fields now have one unambiguous target
  across 285 bodies (805 DIR32, 772 REL32); all REL32 fit. The detailed
  manifest is `audit/direct-body-full-fixup-manifest-seh-wrapper-fix-2026-09-30-v3.json`.
- Materialized a copied `.text` with all 285 bodies and 1,577 preferred-base
  fixups. SHA-256:
  `B0E3C32F268C816D2331AD7125050C322914054B6707355A9ADBBFA8E796B892`.
- Applied the 420 planned entry E9 thunks to a separate copy. Fresh Ghidra
  byte-xref join found zero interior xrefs in those windows; the thunk audit
  found 63 old relocation records intersecting thunk bytes to remove from the
  candidate directory. Output `.text` SHA-256:
  `B3A36BC229A728AA20DE63D167F87D2E8FECBE0860D180072A31D0D3E9275D41`.
- Serialized and round-trip checked the expanded HIGHLOW table: 6,390 unique
  sites, 13,428 bytes, within the original 16,384-byte `.reloc` capacity.
  This is a relocation blob only.

Artifacts:

- `audit/inplace-direct-executable-targets-seh-wrapper-fix-2026-09-30-v3.json`
- `audit/direct-text-seh-wrapper-fix-materialized-2026-09-30-v3.json`
- `audit/direct-text-seh-wrapper-fix-full-2026-09-30-v1.json`
- `audit/extended-relocation-directory-seh-wrapper-fix-2026-09-30-v1.json`

At the time this note was first written, no production candidate PE/ASI had
been emitted from these fresh `.text` and relocation artifacts, and appended
payload/fixup integration plus full PE/startup audits remained. Those static
steps are recorded below. Isolated GTA loader/runtime testing remains undone;
the original ASI remains input-only.

## Experimental PE emitted and static checks (2026-09-30)

- Emitted an isolated experimental PE/ASI candidate from the current
  materialized `.text`, appended payloads, and serialized relocation table:
  `build/pe-layout-probe/ImVehFt-experimental-seh-wrapper-fix-20260930-v1.asi`.
  Candidate SHA-256:
  `306FAD1D39DD12C6FF1E691B8640D7391794341BE117B33EEEEA1D71213343FC`;
  file size 352,768 bytes; 8 PE32 x86 sections; ImageBase `0x10000000`;
  SizeOfImage `0x5E000`.
- Emitter independently reparsed the PE and verified the full 6,390-site
  HIGHLOW set is the union of its independently rebuilt inventories.
- Added and ran `scripts/verify-emitted-candidate-fixups.py`, an independent
  candidate-byte verifier. It checked all 4,810 distinct inventoried direct,
  appended, and direct-local-closure fields: 0 value mismatches; `.text`,
  `.xcode`, `.xrdata`, and `.xdata` bytes match their materialization reports.
- `audit-candidate-startup-contract.py` passed: entrypoint body bytes match the
  original; startup call targets are correct; 82 imported symbols and all
  non-relocation data directories match the original; both moved startup
  functions resolve through the intended appended `.xcode` bodies.
- MSVC `dumpbin /headers` independently reports PE32 x86, 8 sections, entry
  point `0x100111B3`, ImageBase `0x10000000`, and SizeOfImage `0x5E000`.

This is now an emitted **experimental candidate**, not a validated mod release.
No Windows `LoadLibrary`, plugin-loader launch, isolated GTA run, or gameplay
test has been performed. Existing previously named v10/v7 files are older
artifacts and do not validate this fresh candidate. Semantic equivalence of
all 705 routines is still not established.

## Isolated GTA runtime attempt (2026-09-30)

- Launched the experimental v1 candidate from the dedicated clone
  `C:\GTASA-ImVehFt-Test-20260930`, not the user's normal GTA installation.
  The game process exited during startup before reaching the main menu.
- Windows Application Error event 1000 and WER event 1001 record the faulting
  module as the clone's `modloader\my scripts\imvehft-re-test\imvehft.asi`,
  exception `0xC0000409`, and module offset `0x0004BE1B` (report id
  `9fedc4c1-269e-4a1b-a877-c98ec2db4197`). This is a confirmed runtime failure,
  not a successful game test.
- The fault VA maps to the appended `.xcode` region containing the reconstructed
  `___except_handler4`. Exact candidate disassembly at `0x1004BE1B` is
  `mov ecx, dword ptr [esp+0x2c]`; its preceding instruction is the second call
  to `__security_check_cookie` at `0x1004BE16`, and the following instruction
  reads `[ecx+4]`. This proximity alone does **not** establish a cookie failure;
  the reported exception code and instruction do not identify the root cause
  without exception context/registers/stack. The WER-referenced temporary dump
  was absent on first inspection; the archived WER report was preserved.
- Inspected the relevant emitted COFF body: its prologue is `sub esp,18h` and
  saves EBX/EBP/ESI/EDI; at offset `+0x3B`, `[esp+0x2c]` is consistent with the
  first argument's stack slot. That makes an obvious fixed-offset mistake less
  likely, but still cannot explain the `0xC0000409` event. A debugger-level
  first-chance capture is needed before changing the EH4 reconstruction.
- Runtime evidence snapshots are in
  `build/pe-layout-probe/runtime-seh-wrapper-fix-v1-baseline/`, including the
  archived WER report. The isolated clone's active plugin was restored from
  `ImVehFt.asi.pre-experimental-v1-20260930.bak`; its SHA-256 was verified as
  the pinned original `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
  The experimental candidate remains separately available at
  `build/pe-layout-probe/ImVehFt-experimental-seh-wrapper-fix-20260930-v1.asi`.
- Next diagnostic focus is the actual exception context/stack from WinDbg, then
  correlate the active EH4 registration frame with its caller. The broader 35
  `__SEH_prolog4` callsite report remains a secondary audit: only 12/35 frame
  sizes, 7/35 scope aliases, and 10/35 entry-prolog shapes match, so these
  discrepancies still need resolution where they intersect the observed path.

Current conclusion: the 705-object strict compile and binary-layout/fixup
checks passed as static gates, but the emitted experimental image is **not
runtime validated and presently crashes at startup**. Do not label the mod
ready or green until the startup failure is fixed and the isolated game test
reaches the menu and relevant behavior is exercised.

## First-chance dump follow-up (2026-09-30)

- Installed WinDbg and captured a first-chance `0xC0000094` minidump while
  running the experimental candidate in the isolated clone. This is a
  first-chance integer-divide-by-zero event; the game then exits with
  `0xC0000409`. The dump has registers/stack but no exception context, so it
  improves localization but is not a complete crash dump.
- WinDbg maps the exception EIP `0x10010B21` to the clone's `eax.dll`, where
  the instruction is `AAM 0` (divide error). Its stack has return address
  `ImVehFt+0x4D0E5`, in the loader's call to the candidate DLL initializer.
  This establishes the immediate faulting module/instruction and startup
  context; it does not by itself prove why control reached `eax.dll`.
- Correlating the candidate's bytes at that call path reveals a suspicious
  absolute immediate: an instruction in appended `.xcode` loads preferred VA
  `0x10010B1A`, but the emitted base-relocation set has no HIGHLOW entry for
  the immediate field at candidate RVA `0x4CE20`. The candidate is loaded at
  `0x67F80000` while `eax.dll` occupies `0x10000000`, so an unrebased target
  would resolve into `eax.dll`. This is a strong, testable relocation-omission
  hypothesis, not yet a confirmed fix: identify the owning generated/source
  bytes, add the site to the reproducible relocation inventory/emitter, and
  verify the rebased target before rerunning.
- The dump is
  `build/pe-layout-probe/runtime-seh-wrapper-fix-v1-capture-20260930/gta_sa-0xC0000094-firstchance.dmp`;
  WinDbg text is in the adjacent `windbg-dump-analysis3.txt`. The isolated
  clone's active ASI was restored to the pinned original SHA-256 after this
  failed experiment. No GTA process is currently running.
- Test-environment qualification: `C:\GTASA-ImVehFt-Test-20260930` is a
  clone of the user's existing modded GTA installation, not a clean/vanilla
  game. Its `gta_sa.exe` SHA-256 matches the user's install, and it contains
  CLEO, SAMP/Open Multiplayer, ModLoader and many other installed plugins and
  mods. The ModLoader log records the `ImVehFt-RE-Test\ImVehFt.asi` candidate
  as found; it does not establish a clean-room run. Therefore the crash is
  confirmed for that cloned modded setup, but it is not yet an isolated proof
  that the candidate alone causes the failure. Keep this limitation attached
  to all runtime conclusions until retested in a controlled minimal setup.
- WinDbg's GUI dump-analysis window was closed after analysis. The failure
  capture script is retained at `scripts/capture-gta-failfast-dump.ps1`.

Current conclusion remains unchanged: no runtime pass. The relocation theory
must be implemented reproducibly and proven with a subsequent startup test;
the 705 routines are not yet end-to-end validated.
