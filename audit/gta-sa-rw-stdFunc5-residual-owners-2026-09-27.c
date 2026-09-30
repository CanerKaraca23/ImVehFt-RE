/* Full-analysis function mapping; decompilation is not original source. */

/* function 004a4960 FUN_004a4960 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall
FUN_004a4960(int param_1,undefined4 param_2,float param_3,undefined4 param_4,undefined4 param_5,
            float *param_6)

{
  int *piVar1;
  int iVar2;
  
  *param_6 = param_3 * _DAT_0085862c;
  param_6[0xc] = 1.0;
  param_6[0xf] = 1.0;
  param_6[1] = 0.0;
  param_6[2] = 0.0;
  param_6[3] = 0.0;
  param_6[4] = 0.0;
  param_6[5] = 0.0;
  param_6[6] = 0.0;
  param_6[7] = 0.0;
  param_6[8] = 0.0;
  param_6[9] = 0.0;
  param_6[10] = 0.0;
  param_6[0xb] = 0.0;
  param_6[0xd] = 0.0;
  param_6[0xe] = 0.0;
  param_6[0x10] = 0.0;
  param_6[0x11] = 0.0;
  param_6[0x12] = 0.0;
  param_6[0x13] = 0.0;
  param_6[0x14] = 0.0;
  param_6[0x15] = 0.0;
  param_6[0x16] = 0.0;
  param_6[0x17] = 2.0;
  param_6[0x18] = 0.0;
  param_6[0x19] = 2.0;
  iVar2 = 0;
  if ('\0' < *(char *)(param_1 + 8)) {
    do {
      piVar1 = *(int **)(*(int *)(param_1 + 4) + iVar2 * 4);
      if ((*(byte *)((int)piVar1 + 5) & 0x10) != 0) {
        (**(code **)(*piVar1 + 8))(param_2,0,param_3,param_4,param_5,param_6);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < *(char *)(param_1 + 8));
  }
  return;
}



/* function 004d7890 FUN_004d7890 */

void __thiscall
FUN_004d7890(undefined4 *param_1,undefined4 param_2,undefined2 param_3,int param_4,ushort param_5)

{
  *(ushort *)((int)param_1 + 0x55) = param_5;
  param_1[1] = param_2;
  *(undefined2 *)((int)param_1 + 0x3a) = param_3;
  *(uint *)((int)param_1 + 0x4f) = (uint)(param_5 >> 3) * param_4;
  *param_1 = &PTR_FUN_0085f03c;
  param_1[10] = 0;
  param_1[0x17] = 0;
  param_1[0xf] = param_4;
  *(undefined2 *)((int)param_1 + 0x57) = 0;
  *(undefined2 *)((int)param_1 + 0x53) = 2;
  *(undefined2 *)((int)param_1 + 0x49) = 1;
  *(int *)((int)param_1 + 0x4b) = param_4;
  param_1[0x10] = param_4;
  *(undefined2 *)((int)param_1 + 0x47) = 1;
  param_1[0xd] = 0xc2c80000;
  param_1[2] = 0;
  param_1[3] = 0;
  *(undefined1 *)(param_1 + 0xe) = 0;
  *(undefined1 *)(param_1 + 0x11) = 0;
  *(undefined1 *)((int)param_1 + 0x45) = 0;
  return;
}



/* function 004ef2e0 FUN_004ef2e0 */

void __thiscall FUN_004ef2e0(int param_1,short param_2,short param_3)

{
  short sVar1;
  
  *(short *)(param_1 + 0x70) = param_2;
  if (*(short *)(param_1 + 0x5e) == 0) {
    if (*(short *)(param_1 + 0x68) != 0) {
LAB_004ef2fb:
      *(undefined2 *)(param_1 + 0x5c) = 0xffff;
      return;
    }
    sVar1 = FUN_00821b40();
    *(short *)(param_1 + 0x5c) = sVar1;
    if (param_2 <= sVar1) {
      if (param_3 == -1) goto LAB_004ef2fb;
      *(short *)(param_1 + 0x5c) = sVar1 % param_2 + param_3;
    }
  }
  return;
}



/* function 004effd0 FUN_004effd0 */

void __fastcall FUN_004effd0(int param_1)

{
  FUN_004eff50(0xffffffff);
  *(undefined2 *)(param_1 + 0x58) = 0;
  if (*(int *)(param_1 + 8) != 0) {
    FUN_00571a00((undefined4 *)(param_1 + 8));
    *(undefined4 *)(param_1 + 8) = 0;
  }
  *(undefined2 *)(param_1 + 0x5e) = 0;
  *(undefined2 *)(param_1 + 0x5c) = 0;
  return;
}



/* function 00517bf0 FUN_00517bf0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00517bf0(int *param_1,float param_2)

{
  int iVar1;
  float fVar2;
  undefined4 uVar3;
  char cVar4;
  int iVar5;
  float fVar6;
  bool bVar7;
  float10 fVar8;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  fVar2 = (float)DAT_00b7cb84;
  if (DAT_00b7cb84 < 0) {
    fVar2 = fVar2 + _DAT_00858c54;
  }
  local_10 = (float)param_1[0x1a];
  bVar7 = false;
  iVar5 = 0;
  if (*param_1 != 0) {
    FUN_0050eae0(*param_1,&local_c);
    iVar1 = param_1[0x26];
    local_c = *(float *)(iVar1 + 0x19c) - local_c;
    iVar5 = *param_1;
    local_8 = *(float *)(iVar1 + 0x1a0) - local_8;
    local_4 = *(float *)(iVar1 + 0x1a4) - local_4;
    fVar6 = SQRT(local_c * local_c + local_8 * local_8 + local_4 * local_4);
    bVar7 = false;
    if (((*(byte *)(iVar5 + 0x36) & 7) == 3) &&
       ((*(int *)(iVar5 + 0x598) == 0x16 || (*(int *)(iVar5 + 0x598) == 5)))) {
      bVar7 = true;
      local_10 = local_10 * _DAT_00858b8c;
      if (fVar6 < _DAT_00859000) {
        *(undefined1 *)(param_1 + 0x1e) = 1;
      }
    }
    if ((float)param_1[0x12] < fVar6) {
      bVar7 = true;
    }
  }
  uVar3 = DAT_00b7cd68;
  if (_DAT_00858624 <= param_2) {
    iVar1 = param_1[0x16];
    if (bVar7) {
      if ((float)param_1[0x1f] < fVar2 - (float)param_1[0x20]) {
        cVar4 = '\x01';
        if (iVar5 != 0) {
          DAT_00b7cd68 = iVar5;
          FUN_0050eae0(*param_1,&local_c);
          cVar4 = FUN_0056a490(param_1[0x26] + 0x19c,&local_c,1,0,0,1,0,0,1);
        }
        DAT_00b7cd68 = uVar3;
        if ((10 < param_1[0x15]) && (param_1[0x16] == 2)) {
          param_1[0x16] = 1;
        }
        if (((param_1[0x16] == 3) && (*(char *)((int)param_1 + 0x79) == '\0')) && (cVar4 != '\0')) {
          param_1[0x16] = 0;
          bVar7 = iVar1 == 0;
          fVar6 = local_10;
          goto LAB_00517d81;
        }
      }
    }
    else if (iVar1 == 2) {
      fVar6 = (float)param_1[0x1b];
      param_1[0x16] = 1;
      bVar7 = false;
LAB_00517d81:
      param_1[0x18] = (int)fVar6;
      if (!bVar7) {
        param_1[0x19] = (int)fVar2;
        param_1[0x17] = param_1[0x1c];
      }
    }
  }
  if (param_1[0x16] == 2) {
    param_1[0x20] = (int)fVar2;
  }
  if (((char)param_1[0x1e] != '\0') && (param_1[0x16] == 2)) {
    param_1[0x19] = (int)fVar2;
    param_1[0x17] = param_1[0x1c];
    param_1[0x16] = 1;
    param_1[0x18] = param_1[0x1b];
  }
  *(undefined1 *)(param_1 + 0x1e) = 0;
  switch(param_1[0x16]) {
  case 0:
    if (_DAT_00858624 <= ABS((float)param_1[0x1c] - local_10)) goto LAB_00517e2e;
    param_1[0x16] = 2;
    *(undefined1 *)((int)param_1 + 0x79) = 1;
    goto LAB_00517e74;
  case 1:
    if (ABS((float)param_1[0x1c] - (float)param_1[0x1b]) < _DAT_00858624) {
      param_1[0x16] = 3;
      param_1[0x1c] = param_1[0x1b];
      break;
    }
LAB_00517e2e:
    fVar8 = (float10)fsin(((float10)_DAT_00859070 -
                          (((float10)fVar2 - (float10)(float)param_1[0x19]) /
                          (float10)(float)param_1[0x1d]) * (float10)_DAT_0085a994) *
                          (float10)_DAT_008595ec);
    param_1[0x1c] =
         (int)(float)(((float10)(float)param_1[0x18] - (float10)(float)param_1[0x17]) *
                      (fVar8 + (float10)_DAT_00858624) * (float10)_DAT_00858b8c +
                     (float10)(float)param_1[0x17]);
    break;
  case 2:
    param_1[0x1c] = (int)local_10;
    break;
  case 3:
    local_10 = (float)param_1[0x1b];
LAB_00517e74:
    param_1[0x1c] = (int)local_10;
  }
  *(int *)(param_1[0x26] + 0xb4) = param_1[0x1c];
  return;
}



/* function 00538bc0 FUN_00538bc0 */

void __fastcall FUN_00538bc0(int param_1)

{
  undefined4 *puVar1;
  int local_14;
  
  puVar1 = (undefined4 *)(param_1 + 0x2c);
  local_14 = 6;
  do {
    puVar1[-10] = 0;
    puVar1[-9] = 0;
    puVar1[-8] = 0;
    *(byte *)(puVar1 + -0xb) = *(byte *)(puVar1 + -0xb) & 0xf4 | 0x14;
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[2] = 0;
    *(byte *)(puVar1 + -1) = *(byte *)(puVar1 + -1) & 0xf4 | 0x14;
    puVar1[10] = 0;
    puVar1[0xb] = 0;
    puVar1[0xc] = 0;
    *(byte *)(puVar1 + 9) = *(byte *)(puVar1 + 9) & 0xf4 | 0x14;
    puVar1[0x14] = 0;
    puVar1[0x15] = 0;
    puVar1[0x16] = 0;
    *(byte *)(puVar1 + 0x13) = *(byte *)(puVar1 + 0x13) & 0xf4 | 0x14;
    puVar1[0x1e] = 0;
    puVar1[0x1f] = 0;
    *(undefined2 *)((int)puVar1 + -0x2a) = 1;
    puVar1[0x20] = 0;
    puVar1[-5] = 0;
    puVar1[-7] = 0;
    puVar1[-6] = 0;
    puVar1[-4] = 0x3f800000;
    puVar1[-2] = 0;
    *(undefined1 *)(puVar1 + -3) = 100;
    *(undefined1 *)((int)puVar1 + -0xb) = 0x3c;
    *(undefined2 *)((int)puVar1 + -2) = 1;
    puVar1[5] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    puVar1[6] = 0x3f800000;
    puVar1[8] = 0;
    *(undefined1 *)(puVar1 + 7) = 100;
    *(undefined1 *)((int)puVar1 + 0x1d) = 0x3c;
    *(undefined2 *)((int)puVar1 + 0x26) = 1;
    puVar1[0xf] = 0;
    puVar1[0xd] = 0;
    puVar1[0xe] = 0;
    puVar1[0x10] = 0x3f800000;
    puVar1[0x12] = 0;
    *(undefined1 *)(puVar1 + 0x11) = 100;
    *(undefined1 *)((int)puVar1 + 0x45) = 0x3c;
    *(undefined2 *)((int)puVar1 + 0x4e) = 1;
    puVar1[0x19] = 0;
    puVar1[0x17] = 0;
    puVar1[0x18] = 0;
    puVar1[0x1a] = 0x3f800000;
    puVar1[0x1c] = 0;
    *(undefined1 *)(puVar1 + 0x1b) = 100;
    *(undefined1 *)((int)puVar1 + 0x6d) = 0x3c;
    *(undefined2 *)((int)puVar1 + 0x76) = 1;
    puVar1[0x23] = 0;
    puVar1[0x21] = 0;
    puVar1[0x22] = 0;
    puVar1[0x24] = 0x3f800000;
    *(byte *)(puVar1 + 0x1d) = *(byte *)(puVar1 + 0x1d) & 0xf4 | 0x14;
    puVar1[0x26] = 0;
    *(undefined1 *)(puVar1 + 0x25) = 100;
    *(undefined1 *)((int)puVar1 + 0x95) = 0x3c;
    *(undefined2 *)((int)puVar1 + 0x9e) = 1;
    puVar1[0x28] = 0;
    puVar1[0x29] = 0;
    puVar1[0x2a] = 0;
    *(byte *)(puVar1 + 0x27) = *(byte *)(puVar1 + 0x27) & 0xf4 | 0x14;
    puVar1[0x32] = 0;
    puVar1[0x33] = 0;
    puVar1[0x34] = 0;
    *(byte *)(puVar1 + 0x31) = *(byte *)(puVar1 + 0x31) & 0xf4 | 0x14;
    puVar1[0x3c] = 0;
    puVar1[0x3d] = 0;
    puVar1[0x3e] = 0;
    *(byte *)(puVar1 + 0x3b) = *(byte *)(puVar1 + 0x3b) & 0xf4 | 0x14;
    puVar1[0x46] = 0;
    puVar1[0x47] = 0;
    puVar1[0x48] = 0;
    *(byte *)(puVar1 + 0x45) = *(byte *)(puVar1 + 0x45) & 0xf4 | 0x14;
    puVar1[0x50] = 0;
    puVar1[0x51] = 0;
    puVar1[0x52] = 0;
    puVar1[0x2d] = 0;
    puVar1[0x2b] = 0;
    puVar1[0x2c] = 0;
    puVar1[0x2e] = 0x3f800000;
    puVar1[0x30] = 0;
    *(undefined1 *)(puVar1 + 0x2f) = 100;
    *(undefined1 *)((int)puVar1 + 0xbd) = 0x3c;
    *(undefined2 *)((int)puVar1 + 0xc6) = 1;
    puVar1[0x37] = 0;
    puVar1[0x35] = 0;
    puVar1[0x36] = 0;
    puVar1[0x38] = 0x3f800000;
    puVar1[0x3a] = 0;
    *(undefined1 *)(puVar1 + 0x39) = 100;
    *(undefined1 *)((int)puVar1 + 0xe5) = 0x3c;
    *(undefined2 *)((int)puVar1 + 0xee) = 1;
    puVar1[0x41] = 0;
    puVar1[0x3f] = 0;
    puVar1[0x40] = 0;
    puVar1[0x42] = 0x3f800000;
    puVar1[0x44] = 0;
    *(undefined1 *)(puVar1 + 0x43) = 100;
    *(undefined1 *)((int)puVar1 + 0x10d) = 0x3c;
    *(undefined2 *)((int)puVar1 + 0x116) = 1;
    puVar1[0x4b] = 0;
    puVar1[0x49] = 0;
    puVar1[0x4a] = 0;
    puVar1[0x4c] = 0x3f800000;
    puVar1[0x4e] = 0;
    *(undefined1 *)(puVar1 + 0x4d) = 100;
    *(undefined1 *)((int)puVar1 + 0x135) = 0x3c;
    *(byte *)(puVar1 + 0x4f) = *(byte *)(puVar1 + 0x4f) & 0xf4 | 0x14;
    *(undefined2 *)((int)puVar1 + 0x13e) = 1;
    puVar1[0x55] = 0;
    puVar1[0x53] = 0;
    puVar1[0x54] = 0;
    puVar1[0x56] = 0x3f800000;
    puVar1[0x58] = 0;
    *(undefined1 *)(puVar1 + 0x57) = 100;
    *(undefined1 *)((int)puVar1 + 0x15d) = 0x3c;
    puVar1 = puVar1 + 100;
    local_14 = local_14 + -1;
  } while (local_14 != 0);
  *(undefined4 *)(param_1 + 0x960) = 999999;
  return;
}



