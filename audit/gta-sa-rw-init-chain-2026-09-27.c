/* Temporary bounded Ghidra decompilation; not original source. */

/* entry 0x00801970; bounded CFG instructions=3; body bytes=10 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void BOUNDED_00801970(undefined4 param_1)

{
  _DAT_008e266c = param_1;
  return;
}



/* entry 0x0080A240; bounded CFG instructions=36; body bytes=272 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 BOUNDED_0080A240(void)

{
  *(undefined **)(_DAT_00c97b24 + 0xf0) = &UNK_00821bb5;
  *(undefined **)(_DAT_00c97b24 + 0xf4) = &UNK_008230b8;
  *(undefined **)(_DAT_00c97b24 + 0xf8) = &UNK_00826590;
  *(undefined **)(_DAT_00c97b24 + 0xfc) = &UNK_00821f40;
  *(undefined **)(_DAT_00c97b24 + 0x100) = &UNK_008265a0;
  *(undefined **)(_DAT_00c97b24 + 0x104) = &UNK_00826450;
  *(undefined **)(_DAT_00c97b24 + 0x108) = &UNK_0080a420;
  *(undefined **)(_DAT_00c97b24 + 0x10c) = &UNK_0080a400;
  *(undefined **)(_DAT_00c97b24 + 0x110) = &UNK_00822650;
  *(undefined **)(_DAT_00c97b24 + 0x114) = &UNK_008263c0;
  *(undefined **)(_DAT_00c97b24 + 0x118) = &UNK_008214d0;
  *(undefined **)(_DAT_00c97b24 + 0x11c) = &UNK_0080a350;
  *(undefined **)(_DAT_00c97b24 + 0x120) = &UNK_00826330;
  *(undefined **)(_DAT_00c97b24 + 0x124) = &UNK_0080a3a0;
  *(undefined **)(_DAT_00c97b24 + 0x128) = &UNK_0080a3d0;
  *(undefined **)(_DAT_00c97b24 + 300) = &UNK_0082244b;
  *(undefined **)(_DAT_00c97b24 + 0x130) = &UNK_008220ad;
  return 1;
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



/* entry 0x007F5F60; bounded CFG instructions=169; body bytes=972 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 BOUNDED_007F5F60(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  _DAT_00b4e9e0 = func_0x007fb0b0(0x24,0x40c,&UNK_004c9a60,&UNK_004c9a80,0);
  if (_DAT_00b4e9e0 < 0) {
    return 0;
  }
  puVar2 = (undefined4 *)0xb4e7e0;
  for (iVar1 = 0x80; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  DAT_00b4e830 = 0;
  DAT_00b4e831 = 0x18;
  _DAT_00b4e832 = 0;
  DAT_00b4e834 = 1;
  DAT_00b4e835 = 0x20;
  _DAT_00b4e836 = 0x500;
  DAT_00b4e838 = 0;
  DAT_00b4e839 = 0x20;
  _DAT_00b4e83a = 0x600;
  DAT_00b4e83c = 0;
  DAT_00b4e83d = 0x10;
  _DAT_00b4e83e = 0x200;
  DAT_00b4e840 = 0;
  DAT_00b4e841 = 0x10;
  _DAT_00b4e842 = 0xa00;
  DAT_00b4e844 = 1;
  DAT_00b4e845 = 0x10;
  _DAT_00b4e846 = 0x100;
  DAT_00b4e848 = 1;
  DAT_00b4e849 = 0x10;
  _DAT_00b4e84a = 0x300;
  DAT_00b4e84c = 0;
  DAT_00b4e84d = 8;
  _DAT_00b4e84e = 0;
  DAT_00b4e850 = 1;
  DAT_00b4e851 = 8;
  _DAT_00b4e852 = 0;
  DAT_00b4e854 = 1;
  DAT_00b4e855 = 0x10;
  _DAT_00b4e856 = 0;
  DAT_00b4e858 = 0;
  DAT_00b4e859 = 0x10;
  _DAT_00b4e85a = 0;
  DAT_00b4e85c = 1;
  DAT_00b4e85d = 0x20;
  _DAT_00b4e85e = 0;
  DAT_00b4e860 = 1;
  DAT_00b4e861 = 0x20;
  _DAT_00b4e862 = 0;
  DAT_00b4e864 = 0;
  DAT_00b4e865 = 0x20;
  _DAT_00b4e866 = 0;
  DAT_00b4e868 = 0;
  DAT_00b4e869 = 0x20;
  _DAT_00b4e86a = 0;
  DAT_00b4e86c = 1;
  DAT_00b4e86d = 0x20;
  _DAT_00b4e86e = 0;
  DAT_00b4e870 = 1;
  DAT_00b4e871 = 0x40;
  _DAT_00b4e872 = 0;
  DAT_00b4e880 = 1;
  DAT_00b4e881 = 0x10;
  _DAT_00b4e882 = 0;
  DAT_00b4e884 = 0;
  DAT_00b4e885 = 8;
  _DAT_00b4e886 = 0x2000;
  DAT_00b4e8a8 = 0;
  DAT_00b4e8a9 = 8;
  _DAT_00b4e8aa = 0x400;
  DAT_00b4e8ac = 1;
  DAT_00b4e8ad = 0x10;
  _DAT_00b4e8ae = 0;
  DAT_00b4e8b0 = 1;
  DAT_00b4e8b1 = 8;
  _DAT_00b4e8b2 = 0;
  DAT_00b4e8d0 = 0;
  DAT_00b4e8d1 = 0x10;
  _DAT_00b4e8d2 = 0;
  DAT_00b4e8d4 = 0;
  DAT_00b4e8d5 = 0x10;
  _DAT_00b4e8d6 = 0;
  _DAT_00b4e8fa = 0x700;
  _DAT_00b4e906 = 0x700;
  _DAT_00b4e922 = 0x700;
  _DAT_00b4e8fe = 0x900;
  _DAT_00b4e90e = 0x900;
  _DAT_00b4e916 = 0x900;
  _DAT_00b4e91e = 0x900;
  _DAT_00b4e92a = 0x900;
  _DAT_00b4e92e = 0x900;
  DAT_00b4e8d8 = 0;
  _DAT_00b4e8da = 0;
  DAT_00b4e8dc = 0;
  _DAT_00b4e8de = 0;
  DAT_00b4e8e0 = 0;
  _DAT_00b4e8e2 = 0;
  _DAT_00b4e8ee = 0;
  DAT_00b4e8f8 = 0;
  DAT_00b4e8fc = 0;
  DAT_00b4e904 = 0;
  DAT_00b4e90c = 0;
  DAT_00b4e914 = 0;
  DAT_00b4e91c = 0;
  DAT_00b4e920 = 0;
  DAT_00b4e928 = 0;
  DAT_00b4e92c = 0;
  DAT_00b4e924 = 0;
  _DAT_00b4e926 = 0;
  DAT_00b4e998 = 0;
  _DAT_00b4e99a = 0;
  DAT_00b4e99c = 0;
  _DAT_00b4e99e = 0;
  DAT_00b4e9a0 = 0;
  _DAT_00b4e9a2 = 0;
  _DAT_00b4e9a6 = 0;
  DAT_00b4e9a8 = 0;
  _DAT_00b4e9aa = 0;
  DAT_00b4e9ac = 0;
  _DAT_00b4e9ae = 0;
  _DAT_00b4e9b2 = 0;
  DAT_00b4e9b4 = 0;
  _DAT_00b4e9b6 = 0;
  DAT_00b4e8d9 = 0x20;
  DAT_00b4e8dd = 0x20;
  DAT_00b4e8e1 = 0x20;
  DAT_00b4e8ec = 1;
  DAT_00b4e8ed = 0x20;
  DAT_00b4e8f9 = 0x10;
  DAT_00b4e8fd = 0x20;
  DAT_00b4e905 = 0x10;
  DAT_00b4e90d = 0x20;
  DAT_00b4e915 = 0x20;
  DAT_00b4e91d = 0x20;
  DAT_00b4e921 = 0x10;
  DAT_00b4e929 = 0x20;
  DAT_00b4e92d = 0x20;
  DAT_00b4e925 = 0x10;
  DAT_00b4e999 = 0x40;
  DAT_00b4e99d = 0x10;
  DAT_00b4e9a1 = 0x20;
  DAT_00b4e9a4 = 1;
  DAT_00b4e9a5 = 0x40;
  DAT_00b4e9a9 = 0x20;
  DAT_00b4e9ad = 0x40;
  DAT_00b4e9b0 = 1;
  DAT_00b4e9b1 = 0x80;
  DAT_00b4e9b5 = 0x10;
  return 1;
}



/* entry 0x00808820; bounded CFG instructions=28; body bytes=86 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * BOUNDED_00808820(undefined4 *param_1)

{
  if ((*(int *)(_DAT_00c9a6f0 + _DAT_00c97b24) == 0) &&
     (*(int *)(_DAT_00c9a6f0 + 4 + _DAT_00c97b24) == -0x80000000)) {
    if ((param_1[1] & 0x80000000) == 0) {
      *(undefined4 *)(_DAT_00c9a6f0 + _DAT_00c97b24) = *param_1;
    }
    else {
      *(undefined4 *)(_DAT_00c9a6f0 + _DAT_00c97b24) = 0;
    }
    *(undefined4 *)(_DAT_00c9a6f0 + 4 + _DAT_00c97b24) = param_1[1];
    return param_1;
  }
  return param_1;
}



/* entry 0x008088D0; bounded CFG instructions=2; body bytes=5 */

undefined4 BOUNDED_008088D0(undefined4 param_1)

{
  return param_1;
}


