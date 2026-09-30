/* Full-analysis function mapping; decompilation is not original source. */

/* function 004bdb80 FUN_004bdb80 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004bdb80(int *param_1,int param_2,undefined4 param_3,int param_4)

{
  uint *puVar1;
  float fVar2;
  short sVar3;
  int iVar4;
  bool bVar5;
  bool bVar6;
  char cVar7;
  float *pfVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  undefined4 uVar14;
  float *pfVar15;
  float10 fVar16;
  int iStack_f4;
  int local_f0;
  undefined4 uStack_e4;
  float fStack_e0;
  undefined4 uStack_dc;
  int local_d8;
  undefined4 auStack_d4 [25];
  undefined4 auStack_70 [25];
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0083b388;
  pvStack_c = ExceptionList;
  iVar12 = *(int *)(param_2 + 0x14);
  if (iVar12 == 0) {
    return;
  }
  ExceptionList = &pvStack_c;
  FUN_006819d0();
  iVar9 = *param_1;
  pfVar15 = (float *)(*(int *)(iVar9 + 0x14) + 0x30);
  if (*(int *)(iVar9 + 0x14) == 0) {
    pfVar15 = (float *)(iVar9 + 4);
  }
  iVar10 = *(int *)(iVar12 + 0x14);
  pfVar8 = (float *)(iVar10 + 0x30);
  if (iVar10 == 0) {
    pfVar8 = (float *)(iVar12 + 4);
  }
  iVar11 = *(int *)(iVar9 + 0x14);
  bVar6 = (*pfVar8 - *pfVar15) * *(float *)(iVar11 + 0x10) +
          (pfVar8[1] - pfVar15[1]) * *(float *)(iVar11 + 0x14) +
          (pfVar8[2] - pfVar15[2]) * *(float *)(iVar11 + 0x18) < DAT_00858b50;
  fVar2 = (*pfVar8 - *pfVar15) * *(float *)(iVar10 + 0x10) +
          (pfVar8[1] - pfVar15[1]) * *(float *)(iVar10 + 0x14) +
          (pfVar8[2] - pfVar15[2]) * *(float *)(iVar10 + 0x18);
  bVar5 = fVar2 < DAT_00858b50 != (fVar2 == DAT_00858b50);
  local_d8 = (int)*(short *)(param_2 + 0x30);
  sVar3 = *(short *)(param_2 + 0x32);
  local_f0 = 0;
  iVar9 = FUN_005f7e80(iVar9);
  if (iVar9 == 0) {
    if (local_d8 == 4) {
      if ((sVar3 == 1) || (sVar3 == 0)) {
        if (bVar6) {
          FUN_00618970("CompPedCollPedResp",*param_1,iVar12,2000,5,0,1,0x3e800000,500,3,0);
          iVar12 = FUN_0061a5a0(0x1c);
          uStack_4 = 6;
        }
        else {
          if ((param_4 != 0) && (cVar7 = FUN_0061a360(param_4), cVar7 != '\0')) {
            auStack_d4[0] = 0;
            FUN_005f6110(*param_1,iVar12,param_4 + 0xc,auStack_d4,0);
            iVar12 = FUN_0061a5a0(0x3c);
            uStack_4 = 4;
            if (iVar12 == 0) {
              local_f0 = 0;
            }
            else {
              local_f0 = FUN_00671510(4,auStack_d4,0,DAT_0086fc98,DAT_0086fc9c,0,1,1);
            }
            uStack_4 = 0xffffffff;
          }
          iVar12 = FUN_0061a5a0(0x1c);
          uStack_4 = 5;
        }
      }
      else {
        if (sVar3 != 4) {
LAB_004be4b7:
          if ((((sVar3 != 1) && (sVar3 != 0)) ||
              ((local_d8 != 4 && ((local_d8 != 6 && (local_d8 != 7)))))) || (!bVar5))
          goto LAB_004be78a;
          iVar9 = FUN_0061a5a0(0x1c);
          uStack_4 = 0x12;
          if (iVar9 == 0) {
            iVar9 = 0;
          }
          else {
            iVar9 = thunk_FUN_015655e0(0x1c,0xffffffff);
          }
          param_1[0xb] = iVar9;
          uStack_4 = 0xffffffff;
          FUN_00618970("CompPedCollPedResp",*param_1,iVar12,2000,5,0,1,0x3e800000,500,3,0);
          if (local_d8 == 4) goto LAB_004be78a;
          uVar14 = FUN_005f3bc0(iVar12,*param_1);
          iVar12 = FUN_0061a5a0(0x10);
          uStack_4 = 0x13;
LAB_004be6b5:
          if (iVar12 == 0) {
            uStack_4 = 0xffffffff;
            local_f0 = 0;
          }
          else {
            local_f0 = FUN_00631d70(uVar14);
            uStack_4 = 0xffffffff;
          }
          goto LAB_004be78a;
        }
        if (!bVar6) {
          cVar7 = FUN_0061a360(param_4);
          if (cVar7 != '\0') {
            auStack_70[0] = 0;
            FUN_005f6110(*param_1,iVar12,param_4 + 0xc,auStack_70,0);
            iVar9 = FUN_0061a5a0(0x3c);
            uStack_4 = 7;
            if (iVar9 == 0) {
              local_f0 = 0;
            }
            else {
              local_f0 = FUN_00671510(4,auStack_70,0,DAT_0086fc98,DAT_0086fc9c,0,1,1);
            }
            uStack_4 = 0xffffffff;
          }
          FUN_00618970("CompPedCollPedResp",*param_1,iVar12,2000,5,0,1,0x3e800000,500,3,0);
          iVar12 = FUN_0061a5a0(0x1c);
          uStack_4 = 8;
          if (iVar12 == 0) {
            uStack_4 = 0xffffffff;
            param_1[0xb] = 0;
          }
          else {
            iVar12 = thunk_FUN_015655e0(0x1c,0xffffffff);
            uStack_4 = 0xffffffff;
            param_1[0xb] = iVar12;
          }
          goto LAB_004be78a;
        }
        if (!bVar5) goto LAB_004be78a;
        FUN_00618970("CompPedCollPedResp",*param_1,iVar12,2000,5,0,1,0x3e800000,500,3,0);
        iVar12 = FUN_0061a5a0(0x1c);
        uStack_4 = 9;
      }
LAB_004be2ed:
      if (iVar12 != 0) {
        thunk_FUN_015655e0(0x1c,0xffffffff);
        FUN_0040235e();
        return;
      }
      uStack_4 = 0xffffffff;
      param_1[0xb] = 0;
    }
    else {
      if (((local_d8 != 6) && (local_d8 != 7)) || ((sVar3 != 6 && (sVar3 != 7)))) {
        if ((((local_d8 != 1) && (local_d8 != 0)) ||
            ((sVar3 != 4 && ((sVar3 != 6 && (sVar3 != 7)))))) || (!bVar5)) goto LAB_004be4b7;
        if ((sVar3 == 6) || (sVar3 == 7)) {
          iVar9 = *(int *)(*param_1 + 0x59c);
          if ((*(float *)(iVar9 + 0x2c) <= _DAT_0085aae0) ||
             (*(float *)(*(int *)(iVar12 + 0x59c) + 0x2c) <= _DAT_0085aae0)) {
            if (_DAT_0085aae0 < *(float *)(iVar9 + 0x2c)) goto LAB_004be3dc;
          }
          else if (*(float *)(*(int *)(iVar12 + 0x59c) + 0x2c) < *(float *)(iVar9 + 0x2c)) {
LAB_004be3dc:
            uVar14 = FUN_005f3bc0(iVar12,*param_1);
            iVar12 = FUN_0061a5a0(0x18);
            uStack_4 = 0xf;
            goto LAB_004be3fe;
          }
        }
        iVar9 = FUN_0061a5a0(0x1c);
        uStack_4 = 0x10;
        if (iVar9 == 0) {
          iVar9 = 0;
        }
        else {
          iVar9 = thunk_FUN_015655e0(0x1c,0xffffffff);
        }
        uStack_4 = 0xffffffff;
        param_1[0xb] = iVar9;
        FUN_00618970("CompPedCollPedResp",*param_1,iVar12,2000,5,0,1,0x3e800000,500,3,0);
        if (sVar3 != 4) {
          uVar14 = FUN_005f3bc0(iVar12,*param_1);
          iVar12 = FUN_0061a5a0(0x10);
          uStack_4 = 0x11;
          if (iVar12 == 0) {
            uStack_4 = 0xffffffff;
            local_f0 = 0;
          }
          else {
            local_f0 = FUN_00631d70(uVar14);
            uStack_4 = 0xffffffff;
          }
        }
        goto LAB_004be78a;
      }
      if (bVar6) {
        if (!bVar5) goto LAB_004be78a;
        iVar9 = FUN_0061a5a0(0x1c);
        uStack_4 = 0xe;
        if (iVar9 == 0) {
          iVar9 = 0;
        }
        else {
          iVar9 = thunk_FUN_015655e0(0x1c,0xffffffff);
        }
        iVar10 = *param_1;
      }
      else {
        if (bVar5) {
          iVar9 = *(int *)(*param_1 + 0x59c);
          if ((*(float *)(iVar9 + 0x2c) <= _DAT_0085aae0) ||
             (*(float *)(*(int *)(iVar12 + 0x59c) + 0x2c) <= _DAT_0085aae0)) {
            if (_DAT_0085aae0 < *(float *)(iVar9 + 0x2c)) goto LAB_004be61c;
          }
          else if (*(float *)(*(int *)(iVar12 + 0x59c) + 0x2c) < *(float *)(iVar9 + 0x2c)) {
LAB_004be61c:
            uVar14 = FUN_005f3bc0(iVar12,*param_1);
            iVar12 = FUN_0061a5a0(0x18);
            uStack_4 = 10;
LAB_004be3fe:
            if (iVar12 != 0) {
              local_f0 = FUN_00678700(uVar14,0);
              uStack_4 = 0xffffffff;
              goto LAB_004be78a;
            }
            goto LAB_004be643;
          }
          iVar9 = FUN_0061a5a0(0x1c);
          uStack_4 = 0xb;
          if (iVar9 == 0) {
            iVar9 = 0;
          }
          else {
            iVar9 = thunk_FUN_015655e0(0x1c,0xffffffff);
          }
          uStack_4 = 0xffffffff;
          param_1[0xb] = iVar9;
          FUN_00618970("CompPedCollPedResp",*param_1,iVar12,2000,5,0,1,0x3e800000,500,3,0);
          uVar14 = FUN_005f3bc0(iVar12,*param_1);
          iVar12 = FUN_0061a5a0(0x10);
          uStack_4 = 0xc;
          goto LAB_004be6b5;
        }
        iVar9 = FUN_0061a5a0(0x1c);
        uStack_4 = 0xd;
        if (iVar9 == 0) {
          iVar9 = 0;
        }
        else {
          iVar9 = thunk_FUN_015655e0(0x1c,0xffffffff);
        }
        iVar10 = *param_1;
      }
      param_1[0xb] = iVar9;
      uStack_4 = 0xffffffff;
      FUN_00618970("CompPedCollPedResp",iVar10,iVar12,2000,5,0,1,0x3e800000,500,3,0);
    }
    goto LAB_004be78a;
  }
  iVar10 = FUN_005f69a0();
  iVar11 = FUN_005f7e80(iVar12);
  if (iVar11 == 0) {
    iStack_f4 = 0;
  }
  else {
    iStack_f4 = FUN_005f69a0();
  }
  bVar5 = false;
  if (iVar9 == iVar11) {
    bVar5 = true;
    if (iVar12 == iVar10) {
      *(uint *)(iVar12 + 0x474) = *(uint *)(iVar12 + 0x474) | 0x80000000;
    }
    if (*param_1 == iVar10) {
      puVar1 = (uint *)(*param_1 + 0x474);
      *puVar1 = *puVar1 | 0x80000000;
    }
  }
  cVar7 = FUN_005df8f0();
  if (cVar7 != '\0') {
    iVar12 = FUN_0061a5a0(0x1c);
    uStack_4 = 0;
    goto LAB_004be2ed;
  }
  if (iVar11 == 0) {
    if ((local_d8 != 1) && (sVar3 != 1)) goto LAB_004be78a;
    uStack_e4 = *(undefined4 *)(*(int *)(*param_1 + 0x14) + 0x10);
    fStack_e0 = -*(float *)(*(int *)(*param_1 + 0x14) + 0x14);
    uStack_dc = 0;
    FUN_0059c910();
    iVar9 = FUN_0061a5a0(0x1c);
    uStack_4 = 3;
    if (iVar9 != 0) {
      local_f0 = FUN_006532d0(iVar12,&uStack_e4);
      uStack_4 = 0xffffffff;
      goto LAB_004be78a;
    }
  }
  else {
    if ((local_d8 != 1) && (sVar3 != 1)) goto LAB_004be78a;
    if (bVar5) {
      if ((iVar12 != iStack_f4) && ((iVar10 == 0 || (iVar9 = FUN_00601d70(), iVar9 != 1))))
      goto LAB_004be78a;
    }
    else {
      fVar16 = (float10)FUN_0041bd90(0,0x3f800000);
      if (fVar16 < (float10)_DAT_00858c84) {
        fVar16 = (float10)FUN_0041bd90(0,0x3f800000);
        if ((float10)_DAT_0085ad74 <= fVar16) {
          if (fVar16 < (float10)_DAT_0085ba50) {
            iVar9 = FUN_0061a5a0(0x1c);
            uStack_4 = 1;
            if (iVar9 == 0) {
              uStack_4 = 0xffffffff;
              param_1[0xb] = 0;
            }
            else {
              iVar9 = thunk_FUN_015655e0(0x1c,0xffffffff);
              uStack_4 = 0xffffffff;
              param_1[0xb] = iVar9;
            }
          }
        }
        else {
          FUN_00618970("CompPedCollPedResp",*param_1,iVar12,2000,5,0,1,0x3e800000,500,3,0);
        }
      }
    }
    iVar9 = FUN_00600ee0(0x4b7);
    iVar10 = FUN_00681740(0x395);
    iVar11 = FUN_00600ee0(900);
    iVar13 = FUN_00600ee0(0x38b);
    if (bVar5) {
      if (iVar9 != 0) {
        iVar4 = *(int *)(iVar9 + 0x10);
        if (((iVar4 != 0) && (iVar13 != 0)) && ((iVar10 != 0 || (iVar11 != 0)))) {
          iVar12 = *(int *)(iVar4 + 0x14) + 0x30;
          if (*(int *)(iVar4 + 0x14) == 0) {
            iVar12 = iVar4 + 4;
          }
          iVar13 = *(int *)(*param_1 + 0x14);
          if (iVar13 == 0) {
            iVar13 = *param_1 + 4;
          }
          else {
            iVar13 = iVar13 + 0x30;
          }
          FUN_0040fe60(&uStack_e4,iVar13,iVar12);
          uStack_dc = 0;
          fVar16 = (float10)FUN_004082c0();
          fVar2 = (float)fVar16;
          if (iVar10 != 0) {
            *(byte *)(iVar10 + 0x5c) = *(byte *)(iVar10 + 0x5c) | 2;
          }
          if (iVar11 != 0) {
            *(float *)(iVar11 + 0x18) = fVar2 + _DAT_00858b1c;
          }
          FUN_004bc470(fVar2 + _DAT_00858b1c);
          if (fVar2 < _DAT_0086f828) {
            *(undefined4 *)(iVar9 + 0x20) = uStack_e4;
            *(float *)(iVar9 + 0x24) = fStack_e0;
            *(undefined4 *)(iVar9 + 0x28) = uStack_dc;
          }
          goto LAB_004be78a;
        }
        goto LAB_004bdf49;
      }
    }
    else {
LAB_004bdf49:
      if ((iVar9 != 0) && (bVar5)) goto LAB_004be78a;
    }
    uStack_e4 = *(undefined4 *)(*(int *)(*param_1 + 0x14) + 0x10);
    fStack_e0 = -*(float *)(*(int *)(*param_1 + 0x14) + 0x14);
    uStack_dc = 0;
    FUN_0059c910();
    iVar9 = FUN_0061a5a0(0x1c);
    uStack_4 = 2;
    if (iVar9 != 0) {
      local_f0 = FUN_006532d0(iVar12,&uStack_e4);
      uStack_4 = 0xffffffff;
      goto LAB_004be78a;
    }
  }
LAB_004be643:
  uStack_4 = 0xffffffff;
  local_f0 = 0;
LAB_004be78a:
  param_1[9] = local_f0;
  if ((local_f0 != 0) && (cVar7 = FUN_005df8f0(), cVar7 != '\0')) {
    thunk_FUN_0156fc20(1);
  }
  ExceptionList = pvStack_c;
  return;
}



/* function 004be7d0 FUN_004be7d0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004be7d0(int *param_1,int param_2,int *param_3,int param_4)

{
  float fVar1;
  short sVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  int iVar8;
  char cVar9;
  float *pfVar10;
  int iVar11;
  int iVar12;
  int *piVar13;
  int iVar14;
  int iVar15;
  float *pfVar16;
  int iVar17;
  float10 fVar18;
  float fStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  int local_8c;
  int local_88;
  int local_84;
  int local_80;
  float fStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 auStack_70 [25];
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0083b456;
  pvStack_c = ExceptionList;
  iVar17 = *(int *)(param_2 + 0x14);
  ExceptionList = &pvStack_c;
  if (iVar17 == 0) goto code_r0x004bf21c;
  iVar11 = *param_1;
  pfVar16 = (float *)(*(int *)(iVar11 + 0x14) + 0x30);
  if (*(int *)(iVar11 + 0x14) == 0) {
    pfVar16 = (float *)(iVar11 + 4);
  }
  iVar12 = *(int *)(iVar17 + 0x14);
  pfVar10 = (float *)(iVar12 + 0x30);
  if (iVar12 == 0) {
    pfVar10 = (float *)(iVar17 + 4);
  }
  iVar11 = *(int *)(iVar11 + 0x14);
  bVar4 = DAT_00858b50 <=
          (*pfVar10 - *pfVar16) * *(float *)(iVar11 + 0x10) +
          (pfVar10[1] - pfVar16[1]) * *(float *)(iVar11 + 0x14) +
          (pfVar10[2] - pfVar16[2]) * *(float *)(iVar11 + 0x18);
  fVar1 = (*pfVar10 - *pfVar16) * *(float *)(iVar12 + 0x10) +
          (pfVar10[1] - pfVar16[1]) * *(float *)(iVar12 + 0x14) +
          (pfVar10[2] - pfVar16[2]) * *(float *)(iVar12 + 0x18);
  bVar3 = fVar1 < DAT_00858b50 != (fVar1 == DAT_00858b50);
  iVar11 = *(int *)(iVar17 + 0x534);
  sVar2 = *(short *)(param_2 + 0x30);
  if (((iVar11 == 4) || (iVar11 == 6)) || (bVar5 = false, iVar11 == 7)) {
    bVar5 = true;
  }
  local_84 = 0;
  bVar6 = false;
  bVar7 = false;
  ExceptionList = &pvStack_c;
  local_80 = FUN_00600ee0(0x4b7);
  iVar11 = FUN_00681740(0x395);
  local_88 = FUN_00600ee0(900);
  local_8c = FUN_00600ee0(0x38b);
  iVar12 = FUN_00600ee0(0xf3);
  if ((iVar12 != 0) && (*(int *)(iVar12 + 0xc) == 0)) {
    bVar7 = true;
    iVar12 = FUN_005f6a50();
    if (iVar12 < 3) goto code_r0x004bf21c;
    bVar6 = true;
  }
  FUN_005effe0(0x1c,0,0x3f800000,0,0,0);
  if ((param_3 == (int *)0x0) || (iVar12 = (**(code **)(*param_3 + 0x10))(), iVar12 != 0x391)) {
    iVar8 = local_80;
    iVar12 = local_88;
    if (!bVar3) {
      if (bVar4) {
        if (((sVar2 != 4) && (sVar2 != 6)) && (sVar2 != 7)) {
          iVar12 = FUN_0061a5a0(0x1c);
          uStack_4 = 10;
          if (iVar12 == 0) {
            iVar12 = 0;
          }
          else {
            iVar12 = thunk_FUN_015655e0(0x1c,0xffffffff);
          }
          param_1[0xb] = iVar12;
          uStack_4 = 0xffffffff;
          FUN_00618970("CompPedCollPlayerResp",*param_1,iVar17,2000,5,0,1,0x3e800000,500,3,0);
          if (!bVar6) {
            uStack_94 = *(undefined4 *)(*(int *)(iVar17 + 0x14) + 0x10);
            uStack_90 = 0;
            fStack_98 = -*(float *)(*(int *)(iVar17 + 0x14) + 0x14);
            FUN_0059c910();
            iVar11 = FUN_0061a5a0(0x1c);
            uStack_4 = 0xb;
            goto LAB_004bef14;
          }
          goto LAB_004bf12e;
        }
        if (local_80 == 0) {
LAB_004bf02f:
          if ((param_4 != 0) && (cVar9 = FUN_0061a360(param_4), cVar9 != '\0')) {
            auStack_70[0] = 0;
            FUN_005f6110(*param_1,iVar17,param_4 + 0xc,auStack_70,0);
            iVar12 = FUN_0061a5a0(0x3c);
            uStack_4 = 8;
            if (iVar12 == 0) {
              local_84 = 0;
            }
            else {
              local_84 = FUN_00671510(4,auStack_70,0,DAT_0086fc98,DAT_0086fc9c,0,1,1);
            }
            uStack_4 = 0xffffffff;
            bVar6 = false;
          }
        }
        else if ((local_8c == 0) || ((iVar11 == 0 && (local_88 == 0)))) {
LAB_004bf01b:
          if ((!bVar7) || (bVar5)) goto LAB_004bf02f;
        }
        else {
          if (!bVar7) goto LAB_004bf02f;
          if (bVar5) goto LAB_004bf01b;
          iVar14 = *(int *)(*(int *)(local_80 + 0x10) + 0x14);
          iVar15 = iVar14 + 0x30;
          if (iVar14 == 0) {
            iVar15 = *(int *)(local_80 + 0x10) + 4;
          }
          iVar14 = *(int *)(*param_1 + 0x14);
          if (iVar14 == 0) {
            iVar14 = *param_1 + 4;
          }
          else {
            iVar14 = iVar14 + 0x30;
          }
          FUN_0040fe60(&fStack_98,iVar14,iVar15);
          uStack_90 = 0;
          fVar18 = (float10)FUN_004082c0();
          fVar1 = (float)fVar18;
          if (iVar11 == 0) {
            if (iVar12 != 0) {
              *(float *)(iVar12 + 0x18) = fVar1 + _DAT_00858b1c;
            }
          }
          else {
            *(byte *)(iVar11 + 0x5c) = *(byte *)(iVar11 + 0x5c) | 2;
          }
          FUN_004bc470(fVar1 + _DAT_00858b1c);
          if (fVar1 < _DAT_0086f828) {
            *(float *)(iVar8 + 0x20) = fStack_98;
            *(undefined4 *)(iVar8 + 0x24) = uStack_94;
            *(undefined4 *)(iVar8 + 0x28) = uStack_90;
          }
        }
        iVar12 = FUN_0061a5a0(0x1c);
        uStack_4 = 9;
LAB_004bed59:
        if (iVar12 == 0) {
          iVar12 = 0;
        }
        else {
          iVar12 = thunk_FUN_015655e0(0x1c,0xffffffff);
        }
        param_1[0xb] = iVar12;
        uStack_4 = 0xffffffff;
        FUN_00618970("CompPedCollPlayerResp",*param_1,iVar17,2000,5,0,1,0x3e800000,500,3,0);
      }
      goto LAB_004bf122;
    }
    if (bVar4) {
      if (((sVar2 == 4) || (sVar2 == 6)) || (sVar2 == 7)) {
        if (local_80 == 0) {
LAB_004becab:
          if ((param_4 != 0) && (cVar9 = FUN_0061a360(param_4), cVar9 != '\0')) {
            auStack_70[0] = 0;
            FUN_005f6110(*param_1,iVar17,param_4 + 0xc,auStack_70,0);
            iVar12 = FUN_0061a5a0(0x3c);
            uStack_4 = 2;
            if (iVar12 == 0) {
              local_84 = 0;
            }
            else {
              local_84 = FUN_00671510(4,auStack_70,0,DAT_0086fc98,DAT_0086fc9c,0,1,1);
            }
            uStack_4 = 0xffffffff;
            bVar6 = false;
          }
        }
        else if ((local_8c == 0) || ((iVar11 == 0 && (local_88 == 0)))) {
LAB_004bec97:
          if ((!bVar7) || (bVar5)) goto LAB_004becab;
        }
        else {
          if (!bVar7) goto LAB_004becab;
          if (bVar5) goto LAB_004bec97;
          iVar14 = *(int *)(*(int *)(local_80 + 0x10) + 0x14);
          iVar15 = iVar14 + 0x30;
          if (iVar14 == 0) {
            iVar15 = *(int *)(local_80 + 0x10) + 4;
          }
          iVar14 = *(int *)(*param_1 + 0x14);
          if (iVar14 == 0) {
            iVar14 = *param_1 + 4;
          }
          else {
            iVar14 = iVar14 + 0x30;
          }
          FUN_0040fe60(&fStack_98,iVar14,iVar15);
          uStack_90 = 0;
          fVar18 = (float10)FUN_004082c0();
          fVar1 = (float)fVar18;
          if (iVar11 == 0) {
            if (iVar12 != 0) {
              *(float *)(iVar12 + 0x18) = fVar1 + _DAT_00858b1c;
            }
          }
          else {
            *(byte *)(iVar11 + 0x5c) = *(byte *)(iVar11 + 0x5c) | 2;
          }
          FUN_004bc470(fVar1 + _DAT_00858b1c);
          if (fVar1 < _DAT_0086f828) {
            *(float *)(iVar8 + 0x20) = fStack_98;
            *(undefined4 *)(iVar8 + 0x24) = uStack_94;
            *(undefined4 *)(iVar8 + 0x28) = uStack_90;
          }
        }
        iVar12 = FUN_0061a5a0(0x1c);
        uStack_4 = 3;
        goto LAB_004bed59;
      }
      iVar12 = FUN_0061a5a0(0x1c);
      uStack_4 = 4;
      if (iVar12 == 0) {
        iVar12 = 0;
      }
      else {
        iVar12 = thunk_FUN_015655e0(0x1c,0xffffffff);
      }
      uStack_4 = 0xffffffff;
      param_1[0xb] = iVar12;
      FUN_00618970("CompPedCollPlayerResp",*param_1,iVar17,2000,5,0,1,0x3e800000,500,3,0);
      if (!bVar6) {
        uStack_94 = *(undefined4 *)(*(int *)(iVar17 + 0x14) + 0x10);
        uStack_90 = 0;
        fStack_98 = -*(float *)(*(int *)(iVar17 + 0x14) + 0x14);
        FUN_0059c910();
        iVar11 = FUN_0061a5a0(0x1c);
        uStack_4 = 5;
LAB_004bef14:
        if (iVar11 == 0) goto LAB_004bf29b;
        iVar12 = FUN_006532d0(iVar17,&fStack_98);
        goto LAB_004bf216;
      }
      goto LAB_004bf12e;
    }
    iVar12 = FUN_0061a5a0(0x1c);
    uStack_4 = 6;
    if (iVar12 == 0) {
      iVar12 = 0;
    }
    else {
      iVar12 = thunk_FUN_015655e0(0x1c,0xffffffff);
    }
    uStack_4 = 0xffffffff;
    param_1[0xb] = iVar12;
    FUN_00618970("CompPedCollPlayerResp",*param_1,iVar17,2000,5,0,1,0x3e800000,500,3,0);
    if (bVar6) goto LAB_004bf12e;
    uStack_94 = *(undefined4 *)(*(int *)(iVar17 + 0x14) + 0x10);
    uStack_90 = 0;
    fStack_98 = -*(float *)(*(int *)(iVar17 + 0x14) + 0x14);
    FUN_0059c910();
    iVar11 = FUN_0061a5a0(0x1c);
    uStack_4 = 7;
    if (iVar11 != 0) {
      iVar12 = FUN_006532d0(iVar17,&fStack_98);
      goto LAB_004bf216;
    }
LAB_004bf29b:
    iVar12 = 0;
  }
  else {
    cVar9 = FUN_005df8f0();
    if (cVar9 == '\0') {
      iVar12 = FUN_00681720();
      if (iVar12 != 0) {
        piVar13 = (int *)FUN_00681720();
        iVar12 = (**(code **)(*piVar13 + 0x10))();
        if ((iVar12 == 0x391) &&
           (fVar18 = (float10)FUN_0041bd90(0,0x3f800000), fVar18 < (float10)_DAT_00858c84)) {
          fVar18 = (float10)FUN_0041bd90(0,0x3f800000);
          if ((float10)_DAT_0085ad74 <= fVar18) {
            if (fVar18 < (float10)_DAT_0085ba68) {
              iVar12 = FUN_0061a5a0(0x1c);
              uStack_4 = 1;
              goto LAB_004be9b0;
            }
          }
          else {
            FUN_00618970("CompPedCollPlayerResp",*param_1,iVar17,2000,5,0,1,0x3e800000,500,3,0);
          }
        }
      }
    }
    else {
      iVar12 = FUN_0061a5a0(0x1c);
      uStack_4 = 0;
LAB_004be9b0:
      if (iVar12 == 0) {
        iVar12 = 0;
      }
      else {
        iVar12 = thunk_FUN_015655e0(0x1c,0xffffffff);
      }
      uStack_4 = 0xffffffff;
      param_1[0xb] = iVar12;
    }
    if ((bVar3) && (iVar17 == param_3[4])) goto LAB_004bf12e;
LAB_004bf122:
    iVar12 = local_84;
    if (bVar6) {
LAB_004bf12e:
      iVar8 = local_80;
      iVar12 = local_88;
      if (local_80 != 0) {
        if ((local_8c != 0) && ((iVar11 != 0 || (local_88 != 0)))) {
          if (!bVar7) goto LAB_004bf244;
          if (!bVar5) {
            iVar15 = *(int *)(*(int *)(local_80 + 0x10) + 0x14);
            iVar17 = iVar15 + 0x30;
            if (iVar15 == 0) {
              iVar17 = *(int *)(local_80 + 0x10) + 4;
            }
            iVar15 = *(int *)(*param_1 + 0x14);
            if (iVar15 == 0) {
              iVar15 = *param_1 + 4;
            }
            else {
              iVar15 = iVar15 + 0x30;
            }
            FUN_0040fe60(&fStack_98,iVar15,iVar17);
            uStack_90 = 0;
            fVar18 = (float10)FUN_004082c0();
            fVar1 = (float)fVar18;
            if (iVar11 == 0) {
              if (iVar12 != 0) {
                *(float *)(iVar12 + 0x18) = fVar1 + _DAT_00858b1c;
              }
            }
            else {
              *(byte *)(iVar11 + 0x5c) = *(byte *)(iVar11 + 0x5c) | 2;
            }
            FUN_004bc470(fVar1 + _DAT_00858b1c);
            iVar12 = local_84;
            if (fVar1 < _DAT_0086f828) {
              *(float *)(iVar8 + 0x20) = fStack_98;
              *(undefined4 *)(iVar8 + 0x24) = uStack_94;
              *(undefined4 *)(iVar8 + 0x28) = uStack_90;
            }
            goto LAB_004bf216;
          }
        }
        if ((bVar7) && (iVar12 = local_84, !bVar5)) goto LAB_004bf216;
      }
LAB_004bf244:
      uStack_78 = *(undefined4 *)(*(int *)(iVar17 + 0x14) + 0x10);
      uStack_74 = 0;
      fStack_7c = -*(float *)(*(int *)(iVar17 + 0x14) + 0x14);
      FUN_0059c910();
      iVar11 = FUN_0061a5a0(0x1c);
      uStack_4 = 0xc;
      if (iVar11 == 0) goto LAB_004bf29b;
      iVar12 = FUN_006532d0(iVar17,&fStack_7c);
    }
  }
LAB_004bf216:
  param_1[9] = iVar12;
code_r0x004bf21c:
  FUN_0040399b();
  return;
}



/* function 004c2610 FUN_004c2610 */

