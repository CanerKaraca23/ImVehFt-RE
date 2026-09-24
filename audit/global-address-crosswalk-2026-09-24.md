# GTA global address crosswalk (2026-09-24)

## Scope and provenance

This cross-check compares unresolved `DAT_...` references in the 705 candidate translation units with the named absolute-address definitions in the local Plugin-SDK checkout (`DK22Pac/plugin-sdk`, checkout `b55e89b336a81448c1aa1a5b188431c9845ebaa9`). The local `ImVehFt.asi` was re-hashed during this audit and still matches the recorded SHA-256 `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`.

The SDK entries below identify GTA San Andreas US 1.00 global addresses and their SDK names/types. This establishes useful address-level corroboration, not that every candidate's inferred type, control flow, or use is correct. The source inventory was verified against `audit/source-sha256.csv`: 705 rows, zero missing/mismatched files. No candidate source was edited for this audit.

## Exact SDK crosswalk

| Address | Plugin-SDK name/type at address | Candidate usage and finding |
|---|---|---|
| `0x00B74494` | `CPools::ms_pVehiclePool`, pointer to vehicle pool (`CPool<CVehicle, CHeli>*`) | Used as the base of repeated `0xA18` vehicle-slot calculations. Candidate declarations vary across `int*`, `uint8_t*`, integer, and C/C++ linkage forms. The base-address use is plausible, but inconsistent declarations create distinct linker symbols and need a shared, evidence-backed address representation before a real plugin link. |
| `0x00B4E47C` | `CVehicleModelInfo::ms_pRemapTexture`, `RwTexture*` global | Candidate treats it as a 32-bit pointer when calling `FUN_10001fb0`; representation is compatible on x86, but its external data symbol is still not an executable-address binding. |
| `0x00B4E68C` | `CVehicleModelInfo::ms_pLightsTexture`, `RwTexture*` global | Candidate declares/uses a 32-bit integer in `100076d0.cpp`; same width on x86, but pointer semantics should remain explicitly unverified until checked against the Ghidra data references and access instructions. |
| `0x00B4E690` | `CVehicleModelInfo::ms_pLightsOnTexture`, `RwTexture*` global | Same concern as `0x00B4E68C`: pointer-valued SDK global versus candidate integer declaration. |
| `0x00B7CB4C` | `CTimer::m_FrameCounter`, 32-bit unsigned counter | Candidate reads/writes a 32-bit integer in `100099f0.cpp`; width matches, signedness and temporal semantics still need instruction-level confirmation. |
| `0x00B7CB84` | `CTimer::m_snTimeInMilliseconds`, 32-bit unsigned milliseconds | Used for elapsed-time arithmetic in several candidates. Width matches; signed/unsigned treatment differs in places and should be checked against the original comparisons and wrap behavior. |
| `0x00B7CD98` | `CWorld::Players`, base address of player-info storage | Candidate treats this as an integer in `10004bb0.cpp` and compares it against an object field. Address identity is supported; whether that comparison is semantically correct needs Ghidra structure/cross-reference confirmation. |
| `0x00C3EF5C` | `CCustomCarPlateMgr::pCharsetTex`, `RwTexture*` global | Candidate initializes and uses it as the charset texture pointer; this aligns with the SDK label at the address. |
| `0x00C3EF60` | `CCustomCarPlateMgr::pPlatebackTexTab`, base of an `RwTexture*` table | Candidate names `0xC3EF60`, `0xC3EF64`, and `0xC3EF68` as separate texture-pointer globals. On x86 these are consecutive 4-byte table slots 0, 1, and 2, not three independently named SDK globals. This is a strong layout clue for `10003ba0.cpp`. |
| `0x00C3EF78` | `CharsetLockedData`, an unsigned-byte/data pointer | The original candidate declared this as `Texture*` in `10003ba0.cpp` and `uint32_t` under a different identifier in `10003e60.cpp`. Ghidra shows it stores the `0x7FB2D0` raster-lock return and later serves as a byte-buffer base. Those two declarations have now been unified as `uint8_t*`, and the raster lock/unlock calls are expressed with the SDK-backed addresses/signatures; see [`candidate-correction-10003ba0-10003e60.md`](candidate-correction-10003ba0-10003e60.md). |
| `0x00C7C728` | `CMirrors::bRenderingReflection`, boolean | Candidate uses a one-byte `char` flag in `10005860.cpp`; representation is plausible, while exact branch behavior remains unverified. |
| `0x00C812A8` | `CWeather::TrafficLightsBrightness`, `float` | Candidate reads it as a float in vehicle-light routines; exact address/name/type align. |
| `0x00C81300` | `CWeather::Foggyness`, `float` | Candidate reads it as a float in vehicle routines; exact address/name/type align. |
| `0x00C8800C` | `CTxdStore::ms_pTxdPool`, pointer to TXD pool | Candidate uses an integer pointer in `100076d0.cpp` as a pool base; address and pointer-width use are plausible but not a complete semantic validation. |
| `0x00C97B24` | `RwEngineInstance`, RenderWare engine-instance pointer | Candidate models it as a custom `StateInterface*` and calls a member at offset `0x20`. The slot address is confirmed; the custom interface layout/name is not confirmed by this mapping alone. |
| `0x00C97C28` | `GetD3DDevice()` returns the pointer stored here (`IDirect3DDevice9*`) | Candidate uses custom `ContextInterface*`, `int**`, and integer-pointer declarations at the same address. A D3D device vtable interpretation is plausible for the vtable call, but the different declarations are a concrete type/linkage inconsistency to resolve with the original instructions. |

## Implications

1. A portion of the remaining link failures is not a missing SDK function: it comes from address-based process globals represented as external C++ variables, with multiple incompatible decorations across translation units. These cannot safely be “fixed” by dummy link definitions; a runtime plugin must read/write the target game's actual memory locations.
2. Some declarations are merely different 32-bit spellings for the same pointer-sized storage; others (notably `0xC3EF60` table slots and the `0xC3EF78` locked-data pointer) expose useful structural corrections to the interpretation.
3. Do not rename or rewrite candidates solely from this table. Before a semantic edit, verify each use against the original binary's x86 instructions, the exact base-game executable/version, and relevant object layouts. The 705-source hash inventory remains the guard against accidental drift.

SDK evidence files inspected: `plugin_sa/game_sa/CPools.cpp`, `CTimer.cpp`, `CWorld.cpp`, `CCustomCarPlateMgr.cpp`, `CMirrors.cpp`, `CWeather.cpp`, `CTxdStore.cpp`, `CVehicleModelInfo.cpp`, `RenderWare.cpp`, and `common.cpp`.
