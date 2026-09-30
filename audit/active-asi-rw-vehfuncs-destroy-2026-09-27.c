/* Temporary bounded Ghidra decompilation; not original source. */

/* entry 0x100513EA; bounded CFG instructions=24; body bytes=68 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void BOUNDED_100513EA(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  if (param_1 != 0) {
    iVar1 = HeapFree(_DAT_101133f8,0,param_1);
    if (iVar1 == 0) {
      uVar2 = GetLastError();
      uVar2 = func_0x100598f0(uVar2);
      puVar3 = (undefined4 *)func_0x100599ab();
      *puVar3 = uVar2;
    }
  }
  return;
}


