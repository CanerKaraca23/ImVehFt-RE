param(
    [string]$ObjectPath = 'build/recheck/strict-xcode-nogs-o1-exception-fix-20260929/100014a0.obj',
    [string]$ReferenceBinaryPath = 'C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi',
    [string]$OutputPath = '',
    [ValidateRange(1, 100)]
    [int]$Repetitions = 10
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
$root = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$object = Join-Path $root $ObjectPath
$source = Join-Path $root 'tests/runtime_100014a0_original_binary_differential.cpp'
$expectedReferenceHash = '409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3'
$expectedObjectHash = 'FC90C7C83512DF7539F3160171386CC683F33FD2D15833709328A7331117BF11'
if ([string]::IsNullOrWhiteSpace($OutputPath)) {
    $OutputPath = 'build/abi-harness/100014a0-original-differential-' +
        (Get-Date -Format 'yyyyMMdd-HHmmss-fff') + '.exe'
}
$output = Join-Path $root $OutputPath

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
    throw 'Candidate 100014a0 object hash changed; refresh evidence before testing.'
}
if (Test-Path -LiteralPath $output) { throw "Refusing to overwrite $output" }
New-Item -ItemType Directory -Path (Split-Path -Parent $output) -Force | Out-Null
$compiler = Get-Command cl.exe -ErrorAction Stop
$diagnostics = & $compiler.Source /nologo /std:c++20 /O1 /W4 /WX /MT /arch:IA32 /GS- `
    $source $object "/Fe$output" 2>&1
if ($LASTEXITCODE -ne 0) { $diagnostics | ForEach-Object { Write-Error $_ }; throw 'Harness build failed.' }
$passed = 0
for ($run = 1; $run -le $Repetitions; ++$run) {
    & $output $ReferenceBinaryPath *> $null
    if ($LASTEXITCODE -ne 0) { throw "Harness run $run/$Repetitions failed (exit $LASTEXITCODE)." }
    ++$passed
}
Write-Host "100014a0 heap-message exception-copy differential: $passed/$Repetitions fresh processes, 64 cases each."
Write-Host "Harness SHA-256: $(Get-Sha256Hex $output)"
Write-Host "Executable: $output"
