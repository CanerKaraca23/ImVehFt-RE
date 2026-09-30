/* Full-analysis function mapping; decompilation is not original source. */

/* function 004aa6c0 FUN_004aa6c0 */

void __thiscall FUN_004aa6c0(int param_1,undefined1 param_2)

{
  undefined2 uVar1;
  
  *(undefined1 *)(param_1 + 0x52) = param_2;
  uVar1 = FUN_00821b40();
  *(undefined2 *)(param_1 + 0x5c) = uVar1;
  return;
}



/* function 004e7f80 FUN_004e7f80 */

void __fastcall FUN_004e7f80(undefined1 *param_1)

{
  undefined1 uVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *local_10;
  undefined4 *local_c;
  undefined4 *local_8;
  undefined1 *local_4;
  
  *param_1 = 0;
  param_1[1] = 0;
  puVar2 = (undefined4 *)FUN_00558f90();
  local_4 = param_1 + 8;
  puVar6 = (undefined4 *)(param_1 + 0x18);
  for (iVar4 = 0xe; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar6 = puVar6 + 1;
  }
  local_8 = &DAT_00b61d78;
  local_c = &DAT_00b620c0;
  local_10 = &DAT_00b62980;
  puVar6 = &DAT_00b62b40;
  puVar2 = (undefined4 *)(param_1 + 0x110);
  do {
    *puVar6 = 0xffffffff;
    puVar6[1] = 0xffffffff;
    puVar6[2] = 0xffffffff;
    puVar6[3] = 0xffffffff;
    puVar6[4] = 0xffffffff;
    puVar5 = local_10;
    for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = 0xffffffff;
      puVar5 = puVar5 + 1;
    }
    puVar5 = local_c;
    for (iVar4 = 0x28; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = 0xffffffff;
      puVar5 = puVar5 + 1;
    }
    puVar5 = local_8;
    for (iVar4 = 0xf; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = 0xffffffff;
      puVar5 = puVar5 + 1;
    }
    puVar2[-1] = 0xffffffff;
    *puVar2 = 0xffffffff;
    *(undefined1 *)((int)puVar2 + 0x17) = 0xff;
    *(undefined1 *)(puVar2 + 6) = 0xff;
    puVar2[1] = 0xffffffff;
    iVar4 = 0;
    puVar5 = puVar2 + 2;
    do {
      puVar5[-6] = 0;
      *puVar5 = 0xffffffff;
      *(undefined1 *)((int)puVar2 + iVar4 + 0x14) = 6;
      iVar4 = iVar4 + 1;
      puVar5 = puVar5 + 1;
    } while (iVar4 < 3);
    local_10 = local_10 + 8;
    local_c = local_c + 0x28;
    local_8 = local_8 + 0xf;
    puVar6 = puVar6 + 5;
    puVar2 = puVar2 + 0xb;
    *local_4 = 0;
    local_4 = local_4 + 1;
  } while ((int)puVar6 < 0xb62c58);
  uVar1 = FUN_004d9c10(1,0xd);
  param_1[0xad] = uVar1;
  param_1[0xae] = 0;
  param_1[0xac] = 2;
  puVar3 = param_1 + 0xb4;
  iVar4 = 5;
  puVar2 = (undefined4 *)(param_1 + 0x88);
  do {
    puVar3[7] = 0xff;
    *puVar2 = 0xffffffff;
    puVar2 = puVar2 + 1;
    *puVar3 = 6;
    puVar3 = puVar3 + 1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  *(undefined4 *)(param_1 + 0x9c) = 0xffffffff;
  *(undefined4 *)(param_1 + 0xa0) = 0xffffffff;
  *(undefined4 *)(param_1 + 0xa4) = 0;
  *(undefined4 *)(param_1 + 0xa8) = 0;
  param_1[0xb9] = 6;
  param_1[0xc0] = 0xff;
  param_1[0xba] = 6;
  param_1[0xc1] = 0xff;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0;
  *(undefined4 *)(param_1 + 0x50) = 0;
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x58) = 0;
  param_1[2] = 0;
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  param_1[3] = 0;
  param_1[0x16] = 0xff;
  param_1[0x17] = 0xff;
  param_1[7] = 1;
  param_1[4] = 1;
  puVar2 = (undefined4 *)(param_1 + 0x88);
  puVar6 = (undefined4 *)(param_1 + 0xc4);
  for (iVar4 = 0xf; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar6 = puVar6 + 1;
  }
  *(undefined4 *)(param_1 + 0x74) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x78) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x7c) = 0xffffffff;
  DAT_00b62c73 = 3;
  DAT_00b62c72 = 0xff;
  param_1[5] = 0;
  param_1[6] = 0;
  *(undefined4 *)(param_1 + 0x80) = 0;
  *(undefined4 *)(param_1 + 0x84) = 0;
  DAT_00b62c71 = 0;
  DAT_00b62c70 = 0;
  DAT_00b62c6f = 0;
  DAT_00b62c6e = 0;
  DAT_00b62c6d = 0;
  DAT_00b62c6c = 0;
  DAT_00b62c6b = 0;
  DAT_00b62c6a = 0;
  DAT_00b62c69 = 0;
  DAT_00b62c68 = 0;
  DAT_00b62c67 = 0;
  DAT_00b62c66 = 0;
  DAT_00b62c65 = 0;
  DAT_00b62c64 = 0;
  DAT_00b62c63 = 0;
  DAT_00b62c62 = 0;
  DAT_00b62c61 = 0;
  DAT_00b62c60 = 0;
  DAT_00b62c5f = 0;
  DAT_00b62c5e = 0;
  DAT_00b62c5d = 0;
  DAT_00b62c5c = 0;
  DAT_00b62c5b = 0;
  DAT_00b62c5a = 0xff;
  DAT_00b62c59 = 0xff;
  DAT_00b62c58 = 0xff;
  return;
}



/* function 004e8290 FUN_004e8290 */

void __thiscall FUN_004e8290(int param_1,char param_2)

{
  if ((param_2 == '\f') && (DAT_00b6b976 == 0)) {
    param_2 = '\r';
  }
  if ((DAT_00b7cb49 == '\0') && (DAT_00b7cb48 == '\0')) {
    *(int *)(param_1 + 0x7c) = (int)param_2;
    return;
  }
  *(int *)(param_1 + 0x78) = (int)param_2;
  *(undefined4 *)(param_1 + 0x5c) = DAT_00b7cb7c;
  return;
}



/* function 004efe50 FUN_004efe50 */

void __thiscall
FUN_004efe50(undefined2 *param_1,undefined2 param_2,undefined2 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
            undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined1 param_12,
            undefined2 param_13,undefined4 param_14,undefined2 param_15)

{
  int *piVar1;
  
  piVar1 = (int *)(param_1 + 4);
  param_1[1] = param_3;
  *param_1 = param_2;
  *(undefined4 *)(param_1 + 2) = param_4;
  if (*piVar1 != 0) {
    FUN_00571a00(piVar1);
    *piVar1 = 0;
  }
  *(undefined4 *)(param_1 + 10) = param_8;
  *(undefined4 *)(param_1 + 0xc) = param_9;
  *(undefined4 *)(param_1 + 0xe) = param_10;
  *(undefined4 *)(param_1 + 0x10) = param_14;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1a) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 6) = 0xffffffff;
  *(undefined4 *)(param_1 + 8) = 0xbf800000;
  *(undefined4 *)(param_1 + 0x1e) = 0;
  FUN_004ef880(param_5,param_6,param_7);
  *(undefined4 *)(param_1 + 0x28) = param_11;
  param_1[0x38] = 0xffff;
  param_1[0x2f] = 0;
  param_1[0x34] = 0;
  *(undefined4 *)(param_1 + 0x36) = 0;
  *(undefined1 *)(param_1 + 0x2a) = param_12;
  param_1[0x2b] = param_13;
  param_1[0x2c] = 1;
  param_1[0x2e] = param_15;
  *(undefined4 *)(param_1 + 0x30) = 0xc2c80000;
  *(undefined4 *)(param_1 + 0x32) = 0x3f800000;
  return;
}