/* function 005483d0 FUN_005483d0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_005483d0(int param_1)

{
  float *pfVar1;
  float10 fVar2;
  float local_2c;
  float local_28;
  float local_24;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  if (*(char *)(param_1 + 0x40) < '\0') {
    local_24 = *(float *)(*(int *)((&DAT_00a9b0c8)[*(short *)(param_1 + 0x22)] + 0x14) + 0x24);
    local_28 = DAT_00858b50 * local_24;
    if (*(int *)(param_1 + 0x14) == 0) {
      pfVar1 = (float *)(param_1 + 4);
    }
    else {
      pfVar1 = (float *)(*(int *)(param_1 + 0x14) + 0x30);
    }
    local_2c = *pfVar1 - local_28;
    local_28 = pfVar1[1] - local_28;
    local_24 = pfVar1[2] - local_24;
    local_1c = 0;
    local_18 = 0;
    local_14 = 0x3f800000;
    FUN_005454c0(DAT_00b7cb5c * _DAT_00863b5c,&local_2c);
    fVar2 = (float10)FUN_00822130();
    *(float *)(param_1 + 0x58) = (float)(fVar2 * (float10)*(float *)(param_1 + 0x58));
  }
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x5c) + *(float *)(param_1 + 0x44);
  *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x60) + *(float *)(param_1 + 0x48);
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 100) + *(float *)(param_1 + 0x4c);
  *(float *)(param_1 + 0x50) = *(float *)(param_1 + 0x68) + *(float *)(param_1 + 0x50);
  *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x6c) + *(float *)(param_1 + 0x54);
  *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x70) + *(float *)(param_1 + 0x58);
  *(undefined4 *)(param_1 + 0x5c) = 0;
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 0x68) = 0;
  *(undefined4 *)(param_1 + 100) = 0;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0;
  if (((((*(byte *)(param_1 + 0x36) & 7) == 2) && (*(int *)(param_1 + 0x590) == 9)) &&
      (-1 < *(int *)(param_1 + 0x40))) &&
     (((*(byte *)(param_1 + 0x36) & 0xf8) == 0x20 &&
      (ABS(*(float *)(*(int *)(param_1 + 0x14) + 0x28)) < _DAT_00863c1c)))) {
    fVar2 = (float10)FUN_00406da0();
    if (fVar2 < (float10)_DAT_008cd7f4 * (float10)_DAT_008cd7f4) {
      fVar2 = (float10)FUN_00406da0();
      if (fVar2 < (float10)_DAT_008cd7f0 * (float10)_DAT_008cd7f0) {
        fVar2 = (float10)FUN_00822130();
        FUN_0040fef0((float)fVar2);
      }
    }
  }
  return;
}



/* function 00574350 FUN_00574350 */

undefined1 * __fastcall FUN_00574350(undefined1 *param_1)

{
  undefined1 uVar1;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0083ce18;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  _eh_vector_constructor_iterator_
            (param_1 + 0xf8,4,0x19,(_func_void_void_ptr *)&LAB_00727230,FUN_007281e0);
  local_4 = 0;
  param_1[0xea] = 0;
  param_1[0x1ade] = 0;
  param_1[0x1b0b] = 0;
  param_1[0x1b0a] = 0;
  *(undefined4 *)(param_1 + 0xdc) = 0;
  FUN_00573ae0(0x1b);
  FUN_00573ae0(0x24);
  *(undefined4 *)(param_1 + 0xec) = 0;
  *(undefined4 *)(param_1 + 0xf0) = 0;
  param_1[0x1ae8] = 0;
  *(undefined4 *)(param_1 + 0x7c) = 9;
  *(undefined4 *)(param_1 + 0xac) = 0;
  param_1[0xd0] = 0;
  DAT_00b6ec2e = 1;
  *(undefined4 *)(param_1 + 0xbc) = *(undefined4 *)(param_1 + 0xe0);
  *(undefined4 *)(param_1 + 0x90) = 0;
  param_1[0xe9] = 1;
  *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(param_1 + 0xe4);
  *(undefined4 *)(param_1 + 0x1af8) = 0;
  *(undefined4 *)(param_1 + 0x1afc) = 0;
  param_1[0xb8] = 0;
  *(undefined4 *)(param_1 + 0x1b00) = 0x10;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  param_1[0x34] = 0;
  FUN_00573ae0(3);
  FUN_00573ae0(4);
  uVar1 = FUN_004d9c10(1,0xd);
  param_1[0x52] = uVar1;
  param_1[0x5a] = 0;
  param_1[0x5b] = 0;
  param_1[0xeb] = 0;
  param_1[0x84] = 0;
  *(undefined4 *)(param_1 + 0x80) = 0;
  param_1[0x85] = 0;
  *(undefined4 *)(param_1 + 0x88) = 0;
  param_1[0x31] = 0;
  param_1[0x32] = 0;
  param_1[0x33] = 0;
  param_1[0x5c] = 0;
  param_1[0x5f] = 0;
  param_1[0x60] = 0;
  param_1[0xf4] = 0;
  *(undefined4 *)(param_1 + 4) = 0x43160000;
  *param_1 = 1;
  *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
  param_1[0x20] = 1;
  *(undefined4 *)(param_1 + 100) = 0x43960000;
  *(undefined4 *)(param_1 + 0x68) = 0x43a00000;
  *(undefined4 *)(param_1 + 0x6c) = 0x43600000;
  ExceptionList = local_c;
  return param_1;
}



/* function 005b9390 FUN_005b9390 */

undefined4 __thiscall FUN_005b9390(undefined1 *param_1,undefined4 *param_2)

{
  undefined1 uVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *local_c;
  undefined4 *local_8;
  undefined1 *local_4;
  
  *(undefined4 **)(param_1 + 100) = param_2;
  *(undefined4 *)(param_1 + 0x68) = 7;
  *param_1 = 0;
  param_1[1] = 0;
  puVar2 = (undefined4 *)FUN_00558f90();
  puVar6 = (undefined4 *)(param_1 + 0x18);
  for (iVar4 = 0xe; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar6 = puVar6 + 1;
  }
  local_4 = param_1 + 8;
  local_8 = &DAT_00b61d78;
  local_c = &DAT_00b620c0;
  param_2 = &DAT_00b62980;
  puVar6 = &DAT_00b62b40;
  puVar2 = (undefined4 *)(param_1 + 0x110);
  do {
    *puVar6 = 0xffffffff;
    puVar6[1] = 0xffffffff;
    puVar6[2] = 0xffffffff;
    puVar6[3] = 0xffffffff;
    puVar6[4] = 0xffffffff;
    puVar5 = param_2;
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
    param_2 = param_2 + 8;
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
  param_1[0xb9] = 6;
  param_1[0xc0] = 0xff;
  param_1[0xba] = 6;
  param_1[0xc1] = 0xff;
  *(undefined4 *)(param_1 + 0xa4) = 0;
  *(undefined4 *)(param_1 + 0xa8) = 0;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0;
  *(undefined4 *)(param_1 + 0x50) = 0;
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x58) = 0;
  param_1[0x16] = 0xff;
  param_1[0x17] = 0xff;
  param_1[2] = 0;
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  param_1[3] = 0;
  param_1[7] = 1;
  param_1[4] = 1;
  *(undefined4 *)(param_1 + 0x74) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x78) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x7c) = 0xffffffff;
  puVar2 = (undefined4 *)(param_1 + 0x88);
  puVar6 = (undefined4 *)(param_1 + 0xc4);
  for (iVar4 = 0xf; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar6 = puVar6 + 1;
  }
  DAT_00b62c73 = 3;
  DAT_00b62c72 = 0xff;
  param_1[5] = 0;
  param_1[6] = 0;
  *(undefined4 *)(param_1 + 0x80) = 0;
  *(undefined4 *)(param_1 + 0x84) = 0;
  DAT_00b62c71 = 0;
  DAT_00b62c5a = 0xff;
  DAT_00b62c59 = 0xff;
  DAT_00b62c58 = 0xff;
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
  *(undefined4 *)(param_1 + 0x368) = 0;
  uVar1 = FUN_004f3330();
  param_1[0x36c] = uVar1;
  return 1;
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



/* function 005bf750 FUN_005bf750 */

void FUN_005bf750(void)

{
  undefined4 *puVar1;
  
  puVar1 = &DAT_00c8aabc;
  do {
    puVar1[8] = 0;
    puVar1[9] = 0;
    puVar1[10] = 0;
    puVar1[-1] = 0;
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[2] = 0xffffffff;
    puVar1[3] = 0xffffffff;
    puVar1[4] = 0xffffffff;
    puVar1[6] = 0;
    *(undefined2 *)(puVar1 + 7) = 0;
    *(undefined2 *)((int)puVar1 + 0x1e) = 0;
    puVar1[0xb] = 1;
    puVar1[0xc] = 0;
    puVar1[0xd] = 0x3f800000;
    puVar1[0xe] = 0x3f800000;
    puVar1[0xf] = 0;
    puVar1[0x10] = 0;
    puVar1[0x11] = 0;
    puVar1[0x12] = 0;
    puVar1[0x13] = 0;
    puVar1[0x14] = 0;
    puVar1[0x15] = 0;
    puVar1[0x16] = 0;
    puVar1[0x17] = 0;
    puVar1[0x18] = 0;
    puVar1[0x19] = 0;
    *(undefined2 *)(puVar1 + 0x1a) = 0;
    puVar1[5] = 0;
    *(undefined1 *)((int)puVar1 + 0x6a) = 4;
    *(undefined1 *)((int)puVar1 + 0x6b) = 1;
    puVar1 = puVar1 + 0x1c;
  } while ((int)puVar1 < 0xc8cdbc);
  puVar1 = &DAT_00c8a8ac;
  do {
    puVar1[-1] = 0;
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[2] = 0;
    *(undefined2 *)(puVar1 + 3) = 0;
    *(undefined2 *)((int)puVar1 + 0xe) = 0;
    *(undefined2 *)(puVar1 + 4) = 0;
    *(undefined2 *)((int)puVar1 + 0x12) = 0;
    puVar1 = puVar1 + 6;
  } while ((int)puVar1 < 0xc8aaa4);
  FUN_005be670();
  return;
}



/* function 005cc7d0 FUN_005cc7d0 */

void FUN_005cc7d0(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  puVar1 = (undefined4 *)(*(code *)**(undefined4 **)(param_1 + 4))(param_1,0,0xa8);
  *(undefined4 **)(param_1 + 0x194) = puVar1;
  *puVar1 = &LAB_005cc7a0;
  puVar1[1] = &LAB_005cc290;
  puVar1[2] = FUN_005cc610;
  puVar1[6] = FUN_005cc050;
  puVar1[0x17] = 0;
  puVar2 = puVar1 + 0x18;
  iVar3 = 0x10;
  do {
    puVar2[-0x11] = FUN_005cc050;
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  puVar1[7] = &LAB_005cbf00;
  puVar1[0x15] = &LAB_005cbf00;
  iVar3 = *(int *)(param_1 + 0x194);
  *(undefined4 *)(param_1 + 0xc4) = 0;
  *(undefined4 *)(param_1 + 0x7c) = 0;
  *(undefined4 *)(param_1 + 0x17c) = 0;
  *(undefined1 *)(iVar3 + 0xc) = 0;
  *(undefined1 *)(iVar3 + 0xd) = 0;
  *(undefined4 *)(iVar3 + 0x14) = 0;
  *(undefined4 *)(iVar3 + 0xa0) = 0;
  return;
}



/* function 005cc8c0 FUN_005cc8c0 */

void FUN_005cc8c0(int *param_1)

{
  int iVar1;
  
  if (param_1[5] != 0xca) {
    *(undefined4 *)(*param_1 + 0x14) = 0x14;
    *(int *)(*param_1 + 0x18) = param_1[5];
    (**(code **)*param_1)(param_1);
  }
  param_1[0x17] = param_1[7];
  param_1[0x18] = param_1[8];
  switch(param_1[0xb]) {
  case 1:
    param_1[0x19] = 1;
    break;
  case 2:
  case 4:
  case 5:
    param_1[0x19] = 4;
    break;
  case 3:
    param_1[0x19] = 3;
    break;
  default:
    param_1[0x19] = param_1[9];
  }
  param_1[0x1b] = 1;
  iVar1 = 1;
  if (*(char *)((int)param_1 + 0x4a) == '\0') {
    iVar1 = param_1[0x19];
  }
  param_1[0x1a] = iVar1;
  return;
}



/* function 005d2330 FUN_005d2330 */

void __thiscall FUN_005d2330(int param_1,int param_2)

{
  FUN_0059bbc0(*(undefined4 *)(param_2 + 0x14));
  *(undefined1 *)(param_1 + 0x49) = *(undefined1 *)(param_2 + 0x434);
  *(undefined1 *)(param_1 + 0x4a) = *(undefined1 *)(param_2 + 0x435);
  *(undefined1 *)(param_1 + 0x4b) = *(undefined1 *)(param_2 + 0x436);
  *(undefined1 *)(param_1 + 0x4c) = *(undefined1 *)(param_2 + 0x437);
  *(undefined2 *)(param_1 + 0x4e) = *(undefined2 *)(param_2 + 0x45c);
  *(undefined1 *)(param_1 + 0x50) = *(undefined1 *)(param_2 + 0x488);
  *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(param_2 + 0x494);
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_2 + 0x49c);
  *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_2 + 0x4a0);
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_2 + 0x428);
  *(undefined4 *)(param_1 + 100) = *(undefined4 *)(param_2 + 0x42c);
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



/* function 0061a990 FUN_0061a990 */

undefined4 * __thiscall
FUN_0061a990(undefined4 *param_1,char *param_2,char *param_3,undefined4 param_4,undefined4 param_5,
            undefined4 param_6,byte param_7,byte param_8,byte param_9,byte param_10)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0083f128;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  FUN_0061a390();
  param_1[2] = 0;
  *(byte *)(param_1 + 3) = (param_10 & 1) << 2 | *(byte *)(param_1 + 3) & 0xf8;
  param_1[0xe] = param_5;
  param_1[0x10] = param_6;
  *param_1 = &PTR_FUN_0086d54c;
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  *(undefined1 *)(param_1 + 0x13) = 0;
  *(undefined1 *)((int)param_1 + 0x4d) = 0;
  param_1[0x14] = 0;
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  param_1[0x17] = param_4;
  *(byte *)(param_1 + 3) =
       (((param_9 & 1) << 1 | param_8 & 1) << 3 | param_7 & 1) << 1 | *(byte *)(param_1 + 3) & 0x8d;
  local_4 = 0;
  iVar3 = (int)(param_1 + 4) - (int)param_2;
  do {
    cVar1 = *param_2;
    param_2[iVar3] = cVar1;
    param_2 = param_2 + 1;
  } while (cVar1 != '\0');
  iVar3 = (int)(param_1 + 10) - (int)param_3;
  do {
    cVar1 = *param_3;
    param_3[iVar3] = cVar1;
    param_3 = param_3 + 1;
  } while (cVar1 != '\0');
  iVar3 = thunk_FUN_004017fa(param_1 + 10);
  if (iVar3 == 0) {
    param_1[0xf] = 0;
  }
  else {
    uVar2 = FUN_004d42f0(param_1 + 4,iVar3);
    param_1[0xf] = uVar2;
  }
  ExceptionList = pvStack_c;
  return param_1;
}



/* function 0061ac90 FUN_0061ac90 */

undefined4 * __thiscall
FUN_0061ac90(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7,byte param_8)

{
  FUN_0061a390();
  *(byte *)(param_1 + 3) = (param_8 & 1) << 2 | *(byte *)(param_1 + 3) & 0xf8;
  param_1[4] = param_2;
  param_1[5] = param_3;
  param_1[2] = 0;
  param_1[0x12] = param_4;
  *param_1 = &PTR_FUN_0086d594;
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  *(undefined1 *)(param_1 + 0x1a) = 0;
  *(undefined1 *)((int)param_1 + 0x69) = 0;
  param_1[0x13] = param_5;
  param_1[0x11] = 0;
  param_1[6] = 0;
  *(undefined2 *)(param_1 + 0x1b) = 0x1a8;
  param_1[0x14] = param_6;
  param_1[0x17] = param_7;
  return param_1;
}



/* function 0061ad10 FUN_0061ad10 */

