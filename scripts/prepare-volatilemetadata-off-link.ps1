param(
    [string]$BaseResponseFile = 'build/link-probe/volatile-metadata-off-20260929/xcode-705-volatilemetadata-off.rsp',
    [string]$OldObjectDirectoryToken = 'build\recheck\strict-xcode-nogs-o1-volatilemetadata-off-20260929',
    [string]$NewObjectDirectoryToken = 'build\recheck\strict-xcode-nogs-o1-volatilemetadata-off-20260929',
    [string]$OldOutputToken = 'build\link-probe\volatile-metadata-off-20260929',
    [string]$NewOutputToken = 'build\link-probe\volatile-metadata-off-clean-20260929',
    [string]$ResponseFile = 'build/link-probe/volatile-metadata-off-clean-20260929/xcode-705.rsp'
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
if (-not $env:VCToolsInstallDir -or -not $env:WindowsSdkDir) {
    throw 'Run this script from a VS 2022 Developer environment initialized for x86.'
}

$root = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$base = (Resolve-Path (Join-Path $root $BaseResponseFile)).Path
$objects = (Resolve-Path (Join-Path $root $NewObjectDirectoryToken)).Path
$response = Join-Path $root $ResponseFile
$outDirectory = Join-Path $root $NewOutputToken
if (Test-Path -LiteralPath $response) { throw "Refusing to overwrite response file: $response" }
if (Test-Path -LiteralPath $outDirectory) { throw "Refusing to overwrite output directory: $outDirectory" }
$candidateObjects = @(Get-ChildItem -LiteralPath $objects -File -Filter '*.obj')
if ($candidateObjects.Count -ne 705) { throw "Expected 705 candidate objects; found $($candidateObjects.Count)." }

$text = [System.IO.File]::ReadAllText($base)
$text = $text.Replace($OldObjectDirectoryToken, $NewObjectDirectoryToken)
$text = $text.Replace($OldOutputToken, $NewOutputToken)
$stale = @(
    '"/INCLUDE:_FUN_10001db0@8"',
    '"/INCLUDE:_FUN_1001074b@4"',
    '"/INCLUDE:?FUN_10009790@@YIXH@Z"',
    '"/INCLUDE:?invoke@FUN_1001023b_this@@QAEXPBI@Z"'
)
foreach ($line in $stale) {
    if (-not $text.Contains($line)) { throw "Expected stale entry-root directive missing: $line" }
    $pattern = '(?m)^' + [regex]::Escape($line) + '\r?\n'
    $text = [regex]::Replace($text, $pattern, '', 1)
    if ($text.Contains($line)) { throw "Stale entry-root directive was not removed: $line" }
}
$text += [Environment]::NewLine + @'
"/INCLUDE:_FUN_10001db0@12"
"/INCLUDE:_FUN_1001074b"
"/INCLUDE:?FUN_10009790@@YIXHIIIIII@Z"
"/INCLUDE:?invoke@FUN_1001023b_this@@QAEXPBII@Z"
"/alternatename:?FUN_10009790@@YIXH@Z=?FUN_10009790@@YIXHIIIIII@Z"
'@

$resolved = [regex]::Matches($text, '"([^\"]+\\[0-9a-fA-F]{8}\.obj)"') |
    ForEach-Object { $_.Groups[1].Value } |
    Where-Object { $_ -match [regex]::Escape($NewObjectDirectoryToken) }
if (@($resolved).Count -ne 705) { throw "Response maps $(@($resolved).Count) candidate objects, expected 705." }
foreach ($path in $resolved) { if (-not (Test-Path -LiteralPath $path)) { throw "Missing candidate object: $path" } }

New-Item -ItemType Directory -Path $outDirectory | Out-Null
[System.IO.File]::WriteAllText($response, $text, [System.Text.UTF8Encoding]::new($false))
Write-Host "Prepared clean-signature diagnostic response: $response"
& link.exe "@$response"
if ($LASTEXITCODE -ne 0) { throw "Clean-signature diagnostic link failed: $LASTEXITCODE" }
Write-Host 'Link succeeded without /FORCE; output remains diagnostic, not an ASI.'