/* function 0050a970 FUN_0050a970 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0050a970(int param_1,float param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = DAT_00b7cb84 - *(int *)(param_1 + 0x5c);
  fVar1 = (float)iVar3;
  if (iVar3 < 0) {
    fVar1 = fVar1 + _DAT_00858c54;
  }
  fVar1 = *(float *)(param_1 + 300) - fVar1 * _DAT_00858cdc;
  fVar2 = _FUN_00858ca0;
  if ((fVar1 < _FUN_00858ca0) && (fVar2 = fVar1, fVar1 <= DAT_00858b50)) {
    fVar2 = DAT_00858b50;
  }
  if (fVar2 < param_2) {
    *(float *)(param_1 + 300) = param_2;
    *(int *)(param_1 + 0x5c) = DAT_00b7cb84;
  }
  return;
}



/* function 0051a746 FUN_0051a746 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall
FUN_0051a746(int param_1,int param_2,undefined4 param_3,float param_4,float param_5,float param_6,
            float param_7,undefined4 param_8,float param_9,float param_10,float param_11,
            undefined4 param_12,undefined4 param_13,uint param_14,float param_15,undefined4 param_16
            ,float param_17,float param_18,undefined4 param_19,undefined4 param_20,float param_21,
            float param_22,undefined4 param_23,float param_24,float param_25,undefined4 param_26,
            float param_27,float param_28,undefined4 param_29,float param_30,float param_31)

{
  float *pfVar1;
  float fVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  float *pfVar11;
  float unaff_EDI;
  float10 fVar12;
  float10 fVar13;
  float fVar14;
  float fVar15;
  undefined1 *puVar16;
  float fVar17;
  float fVar18;
  undefined4 *puStack_24;
  undefined4 *puStack_20;
  undefined4 *puStack_1c;
  undefined4 *puStack_18;
  undefined1 *puStack_14;
  float fVar19;
  
  DAT_00b6f059 = 0;
  puStack_14 = (undefined1 *)0x51a75c;
  param_3 = (float)param_1;
  param_14 = _rand();
  param_14 = param_14 & 0xffff;
  puStack_14 = (undefined1 *)0x51a77a;
  iVar7 = FUN_00821b40();
  iVar7 = iVar7 * -0x9c;
  pfVar11 = (float *)(&DAT_00b6fec0 + iVar7);
  if (*(int *)(param_1 + 0x21c) == 0) {
    return 0;
  }
  if ((*(byte *)(*(int *)(param_1 + 0x21c) + 0x36) & 7) != 2) {
    return 0;
  }
  puStack_14 = &stack0x000000ac;
  puStack_18 = &param_14;
  puStack_1c = &param_25;
  puStack_20 = &param_2;
  puStack_24 = &param_18;
  puVar16 = (undefined1 *)&param_29;
  thunk_FUN_00407e04(&param_24,&stack0x00000000,&param_4,&param_11,&stack0x0000007c,puVar16,&param_7
                    );
  param_2 = DAT_00b7cb84;
  if ((DAT_008cc488 != 0x38) || (DAT_008ccb9c < DAT_00b7cb4c - 1U)) {
    DAT_008ccba4 = DAT_008ccba8 + DAT_00b7cb84;
    DAT_00b6ec70 = '\0';
    DAT_008cc488 = 0x38;
    DAT_008ccba0 = DAT_00b7cb84;
    FUN_0050e180();
    *(undefined4 *)(iVar7 + 0xb6ff04) = *(undefined4 *)(iVar7 + 0xb6ff08);
    *(float *)(iVar7 + 0xb6ff3c) = *(float *)(iVar7 + 0xb6feec) - *(float *)(iVar7 + 0xb6fef0);
    *(undefined1 *)(iVar7 + 0xb6ff00) = 0;
    *(undefined1 *)(iVar7 + 0xb6ff1c) = 0;
    *(undefined1 *)(iVar7 + 0xb6ff40) = 0;
    *(undefined1 *)(iVar7 + 0xb6ff41) = 0;
    *(undefined4 *)(iVar7 + 0xb6ff24) = *(undefined4 *)(iVar7 + 0xb6ff20);
    *(undefined1 *)(iVar7 + 0xb6ff48) = 0;
    FUN_0050e090();
    FUN_0050d860();
    iVar10 = 0;
    if (0 < *(int *)(iVar7 + 0xb6ff18)) {
      pfVar1 = (float *)(iVar7 + 0xb6fecc);
      do {
        fVar14 = *(float *)(iVar7 + 0xb6fedc);
        param_27 = (float)puStack_14 * fVar14;
        param_28 = unaff_EDI * fVar14;
        param_3 = (float)puStack_24 - (float)puStack_18 * fVar14;
        *pfVar1 = param_3;
        param_4 = (float)puStack_20 - param_27;
        param_5 = (float)puStack_1c - param_28;
        *(float *)(iVar7 + 0xb6fed0) = param_4;
        fVar14 = *(float *)(iVar7 + 0xb6fed8);
        *(float *)(iVar7 + 0xb6fed4) = param_5;
        param_24 = (float)puStack_14 * fVar14;
        param_25 = unaff_EDI * fVar14;
        param_9 = (float)puStack_18 * fVar14 + (float)puStack_24;
        *pfVar11 = param_9;
        param_10 = param_24 + (float)puStack_20;
        param_11 = param_25 + (float)puStack_1c;
        *(float *)(iVar7 + 0xb6fec4) = param_10;
        *(float *)(iVar7 + 0xb6fec8) = param_11;
        *(float *)(iVar7 + 0xb6fed4) = *(float *)(iVar7 + 0xb6fed4) + *(float *)(iVar7 + 0xb6fee0);
        *(float *)(iVar7 + 0xb6fec8) = *(float *)(iVar7 + 0xb6fee0) + *(float *)(iVar7 + 0xb6fec8);
        iVar8 = _rand();
        iVar9 = _rand();
        fVar14 = 1.0;
        if (iVar8 < 0x3fff) {
          fVar14 = -1.0;
        }
        fVar15 = _DAT_00858624;
        if (iVar9 < 0x3fff) {
          fVar15 = _DAT_00858c1c;
        }
        fVar2 = *(float *)(iVar7 + 0xb6fee4);
        param_30 = param_18 * fVar2;
        param_31 = fVar2 * DAT_00858b50;
        param_15 = param_31 * fVar14;
        *pfVar1 = param_17 * fVar2 * fVar14 + *pfVar1;
        *(float *)(iVar7 + 0xb6fed0) = param_30 * fVar14 + *(float *)(iVar7 + 0xb6fed0);
        *(float *)(iVar7 + 0xb6fed4) = param_15 + *(float *)(iVar7 + 0xb6fed4);
        uVar3 = *(undefined4 *)(iVar7 + 0xb6ff38);
        fVar14 = *(float *)(iVar7 + 0xb6fee4);
        fVar2 = *pfVar1;
        param_21 = param_18 * fVar14;
        uVar4 = *(undefined4 *)(iVar7 + 0xb6fed0);
        uVar5 = *(undefined4 *)(iVar7 + 0xb6fed4);
        param_22 = fVar14 * DAT_00858b50;
        param_6 = param_17 * fVar14 * fVar15;
        param_7 = param_21 * fVar15;
        *pfVar11 = param_6 + *pfVar11;
        *(float *)(iVar7 + 0xb6fec4) = param_7 + *(float *)(iVar7 + 0xb6fec4);
        *(float *)(iVar7 + 0xb6fec8) = fVar15 * param_22 + *(float *)(iVar7 + 0xb6fec8);
        iVar8 = FUN_00569e20(fVar2,uVar4,uVar5,uVar3,0,1,1,0,0,0,0);
        if (iVar8 == 0) {
          DAT_00b7cd68 = param_12;
          cVar6 = FUN_0056ba00(&puStack_24,pfVar1,&stack0x00000090,&param_16,1,1,0,0,0,0,0,0);
          DAT_00b7cd68 = 0;
          if (cVar6 == '\0') {
            iVar10 = _rand();
            *(bool *)(iVar7 + 0xb6ff41) = iVar10 < 0x3fff;
            iVar10 = _rand();
            *(bool *)(iVar7 + 0xb6ff48) = iVar10 < 0x3fff;
            goto LAB_0051ab85;
          }
        }
        iVar10 = iVar10 + 1;
      } while (iVar10 < *(int *)(iVar7 + 0xb6ff18));
    }
    *(undefined1 *)(iVar7 + 0xb6ff00) = 0;
    *(undefined1 *)(iVar7 + 0xb6ff1c) = 0;
    *(float *)(iVar7 + 0xb6ff3c) = *(float *)(iVar7 + 0xb6feec) - *(float *)(iVar7 + 0xb6fef0);
    *(undefined1 *)(iVar7 + 0xb6ff40) = 0;
    *(undefined1 *)(iVar7 + 0xb6ff41) = 0;
    *(undefined4 *)(iVar7 + 0xb6ff24) = *(undefined4 *)(iVar7 + 0xb6ff20);
    *(undefined4 *)(iVar7 + 0xb6ff04) = *(undefined4 *)(iVar7 + 0xb6ff08);
    *(undefined1 *)(iVar7 + 0xb6ff48) = 0;
    DAT_00b6ec70 = 1;
    return 0;
  }
LAB_0051ab85:
  iVar10 = param_2;
  if (DAT_00b6ec70 != '\0') {
    return 0;
  }
  fVar15 = (float)(param_2 - DAT_008ccba0) / (float)(DAT_008ccba4 - DAT_008ccba0);
  param_3 = (*pfVar11 - *(float *)(iVar7 + 0xb6fecc)) * fVar15 + *(float *)(iVar7 + 0xb6fecc);
  fVar14 = *(float *)(iVar7 + 0xb6fef4);
  param_4 = (*(float *)(iVar7 + 0xb6fec4) - *(float *)(iVar7 + 0xb6fed0)) * fVar15 +
            *(float *)(iVar7 + 0xb6fed0);
  fVar2 = (*(float *)(iVar7 + 0xb6fec8) - *(float *)(iVar7 + 0xb6fed4)) * fVar15 +
          *(float *)(iVar7 + 0xb6fed4);
  param_15 = unaff_EDI * (float)puVar16;
  param_6 = (float)puStack_18 * (float)puVar16 * fVar14 + (float)puStack_18;
  param_7 = (float)puStack_14 * (float)puVar16 * fVar14 + (float)puStack_14;
  puStack_24 = (undefined4 *)(param_6 + (float)puStack_24);
  puStack_20 = (undefined4 *)(param_7 + (float)puStack_20);
  puStack_1c = (undefined4 *)(param_15 * fVar14 + unaff_EDI + (float)puStack_1c);
  fVar14 = (float)puStack_24 - param_3;
  fVar19 = (float)puStack_20 - param_4;
  fVar17 = SQRT(fVar14 * fVar14 + fVar19 * fVar19);
  fVar18 = _DAT_00858624 / fVar17;
  puStack_18 = (undefined4 *)(fVar14 * fVar18);
  puStack_14 = (undefined1 *)(fVar18 * fVar19);
  fVar14 = param_3;
  fVar19 = param_4;
  if (fVar17 < *(float *)(iVar7 + 0xb6ff34)) {
    fVar14 = (float)puStack_24 - (float)puStack_18 * *(float *)(iVar7 + 0xb6ff34);
    fVar19 = (float)puStack_20 - (float)puStack_14 * *(float *)(iVar7 + 0xb6ff34);
  }
  fVar12 = (float10)*(float *)(iVar7 + 0xb6fef0);
  if ((fVar15 < *(float *)(iVar7 + 0xb6fee8)) && (*(char *)(iVar7 + 0xb6ff41) == '\0')) {
    fVar12 = (float10)fsin(((float10)_DAT_00859070 -
                           ((float10)_DAT_00858624 / (float10)*(float *)(iVar7 + 0xb6fee8)) *
                           (float10)fVar15 * (float10)_DAT_0085a994) * (float10)_DAT_008595ec);
    fVar12 = ((float10)*(float *)(iVar7 + 0xb6fef0) - (float10)*(float *)(iVar7 + 0xb6feec)) *
             (fVar12 + (float10)_DAT_00858624) * (float10)_DAT_00858b8c +
             (float10)*(float *)(iVar7 + 0xb6feec);
  }
  fVar13 = (float10)DAT_00858b50;
  fVar17 = SQRT((fVar14 - (float)puStack_24) * (fVar14 - (float)puStack_24) +
                (fVar19 - (float)puStack_20) * (fVar19 - (float)puStack_20) +
                (fVar2 - (float)puStack_1c) * (fVar2 - (float)puStack_1c));
  if (*(float *)(iVar7 + 0xb6ff28) < fVar17) {
    fVar13 = ((float10)fVar17 - (float10)*(float *)(iVar7 + 0xb6ff28)) /
             ((float10)*(float *)(iVar7 + 0xb6ff2c) - (float10)*(float *)(iVar7 + 0xb6ff28));
    if ((float10)DAT_00858b50 <= fVar13) {
      if ((float10)_DAT_00858624 < fVar13) {
        fVar13 = (float10)_DAT_00858624;
      }
    }
    else {
      fVar13 = (float10)DAT_00858b50;
    }
    fVar13 = (float10)fsin(((float10)_DAT_00859070 - fVar13 * (float10)_DAT_0085a994) *
                           (float10)_DAT_008595ec);
    fVar13 = (fVar13 + (float10)_DAT_00858624) * (float10)_DAT_00858b8c *
             (float10)*(float *)(iVar7 + 0xb6ff30);
  }
  fVar17 = (float)(fVar12 - fVar13);
  fVar18 = fVar15 * *(float *)(iVar7 + 0xb6fef8);
  param_5 = fVar2;
  if ((*(char *)(iVar7 + 0xb6ff1c) != '\0') ||
     (iVar8 = FUN_00569e20(fVar14,fVar19,fVar2,DAT_008ccd28,0,1,1,0,0,0,0), iVar8 != 0)) {
    if ((_DAT_00b70064 & 1) == 0) {
      _DAT_00b70064 = _DAT_00b70064 | 1;
    }
    if (*(char *)(iVar7 + 0xb6ff1c) == '\0') {
      _DAT_00b70058 = fVar14;
      *(undefined1 *)(iVar7 + 0xb6ff1c) = 1;
      DAT_008ccd24 = 100;
      _DAT_00b7005c = fVar19;
      _DAT_00b70060 = fVar2;
    }
    if (DAT_008ccd24 < 0) {
      DAT_008ccd24 = DAT_008ccd24 + -1;
      DAT_00b6ec70 = 1;
      return 0;
    }
    param_15 = fVar2 - _DAT_00b70060;
    param_6 = (fVar14 - _DAT_00b70058) * _DAT_008ccd20;
    param_9 = param_6 + _DAT_00b70058;
    param_10 = (fVar19 - _DAT_00b7005c) * _DAT_008ccd20 + _DAT_00b7005c;
    param_11 = param_15 * _DAT_008ccd20 + _DAT_00b70060;
    DAT_008ccd24 = DAT_008ccd24 + -1;
  }
  if (*(char *)(iVar7 + 0xb6ff00) == '\0') {
    DAT_00b7cd68 = param_12;
    cVar6 = FUN_0056ba00(&puStack_24,&stack0xfffffff8,&stack0x00000090,&param_16,1,1,0,0,0,0,0,0);
    DAT_00b7cd68 = 0;
    if (cVar6 == '\0') {
      iVar8 = *(int *)(iVar7 + 0xb6ff24) + 1;
      *(int *)(iVar7 + 0xb6ff24) = iVar8;
      if (*(int *)(iVar7 + 0xb6ff20) < iVar8) {
        *(int *)(iVar7 + 0xb6ff24) = *(int *)(iVar7 + 0xb6ff20);
      }
    }
    else {
      *(undefined1 *)(iVar7 + 0xb6ff40) = 1;
      if ((*(char *)(iVar7 + 0xb6ff48) == '\0') &&
         (*(int *)(iVar7 + 0xb6ff24) <
          (int)(*(int *)(iVar7 + 0xb6ff20) + (*(int *)(iVar7 + 0xb6ff20) >> 0x1f & 3U)) >> 2)) {
        *(float *)(iVar7 + 0xb6ff44) = fVar17;
        *(undefined1 *)(iVar7 + 0xb6ff48) = 1;
        *(int *)(iVar7 + 0xb6ff4c) = iVar10;
        *(int *)(iVar7 + 0xb6ff50) = *(int *)(iVar7 + 0xb6ff58) + iVar10;
      }
      iVar8 = *(int *)(iVar7 + 0xb6ff24);
      *(int *)(iVar7 + 0xb6ff24) = iVar8 + -1;
      if (iVar8 == 0) {
        *(undefined4 **)(iVar7 + 0xb6ff0c) = puStack_24;
        *(undefined4 **)(iVar7 + 0xb6ff10) = puStack_20;
        *(undefined4 **)(iVar7 + 0xb6ff14) = puStack_1c;
        *(undefined1 *)(iVar7 + 0xb6ff00) = 1;
      }
    }
  }
  else {
    puStack_24 = *(undefined4 **)(iVar7 + 0xb6ff0c);
    puStack_20 = *(undefined4 **)(iVar7 + 0xb6ff10);
    puStack_1c = *(undefined4 **)(iVar7 + 0xb6ff14);
    iVar8 = *(int *)(iVar7 + 0xb6ff04);
    *(int *)(iVar7 + 0xb6ff04) = iVar8 + -1;
    if (iVar8 == 0) {
      DAT_00b6ec70 = 1;
      return 0;
    }
  }
  if (*(char *)(iVar7 + 0xb6ff48) == '\0') {
    if (*(float *)(iVar7 + 0xb6ff54) <= fVar15) {
      *(float *)(iVar7 + 0xb6ff44) = fVar17;
      *(undefined1 *)(iVar7 + 0xb6ff48) = 1;
      *(int *)(iVar7 + 0xb6ff4c) = iVar10;
      *(int *)(iVar7 + 0xb6ff50) = *(int *)(iVar7 + 0xb6ff58) + iVar10;
    }
    if (*(char *)(iVar7 + 0xb6ff48) == '\0') goto LAB_0051b0c7;
  }
  fVar12 = ((float10)param_2 - (float10)*(int *)(iVar7 + 0xb6ff4c)) /
           ((float10)*(int *)(iVar7 + 0xb6ff50) - (float10)*(int *)(iVar7 + 0xb6ff4c));
  if ((float10)DAT_00858b50 <= fVar12) {
    if ((float10)_DAT_00858624 < fVar12) {
      fVar12 = (float10)_DAT_00858624;
    }
  }
  else {
    fVar12 = (float10)DAT_00858b50;
  }
  fVar12 = (float10)fsin(((float10)_DAT_00859070 - fVar12 * (float10)_DAT_0085a994) *
                         (float10)_DAT_008595ec);
  fVar17 = (float)(((float10)*(float *)(iVar7 + 0xb6feec) - (float10)*(float *)(iVar7 + 0xb6ff44)) *
                   (fVar12 + (float10)_DAT_00858624) * (float10)_DAT_00858b8c +
                  (float10)*(float *)(iVar7 + 0xb6ff44));
LAB_0051b0c7:
  cVar6 = FUN_00517400(0x14,&stack0xfffffff8,&puStack_24,fVar15,0);
  if (cVar6 != '\0') {
    DAT_00b6ec70 = 1;
    return 0;
  }
  FUN_0050dd70(&stack0xfffffff8,&puStack_24,fVar18,fVar17,*(undefined4 *)(iVar7 + 0xb6fefc),
               0x3f800000);
  return 1;
}



/* function 0055f4c9 FUN_0055f4c9 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0055f4c9(int param_1,int param_2)

{
  byte bVar1;
  float *in_EAX;
  int unaff_ESI;
  int unaff_EDI;
  
  *in_EAX = (float)unaff_EDI;
  in_EAX[1] = (float)(byte)(&DAT_00b7c310)[param_1];
  in_EAX[2] = (float)(byte)(&DAT_00b7c258)[param_1];
  in_EAX[3] = (float)(byte)(&DAT_00b7c1a0)[param_1];
  in_EAX[4] = (float)(byte)(&DAT_00b7c0e8)[param_1];
  in_EAX[5] = (float)(byte)(&DAT_00b7c030)[param_1];
  *(ushort *)(in_EAX + 9) = (ushort)(byte)(&DAT_00b7bf78)[param_1];
  *(ushort *)((int)in_EAX + 0x26) = (ushort)(byte)(&DAT_00b7bec0)[param_1];
  *(ushort *)(in_EAX + 10) = (ushort)(byte)(&DAT_00b7be08)[param_1];
  *(ushort *)((int)in_EAX + 0x2a) = (ushort)(byte)(&DAT_00b7bd50)[param_1];
  *(ushort *)(in_EAX + 0xb) = (ushort)(byte)(&DAT_00b7bc98)[param_1];
  *(ushort *)((int)in_EAX + 0x2e) = (ushort)(byte)(&DAT_00b7bbe0)[param_1];
  *(ushort *)(in_EAX + 0xc) = (ushort)(byte)(&DAT_00b7bb28)[param_1];
  *(ushort *)((int)in_EAX + 0x32) = (ushort)(byte)(&DAT_00b7ba70)[param_1];
  *(ushort *)(in_EAX + 0xd) = (ushort)(byte)(&DAT_00b7b9b8)[param_1];
  *(ushort *)((int)in_EAX + 0x36) = (ushort)(byte)(&DAT_00b7b900)[param_1];
  *(ushort *)(in_EAX + 0xe) = (ushort)(byte)(&DAT_00b7b848)[param_1];
  *(ushort *)((int)in_EAX + 0x3a) = (ushort)(byte)(&DAT_00b7b790)[param_1];
  in_EAX[0xf] = (float)(int)(char)(&DAT_00b7b6d8)[param_1];
  in_EAX[0x10] = (float)(int)(char)(&DAT_00b7b620)[param_1];
  in_EAX[0x11] = (float)(int)(char)(&DAT_00b7b568)[param_1];
  *(ushort *)(in_EAX + 0x12) = (ushort)(byte)(&DAT_00b7b4b0)[param_1];
  *(ushort *)((int)in_EAX + 0x4a) = (ushort)(byte)(&DAT_00b7b3f8)[param_1];
  *(ushort *)(in_EAX + 0x13) = (ushort)(byte)(&DAT_00b7b340)[param_1];
  in_EAX[0x14] = (float)(int)*(short *)(&DAT_00b7b1d0 + param_1 * 2);
  in_EAX[0x15] = (float)(int)*(short *)(&DAT_00b7b060 + param_1 * 2);
  in_EAX[0x16] = (float)(byte)(&DAT_00b7afa8)[param_1];
  *(ushort *)(in_EAX + 0x17) = (ushort)(byte)(&DAT_00b7aef0)[param_1];
  *(ushort *)((int)in_EAX + 0x5e) = (ushort)(byte)(&DAT_00b7ae38)[param_1];
  *(ushort *)(in_EAX + 0x18) = (ushort)(byte)(&DAT_00b7ad80)[param_1];
  *(ushort *)((int)in_EAX + 0x62) = (ushort)(byte)(&DAT_00b7acc8)[param_1];
  *(ushort *)(in_EAX + 0x19) = (ushort)(byte)(&DAT_00b7ac10)[param_1];
  *(ushort *)((int)in_EAX + 0x66) = (ushort)(byte)(&DAT_00b7ab58)[unaff_ESI + param_2];
  in_EAX[0x1a] = (float)(byte)(&DAT_00b7aaa0)[unaff_ESI + param_2];
  in_EAX[0x1b] = (float)(byte)(&DAT_00b7a9e8)[unaff_ESI + param_2];
  in_EAX[0x1c] = (float)(byte)(&DAT_00b7a930)[unaff_ESI + param_2];
  in_EAX[0x1d] = (float)(byte)(&DAT_00b7a878)[unaff_ESI + param_2];
  in_EAX[0x1e] = (float)(byte)(&DAT_00b7a7c0)[unaff_ESI + param_2];
  in_EAX[0x1f] = (float)(byte)(&DAT_00b7a708)[unaff_ESI + param_2];
  in_EAX[0x20] = (float)(byte)(&DAT_00b7a650)[unaff_ESI + param_2];
  in_EAX[0x21] = (float)(byte)(&DAT_00b7a598)[unaff_ESI + param_2];
  in_EAX[0x22] = (float)(byte)(&DAT_00b7a4e0)[unaff_ESI + param_2];
  in_EAX[0x23] = (float)(byte)(&DAT_00b7a428)[unaff_ESI + param_2];
  in_EAX[0x24] = (float)(byte)(&DAT_00b7a370)[unaff_ESI + param_2];
  in_EAX[0x25] = (float)(byte)(&DAT_00b7a2b8)[unaff_ESI + param_2];
  in_EAX[0x26] = (float)(byte)(&DAT_00b7a200)[unaff_ESI + param_2];
  in_EAX[0x27] = (float)(uint)(byte)(&DAT_00b7a148)[unaff_ESI + param_2];
  *(ushort *)(in_EAX + 0x28) = (ushort)(byte)(&DAT_00b7a090)[unaff_ESI + param_2];
  bVar1 = (&DAT_00b79fd8)[unaff_ESI + param_2];
  in_EAX[0x2a] = 1.0;
  in_EAX[0x29] = (float)bVar1 * _DAT_00858c58;
  return;
}



/* function 0055f870 FUN_0055f870 */

