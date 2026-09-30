param(
    [string]$ReferenceBinaryPath = 'C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi',
    [string]$OutputDirectory = ''
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

function Get-Sha256Hex([string]$Path) {
    $algorithm = [System.Security.Cryptography.SHA256]::Create()
    $stream = [System.IO.File]::OpenRead($Path)
    try {
        return ([System.BitConverter]::ToString(
            $algorithm.ComputeHash($stream))).Replace('-', '')
    }
    finally {
        $stream.Dispose()
        $algorithm.Dispose()
    }
}

if (-not $env:VCToolsInstallDir -or -not $env:WindowsSdkDir) {
    throw 'Run this script from a VS 2022 Developer environment initialized for x86.'
}
if (-not (Test-Path -LiteralPath $ReferenceBinaryPath)) {
    throw "Reference ImVehFt.asi not found: $ReferenceBinaryPath"
}
$expectedReferenceHash = '409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3'
$actualReferenceHash = Get-Sha256Hex $ReferenceBinaryPath
if ($actualReferenceHash -ne $expectedReferenceHash) {
    throw "Reference ASI hash mismatch: $actualReferenceHash"
}

$root = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
if ([string]::IsNullOrWhiteSpace($OutputDirectory)) {
    $OutputDirectory = 'build/abi-harness/10006be0-original-binary-diff-' +
        (Get-Date -Format 'yyyyMMdd-HHmmss-fff')
}
$outputRoot = Join-Path $root $OutputDirectory
if (Test-Path -LiteralPath $outputRoot) {
    throw "Refusing to overwrite existing output directory: $outputRoot"
}
New-Item -ItemType Directory -Path $outputRoot | Out-Null

$compiler = (Get-Command cl.exe -ErrorAction Stop).Source
$sources = @(
    (Join-Path $root 'tests/runtime_10006be0_original_binary_differential.cpp'),
    (Join-Path $root 'src/functions/10006be0.cpp'),
    (Join-Path $root 'src/functions/1001ba40.cpp')
)
$exePath = Join-Path $outputRoot '10006be0-original-binary-differential.exe'
$mapPath = Join-Path $outputRoot '10006be0-original-binary-differential.map'
$objectDirectory = $outputRoot.TrimEnd('\') + '\'
$diagnostics = & $compiler /nologo /std:c++20 /O2 /W4 /WX /MT /GS /arch:IA32 `
    $sources "/Fo$objectDirectory" "/Fe$exePath" /link "/MAP:$mapPath" 2>&1
if ($LASTEXITCODE -ne 0) {
    $diagnostics | ForEach-Object { [Console]::Error.WriteLine($_) }
    throw "Differential harness compile/link failed with exit code $LASTEXITCODE."
}

& $exePath $ReferenceBinaryPath $mapPath
if ($LASTEXITCODE -ne 0) {
    throw "Original-binary differential failed with exit code $LASTEXITCODE."
}
$exeHash = Get-Sha256Hex $exePath
Write-Host "Reference ASI SHA-256: $actualReferenceHash"
Write-Host "Harness SHA-256: $exeHash"
Write-Host "Executable: $exePath"
