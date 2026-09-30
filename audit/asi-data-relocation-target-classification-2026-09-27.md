# Original `.data` relocation target classification

Date: 2026-09-27. This follows the 274 x86 `HIGHLOW` relocation sites in the
original ImVehFt ASI `.data` section and classifies their stored VAs against
the original PE section map. The reproducible raw relocation inventory is
[`asi-base-relocations-2026-09-27.json`](asi-base-relocations-2026-09-27.json),
produced by [`inspect-asi-base-relocations.py`](../scripts/inspect-asi-base-relocations.py).

## Target distribution

| Stored target section | Relocation sites | Unique target VAs |
|---|---:|---:|
| `.rdata` | 234 | 143 |
| `.data` | 30 | 10 |
| `.text` | 10 | 1 |

All 274 stored values point inside the original ASI image. A relocated clone of
`.data` cannot keep these original pointer values verbatim: `.rdata` targets,
internal `.data` targets, and code targets must resolve to corresponding new
image addresses or to explicitly preserved fixed-address mappings.

## The single code target

All ten `.text` relocations are entries at `0x10029D40..0x10029D64` (stride 4)
whose stored value is `0x1001AF2B`. Fresh read-only Ghidra xrefs/listing show
the code at `0x1001AF2B` is a four-instruction helper outside any defined
Ghidra function: `PUSH 2; CALL 0x10012E01; POP ECX; RET`. The call target
`0x10012E01` is candidate `__amsg_exit(int)`, whose source unit exists as
`src/functions/10012e01.cpp`. Immediately afterward, `0x1001AF34` is the
separately defined `__chsize_nolock` candidate.

## CRT startup ordering for the fallback table

A read-only byte probe of the exact target and the existing Ghidra exports
establish the normal process-attach initialization sequence:

1. The PE entrypoint is `0x100111B3` (`entry`), which forwards process attach
   to `___DllMainCRTStartup` at `0x100110BD`.
2. On process attach, `___DllMainCRTStartup` invokes `__CRT_INIT@12` at
   `0x10010F59` before calling ImVehFt's `FUN_10001DB0` DllMain.
3. `__CRT_INIT@12` initializes the CRT and calls `__cinit` at `0x10012C05`.
   Its `PTR___fpmath` slot at `0x10025004` contains `0x1001B318`; the slot is
   in `.rdata` (RVA `0x25004`, section characteristics `0x40000040`, no write
   bit). Ghidra's `__IsNonwritableInCurrentImage` returns true for this
   section, so `__cinit` calls `__fpmath` before `__initp_misc_cfltcvt_tab`.
4. `__fpmath` calls `__cfltcvt_init` at `0x1001B2B8`, which writes all ten
   CRT function pointers to `0x10029D40..0x10029D64`. `__cinit` then encodes
   those entries with `EncodePointer` before running the initializer arrays.

Thus the exact binary's ordinary loader process-attach path replaces the ten
on-disk `0x1001AF2B` fallback pointers before ImVehFt's DllMain runs. This
strongly narrows the helper's role to pre-initialization fallback rather than
an ordinary plugin function, but does not prove CRT code cannot consult the
table earlier during its own initialization. It must not be counted among the
705 application candidates. This does **not** solve relocation of the 274
`.data` pointers for a rebuilt image, prove behavior if CRT initialization is
bypassed/fails, or provide a production link/game test. Runtime readiness
remains unverified.

A callee-graph reachability audit from all Ghidra-exported CRT attach
initialization and failure-cleanup roots traversed 99 exported functions,
found no unexported non-external callee addresses, and found no resolved callee
path to `__input_l` (`0x100119F1`) or `__output_l` (`0x100154DC`) before
`__cinit`. The graph includes computed-call targets Ghidra resolves, not only
direct calls. This narrows the chance that those table consumers use the
fallback during CRT setup, but cannot rule out unresolved indirect calls,
callbacks, or unexported code. Reproduce with `py -3.13
scripts/audit-crt-preinit-direct-calls.py`; results are in
`asi-crt-preinit-direct-call-audit-2026-09-27.json`.

Evidence: read-only probe `asi-crt-fpmath-pointer-2026-09-27.csv`; Ghidra
exports `100111b3.json`, `100110bd.json`, `10010f59.json`, `10012c05.json`,
`10018120.json`, `10017a33.json`, and `1001b318.json`; PE entrypoint and
`.rdata` characteristics parsed from the original ASI. The probe did not
modify the Ghidra project or candidate sources.

Ghidra xrefs from the fallback helper include the 10 `.data` entries and code
references from candidate CRT routines `__output_l` (`0x100154DC`), `__input_l`
(`0x100119F1`), and `__initp_misc_cfltcvt_tab` (`0x10017A33`). The current
candidate set represents the table and startup behavior: `1001b2b8.cpp`
initializes all ten entries to CRT routines, `10017a33.cpp` encodes the table,
and related functions decode selected entries. The standard process-attach
sequence is described below; nonstandard startup/failure paths are outside
that proof.

## Build implication

The fallback helper at `0x1001AF2B` is not one of the 705 source translation
units or the 12 already recovered game hook shims. A new image must either
provide this helper at a valid relocated address and initialize all ten table
entries consistently, or prove from complete startup control flow that the
fallback is unreachable before `__cfltcvt_init` replaces the entries. The
remaining 264 `.data` relocations also point to 153 distinct `.rdata`/`.data`
targets; their remapping is not covered by the 139 hook-shim fixups. No source
or PE image was changed during this classification.

Evidence files:

- [`asi-data-relocation-code-xref-2026-09-27.csv`](asi-data-relocation-code-xref-2026-09-27.csv)
- [`asi-data-relocation-target-owner-2026-09-27.csv`](asi-data-relocation-target-owner-2026-09-27.csv)
- [`asi-reloc-target-context-2026-09-27.txt`](asi-reloc-target-context-2026-09-27.txt)
- `src/functions/1001b2b8.cpp`, `src/functions/10017a33.cpp`, `src/functions/100119f1.cpp`, and `src/functions/100154dc.cpp`
