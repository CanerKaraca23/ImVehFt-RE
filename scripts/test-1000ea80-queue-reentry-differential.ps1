param(
    [ValidateRange(1, 100)]
    [int]$Repetitions = 5
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
$root = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$source = Join-Path $root 'tests/runtime_1000ea80_queue_reentry_differential.cpp'
$object = Join-Path $root 'build/recheck/strict-xcode-nogs-o1-100110bd-root-impl-20260929/1000ea80.obj'
$original = 'C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi'
$expectedSource = '212FA4C41048741D24D4D0F7839321FB21D3EFA5D31BE16485C2D9ABA8AEA171'
$expectedObject = 'F1038CA97F6277A26184A49DCD566BB6FCAA10FDB0141F40BA18F58BA7968D05'
$expectedOriginal = '409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3'

function Get-Sha256([string]$Path) {
    return (Get-FileHash -LiteralPath $Path -Algorithm SHA256).Hash
}

if ((Get-Sha256 $source) -ne $expectedSource) { throw 'Harness source hash changed; refresh the evidence before running.' }
if ((Get-Sha256 $object) -ne $expectedObject) { throw 'Candidate object hash changed; refresh the evidence before running.' }
if ((Get-Sha256 $original) -ne $expectedOriginal) { throw 'Original ASI hash does not match the pinned binary.' }

$exe = Join-Path $root 'build/abi-harness/1000ea80-queue-reentry-differential.exe'
New-Item -ItemType Directory -Path (Split-Path -Parent $exe) -Force | Out-Null
$developerCommand = 'call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat" -arch=x86 -host_arch=x64 && cl.exe /nologo /std:c++20 /O1 /W4 /WX /MT /GS- /arch:IA32 "' + $source + '" "' + $object + '" /Fe"' + $exe + '"'
& cmd.exe /d /s /c $developerCommand
if ($LASTEXITCODE -ne 0) { throw 'Queue differential harness build failed.' }

for ($i = 1; $i -le $Repetitions; ++$i) {
    & $exe
    if ($LASTEXITCODE -ne 0) { throw "Queue differential run $i/$Repetitions failed with exit $LASTEXITCODE." }
}

Write-Host "Harness SHA-256: $(Get-Sha256 $exe)"
Write-Host "Original ASI SHA-256: $(Get-Sha256 $original)"
Write-Host "Candidate object SHA-256: $(Get-Sha256 $object)"
