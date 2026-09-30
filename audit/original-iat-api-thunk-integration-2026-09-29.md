# Original-IAT API call-thunk integration probe — 2026-09-29

## Emitted and checked

`src/hook_shims/x86_original_iat_api_thunks.asm` defines 21 uniquely named
tail-call thunks (`IVF_API_CALL_*`). Each is exactly `FF 25 imm32`, preserving
the API's register/stack contract and tail-returning to the caller. Strict
COFF verification found 21 public thunk symbols, 126 code bytes, and 21
`IMAGE_REL_I386_DIR32` references to the corresponding IAT alias symbols.

The name/DLL crosswalk places all 21 IAT slots in the original `.rdata` at
matching offsets. The isolated link probe used a section-defined alias
provider and confirmed 21/21 linked thunk immediates target the corresponding
offset within linked `.rdata`; it also contains 21 `IMAGE_REL_BASED_HIGHLOW`
records at each thunk's absolute memory operand. Details are in
[`original-iat-api-thunks-unique-symbol-coff-verification-2026-09-29.json`](original-iat-api-thunks-unique-symbol-coff-verification-2026-09-29.json),
[`original-iat-api-data-provider-2026-09-29.json`](original-iat-api-data-provider-2026-09-29.json),
and [`original-iat-api-thunk-linked-section-relocation-verification-2026-09-29.json`](original-iat-api-thunk-linked-section-relocation-verification-2026-09-29.json).

The 705-candidate diagnostic DLL also links successfully when the unique-name
shim object is added. A previous attempt to export the import-library's own
`_API@N` symbol names failed with LNK2005 because the Microsoft import
libraries define those names themselves. Unique shim names avoid that
collision. The full diagnostic link does **not** redirect the candidate
callsites to these shims: its map still resolves those direct API symbols to
the diagnostic import-library stubs. The final image builder must explicitly
rewrite each candidate `REL32` target to the matching `IVF_API_CALL_*` thunk.

## Still unverified

The isolated link probe has different `.text`/`.rdata` RVAs from the original
ASI; it verifies section-relative IAT offsets and relocation mechanics only.
No final PE/ASI was emitted, the 705 candidate call relocations were not
rewritten, and no loader or GTA runtime test was run. The original ASI is
unchanged.
