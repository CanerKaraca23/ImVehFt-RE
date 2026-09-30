param(
    [string]$OutputDirectory = 'build/recheck/strict-xcode-nogs-20260929',
    [string]$ReportPath = 'build/strict-xcode-nogs-20260929.json'
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

if (-not $env:VCToolsInstallDir -or -not $env:WindowsSdkDir) {
    throw 'Run this script from a VS 2022 Developer environment initialized for x86.'
}

$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$sourceRoot = Join-Path $repoRoot 'src/functions'
$outputRoot = Join-Path $repoRoot $OutputDirectory
$reportFile = Join-Path $repoRoot $ReportPath
$forcedHeader = Join-Path $repoRoot 'tests/layout_probe/candidate_xcode_seg.hpp'
$sourceFiles = @(Get-ChildItem -LiteralPath $sourceRoot -File -Filter '*.cpp' | Sort-Object Name)

if ($sourceFiles.Count -ne 705) { throw "Expected 705 candidate translation units; found $($sourceFiles.Count)." }
if (Test-Path -LiteralPath $outputRoot) { throw "Refusing to overwrite object directory: $outputRoot" }
if (Test-Path -LiteralPath $reportFile) { throw "Refusing to overwrite report: $reportFile" }

$compiler = Get-Command cl.exe -ErrorAction Stop
New-Item -ItemType Directory -Path $outputRoot | Out-Null
$results = [System.Collections.Generic.List[object]]::new()

foreach ($source in $sourceFiles) {
    $objectPath = Join-Path $outputRoot ($source.BaseName + '.obj')
    $diagnostics = & $compiler.Source /nologo /std:c++20 /O2 /W4 /WX /MT /arch:IA32 /GS- "/FI$forcedHeader" /c `
        $source.FullName "/Fo$objectPath" 2>&1
    $results.Add([pscustomobject]@{
        address = $source.BaseName.ToLowerInvariant()
        source = "src/functions/$($source.Name)"
        exit_code = $LASTEXITCODE
        object = (Join-Path $OutputDirectory ($source.BaseName + '.obj')).Replace('\', '/')
        diagnostic = ($diagnostics | ForEach-Object { $_.ToString() }) -join "`n"
    })
}

$failed = @($results | Where-Object { $_.exit_code -ne 0 })
$report = [pscustomobject]@{
    target = 'i686-pc-windows-msvc'
    compiler = $compiler.Source
    standard = 'C++20'
    flags = @('/O2', '/W4', '/WX', '/MT', '/arch:IA32', '/GS-', "/FI$forcedHeader", '/c')
    code_section = '.xcode'
    translation_units = $results.Count
    passed = $results.Count - $failed.Count
    failed = $failed.Count
    results = $results
}
$report | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath $reportFile -Encoding utf8

Write-Host "Strict .xcode no-GS compile: $($report.passed)/$($report.translation_units) passed; $($report.failed) failed."
Write-Host "Report: $reportFile"
Write-Host "Objects: $outputRoot"
if ($failed.Count -gt 0) {
    $failed | Format-Table address, exit_code, diagnostic -Wrap
    throw "Strict no-GS compile failed for $($failed.Count) translation unit(s)."
}
