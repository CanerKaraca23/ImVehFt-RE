param(
    [Parameter(Mandatory = $true)][string]$BaseResponseFile,
    [Parameter(Mandatory = $true)][string]$ThunkObject,
    [Parameter(Mandatory = $true)][string]$ResponseFile,
    [Parameter(Mandatory = $true)][string]$OldOutputToken,
    [Parameter(Mandatory = $true)][string]$NewOutputToken,
    [Parameter(Mandatory = $true)][string]$OldMapToken,
    [Parameter(Mandatory = $true)][string]$NewMapToken
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

$root = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$basePath = (Resolve-Path (Join-Path $root $BaseResponseFile)).Path
$thunkPath = (Resolve-Path (Join-Path $root $ThunkObject)).Path
$responsePath = Join-Path $root $ResponseFile
if (Test-Path -LiteralPath $responsePath) {
    throw "Refusing to overwrite response file: $responsePath"
}

$text = [System.IO.File]::ReadAllText($basePath)
foreach ($pair in @(
    @($OldOutputToken, $NewOutputToken),
    @($OldMapToken, $NewMapToken)
)) {
    $count = [regex]::Matches($text, [regex]::Escape($pair[0])).Count
    if ($count -ne 1) { throw "Expected exactly one '$($pair[0])' in base response; found $count." }
    $text = $text.Replace($pair[0], $pair[1])
}

$candidateObjectCount = [regex]::Matches($text, '(?im)^"[^"]*\\[0-9a-f]{8}\.obj"\r?$').Count
if ($candidateObjectCount -ne 705) {
    throw "Expected exactly 705 candidate object entries; found $candidateObjectCount."
}
if ($text.Contains('"' + $thunkPath + '"')) { throw 'Thunk object is already in the response file.' }

$lines = [System.Collections.Generic.List[string]]::new()
$inserted = $false
foreach ($line in $text -split "`r?`n") {
    if (-not $inserted -and $line -match '(?i)\.lib"\s*$') {
        $lines.Add('"' + $thunkPath + '"')
        $inserted = $true
    }
    $lines.Add($line)
}
if (-not $inserted) { throw 'No explicit library boundary found for safe object insertion.' }

$parent = Split-Path -Parent $responsePath
if (-not (Test-Path -LiteralPath $parent)) { New-Item -ItemType Directory -Path $parent -Force | Out-Null }
[System.IO.File]::WriteAllText($responsePath, ($lines -join "`r`n"), [System.Text.UTF8Encoding]::new($false))

& link.exe "@$responsePath"
if ($LASTEXITCODE -ne 0) { throw "Diagnostic API-thunk link failed with exit code $LASTEXITCODE." }
Write-Host "Linked 705 candidate objects plus original-IAT API thunk object: $responsePath"
Write-Host 'Output is a diagnostic DLL; the thunk DIR32 fixups still target the diagnostic DLL import table.'