void __thiscall FUN_004c2610(int *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  short sVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  float10 fVar8;
  float10 fVar9;
  int local_20;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0083b9a6;
  local_c = ExceptionList;
  iVar4 = *(int *)(param_2 + 0x20);
  if (iVar4 != 0) {
    local_20 = 4;
    ExceptionList = &local_c;
    cVar2 = FUN_0061a360(param_4);
    if (cVar2 != '\0') {
      local_20 = *(int *)(param_2 + 0x24);
    }
    sVar1 = *(short *)(param_2 + 0xe);
    if (sVar1 == 200) {
      param_1[9] = 0;
    }
    else if (sVar1 == 0x395) {
      iVar3 = FUN_00681740(0x4b7);
      if (((4 < local_20) && (iVar3 != 0)) && (iVar6 = *(int *)(iVar3 + 0x10), iVar6 != 0)) {
        if (*(int *)(iVar6 + 0x480) == 0) {
          iVar7 = FUN_00601d70();
        }
        else {
          iVar7 = *(int *)(iVar6 + 0x534);
        }
        iVar5 = FUN_00681740(0x38b);
        if ((iVar5 != 0) && (iVar7 < 6)) {
          iVar7 = *(int *)(*param_1 + 0x14);
          if (iVar7 == 0) {
            iVar7 = *param_1 + 4;
          }
          else {
            iVar7 = iVar7 + 0x30;
          }
          if (*(int *)(iVar6 + 0x14) == 0) {
            iVar6 = iVar6 + 4;
          }
          else {
            iVar6 = *(int *)(iVar6 + 0x14) + 0x30;
          }
          FUN_0040fe60(&uStack_18,iVar6,iVar7);
          uStack_10 = 0;
          fVar8 = (float10)FUN_00406da0();
          fVar9 = (float10)*(float *)(iVar5 + 0x1c) * (float10)*(float *)(iVar5 + 0x1c);
          if (fVar8 - fVar9 < fVar9) {
            local_20 = 4;
          }
        }
      }
      iVar6 = FUN_0061a5a0(0x60);
      uStack_4 = 0;
      if (iVar6 == 0) {
        iVar4 = 0;
      }
      else {
        iVar4 = FUN_0066a100(iVar4,param_2 + 0x14,local_20);
      }
      param_1[9] = iVar4;
      if (iVar3 != 0) {
        *(byte *)(iVar4 + 0x5c) = *(byte *)(iVar4 + 0x5c) | 4;
      }
    }
    else if (sVar1 == 0x4b9) {
      iVar3 = FUN_0061a5a0(0x74);
      uStack_4 = 1;
      if (iVar3 == 0) {
        param_1[9] = 0;
      }
      else {
        uStack_18 = 0;
        uStack_14 = 0;
        uStack_10 = 0;
        iVar4 = FUN_006846f0("CompPotPedCollResp",iVar4,1,0x3f000000,1,0,0,0);
        param_1[9] = iVar4;
      }
    }
  }
  ExceptionList = local_c;
  return;
}



