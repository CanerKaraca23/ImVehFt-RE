/* Full-analysis function mapping; decompilation is not original source. */

/* function 004f55c0 FUN_004f55c0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004f55c0(int param_1,short param_2)

{
  int iVar1;
  undefined2 uVar2;
  short sVar3;
  
  iVar1 = *(int *)(param_1 + 0xe8 + param_2 * 8);
  sVar3 = -1;
  if (iVar1 != 0) {
    sVar3 = *(short *)(iVar1 + 0x70);
  }
  if ((-1 < param_2) && (param_2 < 0xc)) {
    if (iVar1 != 0) {
      FUN_004ef2b0(4,0);
      FUN_004ef1c0();
      *(undefined4 *)(param_1 + 0xe8 + param_2 * 8) = 0;
    }
    if (param_2 == 4) {
      *(undefined2 *)(param_1 + 0x154) = *(undefined2 *)(param_1 + 0x148);
      *(undefined4 *)(param_1 + 0x150) = DAT_00b7cb84;
      *(undefined2 *)(param_1 + 0x148) = 0xffff;
      *(undefined2 *)(param_1 + 0x14a) = 0xffff;
      if (0 < sVar3) {
        uVar2 = FUN_00821b40();
        *(undefined2 *)(param_1 + 0x14e) = uVar2;
        return;
      }
      *(undefined2 *)(param_1 + 0x14e) = 0;
    }
  }
  return;
}



/* function 004f5700 FUN_004f5700 */

void __fastcall FUN_004f5700(int param_1)

{
  char cVar1;
  short sVar2;
  undefined2 uVar3;
  int iVar4;
  
  *(undefined1 *)(param_1 + 0xa7) = 0;
  DAT_00b6b990 = *(undefined4 *)(*(int *)(param_1 + 4) + 0x460);
  cVar1 = *(char *)(param_1 + 0x80);
  if ((cVar1 == '\0') || (cVar1 == '\x01')) {
    *(undefined1 *)(param_1 + 0xaa) = 0;
    *(undefined4 *)(param_1 + 0xac) = 0;
    *(undefined2 *)(param_1 + 0x148) = 0xffff;
    *(undefined2 *)(param_1 + 0x14a) = 0xffff;
    *(float *)(param_1 + 0xd8) = (float)(int)*(char *)(DAT_00bd00f8 + 0x4d);
    sVar2 = FUN_004ef520(0x28);
    if (sVar2 != 0) {
      FUN_004efc60(0x28,0);
    }
    if (*(short *)(param_1 + 0xdc) == -1) {
      return;
    }
    if (*(short *)(param_1 + 0xde) == -1) {
      return;
    }
    if (*(short *)(param_1 + 0xe0) == -1) {
      uVar3 = FUN_004f4e60(*(short *)(param_1 + 0xdc));
      *(undefined2 *)(param_1 + 0xe0) = uVar3;
    }
    cVar1 = FUN_004d88c0(*(undefined2 *)(param_1 + 0xde),0x28);
    if (cVar1 == '\0') {
      FUN_004d88a0(*(undefined2 *)(param_1 + 0xde),0x28);
    }
    if ((*(char *)(param_1 + 0xa9) == '\x01') && (*(short *)(param_1 + 0xe0) != -1)) {
      iVar4 = 0;
      do {
        if ((short)iVar4 != 2) {
          FUN_004f55c0(iVar4);
        }
        iVar4 = iVar4 + 1;
      } while ((short)iVar4 < 0xc);
      *(undefined1 *)(param_1 + 0xa9) = 6;
      return;
    }
    iVar4 = 0;
    do {
      FUN_004f55c0(iVar4);
      iVar4 = iVar4 + 1;
    } while ((short)iVar4 < 0xc);
    *(undefined1 *)(param_1 + 0xa9) = 0;
    return;
  }
  if (((cVar1 == '\x05') || (cVar1 == '\x04')) || (cVar1 == '\x06')) {
    iVar4 = 0;
    do {
      FUN_004f55c0(iVar4);
      iVar4 = iVar4 + 1;
    } while ((short)iVar4 < 0xc);
    if ((*(short *)(param_1 + 0xde) != -1) &&
       (cVar1 = FUN_004d88c0(*(short *)(param_1 + 0xde),0x28), cVar1 == '\0')) {
      sVar2 = FUN_004ef520(0x28);
      if (sVar2 != 0) {
        FUN_004efc60(0x28,0);
      }
      FUN_004d88a0(*(undefined2 *)(param_1 + 0xde),0x28);
    }
    if ((*(short *)(param_1 + 0xdc) != -1) && (*(short *)(param_1 + 0xe0) == -1)) {
      uVar3 = FUN_004f4e60(*(short *)(param_1 + 0xdc));
      *(undefined2 *)(param_1 + 0xe0) = uVar3;
    }
    *(undefined4 *)(param_1 + 0x22c) = 0xbf800000;
    *(undefined4 *)(param_1 + 0x230) = 0xc2c80000;
    return;
  }
  if (cVar1 == '\x02') {
    *(float *)(param_1 + 0xd8) = (float)(int)*(char *)(DAT_00bd00f8 + 0x4d);
    sVar2 = FUN_004ef520(0x28);
    if (sVar2 != 0) {
      FUN_004efc60(0x28,0);
    }
    iVar4 = 0;
    do {
      FUN_004f55c0(iVar4);
      iVar4 = iVar4 + 1;
    } while ((short)iVar4 < 0xc);
    if (*(short *)(param_1 + 0xe0) != -1) goto LAB_004f57c2;
    sVar2 = *(short *)(param_1 + 0xdc);
  }
  else {
    if (cVar1 == '\x03') {
      *(float *)(param_1 + 0xd8) = (float)(int)*(char *)(DAT_00bd00f8 + 0x4d);
      if (*(short *)(param_1 + 0xe0) != -1) {
        return;
      }
      uVar3 = FUN_004f4e60(*(undefined2 *)(param_1 + 0xdc));
      *(undefined2 *)(param_1 + 0xe0) = uVar3;
      return;
    }
    if (cVar1 == '\b') {
      *(float *)(param_1 + 0xd8) = (float)(int)*(char *)(DAT_00bd00f8 + 0x4d);
      sVar2 = FUN_004ef520(0x28);
      if (sVar2 != 0) {
        FUN_004efc60(0x28,0);
      }
      if (*(short *)(param_1 + 0xe0) == -1) {
        uVar3 = FUN_004f4e60(*(undefined2 *)(param_1 + 0xdc));
        *(undefined2 *)(param_1 + 0xe0) = uVar3;
      }
      cVar1 = FUN_004d88c0(*(undefined2 *)(param_1 + 0xde),0x28);
      if (cVar1 != '\0') {
        return;
      }
      FUN_004d88a0(*(undefined2 *)(param_1 + 0xde),0x28);
      return;
    }
    if (cVar1 != '\t') {
      return;
    }
    *(float *)(param_1 + 0xd8) = (float)(int)*(char *)(DAT_00bd00f8 + 0x4d);
    sVar2 = FUN_004ef520(0x28);
    if (sVar2 != 0) {
      FUN_004efc60(0x28,0);
    }
    iVar4 = 0;
    do {
      FUN_004f55c0(iVar4);
      iVar4 = iVar4 + 1;
    } while ((short)iVar4 < 0xc);
    if ((*(short *)(param_1 + 0xe0) != -1) || (sVar2 = *(short *)(param_1 + 0xdc), sVar2 == -1))
    goto LAB_004f57c2;
  }
  uVar3 = FUN_004f4e60(sVar2);
  *(undefined2 *)(param_1 + 0xe0) = uVar3;
LAB_004f57c2:
  cVar1 = FUN_004d88c0(*(undefined2 *)(param_1 + 0xde),0x28);
  if (cVar1 != '\0') {
    return;
  }
  FUN_004d88a0(*(undefined2 *)(param_1 + 0xde),0x28);
  return;
}



/* function 004f7670 FUN_004f7670 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004f7670(int param_1,int param_2)

{
  byte bVar1;
  float fVar2;
  undefined1 uVar3;
  short sVar4;
  undefined2 uVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined **ppuVar8;
  bool bVar9;
  
  *(undefined4 *)(param_1 + 0x144) = 0;
  *(int *)(param_1 + 4) = param_2;
  *(undefined1 *)(param_1 + 0xa5) = 0;
  *(undefined1 *)(param_1 + 0xa6) = 0;
  *(undefined1 *)(param_1 + 0xa7) = 0;
  *(undefined1 *)(param_1 + 0xa8) = 0;
  *(undefined1 *)(param_1 + 0xa9) = 0;
  *(undefined1 *)(param_1 + 0xaa) = 0;
  *(undefined4 *)(param_1 + 0xac) = 0;
  *(undefined2 *)(param_1 + 0xe0) = 0xffff;
  *(undefined2 *)(param_1 + 0xb2) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  *(undefined2 *)(param_1 + 0xb4) = 0;
  *(undefined4 *)(param_1 + 0xb8) = 0;
  *(undefined1 *)(param_1 + 0xbc) = 0;
  *(undefined4 *)(param_1 + 0xcc) = 0;
  *(undefined4 *)(param_1 + 0xd0) = 0;
  *(undefined4 *)(param_1 + 0xd4) = 0;
  *(undefined1 *)(param_1 + 0x244) = 0;
  *(undefined1 *)(param_1 + 0xbd) = 0;
  *(undefined2 *)(param_1 + 0x148) = 0xffff;
  *(undefined2 *)(param_1 + 0x14a) = 0xffff;
  *(undefined2 *)(param_1 + 0x154) = 0;
  *(undefined2 *)(param_1 + 0x14e) = 0;
  *(undefined2 *)(param_1 + 0x14c) = 0;
  sVar4 = 0;
  puVar6 = (undefined4 *)(param_1 + 0xe8);
  do {
    *(short *)(puVar6 + -1) = sVar4;
    *puVar6 = 0;
    sVar4 = sVar4 + 1;
    puVar6 = puVar6 + 2;
  } while (sVar4 < 0xc);
  *(undefined4 *)(param_1 + 0xc4) = 0xc2c80000;
  *(undefined4 *)(param_1 + 0x230) = 0xc2c80000;
  *(undefined2 *)(param_1 + 0x156) = 0xffff;
  *(undefined2 *)(param_1 + 0x15c) = 0xffff;
  *(undefined2 *)(param_1 + 0x164) = 0xffff;
  *(undefined2 *)(param_1 + 0x16c) = 0xffff;
  *(undefined4 *)(param_1 + 0x234) = 0xbf800000;
  *(undefined4 *)(param_1 + 0x22c) = 0xbf800000;
  *(undefined4 *)(param_1 + 0x248) = 0xbf800000;
  *(undefined4 *)(param_1 + 0x158) = 0;
  *(undefined4 *)(param_1 + 0x160) = 0;
  *(undefined4 *)(param_1 + 0x168) = 0;
  *(undefined4 *)(param_1 + 0x170) = 0;
  *(undefined4 *)(param_1 + 0x178) = 0;
  *(undefined4 *)(param_1 + 0x17c) = 0;
  *(undefined4 *)(param_1 + 0x180) = 0;
  *(undefined4 *)(param_1 + 0x238) = 0;
  *(undefined4 *)(param_1 + 0x23c) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x240) = 0;
  ppuVar8 = &PTR_LAB_00860af0 + (*(short *)(param_2 + 0x22) + -400) * 9;
  puVar6 = (undefined4 *)(param_1 + 0x80);
  for (iVar7 = 9; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar6 = *ppuVar8;
    ppuVar8 = ppuVar8 + 1;
    puVar6 = puVar6 + 1;
  }
  uVar3 = FUN_006d8470();
  *(undefined1 *)(param_1 + 200) = uVar3;
  if (*(char *)(param_1 + 0x9b) == '\x02') {
    *(undefined1 *)(param_1 + 0x9a) = 0xd;
  }
  *(float *)(param_1 + 0xd8) = (float)(int)*(char *)(DAT_00bd00f8 + 0x4d);
  switch(*(undefined2 *)(param_2 + 0x22)) {
  case 0x1c0:
  case 0x1c9:
  case 0x1ce:
  case 0x1e5:
  case 0x212:
  case 0x21b:
  case 0x23b:
  case 0x23c:
  case 0x23e:
  case 0x247:
    *(undefined1 *)(param_1 + 0xb0) = 1;
    break;
  default:
    *(undefined1 *)(param_1 + 0xb0) = 0;
  }
  bVar1 = *(byte *)(param_1 + 0x80);
  if (9 < bVar1) {
    return;
  }
  switch(bVar1) {
  case 0:
    fVar2 = *(float *)(param_1 + 0xd8) - _DAT_008cbd50;
    *(undefined2 *)(param_1 + 0xde) = *(undefined2 *)(param_1 + 0x82);
    *(float *)(param_1 + 0xd8) = fVar2;
    break;
  case 1:
    *(undefined2 *)(param_1 + 0xde) = *(undefined2 *)(param_1 + 0x82);
    goto LAB_004f7942;
  case 2:
    *(undefined2 *)(param_1 + 0xde) = *(undefined2 *)(param_1 + 0x82);
    goto LAB_004f7954;
  default:
    *(undefined2 *)(param_1 + 0xde) = *(undefined2 *)(param_1 + 0x82);
    break;
  case 4:
  case 6:
    *(undefined2 *)(param_1 + 0xdc) = *(undefined2 *)(param_1 + 0x84);
    *(undefined2 *)(param_1 + 0xde) = *(undefined2 *)(param_1 + 0x82);
    *(undefined1 *)(param_1 + 0xa4) = 1;
    return;
  case 5:
    sVar4 = *(short *)(param_1 + 0x84);
    *(short *)(param_1 + 0xdc) = sVar4;
    *(undefined2 *)(param_1 + 0xde) = *(undefined2 *)(param_1 + 0x82);
    if ((sVar4 != -1) && (*(char *)(param_1 + 0xa4) == '\0')) goto LAB_004f7970;
    goto LAB_004f7980;
  case 7:
    goto switchD_004f7851_caseD_7;
  case 9:
    *(undefined2 *)(param_1 + 0xde) = *(undefined2 *)(param_1 + 0x82);
LAB_004f7942:
    *(float *)(param_1 + 0xd8) = *(float *)(param_1 + 0xd8) - _DAT_008cbd50;
LAB_004f7954:
    sVar4 = *(short *)(param_1 + 0x84);
    *(short *)(param_1 + 0xdc) = sVar4;
    if (*(char *)(param_1 + 0xa4) == '\0') {
      bVar9 = sVar4 == -1;
      goto LAB_004f796e;
    }
    goto LAB_004f7980;
  }
  sVar4 = *(short *)(param_1 + 0x84);
  *(short *)(param_1 + 0xdc) = sVar4;
  if ((*(char *)(param_1 + 0xa4) == '\0') && (sVar4 != -1)) {
    bVar9 = sVar4 == 0x81;
LAB_004f796e:
    if (!bVar9) {
LAB_004f7970:
      uVar5 = FUN_004f4d10(CONCAT22((char)bVar1 >> 7,sVar4));
      *(undefined2 *)(param_1 + 0xe0) = uVar5;
    }
  }
LAB_004f7980:
  *(undefined1 *)(param_1 + 0xa4) = 1;
switchD_004f7851_caseD_7:
  return;
}



/* function 004fca10 FUN_004fca10 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004fca10(int param_1,short param_2,undefined4 param_3,int param_4)

{
  byte *pbVar1;
  float fVar2;
  char cVar3;
  int iVar4;
  float fVar5;
  float10 fVar6;
  float10 fVar7;
  
  *(undefined4 *)(param_1 + 0x144) = DAT_00b7cb84;
  fVar5 = _DAT_008cbbec;
  fVar2 = _DAT_008cbbe4;
  cVar3 = *(char *)(param_1 + 0xa9);
  if (cVar3 == '\x01') {
    if (param_2 == 1) {
      *(undefined1 *)(param_1 + 0xa9) = 1;
      fVar2 = fVar2 + *(float *)(param_1 + 0x23c);
      if (_DAT_00858624 <= fVar2) {
        fVar2 = _DAT_00858624;
      }
      *(float *)(param_1 + 0x23c) = fVar2;
      fVar6 = (float10)FUN_004f51f0(param_3,fVar2);
      fVar7 = (float10)FUN_004f5310(param_3,*(undefined4 *)(param_1 + 0x23c));
      fVar2 = *(float *)(param_1 + 0xd8);
      iVar4 = *(int *)(param_1 + 0xf8);
      if (iVar4 != 0) {
        *(float *)(iVar4 + 0x1c) = (float)fVar7;
        *(float *)(iVar4 + 0x14) = (float)fVar6 + fVar2;
      }
      fVar2 = _DAT_008cbbe8 + *(float *)(param_1 + 0x240);
      if (_DAT_00858624 <= fVar2) {
        fVar2 = _DAT_00858624;
      }
      *(float *)(param_1 + 0x240) = fVar2;
      if (fVar2 < (float)_DAT_00862cd8) {
        fVar6 = (float10)FUN_004f53d0(param_3,fVar2);
        fVar7 = (float10)FUN_004f54f0(param_3,*(undefined4 *)(param_1 + 0x240));
        fVar2 = *(float *)(param_1 + 0xd8);
        iVar4 = *(int *)(param_1 + 0xf0);
        if (iVar4 == 0) {
          return;
        }
        *(float *)(iVar4 + 0x1c) = (float)fVar7;
        *(float *)(iVar4 + 0x14) = (float)fVar6 + fVar2;
        return;
      }
    }
    else {
      if (param_2 == 2) {
        *(undefined1 *)(param_1 + 0xa9) = 2;
        *(undefined4 *)(param_1 + 0x240) = 0;
        fVar6 = (float10)FUN_004f51f0(param_3,0);
        fVar7 = (float10)FUN_004f5310(param_3,*(undefined4 *)(param_1 + 0x240));
        fVar2 = *(float *)(param_1 + 0xd8);
        iVar4 = *(int *)(param_1 + 0xf8);
        if (iVar4 != 0) {
          *(float *)(iVar4 + 0x1c) = (float)fVar7;
          *(float *)(iVar4 + 0x14) = (float)fVar6 + fVar2;
        }
        *(undefined4 *)(param_1 + 0x23c) = 0;
        fVar6 = (float10)FUN_004f53d0(param_3,0);
        fVar7 = (float10)FUN_004f54f0(param_3,*(undefined4 *)(param_1 + 0x23c));
        FUN_004f7f20(1,(float)fVar7,(float)fVar6);
        return;
      }
      *(undefined1 *)(param_1 + 0xa9) = 0;
      if (*(int *)(param_1 + 0xf8) != 0) {
        FUN_004ef2b0(4,0);
        FUN_004ef1c0();
        *(undefined4 *)(param_1 + 0xf8) = 0;
      }
    }
    if (*(int *)(param_1 + 0xf0) != 0) {
      FUN_004ef2b0(4,0);
      FUN_004ef1c0();
      *(undefined4 *)(param_1 + 0xf0) = 0;
      return;
    }
  }
  else {
    if (cVar3 != '\x02') {
      if ((cVar3 == '\0') || (cVar3 == '\n')) {
        if (param_2 == 1) {
          if (cVar3 == '\0') {
            FUN_004f6420(0x67,0);
          }
          *(undefined1 *)(param_1 + 0xa9) = 1;
          *(undefined4 *)(param_1 + 0x240) = 0x3f800000;
          *(undefined4 *)(param_1 + 0x23c) = 0x3f800000;
          fVar6 = (float10)FUN_004f51f0(param_3,0x3f800000);
          fVar7 = (float10)FUN_004f5310(param_3,0x3f800000);
          FUN_004f7f20(2,(float)fVar7,(float)fVar6);
          return;
        }
        if (param_2 == 2) {
          if (cVar3 == '\0') {
            FUN_004f6420(0x67,0);
          }
          *(undefined1 *)(param_1 + 0xa9) = 2;
          *(undefined4 *)(param_1 + 0x240) = 0x3f800000;
          *(undefined4 *)(param_1 + 0x23c) = 0x3f800000;
          fVar6 = (float10)FUN_004f53d0(param_3,0x3f800000);
          fVar7 = (float10)FUN_004f54f0(param_3,0x3f800000);
          FUN_004f7f20(1,(float)fVar7,(float)fVar6);
          return;
        }
      }
      *(undefined1 *)(param_1 + 0xa9) = 0;
      return;
    }
    if (param_2 == 1) {
      *(undefined1 *)(param_1 + 0xa9) = 1;
      *(undefined4 *)(param_1 + 0x240) = 0;
      fVar6 = (float10)FUN_004f53d0(param_3,0);
      fVar7 = (float10)FUN_004f54f0(param_3,*(undefined4 *)(param_1 + 0x240));
      fVar2 = *(float *)(param_1 + 0xd8);
      iVar4 = *(int *)(param_1 + 0xf0);
      if (iVar4 != 0) {
        *(float *)(iVar4 + 0x1c) = (float)fVar7;
        *(float *)(iVar4 + 0x14) = (float)fVar6 + fVar2;
      }
      *(undefined4 *)(param_1 + 0x23c) = 0;
      fVar6 = (float10)FUN_004f51f0(param_3,0);
      fVar7 = (float10)FUN_004f5310(param_3,*(undefined4 *)(param_1 + 0x23c));
      FUN_004f7f20(2,(float)fVar7,(float)fVar6);
      return;
    }
    if (param_2 == 2) {
      *(undefined1 *)(param_1 + 0xa9) = 2;
      fVar5 = fVar5 + *(float *)(param_1 + 0x23c);
      if (_DAT_00858624 <= fVar5) {
        fVar5 = _DAT_00858624;
      }
      *(float *)(param_1 + 0x23c) = fVar5;
      fVar6 = (float10)FUN_004f53d0(param_3,fVar5);
      fVar7 = (float10)FUN_004f54f0(param_3,*(undefined4 *)(param_1 + 0x23c));
      FUN_004f56d0(1,(float)fVar7,(float)fVar6);
      fVar2 = _DAT_008cbbe0 + *(float *)(param_1 + 0x240);
      if (_DAT_00858624 <= fVar2) {
        fVar2 = _DAT_00858624;
      }
      fVar5 = (float)_DAT_00862cd8;
      *(float *)(param_1 + 0x240) = fVar2;
      if (fVar2 < fVar5) {
        if (((float)_DAT_00862d30 < fVar2) && (fVar2 < (float)_DAT_00862cf8)) {
          pbVar1 = (byte *)(*(int *)(param_4 + 0x10) + 0x42b);
          *pbVar1 = *pbVar1 | 0x20;
        }
        fVar6 = (float10)FUN_004f51f0(param_3,*(undefined4 *)(param_1 + 0x240));
        fVar7 = (float10)FUN_004f5310(param_3,*(undefined4 *)(param_1 + 0x240));
        FUN_004f56d0(2,(float)fVar7,(float)fVar6);
        return;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0xa9) = 0;
      if (*(int *)(param_1 + 0xf0) != 0) {
        FUN_004ef2b0(4,0);
        FUN_004ef1c0();
        *(undefined4 *)(param_1 + 0xf0) = 0;
      }
    }
    if (*(int *)(param_1 + 0xf8) != 0) {
      FUN_004ef2b0(4,0);
      FUN_004ef1c0();
      *(undefined4 *)(param_1 + 0xf8) = 0;
      return;
    }
  }
  return;
}



/* function 0050b890 FUN_0050b890 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0050b890(int param_1)

{
  float fVar1;
  
  if (*(char *)(param_1 + 0x3c) == '\0') {
    fVar1 = *(float *)((uint)*(byte *)(param_1 + 0x59) * 0x238 + 0x228 + param_1);
    *(undefined4 *)(param_1 + 0x16c) = 0x3f800000;
    fVar1 = fVar1 * _DAT_00858c24;
    *(undefined4 *)(param_1 + 0x144) = 0x41f00000;
    *(float *)(param_1 + 0x134) = fVar1;
    return;
  }
  *(undefined1 *)(param_1 + 0x3c) = 0;
  *(undefined1 *)(param_1 + 0x3d) = 0;
  *(undefined4 *)(param_1 + 0x144) = 0;
  *(undefined4 *)(param_1 + 0x134) = 0;
  *(undefined4 *)(param_1 + 0x16c) = 0;
  return;
}



/* function 005428c0 FUN_005428c0 */

void __thiscall
FUN_005428c0(int param_1,float param_2,int param_3,undefined4 *param_4,float param_5)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  byte bVar4;
  
  if (*(float *)(param_1 + 0xd8) < param_2) {
    bVar4 = *(byte *)((int)param_4 + 0x21);
    piVar1 = (int *)(param_1 + 0xdc);
    *(float *)(param_1 + 0xd8) = param_2;
    *(ushort *)(param_1 + 0xf8) = (ushort)bVar4;
    if (*piVar1 != 0) {
      FUN_00571a00(piVar1);
    }
    *piVar1 = param_3;
    FUN_00571b70(piVar1);
    *(undefined4 *)(param_1 + 0xec) = *param_4;
    *(undefined4 *)(param_1 + 0xf0) = param_4[1];
    *(undefined4 *)(param_1 + 0xf4) = param_4[2];
    fVar2 = (float)param_4[5];
    fVar3 = (float)param_4[6];
    *(float *)(param_1 + 0xe0) = param_5 * (float)param_4[4];
    *(float *)(param_1 + 0xe4) = param_5 * fVar2;
    *(float *)(param_1 + 0xe8) = param_5 * fVar3;
    if (((*(byte *)(param_1 + 0x36) & 7) == 4) && (*(char *)((int)param_4 + 0x23) == 'A')) {
      *(uint *)(param_1 + 0x140) = *(uint *)(param_1 + 0x140) | 0x80000;
    }
    else if (((*(byte *)(param_3 + 0x36) & 7) == 4) && (*(char *)(param_4 + 8) == 'A')) {
      *(uint *)(param_3 + 0x140) = *(uint *)(param_3 + 0x140) | 0x80000;
    }
  }
  if (((*(char *)(param_1 + 0x40) < '\0') && ((int)*(short *)(param_3 + 0x22) == (uint)DAT_008cd778)
      ) && ((*(byte *)(param_1 + 0x36) & 7) == 4)) {
    *(byte *)(param_1 + 0x148) = ((*(char *)(param_1 + 0x148) != -1) - 1U & 3) + 0x32;
  }
  return;
}



/* function 00547b80 FUN_00547b80 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00547b80(int param_1)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  float fVar5;
  float fVar6;
  float *pfVar7;
  float10 fVar8;
  float local_60;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_2c;
  float local_28;
  float local_24;
  float local_1c;
  float local_18;
  undefined4 local_14;
  
  fVar6 = DAT_00b7cb5c;
  uVar2 = *(uint *)(param_1 + 0x40);
  if (-1 < (char)uVar2) {
    if ((((uVar2 & 0x20) != 0) && ((*(byte *)(param_1 + 0x36) & 7) == 4)) &&
       (_DAT_00859948 < *(float *)(param_1 + 0x158))) {
      iVar3 = *(int *)(param_1 + 0x14);
      fVar1 = *(float *)(param_1 + 0x158);
      if (iVar3 == 0) {
        local_60 = *(float *)(param_1 + 0x10);
      }
      else {
        fVar8 = (float10)fpatan(-(float10)*(float *)(iVar3 + 0x10),(float10)*(float *)(iVar3 + 0x14)
                               );
        local_60 = (float)fVar8;
      }
      if (local_60 <= fVar1 + _DAT_00858cb8) {
        if (local_60 < fVar1 - _DAT_00858cb8) {
          local_60 = local_60 + _DAT_00858cbc;
        }
      }
      else {
        local_60 = local_60 - _DAT_00858cbc;
      }
      local_54 = -1000.0;
      if ((*(float *)(param_1 + 0x58) <= DAT_00858b50) ||
         (DAT_00b7cb5c * *(float *)(param_1 + 0x58) + local_60 <= _DAT_008cd7e8 + fVar1)) {
        if ((*(float *)(param_1 + 0x58) < DAT_00858b50) &&
           (DAT_00b7cb5c * *(float *)(param_1 + 0x58) + local_60 < fVar1 - _DAT_008cd7e8)) {
          local_54 = ((fVar1 - _DAT_008cd7e8) - local_60) / *(float *)(param_1 + 0x58);
        }
      }
      else {
        local_54 = ((_DAT_008cd7e8 + fVar1) - local_60) / *(float *)(param_1 + 0x58);
      }
      if (-DAT_00b7cb5c < local_54 != (-DAT_00b7cb5c == local_54)) {
        FUN_00541f40(local_54);
        FUN_00542e20();
        *(float *)(param_1 + 0x58) = _DAT_008cd7e4 * *(float *)(param_1 + 0x58);
        FUN_00541f40(fVar6 - local_54);
        *(uint *)(param_1 + 0x40) = *(uint *)(param_1 + 0x40) | 0x40000000;
      }
      FUN_00542dd0();
      FUN_00542e20();
      FUN_00541f40(fVar6);
      if ((*(uint *)(param_1 + 0x140) & 0x4000) == 0) {
        return;
      }
      fVar8 = (float10)FUN_00441db0();
      if ((float10)fVar1 <= (float10)_DAT_00858cb8 + fVar8) {
        if ((float10)fVar1 < fVar8 - (float10)_DAT_00858cb8) {
          fVar8 = fVar8 - (float10)_DAT_00858cbc;
        }
      }
      else {
        fVar8 = fVar8 + (float10)_DAT_00858cbc;
      }
      local_60 = local_60 - fVar1;
      fVar8 = fVar8 - (float10)fVar1;
      if (ABS(local_60) < _DAT_00858cdc) {
        local_60 = 0.0;
      }
      if (ABS(fVar8) < (float10)_DAT_00858cdc) {
        fVar8 = (float10)DAT_00858b50;
      }
      if ((float10)DAT_00858b50 <= (float10)local_60 * fVar8) {
        return;
      }
      *(undefined4 *)(param_1 + 0x58) = 0;
      return;
    }
    goto LAB_005480ae;
  }
  iVar3 = *(int *)(param_1 + 0x14);
  if ((uVar2 & 2) != 0) {
    if (DAT_00b7cb5c * *(float *)(param_1 + 0x4c) + *(float *)(iVar3 + 0x38) < DAT_008cdf08) {
      *(float *)(iVar3 + 0x38) = DAT_008cdf08;
      *(undefined4 *)(param_1 + 0x44) = 0;
      *(undefined4 *)(param_1 + 0x48) = 0;
      *(undefined4 *)(param_1 + 0x4c) = 0;
      *(undefined4 *)(param_1 + 0x50) = 0;
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x58) = 0;
    }
    goto LAB_005480ae;
  }
  local_58 = 1000.0;
  local_60 = 1000.0;
  fVar1 = DAT_00b7cb5c * *(float *)(param_1 + 0x44) + *(float *)(iVar3 + 0x30);
  if (((_DAT_008cdef4 < fVar1) && (fVar5 = _DAT_008cdef4, DAT_00858b50 < *(float *)(param_1 + 0x44))
      ) || ((fVar1 < _DAT_008cdf00 &&
            (fVar5 = _DAT_008cdf00, *(float *)(param_1 + 0x44) < DAT_00858b50)))) {
    local_58 = (fVar5 - *(float *)(iVar3 + 0x30)) / *(float *)(param_1 + 0x44);
  }
  fVar1 = DAT_00b7cb5c * *(float *)(param_1 + 0x48) + *(float *)(iVar3 + 0x34);
  if (((_DAT_008cdef8 < fVar1) && (fVar5 = _DAT_008cdef8, DAT_00858b50 < *(float *)(param_1 + 0x48))
      ) || ((fVar1 < _DAT_008cdf04 &&
            (fVar5 = _DAT_008cdf04, *(float *)(param_1 + 0x48) < DAT_00858b50)))) {
    local_60 = (fVar5 - *(float *)(iVar3 + 0x34)) / *(float *)(param_1 + 0x48);
  }
  bVar4 = _DAT_008cdef4 - _DAT_008cdf00 < _DAT_008cdef8 - _DAT_008cdf04;
  local_50 = 0.0;
  local_4c = 0.0;
  if ((local_60 <= local_58) || (_DAT_00858c4c <= local_58)) {
    if (_DAT_00858c4c <= local_60) goto LAB_005480ae;
    local_4c = -1.0;
    local_54 = ABS(*(float *)(param_1 + 0x48));
    if (*(float *)(param_1 + 0x48) <= DAT_00858b50) {
      local_4c = 1.0;
    }
    FUN_00541f40(local_60);
    FUN_00542dd0();
    FUN_00542e20();
    iVar3 = *(int *)(param_1 + 0x14);
    if (((_DAT_008cdef4 - _DAT_00863b64 < *(float *)(iVar3 + 0x30)) ||
        (*(float *)(iVar3 + 0x30) < _DAT_00863b64 + _DAT_008cdf00)) ||
       ((!bVar4 &&
        ((fVar1 = (_DAT_008cdf00 + _DAT_008cdef4) * _DAT_00858b8c,
         fVar1 - _DAT_00863b64 < *(float *)(iVar3 + 0x30) &&
         (*(float *)(iVar3 + 0x30) < _DAT_00863b64 + fVar1)))))) {
      fVar1 = fVar6 * *(float *)(param_1 + 0x48);
      *(uint *)(param_1 + 0x40) = *(uint *)(param_1 + 0x40) | 2;
      if (_DAT_00863b6c < fVar1) {
        fVar1 = _DAT_00863b6c / fVar6;
        goto LAB_00547fab;
      }
      if (fVar1 < -_DAT_00863b6c) {
        fVar1 = -(_DAT_00863b6c / fVar6);
        goto LAB_00547fab;
      }
    }
    else {
      fVar1 = *(float *)(param_1 + 0x48) * _DAT_00858c1c;
LAB_00547fab:
      *(float *)(param_1 + 0x48) = fVar1;
    }
    local_58 = fVar6 - local_60;
  }
  else {
    local_50 = -1.0;
    local_54 = ABS(*(float *)(param_1 + 0x44));
    if (*(float *)(param_1 + 0x44) <= DAT_00858b50) {
      local_50 = 1.0;
    }
    FUN_00541f40(local_58);
    FUN_00542dd0();
    FUN_00542e20();
    iVar3 = *(int *)(param_1 + 0x14);
    if (((_DAT_008cdef8 - _DAT_00863b64 < *(float *)(iVar3 + 0x34)) ||
        (*(float *)(iVar3 + 0x34) < _DAT_00863b64 + _DAT_008cdf04)) ||
       ((bVar4 && ((fVar1 = (_DAT_008cdf04 + _DAT_008cdef8) * _DAT_00858b8c,
                   fVar1 - _DAT_00863b64 < *(float *)(iVar3 + 0x34) &&
                   (*(float *)(iVar3 + 0x34) < _DAT_00863b64 + fVar1)))))) {
      fVar1 = fVar6 * *(float *)(param_1 + 0x44);
      *(uint *)(param_1 + 0x40) = *(uint *)(param_1 + 0x40) | 2;
      if (fVar1 <= _DAT_00863b6c) {
        if (fVar1 < -_DAT_00863b6c) {
          *(float *)(param_1 + 0x44) = -(_DAT_00863b6c / fVar6);
        }
        local_58 = fVar6 - local_58;
      }
      else {
        *(float *)(param_1 + 0x44) = _DAT_00863b6c / fVar6;
        local_58 = fVar6 - local_58;
      }
    }
    else {
      *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * _DAT_00858c1c;
      local_58 = fVar6 - local_58;
    }
  }
  FUN_00541f40(local_58);
  if (DAT_00858b50 < local_54) {
    fVar1 = *(float *)(*(int *)((&DAT_00a9b0c8)[*(short *)(param_1 + 0x22)] + 0x14) + 0x24);
    if (*(int *)(param_1 + 0x14) == 0) {
      pfVar7 = (float *)(param_1 + 4);
    }
    else {
      pfVar7 = (float *)(*(int *)(param_1 + 0x14) + 0x30);
    }
    local_2c = *pfVar7 - local_50 * fVar1;
    local_28 = pfVar7[1] - local_4c * fVar1;
    local_24 = pfVar7[2] - fVar1 * DAT_00858b50;
    local_1c = local_50;
    local_18 = local_4c;
    local_14 = 0;
    FUN_005454c0(_DAT_00863b60 * local_54,&local_2c);
    if ((*(byte *)(param_1 + 0x36) & 7) == 4) {
      FUN_00507350(0x3f8,param_1);
      *(char *)(param_1 + 0x148) = (*(char *)(param_1 + 0x148) == -1) * '\x04' + '2';
    }
  }
LAB_005480ae:
  FUN_00542dd0();
  FUN_00542e20();
  DAT_00b7cb5c = fVar6;
  if (fVar6 < _DAT_00858c14 != (fVar6 == _DAT_00858c14)) {
    DAT_00b7cb5c = _DAT_00858c14;
  }
  return;
}



/* function 0054f0d0 FUN_0054f0d0 */

