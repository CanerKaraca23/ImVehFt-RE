# Installed-mod RenderWare callback audit

Date: 2026-09-27. Purpose: narrow the unresolved callback/re-entry concern for
`100076d0` by examining local ASI files outside backup-named folders. Nothing
was executed or loaded in GTA. Presence under `modloader` does not prove that
ModLoader enabled a file for the current session.

## Inventory and method

`python scripts/audit-active-asi-rw-registration.py` initially scanned 38 ASI candidates
under the local GTA San Andreas directory, excluding `_Backup` and
`.Backup*` paths. The scanner was subsequently expanded to all ASI/DLL candidates;
the fresh 2026-09-27 scan covered 64 modules (including 26 DLLs) and found no
additional wrapper-pattern hits in the DLLs. The known hits remain in six ASIs.
It also checked for direct `rel32` CALL/JMPs to the API addresses. No direct branch to
an API address was found. The scanner also matched direct CALLs to three
same-module thunks in SkyGfx Deferred, SkyGfx Remix, and ModelExtras; those
call-site contexts expose their registration arguments in the output. These
are byte-pattern hits, not by themselves proof of runtime-active registration.
The historical Plugin-SDK header maps `0x7F3BB0` to
`RwTextureRegisterPlugin`, `0x7FB0B0` to `RwRasterRegisterPlugin`, and
`0x7F1260` to `RwFrameRegisterPlugin` (`_sdk_history/snapshot-2014-04-27/src/sdk/game_sa/RenderWare.h`).
No `0x7FB0B0` occurrence was found in the 64-file ASI/DLL byte scan. A fresh
full-analysis xref pass over `gta_sa.exe` found one direct `0x7FB0B0` caller,
`FUN_004c9ab0`, which registers the game raster plugin; its callback behavior
is classified in [`100076d0-call-target-classification-2026-09-27.md`](100076d0-call-target-classification-2026-09-27.md).

| ASI | Wrapper hit / registration evidence | Callback findings |
| --- | --- | --- |
| `.ImVehFt/ImVehFt.asi` | `RwTextureRegisterPlugin` indirect call at `0x1000187E`; SHA-256 matches the reference binary. The actual code sequence begins at `0x10001850`; `0x10001863` is an interior address, not a function entry. | MEXT args include ctor `0x10001AD0`, dtor `0x10001B00`, copy `0x10001B30`. The installed ImVehFt log records `Attaching texture maps plugin...` and `Finished (96).`, matching this binary's logger around the registration call. Log timestamp is 2026-09-11 20:42:40, so it proves historical execution evidence, not execution in the latest session or current live registry state. The dtor can call `RwTextureDestroy`; keep the runtime/re-entry caveat. See `rw-registry-trace-2026-09-27.md`. |
| `.Proper Shaders/ProperShaders.asi` | Ghidra registration call at `0x10085805`; SHA-256 `279FE40E1EE60D3E23177100A504AFFD9EB711E8521A097E1A375AE31978813D`. | The registered texture-plugin dtor/copy arguments are null; the constructor only clears its plugin slot. Registration execution remains unproven. Existing bounded evidence: `propershaders-rw-register-2026-09-27.csv` and `propershaders-rw-functions-2026-09-27.c`. |
| `.SkyGfx Deferred/skygfx.asi` | Wrapper thunk at `0x100544A0`; direct relative call reaches the thunk at `0x1003DD2B`; SHA-256 `F395C5189A069D545BBA0F40F1925A366677ECF5096E98F3AD7BF07397872B4C`. | The call setup passes constructor `0x10054480`, dtor `0`, copy `0`. Ghidra bounded the thunk as a tail jump to `0x7F3BB0`; the call-argument bytes are recorded in this report's scanner output context. |
| `SkyGfx Remix/skygfx.asi` | Wrapper thunk at `0x100187A0`; direct relative call reaches it at `0x10017C00`; SHA-256 `1F367960A2C62A518EA4E7586D9673C70E12C1A74C8C9E3994E5C8044A1B4EE7`. | Call setup passes constructor `0x10018780`, dtor `0`, copy `0`. This is a separate installed file; which SkyGfx copy is selected by ModLoader was not checked. |
| `VehFuncs/VehFuncs.asi` | `RwFrameRegisterPlugin` indirect call in `FUN_1002E600`; SHA-256 `A40B00B71Cbd6CAEFde6731823463CC2C247Dfe1A5B4d1448585570B8568E3BF` (case-insensitive). | Registration uses ctor `0x10022420`, dtor `0x10022450`, copy `0x10022480`. Ghidra bounded the dtor chain `10022450 -> 100513EF -> 100513EA -> HeapFree`; no texture destruction or direct ImVehFt writer call appears in that path. See `active-asi-rw-vehfuncs-callbacks-2026-09-27.c` and `active-asi-rw-vehfuncs-destroy-2026-09-27.c`. |
| `ModelExtras/ModelExtras.asi` | `RwFrameRegisterPlugin` thunk at `0x10008DE0`, reached by direct call at `0x100AEEC6`; SHA-256 `61A287C0A696E91359C3E93D66D3CE55FFA53A760E0E9EEB0D1EFEE87DCD297A`. | Setup passes ctor `0x100AECA0`, dtor `0x100AED60`, copy `0x100AEBB0`. Bounded Ghidra follows the dtor through `0x100BAA3D` to `HeapFree`; no texture destruction or direct ImVehFt writer call appears. See `active-asi-rw-modelextras-dtor-2026-09-27.c` and `active-asi-rw-modelextras-free2-2026-09-27.c`. |

