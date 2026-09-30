/* Temporary bounded Ghidra decompilation; not original source. */

/* entry 0x00801970; bounded CFG instructions=3; body bytes=10 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void BOUNDED_00801970(undefined4 param_1)

{
  _DAT_008e266c = param_1;
  return;
}



/* entry 0x00801FD0; bounded CFG instructions=48; body bytes=199 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 BOUNDED_00801FD0(undefined4 *param_1)

{
  int iVar1;
  
  _DAT_00c9a604 = &DAT_00c9a604;
  _DAT_00c9a608 = &DAT_00c9a604;
  _DAT_00c9a630 = 1;
  _DAT_00c9a634 = func_0x008019b0(0x24,0x10,4,0,0xc9a60c,0x40000);
  if (_DAT_00c9a634 == 0) {
    _DAT_00c9a630 = _DAT_00c9a634;
    return 0;
  }
  **(undefined4 **)(_DAT_00c9a634 + 0x20) = *(undefined4 *)(_DAT_00c9a634 + 0x1c);
  *(undefined4 *)(*(int *)(_DAT_00c9a634 + 0x1c) + 4) = *(undefined4 *)(_DAT_00c9a634 + 0x20);
  iVar1 = _DAT_00c97b24;
  if (param_1 != (undefined4 *)0x0) {
    *(undefined4 *)(_DAT_00c97b24 + 0x134) = *param_1;
    *(undefined4 *)(iVar1 + 0x138) = param_1[1];
    *(undefined4 *)(iVar1 + 0x13c) = param_1[2];
    *(undefined4 *)(iVar1 + 0x140) = param_1[3];
    return 1;
  }
  *(undefined **)(_DAT_00c97b24 + 0x134) = &UNK_008020a0;
  *(undefined **)(_DAT_00c97b24 + 0x138) = &UNK_0082413f;
  *(undefined **)(_DAT_00c97b24 + 0x13c) = &UNK_008020b0;
  *(undefined **)(_DAT_00c97b24 + 0x140) = &UNK_008020d0;
  return 1;
}



/* entry 0x00804140; bounded CFG instructions=24; body bytes=178 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 BOUNDED_00804140(void)

{
  *(undefined **)(_DAT_00c97b24 + 0xc4) = &UNK_00804200;
  *(undefined **)(_DAT_00c97b24 + 200) = &UNK_008232d8;
  *(undefined **)(_DAT_00c97b24 + 0xcc) = &UNK_0082318b;
  *(undefined **)(_DAT_00c97b24 + 0xd0) = &UNK_00823521;
  *(undefined **)(_DAT_00c97b24 + 0xd4) = &UNK_00823674;
  *(undefined **)(_DAT_00c97b24 + 0xd8) = &UNK_00823798;
  *(undefined **)(_DAT_00c97b24 + 0xdc) = &UNK_008262b8;
  *(undefined **)(_DAT_00c97b24 + 0xe0) = &UNK_008262a2;
  *(undefined **)(_DAT_00c97b24 + 0xe4) = &UNK_0082374f;
  *(undefined **)(_DAT_00c97b24 + 0xe8) = &UNK_00823e86;
  *(undefined **)(_DAT_00c97b24 + 0xec) = &UNK_00826261;
  return 1;
}



/* entry 0x008082E0; bounded CFG instructions=17; body bytes=61 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 BOUNDED_008082E0(void)

{
  _DAT_00c9a6e4 = func_0x00801b70(0x3c,_DAT_008e26ac,4,_DAT_008e26b0,0xc9a6c0,0x40000);
  if (_DAT_00c9a6e4 == 0) {
    return 0;
  }
  _DAT_00c9a6ec = 0;
  return 1;
}



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



/* entry 0x007F3170; bounded CFG instructions=208; body bytes=788 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int BOUNDED_007F3170(undefined4 param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  bool bVar17;
  
  _DAT_00c97b24 = 0xc979c8;
  bVar17 = (param_2 & 1) == 0;
  if (bVar17) {
    _DAT_00c97b0c = &UNK_00801c30;
    _DAT_00c97b10 = &UNK_00801d50;
  }
  else {
    _DAT_00c97b0c = &UNK_007f3490;
    _DAT_00c97b10 = &UNK_007f34b0;
  }
  BOUNDED_00801970(bVar17);
  *(undefined4 *)(_DAT_00c97b24 + 0x154) = param_3;
  if ((*(int *)(_DAT_00c97b24 + 0x150) == 0) && (iVar1 = func_0x0080a240(), iVar1 != 0)) {
    iVar1 = BOUNDED_00801FD0(param_1);
    if (iVar1 != 0) {
      iVar1 = BOUNDED_00804140();
      if (iVar1 != 0) {
        iVar1 = BOUNDED_008082E0();
        if (iVar1 != 0) {
          uVar2 = BOUNDED_008084A0(0x8e2298,8,0x40f,&UNK_008087d0,&UNK_00808810,0);
          uVar3 = BOUNDED_008084A0(0x8e2298,0x18,0x401,&UNK_007ede90,&UNK_007ede20,0);
          uVar4 = BOUNDED_008084A0(0x8e2298,0,0x40d,&UNK_0080aa40,&UNK_0080aa50,0);
          uVar5 = BOUNDED_008084A0(0x8e2298,0x18,0x402,&UNK_007f16c0,&UNK_007f1660,0);
          uVar6 = BOUNDED_008084A0(0x8e2298,4,0x403,&UNK_007efef0,&UNK_007eff70,0);
          uVar7 = BOUNDED_008084A0(0x8e2298,4,0x404,&UNK_007ec780,&UNK_007ec7e0,0);
          uVar8 = BOUNDED_008084A0(0x8e2298,4,0x405,&UNK_007ee110,&UNK_007ee0b0,0);
          uVar9 = BOUNDED_008084A0(0x8e2298,0x220,0x406,&UNK_00802280,&UNK_008024e0,0);
          uVar10 = BOUNDED_008084A0(0x8e2298,100,0x407,&UNK_007fb370,&UNK_007fb310,0);
          uVar11 = BOUNDED_008084A0(0x8e2298,0x34,0x408,&UNK_007f3ea0,&UNK_007f3d00,0);
          uVar12 = BOUNDED_008084A0(0x8e2298,0x60,0x409,&UNK_00807c40,&UNK_00807c60,0);
          uVar13 = BOUNDED_008084A0(0x8e2298,4,0x412,&UNK_0080a780,&UNK_0080a7e0,0);
          uVar14 = func_0x00807c70();
          uVar15 = BOUNDED_008084A0(0x8e2298,0x74,0x40a,&UNK_007efe20,&UNK_007efde0,0);
          uVar16 = BOUNDED_008084A0(0x8e2298,0x28,0x40b,&UNK_00807c90,&UNK_00807d80,0);
          if ((-1 < (int)(uVar16 | uVar15 |
                         uVar14 | uVar13 | uVar12 | uVar11 | uVar10 | uVar9 | uVar8 | uVar7 | uVar6
                         | uVar5 | uVar4 | uVar3 | uVar2)) &&
             (iVar1 = func_0x007f5f60(), iVar1 != 0)) {
            *(undefined4 *)(_DAT_00c97b24 + 0x150) = 1;
            return iVar1;
          }
          func_0x00808320();
        }
        func_0x00804240();
      }
      func_0x008020f0();
    }
    func_0x0080a440();
  }
  return 0;
}


