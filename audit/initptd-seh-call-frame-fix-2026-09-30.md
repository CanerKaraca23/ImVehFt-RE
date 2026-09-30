# `__initptd` SEH frame-call correction (2026-09-30)

## Evidence

The v10 first-chance dump stops in `___addlocaleref` with its pointer argument equal to `1`. The original Ghidra export for `0x10014cc3` identifies a Visual Studio 2010 `__initptd` and shows the special `__SEH_prolog4` sequence followed directly by the function body. In the original instruction stream, that prolog call has no ordinary caller stack cleanup; the generated frame is intentionally left active for the function body and `__SEH_epilog4`.

The prior `/O1 /GS-` candidate object instead began with `push esi`, called `__SEH_prolog4` as an ordinary C function, then emitted two `pop ecx` instructions. Its subsequent argument access also used `[esp+8]`. That does not match Ghidra's entry sequence and is consistent with a corrupted/misaligned SEH frame and the invalid locale pointer observed at runtime. This is a strong candidate root cause, not yet proven by a post-fix game run.

## Change and checks

`src/functions/10014cc3.cpp` now has a naked entry wrapper that emits the original frame-prolog call sequence without compiler-generated register saves or cdecl cleanup. It forwards the two arguments to a normal C++ body helper and then invokes the original SEH epilog. The pre-edit source is preserved as `src/functions/10014cc3.cpp.pre-seh-call-frame-fix-20260930.bak` (SHA-256 `B990E1477C70F68F9C50E049B0C79E269791C1EE692271872BC98DD6EDE7D092`).

- Focused MSVC x86 object disassembly: wrapper starts `push 8; push scope; call __SEH_prolog4`; no pre-prolog register save and no post-prolog argument pops. The wrapper has relocations for the scope, prolog, body helper, and epilog symbols.
- Fresh strict `/O1 /W4 /WX /MT /arch:IA32 /GS-` compile: **705/705 passed**, report `build/strict-xcode-nogs-o1-seh-frame-fix-20260930.json`.
- Independent structural objective verifier: **705 PASS / 0 FAIL / 0 UNKNOWN**, report `audit/objective-seh-call-frame-fix-2026-09-30.json`.
- ReAgent source parity: **704 GREEN / 1 YELLOW / 0 RED**. The yellow is `0x10014cc3`, because the parity heuristic counts 9 original calls against 3 in the wrapper TU; the body calls were moved into `__initptd_body`. This is not being represented as green.
- The initial all-705 diagnostic link had 7 unresolved original-image aliases. A seven-symbol provider was generated from exact bytes at the pinned original ASI addresses and linked into a **second, non-forced** diagnostic DLL; this link succeeded with no unresolved-symbol errors (stale `/ORDER` LNK4037 warnings only). Its SHA-256 is `8E2CC7FEFE68DAB0163A475D51439B24BD6A93C71815E26145BC470B2A8DB0F8`; map SHA-256 is `3B96923905EBCBF2A1DEF16379798E5410205A6ED67C66F4A9FDB9893198D7B2`. This is still a diagnostic DLL with an artificial entry point, not a production PE/ASI.
- Fresh body inventory plus the successful diagnostic map yielded a current placement-feasibility report: **560 direct-fit / 144 thunked**, 705/705 mapped executable targets, no out-of-range rel32 edges. This remains a feasibility result, not an instruction-boundary, cross-reference, relocation, startup, or runtime proof. The prior 285/420 payload/placement manifest is stale: `0x10014cc3` now has a 32-byte entry wrapper while its C++ body helper is a separate symbol. No full candidate ASI was emitted from these objects, and the v10 runtime dump does not test this source fix.
- Rechecked that current placement rather than trusting size-fit alone: original instruction-boundary decoding moved 273 more entries to thunks; saved Ghidra interior-xref evidence moved three further entries. The refreshed conservative plan is again **285 direct / 420 thunked**. Four interior refs were observed before that final move; the resulting direct-body set has no known saved interior references.
- Regenerated the 420-root census against the fresh objects and materialized the raw root-body payload (**85,347 bytes**, SHA-256 `2E65AE25C465341D54D11ECF75374C0A9B6B7251F816E931F41DFD11329029E1`). It is explicitly unrelocated. The new `__initptd` call is classified as a same-object `.xcode` helper section (`__initptd_body`, 124 bytes, 11 COFF relocations); that helper must be included in the appended-code closure and its relocations resolved before a PE candidate can be made.
- The fresh closure audit identifies **17 same-object non-`.rdata` sections** (15 `.xcode`, one `.data`, one `.bss`), totaling 11,186 bytes and 233 relocations. It includes the new `__initptd_body` helper. There are 97 unique unresolved external symbol/type pairs in these closure sections; the appended-code/data closure and relocation manifests are not complete yet.
- Cross-checked root and closure externals against the successful diagnostic link map: all **855 unique symbol/type pairs** (including the 97 closure-only additions) fall into a known map class—203 diagnostic code symbols, 63 import slots, 467 address-encoded aliases whose diagnostic placement differs from the encoded VA, and 122 provider/runtime-data symbols; none are absent by exact name. This classifies resolution avenues, but the displaced addresses still require exact original-image or appended-payload target reconciliation before applying fixups.

## Still required

- Regenerate and independently validate instruction-boundary, cross-reference, root-body, closure, and relocation manifests for the fresh 705-object set; emit a full candidate only after those gates reconcile. The prior v10 image is relocation-only over v9 and does **not** contain this wrapper change.
- Run it in the isolated GTA clone with first-chance crash capture and compare behavior; inspect any new failure before another edit.
- Keep the original ASI unchanged. The original ASI still hashes to `409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3`; the clone remains restored to that original hash.

Neither the compile nor structural checks prove semantic equivalence or runtime correctness.
