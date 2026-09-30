/* Full-analysis function mapping; decompilation is not original source. */

/* function 004c75e0 FUN_004c75e0 */

undefined4 * __fastcall FUN_004c75e0(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  FUN_004c4a60();
  param_1[0x17] = 0;
  *(undefined1 *)(param_1 + 0xb4) = 0;
  *(undefined1 *)((int)param_1 + 0x4e) = 0;
  *param_1 = &PTR_FUN_0085c5c8;
  param_1[0xc1] = 0xffffffff;
  puVar2 = (undefined4 *)((int)param_1 + 0x2d6);
  for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0xffffffff;
    puVar2 = puVar2 + 1;
  }
  *(undefined4 *)((int)param_1 + 0x2fa) = 0xffffffff;
  *(undefined4 *)((int)param_1 + 0x2fe) = 0xffffffff;
  return param_1;
}



/* function 004c95c0 FUN_004c95c0 */

void __thiscall FUN_004c95c0(int param_1,undefined4 param_2)

{
  void *pvVar1;
  undefined4 uVar2;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0083bc6b;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  pvVar1 = (void *)FUN_004c94c0();
  local_4 = 0;
  if (pvVar1 == (void *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_004c8d60();
  }
  *(undefined4 *)(param_1 + 0x5c) = uVar2;
  local_4 = 0xffffffff;
  FUN_004c4f70(param_2);
  FUN_004c7b10();
  FUN_004c5460((&PTR_PTR_008a7740)[*(int *)(param_1 + 0x3c)]);
  FUN_004c8900();
  FUN_004c8e60();
  FUN_004c8bd0();
  *(undefined1 *)(param_1 + 0x2d2) = 0xff;
  *(undefined1 *)(param_1 + 0x2d3) = 0xff;
  *(undefined1 *)(param_1 + 0x2d4) = 0xff;
  *(undefined1 *)(param_1 + 0x2d5) = 0xff;
  FUN_004c9450();
  ExceptionList = pvVar1;
  return;
}



/* function 004c9890 FUN_004c9890 */

void __fastcall FUN_004c9890(int param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = *(int *)(param_1 + 0x5c);
  if (iVar1 != 0) {
    FUN_004c7410();
    piVar2 = DAT_00b4e680;
    iVar1 = (iVar1 - *DAT_00b4e680) / 0x314;
    *(byte *)(DAT_00b4e680[1] + iVar1) = *(byte *)(DAT_00b4e680[1] + iVar1) | 0x80;
    if (iVar1 < piVar2[3]) {
      piVar2[3] = iVar1;
    }
    *(undefined4 *)(param_1 + 0x5c) = 0;
  }
  FUN_004c4e70();
  return;
}



/* function 0063c670 FUN_0063c670 */

byte __thiscall FUN_0063c670(int param_1,int param_2,int param_3)

{
  char cVar1;
  undefined4 uVar2;
  void *pvStack_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_00841858;
  local_c = ExceptionList;
  if (param_3 != 2) {
    *(byte *)(param_1 + 0x5c) = *(byte *)(param_1 + 0x5c) | 8;
    return ~(*(byte *)(param_1 + 0x5c) >> 5) & 1;
  }
  ExceptionList = &local_c;
  if (((*(uint *)(param_2 + 0x46c) & 0x100) != 0) &&
     (ExceptionList = &local_c, *(int *)(param_2 + 0x58c) != 0)) {
    ExceptionList = &local_c;
    uVar2 = FUN_0064f110(*(int *)(param_2 + 0x58c),param_2);
    FUN_006478b0(*(undefined4 *)(param_1 + 8),uVar2,0);
    uStack_4 = 0;
    FUN_00647d10(param_2);
    uStack_4 = 0xffffffff;
    FUN_00647950();
  }
  cVar1 = FUN_006181a0(param_2);
  if (cVar1 != '\0') {
    FUN_00618280(param_2,0xfa);
  }
  ExceptionList = pvStack_10;
  return 1;
}



/* function 0063c770 FUN_0063c770 */

undefined4 __thiscall FUN_0063c770(int param_1,int param_2)

{
  void *_Memory;
  int iVar1;
  undefined4 *puVar2;
  
  if ((*(byte *)(param_1 + 0x5c) & 8) != 0) {
    iVar1 = FUN_006817d0(4,0x2c5);
    if (((iVar1 != 0) && (iVar1 != param_1)) && (*(int *)(iVar1 + 0x10) != 0)) {
      *(int *)(param_1 + 0x10) = *(int *)(iVar1 + 0x10);
      *(undefined4 *)(iVar1 + 0x10) = 0;
    }
    *(byte *)(param_1 + 0x5c) = *(byte *)(param_1 + 0x5c) & 0xf7;
  }
  if (*(int *)(param_1 + 0x10) == 0) {
    if (((*(int *)(param_1 + 8) != 0) && (*(int *)(param_2 + 0x58c) == *(int *)(param_1 + 8))) &&
       ((*(uint *)(param_2 + 0x46c) & 0x100) != 0)) {
      FUN_005df910();
    }
    return 1;
  }
  puVar2 = &DAT_008d2e9c;
  do {
    iVar1 = FUN_004d68b0(*(undefined4 *)(param_2 + 0x18),*puVar2);
    if (iVar1 != 0) break;
    puVar2 = puVar2 + 1;
  } while ((int)puVar2 < 0x8d2ecc);
  FUN_006513a0(param_2,*(undefined4 *)(param_1 + 8),iVar1);
  _Memory = *(void **)(param_1 + 0x10);
  if (_Memory != (void *)0x0) {
    FUN_0064fc00();
                    /* WARNING: Subroutine does not return */
    _free(_Memory);
  }
  *(undefined4 *)(param_1 + 0x10) = 0;
  return 1;
}



/* function 0063c840 FUN_0063c840 */

void FUN_0063c840(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  *(byte *)(param_2 + 0x5c) = *(byte *)(param_2 + 0x5c) & 0xdf;
  *(undefined4 *)(param_2 + 0xc) = 0;
  if (*(int *)(param_2 + 8) != 0) {
    FUN_006d3060(1);
    if (*(int *)(*(int *)(param_2 + 8) + 0x460) != 0) {
      uVar1 = FUN_006e3b00(0x182);
      (**(code **)(**(int **)(param_2 + 8) + 0x70))
                ((*(int **)(param_2 + 8))[0x118],10,uVar1,0x182,0x3f800000);
    }
  }
  return;
}



/* function 0063dc20 FUN_0063dc20 */

void __fastcall FUN_0063dc20(int param_1)

{
  int iVar1;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00841b7b;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  iVar1 = FUN_0061a5a0(0x60);
  local_4 = 0;
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_0063c340(*(undefined4 *)(param_1 + 8),0,0);
  }
  *(byte *)(iVar1 + 0x5c) =
       *(byte *)(iVar1 + 0x5c) ^ (*(byte *)(param_1 + 0x5c) ^ *(byte *)(iVar1 + 0x5c)) & 4;
  ExceptionList = local_c;
  return;
}



