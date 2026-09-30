param(
    [string]$ReferencePath = 'C:\Users\caner\OneDrive\Documents\ImVehFt\ImVehFt.asi',
    [string]$ProbePath = '',
    [string]$OutputDirectory = ''
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

function Get-Sha256Hex([string]$Path) {
    $algorithm = [System.Security.Cryptography.SHA256]::Create()
    $stream = [System.IO.File]::OpenRead($Path)
    try {
        return ([System.BitConverter]::ToString($algorithm.ComputeHash($stream))).Replace('-', '')
    }
    finally {
        $stream.Dispose()
        $algorithm.Dispose()
    }
}

$expectedReferenceHash = '409F0DF7AE579841DB05C3EC6DAD0A9AFC579194632874962E1BDEE0CCF020D3'
if ((Get-Sha256Hex $ReferencePath) -ne $expectedReferenceHash) {
    throw 'Reference ASI hash mismatch.'
}
if ([string]::IsNullOrWhiteSpace($ProbePath)) {
    $ProbePath = Join-Path $PSScriptRoot '..\build\pe-layout-probe\validate-image-base-single-function-probe-not-asi.bin'
}
if (-not (Test-Path -LiteralPath $ProbePath -PathType Leaf)) {
    throw "Single-function probe not found: $ProbePath"
}

$root = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
if ([string]::IsNullOrWhiteSpace($OutputDirectory)) {
    $OutputDirectory = 'build/abi-harness/validate-image-base-inplace-' +
        (Get-Date -Format 'yyyyMMdd-HHmmss-fff')
}
$outputRoot = Join-Path $root $OutputDirectory
if (Test-Path -LiteralPath $outputRoot) {
    throw "Refusing to overwrite existing output directory: $outputRoot"
}
New-Item -ItemType Directory -Path $outputRoot | Out-Null

$vsDevCmd = 'C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat'
if (-not (Test-Path -LiteralPath $vsDevCmd)) {
    throw "VS 2022 developer environment not found: $vsDevCmd"
}
$source = Join-Path $root 'tests\validate_image_base_mapped_pe_differential.cpp'
$executable = Join-Path $outputRoot 'validate-image-base-mapped-pe-differential.exe'
$cmdLine = 'cd /d "{0}" && call "{1}" -arch=x86 -host_arch=x64 && cl.exe /nologo /std:c++20 /O2 /W4 /WX /MT /GS /arch:IA32 "{2}" /Fe:"{3}" && "{3}" "{4}" "{5}"' -f `
    $outputRoot, $vsDevCmd, $source, $executable, (Resolve-Path $ReferencePath).Path, (Resolve-Path $ProbePath).Path
& $env:ComSpec /d /c $cmdLine
if ($LASTEXITCODE -ne 0) {
    throw "Mapped-PE differential harness failed with exit code $LASTEXITCODE."
}
Write-Host "Harness: $executable"
Write-Host "Reference SHA-256: $expectedReferenceHash"
Write-Host "Probe SHA-256: $(Get-Sha256Hex $ProbePath)"
