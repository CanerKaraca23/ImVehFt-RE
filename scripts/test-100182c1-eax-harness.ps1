param(
    [string]$ObjectPath = 'build/recheck/strict-all-eax-bridge-20260928/100182c1.obj',
    [string]$OutputPath = 'build/abi-harness/100182c1-eax-output-harness.exe'
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

if (-not $env:VCToolsInstallDir -or -not $env:WindowsSdkDir) {
    throw 'Run this script from a VS 2022 Developer environment initialized for x86.'
}

$root = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$object = Join-Path $root $ObjectPath
$source = Join-Path $root 'tests/abi/100182c1_eax_output_harness.cpp'
$output = Join-Path $root $OutputPath
$outputDirectory = Split-Path -Parent $output

if (-not (Test-Path -LiteralPath $object)) {
    throw "Candidate object not found: $object"
}
if (-not (Test-Path -LiteralPath $source)) {
    throw "Harness source not found: $source"
}
if (Test-Path -LiteralPath $output) {
    throw "Refusing to overwrite harness executable: $output"
}
New-Item -ItemType Directory -Path $outputDirectory -Force | Out-Null

$compiler = Get-Command cl.exe -ErrorAction Stop
$diagnostics = & $compiler.Source /nologo /std:c++20 /O2 /W4 /WX /MT `
    $source $object "/Fe$output" 2>&1
if ($LASTEXITCODE -ne 0) {
    $diagnostics | ForEach-Object { Write-Error $_ }
    throw "Harness build failed with exit code $LASTEXITCODE."
}

Write-Host "Built ABI harness: $output"
& $output
if ($LASTEXITCODE -ne 0) {
    throw "ABI harness failed with exit code $LASTEXITCODE."
}
