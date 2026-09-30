param(
    [string]$ReferenceAsi = 'C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi',
    [string]$ObjectRoot = 'build/recheck/strict-xcode-nogs-o1-10003f80-fix-20260929',
    [string]$OutputDirectory = 'build/abi-harness/10003f80-callback-abi-20260929'
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$reference = (Resolve-Path $ReferenceAsi).Path
$expectedHash = '409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3'
$sha = [System.Security.Cryptography.SHA256]::Create()
$actualHash = [BitConverter]::ToString($sha.ComputeHash([IO.File]::ReadAllBytes($reference))).Replace('-', '')
if ($actualHash -ne $expectedHash) {
    throw "Pinned reference hash mismatch: $actualHash"
}

$outDir = Join-Path $repoRoot $OutputDirectory
if (Test-Path -LiteralPath $outDir) {
    throw "Refusing to overwrite existing harness output: $outDir"
}
$null = New-Item -ItemType Directory -Path $outDir
$compiler = Get-Command cl.exe -ErrorAction Stop
$forcedHeader = Join-Path $repoRoot 'tests/layout_probe/candidate_xcode_seg.hpp'
$harnessSource = Join-Path $repoRoot 'tests/runtime_10003f80_callback_abi.cpp'
$harnessObject = Join-Path $outDir 'runtime_10003f80_callback_abi.obj'
$exe = Join-Path $outDir 'runtime_10003f80_callback_abi.exe'
$candidateObjects = @(
    (Join-Path $repoRoot "$ObjectRoot/10003f80.obj"),
    (Join-Path $repoRoot "$ObjectRoot/10003fb0.obj"),
    (Join-Path $repoRoot "$ObjectRoot/10003fe0.obj")
)
foreach ($object in $candidateObjects) {
    if (-not (Test-Path -LiteralPath $object -PathType Leaf)) {
        throw "Required candidate object is missing: $object"
    }
}

$compileArgs = @('/nologo', '/std:c++20', '/O1', '/W4', '/WX', '/MT',
    '/arch:IA32', '/GS-', "/FI$forcedHeader", '/c', $harnessSource,
    "/Fo$harnessObject")
& $compiler.Source @compileArgs
if ($LASTEXITCODE -ne 0) { throw "Harness compile failed: $LASTEXITCODE" }

$linkArgs = @('/nologo', '/MACHINE:X86', '/SUBSYSTEM:CONSOLE',
    "/OUT:$exe", $harnessObject) + $candidateObjects + @('/INCREMENTAL:NO')
& link.exe @linkArgs
if ($LASTEXITCODE -ne 0) { throw "Harness link failed: $LASTEXITCODE" }

& $exe $reference
if ($LASTEXITCODE -ne 0) { throw "Harness returned failure: $LASTEXITCODE" }
$harnessHash = [BitConverter]::ToString($sha.ComputeHash([IO.File]::ReadAllBytes($harnessSource))).Replace('-', '')
$exeHash = [BitConverter]::ToString($sha.ComputeHash([IO.File]::ReadAllBytes($exe))).Replace('-', '')
"Harness SHA-256: $harnessHash"
"Executable SHA-256: $exeHash"
