param(
  [Parameter(Mandatory=$true)][string]$Candidate,
  [Parameter(Mandatory=$true)][string]$Report
)
$ErrorActionPreference = 'Stop'
if ([IntPtr]::Size -ne 4) { throw 'Run this probe in 32-bit Windows PowerShell.' }
$candidatePath = (Resolve-Path -LiteralPath $Candidate).Path
$image = [IO.File]::ReadAllBytes($candidatePath)
function U16([byte[]]$b,[int]$o) { [BitConverter]::ToUInt16($b,$o) }
function U32([byte[]]$b,[int]$o) { [BitConverter]::ToUInt32($b,$o) }
function ReadAsciiZ([byte[]]$b,[int]$o) {
  $e=$o; while($e -lt $b.Length -and $b[$e] -ne 0){$e++}
  if($e -eq $b.Length){throw ('Unterminated import string at file offset 0x{0:X}' -f $o)}
  [Text.Encoding]::ASCII.GetString($b,$o,$e-$o)
}
$pe=[int](U32 $image 0x3c); if([Text.Encoding]::ASCII.GetString($image,$pe,4) -ne "PE`0`0"){throw 'Bad PE signature'}
$opt=$pe+24; if((U16 $image $opt) -ne 0x10b){throw 'PE32 expected'}
$optSize=U16 $image ($pe+20);$sectionCount=U16 $image ($pe+6);$sizeHeaders=[uint32](U32 $image ($opt+60))
$importRva=[uint32](U32 $image ($opt+96+8));$importSize=[uint32](U32 $image ($opt+96+12));$sectionTable=$opt+$optSize
$sections=@()
for($i=0;$i -lt $sectionCount;$i++){$at=$sectionTable+40*$i;$vs=[uint32](U32 $image ($at+8));$rva=[uint32](U32 $image ($at+12));$rs=[uint32](U32 $image ($at+16));$rawPointer=[uint32](U32 $image ($at+20));$sections += [pscustomobject]@{Rva=$rva;VirtualSize=$vs;RawSize=$rs;FileRawOffset=$rawPointer}}
function RvaToOffset([uint32]$rva){
  if($rva -lt $sizeHeaders){return [int]$rva}
  foreach($section in $sections){if($rva -ge $section.Rva -and $rva -lt ($section.Rva+[Math]::Max($section.VirtualSize,$section.RawSize))){$delta=[uint64]$rva-[uint64]$section.Rva;if($delta -ge $section.RawSize){throw ('Import RVA in zero-fill area 0x{0:X}' -f $rva)};return [int]([uint64]$section.FileRawOffset+$delta)}}
  throw ('RVA outside PE sections: 0x{0:X}' -f $rva)
}
if($importRva -eq 0 -or $importSize -eq 0){throw 'Candidate has no import directory'}
$importOffset=RvaToOffset $importRva;$imports=[Collections.Generic.List[object]]::new();$descriptor=$importOffset
while($descriptor -lt $importOffset+$importSize){
  $oft=[uint32](U32 $image $descriptor);$nameRva=[uint32](U32 $image ($descriptor+12));$iat=[uint32](U32 $image ($descriptor+16))
  if(($oft -bor $nameRva -bor $iat) -eq 0){break}
  $dll=ReadAsciiZ $image (RvaToOffset $nameRva);$thunkRva=if($oft){$oft}else{$iat};$slot=0
  while($true){$thunk=[uint32](U32 $image (RvaToOffset ($thunkRva+4*$slot)));if($thunk -eq 0){break};if(($thunk -band 0x80000000) -ne 0){$name=$null;$ordinal=[int]($thunk -band 0xffff)}else{$name=ReadAsciiZ $image ((RvaToOffset $thunk)+2);$ordinal=$null};$imports.Add([pscustomobject]@{dll=$dll;name=$name;ordinal=$ordinal});$slot++}
  $descriptor+=20
}
if($imports.Count -ne 82){throw ('Expected the pinned 82 imports, found {0}' -f $imports.Count)}
Add-Type -TypeDefinition @'
using System;
using System.Runtime.InteropServices;
public static class ImportProbeNative {
  [DllImport("kernel32.dll", SetLastError=true, CharSet=CharSet.Unicode)] public static extern IntPtr LoadLibraryExW(string file, IntPtr fileHandle, uint flags);
  [DllImport("kernel32.dll", SetLastError=true, CharSet=CharSet.Ansi, ExactSpelling=true)] public static extern IntPtr GetProcAddress(IntPtr module, string name);
  [DllImport("kernel32.dll", SetLastError=true)] public static extern bool FreeLibrary(IntPtr module);
}
'@
$system32=Join-Path $env:windir 'SysWOW64';$modules=@{};$missing=[Collections.Generic.List[object]]::new()
foreach($dll in ($imports.dll | Sort-Object -Unique)){
  $modulePath=Join-Path $system32 $dll
  if(-not(Test-Path -LiteralPath $modulePath)){throw ('Required module missing from 32-bit System directory: {0}' -f $dll)}
  $handle=[ImportProbeNative]::LoadLibraryExW($modulePath,[IntPtr]::Zero,0)
  if($handle -eq [IntPtr]::Zero){throw ('LoadLibraryEx failed for {0}, Win32={1}' -f $dll,[Runtime.InteropServices.Marshal]::GetLastWin32Error())}
  $modules[$dll.ToLowerInvariant()]=$handle
}
foreach($item in $imports){$handle=$modules[$item.dll.ToLowerInvariant()];if($null -ne $item.name){$address=[ImportProbeNative]::GetProcAddress($handle,$item.name)}else{$address=[ImportProbeNative]::GetProcAddress($handle,[IntPtr]$item.ordinal)};if($address -eq [IntPtr]::Zero){$missing.Add([pscustomobject]@{dll=$item.dll;name=$item.name;ordinal=$item.ordinal;win32=[Runtime.InteropServices.Marshal]::GetLastWin32Error()})}}
$freed=$true;foreach($handle in $modules.Values){if(-not[ImportProbeNative]::FreeLibrary($handle)){$freed=$false}}
$result=[pscustomobject]@{candidate=$candidatePath;sha256=(Get-FileHash -LiteralPath $candidatePath -Algorithm SHA256).Hash;import_count=$imports.Count;modules=@($modules.Keys);resolved=$imports.Count-$missing.Count;missing=@($missing);imports_were_resolved_in_candidate=$false;candidate_dllmain_called=$false;gta_or_plugin_loader_started=$false;probe_modules_freed=$freed}
$json=$result|ConvertTo-Json -Depth 5;[IO.File]::WriteAllText((Join-Path (Get-Location) $Report),$json+"`r`n",[Text.UTF8Encoding]::new($false));$result|Select-Object candidate,sha256,import_count,resolved,missing,probe_modules_freed|Format-List
if($missing.Count -ne 0 -or -not $freed){exit 2}
