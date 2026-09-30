param(
    [string]$ObjectPath = 'build/recheck/strict-xcode-nogs-o1-exception-fix-20260929/100076d0.obj',
    [string]$ReferenceBinaryPath = 'C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi',
    [string]$OutputPath = '',
    [ValidateRange(1, 100)]
    [int]$Repetitions = 10
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

if (-not $env:VCToolsInstallDir -or -not $env:WindowsSdkDir) {
    throw 'Run this script from a VS 2022 Developer environment initialized for x86.'
}

$root = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$object = Join-Path $root $ObjectPath
$source = Join-Path $root 'tests/runtime_100076d0_model_info_harness.cpp'
$expectedReferenceHash = '409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3'
if ([string]::IsNullOrWhiteSpace($OutputPath)) {
    $stamp = Get-Date -Format 'yyyyMMdd-HHmmss-fff'
    $OutputPath = "build/abi-harness/100076d0-model-info-harness-$stamp.exe"
}
$output = Join-Path $root $OutputPath
$outputDirectory = Split-Path -Parent $output

if (-not (Test-Path -LiteralPath $object)) {
    throw "Candidate object not found: $object"
}
if (-not (Test-Path -LiteralPath $source)) {
    throw "Harness source not found: $source"
}
if (-not (Test-Path -LiteralPath $ReferenceBinaryPath)) {
    throw "Reference ImVehFt.asi not found: $ReferenceBinaryPath"
}
if (Test-Path -LiteralPath $output) {
    throw "Refusing to overwrite harness executable: $output"
}
New-Item -ItemType Directory -Path $outputDirectory -Force | Out-Null

$compiler = Get-Command cl.exe -ErrorAction Stop
$diagnostics = & $compiler.Source /nologo /std:c++20 /O2 /W4 /WX /MT /GS `
    $source $object "/Fe$output" 2>&1
if ($LASTEXITCODE -ne 0) {
    $diagnostics | ForEach-Object { Write-Error $_ }
    throw "Harness build failed with exit code $LASTEXITCODE."
}

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

$actualReferenceHash = Get-Sha256Hex $ReferenceBinaryPath
if ($actualReferenceHash -ne $expectedReferenceHash) {
    throw "Reference ImVehFt.asi hash mismatch: $actualReferenceHash"
}

for ($run = 1; $run -le $Repetitions; ++$run) {
    & $output $ReferenceBinaryPath *> $null
    if ($LASTEXITCODE -ne 0) {
        throw "Harness run $run/$Repetitions failed with exit code $LASTEXITCODE."
    }
}

$objectHash = Get-Sha256Hex $object
$outputHash = Get-Sha256Hex $output
Write-Host "PE32/x86 candidate-object harness: $Repetitions/$Repetitions fresh processes passed."
Write-Host "Original ImVehFt.asi SHA-256: $actualReferenceHash"
Write-Host "Object SHA-256: $objectHash"
Write-Host "Harness SHA-256: $outputHash"
Write-Host "Executable: $output"
