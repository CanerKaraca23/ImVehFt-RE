param(
    [string]$Image = 'build/link-probe/strict-704-historical-sdk/ImVehFt-optref-comdat-order-v14-current-20260928-diagnostic-not-ASI.dll',
    [string]$Map = 'build/link-probe/strict-704-historical-sdk/ImVehFt-optref-comdat-order-v14-current-20260928-diagnostic-not-ASI.map',
    [string]$Manifest = 'audit/installer-target-thunks-2026-09-27.json'
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
$root = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$imagePath = (Resolve-Path (Join-Path $root $Image)).Path
$mapPath = (Resolve-Path (Join-Path $root $Map)).Path
$manifestPath = (Resolve-Path (Join-Path $root $Manifest)).Path
$imageBytes = [IO.File]::ReadAllBytes($imagePath)
$mapLines = [IO.File]::ReadAllLines($mapPath)
$patches = @(Get-Content -LiteralPath $manifestPath -Raw | ConvertFrom-Json | Select-Object -ExpandProperty patches)

$peOffset = [BitConverter]::ToInt32($imageBytes, 0x3c)
if ([BitConverter]::ToUInt32($imageBytes, $peOffset) -ne 0x00004550) { throw 'Invalid PE signature.' }
if ([BitConverter]::ToUInt16($imageBytes, $peOffset + 4) -ne 0x014c) { throw 'Expected x86 PE image.' }
$sectionCount = [BitConverter]::ToUInt16($imageBytes, $peOffset + 6)
$optionalSize = [BitConverter]::ToUInt16($imageBytes, $peOffset + 20)
$optionalAt = $peOffset + 24
if ([BitConverter]::ToUInt16($imageBytes, $optionalAt) -ne 0x010b) { throw 'Expected PE32 optional header.' }
$imageBase = [BitConverter]::ToUInt32($imageBytes, $optionalAt + 28)
$sectionAt = $optionalAt + $optionalSize
$sections = for ($i = 0; $i -lt $sectionCount; $i++) {
    $at = $sectionAt + 40 * $i
    [pscustomobject]@{
        Name = [Text.Encoding]::ASCII.GetString($imageBytes, $at, 8).Trim([char]0)
        VirtualSize = [BitConverter]::ToUInt32($imageBytes, $at + 8)
        RVA = [BitConverter]::ToUInt32($imageBytes, $at + 12)
        RawOffset = [BitConverter]::ToUInt32($imageBytes, $at + 20)
    }
}

$symbolVAs = @{}
foreach ($line in $mapLines) {
    $parts = @($line.Trim() -split '\s+')
    if ($parts.Count -ge 3 -and $parts[2] -match '^[0-9A-Fa-f]{8}$') {
        if (-not $symbolVAs.ContainsKey($parts[1])) {
            $symbolVAs[$parts[1]] = [Convert]::ToUInt32($parts[2], 16)
        }
    }
}

$uniqueWrappers = [Collections.Generic.HashSet[string]]::new([StringComparer]::Ordinal)
foreach ($patch in $patches) {
    if (-not $symbolVAs.ContainsKey($patch.wrapper_symbol)) { throw "Missing wrapper in link map: $($patch.wrapper_symbol)" }
    if (-not $symbolVAs.ContainsKey($patch.target_symbol)) { throw "Missing intended target in link map: $($patch.target_symbol)" }
    [void]$uniqueWrappers.Add($patch.wrapper_symbol)
    $wrapperVA = [uint32]$symbolVAs[$patch.wrapper_symbol]
    $targetVA = [uint32]$symbolVAs[$patch.target_symbol]
    $wrapperRVA = [uint32]($wrapperVA - $imageBase)
    $section = $sections | Where-Object { $wrapperRVA -ge $_.RVA -and $wrapperRVA -lt ($_.RVA + $_.VirtualSize) } | Select-Object -First 1
    if (-not $section) { throw "Wrapper is outside PE sections: $($patch.wrapper_symbol)" }
    $fileOffset = [int]($section.RawOffset + $wrapperRVA - $section.RVA)
    if ($imageBytes[$fileOffset] -ne 0xe9) { throw "Wrapper is not a JMP rel32: $($patch.wrapper_symbol)" }
    $encodedRel32 = [BitConverter]::ToInt32($imageBytes, $fileOffset + 1)
    $decodedTarget = [long]$wrapperVA + 5 + $encodedRel32
    if ($decodedTarget -ne $targetVA) { throw "Wrapper target mismatch: $($patch.wrapper_symbol)" }

    $opcodeVA = [Convert]::ToUInt32($patch.opcode_address.Substring(2), 16)
    $runtimeRel32 = [long]$targetVA - ([long]$opcodeVA + 5)
    if ($runtimeRel32 -lt [int]::MinValue -or $runtimeRel32 -gt [int]::MaxValue) {
        throw "Installer CALL/JMP displacement is outside signed x86 rel32 range at $($patch.opcode_address)"
    }
}

[pscustomobject]@{
    Image = $imagePath
    PatchSites = $patches.Count
    UniqueWrappers = $uniqueWrappers.Count
    VerifiedWrapperJumps = $patches.Count
    Result = 'PASS'
    Limitation = 'Static link-map and PE-byte check only; does not execute installer patches or validate the GTA process.'
}