undefined4 * __thiscall
FUN_0061ad10(undefined4 *param_1,char *param_2,char *param_3,undefined4 param_4,undefined4 param_5,
            undefined4 param_6,undefined4 param_7,undefined4 param_8,byte param_9)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0083f148;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  FUN_0061a390();
  param_1[2] = 0;
  *(byte *)(param_1 + 3) = (param_9 & 1) << 2 | *(byte *)(param_1 + 3) & 0xf8;
  param_1[6] = param_4;
  param_1[0x12] = param_5;
  *param_1 = &PTR_FUN_0086d594;
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  *(undefined1 *)(param_1 + 0x1a) = 0;
  *(undefined1 *)((int)param_1 + 0x69) = 0;
  param_1[0x14] = param_7;
  param_1[0x17] = param_8;
  local_4 = 0;
  *(undefined2 *)(param_1 + 0x1b) = 0x1a8;
  param_1[0x13] = param_6;
  iVar3 = (int)(param_1 + 7) - (int)param_2;
  do {
    cVar1 = *param_2;
    param_2[iVar3] = cVar1;
    param_2 = param_2 + 1;
  } while (cVar1 != '\0');
  iVar3 = (int)(param_1 + 0xd) - (int)param_3;
  do {
    cVar1 = *param_3;
    param_3[iVar3] = cVar1;
    param_3 = param_3 + 1;
  } while (cVar1 != '\0');
  uVar2 = thunk_FUN_004017fa(param_1 + 0xd);
  uVar2 = FUN_004d42f0(param_1 + 7,uVar2);
  param_1[0x11] = uVar2;
  param_1[4] = 0;
  param_1[5] = 0xbf;
  ExceptionList = pvStack_c;
  return param_1;
}



/* function 0061bb10 FUN_0061bb10 */

void __thiscall FUN_0061bb10(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (-1 < *(int *)(param_1 + 0x40)) {
    *(undefined4 *)(param_1 + 0x44) = DAT_00b7cb84;
    *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x40);
    *(undefined1 *)(param_1 + 0x4c) = 1;
  }
  if ((*(uint *)(param_1 + 0x5c) & 8) == 0) {
    *(uint *)(param_1 + 0x5c) = *(uint *)(param_1 + 0x5c) | 4;
  }
  uVar1 = FUN_004d4410(*(undefined4 *)(param_2 + 0x18),*(undefined4 *)(param_1 + 0x3c),
                       *(undefined4 *)(param_1 + 0x5c),*(undefined4 *)(param_1 + 0x38));
  *(undefined4 *)(param_1 + 8) = uVar1;
  if ((*(byte *)(param_1 + 0xc) & 0x20) != 0) {
    FUN_004cebe0(&LAB_0061aaa0,param_1);
    *(undefined2 *)(param_1 + 0x60) = *(undefined2 *)(*(int *)(param_1 + 8) + 0x2c);
    return;
  }
  if (((*(byte *)(param_1 + 0x5c) & 8) == 0) && ((*(byte *)(param_1 + 0xc) & 0x10) == 0)) {
    FUN_004cebc0(&LAB_0061a8a0,param_1);
    *(undefined2 *)(param_1 + 0x60) = *(undefined2 *)(*(int *)(param_1 + 8) + 0x2c);
    return;
  }
  FUN_004cebe0(&LAB_0061a8a0,param_1);
  *(undefined2 *)(param_1 + 0x60) = *(undefined2 *)(*(int *)(param_1 + 8) + 0x2c);
  return;
}



/* function 00621f50 FUN_00621f50 */

undefined4 * __thiscall
FUN_00621f50(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0083f7c8;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_0061a3b0();
  *param_1 = &PTR_FUN_0086d9c4;
  param_1[4] = param_2;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[0x16] = param_3;
  param_1[0x17] = param_4;
  local_4 = 0;
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  param_1[0x13] = 0;
  *(undefined1 *)(param_1 + 0x14) = 0;
  param_1[0x15] = 0xffffffff;
  param_1[0x18] = param_5;
  if (param_2 != 0) {
    FUN_00571b70(&param_2);
  }
  ExceptionList = local_c;
  return param_1;
}



/* function 006428c0 FUN_006428c0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_006428c0(int param_1,int param_2,byte param_3,float param_4)

{
  int iVar1;
  undefined4 uVar2;
  byte bVar3;
  float10 fVar4;
  float fVar5;
  float fVar6;
  float local_4;
  
  local_4 = 0.0;
  if (param_3 != 0) {
    if ((*(byte *)(param_1 + 0x5c) & 1) == 0) {
      if ((*(float *)(param_1 + 0x44) == DAT_00858b50) &&
         (iVar1 = FUN_00407180(0,1000), 0x3e3 < iVar1)) {
        if (*(int *)(param_1 + 0x20) == -1) {
          FUN_00642760(param_2);
          *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(param_1 + 0x20);
        }
        else {
          *(int *)(param_1 + 0x34) = DAT_00b7cb84;
        }
        uVar2 = FUN_00407180(1,3);
        *(undefined4 *)(param_1 + 0x38) = uVar2;
        fVar4 = (float10)FUN_0041bd90(0x40400000,0x41000000);
        *(float *)(param_1 + 0x40) = (float)fVar4;
        *(undefined4 *)(param_1 + 0x44) = 0;
        *(undefined4 *)(param_1 + 0x3c) = 0;
        local_4 = 0.0;
        goto LAB_0064299e;
      }
    }
    else {
      fVar4 = (float10)fsin((float10)*(float *)(param_1 + 0x2c) * (float10)_DAT_00858cb8);
      local_4 = (float)fVar4;
      if (((uint)(DAT_00b7cb84 - *(int *)(param_1 + 0x34)) < 0x1389) ||
         (iVar1 = FUN_00407180(0,1000), iVar1 < 0x3e4)) goto LAB_0064299e;
    }
    param_3 = 0;
  }
LAB_0064299e:
  bVar3 = *(byte *)(param_1 + 0x5c) ^ (*(byte *)(param_1 + 0x5c) ^ param_3) & 1;
  *(byte *)(param_1 + 0x5c) = bVar3;
  if ((bVar3 & 1) == 0) {
    if (DAT_00858b50 < *(float *)(param_1 + 0x44)) {
      *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) - _DAT_00858c28;
    }
    if (*(float *)(param_1 + 0x44) < DAT_00858b50) {
      *(undefined4 *)(param_1 + 0x44) = 0;
    }
    fVar6 = (_DAT_00858624 - *(float *)(param_1 + 0x44)) * (local_4 - *(float *)(param_1 + 0x3c));
  }
  else {
    if (*(float *)(param_1 + 0x44) < _DAT_00858624) {
      *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) + _DAT_00858c28;
    }
    if (_DAT_00858624 < *(float *)(param_1 + 0x44)) {
      *(undefined4 *)(param_1 + 0x44) = 0x3f800000;
    }
    fVar6 = (local_4 - *(float *)(param_1 + 0x3c)) * *(float *)(param_1 + 0x44);
  }
  *(float *)(param_1 + 0x3c) = fVar6 + *(float *)(param_1 + 0x3c);
  if ((param_4 < _DAT_00859a44) && (DAT_00858b50 < *(float *)(param_1 + 0x3c))) {
    fVar6 = *(float *)(param_1 + 0x40) * *(float *)(param_1 + 0x3c);
    uVar2 = *(undefined4 *)(*(int *)(param_2 + 0x490) + 0x10);
    if (0 < *(int *)(param_1 + 0x38)) {
      fVar5 = fVar6;
      if (*(int *)(param_1 + 0x30) != 0) {
        fVar5 = -fVar6;
      }
      FUN_007eb7c0(uVar2,&DAT_0086ebd4,fVar5,1);
    }
    if (*(int *)(param_1 + 0x38) != 2) {
      fVar6 = -fVar6;
    }
    FUN_007eb7c0(uVar2,&DAT_0086ebc8,fVar6,1);
    *(uint *)(param_2 + 0x470) = *(uint *)(param_2 + 0x470) | 0x4000;
  }
  return;
}



/* function 00642ae0 FUN_00642ae0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00642ae0(int param_1,int param_2,char param_3,float param_4)

{
  int *piVar1;
  float fVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  bool bVar9;
  ushort uVar10;
  
  iVar7 = param_2;
  cVar3 = FUN_005df8f0();
  if (cVar3 != '\0') {
    return;
  }
  iVar8 = *(int *)(param_2 + 0x58c);
  if (DAT_00c81324 <= DAT_00858b50) {
    if (*(int *)(iVar8 + 0x460) == param_2) {
      uVar6 = 10;
    }
    else if (*(int *)(iVar8 + 0x464) == param_2) {
      uVar6 = 8;
    }
    else if (*(int *)(iVar8 + 0x468) == param_2) {
      uVar6 = 0xb;
    }
    else {
      if (*(int *)(iVar8 + 0x46c) != param_2) goto LAB_00642b7b;
      uVar6 = 9;
    }
    FUN_006d3080(uVar6);
  }
  else {
    FUN_006d30b0(10);
    FUN_006d30b0(8);
    FUN_006d30b0(0xb);
    FUN_006d30b0(9);
    param_3 = '\0';
  }
LAB_00642b7b:
  piVar1 = (int *)(param_2 + 0x58c);
  bVar9 = *(int *)(*piVar1 + 0x464) == param_2;
  iVar8 = 0xa2;
  param_2 = 0xa2;
  if ((bVar9) || (*(int *)(*piVar1 + 0x46c) == iVar7)) {
    param_2 = 0xa3;
    iVar8 = 0xa3;
  }
  iVar5 = FUN_004d68b0(*(undefined4 *)(iVar7 + 0x18),iVar8);
  if (param_3 == '\0') {
    if (iVar5 != 0) {
      *(undefined4 *)(iVar5 + 0x1c) = 0xc0800000;
    }
    bVar4 = *(byte *)(param_1 + 0x5c);
LAB_00642e55:
    *(byte *)(param_1 + 0x5c) = bVar4 & 0xfd;
    return;
  }
  bVar4 = *(byte *)(param_1 + 0x5c);
  if ((bVar4 & 2) == 0) {
    iVar5 = FUN_00407180(0,1000);
    if (0x3e3 < iVar5) {
      bVar9 = true;
      if (*(int *)(*(int *)(param_1 + 8) + 0x594) != 0) {
LAB_00642d30:
        FUN_004d4610(*(undefined4 *)(iVar7 + 0x18),0,iVar8,0x40800000);
        if (*(int *)(param_1 + 0x20) == -1) {
          FUN_00642760(iVar7);
          *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_1 + 0x20);
          *(byte *)(param_1 + 0x5c) = *(byte *)(param_1 + 0x5c) | 2;
          return;
        }
        *(int *)(param_1 + 0x48) = DAT_00b7cb84;
        *(byte *)(param_1 + 0x5c) = *(byte *)(param_1 + 0x5c) | 2;
        return;
      }
      uVar6 = FUN_0064f110(*(int *)(param_1 + 8),iVar7);
      iVar8 = FUN_006c2250(uVar6);
      if (((iVar8 != 0) || (cVar3 = FUN_0064ee10(*(undefined4 *)(param_1 + 8),uVar6), cVar3 != '\0')
          ) || (cVar3 = thunk_FUN_004011cd(iVar7), cVar3 == '\0')) {
        bVar9 = false;
      }
      iVar8 = *(int *)(param_1 + 8);
      iVar5 = *(int *)((&DAT_00a9b0c8)[*(short *)(iVar8 + 0x22)] + 0x5c);
      if ((((*(float *)(iVar5 + 0x78) != DAT_00858b50) || (*(float *)(iVar5 + 0x7c) != DAT_00858b50)
           ) || (*(float *)(iVar5 + 0x80) != DAT_00858b50)) &&
         (fVar2 = *(float *)(iVar5 + 0x80) -
                  *(float *)(*(int *)((&DAT_00a9b0c8)[*(short *)(iVar8 + 0x22)] + 0x5c) + 0x38),
         (*(byte *)(iVar8 + 0x429) & 8) == 0)) {
        if ((*(uint *)(&DAT_00c1cdc8 + (uint)*(byte *)(*(int *)(iVar8 + 900) + 0xde) * 0x94) >> 3 &
            1) == 0) {
          if (fVar2 < _DAT_0086ebf0) {
            return;
          }
          uVar10 = (ushort)(fVar2 < _DAT_0086ebec) << 8 | (ushort)(fVar2 == _DAT_0086ebec) << 0xe;
        }
        else {
          if (fVar2 < _DAT_00858ee8) {
            return;
          }
          uVar10 = (ushort)(fVar2 < _DAT_0086ebf4) << 8 | (ushort)(fVar2 == _DAT_0086ebf4) << 0xe;
        }
        if ((uVar10 != 0) && (iVar8 = param_2, bVar9)) goto LAB_00642d30;
      }
    }
  }
  else {
    if (iVar5 == 0) goto LAB_00642e55;
    if (param_4 < _DAT_00859a44) {
      fVar2 = DAT_00858b50;
      if (_DAT_00858f34 <= *(float *)(param_1 + 0x2c)) {
        fVar2 = (*(float *)(param_1 + 0x2c) - _DAT_00858f34) * _DAT_00858cb4;
      }
      if (iVar8 == 0xa2) {
        iVar8 = *(int *)(iVar7 + 0x49c);
      }
      else {
        iVar8 = *(int *)(iVar7 + 0x4a0);
      }
      FUN_007eb7c0(*(undefined4 *)(iVar8 + 0x10),&DAT_0086ebe0,-fVar2,1);
      *(uint *)(iVar7 + 0x470) = *(uint *)(iVar7 + 0x470) | 0x4000;
    }
    if ((5000 < (uint)(DAT_00b7cb84 - *(int *)(param_1 + 0x48))) &&
       (iVar7 = FUN_00407180(0,1000), 0x3e3 < iVar7)) {
      *(undefined4 *)(iVar5 + 0x1c) = 0xc0800000;
      *(byte *)(param_1 + 0x5c) = *(byte *)(param_1 + 0x5c) & 0xfd;
      return;
    }
  }
  return;
}



/* function 0066a850 FUN_0066a850 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0066a850(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  float10 fVar4;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  iVar2 = FUN_0053fb70(0);
  iVar3 = FUN_0056e210(0xffffffff);
  if ((((((param_2 != iVar3) || (*(short *)(iVar2 + 0x10e) != 0)) &&
        (cVar1 = FUN_00534540(), cVar1 != '\0')) &&
       (((*(byte *)(param_1 + 0x5c) & 1) == 0 && (iVar2 = FUN_006181d0(param_2), iVar2 == 0)))) &&
      (iVar2 = FUN_00681810(5), iVar2 == 0)) &&
     ((*(int **)(param_1 + 4) == (int *)0x0 ||
      ((iVar2 = (**(code **)(**(int **)(param_1 + 4) + 0x10))(), iVar2 != 0x395 &&
       (iVar2 = (**(code **)(**(int **)(param_1 + 4) + 0x10))(), iVar2 != 0x3ab)))))) {
    if (*(int *)(param_2 + 0x14) == 0) {
      iVar2 = param_2 + 4;
    }
    else {
      iVar2 = *(int *)(param_2 + 0x14) + 0x30;
    }
    FUN_0040fe60(&fStack_18,(float *)(param_1 + 0x1c),iVar2);
    fVar4 = (float10)FUN_00406da0();
    if ((float10)_DAT_0085eed4 < fVar4) {
      FUN_0059c910();
      iVar2 = *(int *)(param_2 + 0x14);
      if (fStack_18 * *(float *)(iVar2 + 0x10) +
          fStack_14 * *(float *)(iVar2 + 0x14) + fStack_10 * *(float *)(iVar2 + 0x18) <
          _DAT_00c18d48) {
        iVar3 = iVar2 + 0x30;
        if (iVar2 == 0) {
          iVar3 = param_2 + 4;
        }
        fStack_c = fStack_18 + fStack_18 + *(float *)(param_1 + 0x1c);
        fStack_8 = *(float *)(param_1 + 0x20) + fStack_14 + fStack_14;
        fStack_4 = fStack_10 + fStack_10 + *(float *)(iVar3 + 8) + _DAT_0086fd40;
        FUN_00618970("TaskAvoidOthPed",param_2,0,5000,0xffffffff,&fStack_c,0,0x3e800000,500,3,0);
        *(byte *)(param_1 + 0x5c) = *(byte *)(param_1 + 0x5c) | 1;
      }
    }
  }
  return;
}



/* function 0066ea37 FUN_0066ea37 */

