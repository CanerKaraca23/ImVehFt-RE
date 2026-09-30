/* Temporary bounded Ghidra decompilation; not original source. */

/* entry 0x0074CCC0; bounded CFG instructions=51; body bytes=165 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 BOUNDED_0074CCC0(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 0xe);
  if (sVar1 == 1 || sVar1 + -1 < 0) {
    if (*(int *)(param_1 + 0x58) != 0) {
      func_0x00807de0(*(int *)(param_1 + 0x58));
    }
    *(ushort *)(param_1 + 0xc) = *(ushort *)(param_1 + 0xc) | 0xfff;
    *(undefined2 *)(param_1 + 0xe) = *(undefined2 *)(param_1 + 0xe);
    if (*(int *)(param_1 + 0x54) != 0) {
      func_0x00758bc0(*(int *)(param_1 + 0x54));
      *(undefined4 *)(param_1 + 0x54) = 0;
    }
    func_0x00808740(0x8d628c,param_1);
    if (*(int *)(param_1 + 0x5c) != 0) {
      (**(code **)(_DAT_00c97b24 + 0x138))(*(int *)(param_1 + 0x5c));
      *(undefined4 *)(param_1 + 0x5c) = 0;
    }
    func_0x0074e150(param_1 + 0x20);
    *(short *)(param_1 + 0xe) = *(short *)(param_1 + 0xe) + -1;
    (**(code **)(_DAT_00c97b24 + 0x138))(param_1);
    return 1;
  }
  *(short *)(param_1 + 0xe) = sVar1 + -1;
  return 1;
}



/* entry 0x00749C50; bounded CFG instructions=68; body bytes=201 */