void __thiscall
FUN_0055f870(float *param_1,float *param_2,float *param_3,float param_4,float param_5,char param_6)

{
  undefined2 uVar1;
  float fVar2;
  
  if (param_6 == '\0') {
    uVar1 = FUN_00821b40();
    *(undefined2 *)(param_1 + 9) = uVar1;
    uVar1 = FUN_00821b40();
    *(undefined2 *)((int)param_1 + 0x26) = uVar1;
    uVar1 = FUN_00821b40();
    *(undefined2 *)(param_1 + 10) = uVar1;
    uVar1 = FUN_00821b40();
    *(undefined2 *)((int)param_1 + 0x2a) = uVar1;
    uVar1 = FUN_00821b40();
    *(undefined2 *)(param_1 + 0xb) = uVar1;
    uVar1 = FUN_00821b40();
    *(undefined2 *)((int)param_1 + 0x2e) = uVar1;
    uVar1 = FUN_00821b40();
    *(undefined2 *)(param_1 + 0xc) = uVar1;
    uVar1 = FUN_00821b40();
    *(undefined2 *)((int)param_1 + 0x32) = uVar1;
    uVar1 = FUN_00821b40();
    *(undefined2 *)(param_1 + 0xd) = uVar1;
    uVar1 = FUN_00821b40();
    *(undefined2 *)((int)param_1 + 0x36) = uVar1;
    uVar1 = FUN_00821b40();
    *(undefined2 *)(param_1 + 0xe) = uVar1;
    uVar1 = FUN_00821b40();
    *(undefined2 *)((int)param_1 + 0x3a) = uVar1;
    param_1[0xf] = param_5 * param_3[0xf] + param_4 * param_2[0xf];
    uVar1 = FUN_00821b40();
    *(undefined2 *)(param_1 + 0x17) = uVar1;
    uVar1 = FUN_00821b40();
    *(undefined2 *)((int)param_1 + 0x5e) = uVar1;
    uVar1 = FUN_00821b40();
    *(undefined2 *)(param_1 + 0x18) = uVar1;
    uVar1 = FUN_00821b40();
    *(undefined2 *)((int)param_1 + 0x62) = uVar1;
    uVar1 = FUN_00821b40();
    *(undefined2 *)(param_1 + 0x19) = uVar1;
    uVar1 = FUN_00821b40();
    *(undefined2 *)((int)param_1 + 0x66) = uVar1;
  }
  *param_1 = param_5 * *param_3 + param_4 * *param_2;
  param_1[1] = param_5 * param_3[1] + param_4 * param_2[1];
  param_1[2] = param_5 * param_3[2] + param_4 * param_2[2];
  param_1[3] = param_5 * param_3[3] + param_4 * param_2[3];
  param_1[4] = param_5 * param_3[4] + param_4 * param_2[4];
  param_1[5] = param_5 * param_3[5] + param_4 * param_2[5];
  param_1[0x10] = param_5 * param_3[0x10] + param_4 * param_2[0x10];
  param_1[0x11] = param_5 * param_3[0x11] + param_4 * param_2[0x11];
  uVar1 = FUN_00821b40();
  *(undefined2 *)(param_1 + 0x12) = uVar1;
  uVar1 = FUN_00821b40();
  *(undefined2 *)((int)param_1 + 0x4a) = uVar1;
  uVar1 = FUN_00821b40();
  *(undefined2 *)(param_1 + 0x13) = uVar1;
  param_1[0x14] = param_5 * param_3[0x14] + param_4 * param_2[0x14];
  param_1[0x15] = param_5 * param_3[0x15] + param_4 * param_2[0x15];
  param_1[0x1e] = param_5 * param_3[0x1e] + param_4 * param_2[0x1e];
  param_1[0x1f] = param_5 * param_3[0x1f] + param_4 * param_2[0x1f];
  param_1[0x20] = param_5 * param_3[0x20] + param_4 * param_2[0x20];
  param_1[0x21] = param_5 * param_3[0x21] + param_4 * param_2[0x21];
  param_1[0x22] = param_5 * param_3[0x22] + param_4 * param_2[0x22];
  param_1[0x23] = param_5 * param_3[0x23] + param_4 * param_2[0x23];
  param_1[0x24] = param_5 * param_3[0x24] + param_4 * param_2[0x24];
  param_1[0x25] = param_5 * param_3[0x25] + param_4 * param_2[0x25];
  param_1[0x16] = param_5 * param_3[0x16] + param_4 * param_2[0x16];
  param_1[0x26] = param_5 * param_3[0x26] + param_4 * param_2[0x26];
  fVar2 = (float)FUN_00821b40();
  param_1[0x27] = fVar2;
  uVar1 = FUN_00821b40();
  *(undefined2 *)(param_1 + 0x28) = uVar1;
  param_1[0x29] = param_5 * param_3[0x29] + param_4 * param_2[0x29];
  param_1[0x2a] = param_5 * param_3[0x2a] + param_4 * param_2[0x2a];
  param_1[0x1a] = param_5 * param_3[0x1a] + param_4 * param_2[0x1a];
  param_1[0x1b] = param_5 * param_3[0x1b] + param_4 * param_2[0x1b];
  param_1[0x1c] = param_5 * param_3[0x1c] + param_4 * param_2[0x1c];
  param_1[0x1d] = param_5 * param_3[0x1d] + param_4 * param_2[0x1d];
  return;
}



