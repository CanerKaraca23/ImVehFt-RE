/* Full-analysis function mapping; decompilation is not original source. */

/* function 00749c50 FUN_00749c50 */

/* WARNING: Removing unreachable block (ram,0x00749cd2) */

undefined1 * FUN_00749c50(void)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  
  puVar2 = (undefined1 *)
           (**(code **)(DAT_00c97b24 + 0x144))(*(undefined4 *)(DAT_00c924ac + DAT_00c97b24),0x30014)
  ;
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = 1;
    puVar2[1] = 0;
    *(undefined4 *)(puVar2 + 4) = 0;
    *(code **)(puVar2 + 0x10) = FUN_00749d20;
    *(undefined4 *)(puVar2 + 0x14) = 0;
    puVar2[2] = 5;
    puVar2[3] = 1;
    FUN_00804ef0(puVar2,0);
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
    *(code **)(puVar2 + 0x48) = FUN_007491c0;
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
    FUN_008086e0(&DAT_008d624c,puVar2);
    return puVar2;
  }
  return (undefined1 *)0x0;
}



/* function 0074c310 FUN_0074c310 */

int FUN_0074c310(int param_1,int param_2)

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
    iVar1 = (**(code **)(DAT_00c97b24 + 0x134))(iVar7,0x3000f);
    if (iVar1 == 0) {
      uStack_8 = 2;
      uStack_4 = FUN_008088d0(0x80000013,iVar7);
      FUN_00808820(&uStack_8);
      return -1;
    }
  }
  else {
    iVar1 = (**(code **)(DAT_00c97b24 + 0x13c))(*(int *)(param_1 + 0x5c));
    if (iVar1 == 0) {
      uStack_8 = 2;
      uStack_4 = FUN_008088d0(0x80000013,iVar7);
      FUN_00808820(&uStack_8);
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



/* function 0074ca90 FUN_0074ca90 */

undefined1 * FUN_0074ca90(int param_1,int param_2,uint param_3)

{
  undefined1 *puVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  uint uVar6;
  undefined4 *puVar7;
  uint local_8;
  undefined4 local_4;
  
  if (param_1 < 0) {
    return (undefined1 *)0x0;
  }
  if (0xffff < param_1) {
    local_8 = 2;
    local_4 = FUN_008088d0(6);
    FUN_00808820(&local_8);
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
  local_8 = param_3 & 0x1000000;
  iVar2 = DAT_008d628c;
  if (local_8 == 0) {
    if ((param_3 & 8) != 0) {
      iVar2 = DAT_008d628c + param_1 * 4;
    }
    if (uVar6 != 0) {
      iVar2 = iVar2 + uVar6 * param_1 * 8;
    }
    iVar2 = iVar2 + param_2 * 8;
  }
  puVar1 = (undefined1 *)(**(code **)(DAT_00c97b24 + 0x134))(iVar2,0x3000f);
  if ((puVar1 == (undefined1 *)0x0) || (iVar2 = FUN_0074e1b0(puVar1 + 0x20), iVar2 == 0)) {
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
  if (local_8 == 0) {
    puVar3 = puVar1 + DAT_008d628c;
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
  iVar2 = FUN_0074c310(puVar1,1);
  if (iVar2 < 0) {
    FUN_0074e150(puVar1 + 0x20);
    (**(code **)(DAT_00c97b24 + 0x138))(puVar1);
    return (undefined1 *)0x0;
  }
  FUN_008086e0(&DAT_008d628c,puVar1);
  return puVar1;
}



/* function 0074ccc0 FUN_0074ccc0 */

undefined4 FUN_0074ccc0(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 0xe);
  if (sVar1 == 1 || sVar1 + -1 < 0) {
    if (*(int *)(param_1 + 0x58) != 0) {
      FUN_00807de0(*(int *)(param_1 + 0x58));
    }
    *(ushort *)(param_1 + 0xc) = *(ushort *)(param_1 + 0xc) | 0xfff;
    *(undefined2 *)(param_1 + 0xe) = *(undefined2 *)(param_1 + 0xe);
    if (*(int *)(param_1 + 0x54) != 0) {
      FUN_00758bc0(*(int *)(param_1 + 0x54));
      *(undefined4 *)(param_1 + 0x54) = 0;
    }
    FUN_00808740(&DAT_008d628c,param_1);
    if (*(int *)(param_1 + 0x5c) != 0) {
      (**(code **)(DAT_00c97b24 + 0x138))(*(int *)(param_1 + 0x5c));
      *(undefined4 *)(param_1 + 0x5c) = 0;
    }
    FUN_0074e150(param_1 + 0x20);
    *(short *)(param_1 + 0xe) = *(short *)(param_1 + 0xe) + -1;
    (**(code **)(DAT_00c97b24 + 0x138))(param_1);
    return 1;
  }
  *(short *)(param_1 + 0xe) = sVar1 + -1;
  return 1;
}



/* function 0074d190 FUN_0074d190 */

int FUN_0074d190(uint param_1)

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
  int local_3c;
  undefined4 local_38;
  undefined1 local_34 [12];
  uint local_28;
  undefined4 local_24;
  undefined4 local_20;
  int local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  int local_4;
  
  uVar2 = param_1;
  iVar4 = FUN_007ed2d0(param_1,1,0,&param_1);
  if (iVar4 == 0) {
    return 0;
  }
  if ((param_1 < 0x34000) || (0x36003 < param_1)) {
    local_3c = 2;
    local_38 = FUN_008088d0(0x80000004);
    goto LAB_0074d6ae;
  }
  if (param_1 < 0x34001) {
    iVar4 = FUN_007ec9d0(uVar2,&local_28,0x10);
    if (iVar4 != 0x10) {
      return 0;
    }
    iVar4 = FUN_007ec9d0(uVar2,local_34,0xc);
    if (iVar4 != 0xc) {
      return 0;
    }
  }
  else {
    iVar4 = FUN_007ec9d0(uVar2,&local_28,0x10);
    if (iVar4 != 0x10) {
      return 0;
    }
  }
  iVar4 = FUN_0074ca90(local_20,local_24,local_28);
  if (iVar4 == 0) {
    return 0;
  }
  if ((1 < local_1c) && (iVar5 = FUN_0074c310(iVar4,local_1c + -1), iVar5 < 0)) {
LAB_0074d522:
    sVar3 = *(short *)(iVar4 + 0xe);
    if (sVar3 == 1 || sVar3 + -1 < 0) {
      if (*(int *)(iVar4 + 0x58) != 0) {
        FUN_00807de0(*(int *)(iVar4 + 0x58));
      }
      *(undefined2 *)(iVar4 + 0xe) = *(undefined2 *)(iVar4 + 0xe);
      FUN_0074c7d0(iVar4,0xfff);
      FUN_00808740(&DAT_008d628c,iVar4);
      if (*(int *)(iVar4 + 0x5c) != 0) {
        (**(code **)(DAT_00c97b24 + 0x138))(*(int *)(iVar4 + 0x5c));
        *(undefined4 *)(iVar4 + 0x5c) = 0;
      }
      FUN_0074e150(iVar4 + 0x20);
      *(short *)(iVar4 + 0xe) = *(short *)(iVar4 + 0xe) + -1;
      (**(code **)(DAT_00c97b24 + 0x138))(iVar4);
      return 0;
    }
    goto LAB_0074d5e7;
  }
  if (((*(uint *)(iVar4 + 8) & 0x1000000) == 0) && (*(int *)(iVar4 + 0x14) != 0)) {
    if (((local_28 & 8) != 0) &&
       (iVar5 = *(int *)(iVar4 + 0x14) * 4,
       iVar6 = FUN_007ec9d0(uVar2,*(undefined4 *)(iVar4 + 0x30),iVar5), iVar6 != iVar5))
    goto LAB_0074d522;
    if (0 < *(int *)(iVar4 + 0x1c)) {
      iVar5 = 0;
      local_3c = *(int *)(iVar4 + 0x14) << 3;
      if (0 < *(int *)(iVar4 + 0x1c)) {
        puVar7 = (undefined4 *)(iVar4 + 0x34);
        do {
          iVar6 = FUN_007ed4f0(uVar2,*puVar7,local_3c);
          if (iVar6 == 0) goto LAB_0074d3ac;
          iVar5 = iVar5 + 1;
          puVar7 = puVar7 + 1;
        } while (iVar5 < *(int *)(iVar4 + 0x1c));
      }
    }
    local_3c = *(int *)(iVar4 + 0x10);
    if (local_3c != 0) {
      puVar8 = *(undefined2 **)(iVar4 + 0x2c);
      iVar5 = local_3c * 8;
      iVar6 = FUN_007ec9d0(uVar2,puVar8,iVar5);
      if (iVar6 != iVar5) {
LAB_0074d3ac:
        sVar3 = *(short *)(iVar4 + 0xe);
        if (sVar3 == 1 || sVar3 + -1 < 0) {
          if (*(int *)(iVar4 + 0x58) != 0) {
            FUN_00807de0(*(int *)(iVar4 + 0x58));
          }
          *(undefined2 *)(iVar4 + 0xe) = *(undefined2 *)(iVar4 + 0xe);
          FUN_0074c7d0(iVar4,0xfff);
          FUN_00808740(&DAT_008d628c,iVar4);
          if (*(int *)(iVar4 + 0x5c) != 0) {
            (**(code **)(DAT_00c97b24 + 0x138))(*(int *)(iVar4 + 0x5c));
            *(undefined4 *)(iVar4 + 0x5c) = 0;
          }
          FUN_0074e150(iVar4 + 0x20);
          *(short *)(iVar4 + 0xe) = *(short *)(iVar4 + 0xe) + -1;
          (**(code **)(DAT_00c97b24 + 0x138))(iVar4);
          return 0;
        }
        goto LAB_0074d5e7;
      }
      for (; local_3c != 0; local_3c = local_3c + -1) {
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
  local_3c = 0;
  if (0 < *(int *)(iVar4 + 0x18)) {
    do {
      iVar9 = *(int *)(iVar4 + 0x5c) + iVar5;
      iVar6 = FUN_007ec9d0(uVar2,&local_18,0x18);
      if (iVar6 != 0x18) goto LAB_0074d522;
      *(undefined4 *)(iVar9 + 4) = local_18;
      *(undefined4 *)(iVar9 + 8) = local_14;
      *(undefined4 *)(iVar9 + 0xc) = local_10;
      *(undefined4 *)(iVar9 + 0x10) = local_c;
      if (local_8 == 0) {
LAB_0074d44d:
        if (local_4 != 0) {
          uVar10 = *(undefined4 *)(iVar9 + 0x18);
          iVar6 = *(int *)(iVar4 + 0x14) * 0xc;
          goto LAB_0074d463;
        }
      }
      else {
        if (local_4 == 0) {
          iVar6 = FUN_007ed4f0(uVar2,*(undefined4 *)(iVar9 + 0x14),*(int *)(iVar4 + 0x14) * 0xc);
          if (iVar6 != 0) goto LAB_0074d44d;
          goto LAB_0074d522;
        }
        uVar10 = *(undefined4 *)(iVar9 + 0x14);
        iVar6 = *(int *)(iVar4 + 0x14) * 0x18;
LAB_0074d463:
        iVar6 = FUN_007ed4f0(uVar2,uVar10,iVar6);
        if (iVar6 == 0) goto LAB_0074d522;
      }
      local_3c = local_3c + 1;
      iVar5 = iVar5 + 0x1c;
    } while (local_3c < *(int *)(iVar4 + 0x18));
  }
  iVar5 = FUN_007ed2d0(uVar2,8,0,&param_1);
  if (iVar5 == 0) {
    return 0;
  }
  if ((param_1 < 0x34000) || (0x36003 < param_1)) {
    sVar3 = *(short *)(iVar4 + 0xe);
    if (sVar3 == 1 || sVar3 + -1 < 0) {
      if (*(int *)(iVar4 + 0x58) != 0) {
        FUN_00807de0(*(int *)(iVar4 + 0x58));
      }
      *(undefined2 *)(iVar4 + 0xe) = *(undefined2 *)(iVar4 + 0xe);
      FUN_0074c7d0(iVar4,0xfff);
      FUN_00808740(&DAT_008d628c,iVar4);
      if (*(int *)(iVar4 + 0x5c) != 0) {
        (**(code **)(DAT_00c97b24 + 0x138))(*(int *)(iVar4 + 0x5c));
        *(undefined4 *)(iVar4 + 0x5c) = 0;
      }
      FUN_0074e150(iVar4 + 0x20);
      *(short *)(iVar4 + 0xe) = *(short *)(iVar4 + 0xe) + -1;
      (**(code **)(DAT_00c97b24 + 0x138))(iVar4);
    }
    else {
      *(short *)(iVar4 + 0xe) = sVar3 + -1;
    }
    local_3c = 2;
    local_38 = FUN_008088d0(0x80000004);
LAB_0074d6ae:
    FUN_00808820(&local_3c);
    return 0;
  }
  if (param_1 < 0x34001) {
    FUN_0074d870(local_34);
  }
  iVar5 = FUN_0074e600(uVar2,iVar4 + 0x20);
  if (iVar5 == 0) {
LAB_0074d5b4:
    sVar3 = *(short *)(iVar4 + 0xe);
  }
  else {
    if (param_1 < 0x34001) {
      FUN_0074d870(0);
    }
    iVar5 = FUN_00808980(&DAT_008d628c,uVar2,iVar4);
    if (iVar5 != 0) {
      iVar5 = FUN_0074c800(iVar4);
      if (iVar5 != 0) {
        return iVar4;
      }
      goto LAB_0074d5b4;
    }
    sVar3 = *(short *)(iVar4 + 0xe);
  }
  if (sVar3 == 1 || sVar3 + -1 < 0) {
    if (*(int *)(iVar4 + 0x58) != 0) {
      FUN_00807de0(*(int *)(iVar4 + 0x58));
    }
    *(short *)(iVar4 + 0xe) = *(short *)(iVar4 + 0xe) + -1;
    FUN_0074d6d0(iVar4);
    return 0;
  }
LAB_0074d5e7:
  *(short *)(iVar4 + 0xe) = sVar3 + -1;
  return 0;
}



/* function 0074d6d0 FUN_0074d6d0 */

undefined4 FUN_0074d6d0(int param_1)

{
  *(short *)(param_1 + 0xe) = *(short *)(param_1 + 0xe) + 1;
  *(ushort *)(param_1 + 0xc) = *(ushort *)(param_1 + 0xc) | 0xfff;
  if (*(int *)(param_1 + 0x54) != 0) {
    FUN_00758bc0(*(int *)(param_1 + 0x54));
    *(undefined4 *)(param_1 + 0x54) = 0;
  }
  FUN_00808740(&DAT_008d628c,param_1);
  if (*(int *)(param_1 + 0x5c) != 0) {
    (**(code **)(DAT_00c97b24 + 0x138))(*(int *)(param_1 + 0x5c));
    *(undefined4 *)(param_1 + 0x5c) = 0;
  }
  FUN_0074e150(param_1 + 0x20);
  *(short *)(param_1 + 0xe) = *(short *)(param_1 + 0xe) + -1;
  (**(code **)(DAT_00c97b24 + 0x138))(param_1);
  return 1;
}



/* function 0074f760 FUN_0074f760 */

undefined1 * FUN_0074f760(undefined4 *param_1)

{
  undefined1 *puVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  int *piVar8;
  int *piVar9;
  undefined4 uStack_108;
  undefined4 uStack_104;
  int aiStack_100 [64];
  
  puVar4 = (undefined1 *)(**(code **)(DAT_00c97b24 + 0x134))(DAT_008d62d0,0x3000b);
  if (puVar4 == (undefined1 *)0x0) {
    uStack_108 = 2;
    uStack_104 = FUN_008088d0(0x80000013,DAT_008d62d0);
    FUN_00808820(&uStack_108);
    return (undefined1 *)0x0;
  }
  *puVar4 = 7;
  puVar4[1] = 0;
  puVar4[2] = 0;
  puVar4[3] = 0;
  *(undefined4 *)(puVar4 + 4) = 0;
  FUN_0074e1b0(puVar4 + 0x10);
  *(undefined4 *)(puVar4 + 8) = 0;
  *(undefined4 *)(puVar4 + 0xc) = 2;
  puVar5 = (undefined4 *)(**(code **)(DAT_00c97b24 + 0x134))(DAT_008d736c,0x3000b);
  if (puVar5 == (undefined4 *)0x0) {
    uStack_108 = 2;
    uStack_104 = FUN_008088d0(0x80000013,4);
    FUN_00808820(&uStack_108);
    (**(code **)(DAT_00c97b24 + 0x138))(puVar4);
    return (undefined1 *)0x0;
  }
  puVar6 = puVar5 + 0xe;
  puVar5[0xf] = puVar6;
  *puVar6 = puVar6;
  puVar6 = puVar5 + 0x10;
  puVar5[0x11] = puVar6;
  *puVar5 = 0xffffffff;
  *puVar6 = puVar6;
  puVar5[0xd] = 0;
  puVar5[0x1e] = 0;
  *(undefined2 *)((int)puVar5 + 0x82) = 0;
  *(undefined2 *)(puVar5 + 0x21) = 0;
  puVar5[2] = 0;
  puVar5[1] = 0;
  puVar5[3] = 0;
  puVar6 = puVar5 + 4;
  for (iVar7 = 8; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  puVar5[0xc] = 0;
  puVar5[0x15] = param_1[3];
  puVar5[0x16] = param_1[4];
  puVar5[0x17] = param_1[5];
  puVar5[0x12] = *param_1;
  puVar5[0x13] = param_1[1];
  puVar5[0x14] = param_1[2];
  puVar5[0x1b] = param_1[3];
  puVar5[0x1c] = param_1[4];
  puVar5[0x1d] = param_1[5];
  puVar5[0x18] = *param_1;
  puVar5[0x19] = param_1[1];
  uVar3 = param_1[2];
  puVar5[0x1f] = 0;
  puVar5[0x1a] = uVar3;
  *(undefined4 **)(puVar4 + 0x1c) = puVar5;
  *(undefined4 *)(puVar4 + 0x20) = 0;
  *(undefined4 *)(puVar4 + 0x4c) = 0;
  *(undefined4 *)(puVar4 + 0x48) = 0;
  *(undefined4 *)(puVar4 + 0x44) = 0;
  *(undefined4 *)(puVar4 + 0x5c) = param_1[3];
  *(undefined4 *)(puVar4 + 0x60) = param_1[4];
  *(undefined4 *)(puVar4 + 100) = param_1[5];
  *(undefined4 *)(puVar4 + 0x50) = *param_1;
  *(undefined4 *)(puVar4 + 0x54) = param_1[1];
  uVar3 = param_1[2];
  *(undefined4 *)(puVar4 + 0x24) = 0;
  *(undefined4 *)(puVar4 + 0x58) = uVar3;
  puVar1 = puVar4 + 0x2c;
  *(undefined1 **)(puVar4 + 0x30) = puVar1;
  *(undefined1 **)(puVar4 + 0x28) = puVar1;
  *(undefined1 **)puVar1 = puVar1;
  puVar1 = puVar4 + 0x34;
  *(undefined1 **)(puVar4 + 0x38) = puVar1;
  *(undefined1 **)puVar1 = puVar1;
  puVar1 = puVar4 + 0x3c;
  *(undefined1 **)puVar1 = puVar1;
  *(undefined1 **)(puVar4 + 0x40) = puVar1;
  *(code **)(puVar4 + 0x68) = FUN_0074eec0;
  *(undefined4 *)(puVar4 + 0x6c) = 0;
  uVar3 = DAT_008d62d0;
  puVar6 = (undefined4 *)
           (**(code **)(DAT_00c97b24 + 0x144))(*(undefined4 *)(DAT_00c9254c + DAT_00c97b24),0x40507)
  ;
  if (puVar6 != (undefined4 *)0x0) {
    *puVar6 = puVar4;
    puVar6[1] = uVar3;
    puVar2 = puVar6 + 2;
    *puVar2 = *(undefined4 *)(DAT_00c9254c + 4 + DAT_00c97b24);
    puVar6[3] = DAT_00c9254c + 4 + DAT_00c97b24;
    *(undefined4 **)(*(int *)(DAT_00c9254c + 4 + DAT_00c97b24) + 4) = puVar2;
    *(undefined4 **)(DAT_00c9254c + 4 + DAT_00c97b24) = puVar2;
  }
  FUN_008086e0(&DAT_008d62d0,puVar4);
  FUN_008086e0(&DAT_008d736c,puVar5);
  iVar7 = FUN_0074f210(puVar4);
  if (iVar7 != 0) {
    return puVar4;
  }
  piVar8 = *(int **)(DAT_00c9254c + 4 + DAT_00c97b24);
  do {
    if (piVar8 == (int *)(DAT_00c9254c + 4 + DAT_00c97b24)) {
LAB_0074fa36:
      iVar7 = 0;
      piVar8 = *(int **)(puVar4 + 0x1c);
      if (*(int **)(puVar4 + 0x1c) != (int *)0x0) {
        do {
          if (*piVar8 < 0) {
            if (piVar8[0x1e] != 0) {
              FUN_00758bc0(piVar8[0x1e]);
              piVar8[0x1e] = 0;
            }
            piVar9 = (int *)aiStack_100[iVar7];
            iVar7 = iVar7 + -1;
          }
          else {
            piVar9 = (int *)piVar8[2];
            iVar7 = iVar7 + 1;
            aiStack_100[iVar7] = piVar8[3];
          }
          piVar8 = piVar9;
        } while (-1 < iVar7);
      }
      FUN_0074e150(puVar4 + 0x10);
      iVar7 = *(int *)(puVar4 + 0x1c);
      if ((puVar4[3] & 1) != 0) {
        if (iVar7 != 0) {
          FUN_0074eca0(iVar7);
        }
        FUN_00808740(&DAT_008d62d0,puVar4);
        (**(code **)(DAT_00c97b24 + 0x138))(puVar4);
        return (undefined1 *)0x0;
      }
      if (iVar7 != 0) {
        FUN_0074ed50(iVar7);
      }
      FUN_00808740(&DAT_008d62d0,puVar4);
      (**(code **)(DAT_00c97b24 + 0x138))(puVar4);
      return (undefined1 *)0x0;
    }
    if ((undefined1 *)piVar8[-2] == puVar4) {
      *(int *)piVar8[1] = *piVar8;
      *(int *)(*piVar8 + 4) = piVar8[1];
      (**(code **)(DAT_00c97b24 + 0x148))(*(undefined4 *)(DAT_00c9254c + DAT_00c97b24),piVar8 + -2);
      goto LAB_0074fa36;
    }
    piVar8 = (int *)*piVar8;
  } while( true );
}



/* function 0075e310 FUN_0075e310 */

undefined4 FUN_0075e310(void)

{
  int iVar1;
  
  *(undefined4 *)(DAT_00c9bc60 + 0x3c + DAT_00c97b24) = 0;
  *(undefined4 *)(DAT_00c9bc60 + 0x40 + DAT_00c97b24) = 0;
  *(undefined4 *)(DAT_00c9bc60 + 0x44 + DAT_00c97b24) = 0;
  *(undefined4 *)(DAT_00c9bc60 + 0x48 + DAT_00c97b24) = 0;
  *(undefined4 *)(DAT_00c9bc60 + 0x4c + DAT_00c97b24) = 0;
  *(undefined4 *)(DAT_00c9bc60 + 0x50 + DAT_00c97b24) = 0;
  *(undefined4 *)(DAT_00c9bc60 + 0x54 + DAT_00c97b24) = 0;
  *(undefined4 *)(DAT_00c9bc60 + 0x58 + DAT_00c97b24) = 0;
  *(undefined4 *)(DAT_00c9bc60 + 0x5c + DAT_00c97b24) = 0;
  iVar1 = FUN_0074eab0();
  if (iVar1 != 0) {
    iVar1 = FUN_0074eb80();
    if (iVar1 != 0) {
      iVar1 = FUN_0074ead0();
      if (iVar1 != 0) {
        return 1;
      }
    }
  }
  FUN_0074eb40();
  FUN_0074ec00();
  FUN_0074eac0();
  return 0;
}


