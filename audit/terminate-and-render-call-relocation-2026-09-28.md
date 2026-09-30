# terminate and RenderWare caller relocation follow-up (2026-09-28)

Two more Ghidra-supported caller edges were redirected to candidate symbols:

- `10017dde::terminate` now calls candidate `__getptd` and `_abort` directly. `ghidra_exports/10017dde.json` shows these exact callees and their sequence around the thread-local termination callback; candidate declarations preserve the C calling conventions and return/noreturn behavior. Its adjacent backup is `src/functions/10017dde.cpp.pre-relocatable-crt-calls-20260928.bak`.
- `10006be0` now directly calls the candidate `FUN_100073f0` instead of casting its preferred image VA. Ghidra export `ghidra_exports/100073f0.json` identifies the fastcall entry and caller; the call-site prototype retains the existing 8 four-byte arguments and x87 float bit patterns. MSVC decorates the candidate as `@FUN_100073f0@32`; the 705-object map resolves it to `100073f0.obj`. Backup: `src/functions/10006be0.cpp.pre-relocatable-crt-calls-20260928.bak`.

Fresh final checks after both changes: MSVC x86 `/O2 /W4 /WX /MT` 705/705 (`build/strict-all-post-relocatable-render-call-20260928.json`), ReAgent objective 705 PASS / 0 FAIL / 0 UNKNOWN (`audit/objective-post-render-call-relocation-2026-09-28.json`), parity 705 GREEN / 0 YELLOW / 0 RED (`build/parity-post-render-call-relocation-20260928.json`), and a successful normal 705-object diagnostic link (`build/link-probe/strict-704-historical-sdk/ImVehFt-reloc-render-call-final-diagnostic-not-ASI.dll`). Both source manifests have 705 rows and independently verify with zero hash mismatches.

The v17 inventory was superseded by v18 and then v19. The `__SEH_prolog4` caller/frame ABI has since been corrected; see `audit/seh-prolog-caller-abi-2026-09-28.md`. The `__cftoe_l` call at `0x1001bdff` has also been redirected to the candidate C-linkage symbol; see `audit/cftoe-call-relocation-2026-09-28.md` for the call-site and EAX-forwarding evidence.

The DLL remains diagnostic only. No original project/build system is recovered, and original PE layout/relocations, startup/import/hook integration, game loading, and runtime behavior remain unverified.