/* function 005c7130 FUN_005c7130 */

void FUN_005c7130(int *param_1,int param_2)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  if (param_1[5] != 100) {
    *(undefined4 *)(*param_1 + 0x14) = 0x14;
    *(int *)(*param_1 + 0x18) = param_1[5];
    (**(code **)*param_1)(param_1);
  }
  param_1[0x10] = param_2;
  *(undefined1 *)(param_1 + 0x31) = 0;
  *(undefined1 *)(param_1 + 0x33) = 0;
  switch(param_2) {
  case 0:
    iVar3 = param_1[9];
    param_1[0xf] = iVar3;
    if ((iVar3 < 1) || (4 < iVar3)) {
      *(undefined4 *)(*param_1 + 0x14) = 0x1a;
      *(int *)(*param_1 + 0x18) = param_1[0xf];
      *(undefined4 *)(*param_1 + 0x1c) = 4;
      (**(code **)*param_1)(param_1);
    }
    iVar3 = 0;
    if (0 < param_1[0xf]) {
      iVar4 = 0;
      do {
        piVar2 = (int *)(param_1[0x11] + iVar4);
        *piVar2 = iVar3;
        piVar2[2] = 1;
        piVar2[3] = 1;
        piVar2[4] = 0;
        piVar2[5] = 0;
        piVar2[6] = 0;
        iVar3 = iVar3 + 1;
        iVar4 = iVar4 + 0x54;
      } while (iVar3 < param_1[0xf]);
      return;
    }
    break;
  case 1:
    *(undefined1 *)(param_1 + 0x31) = 1;
    param_1[0xf] = 1;
    puVar1 = (undefined4 *)param_1[0x11];
    *puVar1 = 1;
    puVar1[2] = 1;
    puVar1[3] = 1;
    puVar1[4] = 0;
    puVar1[5] = 0;
    puVar1[6] = 0;
    return;
  case 2:
    puVar1 = (undefined4 *)param_1[0x11];
    param_1[0xf] = 3;
    *(undefined1 *)(param_1 + 0x33) = 1;
    puVar1[2] = 1;
    puVar1[3] = 1;
    *puVar1 = 0x52;
    puVar1[4] = 0;
    puVar1[5] = 0;
    puVar1[6] = 0;
    iVar3 = param_1[0x11];
    *(undefined4 *)(iVar3 + 0x5c) = 1;
    *(undefined4 *)(iVar3 + 0x60) = 1;
    *(undefined4 *)(iVar3 + 0x54) = 0x47;
    *(undefined4 *)(iVar3 + 100) = 0;
    *(undefined4 *)(iVar3 + 0x68) = 0;
    *(undefined4 *)(iVar3 + 0x6c) = 0;
    iVar3 = param_1[0x11];
    *(undefined4 *)(iVar3 + 0xb0) = 1;
    *(undefined4 *)(iVar3 + 0xb4) = 1;
    *(undefined4 *)(iVar3 + 0xa8) = 0x42;
    *(undefined4 *)(iVar3 + 0xb8) = 0;
    *(undefined4 *)(iVar3 + 0xbc) = 0;
    *(undefined4 *)(iVar3 + 0xc0) = 0;
    return;
  case 3:
    puVar1 = (undefined4 *)param_1[0x11];
    param_1[0xf] = 3;
    *(undefined1 *)(param_1 + 0x31) = 1;
    *puVar1 = 1;
    puVar1[4] = 0;
    puVar1[5] = 0;
    puVar1[6] = 0;
    puVar1[2] = 2;
    puVar1[3] = 2;
    iVar3 = param_1[0x11];
    *(undefined4 *)(iVar3 + 0x5c) = 1;
    *(undefined4 *)(iVar3 + 0x60) = 1;
    *(undefined4 *)(iVar3 + 100) = 1;
    *(undefined4 *)(iVar3 + 0x68) = 1;
    *(undefined4 *)(iVar3 + 0x6c) = 1;
    *(undefined4 *)(iVar3 + 0x54) = 2;
    iVar3 = param_1[0x11];
    *(undefined4 *)(iVar3 + 0xb0) = 1;
    *(undefined4 *)(iVar3 + 0xb4) = 1;
    *(undefined4 *)(iVar3 + 0xb8) = 1;
    *(undefined4 *)(iVar3 + 0xbc) = 1;
    *(undefined4 *)(iVar3 + 0xc0) = 1;
    *(undefined4 *)(iVar3 + 0xa8) = 3;
    return;
  case 4:
    puVar1 = (undefined4 *)param_1[0x11];
    param_1[0xf] = 4;
    *(undefined1 *)(param_1 + 0x33) = 1;
    puVar1[2] = 1;
    puVar1[3] = 1;
    *puVar1 = 0x43;
    puVar1[4] = 0;
    puVar1[5] = 0;
    puVar1[6] = 0;
    iVar3 = param_1[0x11];
    *(undefined4 *)(iVar3 + 0x5c) = 1;
    *(undefined4 *)(iVar3 + 0x60) = 1;
    *(undefined4 *)(iVar3 + 0x54) = 0x4d;
    *(undefined4 *)(iVar3 + 100) = 0;
    *(undefined4 *)(iVar3 + 0x68) = 0;
    *(undefined4 *)(iVar3 + 0x6c) = 0;
    iVar3 = param_1[0x11];
    *(undefined4 *)(iVar3 + 0xb0) = 1;
    *(undefined4 *)(iVar3 + 0xb4) = 1;
    *(undefined4 *)(iVar3 + 0xa8) = 0x59;
    *(undefined4 *)(iVar3 + 0xb8) = 0;
    *(undefined4 *)(iVar3 + 0xbc) = 0;
    *(undefined4 *)(iVar3 + 0xc0) = 0;
    iVar3 = param_1[0x11];
    *(undefined4 *)(iVar3 + 0x104) = 1;
    *(undefined4 *)(iVar3 + 0x108) = 1;
    *(undefined4 *)(iVar3 + 0xfc) = 0x4b;
    *(undefined4 *)(iVar3 + 0x10c) = 0;
    *(undefined4 *)(iVar3 + 0x110) = 0;
    *(undefined4 *)(iVar3 + 0x114) = 0;
    return;
  case 5:
    puVar1 = (undefined4 *)param_1[0x11];
    param_1[0xf] = 4;
    *(undefined1 *)(param_1 + 0x33) = 1;
    *puVar1 = 1;
    puVar1[4] = 0;
    puVar1[5] = 0;
    puVar1[6] = 0;
    puVar1[2] = 2;
    puVar1[3] = 2;
    iVar3 = param_1[0x11];
    *(undefined4 *)(iVar3 + 0x5c) = 1;
    *(undefined4 *)(iVar3 + 0x60) = 1;
    *(undefined4 *)(iVar3 + 100) = 1;
    *(undefined4 *)(iVar3 + 0x68) = 1;
    *(undefined4 *)(iVar3 + 0x6c) = 1;
    *(undefined4 *)(iVar3 + 0x54) = 2;
    iVar3 = param_1[0x11];
    *(undefined4 *)(iVar3 + 0xb0) = 1;
    *(undefined4 *)(iVar3 + 0xb4) = 1;
    *(undefined4 *)(iVar3 + 0xb8) = 1;
    *(undefined4 *)(iVar3 + 0xbc) = 1;
    *(undefined4 *)(iVar3 + 0xc0) = 1;
    *(undefined4 *)(iVar3 + 0xa8) = 3;
    iVar3 = param_1[0x11];
    *(undefined4 *)(iVar3 + 0xfc) = 4;
    *(undefined4 *)(iVar3 + 0x104) = 2;
    *(undefined4 *)(iVar3 + 0x108) = 2;
    *(undefined4 *)(iVar3 + 0x10c) = 0;
    *(undefined4 *)(iVar3 + 0x110) = 0;
    *(undefined4 *)(iVar3 + 0x114) = 0;
    return;
  default:
    *(undefined4 *)(*param_1 + 0x14) = 10;
    (**(code **)*param_1)(param_1);
  }
  return;
}



