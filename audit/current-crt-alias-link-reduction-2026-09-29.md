# CRT alias contribution to the probe-free layout link — 2026-09-29

The four-object removal experiment left 185 unresolved symbols. To separate
CRT name aliases from test data, a second link kept only the old
`crt_abi_alias_probe.obj` and removed the exception/data/rdata probe objects.
This object contains a 5,676-byte `.drectve` section with 78
`/ALTERNATENAME` directives and no externally defined code/data symbols.

With those alias directives enabled, the linker reported **120 unique
unresolved symbols** (152 diagnostics), down from 185. No DLL was emitted.
The log is
`build/link-probe/entry-exact-nogs-o1-crt-alias-active-20260929/crt-alias-link-20260929.log`;
the response is
`build/recheck/entry-xcode-nogs-o1-crt-alias-active-v2-20260929.rsp`.

This shows that a substantial fraction of the old successful link depended on
symbol-name aliases rather than provided implementations. The aliases are not
yet accepted as production-correct: each must be checked against the target
function's x86 ABI and actual COFF definition. The remaining unresolved set
still includes original-address data/vtable names and exception/runtime
support; the three excluded probe objects cannot be treated as valid
replacement data. The experiment changed no candidate source or installed
ASI and did not produce a loadable image.
