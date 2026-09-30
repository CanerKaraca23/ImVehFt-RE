# Live source revalidation — 2026-09-29

This audit reruns the whole-set structural gates and selected original-binary
differentials against the current working tree. It does not convert structural
green results into whole-program semantic or gameplay proof.

## Whole-set checks

- The address manifest contains 705 source rows. Recomputing SHA-256 for every
  listed candidate source found **0 missing files and 0 hash mismatches**.
- Fresh MSVC 2022 Build Tools 14.44.35207 x86 build, `/O1 /W4 /WX /MT
  /arch:IA32 /GS-`: **705/705** compiled; 0 failed. Report:
  `build/strict-live-rerun-20260929.json` (SHA-256
  `220533C127B4E5917716CD094C46CE9E55CC135AC6FA3326DE95559D35AE74BA`).
- Fresh independent ReAgent objective pass: **705 PASS / 0 FAIL / 0 UNKNOWN**.
  Report: `audit/objective-live-rerun-2026-09-29.json`.
- Fresh ReAgent 0.4.0 parity: **705 GREEN / 0 YELLOW / 0 RED**. Report:
  `build/parity-live-rerun-2026-09-29.json`.

The objective and parity tools analyze candidate structure; neither proves
behavioral equivalence. The strict build proves these translation units compile
under the listed profile, not that a production module links or runs.

## Focused original-binary differentials

All use the original installed ASI with SHA-256
`409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

- `0x100076d0`: linked the freshly rebuilt strict `/O1 /GS-` object
  (`build/recheck/strict-live-rerun-20260929/100076d0.obj`, SHA-256
  `B45E3E21F5A07A809504AE62D424922E279BC18DEDA96F39443DA42C8D059139`)
  into the existing x86 harness. **10/10 fresh processes passed**. The harness
  source is unchanged from the audited 350-pair bounded selector/damaged-lights/
  controlled-reentry suite (SHA-256 `D228DCE93A3A6B03BF40C914B2852BEECFDA558812B4C50DA49DA153BE75D114`).
  Executable: `build/abi-harness/100076d0-model-info-harness-livecurrent-20260929.exe`
  (SHA-256 `1AED8913F7E10A36962514E7C681F25C209551730C79BD3DE01EAD211771AF11`).
  This continues to use controlled fixtures and does not prove live RenderWare
  plugin/driver callback behavior or close the callback/re-entry risk.
- `0x10007030`: linked the freshly rebuilt strict `/O1 /GS-` object
  (`build/recheck/strict-live-rerun-20260929/10007030.obj`, SHA-256
  `EE002D31603C9B2F94AA9D8C6357AC23BBB8FCDA2D7D096636A5B8F80A62EF14`)
  into a fresh differential harness. Direct corona, alpha-above-threshold,
  alpha-below-threshold, and alpha-suppressed cases all matched (**4/4**),
  including the reviewed transform ABI and stack aliases. GTA matrix/transform/
  corona helpers remain controlled stubs; this is not a live effects test.
- `0x1001c60e`: reran the mapped-original harness against the latest diagnostic
  full-set DLL. It again reports **200,480/200,480** normal-path and
  **16,384/16,384** exception-tail bit-exact results across the documented
  floating-point modes. Diagnostic DLL:
  `build/link-probe/entry-m80-reloc-nogs-o1-20260929/ImVehFt-m80-reloc-probe-not-ASI.dll`
  (SHA-256 `6F9C3374844B0A18CB29A90CF769A91E3BE9995170B2774BC9F1160B9C924646`).
  The harness manually resolves imports and does not run DLL entrypoints/CRT
  startup.

## Remaining blockers

The diagnostic DLL is **not a production `.asi`**. No current ImVehFt source
project/build manifest has been found; the available 2014 SDK snapshot does not
establish the original project's exact build recipe. PE section/data/base
relocation layout, startup and installer integration, live GTA/RenderWare
behavior, and gameplay validation remain open. The original installed ASI was
not modified. Do not describe 705/705 structural gates as 705/705 runtime-
verified functions.
