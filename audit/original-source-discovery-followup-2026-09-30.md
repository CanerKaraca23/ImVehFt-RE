# Original ImVehFt source discovery follow-up — 2026-09-30

## Primary release-page check

Rechecked the author's retrievable DK22Pac release page for ImVehFt. Its visible “Files” section lists the 2013 ImVehFt 2.0.2 and 2012 2.0.1 downloads as **ASI** packages, not a source archive. The page is [DK22's ImVehFt release](https://dk22pac.blogspot.com/2013/05/imvehft-improved-vehicle-features-202.html). The original GTAForums thread still returns HTTP 403 to the web reader in this pass.

## Local evidence reconciliation

- `C:\Users\caner\Downloads\SA Plugin SDK` remains absent.
- The separate `_sdk_history\snapshot-2014-04-27` is present and has prior compile evidence (91 SDK translation units); it is a historical SDK snapshot, not the ImVehFt source tree or proof of the exact custom SDK used.
- The 2014 snapshot and current `plugin-sdk-sa` checkout do not supply an ImVehFt solution/project or original source. Diagnostic projects created during this reverse-engineering effort are not the original build system.
- The active ModLoader `ImVehFt.asi` remains byte-identical by SHA-256 to the pinned analysis target; it supplies no source/build metadata.

## Conclusion and limit

This update found no newly available authoritative ImVehFt source or original project/build configuration. It strengthens only the statement that the inspected author release page distributes ASI binaries. It is not proof that source was never shared privately or in an inaccessible attachment. Continue binary-first Ghidra analysis; do not call the 705-TU compile an original-project build.
