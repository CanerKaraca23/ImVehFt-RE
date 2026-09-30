/* Temporary bounded Ghidra decompilation; not original source. */

/* entry 0x004A1940; bounded CFG instructions=160; body bytes=2185 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004a1940(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  float *pfVar7;
  int *piVar8;
  float *pfVar9;
  float *pfVar10;
  float fStack_128;
  float fStack_124;
  float fStack_120;
  float fStack_11c;
  float fStack_118;
  float fStack_114;
  int iStack_110;
  float fStack_10c;
  float fStack_108;
  float fStack_104;
  int local_100;
  float fStack_fc;
  float fStack_f8;
  float fStack_f4;
  float *pfStack_f0;
  float fStack_ec;
  float fStack_e8;
  float fStack_e4;
  int local_e0;
  float fStack_dc;
  float fStack_d8;
  float fStack_d4;
  float fStack_d0;
  float fStack_cc;
  float fStack_c8;
  float fStack_c4;
  float fStack_c0;
  float fStack_bc;
  float fStack_b8;
  float fStack_b4;
  float fStack_b0;
  float fStack_ac;
  undefined1 uStack_a4;
  undefined1 uStack_a3;
  undefined1 uStack_a2;
  undefined1 uStack_a1;
  float fStack_98;
  float fStack_94;
  float fStack_90;
  float fStack_8c;
  float fStack_88;
  float fStack_84;
  float fStack_80;
  float fStack_7c;
  char cStack_70;
  char cStack_6f;
  float afStack_6c [8];
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  char cStack_2c;
  char cStack_2b;
  char cStack_2a;
  float fStack_28;
  float fStack_24;
  float fStack_20;
  
  local_100 = param_1;
  iVar4 = FUN_004a8ec0();
  if (iVar4 != 0) {
    iVar4 = **(int **)(param_1 + 0xc);
    local_e0 = iVar4;
    iVar5 = FUN_004a8ec0();
    if (iVar5 != 0) {
      (**(code **)(DAT_00c97b24 + 0x20))(0xc,1);
      (**(code **)(DAT_00c97b24 + 0x20))(10,5);
      (**(code **)(DAT_00c97b24 + 0x20))(0xb,2);
      FUN_004a13b0(iVar4,0,1);
      pfStack_f0 = (float *)(*(int *)(param_2 + 4) + 0x10);
      for (iVar4 = *(int *)(param_1 + 0x20); iVar4 != 0; iVar4 = *(int *)(iVar4 + 4)) {
        if (*(char *)(iVar4 + 0x37) == '\0') {
          fStack_10c = *(float *)(iVar4 + 0x10);
          fStack_108 = *(float *)(iVar4 + 0x14);
          fStack_104 = *(float *)(iVar4 + 0x18);
        }
        else {
          uVar6 = FUN_004a9440();
          FUN_004aa8c0(uVar6);
          FUN_007edd90(&fStack_10c,iVar4 + 0x10,1,uVar6);
          FUN_004a9460(uVar6);
        }
        FUN_004a4a80(*(undefined4 *)(*(int *)(iVar4 + 0x28) + 0x54),
                     *(float *)(iVar4 + 0xc) / *(float *)(iVar4 + 8),0,
                     *(undefined4 *)(*(int *)(*(int *)(iVar4 + 0x28) + 8) + 0xc),0,&uStack_a4);
        pfVar7 = (float *)FUN_004a9440();
        pfVar7[10] = 1.0;
        pfVar7[5] = 1.0;
        *pfVar7 = 1.0;
        pfVar7[4] = 0.0;
        pfVar7[2] = 0.0;
        pfVar7[1] = 0.0;
        pfVar7[9] = 0.0;
        pfVar7[8] = 0.0;
        pfVar7[6] = 0.0;
        pfVar7[0xe] = 0.0;
        pfVar7[0xd] = 0.0;
        pfVar7[0xc] = 0.0;
        pfVar7[3] = (float)((uint)pfVar7[3] | 0x20003);
        if (cStack_2b == '\0') {
          iVar5 = 0x10;
          if (cStack_2c == '\0') {
            pfVar9 = pfStack_f0;
            pfVar10 = pfVar7;
            for (; iVar5 != 0; iVar5 = iVar5 + -1) {
              *pfVar10 = *pfVar9;
              pfVar9 = pfVar9 + 1;
              pfVar10 = pfVar10 + 1;
            }
            fStack_fc = pfStack_f0[8];
            fStack_f8 = pfStack_f0[9];
            fStack_f4 = pfStack_f0[10];
          }
          else {
            pfVar9 = afStack_6c;
            pfVar10 = pfVar7;
            for (; iVar5 != 0; iVar5 = iVar5 + -1) {
              *pfVar10 = *pfVar9;
              pfVar9 = pfVar9 + 1;
              pfVar10 = pfVar10 + 1;
            }
            fStack_fc = fStack_4c;
            fStack_f8 = fStack_48;
            fStack_f4 = fStack_44;
          }
        }
        else {
          if (cStack_2a == '\0') {
            fStack_128 = fStack_28;
            fStack_124 = fStack_24;
            fStack_120 = fStack_20;
          }
          else {
            fStack_128 = *(float *)(iVar4 + 0x1c);
            fStack_124 = *(float *)(iVar4 + 0x20);
            fStack_120 = *(float *)(iVar4 + 0x24);
          }
          FUN_007ed9b0(&fStack_128,&fStack_128);
          fStack_ec = fStack_10c - pfStack_f0[0xc];
          fStack_e8 = fStack_108 - pfStack_f0[0xd];
          fStack_e4 = fStack_104 - pfStack_f0[0xe];
          FUN_007ed9b0(&fStack_ec,&fStack_ec);
          fStack_11c = fStack_e4 * fStack_124 - fStack_e8 * fStack_120;
          fStack_118 = fStack_ec * fStack_120 - fStack_e4 * fStack_128;
          fStack_114 = fStack_e8 * fStack_128 - fStack_ec * fStack_124;
          fStack_fc = fStack_114 * fStack_124 - fStack_118 * fStack_120;
          fStack_f8 = fStack_11c * fStack_120 - fStack_114 * fStack_128;
          *pfVar7 = fStack_11c;
          pfVar7[1] = fStack_118;
          pfVar7[2] = fStack_114;
          pfVar7[4] = fStack_128;
          pfVar7[5] = fStack_124;
          fStack_f4 = fStack_118 * fStack_128 - fStack_11c * fStack_124;
          pfVar7[6] = fStack_120;
          pfVar7[8] = fStack_fc;
          pfVar7[9] = fStack_f8;
          pfVar7[10] = fStack_f4;
        }
        if (*(byte *)(iVar4 + 0x36) != 0xff) {
          fVar1 = (float)*(byte *)(iVar4 + 0x36);
          *(float *)(iVar4 + 0x38) = fVar1 + fVar1;
        }
        if (*(float *)(iVar4 + 0x38) < DAT_00858b50) {
          fVar1 = *(float *)(iVar4 + 0x38);
          do {
            fVar1 = fVar1 + _DAT_00859e2c;
          } while (fVar1 < DAT_00858b50);
          *(float *)(iVar4 + 0x38) = fVar1;
        }
        if (_DAT_00859e2c <= *(float *)(iVar4 + 0x38)) {
          fVar1 = *(float *)(iVar4 + 0x38);
          do {
            fVar1 = fVar1 - _DAT_00859e2c;
          } while (_DAT_00859e2c <= fVar1);
          *(float *)(iVar4 + 0x38) = fVar1;
        }
        if (*(float *)(iVar4 + 0x38) <= DAT_00858b50) {
          fStack_11c = *pfVar7;
          fStack_118 = pfVar7[1];
          fStack_114 = pfVar7[2];
          fStack_128 = pfVar7[4];
          fStack_124 = pfVar7[5];
          fStack_120 = pfVar7[6];
        }
        else {
          FUN_004a1780(&fStack_11c,pfVar7,&fStack_fc,*(float *)(iVar4 + 0x38) * _DAT_0085a7bc);
          fStack_128 = fStack_f8 * fStack_114 - fStack_f4 * fStack_118;
          fStack_124 = fStack_f4 * fStack_11c - fStack_fc * fStack_114;
          fStack_120 = fStack_fc * fStack_118 - fStack_f8 * fStack_11c;
        }
        FUN_004a9460(pfVar7);
        fStack_98 = ((float)*(byte *)(iVar4 + 0x32) * _DAT_00859a3c - _DAT_00858b8c) * fStack_90 +
                    fStack_98;
        fStack_94 = ((float)*(byte *)(iVar4 + 0x33) * _DAT_00859a3c - _DAT_00858b8c) * fStack_8c +
                    fStack_94;
        if (*(byte *)(iVar4 + 0x30) != 0xff) {
          fStack_98 = (float)*(byte *)(iVar4 + 0x30) * _DAT_00859a3c * fStack_98;
          fStack_94 = (float)*(byte *)(iVar4 + 0x30) * _DAT_00859a3c * fStack_94;
        }
        uStack_a4 = 0;
        uStack_a3 = 0;
        uStack_a2 = 0;
        if ((cStack_70 == '\0') || (cStack_6f == '\x01')) {
          piVar8 = *(int **)(local_100 + 0xc);
LAB_004a1e8f:
          iStack_110 = *piVar8;
        }
        else if (cStack_6f == '\x02') {
          if (*(int **)(local_100 + 0x10) == (int *)0x0) {
LAB_004a1e83:
            piVar8 = *(int **)(local_100 + 0xc);
            goto LAB_004a1e8f;
          }
          iStack_110 = **(int **)(local_100 + 0x10);
        }
        else if (cStack_6f == '\x03') {
          if (*(int **)(local_100 + 0x14) == (int *)0x0) goto LAB_004a1e83;
          iStack_110 = **(int **)(local_100 + 0x14);
        }
        else if (cStack_6f == '\x04') {
          if (*(int **)(local_100 + 0x18) == (int *)0x0) goto LAB_004a1e83;
          iStack_110 = **(int **)(local_100 + 0x18);
        }
        iVar5 = iStack_110;
        if (local_e0 != iStack_110) {
          thunk_FUN_004059d7();
          local_e0 = iVar5;
          FUN_004a13b0(iVar5,0,1);
        }
        fVar1 = fStack_88 * fStack_94;
        fStack_bc = fStack_84 * fStack_94;
        fStack_c4 = fStack_128 * fStack_bc;
        fStack_c0 = fStack_124 * fStack_bc;
        fStack_bc = fStack_bc * fStack_120;
        fStack_cc = fStack_80 * fStack_98;
        fStack_d4 = fStack_11c * fStack_cc;
        fStack_d0 = fStack_118 * fStack_cc;
        fStack_cc = fStack_cc * fStack_114;
        fVar2 = fStack_7c * fStack_98;
        fStack_b0 = fStack_11c * fVar2;
        fStack_ac = fStack_118 * fVar2;
        fStack_c8 = fStack_bc + fVar2 * fStack_114;
        fStack_b4 = fStack_ac + fStack_c0;
        fVar3 = fStack_b0 + fStack_c4;
        fStack_b8 = fStack_cc + fVar1 * fStack_120;
        fStack_dc = fStack_d0 + fVar1 * fStack_124;
        fStack_d8 = fStack_d4 + fStack_128 * fVar1;
        FUN_004a1410(fStack_d8 + fStack_10c,fStack_108 + fStack_dc,fStack_104 + fStack_b8,
                     fVar3 + fStack_10c,fStack_108 + fStack_b4,fStack_104 + fStack_c8,
                     fStack_b0 + fStack_128 * fVar1 + fStack_10c,
                     fStack_ac + fVar1 * fStack_124 + fStack_108,
                     fVar2 * fStack_114 + fVar1 * fStack_120 + fStack_104,0,0,0x3f800000,0x3f800000,
                     0x3f800000,0,uStack_a4,uStack_a3,uStack_a2,uStack_a1,uStack_a4,uStack_a3,
                     uStack_a2,uStack_a1,uStack_a4,uStack_a3,uStack_a2,uStack_a1);
        FUN_004a1410(fVar3 + fStack_10c,fStack_108 + fStack_b4,fStack_104 + fStack_c8,
                     fStack_d8 + fStack_10c,fStack_108 + fStack_dc,fStack_104 + fStack_b8,
                     fStack_d4 + fStack_c4 + fStack_10c,fStack_d0 + fStack_c0 + fStack_108,
                     fStack_cc + fStack_bc + fStack_104,0x3f800000,0x3f800000,0,0,0,0x3f800000,
                     uStack_a4,uStack_a3,uStack_a2,uStack_a1,uStack_a4,uStack_a3,uStack_a2,uStack_a1
                     ,uStack_a4,uStack_a3,uStack_a2,uStack_a1);
      }
      thunk_FUN_004059d7();
    }
  }
  return;
}



/* entry 0x00534310; bounded CFG instructions=72; body bytes=222 */

void __fastcall FUN_00534310(int param_1)

{
  char *pcVar1;
  char cVar2;
  int local_4;
  
  if (*(char **)(param_1 + 0x18) != (char *)0x0) {
    if (**(char **)(param_1 + 0x18) == '\x01') {
      local_4 = param_1;
      cVar2 = FUN_0049cce0(param_1);
      if (cVar2 != '\0') {
        FUN_0049ce40(*(undefined4 *)(param_1 + 0x18));
        return;
      }
    }
    local_4 = 0;
    if (((int)*(short *)(param_1 + 0x22) == (uint)DAT_008cd644) ||
       ((int)*(short *)(param_1 + 0x22) == (uint)DAT_008cd648)) {
      (**(code **)(DAT_00c97b24 + 0x24))(0x1e,&local_4);
      (**(code **)(DAT_00c97b24 + 0x20))(0x1e,0);
    }
    pcVar1 = *(char **)(param_1 + 0x18);
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x2000;
    if (*pcVar1 == '\x01') {
      (**(code **)(pcVar1 + 0x48))();
    }
    else {
      FUN_00749b20(pcVar1);
    }
    thunk_FUN_0156d750(*(undefined4 *)(param_1 + 0x28));
    FUN_005342b0();
    if (((int)*(short *)(param_1 + 0x22) == (uint)DAT_008cd644) ||
       ((int)*(short *)(param_1 + 0x22) == (uint)DAT_008cd648)) {
      (**(code **)(DAT_00c97b24 + 0x20))(0x1e,local_4);
    }
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) & 0xffffdfff;
  }
  return;
}



/* entry 0x0053E230; bounded CFG instructions=160; body bytes=768 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0053e230(void)

{
  short sVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  undefined1 auStack_18 [4];
  int iStack_14;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  (**(code **)(DAT_00c97b24 + 0x20))(6,0);
  (**(code **)(DAT_00c97b24 + 0x20))(8,0);
  (**(code **)(DAT_00c97b24 + 0x20))(0xc,1);
  (**(code **)(DAT_00c97b24 + 0x20))(10,5);
  (**(code **)(DAT_00c97b24 + 0x20))(0xb,6);
  (**(code **)(DAT_00c97b24 + 0x20))(0xe,0);
  (**(code **)(DAT_00c97b24 + 0x20))(0x14,1);
  FUN_0045c210();
  FUN_0060f8c0();
  FUN_00455000();
  if ((DAT_00b6f065 != '\0') && (DAT_00ba6793 == '\0')) {
    FUN_00514860();
  }
  iVar3 = FUN_0056e210(0xffffffff);
  iVar4 = iStack_14;
  if (iVar3 != 0) {
    iVar4 = *(int *)(*(char *)(iVar3 + 0x718) * 0x1c + 0x5a0 + iVar3);
  }
  sVar1 = (&DAT_00b6f1a8)[(uint)DAT_00b6f081 * 0x11c];
  bVar2 = false;
  if (((((sVar1 == 7) || (sVar1 == 0x27)) || (sVar1 == 8)) || ((sVar1 == 0x28 || (sVar1 == 0x2e))))
     || (sVar1 == 0x2d)) {
    bVar2 = true;
  }
  if (((iVar4 == 0x22) || (iVar4 == 0x13)) && (bVar2)) {
    FUN_007170c0(0,0,0,0xff);
    fStack_8 = (float)DAT_00c17044;
    iStack_14 = DAT_00c17048 / 2;
    fStack_4 = 0.0;
    fStack_10 = 0.0;
    if (iVar4 == 0x13) {
      fStack_c = (float)iStack_14 - (float)DAT_00c17048 * _DAT_00859524 * _DAT_0085a994;
      thunk_FUN_00409737(&fStack_10,auStack_18);
      fStack_c = (float)DAT_00c17048;
      iStack_14 = DAT_00c17048 / 2;
      fStack_4 = _DAT_00859524 * fStack_c * _DAT_00858f98 + (float)iStack_14;
    }
    else {
      fStack_c = (float)iStack_14 - (float)DAT_00c17048 * _DAT_00859524 * _DAT_00863b34;
      thunk_FUN_00409737(&fStack_10,auStack_18);
      fStack_c = (float)DAT_00c17048;
      iStack_14 = DAT_00c17048 / 2;
      fStack_4 = _DAT_00859524 * fStack_c * _DAT_00863b34 + (float)iStack_14;
    }
    fStack_8 = (float)DAT_00c17044;
    fStack_10 = 0.0;
    thunk_FUN_00409737(&fStack_10,auStack_18);
    iStack_14 = DAT_00c17044 / 2;
    fStack_10 = 0.0;
    fStack_4 = 0.0;
    fStack_8 = (float)iStack_14 - (float)DAT_00c17044 * _DAT_00859520 * _DAT_00863b34;
    fStack_c = (float)DAT_00c17048;
    thunk_FUN_00409737(&fStack_10,auStack_18);
    fStack_8 = (float)DAT_00c17044;
    iStack_14 = DAT_00c17044 / 2;
    fStack_10 = _DAT_00859520 * fStack_8 * _DAT_00863b34 + (float)iStack_14;
    fStack_4 = 0.0;
    fStack_c = (float)DAT_00c17048;
    thunk_FUN_00409737(&fStack_10,auStack_18);
  }
  FUN_00507030();
  FUN_0058fae0();
  FUN_00721660();
  thunk_FUN_01569fd0();
  FUN_0069efc0(1);
  FUN_0043cec0();
  FUN_00447790();
  thunk_FUN_00719840();
  return;
}



/* entry 0x00553A10; bounded CFG instructions=49; body bytes=144 */

void FUN_00553a10(void)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  
  (**(code **)(DAT_00c97b24 + 0x20))(0xe,1);
  (**(code **)(DAT_00c97b24 + 0x20))(0xc,1);
  (**(code **)(DAT_00c97b24 + 0x20))(0x14,2);
  thunk_FUN_00405bcf();
  FUN_00735d30();
  iVar3 = 0;
  if (0 < DAT_00b76844) {
    do {
      piVar1 = (int *)(&DAT_00b75898)[iVar3];
      if (((*(byte *)((int)piVar1 + 0x36) & 7) == 1) &&
         ((*(byte *)((&DAT_00a9b0c8)[*(short *)((int)piVar1 + 0x22)] + 0x13) & 1) != 0)) {
        cVar2 = FUN_007034f0();
        if (cVar2 == '\0') {
          (**(code **)(*piVar1 + 0x48))();
        }
        else {
          thunk_FUN_007034b5();
          (**(code **)(*piVar1 + 0x48))();
          FUN_007034d0();
        }
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < DAT_00b76844);
  }
  return;
}



/* entry 0x00553AA0; bounded CFG instructions=160; body bytes=592 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00553aa0(undefined4 param_1)

{
  int iVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  float *pfVar5;
  int iVar6;
  undefined4 uVar7;
  
  (**(code **)(DAT_00c97b24 + 0x20))(0xe,1,param_1);
  (**(code **)(DAT_00c97b24 + 0x20))(0xc,1);
  (**(code **)(DAT_00c97b24 + 0x20))(0x14,2);
  if (DAT_00b72914 == 0) {
    (**(code **)(DAT_00c97b24 + 0x20))(0x1e,0x8c);
  }
  iVar6 = 0;
  if (0 < DAT_00b76844) {
    do {
      iVar1 = (&DAT_00b75898)[iVar6];
      bVar2 = *(byte *)(iVar1 + 0x36) & 7;
      if ((bVar2 != 1) || ((*(byte *)((&DAT_00a9b0c8)[*(short *)(iVar1 + 0x22)] + 0x13) & 1) == 0))
      {
        if ((bVar2 == 2) ||
           ((bVar2 == 3 && (iVar4 = FUN_00732b20(*(undefined4 *)(iVar1 + 0x18)), iVar4 != 0xff)))) {
          if ((*(byte *)(iVar1 + 0x36) & 7) == 2) {
            if (*(int *)(iVar1 + 0x590) == 5) {
              if ((((&DAT_00b6f1a8)[(uint)DAT_00b6f081 * 0x11c] == 0xe) ||
                  ((((&DAT_00b6f1a8)[(uint)DAT_00b6f081 * 0x11c] == 0x10 &&
                    (iVar4 = FUN_0050ae90(), iVar4 != 3)) && (iVar4 = FUN_0050ae90(), iVar4 != 0))))
                 || (iVar4 = FUN_00732b20(*(undefined4 *)(iVar1 + 0x18)), iVar4 != 0xff))
              goto LAB_00553ba9;
            }
            else if ((*(uint *)(iVar1 + 0x40) & 0x8000000) == 0) goto LAB_00553ba9;
            if (*(int *)(iVar1 + 0x14) == 0) {
              pfVar5 = (float *)(iVar1 + 4);
            }
            else {
              pfVar5 = (float *)(*(int *)(iVar1 + 0x14) + 0x30);
            }
            cVar3 = FUN_00733d90(iVar1,SQRT((_DAT_00b76874 - pfVar5[1]) *
                                            (_DAT_00b76874 - pfVar5[1]) +
                                            (_DAT_00b76870 - *pfVar5) * (_DAT_00b76870 - *pfVar5) +
                                            (_DAT_00b76878 - pfVar5[2]) *
                                            (_DAT_00b76878 - pfVar5[2])));
          }
          else {
LAB_00553ba9:
            if (*(int *)(iVar1 + 0x14) == 0) {
              pfVar5 = (float *)(iVar1 + 4);
            }
            else {
              pfVar5 = (float *)(*(int *)(iVar1 + 0x14) + 0x30);
            }
            cVar3 = FUN_00734570(iVar1,SQRT((_DAT_00b76870 - *pfVar5) * (_DAT_00b76870 - *pfVar5) +
                                            (_DAT_00b76874 - pfVar5[1]) *
                                            (_DAT_00b76874 - pfVar5[1]) +
                                            (_DAT_00b76878 - pfVar5[2]) *
                                            (_DAT_00b76878 - pfVar5[2])));
          }
          if (cVar3 != '\0') goto LAB_00553c5a;
        }
        FUN_00553260(iVar1);
      }
LAB_00553c5a:
      iVar6 = iVar6 + 1;
    } while (iVar6 < DAT_00b76844);
  }
  uVar7 = *(undefined4 *)(DAT_00c1703c + 0x90);
  FUN_007ee180(DAT_00c1703c);
  *(float *)(DAT_00c1703c + 0x90) = _DAT_008cd814 + *(float *)(DAT_00c1703c + 0x90);
  FUN_007ee190(DAT_00c1703c);
  iVar6 = 0;
  if (0 < DAT_00b76840) {
    do {
      FUN_00553260((&DAT_00b748f8)[iVar6]);
      iVar6 = iVar6 + 1;
    } while (iVar6 < DAT_00b76840);
  }
  FUN_007ee180(DAT_00c1703c);
  *(undefined4 *)(DAT_00c1703c + 0x90) = uVar7;
  FUN_007ee190(DAT_00c1703c);
  return;
}



/* entry 0x00553D00; bounded CFG instructions=58; body bytes=187 */

void FUN_00553d00(void)

{
  bool bVar1;
  
  if (DAT_00b745d4 != 0) {
    bVar1 = *(int *)(*(char *)(DAT_00b7cd98 + 0x718) * 0x1c + 0x5a0 + DAT_00b7cd98) == 0x1c;
    if (bVar1) {
      (**(code **)(DAT_00c97b24 + 0x20))(0x1e,0x50);
    }
    (**(code **)(DAT_00c97b24 + 0x20))(0xe,1);
    (**(code **)(DAT_00c97b24 + 0x20))(8,1);
    (**(code **)(DAT_00c97b24 + 0x20))(6,1);
    (**(code **)(DAT_00c97b24 + 0x20))(0xc,1);
    (**(code **)(DAT_00c97b24 + 0x20))(10,5);
    (**(code **)(DAT_00c97b24 + 0x20))(0xb,6);
    FUN_00553260(DAT_00b745d4);
    (**(code **)(DAT_00c97b24 + 0x20))(0xe,0);
    if (bVar1) {
      (**(code **)(DAT_00c97b24 + 0x20))(0x1e,0);
    }
  }
  return;
}



/* entry 0x00579FA4; bounded CFG instructions=160; body bytes=4760 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00579fa4(void)

{
  float fVar1;
  char cVar2;
  undefined4 *puVar3;
  uint uVar4;
  void *_Memory;
  undefined1 *puVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  char *unaff_EBX;
  int unaff_EBP;
  char *pcVar9;
  bool in_ZF;
  bool bVar10;
  ushort uVar11;
  float10 fVar12;
  int in_stack_00000010;
  short sStack00000014;
  undefined4 in_stack_00000018;
  char *in_stack_0000001c;
  short in_stack_00000020;
  int in_stack_00000024;
  float fStack00000028;
  int in_stack_00000030;
  float fStack00000034;
  float fStack00000038;
  float fStack0000003c;
  float fStack00000040;
  float fStack00000044;
  float fStack0000004c;
  float fStack00000054;
  float fStack00000058;
  float fStack0000005c;
  float fStack00000060;
  float fStack00000064;
  float fStack00000068;
  float fStack0000006c;
  float fStack00000070;
  float fStack00000074;
  float fStack00000078;
  float fStack0000007c;
  float fStack00000080;
  float fStack00000084;
  float fStack00000088;
  float fStack0000008c;
  float fStack00000090;
  float fStack00000094;
  float fStack00000098;
  float fStack0000009c;
  float fStack000000a0;
  float fStack000000a4;
  float fStack000000a8;
  float fStack000000ac;
  float fStack000000b0;
  float fStack000000b4;
  float fStack000000b8;
  float fStack000000bc;
  float in_stack_000000c0;
  float in_stack_000000c4;
  float in_stack_000000c8;
  float in_stack_000000cc;
  char in_stack_000000f0;
  char *pcVar13;
  
  if (in_ZF) goto LAB_00579f65;
LAB_00579fa6:
  pcVar13 = "FEM_ON";
LAB_0057a161:
  puVar5 = (undefined1 *)FUN_006a0050(pcVar13);
switchD_00579daa_caseD_1b:
  if (unaff_EBX != (char *)0x0) {
    iVar6 = *(char *)(unaff_EBP + 0x15d) * 0xe2;
    if (DAT_00c17048 == 0x1c0) {
      fStack00000034 = (float)(int)*(short *)(&DAT_008ce020 + in_stack_00000010 + iVar6);
    }
    else {
      fStack00000034 =
           (float)DAT_00c17048 * (float)(int)*(short *)(&DAT_008ce020 + in_stack_00000010 + iVar6) *
           _DAT_00859524;
    }
    if (DAT_00c17044 == 0x280) {
      _sStack00000014 = (float)(int)*(short *)(&DAT_008ce01e + iVar6 + in_stack_00000010);
    }
    else {
      _sStack00000014 =
           (float)DAT_00c17044 * (float)(int)*(short *)(&DAT_008ce01e + iVar6 + in_stack_00000010) *
           _DAT_00859520;
    }
    FUN_0071a700(_sStack00000014,fStack00000034,unaff_EBX);
  }
  if (puVar5 != (undefined1 *)0x0) {
    FUN_00719490(2);
    FUN_00719590(1);
    FUN_00719610(2);
    if (((char)(&DAT_008ce01b)[in_stack_00000010 + *(char *)(unaff_EBP + 0x15d) * 0xe2] < '\x01') ||
       ('\b' < (char)(&DAT_008ce01b)[in_stack_00000010 + *(char *)(unaff_EBP + 0x15d) * 0xe2])) {
      if ((*(char *)(unaff_EBP + 0x15d) == '\x03') && (in_stack_00000024 == 5)) {
        if (DAT_00c17048 == 0x1c0) {
          fStack00000098 = 1.0;
        }
        else {
          fStack00000098 = (float)DAT_00c17048 * _DAT_00859524;
        }
        fStack000000b0 = fStack00000098;
        if (DAT_00c17044 == 0x280) {
          fStack00000058 = 0.56;
        }
        else {
          fStack00000058 = (float)DAT_00c17044 * _DAT_008652a8;
        }
      }
      else {
        if (DAT_00c17048 == 0x1c0) {
          fStack000000b8 = 1.0;
        }
        else {
          fStack000000b8 = (float)DAT_00c17048 * _DAT_00859524;
        }
        fStack000000b0 = fStack000000b8;
        if (DAT_00c17044 == 0x280) {
          fStack00000058 = 0.7;
        }
        else {
          fStack00000058 = (float)DAT_00c17044 * _DAT_00865434;
        }
      }
    }
    else {
      if (DAT_00c17048 == 0x1c0) {
        fStack000000b0 = 0.95;
      }
      else {
        fStack000000b0 = (float)DAT_00c17048 * _DAT_00865514;
      }
      if (DAT_00c17044 == 0x280) {
        fStack00000058 = 0.35;
      }
      else {
        fStack00000058 = (float)DAT_00c17044 * _DAT_00865464;
      }
    }
    FUN_00719380(fStack00000058,fStack000000b0);
    if (DAT_00c17048 == 0x1c0) {
      _sStack00000014 =
           (float)(int)*(short *)(&DAT_008ce020 +
                                 in_stack_00000010 + *(char *)(unaff_EBP + 0x15d) * 0xe2);
    }
    else {
      _sStack00000014 =
           (float)DAT_00c17048 *
           (float)(int)*(short *)(&DAT_008ce020 +
                                 in_stack_00000010 + *(char *)(unaff_EBP + 0x15d) * 0xe2) *
           _DAT_00859524;
    }
    fVar1 = _DAT_00858a10;
    if (DAT_00c17044 != 0x280) {
      fVar1 = (float)DAT_00c17044 * _DAT_00858620;
    }
    FUN_0071a700((float)DAT_00c17044 - fVar1,_sStack00000014,puVar5);
  }
  if ((((unaff_EBX != (char *)0x0) && (in_stack_00000024 == *(int *)(unaff_EBP + 0x54))) &&
      (cVar2 = *(char *)(unaff_EBP + 0x15d), cVar2 != '\x05')) && (cVar2 != '\x02')) {
    if (in_stack_00000020 == 0) {
      if ((&DAT_008ce022)[cVar2 * 0xe2 + in_stack_00000010] == '\x01') {
        thunk_FUN_005733ea(0x42200000);
      }
      else if ((&DAT_008ce022)[cVar2 * 0xe2 + in_stack_00000010] == '\x02') {
        thunk_FUN_005733ea(0x42200000);
      }
      else {
        thunk_FUN_005733ea(0x42200000);
        thunk_FUN_004016b9(unaff_EBX,1,0);
      }
      in_stack_00000020 = FUN_00821b40();
    }
    if (((*(char *)(unaff_EBP + 0x78) != '\0') &&
        (cVar2 = *(char *)(unaff_EBP + 0x15d), cVar2 != '\r')) &&
       ((cVar2 != '\x0e' && (cVar2 != '\x12')))) {
      in_stack_000000c0 = (float)(int)in_stack_00000020;
      fVar1 = (float)DAT_00c17048 * _DAT_00859524 *
              (float)(int)*(short *)(&DAT_008ce020 + in_stack_00000010 + cVar2 * 0xe2);
      fVar12 = (float10)thunk_FUN_005733ea(0x40a00000);
      in_stack_000000cc = (float)((float10)fVar1 - fVar12);
      fVar12 = (float10)thunk_FUN_005733ea(0x42000000);
      in_stack_000000c8 = (float)(fVar12 + (float10)(int)in_stack_00000020);
      fVar12 = (float10)thunk_FUN_005733ea(0x423c0000);
      in_stack_000000c4 = (float)(fVar12 + (float10)fVar1);
      uVar7 = FUN_007170c0(0xff,0xff,0xff,0xff);
      FUN_00728350(&stack0x000000c0,uVar7);
    }
  }
  if (*(int *)(unaff_EBP + 0xd8) == *(int *)(unaff_EBP + 0xd4)) {
    iVar6 = 8;
    bVar10 = true;
    pcVar13 = s_FES_PLA_008ce013 +
              *(int *)(unaff_EBP + 0x54) * 0x12 + *(char *)(unaff_EBP + 0x15d) * 0xe2;
    pcVar9 = "FED_RES";
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      bVar10 = *pcVar13 == *pcVar9;
      pcVar13 = pcVar13 + 1;
      pcVar9 = pcVar9 + 1;
    } while (bVar10);
    if ((bVar10) && (*(int *)(unaff_EBP + 0x1b18) == 1)) {
      FUN_0057cd30();
    }
  }
  if (*(int *)(unaff_EBP + 0xcc) == *(int *)(unaff_EBP + 200)) {
    iVar6 = 8;
    bVar10 = true;
    pcVar13 = s_FES_PLA_008ce013 +
              *(int *)(unaff_EBP + 0x54) * 0x12 + *(char *)(unaff_EBP + 0x15d) * 0xe2;
    pcVar9 = "FED_AAS";
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      bVar10 = *pcVar13 == *pcVar9;
      pcVar13 = pcVar13 + 1;
      pcVar9 = pcVar9 + 1;
    } while (bVar10);
    if ((bVar10) && (*(int *)(unaff_EBP + 0x1b18) == 1)) {
      FUN_0057cd30();
    }
  }
  if (*(int *)(unaff_EBP + 0xd8) != *(int *)(unaff_EBP + 0xd4)) {
    iVar6 = 8;
    bVar10 = true;
    pcVar13 = s_FES_PLA_008ce013 +
              *(int *)(unaff_EBP + 0x54) * 0x12 + *(char *)(unaff_EBP + 0x15d) * 0xe2;
    pcVar9 = "FED_RES";
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      bVar10 = *pcVar13 == *pcVar9;
      pcVar13 = pcVar13 + 1;
      pcVar9 = pcVar9 + 1;
    } while (bVar10);
    if (bVar10) {
      FUN_0057cd10(1);
    }
  }
  if (*(int *)(unaff_EBP + 0xcc) != *(int *)(unaff_EBP + 200)) {
    iVar6 = 8;
    bVar10 = true;
    pcVar13 = s_FES_PLA_008ce013 +
              *(int *)(unaff_EBP + 0x54) * 0x12 + *(char *)(unaff_EBP + 0x15d) * 0xe2;
    pcVar9 = "FED_AAS";
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      bVar10 = *pcVar13 == *pcVar9;
      pcVar13 = pcVar13 + 1;
      pcVar9 = pcVar9 + 1;
    } while (bVar10);
    if (bVar10) {
      FUN_0057cd10(1);
    }
  }
  if (*(int *)(unaff_EBP + 0xcc) != *(int *)(unaff_EBP + 200)) {
    cVar2 = *(char *)(unaff_EBP + 0x15d);
    iVar6 = 8;
    bVar10 = true;
    pcVar13 = s_FES_PLA_008ce013 + *(int *)(unaff_EBP + 0x54) * 0x12 + cVar2 * 0xe2;
    pcVar9 = "FED_AAS";
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      bVar10 = *pcVar13 == *pcVar9;
      pcVar13 = pcVar13 + 1;
      pcVar9 = pcVar9 + 1;
    } while (bVar10);
    if ((!bVar10) && ((cVar2 == '\x04' || (cVar2 == '\x1b')))) {
      *(int *)(unaff_EBP + 0xcc) = *(int *)(unaff_EBP + 200);
      FUN_0057cd10(3);
    }
  }
  if (*(int *)(unaff_EBP + 0xd8) != *(int *)(unaff_EBP + 0xd4)) {
    cVar2 = *(char *)(unaff_EBP + 0x15d);
    iVar6 = 8;
    bVar10 = true;
    pcVar13 = s_FES_PLA_008ce013 + *(int *)(unaff_EBP + 0x54) * 0x12 + cVar2 * 0xe2;
    pcVar9 = "FED_RES";
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      bVar10 = *pcVar13 == *pcVar9;
      pcVar13 = pcVar13 + 1;
      pcVar9 = pcVar9 + 1;
    } while (bVar10);
    if ((!bVar10) && ((cVar2 == '\x04' || (cVar2 == '\x1b')))) {
      *(int *)(unaff_EBP + 0xd8) = *(int *)(unaff_EBP + 0xd4);
      FUN_0057cd10(3);
    }
  }
  switch((&DAT_008ce012)[in_stack_00000010 + *(char *)(unaff_EBP + 0x15d) * 0xe2]) {
  case 0x1b:
    if (DAT_00c17044 == 0x280) {
      fStack000000bc = 100.0;
    }
    else {
      fStack000000bc = (float)DAT_00c17044 * _DAT_0086544c;
    }
    if (DAT_00c17048 == 0x1c0) {
      fStack00000060 = 20.0;
      fStack000000a4 = 4.0;
      fStack00000068 = 125.0;
    }
    else {
      fStack00000068 = (float)DAT_00c17048;
      fStack00000060 = _DAT_00865448 * fStack00000068;
      fStack000000a4 = _DAT_00865358 * fStack00000068;
      fStack00000068 = fStack00000068 * _DAT_00865294;
    }
    if (DAT_00c17044 == 0x280) {
      fStack000000b4 = 500.0;
    }
    else {
      fStack000000b4 = (float)DAT_00c17044 * _DAT_00865444;
    }
    uVar7 = FUN_00821b40();
    FUN_00576860(fStack000000b4,fStack00000068,fStack000000a4,fStack00000060,fStack000000bc,
                 (float)*(int *)(unaff_EBP + 0x3c) * _DAT_00865440,uVar7);
    if ((in_stack_00000024 == *(int *)(unaff_EBP + 0x54)) && (in_stack_00000018._3_1_ != '\0')) {
      FUN_00573410(0x43160000);
      uVar7 = FUN_00821b40();
      FUN_00573410(0x42fa0000);
      uVar7 = FUN_00821b40(uVar7);
      thunk_FUN_005733ea(0x40400000);
      uVar7 = FUN_00821b40(uVar7);
      cVar2 = thunk_FUN_0040178c(0,uVar7);
      if (cVar2 == '\0') {
        FUN_00573410(0x43160000);
        uVar7 = FUN_00821b40();
        FUN_00573410(0x42fa0000);
        uVar7 = FUN_00821b40(uVar7);
        thunk_FUN_005733ea((float)DAT_00c17044);
        uVar7 = FUN_00821b40(uVar7);
        thunk_FUN_005733ea(0x40400000);
        uVar7 = FUN_00821b40(uVar7);
        cVar2 = thunk_FUN_0040178c(uVar7);
        if (cVar2 != '\0') {
          iVar6 = *(int *)(unaff_EBP + 0xbc);
          *(undefined4 *)(unaff_EBP + 0x1b00) = 6;
          fVar12 = (float10)thunk_FUN_005733ea(0x43fa0000);
          uVar11 = (ushort)(fVar12 < (float10)iVar6) << 8 |
                   (ushort)(fVar12 == (float10)iVar6) << 0xe;
LAB_0057aff2:
          if (uVar11 != 0) {
            iVar6 = *(int *)(unaff_EBP + 0xc0);
            fVar12 = (float10)FUN_00573410(0x42fa0000);
            if (fVar12 <= (float10)iVar6) {
              uVar7 = 0x43160000;
LAB_0057b027:
              fVar12 = (float10)FUN_00573410(uVar7);
              if ((float10)iVar6 <= fVar12) break;
            }
          }
        }
        goto LAB_0057b229;
      }
      *(undefined4 *)(unaff_EBP + 0x1b00) = 7;
    }
    break;
  case 0x1c:
    if (DAT_00c17044 == 0x280) {
      fStack00000070 = 100.0;
    }
    else {
      fStack00000070 = (float)DAT_00c17044 * _DAT_0086544c;
    }
    if (DAT_00c17048 == 0x1c0) {
      fStack000000ac = 20.0;
      fStack00000078 = 4.0;
      fStack00000038 = 95.0;
    }
    else {
      fStack00000038 = (float)DAT_00c17048;
      fStack000000ac = _DAT_00865448 * fStack00000038;
      fStack00000078 = _DAT_00865358 * fStack00000038;
      fStack00000038 = fStack00000038 * _DAT_0086543c;
    }
    if (DAT_00c17044 == 0x280) {
      fStack00000080 = 500.0;
    }
    else {
      fStack00000080 = (float)DAT_00c17044 * _DAT_00865444;
    }
    uVar7 = FUN_00821b40();
    FUN_00576860(fStack00000080,fStack00000038,fStack00000078,fStack000000ac,fStack00000070,
                 (float)(int)*(char *)(unaff_EBP + 0x50) * _DAT_0085a7d4,uVar7);
    if ((in_stack_00000024 == *(int *)(unaff_EBP + 0x54)) && (in_stack_00000018._3_1_ != '\0')) {
      FUN_00573410(0x42f00000);
      uVar7 = FUN_00821b40();
      FUN_00573410(0x42be0000);
      uVar7 = FUN_00821b40(uVar7);
      thunk_FUN_005733ea(0x40400000);
      uVar7 = FUN_00821b40(uVar7);
      cVar2 = thunk_FUN_0040178c(0,uVar7);
      if (cVar2 == '\0') {
        FUN_00573410(0x42f00000);
        uVar7 = FUN_00821b40();
        FUN_00573410(0x42be0000);
        uVar7 = FUN_00821b40(uVar7);
        thunk_FUN_005733ea((float)DAT_00c17044);
        uVar7 = FUN_00821b40(uVar7);
        thunk_FUN_005733ea(0x40400000);
        uVar7 = FUN_00821b40(uVar7);
        cVar2 = thunk_FUN_0040178c(uVar7);
        if (cVar2 != '\0') {
          iVar6 = *(int *)(unaff_EBP + 0xbc);
          *(undefined4 *)(unaff_EBP + 0x1b00) = 10;
          fVar12 = (float10)thunk_FUN_005733ea(0x43fa0000);
          if (fVar12 <= (float10)iVar6) {
            iVar6 = *(int *)(unaff_EBP + 0xc0);
            fVar12 = (float10)FUN_00573410(0x42be0000);
            if (fVar12 <= (float10)iVar6) {
              uVar7 = 0x42f00000;
              goto LAB_0057b027;
            }
          }
        }
        goto LAB_0057b229;
      }
      *(undefined4 *)(unaff_EBP + 0x1b00) = 0xb;
    }
    break;
  case 0x1d:
    if (DAT_00c17044 == 0x280) {
      fStack000000a0 = 100.0;
    }
    else {
      fStack000000a0 = (float)DAT_00c17044 * _DAT_0086544c;
    }
    if (DAT_00c17048 == 0x1c0) {
      fStack00000088 = 20.0;
      fStack000000a8 = 4.0;
      fStack00000090 = 125.0;
    }
    else {
      fStack00000090 = (float)DAT_00c17048;
      fStack00000088 = _DAT_00865448 * fStack00000090;
      fStack000000a8 = _DAT_00865358 * fStack00000090;
      fStack00000090 = fStack00000090 * _DAT_00865294;
    }
    if (DAT_00c17044 == 0x280) {
      fStack0000003c = 500.0;
    }
    else {
      fStack0000003c = (float)DAT_00c17044 * _DAT_00865444;
    }
    uVar7 = FUN_00821b40();
    FUN_00576860(fStack0000003c,fStack00000090,fStack000000a8,fStack00000088,fStack000000a0,
                 (float)(int)*(char *)(unaff_EBP + 0x4f) * _DAT_0085a7d4,uVar7);
    if ((in_stack_00000024 == *(int *)(unaff_EBP + 0x54)) && (in_stack_00000018._3_1_ != '\0')) {
      FUN_00573410(0x43160000);
      uVar7 = FUN_00821b40();
      FUN_00573410(0x42fa0000);
      uVar7 = FUN_00821b40(uVar7);
      thunk_FUN_005733ea(0x40400000);
      uVar7 = FUN_00821b40(uVar7);
      cVar2 = thunk_FUN_0040178c(0,uVar7);
      if (cVar2 == '\0') {
        FUN_00573410(0x43160000);
        uVar7 = FUN_00821b40();
        FUN_00573410(0x42fa0000);
        uVar7 = FUN_00821b40(uVar7);
        thunk_FUN_005733ea((float)DAT_00c17044);
        uVar7 = FUN_00821b40(uVar7);
        thunk_FUN_005733ea(0x40400000);
        uVar7 = FUN_00821b40(uVar7);
        cVar2 = thunk_FUN_0040178c(uVar7);
        if (cVar2 != '\0') {
          iVar6 = *(int *)(unaff_EBP + 0xbc);
          *(undefined4 *)(unaff_EBP + 0x1b00) = 0xc;
          fVar12 = (float10)thunk_FUN_005733ea(0x43fa0000);
          uVar11 = (ushort)(fVar12 < (float10)iVar6) << 8 |
                   (ushort)(fVar12 == (float10)iVar6) << 0xe;
          goto LAB_0057aff2;
        }
        goto LAB_0057b229;
      }
      *(undefined4 *)(unaff_EBP + 0x1b00) = 0xd;
    }
    break;
  case 0x3d:
    if (DAT_00c17044 == 0x280) {
      fStack00000044 = 100.0;
    }
    else {
      fStack00000044 = (float)DAT_00c17044 * _DAT_0086544c;
    }
    if (DAT_00c17048 == 0x1c0) {
      fStack0000004c = 20.0;
      fStack00000054 = 4.0;
      fStack0000005c = 125.0;
    }
    else {
      fStack0000005c = (float)DAT_00c17048;
      fStack0000004c = _DAT_00865448 * fStack0000005c;
      fStack00000054 = _DAT_00865358 * fStack0000005c;
      fStack0000005c = fStack0000005c * _DAT_00865294;
    }
    if (DAT_00c17044 == 0x280) {
      fStack00000064 = 500.0;
    }
    else {
      fStack00000064 = (float)DAT_00c17044 * _DAT_00865444;
    }
    uVar7 = FUN_00821b40();
    FUN_00576860(fStack00000064,fStack0000005c,fStack00000054,fStack0000004c,fStack00000044,
                 (*(float *)(unaff_EBP + 0x40) - _DAT_0086524c) * _DAT_00865438,uVar7);
    if ((in_stack_00000024 == *(int *)(unaff_EBP + 0x54)) && (in_stack_00000018._3_1_ != '\0')) {
      FUN_00573410(0x43160000);
      uVar7 = FUN_00821b40();
      FUN_00573410(0x42fa0000);
      uVar7 = FUN_00821b40(uVar7);
      thunk_FUN_005733ea(0x40400000);
      uVar7 = FUN_00821b40(uVar7);
      cVar2 = thunk_FUN_0040178c(0,uVar7);
      if (cVar2 == '\0') {
        FUN_00573410(0x43160000);
        uVar7 = FUN_00821b40();
        FUN_00573410(0x42fa0000);
        uVar7 = FUN_00821b40(uVar7);
        thunk_FUN_005733ea((float)DAT_00c17044);
        uVar7 = FUN_00821b40(uVar7);
        thunk_FUN_005733ea(0x40400000);
        uVar7 = FUN_00821b40(uVar7);
        cVar2 = thunk_FUN_0040178c(uVar7);
        if (cVar2 != '\0') {
          iVar6 = *(int *)(unaff_EBP + 0xbc);
          *(undefined4 *)(unaff_EBP + 0x1b00) = 8;
          fVar12 = (float10)thunk_FUN_005733ea(0x43fa0000);
          uVar11 = (ushort)(fVar12 < (float10)iVar6) << 8 |
                   (ushort)(fVar12 == (float10)iVar6) << 0xe;
          goto LAB_0057aff2;
        }
        goto LAB_0057b229;
      }
      *(undefined4 *)(unaff_EBP + 0x1b00) = 9;
    }
    break;
  case 0x3e:
    if (DAT_00c17044 == 0x280) {
      fStack0000006c = 100.0;
    }
    else {
      fStack0000006c = (float)DAT_00c17044 * _DAT_0086544c;
    }
    if (DAT_00c17048 == 0x1c0) {
      fStack00000074 = 20.0;
      fStack0000007c = 4.0;
      fStack00000084 = 125.0;
    }
    else {
      fStack00000084 = (float)DAT_00c17048;
      fStack00000074 = _DAT_00865448 * fStack00000084;
      fStack0000007c = _DAT_00865358 * fStack00000084;
      fStack00000084 = fStack00000084 * _DAT_00865294;
    }
    if (DAT_00c17044 == 0x280) {
      fStack00000028 = 500.0;
    }
    else {
      fStack00000028 = (float)DAT_00c17044 * _DAT_00865444;
    }
    uVar7 = FUN_00821b40();
    FUN_00576860(fStack00000028,fStack00000084,fStack0000007c,fStack00000074,fStack0000006c,
                 _DAT_00b6ec1c / DAT_008651a8,uVar7);
    if ((in_stack_00000024 == *(int *)(unaff_EBP + 0x54)) && (in_stack_00000018._3_1_ != '\0')) {
      FUN_00573410(0x43160000);
      uVar7 = FUN_00821b40();
      FUN_00573410(0x42fa0000);
      uVar7 = FUN_00821b40(uVar7);
      thunk_FUN_005733ea(0x40400000);
      uVar7 = FUN_00821b40(uVar7);
      cVar2 = thunk_FUN_0040178c(0,uVar7);
      if (cVar2 == '\0') {
        FUN_00573410(0x43160000);
        uVar7 = FUN_00821b40();
        FUN_00573410(0x42fa0000);
        uVar7 = FUN_00821b40(uVar7);
        thunk_FUN_005733ea((float)DAT_00c17044);
        uVar7 = FUN_00821b40(uVar7);
        thunk_FUN_005733ea(0x40400000);
        uVar7 = FUN_00821b40(uVar7);
        cVar2 = thunk_FUN_0040178c(uVar7);
        if (cVar2 != '\0') {
          iVar6 = *(int *)(unaff_EBP + 0xbc);
          *(undefined4 *)(unaff_EBP + 0x1b00) = 0xe;
          fVar12 = (float10)thunk_FUN_005733ea(0x43fa0000);
          if (fVar12 <= (float10)iVar6) break;
        }
LAB_0057b229:
        *(undefined4 *)(unaff_EBP + 0x1b00) = 0x10;
      }
      else {
        *(undefined4 *)(unaff_EBP + 0x1b00) = 0xf;
      }
    }
  }
  if (in_stack_0000001c != (char *)0x0) {
    FUN_00409b33(in_stack_0000001c);
    return;
  }
  iVar8 = *(char *)(unaff_EBP + 0x15d) * 0xe2;
  iVar6 = in_stack_00000024;
  do {
    in_stack_00000024 = iVar6;
    iVar6 = in_stack_00000024 + 1;
    if (0xb < iVar6) {
      switch(*(undefined1 *)(unaff_EBP + 0x15d)) {
      case 0:
      case 3:
      case 4:
      case 0x1a:
      case 0x1b:
      case 0x24:
      case 0x27:
      case 0x28:
        FUN_0057e240(0);
      }
      return;
    }
    in_stack_00000010 = iVar6 * 0x12;
    cVar2 = (&DAT_008ce01b)[iVar8 + in_stack_00000010];
    puVar5 = (undefined1 *)0x0;
    sStack00000014 = ((cVar2 == '\t') - 1 & 10) + 0x14;
    if ((cVar2 < '\x01') || ('\b' < cVar2)) {
      FUN_00719490(2);
      if (DAT_00c17048 == 0x1c0) {
        fStack0000009c = 1.0;
      }
      else {
        fStack0000009c = (float)DAT_00c17048 * _DAT_00859524;
      }
      if (DAT_00c17044 == 0x280) {
        fStack0000008c = 0.7;
      }
      else {
        fStack0000008c = (float)DAT_00c17044 * _DAT_00865434;
      }
      FUN_00719380(fStack0000008c,fStack0000009c);
      FUN_00719590(2);
    }
    else {
      FUN_00719490(2);
      FUN_00719590(1);
      if (DAT_00c17048 == 0x1c0) {
        fStack00000094 = 0.95;
      }
      else {
        fStack00000094 = (float)DAT_00c17048 * _DAT_00865514;
      }
      if (DAT_00c17044 == 0x280) {
        fStack00000040 = 0.42000002;
      }
      else {
        fStack00000040 = (float)DAT_00c17044 * _DAT_00865510;
      }
      FUN_00719380(fStack00000040,fStack00000094);
    }
    puVar3 = (undefined4 *)FUN_007170c0(0,0,0,0xff);
    FUN_00719510(*puVar3);
    if ((iVar6 == *(int *)(unaff_EBP + 0x54)) && (*(char *)(unaff_EBP + 0x78) != '\0')) {
      puVar3 = (undefined4 *)FUN_007170c0(0xac,0xcb,0xf1,0xff);
      uVar7 = *puVar3;
    }
    else {
      puVar3 = (undefined4 *)FUN_007170c0(0x4a,0x5a,0x6b,0xff);
      uVar7 = *puVar3;
    }
    FUN_00719430(uVar7);
    if ((&DAT_008ce022)[in_stack_00000010 + *(char *)(unaff_EBP + 0x15d) * 0xe2] == '\x01') {
      uVar7 = 1;
    }
    else if ((&DAT_008ce022)[in_stack_00000010 + *(char *)(unaff_EBP + 0x15d) * 0xe2] == '\x02') {
      uVar7 = 2;
    }
    else {
      uVar7 = 0;
    }
    FUN_00719610(uVar7);
    iVar8 = *(char *)(unaff_EBP + 0x15d) * 0xe2 + in_stack_00000010;
    if (((*(short *)(&DAT_008ce01e + iVar8) == 0) && (*(short *)(&DAT_008ce020 + iVar8) == 0)) ||
       ((&DAT_008ce01b)[iVar8] == '\t')) {
      if ((iVar6 == 0) || ((iVar6 == 1 && (in_stack_00000030 == 1)))) {
        *(undefined2 *)(&DAT_008ce01e + iVar8) = 0x140;
        *(undefined2 *)(&DAT_008ce020 + in_stack_00000010 + *(char *)(unaff_EBP + 0x15d) * 0xe2) =
             0x82;
      }
      else {
        *(undefined2 *)(&DAT_008ce01e + iVar8) = *(undefined2 *)(s_FEP_STA_008ce008 + iVar8 + 4);
        iVar8 = *(char *)(unaff_EBP + 0x15d) * 0xe2 + in_stack_00000010;
        *(short *)(&DAT_008ce020 + iVar8) =
             *(short *)(s_FEP_STA_008ce008 + iVar8 + 6) + sStack00000014;
      }
    }
    iVar8 = *(char *)(unaff_EBP + 0x15d) * 0xe2;
  } while (((&DAT_008ce012)[iVar8 + in_stack_00000010] == '\x01') ||
          (pcVar13 = s_FES_PLA_008ce013 + iVar8 + in_stack_00000010, *pcVar13 == '\0'));
  cVar2 = (&DAT_008ce01b)[iVar8 + in_stack_00000010];
  in_stack_00000020 = 0;
  if ((cVar2 < '\x01') || ('\b' < cVar2)) {
    if (cVar2 == '\t') {
      if (*(char *)(iVar6 * 0x105 + -0xa9 + unaff_EBP) == '\0') {
        (&DAT_008ce012)[iVar8 + in_stack_00000010] = 0x14;
        iVar8 = *(char *)(unaff_EBP + 0x15d) * 0xe2;
        in_stack_0000001c = (char *)0x0;
        *(undefined2 *)(&DAT_008ce020 + iVar8 + in_stack_00000010) =
             *(undefined2 *)(s_FEP_STA_008ce008 + in_stack_00000010 + iVar8 + 6);
      }
      else {
        FUN_00718600(iVar6 * 0x105 + unaff_EBP + -0xa8,&DAT_00c1b100);
        in_stack_0000001c = &DAT_00c1b100;
        (&DAT_008ce012)[in_stack_00000010 + *(char *)(unaff_EBP + 0x15d) * 0xe2] = 0xb;
      }
    }
    else {
      if (cVar2 == '\n') {
        if (*(char *)(unaff_EBP + 0xd0) == '\0') {
          pcVar13 = "FEC_MOU";
        }
        else {
          pcVar13 = "FEJ_TIT";
        }
      }
      in_stack_0000001c = (char *)FUN_006a0050(pcVar13);
    }
  }
  else {
    *(undefined2 *)(&DAT_008ce01e + iVar8 + in_stack_00000010) = 0x50;
    FUN_00719610(1);
    if (*(int *)(&DAT_00c16eb8 + iVar6 * 4) == 0) {
      in_stack_0000001c = (char *)FUN_005d0f40(in_stack_00000024);
      uVar4 = FUN_00718690(in_stack_0000001c);
      if (0xfd < uVar4) {
        FUN_00718600(&DAT_0086550c,&DAT_00c1aed8);
        FUN_00718630(in_stack_0000001c,&DAT_00c1aed8);
      }
      puVar5 = (undefined1 *)FUN_00618d00(in_stack_00000024);
LAB_00579c43:
      if ((in_stack_0000001c != (char *)0x0) && (*in_stack_0000001c != '\0')) goto LAB_00579d7e;
    }
    else if (*(int *)(&DAT_00c16eb8 + iVar6 * 4) == 2) {
      in_stack_0000001c = (char *)FUN_006a0050("FESZ_CS");
      goto LAB_00579c43;
    }
    FUN_00821bb5(&DAT_00b71670,"FEM_SL%d",iVar6);
    FUN_00719610(0);
    *(undefined2 *)(&DAT_008ce01e + in_stack_00000010 + *(char *)(unaff_EBP + 0x15d) * 0xe2) = 0x140
    ;
    in_stack_0000001c = (char *)FUN_006a0050(&DAT_00b71670);
    if (DAT_00c17044 == 0x280) {
      in_stack_00000020 = FUN_00821b40();
    }
    else {
      in_stack_00000020 = FUN_00821b40();
    }
  }
LAB_00579d7e:
  unaff_EBX = in_stack_0000001c;
  in_stack_00000024 = iVar6;
  switch((&DAT_008ce012)[in_stack_00000010 + *(char *)(unaff_EBP + 0x15d) * 0xe2]) {
  case 0x18:
    break;
  case 0x19:
    break;
  case 0x1a:
    break;
  default:
    goto switchD_00579daa_caseD_1b;
  case 0x1e:
    break;
  case 0x1f:
    break;
  case 0x20:
    puVar5 = (undefined1 *)FUN_00507000(*(undefined1 *)(unaff_EBP + 0x52));
    goto switchD_00579daa_caseD_1b;
  case 0x21:
    break;
  case 0x22:
    iVar6 = *(int *)(unaff_EBP + 0x24);
    if (iVar6 == 0) {
      pcVar13 = "FED_RDM";
      goto LAB_0057a161;
    }
    if (iVar6 == 1) {
      pcVar13 = "FED_RDB";
      goto LAB_0057a161;
    }
    if (iVar6 == 2) {
      pcVar13 = "FEM_OFF";
      goto LAB_0057a161;
    }
    goto switchD_00579daa_caseD_1b;
  case 0x23:
    break;
  case 0x24:
    switch(*(undefined1 *)(unaff_EBP + 0x84)) {
    case 0:
      pcVar13 = "FEL_ENG";
      goto LAB_0057a161;
    case 1:
      pcVar13 = "FEL_FRE";
      goto LAB_0057a161;
    case 2:
      pcVar13 = "FEL_GER";
      goto LAB_0057a161;
    case 3:
      pcVar13 = "FEL_ITA";
      goto LAB_0057a161;
    case 4:
      pcVar13 = "FEL_SPA";
      goto LAB_0057a161;
    }
    goto switchD_00579daa_caseD_1b;
  case 0x2a:
    uVar7 = FUN_0049ea50();
    switch(uVar7) {
    case 0:
      pcVar13 = "FED_FXL";
      goto LAB_0057a161;
    case 1:
      pcVar13 = "FED_FXM";
      goto LAB_0057a161;
    case 2:
      pcVar13 = "FED_FXH";
      goto LAB_0057a161;
    case 3:
      pcVar13 = "FED_FXV";
      goto LAB_0057a161;
    }
    goto switchD_00579daa_caseD_1b;
  case 0x2b:
    if (*(char *)(unaff_EBP + 0xc4) == '\0') {
      puVar3 = &DAT_008653a4;
    }
    else {
      puVar3 = &DAT_0086539c;
    }
    puVar5 = (undefined1 *)FUN_006a0050(puVar3);
    if (*(char *)(unaff_EBP + 0xe9) == '\0') {
      puVar3 = (undefined4 *)FUN_007170c0(0xe,0x1e,0x2f,0xff);
      FUN_00719430(*puVar3);
    }
    goto switchD_00579daa_caseD_1b;
  case 0x2c:
    _Memory = (void *)FUN_0072f460(100,1,0);
    if (*(int *)(unaff_EBP + 0xcc) < 2) {
      FUN_006a0050(&DAT_008653a4);
                    /* WARNING: Subroutine does not return */
      _free(_Memory);
    }
    (**(code **)(DAT_00c97b24 + 0xf0))(_Memory,&DAT_00859508,*(int *)(unaff_EBP + 0xcc) + -1);
    FUN_00718600(_Memory,&stack0x000000f0);
                    /* WARNING: Subroutine does not return */
    _free(_Memory);
  case 0x2e:
    goto switchD_00579daa_caseD_2e;
  case 0x2f:
    break;
  case 0x30:
    break;
  case 0x31:
    break;
  case 0x32:
    break;
  case 0x33:
    break;
  case 0x34:
    break;
  case 0x38:
    iVar6 = thunk_FUN_00402012();
    FUN_00718600(*(undefined4 *)(iVar6 + *(int *)(unaff_EBP + 0xd8) * 4),&stack0x000000f0);
    iVar6 = 0;
    if (in_stack_000000f0 == '\0') goto LAB_0057a0c7;
    do {
      if ((&stack0x000000f0)[iVar6] == '(') goto joined_r0x0057a0aa;
      pcVar13 = &stack0x000000f1 + iVar6;
      iVar6 = iVar6 + 1;
    } while (*pcVar13 != '\0');
    puVar5 = &stack0x000000f0;
    goto switchD_00579daa_caseD_1b;
  case 0x3a:
    if (*(char *)(unaff_EBP + 0xd0) == '\0') {
      pcVar13 = "FET_SCN";
      goto LAB_0057a161;
    }
    if (*(char *)(unaff_EBP + 0xd0) == '\x01') {
      pcVar13 = "FET_CCN";
      goto LAB_0057a161;
    }
    goto switchD_00579daa_caseD_1b;
  case 0x3b:
    if (DAT_00c1cc02 == '\0') {
      puVar3 = &DAT_008653a4;
    }
    else {
      puVar3 = &DAT_0086539c;
    }
    puVar5 = (undefined1 *)FUN_006a0050(puVar3);
    if (*(char *)(unaff_EBP + 0xd0) == '\x01') {
      puVar3 = (undefined4 *)FUN_007170c0(0xe,0x1e,0x2f,0xff);
      FUN_00719430(*puVar3);
    }
    goto switchD_00579daa_caseD_1b;
  case 0x3c:
    if (DAT_00c1cc03 == '\0') {
      puVar3 = &DAT_008653a4;
    }
    else {
      puVar3 = &DAT_0086539c;
    }
    puVar5 = (undefined1 *)FUN_006a0050(puVar3);
    if (*(char *)(unaff_EBP + 0xd0) == '\x01') {
      puVar3 = (undefined4 *)FUN_007170c0(0xe,0x1e,0x2f,0xff);
      FUN_00719430(*puVar3);
    }
    goto switchD_00579daa_caseD_1b;
  case 0x3f:
    cVar2 = *(char *)(unaff_EBP + 0xb0);
    if (cVar2 == '\0') {
      pcVar13 = "FEA_PR1";
      goto LAB_0057a161;
    }
    if (cVar2 == '\x01') {
      pcVar13 = "FEA_PR2";
      goto LAB_0057a161;
    }
    if (cVar2 == '\x02') {
      pcVar13 = "FEA_PR3";
      goto LAB_0057a161;
    }
    goto switchD_00579daa_caseD_1b;
  case 0x40:
    break;
  case 0x41:
  }
  FUN_00403a5c();
  return;
joined_r0x0057a0aa:
  for (; (0 < iVar6 && ((&stack0x000000ef)[iVar6] == ' ')); iVar6 = iVar6 + -1) {
  }
  (&stack0x000000f0)[iVar6] = 0;
LAB_0057a0c7:
  puVar5 = &stack0x000000f0;
  goto switchD_00579daa_caseD_1b;
switchD_00579daa_caseD_2e:
  if (DAT_00ba6744._1_1_ != '\0') {
LAB_00579f65:
    pcVar13 = "FEM_OFF";
    goto LAB_0057a161;
  }
  goto LAB_00579fa6;
}



/* entry 0x00588050; bounded CFG instructions=160; body bytes=1772 */

/* WARNING (jumptable): Unable to track spacebase fully for stack */
/* WARNING: Removing unreachable block (ram,0x0058840f) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00588050(void)

{
  float fVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 uVar9;
  char *pcVar10;
  undefined4 *puVar11;
  bool bVar12;
  float10 fVar13;
  undefined4 uStack_48;
  float afStack_44 [2];
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  float fStack_20;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  float fStack_c;
  
  iVar4 = FUN_00821b40();
  iVar5 = FUN_00821b40();
  iVar6 = FUN_00821b40();
  iVar7 = FUN_00821b40();
  FUN_00587d20();
  (**(code **)(DAT_00c97b24 + 0x20))(8,0);
  (**(code **)(DAT_00c97b24 + 0x20))(6,0);
  (**(code **)(DAT_00c97b24 + 0x20))(0xc,1);
  (**(code **)(DAT_00c97b24 + 0x20))(10,5);
  (**(code **)(DAT_00c97b24 + 0x20))(0xb,6);
  (**(code **)(DAT_00c97b24 + 0x20))(0xe,0);
  fStack_34 = 0.0;
  fStack_30 = 0.0;
  FUN_00583480(&fStack_2c,&fStack_34);
  cVar3 = DAT_00b73418;
  if (DAT_00ba67a1 == '\0') {
    fStack_38 = _DAT_00ba8314 * _DAT_00866ba4 + _DAT_00baa24c;
    fStack_3c = DAT_00baa248;
    FUN_00583530(&fStack_34,&fStack_3c);
    thunk_FUN_005832f5(&fStack_34);
    FUN_00583480(&fStack_2c,&fStack_34);
    FUN_00585ff0(4,fStack_2c,fStack_28,0xff);
  }
  else if ((DAT_00ba67c0 != '\0') &&
          (((((FUN_0053fb70(0), cVar3 == '\0' && (iVar4 < DAT_00ba6808)) && (DAT_00ba6808 < iVar5))
            && ((iVar6 < DAT_00ba6804 && (DAT_00ba6804 < iVar7)))) || (DAT_00ba6800 == '\0')))) {
    fStack_38 = _DAT_00ba67bc;
    fStack_3c = DAT_00ba67b8;
    FUN_00583530(&fStack_34,&fStack_3c);
    thunk_FUN_005832f5(&fStack_34);
    FUN_00583480(&fStack_2c,&fStack_34);
    FUN_00583350(&fStack_2c,&fStack_28);
    fStack_10 = (float)DAT_00c17044 * _DAT_00859520 * fStack_2c;
    fStack_c = 0.0;
    fStack_18 = fStack_10 - _DAT_00858624;
    fStack_10 = fStack_10 + _DAT_00858624;
    fStack_14 = (float)DAT_00c17048;
    uVar9 = FUN_0058fea0(afStack_44,6);
    thunk_FUN_00409737(&fStack_18,uVar9);
    fStack_14 = (float)DAT_00c17048 * _DAT_00859524 * fStack_28;
    fStack_18 = 0.0;
    fStack_c = fStack_14 - _DAT_00858624;
    fStack_10 = (float)DAT_00c17044;
    fStack_14 = fStack_14 + _DAT_00858624;
    uVar9 = FUN_0058fea0(afStack_44,6);
    thunk_FUN_00409737(&fStack_18,uVar9);
  }
  afStack_44[0] = (float)CONCAT31(afStack_44[0]._1_3_,1);
  do {
    fVar1 = afStack_44[0];
    bVar2 = 1;
    do {
      iVar4 = 0;
      pcVar10 = &DAT_00ba8714;
      do {
        if ((pcVar10[1] & 2U) != 0) {
          switch(((byte)pcVar10[2] & 0x3c) >> 2) {
          case 1:
          case 2:
          case 3:
          case 7:
            cVar3 = thunk_FUN_00408040((int)*pcVar10,bVar2);
            if (cVar3 != '\0') {
LAB_0058837a:
              FUN_00587000(iVar4,fVar1);
            }
            break;
          case 4:
          case 5:
            if ((*pcVar10 != ')') &&
               (cVar3 = thunk_FUN_00408040((int)*pcVar10,bVar2), cVar3 != '\0')) {
              FUN_00586d60(iVar4,fVar1);
            }
            break;
          case 6:
          case 8:
            if ((bVar2 == 3) && ((DAT_00a444a4 == '\0' || (DAT_00ba67a1 == '\0'))))
            goto LAB_0058837a;
          }
        }
        pcVar10 = pcVar10 + 0x28;
        iVar4 = iVar4 + 1;
      } while ((int)pcVar10 < 0xbaa26c);
      bVar2 = bVar2 + 1;
    } while (bVar2 < 4);
    pcVar10 = &DAT_00ba8714;
    do {
      if (((((pcVar10[1] & 2U) != 0) && (bVar2 = (byte)pcVar10[2] >> 2 & 0xf, 3 < bVar2)) &&
          (bVar2 < 6)) && (*pcVar10 == ')')) {
        if ((DAT_00b72914 == 0) &&
           (iVar4 = FUN_0056e210(0xffffffff), *(char *)(iVar4 + 0x2f) == '\0')) {
                    /* WARNING: Could not recover jumptable at 0x005883f5. Too many branches */
                    /* WARNING: Treating indirect jump as call */
          (**(code **)(&DAT_00588768 + (uint)PTR_DAT_0058879c._1_1_ * 4))();
          return;
        }
                    /* WARNING: Could not recover jumptable at 0x00588408. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (**(code **)(&DAT_005887b4 + (uint)PTR_DAT_005887e4._1_1_ * 4))();
        return;
      }
      pcVar10 = pcVar10 + 0x28;
    } while ((int)pcVar10 < 0xbaa26c);
    bVar12 = afStack_44[0]._0_1_ == '\0';
    afStack_44[0] = (float)CONCAT31(afStack_44[0]._1_3_,bVar12);
    if (bVar12) {
      if (DAT_00ba67a1 != '\0') {
        FUN_0056e400(&fStack_24,0);
        fStack_3c = (_DAT_00858624 / _DAT_00ba8314) * (fStack_24 - DAT_00baa248);
        fVar1 = (_DAT_00858624 / _DAT_00ba8314) * (fStack_20 - _DAT_00baa24c);
        fStack_34 = DAT_00ba8308 * fStack_3c + DAT_00ba830c * fVar1;
        fStack_30 = fVar1 * DAT_00ba8308 - DAT_00ba830c * fStack_3c;
        if ((DAT_00ba67a1 == '\0') &&
           (fVar1 = SQRT(fStack_30 * fStack_30 + fStack_34 * fStack_34), _DAT_00858624 < fVar1)) {
          fVar1 = _DAT_00858624 / fVar1;
          fStack_34 = fStack_34 * fVar1;
          fStack_30 = fStack_30 * fVar1;
        }
        FUN_00583480(&fStack_2c,&fStack_34);
        FUN_00584960(fStack_2c,fStack_28);
        if (DAT_00ba67a1 != '\0') {
          return;
        }
      }
      iVar4 = 0;
      puVar11 = &DAT_00b7cd98;
      do {
        iVar5 = FUN_0056e210(iVar4);
        if ((iVar5 != 0) &&
           (((iVar5 = FUN_0056e0d0(iVar4,0), iVar5 == 0 ||
             (iVar5 = FUN_0056e0d0(iVar4,0), *(int *)(iVar5 + 0x594) != 4)) ||
            (iVar5 = FUN_0056e0d0(iVar4,0), *(short *)(iVar5 + 0x22) == 0x21b)))) {
          FUN_0056e400(&fStack_18,0);
          fStack_24 = (_DAT_00858624 / _DAT_00ba8314) * (fStack_18 - DAT_00baa248);
          fVar1 = (_DAT_00858624 / _DAT_00ba8314) * (fStack_14 - _DAT_00baa24c);
          fStack_34 = fStack_24 * DAT_00ba8308 + DAT_00ba830c * fVar1;
          fStack_30 = fVar1 * DAT_00ba8308 - fStack_24 * DAT_00ba830c;
          if ((DAT_00ba67a1 == '\0') &&
             (fVar1 = SQRT(fStack_30 * fStack_30 + fStack_34 * fStack_34), _DAT_00858624 < fVar1)) {
            fVar1 = _DAT_00858624 / fVar1;
            fStack_34 = fStack_34 * fVar1;
            fStack_30 = fStack_30 * fVar1;
          }
          FUN_00583480(&fStack_2c,&fStack_34);
          fVar13 = (float10)FUN_0056e450(iVar4);
          afStack_44[0] = (float)fVar13;
          cVar3 = FUN_00609620();
          if (cVar3 == '\0') {
            puVar8 = (undefined4 *)FUN_007170c0(0xff,0xff,0xff,0xff);
            uStack_48 = *puVar8;
          }
          else {
            puVar8 = (undefined4 *)FUN_007170c0(0x32,0x32,0x50,0xff);
            uStack_48 = *puVar8;
          }
          if ((&DAT_00b6f1a8)[(uint)DAT_00b6f081 * 0x11c] == 1) {
            uVar9 = FUN_00821b40();
            fVar1 = afStack_44[0] + _DAT_00858cb8;
          }
          else {
            uVar9 = FUN_00821b40();
            fVar1 = afStack_44[0] - (_DAT_00ba8310 + _DAT_00858cb8);
          }
          FUN_00584850(&DAT_00baa258,fStack_2c,fStack_28,fVar1,uVar9,uVar9,uStack_48);
        }
        puVar11 = puVar11 + 100;
        iVar4 = iVar4 + 1;
      } while ((int)puVar11 < 0xb7d0b8);
      return;
    }
  } while( true );
}



/* entry 0x0058A330; bounded CFG instructions=160; body bytes=1798 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0058a330(void)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  float10 fVar8;
  float10 fVar9;
  float10 fVar10;
  float10 fVar11;
  float10 fVar12;
  int iStack_34;
  float fStack_30;
  float fStack_2c;
  float afStack_28 [10];
  
  if ((((DAT_0096a7cc == 1) || (DAT_0096a7cc == 2)) || (DAT_00ba676c == 2)) ||
     ((DAT_00bab1dc == 8 && (((byte)DAT_00b7cb4c & 8) == 0)))) {
    return;
  }
  (**(code **)(DAT_00c97b24 + 0x20))(9);
  (**(code **)(DAT_00c97b24 + 0x20))(7,1);
  FUN_00586b00();
  if (DAT_00ba676c == 1) goto LAB_0058aa2a;
  iVar5 = FUN_0056e0d0(0xffffffff);
  if (((iVar5 != 0) && (iVar5 = FUN_0056e0d0(0xffffffff), *(int *)(iVar5 + 0x594) == 4)) &&
     (iVar5 = FUN_0056e0d0(0xffffffff), *(short *)(iVar5 + 0x22) != 0x21b)) {
    iVar5 = FUN_0056e0d0(0xffffffff,0);
    iVar5 = *(int *)(iVar5 + 0x14);
    iVar6 = FUN_0056e0d0(0xffffffff,0);
    fStack_30 = *(float *)(iVar5 + 0x28);
    fStack_2c = -*(float *)(*(int *)(iVar6 + 0x14) + 8);
    FUN_00403d60(afStack_28 + 2,8,4,&LAB_0043e0e0);
    fVar12 = (float10)fpatan((float10)fStack_2c,(float10)fStack_30);
    iStack_34 = 0;
    fVar8 = (float10)DAT_00c17044 * (float10)_DAT_00859520;
    fStack_2c = (float)((float10)_DAT_00866b78 * fVar8 - fVar8 * (float10)_DAT_00859008);
    afStack_28[0] = (float)((float10)_DAT_00866b78 * fVar8 * (float10)_DAT_00858b8c);
    fVar9 = (float10)_DAT_00859524 * (float10)DAT_00c17048;
    fStack_30 = (float)((float10)_DAT_00866b74 * fVar9);
    afStack_28[1] = (float)((float10)fStack_30 - (float10)_DAT_00859008 * fVar9);
    do {
      fVar10 = (float10)iStack_34;
      iStack_34 = iStack_34 + 1;
      fVar10 = fVar10 * (float10)_DAT_00858fe4 + (-fVar12 - (float10)_DAT_00859ab0);
      fVar11 = (float10)fsin(fVar10);
      fVar10 = (float10)fcos(fVar10);
      afStack_28[iStack_34 * 2] =
           (float)(((float10)DAT_00858b50 * fVar10 + fVar11) * (float10)fStack_2c +
                   fVar8 * (float10)_DAT_00858a10 + (float10)afStack_28[0]);
      afStack_28[iStack_34 * 2 + 1] =
           (float)((fVar10 - fVar11 * (float10)DAT_00858b50) * (float10)afStack_28[1] +
                   (float10)fStack_30 * (float10)_DAT_00858b8c +
                  ((float10)DAT_00c17048 - fVar9 * (float10)_DAT_00866b70));
    } while (iStack_34 < 4);
    FUN_007170c0(0xff,0xff,0xff);
    FUN_00728520(afStack_28[4],afStack_28[5],afStack_28[2],afStack_28[3],afStack_28[6],afStack_28[7]
                 ,afStack_28[8],afStack_28[9]);
  }
  iVar5 = FUN_0056e0d0(0xffffffff);
  if (((iVar5 != 0) &&
      (((iVar5 = FUN_0056e0d0(0xffffffff), *(int *)(iVar5 + 0x594) == 4 ||
        (iVar5 = FUN_0056e0d0(0xffffffff), *(int *)(iVar5 + 0x594) == 3)) &&
       (iVar5 = FUN_0056e0d0(0xffffffff), *(short *)(iVar5 + 0x22) != 0x21b)))) ||
     (iVar5 = FUN_0056e210(), *(int *)(*(char *)(iVar5 + 0x718) * 0x1c + 0x5a0 + iVar5) == 0x2e)) {
    fVar1 = (float)DAT_00c17044 * _DAT_00859520;
    afStack_28[2] = _DAT_00858a10 * fVar1 - fVar1 * _DAT_00858ba4;
    fStack_30 = _DAT_00859524 * (float)DAT_00c17048;
    afStack_28[5] = (float)DAT_00c17048 - fStack_30 * _DAT_00866b70;
    afStack_28[4] = _DAT_00858a10 * fVar1 - fVar1 * _DAT_0085862c;
    afStack_28[3] = fStack_30 * _DAT_00866b74 + afStack_28[5];
    FUN_007170c0(10,10,10);
    thunk_FUN_00409737(afStack_28 + 2);
    iVar5 = FUN_0056e0d0(0xffffffff,0);
    if (iVar5 == 0) {
      iVar5 = FUN_0056e210();
      if (*(int *)(iVar5 + 0x14) == 0) goto LAB_0058a68c;
      iVar5 = *(int *)(iVar5 + 0x14) + 0x30;
    }
    else {
      iVar5 = FUN_0056e0d0(0xffffffff);
      if (*(int *)(iVar5 + 0x14) == 0) {
LAB_0058a68c:
        iVar5 = iVar5 + 4;
      }
      else {
        iVar5 = *(int *)(iVar5 + 0x14) + 0x30;
      }
    }
    fVar1 = *(float *)(iVar5 + 8);
    fVar2 = (float)DAT_00c17048 * _DAT_00859524 * _DAT_00866b74;
    fVar3 = _DAT_00858b4c;
    if (_DAT_00858a48 < fVar1) {
      fVar3 = _DAT_00866c08;
    }
    (**(code **)(DAT_00c97b24 + 0x20))(1);
    fStack_2c = _DAT_00858a10 * (float)DAT_00c17044 * _DAT_00859520;
    afStack_28[2] = fStack_2c - (float)DAT_00c17044 * _DAT_00859520 * _DAT_00858fe8;
    fVar4 = _DAT_00859524 * (float)DAT_00c17048;
    fStack_30 = _DAT_00866b74 * fVar4;
    afStack_28[1] = ((float)DAT_00c17048 - fVar4 * _DAT_00866b70) + fStack_30;
    fVar8 = (float10)FUN_00404330(fStack_30,fVar1 * fVar3 * fVar2);
    afStack_28[5] = (float)((float10)afStack_28[1] - fVar8);
    afStack_28[4] = fStack_2c - _DAT_00858c80;
    afStack_28[3] = (float)(((float10)afStack_28[1] - fVar8) + (float10)_FUN_00858ca0);
    FUN_007170c0(200,200,200);
    thunk_FUN_00409737(afStack_28 + 2);
  }
  fVar1 = (float)DAT_00c17044 * _DAT_00859520;
  afStack_28[2] = _DAT_00858a10 * fVar1 - fVar1 * _DAT_00858b90;
  fStack_30 = _DAT_00859524 * (float)DAT_00c17048;
  afStack_28[3] = (float)DAT_00c17048 - fStack_30 * _DAT_00866b70;
  afStack_28[5] = afStack_28[3] - fStack_30 * _DAT_00858b90;
  afStack_28[4] = fVar1 * _DAT_00866b78 * _DAT_00858b8c + _DAT_00858a10 * fVar1;
  afStack_28[3] = fStack_30 * _DAT_00866b74 * _DAT_00858b8c + afStack_28[3];
  FUN_007170c0(0,0,0);
  FUN_00728350(afStack_28 + 2);
  fVar1 = (float)DAT_00c17044 * _DAT_00859520;
  afStack_28[0] = fVar1 * _DAT_00858b90 + _DAT_00858a10 * fVar1 + fVar1 * _DAT_00866b78;
  fVar2 = _DAT_00859524 * (float)DAT_00c17048;
  afStack_28[1] = (float)DAT_00c17048 - fVar2 * _DAT_00866b70;
  afStack_28[3] = afStack_28[1] - fVar2 * _DAT_00858b90;
  afStack_28[2] = fVar1 * _DAT_00866b78 * _DAT_00858b8c + _DAT_00858a10 * fVar1;
  afStack_28[1] = fVar2 * _DAT_00866b74 * _DAT_00858b8c + afStack_28[1];
  uVar7 = FUN_007170c0(0,0,0,0xff);
  FUN_00728350(afStack_28,uVar7);
  fVar1 = (float)DAT_00c17044 * _DAT_00859520;
  fStack_30 = _DAT_00858a10 * fVar1 - fVar1 * _DAT_00858b90;
  fVar2 = _DAT_00859524 * (float)DAT_00c17048;
  fStack_2c = (float)DAT_00c17048 - _DAT_00866b70 * fVar2;
  afStack_28[1] = fVar2 * _DAT_00858b90 + fStack_2c + _DAT_00866b74 * fVar2;
  afStack_28[0] = fVar1 * _DAT_00866b78 * _DAT_00858b8c + _DAT_00858a10 * fVar1;
  fStack_2c = _DAT_00866b74 * fVar2 * _DAT_00858b8c + fStack_2c;
  uVar7 = FUN_007170c0(0,0,0,0xff);
  FUN_00728350(&fStack_30,uVar7);
  fVar1 = _DAT_00859524 * (float)DAT_00c17048;
  fStack_2c = fVar1 * _DAT_00858b90 + ((float)DAT_00c17048 - _DAT_00866b70 * fVar1) +
              _DAT_00866b74 * fVar1;
  fStack_30 = (float)DAT_00c17044 * _DAT_00859520 * _DAT_00866b78 * _DAT_00858b8c +
              _DAT_00858a10 * (float)DAT_00c17044 * _DAT_00859520;
  uVar7 = FUN_007170c0(0,0,0,0xff);
  FUN_00728350(&stack0xffffffc8,uVar7);
LAB_0058aa2a:
  FUN_00588050();
  return;
}



/* entry 0x0058D7D0; bounded CFG instructions=123; body bytes=450 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0058d7d0(int param_1,int param_2,int param_3)

{
  float fVar1;
  float fVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  int *piVar7;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  (**(code **)(DAT_00c97b24 + 0x20))(9,2);
  iVar3 = FUN_00743c60(*(undefined4 *)(*(char *)(param_1 + 0x718) * 0x1c + 0x5a0 + param_1),1);
  if (*(int *)(iVar3 + 0xc) < 1) {
    fStack_10 = (float)param_2;
    fStack_4 = (float)param_3;
    fStack_8 = (float)DAT_00c17044 * _DAT_00859520 * _DAT_00866c4c + (float)param_2;
    fStack_c = (float)DAT_00c17048 * _DAT_00859524 * _DAT_00866c50 + (float)param_3;
    uVar4 = FUN_00821b40();
    uVar4 = FUN_007170c0(0xff,0xff,0xff,uVar4);
    FUN_00728350(&fStack_10,uVar4);
  }
  else {
    iVar6 = (int)*(short *)((&DAT_00a9b0c8)[*(int *)(iVar3 + 0xc)] + 10);
    if (*(char *)(iVar6 + DAT_00c8800c[1]) < '\0') {
      piVar7 = (int *)0x0;
    }
    else {
      piVar7 = (int *)(*DAT_00c8800c + iVar6 * 0xc);
    }
    iVar6 = *piVar7;
    if (iVar6 != 0) {
      uVar4 = FUN_0053cf70(*(undefined4 *)((&DAT_00a9b0c8)[*(int *)(iVar3 + 0xc)] + 4),"ICON");
      puVar5 = (undefined4 *)FUN_00734e50(iVar6,uVar4);
      if (puVar5 != (undefined4 *)0x0) {
        (**(code **)(DAT_00c97b24 + 0x20))(6,0);
        (**(code **)(DAT_00c97b24 + 0x20))(1,*puVar5);
        fVar1 = (float)DAT_00c17048 * _DAT_00859524 * _DAT_00866c50 * _DAT_00858b8c;
        fVar2 = (float)DAT_00c17044 * _DAT_00859520 * _DAT_00866c4c * _DAT_00858b8c;
        FUN_0070d000((float)param_2 + fVar2,(float)param_3 + fVar1,0x3f800000,fVar2,fVar1,0xff,0xff,
                     0xff,0xff,0x3f800000,0xff,0,0);
        (**(code **)(DAT_00c97b24 + 0x20))(8,0);
        return;
      }
    }
  }
  return;
}



/* entry 0x0058E020; bounded CFG instructions=160; body bytes=2765 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0058e020(void)

{
  short sVar1;
  float ***pppfVar2;
  bool bVar3;
  uint3 uVar4;
  char cVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  int iVar9;
  undefined4 *puVar10;
  int *piVar11;
  float unaff_EBX;
  float10 fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  undefined4 ****ppppuVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  undefined4 uStack_30;
  undefined4 ***pppuStack_28;
  float **ppfStack_24;
  float ***pppfStack_20;
  undefined4 ***pppuStack_1c;
  undefined4 ***pppuStack_18;
  float **ppfStack_14;
  undefined4 ***pppuStack_10;
  undefined4 ***pppuStack_c;
  float **ppfStack_8;
  float fStack_4;
  
  uVar4 = (uint3)uStack_30;
  iVar9 = (&DAT_00b7cd98)[(uint)DAT_00b7cd74 * 100];
  sVar1 = (&DAT_00b6f1a8)[(uint)DAT_00b6f081 * 0x11c];
  bVar3 = false;
  uStack_30 = (float ***)(uint)(uint3)uStack_30;
  if (sVar1 == 7) {
LAB_0058e07d:
    if (sVar1 == 0x10) {
LAB_0058e083:
      iVar6 = FUN_0056e0d0(0xffffffff,0);
      if ((iVar6 != 0) &&
         ((iVar6 = FUN_0056e0d0(0xffffffff,0), *(short *)(iVar6 + 0x22) == 0x208 ||
          (iVar6 = FUN_0056e0d0(0xffffffff,0), *(short *)(iVar6 + 0x22) == 0x1a9)))) {
        uStack_30 = (float ***)CONCAT13(1,uVar4);
      }
    }
    if ((((&DAT_00b6f1a8)[(uint)DAT_00b6f081 * 0x11c] != 0x10) && (iVar9 != 0)) &&
       (cVar5 = FUN_0073b1c0(), cVar5 == '\0')) {
      uStack_30 = (float ***)CONCAT13(1,(uint3)uStack_30);
    }
  }
  else {
    if (sVar1 == 0x10) goto LAB_0058e083;
    if ((((sVar1 == 8) || (sVar1 == 0x33)) || (sVar1 == 0x22)) ||
       ((sVar1 == 0x2d || (sVar1 == 0x2e)))) goto LAB_0058e07d;
  }
  sVar1 = (&DAT_00b6f1a8)[(uint)DAT_00b6f081 * 0x11c];
  if (((sVar1 == 0x2a) || (sVar1 == 0x28)) || ((sVar1 == 0x34 || (sVar1 == 0x27)))) {
    bVar3 = true;
  }
  if ((((*(int *)(iVar9 + 0x71c) == 0) && ((*(byte *)(*(int *)(iVar9 + 0x480) + 0x34) & 8) != 0)) &&
      (((iVar6 = FUN_00600f70(), iVar6 == 0 ||
        (iVar6 = FUN_00600f70(), *(char *)(iVar6 + 0xe) == '\0')) &&
       ((((sVar1 = (&DAT_00b6f1a8)[(uint)DAT_00b6f081 * 0x11c], sVar1 == 0x35 || (sVar1 == 0x37)) ||
         (sVar1 == 0x41)) &&
        ((*(int *)(iVar9 + 0x530) != 0x3b && (*(int *)(iVar9 + 0x530) != 0x39)))))))) &&
     (((iVar6 = *(int *)(*(char *)(iVar9 + 0x718) * 0x1c + 0x5a0 + iVar9), 0x15 < iVar6 &&
       (iVar6 < 0x20)) ||
      (((iVar6 == 0x20 || (iVar6 == 0x21)) || ((iVar6 == 0x26 || (iVar6 == 0x25)))))))) {
    if ((sVar1 == 0x35) && (DAT_00b6f080 != '\0')) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
  }
  if (((uStack_30._3_1_ == '\0') && (!bVar3)) && (DAT_00a44490 == 0)) {
    return;
  }
  (**(code **)(DAT_00c97b24 + 0x20))(9,2);
  (**(code **)(DAT_00c97b24 + 0x20))(8,0);
  if ((bVar3) &&
     (((sVar1 = (&DAT_00b6f1a8)[(uint)DAT_00b6f081 * 0x11c], sVar1 == 0x35 || (sVar1 == 0x37)) ||
      (sVar1 == 0x41)))) {
    ppfStack_24 = (float **)((float)DAT_00c17044 * _DAT_00b6ec14);
    pppuStack_28 = (undefined4 ***)((float)DAT_00c17048 * _DAT_00b6ec10);
    fVar12 = (float10)FUN_00609cd0();
    pppfStack_20 = (float ***)(float)fVar12;
    if (fVar12 == (float10)_DAT_00858cc4) {
      pppuStack_10 = (undefined4 ***)((float)ppfStack_24 - _DAT_00858624);
      fStack_4 = (float)pppuStack_28 - _DAT_00858624;
      ppfStack_8 = (float **)((float)ppfStack_24 + _DAT_00858624);
      pppuStack_c = (undefined4 ***)((float)pppuStack_28 + _DAT_00858624);
      uVar7 = FUN_007170c0(0xff,0xff,0xff,0xff);
      thunk_FUN_00409737(&pppuStack_10,uVar7);
    }
    pppuStack_18 = (undefined4 ***)
                   ((float)DAT_00c17044 * _DAT_00859520 * _DAT_00859a44 * (float)pppfStack_20);
    ppfStack_14 = (float **)
                  ((float)DAT_00c17048 * _DAT_00859524 * _DAT_00859a44 * (float)pppfStack_20);
    pppuStack_1c = (undefined4 ***)((float)pppuStack_18 * _DAT_00858b8c);
    pppfStack_20 = (float ***)(((float)pppuStack_1c + (float)ppfStack_24) - (float)pppuStack_18);
    ppfStack_24 = (float **)
                  (((float)ppfStack_14 * _DAT_00858b8c + (float)pppuStack_28) - (float)ppfStack_14);
    pppuStack_28 = (undefined4 ***)((float)pppuStack_1c + (float)pppfStack_20);
    pppfVar2 = (float ***)((float)ppfStack_14 * _DAT_00858b8c + (float)ppfStack_24);
    pppuStack_10 = pppfStack_20;
    pppuStack_c = pppfVar2;
    ppfStack_8 = (float **)pppuStack_28;
    fStack_4 = (float)ppfStack_24;
    uVar7 = FUN_007170c0(0xff,0xff,0xff,0xff);
    ppppuVar16 = &pppuStack_10;
    FUN_00728350(ppppuVar16,uVar7);
    pppfStack_20 = (float ***)((float)pppuStack_28 + (float)pppfStack_20);
    pppuStack_10 = uStack_30;
    pppuStack_18 = pppfStack_20;
    pppuStack_c = pppfVar2;
    uVar8 = FUN_007170c0(0xff,0xff,0xff,0xff);
    FUN_00728350(&pppuStack_18,uVar8);
    ppfStack_24 = (float **)(unaff_EBX + (float)ppfStack_24);
    pppfStack_20 = uStack_30;
    pppuStack_1c = (undefined4 ***)uVar7;
    ppfStack_14 = ppfStack_24;
    uVar7 = FUN_007170c0(0xff,0xff,0xff,0xff);
    FUN_00728350(&pppfStack_20,uVar7);
    pppuStack_28 = uStack_30;
    ppfStack_24 = (float **)uVar8;
    pppfStack_20 = (float ***)ppppuVar16;
    pppuStack_1c = pppfVar2;
    uVar7 = FUN_007170c0(0xff,0xff,0xff,0xff);
    FUN_00728350(&pppuStack_28,uVar7);
  }
  else if ((DAT_00a44490 == 2) ||
          (((sVar1 = (&DAT_00b6f1a8)[(uint)DAT_00b6f081 * 0x11c], sVar1 != 0x22 && (sVar1 != 0x2a))
           && ((sVar1 != 0x29 && (sVar1 != 0x2d)))))) {
    (**(code **)(DAT_00c97b24 + 0x20))(9,2);
    iVar6 = FUN_0056e210(0xffffffff);
    if (((*(int *)(*(char *)(iVar6 + 0x718) * 0x1c + 0x5a0 + iVar6) == 0x2b) ||
        (iVar6 = FUN_0056e210(0xffffffff),
        *(int *)(*(char *)(iVar6 + 0x718) * 0x1c + 0x5a0 + iVar6) == 0x22)) || (DAT_00a44490 == 2))
    {
      iVar6 = FUN_0056e210(0xffffffff);
      if ((*(int *)(*(char *)(iVar6 + 0x718) * 0x1c + 0x5a0 + iVar6) == 0x2b) || (DAT_00a44490 == 2)
         ) {
        fVar19 = (float)DAT_00c17044 * _DAT_00859520 * _DAT_00858fb4;
        fVar17 = (float)DAT_00c17048 * _DAT_00859524 * _DAT_00866c74;
      }
      else {
        fVar19 = (float)DAT_00c17044 * _DAT_00859520 * _DAT_00863b34;
        fVar17 = (float)DAT_00c17048 * _DAT_00859524 * _DAT_00863b34;
      }
      fVar13 = 0.0;
      fVar14 = 0.0;
      iVar9 = FUN_00743c60(*(undefined4 *)(*(char *)(iVar9 + 0x718) * 0x1c + 0x5a0 + iVar9),1);
      if (*(int *)(iVar9 + 0xc) < 1) goto LAB_0058eabe;
      iVar6 = (int)*(short *)((&DAT_00a9b0c8)[*(int *)(iVar9 + 0xc)] + 10);
      if (*(char *)(iVar6 + DAT_00c8800c[1]) < '\0') {
        piVar11 = (int *)0x0;
      }
      else {
        piVar11 = (int *)(*DAT_00c8800c + iVar6 * 0xc);
      }
      iVar6 = *piVar11;
      if (iVar6 == 0) goto LAB_0058eabe;
      uVar7 = FUN_0053cf70(*(undefined4 *)((&DAT_00a9b0c8)[*(int *)(iVar9 + 0xc)] + 4),"CROSSHAIR");
      puVar10 = (undefined4 *)FUN_00734e50(iVar6,uVar7);
    }
    else {
      sVar1 = (&DAT_00b6f1a8)[(uint)DAT_00b6f081 * 0x11c];
      if (((sVar1 != 8) && (sVar1 != 0x10)) &&
         ((sVar1 != 0x28 && ((sVar1 != 0x33 && (sVar1 != 0x34)))))) goto LAB_0058eabe;
      fVar19 = _DAT_0085f114 * (float)DAT_00c17044 * _DAT_00859520;
      fVar17 = _DAT_0085f114 * (float)DAT_00c17048 * _DAT_00859524;
      fVar14 = (float)DAT_00c17044 * _DAT_00859520 * _DAT_00858ba4;
      fVar13 = (float)DAT_00c17048 * _DAT_00859524 * _DAT_00858ba4;
      puVar10 = DAT_00bab204;
    }
    if (puVar10 != (undefined4 *)0x0) {
      (**(code **)(DAT_00c97b24 + 0x20))(6,0);
      (**(code **)(DAT_00c97b24 + 0x20))(2,3);
      (**(code **)(DAT_00c97b24 + 0x20))(1,*puVar10);
      fVar17 = fVar17 * _DAT_00858b8c;
      fVar19 = fVar19 * _DAT_00858b8c;
      fVar15 = fVar17;
      fVar18 = fVar19;
      FUN_0070d000(((float)(DAT_00c17044 / 2) - fVar19) - fVar14,
                   ((float)(DAT_00c17048 / 2) - fVar17) - fVar13,0x3f800000,fVar19,fVar17,0xff,0xff,
                   0xff,0xff,0x3c23d70a,0xff,0,0);
      FUN_0070d000((float)(DAT_00c17044 / 2) + fVar18 + fVar14,
                   ((float)(DAT_00c17048 / 2) - fVar15) - fVar13,0x3f800000,fVar19,fVar17,0xff,0xff,
                   0xff,0xff,0x3c23d70a,0xff,1,0);
      FUN_0070d000(((float)(DAT_00c17044 / 2) - fVar18) - fVar14,
                   (float)(DAT_00c17048 / 2) + fVar15 + fVar13,0x3f800000,fVar19,fVar17,0xff,0xff,
                   0xff,0xff,0x3c23d70a,0xff,0,1);
      FUN_0070d000((float)(DAT_00c17044 / 2) + fVar18 + fVar14,
                   (float)(DAT_00c17048 / 2) + fVar15 + fVar13,0x3f800000,fVar19,fVar17,0xff,0xff,
                   0xff,0xff,0x3c23d70a,0xff,1,1);
      (**(code **)(DAT_00c97b24 + 0x20))(8,0);
    }
  }
  else {
    ppfStack_14 = (float **)((float)DAT_00c17044 * _DAT_00859520 * _DAT_00859a44);
    pppuStack_1c = (undefined4 ***)(DAT_00c17048 / 2);
    pppuStack_18 = (undefined4 ***)((float)DAT_00c17048 * _DAT_00859524 * _DAT_00859a44);
    pppfStack_20 = (float ***)((float)(DAT_00c17044 / 2) - (float)ppfStack_14 * _DAT_00858b8c);
    ppfStack_24 = (float **)((float)(int)pppuStack_1c - (float)pppuStack_18 * _DAT_00858b8c);
    pppuStack_28 = (undefined4 ***)((float)ppfStack_14 * _DAT_00858b8c + (float)pppfStack_20);
    pppfVar2 = (float ***)((float)pppuStack_18 * _DAT_00858b8c + (float)ppfStack_24);
    pppuStack_10 = pppfStack_20;
    pppuStack_c = pppfVar2;
    ppfStack_8 = (float **)pppuStack_28;
    fStack_4 = (float)ppfStack_24;
    uVar7 = FUN_007170c0(0xff,0xff,0xff,0xff);
    ppppuVar16 = &pppuStack_10;
    FUN_00728350(ppppuVar16,uVar7);
    pppuStack_1c = (undefined4 ***)((float)pppuStack_28 + (float)pppuStack_1c);
    pppuStack_10 = uStack_30;
    pppuStack_18 = pppuStack_1c;
    pppuStack_c = pppfVar2;
    uVar8 = FUN_007170c0(0xff,0xff,0xff,0xff);
    FUN_00728350(&pppuStack_18,uVar8);
    pppuStack_28 = (undefined4 ***)(unaff_EBX + (float)pppuStack_28);
    pppfStack_20 = uStack_30;
    pppuStack_1c = (undefined4 ***)uVar7;
    ppfStack_14 = (float **)pppuStack_28;
    uVar7 = FUN_007170c0(0xff,0xff,0xff,0xff);
    FUN_00728350(&pppfStack_20,uVar7);
    pppuStack_1c = uStack_30;
    pppuStack_28 = pppfVar2;
    ppfStack_24 = (float **)uVar8;
    pppfStack_20 = (float ***)ppppuVar16;
    uVar7 = FUN_007170c0(0xff,0xff,0xff,0xff);
    FUN_00728350(&pppuStack_28,uVar7);
  }
LAB_0058eabe:
  (**(code **)(DAT_00c97b24 + 0x20))(10,5);
  (**(code **)(DAT_00c97b24 + 0x20))(0xb,6);
  (**(code **)(DAT_00c97b24 + 0x20))(8,1);
  return;
}



/* entry 0x005D8590; bounded CFG instructions=160; body bytes=723 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_005d8590(int param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  int unaff_ESI;
  float *unaff_EDI;
  float10 extraout_ST0;
  float10 fVar13;
  float10 fVar14;
  float10 extraout_ST1;
  undefined4 uVar15;
  float local_44;
  
  if (*(int *)(param_1 + 0x3c) == 0) {
    uVar15 = *(undefined4 *)(param_1 + 4);
  }
  else {
    uVar15 = *(undefined4 *)(*(int *)(param_1 + 0x3c) + 4);
  }
  iVar10 = FUN_007f0990(uVar15);
  fVar3 = *(float *)(iVar10 + 0x30);
  fVar4 = *(float *)(iVar10 + 0x34);
  fVar1 = (float)(int)*(char *)(unaff_ESI + 2) * _DAT_00858c48 * _DAT_00858b40;
  local_44 = *unaff_EDI;
  fVar2 = (float)(int)*(char *)(unaff_ESI + 3) * _DAT_00858c48 * _DAT_00858b40;
  if (*(short *)(unaff_ESI + 6) == *(short *)(DAT_00c97b24 + 8)) goto LAB_005d87ea;
  fVar5 = _DAT_00858624 / fVar2;
  *(short *)(unaff_ESI + 6) = *(short *)(DAT_00c97b24 + 8);
  uVar11 = FUN_00821b40();
  fVar6 = _DAT_00858624 / fVar1;
  uVar12 = FUN_00821b40();
  fVar8 = ABS(((float)(int)uVar12 * fVar1 - fVar3) * fVar6);
  if ((uVar12 & 1) == 0) {
    fVar8 = _DAT_00858624 - fVar8;
  }
  fVar9 = ABS(((float)(int)uVar11 * fVar2 - fVar4) * fVar5);
  if ((uVar11 & 1) == 0) {
    fVar9 = _DAT_00858624 - fVar9;
  }
  uVar11 = FUN_00821b40();
  uVar12 = FUN_00821b40();
  fVar13 = ABS(((float10)(int)uVar12 * (float10)fVar1 - extraout_ST1) * (float10)fVar6);
  if ((uVar12 & 1) == 0) {
    fVar13 = (float10)_DAT_00858624 - fVar13;
  }
  fVar14 = ABS(((float10)(int)uVar11 * (float10)fVar2 - extraout_ST0) * (float10)fVar5);
  if ((uVar11 & 1) == 0) {
    fVar14 = (float10)_DAT_00858624 - fVar14;
  }
  fVar1 = (float)((float10)fVar3 - extraout_ST1);
  fVar2 = (float)((float10)fVar4 - extraout_ST0);
  if (fVar2 * fVar2 + fVar1 * fVar1 <= DAT_00858b50) {
LAB_005d87b1:
    local_44 = ABS((float)(fVar14 + fVar13) - (fVar9 + fVar8)) + local_44;
    if (_DAT_00858624 <= local_44) {
      local_44 = local_44 - _DAT_00858624;
    }
  }
  else {
    fVar5 = *(float *)(iVar10 + 0x10);
    fVar6 = *(float *)(iVar10 + 0x14);
    fVar7 = *(float *)(iVar10 + 0x18);
    FUN_0059c910();
    FUN_0059c910();
    if (DAT_00858b50 <= fVar6 * fVar2 + fVar1 * fVar5 + fVar7 * 0.0) goto LAB_005d87b1;
    local_44 = local_44 - ABS((float)(fVar14 + fVar13) - (fVar9 + fVar8));
    if (local_44 < DAT_00858b50) {
      local_44 = local_44 + _DAT_00858624;
    }
  }
  *unaff_EDI = local_44;
  unaff_EDI[1] = fVar3;
  unaff_EDI[2] = fVar4;
LAB_005d87ea:
  fVar3 = *(float *)(iVar10 + 0x24) + *(float *)(iVar10 + 0x20);
  fVar4 = _DAT_00858b1c;
  if ((fVar3 < _DAT_00858b1c) && (fVar4 = fVar3, fVar3 <= DAT_00858b50)) {
    fVar4 = DAT_00858b50;
  }
  if (*(float *)(iVar10 + 0x28) < DAT_00858b50) {
    fVar4 = _DAT_00858624 - fVar4;
  }
  *param_2 = -local_44;
  param_2[1] = fVar4;
  return 1;
}



/* entry 0x006D0E20; bounded CFG instructions=20; body bytes=58 */

void __fastcall FUN_006d0e20(int param_1)

{
  (**(code **)(DAT_00c97b24 + 0x20))(0x14,2);
  FUN_004c8460(*(undefined4 *)(param_1 + 0x18));
  if (*(int *)(param_1 + 0x590) == 0) {
    FUN_006a2f30((&DAT_00a9b0c8)[*(short *)(param_1 + 0x22)]);
  }
  return;
}



/* entry 0x006D64F0; bounded CFG instructions=90; body bytes=326 */

void __fastcall FUN_006d64f0(int param_1)

{
  short sVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  
  uVar3 = (&DAT_00a9b0c8)[*(short *)(param_1 + 0x22)];
  (**(code **)(DAT_00c97b24 + 0x20))(0x14,1);
  if (*(int *)(param_1 + 0x590) == 0) {
    FUN_006a2f00(uVar3);
  }
  sVar1 = *(short *)(param_1 + 0x59a);
  if (sVar1 < 0) {
    *(byte *)(param_1 + 0x42f) = *(byte *)(param_1 + 0x42f) & 0xfb;
  }
  else if ((&DAT_00946750)[sVar1 * 0x14] == '\x01') {
    if (*(int *)(param_1 + 0x59c) != 0) {
      *(undefined4 *)(param_1 + 0x59c) = 0;
      FUN_00731a30((int)*(short *)(param_1 + 0x598));
    }
    sVar1 = *(short *)(param_1 + 0x59a);
    *(short *)(param_1 + 0x598) = sVar1;
    *(undefined2 *)(param_1 + 0x59a) = 0xffff;
    FUN_00731a00((int)sVar1);
    if ((*(byte *)((int)*(short *)(param_1 + 0x598) + DAT_00c8800c[1]) & 0x80) == 0) {
      puVar2 = (undefined4 *)(*DAT_00c8800c + *(short *)(param_1 + 0x598) * 0xc);
    }
    else {
      puVar2 = (undefined4 *)0x0;
    }
    uVar3 = FUN_00734940(*puVar2);
    *(undefined4 *)(param_1 + 0x59c) = uVar3;
    if ((*(byte *)(param_1 + 0x42f) & 4) == 0) {
      *(undefined1 *)(param_1 + 0x434) = 1;
    }
  }
  else {
    FUN_004087e0(sVar1 + 20000,8);
  }
  FUN_004c84b0(*(undefined1 *)(param_1 + 0x434),*(undefined1 *)(param_1 + 0x435),
               *(undefined1 *)(param_1 + 0x436),*(undefined1 *)(param_1 + 0x437));
  FUN_004c8c90(param_1);
  DAT_00b4e47c = *(undefined4 *)(param_1 + 0x59c);
  FUN_004c8430(*(undefined4 *)(param_1 + 0x18));
  return;
}



/* entry 0x006E0E20; bounded CFG instructions=160; body bytes=1561 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_006e0e20(int param_1,int param_2,float *param_3,char param_4)

{
  float fVar1;
  byte bVar2;
  float *pfVar3;
  int iVar4;
  float local_94;
  float local_90;
  float local_8c;
  float fStack_88;
  float local_84;
  float local_80;
  float local_7c;
  float fStack_78;
  float fStack_74;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float fStack_38;
  float fStack_34;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_10;
  float fStack_4;
  
  pfVar3 = (float *)(*(int *)((&DAT_00a9b0c8)[*(short *)(param_1 + 0x22)] + 0x5c) + param_2 * 0x18);
  local_44 = *pfVar3;
  local_40 = pfVar3[1];
  local_3c = pfVar3[2];
  if ((((param_2 != 1) || (local_44 != DAT_00858b50)) || (local_40 != DAT_00858b50)) ||
     (local_3c != DAT_00858b50)) {
    FUN_0059c890(&local_94,param_3,&local_44);
    if (param_4 == '\0') {
      fVar1 = local_44 + local_44;
      local_84 = fVar1 * param_3[1];
      local_80 = fVar1 * param_3[2];
      local_94 = local_94 - fVar1 * *param_3;
      local_90 = local_90 - local_84;
      local_8c = local_8c - local_80;
    }
    if (DAT_00b6f03c == 0) {
      pfVar3 = (float *)&DAT_00b6f02c;
    }
    else {
      pfVar3 = (float *)(DAT_00b6f03c + 0x30);
    }
    local_48 = pfVar3[2] - local_8c;
    local_4c = pfVar3[1] - local_90;
    local_50 = *pfVar3 - local_94;
    FUN_0059c970();
    local_7c = local_50 * param_3[4] + local_4c * param_3[5] + local_48 * param_3[6];
    (**(code **)(DAT_00c97b24 + 0x20))(8,0);
    (**(code **)(DAT_00c97b24 + 0x20))(6,1);
    (**(code **)(DAT_00c97b24 + 0x20))(0xc,1);
    (**(code **)(DAT_00c97b24 + 0x20))(10,5);
    (**(code **)(DAT_00c97b24 + 0x20))(0xb,2);
    (**(code **)(DAT_00c97b24 + 0x20))(7,2);
    (**(code **)(DAT_00c97b24 + 0x20))(1,0);
    (**(code **)(DAT_00c97b24 + 0x20))(0x14,1);
    (**(code **)(DAT_00c97b24 + 0x20))(0x1d,5);
    (**(code **)(DAT_00c97b24 + 0x20))(0x1e,0);
    bVar2 = FUN_00821b40();
    fVar1 = _DAT_00858fcc;
    if (*(short *)(param_1 + 0x22) == 0x212) {
      fVar1 = _DAT_00858b8c;
    }
    fStack_88 = fVar1 * param_3[8];
    local_84 = fVar1 * param_3[9];
    fStack_60 = param_3[4] - fStack_88;
    fStack_5c = param_3[5] - local_84;
    fStack_58 = param_3[6] - fVar1 * param_3[10];
    FUN_0059c910();
    FUN_0059c730(&fStack_38,&fStack_60,&local_50);
    FUN_0059c910();
    local_94 = local_94 - param_3[4] * _DAT_00858b1c;
    local_90 = local_90 - param_3[5] * _DAT_00858b1c;
    local_8c = local_8c - param_3[6] * _DAT_00858b1c;
    DAT_00c4d958 = local_94 - fStack_38 * _DAT_00858c28;
    DAT_00c4d95c = local_90 - fStack_34 * _DAT_00858c28;
    DAT_00c4d960 = local_8c - fStack_30 * _DAT_00858c28;
    DAT_00c4d97c = fStack_38 * _DAT_00858c28 + local_94;
    DAT_00c4d980 = fStack_34 * _DAT_00858c28 + local_90;
    DAT_00c4d984 = fStack_30 * _DAT_00858c28 + local_8c;
    fStack_18 = fStack_38 * _DAT_00858b8c;
    fStack_2c = fStack_30 * _DAT_00858b8c;
    fStack_1c = fStack_60 * _DAT_00858b3c;
    fStack_54 = fStack_5c * _DAT_00858b3c;
    local_7c = fStack_58 * _DAT_00858b3c;
    DAT_00c4d9a0 = (fStack_1c + local_94) - fStack_18;
    DAT_00c4d9a4 = (fStack_54 + local_90) - fStack_34 * _DAT_00858b8c;
    DAT_00c4d9a8 = (local_7c + local_8c) - fStack_2c;
    DAT_00c4d9c4 = fStack_1c + local_94 + fStack_18;
    DAT_00c4d9c8 = fStack_54 + local_90 + fStack_34 * _DAT_00858b8c;
    DAT_00c4d9cc = local_7c + local_8c + fStack_2c;
    fStack_10 = fStack_58 * _DAT_00858cc4;
    DAT_00c4d9e8 = fStack_60 * _DAT_00858cc4 + local_94;
    DAT_00c4b95c = 4;
    DAT_00c4b962 = 4;
    DAT_00c4b968 = 4;
    DAT_00c4b96e = 4;
    DAT_00c4d9ec = fStack_5c * _DAT_00858cc4 + local_90;
    DAT_00c4b95a = 1;
    DAT_00c4b95e = 1;
    DAT_00c4d9f0 = fStack_10 + local_8c;
    DAT_00c4d970 = (uint)bVar2 << 0x18 | 0xffffff;
    DAT_00c4d9b8 = 0xffffff;
    DAT_00c4d9dc = 0xffffff;
    DAT_00c4b958 = 0;
    DAT_00c4b960 = 3;
    DAT_00c4b964 = 2;
    DAT_00c4b966 = 3;
    DAT_00c4b96a = 0;
    DAT_00c4b96c = 2;
    DAT_00c4b954 = 0xc;
    DAT_00c4b950 = 5;
    DAT_00c4d994 = DAT_00c4d970;
    DAT_00c4da00 = DAT_00c4d970;
    fStack_88 = DAT_00c4d9e8;
    local_84 = DAT_00c4d9ec;
    local_80 = DAT_00c4d9f0;
    fStack_78 = DAT_00c4d9a0;
    fStack_74 = DAT_00c4d9a4;
    fStack_70 = DAT_00c4d9a8;
    fStack_6c = DAT_00c4d9c4;
    fStack_68 = DAT_00c4d9c8;
    fStack_64 = DAT_00c4d9cc;
    fStack_28 = DAT_00c4d958;
    fStack_24 = DAT_00c4d95c;
    fStack_20 = DAT_00c4d960;
    fStack_4 = DAT_00c4d984;
    iVar4 = FUN_007ef450(&DAT_00c4d958,5,0,0x18);
    if (iVar4 != 0) {
      FUN_007ef550(3,&DAT_00c4b958,DAT_00c4b954);
      FUN_007ef520();
    }
    (**(code **)(DAT_00c97b24 + 0x20))(1,0);
    (**(code **)(DAT_00c97b24 + 0x20))(8,1);
    (**(code **)(DAT_00c97b24 + 0x20))(6,1);
    (**(code **)(DAT_00c97b24 + 0x20))(10,5);
    (**(code **)(DAT_00c97b24 + 0x20))(0xb,6);
    (**(code **)(DAT_00c97b24 + 0x20))(0xc,0);
    (**(code **)(DAT_00c97b24 + 0x20))(0x14,2);
  }
  return;
}



/* entry 0x006E7760; bounded CFG instructions=160; body bytes=953 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_006e7760(void)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  float fStack_58;
  int iStack_50;
  int local_4c;
  float afStack_30 [6];
  float afStack_18 [6];
  
  if ((DAT_008d37d4 == '\0') || (DAT_008d37d5 == '\0')) {
    return;
  }
  if ((DAT_00c8132c < _DAT_008d514c) && (iVar3 = FUN_00821b40(), iVar5 = DAT_00c228e4, iVar3 != 0))
  {
    fVar1 = _DAT_008d37e4 / (float)iVar3;
    DAT_00c228e4 = 0;
    if (DAT_00c228e8 == '\0') {
      _DAT_00c228f0 = _DAT_00c228f0 - DAT_00b7cb5c;
      if (_DAT_00c228f0 < DAT_00858b50 != (_DAT_00c228f0 == DAT_00858b50)) {
        _DAT_00c228f0 = 0.0;
        _DAT_00c228ec = _DAT_00c228ec - DAT_00b7cb5c * _DAT_008d37f0;
        if (_DAT_00c228ec < DAT_00858b50) {
          _DAT_00c228ec = 0.0;
        }
      }
    }
    else {
      _DAT_00c228ec = DAT_00b7cb5c * _DAT_008d37f0 + _DAT_00c228ec;
      if (_DAT_00858624 < _DAT_00c228ec) {
        _DAT_00c228ec = 1.0;
      }
      _DAT_00c228f0 = 40.0;
    }
    DAT_00c228e8 = 0;
    if (DAT_00858b50 < _DAT_00c228ec) {
      FUN_00821b40();
      uVar4 = FUN_00821b40();
      thunk_FUN_00409aaa();
      FUN_00700d70();
      FUN_00700ec0(0,0,(float)DAT_00c17044,(float)DAT_00c17048,DAT_008d37ec,DAT_008d37ec >> 8 & 0xff
                   ,DAT_008d37ec >> 0x10 & 0xff,uVar4,0);
      FUN_00700e00();
      if (_DAT_00c228ec == _DAT_00858624) {
        return;
      }
    }
    thunk_FUN_00409aaa();
    FUN_00700d70();
    (**(code **)(DAT_00c97b24 + 0x20))(6,1);
    (**(code **)(DAT_00c97b24 + 0x20))(1,0);
    uVar2 = DAT_008d37e8 >> 0x18;
    iVar7 = 0;
    iVar3 = FUN_00821b40();
    local_4c = 0;
    uVar6 = DAT_008d37e8;
    if (0 < iVar5) {
      do {
        fStack_58 = (float)(&DAT_00c213b8)[local_4c];
        afStack_30[0] = (float)(int)(short)(&DAT_00c21188)[local_4c];
        afStack_18[0] = (float)(int)(short)(&DAT_00c21214)[local_4c];
        afStack_30[1] = (float)(int)(short)(&DAT_00c212a0)[local_4c];
        afStack_18[1] = afStack_18[0];
        afStack_30[2] = afStack_30[1];
        afStack_18[2] = (float)(int)(short)(&DAT_00c2132c)[local_4c];
        afStack_18[4] = afStack_18[2];
        afStack_30[3] = afStack_30[0];
        afStack_18[5] = afStack_18[2];
        afStack_18[3] = afStack_18[0];
        afStack_30[4] = afStack_30[1];
        afStack_30[5] = afStack_30[0];
        if (0 < iVar3) {
          iStack_50 = iVar3;
          do {
            iVar9 = 0;
            iVar8 = iVar7;
            do {
              (&DAT_00c4d958)[iVar8 * 9] = *(undefined4 *)((int)afStack_30 + iVar9);
              (&DAT_00c4d95c)[iVar8 * 9] = *(undefined4 *)((int)afStack_18 + iVar9);
              (&DAT_00c4d960)[iVar8 * 9] = fStack_58;
              iVar7 = iVar8 + 1;
              (&DAT_00c4d970)[iVar8 * 9] =
                   ((uVar6 & 0xff | uVar2 << 8) << 8 | uVar6 >> 8 & 0xff) << 8 |
                   DAT_008d37e8 >> 0x10 & 0xff;
              if (iVar7 == 0x7fe) {
                iVar7 = FUN_007ef450(&DAT_00c4d958,0x7fe,0,8);
                if (iVar7 != 0) {
                  FUN_007ef6b0(3);
                  FUN_007ef520();
                }
                iVar7 = 0;
                uVar6 = DAT_008d37e8;
              }
              iVar9 = iVar9 + 4;
              iVar8 = iVar7;
            } while (iVar9 < 0x18);
            fStack_58 = fStack_58 + fVar1;
            iStack_50 = iStack_50 + -1;
          } while (iStack_50 != 0);
        }
        local_4c = local_4c + 1;
      } while (local_4c < iVar5);
      if ((0 < iVar7) && (iVar5 = FUN_007ef450(&DAT_00c4d958,iVar7,0,8), iVar5 != 0)) {
        FUN_007ef6b0(3);
        FUN_007ef520();
      }
    }
    FUN_00700e00();
    return;
  }
  DAT_00c228e4 = 0;
  return;
}



/* entry 0x006ED9A0; bounded CFG instructions=160; body bytes=1002 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_006ed9a0(void)

{
  float fVar1;
  bool bVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  float *pfVar7;
  int iVar8;
  float *pfVar9;
  int iVar10;
  short sVar11;
  float fStack_60;
  float fStack_58;
  float fStack_54;
  float fStack_50;
  float fStack_4c;
  uint uStack_48;
  uint uStack_44;
  int iStack_40;
  undefined4 uStack_3c;
  float fStack_38;
  float fStack_34;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  float fStack_c;
  
  (**(code **)(DAT_00c97b24 + 0x20))(1,DAT_00c228b8);
  FUN_006f2710();
  uStack_3c = 0xbcf5c28f;
  iStack_40 = 0;
  do {
    iVar10 = iStack_40;
    iVar8 = (&DAT_00c27994)[(short)iStack_40];
    if (iVar8 == 0) break;
    fStack_2c = *(float *)(*(int *)(iVar8 + 0x14) + 0x14);
    fStack_30 = *(float *)(*(int *)(iVar8 + 0x14) + 0x10);
    iVar6 = FUN_00535300();
    fStack_60 = *(float *)(iVar6 + 0xc) * _DAT_00858f50;
    if (*(short *)(iVar8 + 0x22) == 0x1cc) {
      fStack_60 = fStack_60 * _DAT_00858ee8;
    }
    uStack_44 = (uint)*(byte *)(iVar8 + 0x7c8);
    fVar1 = (float)uStack_44;
    pfVar9 = (float *)(DAT_00b6f03c + 0x30);
    fStack_50 = fVar1 * _DAT_00858c58 * DAT_00858b50;
    if (DAT_00b6f03c == 0) {
      pfVar9 = (float *)&DAT_00b6f02c;
    }
    if (*(int *)(iVar8 + 0x14) == 0) {
      pfVar7 = (float *)(iVar8 + 4);
    }
    else {
      pfVar7 = (float *)(*(int *)(iVar8 + 0x14) + 0x30);
    }
    fVar3 = SQRT((*pfVar7 - *pfVar9) * (*pfVar7 - *pfVar9) +
                 (pfVar7[1] - pfVar9[1]) * (pfVar7[1] - pfVar9[1]));
    if (_DAT_00858b40 < fVar3) {
      fStack_50 = (_DAT_00858a14 - fVar3) * _DAT_00858f10 * fStack_50;
    }
    uStack_48 = (uint)*(ushort *)(iVar8 + 0x644);
    sVar11 = 1;
    if (1 < uStack_48) {
      uStack_44 = 1;
      fVar1 = ((fVar1 * _DAT_00858cec + _DAT_00858b8c) / DAT_008d3940) *
              (DAT_008d3940 - *(float *)(iVar8 + 0x748)) * fStack_60 + fStack_60;
      do {
        pfVar9 = (float *)(iVar8 + 0x64c + uStack_44 * 8);
        fStack_38 = *(float *)(iVar8 + 0x640 + uStack_44 * 8) -
                    *(float *)(iVar8 + 0x648 + uStack_44 * 8);
        bVar2 = true;
        fStack_34 = *(float *)(iVar8 + 0x644 + uStack_44 * 8) - *pfVar9;
        fVar4 = fStack_38 * fStack_38 + fStack_34 * fStack_34;
        if (_DAT_0085eed4 < fVar4) {
          fVar4 = SQRT(fVar4);
          fVar5 = _DAT_00858624 / fVar4;
          fStack_38 = fVar5 * fStack_38;
          fStack_34 = fVar5 * fStack_34;
          if (_DAT_00858ce4 < fVar4) {
            bVar2 = false;
          }
        }
        fStack_4c = (float)*(byte *)(uStack_44 + 0x7c8 + iVar8);
        fStack_58 = ((fStack_4c * _DAT_00858cec + _DAT_00858b8c) / DAT_008d3940) *
                    (DAT_008d3940 - *(float *)(iVar8 + 0x748 + uStack_44 * 4)) * fStack_60 +
                    fStack_60;
        fStack_10 = *(float *)(iVar8 + 0x640 + uStack_44 * 8) - fStack_2c * fVar1;
        fStack_c = fVar1 * fStack_30 + *(float *)(iVar8 + 0x644 + uStack_44 * 8);
        fStack_18 = fStack_2c * fVar1 + *(float *)(iVar8 + 0x640 + uStack_44 * 8);
        fStack_14 = *(float *)(iVar8 + 0x644 + uStack_44 * 8) - fVar1 * fStack_30;
        fStack_20 = fStack_58 * fStack_34 + *(float *)(iVar8 + 0x648 + uStack_44 * 8);
        fStack_1c = *pfVar9 - fStack_58 * fStack_38;
        fStack_28 = *(float *)(iVar8 + 0x648 + uStack_44 * 8) - fStack_58 * fStack_34;
        fStack_24 = fStack_58 * fStack_38 + *pfVar9;
        fStack_54 = (_DAT_00858624 - (float)(int)uStack_44 / (float)uStack_48) * _DAT_00858970;
        if (sVar11 < 3) {
          fStack_54 = fStack_54 * (float)(int)uStack_44 * _DAT_00859040;
        }
        fStack_54 = (fStack_4c * _DAT_00858c58 + _DAT_00858fcc) * fStack_54;
        if (_DAT_00858b40 < fVar3) {
          fStack_54 = (_DAT_00858a14 - fVar3) * _DAT_00858f10 * fStack_54;
        }
        if (bVar2) {
          FUN_006ea260(&fStack_10,&fStack_18,&fStack_20,&fStack_28,&uStack_3c,&fStack_58,&fStack_50,
                       &fStack_54,&uStack_3c);
        }
        fStack_30 = fStack_38;
        fStack_50 = fStack_54;
        fStack_2c = fStack_34;
        sVar11 = sVar11 + 1;
        uStack_48 = (uint)*(ushort *)(iVar8 + 0x644);
        uStack_44 = (uint)sVar11;
        iVar10 = iStack_40;
        fVar1 = fStack_58;
      } while ((int)uStack_44 < (int)uStack_48);
    }
    iStack_40 = iVar10 + 1;
  } while ((short)iStack_40 < 4);
  if (DAT_00c4b950 != 0) {
    thunk_FUN_00541336();
    iVar8 = FUN_007ef450(&DAT_00c4d958,DAT_00c4b950,0,1);
    if (iVar8 != 0) {
      FUN_007ef550(3,&DAT_00c4b958,DAT_00c4b954);
      FUN_007ef520();
    }
  }
  DAT_00c4b950 = 0;
  DAT_00c4b954 = 0;
  return;
}



/* entry 0x006EF673; bounded CFG instructions=160; body bytes=2633 */

/* WARNING: Removing unreachable block (ram,0x006efa04) */
/* WARNING: Removing unreachable block (ram,0x006efa57) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_006ef673(void)

{
  bool bVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  bool bVar5;
  float fVar6;
  undefined1 uVar7;
  float *pfVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  short *psVar16;
  int iVar17;
  float10 fVar18;
  float10 fVar19;
  undefined4 uStack00000014;
  undefined4 uStack00000018;
  undefined4 uStack0000001c;
  int iStack00000020;
  uint in_stack_00000038;
  uint in_stack_00000048;
  uint in_stack_00000058;
  uint in_stack_00000068;
  
  DAT_00c4b954 = 0;
  DAT_00c4b950 = 0;
  (**(code **)(DAT_00c97b24 + 0x20))(1);
  (**(code **)(DAT_00c97b24 + 0x20))(0xe,1);
  (**(code **)(DAT_00c97b24 + 0x20))(10,5);
  (**(code **)(DAT_00c97b24 + 0x20))(0xb,6);
  (**(code **)(DAT_00c97b24 + 0x20))(0x1e,0);
  (**(code **)(DAT_00c97b24 + 0x20))(0xc,1);
  iVar14 = 0;
  if (0 < DAT_00c215ec) {
    do {
      iVar15 = (int)(short)(&DAT_00c21560)[iVar14];
      iVar17 = (int)(short)(&DAT_00c214d0)[iVar14];
      if (DAT_00b6f03c == 0) {
        pfVar8 = (float *)&DAT_00b6f02c;
      }
      else {
        pfVar8 = (float *)(DAT_00b6f03c + 0x30);
      }
      fVar2 = *pfVar8 - (((float)iVar15 + _DAT_00858b8c) * _DAT_00858b58 - _DAT_00859a94);
      fVar3 = pfVar8[1] - (((float)iVar17 + _DAT_00858b8c) * _DAT_00858b58 - _DAT_00859a94);
      bVar1 = _DAT_008d3934 <= SQRT(fVar2 * fVar2 + fVar3 * fVar3);
      bVar5 = false;
      uStack0000001c = 0;
      uStack00000014 = 0x3f800000;
      iStack00000020 = 0;
      uStack00000018 = 0x3f800000;
      if ((((iVar15 < 0) || (iVar17 < 0)) || (0xb < iVar15)) || (0xb < iVar17)) {
LAB_006ef7f7:
        if (bVar1) {
          FUN_006e6870(iVar15,iVar17,uStack0000001c,uStack00000014,0,0x3f800000);
        }
        else {
          FUN_006e6a10(iVar15,iVar17,uStack0000001c,uStack00000014);
        }
      }
      else {
        bVar4 = false;
        bVar5 = false;
        if (iVar15 == 0) {
          uStack00000014 = 0x3d23d70a;
LAB_006ef7c9:
          bVar4 = true;
        }
        else if (iVar15 == 0xb) {
          uStack0000001c = 0x3f75c28f;
          uStack00000014 = 0x3f800000;
          goto LAB_006ef7c9;
        }
        if (iVar17 == 0) {
          uStack00000018 = 0x3d23d70a;
LAB_006ef7ee:
          bVar5 = true;
        }
        else if (iVar17 == 0xb) {
          iStack00000020 = 0x3f75c28f;
          uStack00000018 = 0x3f800000;
          goto LAB_006ef7ee;
        }
        if (bVar4) goto LAB_006ef7f7;
      }
      if (bVar5) {
        if (bVar1) {
          FUN_006e6870(iVar15,iVar17,0,0x3f800000,iStack00000020,uStack00000018);
        }
        else {
          FUN_006e6a10(iVar15,iVar17,0,0x3f800000,iStack00000020,uStack00000018);
        }
      }
      iVar14 = iVar14 + 1;
    } while (iVar14 < DAT_00c215ec);
  }
  if (DAT_00c4b950 != 0) {
    thunk_FUN_00541336();
    iVar14 = FUN_007ef450(&DAT_00c4d958,DAT_00c4b950,0,1);
    if (iVar14 != 0) {
      FUN_007ef550(3,&DAT_00c4b958,DAT_00c4b954);
      FUN_007ef520();
    }
  }
  DAT_00c4b950 = 0;
  DAT_00c4b954 = 0;
  (**(code **)(DAT_00c97b24 + 0x20))(8,0);
  (**(code **)(DAT_00c97b24 + 0x20))(2,DAT_008d3930);
  fVar6 = DAT_008d3928;
  fVar2 = DAT_00b7cb5c * _DAT_00c22890 * _DAT_008d392c;
  _DAT_008d3824 = _DAT_00859018 * fVar2 + _DAT_008d3824;
  fVar3 = DAT_00b7cb5c * _DAT_00c22894 * _DAT_008d392c;
  _DAT_008d3828 = _DAT_00859018 * fVar3 + _DAT_008d3828;
  if (_DAT_00858624 < _DAT_008d3824) {
    _DAT_008d3824 = _DAT_008d3824 - _DAT_00858624;
  }
  if (_DAT_00858624 < _DAT_008d3828) {
    _DAT_008d3828 = _DAT_008d3828 - _DAT_00858624;
  }
  DAT_008d382c = fVar2 * _DAT_00858cec + DAT_008d382c;
  _DAT_008d3830 = fVar3 * _DAT_00858cec + _DAT_008d3830;
  if (_DAT_00858624 < DAT_008d382c) {
    DAT_008d382c = DAT_008d382c - _DAT_00858624;
  }
  if (_DAT_00858624 < _DAT_008d3830) {
    _DAT_008d3830 = _DAT_008d3830 - _DAT_00858624;
  }
  fVar18 = (float10)(DAT_00b7cb84 & 0xfff) * (float10)_DAT_00872174;
  fVar19 = (float10)fsin(fVar18);
  _DAT_00c21184 =
       (float)(fVar19 * (float10)_DAT_00c812e8 * (float10)_DAT_00859018 + (float10)_DAT_008d3824);
  fVar18 = (float10)fcos(fVar18);
  _DAT_00c21180 =
       (float)(fVar18 * (float10)_DAT_00c812e8 * (float10)_DAT_00859018 + (float10)_DAT_008d3828);
  fVar2 = (float)(DAT_00b7cb84 & 0x1fff) * _DAT_00872170;
  _DAT_00c2117c = DAT_008d382c;
  fVar18 = (float10)fcos((float10)fVar2);
  _DAT_00c21178 = (float)(fVar18 * (float10)_DAT_0087216c + (float10)_DAT_008d3830);
  iVar14 = _rand();
  fVar3 = DAT_008d3928;
  _DAT_00c21174 = (float)iVar14 * _DAT_00858c7c * fVar6;
  iVar14 = _rand();
  fVar19 = (float10)fsin((float10)fVar2);
  _DAT_00c21174 = (float)(fVar19 * (float10)_DAT_008d3834 + (float10)_DAT_00c21174);
  _DAT_00c21170 = (float)fVar18 * _DAT_008d3834 + (float)iVar14 * _DAT_00858c7c * fVar3;
  uVar7 = FUN_00821b40();
  _DAT_00c2116c = CONCAT31(_DAT_00c2116d,uVar7);
  uVar7 = FUN_00821b40();
  _DAT_00c2116c = CONCAT11(uVar7,DAT_00c2116c);
  uVar7 = FUN_00821b40();
  _DAT_00c2116c = CONCAT12(uVar7,_DAT_00c2116c);
  DAT_00c21168 = _DAT_00c2116c;
  DAT_008d380c = FUN_00821b40();
  iVar14 = (DAT_008d380c << 8) / (0x100 - DAT_008d380c);
  DAT_008d3808 = 0xff;
  if (iVar14 < 0x100) {
    DAT_008d3808 = iVar14;
  }
  DAT_00c4b954 = 0;
  DAT_00c4b950 = 0;
  (**(code **)(DAT_00c97b24 + 0x20))(1,DAT_00c228a8);
  (**(code **)(DAT_00c97b24 + 0x20))(0xe,1);
  (**(code **)(DAT_00c97b24 + 0x20))(10,5);
  (**(code **)(DAT_00c97b24 + 0x20))(0xb,6);
  iVar14 = 0;
  if (0 < DAT_00c22884) {
    do {
      if (((&DAT_00c2285a)[iVar14 * 8] & 1) != 0) {
        iVar15 = (int)(short)(&DAT_00c22858)[iVar14 * 4];
        iVar10 = (int)(short)(&DAT_00c22856)[iVar14 * 4];
        iVar17 = iVar15 * 0x14;
        iVar12 = (int)(short)(&DAT_00c22854)[iVar14 * 4];
        iVar11 = iVar10 * 0x14;
        iVar13 = iVar12 * 0x14;
        FUN_006ee240((int)(short)(&DAT_00c22910)[iVar12 * 10],
                     (int)(short)(&DAT_00c22912)[iVar12 * 10],(&DAT_00c22914)[iVar12 * 5],
                     *(undefined4 *)(&DAT_00c22918 + iVar13),*(undefined4 *)(&DAT_00c2291c + iVar13)
                     ,*(undefined4 *)(&DAT_00c22920 + iVar13),
                     (int)(short)(&DAT_00c22910)[iVar10 * 10],
                     (int)(short)(&DAT_00c22912)[iVar10 * 10],(&DAT_00c22914)[iVar10 * 5],
                     *(undefined4 *)(&DAT_00c22918 + iVar11),*(undefined4 *)(&DAT_00c2291c + iVar11)
                     ,*(undefined4 *)(&DAT_00c22920 + iVar11),
                     (int)(short)(&DAT_00c22910)[iVar15 * 10],
                     (int)(short)(&DAT_00c22912)[iVar15 * 10],(&DAT_00c22914)[iVar15 * 5],
                     *(undefined4 *)(&DAT_00c22918 + iVar17),*(undefined4 *)(&DAT_00c2291c + iVar17)
                     ,*(undefined4 *)(&DAT_00c22920 + iVar17));
        (&DAT_00c2285a)[iVar14 * 8] = (&DAT_00c2285a)[iVar14 * 8] & 0xfe;
      }
      iVar14 = iVar14 + 1;
    } while (iVar14 < DAT_00c22884);
  }
  iStack00000020 = 0;
  if (0 < DAT_00c22888) {
    psVar16 = &DAT_00c21c94;
    do {
      if ((*(byte *)(psVar16 + 2) & 1) != 0) {
        if (DAT_00c228dc != '\0') {
          uVar7 = FUN_00821b40();
          _DAT_00c2116c = CONCAT31(_DAT_00c2116d,uVar7);
          uVar7 = FUN_00821b40();
          _DAT_00c2116c = CONCAT11(uVar7,DAT_00c2116c);
          uVar7 = FUN_00821b40();
          _DAT_00c2116c = CONCAT12(uVar7,_DAT_00c2116c);
          uVar7 = FUN_00821b40();
          _DAT_00c2116c = CONCAT13(uVar7,_DAT_00c2116c);
          DAT_00c21168 = _DAT_00c2116c;
        }
        iVar10 = (int)*psVar16;
        iVar14 = psVar16[1] * 0x14;
        iVar12 = (int)psVar16[-1];
        iVar15 = (int)psVar16[-2];
        iVar11 = iVar10 * 0x14;
        iVar13 = iVar12 * 0x14;
        iVar17 = iVar15 * 0x14;
        FUN_006ec5d0((int)(short)(&DAT_00c22910)[iVar15 * 10],
                     (int)(short)(&DAT_00c22910)[iVar12 * 10],
                     (int)(short)(&DAT_00c22912)[iVar15 * 10],
                     (int)(short)(&DAT_00c22912)[iVar10 * 10],(&DAT_00c22914)[iVar15 * 5],
                     *(undefined4 *)(&DAT_00c22918 + iVar17),*(undefined4 *)(&DAT_00c2291c + iVar17)
                     ,*(undefined4 *)(&DAT_00c22920 + iVar17),(&DAT_00c22914)[iVar12 * 5],
                     *(undefined4 *)(&DAT_00c22918 + iVar13),*(undefined4 *)(&DAT_00c2291c + iVar13)
                     ,*(undefined4 *)(&DAT_00c22920 + iVar13),(&DAT_00c22914)[iVar10 * 5],
                     *(undefined4 *)(&DAT_00c22918 + iVar11),*(undefined4 *)(&DAT_00c2291c + iVar11)
                     ,*(undefined4 *)(&DAT_00c22920 + iVar11),(&DAT_00c22914)[psVar16[1] * 5],
                     *(undefined4 *)(&DAT_00c22918 + iVar14),*(undefined4 *)(&DAT_00c2291c + iVar14)
                     ,*(undefined4 *)(&DAT_00c22920 + iVar14));
        *(byte *)(psVar16 + 2) = *(byte *)(psVar16 + 2) & 0xfe;
      }
      iStack00000020 = iStack00000020 + 1;
      psVar16 = psVar16 + 5;
    } while (iStack00000020 < DAT_00c22888);
  }
  iVar14 = 0;
  if (0 < DAT_00c215ec) {
    do {
      if ((((short)(&DAT_00c21560)[iVar14] < 0) || (0xb < (short)(&DAT_00c21560)[iVar14])) ||
         (((short)(&DAT_00c214d0)[iVar14] < 0 || (0xb < (short)(&DAT_00c214d0)[iVar14])))) {
        in_stack_00000038 = in_stack_00000038 & 0xffff0000;
        in_stack_00000048 = in_stack_00000048 & 0xffff0000;
        in_stack_00000058 = in_stack_00000058 & 0xffff0000;
        in_stack_00000068 = in_stack_00000068 & 0xffff0000;
        uVar9 = FUN_00821b40(0,0x3f800000,0,in_stack_00000068,0,0x3f800000,0,in_stack_00000058,0,
                             0x3f800000,0,in_stack_00000048,0,0x3f800000,0,in_stack_00000038);
        uVar9 = FUN_00821b40(uVar9);
        uVar9 = FUN_00821b40(uVar9);
        uVar9 = FUN_00821b40(uVar9);
        FUN_006ec5d0(uVar9);
      }
      iVar14 = iVar14 + 1;
    } while (iVar14 < DAT_00c215ec);
  }
  if (DAT_00c4b950 != 0) {
    thunk_FUN_00541336();
    iVar14 = FUN_007ef450(&DAT_00c4d958,DAT_00c4b950,0,1);
    if (iVar14 != 0) {
      FUN_007ef550(3,&DAT_00c4b958,DAT_00c4b954);
      FUN_007ef520();
    }
  }
  DAT_00c4b950 = 0;
  DAT_00c4b954 = 0;
  FUN_006ed9a0();
  FUN_00734650();
  return;
}



/* entry 0x006FAEC0; bounded CFG instructions=160; body bytes=1894 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_006faec0(void)

{
  float *pfVar1;
  float fVar2;
  byte bVar3;
  short sVar4;
  bool bVar5;
  float fVar6;
  float fVar7;
  bool bVar8;
  char cVar9;
  float *pfVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 *puVar13;
  int iVar14;
  float *pfVar15;
  int *piVar16;
  undefined1 *puVar17;
  undefined1 uStack_ac;
  undefined1 uStack_ab;
  undefined1 uStack_aa;
  undefined1 uStack_a9;
  float fStack_a8;
  float fStack_a4;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  float fStack_94;
  undefined1 uStack_90;
  undefined1 uStack_8f;
  undefined1 uStack_8e;
  undefined1 uStack_8d;
  float *pfStack_8c;
  float fStack_88;
  float fStack_84;
  float fStack_80;
  int local_7c;
  float fStack_78;
  float fStack_74;
  int iStack_70;
  int local_6c;
  float fStack_68;
  float fStack_64;
  float fStack_60;
  int local_5c;
  int local_58;
  float fStack_50;
  float fStack_4c;
  undefined1 auStack_48 [4];
  undefined1 auStack_44 [12];
  undefined1 auStack_38 [12];
  undefined1 auStack_2c [44];
  
  local_5c = *(int *)(*(int *)(DAT_00c1703c + 0x60) + 0xc);
  local_58 = *(int *)(*(int *)(DAT_00c1703c + 0x60) + 0x10);
  local_6c = local_5c / 2;
  local_7c = local_58 / 2;
  (**(code **)(DAT_00c97b24 + 0x20))(8,0);
  (**(code **)(DAT_00c97b24 + 0x20))(0xc,1);
  (**(code **)(DAT_00c97b24 + 0x20))(10,2);
  (**(code **)(DAT_00c97b24 + 0x20))(0xb,2);
  (**(code **)(DAT_00c97b24 + 0x20))(6,1);
  bVar8 = true;
  iStack_70 = 0x40;
  piVar16 = &DAT_00c3e090;
  pfVar15 = pfStack_8c;
  do {
    if ((piVar16[-0xb] != 0) &&
       (((char)piVar16[-2] != '\0' || (*(char *)((int)piVar16 + -9) != '\0')))) {
      iVar14 = *piVar16;
      if (iVar14 == 0) {
        fStack_9c = (float)piVar16[-0xe];
        fStack_98 = (float)piVar16[-0xd];
        fStack_94 = (float)piVar16[-0xc];
      }
      else {
        if (((*(byte *)(iVar14 + 0x36) & 7) == 2) && (*(int *)(iVar14 + 0x594) == 9)) {
          iVar14 = iVar14 + 0x5cc;
          puVar17 = auStack_44;
        }
        else {
          if (*(int *)(iVar14 + 0x14) == 0) {
            FUN_0054f560();
            FUN_0054f1b0(*(undefined4 *)(iVar14 + 0x14));
          }
          iVar14 = *(int *)(iVar14 + 0x14);
          puVar17 = auStack_38;
        }
        pfVar10 = (float *)FUN_0059c890(puVar17,iVar14,piVar16 + -0xe);
        fStack_9c = *pfVar10;
        fStack_98 = pfVar10[1];
        fStack_94 = pfVar10[2];
      }
      cVar9 = FUN_0070ce30(&fStack_9c,&fStack_a8,&fStack_78,&fStack_74,1,1);
      if (cVar9 == '\0') {
        *(byte *)(piVar16 + -1) = *(byte *)(piVar16 + -1) | 2;
      }
      else {
        bVar3 = *(byte *)(piVar16 + -1);
        bVar5 = fStack_a8 < DAT_00858b50;
        *(byte *)(piVar16 + -1) = bVar3 & 0xfd;
        if ((((bVar5) || (fStack_a4 < DAT_00858b50)) || ((float)local_5c < fStack_a8)) ||
           ((float)local_58 < fStack_a4)) {
          *(byte *)(piVar16 + -1) = bVar3 & 0xfd | 2;
        }
        if (((char)piVar16[-2] != '\0') && (fStack_a0 < (float)piVar16[-7])) {
          fVar6 = _DAT_00858624 / fStack_a0;
          uVar11 = FUN_00821b40();
          if ((*(byte *)(piVar16 + -1) & 1) == 0) {
            if (!bVar8) {
              (**(code **)(DAT_00c97b24 + 0x20))(6,1);
              bVar8 = true;
            }
          }
          else if (((*(byte *)(piVar16 + -1) & 1) == 1) && (bVar8)) {
            (**(code **)(DAT_00c97b24 + 0x20))(6,0);
            bVar8 = false;
          }
          if (piVar16[-10] != 0) {
            fVar7 = _DAT_00858a10;
            if (fStack_a0 < _DAT_00858a10) {
              fVar7 = fStack_a0;
            }
            fVar7 = fVar7 * DAT_00c81300 * _DAT_00859038 + _DAT_00858624;
            if (piVar16[-0xb] == 1) {
              fStack_a0 = *(float *)(DAT_00c1703c + 0x84) * _DAT_00858ef0;
            }
            (**(code **)(DAT_00c97b24 + 0x20))(6,1);
            (**(code **)(DAT_00c97b24 + 0x20))(1,*(undefined4 *)piVar16[-10]);
            fStack_84 = fStack_98;
            fStack_88 = fStack_9c;
            fStack_80 = fStack_94;
            if (DAT_00b6f03c == 0) {
              pfVar10 = (float *)&DAT_00b6f02c;
            }
            else {
              pfVar10 = (float *)(DAT_00b6f03c + 0x30);
            }
            fStack_60 = fStack_94 - pfVar10[2];
            fStack_64 = fStack_98 - pfVar10[1];
            fStack_68 = fStack_9c - *pfVar10;
            FUN_0059c910();
            fVar2 = (float)piVar16[-6];
            fStack_50 = fStack_64 * fVar2;
            fStack_4c = fStack_60 * fVar2;
            fStack_88 = fStack_88 - fStack_68 * fVar2;
            fStack_84 = fStack_84 - fStack_50;
            fStack_80 = fStack_80 - fStack_4c;
            cVar9 = FUN_0070ce30(&fStack_88,&fStack_a8,&fStack_78,&fStack_74,1,1);
            if (cVar9 != '\0') {
              uVar12 = FUN_00821b40(uVar11,fVar6 * _DAT_00858ba4,0,0xff);
              uVar12 = FUN_00821b40(uVar12);
              uVar12 = FUN_00821b40(uVar12);
              FUN_0070d490(fStack_a8,fStack_a4,fStack_a0,fStack_78 * (float)piVar16[-9],
                           fVar7 * (float)piVar16[-9] * fStack_74,uVar12);
            }
          }
          cVar9 = *(char *)((int)piVar16 + -6);
          if (cVar9 != '\0') {
            if (cVar9 == '\x01') {
              pfVar15 = (float *)&DAT_008d4b68;
            }
            else if (cVar9 == '\x02') {
              pfVar15 = (float *)&DAT_008d4d88;
            }
            (**(code **)(DAT_00c97b24 + 0x20))(6,0);
            _rand();
            (**(code **)(DAT_00c97b24 + 0x20))(1,*DAT_00c3e000);
            sVar4 = *(short *)(pfVar15 + 4);
            while (sVar4 != 0) {
              uStack_90 = FUN_00821b40();
              uStack_8f = FUN_00821b40();
              uStack_8e = FUN_00821b40();
              uStack_8d = 0xff;
              if (DAT_00b6f03c == 0) {
                puVar13 = &DAT_00b6f02c;
              }
              else {
                puVar13 = (undefined4 *)(DAT_00b6f03c + 0x30);
              }
              cVar9 = FUN_0056ba00(&fStack_9c,puVar13,auStack_2c,auStack_48,0,1,1,0,0,0,0,1);
              if (cVar9 == '\0') {
                FUN_0070f440((fStack_a8 - (float)local_6c) * *pfVar15 + (float)local_6c,
                             (fStack_a4 - (float)local_7c) * *pfVar15 + (float)local_7c,
                             pfVar15[1] * _DAT_00858b90,pfVar15[1] * _DAT_00858b90,&uStack_90,0xff,
                             0xff);
              }
              sVar4 = *(short *)(pfVar15 + 9);
              pfVar15 = pfVar15 + 5;
            }
            (**(code **)(DAT_00c97b24 + 0x20))(6,1);
            if ((((*(char *)((int)piVar16 + -6) == '\x02') && (_DAT_00c812d0 != DAT_00858b50)) &&
                (DAT_00b72914 == 0)) && (pfVar15 = (float *)&DAT_008d4d88, DAT_008d4d98 != 0)) {
              fVar6 = (float)local_7c;
              fVar7 = (float)local_6c;
              pfVar10 = pfVar15;
              do {
                pfStack_8c = (float *)((int)*(short *)(pfVar10 + 2) * (uint)*(byte *)(piVar16 + -3))
                ;
                uStack_ac = FUN_00821b40();
                uStack_ab = 0;
                uStack_aa = 0;
                uStack_a9 = 0xff;
                FUN_0070f440((fStack_a8 - fVar7) * (*pfVar10 + _DAT_00858c28) + fVar7,
                             (fStack_a4 - fVar6) * (*pfVar10 + _DAT_00858c28) + fVar6,pfVar10[1],
                             pfVar10[1],&uStack_ac,
                             (int)*(short *)((int)pfVar10 + 0xe) * (int)(short)uVar11 >> 8,0xff);
                pfStack_8c = (float *)((uint)*(byte *)((int)piVar16 + -10) *
                                      (int)*(short *)(pfVar10 + 3));
                uStack_ac = 0;
                uStack_ab = 0;
                uStack_aa = FUN_00821b40();
                uStack_a9 = 0xff;
                FUN_0070f440((fStack_a8 - fVar7) * (*pfVar10 - _DAT_00858c28) + fVar7,
                             (fStack_a4 - fVar6) * (*pfVar10 - _DAT_00858c28) + fVar6,pfVar10[1],
                             pfVar10[1],&uStack_ac,
                             (int)*(short *)((int)pfVar10 + 0xe) * (int)(short)uVar11 >> 8,0xff);
                pfVar15 = pfVar10 + 5;
                pfVar1 = pfVar10 + 9;
                pfVar10 = pfVar15;
              } while (*(short *)pfVar1 != 0);
            }
          }
        }
      }
    }
    piVar16 = piVar16 + 0xf;
    iStack_70 = iStack_70 + -1;
  } while (iStack_70 != 0);
  FUN_0070cf20();
  return;
}



/* entry 0x006FB630; bounded CFG instructions=160; body bytes=993 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_006fb630(void)

{
  float fVar1;
  char cVar2;
  short sVar3;
  byte *pbVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  char *pcVar8;
  undefined1 auStack_68 [4];
  float fStack_64;
  float fStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  float fStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  float fStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  float fStack_3c;
  undefined1 auStack_38 [12];
  undefined1 auStack_2c [8];
  float fStack_24;
  
  if (DAT_00c81308 < DAT_00858b50 != (DAT_00c81308 == DAT_00858b50)) {
    pbVar4 = &DAT_00c3e08e;
    do {
      *pbVar4 = *pbVar4 & 0xfb;
      pbVar4 = pbVar4 + 0x3c;
    } while ((int)pbVar4 < 0xc3ef8e);
    return;
  }
  thunk_FUN_0040a196();
  (**(code **)(DAT_00c97b24 + 0x20))(0xe,0);
  (**(code **)(DAT_00c97b24 + 0x20))(8,0);
  (**(code **)(DAT_00c97b24 + 0x20))(6,0);
  (**(code **)(DAT_00c97b24 + 0x20))(0xc,1);
  (**(code **)(DAT_00c97b24 + 0x20))(10,2);
  (**(code **)(DAT_00c97b24 + 0x20))(0xb,2);
  (**(code **)(DAT_00c97b24 + 0x20))(1,*DAT_00c3e00c);
  iVar7 = 0;
  pcVar8 = &DAT_00c3e088;
  do {
    if ((*(int *)(pcVar8 + -0x24) != 0) &&
       (((*pcVar8 != '\0' || (pcVar8[-1] != '\0')) && (pcVar8[3] != '\0')))) {
      iVar6 = *(int *)(pcVar8 + 8);
      if (iVar6 == 0) {
        uStack_5c = *(undefined4 *)(pcVar8 + -0x30);
        uStack_58 = *(undefined4 *)(pcVar8 + -0x2c);
        fStack_54 = *(float *)(pcVar8 + -0x28);
      }
      else {
        if (*(int *)(iVar6 + 0x14) == 0) {
          FUN_0054f560();
          FUN_0054f1b0(*(undefined4 *)(iVar6 + 0x14));
        }
        puVar5 = (undefined4 *)FUN_0059c890(auStack_38,*(undefined4 *)(iVar6 + 0x14),pcVar8 + -0x30)
        ;
        uStack_5c = *puVar5;
        uStack_58 = puVar5[1];
        fStack_54 = (float)puVar5[2];
      }
      if ((pcVar8[6] & 4U) == 0) {
        cVar2 = FUN_005674e0(&uStack_5c,0xc47a0000,auStack_2c,auStack_68,1,0,0,0,1,0,0);
        if (cVar2 != '\0') {
          pcVar8[6] = pcVar8[6] | 4;
          goto LAB_006fb7d1;
        }
      }
      else if (((DAT_00b7cb4c + iVar7 & 0xfU) == 0) &&
              (cVar2 = FUN_005674e0(&uStack_5c,0xc47a0000,auStack_2c,auStack_68,1,0,0,0,1,0,0),
              cVar2 != '\0')) {
LAB_006fb7d1:
        *(float *)(pcVar8 + -0xc) = fStack_54 - fStack_24;
      }
      if (((pcVar8[6] & 4U) != 0) && (fVar1 = *(float *)(pcVar8 + -0xc), fVar1 < _DAT_00858ba4)) {
        if (DAT_00b6f03c == 0) {
          puVar5 = &DAT_00b6f02c;
        }
        else {
          puVar5 = (undefined4 *)(DAT_00b6f03c + 0x30);
        }
        if (fStack_54 - fVar1 < (float)puVar5[2] != (fStack_54 - fVar1 == (float)puVar5[2])) {
          fStack_3c = fStack_54 - (fVar1 + fVar1);
          uStack_44 = uStack_5c;
          uStack_40 = uStack_58;
          cVar2 = FUN_0070ce30(&uStack_44,&uStack_50,&fStack_60,&fStack_64,1,1);
          if (cVar2 != '\0') {
            fVar1 = *(float *)(pcVar8 + -0x14) * _DAT_00858f34;
            if (_DAT_0085adbc < *(float *)(pcVar8 + -0x14) * _DAT_00858f34) {
              fVar1 = _DAT_0085adbc;
            }
            if (fStack_48 < fVar1) {
              sVar3 = FUN_00821b40();
              iVar6 = (int)sVar3;
              FUN_0070e4a0(uStack_50,uStack_4c,*(undefined4 *)(DAT_00c97b24 + 0x18),
                           fStack_60 * *(float *)(pcVar8 + -0x1c) * _DAT_00858f34,
                           fStack_64 * *(float *)(pcVar8 + -0x1c) +
                           fStack_64 * *(float *)(pcVar8 + -0x1c),
                           (int)((uint)(byte)pcVar8[-4] * iVar6) >> 8,
                           (int)((uint)(byte)pcVar8[-3] * iVar6) >> 8,
                           (int)((uint)(byte)pcVar8[-2] * iVar6) >> 8,0x80,
                           _DAT_00858624 / *(float *)(DAT_00c1703c + 0x80),0xff);
            }
          }
        }
      }
    }
    pcVar8 = pcVar8 + 0x3c;
    iVar7 = iVar7 + 1;
    if (0xc3ef87 < (int)pcVar8) {
      FUN_0070cf20();
      (**(code **)(DAT_00c97b24 + 0x20))(10,5);
      (**(code **)(DAT_00c97b24 + 0x20))(0xb,6);
      (**(code **)(DAT_00c97b24 + 0x20))(0xc,0);
      (**(code **)(DAT_00c97b24 + 0x20))(8,1);
      (**(code **)(DAT_00c97b24 + 0x20))(6,1);
      return;
    }
  } while( true );
}



/* entry 0x007002D0; bounded CFG instructions=160; body bytes=2317 */

/* WARNING: Removing unreachable block (ram,0x00700ad6) */
/* WARNING: Removing unreachable block (ram,0x00700788) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_007002d0(void)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  char cVar7;
  short sVar8;
  short sVar9;
  int iVar10;
  undefined4 uVar11;
  float *pfVar12;
  byte bVar13;
  uint uVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  float fStack_b0;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  float fStack_88;
  int iStack_84;
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  float fStack_74;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float afStack_64 [2];
  float fStack_5c;
  float fStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  float fStack_40;
  undefined1 auStack_3c [8];
  float fStack_34;
  undefined1 auStack_2c [8];
  float fStack_24;
  
  if (DAT_00b5f851 != '\0') {
    return;
  }
  iVar17 = 0;
  (**(code **)(DAT_00c97b24 + 0x20))(0xe,0);
  (**(code **)(DAT_00c97b24 + 0x20))(8,0);
  (**(code **)(DAT_00c97b24 + 0x20))(6,1);
  (**(code **)(DAT_00c97b24 + 0x20))(0xc,1);
  (**(code **)(DAT_00c97b24 + 0x20))(10,2);
  (**(code **)(DAT_00c97b24 + 0x20))(0xb,2);
  (**(code **)(DAT_00c97b24 + 0x20))(1,*DAT_00c6aa78);
  thunk_FUN_0040a196();
  iStack_84 = 0;
  if (0 < DAT_00c3f0d0) {
    do {
      if ((&DAT_00c3f10d)[iVar17] == '\x01') {
        fStack_b0 = 9.0;
        if (DAT_00c81300 != DAT_00858b50) goto LAB_0070039d;
      }
      else if ((&DAT_00c3f10d)[iVar17] == '\x02') {
        fStack_b0 = 3.0;
LAB_0070039d:
        cVar7 = (&DAT_00c3f10c)[iVar17];
        if (cVar7 == '\x01') {
          fStack_34 = *(float *)((int)&DAT_00c3f0f0 + iVar17) * _DAT_00858ccc;
          fStack_5c = fStack_34 + *(float *)((int)&DAT_00c3f0e4 + iVar17);
          sVar8 = FUN_00821b40();
          uVar14 = (int)sVar8 & 0x80000003;
          if ((int)uVar14 < 0) {
            uVar14 = (uVar14 - 1 | 0xfffffffc) + 1;
          }
          iVar10 = (int)sVar8 - uVar14;
          sVar8 = FUN_00821b40();
          if (iVar10 <= sVar8 + 4) {
            sVar9 = FUN_00821b40();
            uVar14 = (int)sVar9 & 0x80000003;
            if ((int)uVar14 < 0) {
              uVar14 = (uVar14 - 1 | 0xfffffffc) + 1;
            }
            iVar15 = (int)sVar9 - uVar14;
            sVar9 = FUN_00821b40();
            do {
              if (iVar15 <= sVar9 + 4) {
                iVar16 = iVar15;
                do {
                  bVar13 = (byte)(iVar16 >> 2) ^ (byte)(iVar10 >> 2);
                  if ((bVar13 & 1) != 0) {
                    fVar1 = (float)iVar10;
                    fVar2 = fVar1 - *(float *)((int)&DAT_00c3f0e0 + iVar17);
                    fVar3 = (float)iVar16;
                    fVar4 = fVar3 - *(float *)((int)&DAT_00c3f0e4 + iVar17);
                    fVar5 = fVar4 * *(float *)((int)&DAT_00c3f0f0 + iVar17) +
                            fVar2 * *(float *)((int)&DAT_00c3f0ec + iVar17);
                    if (((DAT_00858b50 < fVar5) && (fVar5 < _DAT_00858ccc)) &&
                       ((fVar2 * fVar2 + fVar4 * fVar4) - fVar5 * fVar5 < _DAT_00858fe8)) {
                      fStack_78 = *(float *)((int)&DAT_00c3f0e8 + iVar17) + _DAT_0085862c;
                      fStack_80 = fVar1;
                      fStack_7c = fVar3;
                      cVar7 = FUN_005674e0(&fStack_80,fStack_78 - _DAT_00858ba4,auStack_2c,
                                           auStack_3c,1,0,0,0,1,0,0);
                      if (cVar7 != '\0') {
                        fStack_78 = fStack_24 + _DAT_00859918;
                        fVar2 = fVar1 - *(float *)((int)&DAT_00c3f0e0 + iVar17);
                        fVar4 = fVar3 - *(float *)((int)&DAT_00c3f0e4 + iVar17);
                        fVar5 = fStack_78 - *(float *)((int)&DAT_00c3f0e8 + iVar17);
                        fVar6 = fVar4 * *(float *)((int)&DAT_00c3f0f0 + iVar17) +
                                fVar2 * *(float *)((int)&DAT_00c3f0ec + iVar17) +
                                fVar5 * *(float *)((int)&DAT_00c3f0f4 + iVar17);
                        if (((DAT_00858b50 < fVar6) && (fVar6 < _DAT_00858ccc)) &&
                           (((fVar2 * fVar2 + fVar4 * fVar4 + fVar5 * fVar5) - fVar6 * fVar6 <
                             _DAT_00858fe8 &&
                            (fStack_48 = fVar1, fStack_44 = fVar3, fStack_40 = fStack_78,
                            cVar7 = FUN_0070ce30(&fStack_48,&uStack_90,&fStack_74,&fStack_6c,1,1),
                            cVar7 != '\0')))) {
                          iVar18 = (int)((short)(bVar13 & 0xf) >> 1);
                          uVar11 = FUN_00821b40(_DAT_00858624 / fStack_88,
                                                (float)(DAT_00b7cb84 & 0x1fff) *
                                                (float)_DAT_00872610,0xff);
                          uVar11 = FUN_00821b40(uVar11);
                          uVar11 = FUN_00821b40(uVar11);
                          uVar11 = FUN_00821b40(uVar11);
                          FUN_0070e780(uStack_90,uStack_8c,fStack_88,
                                       fStack_74 * *(float *)(&DAT_008d5068 + iVar18 * 4),
                                       fStack_6c * *(float *)(&DAT_008d5068 + iVar18 * 4),uVar11);
                        }
                      }
                    }
                  }
                  iVar16 = iVar16 + 4;
                } while (iVar16 <= sVar9 + 4);
              }
              iVar10 = iVar10 + 4;
            } while (iVar10 <= sVar8 + 4);
          }
        }
        else if ((((cVar7 == '\0') || (cVar7 == '\x04')) || (cVar7 == '\x03')) &&
                (cVar7 = FUN_006ffff0(*(undefined4 *)((int)&DAT_00c3f0e0 + iVar17),
                                      *(undefined4 *)((int)&DAT_00c3f0e4 + iVar17),
                                      *(undefined4 *)((int)&DAT_00c3f0e8 + iVar17),&fStack_70),
                cVar7 != '\0')) {
          sVar8 = FUN_00821b40();
          uVar14 = (int)sVar8 & 0x80000001;
          if ((int)uVar14 < 0) {
            uVar14 = (uVar14 - 1 | 0xfffffffe) + 1;
          }
          iVar10 = (int)sVar8 - uVar14;
          sVar8 = FUN_00821b40();
          if (iVar10 <= sVar8 + 2) {
            sVar9 = FUN_00821b40();
            uVar14 = (int)sVar9 & 0x80000001;
            if ((int)uVar14 < 0) {
              uVar14 = (uVar14 - 1 | 0xfffffffe) + 1;
            }
            iVar15 = (int)sVar9 - uVar14;
            sVar9 = FUN_00821b40();
            do {
              if (iVar15 <= sVar9 + 2) {
                iVar16 = iVar15;
                do {
                  bVar13 = (byte)(iVar16 / 2) ^ (byte)(iVar10 / 2);
                  if ((bVar13 & 1) != 0) {
                    fVar4 = (float)iVar16;
                    fVar2 = fVar4 - *(float *)((int)&DAT_00c3f0e4 + iVar17);
                    fVar1 = (float)iVar10;
                    fVar3 = (float)iVar10 - *(float *)((int)&DAT_00c3f0e0 + iVar17);
                    if (SQRT(fVar2 * fVar2 + fVar3 * fVar3) < fStack_b0) {
                      if (DAT_00b6f03c == 0) {
                        pfVar12 = (float *)&DAT_00b6f02c;
                      }
                      else {
                        pfVar12 = (float *)(DAT_00b6f03c + 0x30);
                      }
                      if (SQRT((fVar1 - *pfVar12) * (fVar1 - *pfVar12) +
                               (fVar4 - pfVar12[1]) * (fVar4 - pfVar12[1])) < _DAT_00858b48) {
                        fStack_50 = (float)iVar16;
                        fStack_4c = fStack_70 + _DAT_00858fa8;
                        fStack_54 = fVar1;
                        cVar7 = FUN_0070ce30(&fStack_54,&uStack_90,&fStack_68,afStack_64,1,1);
                        if (cVar7 != '\0') {
                          iVar18 = (int)((short)(bVar13 & 0xf) >> 1);
                          uVar11 = FUN_00821b40(_DAT_00858624 / fStack_88,
                                                (float)(iVar18 * 0x8fc + DAT_00b7cb84 & 0x7fff) *
                                                (float)_DAT_00872600,0xff);
                          uVar11 = FUN_00821b40(uVar11);
                          uVar11 = FUN_00821b40(uVar11);
                          uVar11 = FUN_00821b40(uVar11);
                          FUN_0070e780(uStack_90,uStack_8c,fStack_88,
                                       fStack_68 * *(float *)(&DAT_008d5068 + iVar18 * 4),
                                       afStack_64[0] * *(float *)(&DAT_008d5068 + iVar18 * 4) *
                                       _DAT_00858cb0,uVar11);
                        }
                      }
                    }
                  }
                  iVar16 = iVar16 + 2;
                } while (iVar16 <= sVar9 + 2);
              }
              iVar10 = iVar10 + 2;
            } while (iVar10 <= sVar8 + 2);
          }
        }
      }
      iStack_84 = iStack_84 + 1;
      iVar17 = iVar17 + 0x30;
    } while (iStack_84 < DAT_00c3f0d0);
  }
  FUN_0070cf20();
  return;
}



/* entry 0x00708300; bounded CFG instructions=160; body bytes=914 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00708300(void)

{
  undefined1 *puVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  byte *pbVar5;
  byte *pbVar6;
  undefined2 *puVar7;
  float *pfVar8;
  int *piVar9;
  int iVar10;
  char *pcVar11;
  byte bStack_17;
  byte bStack_16;
  byte bStack_15;
  int *piStack_14;
  char *pcStack_10;
  int iStack_c;
  uint uStack_8;
  undefined2 *puStack_4;
  
  DAT_00c4b954 = 0;
  DAT_00c4b950 = 0;
  (**(code **)(DAT_00c97b24 + 0x20))(8,0);
  (**(code **)(DAT_00c97b24 + 0x20))(6,1);
  (**(code **)(DAT_00c97b24 + 0x20))(0xc,1);
  (**(code **)(DAT_00c97b24 + 0x20))(0xe,0);
  (**(code **)(DAT_00c97b24 + 0x20))(0x1e,0);
  (**(code **)(DAT_00c97b24 + 0x20))(9,2);
  puVar1 = &DAT_00c4a06b;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + 0x40;
  } while ((int)puVar1 < 0xc4ac6b);
  pcStack_10 = &DAT_00c4a066;
  do {
    pcVar11 = pcStack_10;
    piVar9 = (int *)(pcStack_10 + -0x32);
    if ((*(int *)(pcStack_10 + -0x32) != 0) && (pcStack_10[5] == '\0')) {
      FUN_00707460(*pcStack_10);
      (**(code **)(DAT_00c97b24 + 0x20))(1,**(undefined4 **)(pcVar11 + -6));
      if ((int)pcVar11 < 0xc4ac66) {
        do {
          iVar4 = *piVar9;
          if (((iVar4 != 0) && (*pcVar11 == *(char *)((int)piVar9 + 0x32))) &&
             (piStack_14 = piVar9, *(int *)(pcVar11 + -6) == piVar9[0xb])) {
            do {
              FUN_00707850(*(char *)((int)piVar9 + 0x32),*(char *)((int)piVar9 + 0x39),
                           *(char *)((int)piVar9 + 0x33),(char)piVar9[0xd],
                           *(char *)((int)piVar9 + 0x35),&bStack_17,&bStack_16,&bStack_15);
              iVar10 = (int)*(short *)(iVar4 + 0x58);
              if (0xfff < DAT_00c4b954 + iVar10 * 3 + -6) {
                if ((DAT_00c4b950 != 0) &&
                   (iVar2 = FUN_007ef450(&DAT_00c4d958,DAT_00c4b950,0,1), iVar2 != 0)) {
                  FUN_007ef550(3,&DAT_00c4b958,DAT_00c4b954);
                  FUN_007ef520();
                }
                DAT_00c4b954 = 0;
                DAT_00c4b950 = 0;
              }
              if (0x7ff < DAT_00c4b950 + iVar10) {
                if ((DAT_00c4b950 != 0) &&
                   (iVar2 = FUN_007ef450(&DAT_00c4d958,DAT_00c4b950,0,1), iVar2 != 0)) {
                  FUN_007ef550(3,&DAT_00c4b958,DAT_00c4b954);
                  FUN_007ef520();
                }
                DAT_00c4b954 = 0;
                DAT_00c4b950 = 0;
              }
              iVar2 = DAT_00c4b950;
              iStack_c = (int)(short)piVar9[0xc];
              puStack_4 = &DAT_00c4b958 + DAT_00c4b954;
              DAT_00c40410 = iVar10 * 3 + -6;
              DAT_00c40414 = iVar10;
              iVar10 = FUN_00821b40();
              if (0 < *(short *)(iVar4 + 0x58)) {
                iStack_c = -0x61 - iVar4;
                pfVar3 = (float *)(&DAT_00c4d974 + iVar2 * 9);
                pbVar5 = (byte *)(iVar4 + 0x61);
                pfVar8 = (float *)(iVar4 + 8);
                do {
                  pfVar3[-1] = (float)(((iVar10 << 8 | (uint)bStack_17) << 8 | (uint)bStack_16) << 8
                                      | (uint)bStack_15);
                  pbVar6 = pbVar5 + 1;
                  *pfVar3 = (float)pbVar5[-7] * _DAT_00858b4c;
                  uStack_8 = (uint)*pbVar5;
                  pfVar3[1] = (float)uStack_8 * _DAT_00858b4c;
                  pfVar3[-7] = pfVar8[-2];
                  pfVar3[-6] = pfVar8[-1];
                  pfVar3[-5] = *pfVar8 + _DAT_00859934;
                  pfVar3 = pfVar3 + 9;
                  pbVar5 = pbVar6;
                  pfVar8 = pfVar8 + 3;
                  piVar9 = piStack_14;
                } while ((int)(pbVar6 + iStack_c) < (int)*(short *)(iVar4 + 0x58));
              }
              iVar10 = 0;
              if (0 < (*(short *)(iVar4 + 0x58) + -2) * 3) {
                puVar7 = puStack_4;
                do {
                  *puVar7 = *(undefined2 *)(((int)&DAT_00c403a8 - (int)puStack_4) + (int)puVar7);
                  iVar10 = iVar10 + 1;
                  puVar7 = puVar7 + 1;
                } while (iVar10 < (*(short *)(iVar4 + 0x58) + -2) * 3);
              }
              FUN_007077a0();
              iVar4 = *(int *)(iVar4 + 0x54);
            } while (iVar4 != 0);
            *(char *)((int)piVar9 + 0x37) = '\x01';
            pcVar11 = pcStack_10;
          }
          piVar9 = piVar9 + 0x10;
          piStack_14 = piVar9;
        } while ((int)piVar9 < 0xc4ac34);
      }
      if ((DAT_00c4b950 != 0) && (iVar4 = FUN_007ef450(&DAT_00c4d958,DAT_00c4b950,0,1), iVar4 != 0))
      {
        FUN_007ef550(3,&DAT_00c4b958,DAT_00c4b954);
        FUN_007ef520();
      }
      DAT_00c4b954 = 0;
      DAT_00c4b950 = 0;
    }
    pcStack_10 = pcVar11 + 0x40;
  } while ((int)pcStack_10 < 0xc4ac66);
  (**(code **)(DAT_00c97b24 + 0x20))(0xc,0);
  (**(code **)(DAT_00c97b24 + 0x20))(8,1);
  return;
}



/* entry 0x0070A960; bounded CFG instructions=160; body bytes=3507 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0070a960(void)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  float fVar5;
  float fVar6;
  char cVar7;
  undefined1 uVar8;
  undefined1 uVar9;
  byte *pbVar10;
  int iVar11;
  float fVar12;
  int iVar13;
  uint uVar14;
  float fVar15;
  uint uVar16;
  int iVar17;
  int *piVar18;
  int *piVar19;
  int iVar20;
  int iVar21;
  float fVar22;
  float10 fVar23;
  float10 fVar24;
  float10 extraout_ST0;
  float10 fVar25;
  float10 fVar26;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float10 extraout_ST0_02;
  float10 extraout_ST1;
  float10 extraout_ST1_00;
  float10 extraout_ST1_01;
  float10 extraout_ST1_02;
  float fStack_ec;
  undefined1 uStack_e5;
  float fStack_e4;
  float fStack_e0;
  float fStack_dc;
  float fStack_d8;
  float fStack_d4;
  int *piStack_d0;
  float fStack_cc;
  int iStack_c8;
  float fStack_c4;
  float fStack_c0;
  undefined4 uStack_bc;
  float fStack_b8;
  undefined4 uStack_b4;
  float fStack_b0;
  float fStack_ac;
  int iStack_a8;
  float fStack_a4;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  float fStack_94;
  float fStack_90;
  float fStack_8c;
  float fStack_88;
  float fStack_84;
  float fStack_80;
  float fStack_7c;
  int iStack_78;
  float fStack_74;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  float fStack_5c;
  float fStack_58;
  float fStack_50;
  float fStack_4c;
  float fStack_44;
  float fStack_40;
  float fStack_38;
  float fStack_2c;
  float fStack_20;
  float fStack_14;
  
  DAT_00c4b954 = 0;
  DAT_00c4b950 = 0;
  (**(code **)(DAT_00c97b24 + 0x20))(8,0);
  (**(code **)(DAT_00c97b24 + 0x20))(6,1);
  (**(code **)(DAT_00c97b24 + 0x20))(0xc,1);
  (**(code **)(DAT_00c97b24 + 0x20))(0xe,0);
  (**(code **)(DAT_00c97b24 + 0x20))(2,3);
  (**(code **)(DAT_00c97b24 + 0x20))(0x14,1);
  (**(code **)(DAT_00c97b24 + 0x20))(0x1e,0);
  (**(code **)(DAT_00c97b24 + 0x20))(9,2);
  uVar14 = (uint)DAT_00c403dc;
  if (uVar14 != 0) {
    pbVar10 = &DAT_00c40462;
    uVar16 = uVar14;
    do {
      *pbVar10 = *pbVar10 & 0xfd;
      pbVar10 = pbVar10 + 0x34;
      uVar16 = uVar16 - 1;
    } while (uVar16 != 0);
  }
  fStack_a4 = 0.0;
  if (uVar14 != 0) {
    iVar21 = 0;
    do {
      fVar22 = fStack_a4;
      piVar1 = (int *)((int)&DAT_00c40454 + iVar21);
      if (((&DAT_00c40462)[iVar21] & 2) == 0) {
        FUN_00707460();
        (**(code **)(DAT_00c97b24 + 0x20))(1,*(undefined4 *)*piVar1);
        piVar18 = piVar1;
        fStack_c4 = fVar22;
        if ((int)fVar22 < (int)(uint)DAT_00c403dc) {
          do {
            piVar19 = piVar18;
            if (((&DAT_00c4045e)[iVar21] == *(char *)((int)piVar18 + 10)) && (*piVar1 == *piVar18))
            {
              fStack_b0 = (float)piVar18[-9];
              fStack_ac = (float)piVar18[-8];
              iStack_a8 = piVar18[-7];
              fStack_e4 = fStack_b0 - (ABS((float)piVar18[-6]) + ABS((float)piVar18[-4]));
              fVar22 = fStack_b0 + ABS((float)piVar18[-6]) + ABS((float)piVar18[-4]);
              fStack_e0 = fStack_ac - (ABS((float)piVar18[-5]) + ABS((float)piVar18[-3]));
              fVar5 = fStack_ac + ABS((float)piVar18[-5]) + ABS((float)piVar18[-3]);
              fVar6 = fStack_e4 * _DAT_00858b38 + _DAT_00858b34;
              piStack_d0 = piVar18;
              FUN_008219f0((double)fVar6);
              iVar11 = FUN_00821b40();
              if (iVar11 < 1) {
                fStack_b8 = 0.0;
              }
              else {
                FUN_008219f0((double)fVar6);
                fStack_b8 = (float)FUN_00821b40();
              }
              fVar6 = fStack_e0 * _DAT_00858b38 + _DAT_00858b34;
              FUN_008219f0((double)fVar6);
              iVar11 = FUN_00821b40();
              if (iVar11 < 1) {
                fStack_d8 = 0.0;
              }
              else {
                FUN_008219f0((double)fVar6);
                fStack_d8 = (float)FUN_00821b40();
              }
              fVar6 = fVar22 * _DAT_00858b38 + _DAT_00858b34;
              FUN_008219f0((double)fVar6);
              iVar11 = FUN_00821b40();
              if (iVar11 < 0x77) {
                FUN_008219f0((double)fVar6);
                fStack_cc = (float)FUN_00821b40();
              }
              else {
                fStack_cc = 1.66755e-43;
              }
              fVar6 = fVar5 * _DAT_00858b38 + _DAT_00858b34;
              FUN_008219f0((double)fVar6);
              iVar11 = FUN_00821b40();
              if (iVar11 < 0x77) {
                FUN_008219f0((double)fVar6);
                fStack_d4 = (float)FUN_00821b40();
              }
              else {
                fStack_d4 = 1.66755e-43;
              }
              if (DAT_00b7cd78 == -1) {
                thunk_FUN_00408258();
                DAT_00b7cd78 = 1;
              }
              else {
                DAT_00b7cd78 = DAT_00b7cd78 + 1;
              }
              fVar6 = fStack_e4;
              fVar15 = fStack_d8;
              if ((int)fStack_d8 <= (int)fStack_d4) {
                do {
                  fStack_d8 = fStack_b8;
                  if ((int)fStack_b8 <= (int)fStack_cc) {
                    fStack_e4 = (float)(((int)fVar15 < 1) - 1 & (uint)fVar15);
                    do {
                      uVar14 = ((int)fStack_d8 < 1) - 1 & (uint)fStack_d8;
                      if (0x76 < (int)uVar14) {
                        uVar14 = 0x77;
                      }
                      fVar12 = fStack_e4;
                      if (0x76 < (int)fStack_e4) {
                        fVar12 = 1.66755e-43;
                      }
                      puVar2 = &DAT_00b7d0b8 + ((int)fVar12 * 0x78 + uVar14) * 2;
                      if (piVar18[1] == 0) {
                        if ((*(byte *)((int)piVar18 + 0xe) & 4) == 0) {
                          FUN_0070a470(puVar2,fVar6,fStack_e0,fVar22,fVar5,&fStack_b0,piVar18[-6],
                                       piVar18[-5],piVar18[-4],piVar18[-3],(short)piVar18[2],
                                       *(undefined1 *)((int)piVar18 + 0xb),(char)piVar18[3],
                                       *(undefined1 *)((int)piVar18 + 0xd),piVar18[-2],piVar18[-1],0
                                       ,&uStack_e5,(&DAT_00c4045e)[iVar21]);
                        }
                        else {
                          FUN_0070a630(puVar2,fVar6,fStack_e0,fVar22,fVar5,&fStack_b0,piVar18[-6],
                                       piVar18[-5],piVar18[-4],piVar18[-3],(short)piVar18[2],
                                       *(undefined1 *)((int)piVar18 + 0xb),(char)piVar18[3],
                                       *(undefined1 *)((int)piVar18 + 0xd));
                        }
                      }
                      else {
                        FUN_0070a7e0(puVar2,fVar6,fStack_e0,fVar22,fVar5,&fStack_b0,piVar18[-6],
                                     piVar18[-5],piVar18[-4],piVar18[-3],(short)piVar18[2],
                                     *(undefined1 *)((int)piVar18 + 0xb),(char)piVar18[3],
                                     *(undefined1 *)((int)piVar18 + 0xd),piVar18[-2],piVar18[-1],0);
                      }
                      fStack_d8 = (float)((int)fStack_d8 + 1);
                    } while ((int)fStack_d8 <= (int)fStack_cc);
                  }
                  fVar15 = (float)((int)fVar15 + 1);
                  piVar19 = piStack_d0;
                } while ((int)fVar15 <= (int)fStack_d4);
              }
              *(byte *)((int)piVar19 + 0xe) = *(byte *)((int)piVar19 + 0xe) | 2;
            }
            fStack_c4 = (float)((int)fStack_c4 + 1);
            piStack_d0 = piVar19 + 0xd;
            piVar18 = piStack_d0;
          } while ((int)fStack_c4 < (int)(uint)DAT_00c403dc);
        }
        if ((DAT_00c4b950 != 0) &&
           (iVar11 = FUN_007ef450(&DAT_00c4d958,DAT_00c4b950,0,1), iVar11 != 0)) {
          FUN_007ef550(3,&DAT_00c4b958);
          FUN_007ef520();
        }
        DAT_00c4b954 = 0;
        DAT_00c4b950 = 0;
      }
      if (((((&DAT_00c40462)[iVar21] & 1) != 0) &&
          (cVar7 = FUN_006e8580(fStack_b0,fStack_ac,iStack_a8,&fStack_c0,&uStack_b4), cVar7 != '\0')
          ) && (fStack_c0 < *(float *)((int)&DAT_00c40438 + iVar21))) {
        piStack_d0 = (int *)(ABS(*(float *)((int)&DAT_00c4043c + iVar21)) +
                            ABS(*(float *)((int)&DAT_00c40444 + iVar21)));
        fStack_c4 = ABS(*(float *)((int)&DAT_00c40440 + iVar21)) +
                    ABS(*(float *)((int)&DAT_00c40448 + iVar21));
        FUN_008219f0((double)((*(float *)((int)&DAT_00c40430 + iVar21) - (float)piStack_d0) *
                             _DAT_00858b8c));
        iVar11 = FUN_00821b40();
        fVar22 = (float)(iVar11 * 2);
        FUN_008219f0((double)((*(float *)((int)&DAT_00c40434 + iVar21) - fStack_c4) * _DAT_00858b8c)
                    );
        iVar11 = FUN_00821b40();
        fStack_b8 = (float)(iVar11 << 1);
        FUN_00823820((double)(((float)piStack_d0 + *(float *)((int)&DAT_00c40430 + iVar21)) *
                             _DAT_00858b8c));
        iVar13 = FUN_00821b40();
        iVar20 = iVar13 * 2;
        iStack_78 = iVar20;
        FUN_00823820((double)((fStack_c4 + *(float *)((int)&DAT_00c40434 + iVar21)) * _DAT_00858b8c)
                    );
        iVar11 = FUN_00821b40();
        piStack_d0 = (int *)(iVar11 << 1);
        fStack_88 = *(float *)((int)&DAT_00c4043c + iVar21) *
                    *(float *)((int)&DAT_00c4043c + iVar21) +
                    *(float *)((int)&DAT_00c40440 + iVar21) *
                    *(float *)((int)&DAT_00c40440 + iVar21);
        fStack_c4 = *(float *)((int)&DAT_00c40444 + iVar21) *
                    *(float *)((int)&DAT_00c40444 + iVar21) +
                    *(float *)((int)&DAT_00c40448 + iVar21) *
                    *(float *)((int)&DAT_00c40448 + iVar21);
        iVar17 = 0;
        iVar11 = 0;
        DAT_00c4b954 = 0;
        DAT_00c4b950 = 0;
        fStack_e0 = fVar22;
        if ((int)fVar22 + iVar13 * -2 == 0 || (int)fVar22 < iVar20) {
          do {
            fStack_ec = fStack_b8;
            if ((int)fStack_b8 <= (int)piStack_d0) {
              fStack_e4 = (float)(int)fStack_e0;
              iVar13 = (int)fStack_e0 + 2;
              fStack_cc = _DAT_00858624 / fStack_c4;
              fStack_d8 = _DAT_00858624 / fStack_88;
              fStack_d4 = (float)iVar13;
              do {
                if (0xfff < iVar17 + 6) {
                  if ((iVar11 != 0) &&
                     (iVar11 = FUN_007ef450(&DAT_00c4d958,iVar11,0,1), iVar11 != 0)) {
                    FUN_007ef550(3,&DAT_00c4b958);
                    FUN_007ef520();
                  }
                  iVar17 = 0;
                  iVar11 = 0;
                  DAT_00c4b954 = 0;
                  DAT_00c4b950 = 0;
                }
                if (0x7ff < iVar11 + 4) {
                  if ((iVar11 != 0) &&
                     (iVar11 = FUN_007ef450(&DAT_00c4d958,iVar11,0,1), iVar11 != 0)) {
                    FUN_007ef550(3,&DAT_00c4b958);
                    FUN_007ef520();
                  }
                  iVar17 = 0;
                  iVar11 = 0;
                  DAT_00c4b954 = 0;
                  DAT_00c4b950 = 0;
                }
                fStack_dc = fStack_c0;
                DAT_00c40410 = 6;
                DAT_00c40414 = 4;
                FUN_006e8550(fStack_e0,fStack_ec,&fStack_dc);
                fVar23 = (float10)*(float *)((int)&DAT_00c40448 + iVar21);
                iStack_c8 = (int)*(short *)((int)&DAT_00c4045c + iVar21);
                fStack_68 = *(float *)((int)&DAT_00c4043c + iVar21);
                fStack_64 = *(float *)((int)&DAT_00c40440 + iVar21);
                fVar22 = (float)(int)fStack_ec;
                fStack_38 = fStack_e4 - *(float *)((int)&DAT_00c40430 + iVar21);
                fVar24 = (float10)(int)fStack_ec - (float10)*(float *)((int)&DAT_00c40434 + iVar21);
                fStack_a0 = fStack_e4 - *(float *)((int)&DAT_00c40430 + iVar21);
                fStack_9c = fVar22 - *(float *)((int)&DAT_00c40434 + iVar21);
                fStack_98 = -*(float *)((int)&DAT_00c40438 + iVar21);
                uVar8 = FUN_00821b40();
                fVar6 = fStack_dc;
                uVar9 = (&DAT_00c40461)[iVar21];
                uVar3 = (&DAT_00c40460)[iVar21];
                uVar4 = (&DAT_00c4045f)[iVar21];
                (&DAT_00c4d974)[iVar11 * 9] =
                     (float)(((extraout_ST0 * (float10)DAT_00858b50 +
                              (float10)fStack_38 * fVar23 + extraout_ST1 * fVar24) *
                              (float10)fStack_cc + (float10)_DAT_00858624) * (float10)_DAT_00858b8c)
                ;
                (&DAT_00c4d970)[iVar11 * 9] = CONCAT31(CONCAT21(CONCAT11(uVar8,uVar4),uVar3),uVar9);
                fVar5 = fStack_98 * DAT_00858b50;
                (&DAT_00c4d958)[iVar11 * 9] = fStack_e4;
                (&DAT_00c4d95c)[iVar11 * 9] = fVar22;
                (&DAT_00c4d978)[iVar11 * 9] =
                     _DAT_00858b8c -
                     (fVar5 + fStack_a0 * fStack_68 + fStack_9c * fStack_64) * fStack_d8 *
                     _DAT_00858b8c;
                fStack_dc = fStack_c0;
                (&DAT_00c4d960)[iVar11 * 9] = fVar6 + _DAT_00859934;
                FUN_006e8550(iVar13,fStack_ec,&fStack_dc,uStack_b4,uStack_bc);
                fVar25 = (float10)*(float *)((int)&DAT_00c40448 + iVar21);
                iStack_c8 = (int)*(short *)((int)&DAT_00c4045c + iVar21);
                fStack_50 = *(float *)((int)&DAT_00c4043c + iVar21);
                fStack_4c = *(float *)((int)&DAT_00c40440 + iVar21);
                fStack_20 = fStack_d4 - *(float *)((int)&DAT_00c40430 + iVar21);
                fVar26 = (float10)(int)fStack_ec - (float10)*(float *)((int)&DAT_00c40434 + iVar21);
                fStack_94 = fStack_d4 - *(float *)((int)&DAT_00c40430 + iVar21);
                fStack_90 = fVar22 - *(float *)((int)&DAT_00c40434 + iVar21);
                fStack_8c = -*(float *)((int)&DAT_00c40438 + iVar21);
                uVar9 = FUN_00821b40();
                fVar5 = fStack_dc;
                fVar24 = (float10)DAT_00858b50;
                fVar23 = (float10)_DAT_00858624;
                (&DAT_00c4d994)[iVar11 * 9] =
                     CONCAT31(CONCAT21(CONCAT11(uVar9,(&DAT_00c4045f)[iVar21]),
                                       (&DAT_00c40460)[iVar21]),(&DAT_00c40461)[iVar21]);
                (&DAT_00c4d998)[iVar11 * 9] =
                     (float)(((extraout_ST0_00 * fVar24 +
                              extraout_ST1_00 * fVar26 + (float10)fStack_20 * fVar25) *
                              (float10)fStack_cc + fVar23) * (float10)_DAT_00858b8c);
                (&DAT_00c4d97c)[iVar11 * 9] = fStack_d4;
                (&DAT_00c4d980)[iVar11 * 9] = fVar22;
                (&DAT_00c4d99c)[iVar11 * 9] =
                     _DAT_00858b8c -
                     (fStack_8c * DAT_00858b50 + fStack_90 * fStack_4c + fStack_94 * fStack_50) *
                     fStack_d8 * _DAT_00858b8c;
                fStack_dc = fStack_c0;
                fStack_ec = (float)((int)fStack_ec + 2);
                (&DAT_00c4d984)[iVar11 * 9] = fVar5 + _DAT_00859934;
                FUN_006e8550(fStack_e0,fStack_ec,&fStack_dc,uStack_b4,uStack_bc);
                fVar24 = (float10)*(float *)((int)&DAT_00c40448 + iVar21);
                iStack_c8 = (int)*(short *)((int)&DAT_00c4045c + iVar21);
                fStack_5c = *(float *)((int)&DAT_00c4043c + iVar21);
                fStack_58 = *(float *)((int)&DAT_00c40440 + iVar21);
                fVar22 = (float)(int)fStack_ec;
                fStack_2c = fStack_e4 - *(float *)((int)&DAT_00c40430 + iVar21);
                fVar25 = (float10)(int)fStack_ec - (float10)*(float *)((int)&DAT_00c40434 + iVar21);
                fStack_84 = fStack_e4 - *(float *)((int)&DAT_00c40430 + iVar21);
                fStack_80 = fVar22 - *(float *)((int)&DAT_00c40434 + iVar21);
                fStack_7c = -*(float *)((int)&DAT_00c40438 + iVar21);
                uVar9 = FUN_00821b40();
                fVar5 = fStack_dc;
                (&DAT_00c4d9b8)[iVar11 * 9] =
                     CONCAT31(CONCAT21(CONCAT11(uVar9,(&DAT_00c4045f)[iVar21]),
                                       (&DAT_00c40460)[iVar21]),(&DAT_00c40461)[iVar21]);
                (&DAT_00c4d9a0)[iVar11 * 9] = fStack_e4;
                fVar23 = (float10)DAT_00858b50;
                (&DAT_00c4d9a4)[iVar11 * 9] = fVar22;
                (&DAT_00c4d9bc)[iVar11 * 9] =
                     (float)(((extraout_ST0_01 * fVar23 +
                              extraout_ST1_01 * fVar25 + (float10)fStack_2c * fVar24) *
                              (float10)fStack_cc + (float10)_DAT_00858624) * (float10)_DAT_00858b8c)
                ;
                (&DAT_00c4d9c0)[iVar11 * 9] =
                     _DAT_00858b8c -
                     (fStack_7c * DAT_00858b50 + fStack_80 * fStack_58 + fStack_84 * fStack_5c) *
                     fStack_d8 * _DAT_00858b8c;
                fStack_dc = fStack_c0;
                (&DAT_00c4d9a8)[iVar11 * 9] = fVar5 + _DAT_00859934;
                FUN_006e8550(iVar13,fStack_ec,&fStack_dc,uStack_b4,uStack_bc);
                fVar23 = (float10)*(float *)((int)&DAT_00c40448 + iVar21);
                iStack_c8 = (int)*(short *)((int)&DAT_00c4045c + iVar21);
                fStack_44 = *(float *)((int)&DAT_00c4043c + iVar21);
                fStack_40 = *(float *)((int)&DAT_00c40440 + iVar21);
                fStack_14 = fStack_d4 - *(float *)((int)&DAT_00c40430 + iVar21);
                fVar24 = (float10)(int)fStack_ec - (float10)*(float *)((int)&DAT_00c40434 + iVar21);
                fStack_74 = fStack_d4 - *(float *)((int)&DAT_00c40430 + iVar21);
                fStack_70 = fVar22 - *(float *)((int)&DAT_00c40434 + iVar21);
                fStack_6c = -*(float *)((int)&DAT_00c40438 + iVar21);
                uVar8 = FUN_00821b40();
                uVar9 = (&DAT_00c40460)[iVar21];
                uVar3 = (&DAT_00c40461)[iVar21];
                (&DAT_00c4b958)[iVar17] = 0;
                (&DAT_00c4b960)[iVar17] = 3;
                uVar4 = (&DAT_00c4045f)[iVar21];
                (&DAT_00c4d9e0)[iVar11 * 9] =
                     (float)(((extraout_ST0_02 * (float10)DAT_00858b50 +
                              extraout_ST1_02 * fVar24 + (float10)fStack_14 * fVar23) *
                              (float10)fStack_cc + (float10)_DAT_00858624) * (float10)_DAT_00858b8c)
                ;
                (&DAT_00c4d9dc)[iVar11 * 9] = CONCAT31(CONCAT21(CONCAT11(uVar8,uVar4),uVar9),uVar3);
                (&DAT_00c4d9c4)[iVar11 * 9] = fStack_d4;
                (&DAT_00c4d9c8)[iVar11 * 9] = fVar22;
                (&DAT_00c4b95a)[iVar17] = 1;
                (&DAT_00c4b95c)[iVar17] = 2;
                (&DAT_00c4b95e)[iVar17] = 1;
                (&DAT_00c4b962)[iVar17] = 2;
                (&DAT_00c4d9e4)[iVar11 * 9] =
                     _DAT_00858b8c -
                     (fStack_6c * DAT_00858b50 + fStack_70 * fStack_40 + fStack_74 * fStack_44) *
                     fStack_d8 * _DAT_00858b8c;
                (&DAT_00c4d9cc)[iVar11 * 9] = fStack_dc + _DAT_00859934;
                FUN_007077a0();
                iVar11 = DAT_00c4b950;
                iVar17 = DAT_00c4b954;
                iVar20 = iStack_78;
              } while ((int)fStack_ec <= (int)piStack_d0);
            }
            fStack_e0 = (float)((int)fStack_e0 + 2);
          } while ((int)fStack_e0 <= iVar20);
          if ((iVar11 != 0) && (iVar11 = FUN_007ef450(&DAT_00c4d958,iVar11,0,1), iVar11 != 0)) {
            FUN_007ef550(3,&DAT_00c4b958);
            FUN_007ef520();
          }
        }
        DAT_00c4b954 = 0;
        DAT_00c4b950 = 0;
      }
      fStack_a4 = (float)((int)fStack_a4 + 1);
      iVar21 = iVar21 + 0x34;
    } while ((int)fStack_a4 < (int)(uint)DAT_00c403dc);
  }
  (**(code **)(DAT_00c97b24 + 0x20))(0xc,0);
  (**(code **)(DAT_00c97b24 + 0x20))(8,1);
  (**(code **)(DAT_00c97b24 + 0x20))(6,1);
  (**(code **)(DAT_00c97b24 + 0x20))(2,1);
  (**(code **)(DAT_00c97b24 + 0x20))(0x14,2);
  DAT_00c403dc = 0;
  return;
}



/* entry 0x0070D000; bounded CFG instructions=160; body bytes=787 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0070d000(float param_1,float param_2,float param_3,float param_4,float param_5,byte param_6
                 ,byte param_7,byte param_8,short param_9,undefined4 param_10,undefined1 param_11,
                 char param_12,char param_13)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  float local_40 [4];
  float local_30 [4];
  float local_20 [8];
  
  local_40[0] = param_1 - param_4;
  local_40[1] = param_1 - param_4;
  local_40[2] = param_1 + param_4;
  local_40[3] = param_1 + param_4;
  local_30[0] = param_2 - param_5;
  local_30[1] = param_2 + param_5;
  local_30[2] = param_2 + param_5;
  local_30[3] = param_2 - param_5;
  if (param_12 == '\0') {
    local_20[0] = 0.0;
    local_20[1] = 0.0;
    local_20[2] = 1.0;
    local_20[3] = 1.0;
  }
  else {
    local_20[0] = 1.0;
    local_20[1] = 1.0;
    local_20[2] = 0.0;
    local_20[3] = 0.0;
  }
  if (param_13 == '\0') {
    local_20[4] = 0.0;
    local_20[5] = 1.0;
    local_20[6] = 1.0;
    local_20[7] = 0.0;
  }
  else {
    local_20[4] = 1.0;
    local_20[5] = 0.0;
    local_20[6] = 0.0;
    local_20[7] = 1.0;
  }
  fVar2 = (float)DAT_00c17044;
  iVar4 = 0;
  fVar3 = (float)DAT_00c17048;
  do {
    if (*(float *)((int)local_40 + iVar4) < DAT_00858b50) {
      fVar1 = *(float *)((int)local_40 + iVar4);
      *(undefined4 *)((int)local_40 + iVar4) = 0;
      *(float *)((int)local_20 + iVar4) = (fVar1 / param_4) * _DAT_00858f40;
    }
    if (fVar2 < *(float *)((int)local_40 + iVar4)) {
      *(float *)((int)local_20 + iVar4) =
           _DAT_00858624 - ((*(float *)((int)local_40 + iVar4) - fVar2) * _DAT_00858b8c) / param_4;
      *(float *)((int)local_40 + iVar4) = fVar2;
    }
    if (*(float *)((int)local_30 + iVar4) < DAT_00858b50) {
      fVar1 = *(float *)((int)local_30 + iVar4);
      *(undefined4 *)((int)local_30 + iVar4) = 0;
      *(float *)((int)local_20 + iVar4 + 0x10) = (fVar1 / param_5) * _DAT_00858f40;
    }
    if (fVar3 < *(float *)((int)local_30 + iVar4)) {
      *(float *)((int)local_20 + iVar4 + 0x10) =
           _DAT_00858624 - ((*(float *)((int)local_30 + iVar4) - fVar3) * _DAT_00858b8c) / param_5;
      *(float *)((int)local_30 + iVar4) = fVar3;
    }
    iVar4 = iVar4 + 4;
  } while (iVar4 < 0x10);
  _DAT_00c4b8e0 = local_40[0];
  _DAT_00c4b934 = local_40[3];
  _DAT_00c4b8fc = local_40[1];
  _DAT_00c4b91c = local_30[2];
  _DAT_00c4b918 = local_40[2];
  _DAT_00c4b8e4 = local_30[0];
  _DAT_00c4b900 = local_30[1];
  _DAT_00c4b938 = local_30[3];
  iVar4 = (int)param_9;
  _DAT_00c4b8e8 =
       ((param_3 - DAT_00c3efa0) *
        (*(float *)(DAT_00c97b24 + 0x1c) - *(float *)(DAT_00c97b24 + 0x18)) * DAT_00c3ef9c) /
       ((DAT_00c3ef9c - DAT_00c3efa0) * param_3) + *(float *)(DAT_00c97b24 + 0x18);
  _DAT_00c4b908 = param_10;
  _DAT_00c4b924 = param_10;
  _DAT_00c4b8ec = param_10;
  _DAT_00c4b940 = param_10;
  _DAT_00c4b8f0 =
       ((uint)CONCAT11(param_11,(char)((uint)param_6 * iVar4 >> 8)) << 8 |
       (int)((uint)param_7 * iVar4) >> 8 & 0xffU) << 8 | (int)((uint)param_8 * iVar4) >> 8 & 0xffU;
  _DAT_00c4b8f4 = local_20[0];
  _DAT_00c4b8f8 = local_20[4];
  _DAT_00c4b910 = local_20[1];
  _DAT_00c4b914 = local_20[5];
  _DAT_00c4b92c = local_20[2];
  _DAT_00c4b930 = local_20[6];
  _DAT_00c4b948 = local_20[3];
  _DAT_00c4b94c = local_20[7];
  _DAT_00c4b904 = _DAT_00c4b8e8;
  _DAT_00c4b90c = _DAT_00c4b8f0;
  _DAT_00c4b920 = _DAT_00c4b8e8;
  _DAT_00c4b928 = _DAT_00c4b8f0;
  _DAT_00c4b93c = _DAT_00c4b8e8;
  _DAT_00c4b944 = _DAT_00c4b8f0;
  FUN_00734e90(5,&DAT_00c4b8e0,4);
  return;
}



/* entry 0x0070D320; bounded CFG instructions=95; body bytes=355 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0070d320(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,float param_7,byte param_8,byte param_9,
                 byte param_10,short param_11,undefined4 param_12,undefined1 param_13)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  if (_DAT_00858f54 <= param_7) {
    uVar3 = (uint)param_10;
    uVar2 = (uint)param_9;
    uVar4 = (uint)param_8;
  }
  else {
    if (param_7 < _DAT_00859918) {
      return;
    }
    iVar1 = FUN_00821b40();
    uVar4 = (int)((uint)param_8 * iVar1) >> 8;
    uVar2 = (int)((uint)param_9 * iVar1) >> 8;
    uVar3 = (int)((uint)param_10 * iVar1) >> 8;
    param_11 = (short)((uint)(param_11 * iVar1) >> 8);
  }
  _DAT_00c4b8e0 = param_1;
  _DAT_00c4b8fc = param_3;
  _DAT_00c4b918 = param_5;
  _DAT_00c4b8e4 = param_2;
  _DAT_00c4b900 = param_4;
  _DAT_00c4b91c = param_6;
  iVar1 = (int)param_11;
  _DAT_00c4b8e8 =
       ((param_7 - DAT_00c3efa0) *
        (*(float *)(DAT_00c97b24 + 0x1c) - *(float *)(DAT_00c97b24 + 0x18)) * DAT_00c3ef9c) /
       ((DAT_00c3ef9c - DAT_00c3efa0) * param_7) + *(float *)(DAT_00c97b24 + 0x18);
  _DAT_00c4b8ec = param_12;
  _DAT_00c4b908 = param_12;
  _DAT_00c4b924 = param_12;
  _DAT_00c4b8f0 =
       ((uint)CONCAT11(param_13,(char)((uVar4 & 0xff) * iVar1 >> 8)) << 8 |
       (int)((uVar2 & 0xff) * iVar1) >> 8 & 0xffU) << 8 | (int)((uVar3 & 0xff) * iVar1) >> 8 & 0xffU
  ;
  _DAT_00c4b904 = _DAT_00c4b8e8;
  _DAT_00c4b90c = _DAT_00c4b8f0;
  _DAT_00c4b920 = _DAT_00c4b8e8;
  _DAT_00c4b928 = _DAT_00c4b8f0;
  FUN_00734e90(3,&DAT_00c4b8e0,3);
  return;
}



/* entry 0x0070D490; bounded CFG instructions=160; body bytes=917 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0070d490(float param_1,float param_2,float param_3,float param_4,float param_5,byte param_6
                 ,byte param_7,byte param_8,short param_9,undefined4 param_10,float param_11,
                 undefined1 param_12)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  float10 fVar13;
  float10 fVar14;
  
  if (_DAT_00858f54 <= param_3) {
    uVar11 = (uint)param_8;
    uVar10 = (uint)param_7;
    uVar12 = (uint)param_6;
  }
  else {
    if (param_3 < _DAT_00859918) {
      return;
    }
    iVar9 = FUN_00821b40();
    uVar12 = (int)((uint)param_6 * iVar9) >> 8;
    uVar10 = (int)((uint)param_7 * iVar9) >> 8;
    uVar11 = (int)((uint)param_8 * iVar9) >> 8;
    param_9 = (short)((uint)(param_9 * iVar9) >> 8);
  }
  fVar13 = (float10)fsin((float10)param_11);
  fVar14 = (float10)fcos((float10)param_11);
  fVar1 = (float)((-fVar14 - fVar13) * (float10)param_4 + (float10)param_1);
  fVar2 = (float)((fVar13 - fVar14) * (float10)param_4 + (float10)param_1);
  fVar3 = (float)((fVar14 + fVar13) * (float10)param_4 + (float10)param_1);
  fVar4 = (float)((float10)param_4 * (fVar14 - fVar13) + (float10)param_1);
  fVar6 = (float)(fVar13 - fVar14) * param_5 + param_2;
  fVar7 = (float)(fVar14 + fVar13) * param_5 + param_2;
  fVar5 = (float)((fVar14 - fVar13) * (float10)param_5 + (float10)param_2);
  param_2 = (float)(-fVar14 - fVar13) * param_5 + param_2;
  if (((((((DAT_00858b50 <= fVar1) || (DAT_00858b50 <= fVar2)) || (DAT_00858b50 <= fVar3)) ||
        (DAT_00858b50 <= fVar4)) &&
       (((DAT_00858b50 <= fVar6 || (DAT_00858b50 <= fVar7)) ||
        ((DAT_00858b50 <= fVar5 || (DAT_00858b50 <= param_2)))))) &&
      (((fVar8 = (float)DAT_00c17044, fVar1 <= fVar8 || (fVar2 <= fVar8)) ||
       ((fVar3 <= fVar8 || (fVar4 <= fVar8)))))) &&
     ((((fVar8 = (float)DAT_00c17048, fVar6 <= fVar8 || (fVar7 <= fVar8)) || (fVar5 <= fVar8)) ||
      (param_2 <= fVar8)))) {
    iVar9 = (int)param_9;
    _DAT_00c4b8e8 =
         ((param_3 - DAT_00c3efa0) *
          (*(float *)(DAT_00c97b24 + 0x1c) - *(float *)(DAT_00c97b24 + 0x18)) * DAT_00c3ef9c) /
         ((DAT_00c3ef9c - DAT_00c3efa0) * param_3) + *(float *)(DAT_00c97b24 + 0x18);
    _DAT_00c4b8ec = param_10;
    _DAT_00c4b908 = param_10;
    _DAT_00c4b924 = param_10;
    _DAT_00c4b940 = param_10;
    _DAT_00c4b8f4 = 0;
    _DAT_00c4b8f8 = 0;
    _DAT_00c4b910 = 0;
    _DAT_00c4b914 = 0x3f800000;
    _DAT_00c4b92c = 0x3f800000;
    _DAT_00c4b930 = 0x3f800000;
    _DAT_00c4b948 = 0x3f800000;
    _DAT_00c4b94c = 0;
    _DAT_00c4b8f0 =
         ((uint)CONCAT11(param_12,(char)((uVar12 & 0xff) * iVar9 >> 8)) << 8 |
         (int)((uVar10 & 0xff) * iVar9) >> 8 & 0xffU) << 8 |
         (int)((uVar11 & 0xff) * iVar9) >> 8 & 0xffU;
    _DAT_00c4b8e0 = fVar1;
    _DAT_00c4b8e4 = fVar6;
    _DAT_00c4b8fc = fVar2;
    _DAT_00c4b900 = fVar7;
    _DAT_00c4b904 = _DAT_00c4b8e8;
    _DAT_00c4b90c = _DAT_00c4b8f0;
    _DAT_00c4b918 = fVar3;
    _DAT_00c4b91c = fVar5;
    _DAT_00c4b920 = _DAT_00c4b8e8;
    _DAT_00c4b928 = _DAT_00c4b8f0;
    _DAT_00c4b934 = fVar4;
    _DAT_00c4b938 = param_2;
    _DAT_00c4b93c = _DAT_00c4b8e8;
    _DAT_00c4b944 = _DAT_00c4b8f0;
    FUN_00734e90(5,&DAT_00c4b8e0,4);
  }
  return;
}



/* entry 0x00719840; bounded CFG instructions=160; body bytes=767 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00719840(void)

{
  char cVar1;
  byte bVar2;
  float fVar3;
  byte bVar4;
  uint uVar5;
  char extraout_DL;
  char cVar6;
  char *pcVar7;
  undefined1 uStack_18;
  undefined1 uStack_17;
  undefined1 uStack_16;
  undefined1 uStack_15;
  float fStack_14;
  undefined4 uStack_10;
  float fStack_c;
  undefined1 uStack_6;
  int iStack_4;
  
  if (DAT_00c716a8 != &DAT_00c716b0) {
    FUN_00727b30();
    (**(code **)(DAT_00c97b24 + 0x20))(0xc,1);
    FUN_00718e50(&DAT_00c716b0);
    uStack_18 = DAT_00c71ab4;
    uStack_15 = DAT_00c71ab7;
    fStack_14 = DAT_00c71aa4;
    fStack_c = DAT_00c71aa8;
    pcVar7 = &DAT_00c716e0;
    uStack_17 = DAT_00c71ab5;
    uStack_16 = DAT_00c71ab6;
    if (&DAT_00c716e0 < DAT_00c716a8) {
      do {
        if (*pcVar7 == '\0') {
          do {
            pcVar7 = pcVar7 + 1;
          } while (((uint)pcVar7 & 3) != 0);
          if (DAT_00c716a8 <= pcVar7) break;
          FUN_00718e50(pcVar7);
          fStack_c = DAT_00c71aa8;
          uStack_6 = DAT_00c71ab6;
          fStack_14 = DAT_00c71aa4;
          uStack_18 = DAT_00c71ab4;
          uStack_17 = DAT_00c71ab5;
          uStack_16 = DAT_00c71ab6;
          uStack_15 = DAT_00c71ab7;
          pcVar7 = pcVar7 + 0x30;
        }
        DAT_00c71a54 = '\0';
        cVar1 = *pcVar7;
        cVar6 = DAT_00c71a54;
        while ((DAT_00c71a54 = cVar6, cVar1 == '~' && (cVar6 == '\0'))) {
          pcVar7 = (char *)FUN_00718f00(pcVar7,&uStack_18,DAT_00c71ac8,0);
          if (DAT_00c71ac8 == '\0') {
            DAT_00c71ab4 = uStack_18;
            DAT_00c71ab5 = uStack_17;
            DAT_00c71ab6 = uStack_16;
            DAT_00c71ab7 = uStack_15;
          }
          cVar1 = *pcVar7;
          cVar6 = DAT_00c71a54;
        }
        bVar4 = *pcVar7 - 0x20;
        uStack_10._1_3_ = (undefined3)((uint)uStack_10 >> 8);
        uStack_10 = CONCAT31(uStack_10._1_3_,bVar4);
        if (DAT_00c71ac9 == '\0') {
          if (bVar4 == 0x91) {
            bVar4 = 0x40;
          }
          else if (0x9b < bVar4) {
            bVar4 = 0;
          }
          uStack_10 = CONCAT31(uStack_10._1_3_,bVar4);
        }
        else {
          bVar4 = FUN_007192c0(uStack_10,DAT_00c71ac9);
          uStack_10 = CONCAT31(uStack_10._1_3_,bVar4);
          cVar6 = extraout_DL;
        }
        if (_DAT_00c71abc != DAT_00858b50) {
          fStack_c = (_DAT_00c71ac0 - fStack_14) * _DAT_00c71abc + _DAT_00c71ac4;
        }
        if ((cVar6 == '\0') || (DAT_00c71ac8 == '\0')) {
          FUN_00718a10(fStack_14,fStack_c,uStack_10);
          cVar6 = DAT_00c71a54;
          bVar4 = (byte)uStack_10;
        }
        if (cVar6 == '\0') {
          uVar5 = (uint)bVar4;
          if (bVar4 == 0x3f) {
            uVar5 = 0;
          }
          if (DAT_00c71aca == '\x01') {
            bVar2 = (&DAT_00c718b0)[uVar5 + DAT_00c71acc * 0xd2];
          }
          else {
            bVar2 = (&DAT_00c71981)[DAT_00c71acc * 0xd2];
          }
          fVar3 = ((float)(int)DAT_00c71ace + (float)bVar2) * _DAT_00c71aac;
        }
        else {
          fVar3 = _DAT_00c71ab0 * _DAT_0085f100 + (float)(int)DAT_00c71ace;
        }
        iStack_4 = (int)DAT_00c71ace;
        fStack_14 = fVar3 + fStack_14;
        if (bVar4 == 0) {
          fStack_14 = _DAT_00c71ab8 + fStack_14;
        }
        if (*pcVar7 == '\0') {
          if (cVar6 != '\0') goto LAB_00719afe;
        }
        else if (cVar6 == '\0') {
          pcVar7 = pcVar7 + 1;
        }
        else {
LAB_00719afe:
          DAT_00c71a54 = '\0';
          FUN_00727b30();
        }
      } while (pcVar7 < DAT_00c716a8);
    }
    FUN_0070cf20();
    FUN_007273d0();
    DAT_00c716a8 = &DAT_00c716b0;
  }
  return;
}



/* entry 0x00720640; bounded CFG instructions=160; body bytes=724 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00720640(void)

{
  float fVar1;
  float fVar2;
  char cVar3;
  float fVar4;
  float fVar5;
  undefined1 uVar6;
  byte bVar7;
  byte bVar8;
  short sVar9;
  float *pfVar10;
  float fVar11;
  int iVar12;
  float *pfVar13;
  short sVar14;
  float *pfVar15;
  undefined2 uStack_1c;
  int iStack_18;
  int *piStack_10;
  
  (**(code **)(DAT_00c97b24 + 0x20))(8,0);
  (**(code **)(DAT_00c97b24 + 0x20))(0xc,1);
  (**(code **)(DAT_00c97b24 + 0x20))(10,5);
  (**(code **)(DAT_00c97b24 + 0x20))(0xb,6);
  (**(code **)(DAT_00c97b24 + 0x20))(0xe,1);
  (**(code **)(DAT_00c97b24 + 0x20))(1,*DAT_00c79a88);
  piStack_10 = &DAT_00c79bf4;
  do {
    cVar3 = *(char *)((int)piStack_10 + 10);
    if ((cVar3 != '\0') && (iVar12 = piStack_10[2], 0 < (short)iVar12)) {
      switch(piStack_10[1]) {
      case 0:
        break;
      case 1:
        break;
      case 2:
        break;
      case 3:
      }
      uVar6 = FUN_00821b40();
      bVar7 = FUN_00821b40();
      uStack_1c = CONCAT11(bVar7,uVar6);
      bVar8 = FUN_00821b40();
      if ((cVar3 == '\x01') || (DAT_00b7cb84 < (uint)piStack_10[-1])) {
        sVar9 = 0xff;
      }
      else {
        sVar9 = (short)(((*piStack_10 - DAT_00b7cb84) * 0xff) / (uint)(*piStack_10 - piStack_10[-1])
                       );
      }
      iVar12 = (int)(short)iVar12;
      iStack_18 = 0;
      if (-1 < iVar12) {
        pfVar13 = (float *)(piStack_10 + -0x51);
        pfVar15 = (float *)(piStack_10 + -0x13);
        pfVar10 = (float *)&DAT_00c4d95c;
        do {
          sVar14 = 0x80;
          if ((pfVar10 == (float *)&DAT_00c4d95c) || ((iStack_18 == iVar12 && (cVar3 == '\x02')))) {
            sVar14 = 0;
          }
          pfVar10[-1] = pfVar15[-0x10] + pfVar13[-2];
          *pfVar10 = *pfVar15 + pfVar13[-1];
          fVar4 = *pfVar13 + _DAT_00858b1c;
          pfVar10[1] = fVar4;
          fVar5 = (float)iStack_18 * _DAT_008729ac;
          pfVar10[7] = fVar5;
          fVar1 = pfVar13[-2];
          fVar2 = pfVar15[-0x10];
          fVar11 = (float)((((int)(short)((uint)((int)sVar14 * (int)sVar9) >> 8) << 8 |
                            uStack_1c & 0xff) << 8 | (uint)bVar7) << 8 | (uint)bVar8);
          pfVar10[5] = fVar11;
          pfVar10[6] = 0.0;
          pfVar10[0xe] = fVar11;
          pfVar10[8] = fVar1 - fVar2;
          fVar1 = pfVar13[-1];
          iStack_18 = iStack_18 + 1;
          fVar2 = *pfVar15;
          pfVar10[0xf] = 1.0;
          pfVar15 = pfVar15 + 1;
          pfVar10[9] = fVar1 - fVar2;
          pfVar13 = pfVar13 + 3;
          pfVar10[10] = fVar4;
          pfVar10[0x10] = fVar5;
          pfVar10 = pfVar10 + 0x12;
        } while (iStack_18 <= iVar12);
      }
      thunk_FUN_00541336();
      iVar12 = FUN_007ef450(&DAT_00c4d958,(short)piStack_10[2] * 2 + 2,0,1);
      if (iVar12 != 0) {
        FUN_007ef550(3,&DAT_00c799c8,(short)piStack_10[2] * 6);
        FUN_007ef520();
      }
    }
    piStack_10 = piStack_10 + 0x56;
  } while ((int)piStack_10 < 0xc7c6f4);
  (**(code **)(DAT_00c97b24 + 0x20))(0xc,0);
  (**(code **)(DAT_00c97b24 + 0x20))(8,1);
  (**(code **)(DAT_00c97b24 + 0x20))(6,1);
  return;
}



/* entry 0x00728640; bounded CFG instructions=160; body bytes=1101 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00728640(float param_1,float param_2,ushort param_3,byte param_4,float param_5,char param_6
                 ,char param_7,char param_8,undefined4 param_9,undefined4 param_10,
                 undefined4 param_11)

{
  float fVar1;
  undefined4 uVar2;
  float fVar3;
  ushort uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 *puVar9;
  float fVar10;
  float fVar11;
  undefined1 auStack_1c [12];
  float fStack_10;
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  (**(code **)(DAT_00c97b24 + 0x20))(1,0);
  (**(code **)(DAT_00c97b24 + 0x20))(7,1);
  if (param_5 < DAT_00858b50) {
    param_5 = 0.0;
  }
  fVar3 = param_1 + (float)param_3;
  fVar10 = param_5 * _DAT_00858c58 * (float)param_3 + param_1;
  fStack_8 = fVar10;
  if (fVar3 <= fVar10) {
    fStack_8 = fVar3;
  }
  fStack_10 = param_1;
  fVar11 = (float)param_4;
  fStack_4 = param_2;
  fVar1 = fVar11 + param_2;
  fStack_c = fVar1;
  thunk_FUN_00409737(&fStack_10,&param_9,fVar10,fVar11);
  fStack_10 = fVar3;
  if (fVar10 < fVar3) {
    fStack_10 = fVar10;
  }
  fStack_4 = param_2;
  uVar2 = CONCAT13(param_10._2_1_,
                   CONCAT12(param_10._1_1_,CONCAT11((undefined1)param_10,param_9._3_1_)));
  uVar8 = uVar2;
  fStack_c = fVar1;
  fStack_8 = fVar3;
  uVar5 = FUN_00821b40(uVar2);
  uVar4 = (ushort)param_9;
  param_9._0_2_ = (ushort)param_9 >> 8;
  param_9._2_1_ = 0;
  param_9._3_1_ = 0;
  uVar6 = FUN_00821b40(uVar5);
  param_9._0_2_ = uVar4 & 0xff;
  param_9._2_1_ = '\0';
  param_9._3_1_ = '\0';
  uVar7 = FUN_00821b40(uVar6);
  uVar8 = FUN_007170c0(uVar7,uVar6,uVar5,uVar8);
  thunk_FUN_00409737(&fStack_10,uVar8);
  if (param_6 != '\0') {
    fStack_8 = fVar3;
    if (fVar10 < fVar3) {
      fStack_8 = fVar10;
    }
    param_9._0_2_ = (ushort)param_6;
    param_9._2_1_ = param_6 >> 7;
    fStack_10 = fStack_8 - (float)CONCAT13(param_9._2_1_,CONCAT12(param_9._2_1_,(ushort)param_9));
    if (fStack_10 <= param_1 - _DAT_00858624) {
      fStack_10 = param_1 - _DAT_00858624;
    }
    fStack_4 = param_2;
    param_9._3_1_ = param_9._2_1_;
    fStack_c = fVar1;
    uVar8 = FUN_007170c0(CONCAT13(param_10._3_1_,
                                  CONCAT12(param_10._2_1_,
                                           CONCAT11(param_10._1_1_,(undefined1)param_10))),
                         CONCAT13((undefined1)param_11,
                                  CONCAT12(param_10._3_1_,CONCAT11(param_10._2_1_,param_10._1_1_))),
                         CONCAT13(param_11._1_1_,
                                  CONCAT12((undefined1)param_11,
                                           CONCAT11(param_10._3_1_,param_10._2_1_))),uVar2);
    thunk_FUN_00409737(&fStack_10,uVar8);
  }
  if (param_8 != '\0') {
    fStack_10 = param_1;
    fStack_c = (float)DAT_00c17048 * _DAT_00859524 + (float)DAT_00c17048 * _DAT_00859524 + param_2;
    fStack_4 = param_2;
    fStack_8 = fVar3;
    uVar8 = FUN_007170c0(0,0,0,uVar2);
    thunk_FUN_00409737(&fStack_10,uVar8);
    fStack_c = fVar1 - ((float)DAT_00c17048 * _DAT_00859524 + (float)DAT_00c17048 * _DAT_00859524);
    fStack_10 = param_1;
    fStack_8 = fVar3;
    fStack_4 = fVar1;
    uVar8 = FUN_007170c0(0,0,0,uVar2);
    thunk_FUN_00409737(&fStack_10,uVar8);
    fStack_8 = (float)DAT_00c17044 * _DAT_00859520 + (float)DAT_00c17044 * _DAT_00859520 + param_1;
    fStack_4 = param_2;
    fStack_10 = param_1;
    fStack_c = fVar1;
    uVar8 = FUN_007170c0(0,0,0,uVar2);
    thunk_FUN_00409737(&fStack_10,uVar8);
    fStack_4 = param_2;
    fStack_8 = fVar3 - ((float)DAT_00c17044 * _DAT_00859520 + (float)DAT_00c17044 * _DAT_00859520);
    fStack_10 = fVar3;
    fStack_c = fVar1;
    uVar8 = FUN_007170c0(0,0,0,uVar2);
    thunk_FUN_00409737(&fStack_10,uVar8);
  }
  if (param_7 != '\0') {
    uVar8 = FUN_00821b40();
    FUN_00821bb5(auStack_1c,&DAT_00872a14,uVar8);
    FUN_00718600(auStack_1c,&fStack_10);
    FUN_007194d0(param_1);
    FUN_007194f0(fVar3);
    puVar9 = (undefined4 *)FUN_007170c0(0,0,0,uVar2);
    FUN_00719430(*puVar9);
    FUN_00719590(0);
    FUN_00719490(1);
    FUN_00719380(fVar11 * _DAT_00858b10,fVar11 * _DAT_00858cec);
    uVar4 = FUN_00821b40();
    if (param_1 + _DAT_00858b40 <= (float)uVar4) {
      FUN_00719610(2);
    }
    else {
      FUN_00719610(1);
      uVar4 = uVar4 + 5;
    }
    FUN_0071a700((float)uVar4,param_2 + _FUN_00858ca0,&fStack_10);
  }
  return;
}



/* entry 0x00728DA0; bounded CFG instructions=160; body bytes=1423 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00728da0(int param_1)

{
  float *pfVar1;
  float *pfVar2;
  int iVar3;
  float fVar4;
  bool bVar5;
  bool bVar6;
  char cVar7;
  float *pfVar8;
  int iVar9;
  uint *puVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  float10 extraout_ST0;
  float10 fVar14;
  float10 fVar15;
  int iStack_d0;
  uint uStack_c4;
  float fStack_c0;
  float fStack_bc;
  float fStack_b8;
  int iStack_b4;
  int local_b0;
  float fStack_ac;
  float fStack_a8;
  float fStack_a4;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  float fStack_94;
  float fStack_90;
  float fStack_8c;
  float fStack_88;
  float fStack_84;
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  float fStack_74;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  float fStack_60;
  float fStack_5c;
  undefined1 auStack_58 [4];
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  float fStack_44;
  float fStack_40;
  float fStack_3c;
  undefined1 auStack_28 [28];
  undefined1 auStack_c [12];
  
  local_b0 = param_1;
  (**(code **)(DAT_00c97b24 + 0x20))(8,0);
  (**(code **)(DAT_00c97b24 + 0x20))(6,1);
  (**(code **)(DAT_00c97b24 + 0x20))(0xc,1);
  (**(code **)(DAT_00c97b24 + 0x20))(10,5);
  (**(code **)(DAT_00c97b24 + 0x20))(0xb,6);
  (**(code **)(DAT_00c97b24 + 0x20))(0xe,1);
  (**(code **)(DAT_00c97b24 + 0x20))(1,0);
  (**(code **)(DAT_00c97b24 + 0x20))(0x1d,5);
  (**(code **)(DAT_00c97b24 + 0x20))(0x1e,0);
  _rand();
  uVar13 = (int)*(short *)(param_1 + 4) & 0x8000001f;
  if ((int)uVar13 < 0) {
    uVar13 = (uVar13 - 1 | 0xffffffe0) + 1;
  }
  uStack_c4 = uVar13 - 1;
  if ((short)uStack_c4 < 0) {
    uStack_c4 = uVar13 + 0x1f;
  }
  bVar6 = false;
  bVar5 = false;
  FUN_00502f20();
  iStack_b4 = 0;
  do {
    if (bVar5) break;
    if ((*(char *)((short)uVar13 + 0x30c + param_1) != '\0') &&
       (*(char *)((short)uStack_c4 + 0x30c + param_1) != '\0')) {
      iVar11 = param_1 + (short)uVar13 * 0xc;
      iVar3 = param_1 + (short)uStack_c4 * 0xc;
      pfVar1 = (float *)(iVar3 + 0xc);
      fStack_88 = *(float *)(iVar3 + 0xc) - *(float *)(iVar11 + 0xc);
      pfVar2 = (float *)(iVar11 + 0xc);
      fStack_84 = *(float *)(iVar3 + 0x10) - *(float *)(iVar11 + 0x10);
      fStack_80 = *(float *)(iVar3 + 0x14) - *(float *)(iVar11 + 0x14);
      param_1 = local_b0;
      fStack_7c = fStack_88;
      fStack_78 = fStack_84;
      fStack_74 = fStack_80;
      if (fStack_80 * fStack_80 + fStack_84 * fStack_84 + fStack_88 * fStack_88 < _DAT_00858fe8) {
        if (!bVar6) {
          fStack_7c = *pfVar1 - *pfVar2;
          fStack_78 = *(float *)(iVar3 + 0x10) - *(float *)(iVar11 + 0x10);
          fStack_74 = *(float *)(iVar3 + 0x14) - *(float *)(iVar11 + 0x14);
          fStack_70 = fStack_7c;
          fStack_6c = fStack_78;
          fStack_68 = fStack_74;
          pfVar8 = (float *)FUN_0059c730(auStack_c,&fStack_7c,&DAT_00b6f9ac);
          fStack_ac = *pfVar8;
          fStack_a8 = pfVar8[1];
          fStack_a4 = pfVar8[2];
          bVar6 = true;
          fVar4 = _DAT_00858c28 /
                  SQRT(fStack_a8 * fStack_a8 + fStack_a4 * fStack_a4 + fStack_ac * fStack_ac);
          fStack_ac = fStack_ac * fVar4;
          fStack_a8 = fStack_a8 * fVar4;
          fStack_a4 = fStack_a4 * fVar4;
          iVar9 = _rand();
          fStack_a0 = (float)iVar9 * _DAT_00858c7c;
          iVar9 = _rand();
          fStack_9c = (float)iVar9 * _DAT_00858c7c;
          iVar9 = _rand();
          fStack_98 = (float)iVar9 * _DAT_00858c7c;
          FUN_0059c910();
          fStack_a0 = fStack_a0 * _DAT_00858c28;
          fStack_9c = fStack_9c * _DAT_00858c28;
          fStack_98 = fStack_98 * _DAT_00858c28;
          iVar9 = _rand();
          fStack_94 = (float)iVar9 * _DAT_00858c7c;
          iVar9 = _rand();
          fStack_90 = (float)iVar9 * _DAT_00858c7c;
          iVar9 = _rand();
          fStack_8c = (float)iVar9 * _DAT_00858c7c;
          FUN_0059c910();
          fStack_94 = fStack_94 * _DAT_00858c28;
          fStack_90 = fStack_90 * _DAT_00858c28;
          fStack_8c = fStack_8c * _DAT_00858c28;
        }
        iVar9 = FUN_00821b40();
        puVar10 = &DAT_00c80568;
        do {
          *puVar10 = iVar9 << 0x18 | 0xc8c8ff;
          puVar10 = puVar10 + 9;
        } while ((int)puVar10 < 0xc80718);
        fVar14 = (float10)fStack_ac * extraout_ST0;
        _DAT_00c80550 = (float)((float10)*pfVar2 - fVar14);
        fVar15 = (float10)fStack_a8 * extraout_ST0;
        _DAT_00c80554 = (float)((float10)*(float *)(iVar11 + 0x10) - fVar15);
        _DAT_00c805c4 = (float)((float10)fStack_a4 * extraout_ST0);
        _DAT_00c80558 = *(float *)(iVar11 + 0x14) - _DAT_00c805c4;
        _DAT_00c80574 = (float)(fVar14 + (float10)*pfVar2);
        _DAT_00c80578 = (float)(fVar15 + (float10)*(float *)(iVar11 + 0x10));
        _DAT_00c8057c = _DAT_00c805c4 + *(float *)(iVar11 + 0x14);
        _DAT_00c80598 = (float)((float10)*pfVar1 - fVar14);
        _DAT_00c8059c = (float)((float10)*(float *)(iVar3 + 0x10) - fVar15);
        _DAT_00c805a0 = *(float *)(iVar3 + 0x14) - _DAT_00c805c4;
        _DAT_00c805bc = (float)(fVar14 + (float10)*pfVar1);
        _DAT_00c805c0 = (float)(fVar15 + (float10)*(float *)(iVar3 + 0x10));
        _DAT_00c805c4 = _DAT_00c805c4 + *(float *)(iVar3 + 0x14);
        fVar14 = (float10)fStack_a0 * extraout_ST0;
        _DAT_00c805e0 = (float)((float10)*pfVar2 - fVar14);
        fVar15 = extraout_ST0 * (float10)fStack_9c;
        _DAT_00c805e4 = (float)((float10)*(float *)(iVar11 + 0x10) - fVar15);
        _DAT_00c80654 = (float)(extraout_ST0 * (float10)fStack_98);
        _DAT_00c805e8 = *(float *)(iVar11 + 0x14) - _DAT_00c80654;
        _DAT_00c80604 = (float)(fVar14 + (float10)*pfVar2);
        _DAT_00c80608 = (float)(fVar15 + (float10)*(float *)(iVar11 + 0x10));
        _DAT_00c8060c = _DAT_00c80654 + *(float *)(iVar11 + 0x14);
        _DAT_00c80628 = (float)((float10)*pfVar1 - fVar14);
        _DAT_00c8062c = (float)((float10)*(float *)(iVar3 + 0x10) - fVar15);
        _DAT_00c80630 = *(float *)(iVar3 + 0x14) - _DAT_00c80654;
        _DAT_00c8064c = (float)(fVar14 + (float10)*pfVar1);
        _DAT_00c80650 = (float)(fVar15 + (float10)*(float *)(iVar3 + 0x10));
        _DAT_00c80654 = _DAT_00c80654 + *(float *)(iVar3 + 0x14);
        fVar14 = (float10)fStack_94 * extraout_ST0;
        _DAT_00c80670 = (float)((float10)*pfVar2 - fVar14);
        fVar15 = extraout_ST0 * (float10)fStack_90;
        _DAT_00c80674 = (float)((float10)*(float *)(iVar11 + 0x10) - fVar15);
        _DAT_00c806e4 = (float)(extraout_ST0 * (float10)fStack_8c);
        _DAT_00c80678 = *(float *)(iVar11 + 0x14) - _DAT_00c806e4;
        _DAT_00c80694 = (float)(fVar14 + (float10)*pfVar2);
        _DAT_00c80698 = (float)(fVar15 + (float10)*(float *)(iVar11 + 0x10));
        _DAT_00c8069c = _DAT_00c806e4 + *(float *)(iVar11 + 0x14);
        _DAT_00c806b8 = (float)((float10)*pfVar1 - fVar14);
        _DAT_00c806bc = (float)((float10)*(float *)(iVar3 + 0x10) - fVar15);
        _DAT_00c806c0 = *(float *)(iVar3 + 0x14) - _DAT_00c806e4;
        _DAT_00c806dc = (float)(fVar14 + (float10)*pfVar1);
        _DAT_00c806e0 = (float)(fVar15 + (float10)*(float *)(iVar3 + 0x10));
        _DAT_00c806e4 = _DAT_00c806e4 + *(float *)(iVar3 + 0x14);
        cVar7 = FUN_0056ba00(pfVar1,pfVar2,&uStack_54,auStack_58,1,1,0,0,0,0,0,0);
        if (cVar7 != '\0') {
          FUN_004ab290(0x3f800000,0x3f800000,0x3f800000,0x3e19999a,0x3f400000,0x3f800000,0x3e4ccccd)
          ;
          fStack_c0 = fStack_44 * _DAT_00858b3c;
          fStack_bc = fStack_40 * _DAT_00858b3c;
          fStack_b8 = fStack_3c * _DAT_00858b3c;
          iVar11 = _rand();
          fStack_c0 = ((float)iVar11 * _DAT_00858c7c * _DAT_00872a64 + _DAT_00858cc4) * fStack_c0;
          iVar11 = _rand();
          fStack_bc = ((float)iVar11 * _DAT_00858c7c * _DAT_00872a64 + _DAT_00858cc4) * fStack_bc;
          iVar11 = _rand();
          iStack_d0 = 0;
          fStack_b8 = ((float)iVar11 * _DAT_00858c7c * _DAT_00872a64 + _DAT_00858cc4) * fStack_b8;
          fStack_64 = fStack_c0 * _DAT_00858cc8;
          fStack_60 = fStack_bc * _DAT_00858cc8;
          fStack_5c = fStack_b8 * _DAT_00858cc8;
          do {
            iVar11 = FUN_00821b40();
            fVar4 = (float)iVar11;
            if (iVar11 < 0) {
              fVar4 = fVar4 + _DAT_00858c54;
            }
            FUN_004aa440(&uStack_54,&fStack_c0,(float)iStack_d0 / fVar4,auStack_28,0xbf800000,
                         0x3f99999a,0x3f19999a,0);
            FUN_004aa440(&uStack_54,&fStack_64,(float)iStack_d0 / fVar4,auStack_28,0xbf800000,
                         0x3f99999a,0x3f19999a,0);
            iStack_d0 = iStack_d0 + 1;
          } while (iStack_d0 < 2);
          FUN_00502f50(uStack_54,uStack_50,uStack_4c,
                       SQRT(fStack_c0 * fStack_c0 + fStack_bc * fStack_bc + fStack_b8 * fStack_b8));
          bVar5 = true;
        }
        iVar11 = FUN_007ef450(&DAT_00c80550,0xc,0,0x10);
        param_1 = local_b0;
        if (iVar11 != 0) {
          FUN_007ef550(3,&DAT_00c80700,0x12);
          FUN_007ef520();
          param_1 = local_b0;
        }
      }
    }
    iStack_b4 = iStack_b4 + 1;
    uVar12 = uStack_c4 - 1;
    if ((short)uVar12 < 0) {
      uVar12 = uStack_c4 + 0x1f;
    }
    uVar13 = uStack_c4;
    uStack_c4 = uVar12;
  } while ((short)iStack_b4 < 0x1f);
  (**(code **)(DAT_00c97b24 + 0x20))(8,1);
  (**(code **)(DAT_00c97b24 + 0x20))(0xc,0);
  (**(code **)(DAT_00c97b24 + 0x20))(0xe,0);
  return;
}



/* entry 0x00732B40; bounded CFG instructions=101; body bytes=307 */

void FUN_00732b40(int *param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  undefined1 uVar3;
  undefined4 uVar4;
  
  if (param_1[6] != 0) {
    iVar1 = (&DAT_00a9b0c8)[*(short *)((int)param_1 + 0x22)];
    if ((*(byte *)(iVar1 + 0x12) & 8) != 0) {
      (**(code **)(DAT_00c97b24 + 0x20))(8,0);
    }
    if ((char)((uint)param_1[7] >> 8) < '\0') {
      (**(code **)(DAT_00c97b24 + 0x20))(0x1e,0);
      uVar4 = FUN_00732500(iVar1,param_1,param_2);
      uVar2 = param_1[7];
      param_1[7] = uVar2 | 0x2000;
      if ((uVar2 & 0x8000000) == 0) {
        (**(code **)(DAT_00c97b24 + 0x20))(0x14,1);
      }
      uVar3 = (**(code **)(*param_1 + 0x4c))();
      if (*(char *)param_1[6] == '\x01') {
        FUN_00732610();
      }
      else {
        FUN_00732680(iVar1,(char *)param_1[6],uVar4);
      }
      (**(code **)(*param_1 + 0x50))(uVar3);
      uVar2 = param_1[7];
      param_1[7] = uVar2 & 0xffffdfff;
      if ((uVar2 & 0x8000000) == 0) {
        (**(code **)(DAT_00c97b24 + 0x20))(0x14,2);
      }
    }
    else {
      if ((DAT_00b72914 == 0) && ((*(byte *)(iVar1 + 0x12) & 8) == 0)) {
        (**(code **)(DAT_00c97b24 + 0x20))(0x1e,100);
      }
      else {
        (**(code **)(DAT_00c97b24 + 0x20))(0x1e,0);
      }
      FUN_00553260(param_1);
    }
    if ((*(byte *)(iVar1 + 0x12) & 8) != 0) {
                    /* WARNING: Could not recover jumptable at 0x00732c6e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(DAT_00c97b24 + 0x20))();
      return;
    }
  }
  return;
}



/* entry 0x00732F30; bounded CFG instructions=160; body bytes=546 */

void FUN_00732f30(void)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  int *local_c;
  
  piVar1 = DAT_00c88234;
  local_c = DAT_00c88234;
  (**(code **)(DAT_00c97b24 + 0x20))(6,1);
  (**(code **)(DAT_00c97b24 + 0x20))(8,1);
  (**(code **)(DAT_00c97b24 + 0x20))(0xe,1);
  (**(code **)(DAT_00c97b24 + 0x20))(10,5);
  (**(code **)(DAT_00c97b24 + 0x20))(0xb,6);
  (**(code **)(DAT_00c97b24 + 0x20))(0x1e,0x14);
  if (piVar1 != (int *)&DAT_00c88224) {
    do {
      piVar1 = (int *)*local_c;
      if ((piVar1 == (int *)0x0) || (piVar1[0x13d] == 0)) {
        local_c = (int *)local_c[1];
      }
      else {
        (**(code **)(*piVar1 + 0x4c))();
        iVar7 = ((piVar1[(char)piVar1[0x1c6] * 7 + 0x168] != 0x2e) - 1 & 0xffffffeb) + 0x18;
        uVar2 = FUN_00734a40(piVar1[6]);
        iVar3 = FUN_007c51a0(uVar2,iVar7);
        iVar4 = FUN_007c5120(uVar2);
        puVar9 = (undefined4 *)(iVar3 * 0x40 + iVar4);
        if (iVar7 == 0) {
          if (piVar1[6] == 0) {
            puVar9 = (undefined4 *)0x0;
          }
          else {
            puVar9 = (undefined4 *)(*(int *)(piVar1[6] + 4) + 0x10);
          }
        }
        iVar3 = *(int *)(piVar1[0x13d] + 4);
        puVar8 = (undefined4 *)(iVar3 + 0x10);
        puVar10 = puVar8;
        for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar10 = *puVar9;
          puVar9 = puVar9 + 1;
          puVar10 = puVar10 + 1;
        }
        if (piVar1[(char)piVar1[0x1c6] * 7 + 0x168] == 0x2e) {
          FUN_007f2450(puVar8,&DAT_008d60b0,1);
          FUN_007f1fd0(puVar8,&DAT_008d2338,0x42b40000,1);
        }
        FUN_005df400(0);
        FUN_007f0910(iVar3);
        FUN_00749b20(piVar1[0x13d]);
        iVar4 = piVar1[(char)piVar1[0x1c6] * 7 + 0x168];
        uVar5 = FUN_005e6580();
        iVar4 = FUN_00743c60(iVar4,uVar5);
        if ((*(uint *)(iVar4 + 0x18) >> 0xb & 1) != 0) {
          iVar4 = FUN_007c51a0(uVar2,0x22);
          iVar7 = FUN_007c5120(uVar2);
          puVar9 = (undefined4 *)(iVar4 * 0x40 + iVar7);
          puVar10 = puVar8;
          for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
            *puVar10 = *puVar9;
            puVar9 = puVar9 + 1;
            puVar10 = puVar10 + 1;
          }
          FUN_007f1fd0(puVar8,&DAT_008d60a4,0x43340000,1);
          FUN_007f2450(puVar8,&DAT_008d6098,1);
          FUN_005df400(1);
          FUN_007f0910(iVar3);
          FUN_00749b20(piVar1[0x13d]);
        }
        FUN_005df4e0();
        local_c = (int *)local_c[1];
      }
    } while (local_c != (int *)&DAT_00c88224);
  }
  return;
}



/* entry 0x00742CF0; bounded CFG instructions=160; body bytes=3887 */

/* WARNING: Removing unreachable block (ram,0x0074399c) */
/* WARNING: Removing unreachable block (ram,0x00742f76) */
/* WARNING: Removing unreachable block (ram,0x00743b98) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00742cf0(void)

{
  float *pfVar1;
  float fVar2;
  undefined4 uVar3;
  float fVar4;
  float fVar5;
  char cVar6;
  float *pfVar7;
  int iVar8;
  undefined4 uVar9;
  undefined4 *puVar10;
  float *pfVar11;
  float *pfVar12;
  undefined *puVar13;
  int iVar14;
  float10 fVar15;
  float10 fVar16;
  float10 fVar17;
  float10 fVar18;
  float10 fVar19;
  float10 fVar20;
  float10 fVar21;
  unkbyte10 Var22;
  float local_58;
  float local_54;
  float fStack_50;
  int *local_4c;
  float fStack_48;
  int local_44;
  float fStack_40;
  float fStack_3c;
  float afStack_38 [4];
  float fStack_28;
  float local_24;
  float local_20;
  float local_1c;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  if (DAT_00b6f065 == '\0') {
    local_44 = 0;
    local_4c = &DAT_00b7cd98;
    pfVar11 = (float *)&DAT_00c8a8a0;
    pfVar12 = (float *)&DAT_00c8a848;
    do {
      if ((pfVar12[-3] != 0.0) && ((uint)pfVar12[-3] < (uint)DAT_00b7cb84)) {
        *(undefined1 *)(pfVar12 + -4) = 0;
        pfVar12[-3] = 0.0;
        *pfVar11 = 0.0;
      }
      if (pfVar12[-3] != -NAN) {
        *pfVar11 = 0.0;
      }
      if (*local_4c == 0) {
        *(undefined1 *)(pfVar12 + -4) = 0;
      }
      if (*(char *)(pfVar12 + -4) != '\0') {
        if (*(char *)(pfVar12 + 6) == '\x01') {
          local_24 = pfVar12[-2];
          local_20 = pfVar12[-1];
          local_1c = *pfVar12;
          cVar6 = FUN_0070ce30(&local_24,afStack_38 + 2,&local_54,&local_58,1,1);
          if (cVar6 != '\0') {
            fVar2 = _DAT_00858ba4 / local_58;
            if (_DAT_00858624 < fVar2) {
              local_54 = local_54 * fVar2;
              local_58 = fVar2 * local_58;
            }
            (**(code **)(DAT_00c97b24 + 0x20))(8,0);
            (**(code **)(DAT_00c97b24 + 0x20))(6,0);
            (**(code **)(DAT_00c97b24 + 0x20))(0xc,1);
            (**(code **)(DAT_00c97b24 + 0x20))(10,5);
            (**(code **)(DAT_00c97b24 + 0x20))(0xb,6);
            (**(code **)(DAT_00c97b24 + 0x20))(1,*DAT_00c8a810);
            afStack_38[0] = 0.95;
            afStack_38[1] = 1.05;
            iVar14 = 0;
            do {
              fVar2 = local_58;
              if (_DAT_00858ba4 < local_58) {
                fVar2 = _DAT_00858ba4;
              }
              fVar4 = local_54;
              if (_DAT_00859ad8 < local_54) {
                fVar4 = _DAT_00859ad8;
              }
              FUN_0070d490(afStack_38[2],afStack_38[3],fStack_28,
                           fVar4 * afStack_38[iVar14] * _DAT_00859bb4,
                           fVar2 * afStack_38[iVar14] * _DAT_00859bb4,0,0,0,0xff,0x3c23d70a,0,0xff);
              iVar14 = iVar14 + 1;
            } while (iVar14 < 2);
            fVar2 = local_58;
            if (_DAT_00858ba4 < local_58) {
              fVar2 = _DAT_00858ba4;
            }
            fVar4 = local_54;
            if (_DAT_00859ad8 < local_54) {
              fVar4 = _DAT_00859ad8;
            }
            FUN_0070d490(afStack_38[2],afStack_38[3],fStack_28,fVar4 * _DAT_00859bb4,
                         fVar2 * _DAT_00859bb4,*(undefined1 *)(pfVar12 + 1),
                         *(undefined1 *)((int)pfVar12 + 5),*(undefined1 *)((int)pfVar12 + 6),0xff,
                         0x3c23d70a,0,*(undefined1 *)((int)pfVar12 + 7));
            (**(code **)(DAT_00c97b24 + 0x20))(1,*DAT_00c8a814);
            fVar15 = (float10)((uint)DAT_00b7cb84 & 0x3ff) * (float10)_DAT_00865034;
            fVar2 = (float)fVar15;
            fVar16 = (float10)pfVar12[4] - (float10)_DAT_00858ba4 * fVar15;
            pfVar12[4] = (float)fVar16;
            if (fVar16 < (float10)DAT_00858b50) {
              pfVar12[4] = 0.0;
            }
            if (pfVar12[4] == DAT_00858b50) {
              pfVar12[5] = 1.0;
            }
            else {
              pfVar12[5] = 0.0;
            }
            fVar16 = (float10)fsin(fVar15);
            _DAT_00c8a89c = (float)(fVar16 * (float10)pfVar12[4]);
            fVar15 = (float10)fcos(fVar15);
            _DAT_00c8a898 = (float)(fVar15 * (float10)pfVar12[4]);
            iVar14 = 0;
            fStack_3c = fVar2;
            do {
              fVar4 = local_58;
              if (_DAT_00858ba4 < local_58) {
                fVar4 = _DAT_00858ba4;
              }
              fVar5 = local_54;
              if (_DAT_00859ad8 < local_54) {
                fVar5 = _DAT_00859ad8;
              }
              FUN_0070d490(afStack_38[2] - _DAT_00c8a89c,afStack_38[3] - _DAT_00c8a898,fStack_28,
                           fVar5 * afStack_38[iVar14] * _DAT_00858c98,
                           fVar4 * afStack_38[iVar14] * _DAT_00858c98,0,0,0,0xff,0x3c23d70a,fVar2,
                           0xff);
              iVar14 = iVar14 + 1;
            } while (iVar14 < 2);
            fVar4 = local_58;
            if (_DAT_00858ba4 < local_58) {
              fVar4 = _DAT_00858ba4;
            }
            fVar5 = local_54;
            if (_DAT_00859ad8 < local_54) {
              fVar5 = _DAT_00859ad8;
            }
            FUN_0070d490(afStack_38[2] - _DAT_00c8a89c,afStack_38[3] - _DAT_00c8a898,fStack_28,
                         fVar5 * _DAT_00858c98,fVar4 * _DAT_00858c98,*(undefined1 *)(pfVar12 + 1),
                         *(undefined1 *)((int)pfVar12 + 5),*(undefined1 *)((int)pfVar12 + 6),
                         *(undefined1 *)((int)pfVar12 + 7),0x3c23d70a,fVar2,0xff);
          }
          (**(code **)(DAT_00c97b24 + 0x20))(8,1);
          (**(code **)(DAT_00c97b24 + 0x20))(6,1);
        }
        else {
          (**(code **)(DAT_00c97b24 + 0x20))(8,0);
          (**(code **)(DAT_00c97b24 + 0x20))(6,0);
          (**(code **)(DAT_00c97b24 + 0x20))(0xc,1);
          (**(code **)(DAT_00c97b24 + 0x20))(1,0);
          pfVar1 = pfVar12 + -2;
          FUN_0070ce30(pfVar1,afStack_38 + 2,&local_54,&local_58,0,0);
          if (((((float)DAT_00c17044 < afStack_38[2]) || (afStack_38[2] < DAT_00858b50)) ||
              ((float)DAT_00c17048 < afStack_38[3])) || (afStack_38[3] < DAT_00858b50)) {
            cVar6 = thunk_FUN_0156cf30();
            if (cVar6 != '\0') {
              iVar14 = *(int *)(*local_4c + 0x14);
              Var22 = fpatan((float10)DAT_00b6f9c0 * ((float10)pfVar12[-1] - (float10)DAT_00b6f9d0)
                             + (float10)DAT_00b6f9c4 * ((float10)*pfVar12 - (float10)DAT_00b6f9d4) +
                               (float10)DAT_00b6f9bc * ((float10)*pfVar1 - (float10)DAT_00b6f9cc),
                             (float10)DAT_00b6f9a0 * ((float10)pfVar12[-1] - (float10)DAT_00b6f9d0)
                             + (float10)DAT_00b6f9a4 * ((float10)*pfVar12 - (float10)DAT_00b6f9d4) +
                               ((float10)*pfVar1 - (float10)DAT_00b6f9cc) * (float10)DAT_00b6f99c);
              fVar15 = (float10)fsin(Var22);
              fVar16 = (float10)fcos(Var22);
              if (iVar14 == 0) {
                pfVar7 = (float *)(*local_4c + 4);
              }
              else {
                pfVar7 = (float *)(iVar14 + 0x30);
              }
              Var22 = fpatan((float10)DAT_00b6f9c0 * ((float10)pfVar12[-1] - (float10)pfVar7[1]) +
                             (float10)DAT_00b6f9c4 * ((float10)*pfVar12 - (float10)pfVar7[2]) +
                             (float10)DAT_00b6f9bc * ((float10)*pfVar1 - (float10)*pfVar7),
                             (float10)DAT_00b6f9a0 * ((float10)pfVar12[-1] - (float10)pfVar7[1]) +
                             (float10)DAT_00b6f9a4 * ((float10)*pfVar12 - (float10)pfVar7[2]) +
                             ((float10)*pfVar1 - (float10)*pfVar7) * (float10)DAT_00b6f99c);
              fVar17 = (float10)fsin(Var22);
              fStack_48 = (float)fVar17;
              fVar17 = (float10)fcos(Var22);
              fStack_50 = (float)fVar17;
              fStack_18 = (float)(((float10)_DAT_00858624 - fVar16) * (float10)DAT_00c17044 *
                                 (float10)_DAT_00858b8c);
              fStack_14 = (_DAT_00858624 - (float)fVar15) * (float)DAT_00c17048 * _DAT_00858b8c;
              fStack_40 = fStack_48 * _DAT_00858b8c + fStack_50;
              fStack_10 = fStack_40 * _DAT_008d6140 + fStack_18;
              fStack_c = (_DAT_008d6140 * fStack_48 + fStack_14) -
                         fStack_50 * _DAT_008d6140 * _DAT_00858b8c;
              fStack_8 = (fStack_50 * _DAT_008d6140 + fStack_18) -
                         _DAT_008d6140 * fStack_48 * _DAT_00858b8c;
              fStack_3c = fStack_50 * _DAT_00858b8c + fStack_48;
              fStack_4 = fStack_3c * _DAT_008d6140 + fStack_14;
              FUN_0070d320(fStack_18,fStack_14,fStack_10,fStack_c,fStack_8,fStack_4,0x40200000,0,0,0
                           ,0xff,0x3f800000,0xff);
              fStack_18 = fStack_50 * _DAT_008d6140 * (float)_DAT_0086eee0 + fStack_18;
              fVar2 = _DAT_008d6140 * fStack_48;
              fStack_14 = _DAT_00858b1c * fVar2 + fStack_14;
              fStack_10 = fStack_40 * _DAT_008d6140 * _DAT_00858c98 + fStack_18;
              fStack_c = (fVar2 - _DAT_00858b8c * fStack_50 * _DAT_008d6140) * _DAT_00858c98 +
                         fStack_14;
              fStack_8 = (fStack_50 * _DAT_008d6140 - fVar2 * _DAT_00858b8c) * _DAT_00858c98 +
                         fStack_18;
              fStack_4 = fStack_3c * _DAT_008d6140 * _DAT_00858c98 + fStack_14;
              FUN_0070d320(fStack_18,fStack_14,fStack_10,fStack_c,fStack_8,fStack_4,0x40200000,
                           *(undefined1 *)(pfVar12 + 1),*(undefined1 *)((int)pfVar12 + 5),
                           *(undefined1 *)((int)pfVar12 + 6),0xff,0x3f800000,0xff);
            }
          }
          else {
            fVar15 = (float10)FUN_00404330(pfVar12[2],0x3f99999a,0x3e99999a);
            fVar15 = (float10)FUN_00420800((float)fVar15);
            pfVar12[2] = (float)fVar15;
            fStack_48 = (float)((float10)_DAT_00858c80 * fVar15);
            fStack_50 = (float)(fVar15 * (float10)_DAT_00858fe8);
            if (fStack_28 < _DAT_00858fa0) {
              fStack_28 = 2.5;
            }
            fVar15 = (float10)FUN_00609cd0();
            if ((float10)DAT_00858b50 < fVar15) {
              fStack_48 = (float)(fVar15 * (float10)_DAT_008d6148);
              fStack_50 = pfVar12[2] * _DAT_00858ba4 + fStack_48;
            }
            (**(code **)(DAT_00c97b24 + 0x20))(10,1);
            (**(code **)(DAT_00c97b24 + 0x20))(0xb,1);
            fStack_40 = 0.0;
            do {
              fVar5 = fStack_40;
              fVar15 = (float10)(int)fStack_40 * (float10)_DAT_00858bb0;
              fVar16 = (float10)_DAT_008595ec * fVar15 + (float10)pfVar12[3];
              fVar17 = (float10)fsin(fVar16);
              fVar16 = (float10)fcos(fVar16);
              fVar18 = (fVar15 + (float10)_DAT_00858b48) * (float10)_DAT_008595ec +
                       (float10)pfVar12[3];
              fVar19 = (float10)fStack_50 + (float10)*pfVar11;
              fVar20 = (float10)fsin(fVar18);
              fVar18 = (float10)fcos(fVar18);
              fVar15 = (fVar15 - (float10)_DAT_00858b48) * (float10)_DAT_008595ec +
                       (float10)pfVar12[3];
              fVar21 = (float10)fsin(fVar15);
              fVar15 = (float10)fcos(fVar15);
              fStack_18 = (float)-(fVar17 * ((float10)fStack_48 + (float10)*pfVar11)) +
                          afStack_38[2];
              fStack_14 = (float)(-(fVar16 * ((float10)fStack_48 + (float10)*pfVar11)) +
                                 (float10)afStack_38[3]);
              fStack_10 = (float)-(fVar20 * fVar19) + afStack_38[2];
              fStack_c = (float)-(fVar18 * fVar19) + afStack_38[3];
              fStack_8 = (float)-(fVar21 * fVar19) + afStack_38[2];
              fStack_4 = (float)-(fVar15 * fVar19) + afStack_38[3];
              FUN_0070d320(fStack_18,fStack_14,fStack_10,fStack_c,fStack_8,fStack_4,fStack_28,0,0,0,
                           0xff,0x3f800000,*(undefined1 *)((int)pfVar12 + 7));
              fVar2 = (fStack_8 + fStack_10 + fStack_18) * _DAT_00859040;
              fVar4 = (fStack_4 + fStack_c + fStack_14) * _DAT_00859040;
              fStack_18 = (fStack_18 - fVar2) * _DAT_00858f34 + fVar2;
              fStack_14 = (fStack_14 - fVar4) * _DAT_00858f34 + fVar4;
              fStack_10 = (fStack_10 - fVar2) * _DAT_00858f34 + fVar2;
              fStack_c = (fStack_c - fVar4) * _DAT_00858f34 + fVar4;
              fStack_8 = (fStack_8 - fVar2) * _DAT_00858f34 + fVar2;
              fStack_4 = (fStack_4 - fVar4) * _DAT_00858f34 + fVar4;
              (**(code **)(DAT_00c97b24 + 0x20))(10,5);
              (**(code **)(DAT_00c97b24 + 0x20))(0xb,6);
              (**(code **)(DAT_00c97b24 + 0x20))(0x14,1);
              FUN_0070d320(fStack_18,fStack_14,fStack_10,fStack_c,fStack_8,fStack_4,fStack_28,
                           *(undefined1 *)(pfVar12 + 1),*(undefined1 *)((int)pfVar12 + 5),
                           *(undefined1 *)((int)pfVar12 + 6),0xff,0x3f800000,
                           *(undefined1 *)((int)pfVar12 + 7));
              fStack_40 = (float)((int)fVar5 + 1);
            } while ((int)fStack_40 < 3);
            fVar2 = pfVar12[-3];
            if ((fVar2 == 0.0) || (fVar2 == -NAN)) {
              pfVar12[3] = pfVar12[3] + _DAT_00858c28;
            }
            else {
              pfVar12[3] = pfVar12[3] + _DAT_00858f34;
              *pfVar11 = *pfVar11 + _FUN_00858ca0;
              pfVar12[2] = pfVar12[2] * _DAT_00858c20;
            }
            if (_DAT_00858cbc < pfVar12[3]) {
              pfVar12[3] = 0.0;
            }
            if (fVar2 == 0.0) {
              if ((&DAT_008d6144)[local_44] == '\0') {
                fVar2 = *pfVar11 - _FUN_00858ca0;
                *pfVar11 = fVar2;
                if (fVar2 < DAT_00858b50) {
                  (&DAT_008d6144)[local_44] = 1;
                }
              }
              else {
                fVar2 = pfVar12[2] + pfVar12[2] + *pfVar11;
                *pfVar11 = fVar2;
                if (pfVar12[2] * _DAT_00858ba4 < fVar2) {
                  (&DAT_008d6144)[local_44] = 0;
                }
              }
            }
          }
          (**(code **)(DAT_00c97b24 + 0x20))(0xc,0);
          (**(code **)(DAT_00c97b24 + 0x20))(8,1);
          (**(code **)(DAT_00c97b24 + 0x20))(6,1);
        }
      }
      local_44 = local_44 + 1;
      local_4c = local_4c + 100;
      pfVar12 = pfVar12 + 0xb;
      pfVar11 = pfVar11 + 1;
    } while ((int)pfVar12 < 0xc8a8a0);
    if ((&DAT_00b6f1a8)[(uint)DAT_00b6f081 * 0x11c] == 0x31) {
      (**(code **)(DAT_00c97b24 + 0x20))(8,0);
      (**(code **)(DAT_00c97b24 + 0x20))(6,0);
      (**(code **)(DAT_00c97b24 + 0x20))(0xc,1);
      (**(code **)(DAT_00c97b24 + 0x20))(10,5);
      (**(code **)(DAT_00c97b24 + 0x20))(0xb,6);
      (**(code **)(DAT_00c97b24 + 0x20))(1,*DAT_00c8a818);
      fStack_3c = (float)((uint)DAT_00b7cb84 & 0x3ff);
      FUN_0070d490((*(float *)(&DAT_00b6f2a4 + (uint)DAT_00b6f081 * 0x238) + _DAT_00858624) *
                   (float)DAT_00c17044 * _DAT_00858b8c,
                   (*(float *)(&DAT_00b6f2a8 + (uint)DAT_00b6f081 * 0x238) + _DAT_00858624) *
                   (float)DAT_00c17048 * _DAT_00858b8c,0x42c80000,0x41200000,0x41200000,0xff,0x80,0,
                   0x80,0x3c23d70a,(float)(int)fStack_3c * _DAT_00865034,0xff);
      iVar14 = DAT_00b7cf28;
      if ((*(int *)(DAT_00b7cd98 + 0x58c) != 0) &&
         (*(int *)(*(int *)(DAT_00b7cd98 + 0x58c) + 0x460) != DAT_00b7cd98)) {
        iVar14 = DAT_00b7cd98;
      }
      iVar8 = 0;
      if (iVar14 != 0) {
        uVar3 = *(undefined4 *)(*(char *)(iVar14 + 0x718) * 0x1c + 0x5a0 + iVar14);
        uVar9 = FUN_005e6580();
        iVar8 = FUN_00743c60(uVar3,uVar9);
        if (*(int *)(iVar14 + 0x14) == 0) {
          puVar10 = (undefined4 *)(iVar14 + 4);
        }
        else {
          puVar10 = (undefined4 *)(*(int *)(iVar14 + 0x14) + 0x30);
        }
        iVar8 = FUN_0073e240(*(undefined4 *)(&DAT_00b6f2a4 + (uint)DAT_00b6f081 * 0x238),
                             *(undefined4 *)(&DAT_00b6f2a8 + (uint)DAT_00b6f081 * 0x238),
                             *(float *)(iVar8 + 8) + *(float *)(iVar8 + 8),*puVar10,puVar10[1],
                             puVar10[2],0,0);
      }
      if (iVar8 != DAT_00c8a894) {
        DAT_00c8a890 = DAT_00b7cb84;
        DAT_00c8a894 = iVar8;
      }
      if (iVar8 != 0) {
        if (*(int *)(iVar8 + 0x14) == 0) {
          iVar8 = iVar8 + 4;
        }
        else {
          iVar8 = *(int *)(iVar8 + 0x14) + 0x30;
        }
        cVar6 = FUN_0070ce30(iVar8,afStack_38 + 2,&local_54,&local_58,1,1);
        if (cVar6 != '\0') {
          fVar2 = _DAT_00858ba4 / local_58;
          if (_DAT_00858624 < fVar2) {
            local_54 = local_54 * fVar2;
            local_58 = fVar2 * local_58;
          }
          iVar14 = (int)DAT_00b7cb84 - (int)DAT_00c8a890;
          fVar2 = _DAT_00858b3c - (float)iVar14 * _DAT_00863a44;
          if (fVar2 < _DAT_00858624) {
            fVar2 = _DAT_00858624;
          }
          iVar14 = ((int)(iVar14 + (iVar14 >> 0x1f & 3U)) >> 2) + 0x46;
          if (0xff < iVar14) {
            iVar14 = 0xff;
          }
          fStack_3c = (float)((uint)DAT_00b7cb84 & 0x3ff);
          FUN_0070d490(afStack_38[2],afStack_38[3],fStack_28,fVar2 * local_54,local_58 * fVar2,
                       iVar14,0,0,iVar14,0x3c23d70a,(float)(int)fStack_3c * _DAT_00865034,0xff);
        }
      }
      (**(code **)(DAT_00c97b24 + 0x20))(8,1);
      (**(code **)(DAT_00c97b24 + 0x20))(6,1);
    }
    iVar14 = 0;
    puVar13 = &DAT_00b7cef0;
    do {
      FUN_0056ef90(iVar14);
      puVar13 = puVar13 + 400;
      iVar14 = iVar14 + 1;
    } while ((int)puVar13 < 0xb7d210);
  }
  return;
}



/* entry 0x0074CA90; bounded CFG instructions=160; body bytes=543 */

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



/* entry 0x0074CCC0; bounded CFG instructions=51; body bytes=165 */

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



/* entry 0x0074D190; bounded CFG instructions=160; body bytes=1332 */

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



/* entry 0x0074DD30; bounded CFG instructions=160; body bytes=724 */

/* WARNING: Type propagation algorithm not settling */

int * FUN_0074dd30(undefined4 param_1)

{
  short sVar1;
  int iVar2;
  int *piVar3;
  uint local_2c;
  int local_28 [3];
  int local_1c [4];
  int iStack_c;
  int iStack_8;
  int iStack_4;
  
  iVar2 = FUN_007ed2d0(param_1,1,local_28,&local_2c);
  if (iVar2 == 0) {
    return (int *)0x0;
  }
  if ((local_2c < 0x34000) || (0x36003 < local_2c)) {
LAB_0074df9b:
    local_28[1] = 2;
    local_28[2] = FUN_008088d0(0x80000004);
    FUN_00808820(local_28 + 1);
    return (int *)0x0;
  }
  piVar3 = local_1c;
  for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar3 = 0;
    piVar3 = piVar3 + 1;
  }
  iVar2 = FUN_007ec9d0(param_1,local_1c,local_28[0]);
  if (iVar2 != local_28[0]) {
    return (int *)0x0;
  }
  piVar3 = (int *)(**(code **)(DAT_00c97b24 + 0x144))
                            (*(undefined4 *)(DAT_00c92514 + DAT_00c97b24),0x30007);
  if (piVar3 == (int *)0x0) {
    return (int *)0x0;
  }
  *(undefined2 *)(piVar3 + 6) = 1;
  piVar3[1] = -1;
  *piVar3 = 0;
  piVar3[2] = 0;
  piVar3[3] = DAT_008d62bc;
  piVar3[4] = DAT_008d62c0;
  piVar3[5] = DAT_008d62c4;
  FUN_008086e0(&DAT_008d62a4,piVar3);
  piVar3[1] = local_1c[1];
  piVar3[3] = iStack_c;
  piVar3[4] = iStack_8;
  piVar3[5] = iStack_4;
  *piVar3 = 0;
  if (local_1c[3] != 0) {
    iVar2 = FUN_007ed2d0(param_1,6,0,&local_2c);
    if (iVar2 == 0) {
      sVar1 = (short)piVar3[6];
      if (sVar1 == 1) {
        FUN_00808740(&DAT_008d62a4,piVar3);
        if (*piVar3 != 0) {
          FUN_007f3820(*piVar3);
        }
        *piVar3 = 0;
        (**(code **)(DAT_00c97b24 + 0x148))(*(undefined4 *)(DAT_00c92514 + DAT_00c97b24),piVar3);
        return (int *)0x0;
      }
      goto LAB_0074dfce;
    }
    if ((local_2c < 0x34000) || (0x36003 < local_2c)) {
      if ((short)piVar3[6] == 1) {
        FUN_00808740(&DAT_008d62a4,piVar3);
        if (*piVar3 != 0) {
          FUN_007f3820(*piVar3);
        }
        *piVar3 = 0;
        (**(code **)(DAT_00c97b24 + 0x148))(*(undefined4 *)(DAT_00c92514 + DAT_00c97b24),piVar3);
      }
      else {
        *(short *)(piVar3 + 6) = (short)piVar3[6] + -1;
      }
      goto LAB_0074df9b;
    }
    iVar2 = FUN_008046e0(param_1);
    *piVar3 = iVar2;
  }
  DAT_00c92510 = 0;
  DAT_00c924e8 = 0;
  iVar2 = FUN_00808980(&DAT_008d62a4,param_1,piVar3);
  if (iVar2 != 0) {
    if (DAT_00c92510 != 0) {
      FUN_00808ab0(&DAT_008d62a4,DAT_00c92510,piVar3,DAT_00c924e8);
    }
    return piVar3;
  }
  sVar1 = (short)piVar3[6];
  if (sVar1 == 1) {
    FUN_00808740(&DAT_008d62a4,piVar3);
    if (*piVar3 != 0) {
      FUN_007f3820(*piVar3);
    }
    *piVar3 = 0;
    (**(code **)(DAT_00c97b24 + 0x148))(*(undefined4 *)(DAT_00c92514 + DAT_00c97b24),piVar3);
    return (int *)0x0;
  }
LAB_0074dfce:
  *(short *)(piVar3 + 6) = sVar1 + -1;
  return (int *)0x0;
}



/* entry 0x0074F760; bounded CFG instructions=160; body bytes=923 */

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



/* entry 0x00754E20; bounded CFG instructions=160; body bytes=973 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00754e20(void)

{
  ushort uVar1;
  float fVar2;
  float fVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  ushort *puVar12;
  int iVar13;
  int iVar14;
  float *pfVar15;
  undefined4 *puVar16;
  int *piVar17;
  int iVar18;
  float *pfVar19;
  float10 fVar20;
  int unaff_retaddr;
  int in_stack_00000014;
  ushort *puVar21;
  undefined4 *puStack_50;
  int iStack_48;
  int iStack_44;
  float *pfStack_40;
  undefined1 auStack_30 [4];
  float fStack_2c;
  int local_28;
  float fStack_24;
  float fStack_20;
  float fStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  float fStack_c;
  int iStack_8;
  int iStack_4;
  
  local_28 = *(int *)(in_stack_00000014 + 0x3c);
  uVar7 = local_28 * 3;
  puVar4 = (undefined4 *)(**(code **)(DAT_00c97b24 + 0x134))(local_28 * 0xc,0x1050d);
  puVar16 = puVar4;
  for (uVar7 = uVar7 & 0x3fffffff; uVar7 != 0; uVar7 = uVar7 - 1) {
    *puVar16 = 0;
    puVar16 = puVar16 + 1;
  }
  for (iVar8 = 0; iVar8 != 0; iVar8 = iVar8 + -1) {
    *(undefined1 *)puVar16 = 0;
    puVar16 = (undefined4 *)((int)puVar16 + 1);
  }
  (**(code **)(**(int **)(in_stack_00000014 + 8) + 0x2c))
            (*(int **)(in_stack_00000014 + 8),0,*(int *)(in_stack_00000014 + 0x38) * 2,auStack_30,0)
  ;
  iStack_48 = *(int *)(in_stack_00000014 + 4);
  piVar17 = (int *)(in_stack_00000014 + 0x40);
  do {
    iVar8 = iStack_44 + piVar17[7] * 2;
    iVar9 = *piVar17;
    if (*(int *)(in_stack_00000014 + 0xc) == 5) {
      iVar9 = iVar9 + -2;
    }
    uVar7 = 0;
    if (0 < iVar9) {
      puVar21 = (ushort *)(iVar8 + 4);
      puVar12 = (ushort *)(iVar8 + 2);
      do {
        if (*(int *)(unaff_retaddr + 0xc) == 4) {
          iVar10 = piVar17[1];
          iVar5 = (uint)*(ushort *)(iVar8 + uVar7 * 2) + iVar10;
          iVar14 = (uint)*puVar21 + iVar10;
          iVar10 = (uint)*puVar12 + iVar10;
          uVar7 = uVar7 + 3;
          puVar12 = puVar12 + 3;
          puVar21 = puVar21 + 3;
LAB_00754f90:
          iVar18 = iVar10 * 0xc;
          iVar11 = iVar5 * 0xc;
          fStack_2c = *(float *)(iVar18 + iStack_8) - *(float *)(iVar11 + iStack_8);
          iVar13 = iVar14 * 0xc;
          fStack_24 = *(float *)(iStack_4 + 4 + iVar10 * 8) - *(float *)(iStack_4 + 4 + iVar5 * 8);
          pfStack_40 = (float *)(iStack_4 + 4 + iVar5 * 8);
          fStack_20 = *(float *)(iStack_8 + iVar13) - *(float *)(iVar11 + iStack_8);
          fStack_18 = *(float *)(iStack_4 + 4 + iVar14 * 8) - *pfStack_40;
          fVar2 = fStack_18 * (*(float *)(iStack_4 + iVar10 * 8) - *(float *)(iStack_4 + iVar5 * 8))
                  - (*(float *)(iStack_4 + iVar14 * 8) - *(float *)(iStack_4 + iVar5 * 8)) *
                    fStack_24;
          if (_DAT_00874f44 < ABS(fVar2)) {
            fVar3 = (_DAT_00858624 / fVar2) * (fStack_20 * fStack_24 - fStack_18 * fStack_2c);
            puStack_50[iVar5 * 3] = (float)puStack_50[iVar5 * 3] - fVar3;
            puStack_50[iVar10 * 3] = (float)puStack_50[iVar10 * 3] - fVar3;
            puStack_50[iVar14 * 3] = (float)puStack_50[iVar14 * 3] - fVar3;
          }
          if (_DAT_00874f44 < ABS(fVar2)) {
            fVar3 = (_DAT_00858624 / fVar2) *
                    ((*(float *)(iStack_8 + 4 + iVar13) - *(float *)(iVar11 + 4 + iStack_8)) *
                     fStack_24 -
                    fStack_18 *
                    (*(float *)(iVar18 + 4 + iStack_8) - *(float *)(iVar11 + 4 + iStack_8)));
            puStack_50[iVar5 * 3 + 1] = (float)puStack_50[iVar5 * 3 + 1] - fVar3;
            puStack_50[iVar10 * 3 + 1] = (float)puStack_50[iVar10 * 3 + 1] - fVar3;
            puStack_50[iVar14 * 3 + 1] = (float)puStack_50[iVar14 * 3 + 1] - fVar3;
          }
          puVar4 = puStack_50;
          if (_DAT_00874f44 < ABS(fVar2)) {
            fVar2 = (_DAT_00858624 / fVar2) *
                    ((*(float *)(iStack_8 + 8 + iVar13) - *(float *)(iVar11 + 8 + iStack_8)) *
                     fStack_24 -
                    fStack_18 *
                    (*(float *)(iVar18 + 8 + iStack_8) - *(float *)(iVar11 + 8 + iStack_8)));
            puStack_50[iVar5 * 3 + 2] = (float)puStack_50[iVar5 * 3 + 2] - fVar2;
            puStack_50[iVar10 * 3 + 2] = (float)puStack_50[iVar10 * 3 + 2] - fVar2;
            puStack_50[iVar14 * 3 + 2] = (float)puStack_50[iVar14 * 3 + 2] - fVar2;
          }
        }
        else {
          if ((uVar7 & 1) == 0) {
            iVar5 = (uint)*(ushort *)(iVar8 + uVar7 * 2) + piVar17[1];
            iVar10 = (uint)*puVar12 + piVar17[1];
            uVar1 = *puVar21;
          }
          else {
            iVar10 = (uint)*puVar12 + piVar17[1];
            iVar5 = (uint)*puVar21 + piVar17[1];
            uVar1 = *(ushort *)(iVar8 + uVar7 * 2);
          }
          puVar12 = puVar12 + 1;
          iVar14 = (uint)uVar1 + piVar17[1];
          uVar7 = uVar7 + 1;
          puVar21 = puVar21 + 1;
          if (((iVar5 != iVar10) && (iVar5 != iVar14)) && (iVar10 != iVar14)) goto LAB_00754f90;
        }
        in_stack_00000014 = unaff_retaddr;
      } while ((int)uVar7 < iVar9);
    }
    piVar17 = piVar17 + 9;
    iStack_48 = iStack_48 + -1;
    if (iStack_48 == 0) {
      (**(code **)(**(int **)(in_stack_00000014 + 8) + 0x30))(*(int **)(in_stack_00000014 + 8));
      if (0 < (int)pfStack_40) {
        pfVar15 = (float *)(puVar4 + 2);
        pfVar19 = pfStack_40;
        do {
          fStack_c = *pfVar15 * *pfVar15 + pfVar15[-2] * pfVar15[-2] + pfVar15[-1] * pfVar15[-1];
          fVar20 = (float10)FUN_007edb90(fStack_c);
          pfVar19 = (float *)((int)pfVar19 + -1);
          pfVar15[-2] = (float)(fVar20 * (float10)pfVar15[-2]);
          pfVar15[-1] = (float)((float10)pfVar15[-1] * fVar20);
          *pfVar15 = (float)((float10)*pfVar15 * fVar20);
          pfVar15 = pfVar15 + 3;
        } while (pfVar19 != (float *)0x0);
      }
      uVar6 = FUN_00752ad0(uStack_14,uStack_10,puVar4,pfStack_40,unaff_retaddr);
      (**(code **)(DAT_00c97b24 + 0x138))(puVar4);
      return uVar6;
    }
  } while( true );
}



/* entry 0x007591D0; bounded CFG instructions=160; body bytes=1134 */

undefined4 * FUN_007591d0(int *param_1,undefined4 *param_2,uint param_3)

{
  undefined2 uVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  uint *puVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  uint uVar9;
  int *piVar10;
  ushort uVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  uint uVar15;
  int iVar16;
  uint *puVar17;
  undefined4 *puVar18;
  int *piVar19;
  undefined4 *puVar20;
  undefined4 *puVar21;
  uint uStack_18;
  int *piStack_14;
  
  iVar14 = (int)param_1;
  uVar11 = 0;
  piVar3 = (int *)(**(code **)(DAT_00c97b24 + 0x134))(*(int *)((int)param_1 + 4) << 2,0x10502);
  puVar4 = (undefined4 *)0x0;
  if (piVar3 != (int *)0x0) {
    if (*(int *)(iVar14 + 4) != 0) {
      iVar12 = 0;
      do {
        iVar16 = *(int *)(iVar14 + 8) + iVar12;
        iVar12 = iVar12 + 0x14;
        piVar3[(int)puVar4] = iVar16;
        puVar4 = (undefined4 *)((int)puVar4 + 1);
      } while (puVar4 < *(undefined4 **)(iVar14 + 4));
    }
    FUN_008247e0(piVar3,*(undefined4 *)(iVar14 + 4),4,&LAB_00759640);
    uVar9 = *(uint *)(iVar14 + 4);
    iVar12 = 1;
    if (1 < uVar9) {
      iVar16 = *(int *)(*piVar3 + 8);
      uVar13 = 1;
      if (1 < uVar9) {
        do {
          if (*(int *)(piVar3[uVar13] + 8) != iVar16) {
            iVar12 = iVar12 + 1;
            iVar16 = *(int *)(piVar3[uVar13] + 8);
          }
          uVar13 = uVar13 + 1;
        } while (uVar13 < uVar9);
      }
    }
    iVar16 = (**(code **)(DAT_00c97b24 + 0x134))(iVar12 * 4,&DAT_01010502);
    puVar5 = (undefined4 *)(**(code **)(DAT_00c97b24 + 0x134))(iVar12 * 0xc,0x10502);
    puVar17 = puVar5 + 1;
    puVar5[2] = *(undefined4 *)(*piVar3 + 8);
    *puVar5 = 0;
    *puVar17 = 0;
    iVar12 = 1;
    if ((1 < *(uint *)(iVar14 + 4)) &&
       (uStack_18 = 0, puVar6 = puVar17, piVar19 = piVar3, *(uint *)(iVar14 + 4) != 1)) {
      do {
        uVar9 = *(uint *)(piVar19[1] + 8);
        if (*(uint *)(*piVar19 + 8) != uVar9) {
          puVar6[4] = uVar9;
          puVar6[2] = 0;
          puVar6[3] = uStack_18 + 1;
          iVar12 = iVar12 + 1;
          *puVar6 = (uStack_18 - *puVar6) + 1;
          puVar6 = puVar6 + 3;
        }
        uStack_18 = uStack_18 + 1;
        piVar19 = piVar19 + 1;
      } while (uStack_18 < *(int *)(iVar14 + 4) - 1U);
    }
    puVar5[iVar12 * 3 + -2] = *(int *)(iVar14 + 4) - puVar5[iVar12 * 3 + -2];
    uVar7 = FUN_00801980(0x10,*(uint *)(iVar14 + 4) / 10 + 5,4,0x10502);
    *(undefined4 *)(DAT_00c9b8c0 + 4 + DAT_00c97b24) = uVar7;
    param_1 = (int *)0x0;
    piStack_14 = piVar3;
    for (; iVar12 != 0; iVar12 = iVar12 + -1) {
      puVar8 = (undefined4 *)(**(code **)(DAT_00c97b24 + 0x134))(*puVar17 * 0x14,0x10502);
      uVar9 = 0;
      puVar4 = puVar8;
      if (*puVar17 != 0) {
        do {
          puVar18 = (undefined4 *)*piStack_14;
          puVar20 = puVar4;
          for (iVar14 = 5; iVar14 != 0; iVar14 = iVar14 + -1) {
            *puVar20 = *puVar18;
            puVar18 = puVar18 + 1;
            puVar20 = puVar20 + 1;
          }
          piStack_14 = piStack_14 + 1;
          uVar9 = uVar9 + 1;
          puVar4 = puVar4 + 5;
        } while (uVar9 < *puVar17);
      }
      FUN_00759790(puVar8,*puVar17,&param_1,param_2);
      FUN_0075a660(&param_1,param_3);
      piVar19 = param_1;
      if (param_1 != (int *)0x0) {
        do {
          piVar10 = (int *)(**(code **)(DAT_00c97b24 + 0x134))(piVar19[1] * 2 + 0xc,0x10502);
          piVar10[2] = puVar17[1];
          iVar14 = piVar19[1];
          piVar10[1] = iVar14;
          *piVar10 = (int)(piVar10 + 3);
          uVar9 = 0;
          if (iVar14 != 0) {
            do {
              *(undefined2 *)(*piVar10 + uVar9 * 2) = *(undefined2 *)(*piVar19 + uVar9 * 2);
              uVar9 = uVar9 + 1;
            } while (uVar9 < (uint)piVar10[1]);
          }
          uVar9 = (uint)uVar11;
          uVar11 = uVar11 + 1;
          *(int **)(iVar16 + uVar9 * 4) = piVar10;
          piVar19 = (int *)piVar19[3];
          piVar10 = param_1;
        } while (piVar19 != (int *)0x0);
        while (param_1 = piVar10, piVar10 != (int *)0x0) {
          param_1 = (int *)piVar10[3];
          (**(code **)(DAT_00c97b24 + 0x138))(*piVar10);
          *piVar10 = 0;
          (**(code **)(DAT_00c97b24 + 0x148))
                    (*(undefined4 *)(DAT_00c9b8c0 + 4 + DAT_00c97b24),piVar10);
          piVar10 = param_1;
        }
      }
      (**(code **)(DAT_00c97b24 + 0x138))(puVar8);
      puVar17 = puVar17 + 3;
    }
    FUN_00801b80(*(undefined4 *)(DAT_00c9b8c0 + 4 + DAT_00c97b24));
    uVar9 = 0;
    iVar12 = 0;
    uVar13 = (uint)uVar11;
    *(undefined4 *)(DAT_00c9b8c0 + 4 + DAT_00c97b24) = 0;
    iVar14 = 0x10;
    if (uVar13 != 0) {
      do {
        iVar2 = *(int *)(*(int *)(iVar16 + uVar9 * 4) + 4);
        iVar12 = iVar12 + iVar2;
        uVar9 = uVar9 + 1;
        iVar14 = iVar14 + 0xc + iVar2 * 2;
      } while (uVar9 < uVar13);
    }
    param_3 = uVar13;
    puVar4 = (undefined4 *)FUN_00758920(iVar14);
    *puVar4 = 1;
    *(ushort *)(puVar4 + 1) = uVar11;
    uVar9 = 0;
    uVar1 = *(undefined2 *)(DAT_00c9b8c0 + DAT_00c97b24);
    puVar4[3] = 0;
    *(undefined2 *)((int)puVar4 + 6) = uVar1;
    puVar4[2] = iVar12;
    *(short *)(DAT_00c9b8c0 + DAT_00c97b24) = *(short *)(DAT_00c9b8c0 + DAT_00c97b24) + 1;
    puVar8 = puVar4 + 4 + uVar13 * 3;
    puVar18 = puVar4 + 4;
    if (uVar13 != 0) {
      do {
        *puVar18 = puVar8;
        puVar18[1] = *(undefined4 *)(*(int *)(iVar16 + uVar9 * 4) + 4);
        puVar18[2] = *(undefined4 *)(*(int *)(iVar16 + uVar9 * 4) + 8);
        puVar20 = *(undefined4 **)(iVar16 + uVar9 * 4);
        uVar13 = puVar20[1];
        puVar20 = (undefined4 *)*puVar20;
        puVar21 = puVar8;
        for (uVar15 = (uVar13 & 0x7fffffff) >> 1; uVar15 != 0; uVar15 = uVar15 - 1) {
          *puVar21 = *puVar20;
          puVar20 = puVar20 + 1;
          puVar21 = puVar21 + 1;
        }
        for (uVar13 = uVar13 * 2 & 3; uVar13 != 0; uVar13 = uVar13 - 1) {
          *(undefined1 *)puVar21 = *(undefined1 *)puVar20;
          puVar20 = (undefined4 *)((int)puVar20 + 1);
          puVar21 = (undefined4 *)((int)puVar21 + 1);
        }
        param_2 = (undefined4 *)((int)puVar8 + puVar18[1] * 2);
        (**(code **)(DAT_00c97b24 + 0x138))(*(undefined4 *)(iVar16 + uVar9 * 4));
        *(undefined4 *)(iVar16 + uVar9 * 4) = 0;
        uVar9 = uVar9 + 1;
        puVar8 = param_2;
        puVar18 = puVar18 + 3;
      } while (uVar9 < param_3);
    }
    (**(code **)(DAT_00c97b24 + 0x138))(piVar3);
    (**(code **)(DAT_00c97b24 + 0x138))(iVar16);
    (**(code **)(DAT_00c97b24 + 0x138))(puVar5);
  }
  return puVar4;
}



/* entry 0x00759790; bounded CFG instructions=160; body bytes=2302 */

undefined4 FUN_00759790(int param_1,uint param_2,int *param_3,int param_4)

{
  undefined2 *puVar1;
  int **ppiVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int *piVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  int *piVar12;
  undefined2 *puVar13;
  int iVar14;
  int iVar15;
  uint uVar16;
  undefined4 *puVar17;
  undefined4 *puVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  uint uVar24;
  int local_4c;
  uint local_48;
  int local_3c;
  uint uStack_38;
  uint uStack_28;
  int local_1c;
  undefined4 local_18;
  undefined4 local_14;
  int *local_10;
  int local_c [3];
  
  local_1c = 0;
  local_48 = 0;
  local_3c = 0;
  local_4c = 0;
  local_10 = (int *)0x0;
  local_c[0] = 0;
  local_c[1] = 0;
  local_c[2] = 0;
  local_18 = 0;
  local_14 = 0;
  iVar6 = FUN_0075a090(param_2,&local_18,&local_1c,param_1);
  uVar7 = 0;
  if (param_2 != 0) {
    do {
      iVar11 = *(int *)(iVar6 + uVar7 * 4);
      *(int **)(iVar11 + 0x10) = (&local_10)[*(byte *)(iVar11 + 0x20)];
      iVar11 = *(int *)(iVar6 + uVar7 * 4);
      iVar9 = *(int *)(iVar11 + 0x10);
      if (iVar9 != 0) {
        *(int *)(iVar9 + 0x14) = iVar11;
      }
      piVar8 = *(int **)(iVar6 + uVar7 * 4);
      uVar7 = uVar7 + 1;
      (&local_10)[*(byte *)(piVar8 + 8)] = piVar8;
      *(undefined4 *)(*(int *)(iVar6 + -4 + uVar7 * 4) + 0x14) = 0;
    } while (uVar7 < param_2);
  }
  piVar8 = (int *)(**(code **)(DAT_00c97b24 + 0x144))
                            (*(undefined4 *)(DAT_00c9b8c0 + 4 + DAT_00c97b24),0x10502);
  iVar11 = param_2 * 2 + 2;
  piVar8[1] = 0;
  piVar8[2] = iVar11;
  iVar9 = (**(code **)(DAT_00c97b24 + 0x134))(iVar11 * 4,0x10502);
  *piVar8 = iVar9;
  piVar10 = (int *)(**(code **)(DAT_00c97b24 + 0x144))
                             (*(undefined4 *)(DAT_00c9b8c0 + 4 + DAT_00c97b24),0x10502);
  piVar10[2] = iVar11;
  piVar10[1] = 0;
  iVar11 = (**(code **)(DAT_00c97b24 + 0x134))(iVar11 * 4,0x10502);
  *piVar10 = iVar11;
  if (param_2 == 0) {
LAB_00759f9c:
    (**(code **)(DAT_00c97b24 + 0x138))(*piVar10);
    *piVar10 = 0;
    (**(code **)(DAT_00c97b24 + 0x148))(*(undefined4 *)(DAT_00c9b8c0 + 4 + DAT_00c97b24),piVar10);
    (**(code **)(DAT_00c97b24 + 0x138))(*piVar8);
    *piVar8 = 0;
    (**(code **)(DAT_00c97b24 + 0x148))(*(undefined4 *)(DAT_00c9b8c0 + 4 + DAT_00c97b24),piVar8);
    iVar11 = local_1c;
    while (iVar11 != 0) {
      iVar9 = *(int *)(iVar11 + 0xc);
      (**(code **)(DAT_00c97b24 + 0x148))(local_14,iVar11);
      iVar11 = iVar9;
    }
    FUN_00801b80(local_14);
    uVar7 = 0;
    local_14 = 0;
    if (param_2 != 0) {
      do {
        (**(code **)(DAT_00c97b24 + 0x148))(local_18,*(undefined4 *)(iVar6 + uVar7 * 4));
        *(undefined4 *)(iVar6 + uVar7 * 4) = 0;
        uVar7 = uVar7 + 1;
      } while (uVar7 < param_2);
    }
    FUN_00801b80(local_18);
    local_18 = 0;
    (**(code **)(DAT_00c97b24 + 0x138))(iVar6);
    return 1;
  }
LAB_007598bb:
  iVar9 = 0;
  uStack_38 = 0;
  iVar11 = (-(uint)(param_4 != 0) & 0xfffffffd) + 3;
  if (local_10 == (int *)0x0) {
    iVar14 = 1;
    iVar22 = local_c[0];
    while (iVar22 == 0) {
      piVar12 = local_c + iVar14;
      iVar14 = iVar14 + 1;
      iVar22 = *piVar12;
    }
    piVar12 = (&local_10)[iVar14];
    ppiVar2 = &local_10 + iVar14;
    iVar22 = *(int *)(piVar12[3] + 4);
    if ((iVar22 == 0) || (*(int *)(iVar22 + 0x18) != 0)) {
      iVar14 = 0;
    }
    else {
      iVar14 = 1;
    }
    iVar15 = *(int *)(piVar12[3] + 8);
    if ((iVar15 != 0) && (*(int *)(iVar15 + 0x18) == 0)) {
      iVar9 = 1;
    }
    if (1 < (uint)(iVar14 + iVar9)) {
      iVar9 = *(int *)(piVar12[2] + 4);
      if ((iVar9 == 0) || (*(int *)(iVar9 + 0x18) != 0)) {
        iVar9 = 0;
      }
      else {
        iVar9 = 1;
      }
      iVar14 = *(int *)(piVar12[2] + 8);
      if ((iVar14 == 0) || (*(int *)(iVar14 + 0x18) != 0)) {
        iVar14 = 0;
      }
      else {
        iVar14 = 1;
      }
      if (1 < (uint)(iVar9 + iVar14)) {
        uStack_28 = 1;
        uVar7 = uStack_28;
        goto LAB_00759c5c;
      }
    }
    iVar9 = *(int *)(piVar12[1] + 4);
    if ((iVar9 == 0) || (*(int *)(iVar9 + 0x18) != 0)) {
      iVar14 = 0;
    }
    else {
      iVar14 = 1;
    }
    iVar3 = *(int *)(piVar12[1] + 8);
    if ((iVar3 == 0) || (*(int *)(iVar3 + 0x18) != 0)) {
      iVar19 = 0;
    }
    else {
      iVar19 = 1;
    }
    if (1 < (uint)(iVar14 + iVar19)) {
      if ((iVar22 == 0) || (*(int *)(iVar22 + 0x18) != 0)) {
        iVar14 = 0;
      }
      else {
        iVar14 = 1;
      }
      if ((iVar15 == 0) || (*(int *)(iVar15 + 0x18) != 0)) {
        iVar19 = 0;
      }
      else {
        iVar19 = 1;
      }
      if (1 < (uint)(iVar14 + iVar19)) {
        uStack_28 = 2;
        uVar7 = uStack_28;
        goto LAB_00759c5c;
      }
    }
    iVar14 = *(int *)(piVar12[2] + 4);
    if ((iVar14 == 0) || (*(int *)(iVar14 + 0x18) != 0)) {
      iVar19 = 0;
    }
    else {
      iVar19 = 1;
    }
    iVar4 = *(int *)(piVar12[2] + 8);
    if ((iVar4 == 0) || (*(int *)(iVar4 + 0x18) != 0)) {
      iVar20 = 0;
    }
    else {
      iVar20 = 1;
    }
    if (1 < (uint)(iVar19 + iVar20)) {
      if ((iVar9 == 0) || (*(int *)(iVar9 + 0x18) != 0)) {
        iVar19 = 0;
      }
      else {
        iVar19 = 1;
      }
      if ((iVar3 == 0) || (*(int *)(iVar3 + 0x18) != 0)) {
        iVar20 = 0;
      }
      else {
        iVar20 = 1;
      }
      if (1 < (uint)(iVar19 + iVar20)) {
        uStack_28 = 0;
        uVar7 = uStack_28;
        goto LAB_00759c5c;
      }
    }
    if ((iVar9 == 0) || (*(int *)(iVar9 + 0x18) != 0)) {
      iVar19 = 0;
    }
    else {
      iVar19 = 1;
    }
    if ((iVar3 == 0) || (*(int *)(iVar3 + 0x18) != 0)) {
      iVar20 = 0;
    }
    else {
      iVar20 = 1;
    }
    if ((iVar14 == 0) || (*(int *)(iVar14 + 0x18) != 0)) {
      iVar23 = 0;
    }
    else {
      iVar23 = 1;
    }
    if ((iVar4 == 0) || (*(int *)(iVar4 + 0x18) != 0)) {
      iVar21 = 0;
    }
    else {
      iVar21 = 1;
    }
    if ((uint)(iVar23 + iVar21) < (uint)(iVar19 + iVar20)) {
      if ((iVar9 == 0) || (*(int *)(iVar9 + 0x18) != 0)) {
        iVar9 = 0;
      }
      else {
        iVar9 = 1;
      }
      if ((iVar3 == 0) || (*(int *)(iVar3 + 0x18) != 0)) {
        iVar14 = 0;
      }
      else {
        iVar14 = 1;
      }
      if ((iVar22 == 0) || (*(int *)(iVar22 + 0x18) != 0)) {
        uVar7 = 0;
      }
      else {
        uVar7 = 1;
      }
      if ((iVar15 == 0) || (*(int *)(iVar15 + 0x18) != 0)) {
        uStack_28 = (uVar7 < (uint)(iVar9 + iVar14)) + 1;
        uVar7 = uStack_28;
      }
      else {
        uStack_28 = (uVar7 + 1 < (uint)(iVar9 + iVar14)) + 1;
        uVar7 = uStack_28;
      }
    }
    else {
      if ((iVar14 == 0) || (*(int *)(iVar14 + 0x18) != 0)) {
        iVar9 = 0;
      }
      else {
        iVar9 = 1;
      }
      if ((iVar4 == 0) || (*(int *)(iVar4 + 0x18) != 0)) {
        iVar14 = 0;
      }
      else {
        iVar14 = 1;
      }
      if ((iVar22 == 0) || (*(int *)(iVar22 + 0x18) != 0)) {
        iVar22 = 0;
      }
      else {
        iVar22 = 1;
      }
      if ((iVar15 == 0) || (*(int *)(iVar15 + 0x18) != 0)) {
        iVar15 = 0;
      }
      else {
        iVar15 = 1;
      }
      uStack_28 = (uint)((uint)(iVar9 + iVar14) <= (uint)(iVar22 + iVar15));
      uVar7 = uStack_28;
    }
LAB_00759c5c:
    do {
      uVar16 = 0;
      do {
        uVar16 = uVar16 + 1;
        iVar9 = *(int *)(iVar6 + -4 + uVar16 * 4);
        *(undefined4 *)(iVar9 + 0x1c) = *(undefined4 *)(iVar9 + 0x18);
      } while (uVar16 < param_2);
      iVar9 = iVar11 + 1;
      uVar16 = uVar7;
      if (iVar11 == 0) {
LAB_00759c95:
        uVar16 = uVar16 % 3;
      }
      else {
        if (iVar11 == 1) {
          uVar16 = uVar7 + 1;
          goto LAB_00759c95;
        }
        uVar16 = uStack_28;
        if (iVar11 == 2) {
          uVar16 = uVar7 + 2;
          goto LAB_00759c95;
        }
      }
      if (uVar16 == 0) {
        local_3c = (*ppiVar2)[2];
        local_4c = (*ppiVar2)[1];
      }
      else if (uVar16 == 1) {
        local_3c = (*ppiVar2)[3];
        local_4c = (*ppiVar2)[2];
      }
      else if (uVar16 == 2) {
        local_3c = (*ppiVar2)[1];
        local_4c = (*ppiVar2)[3];
      }
      iVar11 = param_1 + **ppiVar2 * 0x14;
      *(undefined2 *)*piVar8 = *(undefined2 *)(iVar11 + (uVar16 % 3) * 2);
      *(undefined2 *)(*piVar8 + 2) = *(undefined2 *)(iVar11 + ((uVar16 + 1) % 3) * 2);
      *(undefined2 *)(*piVar8 + 4) = *(undefined2 *)(iVar11 + ((uVar16 + 2) % 3) * 2);
      piVar8[1] = 3;
      FUN_0075a250(*ppiVar2,&local_10,iVar9);
      iVar11 = FUN_0075a370(piVar8,local_3c,&local_10,param_1,iVar9);
      uVar24 = iVar11 + 1 + local_48;
      iVar11 = *(int *)(local_4c + 4);
      if (iVar9 < 4) {
        if ((iVar11 == 0) || (*(int *)(iVar11 + 0x1c) != 0)) {
          iVar22 = 0;
        }
        else {
          iVar22 = 1;
        }
        if ((*(int *)(local_4c + 8) == 0) || (*(int *)(*(int *)(local_4c + 8) + 0x1c) != 0)) {
LAB_00759dbd:
          iVar14 = 0;
        }
        else {
          iVar14 = 1;
        }
      }
      else {
        if ((iVar11 == 0) || (*(int *)(iVar11 + 0x18) != 0)) {
          iVar22 = 0;
        }
        else {
          iVar22 = 1;
        }
        if ((*(int *)(local_4c + 8) == 0) || (*(int *)(*(int *)(local_4c + 8) + 0x18) != 0))
        goto LAB_00759dbd;
        iVar14 = 1;
      }
      iVar11 = iVar9;
      if (iVar22 + iVar14 == 0) goto LAB_00759e47;
      *(undefined2 *)*piVar10 = *(undefined2 *)(*piVar8 + 2);
      *(undefined2 *)(*piVar10 + 2) = *(undefined2 *)*piVar8;
      piVar10[1] = 2;
      iVar22 = FUN_0075a370(piVar10,local_4c,&local_10,param_1,iVar9);
      uVar24 = uVar24 + iVar22;
      uVar5 = piVar10[1];
      if ((uVar5 & 1) != 0) {
        *(undefined2 *)(*piVar10 + uVar5 * 2) = *(undefined2 *)(*piVar10 + -4 + uVar5 * 2);
        piVar10[1] = piVar10[1] + 1;
      }
      if (uStack_38 < uVar24) {
        uStack_38 = uVar24;
        uStack_28 = uVar16;
      }
    } while (iVar9 < 4);
    piVar12 = (int *)(**(code **)(DAT_00c97b24 + 0x144))
                               (*(undefined4 *)(DAT_00c9b8c0 + 4 + DAT_00c97b24),0x30502);
    piVar12[3] = *param_3;
    *param_3 = (int)piVar12;
    iVar9 = piVar8[1];
    iVar11 = piVar10[1];
    piVar12[1] = 0;
    iVar11 = iVar9 + -2 + iVar11;
    piVar12[2] = iVar11;
    iVar11 = (**(code **)(DAT_00c97b24 + 0x134))(iVar11 * 4,0x30502);
    *piVar12 = iVar11;
    uVar7 = piVar10[1];
    while (2 < uVar7) {
      *(undefined2 *)(*piVar12 + piVar12[1] * 2) = *(undefined2 *)(*piVar10 + -2 + piVar10[1] * 2);
      piVar12[1] = piVar12[1] + 1;
      uVar7 = piVar10[1] - 1;
      piVar10[1] = uVar7;
    }
    puVar17 = (undefined4 *)*piVar8;
    puVar18 = (undefined4 *)(*piVar12 + piVar12[1] * 2);
    for (uVar7 = piVar8[1] & 0x3fffffff; uVar7 != 0; uVar7 = uVar7 - 1) {
      *puVar18 = *puVar17;
      puVar17 = puVar17 + 1;
      puVar18 = puVar18 + 1;
    }
    for (iVar11 = 0; iVar11 != 0; iVar11 = iVar11 + -1) {
      *(undefined1 *)puVar18 = *(undefined1 *)puVar17;
      puVar17 = (undefined4 *)((int)puVar17 + 1);
      puVar18 = (undefined4 *)((int)puVar18 + 1);
    }
    piVar12[1] = piVar12[2];
    local_48 = uVar24;
    goto LAB_00759f88;
  }
  iVar11 = *local_10;
  piVar12 = (int *)(**(code **)(DAT_00c97b24 + 0x144))
                             (*(undefined4 *)(DAT_00c9b8c0 + 4 + DAT_00c97b24),0x30502);
  piVar12[3] = *param_3;
  *param_3 = (int)piVar12;
  piVar12[2] = 3;
  piVar12[1] = 3;
  puVar13 = (undefined2 *)(**(code **)(DAT_00c97b24 + 0x134))(0xc,0x30502);
  *piVar12 = (int)puVar13;
  puVar1 = (undefined2 *)(param_1 + iVar11 * 0x14);
  *puVar13 = *puVar1;
  *(undefined2 *)(*piVar12 + 2) = puVar1[1];
  *(undefined2 *)(*piVar12 + 4) = puVar1[2];
  local_10[6] = 1;
  local_10[7] = 1;
  local_10 = (int *)local_10[4];
  if (local_10 != (int *)0x0) {
    local_10[5] = 0;
  }
  local_48 = local_48 + 1;
  goto LAB_00759f88;
LAB_00759e47:
  if (uStack_38 < uVar24) {
    uStack_38 = uVar24;
    uStack_28 = uVar16;
  }
  if (3 < iVar9) goto LAB_00759f1b;
  goto LAB_00759c5c;
LAB_00759f1b:
  puVar17 = (undefined4 *)
            (**(code **)(DAT_00c97b24 + 0x144))
                      (*(undefined4 *)(DAT_00c9b8c0 + 4 + DAT_00c97b24),0x30502);
  puVar17[3] = *param_3;
  *param_3 = (int)puVar17;
  puVar17[2] = piVar8[1];
  puVar17[1] = piVar8[1];
  puVar18 = (undefined4 *)(**(code **)(DAT_00c97b24 + 0x134))(piVar8[1] << 2,0x30502);
  *puVar17 = puVar18;
  puVar17 = (undefined4 *)*piVar8;
  for (uVar7 = piVar8[1] & 0x3fffffff; uVar7 != 0; uVar7 = uVar7 - 1) {
    *puVar18 = *puVar17;
    puVar17 = puVar17 + 1;
    puVar18 = puVar18 + 1;
  }
  for (iVar11 = 0; local_48 = uVar24, iVar11 != 0; iVar11 = iVar11 + -1) {
    *(undefined1 *)puVar18 = *(undefined1 *)puVar17;
    puVar17 = (undefined4 *)((int)puVar17 + 1);
    puVar18 = (undefined4 *)((int)puVar18 + 1);
  }
LAB_00759f88:
  if (param_2 <= local_48) goto LAB_00759f9c;
  goto LAB_007598bb;
}



/* entry 0x007C51D0; bounded CFG instructions=160; body bytes=2467 */

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



/* entry 0x007C7190; bounded CFG instructions=100; body bytes=269 */

undefined4
FUN_007c7190(int *param_1,int param_2,uint param_3,uint param_4,undefined4 *param_5,
            undefined4 *param_6,undefined4 *param_7,int param_8)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  undefined4 *puVar8;
  
  uVar6 = param_2 * 0x40 + param_4 * 0x14 + 0xf + param_3;
  puVar1 = (undefined4 *)(**(code **)(DAT_00c97b24 + 0x134))(uVar6,0x30116);
  uVar2 = 0;
  param_1[0xf] = (int)puVar1;
  if (puVar1 != (undefined4 *)0x0) {
    for (uVar5 = uVar6 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *puVar1 = 0;
      puVar1 = puVar1 + 1;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined1 *)puVar1 = 0;
      puVar1 = (undefined4 *)((int)puVar1 + 1);
    }
    puVar1 = (undefined4 *)param_1[0xf];
    *param_1 = param_2;
    param_1[1] = param_3;
    uVar6 = (uint)((int)puVar1 + param_3 + 0xf) & 0xfffffff0;
    param_1[3] = uVar6;
    iVar3 = uVar6 + param_2 * 0x40;
    param_1[5] = iVar3;
    param_1[2] = (int)puVar1;
    param_1[6] = iVar3 + param_4 * 4;
    if ((param_5 != (undefined4 *)0x0) && (param_3 != 0)) {
      for (uVar6 = param_3 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *puVar1 = *param_5;
        param_5 = param_5 + 1;
        puVar1 = puVar1 + 1;
      }
      for (param_3 = param_3 & 3; param_3 != 0; param_3 = param_3 - 1) {
        *(undefined1 *)puVar1 = *(undefined1 *)param_5;
        param_5 = (undefined4 *)((int)param_5 + 1);
        puVar1 = (undefined4 *)((int)puVar1 + 1);
      }
    }
    if ((param_8 != 0) && (iVar3 = *param_1, iVar3 != 0)) {
      iVar4 = iVar3 << 6;
      do {
        iVar4 = iVar4 + -0x40;
        iVar3 = iVar3 + -1;
        puVar1 = (undefined4 *)(iVar4 + param_8);
        puVar8 = (undefined4 *)(param_1[3] + iVar4);
        for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
          *puVar8 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar8 = puVar8 + 1;
        }
      } while (iVar3 != 0);
    }
    if (param_7 != (undefined4 *)0x0) {
      puVar1 = (undefined4 *)param_1[5];
      for (uVar6 = param_4 & 0x3fffffff; uVar6 != 0; uVar6 = uVar6 - 1) {
        *puVar1 = *param_7;
        param_7 = param_7 + 1;
        puVar1 = puVar1 + 1;
      }
      for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
        *(undefined1 *)puVar1 = *(undefined1 *)param_7;
        param_7 = (undefined4 *)((int)param_7 + 1);
        puVar1 = (undefined4 *)((int)puVar1 + 1);
      }
    }
    if (param_6 != (undefined4 *)0x0) {
      puVar1 = (undefined4 *)param_1[6];
      for (iVar3 = (param_4 & 0xfffffff) << 2; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar1 = *param_6;
        param_6 = param_6 + 1;
        puVar1 = puVar1 + 1;
      }
      for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
        *(undefined1 *)puVar1 = *(undefined1 *)param_6;
        param_6 = (undefined4 *)((int)param_6 + 1);
        puVar1 = (undefined4 *)((int)puVar1 + 1);
      }
    }
    uVar2 = 1;
  }
  return uVar2;
}



/* entry 0x007C75B0; bounded CFG instructions=160; body bytes=494 */

int * FUN_007c75b0(uint param_1,int param_2,undefined4 *param_3,undefined4 *param_4,int param_5)

{
  int *piVar1;
  uint uVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  uint uVar8;
  undefined4 *puVar9;
  uint local_104;
  undefined4 auStack_100 [64];
  
  local_104 = 0;
  piVar1 = (int *)(**(code **)(DAT_00c97b24 + 0x144))(DAT_00c978b8,0x30116);
  piVar6 = piVar1;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar6 = 0;
    piVar6 = piVar6 + 1;
  }
  uVar8 = 0;
  piVar1[4] = 1;
  if (param_1 != 0) {
    do {
      uVar2 = piVar1[4];
      if (uVar2 < 4) {
        piVar6 = param_3 + uVar2 + uVar8 * 4;
        do {
          if (*piVar6 == 0) break;
          iVar5 = piVar1[4];
          piVar1[4] = iVar5 + 1;
          if (iVar5 + 1 == 4) goto LAB_007c7633;
          uVar2 = uVar2 + 1;
          piVar6 = piVar6 + 1;
        } while (uVar2 < 4);
      }
      uVar8 = uVar8 + 1;
    } while (uVar8 < param_1);
  }
LAB_007c7633:
  FUN_007c70c0(piVar1,param_4,param_3,auStack_100,&local_104,param_1);
  uVar8 = local_104;
  local_104 = param_2 * 0x40 + param_1 * 0x14 + 0xf + local_104;
  puVar3 = (undefined4 *)(**(code **)(DAT_00c97b24 + 0x134))(local_104,0x30116);
  piVar1[0xf] = (int)puVar3;
  if (puVar3 != (undefined4 *)0x0) {
    for (uVar2 = local_104 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    for (local_104 = local_104 & 3; local_104 != 0; local_104 = local_104 - 1) {
      *(undefined1 *)puVar3 = 0;
      puVar3 = (undefined4 *)((int)puVar3 + 1);
    }
    puVar3 = (undefined4 *)piVar1[0xf];
    *piVar1 = param_2;
    piVar1[1] = uVar8;
    uVar2 = (uint)((int)puVar3 + uVar8 + 0xf) & 0xfffffff0;
    piVar1[3] = uVar2;
    iVar5 = uVar2 + param_2 * 0x40;
    piVar1[5] = iVar5;
    piVar1[6] = iVar5 + param_1 * 4;
    piVar1[2] = (int)puVar3;
    if ((&stack0x00000000 != (undefined1 *)0x100) && (uVar8 != 0)) {
      puVar9 = auStack_100;
      for (uVar2 = uVar8 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar3 = *puVar9;
        puVar9 = puVar9 + 1;
        puVar3 = puVar3 + 1;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined1 *)puVar3 = *(undefined1 *)puVar9;
        puVar9 = (undefined4 *)((int)puVar9 + 1);
        puVar3 = (undefined4 *)((int)puVar3 + 1);
      }
    }
    if ((param_5 != 0) && (iVar5 = *piVar1, iVar5 != 0)) {
      iVar4 = iVar5 << 6;
      do {
        iVar4 = iVar4 + -0x40;
        iVar5 = iVar5 + -1;
        puVar3 = (undefined4 *)(iVar4 + param_5);
        puVar9 = (undefined4 *)(piVar1[3] + iVar4);
        for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
          *puVar9 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar9 = puVar9 + 1;
        }
      } while (iVar5 != 0);
    }
    if (param_4 != (undefined4 *)0x0) {
      puVar3 = (undefined4 *)piVar1[5];
      for (uVar8 = param_1 & 0x3fffffff; uVar8 != 0; uVar8 = uVar8 - 1) {
        *puVar3 = *param_4;
        param_4 = param_4 + 1;
        puVar3 = puVar3 + 1;
      }
      for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
        *(undefined1 *)puVar3 = *(undefined1 *)param_4;
        param_4 = (undefined4 *)((int)param_4 + 1);
        puVar3 = (undefined4 *)((int)puVar3 + 1);
      }
    }
    if (param_3 != (undefined4 *)0x0) {
      puVar3 = (undefined4 *)piVar1[6];
      for (iVar5 = (param_1 & 0xfffffff) << 2; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar3 = *param_3;
        param_3 = param_3 + 1;
        puVar3 = puVar3 + 1;
      }
      for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
        *(undefined1 *)puVar3 = *(undefined1 *)param_3;
        param_3 = (undefined4 *)((int)param_3 + 1);
        puVar3 = (undefined4 *)((int)puVar3 + 1);
      }
    }
    return piVar1;
  }
  (**(code **)(DAT_00c97b24 + 0x148))(DAT_00c978b8,piVar1);
  return (int *)0x0;
}



/* entry 0x007C88B0; bounded CFG instructions=71; body bytes=202 */

uint FUN_007c88b0(uint param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int local_10;
  undefined1 local_c [4];
  undefined4 local_8;
  undefined4 local_4;
  
  uVar1 = param_1;
  iVar2 = FUN_007ed2d0(param_1,1,local_c,&param_1);
  if (iVar2 != 0) {
    if ((param_1 < 0x34000) || (0x36003 < param_1)) {
      local_8 = 0x116;
      local_4 = FUN_008088d0(0x80000004);
      FUN_00808820(&local_8);
    }
    else {
      iVar2 = FUN_007ed540(uVar1,&local_10,4);
      if ((iVar2 != 0) && (local_10 == 9)) {
        puVar3 = (undefined4 *)(**(code **)(DAT_00c97b24 + 0x144))(DAT_00c978b8,0x30116);
        puVar4 = puVar3;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar4 = 0;
          puVar4 = puVar4 + 1;
        }
        iVar2 = FUN_007ed540(uVar1,puVar3,4);
        if (iVar2 != 0) {
          FUN_007c7560(param_2,puVar3);
          return uVar1;
        }
      }
    }
  }
  return 0;
}



/* entry 0x007C8A70; bounded CFG instructions=58; body bytes=158 */

int FUN_007c8a70(int param_1,undefined4 param_2,int param_3,int param_4,int param_5)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  if (*(int *)(param_1 + 0x30) != 0) {
    (**(code **)(DAT_00c97b24 + 0x138))(*(int *)(param_1 + 0x30));
  }
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0;
  uVar4 = param_3 + (param_4 + param_5) * 2;
  puVar1 = (undefined4 *)(**(code **)(DAT_00c97b24 + 0x134))(uVar4,0x30116);
  *(undefined4 **)(param_1 + 0x30) = puVar1;
  iVar2 = 0;
  if (puVar1 != (undefined4 *)0x0) {
    for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar1 = 0;
      puVar1 = puVar1 + 1;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined1 *)puVar1 = 0;
      puVar1 = (undefined4 *)((int)puVar1 + 1);
    }
    *(undefined4 *)(param_1 + 0x24) = param_2;
    *(int *)(param_1 + 0x2c) = param_5;
    param_3 = param_3 + *(int *)(param_1 + 0x30);
    *(int *)(param_1 + 0x28) = param_4;
    *(int *)(param_1 + 0x34) = param_3;
    *(int *)(param_1 + 0x38) = param_3 + param_4 * 2;
    iVar2 = param_1;
  }
  return iVar2;
}



/* entry 0x007C8BE0; bounded CFG instructions=138; body bytes=349 */

undefined4 FUN_007c8be0(undefined4 param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  uint uVar5;
  int local_14;
  int local_10;
  int local_c;
  uint local_8;
  int local_4;
  
  piVar1 = param_2 + 9;
  iVar2 = FUN_007ed540(param_1,&local_c,4);
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = FUN_007ed540(param_1,&local_14,4);
  if (iVar2 != 0) {
    iVar2 = FUN_007ed540(param_1,&local_10,4);
    if (iVar2 == 0) {
      return 0;
    }
    uVar4 = param_1;
    if (0 < local_14) {
      local_4 = local_c;
      iVar2 = *param_2;
      if (param_2[0xc] != 0) {
        (**(code **)(DAT_00c97b24 + 0x138))(param_2[0xc]);
      }
      *piVar1 = 0;
      param_2[10] = 0;
      param_2[0xb] = 0;
      param_2[0xc] = 0;
      param_2[0xd] = 0;
      param_2[0xe] = 0;
      local_8 = iVar2 + (local_14 + local_10) * 2;
      puVar3 = (undefined4 *)(**(code **)(DAT_00c97b24 + 0x134))(local_8,0x30116);
      param_2[0xc] = (int)puVar3;
      uVar4 = 0;
      if (puVar3 != (undefined4 *)0x0) {
        for (uVar5 = local_8 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *puVar3 = 0;
          puVar3 = puVar3 + 1;
        }
        for (uVar5 = local_8 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined1 *)puVar3 = 0;
          puVar3 = (undefined4 *)((int)puVar3 + 1);
        }
        *piVar1 = local_4;
        param_2[10] = local_14;
        iVar2 = param_2[0xc] + iVar2;
        param_2[0xd] = iVar2;
        param_2[0xb] = local_10;
        param_2[0xe] = iVar2 + local_14 * 2;
        iVar2 = FUN_007ec9d0(param_1,param_2[0xc],*param_2 + (local_10 + local_14) * 2);
        uVar4 = param_1;
        if (iVar2 == 0) {
          (**(code **)(DAT_00c97b24 + 0x138))(piVar1);
          return 0;
        }
      }
    }
    return uVar4;
  }
  return 0;
}



/* entry 0x007CDF60; bounded CFG instructions=160; body bytes=1633 */

int FUN_007cdf60(undefined4 param_1)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  undefined1 *puVar8;
  int iVar9;
  undefined1 *puVar10;
  uint uVar11;
  uint uVar12;
  byte *pbVar13;
  int local_450;
  uint local_44c;
  undefined4 local_448;
  int local_444;
  int local_440;
  uint local_43c [4];
  int local_42c;
  int local_424;
  int local_420;
  short local_41a;
  int local_418;
  undefined1 auStack_404 [4];
  undefined4 local_400;
  undefined4 local_3fc;
  undefined4 local_3f8;
  int local_3f4;
  int local_3e4;
  
  iVar2 = FUN_007ecef0(2,1,param_1);
  if (iVar2 == 0) {
    return 0;
  }
  local_440 = iVar2;
  iVar3 = FUN_007ec9d0(iVar2,local_43c,4);
  if (iVar3 != 4) {
    FUN_007ece20(iVar2,0);
    return 0;
  }
  if ((local_43c[0] & 0xffff) != 0x4d42) {
    FUN_007ece20(iVar2,0);
    return 0;
  }
  iVar4 = FUN_007ec9d0(iVar2,(int)&local_400 + 2,0xe);
  iVar3 = local_3f4;
  if (iVar4 != 0xe) {
    FUN_007ece20(iVar2,0);
    return 0;
  }
  local_42c = local_3f8;
  iVar4 = local_3f4 + -4;
  iVar5 = FUN_007ec9d0(iVar2,&local_400,iVar4);
  if (iVar5 != iVar4) {
    FUN_007ece20(iVar2,0);
    return 0;
  }
  local_450 = iVar3 + 0xe;
  if (iVar3 == 0xc) {
    local_424 = (int)(short)local_400;
    local_420 = (int)local_400._2_2_;
    local_41a = local_3fc._2_2_;
    local_418 = 0;
LAB_007ce0fc:
    iVar4 = 1 << ((byte)local_41a & 0x1f);
  }
  else {
    local_424 = local_400;
    local_420 = local_3fc;
    local_41a = local_3f8._2_2_;
    local_418 = local_3f4;
    if (local_3f4 == 2) {
      local_44c = 0x19d;
      local_448 = FUN_008088d0(0x80000009);
      goto LAB_007ce0c7;
    }
    if ((local_3e4 < 1) ||
       (iVar4 = local_3e4, 1 << ((byte)((uint)local_3f8 >> 0x10) & 0x1f) < local_3e4))
    goto LAB_007ce0fc;
  }
  local_444 = (int)local_41a;
  if ((local_444 == 1) || (local_444 == 4)) {
    uVar6 = 4;
  }
  else if (local_444 == 8) {
    uVar6 = 8;
  }
  else {
    uVar6 = 0x20;
  }
  iVar5 = FUN_008026e0(local_424,local_420,uVar6);
  if (iVar5 == 0) {
    FUN_007ece20(iVar2,0);
    return 0;
  }
  iVar7 = FUN_008027a0(iVar5);
  if (iVar7 != 0) {
    if (local_41a < 9) {
      iVar7 = *(int *)(iVar5 + 0x18);
      if (iVar3 == 0xc) {
        local_450 = iVar4 * 3;
        iVar3 = FUN_007ec9d0(iVar2,&local_400,local_450);
        if (iVar3 != local_450) {
          FUN_007ece20(iVar2,0);
          return 0;
        }
        local_450 = local_450 + 0x1a;
        if (0 < iVar4) {
          puVar8 = (undefined1 *)(iVar7 + 2);
          puVar10 = (undefined1 *)((int)&local_400 + 1);
          do {
            puVar8[-2] = puVar10[1];
            puVar8[-1] = *puVar10;
            *puVar8 = puVar10[-1];
            puVar8[1] = 0xff;
            puVar8 = puVar8 + 4;
            iVar4 = iVar4 + -1;
            puVar10 = puVar10 + 3;
          } while (iVar4 != 0);
        }
      }
      else {
        if (iVar3 != 0x28) {
          local_44c = 0x19d;
          local_448 = FUN_008088d0(0x80000009);
LAB_007ce0c7:
          FUN_00808820(&local_44c);
LAB_007ce0cf:
          FUN_007ece20(iVar2,0);
          return 0;
        }
        local_450 = iVar4 * 4;
        iVar3 = FUN_007ec9d0(iVar2,&local_400,local_450);
        if (iVar3 != local_450) {
          FUN_007ece20(iVar2,0);
          return 0;
        }
        local_450 = local_450 + 0x36;
        iVar3 = 0;
        if (0 < iVar4) {
          puVar8 = (undefined1 *)(iVar7 + 2);
          do {
            iVar3 = iVar3 + 1;
            puVar8[-2] = puVar8[(int)&local_400 - iVar7];
            puVar8[-1] = auStack_404[iVar3 * 4 + 1];
            *puVar8 = auStack_404[iVar3 * 4];
            puVar8[1] = 0xff;
            puVar8 = puVar8 + 4;
          } while (iVar3 < iVar4);
        }
      }
    }
    iVar3 = FUN_007ecd00(iVar2,local_42c - local_450);
    if (iVar3 != 0) {
      iVar2 = local_444 * local_424 + 7;
      uVar11 = local_424 + 7;
      iVar4 = (int)(local_444 + 7 + (local_444 + 7 >> 0x1f & 7U)) >> 3;
      uVar12 = ((int)(iVar2 + (iVar2 >> 0x1f & 7U)) >> 3) + 3U & 0xfffffffc;
      iVar3 = (**(code **)(DAT_00c97b24 + 0x134))((uVar11 & 0xfffffff8) * iVar4,0x10000);
      if (iVar3 == 0) {
        local_44c = 0x19d;
        local_448 = FUN_008088d0(0x80000013,(uVar11 & 0xfffffff8) * iVar4);
        FUN_00808820(&local_44c);
LAB_007ce531:
        FUN_00802740(iVar5);
        FUN_007ece20(local_440,0);
        return 0;
      }
      if (((local_418 == 0) || (local_41a == 0x18)) || (local_41a == 0x20)) {
        iVar4 = 0;
        iVar2 = local_420;
        if (0 < local_420) {
          do {
            uVar11 = FUN_007ec9d0(local_440,iVar3,uVar12);
            if (uVar11 != uVar12) {
              (**(code **)(DAT_00c97b24 + 0x138))(iVar3);
              FUN_00802740(iVar5);
              iVar2 = local_440;
              goto LAB_007ce0cf;
            }
            FUN_007ce5d0(iVar5,iVar2 + -1,iVar3,local_444,0);
            iVar4 = iVar4 + 1;
            iVar2 = iVar2 + -1;
          } while (iVar4 < local_420);
        }
      }
      else {
        if (local_418 != 1) {
          local_44c = 0x19d;
          local_448 = FUN_008088d0(0x80000009);
          FUN_00808820(&local_44c);
          (**(code **)(DAT_00c97b24 + 0x138))(iVar3);
          goto LAB_007ce531;
        }
        local_450 = 0;
        if (0 < local_420) {
          do {
            iVar4 = 0;
            while( true ) {
              while( true ) {
                iVar2 = local_440;
                iVar9 = FUN_007ec9d0(local_440,&local_44c,2);
                iVar7 = local_420;
                if (iVar9 != 2) goto LAB_007ce4e5;
                bVar1 = (byte)(local_44c >> 8);
                if ((char)local_44c == '\0') break;
                pbVar13 = (byte *)(iVar3 + iVar4);
                for (uVar11 = (local_44c & 0xff) >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
                  *(uint *)pbVar13 = CONCAT22(CONCAT11(bVar1,bVar1),CONCAT11(bVar1,bVar1));
                  pbVar13 = pbVar13 + 4;
                }
                for (uVar11 = local_44c & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
                  *pbVar13 = bVar1;
                  pbVar13 = pbVar13 + 1;
                }
                iVar4 = iVar4 + (local_44c & 0xff);
              }
              if (bVar1 < 3) break;
              uVar11 = local_44c >> 8 & 0xff;
              uVar12 = FUN_007ec9d0(iVar2,iVar3 + iVar4,uVar11);
              if (uVar12 != uVar11) {
                (**(code **)(DAT_00c97b24 + 0x138))(iVar3);
                FUN_00802740(iVar5);
                goto LAB_007ce0cf;
              }
              iVar4 = iVar4 + (local_44c >> 8 & 0xff);
              if (((local_44c >> 8 & 1) != 0) &&
                 (iVar7 = FUN_007ec9d0(iVar2,&local_44c,1), iVar7 != 1)) {
                (**(code **)(DAT_00c97b24 + 0x138))(iVar3);
                FUN_00802740(iVar5);
                goto LAB_007ce0cf;
              }
            }
            if (bVar1 != 0) {
              if (bVar1 != 1) {
LAB_007ce4e5:
                (**(code **)(DAT_00c97b24 + 0x138))(iVar3);
                FUN_00802740(iVar5);
                goto LAB_007ce0cf;
              }
              local_450 = local_420 + -1;
            }
            FUN_007ce5d0(iVar5,(local_420 - local_450) + -1,iVar3,local_444,1);
            local_450 = local_450 + 1;
          } while (local_450 < iVar7);
        }
      }
      (**(code **)(DAT_00c97b24 + 0x138))(iVar3);
      FUN_007ece20(local_440,0);
      return iVar5;
    }
  }
  FUN_00802740(iVar5);
  FUN_007ece20(iVar2,0);
  return 0;
}



/* entry 0x007EC810; bounded CFG instructions=160; body bytes=431 */

undefined4 *
FUN_007ec810(undefined4 *param_1,undefined4 param_2,undefined4 param_3,int param_4,
            undefined4 *param_5)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  if (param_1 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  *param_1 = param_3;
  param_1[1] = param_4;
  param_1[8] = param_2;
  switch(param_3) {
  case 1:
    iVar1 = (**(code **)(DAT_00c97b24 + 0xec))(param_5);
    if (iVar1 == -1) {
      return (undefined4 *)0x0;
    }
    param_1[3] = param_5;
    return param_1;
  case 2:
    if (param_4 == 1) {
      iVar1 = (**(code **)(DAT_00c97b24 + 200))(param_5,&DAT_008e2220);
    }
    else if (param_4 == 2) {
      iVar1 = (**(code **)(DAT_00c97b24 + 200))(param_5,&DAT_008e2224);
    }
    else {
      if (param_4 != 3) {
        local_10 = 1;
        local_c = FUN_008088d0(0xd);
        FUN_00808820(&local_10);
        goto LAB_007ec8a4;
      }
      iVar1 = (**(code **)(DAT_00c97b24 + 200))(param_5,&DAT_008e2228);
    }
    if (iVar1 != 0) {
      param_1[3] = iVar1;
      return param_1;
    }
LAB_007ec8a4:
    local_8 = 1;
    local_4 = FUN_008088d0(0x80000002,param_5);
    FUN_00808820(&local_8);
    return (undefined4 *)0x0;
  case 3:
    if (param_4 == 1) {
      param_1[3] = 0;
      param_1[4] = param_5[1];
      param_1[5] = *param_5;
      return param_1;
    }
    if (param_4 == 2) {
      param_1[3] = 0;
      param_1[4] = 0;
      param_1[5] = 0;
      return param_1;
    }
    if (param_4 == 3) {
      param_1[3] = param_5[1];
      param_1[4] = param_5[1];
      param_1[5] = *param_5;
      return param_1;
    }
    uVar3 = 0xd;
    break;
  case 4:
    puVar2 = param_1 + 3;
    for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = *param_5;
      param_5 = param_5 + 1;
      puVar2 = puVar2 + 1;
    }
    return param_1;
  default:
    uVar3 = 0xe;
  }
  local_8 = 1;
  local_4 = FUN_008088d0(uVar3);
  FUN_00808820(&local_8);
  return (undefined4 *)0x0;
}



/* entry 0x007EC9D0; bounded CFG instructions=125; body bytes=332 */

uint FUN_007ec9d0(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 local_8;
  undefined4 local_4;
  
  switch(*param_1) {
  case 1:
  case 2:
    break;
  case 3:
    iVar3 = param_1[4];
    iVar2 = param_1[3];
    if ((uint)(iVar3 - iVar2) < param_3) {
      local_8 = 1;
      local_4 = FUN_008088d0(5);
      FUN_00808820(&local_8);
      param_3 = iVar3 - iVar2;
    }
    puVar5 = (undefined4 *)(param_1[5] + param_1[3]);
    for (uVar4 = param_3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *param_2 = *puVar5;
      puVar5 = puVar5 + 1;
      param_2 = param_2 + 1;
    }
    for (uVar4 = param_3 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined1 *)param_2 = *(undefined1 *)puVar5;
      puVar5 = (undefined4 *)((int)puVar5 + 1);
      param_2 = (undefined4 *)((int)param_2 + 1);
    }
    param_1[3] = param_1[3] + param_3;
    return param_3;
  case 4:
    uVar4 = (*(code *)param_1[4])(param_1[7],param_2,param_3);
    return uVar4;
  default:
    local_8 = 1;
    local_4 = FUN_008088d0(0xe);
    FUN_00808820(&local_8);
    return 0;
  }
  uVar1 = param_1[3];
  uVar4 = (**(code **)(DAT_00c97b24 + 0xd0))(param_2,1,param_3,uVar1);
  if (uVar4 != param_3) {
    iVar3 = (**(code **)(DAT_00c97b24 + 0xe0))(uVar1);
    local_8 = 1;
    if (iVar3 != 0) {
      local_4 = FUN_008088d0(5);
      FUN_00808820(&local_8);
      return uVar4;
    }
    local_4 = FUN_008088d0(0x8000001a);
    FUN_00808820(&local_8);
  }
  return uVar4;
}



/* entry 0x007ECB30; bounded CFG instructions=152; body bytes=436 */

undefined4 * FUN_007ecb30(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 local_8;
  undefined4 local_4;
  
  switch(*param_1) {
  case 1:
  case 2:
    uVar2 = (**(code **)(DAT_00c97b24 + 0xd4))(param_2,1,param_3,param_1[3]);
    if (uVar2 == param_3) {
      return param_1;
    }
    local_8 = 1;
    local_4 = FUN_008088d0(0x8000001c);
    break;
  case 3:
    if (param_1[5] == 0) {
      iVar1 = (**(code **)(DAT_00c97b24 + 0x134))(0x200,0x30404);
      param_1[5] = iVar1;
      if (iVar1 == 0) {
        local_8 = 1;
        local_4 = FUN_008088d0(0x80000013,0x200);
        FUN_00808820(&local_8);
        return (undefined4 *)0x0;
      }
      param_1[4] = 0x200;
    }
    iVar1 = param_1[4];
    if ((uint)(iVar1 - param_1[3]) < param_3) {
      iVar3 = iVar1 + 0x200;
      if (0x1ff < param_3) {
        iVar3 = iVar1 + param_3;
      }
      iVar1 = (**(code **)(DAT_00c97b24 + 0x13c))(param_1[5],iVar3,&LAB_01030404);
      if (iVar1 == 0) {
        local_8 = 1;
        local_4 = FUN_008088d0(0x80000013,iVar3 - param_1[4]);
        FUN_00808820(&local_8);
        return (undefined4 *)0x0;
      }
      param_1[5] = iVar1;
      param_1[4] = iVar3;
    }
    puVar4 = (undefined4 *)(param_1[5] + param_1[3]);
    for (uVar2 = param_3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *puVar4 = *param_2;
      param_2 = param_2 + 1;
      puVar4 = puVar4 + 1;
    }
    for (uVar2 = param_3 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined1 *)puVar4 = *(undefined1 *)param_2;
      param_2 = (undefined4 *)((int)param_2 + 1);
      puVar4 = (undefined4 *)((int)puVar4 + 1);
    }
    param_1[3] = param_1[3] + param_3;
    return param_1;
  case 4:
    iVar1 = (*(code *)param_1[5])(param_1[7],param_2,param_3);
    return (undefined4 *)(-(uint)(iVar1 != 0) & (uint)param_1);
  default:
    local_8 = 1;
    local_4 = FUN_008088d0(0xe);
  }
  FUN_00808820(&local_8);
  return (undefined4 *)0x0;
}



/* entry 0x007ECEF0; bounded CFG instructions=157; body bytes=481 */

undefined4 * FUN_007ecef0(undefined4 param_1,int param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  puVar1 = (undefined4 *)
           (**(code **)(DAT_00c97b24 + 0x144))(*(undefined4 *)(DAT_00c9792c + DAT_00c97b24),0x30404)
  ;
  if (puVar1 == (undefined4 *)0x0) goto LAB_007ed008;
  *puVar1 = param_1;
  puVar1[1] = param_2;
  puVar1[8] = 1;
  puVar3 = puVar1;
  switch(param_1) {
  case 1:
    iVar2 = (**(code **)(DAT_00c97b24 + 0xec))(param_3);
    if (iVar2 == -1) goto LAB_007ed008;
    puVar1[3] = param_3;
    break;
  case 2:
    if (param_2 == 1) {
      iVar2 = (**(code **)(DAT_00c97b24 + 200))(param_3,&DAT_008e2220);
LAB_007ecff2:
      if (iVar2 != 0) {
        puVar1[3] = iVar2;
        break;
      }
    }
    else {
      if (param_2 == 2) {
        iVar2 = (**(code **)(DAT_00c97b24 + 200))(param_3,&DAT_008e2224);
        goto LAB_007ecff2;
      }
      if (param_2 == 3) {
        iVar2 = (**(code **)(DAT_00c97b24 + 200))(param_3,&DAT_008e2228);
        goto LAB_007ecff2;
      }
      uStack_20 = 1;
      uStack_1c = FUN_008088d0(0xd);
      FUN_00808820(&uStack_20);
    }
    uStack_18 = 1;
    uStack_14 = FUN_008088d0(0x80000002,param_3);
    FUN_00808820(&uStack_18);
    puVar3 = (undefined4 *)0x0;
    break;
  case 3:
    if (param_2 == 1) {
      puVar1[3] = 0;
      puVar1[4] = param_3[1];
      puVar1[5] = *param_3;
    }
    else if (param_2 == 2) {
      puVar1[3] = 0;
      puVar1[4] = 0;
      puVar1[5] = 0;
    }
    else if (param_2 == 3) {
      puVar1[3] = param_3[1];
      puVar1[4] = param_3[1];
      puVar1[5] = *param_3;
    }
    else {
      uStack_10 = 1;
      uStack_c = FUN_008088d0(0xd);
      FUN_00808820(&uStack_10);
      puVar3 = (undefined4 *)0x0;
    }
    break;
  case 4:
    puVar4 = puVar1 + 3;
    for (iVar2 = 5; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *param_3;
      param_3 = param_3 + 1;
      puVar4 = puVar4 + 1;
    }
    break;
  default:
    uStack_8 = 1;
    uStack_4 = FUN_008088d0(0xe);
    FUN_00808820(&uStack_8);
    goto LAB_007ed008;
  }
  if (puVar3 != (undefined4 *)0x0) {
    return puVar1;
  }
LAB_007ed008:
  (**(code **)(DAT_00c97b24 + 0x148))(*(undefined4 *)(DAT_00c9792c + DAT_00c97b24),puVar1);
  return (undefined4 *)0x0;
}



/* entry 0x007EF520; bounded CFG instructions=18; body bytes=47 */

undefined4 FUN_007ef520(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (*(int *)(DAT_00c9c078 + 0x3c + DAT_00c97b24) == 0) {
    return 0;
  }
  puVar2 = (undefined4 *)(DAT_00c9c078 + 0x38 + DAT_00c97b24);
  for (iVar1 = 0xf; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return 1;
}



/* entry 0x007F0050; bounded CFG instructions=111; body bytes=334 */

undefined1 * FUN_007f0050(undefined1 *param_1,undefined1 *param_2)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  puVar2 = (undefined1 *)
           (**(code **)(DAT_00c97b24 + 0x144))(*(undefined4 *)(DAT_00c9796c + DAT_00c97b24),0x3000e)
  ;
  if (puVar2 == (undefined1 *)0x0) {
    return (undefined1 *)0x0;
  }
  if (param_2 == (undefined1 *)0x0) {
    param_2 = puVar2;
  }
  *puVar2 = *param_1;
  puVar2[1] = param_1[1];
  puVar2[2] = param_1[2];
  puVar1 = puVar2 + 0x90;
  puVar2[3] = param_1[3];
  *(undefined1 **)(puVar2 + 0x94) = puVar1;
  *(undefined1 **)puVar1 = puVar1;
  *(undefined4 *)(puVar2 + 4) = 0;
  puVar5 = (undefined4 *)(param_1 + 0x10);
  puVar6 = (undefined4 *)(puVar2 + 0x10);
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  *(undefined4 *)(puVar2 + 0x98) = 0;
  *(undefined4 *)(puVar2 + 0x9c) = 0;
  *(undefined1 **)(puVar2 + 0xa0) = param_2;
  iVar4 = *(int *)(param_1 + 0x98);
  *(undefined1 **)(param_1 + 0xa0) = puVar2;
  while( true ) {
    if (iVar4 == 0) {
      FUN_008086e0(&DAT_008e2270,puVar2);
      FUN_00808770(&DAT_008e2270,puVar2,param_1);
      return puVar2;
    }
    iVar3 = FUN_007f0050(iVar4,param_2);
    if (iVar3 == 0) break;
    *(undefined4 *)(iVar3 + 0x9c) = *(undefined4 *)(puVar2 + 0x98);
    *(int *)(puVar2 + 0x98) = iVar3;
    *(undefined1 **)(iVar3 + 4) = puVar2;
    iVar4 = *(int *)(iVar4 + 0x9c);
  }
  iVar4 = *(int *)(puVar2 + 0x98);
  while (iVar4 != 0) {
    iVar3 = *(int *)(iVar4 + 0x9c);
    FUN_007f0830(iVar4);
    iVar4 = iVar3;
  }
  FUN_00808740(&DAT_008e2270,puVar2);
  if ((puVar2[3] & 3) != 0) {
    **(undefined4 **)(puVar2 + 0xc) = *(undefined4 *)(puVar2 + 8);
    *(undefined4 *)(*(int *)(puVar2 + 8) + 4) = *(undefined4 *)(puVar2 + 0xc);
  }
  (**(code **)(DAT_00c97b24 + 0x148))(*(undefined4 *)(DAT_00c9796c + DAT_00c97b24),puVar2);
  return (undefined1 *)0x0;
}



/* entry 0x007F18B0; bounded CFG instructions=49; body bytes=111 */

undefined4 * FUN_007f18b0(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  
  uVar1 = param_2[3];
  uVar2 = param_3[3];
  uVar3 = *(uint *)(DAT_00c979bc + 4 + DAT_00c97b24) & 0x20000;
  if ((uVar1 & uVar3) != 0) {
    puVar5 = param_1;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *param_3;
      param_3 = param_3 + 1;
      puVar5 = puVar5 + 1;
    }
    return param_1;
  }
  if ((uVar2 & uVar3) != 0) {
    puVar5 = param_1;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *param_2;
      param_2 = param_2 + 1;
      puVar5 = puVar5 + 1;
    }
    return param_1;
  }
  (**(code **)(DAT_00c979bc + 8 + DAT_00c97b24))(param_1,param_2,param_3);
  param_1[3] = uVar2 & uVar1;
  return param_1;
}



/* entry 0x007F1D00; bounded CFG instructions=160; body bytes=717 */

/* WARNING: Removing unreachable block (ram,0x007f1eda) */
/* WARNING: Removing unreachable block (ram,0x007f1ee7) */
/* WARNING: Removing unreachable block (ram,0x007f1ee9) */
/* WARNING: Removing unreachable block (ram,0x007f1ef4) */
/* WARNING: Removing unreachable block (ram,0x007f1ef6) */
/* WARNING: Removing unreachable block (ram,0x007f1f2b) */
/* WARNING: Removing unreachable block (ram,0x007f1f38) */
/* WARNING: Removing unreachable block (ram,0x007f1f3a) */
/* WARNING: Removing unreachable block (ram,0x007f1f45) */
/* WARNING: Removing unreachable block (ram,0x007f1f47) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float * FUN_007f1d00(float *param_1,float *param_2,float param_3,float param_4,int param_5)

{
  int iVar1;
  float *pfVar2;
  float fVar3;
  float *pfVar4;
  float local_a4;
  float local_a0;
  float local_98;
  float local_90;
  float local_8c;
  float local_84;
  float local_80 [5];
  float local_6c;
  float local_68;
  float local_60;
  float local_5c;
  float local_58;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  float local_40 [3];
  uint uStack_34;
  
  local_84 = _DAT_00858624 - param_2[2] * param_2[2];
  local_8c = (_DAT_00858624 - *param_2 * *param_2) * param_3;
  local_90 = param_2[1] * *param_2;
  local_98 = param_2[1] * param_2[2] * param_3;
  fVar3 = param_2[2] * *param_2 * param_3;
  local_a4 = param_4 * *param_2;
  local_a0 = param_2[1] * param_4;
  local_80[0] = _DAT_00858624 - local_8c;
  local_80[1] = param_2[2] * param_4 + local_90 * param_3;
  local_50 = 0;
  local_4c = 0;
  local_80[2] = fVar3 - local_a0;
  local_48 = 0;
  local_80[3] = 4.2039e-45;
  local_80[4] = local_90 * param_3 - param_2[2] * param_4;
  local_6c = _DAT_00858624 - (_DAT_00858624 - param_2[1] * param_2[1]) * param_3;
  local_68 = local_a4 + local_98;
  local_60 = local_a0 + fVar3;
  local_5c = local_98 - local_a4;
  local_58 = _DAT_00858624 - local_84 * param_3;
  if (param_5 == 0) {
    pfVar2 = local_80;
    pfVar4 = param_1;
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *pfVar4 = *pfVar2;
      pfVar2 = pfVar2 + 1;
      pfVar4 = pfVar4 + 1;
    }
    return param_1;
  }
  if (param_5 == 1) {
    fVar3 = param_1[3];
    if (((uint)fVar3 & *(uint *)(DAT_00c979bc + 4 + DAT_00c97b24) & 0x20000) != 0) {
      pfVar2 = local_80;
      pfVar4 = local_40;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *pfVar4 = *pfVar2;
        pfVar2 = pfVar2 + 1;
        pfVar4 = pfVar4 + 1;
      }
      pfVar2 = local_40;
      pfVar4 = param_1;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *pfVar4 = *pfVar2;
        pfVar2 = pfVar2 + 1;
        pfVar4 = pfVar4 + 1;
      }
      return param_1;
    }
    pfVar2 = local_80;
    pfVar4 = param_1;
  }
  else {
    if (param_5 != 2) {
      local_a4 = 1.4013e-45;
      local_a0 = (float)FUN_008088d0(0x80000003,s_Invalid_combination_type_008e21fc);
      FUN_00808820(&local_a4);
      return (float *)0x0;
    }
    fVar3 = param_1[3];
    if (((uint)fVar3 & *(uint *)(DAT_00c979bc + 4 + DAT_00c97b24) & 0x20000) != 0) {
      pfVar2 = local_80;
      pfVar4 = local_40;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *pfVar4 = *pfVar2;
        pfVar2 = pfVar2 + 1;
        pfVar4 = pfVar4 + 1;
      }
      pfVar2 = local_40;
      pfVar4 = param_1;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *pfVar4 = *pfVar2;
        pfVar2 = pfVar2 + 1;
        pfVar4 = pfVar4 + 1;
      }
      return param_1;
    }
    pfVar2 = param_1;
    pfVar4 = local_80;
  }
  (**(code **)(DAT_00c979bc + 8 + DAT_00c97b24))(local_40,pfVar2,pfVar4);
  uStack_34 = (uint)fVar3 & 3;
  pfVar2 = local_40;
  pfVar4 = param_1;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pfVar4 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar4 = pfVar4 + 1;
  }
  return param_1;
}



/* entry 0x007F2070; bounded CFG instructions=80; body bytes=225 */

float * FUN_007f2070(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  float *pfVar8;
  
  if ((*(uint *)(DAT_00c979bc + 4 + DAT_00c97b24) & (uint)param_2[3] & 0x20000) != 0) {
    pfVar8 = param_1;
    for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
      *pfVar8 = *param_2;
      param_2 = param_2 + 1;
      pfVar8 = pfVar8 + 1;
    }
    return param_1;
  }
  if ((SUB41(param_2[3],0) & 3) == 3) {
    *param_1 = *param_2;
    param_1[1] = param_2[4];
    param_1[2] = param_2[8];
    param_1[4] = param_2[1];
    param_1[5] = param_2[5];
    param_1[6] = param_2[9];
    param_1[8] = param_2[2];
    param_1[9] = param_2[6];
    param_1[10] = param_2[10];
    param_1[0xc] = -(param_2[2] * param_2[0xe] + param_2[0xc] * *param_2 + param_2[0xd] * param_2[1]
                    );
    param_1[0xd] = -(param_2[0xe] * param_2[6] +
                    param_2[0xd] * param_2[5] + param_2[0xc] * param_2[4]);
    fVar1 = param_2[8];
    fVar2 = param_2[0xc];
    fVar3 = param_2[0xd];
    fVar4 = param_2[9];
    fVar5 = param_2[10];
    fVar6 = param_2[0xe];
    param_1[3] = 4.2039e-45;
    param_1[0xe] = -(fVar5 * fVar6 + fVar3 * fVar4 + fVar1 * fVar2);
    return param_1;
  }
  FUN_007f2160(param_1,param_2);
  return param_1;
}



/* entry 0x007F25A0; bounded CFG instructions=143; body bytes=378 */

uint * FUN_007f25a0(uint *param_1,uint *param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint *puVar4;
  uint *puVar5;
  uint uVar6;
  undefined4 local_48;
  undefined4 local_44;
  uint local_40 [16];
  
  if (param_3 == 0) {
    puVar4 = param_1;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *param_2;
      param_2 = param_2 + 1;
      puVar4 = puVar4 + 1;
    }
    return param_1;
  }
  if (param_3 == 1) {
    uVar3 = param_2[3];
    uVar6 = param_1[3];
    uVar1 = *(uint *)(DAT_00c979bc + 4 + DAT_00c97b24) & 0x20000;
    if ((uVar3 & uVar1) != 0) {
      puVar4 = param_1;
      puVar5 = local_40;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      puVar4 = local_40;
      puVar5 = param_1;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      return param_1;
    }
    puVar4 = param_2;
    puVar5 = param_1;
    if ((uVar6 & uVar1) != 0) {
      puVar4 = local_40;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = *param_2;
        param_2 = param_2 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar4 = local_40;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      return param_1;
    }
  }
  else {
    if (param_3 != 2) {
      local_48 = 1;
      local_44 = FUN_008088d0(0x80000003,s_Invalid_combination_type_008e21fc);
      FUN_00808820(&local_48);
      return (uint *)0x0;
    }
    uVar3 = param_1[3];
    uVar6 = param_2[3];
    uVar1 = *(uint *)(DAT_00c979bc + 4 + DAT_00c97b24) & 0x20000;
    if ((uVar3 & uVar1) != 0) {
      puVar4 = local_40;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = *param_2;
        param_2 = param_2 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar4 = local_40;
      puVar5 = param_1;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      return param_1;
    }
    puVar4 = param_1;
    puVar5 = param_2;
    if ((uVar6 & uVar1) != 0) {
      puVar5 = local_40;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      puVar4 = local_40;
      puVar5 = param_1;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      return param_1;
    }
  }
  (**(code **)(DAT_00c979bc + 8 + DAT_00c97b24))(local_40,puVar4,puVar5);
  local_40[3] = uVar6 & uVar3;
  puVar4 = local_40;
  puVar5 = param_1;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar5 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
  }
  return param_1;
}



/* entry 0x007F2F00; bounded CFG instructions=34; body bytes=102 */

int FUN_007f2f00(void)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  iVar2 = FUN_007f2ab0(DAT_00c97b24 + 4,1,0,0,0);
  puVar1 = DAT_00c97b24;
  if (iVar2 != 0) {
    DAT_00c97b24 = &DAT_00c979c8;
    puVar4 = puVar1;
    puVar5 = &DAT_00c979c8;
    for (iVar3 = 0x56; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    (*DAT_00c97b00)(puVar1);
    DAT_00c97b20 = DAT_00c97b20 + -1;
    DAT_00c97b24[0x54] = 1;
  }
  return iVar2;
}



/* entry 0x007F2F70; bounded CFG instructions=149; body bytes=447 */

undefined4 FUN_007f2f70(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 local_8;
  undefined4 local_4;
  
  if (DAT_00c97b24 == (undefined4 *)0x0) {
    DAT_00c97b24 = &DAT_00c979c8;
  }
  if (DAT_00c97b24[0x54] == 1) {
    if (param_1 == 0) {
      local_8 = 1;
      local_4 = FUN_008088d0(0x80000016);
      FUN_00808820(&local_8);
      return 0;
    }
    iVar1 = FUN_007f9c20();
    if (iVar1 != 0) {
      puVar2 = (undefined4 *)(*(code *)DAT_00c97b24[0x4d])(DAT_008e2298,0x40000);
      if (puVar2 == (undefined4 *)0x0) {
        DAT_00c97b24 = &DAT_00c979c8;
        local_8 = 1;
        local_4 = FUN_008088d0(0x80000013,DAT_008e2298);
        FUN_00808820(&local_8);
        return 0;
      }
      puVar4 = &DAT_00c979c8;
      puVar5 = puVar2;
      DAT_00c97b24 = puVar2;
      for (iVar3 = 0x56; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      FUN_007f2ab0(iVar1,4,DAT_00c97b24 + 4,DAT_00c97b24 + 0x4d,0);
      iVar3 = FUN_007f2ab0(iVar1,0,0,param_1,0);
      if (iVar3 != 0) {
        FUN_007f2ab0(iVar1,0xb,DAT_00c97b24 + 0x12,0,0x1d);
        DAT_00c97b20 = DAT_00c97b20 + 1;
        DAT_00c97b24[0x54] = 2;
        return 1;
      }
      DAT_00c97b24 = &DAT_00c979c8;
      puVar4 = puVar2;
      puVar5 = &DAT_00c979c8;
      for (iVar1 = 0x56; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      (*DAT_00c97b00)(puVar2);
      return 0;
    }
  }
  else {
    local_8 = 1;
    local_4 = FUN_008088d0(0x80000001);
    FUN_00808820(&local_8);
  }
  return 0;
}



/* entry 0x007F38A0; bounded CFG instructions=36; body bytes=110 */

int FUN_007f38a0(int param_1,int param_2)

{
  uint uVar1;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  (**(code **)(DAT_00c97b24 + 0xfc))(param_1 + 0x10,param_2,0x20);
  uVar1 = (**(code **)(DAT_00c97b24 + 0x120))(param_2);
  if (0x1f < uVar1) {
    uStack_8 = 1;
    uStack_4 = FUN_008088d0(0x8000001e,param_2,0x20,0x1f,(int)*(char *)(param_2 + 0x1f));
    FUN_00808820(&uStack_8);
    *(undefined1 *)(param_1 + 0x2f) = 0;
  }
  return param_1;
}



/* entry 0x007F3910; bounded CFG instructions=36; body bytes=110 */

int FUN_007f3910(int param_1,int param_2)

{
  uint uVar1;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  (**(code **)(DAT_00c97b24 + 0xfc))(param_1 + 0x30,param_2,0x20);
  uVar1 = (**(code **)(DAT_00c97b24 + 0x120))(param_2);
  if (0x1f < uVar1) {
    uStack_8 = 1;
    uStack_4 = FUN_008088d0(0x8000001e,param_2,0x20,0x1f,(int)*(char *)(param_2 + 0x1f));
    FUN_00808820(&uStack_8);
    *(undefined1 *)(param_1 + 0x4f) = 0;
  }
  return param_1;
}



/* entry 0x007F4690; bounded CFG instructions=160; body bytes=1092 */

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

int FUN_007f4690(int param_1,char *param_2,undefined4 param_3,int *param_4,int *param_5,
                undefined4 param_6,undefined4 param_7)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 uStack_4610;
  undefined4 uStack_460c;
  undefined1 auStack_4608 [255];
  undefined1 uStack_4509;
  undefined1 local_4508 [255];
  undefined1 uStack_4409;
  undefined4 auStack_4408 [256];
  undefined1 auStack_4008 [16388];
  undefined4 uStack_4;
  
  uStack_4 = 0x7f469a;
  (**(code **)(DAT_00c97b24 + 0xfc))(local_4508,param_1,0x100);
  uVar1 = (**(code **)(DAT_00c97b24 + 0x120))(param_1);
  if (0xff < uVar1) {
    uStack_4610 = 1;
    uStack_460c = FUN_008088d0(0x8000001e,param_1,0x100,0xff,(int)*(char *)(param_1 + 0xff));
    FUN_00808820(&uStack_4610);
    uStack_4409 = 0;
  }
  iVar2 = FUN_00803310(param_1);
  if (iVar2 != 0) {
    (**(code **)(DAT_00c97b24 + 0x100))(local_4508,iVar2);
  }
  auStack_4608[0] = 0;
  if ((param_2 != (char *)0x0) && (*param_2 != '\0')) {
    (**(code **)(DAT_00c97b24 + 0xfc))(auStack_4608,param_2,0x100);
    uVar1 = (**(code **)(DAT_00c97b24 + 0x120))(param_2);
    if (0xff < uVar1) {
      uStack_4610 = 1;
      uStack_460c = FUN_008088d0(0x8000001e,param_2,0x100,0xff,(int)param_2[0xff]);
      FUN_00808820(&uStack_4610);
      uStack_4509 = 0;
    }
    iVar2 = FUN_00803310(param_2);
    if (iVar2 != 0) {
      (**(code **)(DAT_00c97b24 + 0x100))(auStack_4608,iVar2);
    }
  }
  iVar2 = FUN_008035c0(local_4508,auStack_4608);
  if (iVar2 == 0) {
    return 0;
  }
  if (((*param_4 == 0) || (*param_5 == 0)) &&
     (iVar3 = FUN_008042c0(iVar2,param_3,param_4,param_5,param_6,param_7), iVar3 == 0)) {
    FUN_00802740(iVar2);
    uStack_4610 = 1;
    uStack_460c = FUN_008088d0(0x80000009);
    FUN_00808820(&uStack_4610);
    return 0;
  }
  if ((*(int *)(iVar2 + 4) == *param_4) && (*(int *)(iVar2 + 8) == *param_5)) {
    return iVar2;
  }
  iVar3 = *(int *)(iVar2 + 0xc);
  iVar4 = iVar2;
  if (iVar3 != 0x20) {
    iVar4 = FUN_008026e0(*(int *)(iVar2 + 4),*(undefined4 *)(iVar2 + 8),0x20);
    if (iVar4 == 0) {
      FUN_00802740(iVar2);
      return 0;
    }
    iVar5 = FUN_008027a0(iVar4);
    if (iVar5 == 0) {
      FUN_00802740(iVar4);
      FUN_00802740(iVar2);
      return 0;
    }
    FUN_00803950(iVar4,iVar2);
    FUN_00802740(iVar2);
  }
  iVar2 = FUN_008026e0(*param_4,*param_5,0x20);
  if (iVar2 == 0) {
    FUN_00802740(iVar4);
    return 0;
  }
  iVar5 = FUN_008027a0(iVar2);
  if (iVar5 != 0) {
    FUN_0080c600(iVar2,iVar4);
    FUN_00802740(iVar4);
    if (iVar3 == 4) {
      iVar3 = FUN_0080c470(auStack_4008);
      if (iVar3 == 0) {
        return iVar2;
      }
      FUN_0080aa80(auStack_4008,iVar2,0x3f800000);
      FUN_0080af60(auStack_4408,0x10,auStack_4008);
      iVar3 = FUN_008026e0(*(undefined4 *)(iVar2 + 4),*(undefined4 *)(iVar2 + 8),4);
      if (iVar3 == 0) {
        return iVar2;
      }
      FUN_008027a0(iVar3);
      FUN_0080bf20(*(undefined4 *)(iVar3 + 0x14),*(undefined4 *)(iVar3 + 0x10),
                   *(undefined4 *)(iVar3 + 0xc),0,auStack_4008,iVar2);
      puVar6 = auStack_4408;
      puVar7 = *(undefined4 **)(iVar3 + 0x18);
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar7 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar7 = puVar7 + 1;
      }
      FUN_00802740(iVar2);
    }
    else {
      if (iVar3 != 8) {
        return iVar2;
      }
      iVar3 = FUN_0080c470(auStack_4008);
      if (iVar3 == 0) {
        return iVar2;
      }
      FUN_0080aa80(auStack_4008,iVar2,0x3f800000);
      FUN_0080af60(auStack_4408,0x100,auStack_4008);
      iVar3 = FUN_008026e0(*(undefined4 *)(iVar2 + 4),*(undefined4 *)(iVar2 + 8),8);
      if (iVar3 == 0) {
        return iVar2;
      }
      FUN_008027a0(iVar3);
      FUN_0080bf20(*(undefined4 *)(iVar3 + 0x14),*(undefined4 *)(iVar3 + 0x10),
                   *(undefined4 *)(iVar3 + 0xc),0,auStack_4008,iVar2);
      puVar6 = auStack_4408;
      puVar7 = *(undefined4 **)(iVar3 + 0x18);
      for (iVar4 = 0x100; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar7 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar7 = puVar7 + 1;
      }
      FUN_00802740(iVar2);
    }
    FUN_0080c520(auStack_4008);
    return iVar3;
  }
  FUN_00802740(iVar2);
  FUN_00802740(iVar4);
  return 0;
}



/* entry 0x007F4AE0; bounded CFG instructions=160; body bytes=1631 */

int * FUN_007f4ae0(int param_1,char *param_2)

{
  code *pcVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  undefined4 uVar8;
  int iStack_668;
  undefined4 uStack_664;
  undefined4 uStack_660;
  undefined4 uStack_65c;
  undefined4 uStack_658;
  uint uStack_654;
  undefined4 uStack_650;
  undefined4 uStack_64c;
  undefined4 uStack_648;
  undefined4 uStack_644;
  int aiStack_640 [16];
  undefined1 auStack_600 [255];
  undefined1 uStack_501;
  undefined1 local_500 [255];
  undefined1 uStack_401;
  undefined1 auStack_400 [1024];
  
  (**(code **)(DAT_00c97b24 + 0xfc))(local_500,param_1,0x100);
  uVar2 = (**(code **)(DAT_00c97b24 + 0x120))(param_1);
  if (0xff < uVar2) {
    iStack_668 = 1;
    uStack_664 = FUN_008088d0(0x8000001e,param_1,0x100,0xff,(int)*(char *)(param_1 + 0xff));
    FUN_00808820(&iStack_668);
    uStack_401 = 0;
  }
  auStack_600[0] = 0;
  if ((param_2 != (char *)0x0) && (*param_2 != '\0')) {
    (**(code **)(DAT_00c97b24 + 0xfc))(auStack_600,param_2,0x100);
    uVar2 = (**(code **)(DAT_00c97b24 + 0x120))(param_2);
    if (0xff < uVar2) {
      iStack_668 = 1;
      uStack_664 = FUN_008088d0(0x8000001e,param_2,0x100,0xff,(int)param_2[0xff]);
      FUN_00808820(&iStack_668);
      uStack_501 = 0;
    }
  }
  uVar8 = 4;
  if ((*(int *)(DAT_00c97b4c + 0x1c + DAT_00c97b24) != 0) &&
     (uVar8 = 0x8004, *(int *)(DAT_00c97b4c + 0x20 + DAT_00c97b24) != 0)) {
    uVar8 = 0x9004;
  }
  pcVar1 = *(code **)(DAT_00c97b4c + 0x30 + DAT_00c97b24);
  if (pcVar1 != (code *)0x0) {
    (*pcVar1)(local_500,auStack_600,0,uVar8);
  }
  uStack_650 = 0;
  uStack_658 = 0;
  iVar3 = FUN_007f4690(local_500,auStack_600,uVar8,&uStack_650,&uStack_658,&uStack_64c,&uStack_654);
  if (iVar3 == 0) {
    return (int *)0x0;
  }
  aiStack_640[0] = iVar3;
  iVar4 = FUN_007fb230(uStack_650,uStack_658,uStack_64c,uStack_654);
  if (iVar4 == 0) {
    FUN_00802740(iVar3);
    return (int *)0x0;
  }
  if ((char)(uStack_654 >> 8) < '\0') {
    if ((uStack_654 & 0x1000) != 0) {
      iVar5 = FUN_00804290(iVar4,iVar3);
      goto LAB_007f4fa0;
    }
    iStack_668 = FUN_007fb160(iVar4);
    iVar3 = 1;
    if (1 < iStack_668) {
      do {
        (**(code **)(DAT_00c97b24 + 0xfc))(local_500,param_1,0x100);
        uVar2 = (**(code **)(DAT_00c97b24 + 0x120))(param_1);
        if (0xff < uVar2) {
          uStack_648 = 1;
          uStack_644 = FUN_008088d0(0x8000001e,param_1,0x100,0xff,(int)*(char *)(param_1 + 0xff));
          FUN_00808820(&uStack_648);
          uStack_401 = 0;
        }
        auStack_600[0] = 0;
        if ((param_2 != (char *)0x0) && (*param_2 != '\0')) {
          (**(code **)(DAT_00c97b24 + 0xfc))(auStack_600,param_2,0x100);
          uVar2 = (**(code **)(DAT_00c97b24 + 0x120))(param_2);
          if (0xff < uVar2) {
            uStack_660 = 1;
            uStack_65c = FUN_008088d0(0x8000001e,param_2,0x100,0xff,(int)param_2[0xff]);
            FUN_00808820(&uStack_660);
            uStack_501 = 0;
          }
        }
        pcVar1 = *(code **)(DAT_00c97b4c + 0x30 + DAT_00c97b24);
        if (pcVar1 != (code *)0x0) {
          (*pcVar1)(local_500,auStack_600,iVar3,uVar8);
        }
        FUN_007fb2d0(iVar4,iVar3,5);
        uStack_650 = *(undefined4 *)(iVar4 + 0xc);
        uStack_658 = *(undefined4 *)(iVar4 + 0x10);
        uStack_64c = *(undefined4 *)(iVar4 + 0x14);
        uStack_654 = (uint)CONCAT11(*(undefined1 *)(iVar4 + 0x23),*(undefined1 *)(iVar4 + 0x20));
        FUN_007faec0(iVar4);
        iVar5 = FUN_007f4690(local_500,auStack_600,uVar8,&uStack_650,&uStack_658,&uStack_64c,
                             &uStack_654);
        aiStack_640[iVar3] = iVar5;
        if (iVar5 == 0) {
          while (iVar3 = iVar3 + -1, -1 < iVar3) {
            FUN_00802740(aiStack_640[iVar3]);
          }
          FUN_007fb020(iVar4);
          return (int *)0x0;
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 < iStack_668);
    }
    if ((*(byte *)(iVar4 + 0x23) & 0x60) == 0) {
      iVar3 = 0;
      if (0 < iStack_668) {
        do {
          FUN_00803e30(aiStack_640[iVar3]);
          iVar3 = iVar3 + 1;
        } while (iVar3 < iStack_668);
      }
    }
    else {
      if ((*(byte *)(iVar4 + 0x23) & 0x40) == 0) {
        uVar8 = 8;
      }
      else {
        uVar8 = 4;
      }
      FUN_007f44c0(auStack_400,0,aiStack_640,iStack_668,uVar8);
      FUN_00803e30(aiStack_640[0]);
    }
    iVar3 = 0;
    if (0 < iStack_668) {
      do {
        iVar5 = FUN_007fb2d0(iVar4,iVar3,5);
        if (iVar5 != 0) {
          iVar6 = FUN_00804290(iVar4,aiStack_640[iVar3]);
          iVar5 = iStack_668;
          if (iVar6 == 0) goto joined_r0x007f4f66;
          FUN_007faec0(iVar4);
        }
        FUN_00802740(aiStack_640[iVar3]);
        iVar3 = iVar3 + 1;
      } while (iVar3 < iStack_668);
    }
  }
  else {
    FUN_00803e30(iVar3);
    iVar5 = FUN_00804290(iVar4,iVar3);
LAB_007f4fa0:
    if (iVar5 == 0) {
      FUN_007fb020(iVar4);
      FUN_00802740(iVar3);
      return (int *)0x0;
    }
    FUN_00802740(iVar3);
  }
  piVar7 = (int *)(**(code **)(DAT_00c97b24 + 0x144))
                            (*(undefined4 *)(DAT_00c97b4c + 8 + DAT_00c97b24),0x30006);
  if (piVar7 != (int *)0x0) {
    piVar7[0x14] = 0;
    *(undefined1 *)((int)piVar7 + 0x51) = 0x11;
    piVar7[1] = 0;
    *(undefined1 *)(piVar7 + 4) = 0;
    *(undefined1 *)(piVar7 + 0xc) = 0;
    *piVar7 = iVar4;
    piVar7[0x15] = 1;
    *(undefined1 *)(piVar7 + 0x14) = 1;
    FUN_008086e0(&DAT_008e23cc,piVar7);
    (**(code **)(DAT_00c97b24 + 0xfc))(piVar7 + 4,param_1,0x20);
    uVar2 = (**(code **)(DAT_00c97b24 + 0x120))(param_1);
    if (0x1f < uVar2) {
      uStack_660 = 1;
      uStack_65c = FUN_008088d0(0x8000001e,param_1,0x20,0x1f,(int)*(char *)(param_1 + 0x1f));
      FUN_00808820(&uStack_660);
      *(undefined1 *)((int)piVar7 + 0x2f) = 0;
    }
    if (param_2 == (char *)0x0) {
      (**(code **)(DAT_00c97b24 + 0xfc))(piVar7 + 0xc,&DAT_00c97904,0x20);
      uVar2 = (**(code **)(DAT_00c97b24 + 0x120))(&DAT_00c97904);
      if (uVar2 < 0x20) {
        return piVar7;
      }
      uStack_660 = 1;
      uStack_65c = FUN_008088d0(0x8000001e,&DAT_00c97904,0x20,0x1f,(int)DAT_00c97923);
    }
    else {
      (**(code **)(DAT_00c97b24 + 0xfc))(piVar7 + 0xc,param_2);
      uVar2 = (**(code **)(DAT_00c97b24 + 0x120))(param_2);
      if (uVar2 < 0x20) {
        return piVar7;
      }
      uStack_660 = 1;
      uStack_65c = FUN_008088d0(0x8000001e,param_2,0x20,0x1f,(int)param_2[0x1f]);
    }
    FUN_00808820(&uStack_660);
    *(undefined1 *)((int)piVar7 + 0x4f) = 0;
    return piVar7;
  }
LAB_007f4f7a:
  FUN_007fb020(iVar4);
  return (int *)0x0;
joined_r0x007f4f66:
  for (; iVar3 < iVar5; iVar3 = iVar3 + 1) {
    FUN_00802740(aiStack_640[iVar3]);
  }
  goto LAB_007f4f7a;
}



/* entry 0x007F6B40; bounded CFG instructions=50; body bytes=169 */

void FUN_007f6b40(void)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  DAT_00c97c68 = 0;
  if (DAT_00c98080 == 0) {
    DAT_00c98080 = FUN_00801980(0x40,0xf,0x10,0x30411);
    puVar3 = &DAT_00c97c70;
    for (iVar1 = 0x104; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
  }
  else {
    uVar2 = 0;
    iVar1 = DAT_00c98080;
    do {
      if (*(int *)((int)&DAT_00c97c70 + uVar2) != 0) {
        (**(code **)(DAT_00c97b24 + 0x148))(iVar1,*(int *)((int)&DAT_00c97c70 + uVar2));
        iVar1 = DAT_00c98080;
        *(undefined4 *)((int)&DAT_00c97c70 + uVar2) = 0;
      }
      uVar2 = uVar2 + 4;
    } while (uVar2 < 0x410);
    FUN_00801e00(iVar1);
  }
  DAT_00c98070 = (undefined4 *)(**(code **)(DAT_00c97b24 + 0x144))(DAT_00c98080,0x30411);
  puVar3 = &DAT_008847a0;
  puVar4 = DAT_00c98070;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  return;
}



/* entry 0x007F7F70; bounded CFG instructions=147; body bytes=488 */

undefined4 FUN_007f7f70(void)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  DAT_008e2440 = 0xffffffff;
  DAT_008e2444 = 0xffffffff;
  DAT_008e2448 = 0xffffffff;
  DAT_008e244c = 0xffffffff;
  DAT_008e2450 = 0xffffffff;
  uVar2 = 0;
  do {
    *(undefined4 *)((int)&DAT_00c97bd8 + uVar2) = 0xffffffff;
    *(undefined4 *)((int)&DAT_00c97bdc + uVar2) = 0;
    *(undefined4 *)((int)&DAT_00c97be0 + uVar2) = 0;
    uVar2 = uVar2 + 0x10;
  } while (uVar2 < 0x40);
  DAT_00c97c68 = 0;
  if (DAT_00c98080 == 0) {
    DAT_00c98080 = FUN_00801980(0x40,0xf,0x10,0x30411);
    puVar4 = &DAT_00c97c70;
    for (iVar3 = 0x104; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
  }
  else {
    uVar2 = 0;
    iVar3 = DAT_00c98080;
    do {
      if (*(int *)((int)&DAT_00c97c70 + uVar2) != 0) {
        (**(code **)(DAT_00c97b24 + 0x148))(iVar3,*(int *)((int)&DAT_00c97c70 + uVar2));
        iVar3 = DAT_00c98080;
        *(undefined4 *)((int)&DAT_00c97c70 + uVar2) = 0;
      }
      uVar2 = uVar2 + 4;
    } while (uVar2 < 0x410);
    FUN_00801e00(iVar3);
  }
  DAT_00c98070 = (undefined4 *)(**(code **)(DAT_00c97b24 + 0x144))(DAT_00c98080,0x30411);
  puVar4 = &DAT_008847a0;
  puVar5 = DAT_00c98070;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
  }
  uVar2 = 0;
  do {
    (**(code **)(*DAT_00c97c28 + 0x104))(DAT_00c97c28,uVar2,0);
    uVar2 = uVar2 + 1;
  } while (uVar2 < 8);
  (**(code **)(*DAT_00c97c28 + 0x1a0))(DAT_00c97c28,0);
  uVar2 = 0;
  do {
    (**(code **)(*DAT_00c97c28 + 400))(DAT_00c97c28,uVar2,0,0,0);
    uVar2 = uVar2 + 1;
  } while (uVar2 < 4);
  (**(code **)(*DAT_00c97c28 + 0x1ac))(DAT_00c97c28,0);
  (**(code **)(*DAT_00c97c28 + 0x15c))(DAT_00c97c28,0);
  (**(code **)(*DAT_00c97c28 + 0x170))(DAT_00c97c28,0);
  if (DAT_00c98090 != DAT_00c97c30) {
    DAT_00c98090 = DAT_00c97c30;
    (**(code **)(*DAT_00c97c28 + 0x94))(DAT_00c97c28,0,DAT_00c97c30);
  }
  uVar2 = 1;
  do {
    piVar1 = DAT_00c97c28;
    if ((&DAT_00c98090)[uVar2] != 0) {
      (&DAT_00c98090)[uVar2] = 0;
      (**(code **)(*piVar1 + 0x94))(piVar1,uVar2,0);
    }
    uVar2 = uVar2 + 1;
  } while (uVar2 < 4);
  if (DAT_00c9808c != DAT_00c97c2c) {
    DAT_00c9808c = DAT_00c97c2c;
    (**(code **)(*DAT_00c97c28 + 0x9c))(DAT_00c97c28,DAT_00c97c2c);
  }
  FUN_007fb5f0();
  FUN_0080dfb0();
  FUN_007f5840();
  FUN_004cb640();
  FUN_00801f90();
  return 1;
}



/* entry 0x007F9D50; bounded CFG instructions=80; body bytes=300 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_007f9d50(void)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  uVar1 = 0;
  DAT_00c98090 = 0;
  DAT_00c98094 = 0;
  DAT_00c98098 = 0;
  DAT_00c9808c = 0;
  _DAT_00c9809c = 0;
  DAT_008e2440 = 0xffffffff;
  DAT_008e2444 = 0xffffffff;
  DAT_008e2448 = 0xffffffff;
  DAT_008e244c = 0xffffffff;
  DAT_008e2450 = 0xffffffff;
  do {
    *(undefined4 *)((int)&DAT_00c97bd8 + uVar1) = 0xffffffff;
    *(undefined4 *)((int)&DAT_00c97bdc + uVar1) = 0;
    *(undefined4 *)((int)&DAT_00c97be0 + uVar1) = 0;
    uVar1 = uVar1 + 0x10;
  } while (uVar1 < 0x40);
  DAT_00c97c68 = 0;
  if (DAT_00c98080 == 0) {
    DAT_00c98080 = FUN_00801980(0x40,0xf,0x10,0x30411);
    puVar3 = &DAT_00c97c70;
    for (iVar2 = 0x104; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
  }
  else {
    uVar1 = 0;
    iVar2 = DAT_00c98080;
    do {
      if (*(int *)((int)&DAT_00c97c70 + uVar1) != 0) {
        (**(code **)(DAT_00c97b24 + 0x148))(iVar2,*(int *)((int)&DAT_00c97c70 + uVar1));
        iVar2 = DAT_00c98080;
        *(undefined4 *)((int)&DAT_00c97c70 + uVar1) = 0;
      }
      uVar1 = uVar1 + 4;
    } while (uVar1 < 0x410);
    FUN_00801e00(iVar2);
  }
  DAT_00c98070 = (undefined4 *)(**(code **)(DAT_00c97b24 + 0x144))(DAT_00c98080,0x30411);
  puVar3 = &DAT_008847a0;
  puVar4 = DAT_00c98070;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  DAT_00c98084 = 0;
  if (DAT_00c98088 != 0) {
    (**(code **)(DAT_00c97b24 + 0x138))(DAT_00c98088);
    DAT_00c98088 = 0;
  }
  return DAT_00c97c28;
}



/* entry 0x007FA390; bounded CFG instructions=114; body bytes=344 */

bool FUN_007fa390(int param_1,int *param_2)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int *piVar6;
  undefined4 *puVar7;
  int local_8;
  
  iVar3 = (&DAT_00c97c70)[param_1];
  if (param_2 == (int *)0x0) {
    if (iVar3 == 0) {
LAB_007fa47c:
      uVar1 = (**(code **)(DAT_00c97b24 + 0x144))(DAT_00c98080,0x30411);
      (&DAT_00c97c70)[param_1] = uVar1;
    }
    else {
      piVar2 = &DAT_008847a0;
      iVar4 = 0x10;
      while (*(int *)(iVar3 + -0x8847a0 + (int)piVar2) == *piVar2) {
        piVar2 = piVar2 + 1;
        iVar4 = iVar4 + -1;
        if (iVar4 == 0) {
          return true;
        }
      }
      if (iVar3 == 0) goto LAB_007fa47c;
    }
    puVar5 = &DAT_008847a0;
    puVar7 = (undefined4 *)(&DAT_00c97c70)[param_1];
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar7 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar7 = puVar7 + 1;
    }
    iVar3 = (**(code **)(*DAT_00c97c28 + 0xb0))(DAT_00c97c28,param_1,&DAT_008847a0);
    if (param_1 == 0x100) {
      DAT_00c97c68 = 1;
    }
    goto LAB_007fa4d9;
  }
  if (iVar3 == 0) {
LAB_007fa3e1:
    uVar1 = (**(code **)(DAT_00c97b24 + 0x144))(DAT_00c98080,0x30411);
    (&DAT_00c97c70)[param_1] = uVar1;
  }
  else {
    local_8 = 0x10;
    piVar2 = param_2;
    while (*(int *)((iVar3 - (int)param_2) + (int)piVar2) == *piVar2) {
      piVar2 = piVar2 + 1;
      local_8 = local_8 + -1;
      if (local_8 == 0) {
        return true;
      }
    }
    if (iVar3 == 0) goto LAB_007fa3e1;
  }
  piVar2 = param_2;
  piVar6 = (int *)(&DAT_00c97c70)[param_1];
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar6 = *piVar2;
    piVar2 = piVar2 + 1;
    piVar6 = piVar6 + 1;
  }
  iVar3 = (**(code **)(*DAT_00c97c28 + 0xb0))(DAT_00c97c28,param_1,param_2);
  if (param_1 == 0x100) {
    DAT_00c97c68 = 0;
    return -1 < iVar3;
  }
LAB_007fa4d9:
  return -1 < iVar3;
}



/* entry 0x007FA660; bounded CFG instructions=84; body bytes=236 */

bool FUN_007fa660(int param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  iVar2 = DAT_00c98084;
  if (param_1 < DAT_00c98084) {
    iVar2 = FUN_007fa8b0(param_2,DAT_00c98088 + param_1 * 0x6c);
    if (iVar2 != 0) {
      return true;
    }
  }
  else {
    DAT_00c98084 = param_1 + 1;
    if (DAT_00c98088 == 0) {
      DAT_00c98088 = (**(code **)(DAT_00c97b24 + 0x134))(DAT_00c98084 * 0x6c,&DAT_01030411);
    }
    else {
      DAT_00c98088 = (**(code **)(DAT_00c97b24 + 0x13c))(DAT_00c98088,DAT_00c98084 * 0x6c);
    }
    if (iVar2 < DAT_00c98084) {
      iVar1 = iVar2 * 0x6c;
      do {
        iVar2 = iVar2 + 1;
        *(undefined4 *)(iVar1 + 0x68 + DAT_00c98088) = 0;
        iVar1 = iVar1 + 0x6c;
      } while (iVar2 < DAT_00c98084);
    }
  }
  puVar3 = param_2;
  puVar4 = (undefined4 *)(DAT_00c98088 + param_1 * 0x6c);
  for (iVar2 = 0x1a; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  iVar2 = (**(code **)(*DAT_00c97c28 + 0xcc))(DAT_00c97c28,param_1,param_2);
  return -1 < iVar2;
}



/* entry 0x007FAA30; bounded CFG instructions=160; body bytes=480 */

bool FUN_007faa30(int *param_1,int *param_2)

{
  char cVar1;
  int *piVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  
  iVar6 = 0;
  piVar5 = param_1 + 1;
  cVar1 = (char)param_1[1];
  while (cVar1 != '\x11') {
    piVar2 = piVar5 + 2;
    piVar5 = piVar5 + 2;
    iVar6 = iVar6 + 1;
    cVar1 = (char)*piVar2;
  }
  uVar7 = iVar6 + 1;
  uVar4 = 0;
  if (DAT_00c97c58 != 0) {
    piVar5 = (int *)(DAT_00c97c60 + 8);
    do {
      if (piVar5[-1] == uVar7) {
        iVar6 = (uVar7 & 0x1fffffff) << 1;
        if ((uVar7 & 0x1fffffff) == 0) {
LAB_007faa94:
          if (uVar4 < DAT_00c97c58) {
            iVar6 = uVar4 * 0xc;
            piVar5 = *(int **)(iVar6 + DAT_00c97c60);
            if (piVar5 == (int *)0x0) {
              (**(code **)(*DAT_00c97c28 + 0x158))
                        (DAT_00c97c28,*(undefined4 *)(iVar6 + DAT_00c97c60 + 8),iVar6 + DAT_00c97c60
                        );
            }
            else {
              (**(code **)(*piVar5 + 4))(piVar5);
            }
            iVar6 = *(int *)(iVar6 + DAT_00c97c60);
            *param_1 = iVar6;
            return iVar6 != 0;
          }
          break;
        }
        piVar2 = param_1;
        while (*(int *)((*piVar5 - (int)param_1) + (int)piVar2) == *piVar2) {
          piVar2 = piVar2 + 1;
          iVar6 = iVar6 + -1;
          if (iVar6 == 0) goto LAB_007faa94;
        }
      }
      uVar4 = uVar4 + 1;
      piVar5 = piVar5 + 3;
    } while (uVar4 < DAT_00c97c58);
  }
  if (DAT_00c97c5c <= DAT_00c97c58) {
    DAT_00c97c5c = DAT_00c97c5c + 0x10;
    if (DAT_00c97c60 == 0) {
      DAT_00c97c60 = (**(code **)(DAT_00c97b24 + 0x134))(DAT_00c97c5c * 0xc);
    }
    else {
      DAT_00c97c60 = (**(code **)(DAT_00c97b24 + 0x13c))
                               (DAT_00c97c60,DAT_00c97c5c * 0xc,&DAT_01040411);
    }
  }
  iVar6 = (**(code **)(*DAT_00c97c28 + 0x158))(DAT_00c97c28,param_1,param_2);
  if (-1 < iVar6) {
    *(int *)(DAT_00c97c60 + DAT_00c97c58 * 0xc) = *param_2;
    *(uint *)(DAT_00c97c60 + 4 + DAT_00c97c58 * 0xc) = uVar7;
    uVar3 = (**(code **)(DAT_00c97b24 + 0x134))(uVar7 * 8,0x40411);
    *(undefined4 *)(DAT_00c97c60 + 8 + DAT_00c97c58 * 0xc) = uVar3;
    piVar5 = *(int **)(DAT_00c97c60 + 8 + DAT_00c97c58 * 0xc);
    for (iVar6 = (uVar7 & 0x1fffffff) << 1; iVar6 != 0; iVar6 = iVar6 + -1) {
      *piVar5 = *param_1;
      param_1 = param_1 + 1;
      piVar5 = piVar5 + 1;
    }
    for (iVar6 = 0; iVar6 != 0; iVar6 = iVar6 + -1) {
      *(char *)piVar5 = (char)*param_1;
      param_1 = (int *)((int)param_1 + 1);
      piVar5 = (int *)((int)piVar5 + 1);
    }
    DAT_00c97c58 = DAT_00c97c58 + 1;
    return *param_2 != 0;
  }
  *param_2 = 0;
  return *param_2 != 0;
}



/* entry 0x008019B0; bounded CFG instructions=153; body bytes=433 */

uint * FUN_008019b0(int param_1,uint param_2,uint param_3,int param_4,uint *param_5,uint param_6)

{
  uint *puVar1;
  uint uVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;
  
  if (DAT_008e266c == 0) {
    param_4 = 0;
  }
  if (param_3 == 0) {
    param_3 = 4;
  }
  if (param_5 == (uint *)0x0) {
    if (DAT_00c9a634 == (uint *)0x0) {
      param_5 = (uint *)(**(code **)(DAT_00c97b24 + 0x134))(0x24,param_6 & 0xff0000);
    }
    else {
      param_5 = (uint *)(**(code **)(DAT_00c97b24 + 0x144))(DAT_00c9a634,param_6 & 0xff0000);
    }
    if (param_5 == (uint *)0x0) {
      return (uint *)0x0;
    }
    param_5[6] = 2;
  }
  else {
    param_5[6] = 3;
  }
  uVar2 = param_1 + -1 + param_3 & ~(param_3 - 1);
  puVar1 = param_5 + 4;
  *param_5 = uVar2;
  param_5[1] = param_2;
  uVar5 = param_2 + 7 >> 3;
  param_5[3] = param_3;
  param_5[2] = uVar5;
  *puVar1 = (uint)puVar1;
  param_5[5] = (uint)puVar1;
  if (param_4 != 0) {
    do {
      puVar3 = (uint *)(**(code **)(DAT_00c97b24 + 0x134))
                                 (uVar2 * param_2 + uVar5 + 7 + param_3,param_6);
      if (puVar3 == (uint *)0x0) {
        puVar3 = (uint *)*puVar1;
        while (puVar3 != puVar1) {
          *(uint *)puVar3[1] = *puVar3;
          *(uint *)(*puVar3 + 4) = puVar3[1];
          (**(code **)(DAT_00c97b24 + 0x138))(puVar3);
          puVar3 = (uint *)*puVar1;
        }
        if ((param_5[6] & 1) == 0) {
          if ((DAT_00c9a634 != param_5) && (DAT_00c9a634 != (uint *)0x0)) {
            (**(code **)(DAT_00c97b24 + 0x148))(DAT_00c9a634,param_5);
            return (uint *)0x0;
          }
          (**(code **)(DAT_00c97b24 + 0x138))(param_5);
        }
        return (uint *)0x0;
      }
      puVar3[1] = 0;
      *puVar3 = 0;
      uVar4 = *puVar1;
      puVar3[1] = (uint)puVar1;
      *puVar3 = uVar4;
      *(uint **)(*puVar1 + 4) = puVar3;
      *puVar1 = (uint)puVar3;
      puVar3 = puVar3 + 2;
      for (uVar4 = param_2 + 7 >> 5; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar3 = 0;
        puVar3 = puVar3 + 1;
      }
      for (uVar4 = uVar5 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined1 *)puVar3 = 0;
        puVar3 = (uint *)((int)puVar3 + 1);
      }
      param_4 = param_4 + -1;
    } while (param_4 != 0);
  }
  uVar2 = (uint)DAT_00c9a604;
  puVar1 = param_5 + 7;
  param_5[8] = (uint)&DAT_00c9a604;
  *puVar1 = uVar2;
  *(uint **)((int)DAT_00c9a604 + 4) = puVar1;
  DAT_00c9a604 = puVar1;
  return param_5;
}



/* entry 0x00801E90; bounded CFG instructions=100; body bytes=254 */

int * FUN_00801e90(int *param_1,code *param_2,undefined4 param_3)

{
  byte bVar1;
  uint uVar2;
  int *piVar3;
  uint uVar4;
  int *piVar5;
  int *piVar6;
  uint uVar7;
  int *piVar8;
  
  uVar2 = param_1[2];
  piVar5 = (int *)param_1[4];
  if ((int *)param_1[4] == param_1 + 4) {
    return param_1;
  }
  do {
    piVar3 = (int *)(**(code **)(DAT_00c97b24 + 0x134))(uVar2,0x10000);
    if (piVar3 == (int *)0x0) {
      return (int *)0x0;
    }
    piVar6 = piVar5 + 2;
    piVar8 = piVar3;
    for (uVar4 = uVar2 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *piVar8 = *piVar6;
      piVar6 = piVar6 + 1;
      piVar8 = piVar8 + 1;
    }
    for (uVar4 = uVar2 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(char *)piVar8 = (char)*piVar6;
      piVar6 = (int *)((int)piVar6 + 1);
      piVar8 = (int *)((int)piVar8 + 1);
    }
    uVar4 = 0;
    piVar6 = (int *)*piVar5;
    if (uVar2 != 0) {
      do {
        bVar1 = *(byte *)(uVar4 + (int)piVar3);
        if (bVar1 != 0) {
          uVar7 = 0;
          do {
            if ((bVar1 & (byte)(0x80 >> ((byte)uVar7 & 0x1f))) != 0) {
              (*param_2)(((int)piVar5 + uVar2 + param_1[3] + 7 & ~(param_1[3] - 1U)) +
                         (uVar7 + uVar4 * 8) * *param_1,param_3);
            }
            uVar7 = uVar7 + 1;
          } while (uVar7 < 8);
        }
        uVar4 = uVar4 + 1;
      } while (uVar4 < uVar2);
    }
    (**(code **)(DAT_00c97b24 + 0x138))(piVar3);
    piVar5 = piVar6;
  } while (piVar6 != param_1 + 4);
  return param_1;
}



/* entry 0x00802AF0; bounded CFG instructions=160; body bytes=936 */

/* WARNING: Removing unreachable block (ram,0x00802d72) */

uint * FUN_00802af0(uint *param_1,int param_2)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined1 *puVar7;
  byte *pbVar8;
  uint uVar9;
  uint *puVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  int iVar13;
  undefined4 *puVar14;
  byte *pbVar15;
  int local_c;
  uint local_8;
  undefined4 local_4;
  
  uVar9 = param_1[1];
  if ((uVar9 != *(uint *)(param_2 + 4)) || (uVar2 = param_1[2], uVar2 != *(uint *)(param_2 + 8))) {
    local_8 = 1;
    local_4 = FUN_008088d0(0x8000000a);
    FUN_00808820(&local_8);
    return (uint *)0x0;
  }
  uVar3 = param_1[3];
  if ((uVar3 == 4) || (uVar3 == 8)) {
    puVar4 = (uint *)(**(code **)(DAT_00c97b24 + 0x144))
                               (*(undefined4 *)(DAT_00c9a65c + DAT_00c97b24),0x30018);
    if (puVar4 == (uint *)0x0) {
      return (uint *)0x0;
    }
    puVar4[1] = uVar9;
    puVar4[2] = uVar2;
    puVar4[3] = uVar3;
    puVar4[5] = 0;
    puVar4[6] = 0;
    *puVar4 = 0;
    FUN_008086e0(&DAT_008e2670,puVar4);
    iVar5 = FUN_008027a0(puVar4);
    if (iVar5 == 0) {
      if ((*puVar4 & 1) != 0) {
        (**(code **)(DAT_00c97b24 + 0x138))(puVar4[5]);
        puVar4[5] = 0;
        puVar4[6] = 0;
        *puVar4 = *puVar4 & 0xfffffffe;
      }
      FUN_00808740(&DAT_008e2670,puVar4);
      (**(code **)(DAT_00c97b24 + 0x148))(*(undefined4 *)(DAT_00c9a65c + DAT_00c97b24),puVar4);
      return (uint *)0x0;
    }
    if (puVar4[3] == param_1[3]) {
      iVar5 = FUN_00803790();
    }
    else {
      iVar5 = FUN_00803840(puVar4,param_1);
    }
    puVar10 = puVar4;
    if (iVar5 == 0) {
      puVar10 = (uint *)0x0;
    }
    uVar9 = *puVar10;
    *puVar10 = uVar9 & 0xfffffffd;
    *puVar10 = *param_1 & 2 | uVar9 & 0xfffffffd;
    if ((*param_1 & 1) != 0) {
      (**(code **)(DAT_00c97b24 + 0x138))(param_1[5]);
      param_1[5] = 0;
      param_1[6] = 0;
      *param_1 = *param_1 & 0xfffffffe;
    }
    param_1[3] = 0x20;
    FUN_008027a0(param_1);
    uVar9 = puVar4[3];
    puVar10 = param_1;
    if (param_1[3] == uVar9) {
      if ((((undefined4 *)param_1[6] != (undefined4 *)0x0) &&
          ((undefined4 *)puVar4[6] != (undefined4 *)0x0)) && ((int)uVar9 < 9)) {
        puVar12 = (undefined4 *)puVar4[6];
        puVar6 = (undefined4 *)param_1[6];
        for (uVar9 = 1 << ((byte)uVar9 & 0x1f) & 0x3fffffff; uVar9 != 0; uVar9 = uVar9 - 1) {
          *puVar6 = *puVar12;
          puVar12 = puVar12 + 1;
          puVar6 = puVar6 + 1;
        }
        for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
          *(undefined1 *)puVar6 = *(undefined1 *)puVar12;
          puVar12 = (undefined4 *)((int)puVar12 + 1);
          puVar6 = (undefined4 *)((int)puVar6 + 1);
        }
      }
      puVar12 = (undefined4 *)puVar4[5];
      local_8 = ((int)(param_1[3] + 7) >> 3) * param_1[1];
      puVar6 = (undefined4 *)param_1[5];
      local_c = 0;
      if (0 < (int)param_1[2]) {
        do {
          puVar11 = puVar12;
          puVar14 = puVar6;
          for (uVar9 = local_8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
            *puVar14 = *puVar11;
            puVar11 = puVar11 + 1;
            puVar14 = puVar14 + 1;
          }
          for (uVar9 = local_8 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
            *(undefined1 *)puVar14 = *(undefined1 *)puVar11;
            puVar11 = (undefined4 *)((int)puVar11 + 1);
            puVar14 = (undefined4 *)((int)puVar14 + 1);
          }
          puVar12 = (undefined4 *)((int)puVar12 + puVar4[4]);
          puVar6 = (undefined4 *)((int)puVar6 + param_1[4]);
          local_c = local_c + 1;
        } while (local_c < (int)param_1[2]);
      }
    }
    else {
      iVar5 = FUN_00803840(param_1,puVar4);
      if (iVar5 == 0) {
        puVar10 = (uint *)0x0;
      }
    }
    uVar9 = *puVar10;
    *puVar10 = uVar9 & 0xfffffffd;
    *puVar10 = *puVar4 & 2 | uVar9 & 0xfffffffd;
    (**(code **)(DAT_00c97b24 + 0x138))(puVar4[5]);
    puVar4[5] = 0;
    puVar4[6] = 0;
    *puVar4 = *puVar4 & 0xfffffffe;
    FUN_00808740(&DAT_008e2670,puVar4);
    (**(code **)(DAT_00c97b24 + 0x148))(*(undefined4 *)(DAT_00c9a65c + DAT_00c97b24),puVar4);
  }
  else if (uVar3 != 0x20) {
    local_8 = 1;
    local_4 = FUN_008088d0(0x80000009);
    FUN_00808820(&local_8);
    return (uint *)0x0;
  }
  iVar5 = *(int *)(param_2 + 0x18);
  uVar9 = param_1[5];
  pbVar15 = *(byte **)(param_2 + 0x14);
  local_c = 0;
  if (0 < (int)param_1[2]) {
    do {
      iVar13 = *(int *)(param_2 + 0xc);
      if ((iVar13 == 4) || (iVar13 == 8)) {
        iVar13 = 0;
        if (0 < (int)param_1[1]) {
          pbVar8 = pbVar15;
          puVar7 = (undefined1 *)(uVar9 + 3);
          do {
            bVar1 = *pbVar8;
            pbVar8 = pbVar8 + 1;
            iVar13 = iVar13 + 1;
            *puVar7 = *(undefined1 *)(iVar5 + 3 + (uint)bVar1 * 4);
            puVar7 = puVar7 + 4;
          } while (iVar13 < (int)param_1[1]);
        }
      }
      else if ((iVar13 == 0x20) && (iVar13 = 0, 0 < (int)param_1[1])) {
        puVar7 = (undefined1 *)(uVar9 + 3);
        do {
          *puVar7 = puVar7[(int)pbVar15 - uVar9];
          puVar7 = puVar7 + 4;
          iVar13 = iVar13 + 1;
        } while (iVar13 < (int)param_1[1]);
      }
      pbVar15 = pbVar15 + *(int *)(param_2 + 0x10);
      uVar9 = uVar9 + param_1[4];
      local_c = local_c + 1;
    } while (local_c < (int)param_1[2]);
  }
  return param_1;
}



/* entry 0x008030C0; bounded CFG instructions=126; body bytes=333 */

undefined4 FUN_008030c0(undefined4 param_1,int param_2,code *param_3,undefined4 param_4)

{
  int iVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcStack_4;
  
  pcVar5 = *(char **)(DAT_00c9a65c + 4 + DAT_00c97b24);
  iVar1 = FUN_0080e9b0(param_1);
  if (((iVar1 == 0) && (pcVar5 != (char *)0x0)) && (*pcVar5 != '\0')) {
    while (*pcVar5 != '\0') {
      (**(code **)(DAT_00c97b24 + 0x10c))(pcVar5,0x3b);
      iVar1 = (**(code **)(DAT_00c97b24 + 0x10c))(pcVar5,0x3b);
      if (iVar1 == 0) {
        uVar4 = (**(code **)(DAT_00c97b24 + 0x120))(pcVar5);
        pcStack_4 = (char *)0x0;
      }
      else {
        uVar4 = iVar1 - (int)pcVar5;
        pcStack_4 = (char *)(iVar1 + 1);
      }
      iVar1 = (**(code **)(DAT_00c97b24 + 0x120))(param_1);
      pcVar2 = (char *)FUN_00803210(iVar1 + uVar4 + param_2);
      if (pcVar2 == (char *)0x0) {
        return 0;
      }
      pcVar6 = pcVar2;
      for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar6 = pcVar6 + 4;
      }
      for (uVar3 = uVar4 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar6 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar6 = pcVar6 + 1;
      }
      (**(code **)(DAT_00c97b24 + 0xf8))(pcVar2 + uVar4,param_1);
      iVar1 = (*param_3)(pcVar2,param_4);
      if (iVar1 == 0) {
        return param_1;
      }
      pcVar5 = pcStack_4;
      if (pcStack_4 == (char *)0x0) {
        return param_1;
      }
    }
  }
  else {
    iVar1 = (**(code **)(DAT_00c97b24 + 0x120))(param_1);
    iVar1 = FUN_00803210(iVar1 + param_2);
    if (iVar1 == 0) {
      return 0;
    }
    (**(code **)(DAT_00c97b24 + 0xf8))(iVar1,param_1);
    (*param_3)(iVar1,param_4);
  }
  return param_1;
}



/* entry 0x008050C0; bounded CFG instructions=160; body bytes=546 */

int * FUN_008050c0(int *param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  int *piVar9;
  undefined4 *puVar10;
  
  if (*param_2 == 0) {
    if (*(code **)(*param_1 + 0x14) != (code *)0x0) {
      (**(code **)(*param_1 + 0x14))(param_1);
    }
    *(int *)(*param_1 + 0x3c) = *(int *)(*param_1 + 0x3c) + -1;
    iVar3 = *param_1;
    if (*(int *)(iVar3 + 0x3c) == 0) {
      if (*(code **)(iVar3 + 0xc) != (code *)0x0) {
        (**(code **)(iVar3 + 0xc))(iVar3);
      }
      if (*(int *)(*param_1 + 0x38) != 0) {
        (**(code **)(DAT_00c97b24 + 0x138))(*param_1);
        *param_1 = 0;
      }
    }
    if (param_1[8] != 0) {
      (**(code **)(DAT_00c97b24 + 0x138))(param_1[8]);
      param_1[8] = 0;
      param_1[9] = 0;
    }
    piVar9 = param_1;
    for (iVar3 = 10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *piVar9 = 0;
      piVar9 = piVar9 + 1;
    }
    param_2[1] = param_2[1] + -1;
    return param_1;
  }
  if (param_1[8] != 0) {
    (**(code **)(DAT_00c97b24 + 0x138))(param_1[8]);
    param_1[8] = 0;
    param_1[9] = 0;
  }
  iVar3 = *param_1;
  if ((*(int *)(iVar3 + 0x3c) == 0) && (*(int *)(iVar3 + 0x38) != 0)) {
    (**(code **)(DAT_00c97b24 + 0x138))(iVar3);
    *param_1 = 0;
  }
  uVar2 = ((int)param_1 - param_2[2]) / 0x28;
  if (uVar2 < param_2[1] - 1U) {
    uVar6 = uVar2;
    puVar4 = (undefined4 *)
             (param_2[2] + uVar2 * 0x80 + *(int *)(DAT_00c9bc60 + 0x38 + DAT_00c97b24) * 0x28);
    do {
      puVar8 = puVar4 + 0x20;
      puVar10 = puVar4;
      for (iVar3 = 0x20; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar10 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar10 = puVar10 + 1;
      }
      uVar6 = uVar6 + 1;
      puVar4 = puVar4 + 0x20;
    } while (uVar6 < param_2[1] - 1U);
    puVar4 = (undefined4 *)(param_2[2] + *(int *)(DAT_00c9bc60 + 0x38 + DAT_00c97b24) * 0xa8);
    uVar6 = uVar2;
    if (uVar2 < param_2[1] - 1U) {
      do {
        *puVar4 = puVar4[3];
        puVar4[1] = puVar4[4];
        puVar4[2] = puVar4[5];
        uVar6 = uVar6 + 1;
        puVar4 = puVar4 + 3;
      } while (uVar6 < param_2[1] - 1U);
    }
    if (uVar2 < param_2[1] - 1U) {
      iVar3 = uVar2 * 0x28;
      uVar6 = uVar2;
      do {
        puVar4 = (undefined4 *)(iVar3 + 0x28 + param_2[2]);
        puVar8 = (undefined4 *)(iVar3 + param_2[2]);
        for (iVar5 = 10; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar8 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar8 = puVar8 + 1;
        }
        *(int *)(param_2[2] + 8 + iVar3) = *(int *)(param_2[2] + 8 + iVar3) + -0x80;
        uVar6 = uVar6 + 1;
        *(int *)(param_2[2] + 0x1c + iVar3) = *(int *)(param_2[2] + 0x1c + iVar3) + -0xc;
        iVar3 = iVar3 + 0x28;
      } while (uVar6 < param_2[1] - 1U);
    }
    uVar6 = 0;
    if (param_2[1] != 1) {
      iVar3 = 0;
      do {
        iVar5 = param_2[2];
        uVar7 = 0;
        if (*(int *)(iVar3 + 4 + iVar5) != 0) {
          do {
            iVar5 = *(int *)(iVar3 + 8 + iVar5);
            piVar9 = (int *)(iVar5 + uVar7 * 4);
            uVar1 = *(uint *)(iVar5 + uVar7 * 4);
            if (uVar2 <= uVar1) {
              if (uVar1 == uVar2) {
                *piVar9 = -1;
              }
              else {
                *piVar9 = uVar1 - 1;
              }
            }
            iVar5 = param_2[2];
            uVar7 = uVar7 + 1;
          } while (uVar7 < *(uint *)(iVar3 + 4 + iVar5));
        }
        uVar6 = uVar6 + 1;
        iVar3 = iVar3 + 0x28;
      } while (uVar6 < param_2[1] - 1U);
    }
  }
  param_2[1] = param_2[1] + -1;
  return param_1;
}



/* entry 0x008057B0; bounded CFG instructions=33; body bytes=102 */

undefined4 * FUN_008057b0(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  puVar1 = (undefined4 *)
           (**(code **)(DAT_00c97b24 + 0x144))(*(undefined4 *)(DAT_00c9bc60 + DAT_00c97b24),0x30409)
  ;
  if (puVar1 != (undefined4 *)0x0) {
    puVar3 = puVar1;
    for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    *puVar1 = 0;
    return puVar1;
  }
  uStack_8 = 1;
  uStack_4 = FUN_008088d0(0x80000013,0x34);
  FUN_00808820(&uStack_8);
  return (undefined4 *)0x0;
}



/* entry 0x00805A20; bounded CFG instructions=160; body bytes=747 */

undefined4 * FUN_00805a20(undefined4 *param_1,int param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  char *pcVar9;
  undefined4 *puVar10;
  char *pcVar11;
  undefined4 *puVar12;
  int local_10;
  uint local_c;
  int iStack_8;
  undefined4 uStack_4;
  
  puVar2 = (undefined4 *)*param_1;
  iVar4 = puVar2[8];
  if (param_2 != 0) {
    iVar4 = iVar4 + 1;
  }
  iVar8 = puVar2[0xb];
  uVar6 = 0xffffffff;
  pcVar9 = (char *)*puVar2;
  do {
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar9 + 1;
  } while (cVar1 != '\0');
  local_10 = iVar8 * 0xc + iVar4 * 0x10 + (~uVar6 + 3 & 0xfffffffc) + 0x40;
  if (iVar8 != 0) {
    puVar5 = (undefined4 *)puVar2[0xc];
    do {
      pcVar9 = (char *)*puVar5;
      uVar6 = 0xffffffff;
      puVar5 = puVar5 + 3;
      do {
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar9 + 1;
      } while (cVar1 != '\0');
      local_10 = local_10 + (~uVar6 + 3 & 0xfffffffc) + iVar4 * 4;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
  }
  puVar5 = (undefined4 *)(**(code **)(DAT_00c97b24 + 0x134))(local_10,0x30409);
  if (puVar5 == (undefined4 *)0x0) {
    iStack_8 = 1;
    uStack_4 = FUN_008088d0(0x80000013,local_10);
    FUN_00808820(&iStack_8);
    return (undefined4 *)0x0;
  }
  uVar6 = 0xffffffff;
  *puVar5 = puVar5 + 0x10;
  pcVar9 = (char *)*puVar2;
  pcVar11 = pcVar9;
  do {
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    cVar1 = *pcVar11;
    pcVar11 = pcVar11 + 1;
  } while (cVar1 != '\0');
  pcVar11 = (char *)*puVar5;
  local_10 = (int)(puVar5 + 0x10) + (~uVar6 + 3 & 0xfffffffc);
  do {
    cVar1 = *pcVar9;
    pcVar9 = pcVar9 + 1;
    *pcVar11 = cVar1;
    pcVar11 = pcVar11 + 1;
  } while (cVar1 != '\0');
  iVar8 = 7;
  puVar10 = puVar2;
  puVar12 = puVar5;
  while( true ) {
    puVar12 = puVar12 + 1;
    puVar10 = puVar10 + 1;
    if (iVar8 == 0) break;
    iVar8 = iVar8 + -1;
    *puVar12 = *puVar10;
  }
  puVar5[8] = iVar4;
  puVar5[9] = local_10;
  local_10 = local_10 + iVar4 * 0xc;
  uVar6 = 0;
  if (puVar2[8] != 0) {
    iVar8 = 0;
    do {
      uVar6 = uVar6 + 1;
      *(undefined4 *)(iVar8 + 4 + puVar5[9]) = *(undefined4 *)(iVar8 + 4 + puVar2[9]);
      *(undefined4 *)(iVar8 + puVar5[9]) = *(undefined4 *)(iVar8 + puVar2[9]);
      *(undefined4 *)(iVar8 + 8 + puVar5[9]) = *(undefined4 *)(iVar8 + 8 + puVar2[9]);
      iVar8 = iVar8 + 0xc;
    } while (uVar6 < (uint)puVar2[8]);
  }
  if (param_2 != 0) {
    iVar8 = uVar6 * 0xc;
    *(undefined4 *)(iVar8 + 4 + puVar5[9]) = 0;
    *(int *)(iVar8 + puVar5[9]) = param_2;
    *(undefined4 *)(iVar8 + 8 + puVar5[9]) = 0;
  }
  puVar5[10] = local_10;
  iStack_8 = iVar4 * 4;
  local_10 = local_10 + iStack_8;
  puVar10 = (undefined4 *)puVar2[10];
  puVar12 = (undefined4 *)puVar5[10];
  for (uVar6 = puVar2[8] & 0x3fffffff; uVar6 != 0; uVar6 = uVar6 - 1) {
    *puVar12 = *puVar10;
    puVar10 = puVar10 + 1;
    puVar12 = puVar12 + 1;
  }
  for (iVar8 = 0; iVar8 != 0; iVar8 = iVar8 + -1) {
    *(undefined1 *)puVar12 = *(undefined1 *)puVar10;
    puVar10 = (undefined4 *)((int)puVar10 + 1);
    puVar12 = (undefined4 *)((int)puVar12 + 1);
  }
  if (param_2 != 0) {
    *(undefined4 *)(puVar5[10] + -4 + iVar4 * 4) = 0;
  }
  uVar3 = puVar2[0xb];
  puVar5[0xc] = local_10;
  puVar5[0xb] = uVar3;
  local_c = 0;
  local_10 = local_10 + puVar2[0xb] * 0xc;
  if (puVar2[0xb] != 0) {
    iVar8 = 0;
    do {
      *(int *)(iVar8 + puVar5[0xc]) = local_10;
      pcVar9 = *(char **)(iVar8 + puVar2[0xc]);
      uVar6 = 0xffffffff;
      pcVar11 = pcVar9;
      do {
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        cVar1 = *pcVar11;
        pcVar11 = pcVar11 + 1;
      } while (cVar1 != '\0');
      local_10 = local_10 + (~uVar6 + 3 & 0xfffffffc);
      pcVar11 = *(char **)(iVar8 + puVar5[0xc]);
      do {
        cVar1 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        *pcVar11 = cVar1;
        pcVar11 = pcVar11 + 1;
      } while (cVar1 != '\0');
      *(int *)(iVar8 + 4 + puVar5[0xc]) = local_10;
      local_10 = local_10 + iStack_8;
      puVar10 = *(undefined4 **)(iVar8 + 4 + puVar2[0xc]);
      puVar12 = *(undefined4 **)(iVar8 + 4 + puVar5[0xc]);
      for (uVar6 = puVar2[8] & 0x3fffffff; uVar6 != 0; uVar6 = uVar6 - 1) {
        *puVar12 = *puVar10;
        puVar10 = puVar10 + 1;
        puVar12 = puVar12 + 1;
      }
      for (iVar7 = 0; iVar7 != 0; iVar7 = iVar7 + -1) {
        *(undefined1 *)puVar12 = *(undefined1 *)puVar10;
        puVar10 = (undefined4 *)((int)puVar10 + 1);
        puVar12 = (undefined4 *)((int)puVar12 + 1);
      }
      if (param_2 != 0) {
        *(undefined4 *)(*(int *)(iVar8 + 4 + puVar5[0xc]) + -4 + iVar4 * 4) =
             *(undefined4 *)(iVar8 + 8 + puVar2[0xc]);
      }
      *(undefined4 *)(iVar8 + 8 + puVar5[0xc]) = *(undefined4 *)(iVar8 + 8 + puVar2[0xc]);
      local_c = local_c + 1;
      iVar8 = iVar8 + 0xc;
    } while (local_c < (uint)puVar2[0xb]);
  }
  uVar3 = puVar2[0xd];
  puVar5[0xe] = 1;
  puVar5[0xd] = uVar3;
  puVar5[0xf] = 0;
  if ((puVar2[0xf] == 0) && (puVar2[0xe] != 0)) {
    (**(code **)(DAT_00c97b24 + 0x138))(puVar2);
  }
  *param_1 = puVar5;
  return puVar5;
}



/* entry 0x00805F40; bounded CFG instructions=160; body bytes=1412 */

int * FUN_00805f40(int *param_1)

{
  int *piVar1;
  int iVar2;
  code *pcVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  uint *puVar10;
  uint uVar11;
  undefined4 *puVar12;
  int iVar13;
  int *piVar14;
  int *piVar15;
  uint uVar16;
  undefined4 uVar17;
  int *local_14;
  undefined4 local_10;
  int local_c;
  int *local_8;
  undefined4 local_4;
  
  piVar4 = param_1;
  if (param_1 == (int *)0x0) {
    local_8 = (int *)0x1;
    local_4 = FUN_008088d0(0x80000016);
    FUN_00808820(&local_8);
    return (int *)0x0;
  }
  if (*param_1 == 0) {
    local_8 = (int *)0x1;
    local_4 = FUN_008088d0(0x34);
    FUN_00808820(&local_8);
  }
  else {
    piVar7 = (int *)param_1[1];
    if (piVar7 == (int *)0x0) {
LAB_008063b2:
      *piVar4 = 0;
      return piVar4;
    }
    local_c = 0;
    if ((piVar7 <= (int *)param_1[10]) || (*(int *)(param_1[2] + param_1[10] * 0x28) == 0)) {
      local_8 = (int *)0x1;
      local_4 = FUN_008088d0(0x24);
      FUN_00808820(&local_8);
      return (int *)0x0;
    }
    param_1 = (int *)0x0;
    local_8 = (int *)0x0;
    while (piVar15 = (int *)0xffffffff, piVar7 != (int *)0x0) {
      piVar14 = (int *)piVar4[2];
      local_14 = piVar7;
      do {
        iVar13 = *(int *)(*piVar14 + 0x20);
        if (iVar13 != 0) {
          puVar10 = *(uint **)(*piVar14 + 0x24);
          do {
            piVar1 = (int *)*puVar10;
            if ((local_8 < piVar1) && (piVar1 < piVar15)) {
              piVar15 = piVar1;
            }
            puVar10 = puVar10 + 3;
            iVar13 = iVar13 + -1;
          } while (iVar13 != 0);
        }
        piVar14 = piVar14 + 10;
        local_14 = (int *)((int)local_14 - 1);
      } while (local_14 != (int *)0x0);
      local_14 = (int *)0x0;
      if (piVar15 == (int *)0xffffffff) break;
      param_1 = (int *)((int)param_1 + 1);
      local_8 = piVar15;
    }
    iVar8 = *(int *)(DAT_00c9bc60 + 0x38 + DAT_00c97b24);
    uVar16 = iVar8 * 0xb4;
    iVar13 = (int)piVar7 * 0x28;
    if (piVar7 != (int *)0x0) {
      iVar13 = iVar13 + *(int *)(piVar4[2] + 4) * (int)piVar7 * 4;
    }
    iVar5 = (((int)piVar7 + 5U) * (int)param_1 + ((int)param_1 + 1) * (int)piVar7) * 4;
    if (piVar7 != (int *)0x0) {
      piVar15 = (int *)piVar4[2];
      local_14 = piVar7;
      do {
        iVar9 = *piVar15;
        iVar2 = *(int *)(iVar9 + 0x34);
        if (iVar2 != 0) {
          iVar5 = iVar5 + iVar2;
        }
        piVar15 = piVar15 + 10;
        iVar5 = iVar5 + *(int *)(iVar9 + 0x20) * 4;
        local_14 = (int *)((int)local_14 - 1);
      } while (local_14 != (int *)0x0);
    }
    uVar11 = iVar5 + (int)param_1 * 0x1c + 0x14 +
             iVar8 * 0xc + ((int)param_1 * 0x34 + 0x14) * (int)piVar7 + iVar13;
    if (uVar16 < uVar11) {
      uVar16 = uVar11;
    }
    if ((uVar16 <= (uint)piVar4[9]) || (iVar13 = FUN_008064d0(piVar4,uVar16), iVar13 != 0)) {
      DAT_00c9a6b4 = (int *)(piVar4[8] + uVar16);
      DAT_00c9a6b8 = (int *)0x0;
      piVar7 = (int *)piVar4[2];
      uVar11 = 0;
      local_14 = piVar4;
      local_10 = 0;
      if (piVar4[1] != 0) {
        do {
          if (*piVar7 != 0) {
            *(undefined4 *)(piVar7[7] + 4) = 0;
            *(undefined4 *)piVar7[7] = 0;
          }
          piVar7 = piVar7 + 10;
          uVar11 = uVar11 + 1;
        } while (uVar11 < (uint)piVar4[1]);
      }
      piVar7 = (int *)piVar4[2];
      uVar11 = 0;
      if (piVar4[1] != 0) {
        do {
          if ((*piVar7 != 0) && (iVar13 = piVar7[1], iVar13 != 0)) {
            piVar15 = (int *)piVar7[2];
            do {
              if (*piVar15 != -1) {
                piVar14 = *(int **)(piVar4[2] + 0x1c + *piVar15 * 0x28);
                *piVar14 = *piVar14 + 1;
              }
              piVar15 = piVar15 + 1;
              iVar13 = iVar13 + -1;
            } while (iVar13 != 0);
          }
          piVar7 = piVar7 + 10;
          uVar11 = uVar11 + 1;
        } while (uVar11 < (uint)piVar4[1]);
      }
      uVar11 = piVar4[10];
      if (**(int **)(piVar4[2] + 0x1c + uVar11 * 0x28) != 0) {
        uVar17 = 0x24;
LAB_008061aa:
        local_8 = (int *)0x1;
        local_4 = FUN_008088d0(uVar17);
        FUN_00808820(&local_8);
        return (int *)0x0;
      }
      uVar6 = 0;
      if (piVar4[1] != 0) {
        puVar12 = (undefined4 *)(piVar4[2] + 0x1c);
        do {
          if ((uVar6 != uVar11) && (*(int *)*puVar12 == 0)) {
            local_8 = (int *)0x1;
            local_4 = FUN_008088d0(0x22);
            FUN_00808820(&local_8);
            return (int *)0x0;
          }
          uVar6 = uVar6 + 1;
          puVar12 = puVar12 + 10;
        } while (uVar6 < (uint)piVar4[1]);
      }
      FUN_008067b0(&local_14,uVar11);
      uVar11 = 0;
      if (piVar4[1] != 0) {
        piVar7 = (int *)(piVar4[2] + 0x1c);
        do {
          if (*(int *)*piVar7 != ((int *)*piVar7)[1]) {
            uVar17 = 0x1c;
            goto LAB_008061aa;
          }
          uVar11 = uVar11 + 1;
          piVar7 = piVar7 + 10;
        } while (uVar11 < (uint)piVar4[1]);
      }
      piVar4[10] = 0;
      iVar13 = *(int *)(DAT_00c9bc60 + 0x38 + DAT_00c97b24);
      local_14 = (int *)(piVar4[2] + iVar13 * 0x28);
      param_1 = (int *)piVar4[1];
      DAT_00c9a6b4 = local_14 + iVar13 * 0x20 + (int)param_1 * 3 + -3;
      piVar7 = (int *)(piVar4[8] + -0xc + uVar16);
      if (-1 < (int)param_1 + -1) {
        iVar13 = ((int)param_1 + -1) * 0x28;
        piVar15 = DAT_00c9a6b4;
        do {
          DAT_00c9a6b4 = piVar15 + -3;
          *piVar7 = *piVar15;
          piVar7[1] = piVar15[1];
          piVar7[2] = piVar15[2];
          *(int **)(iVar13 + 0x1c + piVar4[2]) = piVar7;
          piVar7 = piVar7 + -3;
          param_1 = (int *)((int)param_1 + -1);
          iVar13 = iVar13 + -0x28;
          piVar15 = DAT_00c9a6b4;
        } while (param_1 != (int *)0x0);
      }
      iVar13 = piVar4[2];
      param_1 = (int *)0x0;
      piVar7 = (int *)(iVar13 + piVar4[1] * 0x28);
      if (piVar4[1] != 0) {
        iVar8 = 0;
        do {
          iVar5 = *(int *)(iVar13 + 4 + iVar8);
          piVar15 = local_14;
          piVar14 = piVar7;
          if (iVar5 == 0) {
            *(undefined4 *)(iVar13 + 8 + iVar8) = 0;
          }
          else {
            for (; iVar5 != 0; iVar5 = iVar5 + -1) {
              *piVar14 = *piVar15;
              piVar15 = piVar15 + 1;
              piVar14 = piVar14 + 1;
            }
            *(int **)(iVar8 + 8 + piVar4[2]) = piVar7;
          }
          iVar13 = piVar4[2];
          local_14 = local_14 + 0x20;
          iVar5 = *(int *)(iVar13 + 4 + iVar8);
          local_c = local_c + iVar5;
          iVar8 = iVar8 + 0x28;
          piVar7 = piVar7 + iVar5;
          param_1 = (int *)((int)param_1 + 1);
        } while (param_1 < (uint)piVar4[1]);
      }
      DAT_00c9a6b8 = local_14 + local_c;
      local_8 = DAT_00c9a6b4;
      iVar13 = FUN_0080f0d0(piVar4);
      if (iVar13 == 0) {
        iVar13 = FUN_008064d0(piVar4,(int)DAT_00c9a6b8 - piVar4[8]);
        if (iVar13 == 0) {
LAB_0080642f:
          FUN_008065e0(piVar4,piVar4);
          return (int *)0x0;
        }
        uVar16 = 0;
        if (piVar4[1] != 0) {
          iVar13 = 0;
          do {
            uVar16 = uVar16 + 1;
            *(undefined4 *)(iVar13 + 0x1c + piVar4[2]) = 0;
            iVar13 = iVar13 + 0x28;
          } while (uVar16 < (uint)piVar4[1]);
        }
        param_1 = (int *)(piVar4[1] + -1);
        if (-1 < (int)param_1) {
          iVar13 = (int)param_1 * 0x28;
          do {
            iVar8 = piVar4[2];
            iVar5 = *(int *)(iVar13 + iVar8);
            iVar9 = *(int *)(iVar5 + 0x3c);
            *(int *)(iVar5 + 0x3c) = iVar9 + 1;
            if (((iVar9 == 0) && (*(code **)(iVar5 + 8) != (code *)0x0)) &&
               (iVar9 = (**(code **)(iVar5 + 8))(iVar5), iVar9 == 0)) {
LAB_008063d8:
              uVar16 = piVar4[1];
              uVar11 = (uVar16 - (int)param_1) - 1;
              goto LAB_008063eb;
            }
            if ((*(code **)(iVar5 + 0x10) != (code *)0x0) &&
               (iVar8 = (**(code **)(iVar5 + 0x10))(iVar13 + iVar8), iVar8 == 0)) {
              iVar13 = *(int *)(iVar5 + 0x3c) + -1;
              *(int *)(iVar5 + 0x3c) = iVar13;
              if ((iVar13 == 0) && (*(code **)(iVar5 + 0xc) != (code *)0x0)) {
                (**(code **)(iVar5 + 0xc))(iVar5);
              }
              goto LAB_008063d8;
            }
            iVar13 = iVar13 + -0x28;
            param_1 = (int *)((int)param_1 + -1);
          } while (-1 < (int)param_1);
        }
        iVar13 = piVar4[1] + -1;
        if (-1 < iVar13) {
          iVar8 = iVar13 * 0x28;
          do {
            pcVar3 = *(code **)(*(int *)(iVar8 + piVar4[2]) + 0x18);
            if ((pcVar3 != (code *)0x0) && (iVar5 = (*pcVar3)(iVar8 + piVar4[2],piVar4), iVar5 == 0)
               ) {
              uVar11 = piVar4[1];
              uVar16 = uVar11;
LAB_008063eb:
              uVar11 = uVar16 - uVar11;
              if (uVar11 < uVar16) {
                iVar13 = uVar11 * 0x28;
                do {
                  iVar8 = *(int *)(piVar4[2] + iVar13);
                  if (*(code **)(iVar8 + 0x14) != (code *)0x0) {
                    (**(code **)(iVar8 + 0x14))((int *)(piVar4[2] + iVar13));
                  }
                  iVar5 = *(int *)(iVar8 + 0x3c) + -1;
                  *(int *)(iVar8 + 0x3c) = iVar5;
                  if ((iVar5 == 0) && (*(code **)(iVar8 + 0xc) != (code *)0x0)) {
                    (**(code **)(iVar8 + 0xc))(iVar8);
                  }
                  uVar11 = uVar11 + 1;
                  iVar13 = iVar13 + 0x28;
                } while (uVar11 < (uint)piVar4[1]);
              }
              goto LAB_0080642f;
            }
            iVar13 = iVar13 + -1;
            iVar8 = iVar8 + -0x28;
          } while (-1 < iVar13);
        }
        goto LAB_008063b2;
      }
    }
  }
  return (int *)0x0;
}



/* entry 0x008065E0; bounded CFG instructions=157; body bytes=462 */

undefined4 FUN_008065e0(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined4 *puVar11;
  undefined4 local_8;
  undefined4 uStack_4;
  
  iVar2 = param_2;
  iVar1 = param_1;
  if (param_1 != param_2) {
    iVar9 = *(int *)(param_2 + 4) + -1;
    if (iVar9 < 0) {
      *(undefined4 *)(param_1 + 4) = *(undefined4 *)(param_2 + 4);
    }
    else {
      iVar10 = iVar9 * 0x28;
      param_1 = iVar9;
      do {
        puVar5 = (undefined4 *)(*(int *)(param_2 + 8) + iVar10);
        puVar11 = (undefined4 *)(*(int *)(iVar1 + 8) + iVar10);
        for (iVar9 = 10; iVar9 != 0; iVar9 = iVar9 + -1) {
          *puVar11 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar11 = puVar11 + 1;
        }
        *(undefined4 *)(*(int *)(iVar1 + 8) + 0xc + iVar10) = 0;
        *(undefined4 *)(*(int *)(iVar1 + 8) + 0x10 + iVar10) = 0;
        *(undefined4 *)(*(int *)(iVar1 + 8) + 0x14 + iVar10) = 0;
        *(undefined4 *)(*(int *)(iVar1 + 8) + 0x18 + iVar10) = 0;
        iVar9 = *(int *)(*(int *)(iVar1 + 8) + 0x24 + iVar10);
        if (iVar9 != 0) {
          uVar3 = (**(code **)(DAT_00c97b24 + 0x134))(iVar9,0x30409);
          *(undefined4 *)(*(int *)(iVar1 + 8) + 0x20 + iVar10) = uVar3;
          iVar9 = *(int *)(iVar1 + 8) + iVar10;
          puVar5 = *(undefined4 **)(iVar9 + 0x20);
          if (puVar5 == (undefined4 *)0x0) {
            local_8 = 1;
            uStack_4 = FUN_008088d0(0x80000013,
                                    *(undefined4 *)(*(int *)(iVar1 + 8) + 0x24 + param_1 * 0x28));
            FUN_00808820(&local_8);
            return 0;
          }
          uVar7 = *(uint *)(iVar9 + 0x24);
          puVar11 = *(undefined4 **)(*(int *)(param_2 + 8) + 0x20 + iVar10);
          for (uVar6 = uVar7 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
            *puVar5 = *puVar11;
            puVar11 = puVar11 + 1;
            puVar5 = puVar5 + 1;
          }
          for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
            *(undefined1 *)puVar5 = *(undefined1 *)puVar11;
            puVar11 = (undefined4 *)((int)puVar11 + 1);
            puVar5 = (undefined4 *)((int)puVar5 + 1);
          }
        }
        iVar10 = iVar10 + -0x28;
        param_1 = param_1 + -1;
      } while (-1 < param_1);
      *(undefined4 *)(iVar1 + 4) = *(undefined4 *)(param_2 + 4);
    }
  }
  iVar9 = *(int *)(iVar1 + 8) + *(int *)(DAT_00c9bc60 + 0x38 + DAT_00c97b24) * 0x28;
  param_2 = *(int *)(param_2 + 4);
  iVar10 = param_2 + -1;
  if (-1 < iVar10) {
    iVar4 = iVar10 * 0x28;
    iVar10 = iVar10 * 0x80 + iVar9;
    do {
      *(int *)(*(int *)(iVar1 + 8) + 8 + iVar4) = iVar10;
      puVar5 = *(undefined4 **)(*(int *)(iVar2 + 8) + 8 + iVar4);
      if (puVar5 != (undefined4 *)0x0) {
        puVar11 = *(undefined4 **)(*(int *)(iVar1 + 8) + 8 + iVar4);
        for (iVar8 = 0x20; iVar8 != 0; iVar8 = iVar8 + -1) {
          *puVar11 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar11 = puVar11 + 1;
        }
      }
      iVar10 = iVar10 + -0x80;
      iVar4 = iVar4 + -0x28;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  uVar7 = 0;
  puVar5 = (undefined4 *)(*(int *)(DAT_00c9bc60 + 0x38 + DAT_00c97b24) * 0x80 + iVar9);
  if (*(int *)(iVar2 + 4) != 0) {
    iVar9 = 0;
    do {
      *puVar5 = 0;
      puVar5[1] = 0;
      puVar5[2] = 0;
      uVar7 = uVar7 + 1;
      *(undefined4 **)(*(int *)(iVar1 + 8) + 0x1c + iVar9) = puVar5;
      puVar5 = puVar5 + 3;
      iVar9 = iVar9 + 0x28;
    } while (uVar7 < *(uint *)(iVar2 + 4));
  }
  return 1;
}



/* entry 0x00806DE0; bounded CFG instructions=105; body bytes=310 */

bool FUN_00806de0(int param_1,int *param_2,int param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  bool bVar5;
  int *piVar6;
  undefined4 local_8;
  undefined4 local_4;
  
  uVar1 = *(uint *)(param_3 + 0x2c);
  piVar6 = param_2;
  for (iVar3 = 10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar6 = 0;
    piVar6 = piVar6 + 1;
  }
  if (uVar1 >= 0x21) {
    local_8 = 1;
    local_4 = FUN_008088d0(0x29);
    FUN_00808820(&local_8);
  }
  bVar5 = 0x20 < *(uint *)(param_3 + 0x20);
  if (bVar5) {
    local_8 = 1;
    local_4 = FUN_008088d0(0x28);
    FUN_00808820(&local_8);
  }
  bVar5 = !bVar5 && uVar1 < 0x21;
  uVar4 = *(uint *)(DAT_00c9bc60 + 0x38 + DAT_00c97b24);
  if (uVar4 <= uVar1) {
    local_8 = 1;
    local_4 = FUN_008088d0(0x2a);
    FUN_00808820(&local_8);
    return false;
  }
  if (bVar5) {
    puVar2 = (undefined4 *)(*(int *)(param_1 + 4) * 0x80 + uVar4 * 0x28 + *(int *)(param_1 + 8));
    uVar4 = 0;
    param_2[2] = (int)puVar2;
    param_2[1] = uVar1;
    if (uVar1 != 0) {
      do {
        *puVar2 = 0xffffffff;
        puVar2 = puVar2 + 1;
        uVar4 = uVar4 + 1;
      } while (uVar4 < (uint)param_2[1]);
    }
    puVar2 = (undefined4 *)
             (*(int *)(param_1 + 8) +
             (*(int *)(param_1 + 4) + *(int *)(DAT_00c9bc60 + 0x38 + DAT_00c97b24) * 0xe) * 0xc);
    *puVar2 = 0;
    puVar2[1] = 0;
    puVar2[2] = 0;
    param_2[7] = (int)puVar2;
    param_2[8] = 0;
    param_2[9] = 0;
    *param_2 = param_3;
    *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
  }
  return bVar5;
}



/* entry 0x00809550; bounded CFG instructions=139; body bytes=425 */

undefined4 FUN_00809550(void)

{
  byte bVar1;
  byte bVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  
  puVar4 = (undefined4 *)(DAT_00c97b24 + 0xbc);
  for (puVar3 = (undefined4 *)*puVar4; puVar3 != puVar4; puVar3 = (undefined4 *)*puVar3) {
    bVar1 = *(byte *)((int)puVar3 + -5);
    if ((bVar1 & 1) == 0) {
      for (puVar6 = (undefined4 *)puVar3[0x22]; puVar6 != puVar3 + 0x22;
          puVar6 = (undefined4 *)*puVar6) {
        (*(code *)puVar6[2])(puVar6 + -2);
      }
      for (iVar5 = puVar3[0x24]; iVar5 != 0; iVar5 = *(int *)(iVar5 + 0x9c)) {
        for (puVar6 = *(undefined4 **)(iVar5 + 0x90); puVar6 != (undefined4 *)(iVar5 + 0x90);
            puVar6 = (undefined4 *)*puVar6) {
          (*(code *)puVar6[2])(puVar6 + -2);
        }
        *(byte *)(iVar5 + 3) = *(byte *)(iVar5 + 3) & 0xf7;
        FUN_00809780(*(undefined4 *)(iVar5 + 0x98));
      }
    }
    else {
      if ((bVar1 & 4) != 0) {
        puVar6 = puVar3 + 2;
        puVar7 = puVar3 + 0x12;
        for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar7 = *puVar6;
          puVar6 = puVar6 + 1;
          puVar7 = puVar7 + 1;
        }
      }
      for (puVar6 = (undefined4 *)puVar3[0x22]; puVar6 != puVar3 + 0x22;
          puVar6 = (undefined4 *)*puVar6) {
        (*(code *)puVar6[2])(puVar6 + -2);
      }
      for (iVar5 = puVar3[0x24]; iVar5 != 0; iVar5 = *(int *)(iVar5 + 0x9c)) {
        bVar2 = *(byte *)(iVar5 + 3);
        if ((bVar2 & 4) != 0 || (bVar1 & 4) != 0) {
          FUN_007f18b0(iVar5 + 0x50,iVar5 + 0x10,*(int *)(iVar5 + 4) + 0x50);
        }
        for (puVar6 = *(undefined4 **)(iVar5 + 0x90); puVar6 != (undefined4 *)(iVar5 + 0x90);
            puVar6 = (undefined4 *)*puVar6) {
          (*(code *)puVar6[2])(puVar6 + -2);
        }
        *(byte *)(iVar5 + 3) = *(byte *)(iVar5 + 3) & 0xf3;
        FUN_00809700(*(undefined4 *)(iVar5 + 0x98),bVar2 | bVar1 & 4);
      }
    }
    *(byte *)((int)puVar3 + -5) = bVar1 & 0xf0;
  }
  *(int *)(DAT_00c97b24 + 0xbc) = DAT_00c97b24 + 0xbc;
  *(int *)(DAT_00c97b24 + 0xc0) = DAT_00c97b24 + 0xbc;
  return 1;
}



/* entry 0x0080AA80; bounded CFG instructions=160; body bytes=784 */

void FUN_0080aa80(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  byte bVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  byte *pbVar11;
  byte *pbVar12;
  uint uVar13;
  undefined4 *puVar14;
  int local_10;
  
  iVar3 = *(int *)(param_2 + 0x10);
  iVar6 = *(int *)(param_2 + 0x18);
  pbVar12 = *(byte **)(param_2 + 0x14);
  iVar7 = *(int *)(param_2 + 0xc);
  local_10 = *(int *)(param_2 + 8);
  if ((iVar7 == 4) || (iVar7 == 8)) {
    for (; local_10 != 0; local_10 = local_10 + -1) {
      pbVar11 = pbVar12;
      iVar8 = DAT_008e26e0;
      for (iVar7 = *(int *)(param_2 + 4); DAT_008e26e0 = iVar8, iVar7 != 0; iVar7 = iVar7 + -1) {
        iVar1 = iVar6 + (uint)*pbVar11 * 4;
        bVar4 = 8 - (char)iVar8;
        uVar13 = (((&DAT_00c9a730)[*(byte *)(iVar6 + (uint)*pbVar11 * 4) >> (bVar4 & 0x1f)] * 2 |
                  (&DAT_00c9a730)[*(byte *)(iVar1 + 1) >> (bVar4 & 0x1f)]) * 2 |
                 (&DAT_00c9a730)[*(byte *)(iVar1 + 2) >> (bVar4 & 0x1f)]) * 2 |
                 (&DAT_00c9a730)[*(byte *)(iVar1 + 3) >> (bVar4 & 0x1f)];
        iVar9 = *(int *)(param_1 + 0x4000);
        if (iVar8 != 0) {
          uVar10 = uVar13 & 0xf;
          puVar2 = (undefined4 *)(iVar9 + 0x1c + uVar10 * 4);
          if (*(int *)(iVar9 + 0x1c + uVar10 * 4) == 0) {
            puVar5 = (undefined4 *)
                     (**(code **)(DAT_00c97b24 + 0x144))(*(undefined4 *)(param_1 + 0x4004),0x30411);
            *puVar2 = puVar5;
            puVar14 = puVar5 + 7;
            for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
              *puVar14 = 0;
              puVar14 = puVar14 + 1;
            }
            if (iVar8 == 1) {
              *(undefined1 *)(puVar5 + 6) = 0;
              *puVar5 = 0;
              puVar5[1] = 0;
              puVar5[2] = 0;
              puVar5[3] = 0;
              puVar5[4] = 0;
              puVar5[5] = 0;
            }
          }
          iVar9 = FUN_0080aed0(param_1,*puVar2,uVar13 >> 4,iVar8 + -1);
        }
        FUN_0080ad90(iVar9,iVar1,param_3);
        pbVar11 = pbVar11 + 1;
        iVar8 = DAT_008e26e0;
      }
      pbVar12 = pbVar12 + iVar3;
    }
  }
  else if ((iVar7 == 0x20) && (local_10 != 0)) {
    pbVar12 = pbVar12 + 2;
    do {
      pbVar11 = pbVar12;
      iVar7 = DAT_008e26e0;
      for (iVar6 = *(int *)(param_2 + 4); DAT_008e26e0 = iVar7, iVar6 != 0; iVar6 = iVar6 + -1) {
        bVar4 = 8 - (char)iVar7;
        uVar13 = (((&DAT_00c9a730)[pbVar11[-2] >> (bVar4 & 0x1f)] * 2 |
                  (&DAT_00c9a730)[pbVar11[-1] >> (bVar4 & 0x1f)]) * 2 |
                 (&DAT_00c9a730)[*pbVar11 >> (bVar4 & 0x1f)]) * 2 |
                 (&DAT_00c9a730)[pbVar11[1] >> (bVar4 & 0x1f)];
        iVar8 = *(int *)(param_1 + 0x4000);
        if (iVar7 != 0) {
          uVar10 = uVar13 & 0xf;
          puVar2 = (undefined4 *)(iVar8 + 0x1c + uVar10 * 4);
          if (*(int *)(iVar8 + 0x1c + uVar10 * 4) == 0) {
            puVar5 = (undefined4 *)
                     (**(code **)(DAT_00c97b24 + 0x144))(*(undefined4 *)(param_1 + 0x4004),0x30411);
            *puVar2 = puVar5;
            puVar14 = puVar5 + 7;
            for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
              *puVar14 = 0;
              puVar14 = puVar14 + 1;
            }
            if (iVar7 == 1) {
              *(undefined1 *)(puVar5 + 6) = 0;
              *puVar5 = 0;
              puVar5[1] = 0;
              puVar5[2] = 0;
              puVar5[3] = 0;
              puVar5[4] = 0;
              puVar5[5] = 0;
            }
          }
          iVar8 = FUN_0080aed0(param_1,*puVar2,uVar13 >> 4,iVar7 + -1);
        }
        FUN_0080ad90(iVar8,pbVar11 + -2,param_3);
        pbVar11 = pbVar11 + 4;
        iVar7 = DAT_008e26e0;
      }
      pbVar12 = pbVar12 + iVar3;
      local_10 = local_10 + -1;
    } while (local_10 != 0);
    return;
  }
  return;
}



/* entry 0x0080AED0; bounded CFG instructions=52; body bytes=132 */

int FUN_0080aed0(int param_1,int param_2,uint param_3,int param_4)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  
  if (param_4 == 0) {
    return param_2;
  }
  do {
    piVar1 = (int *)(param_2 + 0x1c + (param_3 & 0xf) * 4);
    if (*piVar1 == 0) {
      puVar2 = (undefined4 *)
               (**(code **)(DAT_00c97b24 + 0x144))(*(undefined4 *)(param_1 + 0x4004),0x30411);
      *piVar1 = (int)puVar2;
      puVar4 = puVar2 + 7;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = 0;
        puVar4 = puVar4 + 1;
      }
      if (param_4 == 1) {
        *(undefined1 *)(puVar2 + 6) = 0;
        *puVar2 = 0;
        puVar2[1] = 0;
        puVar2[2] = 0;
        puVar2[3] = 0;
        puVar2[4] = 0;
        puVar2[5] = 0;
      }
    }
    param_2 = *piVar1;
    param_4 = param_4 + -1;
    param_3 = param_3 >> 4;
  } while (param_4 != 0);
  return param_2;
}



/* entry 0x0080C470; bounded CFG instructions=62; body bytes=176 */

undefined4 FUN_0080c470(int param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  undefined4 *puVar10;
  
  uVar1 = DAT_008e26e0;
  uVar2 = 1 << ((byte)DAT_008e26e0 & 0x1f);
  uVar8 = 0;
  if (uVar2 != 0) {
    do {
      uVar7 = 0;
      uVar6 = 0;
      if (uVar1 != 0) {
        iVar9 = uVar1 * 4;
        do {
          iVar9 = iVar9 + -4;
          if ((uVar8 & 1 << ((byte)uVar6 & 0x1f)) == 0) {
            uVar3 = 0;
          }
          else {
            uVar3 = 1 << ((byte)iVar9 & 0x1f);
          }
          uVar7 = uVar7 | uVar3;
          uVar6 = uVar6 + 1;
        } while (uVar6 < uVar1);
      }
      (&DAT_00c9a730)[uVar8] = uVar7;
      uVar8 = uVar8 + 1;
    } while (uVar8 < uVar2);
  }
  uVar4 = FUN_00801980(0x5c,0x400,4,0x30411);
  *(undefined4 *)(param_1 + 0x4004) = uVar4;
  iVar9 = (**(code **)(DAT_00c97b24 + 0x144))(uVar4,0x30411);
  *(int *)(param_1 + 0x4000) = iVar9;
  puVar10 = (undefined4 *)(iVar9 + 0x1c);
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar10 = 0;
    puVar10 = puVar10 + 1;
  }
  return 1;
}



/* entry 0x0080EA40; bounded CFG instructions=69; body bytes=234 */

undefined4 * FUN_0080ea40(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 local_8;
  undefined4 local_4;
  
  if (param_1 == (undefined4 *)0x0) {
    local_8 = 1;
    local_4 = FUN_008088d0(0x80000016);
    FUN_00808820(&local_8);
    return (undefined4 *)0x0;
  }
  if (*(int *)(DAT_00c97b24 + 0x150) == 3) {
    puVar2 = (undefined4 *)(DAT_00c9bc60 + 4 + DAT_00c97b24);
    puVar3 = param_1;
    for (iVar1 = 0xb; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
    return param_1;
  }
  if (param_1 != (undefined4 *)(DAT_00c9bc60 + 4 + DAT_00c97b24)) {
    local_8 = 1;
    local_4 = FUN_008088d0(0x80000018);
    FUN_00808820(&local_8);
    return (undefined4 *)0x0;
  }
  param_1[4] = 0;
  param_1[1] = 2;
  param_1[7] = 2;
  param_1[9] = 0;
  *param_1 = 7;
  param_1[2] = 5;
  param_1[3] = 6;
  param_1[5] = 1;
  param_1[6] = 1;
  param_1[8] = 0xffffffff;
  param_1[10] = 0xffffffff;
  return param_1;
}



/* entry 0x00811C80; bounded CFG instructions=124; body bytes=356 */

int FUN_00811c80(uint param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  byte bVar4;
  undefined4 *puVar5;
  
  iVar1 = param_1;
  puVar2 = *(undefined4 **)(DAT_00c9ab74 + param_1);
  if (puVar2 == (undefined4 *)0x0) {
    puVar2 = (undefined4 *)(**(code **)(DAT_00c97b24 + 0x144))(DAT_00c9ab80,0x30120);
    if (puVar2 == (undefined4 *)0x0) {
      return 0;
    }
    puVar5 = puVar2;
    for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    *(undefined4 **)(DAT_00c9ab74 + param_1) = puVar2;
  }
  if ((param_2 == 0) || ((puVar2[0xc] != 0 && (puVar2[0xc] != param_2)))) {
    FUN_00810ca0(puVar2);
  }
  puVar2[0xc] = param_2;
  switch(param_2) {
  case 1:
    puVar2[5] = 1;
    return param_1;
  case 2:
    puVar2[5] = 2;
    return param_1;
  case 3:
    puVar2[5] = 1;
    puVar2[0xb] = 2;
    return param_1;
  case 4:
    bVar4 = 0;
    puVar2[5] = 4;
    param_1 = 0;
    iVar3 = *(int *)(DAT_00c9ab74 + iVar1);
    do {
      if (*(int *)(iVar3 + 0x14 + param_1 * 0x18) == 4) goto LAB_00811d69;
      bVar4 = bVar4 + 1;
      param_1 = (uint)bVar4;
    } while (bVar4 < 2);
    break;
  case 5:
    puVar2[5] = 5;
    return param_1;
  case 6:
    puVar2[5] = 5;
    puVar2[0xb] = 4;
    bVar4 = 0;
    iVar3 = *(int *)(DAT_00c9ab74 + param_1);
    param_1 = 0;
    do {
      if (*(int *)(iVar3 + 0x14 + param_1 * 0x18) == 4) goto LAB_00811d69;
      bVar4 = bVar4 + 1;
      param_1 = (uint)bVar4;
    } while (bVar4 < 2);
    break;
  default:
    goto switchD_00811cf9_default;
  }
  iVar3 = 0;
LAB_00811dbc:
  *(undefined4 *)(iVar3 + 8) = 6;
  *(undefined4 *)(iVar3 + 4) = 5;
  FUN_00816280(iVar3,10);
  FUN_00816280(iVar3,0xb);
switchD_00811cf9_default:
  return iVar1;
LAB_00811d69:
  iVar3 = iVar3 + param_1 * 0x18;
  goto LAB_00811dbc;
}



/* entry 0x008149E0; bounded CFG instructions=160; body bytes=4666 */

undefined4 FUN_008149e0(int param_1,int param_2)

{
  char cVar1;
  ushort uVar2;
  ushort uVar3;
  int *piVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int iVar8;
  int *piVar9;
  undefined4 *puVar10;
  uint uVar11;
  int iVar12;
  float *pfVar13;
  float unaff_EBX;
  float fVar14;
  float unaff_ESI;
  int iVar15;
  uint uVar16;
  float unaff_EDI;
  undefined4 *puVar17;
  uint uVar18;
  float fVar19;
  bool bVar20;
  float10 fVar21;
  float10 fVar22;
  float10 fVar23;
  float10 fVar24;
  int unaff_retaddr;
  uint uVar25;
  float fVar26;
  int iVar27;
  float fVar28;
  float local_1f0;
  float fStack_1ec;
  float fStack_1e8;
  float fStack_1e4;
  float fStack_1e0;
  float fStack_1dc;
  float fStack_1d8;
  float fStack_1d4;
  float fStack_1d0;
  float fStack_1cc;
  float fStack_1c8;
  float fStack_1c4;
  float fStack_1c0;
  float fStack_1bc;
  uint uStack_1b8;
  int iStack_1b4;
  float fStack_1b0;
  int iStack_1ac;
  undefined4 *puStack_1a8;
  float fStack_1a4;
  float fStack_1a0;
  float fStack_19c;
  float fStack_198;
  undefined4 *puStack_194;
  float local_190;
  float fStack_18c;
  float fStack_188;
  float fStack_184;
  int iStack_180;
  float fStack_17c;
  float fStack_178;
  float fStack_174;
  float local_170;
  float local_16c;
  float local_168;
  float fStack_164;
  float fStack_160;
  float fStack_15c;
  float fStack_158;
  float fStack_154;
  float fStack_150;
  float fStack_14c;
  float fStack_148;
  undefined4 uStack_144;
  float fStack_140;
  float fStack_13c;
  float fStack_138;
  float fStack_134;
  int local_130 [2];
  float fStack_128;
  float fStack_120;
  ushort auStack_11c [2];
  byte abStack_118 [8];
  undefined1 local_110 [144];
  undefined1 local_80 [64];
  undefined1 local_40 [36];
  int iStack_1c;
  int iStack_14;
  int iStack_8;
  float *pfStack_4;
  
  piVar4 = *(int **)(DAT_00c9ab74 + *(int *)(param_2 + 8));
  local_190 = (float)piVar4[4] * (float)piVar4[3];
  iVar8 = *piVar4;
  if (iVar8 == 0) {
    iVar8 = *(int *)(*DAT_00c97b24 + 4);
  }
  FUN_007fa4f0(0x100,local_40);
  FUN_007f2070(local_80,local_40);
  for (puVar10 = *(undefined4 **)(iVar8 + 0x90); puVar10 != (undefined4 *)(iVar8 + 0x90);
      puVar10 = (undefined4 *)*puVar10) {
    if (*(char *)(puVar10 + -2) == '\x03') {
      if ((puVar10 != (undefined4 *)&DAT_00000008) &&
         (((cVar1 = *(char *)((int)puVar10 + -7), cVar1 == '\x01' || (cVar1 == -0x7f)) ||
          (cVar1 == -0x7e)))) {
        iVar8 = FUN_007f0990(iVar8);
        local_170 = -*(float *)(iVar8 + 0x20);
        local_16c = -*(float *)(iVar8 + 0x24);
        local_168 = -*(float *)(iVar8 + 0x28);
        FUN_007eddc0(local_130,&local_170,local_80);
        goto LAB_00814a85;
      }
      break;
    }
  }
  iVar8 = FUN_007f0990(iVar8);
  FUN_007edd60(local_130,iVar8 + 0x30,local_80);
LAB_00814a85:
  (**(code **)(**(int **)(param_1 + 0x34) + 0x10))(*(int **)(param_1 + 0x34),local_110,&local_1f0);
  fVar26 = 0.0;
  do {
    piVar9 = (int *)(((int)fVar26 + 1) * 0x10 + param_1);
    local_130[(int)fVar26] = 0;
    piVar4 = (int *)*piVar9;
    if ((piVar4 != (int *)0x0) && ((*(ushort *)(piVar9 + 3) & 0xff6) != 0)) {
      (**(code **)(*piVar4 + 0x2c))
                (piVar4,(int)pfStack_4[1] * piVar9[2] + piVar9[1],(int)pfStack_4[6] * piVar9[2],
                 local_130 + (int)fVar26,0x800);
    }
    pfVar13 = pfStack_4;
    fVar26 = (float)((int)fVar26 + 1);
  } while ((int)fVar26 < 2);
  iVar8 = 0;
  while ((abStack_118[iVar8 * 8 + 2] != 0 || (abStack_118[iVar8 * 8 + 3] != 0))) {
    iVar8 = iVar8 + 1;
  }
  iStack_1ac = (uint)*(ushort *)(abStack_118 + iVar8 * 8 + -2) + local_130[auStack_11c[iVar8 * 4]];
  uStack_1b8 = (uint)abStack_118[iVar8 * 8];
  fStack_1d4 = *(float *)((uint)auStack_11c[iVar8 * 4] * 0x10 + 0x18 + param_1);
  for (iVar8 = 0;
      ((abStack_118[iVar8 * 8 + 2] != 3 || (abStack_118[iVar8 * 8 + 3] != 0)) &&
      (abStack_118[iVar8 * 8] != 0x11)); iVar8 = iVar8 + 1) {
  }
  if (abStack_118[iVar8 * 8] == 0x11) {
    fStack_1b0 = 0.0;
  }
  else {
    local_190 = (float)(uint)abStack_118[iVar8 * 8];
    fStack_1b0 = (float)((uint)*(ushort *)(abStack_118 + iVar8 * 8 + -2) +
                        local_130[auStack_11c[iVar8 * 4]]);
    fStack_198 = *(float *)((uint)auStack_11c[iVar8 * 4] * 0x10 + 0x18 + param_1);
  }
  fVar19 = fStack_1b0;
  for (iVar8 = 0;
      ((abStack_118[iVar8 * 8 + 2] != 10 || (abStack_118[iVar8 * 8 + 3] != 0)) &&
      (abStack_118[iVar8 * 8] != 0x11)); iVar8 = iVar8 + 1) {
  }
  if (abStack_118[iVar8 * 8] == 0x11) {
    local_170 = 0.0;
  }
  else {
    local_170 = (float)((uint)*(ushort *)(abStack_118 + iVar8 * 8 + -2) +
                       local_130[auStack_11c[iVar8 * 4]]);
    fStack_148 = *(float *)((uint)auStack_11c[iVar8 * 4] * 0x10 + 0x18 + param_1);
  }
  iVar8 = 0;
  while ((abStack_118[iVar8 * 8 + 2] != 5 || (abStack_118[iVar8 * 8 + 3] != 0))) {
    iVar8 = iVar8 + 1;
  }
  iVar12 = (uint)*(ushort *)(abStack_118 + iVar8 * 8 + -2) + local_130[auStack_11c[iVar8 * 4]];
  iStack_1b4 = *(int *)((uint)auStack_11c[iVar8 * 4] * 0x10 + 0x18 + param_1);
  fStack_1bc = (float)(uint)abStack_118[iVar8 * 8];
  for (iVar8 = 0;
      ((abStack_118[iVar8 * 8 + 2] != 6 || (abStack_118[iVar8 * 8 + 3] != 0)) &&
      (abStack_118[iVar8 * 8] != 0x11)); iVar8 = iVar8 + 1) {
  }
  iStack_180 = iVar12;
  if (abStack_118[iVar8 * 8] != 0x11) {
    puStack_194 = (undefined4 *)(uint)abStack_118[iVar8 * 8];
    iVar15 = (uint)*(ushort *)(abStack_118 + iVar8 * 8 + -2) + local_130[auStack_11c[iVar8 * 4]];
    iVar8 = *(int *)((uint)auStack_11c[iVar8 * 4] * 0x10 + 0x18 + param_1);
    if (iVar15 != 0) {
      iVar27 = 0;
      local_16c = pfStack_4[6];
      if (0 < (int)local_16c) {
        do {
          if (uStack_1b8 == 2) {
            pfVar13 = (float *)((int)fStack_1d4 * iVar27 + iStack_1ac);
            fStack_1e0 = *pfVar13;
            fStack_1dc = pfVar13[1];
            fStack_1d8 = pfVar13[2];
          }
          else {
            FUN_007551f0(uStack_1b8,&fStack_1e0,(int)fStack_1d4 * iVar27 + iStack_1ac);
          }
          if (fStack_1bc == 1.4013e-45) {
            fStack_1d0 = *(float *)(iStack_1b4 * iVar27 + iVar12);
            fStack_1cc = *(float *)(iStack_1b4 * iVar27 + 4 + iVar12);
          }
          else {
            FUN_007555e0(fStack_1bc,&fStack_1d0,iStack_1b4 * iVar27 + iVar12);
          }
          if (fVar19 == 0.0) {
            unaff_EBX = 0.0;
            unaff_ESI = 0.0;
            local_1f0 = 0.0;
          }
          else if (local_190 == 2.8026e-45) {
            pfVar13 = (float *)((int)fStack_198 * iVar27 + (int)fVar19);
            unaff_EBX = *pfVar13;
            unaff_ESI = pfVar13[1];
            local_1f0 = pfVar13[2];
          }
          else {
            FUN_007551f0(local_190,&stack0xfffffe08,(int)fStack_198 * iVar27 + (int)fVar19);
          }
          if (puStack_194 == (undefined4 *)0x2) {
            pfVar13 = (float *)(iVar8 * iVar27 + iVar15);
            fStack_1ec = *pfVar13;
            fStack_1e8 = pfVar13[1];
            fStack_1e4 = pfVar13[2];
          }
          else {
            FUN_007551f0(puStack_194,&fStack_1ec,iVar8 * iVar27 + iVar15);
          }
          fStack_1c8 = fStack_13c - fStack_1e0;
          fStack_1c4 = fStack_138 - fStack_1dc;
          fStack_1c0 = fStack_134 - fStack_1d8;
          fVar21 = (float10)FUN_007edb90(fStack_1c0 * fStack_1c0 +
                                         fStack_1c8 * fStack_1c8 + fStack_1c4 * fStack_1c4);
          fStack_120 = fStack_1ec * unaff_ESI - fStack_1e8 * unaff_EBX;
          fStack_1a4 = (float)((float10)fStack_1e4 * fVar21 * (float10)fStack_1c0 +
                              (float10)fStack_1ec * (float10)fStack_1c8 * fVar21 +
                              (float10)fStack_1e8 * fVar21 * (float10)fStack_1c4);
          pfVar13 = (float *)(unaff_retaddr + iVar27 * 0x2c);
          *pfVar13 = fStack_1e0;
          pfVar13[1] = fStack_1dc;
          pfVar13[2] = fStack_1d8;
          fStack_1a0 = (float)((float10)fStack_120 * fVar21 * (float10)fStack_1c0 +
                              ((float10)fStack_1e8 * (float10)local_1f0 -
                              (float10)fStack_1e4 * (float10)unaff_ESI) *
                              (float10)fStack_1c8 * fVar21 +
                              ((float10)fStack_1e4 * (float10)unaff_EBX -
                              (float10)fStack_1ec * (float10)local_1f0) *
                              fVar21 * (float10)fStack_1c4);
          if (fVar19 == 0.0) {
            fVar26 = 0.0;
            pfVar13[3] = 0.0;
            pfVar13[4] = 0.0;
          }
          else {
            pfVar13[3] = unaff_EBX;
            pfVar13[4] = unaff_ESI;
            fVar26 = local_1f0;
          }
          pfVar13[5] = fVar26;
          if (local_170 == 0.0) {
            pfVar13[6] = -NAN;
          }
          else {
            pfVar13[6] = *(float *)((int)fStack_148 * iVar27 + (int)local_170);
          }
          pfVar13[7] = fStack_1d0;
          pfVar13[8] = fStack_1cc;
          pfVar13[9] = fStack_1a4 * fStack_19c + fStack_1d0;
          pfVar13[10] = fStack_1a0 * fStack_19c + fStack_1cc;
          iVar27 = iVar27 + 1;
        } while (iVar27 < (int)local_16c);
      }
      goto LAB_00815bd7;
    }
  }
  if (*(int *)(param_1 + 8) == 0) {
    fVar28 = 0.0;
    fVar14 = pfStack_4[6];
    fVar26 = fVar14;
    fVar19 = fVar14;
    fStack_1a4 = fVar14;
    if (0 < (int)fVar14) {
      do {
        if (*(int *)(iStack_8 + 0xc) == 4) {
          iVar8 = ((int)fVar28 / 3) * 3;
          fVar26 = (float)(((int)fVar28 + 1) % 3 + iVar8);
          fVar19 = (float)(((int)fVar28 + 2) % 3 + iVar8);
          fVar14 = fVar28;
          iVar12 = iStack_180;
        }
        else if (*(int *)(iStack_8 + 0xc) == 5) {
          if ((int)fVar28 < 2) {
            uVar11 = (uint)fVar28 & 0x80000001;
            bVar20 = uVar11 == 0;
            if ((int)uVar11 < 0) {
              bVar20 = (uVar11 - 1 | 0xfffffffe) == 0xffffffff;
            }
            if (bVar20) {
              fVar26 = (float)((int)fVar28 + 1);
              fVar19 = (float)((int)fVar28 + 2);
              fVar14 = fVar28;
            }
            else {
              fVar26 = (float)((int)fVar28 + 2);
              fVar19 = (float)((int)fVar28 + 1);
              fVar14 = fVar28;
            }
          }
          else {
            uVar11 = (uint)fVar28 & 0x80000001;
            bVar20 = uVar11 == 0;
            if ((int)uVar11 < 0) {
              bVar20 = (uVar11 - 1 | 0xfffffffe) == 0xffffffff;
            }
            if (bVar20) {
              fVar26 = (float)((int)fVar28 + -2);
              fVar19 = (float)((int)fVar28 + -1);
              fVar14 = fVar28;
            }
            else {
              fVar26 = (float)((int)fVar28 + -1);
              fVar19 = (float)((int)fVar28 + -2);
              fVar14 = fVar28;
            }
          }
        }
        if (uStack_1b8 == 2) {
          pfVar13 = (float *)((int)fVar14 * (int)fStack_1d4 + iStack_1ac);
          fStack_1e0 = *pfVar13;
          fStack_1dc = pfVar13[1];
          fStack_1d8 = pfVar13[2];
          pfVar13 = (float *)((int)fVar26 * (int)fStack_1d4 + iStack_1ac);
          local_168 = *pfVar13;
          fStack_164 = pfVar13[1];
          fStack_160 = pfVar13[2];
          pfVar13 = (float *)((int)fVar19 * (int)fStack_1d4 + iStack_1ac);
          fStack_15c = *pfVar13;
          fStack_158 = pfVar13[1];
          fStack_154 = pfVar13[2];
        }
        else {
          FUN_007551f0(uStack_1b8,&fStack_1e0,(int)fVar14 * (int)fStack_1d4 + iStack_1ac);
          FUN_007551f0(uStack_1b8,&local_168,(int)fVar26 * (int)fStack_1d4 + iStack_1ac);
          FUN_007551f0(uStack_1b8,&fStack_15c,(int)fVar19 * (int)fStack_1d4 + iStack_1ac);
        }
        if (fStack_1bc == 1.4013e-45) {
          fStack_1d0 = *(float *)((int)fVar14 * iStack_1b4 + iVar12);
          fStack_1cc = *(float *)((int)fVar14 * iStack_1b4 + 4 + iVar12);
          fStack_150 = *(float *)((int)fVar26 * iStack_1b4 + iVar12);
          fStack_14c = *(float *)((int)fVar26 * iStack_1b4 + 4 + iVar12);
          uStack_144 = *(undefined4 *)((int)fVar19 * iStack_1b4 + iVar12);
          fStack_140 = *(float *)((int)fVar19 * iStack_1b4 + 4 + iVar12);
        }
        else {
          FUN_007555e0(fStack_1bc,&fStack_1d0,(int)fVar14 * iStack_1b4 + iVar12);
          FUN_007555e0(fStack_1bc,&fStack_150,(int)fVar26 * iStack_1b4 + iVar12);
          FUN_007555e0(fStack_1bc,&uStack_144,(int)fVar19 * iStack_1b4 + iVar12);
        }
        if (fStack_1b0 == 0.0) {
          fStack_1ec = 0.0;
          fStack_1e8 = 0.0;
          fStack_1e4 = 0.0;
        }
        else if (local_190 == 2.8026e-45) {
          pfVar13 = (float *)((int)fVar14 * (int)fStack_198 + (int)fStack_1b0);
          fStack_1ec = *pfVar13;
          fStack_1e8 = pfVar13[1];
          fStack_1e4 = pfVar13[2];
        }
        else {
          FUN_007551f0(local_190,&fStack_1ec,(int)fVar14 * (int)fStack_198 + (int)fStack_1b0);
        }
        fVar5 = fStack_13c - fStack_1e0;
        fVar6 = fStack_138 - fStack_1dc;
        local_1f0 = fStack_134 - fStack_1d8;
        fVar21 = (float10)FUN_007edb90(local_1f0 * local_1f0 + fVar5 * fVar5 + fVar6 * fVar6);
        local_1f0 = (float)(fVar21 * (float10)local_1f0);
        fStack_120 = fStack_160 - fStack_1d8;
        fStack_18c = fStack_15c - fStack_1e0;
        puStack_1a8 = (undefined4 *)(fStack_140 - fStack_1cc);
        fStack_128 = (local_168 - fStack_1e0) * (float)puStack_1a8;
        fVar7 = fStack_14c - fStack_1cc;
        fStack_188 = (fStack_158 - fStack_1dc) * fVar7;
        fStack_184 = (fStack_154 - fStack_1d8) * fVar7;
        fStack_1c8 = fStack_128 - fStack_18c * fVar7;
        fStack_1c4 = (fStack_164 - fStack_1dc) * (float)puStack_1a8 - fStack_188;
        fStack_1c0 = fStack_120 * (float)puStack_1a8 - fStack_184;
        fVar24 = (float10)FUN_007edb90(fStack_1c0 * fStack_1c0 +
                                       fStack_1c8 * fStack_1c8 + fStack_1c4 * fStack_1c4);
        fVar23 = (float10)fStack_1c8 * fVar24;
        fVar22 = (float10)fStack_1c4 * fVar24;
        fVar24 = (float10)fStack_1c0 * fVar24;
        fStack_17c = (float)(fVar22 * (float10)fStack_1e4 - fVar24 * (float10)fStack_1e8);
        fStack_178 = (float)((float10)fStack_1ec * fVar24 - fVar23 * (float10)fStack_1e4);
        fStack_174 = (float)(fVar23 * (float10)fStack_1e8 - fVar22 * (float10)fStack_1ec);
        pfVar13 = (float *)(unaff_retaddr + (int)fVar14 * 0x2c);
        *pfVar13 = fStack_1e0;
        pfVar13[1] = fStack_1dc;
        pfVar13[2] = fStack_1d8;
        if (fStack_1b0 == 0.0) {
          pfVar13[3] = 0.0;
          pfVar13[4] = 0.0;
          pfVar13[5] = 0.0;
        }
        else {
          pfVar13[3] = fStack_1ec;
          pfVar13[4] = fStack_1e8;
          pfVar13[5] = fStack_1e4;
        }
        if (local_170 == 0.0) {
          pfVar13[6] = -NAN;
        }
        else {
          pfVar13[6] = *(float *)((int)fVar14 * (int)fStack_148 + (int)local_170);
        }
        pfVar13[7] = fStack_1d0;
        pfVar13[8] = fStack_1cc;
        pfVar13[9] = (float)((float10)fStack_1d0 -
                            (fVar24 * (float10)local_1f0 +
                            fVar23 * (float10)(float)((float10)fVar5 * fVar21) +
                            fVar22 * (float10)(float)((float10)fVar6 * fVar21)) *
                            (float10)fStack_19c);
        pfVar13[10] = fStack_1cc -
                      (fStack_174 * local_1f0 +
                      fStack_17c * (float)((float10)fVar5 * fVar21) +
                      fStack_178 * (float)((float10)fVar6 * fVar21)) * fStack_19c;
        fVar28 = (float)((int)fVar28 + 1);
      } while ((int)fVar28 < (int)fStack_1a4);
    }
  }
  else {
    puVar10 = (undefined4 *)(*(code *)DAT_00c97b24[0x4d])(pfStack_4[6],0x30120);
    fVar19 = pfVar13[6];
    puVar17 = puVar10;
    for (uVar11 = (uint)fVar19 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
      *puVar17 = 0;
      puVar17 = puVar17 + 1;
    }
    for (uVar11 = (uint)fVar19 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
      *(undefined1 *)puVar17 = 0;
      puVar17 = (undefined4 *)((int)puVar17 + 1);
    }
    fVar19 = *pfVar13;
    fStack_1a4 = fVar19;
    puStack_194 = puVar10;
    (**(code **)(**(int **)(param_1 + 8) + 0x2c))
              (*(int **)(param_1 + 8),(int)pfStack_4[7] * 2,(int)fVar19 * 2,&local_16c,0x800);
    uVar25 = 0;
    iVar8 = iStack_180;
    uVar11 = uStack_1b8;
    uVar16 = uStack_1b8;
    uVar18 = uStack_1b8;
    if (0 < (int)fVar19) {
      do {
        fVar19 = fStack_1c0;
        if (*(char *)((uint)*(ushort *)(iVar8 + uVar25 * 2) + (int)puStack_1a8) == '\0') {
          if (*(int *)(iStack_1c + 0xc) == 4) {
            uVar2 = *(ushort *)(iVar8 + uVar25 * 2);
            iVar15 = ((int)uVar25 / 3) * 3;
            uVar3 = *(ushort *)(iVar8 + ((int)(uVar25 + 1) % 3 + iVar15) * 2);
            iVar15 = (int)(uVar25 + 2) % 3 + iVar15;
LAB_0081519b:
            uVar18 = (uint)uVar3;
            uVar16 = (uint)uVar2;
            uVar11 = (uint)*(ushort *)(iVar8 + iVar15 * 2);
          }
          else if (*(int *)(iStack_1c + 0xc) == 5) {
            if ((int)uVar25 < 2) {
              uVar11 = uVar25 & 0x80000001;
              bVar20 = uVar11 == 0;
              if ((int)uVar11 < 0) {
                bVar20 = (uVar11 - 1 | 0xfffffffe) == 0xffffffff;
              }
              if (bVar20) {
                iVar12 = uVar25 + 1;
                iVar15 = uVar25 + 2;
              }
              else {
                iVar12 = uVar25 + 2;
                iVar15 = uVar25 + 1;
              }
            }
            else {
              uVar11 = uVar25 & 0x80000001;
              bVar20 = uVar11 == 0;
              if ((int)uVar11 < 0) {
                bVar20 = (uVar11 - 1 | 0xfffffffe) == 0xffffffff;
              }
              if (bVar20) {
                iVar12 = uVar25 - 2;
                iVar15 = uVar25 - 1;
              }
              else {
                iVar12 = uVar25 - 1;
                iVar15 = uVar25 - 2;
              }
            }
            uVar2 = *(ushort *)(iVar8 + uVar25 * 2);
            uVar3 = *(ushort *)(iVar8 + iVar12 * 2);
            goto LAB_0081519b;
          }
          if (fStack_1cc == 2.8026e-45) {
            pfVar13 = (float *)(uVar16 * (int)fStack_1e8 + (int)fStack_1c0);
            unaff_ESI = *pfVar13;
            local_1f0 = pfVar13[1];
            fStack_1ec = pfVar13[2];
            pfVar13 = (float *)(uVar18 * (int)fStack_1e8 + (int)fStack_1c0);
            fStack_17c = *pfVar13;
            fStack_178 = pfVar13[1];
            fStack_174 = pfVar13[2];
            pfVar13 = (float *)(uVar11 * (int)fStack_1e8 + (int)fStack_1c0);
            local_170 = *pfVar13;
            local_16c = pfVar13[1];
            local_168 = pfVar13[2];
          }
          else {
            FUN_007551f0(fStack_1cc,&stack0xfffffe0c,uVar16 * (int)fStack_1e8 + (int)fStack_1c0);
            FUN_007551f0(fStack_1cc,&fStack_17c,uVar18 * (int)fStack_1e8 + (int)fVar19);
            FUN_007551f0(fStack_1cc,&local_170,uVar11 * (int)fStack_1e8 + (int)fVar19);
          }
          puVar10 = puStack_194;
          if (fStack_1d0 == 1.4013e-45) {
            fStack_1e4 = *(float *)(uVar16 * (int)fStack_1c8 + (int)puStack_194);
            fStack_1e0 = *(float *)(uVar16 * (int)fStack_1c8 + 4 + (int)puStack_194);
            fStack_164 = *(float *)(uVar18 * (int)fStack_1c8 + (int)puStack_194);
            fStack_160 = *(float *)(uVar18 * (int)fStack_1c8 + 4 + (int)puStack_194);
            fStack_158 = *(float *)(uVar11 * (int)fStack_1c8 + (int)puStack_194);
            fStack_154 = *(float *)(uVar11 * (int)fStack_1c8 + 4 + (int)puStack_194);
          }
          else {
            FUN_007555e0(fStack_1d0,&fStack_1e4,
                         (undefined4 *)(uVar16 * (int)fStack_1c8 + (int)puStack_194));
            FUN_007555e0(fStack_1d0,&fStack_164,
                         (undefined4 *)(uVar18 * (int)fStack_1c8 + (int)puVar10));
            FUN_007555e0(fStack_1d0,&fStack_158,
                         (undefined4 *)(uVar11 * (int)fStack_1c8 + (int)puVar10));
          }
          if (fStack_1c4 == 0.0) {
            unaff_EDI = 0.0;
            fVar26 = 0.0;
            unaff_EBX = 0.0;
          }
          else if (fStack_1a4 == 2.8026e-45) {
            pfVar13 = (float *)(uVar16 * iStack_1ac + (int)fStack_1c4);
            unaff_EDI = *pfVar13;
            fVar26 = pfVar13[1];
            unaff_EBX = pfVar13[2];
          }
          else {
            FUN_007551f0(fStack_1a4,&stack0xfffffe00,uVar16 * iStack_1ac + (int)fStack_1c4);
          }
          fVar19 = fStack_150 - unaff_ESI;
          fVar14 = fStack_14c - local_1f0;
          fVar28 = fStack_148 - fStack_1ec;
          fVar21 = (float10)FUN_007edb90(fVar28 * fVar28 + fVar19 * fVar19 + fVar14 * fVar14);
          fVar19 = (float)((float10)fVar19 * fVar21);
          fVar14 = (float)((float10)fVar14 * fVar21);
          fVar28 = (float)(fVar21 * (float10)fVar28);
          fStack_134 = fStack_174 - fStack_1ec;
          fStack_1a0 = local_170 - unaff_ESI;
          fStack_1bc = fStack_154 - fStack_1e0;
          fStack_13c = (fStack_17c - unaff_ESI) * fStack_1bc;
          fVar5 = fStack_160 - fStack_1e0;
          fStack_19c = (local_16c - local_1f0) * fVar5;
          fStack_198 = (local_168 - fStack_1ec) * fVar5;
          fStack_1dc = fStack_13c - fStack_1a0 * fVar5;
          fStack_1d8 = (fStack_178 - local_1f0) * fStack_1bc - fStack_19c;
          fStack_1d4 = fStack_134 * fStack_1bc - fStack_198;
          fVar22 = (float10)FUN_007edb90(fStack_1d4 * fStack_1d4 +
                                         fStack_1dc * fStack_1dc + fStack_1d8 * fStack_1d8);
          fVar21 = (float10)fStack_1dc * fVar22;
          fVar23 = (float10)fStack_1d8 * fVar22;
          fVar22 = (float10)fStack_1d4 * fVar22;
          local_190 = (float)(fVar23 * (float10)unaff_EBX - fVar22 * (float10)fVar26);
          fStack_18c = (float)((float10)unaff_EDI * fVar22 - fVar21 * (float10)unaff_EBX);
          fStack_188 = (float)(fVar21 * (float10)fVar26 - fVar23 * (float10)unaff_EDI);
          pfVar13 = (float *)(iStack_14 + uVar16 * 0x2c);
          *pfVar13 = unaff_ESI;
          pfVar13[1] = local_1f0;
          pfVar13[2] = fStack_1ec;
          if (fStack_1c4 == 0.0) {
            pfVar13[3] = 0.0;
            pfVar13[4] = 0.0;
            pfVar13[5] = 0.0;
          }
          else {
            pfVar13[3] = unaff_EDI;
            pfVar13[4] = fVar26;
            pfVar13[5] = unaff_EBX;
          }
          if (fStack_184 == 0.0) {
            pfVar13[6] = -NAN;
          }
          else {
            pfVar13[6] = *(float *)(uVar16 * (int)fStack_15c + (int)fStack_184);
          }
          pfVar13[7] = fStack_1e4;
          pfVar13[8] = fStack_1e0;
          pfVar13[9] = (float)((float10)fStack_1e4 -
                              (fVar22 * (float10)fVar28 +
                              fVar21 * (float10)fVar19 + fVar23 * (float10)fVar14) *
                              (float10)fStack_1b0);
          pfVar13[10] = fStack_1e0 -
                        (fStack_188 * fVar28 + local_190 * fVar19 + fStack_18c * fVar14) *
                        fStack_1b0;
          *(undefined1 *)(uVar16 + (int)puStack_1a8) = 1;
          iVar8 = iStack_180;
        }
        uVar25 = uVar25 + 1;
        puVar10 = puStack_1a8;
        param_1 = iStack_1c;
      } while ((int)uVar25 < (int)uStack_1b8);
    }
    (**(code **)(**(int **)(param_1 + 8) + 0x30))(*(int **)(param_1 + 8));
    (*(code *)DAT_00c97b24[0x4e])(puVar10);
  }
LAB_00815bd7:
  iVar8 = 0;
  do {
    if (local_130[iVar8] != 0) {
      piVar4 = *(int **)((iVar8 + 1) * 0x10 + iStack_8);
      (**(code **)(*piVar4 + 0x30))(piVar4);
    }
    iVar8 = iVar8 + 1;
  } while (iVar8 < 2);
  return 1;
}


