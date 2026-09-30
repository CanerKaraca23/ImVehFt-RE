param(
    [string]$ObjectPath = 'build/recheck/strict-xcode-nogs-o1-ret-cleanup-final2-20260929/100110bd.obj',
    [string]$ExpectedObjectHash = '4527EE4ACE5C66C85F144DEB406A0D184F8BD4632D195D59F2C1B18FEED0A8EA',
    [string]$EntryObjectPath = 'build/recheck/strict-xcode-nogs-o1-ret-cleanup-final2-20260929/100111b3.obj',
    [string]$ExpectedEntryObjectHash = '8ACD7828EE97838AB647C18162A648B938A327EFB1247098E2EFD933D01500C0',
    [string]$ReferenceBinaryPath = 'C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi',
    [ValidateRange(1, 100)]
    [int]$Repetitions = 5
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
if (-not $env:VCToolsInstallDir -or -not $env:WindowsSdkDir) {
    throw 'Run this script from a VS 2022 Developer environment initialized for x86.'
}

$root = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$object = Join-Path $root $ObjectPath
$entryObject = Join-Path $root $EntryObjectPath
$source = Join-Path $root 'tests/runtime_100110bd_stack_cleanup_differential.cpp'
$expectedReferenceHash = '409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3'
$expectedHarnessSourceHash = 'F1F217B49B0ED692F77ECC2F9786E4297F73472A6F3CD7E6FA1D143D5759EF4B'
$output = Join-Path $root ('build/abi-harness/100110bd-stack-cleanup-' +
    (Get-Date -Format 'yyyyMMdd-HHmmss-fff') + '.exe')

function Get-Sha256Hex([string]$Path) {
    $algorithm = [System.Security.Cryptography.SHA256]::Create()
    $stream = [System.IO.File]::OpenRead($Path)
    try { return ([System.BitConverter]::ToString($algorithm.ComputeHash($stream))).Replace('-', '') }
    finally { $stream.Dispose(); $algorithm.Dispose() }
}

if ((Get-Sha256Hex $ReferenceBinaryPath) -ne $expectedReferenceHash) {
    throw 'Original ImVehFt.asi hash does not match the pinned reference.'
}
if ((Get-Sha256Hex $object) -ne $ExpectedObjectHash) {
    throw 'Candidate object hash changed; refresh evidence before testing.'
}
if ((Get-Sha256Hex $entryObject) -ne $ExpectedEntryObjectHash) {
    throw 'Candidate entry object hash changed; refresh evidence before testing.'
}
if ((Get-Sha256Hex $source) -ne $expectedHarnessSourceHash) {
    throw 'Harness source hash changed; refresh evidence before testing.'
}
New-Item -ItemType Directory -Path (Split-Path -Parent $output) -Force | Out-Null
$compiler = Get-Command cl.exe -ErrorAction Stop
$diagnostics = & $compiler.Source /nologo /std:c++20 /O1 /W4 /WX /MT /arch:IA32 /GS- `
    $source $object $entryObject "/Fe$output" 2>&1
if ($LASTEXITCODE -ne 0) {
    $diagnostics | ForEach-Object { Write-Host $_ }
    throw 'Stack-cleanup differential harness build failed.'
}

for ($run = 1; $run -le $Repetitions; ++$run) {
    & $output $ReferenceBinaryPath
    if ($LASTEXITCODE -ne 0) {
        throw "Harness run $run/$Repetitions failed (exit $LASTEXITCODE)."
    }
}
Write-Host "Harness SHA-256: $(Get-Sha256Hex $output)"
Write-Host "Executable: $output"
