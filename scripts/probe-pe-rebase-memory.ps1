param(
  [Parameter(Mandatory=$true)][string]$Candidate,
  [Parameter(Mandatory=$true)][string]$Report
)
$ErrorActionPreference = 'Stop'
if ([IntPtr]::Size -ne 4) { throw 'Run this probe in 32-bit Windows PowerShell.' }
$resolvedCandidate = (Resolve-Path -LiteralPath $Candidate).Path
$bytes = [IO.File]::ReadAllBytes($resolvedCandidate)
function U16([byte[]]$b,[int]$o) { [BitConverter]::ToUInt16($b,$o) }
function U32([byte[]]$b,[int]$o) { [BitConverter]::ToUInt32($b,$o) }
$pe = [int](U32 $bytes 0x3c)
if ([Text.Encoding]::ASCII.GetString($bytes,$pe,4) -ne "PE`0`0") { throw 'Bad PE signature' }
$sectionCount = U16 $bytes ($pe+6)
$optSize = U16 $bytes ($pe+20)
$opt = $pe+24
if ((U16 $bytes $opt) -ne 0x10b) { throw 'PE32 expected' }
$preferred = [uint32](U32 $bytes ($opt+28))
$sizeImage = [uint32](U32 $bytes ($opt+56))
$sizeHeaders = [uint32](U32 $bytes ($opt+60))
$relocRva = [uint32](U32 $bytes ($opt+96+5*8))
$relocSize = [uint32](U32 $bytes ($opt+96+5*8+4))
$sectionTable = $opt+$optSize
$sections = @()
for ($i=0; $i -lt $sectionCount; $i++) {
  $at = $sectionTable+40*$i
  $name = [Text.Encoding]::ASCII.GetString($bytes,$at,8).Trim([char]0)
  $virtualSize = [uint32](U32 $bytes ($at+8)); $rva = [uint32](U32 $bytes ($at+12))
  $rawSize = [uint32](U32 $bytes ($at+16)); $rawPointer = [uint32](U32 $bytes ($at+20))
  $sections += [pscustomobject]@{name=$name;rva=$rva;virtualSize=$virtualSize;rawSize=$rawSize;fileRawOffset=$rawPointer}
}
function RvaToOffset([uint32]$rva) {
  if ($rva -lt $sizeHeaders) { return [int]$rva }
  foreach ($s in $sections) {
    if ($rva -ge $s.rva -and $rva -lt ($s.rva+[Math]::Max($s.virtualSize,$s.rawSize))) {
      $delta = [uint64]$rva-[uint64]$s.rva
      if ($delta -ge $s.rawSize) { throw ('RVA in zero-fill area: 0x{0:X}' -f $rva) }
      return [int]([uint64]$s.fileRawOffset+$delta)
    }
  }
  throw ('RVA outside file-backed sections: 0x{0:X}' -f $rva)
}
$relocOff = RvaToOffset $relocRva
$sites = [Collections.Generic.List[uint32]]::new()
$cursor = $relocOff; $relocEnd = $relocOff+$relocSize
while ($cursor -lt $relocEnd) {
  if ($cursor+8 -gt $relocEnd) { throw 'Truncated relocation block' }
  $page = [uint32](U32 $bytes $cursor); $blockSize = [uint32](U32 $bytes ($cursor+4))
  if ($blockSize -lt 8 -or ($blockSize%4) -ne 0 -or $cursor+$blockSize -gt $relocEnd) { throw ('Invalid relocation block at file offset {0}: page 0x{1:X}, size 0x{2:X}, end 0x{3:X}' -f $cursor,$page,$blockSize,$relocEnd) }
  for ($relocEntryOffset=$cursor+8; $relocEntryOffset -lt $cursor+$blockSize; $relocEntryOffset+=2) {
    $entry = U16 $bytes $relocEntryOffset; $kind = $entry -shr 12
    if ($kind -eq 3) { $sites.Add([uint32]($page+($entry -band 0xfff))) }
    elseif ($kind -ne 0) { throw ('Unexpected relocation type {0}' -f $kind) }
  }
  $cursor += $blockSize
}
if (($sites | Select-Object -Unique).Count -ne $sites.Count) { throw 'Duplicate HIGHLOW sites' }
Add-Type -TypeDefinition @'
using System;
using System.Runtime.InteropServices;
public static class RebaseProbeNative {
  [DllImport("kernel32.dll", SetLastError=true, ExactSpelling=true)] public static extern IntPtr VirtualAlloc(IntPtr address, UIntPtr size, uint allocationType, uint protect);
  [DllImport("kernel32.dll", SetLastError=true, CharSet=CharSet.Unicode)] public static extern IntPtr LoadLibraryExW(string file, IntPtr fileHandle, uint flags);
  [DllImport("kernel32.dll", SetLastError=true)] public static extern bool FreeLibrary(IntPtr module);
  [DllImport("kernel32.dll", SetLastError=true, ExactSpelling=true)] public static extern bool VirtualFree(IntPtr address, UIntPtr size, uint freeType);
  public static uint Ptr32(IntPtr value) { return unchecked((uint)value.ToInt32()); }
  public static int Delta(uint mapped, uint preferred) { return unchecked((int)(mapped-preferred)); }
  public static uint AddDelta(uint value, int delta) { return unchecked(value+(uint)delta); }
  public static uint Read32(IntPtr address) { return unchecked((uint)Marshal.ReadInt32(address)); }
}
'@
$reserved = [RebaseProbeNative]::VirtualAlloc([IntPtr]([int64]$preferred),[UIntPtr]$sizeImage,0x2000,0x01)
if ($reserved -eq [IntPtr]::Zero) { throw ('Could not reserve preferred base 0x{0:X8}; Win32={1}' -f $preferred,[Runtime.InteropServices.Marshal]::GetLastWin32Error()) }
$module = [RebaseProbeNative]::LoadLibraryExW($resolvedCandidate,[IntPtr]::Zero,1)
if ($module -eq [IntPtr]::Zero) {
  $err=[Runtime.InteropServices.Marshal]::GetLastWin32Error()
  [void][RebaseProbeNative]::VirtualFree($reserved,[UIntPtr]::Zero,0x8000)
  throw ('LoadLibraryExW failed; Win32={0}' -f $err)
}
$mismatches = [Collections.Generic.List[object]]::new()
$moduleBits = [RebaseProbeNative]::Ptr32($module)
$delta = [RebaseProbeNative]::Delta($moduleBits,$preferred)
foreach ($site in $sites) {
  $fileOffset = RvaToOffset $site
  $fileValue = [uint32](U32 $bytes $fileOffset)
  $expected = [RebaseProbeNative]::AddDelta($fileValue,$delta)
  $actual = [RebaseProbeNative]::Read32([IntPtr]::Add($module,[int]$site))
  if ($actual -ne $expected) {
    $mismatches.Add([pscustomobject]@{rva=('0x{0:X}' -f $site);file=('0x{0:X8}' -f $fileValue);expected=('0x{0:X8}' -f $expected);actual=('0x{0:X8}' -f $actual)})
  }
}
$moduleBase = ('0x{0:X8}' -f $moduleBits)
$freed = [RebaseProbeNative]::FreeLibrary($module)
$released = [RebaseProbeNative]::VirtualFree($reserved,[UIntPtr]::Zero,0x8000)
$result = [pscustomobject]@{
  candidate=$resolvedCandidate; sha256=(Get-FileHash -LiteralPath $resolvedCandidate -Algorithm SHA256).Hash
  preferred_base=('0x{0:X8}' -f $preferred); mapped_base=$moduleBase; relocation_delta=('0x{0:X8}' -f [uint32]$delta)
  highlow_sites=$sites.Count; mismatches=$mismatches.Count; mismatch_examples=@($mismatches | Select-Object -First 20)
  imports_resolved=$false; dllmain_called=$false; gta_or_plugin_loader_started=$false
  module_freed=$freed; reservation_released=$released
}
$json = $result | ConvertTo-Json -Depth 6
[IO.File]::WriteAllText((Join-Path (Get-Location) $Report),$json+"`r`n",[Text.UTF8Encoding]::new($false))
$result | Select-Object candidate,sha256,preferred_base,mapped_base,relocation_delta,highlow_sites,mismatches | Format-List
if ($mismatches.Count -ne 0) { exit 2 }
