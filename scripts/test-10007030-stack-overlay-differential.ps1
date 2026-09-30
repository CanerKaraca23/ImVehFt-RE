param(
    [string]$ReferenceBinaryPath = 'C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi',
    [string]$CandidateSource = 'src/functions/10007030.cpp',
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
$expectedHash = '409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3'
$actualHash = Get-Sha256Hex $ReferenceBinaryPath
if ($actualHash -ne $expectedHash) {
    throw "Reference ASI hash mismatch: $actualHash"
}

$root = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$candidatePath = Join-Path $root $CandidateSource
if (-not (Test-Path -LiteralPath $candidatePath)) {
    throw "Candidate source not found: $candidatePath"
}
if ([string]::IsNullOrWhiteSpace($OutputDirectory)) {
    $OutputDirectory = 'build/abi-harness/10007030-stack-overlay-diff-' +
        (Get-Date -Format 'yyyyMMdd-HHmmss-fff')
}
$outputRoot = Join-Path $root $OutputDirectory
if (Test-Path -LiteralPath $outputRoot) {
    throw "Refusing to overwrite existing output directory: $outputRoot"
}
New-Item -ItemType Directory -Path $outputRoot | Out-Null

$compiler = (Get-Command cl.exe -ErrorAction Stop).Source
$harnessSource = Join-Path $root 'tests/runtime_10007030_stack_overlay_differential.cpp'
$harnessObject = Join-Path $outputRoot 'runtime_10007030_stack_overlay_differential.obj'
$candidateObject = Join-Path $outputRoot '10007030.obj'
$exePath = Join-Path $outputRoot '10007030-stack-overlay-differential.exe'
$mapPath = Join-Path $outputRoot '10007030-stack-overlay-differential.map'

foreach ($compile in @(
    @{ Source = $harnessSource; Object = $harnessObject },
    @{ Source = $candidatePath; Object = $candidateObject }
)) {
    $diagnostics = & $compiler /nologo /std:c++20 /O2 /W4 /WX /MT /GS `
        /arch:IA32 "/I$(Join-Path $root 'src/functions')" /c `
        $compile.Source "/Fo$($compile.Object)" 2>&1
    if ($LASTEXITCODE -ne 0) {
        $diagnostics | ForEach-Object { [Console]::Error.WriteLine($_) }
        throw "Compile failed for $($compile.Source) (exit $LASTEXITCODE)."
    }
}

$diagnostics = & $compiler /nologo /MT $harnessObject $candidateObject `
    "/Fe$exePath" /link "/MAP:$mapPath" 2>&1
if ($LASTEXITCODE -ne 0) {
    $diagnostics | ForEach-Object { [Console]::Error.WriteLine($_) }
    throw "Harness link failed (exit $LASTEXITCODE)."
}

& $exePath $ReferenceBinaryPath $mapPath
if ($LASTEXITCODE -ne 0) {
    throw "Original-binary stack-overlay differential failed (exit $LASTEXITCODE)."
}

Write-Host "Reference ASI SHA-256: $actualHash"
Write-Host "Candidate SHA-256: $(Get-Sha256Hex $candidatePath)"
Write-Host "Harness SHA-256: $(Get-Sha256Hex $harnessSource)"
Write-Host "Executable SHA-256: $(Get-Sha256Hex $exePath)"
Write-Host "Executable: $exePath"