void __thiscall FUN_0054f0d0(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0083cb1b;
  local_c = ExceptionList;
  iVar3 = param_2 * 0x54;
  ExceptionList = &local_c;
  piVar1 = operator_new(iVar3 + 4);
  piVar4 = (int *)0x0;
  local_4 = 0;
  if (piVar1 != (int *)0x0) {
    piVar4 = piVar1 + 1;
    *piVar1 = param_2;
    _eh_vector_constructor_iterator_
              (piVar4,0x54,param_2,(_func_void_void_ptr *)&LAB_0054f0c0,thunk_FUN_0059acd0);
  }
  *(int *)(param_1 + 0x50) = param_1 + 0x54;
  *(int *)(param_1 + 0x1a0) = param_1 + 0x1a4;
  *(int **)(param_1 + 0x1f8) = piVar4;
  *(int *)(param_1 + 0xa0) = param_1;
  *(int *)(param_1 + 0xf8) = param_1 + 0xfc;
  *(int *)(param_1 + 0x148) = param_1 + 0xa8;
  *(int *)(param_1 + 0x1f0) = param_1 + 0x150;
  for (; param_2 != 0; param_2 = param_2 + -1) {
    iVar3 = iVar3 + -0x54;
    iVar2 = *(int *)(param_1 + 0x1f8) + iVar3;
    *(undefined4 *)(iVar2 + 0x50) = *(undefined4 *)(param_1 + 0x1a0);
    *(int *)(*(int *)(param_1 + 0x1a0) + 0x4c) = iVar2;
    *(int *)(iVar2 + 0x4c) = param_1 + 0x150;
    *(int *)(param_1 + 0x1a0) = iVar2;
  }
  ExceptionList = local_c;
  return;
}



/* function 00557530 FUN_00557530 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00557530(float *param_1)

{
  float *pfVar1;
  uint *puVar2;
  int iVar3;
  undefined4 uVar4;
  float fVar5;
  int *piVar6;
  char cVar7;
  short sVar8;
  float *pfVar9;
  uint uVar10;
  undefined4 *puVar11;
  float *pfVar12;
  float *pfVar13;
  undefined4 uVar14;
  int *piVar15;
  int iVar16;
  float fVar17;
  float fVar18;
  int iVar19;
  float10 fVar20;
  float local_13c;
  float local_138;
  float local_134;
  float local_130;
  float *local_12c;
  float local_128;
  float local_124;
  float local_120;
  int *local_11c;
  float local_118;
  char cStack_112;
  char cStack_111;
  char cStack_110;
  char cStack_10f;
  char cStack_10e;
  char cStack_10d;
  float local_10c;
  float local_108;
  float local_104;
  char cStack_fe;
  char cStack_fd;
  float local_fc;
  float local_f8;
  float local_f4;
  float local_f0;
  float *local_ec;
  float local_e8;
  float local_e4 [3];
  float local_d8 [6];
  float local_c0 [3];
  undefined1 auStack_b4 [12];
  float local_a8;
  float local_a4;
  float local_a0;
  float local_98;
  float local_94;
  float local_90;
  float local_88;
  float local_84;
  float local_80;
  float local_60;
  float local_5c;
  float local_58;
  float local_50;
  float local_4c;
  float local_48;
  float local_40;
  float local_3c;
  float local_38;
  undefined1 auStack_18 [12];
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0083cc88;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  local_12c = param_1;
  fVar20 = (float10)FUN_00822130();
  local_ec = (float *)(float)fVar20;
  if (DAT_00b6f03c == 0) {
    pfVar9 = (float *)&DAT_00b6f02c;
  }
  else {
    pfVar9 = (float *)(DAT_00b6f03c + 0x30);
  }
  if (_DAT_00858a48 <=
      SQRT((pfVar9[1] - param_1[1]) * (pfVar9[1] - param_1[1]) +
           (*pfVar9 - *param_1) * (*pfVar9 - *param_1))) {
    ExceptionList = pvStack_c;
    return;
  }
  if (((*(byte *)((int)param_1 + 0x327) & 1) == 0) && ((uint)param_1[200] < (uint)DAT_00b7cb84)) {
    param_1[0x62] = param_1[0x62] - DAT_00b7cb5c * _DAT_00863e38;
    fVar18 = DAT_00b7cb5c * param_1[0x62];
    fVar17 = DAT_00b7cb5c * param_1[0x61];
    *param_1 = DAT_00b7cb5c * param_1[0x60] + *param_1;
    param_1[1] = fVar17 + param_1[1];
    param_1[2] = fVar18 + param_1[2];
  }
  if (((*(byte *)((int)param_1 + 0x327) & 4) != 0) && (((byte)DAT_00b7cb4c & 7) == 2)) {
    fVar20 = (float10)FUN_005696c0(*param_1,param_1[1],param_1[2],0,0);
    param_1[0xc1] = (float)fVar20;
  }
  if ((((*(byte *)((int)param_1 + 0x327) & 4) != 0) && (fVar18 = param_1[0xc6], fVar18 != 0.0)) &&
     ((((*(byte *)((int)fVar18 + 0x36) & 7) == 2 ||
       (((uVar10 = (uint)*(short *)((int)fVar18 + 0x22), uVar10 == DAT_008cd6c8 ||
         (uVar10 == DAT_008cd6cc)) || (uVar10 == DAT_008cd6d0)))) || (uVar10 == DAT_008cd6d8)))) {
    iVar16 = *(int *)((int)param_1[0xc5] + 0x14);
    if (iVar16 == 0) {
      iVar16 = (int)param_1[0xc5] + 4;
    }
    else {
      iVar16 = iVar16 + 0x30;
    }
    param_1[0xc1] = *(float *)(iVar16 + 8) - _DAT_00858b8c;
  }
  uVar10 = *(byte *)(param_1 + 0xc9) + 1;
  if (uVar10 < 0x20) {
    local_fc = _DAT_00858624 - (float)local_ec;
    pfVar9 = local_12c + uVar10 * 3 + 0x61;
    iVar16 = 0x20 - uVar10;
    do {
      pfVar1 = pfVar9 + -0x61;
      local_128 = *pfVar1;
      local_124 = pfVar9[-0x60];
      local_120 = pfVar9[-0x5f];
      pfVar13 = pfVar9 + -1;
      uVar10 = _rand();
      local_118 = (float)((uVar10 & 0xf) - 8);
      *pfVar13 = (float)(int)local_118 * _DAT_00858cdc + *pfVar13;
      uVar10 = _rand();
      *pfVar9 = (float)(int)((uVar10 & 0xf) - 8) * _DAT_00858cdc + *pfVar9;
      local_c0[0] = (float)local_ec * *pfVar13;
      local_d8[0] = local_fc * pfVar9[-4];
      local_f0 = local_fc * pfVar9[-2] + (float)local_ec * pfVar9[1];
      local_f4 = local_fc * pfVar9[-3] + (float)local_ec * *pfVar9;
      local_f8 = local_d8[0] + local_c0[0];
      *pfVar13 = local_f8;
      *pfVar9 = local_f4;
      pfVar9[1] = local_f0;
      fVar18 = pfVar9[-0x5f] - DAT_00b7cb5c * _DAT_00858fcc;
      pfVar9[-0x5f] = fVar18;
      if ((*(byte *)((int)local_12c + 0x327) & 4) != 0) {
        fVar17 = local_12c[0xc1] + _DAT_00858c24;
        if (local_12c[0xc1] + _DAT_00858c24 < fVar18) {
          fVar17 = fVar18;
        }
        pfVar9[-0x5f] = fVar17;
      }
      fVar18 = pfVar9[-0x5f] - pfVar9[-0x62];
      local_118 = pfVar9[-0x60] - pfVar9[-99];
      local_d8[3] = *pfVar1 - pfVar9[-100];
      fVar17 = local_12c[0xc3] /
               SQRT(fVar18 * fVar18 + local_118 * local_118 + local_d8[3] * local_d8[3]);
      local_118 = local_118 * fVar17;
      local_d8[3] = local_d8[3] * fVar17;
      local_104 = fVar18 * fVar17 + pfVar9[-0x62];
      local_108 = local_118 + pfVar9[-99];
      local_10c = local_d8[3] + pfVar9[-100];
      *pfVar1 = local_10c;
      pfVar9[-0x60] = local_108;
      pfVar9[-0x5f] = local_104;
      local_11c = (int *)(pfVar9[-0x60] - local_124);
      local_e4[0] = *pfVar1 - local_128;
      local_138 = _DAT_00858624 / DAT_00b7cb5c;
      local_130 = local_138 * (pfVar9[-0x5f] - local_120);
      local_134 = local_138 * (float)local_11c;
      local_138 = local_138 * local_e4[0];
      *pfVar13 = local_138;
      *pfVar9 = local_134;
      pfVar9[1] = local_130;
      pfVar9 = pfVar9 + 3;
      iVar16 = iVar16 + -1;
    } while (iVar16 != 0);
  }
  cVar7 = *(char *)((int)local_12c + 0x325);
  if (((((cVar7 != '\x01') && (cVar7 != '\x02')) &&
       ((cVar7 != '\x04' && ((cVar7 != '\x05' && (cVar7 != '\a')))))) && (cVar7 != '\x06')) &&
     (cVar7 != '\x03')) goto switchD_00558324_caseD_5;
  if (((cVar7 == '\x04') && (DAT_00b76898 == 1)) ||
     (((cVar7 == '\x05' && (DAT_00b76898 == 2)) ||
      (((cVar7 == '\a' && (DAT_00b76898 == 3)) || ((cVar7 == '\x06' && (DAT_00b76898 == 4)))))))) {
LAB_00557995:
    if ((cVar7 == '\x01') || ((cVar7 == '\x02' || (cVar7 == '\x03')))) {
LAB_00557b04:
      FUN_0053fb70(0);
      sVar8 = FUN_0053fc10();
      if (((sVar8 < 0) && (DAT_00a44496 != '\0')) || ((0 < sVar8 && (DAT_00a44495 != '\0')))) {
        local_11c = (int *)(int)sVar8;
        local_12c[199] = local_12c[199] - (float)(int)local_11c * DAT_00b7cb5c * _DAT_00858c14;
      }
      fVar18 = local_12c[199];
      if (_DAT_00863e34 < local_12c[199]) {
        fVar18 = _DAT_00863e34;
      }
      local_12c[199] = fVar18;
    }
    else {
      if (DAT_00a44496 != '\0') {
        local_118 = DAT_00b7cb5c;
        iVar16 = FUN_0053fb70(0);
        pfVar9 = local_12c;
        local_11c = (int *)(int)*(short *)(iVar16 + 0x1c);
        cVar7 = *(char *)((int)local_12c + 0x325);
        fVar18 = (float)(int)local_11c * local_118 * _DAT_00858c14;
        if (((((cVar7 == '\x04') || (cVar7 == '\x05')) || (cVar7 == '\a')) || (cVar7 == '\x06')) &&
           ((DAT_00858b50 < fVar18 && (fVar18 + local_12c[199] < _DAT_00858c20)))) {
          FUN_005073b0(0x68,local_12c[0xc4],0,0x3f800000);
        }
        pfVar9[199] = fVar18 + pfVar9[199];
      }
      if (DAT_00a44495 != '\0') {
        local_118 = DAT_00b7cb5c;
        iVar16 = FUN_0053fb70(0);
        pfVar9 = local_12c;
        local_11c = (int *)(int)*(short *)(iVar16 + 0x20);
        cVar7 = *(char *)((int)local_12c + 0x325);
        fVar18 = (float)(int)local_11c * local_118 * _DAT_00858c14;
        if ((((cVar7 == '\x04') || (cVar7 == '\x05')) || ((cVar7 == '\a' || (cVar7 == '\x06')))) &&
           ((DAT_00858b50 < fVar18 && (_DAT_00858c58 < local_12c[199] - fVar18)))) {
          FUN_005073b0(0x68,local_12c[0xc4],0,0x3f800000);
        }
        pfVar9[199] = pfVar9[199] - fVar18;
      }
    }
  }
  else {
    if (cVar7 == '\x01') goto LAB_00557b04;
    if ((cVar7 == '\x03') || (cVar7 == '\x02')) goto LAB_00557995;
  }
  pfVar9 = local_12c;
  fVar18 = local_12c[199];
  if (local_12c[199] < _DAT_00858c58) {
    fVar18 = _DAT_00858c58;
  }
  local_12c[199] = fVar18;
  if (_DAT_00858c20 < fVar18) {
    fVar18 = _DAT_00858c20;
  }
  fVar17 = local_12c[0xc6];
  local_12c[199] = fVar18;
  pfVar13 = local_12c + 0xc6;
  if (fVar17 == 0.0) {
    fVar17 = local_12c[0xc5];
    local_13c = DAT_008cd898;
    *(uint *)((int)fVar17 + 0x1c) = *(uint *)((int)fVar17 + 0x1c) | 1;
  }
  else {
    fVar18 = *(float *)((int)fVar17 + 0x8c);
    if (*(short *)((int)fVar17 + 0x22) == 0x1ac) {
      fVar18 = _DAT_00859a98;
    }
    local_13c = _DAT_008cd89c * _DAT_00863e30 * fVar18 + DAT_008cd898;
    if (local_13c <= _DAT_00858b8c) {
      *(undefined1 *)((int)fVar17 + 0xb8) = 0;
    }
    else {
      local_13c = 0.5;
      *(undefined1 *)((int)fVar17 + 0xb8) = 0;
    }
  }
  local_ec = pfVar13;
  if (fVar17 != 0.0) {
    if (*(int *)((int)fVar17 + 0x14) == 0) {
      puVar11 = (undefined4 *)((int)fVar17 + 4);
    }
    else {
      puVar11 = (undefined4 *)(*(int *)((int)fVar17 + 0x14) + 0x30);
    }
    cVar7 = FUN_005561b0(*puVar11,puVar11[1],puVar11[2],0x3dcccccd,&local_128);
    if (cVar7 != '\0') {
      if (*(int *)((int)fVar17 + 0x14) == 0) {
        *(float *)((int)fVar17 + 4) = local_128;
        *(float *)((int)fVar17 + 8) = local_124;
        *(float *)((int)fVar17 + 0xc) = local_120;
      }
      else {
        *(float *)(*(int *)((int)fVar17 + 0x14) + 0x30) = local_128;
        *(float *)(*(int *)((int)fVar17 + 0x14) + 0x34) = local_124;
        *(float *)(*(int *)((int)fVar17 + 0x14) + 0x38) = local_120;
      }
      pfVar1 = (float *)((int)fVar17 + 0x44);
      local_128 = *pfVar1;
      local_124 = *(float *)((int)fVar17 + 0x48);
      local_120 = *(float *)((int)fVar17 + 0x4c);
      iVar16 = *(int *)((int)pfVar9[0xc4] + 0x14);
      if (iVar16 == 0) {
        pfVar12 = (float *)((int)pfVar9[0xc4] + 4);
      }
      else {
        pfVar12 = (float *)(iVar16 + 0x30);
      }
      local_130 = pfVar9[2] - pfVar12[2];
      local_134 = pfVar9[1] - pfVar12[1];
      local_138 = *pfVar9 - *pfVar12;
      FUN_00542ce0(&local_f8,local_138,local_134,local_130);
      cVar7 = *(char *)((int)pfVar9 + 0x325);
      if ((((cVar7 == '\x04') || (cVar7 == '\x05')) || (cVar7 == '\x06')) || (cVar7 == '\a')) {
        local_138 = 0.0;
        local_134 = 0.0;
        local_130 = 0.0;
        local_f8 = 0.0;
        local_f4 = 0.0;
        local_f0 = 0.0;
      }
      local_128 = local_128 - local_f8;
      local_124 = local_124 - local_f4;
      local_120 = local_120 - local_f0;
      if (*(int *)((int)fVar17 + 0x14) == 0) {
        pfVar12 = (float *)((int)fVar17 + 4);
      }
      else {
        pfVar12 = (float *)(*(int *)((int)fVar17 + 0x14) + 0x30);
      }
      local_104 = pfVar12[2] - pfVar9[2];
      local_108 = pfVar12[1] - pfVar9[1];
      local_10c = *pfVar12 - *pfVar9;
      FUN_0059c910();
      fVar5 = local_108 * local_124 + local_10c * local_128 + local_104 * local_120;
      fVar18 = local_128;
      if (DAT_00858b50 < fVar5) {
        fVar18 = local_128 - local_10c * fVar5;
        local_124 = local_124 - fVar5 * local_108;
        local_120 = local_120 - fVar5 * local_104;
      }
      local_fc = (local_f0 + local_120) - *(float *)((int)fVar17 + 0x4c);
      local_118 = (local_f4 + local_124) - *(float *)((int)fVar17 + 0x48);
      local_e4[0] = (fVar18 + local_f8) - *pfVar1;
      fVar18 = _DAT_00858624 - local_13c;
      *pfVar1 = local_e4[0] * fVar18 + *pfVar1;
      *(float *)((int)fVar17 + 0x48) = local_118 * fVar18 + *(float *)((int)fVar17 + 0x48);
      *(float *)((int)fVar17 + 0x4c) = local_fc * fVar18 + *(float *)((int)fVar17 + 0x4c);
      local_e8 = local_fc * local_13c;
      fVar18 = pfVar9[0xc4];
      local_11c = (int *)(local_118 * local_13c);
      local_e4[0] = local_e4[0] * local_13c;
      local_130 = *(float *)((int)fVar18 + 0x4c) - local_e8;
      local_134 = *(float *)((int)fVar18 + 0x48) - (float)local_11c;
      local_138 = *(float *)((int)fVar18 + 0x44) - local_e4[0];
      *(float *)((int)fVar18 + 0x44) = local_138;
      *(float *)((int)fVar18 + 0x48) = local_134;
      *(float *)((int)fVar18 + 0x4c) = local_130;
      if (*pfVar13 == 0.0) {
        local_138 = -local_10c;
        local_134 = -local_108;
        local_130 = -local_104;
        FUN_0059b7e0(local_138,local_134,local_130);
      }
      else {
        FUN_0059bcf0(*(undefined4 *)((int)fVar17 + 0x14));
        local_130 = -local_104;
        local_134 = -local_108;
        local_4 = 0;
        local_138 = -local_10c;
        FUN_0059b7e0(local_138,local_134,local_130);
        FUN_0059bcf0(*(undefined4 *)((int)fVar17 + 0x14));
        **(float **)((int)fVar17 + 0x14) = local_a8 * _DAT_00858b1c + local_60 * _DAT_00858c20;
        *(float *)(*(int *)((int)fVar17 + 0x14) + 4) =
             local_a4 * _DAT_00858b1c + local_5c * _DAT_00858c20;
        *(float *)(*(int *)((int)fVar17 + 0x14) + 8) =
             local_a0 * _DAT_00858b1c + local_58 * _DAT_00858c20;
        *(float *)(*(int *)((int)fVar17 + 0x14) + 0x10) =
             local_98 * _DAT_00858b1c + local_50 * _DAT_00858c20;
        *(float *)(*(int *)((int)fVar17 + 0x14) + 0x14) =
             local_94 * _DAT_00858b1c + local_4c * _DAT_00858c20;
        *(float *)(*(int *)((int)fVar17 + 0x14) + 0x18) =
             local_90 * _DAT_00858b1c + local_48 * _DAT_00858c20;
        *(float *)(*(int *)((int)fVar17 + 0x14) + 0x20) =
             local_88 * _DAT_00858b1c + local_40 * _DAT_00858c20;
        *(float *)(*(int *)((int)fVar17 + 0x14) + 0x24) =
             local_84 * _DAT_00858b1c + local_3c * _DAT_00858c20;
        *(float *)(*(int *)((int)fVar17 + 0x14) + 0x28) =
             local_80 * _DAT_00858b1c + local_38 * _DAT_00858c20;
        FUN_0059acd0();
        local_4 = 0xffffffff;
        FUN_0059acd0();
      }
    }
    if (*pfVar13 != 0.0) {
      FUN_0059bbc0(*(undefined4 *)((int)*pfVar13 + 0x14));
      fVar18 = *pfVar13;
      fVar17 = pfVar9[0xc5];
      *(undefined4 *)((int)fVar17 + 0x44) = *(undefined4 *)((int)fVar18 + 0x44);
      *(undefined4 *)((int)fVar17 + 0x48) = *(undefined4 *)((int)fVar18 + 0x48);
      *(undefined4 *)((int)fVar17 + 0x4c) = *(undefined4 *)((int)fVar18 + 0x4c);
      local_130 = *(float *)(*(int *)((&DAT_00a9b0c8)[*(short *)((int)*pfVar13 + 0x22)] + 0x14) +
                            0x14);
      local_138 = 0.0;
      local_134 = 0.0;
      puVar11 = (undefined4 *)
                FUN_0059c890(local_e4,*(undefined4 *)((int)*pfVar13 + 0x14),&local_138);
      uVar14 = puVar11[2];
      fVar18 = pfVar9[0xc5];
      uVar4 = puVar11[1];
      if (*(int *)((int)fVar18 + 0x14) == 0) {
        *(undefined4 *)((int)fVar18 + 4) = *puVar11;
        *(undefined4 *)((int)fVar18 + 8) = uVar4;
        *(undefined4 *)((int)fVar18 + 0xc) = uVar14;
      }
      else {
        *(undefined4 *)(*(int *)((int)fVar18 + 0x14) + 0x30) = *puVar11;
        *(undefined4 *)(*(int *)((int)fVar18 + 0x14) + 0x34) = uVar4;
        *(undefined4 *)(*(int *)((int)fVar18 + 0x14) + 0x38) = uVar14;
      }
    }
  }
  pfVar9 = local_12c;
  piVar6 = DAT_00b74494;
  piVar15 = DAT_00b74490;
  local_10c = local_12c[0x5d];
  local_108 = local_12c[0x5e];
  local_104 = local_12c[0x5f];
  if (*pfVar13 != 0.0) {
    cVar7 = *(char *)((int)local_12c + 0x325);
    if ((((((cVar7 == '\x04') && (DAT_00b76898 == 1)) || ((cVar7 == '\x05' && (DAT_00b76898 == 2))))
         || (((cVar7 == '\a' && (DAT_00b76898 == 3)) || ((cVar7 == '\x06' && (DAT_00b76898 == 4)))))
         ) || (((cVar7 == '\x01' || (cVar7 == '\x03')) || (cVar7 == '\x02')))) &&
       (DAT_00a44494 != '\0')) {
      FUN_0053fb70(0);
      sVar8 = FUN_0053ffe0();
      if (sVar8 != 0) {
        FUN_00556030();
      }
    }
    fVar18 = *pfVar13;
    if ((fVar18 != 0.0) && ((*(uint *)((int)fVar18 + 0x40) & 0x20000000) != 0)) {
      *(uint *)((int)fVar18 + 0x40) = *(uint *)((int)fVar18 + 0x40) & 0xfdffffff;
      *(uint *)((int)*pfVar13 + 0x40) = *(uint *)((int)*pfVar13 + 0x40) & 0x7fffffff;
      fVar18 = pfVar9[0xc5];
      *pfVar13 = 0.0;
      puVar2 = (uint *)((int)fVar18 + 0x1c);
      *puVar2 = *puVar2 | 1;
      *(undefined1 *)((int)pfVar9 + 0x326) = 0x3c;
    }
    fVar18 = *pfVar13;
    if (((fVar18 != 0.0) && ((*(byte *)((int)fVar18 + 0x36) & 7) == 2)) &&
       ((*(int *)((int)fVar18 + 0x594) == 9 && (*(int *)((int)fVar18 + 0x460) != 0)))) {
      FUN_00556030();
    }
    goto switchD_00558324_caseD_5;
  }
  if (*(char *)((int)local_12c + 0x326) != '\0') {
    *(char *)((int)local_12c + 0x326) = *(char *)((int)local_12c + 0x326) + -1;
    goto switchD_00558324_caseD_5;
  }
  cStack_fd = '\0';
  cStack_10f = '\0';
  cStack_fe = '\0';
  cStack_10e = '\0';
  cStack_111 = '\0';
  cStack_112 = '\0';
  cStack_110 = '\0';
  cStack_10d = '\0';
  switch(*(undefined1 *)((int)local_12c + 0x325)) {
  case 1:
    break;
  case 2:
    iVar16 = DAT_00b74490[2];
    if (iVar16 != 0) {
      iVar19 = iVar16 * 0x7c4;
      do {
        iVar3 = iVar16 + -1;
        iVar16 = iVar16 + -1;
        iVar19 = iVar19 + -0x7c4;
        if ((((-1 < *(char *)(iVar3 + piVar15[1])) &&
             (fVar18 = (float)(*piVar15 + iVar19), fVar18 != 0.0)) &&
            (*(int *)((int)fVar18 + 0x530) != 0x37)) &&
           ((cVar7 = FUN_005df8f0(), pfVar9 = local_ec, cVar7 == '\0' &&
            ((*(uint *)((int)fVar18 + 0x46c) & 0x100) == 0)))) {
          if (*(int *)((int)fVar18 + 0x14) == 0) {
            pfVar13 = (float *)((int)fVar18 + 4);
          }
          else {
            pfVar13 = (float *)(*(int *)((int)fVar18 + 0x14) + 0x30);
          }
          local_138 = *pfVar13;
          local_134 = pfVar13[1];
          local_130 = pfVar13[2];
          if (SQRT((local_138 - local_10c) * (local_138 - local_10c) +
                   (local_134 - local_108) * (local_134 - local_108) +
                   (local_130 - local_104) * (local_130 - local_104)) < _DAT_00858fa0) {
            *local_ec = fVar18;
            FUN_00571b70(local_ec);
            puVar2 = (uint *)((int)*pfVar9 + 0x40);
            *puVar2 = *puVar2 | 0x80000000;
            local_130 = *(float *)(*(int *)((&DAT_00a9b0c8)[*(short *)((int)fVar18 + 0x22)] + 0x14)
                                  + 0x14);
            local_138 = 0.0;
            local_134 = 0.0;
            uVar14 = FUN_0059c890(local_e4,*(undefined4 *)((int)*pfVar9 + 0x14),&local_138);
            pfVar9 = local_12c;
            FUN_004241c0(uVar14);
            fVar18 = DAT_00858b50;
            *(uint *)((int)pfVar9[0xc5] + 0x1c) = *(uint *)((int)pfVar9[0xc5] + 0x1c) & 0xfffffffe;
            if (fVar18 < local_104 - local_120) {
              fVar20 = (float10)FUN_00420800((pfVar9[199] -
                                             (local_104 - local_120) *
                                             (_DAT_00858624 / pfVar9[0xc2])) -
                                             (_DAT_00858624 / pfVar9[0xc2]) * pfVar9[0xc3],
                                             0x3c23d70a);
              pfVar9[199] = (float)fVar20;
            }
            break;
          }
        }
      } while (iVar16 != 0);
    }
    goto switchD_00558324_caseD_5;
  case 3:
    cStack_111 = '\x01';
    cStack_112 = '\x01';
    cStack_110 = '\x01';
    cStack_10d = '\x01';
    cStack_fd = '\x01';
    break;
  case 4:
    cStack_10f = '\x01';
    break;
  default:
    goto switchD_00558324_caseD_5;
  case 6:
    cStack_10e = '\x01';
    break;
  case 7:
    cStack_fe = '\x01';
    goto LAB_0055876f;
  }
  iVar16 = DAT_00b74494[2];
  if (iVar16 != 0) {
    iVar19 = iVar16 * 0xa18;
    do {
      iVar3 = iVar16 + -1;
      iVar16 = iVar16 + -1;
      iVar19 = iVar19 + -0xa18;
      if ((((-1 < *(char *)(iVar3 + piVar6[1])) &&
           (fVar18 = (float)(*piVar6 + iVar19), fVar18 != 0.0)) &&
          (((((iVar3 = *(int *)((int)fVar18 + 0x594), iVar3 == 0 ||
              (((iVar3 == 9 && (*(int *)((int)fVar18 + 0x460) == 0)) || (iVar3 == 1)))) ||
             ((*(short *)((int)fVar18 + 0x22) == 0x1d9 || (*(short *)((int)fVar18 + 0x22) == 0x21b))
             )) && ((*(uint *)((int)fVar18 + 0x40) & 0x20000000) == 0)) &&
           (((*(byte *)((int)fVar18 + 0x42d) & 0x10) != 0 &&
            ((cStack_fd == '\0' || (*(short *)((int)fVar18 + 0x22) == 0x234)))))))) &&
         ((*(byte *)((int)fVar18 + 0x4a8) & 0x60) == 0)) {
        local_130 = *(float *)(*(int *)((&DAT_00a9b0c8)[*(short *)((int)fVar18 + 0x22)] + 0x14) +
                              0x14);
        local_138 = 0.0;
        local_134 = 0.0;
        pfVar13 = (float *)FUN_0059c890(local_e4,*(undefined4 *)((int)fVar18 + 0x14),&local_138);
        pfVar9 = local_ec;
        local_128 = *pfVar13;
        local_124 = pfVar13[1];
        local_120 = pfVar13[2];
        if (SQRT((local_124 - local_108) * (local_124 - local_108) +
                 (local_120 - local_104) * (local_120 - local_104) +
                 (local_128 - local_10c) * (local_128 - local_10c)) < _DAT_00858fa0) {
          *local_ec = fVar18;
          FUN_00571b70(local_ec);
          puVar2 = (uint *)((int)*pfVar9 + 0x40);
          *puVar2 = *puVar2 | 0x80000000;
          if ((*(byte *)((int)fVar18 + 0x36) & 0xf8) == 0x10) {
            *(byte *)((int)fVar18 + 0x36) = *(byte *)((int)fVar18 + 0x36) & 7 | 0x18;
          }
          local_130 = *(float *)(*(int *)((&DAT_00a9b0c8)[*(short *)((int)fVar18 + 0x22)] + 0x14) +
                                0x14);
          local_138 = 0.0;
          local_134 = 0.0;
          puVar11 = (undefined4 *)
                    FUN_0059c890(local_e4,*(undefined4 *)((int)*pfVar9 + 0x14),&local_138);
          uVar14 = puVar11[2];
          uVar4 = puVar11[1];
          fVar18 = local_12c[0xc5];
          if (*(int *)((int)fVar18 + 0x14) == 0) {
            *(undefined4 *)((int)fVar18 + 4) = *puVar11;
            *(undefined4 *)((int)fVar18 + 8) = uVar4;
            *(undefined4 *)((int)fVar18 + 0xc) = uVar14;
          }
          else {
            *(undefined4 *)(*(int *)((int)fVar18 + 0x14) + 0x30) = *puVar11;
            *(undefined4 *)(*(int *)((int)fVar18 + 0x14) + 0x34) = uVar4;
            *(undefined4 *)(*(int *)((int)fVar18 + 0x14) + 0x38) = uVar14;
          }
          *(uint *)((int)local_12c[0xc5] + 0x1c) =
               *(uint *)((int)local_12c[0xc5] + 0x1c) & 0xfffffffe;
          fVar18 = _DAT_00858c58;
          pfVar13 = local_ec;
          if (DAT_00858b50 < local_104 - local_120) {
            fVar17 = (local_12c[199] - (local_104 - local_120) * (_DAT_00858624 / local_12c[0xc2]))
                     - (_DAT_00858624 / local_12c[0xc2]) * local_12c[0xc3];
            local_12c[199] = fVar17;
            if (fVar17 <= fVar18) {
              fVar17 = _DAT_00858c58;
            }
            local_12c[199] = fVar17;
          }
          break;
        }
      }
      pfVar13 = local_ec;
    } while (iVar16 != 0);
  }
  if ((((cStack_10f != '\0') || (cStack_10e != '\0')) || (cStack_111 != '\0')) ||
     (((cStack_112 != '\0' || (cStack_110 != '\0')) || (cStack_10d != '\0')))) {
LAB_0055876f:
    if (*pfVar13 == 0.0) {
      iVar16 = DAT_00b7449c[2];
      local_11c = DAT_00b7449c;
      if (iVar16 != 0) {
        local_e8 = (float)(iVar16 * 0x19c);
        piVar15 = DAT_00b7449c;
        do {
          iVar16 = iVar16 + -1;
          local_e8 = (float)((int)local_e8 + -0x19c);
          if (((((*(byte *)(iVar16 + piVar15[1]) & 0x80) == 0) &&
               (fVar18 = (float)(*piVar15 + (int)local_e8), fVar18 != 0.0)) &&
              ((*(uint *)((int)fVar18 + 0x140) & 0x40000) != 0)) &&
             ((((cStack_10f != '\0' &&
                ((((uVar10 = (uint)*(short *)((int)fVar18 + 0x22), uVar10 == DAT_008cd6c8 ||
                   (uVar10 == DAT_008cd6cc)) || (uVar10 == DAT_008cd6d0)) ||
                 ((uVar10 == DAT_008cd6d4 || (uVar10 == DAT_008cd6d8)))))) ||
               ((cStack_fe != '\0' &&
                (uVar10 = (uint)*(short *)((int)fVar18 + 0x22), uVar10 == DAT_008cd6dc)))) ||
              ((((cStack_10e != '\0' &&
                 (((uVar10 = (uint)*(short *)((int)fVar18 + 0x22), uVar10 == DAT_008cd704 ||
                   (uVar10 == DAT_008cd708)) ||
                  ((uVar10 == DAT_008cd70c || (uVar10 == DAT_008cd714)))))) &&
                (*(int *)((int)fVar18 + 0xfc) == 0)) ||
               (((((cStack_111 != '\0' &&
                   (uVar10 = (uint)*(short *)((int)fVar18 + 0x22), uVar10 == DAT_008cd724)) ||
                  ((cStack_112 != '\0' &&
                   (uVar10 = (uint)*(short *)((int)fVar18 + 0x22), uVar10 == DAT_008cd734)))) ||
                 ((cStack_110 != '\0' &&
                  (uVar10 = (uint)*(short *)((int)fVar18 + 0x22), uVar10 == DAT_008cd738)))) ||
                ((cStack_10d != '\0' &&
                 (uVar10 = (uint)*(short *)((int)fVar18 + 0x22), uVar10 == DAT_008cd73c)))))))))) {
            local_130 = *(float *)(*(int *)((&DAT_00a9b0c8)[uVar10] + 0x14) + 0x14);
            local_138 = 0.0;
            local_134 = 0.0;
            pfVar9 = (float *)FUN_0059c890(local_e4,*(undefined4 *)((int)fVar18 + 0x14),&local_138);
            local_128 = *pfVar9;
            local_124 = pfVar9[1];
            local_120 = pfVar9[2];
            uVar10 = (uint)*(short *)((int)fVar18 + 0x22);
            iVar19 = 0;
            if ((((uVar10 == DAT_008cd6c8) || (uVar10 == DAT_008cd6cc)) || (uVar10 == DAT_008cd6d0))
               || (uVar10 == DAT_008cd6d8)) {
              local_d8[5] = -*(float *)(*(int *)((&DAT_00a9b0c8)[uVar10] + 0x14) + 0x14);
              local_d8[3] = 0.0;
              local_d8[4] = 0.0;
              FUN_0059c890(&local_f8,*(undefined4 *)((int)fVar18 + 0x14),local_d8 + 3);
              if (local_120 < local_f0) {
                local_128 = local_f8;
                local_124 = local_f4;
                local_120 = local_f0;
                iVar19 = 2;
              }
              local_c0[0] = *(float *)(*(int *)((&DAT_00a9b0c8)[*(short *)((int)fVar18 + 0x22)] +
                                               0x14) + 0x14);
              local_c0[1] = 0.0;
              local_c0[2] = 0.0;
              pfVar9 = (float *)FUN_0059c890(auStack_18,*(undefined4 *)((int)fVar18 + 0x14),local_c0
                                            );
              local_f8 = *pfVar9;
              local_f4 = pfVar9[1];
              local_f0 = pfVar9[2];
              if (local_120 < local_f0) {
                local_128 = *pfVar9;
                local_124 = pfVar9[1];
                local_120 = pfVar9[2];
                iVar19 = 3;
              }
              local_d8[0] = -*(float *)(*(int *)((&DAT_00a9b0c8)[*(short *)((int)fVar18 + 0x22)] +
                                                0x14) + 0x14);
              local_d8[1] = 0.0;
              local_d8[2] = 0.0;
              pfVar9 = (float *)FUN_0059c890(auStack_b4,*(undefined4 *)((int)fVar18 + 0x14),local_d8
                                            );
              local_f8 = *pfVar9;
              local_f4 = pfVar9[1];
              local_f0 = pfVar9[2];
              if (local_120 < local_f0) {
                local_128 = *pfVar9;
                local_124 = pfVar9[1];
                local_120 = pfVar9[2];
                iVar19 = 1;
              }
            }
            piVar15 = local_11c;
            if (SQRT((local_128 - local_10c) * (local_128 - local_10c) +
                     (local_124 - local_108) * (local_124 - local_108) +
                     (local_120 - local_104) * (local_120 - local_104)) < _DAT_00858fa0) {
              *pfVar13 = fVar18;
              FUN_00571b70(pfVar13);
              *(uint *)((int)*pfVar13 + 0x40) = *(uint *)((int)*pfVar13 + 0x40) | 0x80000000;
              local_d8[2] = *(float *)(*(int *)((&DAT_00a9b0c8)[*(short *)((int)fVar18 + 0x22)] +
                                               0x14) + 0x14);
              local_d8[0] = 0.0;
              local_d8[1] = 0.0;
              uVar14 = FUN_0059c890(auStack_b4,*(undefined4 *)((int)*pfVar13 + 0x14),local_d8);
              pfVar9 = local_12c;
              FUN_004241c0(uVar14);
              *(uint *)((int)pfVar9[0xc5] + 0x1c) = *(uint *)((int)pfVar9[0xc5] + 0x1c) & 0xfffffffe
              ;
              uVar10 = ((int *)*pfVar13)[7];
              if (((uVar10 & 4) != 0) || ((uVar10 & 0x40000) != 0)) {
                (**(code **)(*(int *)*pfVar13 + 0x10))(0);
                FUN_00542800();
              }
              *(uint *)((int)*pfVar13 + 0x40) = *(uint *)((int)*pfVar13 + 0x40) | 0x2000000;
              fVar18 = _DAT_00858c58;
              if (DAT_00858b50 < local_104 - local_120) {
                fVar17 = (pfVar9[199] - (local_104 - local_120) * (_DAT_00858624 / pfVar9[0xc2])) -
                         (_DAT_00858624 / pfVar9[0xc2]) * pfVar9[0xc3];
                pfVar9[199] = fVar17;
                if (fVar17 <= fVar18) {
                  fVar17 = _DAT_00858c58;
                }
                pfVar9[199] = fVar17;
              }
              for (; iVar19 != 0; iVar19 = iVar19 + -1) {
                pfVar9 = *(float **)((int)*pfVar13 + 0x14);
                local_138 = *pfVar9;
                local_134 = pfVar9[1];
                local_f8 = -local_138;
                local_130 = pfVar9[2];
                local_f4 = -local_134;
                *pfVar9 = pfVar9[8];
                pfVar9[1] = pfVar9[9];
                pfVar9[2] = pfVar9[10];
                iVar16 = *(int *)((int)*pfVar13 + 0x14);
                local_f0 = -local_130;
                *(float *)(iVar16 + 0x20) = local_f8;
                *(float *)(iVar16 + 0x24) = local_f4;
                *(float *)(iVar16 + 0x28) = local_f0;
              }
              break;
            }
          }
        } while (iVar16 != 0);
      }
    }
  }
switchD_00558324_caseD_5:
  FUN_00405fa5();
  return;
}



/* function 0056e610 FUN_0056e610 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0056e610(int *param_1)

{
  bool bVar1;
  char cVar2;
  char cVar3;
  int iVar4;
  float10 fVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  
  if (DAT_00969174 == '\0') {
    if ((_DAT_00b9b8f4 & 1) == 0) {
      _DAT_00b9b8f4 = _DAT_00b9b8f4 | 1;
      DAT_00b9b8f2 = DAT_00b70153;
    }
    iVar4 = FUN_0053fb70(0);
    if (((((*(short *)(iVar4 + 0x10e) == 0) && (DAT_00ba82e3 == '\0')) && (DAT_00b6f065 == '\0')) &&
        ((DAT_00b5f851 == '\0' &&
         (cVar3 = thunk_FUN_0156cf30(), cVar2 = DAT_00b9b8f2, cVar3 == '\0')))) &&
       ((param_1[0x2c] == 0 && ((*param_1 != 0 && (*(int *)(*param_1 + 0xfc) == 0)))))) {
      if (DAT_00b70153 != DAT_00b9b8f2) {
        if ((short)param_1[0x51] == 0) {
          DAT_00b9b8f1 = 0;
        }
        *(short *)(param_1 + 0x51) = (short)param_1[0x51] + 1;
      }
      if ((short)param_1[0x51] < 0x31) {
        DAT_00b9b8f0 = '\0';
      }
      else {
        if (DAT_00b70153 == cVar2) {
          return;
        }
        FUN_005effe0(0x151,0,0x3f800000,0,0,0);
        uVar8 = 0;
        uVar7 = 0x6e;
        uVar6 = 400;
        FUN_0053fb70(0,400,0x6e,0);
        thunk_FUN_0053f925(uVar6,uVar7,uVar8);
        if (DAT_00b9b8f0 == '\0') {
          uVar6 = FUN_006a0050("NOTEAT",1,0,1);
          FUN_00588be0(uVar6);
          DAT_00b9b8f0 = '\x01';
        }
        else {
          bVar1 = false;
          fVar5 = (float10)FUN_00558e40(0x15);
          if ((float10)DAT_00858b50 < fVar5) {
            FUN_00559fa0(0x15,0x41c80000);
            FUN_0055b980(0,0x15,0x41c80000);
            bVar1 = true;
            if (DAT_00b9b8f1 == 0) {
              DAT_00b9b8f1 = (char)param_1[0x51] + 0x18;
            }
          }
          fVar5 = (float10)FUN_00558e40(0x17);
          if ((fVar5 <= (float10)DAT_00858b50) ||
             (((short)param_1[0x51] <= (short)(ushort)DAT_00b9b8f1 && (DAT_00b9b8f1 != 0)))) {
            if (!bVar1) {
              *(float *)(*param_1 + 0x540) = *(float *)(*param_1 + 0x540) - _FUN_00858ca0;
            }
          }
          else {
            FUN_00559fa0(0x17,0x41c80000);
            FUN_0055b980(0,0x17,0x41c80000);
          }
        }
      }
      if (DAT_00b70153 != DAT_00b9b8f2) {
        DAT_00b9b8f2 = DAT_00b70153;
      }
    }
  }
  return;
}



/* function 0056f330 FUN_0056f330 */