/* function 00644470 FUN_00644470 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00644470(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  undefined1 uVar3;
  char cVar4;
  short sVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 uVar9;
  uint uVar10;
  int *piVar11;
  undefined1 *puVar12;
  undefined4 uVar13;
  undefined1 auStack_3c [24];
  undefined1 auStack_24 [24];
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0084237f;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  uVar3 = FUN_00506fe0();
  if ((((*(byte *)(param_1 + 0x5c) & 4) != 0) && ((*(uint *)(param_2 + 0x46c) & 0x100) != 0)) &&
     (*(int *)(param_2 + 0x58c) != 0)) {
    piVar11 = (int *)(param_1 + 8);
    if (*(int *)(param_2 + 0x58c) != *(int *)(param_1 + 8)) {
      if (*(int *)(param_1 + 8) != 0) {
        FUN_00571a00(piVar11);
      }
      iVar6 = *(int *)(param_2 + 0x58c);
      *piVar11 = iVar6;
      if (iVar6 != 0) {
        FUN_00571b70(piVar11);
      }
    }
  }
  if ((*(int *)(param_1 + 8) == 0) || ((*(uint *)(param_2 + 0x46c) & 0x100) == 0)) {
    *(uint *)(param_2 + 0x46c) = *(uint *)(param_2 + 0x46c) & 0xfffffeff;
    cVar4 = FUN_006181a0(param_2);
    if (cVar4 != '\0') {
      FUN_00618280(param_2,0xfa);
    }
    ExceptionList = pvStack_c;
    return 1;
  }
  iVar6 = FUN_005f7e80(param_2);
  cVar4 = FUN_00463830(*(undefined4 *)(param_1 + 8));
  if (cVar4 == '\0') {
    *(undefined4 *)(param_1 + 0x4c) = 0;
  }
  else {
    iVar7 = FUN_0056e210(0xffffffff);
    if (((param_2 != iVar7) &&
        (iVar7 = FUN_0056e210(0xffffffff), (*(uint *)(iVar7 + 0x46c) & 0x100) != 0)) &&
       (iVar7 = FUN_0056e210(0xffffffff), *(int *)(iVar7 + 0x58c) == *(int *)(param_1 + 8))) {
      FUN_005effe0(0x22,0,0x3f800000,0,0,0);
    }
    if ((iVar6 == 0) || (cVar4 = FUN_005f69c0(param_2), cVar4 != '\0')) {
      iVar6 = FUN_00821b40();
      uVar10 = *(int *)(param_1 + 0x4c) + iVar6;
      *(uint *)(param_1 + 0x4c) = uVar10;
      if (2000 < uVar10) {
        FUN_004b1cc0(*(undefined4 *)(param_1 + 8));
        uStack_4 = 0;
        FUN_004ab420(auStack_3c,0);
        uStack_4 = 0xffffffff;
        FUN_004b1d50();
      }
    }
  }
  cVar4 = FUN_005df8f0();
  if (((cVar4 != '\0') && (cVar4 = FUN_006d2370(), cVar4 != '\0')) &&
     ((*(char *)(param_1 + 0x58) == '\0' || (cVar4 = thunk_FUN_0156d5d0(), cVar4 != '\0')))) {
    *(undefined4 *)(param_1 + 0x50) = DAT_00b7cb84;
    *(undefined4 *)(param_1 + 0x54) = 2000;
    *(undefined1 *)(param_1 + 0x58) = 1;
    FUN_004b1740(param_2,*(undefined4 *)(param_1 + 8));
    puVar12 = auStack_3c;
    uVar13 = 0;
    uStack_4 = 1;
    FUN_004aba50(puVar12,0);
    FUN_004ab420(puVar12,uVar13);
    uStack_4 = 0xffffffff;
    FUN_004b17f0();
  }
  iVar6 = *(int *)(param_1 + 8);
  if (((*(int *)(iVar6 + 0x590) == 9) || (*(int *)(iVar6 + 0x594) == 2)) ||
     (*(short *)(iVar6 + 0x22) == 0x213)) {
    *(uint *)(param_2 + 0x478) = *(uint *)(param_2 + 0x478) | 0x100000;
  }
  cVar4 = FUN_005df8f0();
  if ((cVar4 == '\0') || (*(int *)(*(int *)(param_1 + 8) + 0x460) != param_2)) {
    piVar11 = *(int **)(param_1 + 8);
    if (piVar11[0x118] != param_2) {
      cVar4 = FUN_006d1bd0(param_2);
      if (cVar4 != '\0') {
        if ((*(byte *)(param_1 + 0x5c) & 0x18) == 0) {
          iVar6 = (**(code **)(**(int **)(param_1 + 8) + 0xbc))();
          if (iVar6 != 0) {
            puVar8 = (undefined4 *)(**(code **)(**(int **)(param_1 + 8) + 0xbc))();
            FUN_004d4610(*(undefined4 *)(param_2 + 0x18),*puVar8,0xcd,0x41000000);
          }
          *(byte *)(param_1 + 0x5c) = *(byte *)(param_1 + 0x5c) | 0x10;
        }
        FUN_00642e70(param_2,1);
        cVar4 = FUN_005df8f0();
        if (((cVar4 != '\0') && (cVar4 = thunk_FUN_0156cf30(), cVar4 != '\0')) &&
           ((*(int *)(param_2 + 0x610) != 0 &&
            (((0 < *(int *)(param_2 + 0x61c) && (cVar4 = thunk_FUN_004011cd(param_2), cVar4 != '\0')
              ) && ((&DAT_00b6f1a8)[(uint)DAT_00b6f081 * 0x11c] == 0x31)))))) {
          iVar6 = *(int *)(*(int *)(param_1 + 8) + 0x468);
          iVar7 = FUN_0061a5a0(0x44);
          uStack_4 = 4;
          if (iVar7 == 0) {
            uVar13 = 0;
          }
          else {
            uVar13 = FUN_006217d0(0,0,0x42c80000,100,8,iVar6 != param_2);
          }
          uStack_4 = 0xffffffff;
          FUN_004b0a00(3,uVar13,0);
          uStack_4 = 5;
          FUN_004ab420(auStack_3c,0);
          uStack_4 = 0xffffffff;
          FUN_004b0a50();
        }
      }
      goto LAB_00644af7;
    }
  }
  else {
    iVar6 = FUN_00609560();
    if (((DAT_00969179 != '\0') && (*(int *)(param_2 + 0x610) != 0)) &&
       ((0 < *(int *)(param_2 + 0x61c) && (cVar4 = thunk_FUN_004011cd(param_2), cVar4 != '\0')))) {
      iVar7 = FUN_0061a5a0(0x44);
      uStack_4 = 2;
      if (iVar7 == 0) {
        uVar13 = 0;
      }
      else {
        uVar13 = FUN_006217d0(0,0,0x42c80000,100,8,0);
      }
      uStack_4 = 0xffffffff;
      FUN_004b0a00(3,uVar13,0);
      uStack_4 = 3;
      FUN_004ab420(auStack_3c,0);
      uStack_4 = 0xffffffff;
      FUN_004b0a50();
    }
    if (((*(short *)(*(int *)(param_2 + 0x58c) + 0x22) != 0x23a) &&
        (*(int *)(*(int *)(param_2 + 0x58c) + 0x590) == 6)) &&
       (cVar4 = FUN_006f4800(), cVar4 == '\0')) {
      if ((iVar6 == 0) ||
         (((sVar5 = FUN_005403f0(), (float)(int)sVar5 == DAT_00858b50 &&
           (sVar5 = FUN_0053fb80(), (float)(int)sVar5 == DAT_00858b50)) &&
          (sVar5 = FUN_00540080(), (float)(int)sVar5 == DAT_00858b50)))) {
        uVar13 = FUN_00639fc0(*(undefined1 *)(*(int *)(*(int *)(param_1 + 8) + 900) + 0xde),0x182);
        (**(code **)(**(int **)(param_2 + 0x58c) + 0x70))(param_2,10,uVar13,0x182,0x3f800000);
      }
      goto LAB_00644af7;
    }
    if ((*(int *)(*(int *)(param_2 + 0x58c) + 0x590) == 0) && (iVar7 = FUN_006c2230(2), iVar7 == 1))
    {
      cVar4 = (**(code **)(**(int **)(param_2 + 0x58c) + 0x98))(2);
      if (cVar4 != '\0') goto LAB_00644af7;
      iVar7 = FUN_004d68b0(*(undefined4 *)(param_2 + 0x18),0x182);
      if (((*(byte *)(*(int *)(param_2 + 0x58c) + 0x487) & 1) == 0) &&
         ((*(byte *)(*(int *)(param_2 + 0x58c) + 0x486) & 1) == 0)) {
        if (iVar7 == 0) {
          if ((iVar6 == 0) ||
             (((sVar5 = FUN_005403f0(), (float)(int)sVar5 == DAT_00858b50 &&
               (sVar5 = FUN_0053fb80(), (float)(int)sVar5 == DAT_00858b50)) &&
              (sVar5 = FUN_00540080(), (float)(int)sVar5 == DAT_00858b50)))) {
            FUN_006d3020(1);
            *(byte *)(param_1 + 0x5c) = *(byte *)(param_1 + 0x5c) | 0x20;
            FUN_00642700(param_2);
            ExceptionList = pvStack_c;
            return 0;
          }
        }
        else {
LAB_0064493e:
          uVar13 = FUN_00639fc0(*(undefined1 *)(*(int *)(*(int *)(param_1 + 8) + 900) + 0xde),
                                (int)*(short *)(iVar7 + 0x2c));
          (**(code **)(**(int **)(param_2 + 0x58c) + 0x70))
                    (param_2,10,uVar13,0x182,*(undefined4 *)(iVar7 + 0x20));
        }
      }
      else if (iVar7 != 0) goto LAB_0064493e;
      FUN_00642e70(param_2,0);
      goto LAB_00644af7;
    }
    piVar11 = *(int **)(param_1 + 8);
  }
  (**(code **)(*piVar11 + 0xb8))(param_2,uVar3);
  FUN_00642e70(param_2,1);
LAB_00644af7:
  iVar6 = FUN_005e02e0();
  if (iVar6 == 0) {
    iVar6 = FUN_004d68b0(*(undefined4 *)(param_2 + 0x18),0xa9);
    if (iVar6 == 0) {
      FUN_0063c500(param_2);
    }
    else {
      cVar4 = FUN_006181a0();
      if (cVar4 != '\0') {
        FUN_00618280(param_2,0xfa);
      }
      if (*(int *)(param_1 + 0x20) != -1) {
        *(undefined4 *)(param_1 + 0x20) = 0xffffffff;
      }
    }
    if ((*(char *)(param_2 + 0x484) == '\x01') && (iVar6 = FUN_005f7e80(param_2), iVar6 == 0)) {
      if ((*(int *)(*(int *)(param_1 + 8) + 0x460) == 0) &&
         (*(int *)(*(int *)(param_1 + 8) + 0x464) == param_2)) {
        if (*(char *)(param_1 + 0x1c) == '\0') {
          *(undefined4 *)(param_1 + 0x14) = DAT_00b7cb84;
          *(undefined4 *)(param_1 + 0x18) = 4000;
          *(undefined1 *)(param_1 + 0x1c) = 1;
        }
        cVar4 = thunk_FUN_0156d5d0();
        if (cVar4 != '\0') {
          iVar6 = FUN_0061a5a0(0x40);
          uStack_4 = 6;
          if (iVar6 == 0) {
            uVar13 = 0;
          }
          else {
            uVar13 = FUN_00632bd0();
          }
          uStack_4 = 0xffffffff;
          iVar6 = FUN_0061a5a0(0x34);
          uStack_4 = 7;
          if (iVar6 == 0) {
            uVar9 = 0;
          }
          else {
            uVar9 = FUN_0063b8c0(*(undefined4 *)(param_1 + 8),0,0,1,0);
          }
          uStack_4 = 0xffffffff;
          FUN_00632d10(uVar9);
          iVar6 = FUN_0061a5a0(0x24);
          uStack_4 = 8;
          if (iVar6 == 0) {
            uVar9 = 0;
          }
          else {
            uVar9 = FUN_0063cb10(*(undefined4 *)(param_1 + 8),0,0x41200000);
          }
          uStack_4 = 0xffffffff;
          FUN_00632d10(uVar9);
          FUN_004b0a00(3,uVar13,0);
          uStack_4 = 9;
          FUN_004ab420(auStack_24,0);
          uStack_4 = 0xffffffff;
          FUN_004b0a50();
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x1c) = 0;
      }
    }
    if ((((((uint)*(ushort *)(param_2 + 0x20) + DAT_00b7cb4c & 0x3fff) == 0) &&
         (iVar6 = *(int *)(*(int *)(param_1 + 8) + 0x460), iVar6 != 0)) && (iVar6 != param_2)) &&
       (cVar4 = FUN_005df8f0(), cVar4 != '\0')) {
      fVar1 = *(float *)(*(int *)(param_1 + 8) + 0x48);
      fVar2 = *(float *)(*(int *)(param_1 + 8) + 0x44);
      if (_DAT_00858cb0 < SQRT(fVar1 * fVar1 + fVar2 * fVar2)) {
        FUN_005effe0(0x20,0,0x3f800000,0,0,0);
      }
      fVar1 = *(float *)(*(int *)(param_1 + 8) + 0x48);
      fVar2 = *(float *)(*(int *)(param_1 + 8) + 0x44);
      if (SQRT(fVar1 * fVar1 + fVar2 * fVar2) < _DAT_00858b1c) {
        FUN_005effe0(0x27,0,0x3f800000,0,0,0);
      }
      FUN_005effe0(0x29,0,0x3f800000,0,0,0);
    }
    ExceptionList = pvStack_c;
    return 0;
  }
  uVar13 = FUN_00407f90();
  return uVar13;
}



/* function 0066d050 FUN_0066d050 */

