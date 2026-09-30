/* Full-analysis function mapping; decompilation is not original source. */

/* function 004aa750 FUN_004aa750 */

undefined4 __thiscall FUN_004aa750(int param_1,int param_2,undefined4 *param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  void *pvVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  
  *(int *)(param_1 + 8) = param_2;
  puVar1 = (undefined4 *)(param_1 + 0x10);
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar1 = *param_3;
    param_3 = param_3 + 1;
    puVar1 = puVar1 + 1;
  }
  *(undefined4 *)(param_1 + 0xc) = param_4;
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined1 *)(param_1 + 0x50) = 1;
  *(undefined1 *)(param_1 + 0x51) = 0;
  *(undefined1 *)(param_1 + 0x52) = 0;
  *(undefined2 *)(param_1 + 0x5c) = 0;
  *(undefined2 *)(param_1 + 0x5e) = 1000;
  *(undefined2 *)(param_1 + 0x60) = 1000;
  *(undefined4 *)(param_1 + 0x68) = 0;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0;
  *(byte *)(param_1 + 0x62) = *(byte *)(param_1 + 0x62) & 0xfc | 4;
  *(undefined4 *)(param_1 + 0x74) = 0;
  if (*(int *)(param_2 + 0x20) != 0) {
    puVar1 = (undefined4 *)FUN_0072f420(0x14,0);
    if (puVar1 == (undefined4 *)0x0) {
      puVar1 = (undefined4 *)0x0;
    }
    else {
      puVar1[4] = 0;
    }
    *(undefined4 **)(param_1 + 0x74) = puVar1;
    puVar5 = *(undefined4 **)(param_2 + 0x20);
    for (iVar4 = 5; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar1 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar1 = puVar1 + 1;
    }
  }
  iVar4 = 0;
  pvVar2 = operator_new((int)*(char *)(param_2 + 0x1b) << 2);
  *(void **)(param_1 + 0x78) = pvVar2;
  if ('\0' < *(char *)(param_2 + 0x1b)) {
    do {
      uVar3 = (**(code **)(**(int **)(*(int *)(param_2 + 0x1c) + iVar4 * 4) + 0xc))();
      *(undefined4 *)(*(int *)(param_1 + 0x78) + iVar4 * 4) = uVar3;
      (**(code **)(**(int **)(*(int *)(param_1 + 0x78) + iVar4 * 4) + 4))
                (*(undefined4 *)(*(int *)(param_2 + 0x1c) + iVar4 * 4),param_1);
      iVar4 = iVar4 + 1;
    } while (iVar4 < *(char *)(param_2 + 0x1b));
  }
  FUN_004dcf20(param_1);
  return 1;
}



/* function 004e9cab FUN_004e9cab */

void FUN_004e9cab(void)

{
  char in_AL;
  char cVar1;
  undefined4 unaff_EBX;
  int unaff_EBP;
  char *unaff_ESI;
  int in_stack_00000014;
  char in_stack_00000018;
  
  if (((in_AL != '\0') || (DAT_00b7cb48 != '\0')) && (in_stack_00000018 == '\0')) {
    *(undefined4 *)(unaff_ESI + 0x78) = unaff_EBX;
    *(int *)(unaff_ESI + 0x5c) = unaff_EBP;
  }
  if (in_stack_00000014 == unaff_EBP) {
    if (in_stack_00000018 != '\0') {
      *(int *)(unaff_ESI + 0x6c) = unaff_EBP;
      *(int *)(unaff_ESI + 0x70) = unaff_EBP;
      unaff_ESI[6] = '\0';
    }
  }
  else {
    *(int *)(unaff_ESI + 0x6c) = unaff_EBP;
    *(int *)(unaff_ESI + 0x70) = unaff_EBP;
    *(undefined4 *)(unaff_ESI + 0x7c) = unaff_EBX;
    unaff_ESI[1] = '\0';
    unaff_ESI[6] = '\0';
    FUN_00506ea0(0x23);
    if (unaff_ESI[0xe9] == (char)unaff_EBX) {
      unaff_ESI[0xe9] = '\r';
    }
    *(char *)(in_stack_00000014 + 0x1a) = unaff_ESI[0xe9];
    *(char *)(in_stack_00000014 + 6) = unaff_ESI[0xea];
    if (((*(int *)(unaff_ESI + 0x68) != 7) || (*unaff_ESI != '\0')) ||
       ((*(int *)(unaff_ESI + 0x6c) != unaff_EBP || (*(int *)(unaff_ESI + 0x70) != unaff_EBP)))) {
      *(undefined4 *)(unaff_ESI + 0x58) = DAT_00b7cb84;
      unaff_ESI[0x16] = DAT_00b70154;
      unaff_ESI[0x17] = DAT_00b70153;
      *(int *)(unaff_ESI + 0x74) = (int)unaff_ESI[0xe9];
    }
    if (unaff_ESI[0xe9] == '\0') {
      cVar1 = FUN_004d9c10(1,0xd);
      unaff_ESI[0xe9] = cVar1;
      return;
    }
  }
  return;
}



