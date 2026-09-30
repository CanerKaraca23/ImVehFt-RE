/* Temporary bounded Ghidra decompilation; not original source. */

/* entry 0x008082E0; bounded CFG instructions=17; body bytes=61 */

undefined4 FUN_008082e0(void)

{
  DAT_00c9a6e4 = thunk_FUN_008019b0(0x3c,DAT_008e26ac,4,DAT_008e26b0,&DAT_00c9a6c0,0x40000);
  if (DAT_00c9a6e4 == 0) {
    return 0;
  }
  DAT_00c9a6ec = 0;
  return 1;
}



/* entry 0x008086E0; bounded CFG instructions=43; body bytes=83 */

int FUN_008086e0(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = *(undefined4 **)(param_1 + 0x10);
  while( true ) {
    if (puVar1 == (undefined4 *)0x0) {
      return param_1;
    }
    iVar2 = (*(code *)puVar1[8])(param_2,*puVar1,puVar1[1]);
    if (iVar2 == 0) break;
    puVar1 = (undefined4 *)puVar1[0xc];
  }
  for (puVar1 = (undefined4 *)puVar1[0xd]; puVar1 != (undefined4 *)0x0;
      puVar1 = (undefined4 *)puVar1[0xd]) {
    (*(code *)puVar1[9])(param_2,*puVar1,puVar1[1]);
  }
  return 0;
}



/* entry 0x008084A0; bounded CFG instructions=169; body bytes=515 */

int FUN_008084a0(int *param_1,int param_2,int param_3,undefined1 *param_4,undefined1 *param_5,
                undefined1 *param_6)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  undefined4 local_8;
  undefined4 local_4;
  
  if (DAT_00c9a6e4 != 0) {
    iVar1 = FUN_007f2b90();
    if (iVar1 == 0) {
      if (*(undefined1 **)(DAT_00c97b24 + 0x144) != &LAB_00801c30) {
        uVar2 = 0;
        if (DAT_00c9a6ec != 0) {
          do {
            if (param_1 == *(int **)(DAT_00c9a6e8 + uVar2 * 4)) break;
            uVar2 = uVar2 + 1;
          } while (uVar2 < DAT_00c9a6ec);
        }
        if (DAT_00c9a6ec == uVar2) {
          iVar1 = (**(code **)(DAT_00c97b24 + 0x134))(DAT_00c9a6ec * 4 + 4,0x40000);
          uVar2 = 0;
          if (DAT_00c9a6e8 != 0) {
            if (DAT_00c9a6ec != 0) {
              do {
                uVar2 = uVar2 + 1;
                *(undefined4 *)(iVar1 + -4 + uVar2 * 4) =
                     *(undefined4 *)(DAT_00c9a6e8 + -4 + uVar2 * 4);
              } while (uVar2 < DAT_00c9a6ec);
            }
            (**(code **)(DAT_00c97b24 + 0x138))(DAT_00c9a6e8);
          }
          *(int **)(iVar1 + uVar2 * 4) = param_1;
          DAT_00c9a6ec = DAT_00c9a6ec + 1;
          DAT_00c9a6e8 = iVar1;
        }
      }
      for (piVar3 = (int *)param_1[4]; piVar3 != (int *)0x0; piVar3 = (int *)piVar3[0xc]) {
        if (piVar3[2] == param_3) {
          local_8 = 1;
          local_4 = FUN_008088d0(0x80000017);
          FUN_00808820(&local_8);
          return *piVar3;
        }
      }
      iVar1 = (param_2 + 3U & 0xfffffffc) + *param_1;
      if (((param_1[2] == 0) || (iVar1 <= param_1[2])) &&
         (piVar3 = (int *)(**(code **)(DAT_00c97b24 + 0x144))(DAT_00c9a6e4,0x40000),
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
        if (param_4 == (undefined1 *)0x0) {
          param_4 = &LAB_008086b0;
        }
        piVar3[8] = (int)param_4;
        if (param_5 == (undefined1 *)0x0) {
          param_5 = &LAB_008086c0;
        }
        piVar3[9] = (int)param_5;
        if (param_6 == (undefined1 *)0x0) {
          param_6 = &LAB_008086d0;
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
      local_8 = 1;
      local_4 = FUN_008088d0(0x80000017);
      FUN_00808820(&local_8);
    }
  }
  return -1;
}



/* entry 0x00801FD0; bounded CFG instructions=48; body bytes=199 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00801fd0(undefined4 *param_1)

{
  int iVar1;
  
  DAT_00c9a604 = &DAT_00c9a604;
  _DAT_00c9a608 = &DAT_00c9a604;
  _DAT_00c9a630 = 1;
  DAT_00c9a634 = FUN_008019b0(0x24,0x10,4,0,&DAT_00c9a60c,0x40000);
  if (DAT_00c9a634 == 0) {
    _DAT_00c9a630 = DAT_00c9a634;
    return 0;
  }
  **(undefined4 **)(DAT_00c9a634 + 0x20) = *(undefined4 *)(DAT_00c9a634 + 0x1c);
  *(undefined4 *)(*(int *)(DAT_00c9a634 + 0x1c) + 4) = *(undefined4 *)(DAT_00c9a634 + 0x20);
  iVar1 = DAT_00c97b24;
  if (param_1 != (undefined4 *)0x0) {
    *(undefined4 *)(DAT_00c97b24 + 0x134) = *param_1;
    *(undefined4 *)(iVar1 + 0x138) = param_1[1];
    *(undefined4 *)(iVar1 + 0x13c) = param_1[2];
    *(undefined4 *)(iVar1 + 0x140) = param_1[3];
    return 1;
  }
  *(undefined1 **)(DAT_00c97b24 + 0x134) = &LAB_008020a0;
  *(code **)(DAT_00c97b24 + 0x138) = _free;
  *(undefined1 **)(DAT_00c97b24 + 0x13c) = &LAB_008020b0;
  *(undefined1 **)(DAT_00c97b24 + 0x140) = &LAB_008020d0;
  return 1;
}



/* entry 0x00804140; bounded CFG instructions=24; body bytes=178 */

undefined4 FUN_00804140(void)

{
  *(undefined1 **)(DAT_00c97b24 + 0xc4) = &LAB_00804200;
  *(code **)(DAT_00c97b24 + 200) = FUN_008232d8;
  *(code **)(DAT_00c97b24 + 0xcc) = _fclose;
  *(code **)(DAT_00c97b24 + 0xd0) = _fread;
  *(code **)(DAT_00c97b24 + 0xd4) = _fwrite;
  *(code **)(DAT_00c97b24 + 0xd8) = FUN_00823798;
  *(undefined1 **)(DAT_00c97b24 + 0xdc) = &LAB_008262b8;
  *(undefined1 **)(DAT_00c97b24 + 0xe0) = &LAB_008262a2;
  *(code **)(DAT_00c97b24 + 0xe4) = _fseek;
  *(code **)(DAT_00c97b24 + 0xe8) = _fflush;
  *(undefined1 **)(DAT_00c97b24 + 0xec) = &LAB_00826261;
  return 1;
}



/* entry 0x00801970; bounded CFG instructions=3; body bytes=10 */

void FUN_00801970(undefined4 param_1)

{
  DAT_008e266c = param_1;
  return;
}


