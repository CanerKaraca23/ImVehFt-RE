/* Temporary bounded Ghidra decompilation; not original source. */

/* entry 0x007F3820; bounded CFG instructions=43; body bytes=121 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 BOUNDED_007F3820(int *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_1[0x15];
  iVar2 = iVar1 + -1;
  param_1[0x15] = iVar2;
  if (iVar2 < 1) {
    param_1[0x15] = iVar1;
    func_0x00808740(0x8e23cc,param_1);
    if (param_1[1] != 0) {
      *(int *)param_1[3] = param_1[2];
      *(int *)(param_1[2] + 4) = param_1[3];
    }
    if (*param_1 != 0) {
      func_0x007fb020(*param_1);
      *param_1 = 0;
    }
    param_1[0x15] = param_1[0x15] + -1;
    (**(code **)(_DAT_00c97b24 + 0x148))(*(undefined4 *)(_DAT_00c97b4c + 8 + _DAT_00c97b24),param_1)
    ;
  }
  return 1;
}



/* entry 0x007FB020; bounded CFG instructions=20; body bytes=62 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 BOUNDED_007FB020(undefined4 param_1)

{
  func_0x00808740(0x8e2518,param_1);
  (**(code **)(_DAT_00c97b24 + 0x5c))(0,param_1,0);
  (**(code **)(_DAT_00c97b24 + 0x148))
            (*(undefined4 *)(_DAT_00c980d8 + 0x60 + _DAT_00c97b24),param_1);
  return 1;
}



/* entry 0x00808740; bounded CFG instructions=23; body bytes=45 */

int BOUNDED_00808740(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  
  for (puVar1 = *(undefined4 **)(param_1 + 0x14); puVar1 != (undefined4 *)0x0;
      puVar1 = (undefined4 *)puVar1[0xd]) {
    (*(code *)puVar1[9])(param_2,*puVar1,puVar1[1]);
  }
  return param_1;
}



/* entry 0x007FB230; bounded CFG instructions=51; body bytes=154 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int BOUNDED_007FB230(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = (**(code **)(_DAT_00c97b24 + 0x144))
                    (*(undefined4 *)(_DAT_00c980d8 + 0x60 + _DAT_00c97b24),0x30407);
  if (iVar2 != 0) {
    pcVar1 = *(code **)(_DAT_00c97b24 + 0x58);
    *(undefined4 *)(iVar2 + 0xc) = param_1;
    *(undefined1 *)(iVar2 + 0x22) = 0;
    *(undefined4 *)(iVar2 + 0x10) = param_2;
    *(undefined4 *)(iVar2 + 0x14) = param_3;
    *(undefined1 *)(iVar2 + 0x21) = 0;
    *(undefined2 *)(iVar2 + 0x1c) = 0;
    *(undefined2 *)(iVar2 + 0x1e) = 0;
    *(int *)iVar2 = iVar2;
    *(undefined4 *)(iVar2 + 4) = 0;
    *(undefined4 *)(iVar2 + 8) = 0;
    iVar3 = (*pcVar1)(0,iVar2,param_4);
    if (iVar3 != 0) {
      func_0x008086e0(0x8e2518,iVar2);
      return iVar2;
    }
    (**(code **)(_DAT_00c97b24 + 0x148))(*(undefined4 *)(_DAT_00c980d8 + 0x60 + _DAT_00c97b24));
  }
  return 0;
}