undefined4 * __thiscall
FUN_0066ea37(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 *param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
            byte param_9,undefined4 param_10,byte param_11)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  void *pvStack_4;
  
  pvStack_4 = ExceptionList;
  ExceptionList = &pvStack_4;
  FUN_0061a3b0();
  *param_1 = &PTR_FUN_008700a8;
  param_1[3] = *param_5;
  param_1[4] = param_5[1];
  param_1[5] = param_5[2];
  param_1[7] = param_6;
  param_1[6] = param_4;
  param_1[8] = param_7;
  param_1[9] = param_8;
  *(undefined2 *)(param_1 + 10) = 0xffff;
  *(undefined2 *)(param_1 + 0xd) = 0xffff;
  param_1[0xf] = param_10;
  param_1[0xe] = 0;
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  *(undefined1 *)(param_1 + 0x12) = 0;
  *(undefined1 *)((int)param_1 + 0x49) = 0;
  uVar1 = param_1[0x13];
  uVar2 = (param_11 & 1) << 3 | param_9 & 1;
  param_1[0x13] = uVar2 | uVar1 & 0xfffffff6;
  if ((param_11 & 1) != 0) {
    param_1[0x13] = uVar2 | uVar1 & 0xffffff96;
    param_1[0x14] = 0;
    param_1[0x15] = 0;
    param_1[0x16] = 0;
    param_1[0x17] = 0;
  }
  puVar3 = (undefined4 *)thunk_FUN_00409aed(100);
  if (puVar3 == (undefined4 *)0x0) {
    puVar3 = (undefined4 *)0x0;
  }
  else {
    *puVar3 = 0;
  }
  param_1[0xc] = puVar3;
  puVar3 = (undefined4 *)FUN_0041b860(0x24);
  if (puVar3 == (undefined4 *)0x0) {
    puVar3 = (undefined4 *)0x0;
  }
  else {
    *puVar3 = 0;
    iVar5 = 8;
    puVar4 = puVar3;
    do {
      puVar4 = puVar4 + 1;
      *(undefined2 *)puVar4 = 0xffff;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  param_1[0xb] = puVar3;
  *(undefined2 *)(param_1 + 0xd) = 0xffff;
  param_1[10] = DAT_008a5f44;
  ExceptionList = pvStack_4;
  return param_1;
}



/* function 0066ebe0 FUN_0066ebe0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __thiscall FUN_0066ebe0(int param_1,undefined4 param_2,int param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  int *piVar9;
  int iVar10;
  float *pfVar11;
  float *pfVar12;
  uint uVar13;
  undefined1 local_c [12];
  
  if (param_3 == 900) {
    *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0x58);
    *(uint *)(param_1 + 0x4c) = *(uint *)(param_1 + 0x4c) & 0xffffffef;
    if (4 < *(int *)(param_1 + 0x18)) {
      piVar9 = *(int **)(param_1 + 0x30);
      iVar10 = *(int *)(param_1 + 0x38);
      if (*piVar9 <= iVar10) {
        iVar10 = *piVar9 + -1;
      }
      if (iVar10 < 0) {
        return 900;
      }
      pfVar11 = (float *)FUN_006698e0(local_c,param_2);
      fVar1 = (float)piVar9[iVar10 * 3 + 1];
      fVar2 = *pfVar11;
      fVar3 = (float)piVar9[iVar10 * 3 + 2];
      fVar4 = pfVar11[1];
      FUN_0059c910();
      pfVar11 = (float *)(*(int *)(param_1 + 0x30) + 4 + iVar10 * 0xc);
      pfVar12 = (float *)FUN_00669980(local_c,param_2);
      fVar5 = pfVar12[1];
      fVar6 = pfVar11[1];
      fVar7 = *pfVar12;
      fVar8 = *pfVar11;
      FUN_0059c910();
      fVar1 = (fVar1 - fVar2) * (fVar7 - fVar8) + (fVar3 - fVar4) * (fVar5 - fVar6) + 0.0;
      if (_DAT_00863c1c <= fVar1) {
        uVar13 = *(uint *)(param_1 + 0x4c) & 0xffffffef;
      }
      else {
        fVar1 = _DAT_00858624 - (fVar1 + _DAT_00858624) * _DAT_008700a4;
        fVar2 = DAT_00858b50;
        if ((DAT_00858b50 <= fVar1) && (fVar2 = fVar1, _DAT_00858624 < fVar1)) {
          fVar2 = _DAT_00858624;
        }
        if (*(int *)(param_1 + 0x18) == 7) {
          fVar2 = fVar2 * _DAT_00858b3c;
          *(undefined4 *)(param_1 + 0x50) = 0x40a00000;
          *(undefined4 *)(param_1 + 0x54) = 0x40a00000;
          *(float *)(param_1 + 0x58) = fVar2;
          uVar13 = *(uint *)(param_1 + 0x4c) | 0x10;
        }
        else {
          fVar2 = fVar2 * _DAT_00858ce8;
          *(undefined4 *)(param_1 + 0x50) = 0x40800000;
          *(undefined4 *)(param_1 + 0x54) = 0x40800000;
          *(float *)(param_1 + 0x58) = fVar2;
          uVar13 = *(uint *)(param_1 + 0x4c) | 0x10;
        }
      }
      *(uint *)(param_1 + 0x4c) = uVar13;
    }
    uVar13 = *(uint *)(param_1 + 0x4c);
    if ((uVar13 & 0x20) != 0) {
      *(uint *)(param_1 + 0x4c) = uVar13 & 0xffffffdf | 0x40;
      return 0x39e;
    }
    *(uint *)(param_1 + 0x4c) = uVar13 & 0xffffff9f;
  }
  return param_3;
}



/* function 00671750 FUN_00671750 */

void __thiscall
FUN_00671750(int param_1,undefined4 param_2,undefined4 *param_3,float param_4,float param_5,
            float param_6,char param_7)

{
  char cVar1;
  
  if ((((param_7 == '\0') && (cVar1 = FUN_00509760(param_1 + 0xc,param_3), cVar1 == '\0')) &&
      (*(float *)(param_1 + 0x1c) == param_4)) &&
     ((*(float *)(param_1 + 0x20) == param_5 && (*(float *)(param_1 + 0x24) == param_6)))) {
    return;
  }
  *(undefined4 *)(param_1 + 0xc) = *param_3;
  *(undefined4 *)(param_1 + 0x10) = param_3[1];
  *(undefined4 *)(param_1 + 0x14) = param_3[2];
  *(float *)(param_1 + 0x1c) = param_4;
  *(float *)(param_1 + 0x20) = param_5;
  *(float *)(param_1 + 0x24) = param_6;
  if ((*(uint *)(param_1 + 0x4c) & 8) != 0) {
    *(undefined4 *)(param_1 + 0x50) = 0;
    *(undefined4 *)(param_1 + 0x54) = 0;
    *(undefined4 *)(param_1 + 0x58) = 0;
    *(undefined4 *)(param_1 + 0x5c) = 0;
    *(uint *)(param_1 + 0x4c) = *(uint *)(param_1 + 0x4c) & 0xffffffdf | 0x40;
  }
  FUN_0066efa0(param_2);
  FUN_006699e0();
  *(uint *)(param_1 + 0x4c) = *(uint *)(param_1 + 0x4c) | 4;
  return;
}



/* function 00688930 FUN_00688930 */

undefined4 * __thiscall FUN_00688930(undefined4 *param_1,undefined4 *param_2,int param_3)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00846c08;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_0061a390();
  *param_1 = &PTR_FUN_00870920;
  *(undefined1 *)(param_1 + 2) = 0;
  *(undefined1 *)((int)param_1 + 9) = 0;
  param_1[4] = 0xbf800000;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  local_4 = 0;
  param_1[8] = param_3;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[0xe] = 0;
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  *(undefined2 *)((int)param_1 + 10) = 0;
  param_1[3] = 0xbf;
  if (param_2 != (undefined4 *)0x0) {
    param_1[5] = *param_2;
    param_1[6] = param_2[1];
    param_1[7] = param_2[2];
  }
  if (param_3 != 0) {
    FUN_00571b70(param_1 + 8);
  }
  param_1[0x17] = 0;
  *(undefined1 *)(param_1 + 0x18) = 0;
  param_1[0x14] = 0;
  ExceptionList = local_c;
  return param_1;
}



/* function 0068a9f0 FUN_0068a9f0 */

void __thiscall FUN_0068a9f0(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  iVar1 = FUN_004a9be0("water_ripples",&local_c,param_3,0);
  *(int *)(param_1 + 0x5c) = iVar1;
  if (iVar1 != 0) {
    FUN_004aa890();
    FUN_004aa2f0();
  }
  return;
}



/* function 0068aa50 FUN_0068aa50 */

void __fastcall FUN_0068aa50(int param_1)

{
  if (*(int *)(param_1 + 0x5c) != 0) {
    FUN_004aa3f0();
    *(undefined4 *)(param_1 + 0x5c) = 0;
  }
  return;
}



