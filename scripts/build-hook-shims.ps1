param(
    [string]$ClPath,
    [string]$MlPath,
    [string]$PythonPath = 'python'
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

if (-not $ClPath) {
    $clCommand = Get-Command cl.exe -ErrorAction SilentlyContinue
    if (-not $clCommand) {
        throw 'cl.exe not found. Use an x86 MSVC developer prompt or pass -ClPath.'
    }
    $ClPath = $clCommand.Source
}

if (-not $MlPath) {
    $mlCommand = Get-Command ml.exe -ErrorAction SilentlyContinue
    if (-not $mlCommand) {
        throw 'ml.exe not found. Use an x86 MSVC developer prompt or pass -MlPath.'
    }
    $MlPath = $mlCommand.Source
}

$repoRoot = Split-Path -Parent $PSScriptRoot
$outputDirectory = Join-Path $repoRoot 'build/hook-shims'
$cppSource = Join-Path $repoRoot 'src/hook_shims/x86_imvehft_hook_shims.cpp'
$asmSource = Join-Path $repoRoot 'src/hook_shims/x86_hook_targets_remaining.asm'
$callbackAsmSource = Join-Path $repoRoot 'src/hook_shims/x86_callback_entry_thunks.asm'
$callbackJmpAsmSource = Join-Path $repoRoot 'src/hook_shims/x86_callback_jmp_thunks.asm'
$cppObject = Join-Path $outputDirectory 'x86_imvehft_hook_shims.obj'
$asmObject = Join-Path $outputDirectory 'x86_hook_targets_remaining.obj'
$callbackAsmObject = Join-Path $outputDirectory 'x86_callback_entry_thunks.obj'
$callbackJmpAsmObject = Join-Path $outputDirectory 'x86_callback_jmp_thunks.obj'
$verifier = Join-Path $repoRoot 'scripts/verify-hook-shim-bytes.py'

New-Item -ItemType Directory -Path $outputDirectory -Force | Out-Null

& $ClPath /nologo /c /O2 /W4 /WX /GS- "/Fo$cppObject" $cppSource
if ($LASTEXITCODE -ne 0) {
    throw "MSVC hook-shim compilation failed with exit code $LASTEXITCODE."
}

& $MlPath /nologo /c /coff /Fo $asmObject $asmSource
if ($LASTEXITCODE -ne 0) {
    throw "MASM hook-target assembly failed with exit code $LASTEXITCODE."
}

& $MlPath /nologo /c /coff /Fo $callbackAsmObject $callbackAsmSource
if ($LASTEXITCODE -ne 0) {
    throw "MASM callback-entry thunk assembly failed with exit code $LASTEXITCODE."
}

& $MlPath /nologo /c /coff /Fo $callbackJmpAsmObject $callbackJmpAsmSource
if ($LASTEXITCODE -ne 0) {
    throw "MASM callback JMP thunk assembly failed with exit code $LASTEXITCODE."
}

& $PythonPath (Join-Path $repoRoot 'scripts/verify-callback-entry-thunks.py') --object $callbackAsmObject
if ($LASTEXITCODE -ne 0) {
    throw 'Ghidra callback-entry thunk byte/relocation verification failed.'
}

& $PythonPath (Join-Path $repoRoot 'scripts/verify-callback-jmp-thunks.py') `
    --object $callbackJmpAsmObject `
    --manifest (Join-Path $repoRoot 'audit/candidate-callback-jmp-thunks-v2-2026-09-27.csv')
if ($LASTEXITCODE -ne 0) {
    throw 'Ghidra callback JMP thunk byte/relocation verification failed.'
}

& $PythonPath $verifier --object $cppObject --object $asmObject
if ($LASTEXITCODE -ne 0) {
    throw "Ghidra byte comparison failed with exit code $LASTEXITCODE."
}

Write-Host 'Built supplemental shim objects; verified 12 hook streams, 25 call-entry thunks and the manifest-mapped callback JMP thunks.'
Write-Host 'These objects are not integrated into or proof of a deployable ImVehFt plugin.'