/* function 005c7420 FUN_005c7420 */

void FUN_005c7420(int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  switch(param_1[10]) {
  case 0:
    FUN_005c7130(param_1,0);
    return;
  case 1:
    if (param_1[5] != 100) {
      *(undefined4 *)(*param_1 + 0x14) = 0x14;
      *(int *)(*param_1 + 0x18) = param_1[5];
      (**(code **)*param_1)(param_1);
    }
    break;
  case 2:
  case 3:
    FUN_005c7130(param_1,3);
    return;
  case 4:
    FUN_005c7130(param_1,4);
    return;
  case 5:
    if (param_1[5] != 100) {
      *(undefined4 *)(*param_1 + 0x14) = 0x14;
      *(int *)(*param_1 + 0x18) = param_1[5];
      (**(code **)*param_1)(param_1);
    }
    puVar1 = (undefined4 *)param_1[0x11];
    param_1[0x10] = 5;
    param_1[0xf] = 4;
    *(undefined1 *)(param_1 + 0x33) = 1;
    *(undefined1 *)(param_1 + 0x31) = 0;
    *puVar1 = 1;
    puVar1[4] = 0;
    puVar1[5] = 0;
    puVar1[6] = 0;
    puVar1[2] = 2;
    puVar1[3] = 2;
    iVar2 = param_1[0x11];
    *(undefined4 *)(iVar2 + 0x54) = 2;
    *(undefined4 *)(iVar2 + 0x5c) = 1;
    *(undefined4 *)(iVar2 + 0x60) = 1;
    *(undefined4 *)(iVar2 + 100) = 1;
    *(undefined4 *)(iVar2 + 0x68) = 1;
    *(undefined4 *)(iVar2 + 0x6c) = 1;
    iVar2 = param_1[0x11];
    *(undefined4 *)(iVar2 + 0xa8) = 3;
    *(undefined4 *)(iVar2 + 0xb0) = 1;
    *(undefined4 *)(iVar2 + 0xb4) = 1;
    *(undefined4 *)(iVar2 + 0xb8) = 1;
    *(undefined4 *)(iVar2 + 0xbc) = 1;
    *(undefined4 *)(iVar2 + 0xc0) = 1;
    iVar2 = param_1[0x11];
    *(undefined4 *)(iVar2 + 0x104) = 2;
    *(undefined4 *)(iVar2 + 0x108) = 2;
    *(undefined4 *)(iVar2 + 0xfc) = 4;
    *(undefined4 *)(iVar2 + 0x10c) = 0;
    *(undefined4 *)(iVar2 + 0x110) = 0;
    *(undefined4 *)(iVar2 + 0x114) = 0;
    return;
  default:
    *(undefined4 *)(*param_1 + 0x14) = 9;
    (**(code **)*param_1)(param_1);
    return;
  }
  param_1[0x10] = 1;
  *(undefined1 *)(param_1 + 0x31) = 1;
  param_1[0xf] = 1;
  *(undefined1 *)(param_1 + 0x33) = 0;
  puVar1 = (undefined4 *)param_1[0x11];
  *puVar1 = 1;
  puVar1[2] = 1;
  puVar1[3] = 1;
  puVar1[4] = 0;
  puVar1[5] = 0;
  puVar1[6] = 0;
  return;
}



