# Installed-game evidence for ImVehFt and callback peers

Date checked: 2026-09-28. Read-only inspection; no game or mod files changed.

## Hash and process observations

- Source ASI `C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi` and
  installed modloader copy
  `C:\Users\caner\OneDrive\Documents\GTA San Andreas\modloader\My Scripts\.ImVehFt\ImVehFt.asi`
  have the same SHA-256:
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.
- No `gta_sa.exe` process was present during this inspection. This is not a
  current gameplay/runtime validation.
- Installed `ImVehFt.log` is dated 2026-09-11 20:42:40 (SHA-256
  `BFDD35D890CC168BE9A4A6D564E211187E551F197BCC50390B766B563DD15BCC`).
  It reports version 2.1.1, successful texture-map setup (`Finished (96)`),
  memory patches, and vehicle-plugin registration. This is useful historical
  evidence that this binary completed those initialization steps in a prior
  run; it is not evidence of a current run or of the reconstructed candidate.

## Modloader trace limits

- `modloader.log` is dated 2026-09-28 01:38:52 (SHA-256
  `8292C035B0C43470ADBB5201F44B06F1458747A727DDBF5A70D093488AD2C7A9`).
- Its installation trace includes `ModelExtras\ModelExtras.asi`,
  `SkyGfx Remix\skygfx.asi`, and `VehFuncs\VehFuncs.asi`; it reports their
  imports patched using the Legacy method. This is evidence the loader handled
  those modules in that session, not proof that each callback ran.
- No `ImVehFt` string occurs in that trace despite the matching installed file
  and older ImVehFt runtime log. Do not infer from that absence whether the
  module was or was not loaded; the log's coverage/verbosity for that folder is
  not established.
- The trace is not sufficient to reconstruct live RenderWare registry values,
  destructor callback order, or callback-time re-entry for candidate
  `0x100076d0`. Those remain open semantic/runtime questions.

## Registration-wrapper byte-pattern scan

The existing read-only `scripts/audit-active-asi-rw-registration.py` was rerun
against the installed game root. It scanned 64 ASI/DLL candidates. This
scanner recognizes wrapper-address immediates and rel32 calls to known thunks;
it does not establish reachability, execution, successful registration, or
registration order. Ghidra confirmation is still needed for each code path.

Relevant hits:

| Module | Wrapper | Hit VA(s) | Image SHA-256 prefix |
|---|---|---|---|
| `.ImVehFt\ImVehFt.asi` | `RwTextureRegisterPlugin` | `0x1000187a` | `409f0df7ae57` |
| `.Proper Shaders\ProperShaders.asi` | `RwTextureRegisterPlugin` | `0x10085801` | `279fe40e1ee6` |
| `.SkyGfx Deferred\skygfx.asi` | `RwTextureRegisterPlugin` | `0x100544a1`, thunk call at `0x1003dd2b` | `f395c5189a06` |
| `SkyGfx Remix\skygfx.asi` | `RwTextureRegisterPlugin` | `0x100187a1`, thunk call at `0x10017c00` | `1f367960a2c6` |
| `ModelExtras\ModelExtras.asi` | `RwFrameRegisterPlugin` | `0x10008f74`, thunk call at `0x100bfbf6` | `293227082c8d` |
| `VehFuncs\VehFuncs.asi` | `RwFrameRegisterPlugin` | `0x1002e617` | `a40b00b71cbd` |

For ModelExtras, SkyGfx Remix, and VehFuncs, the modloader trace independently
records installation and import patching during its 2026-09-28 session. The
two texture-registration wrapper patterns in ImVehFt and Proper Shaders do
not by themselves prove those plugins were loaded in that session. Plugin
registration conflicts/order remain hypotheses until the callsites and
RenderWare registry are confirmed in a controlled runtime.

## Consequence

The installed original binary is byte-identical to the hash-pinned source ASI,
and there is historical initialization evidence for its version-2.1.1 runtime.
No evidence here upgrades any of the 705 candidate results to game-validated
status. A future controlled test must use a separate, backed-up test install
and produce a fresh log attributable to that exact test binary.
