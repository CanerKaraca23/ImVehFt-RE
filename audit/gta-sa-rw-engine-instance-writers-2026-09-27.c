/* Temporary bounded Ghidra decompilation; not original source. */

/* entry 0x007F2F00; bounded CFG instructions=34; body bytes=102 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int BOUNDED_007F2F00(void)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  iVar2 = func_0x007f2ab0(_DAT_00c97b24 + 4,1,0,0,0);
  puVar1 = _DAT_00c97b24;
  if (iVar2 != 0) {
    _DAT_00c97b24 = (undefined4 *)0xc979c8;
    puVar4 = puVar1;
    puVar5 = (undefined4 *)0xc979c8;
    for (iVar3 = 0x56; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    (*_DAT_00c97b00)(puVar1);
    _DAT_00c97b20 = _DAT_00c97b20 + -1;
    _DAT_00c97b24[0x54] = 1;
  }
  return iVar2;
}



/* entry 0x007F2F70; bounded CFG instructions=149; body bytes=447 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 BOUNDED_007F2F70(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  if (_DAT_00c97b24 == (undefined4 *)0x0) {
    _DAT_00c97b24 = (undefined4 *)0xc979c8;
  }
  if (*(int *)((int)_DAT_00c97b24 + 0x150) == 1) {
    if (param_1 == 0) {
      uStack_8 = 1;
      uStack_4 = func_0x008088d0(0x80000016);
      func_0x00808820(&uStack_8);
      return 0;
    }
    iVar1 = func_0x007f9c20();
    if (iVar1 != 0) {
      puVar2 = (undefined4 *)(**(code **)((int)_DAT_00c97b24 + 0x134))(_DAT_008e2298,0x40000);
      if (puVar2 == (undefined4 *)0x0) {
        _DAT_00c97b24 = (undefined4 *)0xc979c8;
        uStack_8 = 1;
        uStack_4 = func_0x008088d0(0x80000013,_DAT_008e2298);
        func_0x00808820(&uStack_8);
        return 0;
      }
      puVar4 = (undefined4 *)0xc979c8;
      puVar5 = puVar2;
      _DAT_00c97b24 = puVar2;
      for (iVar3 = 0x56; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      func_0x007f2ab0(iVar1,4,_DAT_00c97b24 + 4,_DAT_00c97b24 + 0x4d,0);
      iVar3 = func_0x007f2ab0(iVar1,0,0,param_1,0);
      if (iVar3 != 0) {
        func_0x007f2ab0(iVar1,0xb,_DAT_00c97b24 + 0x12,0,0x1d);
        _DAT_00c97b20 = _DAT_00c97b20 + 1;
        _DAT_00c97b24[0x54] = 2;
        return 1;
      }
      _DAT_00c97b24 = (undefined4 *)0xc979c8;
      puVar4 = puVar2;
      puVar5 = (undefined4 *)0xc979c8;
      for (iVar1 = 0x56; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      (*_DAT_00c97b00)(puVar2);
      return 0;
    }
  }
  else {
    uStack_8 = 1;
    uStack_4 = func_0x008088d0(0x80000001);
    func_0x00808820(&uStack_8);
  }
  return 0;
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
  func_0x00801970(bVar17);
  *(undefined4 *)(_DAT_00c97b24 + 0x154) = param_3;
  if ((*(int *)(_DAT_00c97b24 + 0x150) == 0) && (iVar1 = func_0x0080a240(), iVar1 != 0)) {
    iVar1 = func_0x00801fd0(param_1);
    if (iVar1 != 0) {
      iVar1 = func_0x00804140();
      if (iVar1 != 0) {
        iVar1 = func_0x008082e0();
        if (iVar1 != 0) {
          uVar2 = func_0x008084a0(&DAT_008e2298,8,0x40f,&UNK_008087d0,&UNK_00808810,0);
          uVar3 = func_0x008084a0(&DAT_008e2298,0x18,0x401,&UNK_007ede90,&UNK_007ede20,0);
          uVar4 = func_0x008084a0(&DAT_008e2298,0,0x40d,&UNK_0080aa40,&UNK_0080aa50,0);
          uVar5 = func_0x008084a0(&DAT_008e2298,0x18,0x402,&UNK_007f16c0,&UNK_007f1660,0);
          uVar6 = func_0x008084a0(&DAT_008e2298,4,0x403,&UNK_007efef0,&UNK_007eff70,0);
          uVar7 = func_0x008084a0(&DAT_008e2298,4,0x404,&UNK_007ec780,&UNK_007ec7e0,0);
          uVar8 = func_0x008084a0(&DAT_008e2298,4,0x405,&UNK_007ee110,&UNK_007ee0b0,0);
          uVar9 = func_0x008084a0(&DAT_008e2298,0x220,0x406,&UNK_00802280,&UNK_008024e0,0);
          uVar10 = func_0x008084a0(&DAT_008e2298,100,0x407,&UNK_007fb370,&UNK_007fb310,0);
          uVar11 = func_0x008084a0(&DAT_008e2298,0x34,0x408,&UNK_007f3ea0,&UNK_007f3d00,0);
          uVar12 = func_0x008084a0(&DAT_008e2298,0x60,0x409,&UNK_00807c40,&UNK_00807c60,0);
          uVar13 = func_0x008084a0(&DAT_008e2298,4,0x412,&UNK_0080a780,&UNK_0080a7e0,0);
          uVar14 = func_0x00807c70();
          uVar15 = func_0x008084a0(&DAT_008e2298,0x74,0x40a,&UNK_007efe20,&UNK_007efde0,0);
          uVar16 = func_0x008084a0(&DAT_008e2298,0x28,0x40b,&UNK_00807c90,&UNK_00807d80,0);
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