/* function 005edf10 FUN_005edf10 */

void __fastcall FUN_005edf10(int param_1)

{
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined4 *)(param_1 + 0x4c) = 0;
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x58) = 0;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  *(undefined4 *)(param_1 + 100) = 0;
  *(undefined4 *)(param_1 + 0x68) = 0;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0x74) = 0;
  *(undefined4 *)(param_1 + 0x78) = 0;
  *(undefined4 *)(param_1 + 0x7c) = 0;
  *(undefined4 *)(param_1 + 0x84) = 0;
  *(undefined4 *)(param_1 + 0x88) = 0;
  *(undefined4 *)(param_1 + 0x8c) = 0;
  *(undefined4 *)(param_1 + 0x94) = 0;
  *(undefined4 *)(param_1 + 0x98) = 0;
  *(undefined4 *)(param_1 + 0x9c) = 0;
  return;
}



/* function 005fc4c0 FUN_005fc4c0 */

void FUN_005fc4c0(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int *piVar13;
  char cVar14;
  int iVar15;
  int iVar16;
  undefined4 uVar17;
  int *unaff_EBX;
  int *piVar18;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  undefined4 *puVar19;
  bool in_ZF;
  
  if (in_ZF) {
    cVar14 = FUN_005f7760();
    if (cVar14 != '\0') {
      cVar14 = FUN_005f77a0();
      if (cVar14 != '\0') goto LAB_005fc4fe;
    }
    if ((int *)unaff_ESI[1] != unaff_EBX) {
      (*(code *)**(undefined4 **)unaff_ESI[1])(1);
    }
    unaff_ESI[1] = unaff_EBX;
    if ((int *)unaff_ESI[0xa5] != unaff_EBX) {
      (*(code *)**(undefined4 **)unaff_ESI[0xa5])(1);
    }
    unaff_ESI[0xa5] = unaff_EBX;
  }
LAB_005fc4fe:
  iVar15 = *(int *)(unaff_EDI + 4);
  iVar16 = unaff_ESI[3];
  if (iVar15 != iVar16) {
    unaff_ESI[3] = iVar15;
    unaff_ESI[0x2b] = *(undefined4 *)(unaff_EDI + 4);
    unaff_ESI[0x7b] = *(undefined4 *)(unaff_EDI + 4);
  }
  iVar7 = *(int *)(unaff_EDI + 8);
  iVar1 = unaff_ESI[8];
  if (iVar7 != iVar1) {
    unaff_ESI[8] = iVar7;
    unaff_ESI[0x30] = *(undefined4 *)(unaff_EDI + 8);
    unaff_ESI[0x80] = *(undefined4 *)(unaff_EDI + 8);
  }
  iVar8 = *(int *)(unaff_EDI + 0xc);
  iVar2 = unaff_ESI[0xd];
  if (iVar8 != iVar2) {
    unaff_ESI[0xd] = iVar8;
    unaff_ESI[0x35] = *(undefined4 *)(unaff_EDI + 0xc);
    unaff_ESI[0x85] = *(undefined4 *)(unaff_EDI + 0xc);
  }
  iVar9 = *(int *)(unaff_EDI + 0x10);
  iVar3 = unaff_ESI[0x12];
  if (iVar9 != iVar3) {
    unaff_ESI[0x12] = iVar9;
    unaff_ESI[0x3a] = *(undefined4 *)(unaff_EDI + 0x10);
    unaff_ESI[0x8a] = *(undefined4 *)(unaff_EDI + 0x10);
  }
  iVar10 = *(int *)(unaff_EDI + 0x14);
  iVar4 = unaff_ESI[0x17];
  if (iVar10 != iVar4) {
    unaff_ESI[0x17] = iVar10;
    unaff_ESI[0x3f] = *(undefined4 *)(unaff_EDI + 0x14);
    unaff_ESI[0x8f] = *(undefined4 *)(unaff_EDI + 0x14);
  }
  iVar11 = *(int *)(unaff_EDI + 0x18);
  iVar5 = unaff_ESI[0x1c];
  if (iVar11 != iVar5) {
    unaff_ESI[0x1c] = iVar11;
    unaff_ESI[0x44] = *(undefined4 *)(unaff_EDI + 0x18);
    unaff_ESI[0x94] = *(undefined4 *)(unaff_EDI + 0x18);
  }
  iVar12 = *(int *)(unaff_EDI + 0x1c);
  iVar6 = unaff_ESI[0x21];
  if (iVar12 != iVar6) {
    unaff_ESI[0x21] = iVar12;
    unaff_ESI[0x49] = *(undefined4 *)(unaff_EDI + 0x1c);
    unaff_ESI[0x99] = *(undefined4 *)(unaff_EDI + 0x1c);
  }
  if (*(int *)(unaff_EDI + 0x20) == unaff_ESI[0x26]) {
    if ((iVar12 != iVar6 ||
        (iVar11 != iVar5 ||
        (iVar10 != iVar4 ||
        (iVar9 != iVar3 || (iVar8 != iVar2 || (iVar7 != iVar1 || iVar15 != iVar16)))))) !=
        (bool)(char)unaff_EBX) goto LAB_005fc60e;
  }
  else {
    unaff_ESI[0x26] = *(int *)(unaff_EDI + 0x20);
    unaff_ESI[0x4e] = *(undefined4 *)(unaff_EDI + 0x20);
    unaff_ESI[0x9e] = *(undefined4 *)(unaff_EDI + 0x20);
LAB_005fc60e:
    if ((int *)unaff_ESI[0xa4] == unaff_EBX) {
      puVar19 = unaff_ESI + 0x7c;
      iVar15 = 8;
      do {
        if ((int *)*puVar19 != unaff_EBX) {
          (*(code *)**(undefined4 **)*puVar19)(1);
        }
        *puVar19 = unaff_EBX;
        puVar19 = puVar19 + 5;
        iVar15 = iVar15 + -1;
      } while (iVar15 != 0);
      (*(code *)**(undefined4 **)unaff_ESI[0xa3])(*unaff_ESI);
      FUN_005f7800();
      if ((int *)unaff_ESI[1] != unaff_EBX) {
        if ((int *)unaff_ESI[0xa5] == unaff_EBX) {
          uVar17 = FUN_005fc440();
          unaff_ESI[0xa5] = uVar17;
        }
        else {
          puVar19 = unaff_ESI + 4;
          iVar15 = 8;
          do {
            if ((int *)*puVar19 != unaff_EBX) {
              (*(code *)**(undefined4 **)*puVar19)(1);
            }
            *puVar19 = unaff_EBX;
            puVar19 = puVar19 + 5;
            iVar15 = iVar15 + -1;
          } while (iVar15 != 0);
          (**(code **)(*(int *)unaff_ESI[0xa5] + 4))();
        }
      }
    }
    else {
      (**(code **)(*(int *)unaff_ESI[0xa4] + 4))();
    }
  }
  piVar18 = (int *)0x0;
  if ((int *)unaff_ESI[2] == unaff_EBX) goto LAB_005fc768;
  if ((int *)unaff_ESI[1] == unaff_EBX) {
LAB_005fc72f:
    if ((int *)unaff_ESI[1] != unaff_EBX) {
      (*(code *)**(undefined4 **)unaff_ESI[1])(1);
    }
    unaff_ESI[1] = unaff_ESI[2];
    unaff_ESI[2] = unaff_EBX;
    if ((int *)unaff_ESI[0xa5] != unaff_EBX) {
      (*(code *)**(undefined4 **)unaff_ESI[0xa5])(1);
    }
    unaff_ESI[0xa5] = unaff_EBX;
    uVar17 = FUN_005fc440();
    unaff_ESI[0xa5] = uVar17;
  }
  else {
    piVar13 = (int *)((int *)unaff_ESI[1])[4];
    iVar15 = (**(code **)(*(int *)((int *)unaff_ESI[2])[4] + 4))();
    iVar16 = (**(code **)(*piVar13 + 4))();
    if (iVar15 == iVar16) {
      cVar14 = (**(code **)(**(int **)(unaff_ESI[2] + 0x10) + 0x3c))();
      if (cVar14 != '\0') goto LAB_005fc6e0;
    }
    else {
LAB_005fc6e0:
      cVar14 = FUN_004ae100(unaff_ESI[1]);
      if (cVar14 != '\0') goto LAB_005fc72f;
    }
    piVar13 = *(int **)(unaff_ESI[2] + 0x10);
    iVar15 = (**(code **)(**(int **)(unaff_ESI[1] + 0x10) + 4))();
    iVar16 = (**(code **)(*piVar13 + 4))();
    if (iVar16 == iVar15) {
      cVar14 = (**(code **)(**(int **)(unaff_ESI[2] + 0x10) + 0x3c))();
      if (cVar14 != '\0') {
        piVar18 = (int *)(**(code **)(*(int *)unaff_ESI[2] + 0x10))();
      }
    }
  }
LAB_005fc768:
  if ((int *)unaff_ESI[0xa4] != unaff_EBX) {
    iVar15 = (**(code **)(*(int *)unaff_ESI[0xa4] + 8))();
    if (iVar15 == 0) {
      if ((int *)unaff_ESI[0xa4] != unaff_EBX) {
        (*(code *)**(undefined4 **)unaff_ESI[0xa4])(1);
      }
      unaff_ESI[0xa4] = unaff_EBX;
    }
  }
  piVar13 = (int *)unaff_ESI[2];
  if ((piVar13 != unaff_EBX) && ((int *)unaff_ESI[1] != piVar13)) {
    (**(code **)*piVar13)(1);
    unaff_ESI[2] = unaff_EBX;
  }
  if ((((int *)unaff_ESI[0xa4] == unaff_EBX) && ((int *)unaff_ESI[1] != unaff_EBX)) &&
     ((int *)unaff_ESI[0xa5] != unaff_EBX)) {
    (**(code **)(*(int *)unaff_ESI[0xa5] + 8))();
  }
  if (piVar18 != unaff_EBX) {
    FUN_005f7470(piVar18);
    (**(code **)*piVar18)(1);
  }
  return;
}



