/* Temporary bounded Ghidra decompilation; not original source. */

/* entry 0x100860F0; bounded CFG instructions=112; body bytes=403 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall BOUNDED_100860F0(int *param_1)

{
  uint uVar1;
  code *pcVar2;
  int iVar3;
  uint uVar4;
  int *unaff_FS_OFFSET;
  undefined *puStack_64;
  int *piStack_60;
  undefined1 *puStack_40;
  uint uStack_3c;
  int iStack_10;
  undefined *puStack_c;
  uint uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &DAT_100d4897;
  iStack_10 = *unaff_FS_OFFSET;
  uStack_3c = _DAT_101940c0 ^ (uint)&stack0xfffffffc;
  *unaff_FS_OFFSET = (int)&iStack_10;
  puStack_40 = (undefined1 *)0x10086126;
  iVar3 = func_0x100a2bb0();
  if (iVar3 == 0x3e9) {
    uVar4 = param_1[1] - *param_1 >> 2;
    if ((uVar4 != 0) && (uVar1 = param_1[3], param_1[3] = uVar1 + 1, uVar4 <= uVar1))
    goto LAB_1008627d;
    uStack_8 = 1;
    puStack_40 = (undefined1 *)0x10086178;
    func_0x10088210();
    uStack_8 = uStack_8 & 0xffffff00;
    puStack_40 = (undefined1 *)&puStack_64;
    puStack_64 = &UNK_1017a188;
    piStack_60 = param_1;
    func_0x10086ae0();
    func_0x10086cd0();
    uStack_8 = 0xffffffff;
    func_0x10086a00();
  }
  puStack_40 = (undefined1 *)0x100861d1;
  iVar3 = func_0x100a2bb0();
  if (iVar3 == 0x3ea) {
    uVar4 = param_1[1] - *param_1 >> 2;
    if ((uVar4 != 0) && (uVar1 = param_1[3], param_1[3] = uVar1 + 1, uVar4 <= uVar1)) {
LAB_1008627d:
      puStack_40 = (undefined1 *)0x10086282;
      func_0x1006c050();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    uStack_8 = 3;
    puStack_40 = (undefined1 *)0x10086223;
    func_0x10088210();
    uStack_8 = CONCAT31(uStack_8._1_3_,2);
    puStack_40 = (undefined1 *)&puStack_64;
    puStack_64 = &UNK_1017a130;
    piStack_60 = param_1;
    func_0x10086ae0();
    func_0x10086cd0();
    func_0x10086a00();
  }
  *unaff_FS_OFFSET = iStack_10;
  return;
}


