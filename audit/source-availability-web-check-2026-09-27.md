# ImVehFt original-source availability check (2026-09-27)

This is a bounded public-source discovery check, not proof that no private or
unindexed source archive exists. No PDB search was performed or used.

## Evidence checked

- DK22Pac's 2012 ImVehFt release page lists downloadable ImVehFt 2.0.1 and
  2.0.2 ASI packages. The visible file list does not identify a source-code
  archive: <https://dk22pac.blogspot.com/2012/10/imvehft-release.html>.
- The GitHub public-repository list for DK22Pac was queried through the GitHub
  REST API on 2026-09-27. It includes repositories such as `plugin-sdk` and
  `imfx`, but no repository named ImVehFt.
- GitHub repository search for `ImVehFt` returned `JuniorDjjr/ImVehFtFix` and
  this reconstruction repository (`CanerKaraca23/ImVehFt-RE`), not an
  original ImVehFt source repository.
- Local searches have found the supplied mod assets and old SDK material, but
  no original ImVehFt solution/project/source tree suitable for a clean
  project build. Existing 705-TU compiler checks therefore remain candidate
  translation-unit checks, not a build of the original project.

## Consequence

Continue from the exact ImVehFt binary and Ghidra evidence. Treat original
source recovery and a faithful production-plugin link/game test as unavailable
until an actual matching source tree, build configuration, and required SDK
dependencies are found. This discovery does not change any candidate status or
turn compile/parity results into semantic/runtime proof.
