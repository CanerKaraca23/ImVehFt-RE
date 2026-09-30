# Candidate correction: `FUN_10005670` vehicle-pool object-array base

Date: 2026-09-24  
Reference image: `ImVehFt.asi`, SHA-256 `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Evidence and change

Ghidra for `10005670` loads the pool pointer from `0x00B74494` at `0x10005682`, then subtracts the dword at that pool object's address (`SUB EDX,dword ptr [EAX]` at `0x10005689`). Plugin-SDK identifies `0xB74494` as `CPools::ms_pVehiclePool`, and `CPool.h` identifies the first field as `m_pObjects`.

The candidate previously subtracted the external symbol `_DAT_00b74494` directly. It now performs the two corresponding volatile loads—pool pointer slot, then `m_pObjects`—and computes the `0xA18` vehicle-slot index from the object-array base. This replaces an unresolved external symbol and reflects the data flow visible in Ghidra.

## Validation performed

- MSVC 2022 x86 C++20 `/O2`: full candidate set compiled and archived, **705/705**.
- Current `10005670.cpp` passed `/O2 /W4 /WX /MT`.
- ReAgent 0.4.0 parity for the six current corrections: **6 green / 0 yellow / 0 red**.
- ReAgent 0.4.0 objective verifier for the six current corrections: **6/6 PASS**, no structural findings.
- At the time of this report, the diagnostic link reported 198 unresolved unique externals and produced no DLL. The newer 2026-09-26 probe reports 164; it remains diagnostic only and is not the production project.
- The 705-row source hash manifest is now synchronized and independently checked with zero mismatches (2026-09-26).

## Limits

This verifies one address and pointer chain, not the full behavior of `FUN_10005670`. Other candidates reference the same global with differing declarations; each must be checked against its own instructions. The 705-wide ReAgent totals remain from an older source snapshot, and production linking/in-game validation are still outstanding.