/* function 0068aa70 FUN_0068aa70 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0068aa70(int param_1,int param_2)

{
  short sVar1;
  float fVar2;
  char cVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  float10 fVar10;
  float10 fVar11;
  undefined4 uVar12;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  float local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined1 local_28 [28];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_00846c6e;
  local_c = ExceptionList;
  iVar5 = *(int *)(param_2 + 0x14);
  if (iVar5 == 0) {
    fVar10 = (float10)fsin((float10)*(float *)(param_2 + 0x10));
    fVar11 = (float10)fcos((float10)*(float *)(param_2 + 0x10));
    local_58 = -(float)fVar10;
    local_54 = (float)fVar11;
    fVar2 = DAT_00858b50;
  }
  else {
    local_58 = *(float *)(iVar5 + 0x10);
    local_54 = *(float *)(iVar5 + 0x14);
    fVar2 = *(float *)(iVar5 + 0x18);
  }
  local_34 = local_58 * _DAT_00858ee8;
  if (iVar5 == 0) {
    pfVar4 = (float *)(param_2 + 4);
  }
  else {
    pfVar4 = (float *)(iVar5 + 0x30);
  }
  local_54 = local_54 * _DAT_00858ee8 + pfVar4[1];
  local_58 = local_34 + *pfVar4;
  if (*(int *)(param_2 + 0x480) == 0) {
    local_50 = fVar2 * _DAT_00858ee8 + pfVar4[2] + _DAT_00858b8c;
  }
  else {
    local_50 = *(float *)(*(int *)(param_2 + 0x480) + 0x90);
  }
  if (*(short *)(param_1 + 10) == 0) {
    ExceptionList = &local_c;
    iVar5 = FUN_007f2a50();
    *(float *)(iVar5 + 0x30) = local_58;
    *(float *)(iVar5 + 0x34) = local_54;
    *(float *)(iVar5 + 0x38) = local_50;
    FUN_007f18a0(iVar5);
    if (*(int *)(param_1 + 0x5c) == 0) {
      FUN_0068a9f0(param_2,iVar5);
    }
    if (*(int *)(param_1 + 0x5c) != 0) {
      FUN_004aa630(iVar5);
      FUN_004aa910(1);
    }
    FUN_007f2a20(iVar5);
  }
  else {
    ExceptionList = &local_c;
    if (*(int *)(param_1 + 0x5c) != 0) {
      ExceptionList = &local_c;
      FUN_004aa3f0();
      *(undefined4 *)(param_1 + 0x5c) = 0;
    }
  }
  sVar1 = *(short *)(param_1 + 10);
  if (sVar1 != 3) {
    *(undefined1 *)(param_1 + 0x60) = 0;
  }
  if ((sVar1 == 1) || (sVar1 == 2)) {
    iVar5 = *(int *)(param_2 + 0x14);
    local_44 = *(float *)(iVar5 + 0x18);
    fVar10 = (float10)FUN_0053cea0(*(undefined4 *)(iVar5 + 0x10),*(undefined4 *)(iVar5 + 0x14),0,0);
    fVar11 = (float10)FUN_0053cb00((float)fVar10);
    fVar10 = (float10)_DAT_0085a994;
    FUN_004ab290(0x3f800000,0x3f800000,0x3f800000,0x3e4ccccd,0x3ecccccd,0,0x3f000000);
    local_4c = 0.0;
    local_48 = 0.0;
    local_44 = 0.0;
    FUN_004aa440(&local_58,&local_4c,0,local_28,(float)(fVar11 + fVar10),0x3f99999a,0x3f19999a,0);
    FUN_004e2bb0(0x4c,0,0x3f800000,0,0,0,0);
    if (*(short *)(param_1 + 10) != 2) {
      ExceptionList = local_c;
      return;
    }
    uVar12 = FUN_00734a40(*(undefined4 *)(param_2 + 0x18));
    iVar5 = FUN_007c51a0(uVar12,0x18);
    iVar6 = FUN_007c5120(uVar12);
    iVar5 = iVar6 + 0x30 + iVar5 * 0x40;
    iVar6 = FUN_007c51a0(uVar12,0x22);
    iVar7 = FUN_007c5120(uVar12);
    iVar6 = iVar7 + 0x30 + iVar6 * 0x40;
    iVar7 = FUN_007c51a0(uVar12,0x35);
    iVar8 = FUN_007c5120(uVar12);
    iVar7 = iVar8 + 0x30 + iVar7 * 0x40;
    iVar8 = FUN_007c51a0(uVar12,0x2b);
    iVar9 = FUN_007c5120(uVar12);
    iVar8 = iVar9 + 0x30 + iVar8 * 0x40;
    if (*(int *)(param_2 + 0x14) == 0) {
      param_2 = param_2 + 4;
    }
    else {
      param_2 = *(int *)(param_2 + 0x14) + 0x30;
    }
    fVar2 = *(float *)(param_2 + 8);
    if ((ABS(*(float *)(iVar5 + 8) - fVar2) < _DAT_00858c28) &&
       (iVar5 = FUN_004a9be0("water_swim",iVar5,0,0), iVar5 != 0)) {
      FUN_004aa3d0();
      FUN_004e2bb0(0x4a,0,0x3f800000,0,0,0,0);
    }
    if ((ABS(*(float *)(iVar6 + 8) - fVar2) < _DAT_00858c28) &&
       (iVar5 = FUN_004a9be0("water_swim",iVar6,0,0), iVar5 != 0)) {
      FUN_004aa3d0();
      FUN_004e2bb0(0x4a,0,0x3f800000,0,0,0,0);
    }
    if ((ABS(*(float *)(iVar7 + 8) - fVar2) < _DAT_00858c28) &&
       (iVar5 = FUN_004a9be0("water_swim",iVar7,0,0), iVar5 != 0)) {
      FUN_004aa3d0();
      FUN_004e2bb0(0x4a,0,0x3f800000,0,0,0,0);
    }
    if (_DAT_00858c28 <= ABS(*(float *)(iVar8 + 8) - fVar2)) {
      ExceptionList = local_c;
      return;
    }
    iVar5 = FUN_004a9be0("water_swim",iVar8,0,0);
    if (iVar5 == 0) {
      ExceptionList = local_c;
      return;
    }
    FUN_004aa3d0();
    uVar12 = 0x4a;
  }
  else {
    if (sVar1 != 3) {
      if (sVar1 != 4) {
        ExceptionList = local_c;
        return;
      }
      iVar5 = 5;
      cVar3 = FUN_005df8f0();
      if (cVar3 != '\0') {
        FUN_00559af0(8);
        iVar5 = FUN_00821b40();
      }
      iVar6 = FUN_00407180(0,100);
      if (iVar5 <= iVar6) {
        ExceptionList = local_c;
        return;
      }
      uVar12 = FUN_00734a40(*(undefined4 *)(param_2 + 0x18));
      iVar5 = FUN_007c5120(uVar12);
      local_34 = *(float *)(iVar5 + 0xf0);
      uStack_30 = *(undefined4 *)(iVar5 + 0xf4);
      uStack_2c = *(undefined4 *)(iVar5 + 0xf8);
      if ((_DAT_00c19684 & 1) == 0) {
        _DAT_00c19684 = _DAT_00c19684 | 1;
        uStack_4 = 0;
        FUN_004ab290(0x3f800000,0x3f800000,0x3f800000,0x3e800000,0x3e99999a,0,0x3f000000);
        uStack_4 = 0xffffffff;
      }
      uStack_40 = 0;
      uStack_3c = 0;
      uStack_38 = 0x40000000;
      FUN_004aa440(&local_34,&uStack_40,0,&DAT_00c19668,0xbf800000,0x3f99999a,0x3f19999a,0);
      ExceptionList = local_c;
      return;
    }
    if (*(char *)(param_1 + 0x60) != '\0') {
      ExceptionList = local_c;
      return;
    }
    local_4c = local_58;
    local_48 = local_54;
    local_44 = local_50;
    FUN_004a1070(&local_4c);
    *(undefined1 *)(param_1 + 0x60) = 1;
    uVar12 = 0x4b;
  }
  FUN_004e2bb0(uVar12,0,0x3f800000,0,0,0,0);
  ExceptionList = local_c;
  return;
}



/* function 00694850 FUN_00694850 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00694850(undefined4 *param_1)

{
  float fVar1;
  
  *param_1 = 0xbf800000;
  param_1[0x20] = 0x3f800000;
  param_1[1] = 0x3f800000;
  param_1[2] = 0x3f800000;
  param_1[3] = 0x3f800000;
  param_1[5] = param_1[0x20];
  param_1[4] = 0;
  param_1[7] = 0;
  param_1[6] = -(float)param_1[0x20];
  param_1[8] = param_1[0x20];
  param_1[9] = 0;
  param_1[0xb] = -(float)param_1[0x20];
  param_1[10] = -(float)param_1[0x20];
  param_1[0xc] = 0;
  param_1[0xd] = -(float)param_1[0x20];
  param_1[0xe] = param_1[0x20];
  param_1[0xf] = -(float)param_1[0x20];
  param_1[0x11] = 0;
  param_1[0x10] = -(float)param_1[0x20];
  param_1[0x12] = param_1[0x20];
  param_1[0x13] = 0;
  fVar1 = (float)param_1[0x20] + _DAT_00858c84;
  param_1[0x14] = 0;
  param_1[0x15] = -fVar1;
  fVar1 = (float)param_1[0x20] + _DAT_00858c84;
  param_1[0x17] = -fVar1;
  param_1[0x16] = -fVar1;
  fVar1 = (float)param_1[0x20] + _DAT_00858c84;
  param_1[0x18] = fVar1;
  param_1[0x19] = -fVar1;
  param_1[0x1a] = 0;
  param_1[0x1b] = ((float)param_1[0x20] + _DAT_00858c84) * _DAT_00858b18;
  fVar1 = ((float)param_1[0x20] + _DAT_00858c84) * _DAT_00858b18;
  param_1[0x1c] = -(float)param_1[0x20];
  param_1[0x1d] = fVar1;
  fVar1 = ((float)param_1[0x20] + _DAT_00858c84) * _DAT_00858b18;
  param_1[0x1e] = param_1[0x20];
  param_1[0x1f] = fVar1;
  return;
}



/* function 006c2b90 FUN_006c2b90 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_006c2b90(undefined4 *param_1,int param_2,undefined4 param_3)

{
  float *pfVar1;
  float *pfVar2;
  undefined4 uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float *pfVar7;
  undefined4 *puVar8;
  
  if (((*(byte *)(param_2 + 0x36) & 7) == 2) && (*(int *)(param_2 + 0x590) == 5)) {
    *(undefined1 *)((int)param_1 + 0xba) = 1;
  }
  else {
    *(undefined1 *)((int)param_1 + 0xba) = 0;
  }
  pfVar7 = (float *)FUN_00535300();
  pfVar1 = (float *)(param_1 + 0x1f);
  *pfVar1 = *pfVar7;
  param_1[0x20] = pfVar7[1];
  param_1[0x21] = pfVar7[2];
  pfVar2 = (float *)(param_1 + 0x1c);
  *pfVar2 = pfVar7[3];
  param_1[0x1d] = pfVar7[4];
  param_1[0x1e] = pfVar7[5];
  if (*(char *)((int)param_1 + 0xba) == '\0') {
    if (*(short *)(param_2 + 0x22) == 0x1a1) {
      param_1[0x1d] = (float)param_1[0x1d] * _DAT_00863264;
      param_1[0x20] = (float)param_1[0x20] * _DAT_00858ee8;
      goto LAB_006c2de1;
    }
    if (*(short *)(param_2 + 0x22) == 0x1cc) {
      param_1[0x20] = (float)param_1[0x1d] * _DAT_00871658;
      param_1[0x1d] = (float)param_1[0x1d] * _DAT_00859994;
      *pfVar2 = *pfVar2 * _DAT_00858c24;
      *pfVar1 = *pfVar1 * _DAT_00858c24;
      fVar4 = (float)param_1[0x21] - _DAT_00858b1c;
    }
    else {
      if (((*(byte *)(param_2 + 0x36) & 7) != 2) || (*(int *)(param_2 + 0x594) != 3))
      goto LAB_006c2de1;
      param_1[0x20] = -(float)param_1[0x1d];
      param_1[0x1e] = (float)param_1[0x21] * _DAT_00871654;
      fVar4 = (float)param_1[0x21] * _DAT_00862e1c;
    }
    goto LAB_006c2ddb;
  }
  switch(*(undefined2 *)(param_2 + 0x22)) {
  case 0x1be:
    fVar4 = (float)param_1[0x1d] * _DAT_00858c20;
    break;
  default:
    fVar4 = (float)param_1[0x1d] * _DAT_0087124c;
    break;
  case 0x1c4:
    param_1[0x1d] = (float)param_1[0x1d] * _DAT_008595f0;
    param_1[0x20] = (float)param_1[0x20] * _DAT_00871660;
    goto LAB_006c2de1;
  case 0x1c5:
  case 0x1ed:
    goto switchD_006c2c23_caseD_1c5;
  case 0x1c6:
    param_1[0x1d] = (float)param_1[0x1d] * _DAT_00859918;
    fVar4 = (float)param_1[0x20] * _DAT_0087165c;
    goto LAB_006c2cd1;
  case 0x1d8:
    param_1[0x1d] = (float)param_1[0x1d] * _DAT_00858f14;
    param_1[0x20] = (float)param_1[0x20] * _DAT_00858c20;
    fVar4 = (float)param_1[0x21] - _DAT_00858c24;
    goto LAB_006c2ddb;
  case 0x1d9:
    param_1[0x1d] = (float)param_1[0x1d] * _DAT_00859918;
    fVar4 = (float)param_1[0x20] * _DAT_00858c20;
LAB_006c2cd1:
    param_1[0x20] = fVar4;
    fVar4 = (float)param_1[0x21] - _DAT_00858cc4;
    goto LAB_006c2ddb;
  case 0x1e4:
    fVar4 = (float)param_1[0x1d] * _DAT_00858f14;
    break;
  case 0x253:
    param_1[0x1d] = (float)param_1[0x1d] * _DAT_008595f0;
    param_1[0x20] = (float)param_1[0x20] * _DAT_00858c98;
    fVar4 = (float)param_1[0x21] - _DAT_00858b1c;
LAB_006c2ddb:
    param_1[0x21] = fVar4;
    goto LAB_006c2de1;
  }
  param_1[0x1d] = fVar4;
switchD_006c2c23_caseD_1c5:
  param_1[0x20] = (float)param_1[0x20] * _DAT_00858c20;
LAB_006c2de1:
  fVar4 = (*pfVar2 - *pfVar1) * _DAT_00858b8c;
  param_1[0x27] = fVar4;
  fVar5 = ((float)param_1[0x1d] - (float)param_1[0x20]) * _DAT_00858b8c;
  param_1[0x28] = fVar5;
  fVar6 = ((float)param_1[0x1e] - (float)param_1[0x21]) * _DAT_00858b8c;
  param_1[0x29] = fVar6;
  if ((fVar6 <= fVar4) || (fVar6 <= fVar5)) {
    if ((fVar5 <= fVar4) || (fVar5 <= fVar6)) {
      fVar4 = _DAT_00858624 / fVar4;
      param_1[0x2a] = 0x3f800000;
      param_1[0x2b] = fVar4 * fVar5;
      param_1[0x2c] = fVar4 * fVar6;
    }
    else {
      fVar5 = _DAT_00858624 / fVar5;
      param_1[0x2b] = 0x3f800000;
      param_1[0x2a] = fVar4 * fVar5;
      param_1[0x2c] = fVar5 * fVar6;
    }
  }
  else {
    fVar6 = _DAT_00858624 / fVar6;
    param_1[0x2c] = 0x3f800000;
    param_1[0x2a] = fVar4 * fVar6;
    param_1[0x2b] = fVar6 * fVar5;
  }
  param_1[0x22] = 0x3f800000;
  param_1[0x30] = 0;
  param_1[0x31] = 0;
  *(undefined1 *)(param_1 + 0x26) = 0;
  param_1[0x2f] = 0;
  param_1[0x32] = 0;
  if (*(int *)(param_2 + 0x14) == 0) {
    puVar8 = (undefined4 *)(param_2 + 4);
  }
  else {
    puVar8 = (undefined4 *)(*(int *)(param_2 + 0x14) + 0x30);
  }
  *param_1 = *puVar8;
  param_1[1] = puVar8[1];
  uVar3 = puVar8[2];
  param_1[0x19] = (float)param_1[0x1a] + (float)param_1[0x19];
  param_1[2] = uVar3;
  param_1[0x16] = 0;
  param_1[0x17] = 0;
  param_1[0x18] = param_1[2];
  param_1[0x1b] = param_3;
  return;
}



/* function 006f9eb0 FUN_006f9eb0 */

void __fastcall FUN_006f9eb0(undefined4 *param_1)

{
  param_1[1] = 0xffffffff;
  param_1[2] = 0xffffffff;
  param_1[4] = 0xffffffff;
  param_1[5] = 0xffffffff;
  param_1[3] = 0xffffffff;
  param_1[6] = 0xffffffff;
  param_1[8] = 0xffffffff;
  *(undefined1 *)(param_1 + 9) = 0;
  param_1[10] = 0xffffffff;
  param_1[0xb] = 0xffffffff;
  param_1[0xd] = 0xffffffff;
  param_1[0xe] = 0xffffffff;
  param_1[0xc] = 0xffffffff;
  param_1[0xf] = 0xffffffff;
  param_1[0x11] = 0xffffffff;
  *(undefined1 *)(param_1 + 0x12) = 0;
  param_1[0x13] = 0xffffffff;
  param_1[0x14] = 0xffffffff;
  param_1[0x16] = 0xffffffff;
  param_1[0x17] = 0xffffffff;
  param_1[0x15] = 0xffffffff;
  param_1[0x18] = 0xffffffff;
  param_1[0x1a] = 0xffffffff;
  *(undefined1 *)(param_1 + 0x1b) = 0;
  param_1[0x1c] = 0xffffffff;
  param_1[0x1d] = 0xffffffff;
  param_1[0x1f] = 0xffffffff;
  param_1[0x20] = 0xffffffff;
  param_1[0x1e] = 0xffffffff;
  param_1[0x21] = 0xffffffff;
  param_1[0x23] = 0xffffffff;
  *(undefined1 *)(param_1 + 0x24) = 0;
  *param_1 = 0;
  return;
}



/* function 0076b567 FUN_0076b567 */

int __fastcall FUN_0076b567(int param_1)

{
  FUN_0076e66c();
  FUN_00781c4b();
  FUN_00781b83();
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x58) = 0;
  *(undefined4 *)(param_1 + 100) = 0;
  *(undefined4 *)(param_1 + 0x68) = 0;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  return param_1;
}



/* function 0076b60b FUN_0076b60b */

uint __thiscall
FUN_0076b60b(int param_1,WCHAR *param_2,LPSTR param_3,undefined4 param_4,undefined4 param_5,
            uint param_6,undefined4 param_7,undefined4 param_8)

{
  char *pcVar1;
  WCHAR WVar2;
  WCHAR *pWVar3;
  undefined4 *puVar4;
  DWORD nBufferLength;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  WCHAR local_108 [130];
  
  iVar5 = param_6;
  *(uint *)(param_1 + 0x58) = param_6;
  if (param_3 != (LPSTR)0x0) {
    WideCharToMultiByte(0xfde9,0,param_2,-1,(LPSTR)local_108,0x104,(LPCSTR)0x0,(LPBOOL)0x0);
    param_2 = local_108;
  }
  if (iVar5 == 0) {
    nBufferLength = GetFullPathNameA((LPCSTR)param_2,0,(LPSTR)0x0,(LPSTR *)0x0);
    param_6 = nBufferLength + 1;
    iVar5 = FUN_0076e3b3(param_6);
    *(int *)(param_1 + 0x60) = iVar5;
    if (iVar5 != 0) {
      iVar5 = FUN_0076e3b3(param_6);
      *(int *)(param_1 + 0x5c) = iVar5;
      if (iVar5 != 0) {
        GetFullPathNameA((LPCSTR)param_2,nBufferLength,*(LPSTR *)(param_1 + 0x60),&param_3);
        *(undefined1 *)(nBufferLength + *(int *)(param_1 + 0x60)) = 0;
        puVar4 = *(undefined4 **)(param_1 + 0x60);
        puVar7 = *(undefined4 **)(param_1 + 0x5c);
        for (uVar6 = param_6 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
          *puVar7 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar7 = puVar7 + 1;
        }
        for (uVar6 = param_6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *(undefined1 *)puVar7 = *(undefined1 *)puVar4;
          puVar4 = (undefined4 *)((int)puVar4 + 1);
          puVar7 = (undefined4 *)((int)puVar7 + 1);
        }
        if (param_3 != (LPSTR)0x0) {
          *param_3 = '\0';
        }
        uVar6 = FUN_00781c5d(*(undefined4 *)(param_1 + 0x5c),0);
        if ((int)uVar6 < 0) {
          FUN_0076eb84(param_5,0,0x5e3,"failed to open source file: \'%s\'",param_2);
          return uVar6;
        }
        *(undefined4 *)(param_1 + 100) = *(undefined4 *)(param_1 + 0x44);
        *(undefined4 *)(param_1 + 0x68) = *(undefined4 *)(param_1 + 0x48);
        goto LAB_0076b78f;
      }
    }
  }
  else {
    pWVar3 = param_2;
    do {
      WVar2 = *pWVar3;
      pWVar3 = (WCHAR *)((int)pWVar3 + 1);
    } while ((char)WVar2 != '\0');
    pcVar1 = (char *)((int)pWVar3 + (1 - ((int)param_2 + 1)));
    puVar4 = (undefined4 *)FUN_0076e3b3(pcVar1);
    *(undefined4 **)(param_1 + 0x5c) = puVar4;
    if (puVar4 != (undefined4 *)0x0) {
      pWVar3 = param_2;
      for (uVar6 = (uint)pcVar1 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *puVar4 = *(undefined4 *)pWVar3;
        pWVar3 = pWVar3 + 2;
        puVar4 = puVar4 + 1;
      }
      for (uVar6 = (uint)pcVar1 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(char *)puVar4 = (char)*pWVar3;
        pWVar3 = (WCHAR *)((int)pWVar3 + 1);
        puVar4 = (undefined4 *)((int)puVar4 + 1);
      }
      param_6 = (**(code **)**(undefined4 **)(param_1 + 0x58))
                          (*(undefined4 **)(param_1 + 0x58),param_7,*(undefined4 *)(param_1 + 0x5c),
                           param_8,param_1 + 100,param_1 + 0x68);
      if ((int)param_6 < 0) {
        FUN_0076eb84(param_5,0,0x5e3,"failed to open source file: \'%s\'",param_2);
        return param_6;
      }
LAB_0076b78f:
      uVar6 = FUN_0076e687(*(undefined4 *)(param_1 + 100),*(undefined4 *)(param_1 + 0x68),
                           *(undefined4 *)(param_1 + 0x5c),1,param_4,param_5);
      if ((int)uVar6 < 0) {
        return uVar6;
      }
      return 0;
    }
  }
  return 0x8007000e;
}



/* function 0076faeb FUN_0076faeb */

void __fastcall FUN_0076faeb(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[0xd] = 0;
  param_1[0x16] = 0;
  param_1[0x17] = 0;
  param_1[0x18] = 0;
  param_1[0x1e] = 0;
  return;
}



/* function 00770859 FUN_00770859 */