/* WARNING: Removing unreachable block (ram,0x00749cd2) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 * BOUNDED_00749C50(void)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  
  puVar2 = (undefined1 *)
           (**(code **)(_DAT_00c97b24 + 0x144))
                     (*(undefined4 *)(_DAT_00c924ac + _DAT_00c97b24),0x30014);
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = 1;
    puVar2[1] = 0;
    *(undefined4 *)(puVar2 + 4) = 0;
    *(undefined **)(puVar2 + 0x10) = &UNK_00749d20;
    *(undefined4 *)(puVar2 + 0x14) = 0;
    puVar2[2] = 5;
    puVar2[3] = 1;
    func_0x00804ef0(puVar2,0);
    *(undefined4 *)(puVar2 + 0x18) = 0;
    puVar2[3] = puVar2[3] | 1;
    *(undefined4 *)(puVar2 + 0x28) = 0;
    *(undefined4 *)(puVar2 + 0x1c) = 0;
    *(undefined4 *)(puVar2 + 0x20) = 0;
    *(undefined4 *)(puVar2 + 0x24) = 0;
    *(undefined4 *)(puVar2 + 0x38) = 0;
    *(undefined4 *)(puVar2 + 0x2c) = 0;
    *(undefined4 *)(puVar2 + 0x30) = 0;
    *(undefined4 *)(puVar2 + 0x34) = 0;
    *(undefined **)(puVar2 + 0x48) = &UNK_007491c0;
    *(undefined4 *)(puVar2 + 0x54) = 0x3f800000;
    *(undefined4 *)(puVar2 + 0x58) = 0x3f800000;
    puVar1 = puVar2 + 100;
    *(undefined2 *)(puVar2 + 0x50) = 0;
    *(undefined2 *)(puVar2 + 0x52) = 0;
    *(undefined4 *)(puVar2 + 0x5c) = 0;
    *(undefined4 *)(puVar2 + 0x4c) = 3;
    *(undefined4 *)(puVar2 + 0x44) = 0;
    *(undefined4 *)(puVar2 + 0x40) = 0;
    *(undefined4 *)(puVar2 + 0x3c) = 0;
    *(undefined4 *)(puVar2 + 0x6c) = 0;
    *(undefined1 **)puVar1 = puVar1;
    *(undefined1 **)(puVar2 + 0x68) = puVar1;
    func_0x008086e0(0x8d624c,puVar2);
    return puVar2;
  }
  return (undefined1 *)0x0;
}



/* entry 0x0074CA90; bounded CFG instructions=180; body bytes=543 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 * BOUNDED_0074CA90(int param_1,int param_2,uint param_3)

{
  undefined1 *puVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  uint uVar6;
  undefined4 *puVar7;
  uint uStack_8;
  undefined4 uStack_4;
  
  if (param_1 < 0) {
    return (undefined1 *)0x0;
  }
  if (0xffff < param_1) {
    uStack_8 = 2;
    uStack_4 = func_0x008088d0(6);
    func_0x00808820(&uStack_8);
    return (undefined1 *)0x0;
  }
  if (param_2 < 0) {
    return (undefined1 *)0x0;
  }
  if ((param_3 & 0xff0000) == 0) {
    if (-1 < (char)(byte)param_3) {
      uVar6 = param_3 >> 2 & 1;
      goto LAB_0074cc5a;
    }
    uVar6 = 2;
  }
  else {
    uVar6 = param_3 >> 0x10 & 0xff;
LAB_0074cc5a:
    if (uVar6 == 1) {
      uVar5 = 4;
      goto LAB_0074cafc;
    }
  }
  uVar5 = -(uint)(1 < uVar6) & 0x80;
LAB_0074cafc:
  uStack_8 = param_3 & 0x1000000;
  iVar2 = _DAT_008d628c;
  if (uStack_8 == 0) {
    if ((param_3 & 8) != 0) {
      iVar2 = _DAT_008d628c + param_1 * 4;
    }
    if (uVar6 != 0) {
      iVar2 = iVar2 + uVar6 * param_1 * 8;
    }
    iVar2 = iVar2 + param_2 * 8;
  }
  puVar1 = (undefined1 *)(**(code **)(_DAT_00c97b24 + 0x134))(iVar2,0x3000f);
  if ((puVar1 == (undefined1 *)0x0) || (iVar2 = func_0x0074e1b0(puVar1 + 0x20), iVar2 == 0)) {
    return (undefined1 *)0x0;
  }
  puVar4 = (undefined4 *)(puVar1 + 0x34);
  *(undefined4 *)(puVar1 + 0x5c) = 0;
  *(undefined4 *)(puVar1 + 0x18) = 0;
  *(undefined4 *)(puVar1 + 4) = 0;
  *(undefined4 *)(puVar1 + 0x58) = 0;
  *(undefined2 *)(puVar1 + 0xc) = 0;
  *(undefined4 *)(puVar1 + 0x54) = 0;
  *puVar1 = 8;
  puVar1[1] = 0;
  puVar1[2] = 0;
  puVar1[3] = 0;
  *(undefined2 *)(puVar1 + 0xe) = 1;
  *(uint *)(puVar1 + 0x1c) = uVar6;
  puVar7 = puVar4;
  for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  *(undefined4 *)(puVar1 + 0x30) = 0;
  *(undefined4 *)(puVar1 + 0x2c) = 0;
  *(int *)(puVar1 + 0x10) = param_2;
  *(uint *)(puVar1 + 8) = param_3 & 0xf000000 | (byte)param_3 & 0x7b | uVar5;
  *(int *)(puVar1 + 0x14) = param_1;
  if (uStack_8 == 0) {
    puVar3 = puVar1 + _DAT_008d628c;
    if (((param_3 & 8) != 0) && (param_1 != 0)) {
      *(undefined1 **)(puVar1 + 0x30) = puVar3;
      puVar3 = puVar3 + param_1 * 4;
    }
    if (((uVar6 != 0) && (param_1 != 0)) && (uVar6 != 0)) {
      do {
        *puVar4 = puVar3;
        puVar3 = puVar3 + param_1 * 8;
        puVar4 = puVar4 + 1;
        uVar6 = uVar6 - 1;
      } while (uVar6 != 0);
    }
    if (param_2 != 0) {
      *(undefined1 **)(puVar1 + 0x2c) = puVar3;
      iVar2 = 0;
      if (0 < param_2) {
        do {
          iVar2 = iVar2 + 1;
          *(undefined2 *)(*(int *)(puVar1 + 0x2c) + -2 + iVar2 * 8) = 0xffff;
        } while (iVar2 < param_2);
      }
    }
  }
  iVar2 = func_0x0074c310(puVar1,1);
  if (iVar2 < 0) {
    func_0x0074e150(puVar1 + 0x20);
    (**(code **)(_DAT_00c97b24 + 0x138))(puVar1);
    return (undefined1 *)0x0;
  }
  func_0x008086e0(&DAT_008d628c,puVar1);
  return puVar1;
}



/* entry 0x0074C310; bounded CFG instructions=157; body bytes=443 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int BOUNDED_0074C310(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  int iVar6;
  int iVar7;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  if ((*(uint *)(param_1 + 8) & 0x1000000) == 0) {
    iVar7 = *(int *)(param_1 + 0x14) * 0xc;
    iVar6 = iVar7 + 0x1c;
    if ((*(uint *)(param_1 + 8) & 0x10) != 0) {
      iVar6 = iVar6 + iVar7;
    }
  }
  else {
    iVar6 = 0x1c;
  }
  iVar7 = (*(int *)(param_1 + 0x18) + param_2) * iVar6;
  if (*(int *)(param_1 + 0x5c) == 0) {
    iVar1 = (**(code **)(_DAT_00c97b24 + 0x134))(iVar7,0x3000f);
    if (iVar1 == 0) {
      uStack_8 = 2;
      uStack_4 = func_0x008088d0(0x80000013,iVar7);
      func_0x00808820(&uStack_8);
      return -1;
    }
  }
  else {
    iVar1 = (**(code **)(_DAT_00c97b24 + 0x13c))(*(int *)(param_1 + 0x5c));
    if (iVar1 == 0) {
      uStack_8 = 2;
      uStack_4 = func_0x008088d0(0x80000013,iVar7);
      func_0x00808820(&uStack_8);
      return -1;
    }
    puVar4 = (undefined1 *)(*(int *)(param_1 + 0x18) * iVar6 + -1 + iVar1);
    puVar5 = puVar4 + param_2 * 0x1c;
    for (iVar6 = (iVar6 + -0x1c) * *(int *)(param_1 + 0x18); iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar5 = *puVar4;
      puVar5 = puVar5 + -1;
      puVar4 = puVar4 + -1;
    }
  }
  iVar6 = *(int *)(param_1 + 0x18) + param_2;
  iVar7 = 0;
  *(int *)(param_1 + 0x18) = iVar6;
  *(int *)(param_1 + 0x5c) = iVar1;
  iVar1 = iVar1 + iVar6 * 0x1c;
  if (0 < iVar6) {
    iVar6 = 0;
    do {
      iVar2 = *(int *)(param_1 + 0x5c);
      *(undefined4 *)(iVar2 + 0x14 + iVar6) = 0;
      iVar2 = iVar2 + iVar6;
      *(undefined4 *)(iVar2 + 0x18) = 0;
      if (((*(uint *)(param_1 + 8) & 0x1000000) == 0) && (*(int *)(param_1 + 0x14) != 0)) {
        *(int *)(iVar2 + 0x14) = iVar1;
        iVar1 = iVar1 + *(int *)(param_1 + 0x14) * 0xc;
        if ((*(byte *)(param_1 + 8) & 0x10) != 0) {
          *(int *)(iVar2 + 0x18) = iVar1;
          iVar1 = iVar1 + *(int *)(param_1 + 0x14) * 0xc;
        }
      }
      iVar7 = iVar7 + 1;
      iVar6 = iVar6 + 0x1c;
    } while (iVar7 < *(int *)(param_1 + 0x18));
  }
  iVar6 = *(int *)(param_1 + 0x18) - param_2;
  if (iVar6 < *(int *)(param_1 + 0x18)) {
    iVar7 = iVar6 * 0x1c;
    do {
      iVar1 = *(int *)(param_1 + 0x5c);
      *(undefined4 *)(iVar1 + 4 + iVar7) = 0;
      piVar3 = (int *)(iVar1 + iVar7);
      iVar6 = iVar6 + 1;
      iVar7 = iVar7 + 0x1c;
      piVar3[2] = 0;
      piVar3[3] = 0;
      piVar3[4] = 0;
      *piVar3 = param_1;
    } while (iVar6 < *(int *)(param_1 + 0x18));
  }
  return *(int *)(param_1 + 0x18) - param_2;
}



/* entry 0x0074D190; bounded CFG instructions=442; body bytes=1332 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int BOUNDED_0074D190(uint param_1)

{
  undefined2 uVar1;
  uint uVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined2 *puVar8;
  int iVar9;
  undefined4 uVar10;
  int iStack_3c;
  undefined4 uStack_38;
  undefined1 auStack_34 [12];
  uint uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  int iStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  int iStack_8;
  int iStack_4;
  
  uVar2 = param_1;
  iVar4 = func_0x007ed2d0(param_1,1,0,&param_1);
  if (iVar4 == 0) {
    return 0;
  }
  if ((param_1 < 0x34000) || (0x36003 < param_1)) {
    iStack_3c = 2;
    uStack_38 = func_0x008088d0(0x80000004);
    goto LAB_0074d6ae;
  }
  if (param_1 < 0x34001) {
    iVar4 = func_0x007ec9d0(uVar2,&uStack_28,0x10);
    if (iVar4 != 0x10) {
      return 0;
    }
    iVar4 = func_0x007ec9d0(uVar2,auStack_34,0xc);
    if (iVar4 != 0xc) {
      return 0;
    }
  }
  else {
    iVar4 = func_0x007ec9d0(uVar2,&uStack_28,0x10);
    if (iVar4 != 0x10) {
      return 0;
    }
  }
  iVar4 = BOUNDED_0074CA90(uStack_20,uStack_24,uStack_28);
  if (iVar4 == 0) {
    return 0;
  }
  if ((1 < iStack_1c) && (iVar5 = BOUNDED_0074C310(iVar4,iStack_1c + -1), iVar5 < 0)) {
LAB_0074d522:
    sVar3 = *(short *)(iVar4 + 0xe);
    if (sVar3 == 1 || sVar3 + -1 < 0) {
      if (*(int *)(iVar4 + 0x58) != 0) {
        func_0x00807de0(*(int *)(iVar4 + 0x58));
      }
      *(undefined2 *)(iVar4 + 0xe) = *(undefined2 *)(iVar4 + 0xe);
      func_0x0074c7d0(iVar4,0xfff);
      func_0x00808740(&DAT_008d628c,iVar4);
      if (*(int *)(iVar4 + 0x5c) != 0) {
        (**(code **)(_DAT_00c97b24 + 0x138))(*(int *)(iVar4 + 0x5c));
        *(undefined4 *)(iVar4 + 0x5c) = 0;
      }
      func_0x0074e150(iVar4 + 0x20);
      *(short *)(iVar4 + 0xe) = *(short *)(iVar4 + 0xe) + -1;
      (**(code **)(_DAT_00c97b24 + 0x138))(iVar4);
      return 0;
    }
    goto LAB_0074d5e7;
  }
  if (((*(uint *)(iVar4 + 8) & 0x1000000) == 0) && (*(int *)(iVar4 + 0x14) != 0)) {
    if (((uStack_28 & 8) != 0) &&
       (iVar5 = *(int *)(iVar4 + 0x14) * 4,
       iVar6 = func_0x007ec9d0(uVar2,*(undefined4 *)(iVar4 + 0x30),iVar5), iVar6 != iVar5))
    goto LAB_0074d522;
    if (0 < *(int *)(iVar4 + 0x1c)) {
      iVar5 = 0;
      iStack_3c = *(int *)(iVar4 + 0x14) << 3;
      if (0 < *(int *)(iVar4 + 0x1c)) {
        puVar7 = (undefined4 *)(iVar4 + 0x34);
        do {
          iVar6 = func_0x007ed4f0(uVar2,*puVar7,iStack_3c);
          if (iVar6 == 0) goto LAB_0074d3ac;
          iVar5 = iVar5 + 1;
          puVar7 = puVar7 + 1;
        } while (iVar5 < *(int *)(iVar4 + 0x1c));
      }
    }
    iStack_3c = *(int *)(iVar4 + 0x10);
    if (iStack_3c != 0) {
      puVar8 = *(undefined2 **)(iVar4 + 0x2c);
      iVar5 = iStack_3c * 8;
      iVar6 = func_0x007ec9d0(uVar2,puVar8,iVar5);
      if (iVar6 != iVar5) {
LAB_0074d3ac:
        sVar3 = *(short *)(iVar4 + 0xe);
        if (sVar3 == 1 || sVar3 + -1 < 0) {
          if (*(int *)(iVar4 + 0x58) != 0) {
            func_0x00807de0(*(int *)(iVar4 + 0x58));
          }
          *(undefined2 *)(iVar4 + 0xe) = *(undefined2 *)(iVar4 + 0xe);
          func_0x0074c7d0(iVar4,0xfff);
          func_0x00808740(&DAT_008d628c,iVar4);
          if (*(int *)(iVar4 + 0x5c) != 0) {
            (**(code **)(_DAT_00c97b24 + 0x138))(*(int *)(iVar4 + 0x5c));
            *(undefined4 *)(iVar4 + 0x5c) = 0;
          }
          func_0x0074e150(iVar4 + 0x20);
          *(short *)(iVar4 + 0xe) = *(short *)(iVar4 + 0xe) + -1;
          (**(code **)(_DAT_00c97b24 + 0x138))(iVar4);
          return 0;
        }
        goto LAB_0074d5e7;
      }
      for (; iStack_3c != 0; iStack_3c = iStack_3c + -1) {
        uVar1 = *puVar8;
        *puVar8 = puVar8[1];
        puVar8[1] = uVar1;
        uVar1 = puVar8[2];
        puVar8[2] = puVar8[3];
        puVar8[3] = uVar1;
        puVar8 = puVar8 + 4;
      }
    }
  }
  iVar5 = 0;
  iStack_3c = 0;
  if (0 < *(int *)(iVar4 + 0x18)) {
    do {
      iVar9 = *(int *)(iVar4 + 0x5c) + iVar5;
      iVar6 = func_0x007ec9d0(uVar2,&uStack_18,0x18);
      if (iVar6 != 0x18) goto LAB_0074d522;
      *(undefined4 *)(iVar9 + 4) = uStack_18;
      *(undefined4 *)(iVar9 + 8) = uStack_14;
      *(undefined4 *)(iVar9 + 0xc) = uStack_10;
      *(undefined4 *)(iVar9 + 0x10) = uStack_c;
      if (iStack_8 == 0) {
LAB_0074d44d:
        if (iStack_4 != 0) {
          uVar10 = *(undefined4 *)(iVar9 + 0x18);
          iVar6 = *(int *)(iVar4 + 0x14) * 0xc;
          goto LAB_0074d463;
        }
      }
      else {
        if (iStack_4 == 0) {
          iVar6 = func_0x007ed4f0(uVar2,*(undefined4 *)(iVar9 + 0x14),*(int *)(iVar4 + 0x14) * 0xc);
          if (iVar6 != 0) goto LAB_0074d44d;
          goto LAB_0074d522;
        }
        uVar10 = *(undefined4 *)(iVar9 + 0x14);
        iVar6 = *(int *)(iVar4 + 0x14) * 0x18;
LAB_0074d463:
        iVar6 = func_0x007ed4f0(uVar2,uVar10,iVar6);
        if (iVar6 == 0) goto LAB_0074d522;
      }
      iStack_3c = iStack_3c + 1;
      iVar5 = iVar5 + 0x1c;
    } while (iStack_3c < *(int *)(iVar4 + 0x18));
  }
  iVar5 = func_0x007ed2d0(uVar2,8,0,&param_1);
  if (iVar5 == 0) {
    return 0;
  }
  if ((param_1 < 0x34000) || (0x36003 < param_1)) {
    sVar3 = *(short *)(iVar4 + 0xe);
    if (sVar3 == 1 || sVar3 + -1 < 0) {
      if (*(int *)(iVar4 + 0x58) != 0) {
        func_0x00807de0(*(int *)(iVar4 + 0x58));
      }
      *(undefined2 *)(iVar4 + 0xe) = *(undefined2 *)(iVar4 + 0xe);
      func_0x0074c7d0(iVar4,0xfff);
      func_0x00808740(&DAT_008d628c,iVar4);
      if (*(int *)(iVar4 + 0x5c) != 0) {
        (**(code **)(_DAT_00c97b24 + 0x138))(*(int *)(iVar4 + 0x5c));
        *(undefined4 *)(iVar4 + 0x5c) = 0;
      }
      func_0x0074e150(iVar4 + 0x20);
      *(short *)(iVar4 + 0xe) = *(short *)(iVar4 + 0xe) + -1;
      (**(code **)(_DAT_00c97b24 + 0x138))(iVar4);
    }
    else {
      *(short *)(iVar4 + 0xe) = sVar3 + -1;
    }
    iStack_3c = 2;
    uStack_38 = func_0x008088d0(0x80000004);
LAB_0074d6ae:
    func_0x00808820(&iStack_3c);
    return 0;
  }
  if (param_1 < 0x34001) {
    func_0x0074d870(auStack_34);
  }
  iVar5 = func_0x0074e600(uVar2,iVar4 + 0x20);
  if (iVar5 == 0) {
LAB_0074d5b4:
    sVar3 = *(short *)(iVar4 + 0xe);
  }
  else {
    if (param_1 < 0x34001) {
      func_0x0074d870(0);
    }
    iVar5 = func_0x00808980(&DAT_008d628c,uVar2,iVar4);
    if (iVar5 != 0) {
      iVar5 = func_0x0074c800(iVar4);
      if (iVar5 != 0) {
        return iVar4;
      }
      goto LAB_0074d5b4;
    }
    sVar3 = *(short *)(iVar4 + 0xe);
  }
  if (sVar3 == 1 || sVar3 + -1 < 0) {
    if (*(int *)(iVar4 + 0x58) != 0) {
      func_0x00807de0(*(int *)(iVar4 + 0x58));
    }
    *(short *)(iVar4 + 0xe) = *(short *)(iVar4 + 0xe) + -1;
    func_0x0074d6d0(iVar4);
    return 0;
  }
LAB_0074d5e7:
  *(short *)(iVar4 + 0xe) = sVar3 + -1;
  return 0;
}



/* entry 0x0074D6D0; bounded CFG instructions=34; body bytes=117 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 BOUNDED_0074D6D0(int param_1)

{
  *(short *)(param_1 + 0xe) = *(short *)(param_1 + 0xe) + 1;
  *(ushort *)(param_1 + 0xc) = *(ushort *)(param_1 + 0xc) | 0xfff;
  if (*(int *)(param_1 + 0x54) != 0) {
    func_0x00758bc0(*(int *)(param_1 + 0x54));
    *(undefined4 *)(param_1 + 0x54) = 0;
  }
  func_0x00808740(&DAT_008d628c,param_1);
  if (*(int *)(param_1 + 0x5c) != 0) {
    (**(code **)(_DAT_00c97b24 + 0x138))(*(int *)(param_1 + 0x5c));
    *(undefined4 *)(param_1 + 0x5c) = 0;
  }
  func_0x0074e150(param_1 + 0x20);
  *(short *)(param_1 + 0xe) = *(short *)(param_1 + 0xe) + -1;
  (**(code **)(_DAT_00c97b24 + 0x138))(param_1);
  return 1;
}


