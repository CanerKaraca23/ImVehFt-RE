param(
    [Parameter(Mandatory = $true)][string]$BaseResponseFile,
    [Parameter(Mandatory = $true)][string]$OldObjectDirectoryToken,
    [Parameter(Mandatory = $true)][string]$NewObjectDirectoryToken,
    [Parameter(Mandatory = $true)][string]$OldOutputToken,
    [Parameter(Mandatory = $true)][string]$NewOutputToken,
    [Parameter(Mandatory = $true)][string]$OldMapToken,
    [Parameter(Mandatory = $true)][string]$NewMapToken,
    [Parameter(Mandatory = $true)][string]$EntryTemplateObject,
    [Parameter(Mandatory = $true)][string]$ResponseFile
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
if (-not $env:VCToolsInstallDir -or -not $env:WindowsSdkDir) {
    throw 'Run from a VS 2022 Developer environment initialized for x86.'
}

$root = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$base = (Resolve-Path (Join-Path $root $BaseResponseFile)).Path
$entryObject = (Resolve-Path (Join-Path $root $EntryTemplateObject)).Path
$response = Join-Path $root $ResponseFile
$responseParent = Split-Path -Parent $response
if (-not (Test-Path -LiteralPath $responseParent)) {
    New-Item -ItemType Directory -Path $responseParent | Out-Null
}
if (Test-Path -LiteralPath $response) { throw "Refusing to overwrite response file: $response" }

$candidateObjects = @(Get-ChildItem -LiteralPath (Join-Path $root $NewObjectDirectoryToken) -File -Filter '*.obj')
if ($candidateObjects.Count -ne 705) { throw "Expected 705 candidate objects; found $($candidateObjects.Count)." }

$content = [System.IO.File]::ReadAllText($base)
$count = [regex]::Matches($content, [regex]::Escape($OldObjectDirectoryToken)).Count
if ($count -ne 705) { throw "Expected 705 old object-directory tokens; found $count." }
$content = $content.Replace($OldObjectDirectoryToken, (Join-Path $root $NewObjectDirectoryToken))
foreach ($replacement in @(
    @($OldOutputToken, $NewOutputToken),
    @($OldMapToken, $NewMapToken)
)) {
    $oldToken = [string]$replacement[0]
    $newToken = [string]$replacement[1]
    if ([regex]::Matches($content, [regex]::Escape($oldToken)).Count -ne 1) {
        throw "Expected exactly one response-file token: $oldToken"
    }
    $content = $content.Replace($oldToken, $newToken)
}

$firstCandidateLine = '"' + (Join-Path (Join-Path $root $NewObjectDirectoryToken) '10001010.obj') + '"'
$firstIndex = $content.IndexOf($firstCandidateLine, [StringComparison]::OrdinalIgnoreCase)
if ($firstIndex -lt 0) { throw 'Could not locate first candidate object in rewritten response.' }
$content = $content.Insert($firstIndex, '"' + $entryObject + '"' + [Environment]::NewLine)
[System.IO.File]::WriteAllText($response, $content, [System.Text.UTF8Encoding]::new($false))

Write-Host "Prepared response with exact original .text template before 705 .xcode objects: $response"
& link.exe "@$response"
if ($LASTEXITCODE -ne 0) { throw "Layout diagnostic link failed with exit code $LASTEXITCODE." }