void __fastcall FUN_0056f330(undefined4 *param_1)

{
  uint *puVar1;
  
  *param_1 = 0;
  param_1[0x2c] = 0;
  if (param_1[0x2d] != 0) {
    puVar1 = (uint *)(param_1[0x2d] + 0x40);
    *puVar1 = *puVar1 & 0xfbffffff;
    param_1[0x2d] = 0;
  }
  param_1[0x2f] = 0;
  param_1[0x2e] = 0;
  *(undefined1 *)(param_1 + 0x37) = 0;
  *(undefined2 *)(param_1 + 0x4c) = 0;
  param_1[0x4d] = 0x3f800000;
  *(undefined1 *)((int)param_1 + 0xdd) = 0;
  *(undefined1 *)((int)param_1 + 0xde) = 0;
  *(undefined1 *)((int)param_1 + 0xdf) = 0;
  *(undefined1 *)((int)param_1 + 0xd5) = 0;
  *(undefined1 *)(param_1 + 0x35) = 0;
  param_1[0x33] = 0;
  param_1[0x34] = DAT_00b7cb84;
  *(undefined1 *)(param_1 + 0x54) = 100;
  *(undefined1 *)((int)param_1 + 0x14f) = 100;
  *(undefined1 *)((int)param_1 + 0x153) = 1;
  param_1[0x30] = 0;
  param_1[0x31] = 3;
  param_1[0x39] = 0;
  param_1[0x3a] = 0;
  param_1[0x3b] = 0;
  param_1[0x3d] = 0;
  param_1[0x3c] = 0;
  param_1[0x3e] = 0;
  param_1[0x3f] = 0;
  param_1[0x40] = 0;
  param_1[0x41] = 0;
  param_1[0x42] = 0;
  param_1[0x43] = 0;
  param_1[0x44] = 0;
  param_1[0x45] = 0;
  param_1[0x46] = 0;
  param_1[0x47] = 0;
  param_1[0x48] = 0;
  param_1[0x49] = 0;
  param_1[0x4a] = 0;
  param_1[0x4b] = 0;
  *(undefined1 *)(param_1 + 0x53) = 0;
  *(undefined1 *)((int)param_1 + 0x14d) = 0;
  *(undefined1 *)((int)param_1 + 0x14e) = 0;
  *(undefined1 *)((int)param_1 + 0x151) = 0;
  *(undefined1 *)((int)param_1 + 0x152) = 0;
  param_1[0x4e] = 0;
  param_1[0x4f] = 0;
  param_1[0x50] = 0;
  *(undefined2 *)(&DAT_00b7cedc + (uint)DAT_00b7cd74 * 400) = 0;
  *(undefined2 *)((int)param_1 + 0x156) = 1;
  param_1[0x52] = 0;
  *(undefined1 *)(param_1 + 0x55) = 0;
  *(undefined1 *)(param_1 + 0x56) = 0;
  param_1[99] = 0;
  if (*(char *)(param_1 + 0x62) != '\0') {
    thunk_FUN_0156cf30();
    if (*(char *)(param_1 + 0x62) != '\0') {
      FUN_00409c10(0x173);
      *(undefined1 *)(param_1 + 0x62) = 0;
      param_1[99] = 0;
    }
  }
  return;
}



/* function 00571317 FUN_00571317 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00571317(int param_1)

{
  int *piVar1;
  float fVar2;
  char cVar3;
  undefined4 uVar4;
  float *pfVar5;
  undefined4 *puVar6;
  int iVar7;
  int *unaff_EBX;
  uint unaff_EBP;
  int *unaff_ESI;
  short in_stack_0000001c;
  float in_stack_00000020;
  undefined4 in_stack_00000024;
  float in_stack_00000030;
  void *in_stack_00000058;
  undefined4 in_stack_00000068;
  
  piVar1 = (int *)(&DAT_00b7cd98)[param_1 * 100];
  if ((piVar1 == unaff_EBX) || ((piVar1[0x11b] & unaff_EBP) == 0)) {
    iVar7 = 0;
  }
  else {
    iVar7 = piVar1[0x163];
  }
  if (DAT_00858b50 <
      *(float *)(iVar7 + 0x4c) * *(float *)(iVar7 + 0x4c) +
      *(float *)(iVar7 + 0x48) * *(float *)(iVar7 + 0x48) +
      *(float *)(iVar7 + 0x44) * *(float *)(iVar7 + 0x44)) {
    uVar4 = FUN_006d1080();
    switch(uVar4) {
    case 2:
      piVar1 = (int *)(&DAT_00b7cd98)[(uint)DAT_00b7cd74 * 100];
      if ((piVar1 == unaff_EBX) || ((piVar1[0x11b] & unaff_EBP) == 0)) {
        iVar7 = 0;
      }
      else {
        iVar7 = piVar1[0x163];
      }
      if (*(int *)(iVar7 + 0x594) != 10) {
        piVar1 = (int *)(&DAT_00b7cd98)[(uint)DAT_00b7cd74 * 100];
        if ((piVar1 == unaff_EBX) || ((piVar1[0x11b] & unaff_EBP) == 0)) {
          FUN_0055cd60(0);
        }
        else {
          FUN_0055cd60(piVar1[0x163]);
        }
      }
      break;
    case 3:
    case 5:
      piVar1 = (int *)(&DAT_00b7cd98)[(uint)DAT_00b7cd74 * 100];
      if ((piVar1 == unaff_EBX) || ((piVar1[0x11b] & unaff_EBP) == 0)) {
        FUN_0055cc00(0);
      }
      else {
        FUN_0055cc00(piVar1[0x163]);
      }
      break;
    case 4:
      break;
    default:
      piVar1 = (int *)(&DAT_00b7cd98)[(uint)DAT_00b7cd74 * 100];
      if ((piVar1 == unaff_EBX) || ((piVar1[0x11b] & unaff_EBP) == 0)) {
        FUN_0055cac0(0);
      }
      else {
        FUN_0055cac0(piVar1[0x163]);
      }
    }
  }
  if (*(int **)(*unaff_ESI + 0x480) == unaff_EBX) {
    iVar7 = 0;
  }
  else {
    iVar7 = **(int **)(*unaff_ESI + 0x480);
  }
  if ((*(int **)(iVar7 + 0x2c) == unaff_EBX) || (cVar3 = thunk_FUN_0156aa10(), cVar3 != '\0')) {
    unaff_ESI[0x52] = (int)unaff_EBX;
  }
  else {
    in_stack_00000030 = DAT_00858b50;
    if ((_DAT_00b9b9a0 & 1) == 0) {
      _DAT_00b9b9a0 = _DAT_00b9b9a0 | 1;
    }
    if (DAT_00b7cb84 / 20000 != DAT_00b7cb78 / 20000) {
      pfVar5 = (float *)FUN_0056e010(&stack0x00000034,0xffffffff);
      DAT_008cdf21 = _DAT_0085862c <=
                     SQRT((_DAT_00b9b994 - *pfVar5) * (_DAT_00b9b994 - *pfVar5) +
                          (_DAT_00b9b998 - pfVar5[1]) * (_DAT_00b9b998 - pfVar5[1]) +
                          (_DAT_00b9b99c - pfVar5[2]) * (_DAT_00b9b99c - pfVar5[2]));
      pfVar5 = (float *)FUN_0056e010(&stack0x00000034,0xffffffff);
      _DAT_00b9b994 = *pfVar5;
      _DAT_00b9b998 = pfVar5[1];
      _DAT_00b9b99c = pfVar5[2];
      puVar6 = (undefined4 *)FUN_0056e010(&stack0x0000004c,0xffffffff);
      FUN_0044f460(&stack0x0000001c,*puVar6,puVar6[1],puVar6[2],unaff_EBX,0x42700000,1,unaff_EBX,
                   unaff_EBX,unaff_EBX,unaff_EBX);
      DAT_008cdf20 = in_stack_0000001c != -1;
    }
    if (*(int **)(*unaff_ESI + 0x480) == unaff_EBX) {
      iVar7 = 0;
    }
    else {
      iVar7 = **(int **)(*unaff_ESI + 0x480);
    }
    fVar2 = in_stack_00000030;
    switch(*(undefined4 *)(iVar7 + 0x2c)) {
    case 1:
      fVar2 = _DAT_00863e28;
      break;
    case 2:
      fVar2 = _DAT_0086503c;
      break;
    case 3:
      fVar2 = _DAT_00865038;
      break;
    case 4:
      fVar2 = _DAT_00859f80;
      break;
    case 5:
      fVar2 = _DAT_00858b58;
      break;
    case 6:
      fVar2 = _DAT_00858c4c;
    }
    in_stack_00000020 = (fVar2 - (float)unaff_ESI[0x52]) * DAT_00b7cb5c * _DAT_00858fc4;
    if ((in_stack_00000020 < DAT_00858b50) ||
       ((((DAT_008cdf21 != '\0' && (DAT_008cdf20 != '\0')) &&
         (cVar3 = FUN_0072dd50(), cVar3 == '\0')) &&
        ((cVar3 = FUN_0072dd60(), cVar3 == '\0' && (DAT_00b72914 == unaff_EBX)))))) {
      unaff_ESI[0x52] = (int)(in_stack_00000020 + (float)unaff_ESI[0x52]);
    }
  }
  FUN_0056ec80(in_stack_00000068,in_stack_00000024);
  iVar7 = unaff_ESI[0x2e];
  if (0x3b9ac9fe < iVar7) {
    iVar7 = 999999999;
  }
  unaff_ESI[0x2e] = iVar7;
  iVar7 = unaff_ESI[0x2f];
  if (0x3b9ac9fe < iVar7) {
    iVar7 = 999999999;
  }
  unaff_ESI[0x2f] = iVar7;
  ExceptionList = in_stack_00000058;
  return;
}



/* function 00592aa0 FUN_00592aa0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall
FUN_00592aa0(int param_1,int param_2,int param_3,float param_4,int param_5,int param_6,int param_7,
            uint *param_8,uint *param_9,char param_10)

{
  uint *puVar1;
  byte bVar2;
  float fVar3;
  float fVar4;
  char cVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  undefined4 uVar9;
  int iVar10;
  int *piVar11;
  uint local_2b4;
  int iStack_2b0;
  uint local_2ac;
  undefined1 auStack_298 [48];
  float fStack_268;
  float fStack_264;
  float fStack_260;
  undefined4 uStack_258;
  undefined4 uStack_254;
  undefined1 auStack_250 [68];
  undefined4 local_20c;
  undefined4 local_208;
  undefined1 auStack_204 [60];
  undefined4 uStack_1c8;
  undefined4 uStack_1c4;
  undefined1 auStack_1bc [64];
  undefined4 local_17c;
  undefined4 local_178;
  undefined1 local_174 [64];
  undefined4 local_134;
  undefined4 local_130;
  undefined1 auStack_12c [64];
  undefined4 local_ec;
  undefined4 local_e8 [18];
  undefined1 auStack_a0 [4];
  undefined1 auStack_9c [68];
  undefined1 auStack_58 [4];
  undefined1 auStack_54 [72];
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0083d001;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  iVar6 = FUN_004a8ec0();
  if (iVar6 < 1) goto LAB_005930e2;
  if ((param_7 == 1) || (param_7 == 3)) {
    uVar7 = (uint)*(byte *)(param_2 + 0xd);
    uVar8 = (uint)*(byte *)(param_2 + 0xc);
    local_2b4 = uVar7;
    local_2ac = uVar8;
  }
  else {
    uVar7 = (uint)*(byte *)(param_2 + 0xc);
    uVar8 = (uint)*(byte *)(param_2 + 0xd);
    local_2b4 = uVar8;
    local_2ac = uVar7;
  }
  if (((param_6 == 1) && (param_10 == '\0')) &&
     (cVar5 = FUN_00591680(param_3,param_4,uVar7,uVar8,*(undefined1 *)(param_2 + 0x10)),
     cVar5 == '\0')) goto LAB_005930e2;
  local_20c = 0;
  local_208 = 0;
  local_4 = 0;
  if (*(char *)(param_2 + 0x13) == '\0') {
    FUN_0059ae70();
  }
  else {
    local_134 = 0;
    local_130 = 0;
    fVar3 = _DAT_00858b8c - (float)local_2b4 * _DAT_00858b8c;
    fVar4 = _DAT_00858b8c - (float)local_2ac * _DAT_00858b8c;
    local_ec = 0;
    local_e8[0] = 0;
    local_17c = 0;
    local_178 = 0;
    local_4._0_1_ = 3;
    local_4._1_3_ = 0;
    FUN_0059ae70();
    FUN_0059af40(fVar4,fVar3,0);
    FUN_0059ae70();
    local_2ac = FUN_00407180(-(uint)*(byte *)(param_2 + 0x13),(uint)*(byte *)(param_2 + 0x13));
    FUN_0059b390((float)(int)local_2ac * _DAT_008595ec);
    FUN_0059ae70();
    FUN_0059af40(-fVar4,-fVar3,0);
    uVar9 = FUN_0059be30(auStack_54,auStack_1bc,auStack_12c);
    local_4._0_1_ = 4;
    uVar9 = FUN_0059be30(auStack_9c,uVar9,local_174);
    local_4 = CONCAT31(local_4._1_3_,5);
    FUN_0059bbc0(uVar9);
    puStack_8._0_1_ = 4;
    FUN_0059acd0();
    puStack_8._0_1_ = 3;
    FUN_0059acd0();
    puStack_8._0_1_ = 2;
    FUN_0059acd0();
    puStack_8._0_1_ = 1;
    FUN_0059acd0();
    puStack_8 = (undefined1 *)((uint)puStack_8._1_3_ << 8);
    FUN_0059acd0();
  }
  FUN_0059c050(param_1 + 0x18,0);
  uStack_258 = 0;
  uStack_254 = 0;
  uStack_1c8 = 0;
  uStack_1c4 = 0;
  puStack_8._0_1_ = 8;
  FUN_0059ae70();
  FUN_0059b390((float)param_6 * _DAT_00858fe4);
  iVar6 = 0;
  iStack_2b0 = 0;
  if (param_6 == 1) {
    iVar6 = uVar7 - 1;
  }
  else if (param_6 == 2) {
    iVar6 = uVar7 - 1;
    iStack_2b0 = local_2ac - 1;
  }
  else if (param_6 == 3) {
    iStack_2b0 = local_2ac - 1;
  }
  if ((param_5 == 1) || (param_5 == 2)) {
    iVar10 = *(int *)(param_1 + 0x14);
    bVar2 = *(byte *)(iVar10 + 2);
    fVar3 = (float)(int)-(uint)*(byte *)(iVar10 + 4) * _DAT_00858b8c + param_4;
    fVar4 = (float)(int)-(uint)*(byte *)(iVar10 + 3) * _DAT_00858b8c + (float)iStack_2b0 +
            (float)param_3;
LAB_00592e7a:
    fStack_268 = fStack_268 +
                 (float)(int)-(uint)bVar2 * _DAT_00858b8c + (float)iVar6 + (float)param_2 +
                 _DAT_00858b8c;
    fStack_264 = fStack_264 + fVar4 + _DAT_00858b8c;
    fStack_260 = fStack_260 + fVar3;
  }
  else if (param_5 == 0) {
    iVar10 = *(int *)(param_1 + 0x14);
    bVar2 = *(byte *)(iVar10 + 2);
    fVar3 = (float)*(byte *)(iVar10 + 4) * _DAT_00858b8c - param_4;
    fVar4 = (float)(int)-(uint)*(byte *)(iVar10 + 3) * _DAT_00858b8c + (float)iStack_2b0 +
            (float)param_3;
    goto LAB_00592e7a;
  }
  uVar9 = FUN_0059be30(auStack_a0,local_e8,auStack_298);
  puStack_8._0_1_ = 9;
  uVar9 = FUN_0059be30(auStack_58,uVar9,auStack_250);
  puStack_8 = (undefined1 *)CONCAT31(puStack_8._1_3_,10);
  FUN_0059bbc0(uVar9);
  local_4._0_1_ = 9;
  FUN_0059acd0();
  local_4._0_1_ = 8;
  FUN_0059acd0();
  iVar6 = FUN_004a8e70();
  if (iVar6 != 0) {
    iVar10 = FUN_00404090(0x38);
    local_4._0_1_ = 0xb;
    if (iVar10 == 0) {
      piVar11 = (int *)0x0;
    }
    else {
      piVar11 = (int *)thunk_FUN_0156cfd0();
    }
    *(int **)(iVar6 + 8) = piVar11;
    local_4 = CONCAT31(local_4._1_3_,8);
    (**(code **)(*piVar11 + 0x18))(*(undefined2 *)(param_2 + 8));
    FUN_0054f610(auStack_204);
    *(undefined1 *)(*(int *)(iVar6 + 8) + 0x2f) = *(undefined1 *)(param_1 + 0x10);
    puVar1 = (uint *)(*(int *)(iVar6 + 8) + 0x1c);
    *puVar1 = *puVar1 | 0x10000;
    puVar1 = (uint *)(*(int *)(iVar6 + 8) + 0x1c);
    *puVar1 = *puVar1 | 0x400000;
    FUN_00563220(*(undefined4 *)(iVar6 + 8));
    *(undefined2 *)(iVar6 + 0xc) = (undefined2)param_3;
    *(undefined2 *)(iVar6 + 0xe) = param_4._0_2_;
    FUN_004a8df0(iVar6);
    if (param_6 == 1) {
      if (*(char *)(param_2 + 0x11) == '\0') {
        uVar9 = 5;
      }
      else {
        uVar9 = 6;
      }
      FUN_00591700(param_3,param_4,uVar7,uVar8,uVar9,1);
    }
    *param_8 = uVar7;
    *param_9 = uVar8;
    uVar9 = *(undefined4 *)(iVar6 + 8);
    local_4._0_1_ = 7;
    FUN_0059acd0();
    local_4._0_1_ = 6;
    FUN_0059acd0();
    local_4 = (uint)local_4._1_3_ << 8;
    FUN_0059acd0();
    local_4 = 0xffffffff;
    FUN_0059acd0();
    ExceptionList = local_c;
    return uVar9;
  }
  local_4._0_1_ = 7;
  FUN_0059acd0();
  local_4._0_1_ = 6;
  FUN_0059acd0();
  local_4 = (uint)local_4._1_3_ << 8;
  FUN_0059acd0();
  local_4 = 0xffffffff;
  FUN_0059acd0();
LAB_005930e2:
  *param_8 = 0;
  *param_9 = 0;
  ExceptionList = local_c;
  return 0;
}



/* function 0059f840 FUN_0059f840 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0059f840(int *param_1)

{
  short sVar1;
  char cVar2;
  ushort uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  *(byte *)((int)param_1 + 0x36) = *(byte *)((int)param_1 + 0x36) & 0xfc | 4;
  param_1[0x58] = (int)&DAT_00bb4a90;
  *(undefined1 *)(param_1 + 0x51) = 0;
  *(undefined1 *)((int)param_1 + 0x145) = 0;
  *(undefined1 *)(param_1 + 0x4f) = 1;
  (**(code **)(*param_1 + 0x10))(1);
  uVar4 = param_1[0x50] & 0xfc040000U | 0x40000;
  param_1[0x50] = uVar4;
  if (*(short *)((int)param_1 + 0x22) == -1) {
    param_1[0x50] = uVar4;
  }
  else {
    FUN_005a2d00((int)*(short *)((int)param_1 + 0x22),param_1);
    iVar6 = *(int *)((&DAT_00a9b0c8)[*(short *)((int)param_1 + 0x22)] + 0x14);
    if ((*(byte *)(iVar6 + 0x29) & 1) != 0) {
      thunk_FUN_01569960(*(undefined1 *)(iVar6 + 0x28));
      param_1[0x50] = param_1[0x50] | 0x10000;
    }
    iVar5 = (**(code **)(*(int *)(&DAT_00a9b0c8)[*(short *)((int)param_1 + 0x22)] + 4))();
    if ((iVar5 != 0) &&
       (((uVar3 = *(ushort *)(iVar5 + 0x12) & 0x7800, uVar3 == 0x800 || (uVar3 == 0x1000)) &&
        ((*(byte *)(param_1 + 0x10) & 4) == 0)))) {
      param_1[0x2b] =
           (int)((*(float *)(iVar6 + 0x14) - *(float *)(iVar6 + 8)) * _DAT_00858cc4 +
                *(float *)(iVar6 + 8));
    }
  }
  if ((*(byte *)(param_1 + 0x10) & 0x20) != 0) {
    iVar6 = FUN_00535300();
    if (*(undefined2 **)(iVar6 + 0x2c) != (undefined2 *)0x0) {
      **(undefined2 **)(iVar6 + 0x2c) = 0;
    }
  }
  sVar1 = *(short *)((int)param_1 + 0x22);
  param_1[0x55] = 0x447a0000;
  param_1[0x56] = -0x3b85c000;
  param_1[0x54] = 0;
  *(undefined1 *)((int)param_1 + 0x13d) = 0;
  *(undefined2 *)((int)param_1 + 0x13e) = 0;
  *(undefined1 *)((int)param_1 + 0x14d) = 0;
  *(undefined1 *)(param_1 + 0x53) = 0;
  *(undefined2 *)((int)param_1 + 0x14a) = 0xffff;
  *(undefined1 *)((int)param_1 + 0x147) = 0xff;
  *(undefined1 *)(param_1 + 0x52) = 0xff;
  param_1[0x59] = 0;
  if ((int)sVar1 == (uint)DAT_008cd608) {
    param_1[0x10] = param_1[0x10] | 0x8000000;
  }
  if (sVar1 != -1) {
    cVar2 = (**(code **)(*(int *)(&DAT_00a9b0c8)[sVar1] + 0x10))();
    if (cVar2 == '\x04') {
      param_1[7] = param_1[7] | 0x10000000;
    }
  }
  uVar4 = (uint)*(short *)((int)param_1 + 0x22);
  if (((((uVar4 == DAT_008cd4fc) || (uVar4 == DAT_008cd614)) ||
       ((uVar4 == DAT_008cd518 || ((uVar4 == DAT_008cd51c || (uVar4 == DAT_008cd520)))))) ||
      (uVar4 == DAT_008cd524)) || ((uVar4 == DAT_008cd504 || (uVar4 == DAT_008cd500)))) {
LAB_0059fa77:
    uVar4 = param_1[0x50] | 0x100;
  }
  else {
    if (*(short *)((int)param_1 + 0x22) != -1) {
      iVar6 = (**(code **)(*(int *)(&DAT_00a9b0c8)[uVar4] + 4))();
      if (iVar6 != 0) {
        (**(code **)(*(int *)(&DAT_00a9b0c8)[*(short *)((int)param_1 + 0x22)] + 4))();
        iVar6 = thunk_FUN_0156c780();
        if (iVar6 != 0) goto LAB_0059fa77;
      }
    }
    uVar4 = param_1[0x50] & 0xfffffeff;
  }
  param_1[0x50] = uVar4;
  param_1[0x50] = uVar4 & 0xfffffdff;
  uVar4 = (uint)*(short *)((int)param_1 + 0x22);
  *(undefined1 *)((int)param_1 + 0x2f) = 0xd;
  *(undefined2 *)((int)param_1 + 0x16a) = 0xffff;
  param_1[0x5b] = 0;
  param_1[0x10] = param_1[0x10] & 0xfdffffff;
  param_1[0x4e] = 0;
  if (((((uVar4 != DAT_008cd6ac) && (uVar4 != DAT_008cd6b0)) && (uVar4 != DAT_008cd6b4)) &&
      ((uVar4 != DAT_008cd6b8 && (uVar4 != DAT_008cd6bc)))) &&
     ((uVar4 != DAT_008cd6c0 && (uVar4 != DAT_008cd6c4)))) {
    cVar2 = FUN_00448af0(uVar4);
    if (cVar2 == '\0') goto LAB_0059fb1d;
  }
  FUN_0059f400();
LAB_0059fb1d:
  param_1[0x5d] = 0;
  param_1[0x57] = 0x3f800000;
  *(undefined1 *)((int)param_1 + 0x149) = 0x48;
  *(undefined2 *)(param_1 + 0x5a) = 0xffff;
  return;
}



/* function 005a0d96 FUN_005a0d96 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall
FUN_005a0d96(int *param_1,float param_2,int param_3,undefined4 param_4,int param_5,int param_6)

{
  float fVar1;
  char cVar2;
  byte bVar3;
  void *in_EAX;
  int iVar4;
  undefined4 *puVar5;
  int *piVar6;
  bool bVar7;
  undefined4 uVar8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined1 auStack_a0 [12];
  undefined1 auStack_94 [72];
  undefined1 auStack_4c [64];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0083d26b;
  ExceptionList = &local_c;
  if ((*(byte *)(param_1 + 7) & 1) == 0) {
    ExceptionList = in_EAX;
    return;
  }
  if (((param_6 == 0x37) && (param_5 != 0)) && ((*(byte *)(param_5 + 0x36) & 7) == 2)) {
    param_6 = 0x32;
  }
  local_c = in_EAX;
  cVar2 = FUN_005448b0(param_6,0);
  if (cVar2 == '\0') {
    ExceptionList = local_c;
    return;
  }
  fVar1 = (float)param_1[0x55] - param_2 * *(float *)(param_1[0x58] + 0x18);
  param_1[0x55] = (int)fVar1;
  if (fVar1 < DAT_00858b50) {
    param_1[0x55] = 0;
  }
  if ((char)param_1[0x51] == '\0') {
    ExceptionList = local_c;
    return;
  }
  if ((((param_1[0x10] & 0x400000U) != 0) && (iVar4 = FUN_0056e210(0xffffffff), param_5 != iVar4))
     && (iVar4 = FUN_0056e0d0(0xffffffff,0), param_5 != iVar4)) {
    ExceptionList = local_c;
    return;
  }
  if ((int)*(short *)((int)param_1 + 0x22) == (uint)DAT_008cd748) {
    if (param_5 == 0) {
      ExceptionList = local_c;
      return;
    }
    bVar3 = *(byte *)(param_5 + 0x36) & 7;
    if (bVar3 == 3) {
      if ((*(uint *)(param_5 + 0x46c) & 0x100) == 0) {
        ExceptionList = local_c;
        return;
      }
      iVar4 = *(int *)(param_5 + 0x58c);
      if (iVar4 == 0) {
        ExceptionList = local_c;
        return;
      }
    }
    else {
      iVar4 = param_5;
      if (bVar3 != 2) {
        ExceptionList = local_c;
        return;
      }
    }
    if (iVar4 == 0) {
      ExceptionList = local_c;
      return;
    }
    if (*(short *)(iVar4 + 0x22) != 0x259) {
      ExceptionList = local_c;
      return;
    }
  }
  if ((param_5 != 0) && (*(short *)(param_5 + 0x22) == 0x212)) {
    ExceptionList = local_c;
    return;
  }
  iVar4 = param_1[0x58];
  *(char *)(param_1 + 0x52) = (char)param_6;
  bVar7 = false;
  if ((param_2 * *(float *)(iVar4 + 0x18) <= _DAT_00858a28) &&
     ((float)param_1[0x55] != DAT_00858b50)) goto LAB_005a10c3;
  switch((char)param_1[0x51]) {
  case '\x01':
    if ((param_1[7] & 0x200U) == 0) {
      bVar7 = true;
      (**(code **)(*param_1 + 0x20))();
    }
LAB_005a10b4:
    param_1[7] = param_1[7] | 0x200;
    break;
  case '\x14':
    param_1[7] = param_1[7] & 0xffffff7e;
    cVar2 = thunk_FUN_015619f0();
    if (cVar2 == '\0') {
      FUN_00542860();
    }
    param_1[7] = param_1[7] | 4;
    param_1[0x10] = param_1[0x10] | 0x800000;
    param_1[0x11] = 0;
    param_1[0x12] = 0;
    param_1[0x13] = 0;
    param_1[0x14] = 0;
    param_1[0x15] = 0;
    param_1[0x16] = 0;
    (**(code **)(*param_1 + 0x20))();
    bVar7 = true;
    break;
  case '\x15':
    if ((param_1[7] & 0x200U) == 0) {
      (**(code **)(*param_1 + 0x20))();
      goto LAB_005a10b4;
    }
    param_1[7] = param_1[7] & 0xffffff7e;
    cVar2 = thunk_FUN_015619f0();
    if (cVar2 == '\0') {
      FUN_00542860();
    }
    param_1[7] = param_1[7] | 4;
    param_1[0x10] = param_1[0x10] | 0x800000;
    param_1[0x11] = 0;
    param_1[0x12] = 0;
    param_1[0x13] = 0;
    param_1[0x14] = 0;
    param_1[0x15] = 0;
    param_1[0x16] = 0;
    (**(code **)(*param_1 + 0x20))();
    bVar7 = true;
    break;
  case -0x38:
  case -0x36:
    local_c4 = *(undefined4 *)(iVar4 + 0x38);
    local_c0 = *(undefined4 *)(iVar4 + 0x3c);
    local_bc = *(undefined4 *)(iVar4 + 0x40);
    bVar7 = param_2 * *(float *)(iVar4 + 0x18) <= *(float *)(iVar4 + 0x34) * _DAT_00858a28;
    if (bVar7) {
      uVar8 = *(undefined4 *)(iVar4 + 0x44);
    }
    else {
      uVar8 = *(undefined4 *)(iVar4 + 0x44);
    }
    FUN_0059e9b0(param_1,&local_c4,uVar8,!bVar7);
    param_1[7] = param_1[7] & 0xffffff7e;
    cVar2 = thunk_FUN_015619f0();
    if (cVar2 == '\0') {
      FUN_00542860();
    }
    param_1[7] = param_1[7] | 4;
    param_1[0x10] = param_1[0x10] | 0x800000;
    param_1[0x11] = 0;
    param_1[0x12] = 0;
    param_1[0x13] = 0;
    param_1[0x14] = 0;
    param_1[0x15] = 0;
    param_1[0x16] = 0;
    param_1[0x50] = param_1[0x50] | 0x400;
    (**(code **)(*param_1 + 0x20))();
    bVar7 = true;
  }
  if ((*(byte *)(param_1 + 7) & 0x81) == 0) {
    param_1[0x55] = 0;
  }
LAB_005a10c3:
  if (bVar7) {
    cVar2 = FUN_0059f2d0();
    FUN_00506ed0(param_1);
    if (cVar2 != '\0') {
      ExceptionList = local_c;
      return;
    }
  }
  cVar2 = *(char *)(param_1[0x58] + 0x20);
  if (cVar2 != '\0') {
    if (cVar2 != '\x03') {
      if (bVar7) {
        bVar7 = cVar2 == '\x02';
      }
      else {
        if (cVar2 != '\x01') {
          ExceptionList = local_c;
          return;
        }
        bVar7 = _DAT_00858ca4 < param_2;
      }
      if (!bVar7) {
        ExceptionList = local_c;
        return;
      }
    }
    if (_DAT_0085ab78 <= *(float *)(param_1[0x58] + 0x24)) {
      FUN_0059bcf0(param_1[5]);
      iVar4 = param_1[0x58];
      uStack_ac = *(undefined4 *)(iVar4 + 0x24);
      uStack_a8 = *(undefined4 *)(iVar4 + 0x28);
      uStack_a4 = *(undefined4 *)(iVar4 + 0x2c);
      uStack_4 = 0;
      puVar5 = (undefined4 *)FUN_0059c790(auStack_a0,auStack_94,&uStack_ac);
      uStack_b8 = *puVar5;
      uStack_b4 = puVar5[1];
      uStack_b0 = puVar5[2];
      if (param_1[5] == 0) {
        piVar6 = param_1 + 1;
      }
      else {
        piVar6 = (int *)(param_1[5] + 0x30);
      }
      FUN_00411a00(piVar6);
      iVar4 = thunk_FUN_0040183f(*(undefined4 *)(param_1[0x58] + 0x30),&uStack_b8,0,0);
      uStack_4 = 0xffffffff;
      FUN_0059acd0();
    }
    else {
      if (param_3 == 0) {
        ExceptionList = local_c;
        return;
      }
      FUN_0049e950(auStack_4c,param_3,param_4);
      iVar4 = FUN_004a95c0(*(undefined4 *)(param_1[0x58] + 0x30),auStack_4c,0,0);
    }
    if (iVar4 != 0) {
      FUN_004aa3d0();
    }
  }
  ExceptionList = local_c;
  return;
}



/* function 005a2d00 FUN_005a2d00 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_005a2d00(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  float *pfVar5;
  
  if (*(short *)((&DAT_00a9b0c8)[param_1] + 0x10) == -1) {
    *(undefined4 *)(param_2 + 0x8c) = 0x47c34f80;
    *(undefined4 *)(param_2 + 0x90) = 0x47c34f80;
    *(undefined4 **)(param_2 + 0x160) = &DAT_00bb4a90;
    *(uint *)(param_2 + 0x40) = *(uint *)(param_2 + 0x40) & 0xfffffffd | 0x80000c;
  }
  else {
    iVar2 = (int)*(short *)((&DAT_00a9b0c8)[param_1] + 0x10);
    iVar4 = iVar2 * 0x50;
    pfVar5 = (float *)(&DAT_00bb4a90 + iVar2 * 0x14);
    *(float **)(param_2 + 0x160) = pfVar5;
    *(float *)(param_2 + 0x8c) = *pfVar5;
    *(undefined4 *)(param_2 + 0x90) = (&DAT_00bb4a94)[iVar2 * 0x14];
    *(undefined4 *)(param_2 + 0x98) = (&DAT_00bb4a98)[iVar2 * 0x14];
    *(undefined4 *)(param_2 + 0x9c) = (&DAT_00bb4a9c)[iVar2 * 0x14];
    *(undefined4 *)(param_2 + 0xa0) = (&DAT_00bb4aa0)[iVar2 * 0x14];
    *(undefined1 *)(param_2 + 0x144) = (&DAT_00bb4aac)[iVar4];
    if (_DAT_00863c08 <= *pfVar5) {
      uVar3 = *(uint *)(param_2 + 0x40) & 0xfffffffd;
      *(uint *)(param_2 + 0x40) = uVar3 | 0xc;
      if ((&DAT_00bb4aac)[iVar4] == '\0') {
        *(uint *)(param_2 + 0x40) = uVar3 | 0x80000c;
      }
    }
    cVar1 = (&DAT_00bb4aad)[iVar4];
    if (cVar1 == '\x06') {
      *(uint *)(param_2 + 0x40) = *(uint *)(param_2 + 0x40) | 0x20;
      *(uint *)(param_2 + 0x140) = *(uint *)(param_2 + 0x140) & 0xffff3fff;
      return;
    }
    if (cVar1 == '\a') {
      *(uint *)(param_2 + 0x40) = *(uint *)(param_2 + 0x40) | 0x2c;
      *(uint *)(param_2 + 0x140) = *(uint *)(param_2 + 0x140) & 0xffff7fff | 0x4000;
      return;
    }
    if (cVar1 == '\b') {
      *(uint *)(param_2 + 0x40) = *(uint *)(param_2 + 0x40) | 0x40;
      FUN_005a2cb0(0,0,*(float *)(*(int *)((&DAT_00a9b0c8)[param_1] + 0x14) + 8) * _DAT_00858c98);
      return;
    }
    if (cVar1 == '\t') {
      *(uint *)(param_2 + 0x40) = *(uint *)(param_2 + 0x40) & 0xfffffffd | 0x80;
      return;
    }
  }
  return;
}



/* function 005bc533 FUN_005bc533 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_005bc533(int param_1)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  undefined4 in_EAX;
  int iVar4;
  undefined4 *unaff_EBP;
  int unaff_ESI;
  undefined4 *puVar5;
  
  puVar5 = unaff_EBP;
  for (; param_1 != 0; param_1 = param_1 + -1) {
    *puVar5 = in_EAX;
    puVar5 = puVar5 + 1;
  }
  *(undefined4 *)(unaff_ESI + 0x954) = 0;
  thunk_FUN_004010f8();
  *(undefined1 *)(unaff_ESI + 0x27) = 0;
  *(undefined1 *)(unaff_ESI + 0x3e) = 0;
  *(undefined4 *)(unaff_ESI + 0x140) = 0;
  *(undefined1 *)(unaff_ESI + 0x1c) = 0;
  FUN_0050e490();
  FUN_0050e490();
  FUN_0050e490();
  fVar2 = _DAT_0086a46c - DAT_0086a468;
  *(undefined2 *)(unaff_ESI + 0x180) = 4;
  *(undefined2 *)(unaff_ESI + 0x3b8) = 4;
  fVar3 = DAT_0086a468;
  *(float *)(unaff_ESI + 0x274) = fVar2;
  *(undefined1 *)(unaff_ESI + 0x41) = 0;
  *(undefined1 *)(unaff_ESI + 0x42) = 0;
  *(undefined1 *)(unaff_ESI + 0x43) = 0;
  *(undefined1 *)(unaff_ESI + 0x44) = 1;
  *(undefined1 *)(unaff_ESI + 0x40) = 0;
  *(float *)(unaff_ESI + 0x270) = fVar3;
  *(undefined4 *)(unaff_ESI + 0x250) = 0xbf0ccccd;
  *(undefined4 *)(unaff_ESI + 0x254) = 0x3fc00000;
  *(undefined4 *)(unaff_ESI + 600) = 0x40666666;
  *(undefined4 *)(unaff_ESI + 0x25c) = 0x3d75c28f;
  *(undefined4 *)(unaff_ESI + 0x260) = 0xbdcccccd;
  *(undefined4 *)(unaff_ESI + 0x264) = 0;
  *(undefined4 *)(unaff_ESI + 0x268) = 0xbd8f5c29;
  *(undefined4 *)(unaff_ESI + 0x26c) = 0x3f668113;
  *(undefined1 *)(unaff_ESI + 0x2d) = 0;
  FUN_0050ab10();
  *(undefined1 *)(unaff_ESI + 0x22) = 0;
  *(undefined4 *)(unaff_ESI + 0x390) = 0;
  *(undefined4 *)(unaff_ESI + 0x5c8) = 0;
  *(undefined4 *)(unaff_ESI + 0x800) = 0;
  *(undefined4 *)(unaff_ESI + 0x1c8) = 0;
  *(undefined4 *)(unaff_ESI + 0x1cc) = 0;
  *(undefined4 *)(unaff_ESI + 0x400) = 0;
  *(undefined4 *)(unaff_ESI + 0x404) = 0;
  *(undefined1 *)(unaff_ESI + 0x176) = 0;
  *(undefined1 *)(unaff_ESI + 0x3ae) = 0;
  *(undefined1 *)(unaff_ESI + 0x5e6) = 0;
  *(undefined4 *)(unaff_ESI + 0x39c) = 0;
  *(undefined4 *)(unaff_ESI + 0x5d4) = 0;
  *(undefined4 *)(unaff_ESI + 0x80c) = 0;
  *(undefined1 *)(unaff_ESI + 0x3f) = 0;
  *(undefined4 *)(unaff_ESI + 0xc10) = 0x3e800000;
  *(undefined4 *)(unaff_ESI + 0xc14) = 0x3f400000;
  *(undefined4 *)(unaff_ESI + 0xc20) = 0x3f59999a;
  *(undefined1 *)(unaff_ESI + 0x50) = 0;
  *(undefined4 *)(unaff_ESI + 0x5c) = 0;
  *(undefined4 *)(unaff_ESI + 300) = 0;
  *(undefined4 *)(unaff_ESI + 0xc34) = 0x1e;
  *(undefined1 *)(unaff_ESI + 0x25) = 0;
  *(undefined1 *)(unaff_ESI + 0x3a) = 0;
  *(undefined4 *)(unaff_ESI + 0x81c) = 0;
  *(undefined4 *)(unaff_ESI + 0x820) = 0;
  *(undefined1 *)(unaff_ESI + 0x26) = 0;
  *(undefined1 *)(unaff_ESI + 0x28) = 0;
  *(undefined4 *)(unaff_ESI + 0x138) = 0x3f666666;
  *(undefined1 *)(unaff_ESI + 0x31) = 0;
  *(undefined1 *)(unaff_ESI + 0x4f) = 0;
  *(undefined1 *)unaff_EBP = 0;
  piVar1 = (int *)(unaff_ESI + 0x958);
  *(undefined1 *)(unaff_ESI + 0x19) = 0;
  *(undefined2 *)(unaff_ESI + 0x46) = 0x32;
  *(undefined2 *)(unaff_ESI + 0x48) = 0x31;
  *(undefined2 *)(unaff_ESI + 0x4a) = 3;
  *(undefined2 *)(unaff_ESI + 0x4c) = 0x30;
  *(undefined1 *)(unaff_ESI + 0x3d) = 0;
  *(undefined4 *)(unaff_ESI + 0x134) = 0;
  *(undefined1 *)(unaff_ESI + 0x30) = 0;
  *(undefined4 *)(unaff_ESI + 0xb4) = 2;
  *(undefined4 *)(unaff_ESI + 200) = 2;
  *(undefined4 *)(unaff_ESI + 0xc0) = 0;
  *(undefined4 *)(unaff_ESI + 0xbc) = 0;
  *(undefined4 *)(unaff_ESI + 0xb8) = 0;
  *(undefined4 *)(unaff_ESI + 0xd4) = 0;
  *(undefined4 *)(unaff_ESI + 0xd0) = 0;
  *(undefined4 *)(unaff_ESI + 0xcc) = 0;
  *piVar1 = 0;
  iVar4 = FUN_0056e0d0(0xffffffff,0);
  if (iVar4 == 0) {
    *piVar1 = (&DAT_00b7cd98)[(uint)DAT_00b7cd74 * 100];
  }
  else {
    iVar4 = FUN_0056e0d0(0xffffffff,0);
    *piVar1 = iVar4;
  }
  if (*piVar1 != 0) {
    FUN_00571b70(piVar1);
  }
  *(undefined1 *)(unaff_ESI + 0x23) = 0;
  *(undefined4 *)(unaff_ESI + 0x144) = 0;
  *(undefined4 *)(unaff_ESI + 0x148) = 0;
  *(undefined1 *)(unaff_ESI + 0x3d) = 0;
  *(undefined1 *)(unaff_ESI + 0x3c) = 0;
  *(undefined1 *)(unaff_ESI + 0x56) = 0;
  *(undefined4 *)(unaff_ESI + 0x154) = 0x3f800000;
  *(undefined4 *)(unaff_ESI + 0x120) = 0;
  if (DAT_00ba67a5 == '\0') {
    *(undefined1 *)(unaff_ESI + 0x51) = 0;
    DAT_00c3efab = 0;
    *(undefined4 *)(unaff_ESI + 0xbfc) = 0;
    *(undefined1 *)(unaff_ESI + 0x52) = 0;
    *(undefined4 *)(unaff_ESI + 0xc08) = 0;
    *(undefined4 *)(unaff_ESI + 0xc00) = 0;
    _DAT_00b6ec18 = 0x3ac49ba6;
  }
  if (DAT_00ba67a5 == '\x01') {
    *(undefined4 *)(unaff_ESI + 0xc08) = 0;
  }
  *(undefined1 *)(unaff_ESI + 0x33) = 0;
  *(undefined2 *)(unaff_ESI + 0xc3c) = 1;
  *(undefined1 *)(unaff_ESI + 0x38) = 0;
  *(undefined1 *)(unaff_ESI + 0x39) = 0;
  *(undefined4 *)(unaff_ESI + 0xd8) = 0;
  *(undefined4 *)(unaff_ESI + 0xc4) = 0;
  *(undefined1 *)(unaff_ESI + 0x36) = 0;
  *(undefined4 *)(unaff_ESI + 0x130) = 0x428c0000;
  *(undefined2 *)(unaff_ESI + 0xc38) = 4;
  *(undefined1 *)(unaff_ESI + 0x2a) = 0;
  *(undefined1 *)(unaff_ESI + 0x37) = 0;
  FUN_0059aed0(0x3f800000);
  *(undefined1 *)(unaff_ESI + 0x34) = 0;
  *(undefined1 *)(unaff_ESI + 0x24) = 0;
  *(undefined4 *)(unaff_ESI + 100) = 5000;
  *(undefined4 *)(unaff_ESI + 0x6c) = 0;
  *(undefined1 *)(unaff_ESI + 0x21) = 0;
  *(undefined4 *)(unaff_ESI + 0x70) = 0;
  *(undefined4 *)(unaff_ESI + 0x74) = 0;
  *(undefined4 *)(unaff_ESI + 0xf0) = 0x3f800000;
  *(undefined1 *)(unaff_ESI + 0x1a) = 0;
  *(undefined1 *)(unaff_ESI + 0x1b) = 0;
  *(undefined4 *)(unaff_ESI + 0xa0) = 0;
  *(undefined1 *)(unaff_ESI + 0x4e) = 0;
  FUN_0050bf40(0xff,0xff,0xff,0,0);
  *(undefined1 *)(unaff_ESI + 0x1e) = 0;
  *(undefined1 *)(unaff_ESI + 0x54) = 0;
  *(undefined4 *)(unaff_ESI + 0xa8) = 6;
  *(undefined4 *)(unaff_ESI + 0xac) = 0;
  *(undefined4 *)(unaff_ESI + 0x124) = 0;
  *(undefined4 *)(unaff_ESI + 0x128) = 0;
  *(undefined4 *)(unaff_ESI + 0x83c) = 0;
  *(undefined4 *)(unaff_ESI + 0x840) = 0;
  *(undefined4 *)(unaff_ESI + 0x844) = 0;
  *(undefined4 *)(unaff_ESI + 0x94) = 4;
  *(undefined4 *)(unaff_ESI + 0x98) = 0;
  *(undefined1 *)(unaff_ESI + 0x29) = 1;
  *(undefined1 *)(unaff_ESI + 0x58) = 0;
  *(undefined4 *)(unaff_ESI + 0x78) = 0;
  *(undefined1 *)(unaff_ESI + 0x2b) = 1;
  *(undefined1 *)(unaff_ESI + 0x2c) = 0;
  _DAT_00b6ec14 = 0x3f07ae14;
  _DAT_00b6ec10 = 0x3ecccccd;
  *(undefined4 *)(unaff_ESI + 0x164) = 0;
  *(undefined2 *)(unaff_ESI + 0x168) = 0;
  DAT_008cc380 = 1;
  *(undefined1 *)(unaff_ESI + 0x971) = 1;
  return;
}



/* function 005c30d0 FUN_005c30d0 */