The raw scan's full paths, hit offsets, mapped immediate VAs, section names,
and surrounding bytes are reproducible from the scanner. Ghidra callback
decompilations are bounded CFGs, not original source or complete call graphs.
PDB analyzers were explicitly disabled for the later Ghidra checks by
`scripts/GhidraDisablePdbAnalyzers.java`; the work is binary-only.

## Game executable's own texture-registry callback

The installed `gta_sa.exe` Ghidra trace in
[`rw-registration-callers-2026-09-27.c`](rw-registration-callers-2026-09-27.c)
finds one `RwTextureRegisterPlugin` registration in `FUN_00748F70`: size `1`,
plugin ID `0x127`, constructor `0x749020`, destructor `0x749030`, and copy
callback `0x749040`. The bounded callback decompilation in
[`rw-registered-callbacks-2026-09-27.c`](rw-registered-callbacks-2026-09-27.c)
shows the destructor simply returns its data argument; it does not call the
ImVehFt writer or re-enter vehicle processing. `RwTextureDestroy` can also
destroy an attached raster via `0x7FB020`, so the raster registry is reachable
on this path and must be considered separately.

## Effect on the `100076d0` warning

The specific concern was whether texture destruction inside `100076d0` could
dispatch an installed plugin destructor that re-enters the vehicle path and
changes `DAT_1003C1FC` from null to non-null before the later stack-slot read.
Among the scanned texture-registration sites, the two SkyGfx call setups and
the ProperShaders registration have null destructors. GTA's identified
texture-plugin destructor only returns its argument. ImVehFt's own non-null
texture destructor is passed by a registration path installed by DllMain
through the internal callback dispatcher; execution is corroborated by the
historical ImVehFt log (`Finished (96).`, 2026-09-11). The latest live
registry state is not established. VehFuncs and ModelExtras use the
separate frame-plugin registry and their bounded destructors free heap blocks;
they are not evidence of texture-destroy callback re-entry.

This narrows the known local-mod callback route but does **not** prove that
`DAT_1003C1FC` cannot change during the function. ModLoader enablement, the
live RenderWare registry, all other code paths/modules, callback side effects,
and runtime re-entry were not observed. Keep `100076d0` YELLOW; do not alter
its initializer or promote the parity result to a semantic pass from this
static evidence. A follow-up traced the raster callback chain; see
[`100076d0-call-target-classification-2026-09-27.md`](100076d0-call-target-classification-2026-09-27.md).
