# Candidate correction: `FUN_100074d0` vehicle-pool base dereference

Date: 2026-09-24  
Reference image: `ImVehFt.asi`, SHA-256 `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

## Evidence and change

At `0x100074e4`, Ghidra loads the pointer stored at `0x00B74494` (`CPools::ms_pVehiclePool`). It then subtracts the dword at that pool object's address from the vehicle address (`SUB EDX,dword ptr [EAX]` at `0x100074ee`). The historical/local Plugin-SDK defines `CPools::ms_pVehiclePool` at `0xB74494`; `CPool.h` shows the first field is `m_pObjects`. Thus the subtraction base is the pool's object-array pointer, not the pool-object address itself.

The candidate had declared `DAT_00b74494` as an external signed integer and used it directly as the subtraction base. It now performs the two evidenced volatile loads: first the pool pointer from `0xB74494`, then the first `CPool` dword (`m_pObjects`). The compiled x86 object shows `mov ecx,[0B74494h]`, `mov ecx,[ecx]`, and `sub edx,ecx`, matching Ghidra's dereference sequence. The change removes this candidate's dependency on a fake external C++ global.

## Validation performed

- MSVC 2022 x86 C++20 `/O2`: full candidate set compiled and archived, **705/705**.
- Current `100074d0.cpp` passed `/O2 /W4 /WX /MT`.
- ReAgent 0.4.0 targeted parity for the five corrected sources (`10003ba0`, `10003e60`, `100076d0`, `100099f0`, `100074d0`): **5 green / 0 yellow / 0 red**.
- ReAgent 0.4.0 objective verifier for those five current sources: **5/5 PASS**, no structural findings.
- Diagnostic full-set link against the historical SDK/static helper probe now reports **199 unresolved unique externals**, down from 200; it produced no DLL and is not the production project.
- The current 705-row source hash manifest was refreshed and checked against every candidate source.

## Limits

The address/type/data-flow match and object instruction sequence are strong local evidence for this specific correction, not complete function-semantic proof. Other candidates still use inconsistent `0xB74494` declarations and must be assessed individually against their own Ghidra instructions. Aggregate 705/705 ReAgent totals predate the current five targeted edits; no full production link or in-game test has been performed.
