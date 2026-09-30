param(
    [string]$OutputDirectory,
    [ValidateRange(0, 1000000)][uint32]$RandomPatternCount = 4096
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

if (-not $env:VCToolsInstallDir -or -not $env:WindowsSdkDir) {
    throw 'Run this script from a VS 2022 Developer environment initialized for x86.'
}

$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
if ([string]::IsNullOrWhiteSpace($OutputDirectory)) {
    $OutputDirectory = 'build/abi-harness/1001ba40-original-binary-diff-' +
        (Get-Date -Format 'yyyyMMdd-HHmmss-fff')
}
$outputRoot = Join-Path $repoRoot $OutputDirectory
$exePath = Join-Path $outputRoot '1001ba40-original-binary-differential.exe'
if (Test-Path -LiteralPath $outputRoot) {
    throw "Refusing to overwrite existing output directory: $outputRoot"
}

New-Item -ItemType Directory -Path $outputRoot | Out-Null
$compiler = (Get-Command cl.exe -ErrorAction Stop).Source
$harness = Join-Path $repoRoot 'tests/runtime_1001ba40_binary_differential.cpp'
$candidate = Join-Path $repoRoot 'src/functions/1001ba40.cpp'

$diagnostics = & $compiler /nologo /std:c++20 /O2 /W4 /WX /MT /c `
    "/DIVF_RANDOM_PATTERN_COUNT=$RandomPatternCount" `
    $harness "/Fo$(Join-Path $outputRoot 'harness.obj')" 2>&1
if ($LASTEXITCODE -ne 0) {
    $diagnostics | ForEach-Object { Write-Error $_ }
    throw "Harness compile failed (exit $LASTEXITCODE)."
}

$diagnostics = & $compiler /nologo /std:c++20 /O2 /W4 /WX /MT /c `
    $candidate "/Fo$(Join-Path $outputRoot 'candidate.obj')" 2>&1
if ($LASTEXITCODE -ne 0) {
    $diagnostics | ForEach-Object { Write-Error $_ }
    throw "Candidate helper compile failed (exit $LASTEXITCODE)."
}

$diagnostics = & $compiler /nologo /MT `
    (Join-Path $outputRoot 'harness.obj') `
    (Join-Path $outputRoot 'candidate.obj') "/Fe$exePath" 2>&1
if ($LASTEXITCODE -ne 0) {
    $diagnostics | ForEach-Object { Write-Error $_ }
    throw "Harness link failed (exit $LASTEXITCODE)."
}

Write-Host "Built x86 binary-differential harness: $exePath"
& $exePath
if ($LASTEXITCODE -ne 0) {
    throw "Binary-differential test failed (exit $LASTEXITCODE)."
}