/* function 00601da0 FUN_00601da0 */

void __fastcall FUN_00601da0(int param_1)

{
  FUN_00681850();
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x58) = 0;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 100) = 0;
  FUN_004bc550();
  FUN_004ab370(0);
  FUN_005ff9d0();
  FUN_005ff9d0();
  FUN_005fff90();
  return;
}



/* function 0063c340 FUN_0063c340 */

undefined4 * __thiscall
FUN_0063c340(undefined4 *param_1,undefined4 param_2,int param_3,byte param_4)

{
  void *pvVar1;
  undefined4 uVar2;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00841823;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_0061a390();
  param_1[2] = param_2;
  *param_1 = &PTR_FUN_0086e904;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  *(undefined1 *)(param_1 + 7) = 0;
  *(undefined1 *)((int)param_1 + 0x1d) = 0;
  param_1[0x13] = 0;
  param_1[0x14] = 0;
  param_1[0x15] = 0;
  *(undefined1 *)(param_1 + 0x16) = 0;
  *(undefined1 *)((int)param_1 + 0x59) = 0;
  *(byte *)(param_1 + 0x17) = (param_4 & 1 | 2) << 2 | *(byte *)(param_1 + 0x17) & 0xcb;
  local_4 = 0;
  if (param_1[2] != 0) {
    FUN_00571b70(param_1 + 2);
  }
  if (param_3 != 0) {
    pvVar1 = operator_new(0x1c);
    local_4 = CONCAT31(local_4._1_3_,1);
    if (pvVar1 == (void *)0x0) {
      uVar2 = 0;
    }
    else {
      local_18 = 0;
      local_14 = 0;
      local_10 = 0;
      uVar2 = FUN_0064fbb0(&local_18,0,*(undefined4 *)(param_3 + 0x14),
                           *(undefined4 *)(param_3 + 0x18));
    }
    param_1[4] = uVar2;
  }
  *(byte *)(param_1 + 0x17) = *(byte *)(param_1 + 0x17) & 0xfc;
  param_1[0x11] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  param_1[8] = 0xffffffff;
  ExceptionList = local_c;
  return param_1;
}



