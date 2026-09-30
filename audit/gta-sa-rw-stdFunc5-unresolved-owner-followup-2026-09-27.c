/* Full-analysis function mapping; decompilation is not original source. */

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



/* function 00403caf FUN_00403caf */

void FUN_00403caf(void)

{
  FUN_005fc4c0();
  return;
}



/* function 006c4197 FUN_006c4197 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * __thiscall
FUN_006c4197(undefined4 *param_1,undefined4 param_2,undefined4 param_3,int param_4,
            undefined4 param_5)

{
  undefined4 *puVar1;
  int iVar2;
  void *unaff_ESI;
  void *pvStack_4;
  
  pvStack_4 = ExceptionList;
  ExceptionList = &pvStack_4;
  FUN_006b0a90(param_4,param_5,1);
  *param_1 = &PTR_FUN_00871680;
  param_1[0x165] = 3;
  param_1[0x263] = 0;
  param_1[0x264] = 0;
  param_1[0x265] = 0;
  param_1[0x266] = 0;
  param_1[0x267] = 0;
  param_1[0x268] = 0;
  param_1[0x269] = 0;
  param_1[0x26c] = 0x41200000;
  param_1[0x26a] = 0x41200000;
  param_1[0x26b] = 0x41200000;
  param_1[0x26d] = 0;
  *(byte *)(param_1 + 0x262) = *(byte *)(param_1 + 0x262) & 0xfc;
  param_1[0x280] = 0;
  param_1[0x10] = param_1[0x10] | 0x1000000;
  if (param_4 == 0x1a9) {
    FUN_006c21c0(2,0);
    param_1[0x17a] = 0x3f71463b;
    param_1[0x17b] = 0;
    *(undefined1 *)((int)param_1 + 0x5f2) = 1;
    *(undefined2 *)(param_1 + 0x17c) = 0x13;
  }
  *(undefined1 *)((int)param_1 + 0x9b9) = 4;
  *(undefined4 *)((int)param_1 + 0x9ba) = 0;
  param_1[0x27c] = DAT_00b7cb84;
  puVar1 = param_1 + 0x276;
  iVar2 = 6;
  do {
    puVar1[-6] = 0;
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  param_1[0x281] = 0;
  param_1[0x282] = DAT_00b7cb84;
  *(byte *)(param_1 + 0x10b) = *(byte *)(param_1 + 0x10b) | 0x40;
  *(undefined1 *)((int)param_1 + 0x3df) = 10;
  param_1[0x283] = 0;
  *(undefined1 *)(param_1 + 0x284) = 0x10;
  *(undefined1 *)(param_1 + 0x26e) = 0;
  *(undefined1 *)((int)param_1 + 0xa11) = 0;
  iVar2 = _rand();
  param_1[0x285] = (float)iVar2 * _DAT_00858c7c * _DAT_00858b44 + _FUN_00858ca0;
  ExceptionList = unaff_ESI;
  return param_1;
}



/* function 0053e920 FUN_0053e920 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0053e920(int param_1)

{
  char cVar1;
  undefined2 uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  float10 fVar6;
  undefined2 uVar7;
  undefined2 uVar8;
  float fStack_8;
  float fStack_4;
  
  FUN_00561a80();
  FUN_00561a40();
  do {
    uVar3 = FUN_00561a80();
    uVar4 = FUN_00561a40();
  } while (uVar3 / uVar4 - _DAT_00b72ca8 < 0xe);
  uVar3 = FUN_00561a80();
  _DAT_00b72ca8 = FUN_00561a40();
  _DAT_00b72ca8 = uVar3 / _DAT_00b72ca8;
  FUN_00561b10();
  FUN_00727350();
  FUN_00719800();
  DAT_00c3f0d0 = 0;
  FUN_0053bee0();
  FUN_00507750();
  FUN_007354e0(DAT_00c17038);
  if (param_1 != 0) {
    if ((DAT_00ba67a4 == '\0') && (iVar5 = FUN_0050ae20(), iVar5 != 2)) {
      fStack_8 = (float)DAT_00c17044 * _DAT_00858b8c;
      fStack_4 = (float)DAT_00c17048 * _DAT_00858b8c;
      thunk_FUN_007453f0(&fStack_8);
      FUN_005556e0();
      FUN_00553910();
      FUN_00563430();
      FUN_00706ab0();
      FUN_00727140();
      uVar8 = DAT_00b7c4c8;
      uVar7 = DAT_00b7c4c6;
      uVar2 = DAT_00b7c4c4;
      if (DAT_00c812cc != '\0') {
        DAT_00b7c4ca = 0xff;
        DAT_00b7c4cc = 0xff;
        DAT_00b7c4ce = 0xff;
        uVar8 = 0xff;
        uVar7 = 0xff;
        uVar2 = 0xff;
      }
      cVar1 = FUN_0053d7a0(uVar2,uVar7,uVar8,DAT_00b7c4ca,DAT_00b7c4cc,DAT_00b7c4ce,0xff);
      if (cVar1 == '\0') {
        return;
      }
      FUN_00734650();
      FUN_007ee2a0(DAT_00c1703c,DAT_00b7c4f0);
      *(undefined4 *)(DAT_00c1703c + 0x88) = _DAT_00b7c4f4;
      FUN_00726090();
      FUN_0053df40();
      FUN_00732f30();
      FUN_0053e8d0();
      FUN_0053e170();
      if (((DAT_00b6f0b8 == 0) || (DAT_00b6f0b8 == 2)) && (DAT_00858b50 < _DAT_00b6f16c)) {
        FUN_0050bf80(0x96);
      }
      FUN_0050b8f0();
      FUN_0053e230();
    }
    else {
      FUN_006ff420();
      fVar6 = (float10)fptan((float10)DAT_008d5038 * (float10)_DAT_008631d4);
      FUN_0072fc70(DAT_00c1703c,0,(float)fVar6,DAT_00c3efa4);
      FUN_007328c0(DAT_00c1703c);
      FUN_007ee340(DAT_00c1703c,&DAT_00b72ca0,2);
      iVar5 = thunk_FUN_00745210(DAT_00c1703c);
      if (iVar5 == 0) {
        return;
      }
    }
    if (DAT_00ba67a4 != '\0') {
      FUN_0057c290();
    }
    (**(code **)(DAT_00c97b24 + 0x20))(1,0);
    FUN_0053e600();
    FUN_0058d490();
    FUN_0069efc0(0);
    thunk_FUN_00719840();
    if (DAT_00c6e97c != '\0') {
      if (DAT_00ba67a4 == '\0') {
        FUN_005a87f0();
      }
      if ((DAT_00c6e97c != '\0') && (DAT_00ba67a4 == '\0')) {
        FUN_005a87f0();
      }
    }
    FUN_00532260();
    FUN_00734640();
    FUN_007ee180(DAT_00c1703c);
    thunk_FUN_00745240(DAT_00c1703c);
  }
  return;
}


