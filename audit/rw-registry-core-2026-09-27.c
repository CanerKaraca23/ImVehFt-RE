/* Temporary bounded Ghidra decompilation; not original source. */

/* entry 0x008084A0; bounded CFG instructions=169; body bytes=515 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int BOUNDED_008084A0(int *param_1,int param_2,int param_3,undefined *param_4,undefined *param_5,
                    undefined *param_6)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  if (_DAT_00c9a6e4 != 0) {
    iVar1 = func_0x007f2b90();
    if (iVar1 == 0) {
      if (*(undefined **)(_DAT_00c97b24 + 0x144) != &UNK_00801c30) {
        uVar2 = 0;
        if (_DAT_00c9a6ec != 0) {
          do {
            if (param_1 == *(int **)(_DAT_00c9a6e8 + uVar2 * 4)) break;
            uVar2 = uVar2 + 1;
          } while (uVar2 < _DAT_00c9a6ec);
        }
        if (_DAT_00c9a6ec == uVar2) {
          iVar1 = (**(code **)(_DAT_00c97b24 + 0x134))(_DAT_00c9a6ec * 4 + 4,0x40000);
          uVar2 = 0;
          if (_DAT_00c9a6e8 != 0) {
            if (_DAT_00c9a6ec != 0) {
              do {
                uVar2 = uVar2 + 1;
                *(undefined4 *)(iVar1 + -4 + uVar2 * 4) =
                     *(undefined4 *)(_DAT_00c9a6e8 + -4 + uVar2 * 4);
              } while (uVar2 < _DAT_00c9a6ec);
            }
            (**(code **)(_DAT_00c97b24 + 0x138))(_DAT_00c9a6e8);
          }
          *(int **)(iVar1 + uVar2 * 4) = param_1;
          _DAT_00c9a6ec = _DAT_00c9a6ec + 1;
          _DAT_00c9a6e8 = iVar1;
        }
      }
      for (piVar3 = (int *)param_1[4]; piVar3 != (int *)0x0; piVar3 = (int *)piVar3[0xc]) {
        if (piVar3[2] == param_3) {
          uStack_8 = 1;
          uStack_4 = func_0x008088d0(0x80000017);
          func_0x00808820(&uStack_8);
          return *piVar3;
        }
      }
      iVar1 = (param_2 + 3U & 0xfffffffc) + *param_1;
      if (((param_1[2] == 0) || (iVar1 <= param_1[2])) &&
         (piVar3 = (int *)(**(code **)(_DAT_00c97b24 + 0x144))(_DAT_00c9a6e4,0x40000),
         piVar3 != (int *)0x0)) {
        *piVar3 = *param_1;
        *param_1 = iVar1;
        piVar3[1] = param_2;
        piVar3[2] = param_3;
        piVar3[3] = 0;
        piVar3[4] = 0;
        piVar3[5] = 0;
        piVar3[6] = 0;
        piVar3[7] = 0;
        if (param_4 == (undefined *)0x0) {
          param_4 = &UNK_008086b0;
        }
        piVar3[8] = (int)param_4;
        if (param_5 == (undefined *)0x0) {
          param_5 = &UNK_008086c0;
        }
        piVar3[9] = (int)param_5;
        if (param_6 == (undefined *)0x0) {
          param_6 = &UNK_008086d0;
        }
        piVar3[10] = (int)param_6;
        piVar3[0xb] = 0;
        piVar3[0xc] = 0;
        piVar3[0xd] = 0;
        piVar3[0xe] = (int)param_1;
        if (param_1[4] == 0) {
          param_1[4] = (int)piVar3;
          param_1[5] = (int)piVar3;
          return *piVar3;
        }
        *(int **)(param_1[5] + 0x30) = piVar3;
        piVar3[0xd] = param_1[5];
        param_1[5] = (int)piVar3;
        return *piVar3;
      }
    }
    else {
      uStack_8 = 1;
      uStack_4 = func_0x008088d0(0x80000017);
      func_0x00808820(&uStack_8);
    }
  }
  return -1;
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



/* entry 0x00808980; bounded CFG instructions=111; body bytes=299 */

/* WARNING: Type propagation algorithm not settling */

