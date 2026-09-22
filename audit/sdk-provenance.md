# SDK provenance

The local reference binary `ImVehFt.asi` has an x86 PE header, a linker-version trace of 10.00, and a PE timestamp of 2014-05-23 20:08:32 UTC. It imports `d3dx9_43.dll` and the Windows system libraries, but no `plugin.dll`.

The local `C:/Users/caner/Downloads/SA Plugin SDK` directory is a dated September/October 2013 SDK snapshot. Its `plugin.lib` is an import library: it contains an `__IMPORT_DESCRIPTOR_plugin` and expects a separate `plugin.dll`. Using that library in the current diagnostic link produced no DLL and 612 unresolved linker diagnostics, so it is not treated as the binary's final link input.

The closest public historical Plugin-SDK line before the binary timestamp is the static-library work in the April 2014 history. The 2014-04-27 commit `888a67c1587ece1053a05f0cb6219a0c6c4dad0a` retains `PLUGIN_API` as a static implementation marker in `src/sdk/plugin/plugin.h`; the 2014-04-08 commit `d55b334629df248aec238f1d8e80673166bc7301` is the earlier commit explicitly titled `Static version is done`.

This is provenance evidence, not proof that ImVehFt used one exact commit. The full link remains blocked by reconstructed internal image data, CRT/EH ABI pieces, and missing original project inputs.
