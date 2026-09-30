param(
    [ValidateRange(1, 100)]
    [int]$Repetitions = 10
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
$root = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$copy = Join-Path $root 'src/functions/10001b30.cpp'
$destroy = Join-Path $root 'src/functions/10001b00.cpp'
$constructor = Join-Path $root 'src/functions/10001ad0.cpp'
$harness = Join-Path $root 'tests/runtime_10001b30_mext_copy_differential.cpp'
$original = 'C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi'
$expectedCopy = '106552B9F9DE2AFC908D1DF584772FFD284BF0C9154496402AF6B54D992EF449'
$expectedDestroy = 'E557E022C0B23F7FC6AA07F1CA5109F0C69419518C6BD686AF7906AD2A49E416'
$expectedConstructor = 'D675CB21D80A8C9C0226B57BC5AD47630DD9EB040898FDBB7568E6D8B2BD460F'
$expectedOriginal = '409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3'

function Get-Sha256([string]$Path) {
    (Get-FileHash -LiteralPath $Path -Algorithm SHA256).Hash
}

if ((Get-Sha256 $copy) -ne $expectedCopy) { throw 'Copy callback source changed; refresh evidence.' }
if ((Get-Sha256 $destroy) -ne $expectedDestroy) { throw 'Destructor source changed; refresh evidence.' }
if ((Get-Sha256 $constructor) -ne $expectedConstructor) { throw 'Constructor source changed; refresh evidence.' }
if ((Get-Sha256 $original) -ne $expectedOriginal) { throw 'Original ASI hash does not match.' }

$out = Join-Path $root 'build/abi-harness/10001b30-mext-copy-differential-20260929'
New-Item -ItemType Directory -Path $out -Force | Out-Null
$copyObject = Join-Path $out '10001b30.obj'
$destroyObject = Join-Path $out '10001b00.obj'
$constructorObject = Join-Path $out '10001ad0.obj'
$exe = Join-Path $out 'runtime_10001b30_mext_copy_differential.exe'
$forcedInclude = Join-Path $root 'tests/layout_probe/candidate_xcode_seg.hpp'
$developerCommand = 'call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat" -arch=x86 -host_arch=x64 && cl.exe /nologo /std:c++20 /O1 /W4 /WX /MT /GS- /arch:IA32 /FI"' + $forcedInclude + '" /c "' + $copy + '" /Fo"' + $copyObject + '" && cl.exe /nologo /std:c++20 /O1 /W4 /WX /MT /GS- /arch:IA32 /FI"' + $forcedInclude + '" /c "' + $destroy + '" /Fo"' + $destroyObject + '" && cl.exe /nologo /std:c++20 /O1 /W4 /WX /MT /GS- /arch:IA32 /FI"' + $forcedInclude + '" /c "' + $constructor + '" /Fo"' + $constructorObject + '" && cl.exe /nologo /std:c++20 /O1 /W4 /WX /MT /GS- /arch:IA32 "' + $harness + '" "' + $copyObject + '" "' + $destroyObject + '" "' + $constructorObject + '" /Fe"' + $exe + '"'
& cmd.exe /d /s /c $developerCommand
if ($LASTEXITCODE -ne 0) { throw 'Strict x86 candidate/harness build failed.' }

for ($i = 1; $i -le $Repetitions; ++$i) {
    Write-Host "Differential process $i/$Repetitions"
    & $exe
    if ($LASTEXITCODE -ne 0) { throw "Differential process $i/$Repetitions failed with exit $LASTEXITCODE." }
}

Write-Host "Copy source SHA-256: $(Get-Sha256 $copy)"
Write-Host "Destructor source SHA-256: $(Get-Sha256 $destroy)"
Write-Host "Constructor source SHA-256: $(Get-Sha256 $constructor)"
Write-Host "Harness source SHA-256: $(Get-Sha256 $harness)"
Write-Host "Copy object SHA-256: $(Get-Sha256 $copyObject)"
Write-Host "Destructor object SHA-256: $(Get-Sha256 $destroyObject)"
Write-Host "Constructor object SHA-256: $(Get-Sha256 $constructorObject)"
Write-Host "Harness executable SHA-256: $(Get-Sha256 $exe)"
Write-Host "Original ASI SHA-256: $(Get-Sha256 $original)"
