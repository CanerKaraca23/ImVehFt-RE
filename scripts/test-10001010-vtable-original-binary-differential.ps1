param(
    [string]$ObjectPath = 'build/recheck/strict-xcode-nogs-o1-current-705-20260929/10001010.obj',
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
$source = Join-Path $root 'tests/runtime_10001010_vtable_original_binary_differential.cpp'
$candidate = Join-Path $root 'src/functions/10001010.cpp'
$manifest = Join-Path $root 'audit/source-sha256.csv'
$expectedReferenceHash = '409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3'
$expectedCandidateHash = '53DDEE3B7841FB2C70BDD331A84E9FAB8B3208675435A121E39C8042B59C2BB7'
$expectedObjectHash = 'AA5FB7F60DE50E8CFF6BDA475908428029B15933DB524778CAF6D3809B7DDEF4'
if ([string]::IsNullOrWhiteSpace($OutputPath)) {
    $OutputPath = 'build/abi-harness/10001010-vtable-differential-' +
        (Get-Date -Format 'yyyyMMdd-HHmmss-fff') + '.exe'
}
$output = Join-Path $root $OutputPath

function Get-Sha256Hex([string]$Path) {
    $algorithm = [System.Security.Cryptography.SHA256]::Create()
    $stream = [System.IO.File]::OpenRead($Path)
    try { return ([System.BitConverter]::ToString($algorithm.ComputeHash($stream))).Replace('-', '') }
    finally { $stream.Dispose(); $algorithm.Dispose() }
}

if ((Get-Sha256Hex $ReferenceBinaryPath) -ne $expectedReferenceHash) {
    throw 'Original ImVehFt.asi hash does not match pinned reference.'
}
if ((Get-Sha256Hex $candidate) -ne $expectedCandidateHash) {
    throw 'Candidate source hash changed; refresh evidence before testing.'
}
$manifestRow = Import-Csv -LiteralPath $manifest | Where-Object address -eq '10001010'
if (-not $manifestRow -or $manifestRow.sha256 -ne $expectedCandidateHash.ToLowerInvariant()) {
    throw 'Current source manifest does not match the hash-pinned candidate.'
}
if ((Get-Sha256Hex $object) -ne $expectedObjectHash) {
    throw 'Candidate object hash changed; refresh evidence before testing.'
}
if (Test-Path -LiteralPath $output) { throw "Refusing to overwrite $output" }
New-Item -ItemType Directory -Path (Split-Path -Parent $output) -Force | Out-Null
$compiler = Get-Command cl.exe -ErrorAction Stop
$diagnostics = & $compiler.Source /nologo /std:c++20 /O1 /W4 /WX /MT /arch:IA32 /GS- `
    $source $object "/Fe$output" 2>&1
if ($LASTEXITCODE -ne 0) {
    $diagnostics | ForEach-Object { Write-Host $_ }
    throw 'Differential harness build failed.'
}
$passed = 0
for ($run = 1; $run -le $Repetitions; ++$run) {
    & $output $ReferenceBinaryPath *> $null
    if ($LASTEXITCODE -ne 0) { throw "Harness run $run/$Repetitions failed (exit $LASTEXITCODE)." }
    ++$passed
}
Write-Host "10001010 vtable/destruction differential: $passed/$Repetitions fresh processes, 128 cases each."
Write-Host "Candidate source SHA-256: $(Get-Sha256Hex $candidate)"
Write-Host "Candidate object SHA-256: $(Get-Sha256Hex $object)"
Write-Host "Harness executable SHA-256: $(Get-Sha256Hex $output)"
Write-Host "Executable: $output"
