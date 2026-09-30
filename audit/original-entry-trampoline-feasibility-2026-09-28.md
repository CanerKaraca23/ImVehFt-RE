# Original-entry trampoline feasibility (2026-09-28)

Reproducible command: `python scripts/audit-entry-trampoline-feasibility.py`.
The machine-readable result is
[`entry-trampoline-feasibility-2026-09-28.json`](entry-trampoline-feasibility-2026-09-28.json).

The audit matched all **705** reference function entries to executable body
targets in the existing diagnostic link map. **429** candidate bodies fit
directly in their bounded entry gaps (the final body fits the remaining
reference `.text` tail); **275** require a five-byte x86 `E9 rel32` entry
thunk. Every such gap is at least **8 bytes**, every target is executable,
and all 275 displacements fit signed 32-bit rel32. This is an address
placement feasibility result, not a newly emitted PE or an ASI.

The script checks the existing diagnostic DLL/map and the original ASI. It does
not generate entry thunks, restore `.rdata`/`.data` layout or base relocations,
settle CRT/loader startup and installer interactions, or prove GTA runtime
behavior. A 5-byte thunk overwrites original entry instructions, so semantic
safety still depends on whole-function correctness and consistent relocation
of all intra-image references. No game-loadable output is claimed.