/* function 0066a100 FUN_0066a100 */

undefined4 * __thiscall
FUN_0066a100(undefined4 *param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00845038;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_0061a3b0();
  param_1[3] = param_2;
  *param_1 = &PTR_FUN_0086fec4;
  param_1[7] = *param_3;
  param_1[8] = param_3[1];
  param_1[9] = param_3[2];
  param_1[10] = *param_3;
  param_1[0xb] = param_3[1];
  param_1[0xc] = param_3[2];
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  *(undefined1 *)(param_1 + 0x12) = 0;
  *(undefined1 *)((int)param_1 + 0x49) = 0;
  param_1[0x13] = 0;
  param_1[0x14] = 0;
  *(undefined1 *)(param_1 + 0x15) = 0;
  *(undefined1 *)((int)param_1 + 0x55) = 0;
  param_1[0x16] = param_4;
  local_4 = 0;
  *(byte *)(param_1 + 0x17) = *(byte *)(param_1 + 0x17) & 0xf8;
  if (param_1[3] != 0) {
    FUN_00571b70(param_1 + 3);
  }
  ExceptionList = local_c;
  return param_1;
}



/* function 00681e70 FUN_00681e70 */

undefined4 * __thiscall
FUN_00681e70(undefined4 *param_1,undefined4 param_2,int param_3,undefined1 param_4,
            undefined4 param_5,undefined1 param_6,undefined1 param_7,undefined4 param_8,
            undefined4 param_9,undefined4 param_10)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_008464d8;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_0061a3b0();
  *(undefined1 *)(param_1 + 0x16) = param_4;
  *(undefined1 *)((int)param_1 + 0x5d) = param_6;
  param_1[0xf] = param_5;
  *(undefined1 *)((int)param_1 + 0x5b) = param_7;
  param_1[0x10] = param_8;
  param_1[0x11] = param_9;
  local_4 = 0;
  *param_1 = &PTR_FUN_00870664;
  param_1[0xe] = param_3;
  param_1[0x12] = param_10;
  *(undefined1 *)((int)param_1 + 0x59) = 1;
  *(undefined1 *)(param_1 + 0x17) = 0;
  *(undefined1 *)((int)param_1 + 0x5a) = 0xff;
  *(undefined1 *)((int)param_1 + 0x6e) = 0;
  *(undefined1 *)((int)param_1 + 0x5e) = 0;
  if (param_3 != 0) {
    FUN_00571b70(param_1 + 0xe);
  }
  ExceptionList = local_c;
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