void __fastcall FUN_0066d050(int param_1)

{
  int iVar1;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0084540b;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  iVar1 = FUN_0061a5a0(0x60);
  local_4 = 0;
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_0066a100(*(undefined4 *)(param_1 + 0xc),param_1 + 0x1c,
                         *(undefined4 *)(param_1 + 0x58));
  }
  if ((*(byte *)(param_1 + 0x5c) & 4) != 0) {
    *(byte *)(iVar1 + 0x5c) = *(byte *)(iVar1 + 0x5c) | 4;
  }
  ExceptionList = local_c;
  return;
}



/* function 00671800 FUN_00671800 */

void __thiscall FUN_00671800(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  if (-1 < *(int *)(param_1 + 0x3c)) {
    *(undefined4 *)(param_1 + 0x40) = DAT_00b7cb84;
    *(int *)(param_1 + 0x44) = *(int *)(param_1 + 0x3c);
    *(undefined1 *)(param_1 + 0x48) = 1;
  }
  if ((*(byte *)(param_1 + 0x4c) & 8) != 0) {
    *(undefined4 *)(param_1 + 0x50) = 0;
    *(undefined4 *)(param_1 + 0x54) = 0;
    *(undefined4 *)(param_1 + 0x58) = 0;
    *(undefined4 *)(param_1 + 0x5c) = 0;
  }
  if ((*(uint *)(param_2 + 0x46c) & 0x100) != 0) {
    FUN_00669690(0x2c0,param_2);
    return;
  }
  FUN_00671750(param_2,param_1 + 0xc,*(undefined4 *)(param_1 + 0x1c),*(undefined4 *)(param_1 + 0x20)
               ,*(undefined4 *)(param_1 + 0x24),1);
  uVar1 = *(uint *)(param_1 + 0x4c);
  uVar3 = uVar1 & 0xfffffffb;
  *(uint *)(param_1 + 0x4c) = uVar3;
  if ((uVar3 >> 1 & 1) == 0) {
    iVar2 = 900;
  }
  else if (*(int *)(param_1 + 0x38) == **(int **)(param_1 + 0x30)) {
    iVar2 = 0x516;
  }
  else {
    iVar2 = (-(uint)(*(int *)(param_1 + 0x38) + 1 != **(int **)(param_1 + 0x30)) & 0xfffffffd) +
            0x387;
  }
  if ((uVar1 & 8) != 0) {
    iVar2 = FUN_0066ebe0(param_2,iVar2);
  }
  FUN_00669690(iVar2,param_2);
  return;
}


