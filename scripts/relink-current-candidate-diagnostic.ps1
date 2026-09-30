param(
    [Parameter(Mandatory = $true)][string]$BaseResponseFile,
    [Parameter(Mandatory = $true)][string]$ObjectDirectory,
    [Parameter(Mandatory = $true)][string]$OldObjectDirectoryToken,
    [Parameter(Mandatory = $true)][string]$NewObjectDirectoryToken,
    [Parameter(Mandatory = $true)][string]$OldOutputToken,
    [Parameter(Mandatory = $true)][string]$NewOutputToken,
    [Parameter(Mandatory = $true)][string]$ResponseFile,
    [string]$ReplaceToken,
    [string]$ReplaceWithToken,
    [switch]$IncludeCandidateCodeSymbols,
    [string]$OrderFile
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

if (-not $env:VCToolsInstallDir -or -not $env:WindowsSdkDir) {
    throw 'Run this script from a VS 2022 Developer environment initialized for x86.'
}

$root = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$objects = (Resolve-Path (Join-Path $root $ObjectDirectory)).Path
$rspOut = Join-Path $root $ResponseFile
$rspParent = Split-Path -Parent $rspOut
if (-not (Test-Path -LiteralPath $rspParent)) {
    New-Item -ItemType Directory -Path $rspParent -Force | Out-Null
}
if (Test-Path -LiteralPath $rspOut) {
    throw "Refusing to overwrite response file: $rspOut"
}

$candidateObjects = @(Get-ChildItem -LiteralPath $objects -File -Filter '*.obj')
if ($candidateObjects.Count -ne 705) {
    throw "Expected 705 current candidate objects; found $($candidateObjects.Count)."
}

$base = (Resolve-Path (Join-Path $root $BaseResponseFile)).Path
$content = [System.IO.File]::ReadAllText($base)
$content = $content.Replace($OldObjectDirectoryToken, $NewObjectDirectoryToken)
$content = $content.Replace($OldOutputToken, $NewOutputToken)
if ($ReplaceToken) {
    $replaceCount = [regex]::Matches($content, [regex]::Escape($ReplaceToken)).Count
    if ($replaceCount -ne 1) {
        throw "Expected exactly one occurrence of '$ReplaceToken' in base response; found $replaceCount."
    }
    $content = $content.Replace($ReplaceToken, $ReplaceWithToken)
}

$resolvedCandidatePaths = [regex]::Matches($content, '"([^"]+\\[0-9a-fA-F]{8}\.obj)"') |
    ForEach-Object { $_.Groups[1].Value } |
    Where-Object { $_ -match [regex]::Escape($NewObjectDirectoryToken) }
if (@($resolvedCandidatePaths).Count -ne 705) {
    throw "Response file contains $(@($resolvedCandidatePaths).Count) remapped candidate objects, expected 705."
}
foreach ($path in $resolvedCandidatePaths) {
    if (-not (Test-Path -LiteralPath $path)) {
        throw "Candidate object missing from response file: $path"
    }
}

if ($IncludeCandidateCodeSymbols) {
    $includeSymbols = [System.Collections.Generic.HashSet[string]]::new([System.StringComparer]::Ordinal)
    foreach ($candidate in $candidateObjects) {
        $bytes = [System.IO.File]::ReadAllBytes($candidate.FullName)
        if ($bytes.Length -lt 20 -or [BitConverter]::ToUInt16($bytes, 0) -ne 0x14c) {
            throw "Expected an x86 COFF object: $($candidate.FullName)"
        }
        $sectionCount = [BitConverter]::ToUInt16($bytes, 2)
        $symbolPointer = [BitConverter]::ToUInt32($bytes, 8)
        $symbolCount = [BitConverter]::ToUInt32($bytes, 12)
        if ([BitConverter]::ToUInt16($bytes, 16) -ne 0) {
            throw "Unexpected optional header in COFF object: $($candidate.FullName)"
        }
        $sectionNames = @{}
        for ($sectionIndex = 0; $sectionIndex -lt $sectionCount; $sectionIndex++) {
            $sectionAt = 20 + $sectionIndex * 40
            $sectionName = [Text.Encoding]::ASCII.GetString($bytes, $sectionAt, 8).Trim([char]0)
            $sectionNames[$sectionIndex + 1] = $sectionName
        }
        $stringsAt = [int64]$symbolPointer + [int64]$symbolCount * 18
        if ($stringsAt + 4 -gt $bytes.Length) { throw "Missing COFF string table: $($candidate.FullName)" }
        $stringLength = [BitConverter]::ToUInt32($bytes, [int]$stringsAt)
        if ($stringsAt + $stringLength -gt $bytes.Length) { throw "Invalid COFF string table: $($candidate.FullName)" }
        for ($symbolIndex = 0; $symbolIndex -lt $symbolCount;) {
            $symbolAt = [int64]$symbolPointer + [int64]$symbolIndex * 18
            $namePrefix = [BitConverter]::ToUInt32($bytes, [int]$symbolAt)
            if ($namePrefix -eq 0) {
                $nameOffset = [BitConverter]::ToUInt32($bytes, [int]$symbolAt + 4)
                $nameAt = [int]$stringsAt + [int]$nameOffset
                $nameEnd = $nameAt
                while ($nameEnd -lt $stringsAt + $stringLength -and $bytes[$nameEnd] -ne 0) { $nameEnd++ }
                $symbolName = [Text.Encoding]::ASCII.GetString($bytes, $nameAt, $nameEnd - $nameAt)
            }
            else {
                $symbolName = [Text.Encoding]::ASCII.GetString($bytes, [int]$symbolAt, 8).Trim([char]0)
            }
            $sectionNumber = [BitConverter]::ToInt16($bytes, [int]$symbolAt + 12)
            $storageClass = $bytes[[int]$symbolAt + 16]
            if ($storageClass -eq 2 -and $sectionNumber -gt 0 -and
                $sectionNames.ContainsKey([int]$sectionNumber) -and
                ($sectionNames[[int]$sectionNumber].StartsWith('.text', [StringComparison]::Ordinal) -or
                 $sectionNames[[int]$sectionNumber].StartsWith('.xcode', [StringComparison]::Ordinal))) {
                [void]$includeSymbols.Add($symbolName)
            }
            $auxCount = $bytes[[int]$symbolAt + 17]
            $symbolIndex += 1 + $auxCount
        }
    }
    if ($includeSymbols.Count -lt 705) {
        throw "Candidate public code symbols found in COFF objects: $($includeSymbols.Count); expected at least 705."
    }
    $content += [Environment]::NewLine + (($includeSymbols | Sort-Object | ForEach-Object { '"/INCLUDE:' + $_ + '"' }) -join [Environment]::NewLine)
    Write-Host "Added /INCLUDE roots for $($includeSymbols.Count) externally visible candidate code symbols from COFF symbol tables"
}
if ($OrderFile) {
    $orderPath = (Resolve-Path (Join-Path $root $OrderFile)).Path
    $content += [Environment]::NewLine + '"/ORDER:@' + $orderPath + '"'
    Write-Host "Added MSVC COMDAT order file: $orderPath"
}

[System.IO.File]::WriteAllText($rspOut, $content, [System.Text.UTF8Encoding]::new($false))

Write-Host "Prepared diagnostic link response with 705 current candidate objects: $rspOut"
& link.exe "@$rspOut"
if ($LASTEXITCODE -ne 0) {
    throw "Diagnostic linker failed with exit code $LASTEXITCODE."
}
