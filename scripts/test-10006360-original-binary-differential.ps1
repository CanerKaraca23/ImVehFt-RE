param(
    [string]$ReferenceAsi = 'C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi',
    [string]$GtaExecutable = 'C:\Users\caner\OneDrive\Documents\GTA San Andreas\gta_sa.exe',
    [string]$ObjectRoot = 'build/recheck/strict-xcode-nogs-o1-10006360-fastcall-full-20260930',
    [string]$OutputDirectory = 'build/abi-harness/10006360-real-gta-math-differential-20260930'
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$reference = (Resolve-Path $ReferenceAsi).Path
$gta = (Resolve-Path $GtaExecutable).Path
$expectedHash = '409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3'
$expectedGtaHash = 'F01A00CE950FA40CA1ED59DF0E789848C6EDCF6405456274965885D0929343AC'
$sha = [System.Security.Cryptography.SHA256]::Create()
$actualHash = [BitConverter]::ToString(
    $sha.ComputeHash([IO.File]::ReadAllBytes($reference))).Replace('-', '')
if ($actualHash -ne $expectedHash) {
    throw "Pinned reference hash mismatch: $actualHash"
}
$actualGtaHash = [BitConverter]::ToString(
    $sha.ComputeHash([IO.File]::ReadAllBytes($gta))).Replace('-', '')
if ($actualGtaHash -ne $expectedGtaHash) {
    throw "Pinned GTA executable hash mismatch: $actualGtaHash"
}

$outDir = Join-Path $repoRoot $OutputDirectory
if (Test-Path -LiteralPath $outDir) {
    throw "Refusing to overwrite existing harness output: $outDir"
}
$null = New-Item -ItemType Directory -Path $outDir
$compiler = Get-Command cl.exe -ErrorAction Stop
$linker = Get-Command link.exe -ErrorAction Stop
$candidateObject = Join-Path $repoRoot "$ObjectRoot/10006360.obj"
$helperObject = Join-Path $repoRoot "$ObjectRoot/10010120.obj"
foreach ($object in @($candidateObject, $helperObject)) {
    if (-not (Test-Path -LiteralPath $object -PathType Leaf)) {
        throw "Current candidate object is missing: $object"
    }
}

$harnessSource = Join-Path $repoRoot 'tests/runtime_10006360_original_binary_differential.cpp'
$harnessObject = Join-Path $outDir 'runtime_10006360_original_binary_differential.obj'
$exe = Join-Path $outDir 'runtime_10006360_original_binary_differential.exe'
$compileArgs = @('/nologo', '/std:c++20', '/O1', '/W4', '/WX', '/MT',
    '/arch:IA32', '/GS-', '/c', $harnessSource, "/Fo$harnessObject")
& $compiler.Source @compileArgs
if ($LASTEXITCODE -ne 0) { throw "Harness compile failed: $LASTEXITCODE" }

$linkArgs = @('/nologo', '/MACHINE:X86', '/SUBSYSTEM:CONSOLE', "/OUT:$exe",
    '/BASE:0x02000000', '/DYNAMICBASE:NO', $harnessObject,
    $candidateObject, $helperObject, '/INCREMENTAL:NO')
& $linker.Source @linkArgs
if ($LASTEXITCODE -ne 0) { throw "Harness link failed: $LASTEXITCODE" }

& $exe $reference $gta
if ($LASTEXITCODE -ne 0) { throw "Harness returned failure: $LASTEXITCODE" }
"Harness SHA-256: $([BitConverter]::ToString($sha.ComputeHash([IO.File]::ReadAllBytes($harnessSource))).Replace('-', ''))"
"Executable SHA-256: $([BitConverter]::ToString($sha.ComputeHash([IO.File]::ReadAllBytes($exe))).Replace('-', ''))"
