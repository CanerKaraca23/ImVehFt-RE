/* Full-analysis function mapping; decompilation is not original source. */

/* function 005c7590 FUN_005c7590 */

void FUN_005c7590(int *param_1)

{
  int iVar1;
  int *piVar2;
  
  if (param_1[5] != 100) {
    *(undefined4 *)(*param_1 + 0x14) = 0x14;
    *(int *)(*param_1 + 0x18) = param_1[5];
    (**(code **)*param_1)(param_1);
  }
  if (param_1[0x11] == 0) {
    iVar1 = (**(code **)param_1[1])(param_1,0,0x150);
    param_1[0x11] = iVar1;
  }
  param_1[0xe] = 8;
  FUN_005c6bf0(param_1,0,&DAT_0086b450,0x32,1);
  FUN_005c6bf0(param_1,1,&DAT_0086b350,0x32,1);
  FUN_005c70d0();
  piVar2 = param_1 + 0x22;
  iVar1 = 0x10;
  do {
    *(undefined1 *)(piVar2 + -4) = 0;
    *(undefined1 *)piVar2 = 1;
    *(undefined1 *)(piVar2 + 4) = 5;
    piVar2 = (int *)((int)piVar2 + 1);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  param_1[0x2b] = 0;
  param_1[0x2a] = 0;
  *(undefined1 *)(param_1 + 0x2c) = 0;
  *(undefined1 *)((int)param_1 + 0xb1) = 0;
  *(undefined1 *)((int)param_1 + 0xb2) = 0;
  if (8 < param_1[0xe]) {
    *(undefined1 *)((int)param_1 + 0xb2) = 1;
  }
  *(undefined1 *)((int)param_1 + 0xb3) = 0;
  param_1[0x2d] = 0;
  param_1[0x2e] = 0;
  param_1[0x2f] = 0;
  param_1[0x30] = 0;
  *(undefined1 *)((int)param_1 + 0xc5) = 1;
  *(undefined1 *)((int)param_1 + 0xc6) = 1;
  *(undefined1 *)((int)param_1 + 199) = 0;
  *(undefined2 *)(param_1 + 0x32) = 1;
  *(undefined2 *)((int)param_1 + 0xca) = 1;
  FUN_005c7420(param_1);
  return;
}



/* function 005d0470 FUN_005d0470 */

void FUN_005d0470(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int local_1f0;
  undefined4 local_1ec [6];
  undefined4 local_1d4;
  undefined4 local_1d0;
  uint local_1cc;
  undefined4 local_1c8;
  undefined4 local_1c4;
  undefined4 local_134;
  uint local_11c;
  undefined1 local_84 [132];
  
  iVar2 = thunk_FUN_007452b0(param_1);
  local_1ec[0] = FUN_005cd810(local_84);
  FUN_005cf960(local_1ec,0x3e,0x168);
  local_1c4 = 2;
  FUN_005c7590(local_1ec);
  local_1d0 = *(undefined4 *)(iVar2 + 4);
  local_1cc = *(uint *)(iVar2 + 8);
  local_1c8 = 4;
  local_134 = 2;
  local_1d4 = param_2;
  FUN_005c26b0(local_1ec,1);
  iVar1 = *(int *)(iVar2 + 0x14);
  iVar4 = 0;
  local_1f0 = iVar1;
  if (local_11c < local_1cc) {
    do {
      local_1f0 = iVar1 + *(int *)(iVar2 + 4) * iVar4 * 4;
      iVar3 = FUN_005c2730(local_1ec,&local_1f0,1);
      if (iVar3 != 1) break;
      iVar4 = iVar4 + 1;
    } while (local_11c < local_1cc);
  }
  FUN_005cfac0(local_1ec);
  thunk_FUN_005c6b90(local_1ec);
  FUN_00802740(iVar2);
  return;
}



/* function 005d0820 FUN_005d0820 */

void FUN_005d0820(undefined4 param_1,undefined4 param_2)

{
  undefined1 local_14 [8];
  undefined1 *local_c;
  undefined1 *local_8;
  undefined1 *local_4;
  
  DAT_00bd0b74 = (FILE *)thunk_FUN_008232d8(param_2,&DAT_00860adc);
  if (0 < (int)DAT_00bd0b74) {
    local_c = &LAB_005d03e0;
    local_8 = &LAB_005d0400;
    local_4 = &LAB_005d0440;
    FUN_005d0470(param_1,local_14);
    _fclose(DAT_00bd0b74);
  }
  return;
}



/* function 007046e0 FUN_007046e0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_007046e0(void)

{
  int iVar1;
  bool bVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  char cVar8;
  int iVar9;
  undefined4 *puVar10;
  FILE *_File;
  float10 fVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  float fVar14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  if (DAT_00c402cf != '\0') {
    return;
  }
  (**(code **)(DAT_00c97b24 + 0x20))(2,3);
  FUN_007ee180(DAT_00c1703c);
  FUN_007fb060(DAT_00c402d8);
  FUN_007faf50(*(undefined4 *)(DAT_00c1703c + 0x60),0,0);
  FUN_007fb110();
  thunk_FUN_00745210(DAT_00c1703c);
  if ((_DAT_00c40330 & 1) == 0) {
    _DAT_00c40330 = _DAT_00c40330 | 1;
    _DAT_00c4032c = DAT_008d516c;
  }
  if (DAT_00c402c6 != '\0') {
    FUN_00704150();
  }
  FUN_00821b40();
  FUN_00821b40();
  FUN_00821b40();
  uVar3 = FUN_00821b40();
  FUN_00821b40();
  FUN_00821b40();
  FUN_00821b40();
  uVar4 = FUN_00821b40();
  FUN_00821b40();
  FUN_00821b40();
  FUN_00821b40();
  iVar9 = FUN_0056e210(0xffffffff);
  if (iVar9 != 0) {
    uVar13 = 0;
    fVar14 = DAT_00b7cb5c * _DAT_008d5168;
    FUN_0056e210(0xffffffff,0);
    fVar11 = (float10)FUN_005447b0(uVar13);
    uVar13 = 0;
    if ((float10)fVar14 <= ABS(fVar11 - (float10)_DAT_00c4032c)) {
      FUN_0056e210(0xffffffff,0);
      fVar11 = (float10)FUN_005447b0(uVar13);
      if (fVar11 <= (float10)_DAT_00c4032c) {
        fVar11 = (float10)_DAT_00c4032c - (float10)fVar14;
      }
      else {
        fVar11 = (float10)_DAT_00c4032c + (float10)fVar14;
      }
    }
    else {
      FUN_0056e210(0xffffffff);
      fVar11 = (float10)FUN_005447b0(uVar13);
    }
    _DAT_00c4032c = (float)fVar11;
    if (DAT_008d516c < _DAT_00c4032c) {
      _DAT_00c4032c = DAT_008d516c;
    }
  }
  FUN_00821b40();
  FUN_00821b40();
  FUN_00821b40();
  FUN_00821b40();
  FUN_00821b40();
  FUN_00821b40();
  uVar5 = FUN_00821b40();
  uVar6 = FUN_00821b40();
  uVar7 = FUN_00821b40();
  uStack_10 = CONCAT13(uVar3,CONCAT12(uVar7,CONCAT11(uVar6,uVar5)));
  uVar3 = FUN_00821b40();
  uVar5 = FUN_00821b40();
  uVar6 = FUN_00821b40();
  uStack_c = CONCAT13(uVar4,CONCAT12(uVar6,CONCAT11(uVar5,uVar3)));
  if (DAT_008d518c != '\0') {
    FUN_00703650(uStack_10,uStack_c);
  }
  if (((DAT_00c402c4 != '\0') && (DAT_00c402b8 == '\0')) && (DAT_00c402b9 == '\0')) {
    FUN_00702f00(DAT_008d5204);
    FUN_00702080(DAT_008d50f8,0,2,0xff);
  }
  if (DAT_00c402c7 != '\0') {
    FUN_00700be0(0x3f800000);
  }
  if (((DAT_008d5100 != '\0') && (DAT_008d5108 != '\0')) && (DAT_008d5109 != '\0')) {
    iVar9 = FUN_0056e0d0(0xffffffff,0);
    bVar2 = true;
    fVar14 = DAT_00c402c8;
    if (DAT_00c402c8 == DAT_00858b50) {
      if (((iVar9 == 0) || (iVar1 = *(int *)(iVar9 + 0x594), iVar1 == 4)) ||
         ((iVar1 == 3 || ((iVar1 == 5 || (iVar1 == 6)))))) {
        bVar2 = false;
      }
      else if ((((iVar1 == 0) && ((*(uint *)(iVar9 + 0x38c) & 0x80000) != 0)) &&
               (*(float *)(iVar9 + 0x8a4) < (float)_DAT_00859ef8)) &&
              (fVar11 = (float10)FUN_0040fdb0(iVar9 + 0x44,*(int *)(iVar9 + 0x14) + 0x10),
              (float10)_DAT_00858cc4 < fVar11)) {
        fVar11 = ((float10)*(float *)(iVar9 + 0x49c) + (float10)_DAT_00858624) * fVar11;
        fVar11 = fVar11 + fVar11;
        uStack_8 = (float)fVar11;
        if ((float10)_DAT_00858624 < fVar11) {
          uStack_8 = 1.0;
        }
        FUN_00700be0(uStack_8);
        fVar14 = DAT_00c402c8;
        goto LAB_00704e8a;
      }
      if ((DAT_00b5f851 != '\0') || (!bVar2)) goto LAB_00704e92;
      FUN_0056e090(0xffffffff);
      fVar11 = (float10)FUN_004082c0();
      fVar14 = (float)fVar11;
    }
LAB_00704e8a:
    FUN_007030a0(fVar14);
  }
LAB_00704e92:
  cVar8 = '\0';
  DAT_00c402c8 = 0.0;
  DAT_008d5109 = 1;
  DAT_00c402b7 = '\0';
  if ((DAT_00b5f851 != '\0') || (DAT_00b5f852 != '\0')) {
    cVar8 = '\x01';
    DAT_00c402b7 = '\x01';
  }
  if (DAT_00c402b8 == '\0') {
    _DAT_00c40300 = DAT_008d50b0;
  }
  else if (cVar8 == '\0') {
    FUN_007011c0(DAT_008d50ac);
    FUN_007037c0(DAT_008d50a8,1);
    cVar8 = DAT_00c402b7;
  }
  if ((DAT_00c402b9 != '\0') && (cVar8 == '\0')) {
    FUN_00703f80(DAT_008d50cc,DAT_008d50d0);
    FUN_007037c0(DAT_008d50b4,1);
  }
  if ((DAT_00c402cc != '\0') && (DAT_00c402c4 == '\0')) {
    uVar13 = DAT_008d5114;
    if (DAT_00c402ce == '\0') {
      uVar13 = DAT_00b7c53c;
    }
    FUN_00702080(uVar13,DAT_008d510c,DAT_008d5110,DAT_008d5118);
  }
  if ((DAT_00c402d1 != '\0') || (DAT_00c40328 != 0)) {
    if ((float)(int)DAT_00c40328 < DAT_00c81324 * _DAT_00858bf4) {
      DAT_00c40328 = DAT_00c40328 + 1;
    }
    if (DAT_00c81324 * _DAT_00858bf4 < (float)(int)DAT_00c40328) {
      DAT_00c40328 = DAT_00c40328 - 1;
    }
    DAT_00c40328 = ((int)DAT_00c40328 < 0) - 1 & DAT_00c40328;
    cVar8 = FUN_0072ddb0();
    if ((((cVar8 == '\0') && (cVar8 = FUN_0072ddc0(), cVar8 == '\0')) &&
        (DAT_00c8132c < DAT_00858b50 != (DAT_00c8132c == DAT_00858b50))) && (DAT_00b72914 == 0)) {
      if (DAT_00b6f03c == 0) {
        puVar10 = &DAT_00b6f02c;
      }
      else {
        puVar10 = (undefined4 *)(DAT_00b6f03c + 0x30);
      }
      if ((float)puVar10[2] < _DAT_00858978 != ((float)puVar10[2] == _DAT_00858978)) {
        FUN_007037c0((int)(DAT_00c40328 + ((int)DAT_00c40328 >> 0x1f & 3U)) >> 2,1);
      }
    }
  }
  if (DAT_00c402b4 != '\0') {
    FUN_007037c0(DAT_008d5094,1);
  }
  if (DAT_00c402ba == '\0') {
    if ((_DAT_00c812dc <= DAT_00858b50) && (DAT_00a9af38 == '\0')) {
      if (DAT_00c8132c < _DAT_008d514c) goto LAB_0070511e;
      uVar13 = 0;
      goto LAB_00705111;
    }
    if (_DAT_008d514c <= DAT_00c8132c) goto LAB_007050e9;
    if (_DAT_00c812dc <= DAT_00858b50) {
      if (DAT_00a9af38 == '\0') goto LAB_0070511e;
      uVar13 = 1;
      goto LAB_00705111;
    }
    uVar13 = 0;
    uVar12 = DAT_00c812d8;
  }
  else {
LAB_007050e9:
    uVar13 = 0;
LAB_00705111:
    uVar12 = 0x3f800000;
  }
  FUN_00701780(uVar12,uVar13);
LAB_0070511e:
  if ((DAT_00c402d3 != '\0') || (_DAT_008d514c <= DAT_00c8132c)) {
    FUN_00821b40();
    uVar3 = FUN_00821b40();
    uVar4 = FUN_00821b40();
    uVar5 = FUN_00821b40();
    uStack_8 = (float)(uint)CONCAT12(uVar5,CONCAT11(uVar4,uVar3));
    _DAT_00c40324 = DAT_00b7cb5c + _DAT_00c40324;
    if (_DAT_0085f114 < _DAT_00c40324) {
      _DAT_00c40324 = 24.0;
    }
    FUN_007039c0(uStack_8,_DAT_00c40324 * _DAT_0087265c * (float)DAT_00c17044 * _DAT_00859520 *
                          _DAT_008d5130,(float)DAT_00c17048 * _DAT_00859524 * _DAT_008d5134,
                 DAT_008d512c,DAT_008d5138,DAT_008d513c);
  }
  else {
    _DAT_00c40324 = 0.0;
  }
  if (DAT_00c402c5 != '\0') {
    FUN_00702f40();
  }
  if ((DAT_00c8a7c0._1_1_ != '\0') && (DAT_00ba67a7 != '\0')) {
    DAT_00c8a7c0._1_1_ = '\0';
    DAT_00c402d0 = 0;
  }
  if (DAT_00c40321 == '\0') {
    if (DAT_00c8a7c0._1_1_ != '\0') {
      if (DAT_00ba6830 != '\0') {
        DAT_00c40320 = '\x01';
      }
      DAT_00c40321 = 1;
      return;
    }
  }
  else if (DAT_00c8a7c0._1_1_ != '\0') {
    DAT_00c40321 = '\0';
    FUN_005619d0();
    if (DAT_00c40320 != '\0') {
      FUN_00732f30();
      FUN_0053e8d0();
      FUN_00538860();
      iVar9 = 1;
      FUN_00821bb5(&DAT_00b71670,"Gallery\\gallery%d.jpg",1);
      _File = (FILE *)FUN_008232d8(&DAT_00b71670,&DAT_0085a53c);
      while (_File != (FILE *)0x0) {
        iVar9 = iVar9 + 1;
        FUN_00821bb5(&DAT_00b71670,"Gallery\\gallery%d.jpg",iVar9);
        _fclose(_File);
        _File = (FILE *)FUN_008232d8(&DAT_00b71670,&DAT_0085a53c);
      }
      FUN_005d0820(DAT_00b6f97c,&DAT_00b71670);
      FUN_005387d0(&DAT_00858b54);
    }
    FUN_00561a00();
    if (DAT_00ba677b == '\0') {
      DAT_00c7c714 = 1;
      DAT_00c7c710 = 0;
    }
    DAT_00c40320 = '\0';
    DAT_00c8a7c0._1_1_ = '\0';
    DAT_00c402d0 = 0;
  }
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