int __thiscall FUN_00770859(undefined4 *param_1,uint param_2)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int *piVar8;
  bool bVar9;
  bool bVar10;
  undefined4 uVar11;
  char *pcVar12;
  int *local_8;
  
  iVar4 = param_2;
  *(undefined4 *)(param_2 + 0x58) = param_1[0x17] << 2;
  iVar5 = *(int *)(param_2 + 0x30);
  local_8 = (int *)0x1;
  bVar9 = false;
  if (iVar5 == 0x1f) {
    local_8 = (int *)0x2;
  }
  if (param_1[0x1e] != 0) {
    if ((((iVar5 == 0x1a) || (iVar5 == 0x19)) || (iVar5 == 0x1c)) || (iVar5 == 0x1e)) {
      pcVar12 = "call, callnz, label, and ret instructions are not allowed in assembly fragments";
      uVar11 = 0x7e9;
LAB_007708d1:
      FUN_0076eb84(*param_1,param_2 + 0x10,uVar11,pcVar12);
      return -0x7fffbffb;
    }
    if (((((iVar5 == 0x14) || (iVar5 == 0x15)) ||
         ((iVar5 == 0x16 || ((iVar5 == 0x17 || (iVar5 == 0x18)))))) &&
        (*(int *)(param_2 + 0x48) != 0)) && (*(int *)(*(int *)(param_2 + 0x48) + 0x10) == 0)) {
      pcVar12 = "Matrices cannot be specified in temp registers with the fragment linker";
      uVar11 = 0x7ea;
      goto LAB_007708d1;
    }
  }
  iVar5 = *(int *)(param_2 + 0x3c);
  piVar8 = local_8;
  if ((iVar5 != 0) && (*(int *)(iVar5 + 4) == 0x12)) {
    bVar9 = *(int *)(iVar5 + 0x10) == -1;
    if (*(int *)(iVar5 + 0x14) != 0) {
      FUN_0076eb84(*param_1,param_2 + 0x10,0x7de,
                   "source modifiers are not allowed on destination parameters");
      param_1[0x13] = 1;
    }
    iVar5 = *(int *)(iVar5 + 0x28);
    piVar8 = (int *)((int)local_8 + 1);
    if (iVar5 != 0) {
      if (((int)param_1[0xe] < 4) || (5 < (int)param_1[0xe])) {
        FUN_0076eb84(*param_1,param_2 + 0x10,0x7d8,
                     "relative addressing of destination parameters is not supported in this shader version"
                    );
        param_1[0x13] = 1;
      }
      else {
        bVar9 = *(int *)(iVar5 + 0x10) == -1 || bVar9;
        if (*(int *)(iVar5 + 0x28) != 0) {
          FUN_0076eb84(*param_1,param_2 + 0x10,0x7d9,
                       "only one address register reference is allowed in a relative address expression"
                      );
          param_1[0x13] = 1;
        }
        piVar8 = (int *)((int)local_8 + 2);
      }
    }
  }
  local_8 = piVar8;
  if ((*(int *)(param_2 + 0x40) != 0) && (*(int *)(*(int *)(param_2 + 0x40) + 4) == 0x12)) {
    iVar5 = param_1[0xe];
    if (((-1 < iVar5) && (iVar5 < 2)) || ((5 < iVar5 && (iVar5 < 0xb)))) {
      FUN_0076eb84(*param_1,param_2 + 0x10,0x7e5,
                   "predicates are not supported in this shader version");
      param_1[0x13] = 1;
    }
    iVar5 = *(int *)(param_2 + 0x40);
    local_8 = (int *)((int)local_8 + 1);
    if (*(int *)(iVar5 + 0x10) == -1) {
      bVar9 = true;
    }
    if ((*(int *)(iVar5 + 0x14) != 0) && (*(int *)(iVar5 + 0x14) != 0xd000000)) {
      FUN_0076eb84(*param_1,param_2 + 0x10,0x7e3,"source modifiers are not allowed on predicates");
      param_1[0x13] = 1;
    }
    if (*(int *)(iVar5 + 0x28) != 0) {
      FUN_0076eb84(*param_1,param_2 + 0x10,0x7e4,
                   "relative addressing of predicates is not supported in this shader version");
      param_1[0x13] = 1;
    }
  }
  param_2 = 0;
  piVar8 = (int *)(iVar4 + 0x44);
  do {
    iVar5 = *piVar8;
    if (iVar5 == 0) break;
    iVar6 = *(int *)(iVar4 + 0x30);
    piVar1 = (int *)((int)local_8 + 1);
    if (((iVar6 != 0x51) && (iVar6 != 0x30)) && (iVar6 != 0x2f)) {
      if (*(int *)(iVar5 + 0x10) == -1) {
        bVar9 = true;
      }
      iVar5 = *(int *)(iVar5 + 0x28);
      if (iVar5 != 0) {
        if (*(int *)(iVar5 + 0x10) == -1) {
          bVar9 = true;
        }
        if (*(int *)(iVar5 + 0x28) != 0) {
          FUN_0076eb84(*param_1,iVar4 + 0x10,0x7d9,
                       "only one address register reference is allowed in a relative address expression"
                      );
          param_1[0x13] = 1;
        }
        if (param_1[0xe] != 0) {
          piVar1 = (int *)((int)local_8 + 2);
        }
      }
    }
    local_8 = piVar1;
    param_2 = param_2 + 1;
    piVar8 = piVar8 + 1;
  } while (param_2 < 4);
  iVar5 = FUN_007707b7(local_8);
  if (iVar5 < 0) {
    return iVar5;
  }
  iVar5 = param_1[0x17] + (int)local_8;
  uVar7 = *(uint *)(iVar4 + 0x30);
  if ((uVar7 != 3) ||
     (((iVar6 = param_1[0xe], iVar6 < 0 || (5 < iVar6)) && ((iVar6 < 10 || (0xe < iVar6))))))
  goto LAB_00770c01;
  iVar6 = *(int *)(iVar4 + 0x48);
  uVar2 = *(uint *)(iVar6 + 0x14);
  uVar11 = 0x7000000;
  uVar7 = 2;
  if (uVar2 < 0x7000001) {
    if (uVar2 == 0x7000000) {
      *(undefined4 *)(iVar6 + 0x14) = 0x8000000;
      goto LAB_00770c01;
    }
    if (uVar2 == 0) {
      *(undefined4 *)(iVar6 + 0x14) = 0x1000000;
      goto LAB_00770c01;
    }
    if (uVar2 == 0x1000000) {
      *(undefined4 *)(iVar6 + 0x14) = 0;
      goto LAB_00770c01;
    }
    uVar11 = 0x2000000;
    if (uVar2 == 0x2000000) {
      *(undefined4 *)(iVar6 + 0x14) = 0x3000000;
      goto LAB_00770c01;
    }
    if (uVar2 != 0x3000000) {
      uVar11 = 0x4000000;
      if (uVar2 == 0x4000000) {
        *(undefined4 *)(iVar6 + 0x14) = 0x5000000;
        goto LAB_00770c01;
      }
      if (uVar2 != 0x5000000) {
        bVar10 = uVar2 == 0x6000000;
        goto LAB_00770b70;
      }
    }
  }
  else if (uVar2 != 0x8000000) {
    if ((uVar2 != 0x9000000) && (uVar2 != 0xa000000)) {
      uVar11 = 0xb000000;
      if (uVar2 == 0xb000000) {
        *(undefined4 *)(iVar6 + 0x14) = 0xc000000;
        goto LAB_00770c01;
      }
      if (uVar2 == 0xc000000) goto LAB_00770bfe;
      bVar10 = uVar2 == 0xd000000;
LAB_00770b70:
      if (!bVar10) goto LAB_00770c01;
    }
    FUN_0076eb84(*param_1,iVar4 + 0x10,0x7dd,"source modifiers incompatible with SUB instruction");
    param_1[0x13] = 1;
    goto LAB_00770c01;
  }
LAB_00770bfe:
  *(undefined4 *)(iVar6 + 0x14) = uVar11;
LAB_00770c01:
  if (*(int *)(iVar4 + 0x54) != 0) {
    uVar7 = uVar7 | 0x40000000;
  }
  if (*(int *)(iVar4 + 0x40) != 0) {
    uVar7 = uVar7 | 0x10000000;
  }
  iVar6 = param_1[0xe];
  if (((0 < iVar6) && (iVar6 < 6)) || ((9 < iVar6 && (iVar6 < 0xf)))) {
    uVar7 = uVar7 | ((int)local_8 + -1) * 0x1000000;
  }
  iVar6 = *(int *)(iVar4 + 0x30);
  if (((iVar6 == 0x29) || (iVar6 == 0x2d)) || (iVar6 == 0x5e)) {
    uVar7 = uVar7 | (*(uint *)(iVar4 + 0x38) & 7) << 0x10;
  }
  *(uint *)(param_1[0x16] + param_1[0x17] * 4) = uVar7;
  param_1[0x17] = param_1[0x17] + 1;
  iVar6 = param_1[0x17];
  if (*(int *)(iVar4 + 0x30) == 0x1f) {
    *(uint *)(param_1[0x16] + iVar6 * 4) = *(uint *)(iVar4 + 0x38) | 0x80000000;
    param_1[0x17] = param_1[0x17] + 1;
    iVar6 = param_1[0x17];
  }
  iVar3 = *(int *)(iVar4 + 0x3c);
  if ((iVar3 != 0) && (*(int *)(iVar3 + 4) == 0x12)) {
    if ((param_1[0xe] == 0) && (*(int *)(iVar3 + 0x20) == 0xf0000)) {
      iVar6 = *(int *)(iVar4 + 0x30);
      if ((iVar6 == 0x15) || (iVar6 == 0x17)) {
        *(undefined4 *)(iVar3 + 0x20) = 0x70000;
      }
      else if (iVar6 == 0x18) {
        *(undefined4 *)(iVar3 + 0x20) = 0x30000;
      }
    }
    uVar7 = ((*(uint *)(iVar3 + 0x10) | 0xfffffff8) << 0x14 | *(uint *)(iVar3 + 0x10) & 0x18) << 8 |
            *(uint *)(iVar4 + 0x34) & 0xff00000 | *(uint *)(iVar3 + 0x18) & 0x7ff |
            *(uint *)(iVar3 + 0x20) & 0xf0000;
    if (*(int *)(iVar3 + 0x28) != 0) {
      uVar7 = uVar7 | 0x2000;
    }
    *(uint *)(param_1[0x16] + param_1[0x17] * 4) = uVar7;
    param_1[0x17] = param_1[0x17] + 1;
    iVar3 = *(int *)(iVar3 + 0x28);
    iVar6 = param_1[0x17];
    if (iVar3 != 0) {
      *(uint *)(param_1[0x16] + iVar6 * 4) =
           ((*(uint *)(iVar3 + 0x10) | 0xfffffff8) << 0x14 | *(uint *)(iVar3 + 0x10) & 0x18) << 8 |
           *(uint *)(iVar3 + 0x14) & 0xf000000 | *(uint *)(iVar3 + 0x18) & 0x7ff |
           *(uint *)(iVar3 + 0x24) & 0xff0000;
      param_1[0x17] = param_1[0x17] + 1;
      iVar6 = param_1[0x17];
    }
  }
  iVar3 = *(int *)(iVar4 + 0x40);
  if ((iVar3 != 0) && (*(int *)(iVar3 + 4) == 0x12)) {
    *(uint *)(param_1[0x16] + iVar6 * 4) =
         ((*(uint *)(iVar3 + 0x10) | 0xfffffff8) << 0x14 | *(uint *)(iVar3 + 0x10) & 0x18) << 8 |
         *(uint *)(iVar3 + 0x14) & 0xf000000 | *(uint *)(iVar3 + 0x18) & 0x7ff |
         *(uint *)(iVar3 + 0x24) & 0xff0000;
    param_1[0x17] = param_1[0x17] + 1;
    iVar6 = param_1[0x17];
  }
  iVar3 = *(int *)(iVar4 + 0x30);
  if (iVar3 == 0x51) {
    param_2 = 0;
    piVar8 = (int *)(iVar4 + 0x44);
    do {
      iVar3 = *piVar8;
      if (iVar3 == 0) break;
      if ((4 < *(int *)(iVar3 + 0x10)) && (*(int *)(iVar3 + 0x10) < 9)) {
        *(float *)(param_1[0x16] + iVar6 * 4) = (float)*(double *)(iVar3 + 0x18);
      }
      param_1[0x17] = param_1[0x17] + 1;
      param_2 = param_2 + 1;
      iVar6 = param_1[0x17];
      piVar8 = piVar8 + 1;
    } while (param_2 < 4);
  }
  else if (iVar3 == 0x30) {
    param_2 = 0;
    piVar8 = (int *)(iVar4 + 0x44);
    do {
      iVar3 = *piVar8;
      if (iVar3 == 0) break;
      if ((*(int *)(iVar3 + 0x10) == 2) || (*(int *)(iVar3 + 0x10) == 4)) {
        *(undefined4 *)(param_1[0x16] + iVar6 * 4) = *(undefined4 *)(iVar3 + 0x18);
      }
      param_1[0x17] = param_1[0x17] + 1;
      param_2 = param_2 + 1;
      iVar6 = param_1[0x17];
      piVar8 = piVar8 + 1;
    } while (param_2 < 4);
  }
  else if (iVar3 == 0x2f) {
    *(uint *)(param_1[0x16] + iVar6 * 4) = (uint)(*(int *)(*(int *)(iVar4 + 0x44) + 0x18) != 0);
    param_1[0x17] = param_1[0x17] + 1;
  }
  else {
    param_2 = 0;
    local_8 = (int *)(iVar4 + 0x44);
    do {
      iVar6 = *local_8;
      if (iVar6 == 0) break;
      if (((param_1[0xe] == 0) && (*(undefined **)(iVar6 + 0x24) == &DAT_00e40000)) &&
         ((iVar3 = *(int *)(iVar4 + 0x30), iVar3 == 6 ||
          ((((iVar3 == 7 || (iVar3 == 0xe)) || (iVar3 == 0x4e)) ||
           ((iVar3 == 0xf || (iVar3 == 0x4f)))))))) {
        *(undefined4 *)(iVar6 + 0x24) = 0xff0000;
      }
      uVar7 = ((*(uint *)(iVar6 + 0x10) | 0xfffffff8) << 0x14 | *(uint *)(iVar6 + 0x10) & 0x18) << 8
              | *(uint *)(iVar6 + 0x14) & 0xf000000 | *(uint *)(iVar6 + 0x18) & 0x7ff |
              *(uint *)(iVar6 + 0x24) & 0xff0000;
      if (*(int *)(iVar6 + 0x28) != 0) {
        uVar7 = uVar7 | 0x2000;
      }
      *(uint *)(param_1[0x16] + param_1[0x17] * 4) = uVar7;
      param_1[0x17] = param_1[0x17] + 1;
      iVar6 = *(int *)(iVar6 + 0x28);
      if (iVar6 != 0) {
        if (param_1[0xe] == 0) {
          if (((*(int *)(iVar6 + 0x10) != 3) || (*(int *)(iVar6 + 0x14) != 0)) ||
             ((*(int *)(iVar6 + 0x18) != 0 || (*(int *)(iVar6 + 0x24) != 0)))) {
            FUN_0076eb84(*param_1,iVar4 + 0x10,0x7d7,
                         "only a0.x is allowed as a relative address register in vs_1_1");
            param_1[0x13] = 1;
          }
        }
        else {
          *(uint *)(param_1[0x16] + param_1[0x17] * 4) =
               ((*(uint *)(iVar6 + 0x10) | 0xfffffff8) << 0x14 | *(uint *)(iVar6 + 0x10) & 0x18) <<
               8 | *(uint *)(iVar6 + 0x14) & 0xf000000 | *(uint *)(iVar6 + 0x18) & 0x7ff |
               *(uint *)(iVar6 + 0x24) & 0xff0000;
          param_1[0x17] = param_1[0x17] + 1;
        }
      }
      param_2 = param_2 + 1;
      local_8 = local_8 + 1;
    } while (param_2 < 4);
  }
  if (param_1[0x17] != iVar5) {
    FUN_0076eb84(*param_1,iVar4 + 0x10,0,"internal error: instruction size mismatch");
    param_1[0x13] = 1;
  }
  if (bVar9) {
    param_1[0x19] = param_1[0x17];
  }
  else {
    iVar5 = FUN_00770767(iVar4 + 0x10);
    if (iVar5 < 0) {
      param_1[0x14] = 1;
    }
  }
  return 0;
}



/* function 0077107f FUN_0077107f */

void __fastcall FUN_0077107f(undefined4 *param_1)

