$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

$repoRoot = Split-Path -Parent $PSScriptRoot
$sourceRoot = Join-Path $repoRoot 'src/functions'
$buildRoot = Join-Path $repoRoot 'build'
$objectRoot = Join-Path $buildRoot 'obj'
$sourceFiles = @(Get-ChildItem -LiteralPath $sourceRoot -File -Filter '*.cpp' | Sort-Object Name)

if ($sourceFiles.Count -ne 705) {
    throw "Expected 705 candidate translation units; found $($sourceFiles.Count)."
}

$compiler = Get-Command cl.exe -ErrorAction Stop
$librarian = Get-Command lib.exe -ErrorAction Stop
New-Item -ItemType Directory -Path $objectRoot -Force | Out-Null

$results = [System.Collections.Generic.List[object]]::new()
foreach ($source in $sourceFiles) {
    $objectPath = Join-Path $objectRoot ($source.BaseName + '.obj')
    $diagnostics = & $compiler.Source /nologo /std:c++20 /O2 /c $source.FullName "/Fo$objectPath" 2>&1
    $exitCode = $LASTEXITCODE
    $results.Add([pscustomobject]@{
        address = $source.BaseName.ToLowerInvariant()
        source = [System.IO.Path]::GetRelativePath($repoRoot, $source.FullName).Replace('\', '/')
        exit_code = $exitCode
        object = [System.IO.Path]::GetRelativePath($repoRoot, $objectPath).Replace('\', '/')
        diagnostic = ($diagnostics | ForEach-Object { $_.ToString() }) -join "`n"
    })
}

$failed = @($results | Where-Object { $_.exit_code -ne 0 })
$report = [pscustomobject]@{
    target = 'i686-pc-windows-msvc'
    compiler = $compiler.Source
    standard = 'C++20'
    flags = @('/O2', '/c')
    translation_units = $results.Count
    passed = $results.Count - $failed.Count
    failed = $failed.Count
    results = $results
}
$reportPath = Join-Path $buildRoot 'compile-report.json'
$report | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath $reportPath -Encoding utf8

if ($failed.Count -gt 0) {
    $failed | Format-Table address, exit_code, diagnostic -Wrap
    throw "Compilation failed for $($failed.Count) translation unit(s); see build/compile-report.json."
}

$responsePath = Join-Path $buildRoot 'objects.rsp'
$objectPaths = @($results | ForEach-Object { '"' + (Join-Path $repoRoot $_.object.Replace('/', '\')) + '"' })
Set-Content -LiteralPath $responsePath -Value $objectPaths -Encoding utf8
$archivePath = Join-Path $buildRoot 'ImVehFtCandidates.lib'
& $librarian.Source /nologo "/OUT:$archivePath" "@$responsePath"
if ($LASTEXITCODE -ne 0) {
    throw "lib.exe failed with exit code $LASTEXITCODE."
}

Write-Host "Compiled $($results.Count)/705 candidate translation units."
Write-Host "Static archive: $archivePath"
Write-Host "Compile report: $reportPath"
