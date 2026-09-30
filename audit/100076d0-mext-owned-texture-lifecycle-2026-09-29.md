# `100076d0` MEXT owned-texture lifecycle — 2026-09-29

## Fresh binary evidence

Ran a read-only, `-noanalysis` Ghidra 12.1.3 query on the existing ImVehFt
program (`ImVehFt.asi`, image base `0x10000000`) and cross-checked the matching
GTA SA program at image base `0x00400000`. The query log is
`mext-owned-texture-lifecycle-2026-09-29.log` (SHA-256
`EFD64D58166EA1182B2FBC3932804D258C7383E9233257B1F128BC28161BF8B3`). The
GTA-side constructor/destructor/texture-create query is in
`gta-rw-target-trace-2026-09-29.log` (SHA-256
`50D1F4B93475C353368AFAD6071930E74683B3685821398671C2BC46748C56E7`). Both
reference binaries remain hash-pinned in the adjacent callback-target audit.

The exact ImVehFt candidate sources examined match `audit/source-sha256.csv`:

- `10001980.cpp`: `44A2622884992DB9788F30520EC50E9053FFAA024956A4F529939B54464828CB`
- `10001ad0.cpp`: `D675CB21D80A8C9C0226B57BC5AD47630DD9EB040898FDBB7568E6D8B2BD460F`
- `10001b00.cpp`: `E557E022C0B23F7FC6AA07F1CA5109F0C69419518C6BD686AF7906AD2A49E416`
- `10001b30.cpp`: `106552B9F9DE2AFC908D1DF584772FFD284BF0C9154496402AF6B54D992EF449`

## Ownership and destruction path

1. ImVehFt registers its 16-byte `MEXT` texture plugin (ID `0x5445584d`) with
   constructor `0x10001ad0`, destructor `0x10001b00`, and copy callback
   `0x10001b30`.
2. Texture constructor `0x7f37c0` allocates a texture and calls GTA's plugin
   constructor walker `0x8086e0` with registry root `0x8e23cc`. The same root is
   passed by texture destructor `0x7f3820` to destructor walker `0x808740`.
   The constructor walker calls each registry record's `+0x20` callback.
3. The registered MEXT constructor writes `1` at plugin offset `+0`, and zeroes
   `+4`, `+8`, and the owned-texture pointer at `+0x0c`.
4. ImVehFt's texture-dictionary callback `0x10001980` creates a raster through
   `0x7fb230`, creates a texture through `0x7f37c0`, then stores that result at
   `+0x0c` of the current/source MEXT record. Thus the created texture gets its
   own MEXT constructor first, and the owning source record gets the pointer.
5. MEXT destructor `0x10001b00` destroys that owned texture only when its own
   record's `+0x0c` is non-null. For the texture created by step 4, its own
   record starts with `+0x0c == 0`; its destruction therefore does not recurse
   again through this same MEXT owned-texture edge, unless another operation
   later changes that field. The copy callback can create and assign an owned
   texture on its destination record by the same raster-create/texture-create
   route.

## Adjudication

This closes one specific concern: the ordinary MEXT-owned texture construction
path does not, by itself, create an indefinitely self-recursive chain through
`10001b00`. It does **not** close `100076d0`'s live re-entry risk. Every nested
texture destroy still walks the live texture-plugin registry, may destroy an
attached raster through the separate raster-plugin registry, and calls runtime
RenderWare/allocator slots. External plugin callbacks, registry contents/order,
runtime mutations of MEXT records, and game-time re-entry remain unobserved.
The earlier 15-case queue differential uses synthetic records and provides no
evidence for those runtime targets.

No candidate source or installed binary was changed. This is new binary-backed
static evidence only; keep `100076d0` runtime status OPEN until the live
callback/re-entry behavior is observed or ruled out with equally direct proof.

Reproduction scripts:

- `../scripts/ghidra_dump_mext_owned_texture_lifecycle.java`
- `../scripts/ghidra_dump_gta_rw_callback_targets.java`
