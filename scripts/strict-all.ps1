param(
    [string]$OutputDirectory = 'build/recheck/strict-all-msvc-env-20260927',
    [string]$ReportPath = 'build/strict-all-20260927.json',
    [switch]$UseIa32FloatingPoint
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
$sourceFiles = @(Get-ChildItem -LiteralPath $sourceRoot -File -Filter '*.cpp' | Sort-Object Name)

if ($sourceFiles.Count -ne 705) {
    throw "Expected 705 candidate translation units; found $($sourceFiles.Count)."
}
if (Test-Path -LiteralPath $reportFile) {
    throw "Refusing to overwrite existing report: $reportFile"
}

$compilerCommand = Get-Command cl.exe -ErrorAction Stop
$architectureFlags = @()
if ($UseIa32FloatingPoint) {
    # Match the original 32-bit target's x87 floating-point instruction family
    # during diagnostic compilation; this does not establish original compiler
    # flags or production-project equivalence.
    $architectureFlags += '/arch:IA32'
}
New-Item -ItemType Directory -Path $outputRoot -Force | Out-Null
$results = [System.Collections.Generic.List[object]]::new()

foreach ($source in $sourceFiles) {
    $objectPath = Join-Path $outputRoot ($source.BaseName + '.obj')
    $diagnostics = & $compilerCommand.Source /nologo /std:c++20 /O2 /W4 /WX /MT `
        @architectureFlags /c `
        $source.FullName "/Fo$objectPath" 2>&1
    $exitCode = $LASTEXITCODE
    $results.Add([pscustomobject]@{
        address = $source.BaseName.ToLowerInvariant()
        source = "src/functions/$($source.Name)"
        exit_code = $exitCode
        object = (Join-Path $OutputDirectory ($source.BaseName + '.obj')).Replace('\', '/')
        diagnostic = ($diagnostics | ForEach-Object { $_.ToString() }) -join "`n"
    })
}

$failed = @($results | Where-Object { $_.exit_code -ne 0 })
$report = [pscustomobject]@{
    target = 'i686-pc-windows-msvc'
    compiler = $compilerCommand.Source
    standard = 'C++20'
    flags = @('/O2', '/W4', '/WX', '/MT') + $architectureFlags + @('/c')
    translation_units = $results.Count
    passed = $results.Count - $failed.Count
    failed = $failed.Count
    results = $results
}
$report | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath $reportFile -Encoding utf8

Write-Host "Strict compile: $($report.passed)/$($report.translation_units) passed; $($report.failed) failed."
Write-Host "Report: $reportFile"
Write-Host "Objects: $outputRoot"

if ($failed.Count -gt 0) {
    $failed | Format-Table address, exit_code, diagnostic -Wrap
    throw "Strict compile failed for $($failed.Count) translation unit(s)."
}
