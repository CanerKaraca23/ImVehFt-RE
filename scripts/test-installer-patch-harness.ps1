param(
    [string]$InstallerObject = 'build/recheck/strict-all-live-20260928-2/10002210.obj',
    [string]$GtaExecutable = 'C:\Users\caner\OneDrive\Documents\GTA San Andreas\gta_sa.exe',
    [ValidatePattern('^0x[0-9A-Fa-f]{8}$')]
    [string]$HarnessBaseAddress = '0x00400000',
    [ValidatePattern('^0x[0-9A-Fa-f]{1,8}$')]
    [string]$HeapReserveSize = '0x40000'
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
if (-not (Get-Command cl.exe -ErrorAction SilentlyContinue)) {
    throw 'Run this script from a Visual Studio Developer PowerShell initialized for x86.'
}
$root = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$objectPath = (Resolve-Path (Join-Path $root $InstallerObject)).Path
$gtaExecutablePath = (Resolve-Path -LiteralPath $GtaExecutable).Path
$sha256 = [Security.Cryptography.SHA256]::Create()
$gtaExecutableSha256 = ([BitConverter]::ToString(
    $sha256.ComputeHash([IO.File]::ReadAllBytes($gtaExecutablePath)))).Replace('-', '')
$sourcePath = Join-Path $root 'tests/runtime_installer_patch_harness.cpp'
$manifestPath = (Resolve-Path (Join-Path $root 'tests/runtime_harness.asInvoker.manifest')).Path
$sourceText = [IO.File]::ReadAllText($sourcePath)
$manifest = Get-Content (Join-Path $root 'audit/installer-target-thunks-2026-09-27.json') -Raw | ConvertFrom-Json
$siteEvidence = Import-Csv (Join-Path $root 'audit/asi-hook-target-disassembly-2026-09-27.csv')
$harnessHooks = [regex]::Matches($sourceText, '\{(0x[0-9A-Fa-f]{8}),\s*(0x[0-9A-Fa-f]{2}),\s*&IVF_INSTALL_TARGET_([0-9A-Fa-f]{8})\}')
if ($harnessHooks.Count -ne $manifest.patch_site_count) {
    throw "Harness has $($harnessHooks.Count) hook cases; manifest requires $($manifest.patch_site_count)."
}
foreach ($patch in $manifest.patches) {
    $hookSite = $siteEvidence | Where-Object { $_.hook_site -ieq $patch.opcode_address } | Select-Object -First 1
    if (-not $hookSite -or $hookSite.target -ine $patch.target_address) {
        throw "Manifest target lacks matching original disassembly evidence: $($patch.opcode_address)."
    }
    $expectedOpcode = $hookSite.opcode.Replace('0X', '0x')
    $targetSuffix = $patch.target_address.Substring(2)
    $matches = @($harnessHooks | Where-Object {
        $_.Groups[1].Value -ieq $patch.opcode_address -and
        $_.Groups[2].Value -ieq $expectedOpcode -and
        $_.Groups[3].Value -ieq $targetSuffix
    })
    if ($matches.Count -ne 1) { throw "Harness case does not match evidence/manifest: $($patch.opcode_address)." }
}
$stamp = Get-Date -Format 'yyyyMMdd-HHmmss-fff'
$outDir = Join-Path $root "build/runtime-check/$stamp"
New-Item -ItemType Directory -Path $outDir | Out-Null
$exePath = Join-Path $outDir 'hook-patch-harness.exe'

& cl.exe /nologo /std:c++20 /O2 /W4 /WX /MT /arch:IA32 $sourcePath $objectPath `
    /Fe:$exePath /link /MACHINE:X86 /SUBSYSTEM:CONSOLE /INCREMENTAL:NO `
    "/BASE:$HarnessBaseAddress" "/HEAP:$HeapReserveSize,0x1000" /DYNAMICBASE:NO `
    /SECTION:.gta,RW /OPT:REF /OPT:NOICF /MANIFEST:EMBED `
    "/MANIFESTINPUT:$manifestPath"
if ($LASTEXITCODE -ne 0) { throw "MSVC harness build failed with exit code $LASTEXITCODE." }

$startInfo = New-Object System.Diagnostics.ProcessStartInfo
$startInfo.FileName = $exePath
$startInfo.UseShellExecute = $false
$startInfo.Arguments = '"' + $gtaExecutablePath + '"'
$startInfo.CreateNoWindow = $true
$startInfo.RedirectStandardOutput = $true
$startInfo.RedirectStandardError = $true
$process = [System.Diagnostics.Process]::Start($startInfo)
$stdout = $process.StandardOutput.ReadToEnd()
$stderr = $process.StandardError.ReadToEnd()
$process.WaitForExit()
$testSha256 = ([BitConverter]::ToString(
    ([Security.Cryptography.SHA256]::Create()).ComputeHash([IO.File]::ReadAllBytes($exePath)))).Replace('-', '')
if ($process.ExitCode -ne 0) {
    $blocked = [pscustomobject]@{
        result = 'BLOCKED'
        exit_code = $process.ExitCode
        harness_output = $stderr.Trim()
        test_executable = $exePath.Replace($root + '\', '').Replace('\', '/')
        test_sha256 = $testSha256
        installer_object = $objectPath.Replace($root + '\', '').Replace('\', '/')
        gta_executable = $gtaExecutablePath
        gta_executable_sha256 = $gtaExecutableSha256
        scope = 'Actual candidate installer object against synthetic memory seeded from the selected GTA PE; the installer is not called when a compatibility precondition fails.'
    }
    $blocked | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath (Join-Path $outDir 'result.json') -Encoding UTF8
    throw "Installer harness failed with exit code $($process.ExitCode). stdout=$stdout stderr=$stderr"
}
if ($stderr -notmatch 'PASS actual FUN_10002210 object: 22/22 rel32 hook patches, 3 function-pointer patches') {
    throw "Installer harness did not emit the expected full PASS line. stderr=$stderr"
}

$result = [pscustomobject]@{
    result = 'PASS'
    exit_code = $process.ExitCode
    harness_output = $stderr.Trim()
    test_executable = $exePath.Replace($root + '\', '').Replace('\', '/')
    test_sha256 = $testSha256
    installer_object = $objectPath.Replace($root + '\', '').Replace('\', '/')
    gta_executable = $gtaExecutablePath
    gta_executable_sha256 = $gtaExecutableSha256
    scope = 'Executes the actual candidate installer object against synthetic memory at original GTA VAs seeded from the specified GTA PE pages; selected ImVehFt callbacks are stubs while Windows memory/protection/profile APIs are real.'
    limitation = 'Not a real GTA process or startup-loader run; the game image is not executed and callback targets are stubs.'
}
$result | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath (Join-Path $outDir 'result.json') -Encoding UTF8
$result
