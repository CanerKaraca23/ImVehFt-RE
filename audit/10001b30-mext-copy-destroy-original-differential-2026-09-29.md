# MEXT copy/create/destroy original-binary differential — 2026-09-29

## Result

Compared original ASI bodies for `10001b30` (MEXT copy), `10001b00` (MEXT
destructor), and `10001ad0` (MEXT constructor) with the corresponding current
MSVC x86 candidate objects. The original ASI was mapped at its preferred base;
Ghidra-confirmed calls to `RwRasterCreate` (`0x7fb230`), `RwTextureCreate`
(`0x7f37c0`), and `RwTextureDestroy` (`0x7f3820`) were redirected to controlled
stubs. Candidate objects were patched only at their unique matching API
immediates after strict source-hash checks.

Ten fresh PE32 processes each ran two original-versus-candidate cases (20
pairs), all matching:

1. Source MEXT record has no owned texture: copy return, copied fields,
   destination's constructor-initialized null owner field, and absence of
   RenderWare API calls match.
2. Source record owns a texture: raster creation received width 640, height
   480, flags 0, type 5; texture creation received that raster; destination
   received the returned texture; destroying the destination caused one
   `RwTextureDestroy` call; the stub re-entered the actual MEXT destructor on
   the child texture, whose constructor-initialized zero owner slot terminated
   the same-plugin nested edge. Return values, callback order, and source,
   destination, child-texture, and raster bytes matched.

Runner: `../scripts/test-10001b30-mext-copy-differential.ps1 -Repetitions 10`.
Harness: `../tests/runtime_10001b30_mext_copy_differential.cpp`.
All candidate objects and the harness compiled with MSVC 2022 x86 `/O1 /W4
/WX /MT /GS- /arch:IA32`.

## Reproducibility hashes

- Original ASI SHA-256:
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`
- Candidate `10001b30.cpp` SHA-256:
  `106552B9F9DE2AFC908D1DF584772FFD284BF0C9154496402AF6B54D992EF449`
- Candidate `10001b00.cpp` SHA-256:
  `E557E022C0B23F7FC6AA07F1CA5109F0C69419518C6BD686AF7906AD2A49E416`
- Candidate `10001ad0.cpp` SHA-256:
  `D675CB21D80A8C9C0226B57BC5AD47630DD9EB040898FDBB7568E6D8B2BD460F`
- Harness source SHA-256:
  `FC51658608DBA20E6F56336B2254E357039C4A7C65DD407CD6288A0EC95ED167`
- Copy object SHA-256:
  `0B0D3E3935663E47B5622EF2E0E09C833B6869424BBDBFC431838D440B599DCF`
- Destructor object SHA-256:
  `D9C5FADF294EFEBE7F24B05BB335C88D9F93291BDA9DC863C935BF7D0A1E1545`
- Constructor object SHA-256:
  `71D3706A492E2A64FC55818435F373E54E6BC99B6F6CB40BC4F9217C82BE83D9`
- Harness executable SHA-256:
  `AFC7B393D3C6A265CBAB9D4A7DF68A1562F31CE106639DB8C6BECC244781CC38`

## Scope boundary

The API stubs model only the observed RenderWare calls and deliberately invoke
the MEXT constructor/destructor callbacks. They do not execute GTA's real
texture/raster registry, allocator, `stdFunc[5]`, COM release, third-party
callbacks, or live `100076d0` vehicle processing. This differential supports
the ordinary ImVehFt MEXT-owned-texture path, but does not prove that unrelated
runtime callbacks cannot re-enter `100076d0`. Keep its live-runtime finding
OPEN; no candidate source or installed binary was changed.