/* function 004ef680 FUN_004ef680 */

undefined2 * __thiscall FUN_004ef680(undefined2 *param_1,undefined2 *param_2)

{
  int *piVar1;
  
  if (param_1 != param_2) {
    piVar1 = (int *)(param_1 + 4);
    if (*(int *)(param_1 + 4) != 0) {
      FUN_00571a00(piVar1);
      *piVar1 = 0;
    }
    *param_1 = *param_2;
    param_1[1] = param_2[1];
    *(undefined4 *)(param_1 + 2) = *(undefined4 *)(param_2 + 2);
    *(undefined4 *)(param_1 + 6) = *(undefined4 *)(param_2 + 6);
    *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_2 + 8);
    *(undefined4 *)(param_1 + 10) = *(undefined4 *)(param_2 + 10);
    *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_2 + 0xc);
    *(undefined4 *)(param_1 + 0xe) = *(undefined4 *)(param_2 + 0xe);
    *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(param_2 + 0x10);
    *(undefined4 *)(param_1 + 0x12) = *(undefined4 *)(param_2 + 0x12);
    *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(param_2 + 0x14);
    *(undefined4 *)(param_1 + 0x16) = *(undefined4 *)(param_2 + 0x16);
    *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_2 + 0x18);
    *(undefined4 *)(param_1 + 0x1a) = *(undefined4 *)(param_2 + 0x1a);
    *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_2 + 0x1c);
    *(undefined4 *)(param_1 + 0x1e) = *(undefined4 *)(param_2 + 0x1e);
    *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_2 + 0x20);
    *(undefined4 *)(param_1 + 0x22) = *(undefined4 *)(param_2 + 0x22);
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_2 + 0x24);
    *(undefined4 *)(param_1 + 0x26) = *(undefined4 *)(param_2 + 0x26);
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_2 + 0x28);
    *(undefined1 *)(param_1 + 0x2a) = *(undefined1 *)(param_2 + 0x2a);
    param_1[0x2b] = param_2[0x2b];
    param_1[0x2c] = param_2[0x2c];
    param_1[0x2e] = param_2[0x2e];
    param_1[0x2f] = param_2[0x2f];
    *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_2 + 0x30);
    *(undefined4 *)(param_1 + 0x32) = *(undefined4 *)(param_2 + 0x32);
    param_1[0x34] = param_2[0x34];
    *(undefined4 *)(param_1 + 0x36) = *(undefined4 *)(param_2 + 0x36);
    param_1[0x38] = param_2[0x38];
    *piVar1 = 0;
    if (*(int *)(param_2 + 4) != 0) {
      *piVar1 = *(int *)(param_2 + 4);
      FUN_00571b70(piVar1);
    }
  }
  return param_1;
}



/* function 0050a160 FUN_0050a160 */

void __thiscall FUN_0050a160(undefined4 *param_1,char param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[4] = 0xbf800000;
  param_1[0xb] = 0xbf800000;
  param_1[0xd] = 0xbf800000;
  param_1[0x17] = 0xbf800000;
  param_1[0x18] = 0xbf800000;
  param_1[0x19] = 0xbf800000;
  param_1[0xf] = 0xbf800000;
  param_1[0x20] = 0xbf800000;
  *param_1 = 0;
  param_1[0x16] = 3;
  *(undefined1 *)(param_1 + 0x1e) = 0;
  param_1[0x1c] = 0x428c0000;
  param_1[0x15] = 0;
  *(undefined1 *)((int)param_1 + 0x79) = 0;
  param_1[9] = 0x3f800000;
  uVar1 = DAT_00b7cb84;
  if (param_2 != '\0') {
    iVar2 = FUN_0053fb70(0);
    *(undefined4 *)(iVar2 + 0x120) = uVar1;
  }
  return;
}