void FUN_005c30d0(int param_1,char param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  
  puVar1 = (undefined4 *)(*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,0x50);
  *(undefined4 **)(param_1 + 0x148) = puVar1;
  *puVar1 = &LAB_005c2ff0;
  if (param_2 == '\0') {
    iVar3 = (**(code **)(*(int *)(param_1 + 4) + 4))(param_1,1,0x500);
    puVar1[7] = iVar3 + 0x80;
    puVar1[8] = iVar3 + 0x100;
    puVar1[9] = iVar3 + 0x180;
    puVar1[10] = iVar3 + 0x200;
    puVar1[0xb] = iVar3 + 0x280;
    puVar1[0xc] = iVar3 + 0x300;
    puVar1[6] = iVar3;
    puVar1[0xd] = iVar3 + 0x380;
    puVar1[0xe] = iVar3 + 0x400;
    puVar1[0xf] = iVar3 + 0x480;
    puVar1[0x10] = 0;
  }
  else {
    _param_2 = 0;
    if (0 < *(int *)(param_1 + 0x3c)) {
      puVar4 = (undefined4 *)(*(int *)(param_1 + 0x44) + 0xc);
      puVar1 = puVar1 + 0x10;
      do {
        iVar3 = *(int *)(param_1 + 4);
        uVar2 = FUN_005cf8a0(puVar4[5],*puVar4,*puVar4);
        uVar2 = FUN_005cf8a0(puVar4[4],puVar4[-1],uVar2);
        uVar2 = (**(code **)(iVar3 + 0x14))(param_1,1,0,uVar2);
        *puVar1 = uVar2;
        _param_2 = _param_2 + 1;
        puVar1 = puVar1 + 1;
        puVar4 = puVar4 + 0x15;
      } while (_param_2 < *(int *)(param_1 + 0x3c));
      return;
    }
  }
  return;
}



/* function 005c7920 FUN_005c7920 */

void FUN_005c7920(int *param_1,char param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  
  if (param_2 != '\0') {
    *(undefined4 *)(*param_1 + 0x14) = 4;
    (**(code **)*param_1)(param_1);
  }
  puVar1 = (undefined4 *)(**(code **)param_1[1])(param_1,1,0x20);
  param_1[0x51] = (int)puVar1;
  *puVar1 = &LAB_005c76a0;
  if (*(char *)(param_1[0x55] + 8) == '\0') {
    puVar1[1] = &LAB_005c7710;
    iVar3 = 0;
    if (0 < param_1[0xf]) {
      piVar4 = (int *)(param_1[0x11] + 8);
      puVar1 = puVar1 + 2;
      do {
        uVar2 = (**(code **)(param_1[1] + 8))
                          (param_1,1,(piVar4[5] * param_1[0x36] * 8) / *piVar4,param_1[0x37]);
        *puVar1 = uVar2;
        iVar3 = iVar3 + 1;
        puVar1 = puVar1 + 1;
        piVar4 = piVar4 + 0x15;
      } while (iVar3 < param_1[0xf]);
    }
    return;
  }
  *(undefined4 *)(*param_1 + 0x14) = 0x30;
  (**(code **)*param_1)(param_1);
  return;
}



/* function 005ca490 FUN_005ca490 */

uint FUN_005ca490(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int *unaff_ESI;
  uint uStack_8;
  int *piStack_4;
  
  iVar2 = unaff_ESI[0x49];
  if (iVar2 != 1) {
    if ((iVar2 < 1) || (4 < iVar2)) {
      *(undefined4 *)(*unaff_ESI + 0x14) = 0x1a;
      *(int *)(*unaff_ESI + 0x18) = unaff_ESI[0x49];
      *(undefined4 *)(*unaff_ESI + 0x1c) = 4;
      (**(code **)*unaff_ESI)();
    }
    iVar2 = FUN_005cf890(unaff_ESI[7],unaff_ESI[0x44] << 3);
    unaff_ESI[0x4e] = iVar2;
    iVar2 = FUN_005cf890(unaff_ESI[8],unaff_ESI[0x45] << 3);
    unaff_ESI[0x4f] = iVar2;
    uVar4 = unaff_ESI[0x49];
    unaff_ESI[0x50] = 0;
    uStack_8 = 0;
    if (0 < (int)uVar4) {
      piStack_4 = unaff_ESI + 0x4a;
      do {
        iVar2 = *piStack_4;
        uVar4 = *(uint *)(iVar2 + 8);
        uVar1 = *(uint *)(iVar2 + 0xc);
        *(uint *)(iVar2 + 0x40) = *(int *)(iVar2 + 0x24) * uVar4;
        uVar3 = *(uint *)(iVar2 + 0x1c) % uVar4;
        iVar5 = uVar1 * uVar4;
        *(uint *)(iVar2 + 0x34) = uVar4;
        *(uint *)(iVar2 + 0x38) = uVar1;
        *(int *)(iVar2 + 0x3c) = iVar5;
        if (uVar3 == 0) {
          uVar3 = uVar4;
        }
        *(uint *)(iVar2 + 0x44) = uVar3;
        uVar4 = *(uint *)(iVar2 + 0x20) % uVar1;
        if (uVar4 == 0) {
          uVar4 = uVar1;
        }
        *(uint *)(iVar2 + 0x48) = uVar4;
        if (10 < unaff_ESI[0x50] + iVar5) {
          *(undefined4 *)(*unaff_ESI + 0x14) = 0xd;
          (**(code **)*unaff_ESI)();
        }
        if (0 < iVar5) {
          do {
            unaff_ESI[unaff_ESI[0x50] + 0x51] = uStack_8;
            iVar5 = iVar5 + -1;
            unaff_ESI[0x50] = unaff_ESI[0x50] + 1;
          } while (iVar5 != 0);
        }
        uVar4 = uStack_8 + 1;
        piStack_4 = piStack_4 + 1;
        uStack_8 = uVar4;
      } while ((int)uVar4 < unaff_ESI[0x49]);
    }
    return uVar4;
  }
  iVar2 = unaff_ESI[0x4a];
  unaff_ESI[0x4e] = *(int *)(iVar2 + 0x1c);
  unaff_ESI[0x4f] = *(int *)(iVar2 + 0x20);
  uVar4 = *(uint *)(iVar2 + 0xc);
  *(undefined4 *)(iVar2 + 0x40) = *(undefined4 *)(iVar2 + 0x24);
  uVar1 = *(uint *)(iVar2 + 0x20);
  uVar3 = uVar1 % uVar4;
  *(undefined4 *)(iVar2 + 0x34) = 1;
  *(undefined4 *)(iVar2 + 0x38) = 1;
  *(undefined4 *)(iVar2 + 0x3c) = 1;
  *(undefined4 *)(iVar2 + 0x44) = 1;
  if (uVar3 == 0) {
    uVar3 = uVar4;
  }
  *(uint *)(iVar2 + 0x48) = uVar3;
  unaff_ESI[0x50] = 1;
  unaff_ESI[0x51] = 0;
  return uVar1 / uVar4;
}



/* function 005d2220 FUN_005d2220 */

void __thiscall FUN_005d2220(int param_1,int param_2)

{
  uint uVar1;
  
  FUN_0059b9f0(*(undefined4 *)(param_2 + 0x14));
  *(undefined1 *)(param_2 + 0x13d) = *(undefined1 *)(param_1 + 0x18);
  *(undefined2 *)(param_2 + 0x13e) = *(undefined2 *)(param_1 + 0x1a);
  *(undefined4 *)(param_2 + 0x150) = *(undefined4 *)(param_1 + 0x1c);
  *(undefined4 *)(param_2 + 0x1c) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_2 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  *(undefined1 *)(param_2 + 0x13c) = *(undefined1 *)(param_1 + 0x2c);
  *(undefined1 *)(param_2 + 0x144) = *(undefined1 *)(param_1 + 0x2d);
  *(undefined1 *)(param_2 + 0x145) = *(undefined1 *)(param_1 + 0x2e);
  if ((*(byte *)(param_1 + 0x2f) & 1) == 0) {
    uVar1 = *(uint *)(param_2 + 0x40) & 0xfffffffb;
  }
  else {
    uVar1 = *(uint *)(param_2 + 0x40) | 4;
  }
  *(uint *)(param_2 + 0x40) = uVar1;
  if ((*(byte *)(param_1 + 0x2f) & 2) == 0) {
    uVar1 = *(uint *)(param_2 + 0x40) & 0xffffdfff;
  }
  else {
    uVar1 = *(uint *)(param_2 + 0x40) | 0x2000;
  }
  *(uint *)(param_2 + 0x40) = uVar1;
  if ((*(byte *)(param_1 + 0x2f) & 4) == 0) {
    uVar1 = *(uint *)(param_2 + 0x40) & 0xfffbffff;
  }
  else {
    uVar1 = *(uint *)(param_2 + 0x40) | 0x40000;
  }
  *(uint *)(param_2 + 0x40) = uVar1;
  if ((*(byte *)(param_1 + 0x2f) & 8) == 0) {
    uVar1 = *(uint *)(param_2 + 0x40) & 0xfff7ffff;
  }
  else {
    uVar1 = *(uint *)(param_2 + 0x40) | 0x80000;
  }
  *(uint *)(param_2 + 0x40) = uVar1;
  if ((*(byte *)(param_1 + 0x2f) & 0x10) == 0) {
    uVar1 = *(uint *)(param_2 + 0x40) & 0xffefffff;
  }
  else {
    uVar1 = *(uint *)(param_2 + 0x40) | 0x100000;
  }
  *(uint *)(param_2 + 0x40) = uVar1;
  if ((*(byte *)(param_1 + 0x2f) & 0x20) == 0) {
    uVar1 = *(uint *)(param_2 + 0x40) & 0xffdfffff;
  }
  else {
    uVar1 = *(uint *)(param_2 + 0x40) | 0x200000;
  }
  *(uint *)(param_2 + 0x40) = uVar1;
  if ((*(byte *)(param_1 + 0x2f) & 0x40) != 0) {
    *(uint *)(param_2 + 0x40) = *(uint *)(param_2 + 0x40) | 0x800000;
    return;
  }
  *(uint *)(param_2 + 0x40) = *(uint *)(param_2 + 0x40) & 0xff7fffff;
  return;
}



/* function 005d2560 FUN_005d2560 */

void __thiscall FUN_005d2560(undefined4 *param_1,int param_2)

{
  *(undefined4 *)(param_2 + 0xb8) = *param_1;
  *(undefined2 *)(param_2 + 0x130) = *(undefined2 *)(param_1 + 1);
  *(undefined1 *)(param_2 + 0xdc) = *(undefined1 *)((int)param_1 + 6);
  *(undefined2 *)(param_2 + 0x130) = *(undefined2 *)(param_1 + 1);
  *(undefined4 *)(param_2 + 0x134) = param_1[2];
  *(undefined4 *)(param_2 + 0xbc) = param_1[3];
  *(ushort *)(param_2 + 0x144) = (ushort)*(byte *)(param_1 + 4);
  *(undefined4 *)(param_2 + 0xc0) = param_1[5];
  *(undefined4 *)(param_2 + 0xc4) = param_1[6];
  *(undefined1 *)(param_2 + 0x14c) = *(undefined1 *)(param_1 + 7);
  *(undefined1 *)(param_2 + 0x14d) = *(undefined1 *)((int)param_1 + 0x1d);
  *(undefined1 *)(param_2 + 0x14e) = *(undefined1 *)((int)param_1 + 0x1e);
  *(undefined1 *)(param_2 + 0x14f) = *(undefined1 *)((int)param_1 + 0x1f);
  *(undefined1 *)(param_2 + 0x150) = *(undefined1 *)(param_1 + 8);
  *(undefined1 *)(param_2 + 0x151) = *(undefined1 *)((int)param_1 + 0x21);
  *(undefined1 *)(param_2 + 0x152) = *(undefined1 *)((int)param_1 + 0x22);
  *(undefined1 *)(param_2 + 0x153) = *(undefined1 *)((int)param_1 + 0x23);
  *(undefined1 *)(param_2 + 0x154) = *(undefined1 *)(param_1 + 9);
  *(undefined2 *)(param_2 + 0x156) = *(undefined2 *)((int)param_1 + 0x26);
  return;
}



/* function 005df560 FUN_005df560 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_005df560(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  float unaff_EBX;
  undefined4 *puVar6;
  undefined4 unaff_EBP;
  undefined4 unaff_ESI;
  undefined4 *puVar7;
  float unaff_EDI;
  undefined4 *puVar8;
  undefined4 uStack_138;
  undefined4 uStack_134;
  undefined1 auStack_130 [4];
  undefined1 local_12c [56];
  undefined1 auStack_f4 [4];
  undefined1 auStack_f0 [4];
  undefined1 auStack_ec [4];
  undefined1 auStack_e8 [4];
  undefined1 local_e4 [56];
  undefined1 auStack_ac [8];
  undefined1 auStack_a4 [4];
  undefined1 auStack_a0 [4];
  undefined1 local_9c [60];
  undefined1 auStack_60 [12];
  undefined1 local_54 [52];
  void *pvStack_20;
  int iStack_18;
  undefined1 uStack_14;
  undefined1 uStack_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0083d875;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  uVar1 = FUN_00734a40(param_1);
  iVar2 = FUN_007c51a0(uVar1,0x12e);
  iVar3 = FUN_007c5120(uVar1);
  puVar6 = (undefined4 *)(iVar3 + iVar2 * 0x40);
  iVar2 = FUN_007c51a0(uVar1,0x20);
  iVar3 = FUN_007c5120(uVar1);
  puVar7 = (undefined4 *)(iVar3 + iVar2 * 0x40);
  puVar8 = puVar6;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  }
  FUN_0059c050(puVar6,0);
  local_4 = 0;
  iVar2 = FUN_007c51a0(uVar1,0x1f);
  iVar3 = FUN_007c5120(uVar1);
  FUN_0059c050(iVar3 + iVar2 * 0x40,0);
  local_4._0_1_ = 1;
  FUN_0059bdd0(local_54,local_9c);
  local_4._0_1_ = 2;
  uVar4 = FUN_0059be30(local_e4,local_54,local_12c);
  local_4 = CONCAT31(local_4._1_3_,3);
  FUN_0059bbc0(uVar4);
  puStack_8._0_1_ = 2;
  FUN_0059acd0();
  FUN_0059a840(&stack0xfffffec4,&uStack_134,&uStack_138,0x15);
  if (DAT_008d21e0 != '\0') {
    unaff_EBX = unaff_EBX * _DAT_00858b8c;
  }
  FUN_0059aa40(unaff_EBX,uStack_134,uStack_138,0x15);
  uVar4 = FUN_0059be30(auStack_e8,auStack_a0,auStack_130);
  puStack_8 = (undefined1 *)CONCAT31(puStack_8._1_3_,4);
  FUN_0059bbc0(uVar4);
  pvStack_c._0_1_ = 2;
  FUN_0059acd0();
  FUN_0059bbb0();
  iVar2 = FUN_007c51a0(uVar1,0x12d);
  iVar3 = FUN_007c5120(uVar1);
  puVar6 = (undefined4 *)(iVar3 + iVar2 * 0x40);
  iVar2 = FUN_007c51a0(uVar1,0x16);
  iVar3 = FUN_007c5120(uVar1);
  puVar7 = (undefined4 *)(iVar3 + iVar2 * 0x40);
  puVar8 = puVar6;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  }
  FUN_0059bd10(puVar6,0);
  iVar2 = FUN_007c51a0(uVar1,0x15);
  iVar3 = FUN_007c5120(uVar1);
  FUN_0059bd10(iVar3 + iVar2 * 0x40,0);
  uVar1 = FUN_0059bdd0(auStack_ec,auStack_a4);
  pvStack_c = (void *)CONCAT31(pvStack_c._1_3_,5);
  FUN_0059bbc0(uVar1);
  uStack_10 = 2;
  FUN_0059acd0();
  uVar1 = FUN_0059be30(auStack_f0,auStack_60,&uStack_138);
  uStack_10 = 6;
  FUN_0059bbc0(uVar1);
  uStack_14 = 2;
  FUN_0059acd0();
  FUN_0059a840(&stack0xfffffeb8,&stack0xfffffec0,&stack0xfffffebc,0x15);
  if (DAT_008d21e0 != '\0') {
    unaff_EDI = unaff_EDI * _DAT_00858b8c;
  }
  FUN_0059aa40(unaff_EDI,unaff_EBP,unaff_ESI,0x15);
  uVar1 = FUN_0059be30(auStack_f4,auStack_ac,&stack0xfffffec4);
  uStack_14 = 7;
  FUN_0059bbc0(uVar1);
  iStack_18._0_1_ = 2;
  FUN_0059acd0();
  FUN_0059bbb0();
  iStack_18._0_1_ = 1;
  FUN_0059acd0();
  iStack_18 = (uint)iStack_18._1_3_ << 8;
  FUN_0059acd0();
  iStack_18 = 0xffffffff;
  FUN_0059acd0();
  ExceptionList = pvStack_20;
  return;
}



/* function 005e8030 FUN_005e8030 */

undefined4 * __thiscall FUN_005e8030(undefined4 *param_1,undefined4 param_2)

