param(
    [string]$OutputDirectory = 'build/recheck/clang-all',
    [string]$ReportPath = 'build/clang-all.json'
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$sourceRoot = Join-Path $repoRoot 'src/functions'
$outputRoot = Join-Path $repoRoot $OutputDirectory
$reportFile = Join-Path $repoRoot $ReportPath
$compilerPath = 'C:\Program Files\LLVM\bin\clang-cl.exe'

if (-not (Test-Path -LiteralPath $compilerPath -PathType Leaf)) {
    throw "clang-cl was not found at the expected path: $compilerPath"
}
if (-not $env:WindowsSdkDir -or -not $env:INCLUDE) {
    throw 'Run this script from a VS 2022 Developer environment initialized for x86.'
}
if (Test-Path -LiteralPath $reportFile) {
    throw "Refusing to overwrite existing report: $reportFile"
}

$sourceFiles = @(Get-ChildItem -LiteralPath $sourceRoot -File -Filter '*.cpp' | Sort-Object Name)
if ($sourceFiles.Count -ne 705) {
    throw "Expected 705 candidate translation units; found $($sourceFiles.Count)."
}

New-Item -ItemType Directory -Path $outputRoot -Force | Out-Null
$results = [System.Collections.Generic.List[object]]::new()
foreach ($source in $sourceFiles) {
    $objectPath = Join-Path $outputRoot ($source.BaseName + '.obj')
    $previousErrorActionPreference = $ErrorActionPreference
    $ErrorActionPreference = 'Continue'
    try {
        $diagnostics = & $compilerPath --target=i686-pc-windows-msvc /nologo /std:c++20 /O2 /FIlocale.h /c `
            $source.FullName "/Fo$objectPath" 2>&1
    }
    finally {
        $ErrorActionPreference = $previousErrorActionPreference
    }
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
    compiler = $compilerPath
    compiler_version = (& $compilerPath --version | Select-Object -First 1).ToString()
    standard = 'C++20'
    flags = @('--target=i686-pc-windows-msvc', '/O2', '/FIlocale.h', '/c')
    forced_include = 'locale.h (UCRT locale type declarations for independent Clang TU compilation)'
    translation_units = $results.Count
    passed = $results.Count - $failed.Count
    failed = $failed.Count
    results = $results
}
$report | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath $reportFile -Encoding utf8

Write-Host "Strict Clang compile: $($report.passed)/$($report.translation_units) passed; $($report.failed) failed."
Write-Host "Report: $reportFile"
Write-Host "Objects: $outputRoot"
if ($failed.Count -gt 0) {
    $failed | Format-Table address, exit_code, diagnostic -Wrap
    throw "Clang compile failed for $($failed.Count) translation unit(s)."
}