/* function 0050a9f0 FUN_0050a9f0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0050a9f0(int param_1,float param_2,float param_3,float param_4,float param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  iVar4 = (uint)*(byte *)(param_1 + 0x59) * 0x238;
  param_3 = *(float *)(iVar4 + 0x310 + param_1) - param_3;
  param_4 = *(float *)(iVar4 + 0x314 + param_1) - param_4;
  param_5 = *(float *)(iVar4 + 0x318 + param_1) - param_5;
  fVar1 = SQRT(param_3 * param_3 + param_4 * param_4);
  fVar1 = SQRT(fVar1 * fVar1 + param_5 * param_5);
  fVar2 = _DAT_00858628;
  if ((fVar1 <= _DAT_00858628) && (fVar2 = fVar1, fVar1 < DAT_00858b50)) {
    fVar2 = DAT_00858b50;
  }
  iVar4 = DAT_00b7cb84 - *(int *)(param_1 + 0x5c);
  fVar1 = (float)_DAT_0085a310 - fVar2 * (float)_DAT_0085a308;
  fVar2 = (float)iVar4;
  if (iVar4 < 0) {
    fVar2 = fVar2 + _DAT_00858c54;
  }
  fVar2 = (*(float *)(param_1 + 300) - fVar2 * _DAT_00858cdc) * fVar1;
  fVar3 = _FUN_00858ca0;
  if ((fVar2 < _FUN_00858ca0) && (fVar3 = fVar2, fVar2 <= DAT_00858b50)) {
    fVar3 = DAT_00858b50;
  }
  fVar1 = fVar1 * param_2 * _DAT_00858f9c;
  if (fVar3 < fVar1) {
    *(float *)(param_1 + 300) = fVar1;
    *(int *)(param_1 + 0x5c) = DAT_00b7cb84;
  }
  return;
}



/* function 0050e180 FUN_0050e180 */

void __fastcall FUN_0050e180(int param_1)

{
  *(undefined4 *)(param_1 + 0x18) = 0x42480000;
  *(undefined4 *)(param_1 + 0x24) = 0x42480000;
  *(undefined4 *)(param_1 + 0x1c) = 0x41f00000;
  *(undefined4 *)(param_1 + 0x20) = 0x425c0000;
  *(undefined4 *)(param_1 + 0x28) = 0x3d4ccccd;
  *(undefined4 *)(param_1 + 0x2c) = 0x428c0000;
  *(undefined4 *)(param_1 + 0x30) = 0x41b00000;
  *(undefined4 *)(param_1 + 0x34) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 0x41200000;
  *(undefined4 *)(param_1 + 0x48) = 0x1e;
  *(undefined4 *)(param_1 + 0x58) = 8;
  *(undefined4 *)(param_1 + 0x60) = 0x3c;
  *(undefined4 *)(param_1 + 0x68) = 0x42c80000;
  *(undefined4 *)(param_1 + 0x6c) = 0x42dc0000;
  *(undefined4 *)(param_1 + 0x70) = 0x41200000;
  *(undefined4 *)(param_1 + 0x74) = 0x40a00000;
  *(undefined4 *)(param_1 + 0x78) = 0x41400000;
  *(undefined4 *)(param_1 + 0x94) = 0x3f400000;
  *(undefined4 *)(param_1 + 0x98) = 4000;
  *(undefined1 *)(param_1 + 0x40) = 0;
  *(undefined1 *)(param_1 + 0x5c) = 0;
  *(undefined1 *)(param_1 + 0x80) = 0;
  *(undefined1 *)(param_1 + 0x81) = 0;
  *(undefined4 *)(param_1 + 0x7c) = 0x42400000;
  *(undefined4 *)(param_1 + 100) = 0x3c;
  *(undefined4 *)(param_1 + 0x44) = 0x1e;
  *(undefined1 *)(param_1 + 0x88) = 0;
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



/* function 0067b4e7 FUN_0067b4e7 */

undefined4 * __thiscall
FUN_0067b4e7(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4,
            undefined4 param_5,undefined4 param_6,int param_7)

{
  void *local_4;
  
  local_4 = ExceptionList;
  ExceptionList = &local_4;
  FUN_0061a390();
  *param_1 = &PTR_FUN_008705c4;
  *(undefined1 *)(param_1 + 2) = 0;
  *(undefined1 *)((int)param_1 + 9) = 0;
  *(undefined1 *)((int)param_1 + 10) = 0;
  *(undefined1 *)((int)param_1 + 0xb) = 0;
  *(undefined1 *)(param_1 + 3) = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  param_1[0x13] = 0;
  param_1[0x14] = 0;
  param_1[0x16] = param_6;
  param_1[0x15] = param_5;
  param_1[0x17] = 0;
  param_1[0x18] = param_7;
  *(undefined1 *)((int)param_1 + 0xd) = 0;
  *(undefined1 *)((int)param_1 + 0xe) = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  if (param_7 != 0) {
    FUN_00571b70(param_1 + 0x18);
  }
  if (param_4 != (undefined4 *)0x0) {
    param_1[0x12] = *param_4;
    param_1[0x13] = param_4[1];
    param_1[0x14] = param_4[2];
  }
  param_1[0x19] = 0;
  param_1[0x1a] = 0;
  ExceptionList = local_4;
  return param_1;
}


