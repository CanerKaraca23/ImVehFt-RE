/* Temporary bounded Ghidra decompilation; not original source. */

/* entry 0x100AED60; bounded CFG instructions=27; body bytes=58 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int BOUNDED_100AED60(int param_1)

{
  int iVar1;
  
  if (param_1 != 0) {
    iVar1 = _DAT_1015d334 + param_1;
    if ((iVar1 != 0) && (*(int *)(iVar1 + 4) != 0)) {
      func_0x100baa3d(*(int *)(iVar1 + 4),0x40);
      *(undefined4 *)(iVar1 + 4) = 0;
    }
    return param_1;
  }
  return 0;
}


