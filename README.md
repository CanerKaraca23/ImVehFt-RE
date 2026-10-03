# ImVehFt-RE

ImVehFt-RE is an ongoing reverse-engineering project for the 32-bit Windows
`ImVehFt.asi` plugin used with Grand Theft Auto: San Andreas. It contains
address-mapped C++ reconstructions of functions studied from the original
binary, along with the analysis tools and evidence used to review them.

This is a reconstruction, not the original author's source code or build
project. The aim is to make the recovered behavior easier to inspect, compare,
and validate—not to claim that the code is identical to the source originally
written by the mod's author.

## Project status

The repository contains 705 address-named function translation units. The
latest recorded source checks (September 30, 2026) report a successful strict
MSVC x86 compile for all 705 files and passing structural comparison checks.
Those results establish that the sources compile and satisfy the checks used;
they do not prove complete behavioral equivalence.

A production-ready `.asi` has not been validated. Final executable layout,
relocation, startup and plugin-loader integration still need verification, and
the reconstructed plugin has not passed testing in a clean GTA installation.
Treat generated binaries as experimental until those checks are complete.

## Repository contents

- `src/functions/` — the address-mapped C++ function reconstructions.
- `audit/` — Ghidra-derived notes, comparison results, hashes, and known
  limitations.
- `scripts/` — utilities for compiling, inspecting, and checking the
  reconstruction.
- `tests/` — focused checks and harnesses for selected functions and layouts.
- `docs/README-HISTORY-2026-10-03.md` — archived chronological development
  notes retained from the former README.

For the current technical state, start with [`audit/status.json`](audit/status.json).
For the source-to-address mapping, see
[`audit/function-name-map.csv`](audit/function-name-map.csv).

## Build note

The checked-in sources can be compiled as x86 translation units with Visual
Studio 2022 Build Tools and the Windows SDK. A successful object build is not
the same as producing a correctly laid-out, loadable `.asi`; do not install an
experimental output into a regular game setup.

## Rights and attribution

This repository does not include the original ImVehFt source or a confirmed
license for redistributing reconstructed code or binaries. The original mod's
author retains any rights they hold. Check the author's terms and applicable
law before redistributing or shipping this work.
