param(
    [string]$ReferenceAsi = 'C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi',
    [string]$ObjectRoot = 'build/recheck/strict-xcode-nogs-o1-100074d0-aee1-global-20260930',
    [string]$OutputDirectory = 'build/abi-harness/100069e0-caller-contract-recheck-20260929'
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$reference = (Resolve-Path $ReferenceAsi).Path
$expectedHash = '409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3'
$sha = [System.Security.Cryptography.SHA256]::Create()
$actualHash = [BitConverter]::ToString(
    $sha.ComputeHash([IO.File]::ReadAllBytes($reference))).Replace('-', '')
if ($actualHash -ne $expectedHash) {
    throw "Pinned reference hash mismatch: $actualHash"
}

$outDir = Join-Path $repoRoot $OutputDirectory
if (Test-Path -LiteralPath $outDir) {
    throw "Refusing to overwrite existing harness output: $outDir"
}
$null = New-Item -ItemType Directory -Path $outDir
$compiler = Get-Command cl.exe -ErrorAction Stop
$linker = Get-Command link.exe -ErrorAction Stop
$candidateObject = Join-Path $repoRoot "$ObjectRoot/10006790.obj"
$candidateObjects = @(
    $candidateObject,
    (Join-Path $repoRoot "$ObjectRoot/10003f80.obj"),
    (Join-Path $repoRoot "$ObjectRoot/10003fb0.obj"),
    (Join-Path $repoRoot "$ObjectRoot/10003fe0.obj"),
    (Join-Path $repoRoot "$ObjectRoot/100069e0.obj"),
    (Join-Path $repoRoot "$ObjectRoot/10006ad0.obj"),
    (Join-Path $repoRoot "$ObjectRoot/100074d0.obj")
)
foreach ($object in $candidateObjects) {
    if (-not (Test-Path -LiteralPath $object -PathType Leaf)) {
        throw "Current candidate object is missing: $object"
    }
}

$harnessSource = Join-Path $repoRoot 'tests/runtime_10006790_cmatrix_setrotatexonly_differential.cpp'
$harnessObject = Join-Path $outDir 'runtime_10006790_cmatrix_setrotatexonly_differential.obj'
$exe = Join-Path $outDir 'runtime_10006790_cmatrix_setrotatexonly_differential.exe'
$compileArgs = @('/nologo', '/std:c++20', '/O1', '/W4', '/WX', '/MT',
    '/arch:IA32', '/GS-', '/c', $harnessSource, "/Fo$harnessObject")
& $compiler.Source @compileArgs
if ($LASTEXITCODE -ne 0) { throw "Harness compile failed: $LASTEXITCODE" }

$linkArgs = @('/nologo', '/MACHINE:X86', '/SUBSYSTEM:CONSOLE', "/OUT:$exe",
    '/BASE:0x00400000', '/DYNAMICBASE:NO', $harnessObject,
    $candidateObjects, '/INCREMENTAL:NO')
& $linker.Source @linkArgs
if ($LASTEXITCODE -ne 0) { throw "Harness link failed: $LASTEXITCODE" }

& $exe $reference
if ($LASTEXITCODE -ne 0) { throw "Harness returned failure: $LASTEXITCODE" }
"Harness SHA-256: $([BitConverter]::ToString($sha.ComputeHash([IO.File]::ReadAllBytes($harnessSource))).Replace('-', ''))"
"Executable SHA-256: $([BitConverter]::ToString($sha.ComputeHash([IO.File]::ReadAllBytes($exe))).Replace('-', ''))"