int BOUNDED_00808980(int param_1,int param_2,int param_3)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iStack_10;
  uint auStack_c [3];
  
  iVar4 = param_2;
  iVar3 = func_0x007ed2d0(param_2,3,&iStack_10,auStack_c);
  iVar2 = param_3;
  if (iVar3 != 0) {
    if ((auStack_c[0] < 0x34000) || (0x36003 < auStack_c[0])) {
      auStack_c[1] = 1;
      auStack_c[2] = func_0x008088d0(0x80000004);
      func_0x00808820(auStack_c + 1);
    }
    else {
      for (; iStack_10 != 0; iStack_10 = iStack_10 + (-0xc - param_2)) {
        iVar3 = func_0x007ed0f0(iVar4,&param_3,&param_2,0,0);
        if (iVar3 == 0) {
          return 0;
        }
        for (puVar1 = *(undefined4 **)(param_1 + 0x10); puVar1 != (undefined4 *)0x0;
            puVar1 = (undefined4 *)puVar1[0xc]) {
          if (puVar1[2] == param_3) {
            if ((code *)puVar1[3] != (code *)0x0) {
              iVar3 = (*(code *)puVar1[3])(iVar4,param_2,iVar2,*puVar1,puVar1[1]);
              goto LAB_00808a15;
            }
            break;
          }
        }
        iVar3 = func_0x007ecd00(iVar4,param_2);
LAB_00808a15:
        if (iVar3 == 0) {
          return 0;
        }
      }
      puVar1 = *(undefined4 **)(param_1 + 0x10);
      iStack_10 = 0;
      while( true ) {
        if (puVar1 == (undefined4 *)0x0) {
          return param_1;
        }
        if (((code *)puVar1[6] != (code *)0x0) &&
           (iVar4 = (*(code *)puVar1[6])(iVar2,*puVar1,puVar1[1]), iVar4 == 0)) break;
        puVar1 = (undefined4 *)puVar1[0xc];
      }
    }
  }
  return 0;
}



/* entry 0x00808B00; bounded CFG instructions=30; body bytes=61 */

int BOUNDED_00808B00(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  for (puVar1 = *(undefined4 **)(param_1 + 0x10); puVar1 != (undefined4 *)0x0;
      puVar1 = (undefined4 *)puVar1[0xc]) {
    if (((code *)puVar1[5] != (code *)0x0) &&
       (iVar2 = (*(code *)puVar1[5])(param_2,*puVar1,puVar1[1]), 0 < iVar2)) {
      iVar3 = iVar3 + 0xc + iVar2;
    }
  }
  return iVar3;
}



/* entry 0x00808B40; bounded CFG instructions=92; body bytes=201 */

int BOUNDED_00808B40(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  for (puVar1 = *(undefined4 **)(param_1 + 0x10); puVar1 != (undefined4 *)0x0;
      puVar1 = (undefined4 *)puVar1[0xc]) {
    if (((code *)puVar1[5] != (code *)0x0) &&
       (iVar2 = (*(code *)puVar1[5])(param_3,*puVar1,puVar1[1]), 0 < iVar2)) {
      iVar3 = iVar3 + 0xc + iVar2;
    }
  }
  iVar3 = func_0x007ed270(param_2,3,iVar3,0x36003,0xffff);
  if (iVar3 != 0) {
    puVar1 = *(undefined4 **)(param_1 + 0x10);
    while( true ) {
      if (puVar1 == (undefined4 *)0x0) {
        return param_1;
      }
      if (((((code *)puVar1[5] != (code *)0x0) && (puVar1[4] != 0)) &&
          (iVar3 = (*(code *)puVar1[5])(param_3,*puVar1,puVar1[1]), 0 < iVar3)) &&
         ((iVar2 = func_0x007ed270(param_2,puVar1[2],iVar3,0x36003,0xffff), iVar2 == 0 ||
          (iVar3 = (*(code *)puVar1[4])(param_2,iVar3,param_3,*puVar1,puVar1[1]), iVar3 == 0))))
      break;
      puVar1 = (undefined4 *)puVar1[0xc];
    }
  }
  return 0;
}



/* entry 0x00808C10; bounded CFG instructions=47; body bytes=113 */

undefined4 BOUNDED_00808C10(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iStack_4;
  
  iVar1 = param_2;
  iVar2 = func_0x007ed2d0(param_2,3,&param_2,0);
  if (iVar2 != 0) {
    while( true ) {
      if (param_2 == 0) {
        return param_1;
      }
      iVar2 = func_0x007ed0f0(iVar1,0,&iStack_4,0,0);
      if ((iVar2 == 0) || (iVar2 = func_0x007ecd00(iVar1,iStack_4), iVar2 == 0)) break;
      param_2 = param_2 + (-0xc - iStack_4);
    }
  }
  return 0;
}


