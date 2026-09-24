# SDK provenance

The local reference binary `ImVehFt.asi` has an x86 PE header, a linker-version trace of 10.00, and a PE timestamp of 2014-05-23 20:08:32 UTC. It imports `d3dx9_43.dll` and the Windows system libraries, but no `plugin.dll`.

The local `C:/Users/caner/Downloads/SA Plugin SDK` directory is a dated September/October 2013 SDK snapshot. Its `plugin.lib` is an import library: it contains an `__IMPORT_DESCRIPTOR_plugin` and expects a separate `plugin.dll`. Using that library in the current diagnostic link produced no DLL and 612 unresolved linker diagnostics, so it is not treated as the binary's final link input.

The closest public historical Plugin-SDK line before the binary timestamp is the static-library work in the April 2014 history. The 2014-04-27 commit `888a67c1587ece1053a05f0cb6219a0c6c4dad0a` retains `PLUGIN_API` as a static implementation marker in `src/sdk/plugin/plugin.h`; the 2014-04-08 commit `d55b334629df248aec238f1d8e80673166bc7301` is the earlier commit explicitly titled `Static version is done`.

The 2014-04-27 source snapshot was built as an x86 static library with the installed VS2022 toolchain. All 91 SDK translation units compiled. Two local test-only compatibility edits were needed in `CallbackResetDevice.hpp`: correcting the MSVC naked-function return declaration and removing an unreachable GCC-only jump from the MSVC branch. The historical source tree remains a separate checkout; these edits do not change the 705 candidate sources.

The resulting `Plugin2014.lib` was added to the same strict 705-object diagnostic link used with the modern SDK. Both link probes report 228 unresolved externals and produce no DLL. A public-symbol comparison against the unresolved names found no matching provider in either SDK library. This confirms that changing SDK library vintage alone does not clear the current link blockers.

This is provenance evidence, not proof that ImVehFt used one exact commit. The remaining blockers are chiefly GTA executable addresses, unresolved image globals/data, old CRT/EH ABI helpers, and missing original project inputs.
