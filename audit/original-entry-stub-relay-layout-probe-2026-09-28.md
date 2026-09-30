# Original-entry stub and short-relay layout probe

Date: 2026-09-28. This read-only calculation follows the candidate COMDAT
collision audit. It tests only whether the 704 entries with a known next-entry
boundary can reserve a non-overlapping entry stub and, for sub-five-byte
entry gaps, a nearby short-jump relay. It does not edit a PE or prove that the
original addresses are safe to overwrite in an eventual image.

## Result

The fit report has 705 entries, but its final entry has no next-entry boundary
and is excluded from this bounded interval allocation. Of the other 704:

- 702 entries have at least five bytes before the next mapped entry and can
  reserve a five-byte `E9 rel32` stub in this model.
- Two entries are only three bytes apart and cannot both reserve five-byte
  stubs: `0x10018F94` / `0x10018F97`, and `0x1002044B` / `0x1002044E`.
- For each pair, using two-byte `EB rel8` entry stubs permits a distinct
  five-byte relay at `0x10018F9C` and `0x10020453`, respectively. Each relay
  is eight bytes after the first entry; both short jumps have positive
  displacements within signed rel8 range. The relay bytes do not intersect
  any modeled entry stub, and the two relay slots are disjoint.
- The allocation leaves 677 other modeled gaps at least five bytes long.

This resolves the *local stub-overlap issue* for those two close pairs under
the modeled layout. It does not resolve the main current-image collision:
candidate COMDAT bodies must be placed in a separate, collision-free code
region before these entry stubs can safely occupy the original entry area.

## Important limits / next layout gates

The probe is based on next mapped entry addresses, not proven original function
extents. The highest mapped entry lacks a next-entry boundary, so its stub
slot still needs an independently justified bound. The calculation also does
not reserve supplemental hook sites, original data, support/runtime code,
relocation destinations, exception/unwind tables, startup/TLS/CRT structures,
or internal direct-call targets. No bytes were emitted or patched; the
diagnostic DLL remains not an ASI and is not game-test-ready.