{
  int iVar1;
  void *pvVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  uint local_2c;
  undefined4 local_28;
  undefined1 local_24 [16];
  void *local_14;
  undefined4 *local_10;
  uint local_c;
  undefined4 *local_8;
  
  FUN_007839b5(0x464e4946);
  iVar1 = param_1[0x1e];
  local_14 = (void *)0x0;
  local_8 = (undefined4 *)0x0;
  iVar1 = *(int *)(iVar1 + 0x60) + *(int *)(iVar1 + 0x5c) + *(int *)(iVar1 + 0x58);
  if ((iVar1 != 0) && (pvVar2 = operator_new(iVar1 * 4), local_14 = pvVar2, pvVar2 != (void *)0x0))
  {
    FUN_0076fac6(pvVar2);
    iVar1 = *(int *)(param_1[0x1e] + 0x60);
    FUN_0076fac6((void *)((int)pvVar2 + iVar1 * 4));
    iVar1 = iVar1 + *(int *)(param_1[0x1e] + 0x58);
    FUN_0076fac6((void *)((int)pvVar2 + iVar1 * 4));
    uVar4 = iVar1 + *(int *)(param_1[0x1e] + 0x5c);
    FUN_008247e0(pvVar2,uVar4,4,&LAB_00770fd3);
    local_10 = (undefined4 *)(uVar4 * 0x14);
    local_8 = operator_new((uint)local_10);
    if (local_8 != (undefined4 *)0x0) {
      local_34 = 0;
      local_28 = 0;
      local_30 = 0;
      local_38 = 0x14;
      local_2c = uVar4;
      iVar1 = FUN_00783a03(&local_38,0x14,1,0);
      if (-1 < iVar1) {
        puVar5 = local_8;
        for (uVar3 = (uint)local_10 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
          *puVar5 = 0;
          puVar5 = puVar5 + 1;
        }
        for (uVar3 = (uint)local_10 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *(undefined1 *)puVar5 = 0;
          puVar5 = (undefined4 *)((int)puVar5 + 1);
        }
        iVar1 = FUN_00783a03(local_8,local_10,1,&local_28);
        if (-1 < iVar1) {
          local_c = 0;
          if (uVar4 != 0) {
            local_10 = local_8;
            do {
              puVar5 = *(undefined4 **)((int)local_14 + local_c * 4);
              iVar1 = FUN_00783eaf(local_24,local_10,*puVar5,puVar5[1],*(undefined4 *)param_1[0x16])
              ;
              if (iVar1 < 0) goto LAB_0077127f;
              local_c = local_c + 1;
              local_10 = local_10 + 5;
            } while (local_c < uVar4);
          }
          iVar1 = FUN_00783a03(PTR_s_D3DX9_Shader_Assembler_008d88b8,0xffffffff,5,&local_34);
          if (-1 < iVar1) {
            uVar4 = FUN_00783b3a();
            if (uVar4 < 0x8001) {
              iVar1 = FUN_007707b7(uVar4);
              if (-1 < iVar1) {
                _memmove((void *)(param_1[0x16] + 4 + uVar4 * 4),(void *)(param_1[0x16] + 4),
                         param_1[0x17] * 4 - 4);
                iVar1 = FUN_00783b46(param_1[0x16] + 4,uVar4);
                if (-1 < iVar1) {
                  param_1[0x17] = param_1[0x17] + uVar4;
                  param_1[0x1a] = param_1[0x1a] + uVar4;
                  param_1[0x19] = param_1[0x17];
                }
              }
            }
            else {
              FUN_0076eb84(*param_1,param_1 + 4,0x7ef,"fragment info exceeds maximum comment size");
            }
          }
        }
      }
    }
  }
LAB_0077127f:
                    /* WARNING: Subroutine does not return */
  _free(local_14);
}



/* function 0077129f FUN_0077129f */

void __fastcall FUN_0077129f(undefined4 *param_1)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  undefined2 *puVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 local_54;
  undefined1 local_50 [4];
  undefined1 local_4c [4];
  uint local_48;
  undefined1 local_44 [4];
  uint local_40;
  undefined1 local_3c [12];
  undefined1 local_30 [20];
  int local_1c;
  int local_18;
  uint local_14;
  undefined4 *local_10;
  undefined4 *local_c;
  int local_8;
  
  FUN_007839b5(0x47554244);
  puVar7 = &local_54;
  for (iVar4 = 10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  iVar4 = 0;
  local_54 = 0x28;
  local_10 = (undefined4 *)0x0;
  local_c = (undefined4 *)0x0;
  local_8 = FUN_00783a03(&local_54,0x28,1,0);
  if (local_8 < 0) goto LAB_00771562;
  for (iVar1 = param_1[0xd]; iVar8 = iVar4, iVar1 != 0; iVar1 = *(int *)(iVar1 + 0xc)) {
    if ((*(int *)(iVar1 + 8) != 0) && (*(int *)(*(int *)(iVar1 + 8) + 4) == 0x11)) {
      iVar4 = *(int *)(iVar1 + 8);
      iVar8 = iVar4;
      break;
    }
  }
  for (; iVar4 != 0; iVar4 = *(int *)(iVar4 + 0xc)) {
    local_40 = local_40 + 1;
  }
  if (local_40 == 0) {
LAB_00771440:
    if ((((param_1[0x1d] == 0) ||
         (local_8 = FUN_00783a03(param_1[0x1d],0xffffffff,7,local_30), -1 < local_8)) &&
        ((param_1[0x1b] == 0 ||
         ((iVar4 = FUN_00783a03(param_1[0x1b],param_1[0x1c],5,local_4c), -1 < iVar4 &&
          (iVar4 = FUN_00783a03(&DAT_00858b54,1,5,0), -1 < iVar4)))))) &&
       (iVar4 = FUN_00783a03(PTR_s_D3DX9_Shader_Assembler_008d88b8,0xffffffff,5,local_50),
       -1 < iVar4)) {
      uVar2 = FUN_00783b3a();
      if (uVar2 < 0x8001) {
        local_8 = FUN_007707b7(uVar2);
        if (local_8 < 0) goto LAB_00771562;
        _memmove((void *)(param_1[0x16] + 4 + uVar2 * 4),(void *)(param_1[0x16] + 4),
                 param_1[0x17] * 4 - 4);
        uVar5 = 0;
        if (local_40 != 0) {
          piVar3 = local_c + 1;
          do {
            *piVar3 = *piVar3 + (param_1[0x1a] + uVar2) * 4;
            uVar5 = uVar5 + 1;
            piVar3 = piVar3 + 2;
          } while (uVar5 < local_40);
        }
        local_8 = FUN_00783b46(param_1[0x16] + 4,uVar2);
        if (local_8 < 0) goto LAB_00771562;
        param_1[0x17] = param_1[0x17] + uVar2;
        param_1[0x1a] = param_1[0x1a] + uVar2;
        param_1[0x19] = param_1[0x17];
      }
      else {
        FUN_0076ec4d(*param_1,param_1 + 4,0x7ee,
                     "debug info exceeds maximum comment size; no debug info emitted");
      }
      local_8 = 0;
    }
  }
  else {
    local_10 = operator_new(local_40 << 2);
    uVar2 = local_40;
    puVar7 = local_10;
    if (local_10 != (undefined4 *)0x0) {
      for (; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar7 = 0;
        puVar7 = puVar7 + 1;
      }
      local_c = operator_new(local_40 << 3);
      if (local_c != (undefined4 *)0x0) {
        local_1c = local_40 << 3;
        puVar7 = local_c;
        for (iVar4 = (local_40 & 0x1fffffff) << 1; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar7 = 0;
          puVar7 = puVar7 + 1;
        }
        for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
          *(undefined1 *)puVar7 = 0;
          puVar7 = (undefined4 *)((int)puVar7 + 1);
        }
        if (iVar8 != 0) {
          puVar6 = (undefined2 *)((int)local_c + local_40 * 8 + -6);
          do {
            *puVar6 = 0xffff;
            puVar6[-1] = *(undefined2 *)(iVar8 + 0x24);
            *(undefined4 *)(puVar6 + 1) = *(undefined4 *)(iVar8 + 0x58);
            if (*(int *)(iVar8 + 0x20) != 0) {
              iVar4 = FUN_00783a03(*(int *)(iVar8 + 0x20),0xffffffff,7,&local_18);
              if (iVar4 < 0) goto LAB_00771562;
              local_14 = 0;
              if (local_48 != 0) {
                do {
                  if (local_10[local_14] == local_18) break;
                  local_14 = local_14 + 1;
                } while (local_14 < local_48);
              }
              if (local_14 == local_48) {
                local_10[local_48] = local_18;
                local_48 = local_48 + 1;
              }
              *puVar6 = (short)local_14;
            }
            iVar8 = *(int *)(iVar8 + 0xc);
            puVar6 = puVar6 + -4;
          } while (iVar8 != 0);
        }
        if (((local_48 != 0) &&
            (local_8 = FUN_00783a03(local_10,local_48 << 2,1,local_44), local_8 < 0)) ||
           (local_8 = FUN_00783a03(local_c,local_1c,1,local_3c), local_8 < 0)) goto LAB_00771562;
        goto LAB_00771440;
      }
    }
    local_8 = -0x7ff8fff2;
  }
LAB_00771562:
                    /* WARNING: Subroutine does not return */
  _free(local_10);
}



/* function 00771724 FUN_00771724 */

int __thiscall
FUN_00771724(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,short *param_5,
            int param_6,int *param_7,undefined4 *param_8,int *param_9)

{
  undefined4 *puVar1;
  short sVar2;
  short *psVar3;
  int *piVar4;
  short *psVar5;
  int iVar6;
  char *pcVar7;
  
  piVar4 = param_9;
  psVar3 = param_5;
  psVar5 = param_5;
  do {
    sVar2 = *psVar5;
    psVar5 = (short *)((int)psVar5 + 1);
  } while ((char)sVar2 != '\0');
  if ((uint)((int)psVar5 - (int)((int)param_5 + 1)) < 3) {
    FUN_0076eb84(param_2,param_4,0x7d5,"invalid register, input, or constant name \'%s\'",param_5);
    return -0x7fffbffb;
  }
  *param_7 = 0;
  *param_8 = 0;
  *param_9 = 0;
  if (*param_5 == DAT_0087a1c4) {
    *param_7 = 1;
    iVar6 = FUN_0076fa94(param_5);
    if (iVar6 == 0) {
      iVar6 = FUN_0076f70a(psVar3 + 1,(int)&param_7 + 3,(int)&param_5 + 3);
      if (iVar6 < 0) {
        pcVar7 = "Invalid input register \'%s\' specified";
        goto LAB_007717b8;
      }
      *piVar4 = *(int *)(param_1 + 0x58);
      FUN_00771648(psVar3,*(undefined4 *)(param_1 + 0x58),1);
      *(int *)(param_1 + 0x58) = *(int *)(param_1 + 0x58) + 1;
    }
    else {
      *piVar4 = *(int *)(iVar6 + 4);
    }
    if (param_6 == 0) {
      return 0;
    }
    pcVar7 = "addressing operations are not allowed on input registers \'%s\'";
  }
  else if (*param_5 == DAT_0087a1c0) {
    *param_7 = 0;
    iVar6 = FUN_0076fa94(param_5);
    if (iVar6 == 0) {
      *piVar4 = *(int *)(param_1 + 0x5c);
      FUN_00771648(psVar3,*(undefined4 *)(param_1 + 0x5c),1);
      *(int *)(param_1 + 0x5c) = *(int *)(param_1 + 0x5c) + 1;
    }
    else {
      *piVar4 = *(int *)(iVar6 + 4);
    }
    if (param_6 == 0) {
      return 0;
    }
    pcVar7 = "addressing operations not allowed on temporary registers \'%s\'";
  }
  else {
    sVar2 = *param_5;
    if (((sVar2 == DAT_0087a344) || (sVar2 == DAT_0087a340)) || (sVar2 == DAT_0087a33c)) {
      if (*param_5 == DAT_0087a340) {
        *param_7 = 0xe;
      }
      else {
        *param_7 = (-(uint)(*param_5 != DAT_0087a33c) & 0xfffffffb) + 7;
      }
      iVar6 = FUN_0076fa94(param_5);
      if (iVar6 == 0) {
        iVar6 = FUN_00783cf8(param_4,psVar3,&param_8);
        if (iVar6 < 0) {
          return iVar6;
        }
        if (param_8 == (undefined4 *)0x0) {
          FUN_0076eb84(param_2,param_4,0x7d5,
                       "constant register \'%s\' must be defined as a variable \'%s\'",psVar3,
                       psVar3 + 1);
          return -0x7fffbffb;
        }
        *piVar4 = *(int *)(param_1 + 0x54);
        FUN_00771648(psVar3,*(undefined4 *)(param_1 + 0x54),param_8);
        *(int *)(param_1 + 0x54) = *(int *)(param_1 + 0x54) + (int)param_8;
        *(int *)(param_1 + 0x60) = *(int *)(param_1 + 0x60) + 1;
      }
      else {
        *piVar4 = *(int *)(iVar6 + 4);
        param_8 = *(undefined4 **)(iVar6 + 8);
      }
      if (param_6 == 0) {
        return 0;
      }
      puVar1 = *(undefined4 **)(param_6 + 0x18);
      if (param_8 < puVar1) {
        FUN_0076eb84(param_2,param_4,0x7d5,
                     "constant register address out of bounds on constant \'%s\', size %d, offset %d"
                     ,psVar3,param_8,puVar1);
        return -0x7fffbffb;
      }
      *piVar4 = *piVar4 + (int)puVar1;
      return 0;
    }
    pcVar7 = 
    "\'%s\' is not a valid register name.  Registers must start with v_, r_, c_, b_, or i_ depending on the register type."
    ;
  }
LAB_007717b8:
  FUN_0076eb84(param_2,param_4,0x7d5,pcVar7,psVar3);
  return -0x7fffbffb;
}



/* function 007859fe FUN_007859fe */

undefined4 * __fastcall FUN_007859fe(undefined4 *param_1)

{
  FUN_00784b73();
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[0x12] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  param_1[0x13] = 0xffffffff;
  param_1[0x14] = 0xffffffff;
  param_1[0x15] = 0xffffffff;
  param_1[0x16] = 0xffffffff;
  param_1[0x17] = 0xffffffff;
  param_1[0x18] = 0xffffffff;
  param_1[0x19] = 0xffffffff;
  *param_1 = &PTR_FUN_0087b100;
  return param_1;
}



/* function 00789a92 FUN_00789a92 */

int __thiscall FUN_00789a92(int *param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int *piVar2;
  
  if (param_3 == 0) {
    iVar1 = -0x7fffbffb;
  }
  else {
    param_1[0xb] = param_3;
    param_1[0xc] = param_4;
    param_1[0xd] = param_5;
    param_1[10] = param_2;
    param_1[0xe] = 0;
    param_1[0xf] = 0;
    param_1[0x10] = 0;
    iVar1 = FUN_00784ecf(&DAT_0087b124,0,0xffffffff,4);
    param_1[0x13] = iVar1;
    iVar1 = FUN_00784ecf(&DAT_00879a40,0x189,0xffffffff,4);
    param_1[0x14] = iVar1;
    iVar1 = FUN_00784ecf(&DAT_00879a94,0x129,0xffffffff,4);
    param_1[0x15] = iVar1;
    iVar1 = FUN_00784ecf(&DAT_00879a98,0x29,0xffffffff,4);
    param_1[0x16] = iVar1;
    iVar1 = FUN_00784ecf(&DAT_00879a38,0x32,0xffffffff,4);
    param_1[0x17] = iVar1;
    iVar1 = FUN_00784ecf(&DAT_0085a53c,3,0xffffffff,4);
    param_1[0x18] = iVar1;
    iVar1 = FUN_00784ecf(&DAT_00863a2c,6,0xffffffff,4);
    param_1[0x19] = iVar1;
    iVar1 = FUN_00784ecf(&DAT_00879a5c,0x169,0xffffffff,4);
    param_1[0x1a] = iVar1;
    if (param_1[1] == 8) {
      piVar2 = param_1 + 0x1b;
      for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *piVar2 = 0;
        piVar2 = piVar2 + 1;
      }
      iVar1 = (**(code **)(*param_1 + 0x10))();
      if ((-1 < iVar1) && (iVar1 = FUN_00785a61(0), -1 < iVar1)) {
        iVar1 = 0;
      }
    }
    else {
      iVar1 = -0x7ff8fff2;
    }
  }
  return iVar1;
}



/* function 00789ba9 FUN_00789ba9 */

int __thiscall FUN_00789ba9(int *param_1,int param_2)

