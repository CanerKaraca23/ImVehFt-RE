param(
    [string]$ObjectPath = 'build/recheck/strict-fputs-asm-rerun-20260929/10010913.obj',
    [string]$ReferenceBinaryPath = 'C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi',
    [string]$OutputPath = 'build/abi-harness/10010913-fputs-original-differential-verified-20260929.exe',
    [ValidateRange(1, 100)]
    [int]$Repetitions = 5
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
$root = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$object = Join-Path $root $ObjectPath
$source = Join-Path $root 'tests/runtime_10010913_fputs_original_differential.cpp'
$output = Join-Path $root $OutputPath
$expectedReferenceHash = '409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3'
$expectedObjectHash = '2604C67C9972909FBFD92F5A84E4B612AD3D18E18378CECE4A5753FEADA59D45'

function Get-Sha256Hex([string]$Path) {
    $algorithm = [System.Security.Cryptography.SHA256]::Create()
    $stream = [System.IO.File]::OpenRead($Path)
    try { return ([System.BitConverter]::ToString($algorithm.ComputeHash($stream))).Replace('-', '') }
    finally { $stream.Dispose(); $algorithm.Dispose() }
}

if (-not (Test-Path -LiteralPath $object)) { throw "Candidate object missing: $object" }
if (-not (Test-Path -LiteralPath $source)) { throw "Harness source missing: $source" }
if ((Get-Sha256Hex $ReferenceBinaryPath) -ne $expectedReferenceHash) {
    throw 'Original ImVehFt.asi hash does not match the pinned reference.'
}
if ((Get-Sha256Hex $object) -ne $expectedObjectHash) {
    throw 'Candidate 10010913 object hash changed; refresh evidence before testing.'
}
if (Test-Path -LiteralPath $output) { throw "Refusing to overwrite $output" }
if (-not $env:VCToolsInstallDir -or -not $env:WindowsSdkDir) {
    $vcvars = 'C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat'
    $envLines = & cmd.exe /c "call `"$vcvars`" x86 >nul && set"
    foreach ($line in $envLines) {
        if ($line -match '^([^=]+)=(.*)$') {
            [Environment]::SetEnvironmentVariable($matches[1], $matches[2], 'Process')
        }
    }
}

New-Item -ItemType Directory -Path (Split-Path -Parent $output) -Force | Out-Null
$compiler = Get-Command cl.exe -ErrorAction Stop
$diagnostics = & $compiler.Source /nologo /std:c++20 /O1 /W4 /WX /MT /arch:IA32 /GS- `
    $source $object "/Fe$output" 2>&1
if ($LASTEXITCODE -ne 0) {
    $diagnostics | ForEach-Object { Write-Error $_ }
    throw 'Harness build failed.'
}

for ($run = 1; $run -le $Repetitions; ++$run) {
    $result = & $output $ReferenceBinaryPath 2>&1
    if ($LASTEXITCODE -ne 0) {
        $result | ForEach-Object { Write-Error $_ }
        throw "Harness run $run/$Repetitions failed (exit $LASTEXITCODE)."
    }
    $result | ForEach-Object { Write-Host $_ }
}
Write-Host "10010913 fputs differential: $Repetitions fresh processes, 10 controlled cases each."
Write-Host "Original ASI SHA-256: $(Get-Sha256Hex $ReferenceBinaryPath)"
Write-Host "Candidate object SHA-256: $(Get-Sha256Hex $object)"
Write-Host "Harness SHA-256: $(Get-Sha256Hex $output)"
Write-Host "Executable: $output"
