/* Temporary bounded Ghidra decompilation; not original source. */

/* entry 0x100BB9DA; bounded CFG instructions=24; body bytes=68 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void BOUNDED_100BB9DA(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  if (param_1 != 0) {
    iVar1 = HeapFree(_DAT_1015e38c,0,param_1);
    if (iVar1 == 0) {
      uVar2 = GetLastError();
      uVar2 = func_0x100c7a39(uVar2);
      puVar3 = (undefined4 *)func_0x100c7af4();
      *puVar3 = uVar2;
    }
  }
  return;
}