/* function 007ac82a FUN_007ac82a */

void FUN_007ac82a(undefined4 *param_1)

{
  byte bVar1;
  byte extraout_AH;
  
  bVar1 = FUN_007ac746();
  if (((bVar1 & 0x20) != 0) && ((char)bVar1 < '\0')) {
    *param_1 = FUN_007c203b;
    param_1[1] = FUN_007c0e87;
    param_1[2] = &LAB_007c22fc;
    param_1[3] = &LAB_007bccf9;
    param_1[5] = FUN_007c2090;
    param_1[6] = FUN_007c0ef8;
    param_1[7] = FUN_007c0f5f;
    param_1[8] = &LAB_007c237e;
    param_1[9] = FUN_007c20c9;
    param_1[10] = thunk_FUN_007c15ea;
    param_1[0xb] = &LAB_007bcf2b;
    param_1[0xc] = &LAB_007c2726;
    param_1[0xd] = &LAB_007c2769;
    param_1[0xe] = FUN_007c1841;
    param_1[0xf] = FUN_007c19c9;
    param_1[0x10] = &LAB_007c23dd;
    param_1[0x11] = &LAB_007c212d;
    param_1[0x12] = &LAB_007c0e6b;
    param_1[0x13] = &LAB_007bb77c;
    param_1[0x14] = &LAB_007bb815;
    param_1[0x15] = FUN_007c290b;
    param_1[0x16] = &LAB_007c284d;
    param_1[0x17] = FUN_007bb872;
    param_1[0x18] = &LAB_007bb8b6;
    param_1[0x19] = &LAB_007bbce7;
    param_1[0x1a] = &LAB_007bcffa;
    param_1[0x1b] = &LAB_007bd04a;
    param_1[0x1c] = &LAB_007bd135;
    param_1[0x1d] = FUN_007bbdac;
    param_1[0x1e] = &LAB_007bd211;
    param_1[0x1f] = &LAB_007bd274;
    param_1[0x20] = &LAB_007bd2d2;
    param_1[0x21] = &LAB_007bd32b;
    param_1[0x22] = &LAB_007c296f;
    param_1[0x23] = FUN_007bbe18;
    param_1[0x24] = FUN_007bbf4f;
    param_1[0x25] = &LAB_007bd372;
    param_1[0x26] = &LAB_007bd41a;
    param_1[0x27] = FUN_007bd5a1;
    param_1[0x28] = FUN_007be739;
    param_1[0x29] = &LAB_007be8de;
    param_1[0x2a] = FUN_007bee12;
    param_1[0x2b] = FUN_007bbfdc;
    param_1[0x2c] = &LAB_007bc06e;
    param_1[0x36] = &LAB_007c250f;
    param_1[0x33] = &LAB_007c0fbe;
    param_1[0x30] = &LAB_007c21c5;
    param_1[0x2e] = &LAB_007c220e;
    param_1[0x34] = &LAB_007c2580;
    param_1[0x31] = &LAB_007c102f;
    param_1[0x37] = FUN_007bc0d2;
    param_1[0x38] = &LAB_007bc179;
    param_1[0x35] = &LAB_007c2648;
    param_1[0x2f] = &LAB_007c2251;
    param_1[0x32] = &LAB_007c1103;
    param_1[4] = &LAB_007c073f;
    param_1[0x2d] = FUN_007bc2c0;
    param_1[0x3a] = FUN_007c1d80;
    param_1[0x39] = &LAB_007c1ec0;
    if (((extraout_AH & 1) != 0) && ((extraout_AH & 2) != 0)) {
      param_1[0xf] = FUN_007c1bef;
      param_1[0x12] = FUN_007c045d;
      param_1[0x26] = &LAB_007bd4ec;
      param_1[0x27] = FUN_007bf309;
      param_1[0x18] = &LAB_007bbad2;
    }
  }
  if ((bVar1 & 0x40) != 0) {
    param_1[0x3e] = FUN_007bb140;
    param_1[0x3f] = &LAB_007bb1e0;
    param_1[0x40] = &LAB_007bb500;
    param_1[0x3b] = &LAB_007baac0;
    param_1[0x3c] = &LAB_007bad20;
    param_1[0x3d] = &LAB_007baf80;
    param_1[0x41] = FUN_007baa00;
    param_1[0x44] = FUN_007ba940;
  }
  return;
}