{
  int iVar1;
  void *pvVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  uVar3 = 0;
  if (param_2 == 0) {
    iVar1 = -0x7fffbffb;
  }
  else {
    param_1[10] = *(int *)(param_2 + 0x28);
    param_1[0xb] = *(int *)(param_2 + 0x2c);
    param_1[0xc] = *(int *)(param_2 + 0x30);
    param_1[0xd] = *(int *)(param_2 + 0x34);
    param_1[0xf] = *(int *)(param_2 + 0x3c);
    param_1[0x10] = *(int *)(param_2 + 0x40);
    param_1[0x13] = *(int *)(param_2 + 0x4c);
    param_1[0x14] = *(int *)(param_2 + 0x50);
    param_1[0x15] = *(int *)(param_2 + 0x54);
    param_1[0x16] = *(int *)(param_2 + 0x58);
    param_1[0x17] = *(int *)(param_2 + 0x5c);
    param_1[0x18] = *(int *)(param_2 + 0x60);
    param_1[0x19] = *(int *)(param_2 + 100);
    param_1[0x1a] = *(int *)(param_2 + 0x68);
    if (param_1[1] != 0) {
      do {
        if (*(int *)(param_1[4] + uVar3 * 4) != 0) {
          FUN_00784b99(1);
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 < (uint)param_1[1]);
    }
    uVar3 = 0;
    if (param_1[2] != 0) {
      do {
        if (*(int *)(param_1[5] + uVar3 * 4) != 0) {
          FUN_00784bb5(1);
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 < (uint)param_1[2]);
    }
    uVar3 = 0;
    if (param_1[3] != 0) {
      do {
        if (*(int *)(param_1[6] + uVar3 * 4) != 0) {
          FUN_00784bd1(1);
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 < (uint)param_1[3]);
    }
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    if ((uint)param_1[7] < *(uint *)(param_2 + 4)) {
                    /* WARNING: Subroutine does not return */
      _free((void *)param_1[4]);
    }
    if ((uint)param_1[8] < *(uint *)(param_2 + 8)) {
                    /* WARNING: Subroutine does not return */
      _free((void *)param_1[5]);
    }
    if ((uint)param_1[9] < *(uint *)(param_2 + 0xc)) {
                    /* WARNING: Subroutine does not return */
      _free((void *)param_1[6]);
    }
    param_1[1] = *(int *)(param_2 + 4);
    param_1[2] = *(int *)(param_2 + 8);
    param_1[3] = *(int *)(param_2 + 0xc);
    puVar4 = (undefined4 *)param_1[4];
    for (uVar3 = param_1[1] & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    for (iVar1 = 0; iVar1 != 0; iVar1 = iVar1 + -1) {
      *(undefined1 *)puVar4 = 0;
      puVar4 = (undefined4 *)((int)puVar4 + 1);
    }
    puVar4 = (undefined4 *)param_1[5];
    for (uVar3 = param_1[2] & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    for (iVar1 = 0; iVar1 != 0; iVar1 = iVar1 + -1) {
      *(undefined1 *)puVar4 = 0;
      puVar4 = (undefined4 *)((int)puVar4 + 1);
    }
    puVar4 = (undefined4 *)param_1[6];
    for (uVar3 = param_1[3] & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    for (iVar1 = 0; iVar1 != 0; iVar1 = iVar1 + -1) {
      *(undefined1 *)puVar4 = 0;
      puVar4 = (undefined4 *)((int)puVar4 + 1);
    }
    uVar3 = 0;
    if (param_1[1] != 0) {
      do {
        pvVar2 = operator_new(0x34);
        if (pvVar2 == (void *)0x0) {
          iVar1 = 0;
        }
        else {
          iVar1 = FUN_007b4d5c();
        }
        *(int *)(param_1[4] + uVar3 * 4) = iVar1;
        if (iVar1 == 0) {
          return -0x7ff8fff2;
        }
        iVar1 = FUN_007b4da6(*(undefined4 *)(*(int *)(param_2 + 0x10) + uVar3 * 4));
        if (iVar1 < 0) {
          return iVar1;
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 < (uint)param_1[1]);
    }
    uVar3 = 0;
    if (param_1[2] != 0) {
      do {
        pvVar2 = operator_new(0x60);
        if (pvVar2 == (void *)0x0) {
          iVar1 = 0;
        }
        else {
          iVar1 = FUN_007856cd();
        }
        *(int *)(param_1[5] + uVar3 * 4) = iVar1;
        if (iVar1 == 0) {
          return -0x7ff8fff2;
        }
        iVar1 = FUN_0078572c(*(undefined4 *)(*(int *)(param_2 + 0x14) + uVar3 * 4));
        if (iVar1 < 0) {
          return iVar1;
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 < (uint)param_1[2]);
    }
    uVar3 = 0;
    if (param_1[3] != 0) {
      do {
        pvVar2 = operator_new(0x38);
        if (pvVar2 == (void *)0x0) {
          iVar1 = 0;
        }
        else {
          iVar1 = FUN_007851ab();
        }
        *(int *)(param_1[6] + uVar3 * 4) = iVar1;
        if (iVar1 == 0) {
          return -0x7ff8fff2;
        }
        iVar1 = FUN_0078543d(*(undefined4 *)(*(int *)(param_2 + 0x18) + uVar3 * 4));
        if (iVar1 < 0) {
          return iVar1;
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 < (uint)param_1[3]);
    }
    iVar1 = (**(code **)(*param_1 + 0x10))();
    if ((-1 < iVar1) && (iVar1 = FUN_00785a61(*(undefined4 *)(param_2 + 0x48)), -1 < iVar1)) {
      iVar1 = 0;
    }
  }
  return iVar1;
}



/* function 0082d726 __XcptFilter */

/* Library Function - Single Match
    __XcptFilter
   
   Library: Visual Studio 2003 Release */

int __cdecl __XcptFilter(ulong _ExceptionNum,_EXCEPTION_POINTERS *_ExceptionPtr)

{
  ulong *puVar1;
  code *pcVar2;
  void *pvVar3;
  ulong uVar4;
  void *pvVar5;
  _ptiddata p_Var6;
  int iVar7;
  int iVar8;
  ulong *puVar9;
  
  p_Var6 = __getptd();
  puVar1 = p_Var6->_initaddr;
  puVar9 = puVar1;
  do {
    if (*puVar9 == _ExceptionNum) break;
    puVar9 = puVar9 + 3;
  } while (puVar9 < puVar1 + DAT_008e3594 * 3);
  if ((puVar1 + DAT_008e3594 * 3 <= puVar9) || (*puVar9 != _ExceptionNum)) {
    puVar9 = (ulong *)0x0;
  }
  if ((puVar9 == (ulong *)0x0) || (pcVar2 = (code *)puVar9[2], pcVar2 == (code *)0x0)) {
    iVar7 = UnhandledExceptionFilter(_ExceptionPtr);
  }
  else if (pcVar2 == (code *)0x5) {
    puVar9[2] = 0;
    iVar7 = 1;
  }
  else {
    if (pcVar2 != (code *)0x1) {
      pvVar3 = p_Var6->_initarg;
      p_Var6->_initarg = _ExceptionPtr;
      if (puVar9[1] == 8) {
        if (DAT_008e3588 < DAT_008e358c + DAT_008e3588) {
          iVar8 = DAT_008e3588 * 0xc;
          iVar7 = DAT_008e3588;
          do {
            *(undefined4 *)(iVar8 + 8 + (int)p_Var6->_initaddr) = 0;
            iVar7 = iVar7 + 1;
            iVar8 = iVar8 + 0xc;
          } while (iVar7 < DAT_008e358c + DAT_008e3588);
        }
        uVar4 = *puVar9;
        pvVar5 = p_Var6->_pxcptacttab;
        if (uVar4 == 0xc000008e) {
          p_Var6->_pxcptacttab = (void *)0x83;
        }
        else if (uVar4 == 0xc0000090) {
          p_Var6->_pxcptacttab = (void *)0x81;
        }
        else if (uVar4 == 0xc0000091) {
          p_Var6->_pxcptacttab = (void *)0x84;
        }
        else if (uVar4 == 0xc0000093) {
          p_Var6->_pxcptacttab = (void *)0x85;
        }
        else if (uVar4 == 0xc000008d) {
          p_Var6->_pxcptacttab = (void *)0x82;
        }
        else if (uVar4 == 0xc000008f) {
          p_Var6->_pxcptacttab = (void *)0x86;
        }
        else if (uVar4 == 0xc0000092) {
          p_Var6->_pxcptacttab = (void *)0x8a;
        }
        (*pcVar2)(8,p_Var6->_pxcptacttab);
        p_Var6->_pxcptacttab = pvVar5;
      }
      else {
        puVar9[2] = 0;
        (*pcVar2)(puVar9[1]);
      }
      p_Var6->_initarg = pvVar3;
    }
    iVar7 = -1;
  }
  return iVar7;
}



/* function 0082eb9c _raise */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    _raise
   
   Library: Visual Studio 2003 Release */

int __cdecl _raise(int _SigNum)

{
  bool bVar1;
  int iVar2;
  undefined4 *puVar3;
  code *pcVar4;
  void *local_30;
  void *local_2c;
  _ptiddata local_28;
  
  bVar1 = false;
  if (_SigNum == 2) {
    puVar3 = &DAT_00c9aee4;
    pcVar4 = DAT_00c9aee4;
LAB_0082ec29:
    bVar1 = true;
  }
  else {
    if (((_SigNum != 4) && (_SigNum != 8)) && (_SigNum != 0xb)) {
      if (_SigNum == 0xf) {
        puVar3 = &DAT_00c9aef0;
        pcVar4 = DAT_00c9aef0;
      }
      else if (_SigNum == 0x15) {
        puVar3 = &DAT_00c9aee8;
        pcVar4 = DAT_00c9aee8;
      }
      else {
        if (_SigNum != 0x16) {
          return -1;
        }
        puVar3 = &DAT_00c9aeec;
        pcVar4 = DAT_00c9aeec;
      }
      goto LAB_0082ec29;
    }
    local_28 = __getptd();
    iVar2 = siglookup();
    puVar3 = (undefined4 *)(iVar2 + 8);
    pcVar4 = (code *)*puVar3;
  }
  if (pcVar4 == (code *)0x1) {
    return 0;
  }
  if (pcVar4 == (code *)0x0) {
                    /* WARNING: Subroutine does not return */
    __exit(3);
  }
  if (bVar1) {
    __lock(0);
  }
  if (((_SigNum == 8) || (_SigNum == 0xb)) || (_SigNum == 4)) {
    local_2c = local_28->_initarg;
    local_28->_initarg = (void *)0x0;
    if (_SigNum == 8) {
      local_30 = local_28->_pxcptacttab;
      local_28->_pxcptacttab = (void *)0x8c;
      goto LAB_0082ec88;
    }
  }
  else {
LAB_0082ec88:
    iVar2 = DAT_008e3588;
    if (_SigNum == 8) {
      for (; iVar2 < DAT_008e358c + DAT_008e3588; iVar2 = iVar2 + 1) {
        *(undefined4 *)((int)local_28->_initaddr + iVar2 * 0xc + 8) = 0;
      }
      goto LAB_0082ecb6;
    }
  }
  *puVar3 = 0;
LAB_0082ecb6:
  FUN_0082ecd7();
  if (_SigNum == 8) {
    (*pcVar4)(8,local_28->_pxcptacttab);
  }
  else {
    (*pcVar4)(_SigNum);
    if ((_SigNum != 0xb) && (_SigNum != 4)) {
      return 0;
    }
  }
  local_28->_initarg = local_2c;
  if (_SigNum == 8) {
    local_28->_pxcptacttab = local_30;
  }
  return 0;
}



/* function 012a5fc0 FUN_012a5fc0 */

uint * __thiscall FUN_012a5fc0(uint *param_1,uint param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 local_14;
  undefined1 local_13;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_012f9adc;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_012a6150();
  local_8 = 0;
  FUN_012a6240();
  local_8 = CONCAT31(local_8._1_3_,1);
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = param_2;
  local_14 = 0xff;
  local_13 = 0x15;
  local_16 = 0xe8;
  local_15 = 0xe9;
  param_1[0x15] = 0xffff;
  param_1[0x16] = 0xffff;
  param_1[0x17] = 0xffff;
  if ((param_2 & 1) != 0) {
    uVar1 = FUN_012aa4c0(&local_14,2);
    FUN_012a76b0(uVar1);
    iVar2 = FUN_012a7670();
    param_1[0x15] = iVar2 - 1;
  }
  if ((param_2 & 2) != 0) {
    uVar1 = FUN_012aa4c0(&local_16,1);
    FUN_012a76b0(uVar1);
    iVar2 = FUN_012a7670();
    param_1[0x16] = iVar2 - 1;
  }
  if ((param_2 & 4) != 0) {
    uVar1 = FUN_012aa4c0(&local_15,1);
    FUN_012a76b0(uVar1);
    iVar2 = FUN_012a7670();
    param_1[0x17] = iVar2 - 1;
  }
  ExceptionList = local_10;
  return param_1;
}



/* function 01561cf0 FUN_01561cf0 */

void __thiscall FUN_01561cf0(undefined4 *param_1,undefined4 *param_2)

{
  uint uVar1;
  uint unaff_ESI;
  
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  param_1[2] = param_2[2];
  param_1[3] = param_2[3];
  param_1[4] = param_2[4];
  param_1[5] = param_2[5];
  param_1[6] = param_2[6];
  param_1[7] = param_2[7];
  *(undefined1 *)(param_1 + 8) = *(undefined1 *)(param_2 + 8);
  *(undefined1 *)((int)param_1 + 0x21) = *(undefined1 *)((int)param_2 + 0x21);
  param_1[9] = param_2[9];
  param_1[10] = param_2[10];
  param_1[0xb] = param_2[0xb];
  param_1[0xc] = param_2[0xc];
  uVar1 = (param_1[0xd] ^ unaff_ESI) & 0x200 ^ unaff_ESI;
  param_1[0xd] = uVar1;
  uVar1 = (param_2[0xd] ^ uVar1) & 0x400 ^ uVar1;
  param_1[0xd] = uVar1;
  uVar1 = (param_2[0xd] ^ uVar1) & 0x800 ^ uVar1;
  param_1[0xd] = uVar1;
  param_1[0xd] = (param_2[0xd] ^ uVar1) & 0x1000 ^ uVar1;
  param_1[0xe] = param_2[0xe];
  param_1[0xf] = param_2[0xf];
  *(undefined1 *)(param_1 + 0x10) = *(undefined1 *)(param_2 + 0x10);
  *(undefined1 *)((int)param_1 + 0x41) = *(undefined1 *)((int)param_2 + 0x41);
  *(undefined1 *)((int)param_1 + 0x42) = *(undefined1 *)((int)param_2 + 0x42);
  *(undefined1 *)((int)param_1 + 0x43) = *(undefined1 *)((int)param_2 + 0x43);
  param_1[0x11] = param_2[0x11];
  param_1[0x12] = param_2[0x12];
  param_1[0x13] = param_2[0x13];
  param_1[0x14] = param_2[0x14];
  param_1[0x15] = param_2[0x15];
  param_1[0x16] = param_2[0x16];
  param_1[0x17] = param_2[0x17];
  param_1[0x18] = param_2[0x18];
  param_1[0x19] = param_2[0x19];
  param_1[0x1a] = param_2[0x1a];
  param_1[0x1b] = param_2[0x1b];
  param_1[0x1c] = param_2[0x1c];
  param_1[0x1d] = param_2[0x1d];
  param_1[0x1e] = param_2[0x1e];
  param_1[0x1f] = param_2[0x1f];
  param_1[0x20] = param_2[0x20];
  *(undefined1 *)(param_1 + 0x21) = *(undefined1 *)(param_2 + 0x21);
  *(undefined1 *)((int)param_1 + 0x85) = *(undefined1 *)((int)param_2 + 0x85);
  *(undefined1 *)((int)param_1 + 0x86) = *(undefined1 *)((int)param_2 + 0x86);
  *(undefined2 *)(param_1 + 0x22) = *(undefined2 *)(param_2 + 0x22);
  *(undefined2 *)((int)param_1 + 0x8a) = *(undefined2 *)((int)param_2 + 0x8a);
  *(undefined1 *)(param_1 + 0x23) = *(undefined1 *)(param_2 + 0x23);
  *(undefined1 *)((int)param_1 + 0x8d) = *(undefined1 *)((int)param_2 + 0x8d);
  *(undefined1 *)((int)param_1 + 0x8e) = *(undefined1 *)((int)param_2 + 0x8e);
  param_1[0x24] = param_2[0x24];
  param_1[0x25] = param_2[0x25];
  param_1[0x26] = param_2[0x26];
  param_1[0x27] = param_2[0x27];
  uVar1 = param_1[0x28] ^ (param_1[0x28] ^ param_2[0x28]) & 0x7fffffff;
  param_1[0x28] = uVar1;
  param_1[0x28] = (param_2[0x28] ^ uVar1) & 0x7fffffff ^ param_2[0x28];
  param_1[0x29] = param_2[0x29];
  param_1[0x2a] = param_2[0x2a];
  return;
}


