# Linked installer target verification

Date: 2026-09-28. This is a fresh static verification of the existing current-
object diagnostic link. It does not modify candidate sources or link outputs.

Command:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File scripts/verify-linked-installer-targets.ps1
```

The checker cross-references the preserved 22-site installer target manifest
with the current link map and PE bytes. It verifies that all 20 unique
`IVF_INSTALL_TARGET_*` wrapper symbols and each intended target symbol are
present; every wrapper is inside a PE section and begins with `JMP rel32`; the
decoded jump destination matches the intended linked candidate or supplemental
hook shim; and the runtime displacement from each original GTA patch site to
that linked destination is representable as signed x86 `rel32`.

Result: **22/22 patch sites and 20/20 wrappers pass** against
`ImVehFt-optref-comdat-order-v14-current-20260928-diagnostic-not-ASI.dll`.
The link map places the wrappers and targets in the diagnostic image, whose
base-relocation directory allows loader rebasing; the installer computes each
call displacement from the actual linked symbol address at runtime.

This is stronger than merely finding successful linker output, but still is
not an execution of `FUN_10002210`, a patch against `gta_sa.exe`, or a game
test. It does not establish correctness of the 705 function bodies, global
state/CRT initialization, or indirect RenderWare behavior. The DLL remains a
diagnostic artifact and was not installed or loaded.