{
  undefined1 uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  undefined **local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined2 uStack_16;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0083da03;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  FUN_00542260();
  *param_1 = &PTR_FUN_0086c358;
  param_1[0x52] = 0;
  param_1[0x4e] = &PTR_FUN_0086c2a8;
  param_1[0x7c] = 0;
  param_1[0x78] = &PTR_LAB_0085f438;
  *(undefined2 *)(param_1 + 0x9a) = 0;
  param_1[0xa0] = 0;
  param_1[0xa1] = 0;
  param_1[0x73] = 0;
  *(undefined1 *)(param_1 + 0x6d) = 0;
  param_1[0x75] = 0;
  param_1[0x76] = 0;
  param_1[0x77] = 0;
  local_4._0_1_ = 1;
  local_4._1_3_ = 0;
  FUN_004e4f10();
  param_1[0xe9] = 0;
  param_1[0x106] = 0;
  param_1[0x107] = 0;
  param_1[0x108] = 0;
  param_1[0x10c] = 0;
  *(undefined1 *)((int)param_1 + 0x412) = 0;
  param_1[0x109] = 0;
  *(undefined1 *)(param_1 + 0x104) = 0;
  *(undefined1 *)((int)param_1 + 0x411) = 0;
  param_1[0x10a] = 0;
  param_1[0x10b] = 0;
  param_1[0xe5] = &PTR_LAB_0086c2ac;
  param_1[0x10e] = 0;
  *(undefined1 *)(param_1 + 0x10d) = 0;
  param_1[0x136] = 0;
  param_1[0x137] = 0;
  param_1[0x138] = 0;
  param_1[0x139] = 0;
  param_1[0x13a] = 0;
  param_1[0x13b] = 0;
  param_1[0x13c] = 0;
  local_4._0_1_ = 3;
  FUN_005fd8c0(param_1);
  param_1[0x150] = 0x42c80000;
  param_1[0x151] = 0x42c80000;
  param_1[0x152] = 0;
  param_1[0x166] = param_2;
  _eh_vector_constructor_iterator_
            (param_1 + 0x168,0x1c,0xd,(_func_void_void_ptr *)&LAB_00441e00,
             (_func_void_void_ptr *)&DAT_004411a0);
  local_4._0_1_ = 4;
  *(byte *)((int)param_1 + 0x36) = *(byte *)((int)param_1 + 0x36) & 0xfb | 3;
  param_1[0x10] = param_1[0x10] | 0x10000010;
  *(undefined1 *)(param_1 + 0x121) = 1;
  param_1[0x163] = 0;
  param_1[0x14b] = 0;
  param_1[0x1d1] = 0;
  param_1[0x1d3] = 0;
  param_1[0x1d2] = 0;
  param_1[0x1d4] = 0;
  param_1[0x154] = 0;
  param_1[0x155] = 0;
  param_1[0x15b] = 0;
  param_1[0x15c] = 0;
  param_1[0x15d] = 0;
  param_1[0x15e] = 0;
  param_1[0x15f] = 0;
  param_1[0x14c] = 1;
  param_1[0x14d] = 1;
  local_1c = 0x3f800000;
  param_1[0x156] = 0;
  param_1[0x158] = 0x41700000;
  param_1[0x159] = 0x3dcccccd;
  param_1[0x157] = 0;
  param_1[0x15a] = 0;
  local_24 = (undefined **)0x0;
  local_20 = 0;
  param_1[0x160] = 0x3f800000;
  *(undefined1 *)((int)param_1 + 0x719) = 0x28;
  param_1[0x165] = 0;
  param_1[0x4a] = 0;
  param_1[0x14e] = 0;
  param_1[0x1cc] = 0;
  param_1[0x1cd] = 0x3f800000;
  param_1[0x1c7] = 0;
  param_1[0x1ce] = 0;
  param_1[0x1cf] = 0;
  param_1[0x161] = 0;
  param_1[0x162] = 0x47c34fff;
  param_1[0x23] = 0x428c0000;
  param_1[0x24] = 0x42c80000;
  param_1[0x26] = 0x3bbb3ee7;
  param_1[0x27] = 0x3d4ccccd;
  *(undefined1 *)(param_1 + 0x1d5) = 0xff;
  param_1[0x11b] = param_1[0x11b] & 0xfffe2000 | 0x2000;
  uVar2 = _rand();
  param_1[0x11c] = 0x6100000;
  param_1[0x11b] = ((uVar2 & 3) == 0 | 0xffffc000) << 0x11 | param_1[0x11b] & 0x1ffff;
  param_1[0x11d] = param_1[0x11d] & 0x20000000 | 0x4000000;
  param_1[0x11e] = param_1[0x11e] & 0xffc21020 | 0x21000;
  FUN_004e6aa0(param_1);
  FUN_004e0e80(param_1);
  puVar3 = (undefined4 *)FUN_006089b0(param_1[0x166]);
  param_1[0x138] = *puVar3;
  param_1[0x139] = puVar3[1];
  param_1[0x13a] = puVar3[2];
  param_1[0x13b] = puVar3[3];
  param_1[0x13c] = puVar3[4];
  param_1[0x1c3] = 0x37;
  param_1[0x1c4] = 0x37;
  *(undefined1 *)(param_1 + 0x1c6) = 0;
  puVar3 = param_1 + 0x169;
  iVar5 = 0xd;
  do {
    puVar3[-1] = 0;
    *puVar3 = 0;
    puVar3[1] = 0;
    puVar3[2] = 0;
    puVar3[3] = 0;
    puVar3 = puVar3 + 7;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  *(undefined1 *)(param_1 + 0x1cb) = 1;
  *(undefined1 *)((int)param_1 + 0x72d) = 4;
  *(undefined1 *)((int)param_1 + 0x72e) = 0;
  FUN_005e6080(0,0,1);
  *(undefined1 *)((int)param_1 + 0x71a) = 0x3c;
  *(undefined1 *)(param_1 + 0x1d8) = 0xff;
  param_1[0x1d9] = 0;
  param_1[0x1da] = 0;
  param_1[0x3f] = 0;
  param_1[0x1e1] = 0;
  *(undefined1 *)(param_1 + 0x118) = 0;
  param_1[0x11a] = 0;
  param_1[0x1d0] = 0xffffffff;
  *(undefined2 *)((int)param_1 + 0x756) = 0;
  *(undefined1 *)((int)param_1 + 0x72f) = 0;
  param_1[0x153] = 0;
  param_1[0x164] = 0;
  param_1[0x13d] = 0;
  param_1[0x13e] = 0;
  param_1[0x13f] = 0;
  param_1[0x140] = 0;
  *(undefined2 *)(param_1 + 0x141) = 0;
  *(undefined2 *)((int)param_1 + 0x506) = 0;
  *(undefined2 *)(param_1 + 0x142) = 0;
  *(undefined2 *)((int)param_1 + 0x50a) = 0;
  param_1[0x1e2] = 0;
  param_1[0x1e3] = 0;
  param_1[0x1e6] = 0xffffffff;
  iVar5 = FUN_006074a0(0x294);
  local_4._0_1_ = 5;
  if (iVar5 == 0) {
    uVar4 = 0;
  }
  else {
    uVar4 = FUN_00607140(param_1);
  }
  param_1[0x11f] = uVar4;
  local_4._0_1_ = 4;
  uVar1 = (undefined1)local_4;
  local_4._0_1_ = 4;
  param_1[0x120] = 0;
  if ((param_1[0x166] != 0) && (uVar1 = (undefined1)local_4, param_1[0x166] != 1)) {
    iVar5 = FUN_0061a5a0(0x20);
    local_4._0_1_ = 6;
    if (iVar5 == 0) {
      uVar4 = 0;
    }
    else {
      uVar4 = FUN_00690d20();
    }
    local_4._0_1_ = 4;
    FUN_00681b60(uVar4,3);
    uVar1 = (undefined1)local_4;
  }
  local_4._0_1_ = uVar1;
  iVar5 = FUN_0061a5a0(0x20);
  local_4._0_1_ = 7;
  if (iVar5 == 0) {
    uVar4 = 0;
  }
  else {
    uVar4 = FUN_0062f310(0,1,0,0x41000000);
  }
  local_4._0_1_ = 4;
  FUN_00681af0(uVar4,4,0);
  param_1[0x1d6] = 0;
  param_1[0x1e4] = 0x3f800000;
  *(undefined2 *)(param_1 + 0x1e5) = 0xffff;
  FUN_00611570(param_1,0);
  param_1[0x11d] = param_1[0x11d] & 0xdfffffff;
  param_1[0x11e] = param_1[0x11e] & 0xffffffdf;
  if (((DAT_0096913f != '\0') && (param_1[0x166] != 0)) && (param_1[0x166] != 1)) {
    uVar4 = FUN_00608830(0);
    FUN_00608da0(4,uVar4);
    uVar4 = FUN_0056e210(0xffffffff);
    FUN_004af820(uVar4);
    local_24 = &PTR_FUN_00858e68;
    local_4._0_1_ = 8;
    uStack_16 = 1000;
    FUN_004ab420(&local_24,0);
    local_4 = CONCAT31(local_4._1_3_,4);
    local_24 = &PTR_FUN_00858e68;
    FUN_004af890();
  }
  ExceptionList = pvStack_c;
  return param_1;
}



/* function 005f8900 FUN_005f8900 */

undefined4 FUN_005f8900(int param_1,int param_2)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  char cVar6;
  int *piVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int *piVar14;
  int local_11c;
  int local_118;
  undefined4 local_114;
  undefined4 local_10c;
  int aiStack_cc [16];
  int iStack_8c;
  int local_68 [7];
  undefined1 local_4c [64];
  void *local_c;
  undefined1 *puStack_8;
  int iStack_4;
  
  iStack_4 = 0xffffffff;
  puStack_8 = &LAB_0083e12d;
  local_c = ExceptionList;
  sVar2 = *(short *)(param_1 + 0xe);
  iVar9 = *(int *)(param_2 + 0x2cc);
  iVar3 = *(int *)(param_2 + 0x28);
  if ((iVar3 != 0) && (iVar4 = *(int *)(param_1 + 0x14), iVar4 != 0)) {
    bVar1 = *(byte *)(iVar4 + 0x488);
    iVar12 = 0;
    piVar7 = local_68;
    for (iVar10 = 7; iVar10 != 0; iVar10 = iVar10 + -1) {
      *piVar7 = 0;
      piVar7 = piVar7 + 1;
    }
    piVar7 = (int *)(param_2 + 0xc);
    iVar10 = 7;
    do {
      iVar11 = *piVar7;
      if ((iVar11 != 0) && (*(char *)(iVar11 + 0x484) == '\x02')) {
        local_68[iVar12] = iVar11;
        iVar12 = iVar12 + 1;
      }
      piVar7 = piVar7 + 1;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
    piVar14 = local_68 + iVar12;
    piVar7 = (int *)(param_2 + 0xc);
    iVar10 = 7;
    do {
      iVar12 = *piVar7;
      if ((iVar12 != 0) && (*(char *)(iVar12 + 0x484) != '\x02')) {
        *piVar14 = iVar12;
        piVar14 = piVar14 + 1;
      }
      piVar7 = piVar7 + 1;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
    local_11c = 0;
    local_118 = 0;
    iVar10 = iVar3;
    ExceptionList = &local_c;
    do {
      iVar12 = local_68[local_118];
      local_118 = local_118 + 1;
      if (iVar12 != 0) {
        if (local_11c < (int)(uint)bVar1) {
          if ((((sVar2 == 0x5e9) && (-1 < iVar9)) && (iVar9 < 0x40)) &&
             ((&DAT_00c17900)[iVar9 * 0x10] != 0)) {
            local_10c = 0;
            iVar13 = 0;
            piVar7 = (int *)(param_2 + 0xc);
            iVar11 = 7;
            do {
              if (*piVar7 != 0) {
                iVar13 = iVar13 + 1;
              }
              piVar7 = piVar7 + 1;
              iVar11 = iVar11 + -1;
            } while (iVar11 != 0);
            if (((iVar13 == 1) && (*(int *)(iVar4 + 0x590) != 9)) && (*(int *)(iVar4 + 0x594) != 2))
            {
              local_10c = 1;
              iVar11 = *(int *)(iVar4 + 0x464);
              if ((iVar11 != 0) && (iVar11 != iVar12)) {
                iVar13 = 0;
                piVar7 = (int *)(param_2 + 0xc);
                do {
                  if (*piVar7 == iVar11) goto LAB_005f8abe;
                  iVar13 = iVar13 + 1;
                  piVar7 = piVar7 + 1;
                } while (iVar13 < 7);
                if ((*(int *)(param_2 + 0x28) == iVar11) ||
                   ((*(uint *)(iVar11 + 0x46c) & 0x20000000) != 0)) {
LAB_005f8abe:
                  local_10c = 0;
                }
              }
            }
            FUN_00632bd0();
            iStack_4 = 0;
            iVar11 = FUN_0061a5a0(0x24);
            iStack_4._0_1_ = 1;
            if (iVar11 == 0) {
              uVar8 = 0;
            }
            else {
              uVar8 = FUN_0063b320(iVar4,iVar10,local_10c,6);
            }
            iStack_4._0_1_ = 0;
            FUN_00632d10(uVar8);
            iVar10 = FUN_0061a5a0(0x1c);
            iStack_4._0_1_ = 2;
            if (iVar10 == 0) {
              uVar8 = 0;
            }
            else {
              uVar8 = FUN_00635450(iVar9);
            }
            iStack_4._0_1_ = 0;
            FUN_00632d10(uVar8);
            FUN_0061a390();
            iStack_4._0_1_ = 3;
            FUN_005f7540(iVar12,local_4c,param_2 + 0x3c,0xffffffff,0);
            iStack_4 = (uint)iStack_4._1_3_ << 8;
            FUN_0061a3a0();
            iStack_4 = 0xffffffff;
            FUN_006389f0();
            local_11c = local_11c + 1;
            iVar10 = iVar12;
          }
          else {
            local_114 = 0;
            iVar13 = 0;
            piVar7 = (int *)(param_2 + 0xc);
            iVar11 = 7;
            do {
              if (*piVar7 != 0) {
                iVar13 = iVar13 + 1;
              }
              piVar7 = piVar7 + 1;
              iVar11 = iVar11 + -1;
            } while (iVar11 != 0);
            if (((iVar13 == 1) && (*(int *)(iVar4 + 0x590) != 9)) && (*(int *)(iVar4 + 0x594) != 2))
            {
              local_114 = 1;
              iVar11 = *(int *)(iVar4 + 0x464);
              if ((iVar11 != 0) && (iVar11 != iVar12)) {
                iVar13 = 0;
                piVar7 = (int *)(param_2 + 0xc);
                do {
                  if (*piVar7 == iVar11) goto LAB_005f8c3e;
                  iVar13 = iVar13 + 1;
                  piVar7 = piVar7 + 1;
                } while (iVar13 < 7);
                if ((*(int *)(param_2 + 0x28) == iVar11) ||
                   ((*(uint *)(iVar11 + 0x46c) & 0x20000000) != 0)) {
LAB_005f8c3e:
                  local_114 = 0;
                }
              }
            }
            FUN_0063b320(iVar4,iVar10,local_114,6);
            iStack_4 = 4;
            FUN_0061a390();
            piVar14 = (int *)(param_2 + 0x3c);
            iStack_4._0_1_ = 5;
            iVar10 = 0;
            piVar7 = piVar14;
            do {
              if (*piVar7 == iVar12) {
                if ((int *)piVar14[iVar10 * 5 + 1] != (int *)0x0) {
                  iVar11 = (**(code **)(*(int *)piVar14[iVar10 * 5 + 1] + 0x10))();
                  iVar13 = (**(code **)(iStack_8c + 0x10))();
                  if (iVar11 != iVar13) {
                    puVar5 = (undefined4 *)piVar14[iVar10 * 5 + 1];
                    iVar11 = (**(code **)(iStack_8c + 4))();
                    piVar14[iVar10 * 5 + 1] = iVar11;
                    piVar14[iVar10 * 5 + 2] = -1;
                    if (puVar5 != (undefined4 *)0x0) {
                      (**(code **)*puVar5)(1);
                    }
                    break;
                  }
                }
                if (piVar14[iVar10 * 5 + 1] == 0) {
                  iVar11 = (**(code **)(iStack_8c + 4))();
                  piVar14[iVar10 * 5 + 1] = iVar11;
                  piVar14[iVar10 * 5 + 2] = -1;
                }
                break;
              }
              iVar10 = iVar10 + 1;
              piVar7 = piVar7 + 5;
            } while (iVar10 < 8);
            iStack_4._0_1_ = 4;
            FUN_0061a3a0();
            if ((*(uint *)(iVar12 + 0x474) & 0x2000000) == 0) {
              *(uint *)(iVar12 + 0x474) = *(uint *)(iVar12 + 0x474) | 0x2000000;
              FUN_00632bd0();
              iStack_4._0_1_ = 6;
              iVar10 = FUN_0061a5a0(0x60);
              iStack_4._0_1_ = 7;
              if (iVar10 == 0) {
                uVar8 = 0;
              }
              else {
                uVar8 = FUN_0063c340(iVar4,0,1);
              }
              iStack_4 = CONCAT31(iStack_4._1_3_,6);
              FUN_00632d10(uVar8);
              piVar14 = (int *)(param_2 + 0x21c);
              iVar10 = 0;
              piVar7 = piVar14;
              do {
                if (*piVar7 == iVar12) {
                  piVar7 = *(int **)(param_2 + 0x220 + iVar10 * 0x14);
                  if (piVar7 != (int *)0x0) {
                    uVar8 = (**(code **)(*piVar7 + 4))();
                    FUN_00632d10(uVar8);
                  }
                  break;
                }
                iVar10 = iVar10 + 1;
                piVar7 = piVar7 + 5;
              } while (iVar10 < 8);
              iVar10 = 0;
              piVar7 = piVar14;
              do {
                if (*piVar7 == iVar12) {
                  piVar7 = *(int **)(param_2 + 0x220 + iVar10 * 0x14);
                  if (piVar7 != (int *)0x0) {
                    iVar11 = (**(code **)(aiStack_cc[0] + 0x10))();
                    iVar13 = (**(code **)(*piVar7 + 0x10))();
                    if (iVar13 != iVar11) {
                      puVar5 = (undefined4 *)piVar14[iVar10 * 5 + 1];
                      iVar11 = (**(code **)(aiStack_cc[0] + 4))();
                      piVar14[iVar10 * 5 + 1] = iVar11;
                      piVar14[iVar10 * 5 + 2] = -1;
                      if (puVar5 != (undefined4 *)0x0) {
                        (**(code **)*puVar5)(1);
                      }
                      break;
                    }
                  }
                  if (piVar14[iVar10 * 5 + 1] == 0) {
                    iVar11 = (**(code **)(aiStack_cc[0] + 4))();
                    piVar14[iVar10 * 5 + 1] = iVar11;
                    piVar14[iVar10 * 5 + 2] = -1;
                  }
                  break;
                }
                iVar10 = iVar10 + 1;
                piVar7 = piVar7 + 5;
              } while (iVar10 < 8);
              iStack_4 = CONCAT31(iStack_4._1_3_,4);
              FUN_006389f0();
            }
            iStack_4 = 0xffffffff;
            FUN_0063b3c0();
            local_11c = local_11c + 1;
            iVar10 = iVar12;
          }
        }
        else {
          FUN_0061a3b0();
          iStack_4 = 8;
          FUN_0061a390();
          piVar14 = (int *)(param_2 + 0x3c);
          iStack_4._0_1_ = 9;
          iVar11 = 0;
          piVar7 = piVar14;
          do {
            if (*piVar7 == iVar12) {
              piVar7 = *(int **)(param_2 + 0x40 + iVar11 * 0x14);
              if (piVar7 != (int *)0x0) {
                iVar12 = (**(code **)(*piVar7 + 0x10))();
                iVar13 = (*(code *)PTR_LAB_00858ec0)();
                if (iVar12 != iVar13) {
                  puVar5 = (undefined4 *)piVar14[iVar11 * 5 + 1];
                  iVar12 = (*(code *)PTR_FUN_00858eb4)();
                  piVar14[iVar11 * 5 + 1] = iVar12;
                  piVar14[iVar11 * 5 + 2] = -1;
                  if (puVar5 != (undefined4 *)0x0) {
                    (**(code **)*puVar5)(1);
                  }
                  break;
                }
              }
              if (piVar14[iVar11 * 5 + 1] == 0) {
                iVar12 = (*(code *)PTR_FUN_00858eb4)();
                piVar14[iVar11 * 5 + 1] = iVar12;
                piVar14[iVar11 * 5 + 2] = -1;
              }
              break;
            }
            iVar11 = iVar11 + 1;
            piVar7 = piVar7 + 5;
          } while (iVar11 < 8);
          iStack_4 = CONCAT31(iStack_4._1_3_,8);
          FUN_0061a3a0();
          iStack_4 = 0xffffffff;
          FUN_0061a3d0();
        }
      }
    } while (local_118 < 7);
    cVar6 = FUN_005df8f0();
    if ((cVar6 == '\0') && ((*(uint *)(iVar3 + 0x474) & 0x2000000) == 0)) {
      *(uint *)(iVar3 + 0x474) = *(uint *)(iVar3 + 0x474) | 0x2000000;
      FUN_00632bd0();
      iStack_4 = 10;
      iVar9 = FUN_0061a5a0(0x60);
      iStack_4._0_1_ = 0xb;
      if (iVar9 == 0) {
        uVar8 = 0;
      }
      else {
        uVar8 = FUN_0063c340(iVar4,0,1);
      }
      iStack_4 = CONCAT31(iStack_4._1_3_,10);
      FUN_00632d10(uVar8);
      iVar9 = 0;
      piVar7 = (int *)(param_2 + 0x21c);
      do {
        if (*piVar7 == iVar3) {
          piVar7 = *(int **)(param_2 + 0x220 + iVar9 * 0x14);
          if (piVar7 != (int *)0x0) {
            uVar8 = (**(code **)(*piVar7 + 4))();
            FUN_00632d10(uVar8);
          }
          break;
        }
        iVar9 = iVar9 + 1;
        piVar7 = piVar7 + 5;
      } while (iVar9 < 8);
      FUN_005f7540(iVar3,aiStack_cc,(int *)(param_2 + 0x21c),0xffffffff,0);
      iStack_4 = 0xffffffff;
      FUN_006389f0();
    }
  }
  ExceptionList = local_c;
  return 0;
}



/* function 00604500 FUN_00604500 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00604500(char *param_1,int param_2)

{
  float fVar1;
  float fVar2;
  char cVar3;
  int iVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  uint uVar9;
  uint uVar10;
  byte bVar11;
  undefined4 uVar12;
  float10 fVar13;
  float10 fVar14;
  float *pfVar15;
  float fStack_120;
  float local_11c;
  float fStack_114;
  float fStack_110;
  float fStack_10c;
  float *pfStack_108;
  char *local_104;
  float fStack_100;
  float fStack_fc;
  float fStack_f8;
  float fStack_f4;
  float fStack_f0;
  float fStack_ec;
  float fStack_e8;
  float fStack_e4;
  undefined **ppuStack_e0;
  float fStack_dc;
  float fStack_d8;
  undefined **appuStack_ac [14];
  undefined1 auStack_74 [12];
  float fStack_68;
  float fStack_64;
  float fStack_60;
  undefined1 auStack_5c [12];
  undefined1 auStack_50 [12];
  undefined1 auStack_44 [56];
  void *pvStack_c;
  undefined1 *puStack_8;
  uint uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0083e99d;
  pvStack_c = ExceptionList;
  if ((*(int *)(param_2 + 0xdc) == 0) || (*(float *)(param_2 + 0xd8) == DAT_00858b50)) {
    *param_1 = '\0';
    return;
  }
  ExceptionList = &pvStack_c;
  local_104 = param_1;
  iVar4 = FUN_006819d0();
  if ((iVar4 == 0) || (cVar3 = FUN_0061a360(iVar4), cVar3 == '\0')) {
    uVar12 = 1;
  }
  else {
    uVar12 = *(undefined4 *)(iVar4 + 8);
  }
  iVar4 = *(int *)(param_2 + 0xdc);
  switch(*(byte *)(iVar4 + 0x36) & 7) {
  case 1:
    FUN_004acf00(*(undefined2 *)(param_2 + 0xf8),*(undefined4 *)(param_2 + 0xd8),iVar4,
                 param_2 + 0xe0,param_2 + 0xec,uVar12);
    uStack_4 = 0xe;
    FUN_004ab420(&ppuStack_e0,0);
    uStack_4 = 0xffffffff;
    FUN_004acff0();
    break;
  case 2:
    if (*local_104 == '\0') {
      pfVar15 = (float *)(iVar4 + 0x44);
      fVar13 = (float10)FUN_00406da0();
      fVar1 = (float)fVar13;
      if (*(int *)(iVar4 + 0x4c4) == 0) {
        local_11c = DAT_0086c920;
      }
      else {
        local_11c = DAT_0086c924;
      }
      if (((((*(int *)(iVar4 + 0x594) == 6) && ((*(byte *)(iVar4 + 0x40) & 4) != 0)) &&
           ((*(uint *)(param_2 + 0x1c) >> 4 & 1) != 0)) &&
          (((*(byte *)(param_2 + 0x46c) & 1) != 0 && (*(int *)(param_2 + 0x568) == 0)))) &&
         (_DAT_00858fc4 < fVar1)) {
        FUN_005f0360(iVar4,0x41700000,0);
      }
      if (fVar1 <= local_11c) {
        if ((*(int *)(param_2 + 0xfc) == 0) ||
           ((*(byte *)(*(int *)(param_2 + 0xfc) + 0x36) & 7) != 2)) {
          cVar3 = FUN_005df8f0();
          if (cVar3 == '\0') {
            uVar8 = 0;
            uVar12 = FUN_00601d70(0);
            FUN_004ac840(*(undefined2 *)(param_2 + 0xf8),*(undefined4 *)(param_2 + 0xd8),
                         *(undefined4 *)(param_2 + 0xdc),param_2 + 0xe0,param_2 + 0xec,uVar12,uVar8)
            ;
            uStack_4 = 2;
            FUN_004ab420(appuStack_ac,0);
            uStack_4 = 0xffffffff;
            FUN_004ac920();
          }
          break;
        }
        uVar12 = FUN_005f3640(param_2,iVar4);
        FUN_004ad3f0(iVar4,*(undefined4 *)(param_2 + 0xd8),0x31,3,0);
        uStack_4 = 3;
        FUN_004ad830(iVar4,DAT_00b7cb84,0x31,3,uVar12,0,*(uint *)(param_2 + 0x46c) >> 8 & 0xffffff01
                    );
        uStack_4 = CONCAT31(uStack_4._1_3_,4);
        cVar3 = FUN_004b35a0(param_2);
        if (cVar3 != '\0') {
          FUN_004b5ac0(param_2,auStack_74,1);
        }
        uStack_4 = CONCAT31(uStack_4._1_3_,3);
      }
      else {
        local_11c = *(float *)(param_2 + 0xd8);
        if ((((*(byte *)(param_2 + 0x46c) & 1) != 0) &&
            (fVar2 = *(float *)(param_2 + 0xe0) * *(float *)(param_2 + 0x550) +
                     *(float *)(param_2 + 0xe4) * *(float *)(param_2 + 0x554), fVar2 < DAT_00858b50)
            ) && (local_11c = fVar2 * *(float *)(param_2 + 0x8c) + local_11c,
                 local_11c < DAT_00858b50)) {
          local_11c = 0.0;
        }
        cVar3 = FUN_005df8f0();
        if (cVar3 != '\0') {
          if (_DAT_00858ba4 < local_11c) {
            local_11c = 20.0;
          }
          fVar13 = (float10)FUN_00441db0();
          pfVar5 = (float *)FUN_00535300();
          fStack_f4 = *pfVar5;
          fStack_f0 = pfVar5[1];
          fStack_ec = pfVar5[2];
          iVar6 = FUN_00535300();
          fStack_100 = *(float *)(iVar6 + 0xc);
          fStack_fc = *(float *)(iVar6 + 0x10);
          fStack_f8 = *(float *)(iVar6 + 0x14);
          fStack_d8 = fStack_f8 + fStack_ec;
          fStack_dc = fStack_f0 + fStack_fc;
          ppuStack_e0 = (undefined **)(fStack_f4 + fStack_100);
          FUN_004119d0(&fStack_114,&ppuStack_e0,0x40000000);
          pfVar5 = (float *)FUN_0059c890(auStack_5c,*(undefined4 *)(iVar4 + 0x14),&fStack_114);
          fStack_114 = *pfVar5;
          fStack_110 = pfVar5[1];
          fStack_10c = pfVar5[2];
          if (*(int *)(param_2 + 0x14) == 0) {
            iVar6 = param_2 + 4;
          }
          else {
            iVar6 = *(int *)(param_2 + 0x14) + 0x30;
          }
          pfVar5 = (float *)FUN_0040fe60(auStack_50,&fStack_114,iVar6);
          fStack_114 = *pfVar5;
          fStack_110 = pfVar5[1];
          fVar14 = (float10)fpatan(-(float10)fStack_114,(float10)fStack_110);
          fStack_10c = pfVar5[2];
          fVar13 = (float10)FUN_0053cb50((float)((float10)(float)fVar13 - fVar14));
          iVar6 = *(int *)(iVar4 + 0x14) + 0x30;
          fVar14 = (float10)fpatan((float10)fStack_100 - (float10)fStack_f4,
                                   (float10)fStack_fc - (float10)fStack_f0);
          pfStack_108 = (float *)(float)fVar14;
          if (*(int *)(iVar4 + 0x14) == 0) {
            iVar6 = iVar4 + 4;
          }
          if (*(int *)(param_2 + 0x14) == 0) {
            iVar7 = param_2 + 4;
          }
          else {
            iVar7 = *(int *)(param_2 + 0x14) + 0x30;
          }
          FUN_0040fe60(&fStack_68,iVar7,iVar6);
          FUN_0059c910();
          fVar2 = ABS((float)fVar13);
          if ((fVar2 < (float)pfStack_108) || (_DAT_00858cb8 - (float)pfStack_108 < fVar2)) {
            fVar13 = (float10)fStack_68 * (float10)*pfVar15 +
                     (float10)fStack_60 * (float10)*(float *)(iVar4 + 0x4c) +
                     (float10)fStack_64 * (float10)*(float *)(iVar4 + 0x48);
          }
          else if ((float)fVar13 <= DAT_00858b50) {
            uVar12 = *(undefined4 *)(iVar4 + 0x14);
            fVar13 = (float10)FUN_0040fdb0(uVar12,pfVar15);
            if ((_DAT_0086cd7c < fVar1) && (fVar13 < (float10)_DAT_00858b1c)) {
              fVar14 = (float10)FUN_0040fdb0(uVar12,*(int *)(param_2 + 0x14) + 0x10);
              fVar13 = (float10)(float)fVar13;
              if (fVar14 < (float10)DAT_00858b50) {
                pfStack_108 = pfVar15;
              }
            }
          }
          else {
            uVar12 = FUN_0040fe90(auStack_44,0xbf800000,*(undefined4 *)(iVar4 + 0x14));
            fVar13 = (float10)FUN_0040fdb0(uVar12,pfVar15);
          }
          if ((float10)_DAT_00858b1c < fVar13) {
            FUN_005f0360(iVar4,local_11c,0);
          }
          break;
        }
        if ((*(int *)(param_2 + 0xfc) == 0) ||
           ((*(byte *)(*(int *)(param_2 + 0xfc) + 0x36) & 7) != 2)) {
          FUN_005f0360(iVar4,*(undefined4 *)(param_2 + 0xd8),0);
          break;
        }
        uVar12 = FUN_005f3640(param_2,iVar4);
        FUN_004ad3f0(iVar4,*(undefined4 *)(param_2 + 0xd8),0x31,3,0);
        uStack_4 = 0;
        FUN_004ad830(iVar4,DAT_00b7cb84,0x31,3,uVar12,0,*(uint *)(param_2 + 0x46c) >> 8 & 0xffffff01
                    );
        uStack_4 = CONCAT31(uStack_4._1_3_,1);
        cVar3 = FUN_004b35a0(param_2);
        if (cVar3 != '\0') {
          FUN_004b5ac0(param_2,auStack_74,1);
        }
        uStack_4 = uStack_4 & 0xffffff00;
      }
      FUN_004ad960();
      uStack_4 = 0xffffffff;
      FUN_004ad420();
    }
    break;
  case 3:
    uVar8 = FUN_00601d70();
    cVar3 = FUN_005df8f0();
    if (cVar3 == '\0') {
      cVar3 = FUN_005df8f0();
      if (cVar3 == '\0') {
        FUN_004ac990(*(undefined2 *)(param_2 + 0xf8),*(undefined4 *)(param_2 + 0xd8),
                     *(undefined4 *)(param_2 + 0xdc),param_2 + 0xe0,param_2 + 0xec,uVar12,uVar8);
        uStack_4 = 8;
        FUN_004ab420(appuStack_ac,0);
      }
      else {
        FUN_005fed40(*(undefined2 *)(param_2 + 0xf8),*(undefined4 *)(param_2 + 0xd8),
                     *(undefined4 *)(param_2 + 0xdc),param_2 + 0xe0,param_2 + 0xec,uVar12,uVar8);
        uStack_4 = 6;
        FUN_004ab420(appuStack_ac,0);
        thunk_FUN_0156fc20(1);
        FUN_005effe0(0x1c,0,0x3f800000,0,0,0);
        uVar9 = FUN_00608970(4);
        uVar10 = FUN_00608830(*(undefined4 *)(iVar4 + 0x598));
        if ((uVar9 & uVar10) != 0) {
          thunk_FUN_01561070(iVar4);
          uStack_4._0_1_ = 7;
          FUN_004ab420(&ppuStack_e0,0);
          uStack_4 = CONCAT31(uStack_4._1_3_,6);
          ppuStack_e0 = &PTR_FUN_00858e68;
          FUN_004af890();
        }
        appuStack_ac[0] = &PTR_FUN_0086c970;
      }
    }
    else {
      FUN_005fee40(*(undefined2 *)(param_2 + 0xf8),*(undefined4 *)(param_2 + 0xd8),
                   *(undefined4 *)(param_2 + 0xdc),param_2 + 0xe0,param_2 + 0xec,uVar12,uVar8);
      uStack_4 = 5;
      FUN_004ab420(&ppuStack_e0,0);
      FUN_005effe0(0x1c,0,0x3f800000,0,0,0);
      ppuStack_e0 = &PTR_FUN_0086c9b0;
    }
    iVar6 = param_2 + 0xec;
    uStack_4 = 0xffffffff;
    FUN_004aca70();
    if (*(int *)(iVar4 + 0xdc) == 0) {
      fStack_114 = *(float *)(param_2 + 0xe0) * _DAT_00858c1c;
      fStack_110 = *(float *)(param_2 + 0xe4) * _DAT_00858c1c;
      fStack_10c = *(float *)(param_2 + 0xe8) * _DAT_00858c1c;
      cVar3 = FUN_005df8f0();
      if (cVar3 == '\0') {
        cVar3 = FUN_005df8f0();
        if (cVar3 == '\0') {
          FUN_004ac990(*(undefined2 *)(param_2 + 0xf8),*(undefined4 *)(param_2 + 0xd8),param_2,
                       &fStack_114,iVar6,uVar12,uVar8);
          uStack_4 = 0xc;
          FUN_004ab420(appuStack_ac,0);
          uStack_4 = 0xffffffff;
          FUN_004aca70();
        }
        else {
          FUN_005fed40(*(undefined2 *)(param_2 + 0xf8),*(undefined4 *)(param_2 + 0xd8),param_2,
                       &fStack_114,iVar6,uVar12,uVar8);
          uStack_4 = 10;
          FUN_004ab420(appuStack_ac,0);
          thunk_FUN_0156fc20(1);
          uVar9 = FUN_00608970(4);
          uVar10 = FUN_00608830(*(undefined4 *)(param_2 + 0x598));
          if ((uVar9 & uVar10) != 0) {
            thunk_FUN_01561070(param_2);
            uStack_4._0_1_ = 0xb;
            FUN_004ab420(&ppuStack_e0,0);
            uStack_4 = CONCAT31(uStack_4._1_3_,10);
            ppuStack_e0 = &PTR_FUN_00858e68;
            FUN_004af890();
          }
          uStack_4 = 0xffffffff;
          appuStack_ac[0] = &PTR_FUN_0086c970;
          FUN_004aca70();
        }
      }
      else {
        FUN_005fee40(*(undefined2 *)(param_2 + 0xf8),*(undefined4 *)(param_2 + 0xd8),param_2,
                     &fStack_114,iVar6,uVar12,uVar8);
        uStack_4 = 9;
        FUN_004ab420(appuStack_ac,0);
        uStack_4 = 0xffffffff;
        appuStack_ac[0] = &PTR_FUN_0086c9b0;
        FUN_004aca70();
      }
    }
    break;
  case 4:
    bVar11 = *(byte *)(param_2 + 0x46c) & 1;
    fStack_120 = *(float *)(param_2 + 0xd8);
    if (((bVar11 != 0) && (cVar3 = thunk_FUN_015619f0(), cVar3 == '\0')) &&
       (fVar1 = *(float *)(param_2 + 0xe0) * *(float *)(param_2 + 0x550) +
                *(float *)(param_2 + 0xe4) * *(float *)(param_2 + 0x554), fVar1 < DAT_00858b50)) {
      fVar13 = (float10)FUN_00420800(0,fVar1 * *(float *)(param_2 + 0x8c) + fStack_120);
      fStack_120 = (float)fVar13;
    }
    local_11c = DAT_008d23b0;
    if (*(int *)(param_2 + 0x480) != 0) {
      local_11c = DAT_008d23ac;
    }
    if ((((fStack_120 <= local_11c) || (cVar3 = thunk_FUN_015619f0(), cVar3 != '\0')) ||
        ((bVar11 == 0 || (iVar4 == *(int *)(param_2 + 0x584))))) ||
       ((*(int *)(iVar4 + 0xfc) != 0 && (iVar4 == *(int *)(iVar4 + 0xfc))))) {
      FUN_004accf0(*(undefined2 *)(param_2 + 0xf8),*(undefined4 *)(param_2 + 0xd8),iVar4,
                   param_2 + 0xe0,param_2 + 0xec,uVar12);
      uStack_4 = 0xd;
      FUN_004ab420(&ppuStack_e0,0);
      uStack_4 = 0xffffffff;
      FUN_004acdd0();
    }
    else {
      fStack_e4 = -*(float *)(param_2 + 0xe4);
      fStack_e8 = -*(float *)(param_2 + 0xe0);
      uVar12 = FUN_005def60(&fStack_e8);
      uVar12 = FUN_00821b40(3,uVar12);
      FUN_0073a530(param_2,*(undefined4 *)(param_2 + 0xdc),0x36,uVar12);
      *(undefined4 *)(param_2 + 0x128) = *(undefined4 *)(param_2 + 0xdc);
    }
  }
  FUN_00401ce1();
  return;
}



/* function 00614720 FUN_00614720 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00614720(float param_1,float param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  float fVar2;
  bool bVar3;
  float fVar4;
  char cVar5;
  byte bVar6;
  char cVar7;
  float *pfVar8;
  int iVar9;
  undefined4 uVar10;
  int iVar11;
  uint3 uVar15;
  float fVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  byte bVar16;
  uint uVar17;
  float fVar18;
  float10 fVar19;
  float *pfVar20;
  undefined4 uVar21;
  float local_128;
  char local_121;
  float local_120;
  float local_11c;
  float local_118;
  float local_114;
  float local_110;
  uint local_10c;
  float local_108;
  char cStack_102;
  char cStack_101;
  float local_100 [6];
  int local_e8;
  float fStack_e4;
  float fStack_e0;
  float fStack_dc;
  uint local_d8;
  uint local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float fStack_c0;
  float fStack_bc;
  float fStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  float fStack_a8;
  float fStack_a4;
  float fStack_a0;
  undefined1 auStack_9c [4];
  undefined1 local_98 [4];
  undefined1 auStack_94 [8];
  float fStack_8c;
  float fStack_84;
  float fStack_80;
  float fStack_7c;
  undefined1 auStack_68 [35];
  char cStack_45;
  undefined1 auStack_3c [12];
  undefined1 auStack_30 [12];
  undefined1 auStack_24 [12];
  undefined1 auStack_18 [12];
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0083ef8e;
  pvStack_c = ExceptionList;
  uVar17 = (uint)DAT_00b7cd74;
  fVar18 = -NAN;
  bVar3 = false;
  local_11c = -NAN;
  local_108 = -NAN;
  local_d8 = CONCAT22(local_d8._2_2_,0xffff);
  local_d4 = CONCAT22(local_d4._2_2_,0xffff);
  local_d0 = 0.0;
  ExceptionList = &pvStack_c;
  cVar5 = thunk_FUN_0156eff0();
  if ((cVar5 != '\0') || (DAT_0096917a != '\0')) goto LAB_00615957;
  pfVar8 = (float *)FUN_0056e250(DAT_00b7cd74);
  local_c8 = pfVar8[1];
  fVar12 = *pfVar8;
  local_c4 = pfVar8[2];
  iVar11 = (&DAT_00b7cd98)[uVar17 * 100];
  piVar1 = *(int **)(iVar11 + 0x480);
  if (piVar1 == (int *)0x0) {
    iVar9 = 0;
  }
  else {
    iVar9 = *piVar1;
  }
  local_cc = fVar12;
  if (2 < *(int *)(iVar9 + 0x2c)) {
    piVar1 = *(int **)(iVar11 + 0x480);
    if (piVar1 == (int *)0x0) {
      iVar11 = 0;
    }
    else {
      iVar11 = *piVar1;
    }
    if (((DAT_00c0ec68 < (int)(uint)*(byte *)(iVar11 + 0x19)) &&
        (cVar5 = thunk_FUN_01563620(), cVar5 == '\0')) &&
       (iVar11 = (&DAT_00b7cd98)[uVar17 * 100], (*(uint *)(iVar11 + 0x46c) & 0x100) == 0)) {
      piVar1 = *(int **)(iVar11 + 0x480);
      if (piVar1 == (int *)0x0) {
        iVar11 = 0;
      }
      else {
        iVar11 = *piVar1;
      }
      if ((((int)(uint)*(byte *)(iVar11 + 0x1a) <= DAT_00969098) ||
          (local_128 = (float)(uint)*(ushort *)(&DAT_00b7cec8 + uVar17 * 400),
          (float)(int)local_128 * DAT_008a5b20 < (float)DAT_00969094 !=
          ((float)(int)local_128 * DAT_008a5b20 == (float)DAT_00969094))) ||
         (DAT_008a5b24 <=
          DAT_009690ac + DAT_009690a8 + DAT_009690a0 + DAT_0096909c + DAT_00969094 + DAT_00969098))
      {
        bVar3 = true;
        fVar19 = (float10)FUN_006116c0();
        param_1 = (float)(fVar19 * (float10)_DAT_0086c850);
        fVar19 = (float10)FUN_006116c0();
        param_2 = (float)(fVar19 * (float10)_DAT_0086d284);
      }
    }
  }
  cVar5 = FUN_00441c10();
  if (((cVar5 != '\0') && (_DAT_00858b1c < DAT_008d2530)) && (DAT_00c0ec68 < 1)) {
    bVar3 = true;
  }
  local_120 = (float)_DAT_008d2538;
  thunk_FUN_015635c0();
  fVar2 = _DAT_00c0bc40 + _DAT_00c0bc44 + _DAT_00c0bc48 + _DAT_00c0e978;
  if (fVar2 <= local_120) {
    local_120 = fVar2;
  }
  if (DAT_00b72914 != 0) {
    local_120 = (float)DAT_008d253c;
  }
  uVar10 = FUN_0072dd90();
  fVar2 = _DAT_00858624;
  if ((char)uVar10 != '\0') {
    fVar2 = _DAT_00858cc8;
  }
  if ((float)DAT_00c0ec28 < fVar2 * DAT_008d2530 * local_120) {
    if (bVar3) goto LAB_00614972;
    uVar15 = (uint3)(CONCAT22((short)((uint)uVar10 >> 0x10),
                              (ushort)(local_c4 < _DAT_00858f4c) << 8 |
                              (ushort)(NAN(local_c4) || NAN(_DAT_00858f4c)) << 10 |
                              (ushort)(local_c4 == _DAT_00858f4c) << 0xe) >> 8);
    if (local_c4 < _DAT_00858f4c || (local_c4 == _DAT_00858f4c) != 0) {
      iVar11 = (uint)uVar15 << 8;
    }
    else {
      iVar11 = CONCAT31(uVar15,1);
    }
    cVar5 = FUN_0060fbd0(&local_10c,&local_e8,iVar11,_DAT_00858f4c < local_c4);
    if (cVar5 == '\0') goto LAB_00615957;
    if (((local_10c == 4) || (local_10c == 5)) &&
       (fVar19 = (float10)FUN_0041bd90(0,0x3f800000), (float10)_DAT_00858c20 < fVar19)) {
      FUN_00613180(&local_11c,&local_108);
      if ((local_11c == -NAN) || (local_108 == -NAN)) goto LAB_00615957;
      local_10c = *(uint *)((&DAT_00a9b0c8)[(int)local_11c] + 0x28);
      fVar18 = local_11c;
    }
    if (0 < (int)DAT_008d2534) {
      local_10c = DAT_008d2534;
    }
    if (((int)local_10c < 7) || (0x10 < (int)local_10c)) goto LAB_00614983;
    local_120 = (float)FUN_00610db0();
  }
  else {
    if (!bVar3) goto LAB_00615957;
LAB_00614972:
    local_10c = 6;
    local_e8 = 0;
LAB_00614983:
    local_120 = 1.4013e-45;
  }
  local_128 = param_1;
  local_11c = param_2;
  if ((6 < (int)local_10c) && ((int)local_10c < 0x11)) {
    local_128 = param_1 + _DAT_00858ca4;
    local_11c = param_2 + _DAT_00858ca4;
  }
  if ((local_10c == 6) && (iVar11 = FUN_0056e230(0xffffffff), 0 < *(int *)(iVar11 + 0x2c))) {
    uVar10 = 1;
  }
  else {
    uVar10 = 0;
  }
  cVar5 = FUN_0044e790(fVar12,local_c8,local_128,local_11c,param_3,param_4,&local_118,&local_d8,
                       &local_d4,local_98,uVar10,0);
  if (cVar5 != '\0') {
    bVar6 = *(byte *)(*(int *)(&DAT_0096f854 + (local_d4 & 0xffff) * 4) + 0x1a +
                     (local_d4 >> 0x10) * 0x1c) & 0xf;
    bVar16 = *(byte *)(*(int *)(&DAT_0096f854 + (local_d8 & 0xffff) * 4) + 0x1a +
                      (local_d8 >> 0x10) * 0x1c) & 0xf;
    if (bVar16 < bVar6) {
      bVar6 = bVar16;
    }
    uVar17 = _rand();
    if ((uVar17 & 0xf) <= (uint)bVar6) {
      pfVar8 = &local_114;
      pfVar20 = &local_118;
      iVar11 = _rand();
      FUN_0044da30(local_d8,local_d4,iVar11,pfVar20,pfVar8);
      fVar12 = local_108;
      if (((int)local_10c < 7) || (0x10 < (int)local_10c)) {
        if (((int)fVar18 < 0) || ((int)local_108 < 0)) {
          local_108 = 0.0;
          if (0 < (int)local_120) {
            do {
              fVar12 = local_d0;
              fVar18 = local_108;
              if (local_10c == 6) {
                if (local_e8 == 4) {
                  if (DAT_008e6328 != '\x01') break;
                  uVar10 = 0x1d;
LAB_00615087:
                  iVar11 = FUN_00743c60(uVar10,1);
                  cVar5 = (&DAT_008e4cd0)[*(int *)(iVar11 + 0xc) * 0x14];
                }
                else {
                  if (local_e8 != 2) {
                    if (local_e8 != 5) goto LAB_0061512d;
                    if ((DAT_008e633c == '\x01') &&
                       (iVar11 = FUN_00743c60(0x1d,1),
                       (&DAT_008e4cd0)[*(int *)(iVar11 + 0xc) * 0x14] == '\x01')) {
                      uVar10 = 0x10;
                      goto LAB_00615087;
                    }
                    break;
                  }
                  if (DAT_008e6314 != '\x01') break;
                  iVar11 = FUN_00743c60(0x1c,1);
                  cVar5 = (&DAT_008e4cd0)[*(int *)(iVar11 + 0xc) * 0x14];
                }
                if (cVar5 != '\x01') break;
              }
              else if (*(int *)((&DAT_00a9b0c8)[local_e8] + 0x1c) == 0) break;
LAB_0061512d:
              local_110 = local_110 + _DAT_00858cb0;
              if (((int)fVar18 < (int)local_120) && (_rand(), fVar12 != 0.0)) {
                fVar2 = (_DAT_00858624 + (float)(int)local_108) * _DAT_00858f34;
                fVar4 = (float)(int)local_108 * _DAT_00858f34;
                local_128 = fVar2;
                local_11c = fVar4;
                fVar19 = (float10)FUN_0041bd90(fVar4,fVar2);
                local_11c = (float)fVar19;
                fVar19 = (float10)FUN_0041bd90(fVar4,fVar2);
                local_128 = (float)fVar19;
                uVar17 = _rand();
                if ((uVar17 & 1) != 0) {
                  local_11c = -local_11c;
                }
                uVar17 = _rand();
                local_114 = local_128;
                if ((uVar17 & 1) != 0) {
                  local_114 = -local_128;
                }
                if (*(int *)((int)fVar12 + 0x14) == 0) {
                  pfVar8 = (float *)((int)fVar12 + 4);
                }
                else {
                  pfVar8 = (float *)(*(int *)((int)fVar12 + 0x14) + 0x30);
                }
                local_118 = local_11c + *pfVar8;
                if (*(int *)((int)fVar12 + 0x14) == 0) {
                  iVar11 = (int)fVar12 + 4;
                }
                else {
                  iVar11 = *(int *)((int)fVar12 + 0x14) + 0x30;
                }
                local_114 = local_114 + *(float *)(iVar11 + 4);
              }
              cVar5 = FUN_00616860(&local_118,0xbf800000,0xffffffff,0,1,1,1);
              if (cVar5 == '\0') break;
              local_11c = (float)((int)fVar18 + 1);
              if ((int)local_11c < (int)local_120) {
                fVar19 = (float10)FUN_005696c0(local_118,local_114,local_110 + _FUN_00858ca0,
                                               &cStack_102,0);
                if (cStack_102 == '\0') break;
                if ((float10)local_110 <= fVar19 + (float10)_DAT_00858cb0) {
                  local_110 = (float)(fVar19 + (float10)_DAT_00858cb0);
                }
              }
              cVar7 = '\x01';
              cVar5 = FUN_00420d40(&local_118,0x40000000);
              if (cVar5 == '\0') {
LAB_006152bf:
                if (*(int *)((&DAT_00a9b0c8)[local_e8] + 0x2c) == 0x28) {
                  cVar7 = FUN_006114c0(&local_118);
                }
              }
              else {
                local_128 = SQRT((local_114 - local_c8) * (local_114 - local_c8) +
                                 (local_118 - local_cc) * (local_118 - local_cc));
                fVar19 = (float10)FUN_006116c0();
                if (fVar19 * (float10)_DAT_0086c850 <= (float10)local_128) goto LAB_006152bf;
                cVar7 = '\0';
              }
              iVar11 = local_e8;
              cVar5 = FUN_00611760(local_e8);
              uVar17 = local_10c;
              if ((cVar5 != '\0') && ((DAT_00b70153 < 8 || (0x13 < DAT_00b70153)))) {
                cVar7 = '\0';
              }
              if ((((local_10c == 0x11) &&
                   ((cVar7 == '\0' ||
                    (fVar19 = (float10)FUN_006143e0(0x11,local_118,local_114,local_110),
                    fVar19 < (float10)_DAT_00858ba4)))) || (cVar7 == '\0')) ||
                 ((((((6 < (int)uVar17 && ((int)uVar17 < 0x11)) && (uVar17 != 8)) &&
                    ((_DAT_0086d280 < local_118 && (local_118 < _DAT_0086d27c)))) &&
                   (_DAT_0086d278 < local_114)) && (local_114 < _DAT_0086d274)))) break;
              fVar18 = (float)thunk_FUN_004018c3(uVar17,iVar11,&local_118,1);
              local_121 = '\0';
              cVar5 = FUN_00611760(local_e8);
              if ((cVar5 == '\0') || (uVar17 = _rand(), (uVar17 & 3) == 0)) {
LAB_006157a7:
                cVar5 = FUN_00441c10();
                if (cVar5 == '\0') {
                  FUN_0046ff20(fVar18,0,0);
                }
                else {
                  uVar17 = _rand();
                  if ((uVar17 & 3) == 0) {
                    if (local_10c != 6) {
                      local_128 = (float)FUN_005a1ee0(0x17c);
                      uStack_4 = 7;
                      if (local_128 == 0.0) {
                        uVar10 = 0;
                      }
                      else {
                        uVar10 = FUN_005a1d70(DAT_008cd5a8,1);
                      }
                      uStack_4 = 0xffffffff;
                      FUN_00563220(uVar10);
                      uVar21 = FUN_00673d00(fVar18);
                      FUN_00681af0(uVar21,4,0);
                      uStack_b4 = 0;
                      uStack_b0 = 0x3ee66666;
                      uStack_ac = 0x3eb33333;
                      local_128 = (float)FUN_0061a5a0(0x3c);
                      uStack_4 = 8;
                      if (local_128 == 0.0) {
                        uVar10 = 0;
                      }
                      else {
                        uVar10 = FUN_006913a0(uVar10,&uStack_b4,1,1,0x13e,0x51,0);
                      }
                      uStack_4 = 0xffffffff;
                      FUN_00681b60(uVar10,4);
                    }
                  }
                  else {
                    local_128 = (float)FUN_0061a5a0(0x38);
                    uStack_4 = 6;
                    if (local_128 == 0.0) {
                      uVar10 = 0;
                    }
                    else {
                      uVar21 = 1;
                      uVar10 = FUN_00407180(0,8,1);
                      uVar10 = thunk_FUN_0156f300(6,uVar10,uVar21);
                    }
                    uStack_4 = 0xffffffff;
                    FUN_00681af0(uVar10,4,0);
                  }
                }
              }
              else {
                fStack_b8 = local_110 + _FUN_00858ca0;
                fStack_bc = local_114;
                fStack_c0 = local_118;
                local_128 = 0.0;
                FUN_005674e0(&fStack_c0,local_110 - _FUN_00858ca0,auStack_68,&local_128,1,0,0,0,0,0,
                             0);
                if ((local_128 == 0.0) ||
                   (((((cVar5 = FUN_0055e750(cStack_45), cVar5 == '\0' && (cStack_45 != '\"')) &&
                      (cStack_45 != -0x60)) && (DAT_00969159 == '\0')) ||
                    ((cVar5 = FUN_00632140(), cVar5 == '\0' && (DAT_00969159 == '\0'))))))
                goto LAB_006157a7;
                bVar3 = true;
                local_100[3] = 0.0;
                local_100[4] = 0.0;
                cVar5 = FUN_00616860(&local_118,0x40400000,2,local_100 + 3,1,1,1);
                if (cVar5 != '\0') {
                  if ((local_100[3] != 0.0) && (local_100[3] != fVar18)) {
                    bVar3 = false;
                  }
                  if ((local_100[4] != 0.0) && (local_100[4] != fVar18)) {
                    bVar3 = false;
                  }
                }
                if (cStack_45 != -0x60) {
                  local_121 = '\x01';
                }
                if (!bVar3) goto LAB_006157a7;
                if (*(int *)((int)fVar18 + 0x14) == 0) {
                  pfVar8 = (float *)((int)fVar18 + 4);
                }
                else {
                  pfVar8 = (float *)(*(int *)((int)fVar18 + 0x14) + 0x30);
                }
                fStack_e4 = *pfVar8;
                fStack_e0 = pfVar8[1];
                fStack_dc = pfVar8[2];
                fStack_a0 = fStack_dc + _DAT_0085862c;
                fStack_a8 = fStack_e4;
                fStack_a4 = fStack_e0;
                cVar5 = FUN_005674e0(&fStack_a8,0xc1200000,auStack_94,auStack_9c,1,0,0,0,1,0,0);
                if ((cVar5 != '\0') &&
                   (_DAT_00858ef0 < (fStack_84 + fStack_80) * DAT_00858b50 + fStack_7c)) {
                  fVar19 = (float10)FUN_0041bd90(0,0x3f800000);
                  fVar19 = fVar19 * (float10)_DAT_00858cbc;
                  fVar12 = (float)fVar19;
                  *(float *)((int)fVar18 + 0x55c) = (float)fVar19;
                  *(float *)((int)fVar18 + 0x558) = (float)fVar19;
                  local_128 = fVar12;
                  FUN_0043e0c0(fVar12);
                  iVar11 = 0;
                  if (local_121 != '\0') {
                    fStack_dc = fStack_8c + _DAT_00858cec;
                    iVar11 = FUN_006eaba0(&fStack_e4,0xb);
                    if (iVar11 != 0) {
                      FUN_0043e0c0(fVar12);
                      iVar9 = *(int *)(iVar11 + 0x14);
                      *(float *)(iVar9 + 0x20) = fStack_84;
                      *(float *)(iVar9 + 0x24) = fStack_80;
                      *(float *)(iVar9 + 0x28) = fStack_7c;
                      puVar14 = *(undefined4 **)(iVar11 + 0x14);
                      puVar13 = (undefined4 *)FUN_0059c730(auStack_18,puVar14 + 8,puVar14 + 4);
                      *puVar14 = *puVar13;
                      puVar14[1] = puVar13[1];
                      puVar14[2] = puVar13[2];
                      iVar9 = *(int *)(iVar11 + 0x14);
                      puVar14 = (undefined4 *)FUN_0059c730(auStack_30,iVar9 + 0x20,iVar9);
                      *(undefined4 *)(iVar9 + 0x10) = *puVar14;
                      *(undefined4 *)(iVar9 + 0x14) = puVar14[1];
                      *(undefined4 *)(iVar9 + 0x18) = puVar14[2];
                      thunk_FUN_01569bf0();
                      FUN_00532b00();
                      uVar17 = _rand();
                      if ((uVar17 & 3) == 0) {
                        uVar10 = *(undefined4 *)(iVar11 + 0x14);
                        local_100[0] = fStack_e4;
                        local_100[1] = fStack_e0;
                        local_100[2] = fStack_dc;
                        fVar19 = (float10)FUN_0041bd90(0xbf000000,0x3f000000);
                        uVar10 = FUN_0040fec0(auStack_3c,uVar10,(float)fVar19);
                        FUN_00411a00(uVar10);
                        iVar9 = *(int *)(iVar11 + 0x14);
                        fVar19 = (float10)FUN_0041bd90(0xbf800000,0x3f800000);
                        uVar10 = FUN_0040fec0(auStack_24,iVar9 + 0x10,(float)fVar19);
                        FUN_00411a00(uVar10);
                        FUN_006eaba0(local_100,6);
                      }
                    }
                  }
                  uVar17 = _rand();
                  if ((uVar17 & 3) == 0) {
                    local_128 = (float)FUN_0061a5a0(0x38);
                    uStack_4 = 5;
                    if (local_128 == 0.0) goto LAB_0061575b;
                    uVar10 = FUN_00631f80(iVar11,1);
                  }
                  else {
                    local_128 = (float)FUN_0061a5a0(0x38);
                    uStack_4 = 4;
                    if (local_128 == 0.0) {
LAB_0061575b:
                      uVar10 = 0;
                    }
                    else {
                      uVar10 = FUN_00631f80(iVar11,0);
                    }
                  }
                  uStack_4 = 0xffffffff;
                  FUN_00681af0(uVar10,3,0);
                }
              }
              if (local_108 == 0.0) {
                local_d0 = fVar18;
              }
              FUN_00732b00(*(undefined4 *)((int)fVar18 + 0x18),0);
              if ((((int)local_120 < (int)local_11c) || ((int)local_120 < 2)) ||
                 (local_108 = local_11c, (int)local_120 <= (int)local_11c)) break;
            } while( true );
          }
        }
        else {
          local_100[3] = local_118;
          local_100[4] = local_114;
          local_100[5] = local_110;
          cVar5 = FUN_00441c10();
          if (cVar5 == '\0') {
            cVar5 = FUN_00420d40(local_100 + 3,0x3fc00000);
            if (cVar5 != '\0') {
              iVar11 = FUN_0056e210(0xffffffff);
              if (*(int *)(iVar11 + 0x14) == 0) {
                pfVar8 = (float *)(iVar11 + 4);
              }
              else {
                pfVar8 = (float *)(*(int *)(iVar11 + 0x14) + 0x30);
              }
              local_128 = SQRT((local_100[4] - pfVar8[1]) * (local_100[4] - pfVar8[1]) +
                               (local_100[3] - *pfVar8) * (local_100[3] - *pfVar8));
              fVar19 = (float10)FUN_006116c0();
              if ((float10)local_128 < fVar19 * (float10)_DAT_0086c850) goto LAB_00615957;
            }
            local_128 = *(float *)(*(int *)((&DAT_00a9b0c8)[(int)fVar18] + 0x14) + 0x24);
            cVar5 = FUN_00616860(local_100 + 3,local_128,0xffffffff,0,1,1,1);
            if (cVar5 != '\0') {
              fVar19 = (float10)FUN_005696c0(local_100[3],local_100[4],local_100[5] + _DAT_00858624,
                                             &local_121,0);
              if (local_121 != '\0') {
                if ((float10)local_100[5] <= fVar19 + (float10)_DAT_00858624) {
                  local_120 = (float)(fVar19 + (float10)_DAT_00858624);
                }
                else {
                  local_120 = local_100[5];
                }
                if (*(int *)((&DAT_00a9b0c8)[(int)fVar18] + 0x1c) != 0) {
                  local_100[0] = local_100[3];
                  local_100[1] = local_100[4];
                  local_100[2] = local_120;
                  fVar18 = (float)thunk_FUN_004018c3(4,fVar18,local_100,1);
                  if ((fVar18 != 0.0) &&
                     (FUN_00732b00(*(undefined4 *)((int)fVar18 + 0x18),0),
                     *(int *)((&DAT_00a9b0c8)[(int)fVar12] + 0x1c) != 0)) {
                    local_100[0] = local_100[3];
                    local_100[1] = local_100[4];
                    local_100[2] = local_120;
                    fVar12 = (float)thunk_FUN_004018c3(5,fVar12,local_100,1);
                    if (fVar12 != 0.0) {
                      fVar19 = (float10)FUN_005e04b0();
                      local_120 = (float)fVar19;
                      fVar19 = (float10)FUN_005e04b0();
                      local_11c = (float)fVar19;
                      if (((_DAT_00858f34 <= local_120) && (_DAT_00858f34 <= local_11c)) &&
                         (ABS(local_120 - local_11c) <= _DAT_008631d0)) {
                        if (local_120 <= local_11c) {
                          local_128 = (float)FUN_0061a5a0(0x20);
                          uStack_4 = 2;
                          if (local_128 == 0.0) {
                            uVar10 = 0;
                          }
                          else {
                            uVar10 = FUN_006836f0(fVar18,0,1,1,0x41200000);
                          }
                          uStack_4 = 0xffffffff;
                          FUN_00681af0(uVar10,3,0);
                          local_128 = (float)FUN_0061a5a0(0x20);
                          uStack_4 = 3;
                          if (local_128 == 0.0) {
                            uVar10 = 0;
                          }
                          else {
                            uVar10 = FUN_006836f0(fVar12,1,1,1,0x41200000);
                          }
                        }
                        else {
                          local_128 = (float)FUN_0061a5a0(0x20);
                          uStack_4 = 0;
                          if (local_128 == 0.0) {
                            uVar10 = 0;
                          }
                          else {
                            uVar10 = FUN_006836f0(fVar12,0,1,1,0x41200000);
                          }
                          uStack_4 = 0xffffffff;
                          FUN_00681af0(uVar10,3,0);
                          local_128 = (float)FUN_0061a5a0(0x20);
                          uStack_4 = 1;
                          if (local_128 == 0.0) {
                            uVar10 = 0;
                          }
                          else {
                            uVar10 = FUN_006836f0(fVar18,1,1,1,0x41200000);
                          }
                        }
                        uStack_4 = 0xffffffff;
                        FUN_00681af0(uVar10,3,0);
                        local_100[1] = DAT_00c1970c;
                        local_100[0] = DAT_00c19708;
                        local_100[2] = 0.0;
                        if (*(int *)((int)fVar18 + 0x14) == 0) {
                          iVar11 = (int)fVar18 + 4;
                        }
                        else {
                          iVar11 = *(int *)((int)fVar18 + 0x14) + 0x30;
                        }
                        FUN_0040fe30(&fStack_e4,iVar11,local_100);
                        fVar19 = (float10)FUN_005696c0(fStack_e4,fStack_e0,fStack_dc + _DAT_00858624
                                                       ,&cStack_101,0);
                        if (cStack_101 == '\0') {
LAB_00614f9e:
                          FUN_00610f20(fVar18);
                          FUN_00610f20(fVar12);
                        }
                        else {
                          if ((float10)fStack_dc <= fVar19 + (float10)_DAT_00858624) {
                            local_128 = (float)(fVar19 + (float10)_DAT_00858624);
                          }
                          else {
                            local_128 = fStack_dc;
                          }
                          thunk_FUN_01566e30(fStack_e4,fStack_e0,local_128);
                          local_100[0] = 0.0;
                          local_100[1] = 0.0;
                          local_100[2] = 0.0;
                          FUN_00616860(&fStack_e4,
                                       *(undefined4 *)
                                        (*(int *)((&DAT_00a9b0c8)[(int)local_108] + 0x14) + 0x24),3,
                                       local_100,1,1,1);
                          iVar11 = 0;
                          do {
                            fVar2 = local_100[iVar11];
                            if (((fVar2 != 0.0) && (fVar2 != fVar18)) && (fVar2 != fVar12))
                            goto LAB_00614f9e;
                            iVar11 = iVar11 + 1;
                          } while (iVar11 < 3);
                          FUN_00732b00(*(undefined4 *)((int)fVar12 + 0x18),0);
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      else {
        FUN_006117d0(local_10c,local_120,&local_118);
      }
    }
  }
LAB_00615957:
  FUN_00401f53();
  return;
}



/* function 006b7f90 FUN_006b7f90 */

void __fastcall FUN_006b7f90(int param_1)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  int unaff_retaddr;
  float fStack_114;
  float fStack_110;
  float fStack_10c;
  float fStack_108;
  float fStack_104;
  float fStack_100;
  undefined1 auStack_f4 [12];
  undefined1 auStack_e8 [68];
  undefined4 local_a4;
  undefined4 local_a0 [17];
  undefined4 local_5c;
  undefined4 local_58 [19];
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_008482ce;
  pvStack_c = ExceptionList;
  if ((*(char *)(param_1 + 0x7b5) != '\0') || (*(char *)(param_1 + 0x7b4) != '\0')) {
    local_a4 = 0;
    local_a0[0] = 0;
    local_5c = 0;
    local_58[0] = 0;
    local_4 = 1;
    if (*(int *)(param_1 + 0x5a4) != 0) {
      ExceptionList = &pvStack_c;
      FUN_0059bd10(*(int *)(param_1 + 0x5a4) + 0x10,0);
      FUN_0059bbc0(*(undefined4 *)(param_1 + 0x14));
      thunk_FUN_0156ff00(local_a0);
      uVar2 = FUN_00734a40(*(undefined4 *)(unaff_retaddr + 0x18));
      sVar1 = *(short *)(param_1 + 0x22);
      iVar3 = *(int *)((&DAT_00a9b0c8)[sVar1] + 0x5c);
      fStack_108 = *(float *)(iVar3 + 0x78);
      fStack_104 = *(float *)(iVar3 + 0x7c);
      fStack_100 = *(float *)(iVar3 + 0x80);
      if (((fStack_108 == DAT_00858b50) && (fStack_104 == DAT_00858b50)) &&
         (fStack_100 == DAT_00858b50)) {
        if (sVar1 == 0x1fe) {
          fStack_108 = DAT_008d3250;
          fStack_104 = DAT_008d3254;
          fStack_100 = DAT_008d3258;
        }
        else if (sVar1 == 0x1fd) {
          fStack_108 = DAT_008d325c;
          fStack_104 = DAT_008d3260;
          fStack_100 = DAT_008d3264;
        }
        else {
          fStack_108 = DAT_008d3244;
          fStack_104 = DAT_008d3248;
          fStack_100 = DAT_008d324c;
        }
      }
      else {
        iVar3 = FUN_007c51a0(uVar2,0x18);
        iVar4 = FUN_007c5120(uVar2);
        fStack_114 = DAT_008d3274;
        fStack_10c = (float)DAT_008d327c;
        fStack_110 = (float)DAT_008d3278;
        FUN_0059c050(iVar4 + iVar3 * 0x40,0);
        puStack_8._0_1_ = 2;
        pfVar5 = (float *)FUN_0059c790(auStack_f4,local_58,&fStack_114);
        fStack_114 = *pfVar5;
        fStack_110 = pfVar5[1];
        fStack_10c = pfVar5[2];
        pfVar5 = (float *)FUN_0059c810(auStack_f4,&fStack_114,auStack_e8);
        fStack_114 = *pfVar5;
        fStack_108 = fStack_114 + fStack_108;
        fStack_110 = pfVar5[1];
        fStack_10c = pfVar5[2];
        fStack_104 = fStack_110 + fStack_104;
        puStack_8 = (undefined1 *)CONCAT31(puStack_8._1_3_,1);
        fStack_100 = fStack_10c + fStack_100;
        FUN_0059acd0();
      }
      FUN_00403c8d();
      return;
    }
    local_4 = 0;
    ExceptionList = &pvStack_c;
    FUN_0059acd0();
    local_4 = 0xffffffff;
    FUN_0059acd0();
  }
  ExceptionList = pvStack_c;
  return;
}



/* function 006c94a0 FUN_006c94a0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_006c94a0(int *param_1)

{
  short sVar1;
  char cVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  float *pfVar7;
  undefined4 uVar8;
  int *piVar9;
  float10 fVar10;
  float10 fVar11;
  float fVar12;
  int iVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fStack_130;
  int iStack_12c;
  float fStack_128;
  int iStack_11c;
  undefined4 uStack_118;
  float fStack_114;
  undefined4 uStack_110;
  undefined4 local_10c;
  int local_fc;
  undefined1 auStack_f8 [8];
  float fStack_f0;
  float fStack_ec;
  float fStack_e0;
  float fStack_dc;
  float fStack_d4;
  float fStack_d0;
  float fStack_cc;
  float fStack_c4;
  undefined4 uStack_b4;
  undefined4 local_94;
  undefined4 local_90 [27];
  undefined1 uStack_24;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_008485ab;
  pvStack_c = ExceptionList;
  local_94 = 0;
  local_90[0] = 0;
  iVar6 = (&DAT_00a9b0c8)[*(short *)((int)param_1 + 0x22)];
  local_4 = 0;
  local_10c = 0;
  ExceptionList = &pvStack_c;
  local_fc = iVar6;
  FUN_00535300();
  FUN_006d6480();
  if (*(short *)((int)param_1 + 0x22) == 0x21b) {
    (**(code **)(*param_1 + 0x114))();
  }
  if ((*(byte *)((int)param_1 + 0x42b) & 1) != 0) {
    (**(code **)(*param_1 + 0xd0))();
    iVar5 = 0;
    pfVar7 = (float *)(param_1 + 0x20e);
    pfVar4 = (float *)(param_1 + 0x1ce);
    do {
      fVar12 = _DAT_00858624 - pfVar7[0x10] / pfVar7[0x14];
      fStack_128 = (pfVar7[-0x19] - fVar12) / (_DAT_00858624 - fVar12);
      FUN_004c7d20(iVar5,auStack_f8,1);
      fVar12 = fStack_f0 + *(float *)(param_1[0xe1] + 0xb8);
      if (DAT_00858b50 < fStack_128) {
        fVar12 = fVar12 - fStack_128 * pfVar7[0x10];
      }
      if ((fVar12 <= *pfVar7) &&
         (((param_1[0x10] & 0x4000000U) == 0 || ((param_1[0xe3] & 0x20000U) == 0)))) {
        fVar12 = (fVar12 - *pfVar7) * _DAT_00858f34 + *pfVar7;
      }
      *pfVar7 = fVar12;
      if (*(short *)((int)param_1 + 0x22) == 0x250) {
        if (_DAT_00858624 <= pfVar7[-0x19]) {
          fVar10 = (float10)pfVar7[-4] * (float10)_DAT_00858ef0;
        }
        else {
          iVar6 = param_1[5];
          fStack_130 = *(float *)(iVar6 + 0x14) * *pfVar4 +
                       pfVar4[-1] * *(float *)(iVar6 + 0x10) + *(float *)(iVar6 + 0x18) * pfVar4[1];
          if (fStack_130 < _DAT_00858c1c) {
            fStack_130 = -1.0;
            fVar10 = (float10)FUN_00821e70();
            fVar10 = -fVar10;
          }
          else if (fStack_130 <= _DAT_00858624) {
            fVar10 = (float10)FUN_00821e70();
            fVar10 = -fVar10;
          }
          else {
            fStack_130 = 1.0;
            fVar10 = (float10)FUN_00821e70();
            fVar10 = -fVar10;
          }
        }
        pfVar7[-4] = (float)fVar10;
      }
      iVar5 = iVar5 + 1;
      pfVar7 = pfVar7 + 1;
      pfVar4 = pfVar4 + 0xb;
      iVar6 = local_fc;
    } while (iVar5 < 4);
  }
  uVar8 = 1;
  thunk_FUN_00401a84(4,1);
  iVar5 = 7;
  thunk_FUN_00401a84(7,1);
  fVar12 = 2.8026e-45;
  thunk_FUN_00401a84(2,1);
  if (*(short *)((int)param_1 + 0x22) == 0x208) {
    uVar8 = 3;
  }
  thunk_FUN_00401a84(5,uVar8);
  fVar15 = DAT_00b7cb5c * (float)param_1[0x271] + (float)param_1[0x272];
  param_1[0x272] = (int)fVar15;
  if (_DAT_00858cbc < fVar15) {
    fVar15 = (float)param_1[0x272];
    do {
      fVar15 = fVar15 - _DAT_00858cbc;
    } while (_DAT_00858cbc < fVar15);
    param_1[0x272] = (int)fVar15;
  }
  if ((*(byte *)((int)param_1 + 0x36) & 0xf8) < 0x19) {
    if (param_1[0x1a2] != 0) {
      FUN_0059bd10(param_1[0x1a2] + 0x10,0);
      FUN_0059bbb0();
      iVar13 = *(int *)(iVar6 + 0x5c);
      if (((*(float *)(iVar13 + 0x84) != DAT_00858b50) ||
          (*(float *)(iVar13 + 0x88) != DAT_00858b50)) ||
         (*(float *)(iVar13 + 0x8c) != DAT_00858b50)) {
        FUN_0059c910();
      }
      FUN_0059c600(&stack0xfffffebc,_DAT_00871914 * _DAT_008595ec * (float)param_1[0x262]);
      FUN_0059c080(uStack_b4);
      if ((*(short *)((int)param_1 + 0x22) == 0x21b) && (param_1[0x1aa] != 0)) {
        FUN_0059bd10(param_1[0x1aa] + 0x10,0);
        FUN_0059bbb0();
        FUN_0059c080(uStack_b4);
      }
    }
    if (param_1[0x1a6] != 0) {
      fVar15 = 1.0;
      fVar14 = 0.0;
      if (((_DAT_00858624 < *(float *)(param_1[0xe2] + 0x34)) &&
          (ABS((float)param_1[0x273]) < _DAT_00858624)) &&
         ((param_1[0x1a7] != 0 || (param_1[0x1a8] != 0)))) {
        fVar15 = (_DAT_00858624 - ABS((float)param_1[0x273])) * _DAT_00871920 + _DAT_00858624;
        fVar14 = (_DAT_00858624 - ABS((float)param_1[0x273])) * _DAT_00871924;
      }
      FUN_0059bd10(param_1[0x1a6] + 0x10,0);
      FUN_0059bbb0();
      iVar13 = *(int *)(iVar6 + 0x5c);
      if (((*(float *)(iVar13 + 0x6c) == DAT_00858b50) &&
          (*(float *)(iVar13 + 0x70) == DAT_00858b50)) &&
         (*(float *)(iVar13 + 0x74) == DAT_00858b50)) {
        fVar16 = 1.0;
      }
      else {
        fVar16 = *(float *)(iVar13 + 0x6c) - fStack_c4;
        FUN_0059c910();
      }
      FUN_0059c600(&stack0xfffffebc,_DAT_0087191c * _DAT_008595ec * (float)param_1[0x264] + fVar14);
      FUN_0059c080(uStack_b4);
      if (_DAT_00858624 < fVar15) {
        FUN_0059bb60();
        if (fVar16 == _DAT_00858624) {
          fStack_e0 = fStack_e0 * fVar15;
        }
        else {
          cVar2 = FUN_004c7dd0(&uStack_118,0x14);
          if (cVar2 != '\0') {
            fStack_114 = (_DAT_00858624 - fVar15) * *(float *)(iVar5 + 0x10) * _DAT_00871928 +
                         fStack_114;
            FUN_0059af80(uStack_118,fStack_114,uStack_110);
          }
        }
        FUN_0059bbb0();
      }
      if (param_1[0x1a5] != 0) {
        FUN_0059bd10(param_1[0x1a5] + 0x10,0);
        FUN_0059bbb0();
        fVar16 = fVar16 * _DAT_00858c1c;
        FUN_0059c600(&stack0xfffffebc,_DAT_0087191c * _DAT_008595ec * (float)param_1[0x264] - fVar14
                    );
        FUN_0059c080(uStack_b4);
        if (_DAT_00858624 < fVar15) {
          FUN_0059bb60();
          if (fVar16 == _DAT_00858c1c) {
            fStack_e0 = fStack_e0 * fVar15;
          }
          else {
            cVar2 = FUN_004c7dd0(&uStack_118,0x13);
            if (cVar2 != '\0') {
              fStack_114 = (_DAT_00858624 - fVar15) * *(float *)(iVar5 + 0x10) * _DAT_00871928 +
                           fStack_114;
              FUN_0059af80(uStack_118,fStack_114,uStack_110);
            }
          }
          FUN_0059bbb0();
        }
      }
    }
    if (param_1[0x1a4] != 0) {
      FUN_0059bd10(param_1[0x1a4] + 0x10,0);
      FUN_0059bbb0();
      iVar6 = *(int *)(iVar6 + 0x5c);
      if (((*(float *)(iVar6 + 0x78) != DAT_00858b50) || (*(float *)(iVar6 + 0x7c) != DAT_00858b50))
         || (*(float *)(iVar6 + 0x80) != DAT_00858b50)) {
        FUN_0059c910();
      }
      FUN_0059c600(&stack0xfffffebc,-(_DAT_00871918 * _DAT_008595ec * (float)param_1[0x263]));
      FUN_0059c080(uStack_b4);
      if (param_1[0x1a3] != 0) {
        FUN_0059bd10(param_1[0x1a3] + 0x10,0);
        FUN_0059bbb0();
        FUN_0059c600(&stack0xfffffebc,_DAT_00871918 * _DAT_008595ec * (float)param_1[0x263]);
        FUN_0059c080(uStack_b4);
      }
    }
  }
  iVar5 = 0xc;
  iVar6 = 0xd;
  fVar15 = 1.0;
  while( true ) {
    if (param_1[iVar5 + 0x192] != 0) {
      thunk_FUN_00403907(param_1[iVar5 + 0x192],1,
                         fVar15 * (float)param_1[0x272] + fVar15 * (float)param_1[0x272],1);
      iStack_12c = 0;
      FUN_007f1200(param_1[iVar5 + 0x192],&LAB_006a0750,&iStack_12c);
      if (iStack_12c != 0) {
        FUN_006d2960(iStack_12c,0xff);
      }
    }
    if (param_1[iVar6 + 0x192] != 0) {
      thunk_FUN_00403907(param_1[iVar6 + 0x192],1,-(fVar15 * (float)param_1[0x272]),1);
      iStack_12c = 0;
      FUN_007f1200(param_1[iVar6 + 0x192],&LAB_006a0750,&iStack_12c);
      if (iStack_12c != 0) {
        FUN_006d2960(iStack_12c,0);
      }
    }
    if (iVar5 != 0xc) break;
    iVar5 = 0xe;
    iVar6 = 0xf;
    fVar15 = -1.0;
  }
  iVar6 = -1;
  fVar15 = 0.0;
  fVar14 = 0.0;
  switch(*(undefined2 *)((int)param_1 + 0x22)) {
  case 0x1dc:
    uVar8 = 1;
    fVar16 = -DAT_0087192c;
    break;
  default:
    goto switchD_006c9daa_caseD_1dd;
  case 0x207:
  case 0x241:
    fVar16 = -DAT_0087192c;
    uVar8 = 1;
    iVar6 = 0;
    fVar15 = DAT_00871938;
    break;
  case 0x208:
    uVar8 = 0;
    iVar6 = 0;
    fVar15 = DAT_00871934;
    fVar14 = DAT_00871938;
    fVar16 = DAT_00871930;
    break;
  case 0x229:
    uVar8 = 0;
    fVar16 = DAT_00871940;
    break;
  case 0x250:
    uVar8 = 0;
    iVar6 = 0;
    fVar15 = -DAT_0087193c;
    fVar16 = DAT_0087193c;
  }
  thunk_FUN_00403907(param_1[0x1a7],uVar8,ABS((float)param_1[0x273]) * fVar16,1);
  thunk_FUN_00403907(param_1[0x1a8],uVar8,ABS((float)param_1[0x273]) * fVar12,1);
  if ((-1 < iVar6) &&
     (thunk_FUN_00403907(param_1[0x1a9],iVar6,ABS((float)param_1[0x273]) * fVar15,1),
     (float)_DAT_00859ef8 < fVar14)) {
    thunk_FUN_00403907(param_1[0x1aa],iVar6,ABS((float)param_1[0x273]) * fVar14,1);
  }
switchD_006c9daa_caseD_1dd:
  sVar1 = *(short *)((int)param_1 + 0x22);
  if (sVar1 == 0x250) {
    thunk_FUN_00403907(param_1[0x1aa],0,(float)*(ushort *)(param_1 + 0x21b) * _DAT_008d33c0,1);
  }
  else if (sVar1 == 0x208) {
    fVar12 = ((float)*(ushort *)(param_1 + 0x21b) * _DAT_00858fe4) / (float)(int)DAT_008d33c4;
    thunk_FUN_00403907(param_1[0x198],0,fVar12,1);
    thunk_FUN_00403907(param_1[0x195],0,fVar12,1);
    if ((*(byte *)(param_1 + 0x10a) & 0x10) == 0) {
      piVar9 = param_1 + 0x27a;
      iVar6 = 4;
      do {
        if (*piVar9 != 0) {
          FUN_004aa3f0();
          *piVar9 = 0;
        }
        piVar9 = piVar9 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      if (param_1[0x160] != 0) {
        FUN_004aa3f0();
        param_1[0x160] = 0;
        param_1[0x261] = 0;
      }
    }
    else {
      fVar12 = ((float)param_1[0x265] + _DAT_00858624) * _DAT_00858b8c;
      if ((int)(uint)*(ushort *)(param_1 + 0x21b) < (int)DAT_008d33c8) {
        if (param_1[0x160] != 0) {
          FUN_004aa3f0();
          param_1[0x160] = 0;
          param_1[0x261] = 0;
        }
      }
      else {
        FUN_006b0690(fVar12,0x40000000);
      }
      iVar6 = param_1[0x198];
      iVar5 = param_1[0x195] + 0x10;
      iVar13 = 4;
      piVar9 = param_1 + 0x27a;
      do {
        if (((param_1[6] != 0) && (iVar3 = *(int *)(param_1[6] + 4) + 0x10, iVar3 != 0)) &&
           (*piVar9 == 0)) {
          iVar3 = FUN_004a9be0("jetthrust",&stack0xfffffec8,iVar3,0);
          *piVar9 = iVar3;
          if (iVar3 != 0) {
            FUN_004aa2f0();
            FUN_004aa910(1);
            FUN_004aa890();
          }
        }
        piVar9 = piVar9 + 1;
        iVar13 = iVar13 + -1;
      } while (iVar13 != 0);
      if (param_1[0x27a] != 0) {
        FUN_0059be30(local_90,param_1[5],iVar6 + 0x10);
        uStack_24 = 1;
        FUN_004aa630(local_90);
        FUN_004aa660(&stack0xfffffec8);
        FUN_004aa6c0(1,fVar12);
        uStack_24 = 0;
        FUN_0059acd0();
      }
      if (param_1[0x27b] != 0) {
        FUN_0059be30(local_90,param_1[5],iVar6 + 0x10);
        uStack_24 = 2;
        FUN_004aa630(local_90);
        FUN_004aa660(&stack0xfffffec8);
        FUN_004aa6c0(1,fVar12);
        uStack_24 = 0;
        FUN_0059acd0();
      }
      if (param_1[0x27c] != 0) {
        FUN_0059be30(local_90,param_1[5],iVar5);
        uStack_24 = 3;
        FUN_004aa630(local_90);
        FUN_004aa660(&stack0xfffffec8);
        FUN_004aa6c0(1,fVar12);
        uStack_24 = 0;
        FUN_0059acd0();
      }
      if (param_1[0x27d] != 0) {
        FUN_0059be30(local_90,param_1[5],iVar5);
        uStack_24 = 4;
        FUN_004aa630(local_90);
        FUN_004aa660(&stack0xfffffec8);
        FUN_004aa6c0(1,fVar12);
        uStack_24 = 0;
        FUN_0059acd0();
      }
    }
  }
  else if ((sVar1 == 0x21b) && (param_1[0x1a9] != 0)) {
    iVar6 = FUN_00535300();
    iVar6 = *(int *)(iVar6 + 0x2c);
    FUN_004c7d20(0,&stack0xfffffec8,0);
    FUN_0059bd10(param_1[0x1a9] + 0x10,0);
    pfVar7 = (float *)param_1[5];
    fVar12 = DAT_008d3414;
    if ((pfVar7[4] * (float)param_1[0x11] +
        pfVar7[5] * (float)param_1[0x12] + pfVar7[6] * (float)param_1[0x13]) * _DAT_008d3418 <=
        DAT_008d3414) {
      fVar12 = ((float)param_1[0x11] * pfVar7[4] +
               (float)param_1[0x12] * pfVar7[5] + (float)param_1[0x13] * pfVar7[6]) * _DAT_008d3418;
    }
    fStack_d4 = -DAT_008d3414;
    fStack_d0 = fStack_d4;
    if (fStack_d4 <= fVar12) {
      if (((float)param_1[0x11] * pfVar7[4] +
          (float)param_1[0x12] * pfVar7[5] + (float)param_1[0x13] * pfVar7[6]) * _DAT_008d3418 <=
          DAT_008d3414) {
        fStack_d0 = ((float)param_1[0x11] * pfVar7[4] +
                    (float)param_1[0x12] * pfVar7[5] + (float)param_1[0x13] * pfVar7[6]) *
                    _DAT_008d3418;
      }
      else {
        fStack_d0 = DAT_008d3414;
      }
    }
    fVar12 = DAT_008d3414;
    if ((*pfVar7 * (float)param_1[0x11] +
        (float)param_1[0x12] * pfVar7[1] + (float)param_1[0x13] * pfVar7[2]) * _DAT_008d3418 <=
        DAT_008d3414) {
      fVar12 = (*pfVar7 * (float)param_1[0x11] +
               (float)param_1[0x12] * pfVar7[1] + (float)param_1[0x13] * pfVar7[2]) * _DAT_008d3418;
    }
    if (fStack_d4 <= fVar12) {
      if (((float)param_1[0x11] * *pfVar7 +
          (float)param_1[0x12] * pfVar7[1] + (float)param_1[0x13] * pfVar7[2]) * _DAT_008d3418 <=
          DAT_008d3414) {
        fStack_d4 = ((float)param_1[0x11] * *pfVar7 +
                    (float)param_1[0x12] * pfVar7[1] + (float)param_1[0x13] * pfVar7[2]) *
                    _DAT_008d3418;
      }
      else {
        fStack_d4 = DAT_008d3414;
      }
    }
    fVar10 = (float10)FUN_00822130();
    iVar5 = *(int *)(iVar6 + 0x10);
    fVar11 = ((((float10)(float)param_1[0x20e] - (float10)(float)param_1[0x20f]) +
              ((float10)(float)param_1[0x210] - (float10)(float)param_1[0x211])) *
             (float10)_DAT_00858b8c) /
             ((float10)*(float *)(iVar5 + 4) - (float10)*(float *)(iVar5 + 0x24));
    if (fVar11 <= (float10)_DAT_008d340c) {
      if (fVar11 < (float10)-_DAT_008d340c) {
        fVar11 = (float10)-_DAT_008d340c;
      }
    }
    else {
      fVar11 = (float10)_DAT_008d340c;
    }
    fVar12 = (float)((float10)_DAT_00858624 - fVar10);
    fStack_dc = (float)((float10)fVar12 * fVar11 + (float10)fStack_dc * fVar10);
    iVar6 = *(int *)(iVar6 + 0x10);
    fVar11 = ((((float10)(float)param_1[0x210] - (float10)(float)param_1[0x20e]) +
              ((float10)(float)param_1[0x211] - (float10)(float)param_1[0x20f])) *
             (float10)_DAT_00858b8c) /
             ((float10)*(float *)(iVar6 + 0x60) - (float10)*(float *)(iVar6 + 0x20));
    if (fVar11 <= (float10)_DAT_008d3408) {
      if (fVar11 < (float10)-_DAT_008d3408) {
        fVar11 = (float10)-_DAT_008d3408;
      }
    }
    else {
      fVar11 = (float10)_DAT_008d3408;
    }
    fStack_ec = (float)((float10)fVar12 * fVar11 + (float10)fStack_ec * fVar10);
    fVar11 = (float10)_DAT_00858624 -
             (((float10)(float)param_1[0x211] + (float10)(float)param_1[0x20f] +
               (float10)(float)param_1[0x210] + (float10)(float)param_1[0x20e]) *
              (float10)_DAT_00858c84 - (float10)fStack_130) /
             ((float10)*(float *)(iStack_11c + 0x40) * (float10)_DAT_00858b8c);
    if ((float10)_DAT_008d3404 < fVar11) {
      fVar11 = (float10)_DAT_008d3404;
    }
    fStack_cc = (float)((float10)fVar12 * fVar11 + (float10)fStack_cc * fVar10);
    FUN_0059bbb0();
  }
  FUN_00407ebb();
  return;
}



/* function 00720930 FUN_00720930 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00720930(int param_1,undefined4 *param_2,float param_3,float param_4,undefined4 param_5,
                 char *param_6,float param_7)

{
  undefined4 *puVar1;
  float *pfVar2;
  short sVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  char cVar8;
  int *piVar9;
  char *pcVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  int iVar15;
  int local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_4;
  
  iVar15 = DAT_00b7cb84;
  if (DAT_00a43088 != '\x01') {
    iVar14 = 0;
    iVar12 = 0;
    piVar9 = &DAT_00c79be8;
    do {
      if ((*(char *)((int)piVar9 + 0x16) == '\x01') && (*piVar9 == param_1)) {
LAB_00720abe:
        if (iVar12 < 0x20) {
          iVar14 = iVar12 * 0x158;
          if (((&DAT_00c79bf8)[iVar12 * 0x56] == 3) != (bool)*param_6) {
            iVar15 = DAT_00b7cb84 + 10000;
            iVar11 = DAT_00b7cb84 + 20000;
            (&DAT_00c79bfe)[iVar14] = 2;
            (&DAT_00c79bf0)[iVar12 * 0x56] = iVar15;
            (&DAT_00c79bf4)[iVar12 * 0x56] = iVar11;
            return;
          }
          uVar13 = DAT_00b7cb84 - (&DAT_00c79bec)[iVar12 * 0x56];
          (&DAT_00c79bff)[iVar14] = 1;
          if (uVar13 < 0x65) {
            puVar1 = &DAT_00c79aa8 + iVar12 * 0x56 + (short)(&DAT_00c79bfc)[iVar12 * 0xac] * 3;
            *puVar1 = *param_2;
            puVar1[1] = param_2[1];
            puVar1[2] = param_2[2];
            return;
          }
          sVar3 = (&DAT_00c79bfc)[iVar12 * 0xac];
          (&DAT_00c79bec)[iVar12 * 0x56] = iVar15;
          if (0xe < sVar3) {
            (&DAT_00c79bec)[iVar12 * 0x56] = iVar15;
            (&DAT_00c79bfe)[iVar14] = 2;
            (&DAT_00c79bf0)[iVar12 * 0x56] = iVar15 + 10000;
            (&DAT_00c79bf4)[iVar12 * 0x56] = iVar15 + 20000;
            *param_6 = '\0';
            return;
          }
          sVar3 = sVar3 + 1;
          (&DAT_00c79bfc)[iVar12 * 0xac] = sVar3;
          puVar1 = &DAT_00c79aa8 + iVar12 * 0x56 + sVar3 * 3;
          *puVar1 = *param_2;
          puVar1[1] = param_2[1];
          puVar1[2] = param_2[2];
          pfVar2 = (float *)(&DAT_00c79aa8 +
                            iVar12 * 0x56 + (short)(&DAT_00c79bfc)[iVar12 * 0xac] * 3);
          fVar4 = pfVar2[1] - pfVar2[-2];
          fVar5 = pfVar2[-3] - *pfVar2;
          fVar7 = SQRT(fVar4 * fVar4 + fVar5 * fVar5);
          fVar6 = _DAT_00858624;
          if (fVar7 < DAT_00858b50 == (fVar7 == DAT_00858b50)) {
            fVar5 = (_DAT_00858624 / fVar7) * fVar5;
            fVar6 = (_DAT_00858624 / fVar7) * fVar4;
          }
          fVar7 = SQRT(param_4 * param_4 + param_3 * param_3);
          fVar4 = _DAT_00858624;
          if (fVar7 < DAT_00858b50 == (fVar7 == DAT_00858b50)) {
            param_4 = (_DAT_00858624 / fVar7) * param_4;
            fVar4 = (_DAT_00858624 / fVar7) * param_3;
          }
          fVar4 = ABS(fVar5 * param_4 + fVar6 * fVar4) + _DAT_00858624;
          (&DAT_00c79b68)[iVar12 * 0x56 + (int)(short)(&DAT_00c79bfc)[iVar12 * 0xac]] =
               fVar4 * fVar6 * param_7 * _DAT_00858b8c;
          (&DAT_00c79ba8)[iVar12 * 0x56 + (int)(short)(&DAT_00c79bfc)[iVar12 * 0xac]] =
               fVar4 * fVar5 * param_7 * _DAT_00858b8c;
          sVar3 = (&DAT_00c79bfc)[iVar12 * 0xac];
          if (sVar3 == 1) {
            (&DAT_00c79b68)[iVar12 * 0x56] = (&DAT_00c79b6c)[iVar12 * 0x56];
            (&DAT_00c79ba8)[iVar12 * 0x56] = (&DAT_00c79bac)[iVar12 * 0x56];
          }
          if (sVar3 < 9) {
            return;
          }
          *param_6 = '\0';
          return;
        }
        break;
      }
      if ((*(char *)((int)piVar9 + 0x16e) == '\x01') && (piVar9[0x56] == param_1)) {
        iVar12 = iVar12 + 1;
        goto LAB_00720abe;
      }
      if ((*(char *)((int)piVar9 + 0x2c6) == '\x01') && (piVar9[0xac] == param_1)) {
        iVar12 = iVar12 + 2;
        goto LAB_00720abe;
      }
      if ((*(char *)((int)piVar9 + 0x41e) == '\x01') && (piVar9[0x102] == param_1)) {
        iVar12 = iVar12 + 3;
        goto LAB_00720abe;
      }
      if ((*(char *)((int)piVar9 + 0x576) == '\x01') && (piVar9[0x158] == param_1)) {
        iVar12 = iVar12 + 4;
        goto LAB_00720abe;
      }
      if ((*(char *)((int)piVar9 + 0x6ce) == '\x01') && (piVar9[0x1ae] == param_1)) {
        iVar12 = iVar12 + 5;
        goto LAB_00720abe;
      }
      if ((*(char *)((int)piVar9 + 0x826) == '\x01') && (piVar9[0x204] == param_1)) {
        iVar12 = iVar12 + 6;
        goto LAB_00720abe;
      }
      if ((*(char *)((int)piVar9 + 0x97e) == '\x01') && (piVar9[0x25a] == param_1)) {
        iVar12 = iVar12 + 7;
        goto LAB_00720abe;
      }
      piVar9 = piVar9 + 0x2b0;
      iVar12 = iVar12 + 8;
    } while ((int)piVar9 < 0xc7c6e8);
    iVar15 = 0;
    pcVar10 = &DAT_00c79d56;
    do {
      if (pcVar10[-0x158] == '\0') {
LAB_00720d13:
        if (iVar15 < 0x20) goto LAB_00720e21;
        break;
      }
      if (*pcVar10 == '\0') {
        iVar15 = iVar15 + 1;
        goto LAB_00720d13;
      }
      if (pcVar10[0x158] == '\0') {
        iVar15 = iVar15 + 2;
        goto LAB_00720d13;
      }
      if (pcVar10[0x2b0] == '\0') {
        iVar15 = iVar15 + 3;
        goto LAB_00720d13;
      }
      if (pcVar10[0x408] == '\0') {
        iVar15 = iVar15 + 4;
        goto LAB_00720d13;
      }
      if (pcVar10[0x560] == '\0') {
        iVar15 = iVar15 + 5;
        goto LAB_00720d13;
      }
      if (pcVar10[0x6b8] == '\0') {
        iVar15 = iVar15 + 6;
        goto LAB_00720d13;
      }
      if (pcVar10[0x810] == '\0') {
        iVar15 = iVar15 + 7;
        goto LAB_00720d13;
      }
      pcVar10 = pcVar10 + 0xac0;
      iVar15 = iVar15 + 8;
    } while ((int)pcVar10 < 0xc7c856);
    uVar13 = 0xffffffff;
    local_1c = -1;
    iVar12 = 0;
    do {
      if (((&DAT_00c79bff)[iVar14] == '\0') && (*(uint *)((int)&DAT_00c79bec + iVar14) < uVar13)) {
        pfVar2 = (float *)((int)&DAT_00c79aa8 +
                          *(short *)((int)&DAT_00c79bfc + iVar14) * 0xc + iVar14);
        local_4 = pfVar2[2] + *(float *)((int)&DAT_00c79ab0 + iVar14);
        local_18 = (*pfVar2 + *(float *)((int)&DAT_00c79aa8 + iVar14)) * _DAT_00858b8c;
        local_14 = (pfVar2[1] + *(float *)((int)&DAT_00c79aac + iVar14)) * _DAT_00858b8c;
        local_10 = local_4 * _DAT_00858b8c;
        fVar4 = *(float *)((int)&DAT_00c79aa8 + iVar14) - local_18;
        fVar6 = *(float *)((int)&DAT_00c79aac + iVar14) - local_14;
        fVar5 = *(float *)((int)&DAT_00c79ab0 + iVar14) - local_10;
        cVar8 = FUN_00420d40(&local_18,SQRT(fVar4 * fVar4 + fVar6 * fVar6 + fVar5 * fVar5));
        if (cVar8 == '\0') {
          uVar13 = *(uint *)((int)&DAT_00c79bec + iVar14);
          local_1c = iVar12;
        }
      }
      iVar14 = iVar14 + 0x158;
      iVar12 = iVar12 + 1;
    } while (iVar14 < 0x2b00);
    if (-1 < local_1c) {
      iVar15 = local_1c;
    }
    if (iVar15 < 0x20) {
LAB_00720e21:
      (&DAT_00c79be8)[iVar15 * 0x56] = param_1;
      (&DAT_00c79bfe)[iVar15 * 0x158] = 1;
      (&DAT_00c79aa8)[iVar15 * 0x56] = *param_2;
      (&DAT_00c79aac)[iVar15 * 0x56] = param_2[1];
      (&DAT_00c79ab0)[iVar15 * 0x56] = param_2[2];
      iVar12 = DAT_00b7cb84 + -1000;
      (&DAT_00c79b68)[iVar15 * 0x56] = 0;
      (&DAT_00c79ba8)[iVar15 * 0x56] = 0;
      (&DAT_00c79bff)[iVar15 * 0x158] = 1;
      (&DAT_00c79bfc)[iVar15 * 0xac] = 0;
      (&DAT_00c79bec)[iVar15 * 0x56] = iVar12;
      if (*param_6 != '\0') {
        (&DAT_00c79bf8)[iVar15 * 0x56] = 3;
        return;
      }
      (&DAT_00c79bf8)[iVar15 * 0x56] = param_5;
      return;
    }
    *param_6 = '\0';
  }
  return;
}



/* function 0079d1e5 FUN_0079d1e5 */

undefined4 * __fastcall FUN_0079d1e5(undefined4 *param_1)

{
  FUN_007ad0af();
  param_1[0x7e] = 0xffffffff;
  param_1[0x50] = 0;
  param_1[0x51] = 0;
  param_1[0x81] = 0;
  *param_1 = &PTR_FUN_00880780;
  return param_1;
}



/* function 007a0301 FUN_007a0301 */

int __fastcall FUN_007a0301(int param_1)

{
  uint uVar1;
  byte bVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  void *pvVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int *piVar11;
  uint *puVar12;
  undefined4 uVar13;
  char *pcVar14;
  int local_78 [6];
  int local_60 [6];
  uint local_48 [6];
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  int *local_20;
  int *local_1c;
  int local_18;
  uint local_14;
  undefined4 *local_10;
  undefined4 *local_c;
  uint local_8;
  
  local_c = (undefined4 *)0x0;
  local_10 = (undefined4 *)0x0;
  iVar9 = 6;
  piVar11 = local_60;
  for (iVar8 = iVar9; iVar8 != 0; iVar8 = iVar8 + -1) {
    *piVar11 = 0;
    piVar11 = piVar11 + 1;
  }
  piVar11 = local_78;
  for (iVar8 = iVar9; iVar8 != 0; iVar8 = iVar8 + -1) {
    *piVar11 = 0;
    piVar11 = piVar11 + 1;
  }
  puVar12 = local_48;
  for (iVar8 = iVar9; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  puVar6 = (undefined4 *)(param_1 + 0x1c8);
  for (iVar8 = iVar9; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar6 = 0xffffffff;
    puVar6 = puVar6 + 1;
  }
  puVar6 = (undefined4 *)(param_1 + 0x1e0);
  for (; iVar9 != 0; iVar9 = iVar9 + -1) {
    *puVar6 = 0xffffffff;
    puVar6 = puVar6 + 1;
  }
  local_18 = 1;
  local_24 = 0;
  local_8 = 0;
  if (*(int *)(param_1 + 0xc) != 0) {
    local_20 = *(int **)(param_1 + 0x18);
    do {
      puVar12 = (uint *)*local_20;
      uVar5 = *puVar12;
      uVar10 = uVar5 & 0xff000000;
      if ((((uVar10 == 0x40000000) || (uVar10 == 0x44000000)) || (uVar10 == 0x48000000)) ||
         (uVar10 == 0x4c000000)) {
LAB_007a049b:
        if (uVar10 == 0x34000000) {
LAB_007a04a3:
          iVar9 = *(int *)puVar12[2];
        }
        else {
          iVar9 = *(int *)(puVar12[2] + (uVar5 & 0xffffff) * 4);
        }
        piVar11 = *(int **)(*(int *)(param_1 + 0x14) + iVar9 * 4);
        if ((*piVar11 == *(int *)(param_1 + 0x58)) && (piVar11[8] == 0)) {
          if ((char)piVar11[0x14] != '\x03') {
            pcVar14 = "texture loads or clips cannot be from inputs not marked TEXCOORD";
            uVar13 = 0x11a1;
            iVar9 = piVar11[0x11];
            goto LAB_007a0808;
          }
          if ((local_60[*(byte *)((int)piVar11 + 0x51)] != 0) &&
             ((*(uint *)(param_1 + 0x30) & 0xffff) != 0x104)) {
            local_18 = 0;
          }
          local_60[*(byte *)((int)piVar11 + 0x51)] = 1;
        }
        else {
          local_18 = 0;
        }
      }
      else {
        if (uVar10 == 0x34000000) goto LAB_007a04a3;
        if ((uVar10 == 0xee000000) || (uVar10 == 0xef000000)) goto LAB_007a049b;
        uVar10 = uVar5 & 0xffffff;
        local_2c = uVar10;
        if ((uVar10 != 0) && (uVar5 != 0)) {
          local_14 = 0;
          local_30 = puVar12[1];
          if (puVar12[1] != 0) {
            local_1c = (int *)puVar12[2];
            do {
              uVar5 = local_14;
              piVar11 = *(int **)(*(int *)(param_1 + 0x14) + *local_1c * 4);
              if ((*piVar11 == *(int *)(param_1 + 0x58)) &&
                 (bVar2 = *(byte *)((int)piVar11 + 0x51), (char)piVar11[0x14] == '\x03')) {
                if ((local_60[bVar2] != 0) &&
                   (((*(uint *)(param_1 + 0x30) & 0xffff) != 0x104 && (local_48[bVar2] == 0)))) {
                  local_18 = 0;
                }
                local_60[bVar2] = 1;
                uVar1 = uVar5 + uVar10;
                local_78[bVar2] = 1;
                uVar4 = local_2c;
                if (uVar5 < uVar1) {
                  local_28 = uVar1 - local_14;
                  uVar5 = local_48[bVar2];
                  piVar11 = local_1c;
                  do {
                    uVar10 = *(int *)(*(int *)(*(int *)(param_1 + 0x14) + *piVar11 * 4) + 0xc) + 1;
                    if (uVar5 < uVar10) {
                      uVar5 = uVar10;
                    }
                    piVar11 = piVar11 + 1;
                    local_28 = local_28 - 1;
                  } while (local_28 != 0);
                  local_48[bVar2] = uVar5;
                  uVar10 = uVar4;
                }
              }
              local_14 = local_14 + uVar10;
              local_1c = local_1c + uVar10;
            } while (local_14 < local_30);
          }
          local_24 = local_24 + 1;
        }
      }
      local_8 = local_8 + 1;
      local_20 = local_20 + 1;
    } while (local_8 < *(uint *)(param_1 + 0xc));
    if (0x10 < local_24) {
      local_18 = 0;
    }
  }
  uVar5 = 0;
  if (*(int *)(param_1 + 8) != 0) {
    do {
      iVar9 = uVar5 * 4;
      uVar5 = uVar5 + 1;
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x14) + iVar9) + 0x28) = 0;
    } while (uVar5 < *(uint *)(param_1 + 8));
  }
  if (local_18 == 0) {
    pvVar7 = operator_new(0x800);
    *(void **)(param_1 + 0x140) = pvVar7;
    if (pvVar7 == (void *)0x0) {
      return -0x7ff8fff2;
    }
    pvVar7 = operator_new(0x800);
    *(void **)(param_1 + 0x144) = pvVar7;
    if (pvVar7 == (void *)0x0) {
      return -0x7ff8fff2;
    }
    local_c = operator_new(0x800);
    if (local_c == (undefined4 *)0x0) {
      return -0x7ff8fff2;
    }
    local_10 = operator_new(0x800);
    puVar6 = *(undefined4 **)(param_1 + 0x140);
    for (iVar9 = 0x200; iVar9 != 0; iVar9 = iVar9 + -1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    puVar6 = *(undefined4 **)(param_1 + 0x144);
    for (iVar9 = 0x200; iVar9 != 0; iVar9 = iVar9 + -1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    puVar6 = local_c;
    for (iVar9 = 0x200; iVar9 != 0; iVar9 = iVar9 + -1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    puVar6 = local_10;
    for (iVar9 = 0x200; iVar9 != 0; iVar9 = iVar9 + -1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    *(undefined4 *)(param_1 + 0x134) = 0;
    *(undefined4 *)(param_1 + 0x138) = 0;
    local_1c = (int *)0x0;
    local_8 = 0;
    if (*(int *)(param_1 + 0xc) != 0) {
      do {
        if (0x1ff < local_8) {
          pcVar14 = "program too big";
          uVar13 = 0x11a2;
          iVar9 = 0;
LAB_007a0808:
          FUN_007899a1(param_1,iVar9,uVar13,pcVar14);
          return -0x7fffbffb;
        }
        puVar12 = *(uint **)(*(int *)(param_1 + 0x18) + local_8 * 4);
        uVar5 = *puVar12 & 0xff000000;
        if ((((uVar5 == 0x40000000) || (uVar5 == 0x44000000)) || (uVar5 == 0x48000000)) ||
           (((uVar5 == 0x4c000000 || (uVar5 == 0x34000000)) ||
            ((uVar5 == 0xef000000 || (uVar5 == 0xee000000)))))) {
          local_28 = *puVar12 & 0xffffff;
          if (uVar5 == 0x34000000) {
            local_28 = 0;
          }
          piVar11 = (int *)(puVar12[2] + local_28 * 4);
          piVar3 = *(int **)(*(int *)(param_1 + 0x14) + *piVar11 * 4);
          if ((*piVar3 == *(int *)(param_1 + 0x60)) || (piVar3[8] != 0)) {
            iVar9 = FUN_0079f990(piVar11,puVar12[1] - local_28,local_c,&local_1c);
            if (iVar9 < 0) goto LAB_007a07a0;
          }
          else if (*piVar3 == *(int *)(param_1 + 0x58)) {
            if ((char)piVar3[0x14] == '\x03') {
              if ((local_78[*(byte *)((int)piVar3 + 0x51)] == 0) ||
                 ((*(uint *)(param_1 + 0x30) & 0xffff) == 0x104)) goto LAB_007a0701;
              pcVar14 = "can read from texcoord and use it for texlookup only in ps_1_4 and higher";
              uVar13 = 0x11a8;
            }
            else {
              pcVar14 = 
              "cannot perform dependent texture read which in any way is based on color inputs";
              uVar13 = 0x11a1;
            }
            FUN_007899a1(param_1,0,uVar13,pcVar14);
            iVar9 = -0x7fffbffb;
            goto LAB_007a07a0;
          }
        }
LAB_007a0701:
        local_8 = local_8 + 1;
      } while (local_8 < *(uint *)(param_1 + 0xc));
    }
    piVar11 = (int *)0x0;
    if (local_1c != (int *)0x0) {
      puVar6 = local_c;
      do {
        *(undefined4 *)(((int)local_10 - (int)local_c) + (int)puVar6) = *puVar6;
        *puVar6 = 0;
        piVar11 = (int *)((int)piVar11 + 1);
        puVar6 = puVar6 + 1;
      } while (piVar11 < local_1c);
    }
    iVar9 = FUN_0079fb55(*(undefined4 *)(param_1 + 0x144),param_1 + 0x138,
                         *(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0xc),0,0);
    if ((iVar9 < 0) ||
       (iVar9 = FUN_0079fb55(*(undefined4 *)(param_1 + 0x140),param_1 + 0x134,local_10,local_1c,
                             *(undefined4 *)(param_1 + 0x144),*(undefined4 *)(param_1 + 0x88)),
       iVar9 < 0)) goto LAB_007a07a0;
  }
  else {
    *(undefined4 *)(param_1 + 0x140) = 0;
    puVar6 = operator_new(0x800);
    *(undefined4 **)(param_1 + 0x144) = puVar6;
    if (puVar6 == (undefined4 *)0x0) {
      return -0x7ff8fff2;
    }
    for (iVar9 = 0x200; iVar9 != 0; iVar9 = iVar9 + -1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    iVar9 = FUN_0079fb55(*(undefined4 *)(param_1 + 0x144),param_1 + 0x138,
                         *(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0xc),0,0);
    if (iVar9 < 0) {
      return iVar9;
    }
  }
  iVar9 = 0;
  uVar5 = 0;
  if (*(int *)(param_1 + 8) != 0) {
    do {
      puVar6 = *(undefined4 **)(*(int *)(param_1 + 0x14) + uVar5 * 4);
      if (puVar6[10] == 1) {
        *puVar6 = *(undefined4 *)(param_1 + 0x4c);
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)(param_1 + 8));
  }
LAB_007a07a0:
  uVar5 = 0;
  if (local_c != (undefined4 *)0x0) {
    if (iVar9 < 0) {
      do {
        if (local_c[uVar5] != 0) {
          FUN_00784bd1(1);
        }
        uVar5 = uVar5 + 1;
      } while (uVar5 < 0x200);
    }
                    /* WARNING: Subroutine does not return */
    _free(local_c);
  }
  if (local_10 != (undefined4 *)0x0) {
    if (iVar9 < 0) {
      uVar5 = 0;
      do {
        if (local_10[uVar5] != 0) {
          FUN_00784bd1(1);
        }
        uVar5 = uVar5 + 1;
      } while (uVar5 < 0x200);
    }
                    /* WARNING: Subroutine does not return */
    _free(local_10);
  }
  return iVar9;
}



/* function 007aa21b FUN_007aa21b */

int __thiscall FUN_007aa21b(int *param_1,int *param_2,uint *param_3)

{
  char *pcVar1;
  char cVar2;
  ushort uVar3;
  int *piVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  char *pcVar8;
  void *_Memory;
  undefined4 *puVar9;
  uint uVar10;
  undefined1 local_34 [16];
  uint local_24 [5];
  uint local_10;
  int local_c;
  uint local_8;
  
  piVar5 = param_2;
  uVar3 = *(ushort *)((int)param_2 + 0x52);
  uVar6 = param_2[0x14] & 0xffff;
  if (param_1[0x3b] != 0) {
    if (param_2[0x14] == 0xffffffff) {
      return 0;
    }
    if (uVar6 != 0xffff) {
      FUN_00825c29(local_34,0x20,"v_%s%d",(&PTR_s_UNKNOWN_008dd090)[uVar6],uVar3);
      local_24[3] = local_24[3] & 0xffffff;
      iVar7 = FUN_00771648(local_34,param_2[2],1);
      if (iVar7 < 0) {
        return iVar7;
      }
      param_1[0x52] = param_1[0x52] + 1;
      if ((((*(byte *)(param_1 + 0xd) & 1) != 0) && (iVar7 = param_2[0x11], iVar7 != 0)) &&
         ((*(int *)(iVar7 + 4) == 5 && (iVar7 = *(int *)(iVar7 + 0x14), *(int *)(iVar7 + 4) == 2))))
      {
        pcVar8 = *(char **)(iVar7 + 0x18);
        pcVar1 = pcVar8 + 1;
        do {
          cVar2 = *pcVar8;
          pcVar8 = pcVar8 + 1;
        } while (cVar2 != '\0');
        _Memory = operator_new((uint)(pcVar8 + (3 - (int)pcVar1)));
        if (_Memory != (void *)0x0) {
          FUN_00821bb5(_Memory,&DAT_00881990,*(undefined4 *)(iVar7 + 0x18));
          FUN_00771648(_Memory,param_2[2],1);
                    /* WARNING: Subroutine does not return */
          _free(_Memory);
        }
        return -0x7ff8fff2;
      }
    }
    if (param_3 == (uint *)0x0) {
      return 0;
    }
    uVar6 = param_2[0x14];
    goto LAB_007aa476;
  }
  param_2 = (int *)0xd;
  switch(uVar6) {
  case 1:
    param_2 = (int *)0x0;
    break;
  case 2:
    param_2 = (int *)0x1;
    break;
  case 3:
    param_2 = (int *)0x2;
    break;
  case 4:
    param_2 = (int *)0x3;
    break;
  case 5:
    param_2 = (int *)0x4;
    break;
  case 6:
    param_2 = (int *)0x5;
    break;
  case 7:
    param_2 = (int *)0x6;
    break;
  case 8:
    param_2 = (int *)0x7;
    break;
  case 9:
    param_2 = (int *)0x8;
    if (uVar3 != 0) {
      return -0x7fffbffb;
    }
    goto LAB_007aa355;
  case 10:
    param_2 = (int *)0x9;
    break;
  case 0xb:
    param_2 = (int *)0xa;
    break;
  case 0xc:
    param_2 = (int *)0xb;
    break;
  case 0xd:
    param_2 = (int *)0xc;
    break;
  case 0xe:
    break;
  default:
    goto LAB_007aa4e4;
  }
  if (0xf < uVar3) {
LAB_007aa4e4:
    return -0x7fffbffb;
  }
LAB_007aa355:
  uVar6 = (uint)param_2 | (uint)(uVar3 | 0x8000) << 0x10;
  iVar7 = FUN_007b3be1(0x1f);
  if (iVar7 < 0) {
    return iVar7;
  }
  iVar7 = FUN_007b25ab(uVar6);
  if (iVar7 < 0) {
    return iVar7;
  }
  if ((*(byte *)(param_1 + 0xd) & 1) != 0) {
    local_c = 0;
    local_8 = 0;
    local_24[0] = 0xffffffff;
    local_24[1] = 0xffffffff;
    local_24[2] = 0xffffffff;
    local_24[3] = 0xffffffff;
    if (param_1[2] != 0) {
      iVar7 = *piVar5;
      puVar9 = (undefined4 *)param_1[5];
      do {
        piVar4 = (int *)*puVar9;
        if (((iVar7 == *piVar4) && (piVar5[1] == piVar4[1])) && (piVar5[2] == piVar4[2])) {
          local_24[piVar4[3]] = local_8;
        }
        local_8 = local_8 + 1;
        puVar9 = puVar9 + 1;
      } while (local_8 < (uint)param_1[2]);
    }
    uVar10 = 0;
    iVar7 = local_c;
    do {
      if (local_24[uVar10] != 0xffffffff) {
        local_24[iVar7] = local_24[uVar10];
        iVar7 = iVar7 + 1;
      }
      uVar10 = uVar10 + 1;
    } while (uVar10 < 4);
    iVar7 = (**(code **)(*param_1 + 0x60))(local_24,iVar7,&local_c,1);
    if (iVar7 < 0) {
      return iVar7;
    }
  }
  iVar7 = (**(code **)(*param_1 + 0x74))(piVar5,local_24 + 4,&local_10);
  if (iVar7 < 0) {
    return iVar7;
  }
  iVar7 = (**(code **)(*param_1 + 0x54))
                    (((local_10 | 0xfffffff8) << 0x14 | local_10 & 0x18) << 8 | local_24[4] & 0x7ff,
                     0xf0000);
  if (iVar7 < 0) {
    return iVar7;
  }
  iVar7 = (**(code **)(*param_1 + 0x50))();
  if (iVar7 < 0) {
    return iVar7;
  }
  iVar7 = FUN_007affb1();
  if (iVar7 < 0) {
    return iVar7;
  }
  if (param_3 == (uint *)0x0) {
    return 0;
  }
LAB_007aa476:
  *param_3 = uVar6;
  return 0;
}



/* function 007aaf82 FUN_007aaf82 */

undefined4 * __thiscall FUN_007aaf82(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  FUN_007ad0af();
  *param_1 = &PTR_FUN_008819f0;
  puVar2 = param_1 + 0x43;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = param_1 + 0x4b;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_1[0x52] = 0;
  param_1[0x53] = 0;
  param_1[0x3b] = param_2;
  return param_1;
}



/* function 007c51d0 FUN_007c51d0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_007c51d0(uint *param_1)

{
  byte *pbVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  code *pcVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  int iVar9;
  uint *puVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  float *pfVar15;
  uint *puVar16;
  float *pfVar17;
  uint *puVar18;
  uint *local_a14;
  uint *local_a10;
  uint *local_a0c;
  uint *local_a04;
  int local_a00;
  int local_9d8;
  float local_9d0 [5];
  float local_9bc;
  float local_9b8;
  float local_9b0;
  float local_9ac;
  float local_9a8;
  undefined4 local_9a0;
  undefined4 local_99c;
  undefined4 local_998;
  int local_990;
  float local_98c;
  uint local_980 [4];
  undefined4 local_970;
  undefined4 local_96c;
  undefined4 local_968;
  undefined4 local_960;
  undefined4 local_95c;
  undefined4 local_958;
  undefined4 local_950;
  undefined4 local_94c;
  undefined4 local_948;
  uint local_940 [4];
  undefined4 local_930;
  undefined4 local_92c;
  undefined4 local_928;
  undefined4 local_920;
  undefined4 local_91c;
  undefined4 local_918;
  undefined4 local_910;
  undefined4 local_90c;
  undefined4 local_908;
  uint local_900;
  undefined4 local_8fc;
  undefined4 local_8f8;
  uint local_8f4;
  undefined4 local_8f0;
  undefined4 local_8ec;
  undefined4 local_8e8;
  undefined4 local_8e0;
  undefined4 local_8dc;
  undefined4 local_8d8;
  undefined4 local_8d0;
  undefined4 local_8cc;
  undefined4 local_8c8;
  uint local_8c0 [16];
  uint local_880 [48];
  uint local_7c0 [496];
  
  uVar4 = *param_1;
  if ((uVar4 & 2) != 0) {
    iVar12 = *(int *)(param_1[5] + 4);
    if (iVar12 == 0) {
      local_958 = 0x3f800000;
      local_980[3] = local_980[3] | 0x20003;
      local_96c = 0x3f800000;
      local_980[0] = 0x3f800000;
      local_970 = 0;
      local_980[2] = 0;
      local_980[1] = 0;
      local_95c = 0;
      local_960 = 0;
      local_968 = 0;
      local_948 = 0;
      local_94c = 0;
      local_950 = 0;
    }
    else {
      iVar9 = FUN_007f0340(iVar12);
      if (iVar9 == 0) {
        puVar10 = (uint *)FUN_007f0990(iVar12);
        puVar16 = local_980;
        for (iVar12 = 0x10; iVar12 != 0; iVar12 = iVar12 + -1) {
          *puVar16 = *puVar10;
          puVar10 = puVar10 + 1;
          puVar16 = puVar16 + 1;
        }
      }
      else {
        puVar10 = (uint *)(iVar12 + 0x10);
        puVar16 = local_980;
        for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
          *puVar16 = *puVar10;
          puVar10 = puVar10 + 1;
          puVar16 = puVar16 + 1;
        }
        for (iVar12 = *(int *)(iVar12 + 4); iVar12 != 0; iVar12 = *(int *)(iVar12 + 4)) {
          puVar10 = local_980;
          puVar16 = local_880;
          for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
            *puVar16 = *puVar10;
            puVar10 = puVar10 + 1;
            puVar16 = puVar16 + 1;
          }
          FUN_007f18b0(local_980,local_880,iVar12 + 0x10);
        }
      }
    }
    uVar14 = uVar4 & 0x2000;
    if ((uVar14 != 0) && ((*(byte *)(*(int *)(param_1[5] + 0xa0) + 3) & 3) == 0)) {
      *(undefined4 *)(*(int *)(param_1[5] + 0xa0) + 8) = *(undefined4 *)(DAT_00c97b24 + 0xbc);
      *(int *)(*(int *)(param_1[5] + 0xa0) + 0xc) = DAT_00c97b24 + 0xbc;
      *(int *)(*(int *)(DAT_00c97b24 + 0xbc) + 4) = *(int *)(param_1[5] + 0xa0) + 8;
      *(int *)(DAT_00c97b24 + 0xbc) = *(int *)(param_1[5] + 0xa0) + 8;
      pbVar1 = (byte *)(*(int *)(param_1[5] + 0xa0) + 3);
      *pbVar1 = *pbVar1 | 2;
    }
    uVar11 = param_1[8];
    local_a00 = 0;
    iVar9 = *(int *)(uVar11 + 0x24);
    pcVar5 = *(code **)(uVar11 + 0x3c);
    iVar12 = uVar11 + 0x4c;
    local_a10 = local_7c0;
    if ((int)param_1[1] < 1) {
      return 1;
    }
    local_a0c = (uint *)(param_1[4] + 8);
    do {
      if (pcVar5 == (code *)&LAB_007c5b80) {
        fVar2 = *(float *)(iVar12 + 8);
        fVar3 = *(float *)(iVar12 + 0xc);
        fVar6 = *(float *)(iVar12 + 0x10);
        fVar7 = *(float *)(iVar12 + 0x14);
        local_98c = fVar7 * fVar2;
        fVar8 = fVar6 * fVar6 + fVar3 * fVar3;
        local_9d0[0] = _DAT_00858624 - (fVar8 + fVar8);
        local_9d0[1] = fVar3 * fVar2 + fVar7 * fVar6;
        local_9d0[1] = local_9d0[1] + local_9d0[1];
        local_9d0[2] = fVar6 * fVar2 - fVar7 * fVar3;
        local_9d0[2] = local_9d0[2] + local_9d0[2];
        local_9d0[4] = fVar3 * fVar2 - fVar7 * fVar6;
        local_9d0[4] = local_9d0[4] + local_9d0[4];
        fVar8 = fVar6 * fVar6 + fVar2 * fVar2;
        local_9bc = _DAT_00858624 - (fVar8 + fVar8);
        local_9b8 = local_98c + fVar6 * fVar3;
        local_9b8 = local_9b8 + local_9b8;
        local_9b0 = fVar7 * fVar3 + fVar6 * fVar2;
        local_9b0 = local_9b0 + local_9b0;
        local_9ac = fVar6 * fVar3 - local_98c;
        local_9ac = local_9ac + local_9ac;
        fVar2 = fVar3 * fVar3 + fVar2 * fVar2;
        local_9a8 = _DAT_00858624 - (fVar2 + fVar2);
        local_9a0 = *(undefined4 *)(iVar12 + 0x18);
        local_99c = *(undefined4 *)(iVar12 + 0x1c);
        local_998 = *(undefined4 *)(iVar12 + 0x20);
        local_9d0[3] = 4.2039e-45;
      }
      else {
        (*pcVar5)(local_9d0,iVar12);
      }
      FUN_007f18b0(local_8c0,local_9d0,local_980);
      uVar11 = local_a0c[1];
      if (uVar11 != 0) {
        if ((uVar4 & 0x1000) == 0) {
          if (uVar14 != 0) goto LAB_007c557d;
        }
        else {
          pfVar15 = local_9d0;
          pfVar17 = (float *)(uVar11 + 0x10);
          for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
            *pfVar17 = *pfVar15;
            pfVar15 = pfVar15 + 1;
            pfVar17 = pfVar17 + 1;
          }
          if (uVar14 == 0) {
            FUN_007f0910(uVar11);
          }
          else {
LAB_007c557d:
            puVar10 = local_8c0;
            puVar16 = (uint *)(uVar11 + 0x50);
            for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
              *puVar16 = *puVar10;
              puVar10 = puVar10 + 1;
              puVar16 = puVar16 + 1;
            }
            *(byte *)(uVar11 + 3) = *(byte *)(uVar11 + 3) & 0xfb | 8;
          }
        }
      }
      uVar11 = *local_a0c & 3;
      if (uVar11 == 0) {
LAB_007c55cb:
        puVar10 = local_8c0;
LAB_007c55d2:
        puVar16 = local_980;
        for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
          *puVar16 = *puVar10;
          puVar10 = puVar10 + 1;
          puVar16 = puVar16 + 1;
        }
      }
      else {
        if (uVar11 == 1) {
          puVar10 = local_a10 + -0x10;
          local_a10 = puVar10;
          goto LAB_007c55d2;
        }
        if (uVar11 == 2) {
          puVar18 = local_a10 + 0x10;
          puVar10 = local_980;
          puVar16 = local_a10;
          for (iVar13 = 0x10; local_a10 = puVar18, iVar13 != 0; iVar13 = iVar13 + -1) {
            *puVar16 = *puVar10;
            puVar10 = puVar10 + 1;
            puVar16 = puVar16 + 1;
          }
          goto LAB_007c55cb;
        }
      }
      iVar12 = iVar12 + iVar9;
      local_a0c = local_a0c + 4;
      local_a00 = local_a00 + 1;
      if ((int)param_1[1] <= local_a00) {
        return 1;
      }
    } while( true );
  }
  if (((uVar4 & 1) == 0) || (param_1[7] == 0xffffffff)) {
    if ((uVar4 & 0x4000) == 0) {
      local_a14 = local_940;
    }
    else {
      local_a14 = &local_900;
      local_8f4 = local_8f4 | 0x20003;
      local_8d8 = 0x3f800000;
      local_8ec = 0x3f800000;
      local_900 = 0x3f800000;
      local_8f0 = 0;
      local_8f8 = 0;
      local_8fc = 0;
      local_8dc = 0;
      local_8e0 = 0;
      local_8e8 = 0;
      local_8c8 = 0;
      local_8cc = 0;
      local_8d0 = 0;
      if ((uVar4 & 0x2000) == 0) goto LAB_007c5759;
    }
    uVar14 = param_1[5];
  }
  else {
    local_a14 = (uint *)(param_1[7] * 0x40 + *(int *)(param_1[6] + 8));
    if (((uVar4 & 0x2000) == 0) || ((uVar4 & 0x4000) == 0)) goto LAB_007c5759;
    uVar14 = *(uint *)(param_1[6] + 0x14);
  }
  if ((uVar14 == 0) || (iVar12 = *(int *)(uVar14 + 4), iVar12 == 0)) {
    local_918 = 0x3f800000;
    local_940[3] = local_940[3] | 0x20003;
    local_92c = 0x3f800000;
    local_940[0] = 0x3f800000;
    local_930 = 0;
    local_940[2] = 0;
    local_940[1] = 0;
    local_91c = 0;
    local_920 = 0;
    local_928 = 0;
    local_908 = 0;
    local_90c = 0;
    local_910 = 0;
  }
  else {
    iVar9 = FUN_007f0340(iVar12);
    if (iVar9 == 0) {
      puVar10 = (uint *)FUN_007f0990(iVar12);
      puVar16 = local_940;
      for (iVar12 = 0x10; iVar12 != 0; iVar12 = iVar12 + -1) {
        *puVar16 = *puVar10;
        puVar10 = puVar10 + 1;
        puVar16 = puVar16 + 1;
      }
    }
    else {
      puVar10 = (uint *)(iVar12 + 0x10);
      puVar16 = local_940;
      for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
        *puVar16 = *puVar10;
        puVar10 = puVar10 + 1;
        puVar16 = puVar16 + 1;
      }
      for (iVar12 = *(int *)(iVar12 + 4); iVar12 != 0; iVar12 = *(int *)(iVar12 + 4)) {
        puVar10 = local_940;
        puVar16 = local_880;
        for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
          *puVar16 = *puVar10;
          puVar10 = puVar10 + 1;
          puVar16 = puVar16 + 1;
        }
        FUN_007f18b0(local_940,local_880,iVar12 + 0x10);
      }
    }
  }
LAB_007c5759:
  uVar14 = uVar4 & 0x2000;
  if ((uVar14 != 0) && ((*(byte *)(*(int *)(param_1[5] + 0xa0) + 3) & 3) == 0)) {
    *(undefined4 *)(*(int *)(param_1[5] + 0xa0) + 8) = *(undefined4 *)(DAT_00c97b24 + 0xbc);
    *(int *)(*(int *)(param_1[5] + 0xa0) + 0xc) = DAT_00c97b24 + 0xbc;
    *(int *)(*(int *)(DAT_00c97b24 + 0xbc) + 4) = *(int *)(param_1[5] + 0xa0) + 8;
    *(int *)(DAT_00c97b24 + 0xbc) = *(int *)(param_1[5] + 0xa0) + 8;
    pbVar1 = (byte *)(*(int *)(param_1[5] + 0xa0) + 3);
    *pbVar1 = *pbVar1 | 2;
  }
  uVar11 = param_1[8];
  puVar10 = (uint *)param_1[2];
  local_9d8 = 0;
  local_990 = *(int *)(uVar11 + 0x24);
  pcVar5 = *(code **)(uVar11 + 0x3c);
  iVar12 = uVar11 + 0x4c;
  local_a0c = local_880 + 1;
  if (0 < (int)param_1[1]) {
    local_a04 = (uint *)(param_1[4] + 8);
    do {
      if (pcVar5 == (code *)&LAB_007c5b80) {
        fVar2 = *(float *)(iVar12 + 8);
        fVar3 = *(float *)(iVar12 + 0xc);
        fVar6 = *(float *)(iVar12 + 0x10);
        fVar7 = *(float *)(iVar12 + 0x14);
        local_98c = fVar7 * fVar2;
        fVar8 = fVar6 * fVar6 + fVar3 * fVar3;
        local_9d0[0] = _DAT_00858624 - (fVar8 + fVar8);
        local_9d0[1] = fVar3 * fVar2 + fVar7 * fVar6;
        local_9d0[1] = local_9d0[1] + local_9d0[1];
        local_9d0[2] = fVar6 * fVar2 - fVar7 * fVar3;
        local_9d0[2] = local_9d0[2] + local_9d0[2];
        local_9d0[4] = fVar3 * fVar2 - fVar7 * fVar6;
        local_9d0[4] = local_9d0[4] + local_9d0[4];
        fVar8 = fVar6 * fVar6 + fVar2 * fVar2;
        local_9bc = _DAT_00858624 - (fVar8 + fVar8);
        local_9b8 = local_98c + fVar6 * fVar3;
        local_9b8 = local_9b8 + local_9b8;
        local_9b0 = fVar7 * fVar3 + fVar6 * fVar2;
        local_9b0 = local_9b0 + local_9b0;
        local_9ac = fVar6 * fVar3 - local_98c;
        local_9ac = local_9ac + local_9ac;
        fVar2 = fVar3 * fVar3 + fVar2 * fVar2;
        local_9a8 = _DAT_00858624 - (fVar2 + fVar2);
        local_9a0 = *(undefined4 *)(iVar12 + 0x18);
        local_99c = *(undefined4 *)(iVar12 + 0x1c);
        local_998 = *(undefined4 *)(iVar12 + 0x20);
        local_9d0[3] = 4.2039e-45;
      }
      else {
        (*pcVar5)(local_9d0,iVar12);
      }
      FUN_007f18b0(puVar10,local_9d0,local_a14);
      uVar11 = local_a04[1];
      if (uVar11 != 0) {
        if ((uVar4 & 0x1000) == 0) {
          if (uVar14 != 0) goto LAB_007c5aba;
        }
        else {
          pfVar15 = local_9d0;
          pfVar17 = (float *)(uVar11 + 0x10);
          for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
            *pfVar17 = *pfVar15;
            pfVar15 = pfVar15 + 1;
            pfVar17 = pfVar17 + 1;
          }
          if (uVar14 == 0) {
            FUN_007f0910(uVar11);
          }
          else {
LAB_007c5aba:
            if ((uVar4 & 0x4000) == 0) {
              puVar16 = puVar10;
              puVar18 = (uint *)(uVar11 + 0x50);
              for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
                *puVar18 = *puVar16;
                puVar16 = puVar16 + 1;
                puVar18 = puVar18 + 1;
              }
            }
            else {
              FUN_007f18b0(uVar11 + 0x50,puVar10,local_940);
            }
            *(byte *)(uVar11 + 3) = *(byte *)(uVar11 + 3) & 0xfb | 8;
          }
        }
      }
      uVar11 = *local_a04 & 3;
      puVar16 = puVar10;
      if (uVar11 != 0) {
        if (uVar11 == 1) {
          local_a0c = local_a0c + -1;
          puVar16 = (uint *)*local_a0c;
        }
        else {
          puVar16 = local_a14;
          if (uVar11 == 2) {
            *local_a0c = (uint)local_a14;
            local_a0c = local_a0c + 1;
            puVar16 = puVar10;
          }
        }
      }
      local_a14 = puVar16;
      iVar12 = iVar12 + local_990;
      puVar10 = puVar10 + 0x10;
      local_a04 = local_a04 + 4;
      local_9d8 = local_9d8 + 1;
    } while (local_9d8 < (int)param_1[1]);
  }
  return 1;
}



/* function 007d61a0 FUN_007d61a0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_007d61a0(int param_1)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  float10 fVar6;
  float10 fVar7;
  ushort uVar8;
  byte *pbVar9;
  int iVar10;
  int iVar11;
  byte bVar12;
  int iVar13;
  uint uVar14;
  double dVar15;
  double dVar16;
  undefined2 local_44;
  undefined2 local_40;
  int local_34;
  byte local_30;
  double local_28;
  double local_20;
  double local_18;
  double local_10;
  
  uVar14 = *(uint *)(param_1 + 0x70);
  bVar1 = *(byte *)(param_1 + 0x126);
  if (((uVar14 & 0x100) != 0) && ((uVar14 & 0x1000) != 0)) {
    if ((bVar1 & 2) != 0) {
      if (bVar1 == 3) {
        pbVar9 = (byte *)((uint)*(byte *)(param_1 + 0x138) * 3 + *(int *)(param_1 + 0x114));
        *(ushort *)(param_1 + 0x13a) = (ushort)*pbVar9;
        *(ushort *)(param_1 + 0x13c) = (ushort)pbVar9[1];
        uVar8 = (ushort)pbVar9[2];
        goto LAB_007d627e;
      }
      goto switchD_007d61ef_caseD_3;
    }
    switch(*(undefined1 *)(param_1 + 0x127)) {
    case 1:
      uVar8 = *(short *)(param_1 + 0x140) * 0xff;
      break;
    case 2:
      uVar8 = *(short *)(param_1 + 0x140) * 0x55;
      break;
    default:
      goto switchD_007d61ef_caseD_3;
    case 4:
      uVar8 = *(short *)(param_1 + 0x140) * 0x11;
      break;
    case 8:
    case 0x10:
      uVar8 = *(ushort *)(param_1 + 0x140);
      *(ushort *)(param_1 + 0x13c) = uVar8;
      *(ushort *)(param_1 + 0x13a) = uVar8;
      goto LAB_007d627e;
    }
    *(ushort *)(param_1 + 0x140) = uVar8;
    *(ushort *)(param_1 + 0x13c) = uVar8;
    *(ushort *)(param_1 + 0x13a) = uVar8;
LAB_007d627e:
    *(ushort *)(param_1 + 0x13e) = uVar8;
  }
switchD_007d61ef_caseD_3:
  *(undefined4 *)(param_1 + 0x142) = *(undefined4 *)(param_1 + 0x138);
  *(undefined4 *)(param_1 + 0x146) = *(undefined4 *)(param_1 + 0x13c);
  *(undefined2 *)(param_1 + 0x14a) = *(undefined2 *)(param_1 + 0x140);
  if ((uVar14 & 0x602000) == 0) {
    if (((char)uVar14 < '\0') && (bVar1 == 3)) {
      bVar12 = *(byte *)(param_1 + 0x13a);
      bVar3 = *(byte *)(param_1 + 0x13c);
      local_40 = CONCAT11(bVar3,bVar12);
      uVar8 = *(ushort *)(param_1 + 0x11a);
      bVar4 = *(byte *)(param_1 + 0x13e);
      iVar10 = 0;
      if (uVar8 != 0) {
        pbVar9 = (byte *)(*(int *)(param_1 + 0x114) + 2);
        do {
          bVar5 = *(byte *)(iVar10 + *(int *)(param_1 + 0x188));
          if (bVar5 == 0) {
            *(undefined2 *)(pbVar9 + -2) = local_40;
            *pbVar9 = bVar4;
          }
          else if (bVar5 != 0xff) {
            uVar14 = (0xff - (uint)bVar5) * (uint)bVar12 + 0x80 + (uint)pbVar9[-2] * (uint)bVar5 &
                     0xffff;
            pbVar9[-2] = (byte)((uVar14 >> 8) + uVar14 >> 8);
            uVar14 = (uint)*(byte *)(*(int *)(param_1 + 0x188) + iVar10);
            uVar14 = (0xff - uVar14) * (uint)bVar3 + 0x80 + pbVar9[-1] * uVar14 & 0xffff;
            pbVar9[-1] = (byte)((uVar14 >> 8) + uVar14 >> 8);
            uVar14 = (uint)*(byte *)(*(int *)(param_1 + 0x188) + iVar10);
            uVar14 = (0xff - uVar14) * (uint)bVar4 + 0x80 + *pbVar9 * uVar14 & 0xffff;
            *pbVar9 = (byte)((uVar14 >> 8) + uVar14 >> 8);
          }
          iVar10 = iVar10 + 1;
          pbVar9 = pbVar9 + 3;
        } while (iVar10 < (int)(uint)uVar8);
      }
    }
    goto LAB_007d67e8;
  }
  FUN_007da080(param_1);
  if (-1 < *(char *)(param_1 + 0x70)) {
    if (bVar1 == 3) {
      uVar14 = (uint)*(ushort *)(param_1 + 0x118);
      if (uVar14 != 0) {
        pbVar9 = (byte *)(*(int *)(param_1 + 0x114) + 2);
        do {
          pbVar9[-2] = *(byte *)((uint)pbVar9[-2] + *(int *)(param_1 + 0x164));
          pbVar9[-1] = *(byte *)((uint)pbVar9[-1] + *(int *)(param_1 + 0x164));
          uVar14 = uVar14 - 1;
          *pbVar9 = *(byte *)((uint)*pbVar9 + *(int *)(param_1 + 0x164));
          pbVar9 = pbVar9 + 3;
        } while (uVar14 != 0);
      }
    }
    goto LAB_007d67e8;
  }
  if (bVar1 != 3) {
    cVar2 = *(char *)(param_1 + 0x130);
    local_18 = 1.0;
    uVar14 = (1 << (*(byte *)(param_1 + 0x127) & 0x1f)) - 1;
    local_28 = 1.0;
    if (cVar2 == '\x01') {
      local_18 = (double)*(float *)(param_1 + 0x160);
      local_28 = 1.0;
    }
    else if (cVar2 == '\x02') {
      local_18 = (double)((float)_DAT_0085a310 / *(float *)(param_1 + 0x15c));
      local_28 = (double)((float)_DAT_0085a310 /
                         (*(float *)(param_1 + 0x160) * *(float *)(param_1 + 0x15c)));
    }
    else if (cVar2 == '\x03') {
      local_18 = (double)((float)_DAT_0085a310 / *(float *)(param_1 + 0x134));
      local_28 = (double)((float)_DAT_0085a310 /
                         (*(float *)(param_1 + 0x160) * *(float *)(param_1 + 0x134)));
    }
    dVar16 = _DAT_0085a310 / (double)uVar14;
    if ((bVar1 & 2) == 0) {
      dVar15 = _pow((double)*(ushort *)(param_1 + 0x140) * dVar16,local_18);
      local_20._0_2_ =
           (undefined2)
           (int)ROUND((float)((float10)dVar15 * (float10)uVar14 + (float10)_DAT_00859060));
      *(undefined2 *)(param_1 + 0x14a) = local_20._0_2_;
      dVar16 = _pow((double)*(ushort *)(param_1 + 0x140) * dVar16,local_28);
      local_20._0_2_ =
           (undefined2)
           (int)ROUND((float)((float10)dVar16 * (float10)uVar14 + (float10)_DAT_00859060));
      *(undefined2 *)(param_1 + 0x140) = local_20._0_2_;
    }
    else {
      dVar15 = _pow((double)*(ushort *)(param_1 + 0x13a) * dVar16,local_18);
      local_20._0_2_ =
           (undefined2)
           (int)ROUND((float)((float10)dVar15 * (float10)uVar14 + (float10)_DAT_00859060));
      *(undefined2 *)(param_1 + 0x144) = local_20._0_2_;
      dVar15 = _pow((double)*(ushort *)(param_1 + 0x13c) * dVar16,local_18);
      local_20._0_2_ =
           (undefined2)
           (int)ROUND((float)((float10)dVar15 * (float10)uVar14 + (float10)_DAT_00859060));
      *(undefined2 *)(param_1 + 0x146) = local_20._0_2_;
      dVar15 = _pow((double)*(ushort *)(param_1 + 0x13e) * dVar16,local_18);
      local_20._0_2_ =
           (undefined2)
           (int)ROUND((float)((float10)dVar15 * (float10)uVar14 + (float10)_DAT_00859060));
      *(undefined2 *)(param_1 + 0x148) = local_20._0_2_;
      dVar15 = _pow((double)*(ushort *)(param_1 + 0x13a) * dVar16,local_28);
      local_20._0_2_ =
           (undefined2)
           (int)ROUND((float)((float10)dVar15 * (float10)uVar14 + (float10)_DAT_00859060));
      *(undefined2 *)(param_1 + 0x13a) = local_20._0_2_;
      dVar15 = _pow((double)*(ushort *)(param_1 + 0x13c) * dVar16,local_28);
      local_20._0_2_ =
           (undefined2)
           (int)ROUND((float)((float10)dVar15 * (float10)uVar14 + (float10)_DAT_00859060));
      *(undefined2 *)(param_1 + 0x13c) = local_20._0_2_;
      dVar16 = _pow((double)*(ushort *)(param_1 + 0x13e) * dVar16,local_28);
      local_20._0_2_ =
           (undefined2)
           (int)ROUND((float)((float10)dVar16 * (float10)uVar14 + (float10)_DAT_00859060));
      *(undefined2 *)(param_1 + 0x13e) = local_20._0_2_;
    }
    goto LAB_007d67e8;
  }
  iVar10 = *(int *)(param_1 + 0x114);
  uVar8 = *(ushort *)(param_1 + 0x118);
  cVar2 = *(char *)(param_1 + 0x130);
  if (cVar2 == '\x02') {
    iVar13 = *(int *)(param_1 + 0x164);
    bVar12 = *(byte *)((uint)*(ushort *)(param_1 + 0x13e) + iVar13);
    local_44 = CONCAT11(*(undefined1 *)((uint)*(ushort *)(param_1 + 0x13c) + iVar13),
                        *(undefined1 *)(iVar13 + (uint)*(ushort *)(param_1 + 0x13a)));
    iVar13 = *(int *)(param_1 + 0x16c);
    local_40._0_1_ = *(byte *)(iVar13 + (uint)*(ushort *)(param_1 + 0x13a));
    local_20._0_1_ = *(byte *)(iVar13 + (uint)*(ushort *)(param_1 + 0x13c));
    local_28._0_1_ = *(byte *)(iVar13 + (uint)*(ushort *)(param_1 + 0x13e));
  }
  else {
    if (cVar2 == '\x01') {
      local_10 = (double)*(float *)(param_1 + 0x160);
LAB_007d63b9:
      local_20 = 1.0;
    }
    else if (cVar2 == '\x02') {
      local_10 = (double)((float)_DAT_0085a310 / *(float *)(param_1 + 0x15c));
      local_20 = (double)((float)_DAT_0085a310 /
                         (*(float *)(param_1 + 0x160) * *(float *)(param_1 + 0x15c)));
    }
    else {
      if (cVar2 != '\x03') {
        local_10 = 1.0;
        goto LAB_007d63b9;
      }
      local_10 = (double)((float)_DAT_0085a310 / *(float *)(param_1 + 0x134));
      local_20 = (double)((float)_DAT_0085a310 /
                         (*(float *)(param_1 + 0x160) * *(float *)(param_1 + 0x134)));
    }
    if (_DAT_00859068 <= ABS(local_20 - _DAT_0085a310)) {
      dVar16 = _pow((double)*(ushort *)(param_1 + 0x13a) * _DAT_00883250,local_20);
      fVar7 = (float10)_DAT_00883248;
      fVar6 = (float10)_DAT_00859060;
      dVar15 = _pow((double)*(ushort *)(param_1 + 0x13c) * _DAT_00883250,local_20);
      local_28._0_1_ =
           (byte)(int)ROUND((float)((float10)dVar15 * (float10)_DAT_00883248 +
                                   (float10)_DAT_00859060));
      local_44 = CONCAT11(local_28._0_1_,(char)(int)ROUND((float)((float10)dVar16 * fVar7 + fVar6)))
      ;
      dVar16 = _pow((double)*(ushort *)(param_1 + 0x13e) * _DAT_00883250,local_20);
      local_40._0_1_ =
           (byte)(int)ROUND((float)((float10)dVar16 * (float10)_DAT_00883248 +
                                   (float10)_DAT_00859060));
      bVar12 = (byte)local_40;
    }
    else {
      local_44 = CONCAT11(*(undefined1 *)(param_1 + 0x13c),*(undefined1 *)(param_1 + 0x13a));
      bVar12 = *(byte *)(param_1 + 0x13e);
    }
    dVar16 = _pow((double)*(ushort *)(param_1 + 0x13a) * _DAT_00883250,local_10);
    local_40._0_1_ =
         (byte)(int)ROUND((float)((float10)dVar16 * (float10)_DAT_00883248 + (float10)_DAT_00859060)
                         );
    dVar16 = _pow((double)*(ushort *)(param_1 + 0x13c) * _DAT_00883250,local_10);
    local_20._0_1_ =
         (byte)(int)ROUND((float)((float10)dVar16 * (float10)_DAT_00883248 + (float10)_DAT_00859060)
                         );
    dVar16 = _pow((double)*(ushort *)(param_1 + 0x13e) * _DAT_00883250,local_10);
    local_28._0_1_ =
         (byte)(int)ROUND((float)((float10)dVar16 * (float10)_DAT_00883248 + (float10)_DAT_00859060)
                         );
  }
  iVar13 = 0;
  if (uVar8 != 0) {
    pbVar9 = (byte *)(iVar10 + 2);
    do {
      if ((iVar13 < (int)(uint)*(ushort *)(param_1 + 0x11a)) &&
         (bVar3 = *(byte *)(iVar13 + *(int *)(param_1 + 0x188)), bVar3 != 0xff)) {
        if (bVar3 == 0) {
          *(undefined2 *)(pbVar9 + -2) = local_44;
          *pbVar9 = bVar12;
        }
        else {
          uVar14 = (uint)*(byte *)((uint)pbVar9[-2] + *(int *)(param_1 + 0x16c)) * (uint)bVar3 +
                   0x80 + (0xff - (uint)bVar3) * (uint)(byte)local_40 & 0xffff;
          pbVar9[-2] = *(byte *)(((int)((uVar14 >> 8) + uVar14) >> 8 & 0xffU) +
                                *(int *)(param_1 + 0x168));
          uVar14 = (uint)*(byte *)(*(int *)(param_1 + 0x188) + iVar13);
          uVar14 = *(byte *)((uint)pbVar9[-1] + *(int *)(param_1 + 0x16c)) * uVar14 + 0x80 +
                   (0xff - uVar14) * (uint)local_20._0_1_ & 0xffff;
          pbVar9[-1] = *(byte *)(((int)((uVar14 >> 8) + uVar14) >> 8 & 0xffU) +
                                *(int *)(param_1 + 0x168));
          uVar14 = (uint)*(byte *)(*(int *)(param_1 + 0x188) + iVar13);
          uVar14 = *(byte *)((uint)*pbVar9 + *(int *)(param_1 + 0x16c)) * uVar14 + 0x80 +
                   (0xff - uVar14) * (uint)local_28._0_1_ & 0xffff;
          *pbVar9 = *(byte *)(((int)((uVar14 >> 8) + uVar14) >> 8 & 0xffU) +
                             *(int *)(param_1 + 0x168));
        }
      }
      else {
        pbVar9[-2] = *(byte *)((uint)pbVar9[-2] + *(int *)(param_1 + 0x164));
        pbVar9[-1] = *(byte *)((uint)pbVar9[-1] + *(int *)(param_1 + 0x164));
        *pbVar9 = *(byte *)((uint)*pbVar9 + *(int *)(param_1 + 0x164));
      }
      iVar13 = iVar13 + 1;
      pbVar9 = pbVar9 + 3;
    } while (iVar13 < (int)(uint)uVar8);
  }
LAB_007d67e8:
  if (((*(byte *)(param_1 + 0x70) & 8) != 0) && (bVar1 == 3)) {
    iVar13 = 8 - (uint)*(byte *)(param_1 + 0x17c);
    iVar10 = 8 - (uint)*(byte *)(param_1 + 0x17d);
    local_34 = 8 - (uint)*(byte *)(param_1 + 0x17e);
    if ((iVar13 < 0) || (8 < iVar13)) {
      iVar13 = 0;
    }
    if ((iVar10 < 0) || (8 < iVar10)) {
      iVar10 = 0;
    }
    if ((local_34 < 0) || (8 < local_34)) {
      local_34 = 0;
    }
    if (*(ushort *)(param_1 + 0x118) != 0) {
      iVar11 = 0;
      uVar14 = (uint)*(ushort *)(param_1 + 0x118);
      do {
        pbVar9 = (byte *)(*(int *)(param_1 + 0x114) + iVar11);
        *pbVar9 = *pbVar9 >> ((byte)iVar13 & 0x1f);
        local_30 = (byte)iVar10;
        pbVar9 = (byte *)(*(int *)(param_1 + 0x114) + 1 + iVar11);
        *pbVar9 = *pbVar9 >> (local_30 & 0x1f);
        pbVar9 = (byte *)(*(int *)(param_1 + 0x114) + 2 + iVar11);
        iVar11 = iVar11 + 3;
        *pbVar9 = *pbVar9 >> ((byte)local_34 & 0x1f);
        uVar14 = uVar14 - 1;
      } while (uVar14 != 0);
    }
  }
  return;
}



/* function 0156ae50 FUN_0156ae50 */

undefined4 * __thiscall FUN_0156ae50(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  
  *param_1 = *param_2;
  thunk_FUN_01561cf0(param_2 + 1);
  param_1[0x2c] = param_2[0x2c];
  param_1[0x2d] = param_2[0x2d];
  param_1[0x2e] = param_2[0x2e];
  param_1[0x2f] = param_2[0x2f];
  param_1[0x30] = param_2[0x30];
  param_1[0x31] = param_2[0x31];
  param_1[0x32] = param_2[0x32];
  param_1[0x33] = param_2[0x33];
  param_1[0x34] = param_2[0x34];
  *(undefined1 *)(param_1 + 0x35) = *(undefined1 *)(param_2 + 0x35);
  *(undefined1 *)((int)param_1 + 0xd5) = *(undefined1 *)((int)param_2 + 0xd5);
  param_1[0x36] = param_2[0x36];
  *(undefined1 *)(param_1 + 0x37) = *(undefined1 *)(param_2 + 0x37);
  *(undefined1 *)((int)param_1 + 0xdd) = *(undefined1 *)((int)param_2 + 0xdd);
  *(undefined1 *)((int)param_1 + 0xde) = *(undefined1 *)((int)param_2 + 0xde);
  *(undefined1 *)((int)param_1 + 0xdf) = *(undefined1 *)((int)param_2 + 0xdf);
  param_1[0x38] = param_2[0x38];
  param_1[0x39] = param_2[0x39];
  param_1[0x3a] = param_2[0x3a];
  param_1[0x3b] = param_2[0x3b];
  param_1[0x3c] = param_2[0x3c];
  param_1[0x3d] = param_2[0x3d];
  param_1[0x3e] = param_2[0x3e];
  param_1[0x3f] = param_2[0x3f];
  param_1[0x40] = param_2[0x40];
  param_1[0x41] = param_2[0x41];
  param_1[0x42] = param_2[0x42];
  param_1[0x43] = param_2[0x43];
  param_1[0x44] = param_2[0x44];
  param_1[0x45] = param_2[0x45];
  param_1[0x46] = param_2[0x46];
  param_1[0x47] = param_2[0x47];
  param_1[0x48] = param_2[0x48];
  param_1[0x49] = param_2[0x49];
  param_1[0x4a] = param_2[0x4a];
  param_1[0x4b] = param_2[0x4b];
  *(undefined2 *)(param_1 + 0x4c) = *(undefined2 *)(param_2 + 0x4c);
  param_1[0x4d] = param_2[0x4d];
  param_1[0x4e] = param_2[0x4e];
  param_1[0x4f] = param_2[0x4f];
  param_1[0x50] = param_2[0x50];
  *(undefined2 *)(param_1 + 0x51) = *(undefined2 *)(param_2 + 0x51);
  param_1[0x52] = param_2[0x52];
  *(undefined1 *)(param_1 + 0x53) = *(undefined1 *)(param_2 + 0x53);
  *(undefined1 *)((int)param_1 + 0x14d) = *(undefined1 *)((int)param_2 + 0x14d);
  *(undefined1 *)((int)param_1 + 0x14e) = *(undefined1 *)((int)param_2 + 0x14e);
  *(undefined1 *)((int)param_1 + 0x14f) = *(undefined1 *)((int)param_2 + 0x14f);
  *(undefined1 *)(param_1 + 0x54) = *(undefined1 *)(param_2 + 0x54);
  *(undefined1 *)((int)param_1 + 0x151) = *(undefined1 *)((int)param_2 + 0x151);
  *(undefined1 *)((int)param_1 + 0x152) = *(undefined1 *)((int)param_2 + 0x152);
  *(undefined1 *)((int)param_1 + 0x153) = *(undefined1 *)((int)param_2 + 0x153);
  *(undefined1 *)(param_1 + 0x55) = *(undefined1 *)(param_2 + 0x55);
  *(undefined2 *)((int)param_1 + 0x156) = *(undefined2 *)((int)param_2 + 0x156);
  param_1[0x56] = param_2[0x56];
  param_1[0x57] = param_2[0x57];
  param_1[0x58] = param_2[0x58];
  puVar1 = param_1 + 0x59;
  iVar2 = 0x20;
  do {
    *(undefined1 *)puVar1 = *(undefined1 *)((int)puVar1 + ((int)param_2 - (int)param_1));
    puVar1 = (undefined4 *)((int)puVar1 + 1);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  param_1[0x61] = param_2[0x61];
  *(undefined1 *)(param_1 + 0x62) = *(undefined1 *)(param_2 + 0x62);
  param_1[99] = param_2[99];
  return param_1;
}


