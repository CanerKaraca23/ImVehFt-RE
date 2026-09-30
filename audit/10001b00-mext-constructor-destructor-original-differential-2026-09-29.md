# MEXT constructor/destructor original-binary differential — 2026-09-29

## Result

Compared the actual `FUN_10001ad0` and `FUN_10001b00` bodies from the
hash-pinned original ImVehFt ASI with their current MSVC x86 candidate objects.
The original ASI was mapped at its preferred image base; its verified call
immediate to GTA `RwTextureDestroy` (`0x007f3820`) and the candidate object's
single matching call immediate were redirected to one controlled test stub.
The callback bodies themselves were not substituted.

Ten fresh PE32 processes each ran three original-versus-candidate cases (30
pairs total), all matching:

1. Non-null texture with an initialized MEXT record whose owned-texture slot is
   zero: no RenderWare destroy call.
2. Non-null texture with an owned pointer: exactly one destroy call carrying
   that pointer.
3. The destroy stub re-enters the MEXT destructor on a child texture after
   initializing its MEXT record through the actual original/candidate
   constructor: return values, record bytes, child initialization, and callback
   trace all match; the child's zero owned-texture slot terminates this
   same-plugin nested edge.

Runner: `../scripts/test-10001b00-mext-destructor-differential.ps1 -Repetitions 10`.
Harness: `../tests/runtime_10001b00_mext_destructor_differential.cpp`.
Compile flags: MSVC 2022 x86 `/O1 /W4 /WX /MT /GS- /arch:IA32`.

## Reproducibility hashes

- Original ASI SHA-256:
  `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`
- Candidate `10001b00.cpp` SHA-256:
  `E557E022C0B23F7FC6AA07F1CA5109F0C69419518C6BD686AF7906AD2A49E416`
- Candidate `10001ad0.cpp` SHA-256:
  `D675CB21D80A8C9C0226B57BC5AD47630DD9EB040898FDBB7568E6D8B2BD460F`
- Harness source SHA-256:
  `67B9ECEB9FB5BAD929EC7FFBE40509BE0193412C743E42B569A6FE7894C637AB`
- Destructor object SHA-256:
  `C0F8743DC2DF528EAE7D86645F8B872C23CF41F69DF48E82441105B468BC9248`
- Constructor object SHA-256:
  `6BEE972036A9432BACF3288709A2055D4FBAFE5FC7A8B1992C853B53BD0A7C6E`
- Harness executable SHA-256:
  `7AAA647BA0E3FE0997E6F67EBF369187529319FC11B350388AC10A1233ABFC8C`

## Scope boundary

The callback stub models only the `RwTextureDestroy` API boundary. It does not
run GTA's live texture/raster plugin registry, real raster destruction,
`stdFunc[5]`, allocator or COM release callbacks, or the full `100076d0`
vehicle-processing function. This validates the local MEXT ctor/dtor behavior
in bounded cases and supports the static ownership trace; it does not close the
external callback/re-entry finding. Keep `100076d0` runtime status OPEN and do
not treat this three-case-per-process differential as game validation.
No candidate source or installed binary was changed.
