# Installer relative-branch target inventory

Date: 2026-09-27. This read-only inventory derives every statically encoded
`CALL rel32` / `JMP rel32` target in candidate installer
`src/functions/10002210.cpp`. For each patch, the 32-bit displacement is
interpreted as signed and added to the address after the 5-byte branch at the
GTA patch site. The original values reproduce the addresses listed below.

| Opcode | GTA patch site | Original rel32 | Original target | Rebuild target class |
|---|---:|---:|---:|---|
| E8 | `0x006D6617` | `0x0F930EB4` | `0x100074D0` | candidate TU |
| E8 | `0x005B8FFD` | `0x0FA4F13E` | `0x10008140` | candidate TU |
| E8 | `0x006D6494` | `0x0F92EC47` | `0x100050E0` | candidate TU |
| E8 | `0x0053BFCC` | `0x0FAC8B3F` | `0x10004B10` | supplemental hook shim |
| E8 | `0x006D6A58` | `0x0F92D863` | `0x100042C0` | candidate TU |
| E9 | `0x005D5BC7` | `0x0FA32BB4` | `0x10008780` | supplemental hook shim |
| E9 | `0x005D5C1E` | `0x0FA32C0D` | `0x10008830` | supplemental hook shim |
| E9 | `0x005D5AD1` | `0x0FA32E6A` | `0x10008940` | supplemental hook shim |
| E9 | `0x006E198E` | `0x0F9265FD` | `0x10007F90` | supplemental hook shim |
| E9 | `0x006E18DA` | `0x0F926671` | `0x10007F50` | supplemental hook shim |
| E9 | `0x006E1A2D` | `0x0F92653E` | `0x10007F70` | supplemental hook shim |
| E8 | `0x006FDED6` | `0x0F905F65` | `0x10003E40` | supplemental hook shim |
| E8 | `0x006FDF10` | `0x0F90602B` | `0x10003F40` | candidate TU |
| E9 | `0x006AB350` | `0x0F957CDB` | `0x10003030` | supplemental hook shim |
| E8 | `0x006F3AED` | `0x0F90F56E` | `0x10003060` | supplemental hook shim |
| E8 | `0x006F3973` | `0x0F90F708` | `0x10003080` | supplemental hook shim |
| E8 | `0x006E174B` | `0x0F921CB0` | `0x10003400` | candidate TU |
| E8 | `0x006E175E` | `0x0F921C9D` | `0x10003400` | candidate TU |
| E8 | `0x006E173C` | `0x0F921F1F` | `0x10003660` | candidate TU |
| E8 | `0x006E1773` | `0x0F921EE8` | `0x10003660` | candidate TU |
| E9 | `0x006E27E6` | `0x0F9209F5` | `0x100031E0` | supplemental hook shim |
| E8 | `0x006E0DF7` | `0x0F922544` | `0x10003340` | candidate TU |

## Result and limit

All **22 branch patch sites / 20 unique destinations** resolve: eight
destinations have candidate translation units and the other twelve match the
separately reconstructed hook-target inventory. No missing destination was
found in this specific installer rel32 set. The target membership check is
reproducible from the installer source, `audit/asi-hook-target-cfg-2026-09-27.csv`,
and `src/functions/`.

This closes only the destination inventory. It does **not** make the diagnostic
DLL safe or production-ready. A relocatable build still has to calculate new
relative displacements to linked symbols and rewrite the relevant patch
operands. Several exact-byte shim bodies also embed original absolute ImVehFt
global addresses and GTA continuation addresses; those must be audited and
relocated without changing register/stack behavior. Installer hook sites,
all fixed data references, PE image/link layout, loader behavior, and in-game
behavior remain unvalidated. No source function, binary, or installer patch
was changed by this inventory.
