param(
    [string]$OutputDirectory = 'build/recheck/strict-xcode-nogs-o1-20260929',
    [string]$ReportPath = 'build/strict-xcode-nogs-o1-20260929.json',
    [switch]$EnableGS
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
$compilerArguments = @('/nologo', '/std:c++20', '/O1', '/W4', '/WX', '/MT', '/arch:IA32')
if (-not $EnableGS) { $compilerArguments += '/GS-' }
$gsFlags = if ($EnableGS) { @() } else { @('/GS-') }
$gsLabel = if ($EnableGS) { 'GS' } else { 'no-GS' }
New-Item -ItemType Directory -Path $outputRoot | Out-Null
$results = [System.Collections.Generic.List[object]]::new()

foreach ($source in $sourceFiles) {
    $objectPath = Join-Path $outputRoot ($source.BaseName + '.obj')
    $diagnostics = & $compiler.Source @compilerArguments "/FI$forcedHeader" /c `
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
    flags = @('/O1', '/W4', '/WX', '/MT', '/arch:IA32') + $gsFlags + @("/FI$forcedHeader", '/c')
    code_section = '.xcode'
    translation_units = $results.Count
    passed = $results.Count - $failed.Count
    failed = $failed.Count
    results = $results
}
$report | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath $reportFile -Encoding utf8

Write-Host "Strict .xcode $gsLabel /O1 compile: $($report.passed)/$($report.translation_units) passed; $($report.failed) failed."
Write-Host "Report: $reportFile"
Write-Host "Objects: $outputRoot"
if ($failed.Count -gt 0) {
    $failed | Format-Table address, exit_code, diagnostic -Wrap
    throw "Strict no-GS /O1 compile failed for $($failed.Count) translation unit(s)."
}
