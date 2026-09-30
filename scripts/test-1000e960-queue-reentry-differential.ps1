param(
    [ValidateRange(1, 100)]
    [int]$Repetitions = 5
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
$root = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$source = Join-Path $root 'tests/runtime_1000e960_queue_reentry_differential.cpp'
$candidateSource = Join-Path $root 'src/functions/1000e960.cpp'
$original = 'C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi'
$expectedCandidateSource = 'A33AC5B64EA205301287BCACC3CB2624D1FE8EA407C4477939F141E03DF06AA1'
$expectedOriginal = '409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3'

function Get-Sha256([string]$Path) {
    return (Get-FileHash -LiteralPath $Path -Algorithm SHA256).Hash
}

if ((Get-Sha256 $candidateSource) -ne $expectedCandidateSource) {
    throw 'Candidate source changed; refresh the evidence before running.'
}
if ((Get-Sha256 $original) -ne $expectedOriginal) {
    throw 'Original ASI hash does not match the pinned binary.'
}

$out = Join-Path $root 'build/abi-harness/1000e960-queue-reentry-differential-20260929'
New-Item -ItemType Directory -Path $out -Force | Out-Null
$object = Join-Path $out '1000e960.obj'
$exe = Join-Path $out 'runtime_1000e960_queue_reentry_differential.exe'
$developerCommand = 'call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat" -arch=x86 -host_arch=x64 && cl.exe /nologo /std:c++20 /O1 /W4 /WX /MT /GS- /arch:IA32 /c "' + $candidateSource + '" /Fo"' + $object + '" && cl.exe /nologo /std:c++20 /O1 /W4 /WX /MT /GS- /arch:IA32 "' + $source + '" "' + $object + '" /Fe"' + $exe + '"'
& cmd.exe /d /s /c $developerCommand
if ($LASTEXITCODE -ne 0) { throw 'Candidate object or focused differential harness build failed.' }

for ($i = 1; $i -le $Repetitions; ++$i) {
    & $exe
    if ($LASTEXITCODE -ne 0) { throw "Differential run $i/$Repetitions failed with exit $LASTEXITCODE." }
}

Write-Host "Harness SHA-256: $(Get-Sha256 $exe)"
Write-Host "Candidate object SHA-256: $(Get-Sha256 $object)"
Write-Host "Original ASI SHA-256: $(Get-Sha256 $original)"
