/* Full-analysis function mapping; decompilation is not original source. */

/* function 004f0000 FUN_004f0000 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004f0000(ushort *param_1)

{
  undefined2 *puVar1;
  ushort uVar2;
  undefined4 uVar3;
  char cVar4;
  ushort uVar5;
  ushort uVar6;
  int iVar7;
  int iVar8;
  ushort *puVar9;
  undefined4 *puVar10;
  int iVar11;
  ushort *puVar12;
  short sVar13;
  short sVar14;
  short sVar15;
  short sVar16;
  int iVar17;
  float10 fVar18;
  float fVar19;
  int local_28;
  int local_20;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  sVar13 = 0;
  local_c = 0x3f800000;
  local_8 = 0;
  local_4 = 0;
  if (*param_1 != 0) {
    iVar7 = 0;
    do {
      sVar13 = sVar13 + 1;
      *(undefined2 *)(*(int *)(param_1 + 0x43fe) + iVar7 * 2) = 0xffff;
      iVar7 = (int)sVar13;
    } while (iVar7 < (int)(uint)*param_1);
  }
  uVar3 = DAT_00b7cb7c;
  if (((DAT_00b7cb49 == '\0') && (DAT_00b7cb48 == '\0')) &&
     (*(char *)((int)param_1 + 0x8cb5) == '\0')) {
    *(undefined4 *)(param_1 + 0x4658) = DAT_00b7cb84;
    *(undefined1 *)(param_1 + 0x465a) = 0;
  }
  else {
    if ((char)param_1[0x465a] == '\0') {
      *(undefined4 *)(param_1 + 0x465c) = *(undefined4 *)(param_1 + 0x4658);
    }
    *(undefined4 *)(param_1 + 0x4658) = uVar3;
    *(undefined1 *)(param_1 + 0x465a) = 1;
  }
  FUN_004d8820(param_1[1],*(undefined4 *)(param_1 + 0x43fc));
  FUN_004d8e90(param_1 + 0x4400);
  FUN_004d8eb0(param_1 + 0x452c);
  puVar12 = param_1 + 0x2d;
  iVar7 = 300;
  do {
    if (((puVar12[1] != 0) && (puVar12[2] != 0)) &&
       (((*puVar12 & 0x20) != 0 && (*(byte *)puVar12 = (byte)*puVar12 & 0xdf, puVar12[4] == 0)))) {
      uVar5 = FUN_00821b40();
      puVar12[3] = uVar5;
    }
    puVar12 = puVar12 + 0x3a;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  iVar7 = 0;
  if (*param_1 != 0) {
    iVar8 = 0;
    do {
      sVar13 = *(short *)(*(int *)(param_1 + 0x43fa) + iVar8 * 2);
      if ((sVar13 != -1) &&
         (param_1[sVar13 * 0x3a + 0x30] = *(ushort *)(*(int *)(param_1 + 0x43fc) + iVar8 * 2),
         param_1[*(short *)(*(int *)(param_1 + 0x43fa) + iVar8 * 2) * 0x3a + 0x36] != 0)) {
        FUN_004d88e0(param_1[1],iVar7);
      }
      iVar7 = iVar7 + 1;
      iVar8 = (int)(short)iVar7;
    } while (iVar8 < (int)(uint)*param_1);
  }
  puVar9 = param_1 + 0x4400;
  puVar12 = param_1 + 0x30;
  local_20 = 300;
  do {
    if (((puVar12[-2] != 0) && (puVar12[-1] != 0)) && ((char)puVar12[-4] == '\0')) {
      if ((((DAT_00b7cb49 == '\0') && (DAT_00b7cb48 == '\0')) &&
          (*(char *)((int)param_1 + 0x8cb5) == '\0')) || ((puVar12[-3] & 0x10) != 0)) {
        uVar5 = *puVar9;
        uVar2 = puVar9[300];
        puVar12[10] = uVar5;
        if (puVar12[1] == 0) {
          if (puVar12[6] == 0) goto LAB_004f02b4;
          *puVar12 = 0xffff;
        }
      }
      else {
        uVar5 = *puVar9;
        uVar2 = puVar9[300];
        puVar12[10] = uVar5;
        if (puVar12[1] == 0) {
          if (puVar12[6] == 0) {
LAB_004f02b4:
            uVar6 = FUN_00821b40();
            *puVar12 = uVar6;
            if ((short)uVar5 <= (short)uVar6) {
              if (uVar2 == 0xffff) {
                *puVar12 = 0xffff;
              }
              else {
                *puVar12 = (short)uVar6 % (short)uVar5 + uVar2;
              }
            }
          }
          else {
            *puVar12 = 0xffff;
          }
        }
      }
    }
    puVar9 = puVar9 + 1;
    puVar12 = puVar12 + 0x3a;
    local_20 = local_20 + -1;
    if (local_20 == 0) {
      sVar13 = 0;
      if (*param_1 != 0) {
        iVar7 = 0;
        do {
          if (*(short *)(*(int *)(param_1 + 0x43fc) + iVar7 * 2) == -1) {
            *(undefined2 *)(*(int *)(param_1 + 0x43fa) + iVar7 * 2) = 0xffff;
          }
          sVar13 = sVar13 + 1;
          iVar7 = (int)sVar13;
        } while (iVar7 < (int)(uint)*param_1);
      }
      puVar12 = param_1 + 6;
      iVar7 = 300;
      do {
        if (((puVar12[0x28] != 0) && ((char)puVar12[0x26] == '\0')) && (puVar12[0x2a] == 0xffff)) {
          if ((char)puVar12[0x27] < '\0') {
            iVar8 = *(int *)puVar12;
            if (iVar8 == 0) {
              puVar12[0x30] = 1;
            }
            else {
              if (*(int *)(iVar8 + 0x14) == 0) {
                puVar10 = (undefined4 *)(iVar8 + 4);
              }
              else {
                puVar10 = (undefined4 *)(*(int *)(iVar8 + 0x14) + 0x30);
              }
              FUN_004ef880(*puVar10,puVar10[1],puVar10[2]);
            }
          }
          if ((((puVar12[0x27] & 4) != 0) && (*(undefined4 **)(puVar12 + -2) != (undefined4 *)0x0))
             && ((**(code **)**(undefined4 **)(puVar12 + -2))(puVar12 + -4,0xffffffff),
                *(float *)(puVar12 + 0xc) == DAT_00858b50)) {
            *(undefined4 *)(puVar12 + 0x2e) = *(undefined4 *)(puVar12 + 10);
          }
          puVar12[0x28] = 0;
          if (*(int *)puVar12 != 0) {
            FUN_00571a00(puVar12);
            puVar12[0] = 0;
            puVar12[1] = 0;
          }
          puVar12[0x2b] = 0;
          puVar12[0x2a] = 0;
        }
        puVar12 = puVar12 + 0x3a;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
      puVar12 = param_1 + 0x30;
      iVar7 = 300;
      do {
        if (puVar12[-2] != 0) {
          FUN_004eff50(*puVar12);
        }
        puVar12 = puVar12 + 0x3a;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
      puVar12 = param_1 + 2;
      iVar7 = 300;
      do {
        if (puVar12[0x2c] != 0) {
          FUN_004efa10();
        }
        puVar12 = puVar12 + 0x3a;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
      sVar15 = 0;
      sVar14 = 0;
      sVar13 = 0;
      if (*param_1 != 0) {
        iVar7 = 0;
        do {
          sVar13 = *(short *)(*(int *)(param_1 + 0x43fa) + iVar7 * 2);
          if ((sVar13 != -1) && ((param_1[sVar13 * 0x3a + 0x2d] & 2) != 0)) {
            *(short *)(*(int *)(param_1 + 0x43fe) + sVar15 * 2) = sVar13;
            sVar15 = sVar15 + 1;
          }
          sVar14 = sVar14 + 1;
          iVar7 = (int)sVar14;
          sVar13 = sVar15;
        } while (iVar7 < (int)(uint)*param_1);
      }
      sVar14 = 0;
      puVar12 = param_1 + 0x31;
      do {
        if (((puVar12[-3] != 0) && ((*puVar12 == 0 || ((puVar12[-4] & 2) == 0)))) &&
           ((char)puVar12[-5] == '\0')) {
          sVar15 = *param_1 - 1;
          sVar16 = sVar15;
          if (sVar13 <= sVar15) {
            do {
              if (*(short *)(*(int *)(param_1 + 0x43fe) + sVar16 * 2) != -1) break;
              sVar16 = sVar16 + -1;
            } while (sVar13 <= sVar16);
          }
          if (sVar13 <= sVar16) {
            do {
              iVar7 = (int)*(short *)(*(int *)(param_1 + 0x43fe) + sVar16 * 2);
              if ((*(float *)(puVar12 + 1) < *(float *)(param_1 + iVar7 * 0x3a + 0x32)) &&
                 (((byte)puVar12[-4] >> 3 & 1) <= ((byte)param_1[iVar7 * 0x3a + 0x2d] >> 3 & 1)))
              break;
              sVar16 = sVar16 + -1;
            } while (sVar13 <= sVar16);
          }
          iVar7 = (int)sVar16;
          if (iVar7 != *param_1 - 1) {
            for (; iVar7 + 1 < (int)sVar15; sVar15 = sVar15 + -1) {
              puVar1 = (undefined2 *)(*(int *)(param_1 + 0x43fe) + sVar15 * 2);
              *puVar1 = puVar1[-1];
            }
            *(short *)(*(int *)(param_1 + 0x43fe) + 2 + iVar7 * 2) = sVar14;
          }
        }
        sVar14 = sVar14 + 1;
        puVar12 = puVar12 + 0x3a;
      } while (sVar14 < 300);
      iVar7 = 0;
      local_28 = 0;
      if (*param_1 != 0) {
        do {
          sVar13 = *(short *)(*(int *)(param_1 + 0x43fa) + iVar7 * 2);
          if (sVar13 != -1) {
            sVar14 = 0;
            if (*param_1 != 0) {
              iVar8 = 0;
              do {
                if (sVar13 == *(short *)(*(int *)(param_1 + 0x43fe) + iVar8 * 2)) break;
                sVar14 = sVar14 + 1;
                iVar8 = (int)sVar14;
              } while (iVar8 < (int)(uint)*param_1);
            }
            if ((int)sVar14 == (uint)*param_1) {
              param_1[sVar13 * 0x3a + 0x31] = 0;
              *(undefined2 *)(*(int *)(param_1 + 0x43fa) + iVar7 * 2) = 0xffff;
              FUN_004d88e0(param_1[1],local_28);
            }
            else {
              *(undefined2 *)(*(int *)(param_1 + 0x43fe) + sVar14 * 2) = 0xffff;
            }
          }
          local_28 = local_28 + 1;
          iVar7 = (int)(short)local_28;
        } while (iVar7 < (int)(uint)*param_1);
      }
      iVar8 = 0;
      iVar7 = 0;
      sVar13 = 0;
      if (*param_1 != 0) {
        do {
          sVar14 = *(short *)(*(int *)(param_1 + 0x43fe) + iVar8 * 2);
          if ((sVar14 != -1) && (iVar11 = (int)(short)iVar7, iVar11 < (int)(uint)*param_1)) {
            do {
              iVar17 = iVar7;
              if (*(short *)(*(int *)(param_1 + 0x43fa) + iVar11 * 2) == -1) {
                *(short *)(*(int *)(param_1 + 0x43fa) + (short)iVar17 * 2) = sVar14;
                iVar7 = 1;
                param_1[*(short *)(*(int *)(param_1 + 0x43fe) + iVar8 * 2) * 0x3a + 0x31] = 1;
                puVar12 = param_1 + *(short *)(*(int *)(param_1 + 0x43fe) + iVar8 * 2) * 0x3a + 2;
                if ((puVar12[0x2b] & 1) == 0) {
                  fVar18 = (float10)FUN_004d7e40(*(undefined4 *)(puVar12 + 0x26),
                                                 *(undefined4 *)(puVar12 + 0x24),
                                                 *(undefined4 *)(puVar12 + 0x22),
                                                 *(undefined4 *)(puVar12 + 0x20),
                                                 *(undefined4 *)(puVar12 + 0x28));
                  fVar18 = fVar18 * (float10)*(float *)(puVar12 + 0x32);
                }
                else {
                  fVar18 = (float10)*(float *)(puVar12 + 0x32);
                }
                fVar19 = _DAT_00858624;
                if ((((puVar12[0x2b] & 0x10) == 0) &&
                    (cVar4 = FUN_00561ad0(), fVar19 = _DAT_00858624, cVar4 != '\0')) &&
                   ((&DAT_00b6f1a8)[(uint)DAT_00b6f081 * 0x11c] != 0x2e)) {
                  fVar19 = _DAT_008cba6c;
                }
                uVar5 = puVar12[0x2b];
                if (((uVar5 & 1) == 0) || ((uVar5 & 0x10) == 0)) {
                  iVar7 = 0;
                }
                FUN_004d86b0(param_1[1],iVar17,puVar12[1],*puVar12,puVar12[0x2e],
                             iVar7 << 9 | ((uVar5 & 0x1000) >> 0xc) << 8 | (uVar5 >> 0xb & 1) << 7 |
                             (uVar5 >> 10 & 1) << 6 | (uVar5 >> 9 & 1) * 2 | (uVar5 >> 8 & 1) * 4 |
                             ((uVar5 & 0xff) >> 6 & 1) << 4 | ((uVar5 & 0xff) >> 5 & 1) * 8 |
                             (uint)((uVar5 & 1) != 0),*(undefined4 *)(puVar12 + 0xe));
                thunk_FUN_00402182(param_1[1],iVar17,*(undefined4 *)(puVar12 + 0x30),0);
                if ((puVar12[0x2b] & 1) == 0) {
                  FUN_004d80b0(&local_c,puVar12 + 0x12);
                }
                else {
                  local_c = *(undefined4 *)(puVar12 + 0x12);
                  local_8 = *(undefined4 *)(puVar12 + 0x14);
                  local_4 = *(undefined4 *)(puVar12 + 0x16);
                }
                FUN_004d8920(param_1[1],iVar17,&local_c,0);
                FUN_004d8960(param_1[1],iVar17,fVar19 * (float)fVar18);
                break;
              }
              iVar11 = (int)(short)(iVar17 + 1);
              iVar7 = iVar17 + 1;
            } while (iVar11 < (int)(uint)*param_1);
            iVar7 = iVar17 + 1;
          }
          sVar13 = sVar13 + 1;
          iVar8 = (int)sVar13;
        } while (iVar8 < (int)(uint)*param_1);
      }
      iVar7 = 0;
      if (*param_1 != 0) {
        iVar8 = 0;
        do {
          sVar13 = *(short *)(*(int *)(param_1 + 0x43fa) + iVar8 * 2);
          if ((sVar13 != -1) && (iVar8 = (int)sVar13, param_1[iVar8 * 0x3a + 0x2e] != 0)) {
            if ((DAT_00b7cb49 == '\0') &&
               ((DAT_00b7cb48 == '\0' && (*(char *)((int)param_1 + 0x8cb5) == '\0')))) {
              thunk_FUN_00402182(param_1[1],iVar7,*(undefined4 *)(param_1 + iVar8 * 0x3a + 0x32),0);
              if ((param_1[iVar8 * 0x3a + 0x2d] & 1) == 0) {
                fVar18 = (float10)FUN_004d7e40(*(undefined4 *)(param_1 + iVar8 * 0x3a + 0x28),
                                               *(undefined4 *)(param_1 + iVar8 * 0x3a + 0x26),
                                               *(undefined4 *)(param_1 + iVar8 * 0x3a + 0x24),
                                               *(undefined4 *)(param_1 + iVar8 * 0x3a + 0x22),
                                               *(undefined4 *)(param_1 + iVar8 * 0x3a + 0x2a));
                fVar18 = fVar18 * (float10)*(float *)(param_1 + iVar8 * 0x3a + 0x34);
              }
              else {
                fVar18 = (float10)*(float *)(param_1 + iVar8 * 0x3a + 0x34);
              }
              fVar19 = _DAT_00858624;
              if ((((param_1[iVar8 * 0x3a + 0x2d] & 0x10) == 0) &&
                  (cVar4 = FUN_00561ad0(), fVar19 = _DAT_00858624, cVar4 != '\0')) &&
                 ((&DAT_00b6f1a8)[(uint)DAT_00b6f081 * 0x11c] != 0x2e)) {
                fVar19 = _DAT_008cba6c;
              }
              fVar19 = fVar19 * (float)fVar18;
              uVar5 = param_1[1];
            }
            else if ((param_1[iVar8 * 0x3a + 0x2d] & 0x10) == 0) {
              thunk_FUN_00402182(param_1[1],iVar7,0xc2c80000,0);
              uVar5 = param_1[1];
              fVar19 = 0.0;
            }
            else {
              thunk_FUN_00402182(param_1[1],iVar7,*(undefined4 *)(param_1 + iVar8 * 0x3a + 0x32),0);
              if ((param_1[iVar8 * 0x3a + 0x2d] & 1) == 0) {
                fVar18 = (float10)FUN_004d7e40(*(undefined4 *)(param_1 + iVar8 * 0x3a + 0x28),
                                               *(undefined4 *)(param_1 + iVar8 * 0x3a + 0x26),
                                               *(undefined4 *)(param_1 + iVar8 * 0x3a + 0x24),
                                               *(undefined4 *)(param_1 + iVar8 * 0x3a + 0x22),
                                               *(undefined4 *)(param_1 + iVar8 * 0x3a + 0x2a));
                fVar18 = fVar18 * (float10)*(float *)(param_1 + iVar8 * 0x3a + 0x34);
              }
              else {
                fVar18 = (float10)*(float *)(param_1 + iVar8 * 0x3a + 0x34);
              }
              fVar19 = _DAT_00858624;
              if ((((param_1[iVar8 * 0x3a + 0x2d] & 0x10) == 0) &&
                  (cVar4 = FUN_00561ad0(), fVar19 = _DAT_00858624, cVar4 != '\0')) &&
                 ((&DAT_00b6f1a8)[(uint)DAT_00b6f081 * 0x11c] != 0x2e)) {
                fVar19 = _DAT_008cba6c;
              }
              fVar19 = fVar19 * (float)fVar18;
              uVar5 = param_1[1];
            }
            FUN_004d8960(uVar5,iVar7,fVar19);
            if ((param_1[iVar8 * 0x3a + 0x2d] & 1) == 0) {
              FUN_004d80b0(&local_c,param_1 + iVar8 * 0x3a + 0x14);
            }
            else {
              local_c = *(undefined4 *)(param_1 + iVar8 * 0x3a + 0x14);
              local_8 = *(undefined4 *)(param_1 + iVar8 * 0x3a + 0x16);
              local_4 = *(undefined4 *)(param_1 + iVar8 * 0x3a + 0x18);
            }
            FUN_004d8920(param_1[1],iVar7,&local_c,0);
          }
          iVar7 = iVar7 + 1;
          iVar8 = (int)(short)iVar7;
        } while (iVar8 < (int)(uint)*param_1);
      }
      FUN_004d9870();
      puVar12 = param_1 + 0x2f;
      iVar7 = 300;
      do {
        if (puVar12[-1] != 0) {
          *puVar12 = 1;
          if (('\0' < (char)puVar12[-3]) &&
             ((((DAT_00b7cb49 == '\0' && (DAT_00b7cb48 == '\0')) &&
               (*(char *)((int)param_1 + 0x8cb5) == '\0')) || ((puVar12[-2] & 0x10) != 0)))) {
            *(char *)(puVar12 + -3) = (char)puVar12[-3] + -1;
          }
        }
        puVar12 = puVar12 + 0x3a;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
      return;
    }
  } while( true );
}



/* function 005078a0 FUN_005078a0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_005078a0(float param_1)

{
  float10 fVar1;
  
  fVar1 = (float10)FUN_004d9590();
  if ((fVar1 < (float10)param_1) && (fVar1 + (float10)_DAT_00858b4c < (float10)param_1)) {
    param_1 = (float)(fVar1 + (float10)_DAT_00858b4c);
  }
  FUN_004d9560(param_1);
  FUN_004f0000();
  return;
}



/* function 00590ac0 FUN_00590ac0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00590ac0(float param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  
  iVar2 = (int)param_1;
  DAT_00bab31c = '\x01';
  if (param_1 == 0.0) {
    DAT_008d093c = DAT_008d093c + 1;
  }
  else {
    DAT_00bab31f = '\x01';
  }
  iVar3 = 0x14;
  do {
    DAT_00bab320 = 0;
    iVar1 = FUN_007ee190(DAT_00c1703c);
    if (iVar1 != 0) {
      FUN_00734750();
      (**(code **)(DAT_00c97b24 + 0x20))(0xc,1);
      FUN_0058ff60();
      if ((0 < DAT_008d093c) && ((DAT_00bab31c == '\0' || (DAT_008d093c != 1)))) {
        FUN_00590370();
      }
      FUN_007ee180(DAT_00c1703c);
      thunk_FUN_00745240(DAT_00c1703c);
    }
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  uVar4 = 0;
  do {
    DAT_00bab320 = FUN_00821b40();
    if ((iVar2 != 0) || (DAT_00bab31e != '\0')) {
      if (DAT_00bab31f == '\0') {
        param_1 = 1.0;
      }
      else {
        param_1 = (_DAT_00859aac - (float)DAT_00bab320) * _DAT_00859a3c;
      }
      FUN_005078a0(param_1);
    }
    iVar3 = FUN_007ee190(DAT_00c1703c);
    if (iVar3 != 0) {
      FUN_00734750();
      (**(code **)(DAT_00c97b24 + 0x20))(0xc,1);
      FUN_0058ff60();
      if ((0 < DAT_008d093c) && ((DAT_00bab31c == '\0' || (DAT_008d093c != 1)))) {
        FUN_00590370();
      }
      FUN_007ee180(DAT_00c1703c);
      thunk_FUN_00745240(DAT_00c1703c);
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < 0x32);
  DAT_00bab320 = 0xff;
  iVar3 = FUN_007ee190(DAT_00c1703c);
  if (iVar3 != 0) {
    FUN_00734750();
    (**(code **)(DAT_00c97b24 + 0x20))(0xc,1);
    FUN_0058ff60();
    if ((0 < DAT_008d093c) && ((DAT_00bab31c == '\0' || (DAT_008d093c != 1)))) {
      FUN_00590370();
    }
    FUN_007ee180(DAT_00c1703c);
    thunk_FUN_00745240(DAT_00c1703c);
  }
  DAT_00bab31e = 0;
  DAT_00bab31c = 0;
  if (iVar2 != 0) {
    DAT_00bab318 = 0;
    piVar5 = &DAT_00bab35c;
    do {
      if (*piVar5 != 0) {
        FUN_00727240();
      }
      piVar5 = piVar5 + 1;
    } while ((int)piVar5 < 0xbab378);
    iVar2 = FUN_00731850("loadscs");
    if (iVar2 != -1) {
      FUN_00731e90(iVar2);
      FUN_00731cd0(iVar2);
    }
  }
  return;
}



/* function 0053d0b0 FUN_0053d0b0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0053d0b0(int param_1)

{
  float fVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  int iVar10;
  undefined4 uVar11;
  uint uVar12;
  undefined4 *puVar13;
  int iVar14;
  undefined4 *puVar15;
  float *pfVar16;
  
  iVar10 = FUN_0056e210(0xffffffff);
  if (iVar10 != 0) {
    uVar11 = FUN_00821b40();
    *(undefined4 *)(param_1 + 0x48) = uVar11;
  }
  uVar12 = *(uint *)(param_1 + 0x3c);
  if (*(uint *)(param_1 + 0x4c) < uVar12) {
    *(uint *)(param_1 + 0x4c) = uVar12;
  }
  fVar1 = (float)(int)uVar12;
  pfVar16 = (float *)(param_1 + 0x8c);
  if ((int)uVar12 < 0) {
    fVar1 = fVar1 + _DAT_00858c54;
  }
  uVar12 = *(uint *)(param_1 + 0x40);
  *pfVar16 = fVar1 + *pfVar16;
  if (*(uint *)(param_1 + 0x50) < uVar12) {
    *(uint *)(param_1 + 0x50) = uVar12;
  }
  fVar1 = (float)(int)uVar12;
  if ((int)uVar12 < 0) {
    fVar1 = fVar1 + _DAT_00858c54;
  }
  uVar12 = *(uint *)(param_1 + 0x44);
  *(float *)(param_1 + 0x90) = fVar1 + *(float *)(param_1 + 0x90);
  if (*(uint *)(param_1 + 0x54) < uVar12) {
    *(uint *)(param_1 + 0x54) = uVar12;
  }
  fVar1 = (float)(int)uVar12;
  if ((int)uVar12 < 0) {
    fVar1 = fVar1 + _DAT_00858c54;
  }
  uVar12 = *(uint *)(param_1 + 0x48);
  *(float *)(param_1 + 0x94) = fVar1 + *(float *)(param_1 + 0x94);
  if (*(uint *)(param_1 + 0x58) < uVar12) {
    *(uint *)(param_1 + 0x58) = uVar12;
  }
  fVar1 = (float)(int)uVar12;
  if ((int)uVar12 < 0) {
    fVar1 = fVar1 + _DAT_00858c54;
  }
  *(float *)(param_1 + 0x98) = fVar1 + *(float *)(param_1 + 0x98);
  uVar12 = DAT_00b7cb84 - *(int *)(param_1 + 0x20);
  if (uVar12 < 0x7d1) {
    if (uVar12 < 1000) {
      *(int *)(param_1 + 0x24) = *(int *)(param_1 + 0x24) + 1;
    }
    else {
      *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x24);
      *(int *)(param_1 + 0x20) = DAT_00b7cb84;
      if (*(int *)(param_1 + 0x24) == 0) {
        *(undefined4 *)(param_1 + 0x24) = 1;
      }
      fVar1 = (float)*(int *)(param_1 + 0x24);
      if (*(int *)(param_1 + 0x24) < 0) {
        fVar1 = fVar1 + _DAT_00858c54;
      }
      fVar1 = _DAT_00858624 / fVar1;
      iVar10 = 4;
      *pfVar16 = fVar1 * *pfVar16;
      *(float *)(param_1 + 0x90) = fVar1 * *(float *)(param_1 + 0x90);
      *(float *)(param_1 + 0x94) = fVar1 * *(float *)(param_1 + 0x94);
      *(float *)(param_1 + 0x98) = fVar1 * *(float *)(param_1 + 0x98);
      *(undefined4 *)(param_1 + 0x24) = 0;
      puVar15 = (undefined4 *)(param_1 + 0x9c);
      do {
        puVar13 = puVar15 + 7;
        iVar14 = 7;
        do {
          *puVar13 = puVar13[-1];
          puVar13 = puVar13 + -1;
          iVar14 = iVar14 + -1;
        } while (iVar14 != 0);
        uVar11 = FUN_00821b40();
        *puVar15 = uVar11;
        *pfVar16 = 0.0;
        pfVar16 = pfVar16 + 1;
        puVar15 = puVar15 + 8;
        iVar10 = iVar10 + -1;
      } while (iVar10 != 0);
      *(undefined4 *)(param_1 + 0x14) = 0;
      iVar10 = 0;
      do {
        iVar14 = *(int *)(param_1 + 0x4c + iVar10 * 4);
        if (iVar14 == 0) {
          *(undefined4 *)(param_1 + 0x5c + iVar10 * 4) = 0;
        }
        else {
          fVar1 = (float)*(int *)(param_1 + 0x9c + iVar10 * 0x20);
          if (*(int *)(param_1 + 0x9c + iVar10 * 0x20) < 0) {
            fVar1 = fVar1 + _DAT_00858c54;
          }
          iVar2 = *(int *)((iVar10 + 5) * 0x20 + param_1);
          fVar9 = (float)iVar2;
          if (iVar2 < 0) {
            fVar9 = fVar9 + _DAT_00858c54;
          }
          fVar8 = (float)*(int *)(param_1 + 0xa4 + iVar10 * 0x20);
          if (*(int *)(param_1 + 0xa4 + iVar10 * 0x20) < 0) {
            fVar8 = fVar8 + _DAT_00858c54;
          }
          fVar7 = (float)*(int *)(param_1 + 0xa8 + iVar10 * 0x20);
          if (*(int *)(param_1 + 0xa8 + iVar10 * 0x20) < 0) {
            fVar7 = fVar7 + _DAT_00858c54;
          }
          fVar6 = (float)*(int *)(param_1 + 0xac + iVar10 * 0x20);
          if (*(int *)(param_1 + 0xac + iVar10 * 0x20) < 0) {
            fVar6 = fVar6 + _DAT_00858c54;
          }
          fVar5 = (float)*(int *)(param_1 + 0xb0 + iVar10 * 0x20);
          if (*(int *)(param_1 + 0xb0 + iVar10 * 0x20) < 0) {
            fVar5 = fVar5 + _DAT_00858c54;
          }
          fVar4 = (float)*(int *)(param_1 + 0xb4 + iVar10 * 0x20);
          if (*(int *)(param_1 + 0xb4 + iVar10 * 0x20) < 0) {
            fVar4 = fVar4 + _DAT_00858c54;
          }
          iVar2 = *(int *)(param_1 + 0xb8 + iVar10 * 0x20);
          fVar3 = (float)iVar2;
          if (iVar2 < 0) {
            fVar3 = fVar3 + _DAT_00858c54;
          }
          fVar1 = (fVar3 + fVar4 + fVar5 + fVar6 + fVar7 + fVar8 + fVar9 + fVar1) * _DAT_00858c48;
          fVar9 = (float)iVar14;
          if (iVar14 < 0) {
            fVar9 = fVar9 + _DAT_00858c54;
          }
          if (fVar9 < fVar1) {
            fVar1 = fVar9;
          }
          *(float *)(param_1 + 0x5c + iVar10 * 4) = fVar1;
        }
        if (iVar10 == 3) {
          fVar1 = *(float *)(param_1 + 0x68);
        }
        else if (iVar10 == 2) {
          fVar1 = *(float *)(param_1 + 100);
        }
        else {
          iVar14 = FUN_00561a40();
          fVar1 = (float)iVar14;
          if (iVar14 < 0) {
            fVar1 = fVar1 + _DAT_00858c54;
          }
          fVar1 = *(float *)(param_1 + 0x5c + iVar10 * 4) / fVar1;
        }
        fVar1 = fVar1 / *(float *)(param_1 + 0x6c + iVar10 * 4);
        if ((fVar1 <= _DAT_00863ad8) || (1 < *(int *)(param_1 + 0x14))) {
          if ((_DAT_00863ad4 < fVar1) && (*(int *)(param_1 + 0x14) < 1)) {
            *(undefined4 *)(param_1 + 0x14) = 1;
          }
        }
        else {
          *(undefined4 *)(param_1 + 0x14) = 2;
        }
        *(float *)(param_1 + 0x7c + iVar10 * 4) = fVar1;
        fVar1 = (float)*(int *)(param_1 + 0x4c + iVar10 * 4);
        if (*(int *)(param_1 + 0x4c + iVar10 * 4) < 0) {
          fVar1 = fVar1 + _DAT_00858c54;
        }
        iVar14 = iVar10 * 4;
        iVar10 = iVar10 + 1;
        *(float *)(param_1 + 0x58 + iVar10 * 4) = *(float *)(param_1 + 0x5c + iVar14) / fVar1;
      } while (iVar10 < 4);
    }
    if (*(int *)(param_1 + 8) != 0) {
      *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(param_1 + 0x18);
    }
    return;
  }
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(int *)(param_1 + 0x20) = DAT_00b7cb84;
  return;
}



/* function 0053bee0 FUN_0053bee0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0053bee0(void)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  float fStack_c;
  float fStack_8;
  undefined4 uStack_4;
  
  FUN_00541dd0();
  FUN_0053d030();
  uVar2 = FUN_00561a80();
  uVar3 = FUN_00561a40();
  FUN_0040e670();
  uVar4 = FUN_00561a80();
  uVar5 = FUN_00561a40();
  uVar2 = uVar4 / uVar5 - uVar2 / uVar3;
  FUN_004d5d00();
  if ((DAT_00b5f852 == '\0') && (DAT_00b7cb48 == '\0')) {
    FUN_0057b440();
  }
  FUN_00572d10();
  FUN_006997e0();
  if (DAT_00b6f03c == 0) {
    puVar6 = &DAT_00b6f02c;
  }
  else {
    puVar6 = (undefined4 *)(DAT_00b6f03c + 0x30);
  }
  FUN_005083c0(0,*puVar6,puVar6[1],puVar6[2]);
  DAT_00c81450 = 0;
  if ((DAT_00b7cb49 == '\0') && (DAT_00b7cb48 == '\0')) {
    FUN_00727260();
    FUN_00727350();
    FUN_00719800();
    thunk_FUN_01566d70();
    FUN_0052cf10();
    FUN_0072b850();
    FUN_0046a000();
    FUN_00411e20();
    FUN_00450a60(0);
    FUN_006f5900();
    FUN_006c79a0();
    FUN_0043dac0();
    FUN_007205c0();
    FUN_0071b0d0();
    FUN_00562360();
    FUN_00539ce0();
    thunk_FUN_01569c50();
    FUN_0053af00();
    if (uVar2 < 4) {
      uVar2 = FUN_00561a80();
      uVar3 = FUN_00561a40();
      FUN_00616650(1);
      uVar4 = FUN_00561a80();
      uVar5 = FUN_00561a40();
      uVar2 = uVar4 / uVar5 - uVar2 / uVar3;
    }
    else {
      FUN_00616650(0);
    }
    FUN_0073a360();
    if (DAT_00b5f851 == '\0') {
      FUN_006f3f40();
    }
    if (DAT_00a43088 != '\x01') {
      FUN_006f3fe0();
    }
    FUN_00712ff0();
    FUN_007185b0();
    FUN_0072a3c0();
    FUN_005720a0();
    FUN_00460500();
    FUN_005684a0();
    FUN_0053d0b0();
    if (DAT_00b7cb89 == '\0') {
      FUN_00458de0();
      FUN_00423f10();
      FUN_0044c8c0();
      FUN_00440d10();
      FUN_0049c490();
      FUN_00712330();
      FUN_00726aa0();
      FUN_00558d70();
    }
    FUN_007046a0();
    FUN_00561760();
    FUN_00610bf0();
    if ((DAT_00c0b184 & 1) != 0) {
      FUN_00605a30();
    }
    cVar1 = thunk_FUN_0156e610();
    if (cVar1 == '\0') {
      FUN_0050b5d0();
    }
    else {
      FUN_0052b730();
    }
    FUN_0072dec0();
    if (DAT_00a43088 != '\x01') {
      FUN_00442ad0();
      FUN_00446610();
    }
    thunk_FUN_0156d7c0();
    FUN_0043b0f0();
    FUN_0041bc80();
    FUN_006fc5a0();
    FUN_006fadf0();
    FUN_0070c950();
    if (DAT_00b6f03c == 0) {
      puVar6 = &DAT_00b6f02c;
    }
    else {
      puVar6 = (undefined4 *)(DAT_00b6f03c + 0x30);
    }
    FUN_005dcfa0(puVar6);
    FUN_005d8050();
    fStack_c = *(float *)(&DAT_00b79f90 + DAT_00b79fd0 * 4) +
               *(float *)(&DAT_00b79f90 + DAT_00b79fd0 * 4);
    uStack_4 = 0xbfc00000;
    fStack_8 = *(float *)(&DAT_00b79f50 + DAT_00b79fd0 * 4) +
               *(float *)(&DAT_00b79f50 + DAT_00b79fd0 * 4);
    FUN_00710b50(&fStack_c);
    if (DAT_00b6f03c == 0) {
      puVar6 = &DAT_00b6f02c;
    }
    else {
      puVar6 = (undefined4 *)(DAT_00b6f03c + 0x30);
    }
    FUN_00711d90(puVar6);
    if (DAT_00a43088 != '\x01') {
      if (uVar2 < 4) {
        FUN_004341c0();
      }
      FUN_004629e0();
      FUN_0042cd10();
      FUN_004322b0();
    }
    FUN_0049e640(DAT_00b6f97c,DAT_00b7cb5c * _DAT_00858b38);
    FUN_0059e670(DAT_00b7cb5c);
    FUN_00598f50();
    FUN_005a3110();
    FUN_006e4f10(DAT_00b7cb5c * _DAT_00858b38);
  }
  FUN_006eb710();
  return;
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



/* function 00722230 FUN_00722230 */

undefined4 __thiscall
FUN_00722230(int param_1,undefined4 param_2,ushort param_3,undefined4 param_4,undefined1 param_5,
            undefined1 param_6,undefined1 param_7,undefined1 param_8,undefined2 param_9,
            undefined4 param_10,undefined2 param_11)

{
  uint *puVar1;
  int iVar2;
  ushort uVar3;
  int iVar4;
  undefined4 uVar5;
  
  *(undefined4 *)(param_1 + 0x54) = param_2;
  FUN_0059ae70();
  uVar3 = param_3;
  param_2 = 0;
  uVar5 = DAT_00c7c6e0;
  if ((param_3 != 2) && (uVar5 = DAT_00c7c6dc, param_3 != 3)) {
    uVar5 = (&DAT_00c7c6dc)[param_3];
  }
  FUN_00749b70(uVar5,&LAB_00722220,&param_2);
  iVar4 = FUN_00749e60(param_2);
  uVar5 = FUN_007f0410();
  FUN_0074bf20(iVar4,uVar5);
  FUN_007328a0(iVar4,0);
  iVar2 = *(int *)(iVar4 + 0x18);
  puVar1 = (uint *)(iVar2 + 8);
  *puVar1 = *puVar1 | 0x40;
  *(int *)(param_1 + 0x48) = iVar4;
  FUN_0059bd10(*(int *)(iVar4 + 4) + 0x10,0);
  *(undefined4 *)(param_1 + 0x4c) = **(undefined4 **)(iVar2 + 0x20);
  *(undefined4 *)(param_1 + 0x6c) = param_4;
  *(undefined4 *)(param_1 + 0x68) = param_4;
  *(undefined1 *)(param_1 + 0x58) = param_5;
  *(undefined1 *)(param_1 + 0x59) = param_6;
  *(undefined1 *)(param_1 + 0x5a) = param_7;
  *(undefined1 *)(param_1 + 0x5b) = param_8;
  *(undefined2 *)(param_1 + 0x5c) = param_9;
  *(undefined4 *)(param_1 + 100) = param_10;
  *(undefined2 *)(param_1 + 0x5e) = param_11;
  *(undefined4 *)(param_1 + 0x60) = DAT_00b7cb84;
  *(undefined4 *)(param_1 + 0x90) = 0;
  *(undefined4 *)(param_1 + 0x94) = 0;
  *(ushort *)(param_1 + 0x50) = uVar3;
  *(undefined4 *)(param_1 + 0x8c) = 0x477fff00;
  *(undefined4 *)(param_1 + 0x98) = 0;
  *(undefined4 *)(param_1 + 0x9c) = DAT_00b7cb84;
  return CONCAT31((int3)((uint)*(int *)(param_1 + 0x48) >> 8),*(int *)(param_1 + 0x48) != 0);
}



/* function 00725120 FUN_00725120 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

short * FUN_00725120(int param_1,undefined4 param_2,float *param_3,float param_4,undefined4 param_5,
                    undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9,
                    float param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
                    undefined4 param_14,char param_15)

{
  undefined4 uVar1;
  float *pfVar2;
  char cVar3;
  undefined1 uVar4;
  short sVar5;
  short sVar6;
  float *pfVar7;
  int *piVar8;
  short *psVar9;
  int iVar10;
  float fVar11;
  float fVar12;
  short *psVar13;
  float10 fVar14;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float fVar15;
  float local_58;
  undefined1 local_54 [4];
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  undefined1 local_2c [8];
  undefined4 local_24;
  
  pfVar2 = param_3;
  pfVar7 = (float *)FUN_0056e250(0);
  local_4c = pfVar7[1];
  local_50 = *pfVar7;
  local_48 = pfVar7[2];
  psVar13 = (short *)0x0;
  sVar6 = (short)param_2;
  param_3 = (float *)SQRT((param_3[1] - local_4c) * (param_3[1] - local_4c) +
                          (*param_3 - local_50) * (*param_3 - local_50));
  if (sVar6 == 2) {
    param_3 = (float *)((float)param_3 * _DAT_00858c84);
  }
  else if (((((sVar6 != 0) && (sVar6 != 1)) && (sVar6 != 3)) && ((sVar6 != 4 && (sVar6 != 5)))) &&
          (sVar6 != 6)) {
    return (short *)0x0;
  }
  iVar10 = 0;
  piVar8 = &DAT_00c7ddac;
  do {
    if ((*(char *)((int)piVar8 + -2) == '\0') && (*piVar8 == param_1)) {
      psVar13 = (short *)(&DAT_00c7dd58 + iVar10 * 0xa0);
      if (psVar13 != (short *)0x0) goto LAB_00725498;
      break;
    }
    piVar8 = piVar8 + 0x28;
    iVar10 = iVar10 + 1;
  } while ((int)piVar8 < 0xc7f1ac);
  iVar10 = 0;
  psVar9 = &DAT_00c7dda8;
  do {
    if (*psVar9 == 0x101) {
      psVar13 = (short *)(&DAT_00c7dd58 + iVar10 * 0xa0);
      if (psVar13 != (short *)0x0) goto LAB_00725498;
      break;
    }
    psVar9 = psVar9 + 0x50;
    iVar10 = iVar10 + 1;
  } while ((int)psVar9 < 0xc7f1a8);
  if ((((sVar6 != 0) && (sVar6 != 3)) && (sVar6 != 5)) && (sVar6 != 6)) {
    return psVar13;
  }
  psVar9 = &DAT_00c7dda8;
  do {
    if (((float)param_3 < *(float *)(psVar9 + 0x12)) &&
       ((((sVar5 = *psVar9, sVar5 == 0 || (sVar5 == 3)) || ((sVar5 == 5 || (sVar5 == 6)))) &&
        ((psVar13 == (short *)0x0 || (*(float *)(psVar13 + 0x3a) < *(float *)(psVar9 + 0x12))))))) {
      psVar13 = psVar9 + -0x28;
    }
    if ((((float)param_3 < *(float *)(psVar9 + 0x62)) &&
        ((((sVar5 = psVar9[0x50], sVar5 == 0 || (sVar5 == 3)) || (sVar5 == 5)) || (sVar5 == 6)))) &&
       ((psVar13 == (short *)0x0 || (*(float *)(psVar13 + 0x3a) < *(float *)(psVar9 + 0x62))))) {
      psVar13 = psVar9 + 0x28;
    }
    if ((((float)param_3 < *(float *)(psVar9 + 0xb2)) &&
        (((sVar5 = psVar9[0xa0], sVar5 == 0 || (sVar5 == 3)) || ((sVar5 == 5 || (sVar5 == 6)))))) &&
       ((psVar13 == (short *)0x0 || (*(float *)(psVar13 + 0x3a) < *(float *)(psVar9 + 0xb2))))) {
      psVar13 = psVar9 + 0x78;
    }
    if (((float)param_3 < *(float *)(psVar9 + 0x102)) &&
       (((((sVar5 = psVar9[0xf0], sVar5 == 0 || (sVar5 == 3)) || (sVar5 == 5)) || (sVar5 == 6)) &&
        ((psVar13 == (short *)0x0 || (*(float *)(psVar13 + 0x3a) < *(float *)(psVar9 + 0x102)))))))
    {
      psVar13 = psVar9 + 200;
    }
    if ((((float)param_3 < *(float *)(psVar9 + 0x152)) &&
        (((sVar5 = psVar9[0x140], sVar5 == 0 || (sVar5 == 3)) || ((sVar5 == 5 || (sVar5 == 6))))))
       && ((psVar13 == (short *)0x0 || (*(float *)(psVar13 + 0x3a) < *(float *)(psVar9 + 0x152)))))
    {
      psVar13 = psVar9 + 0x118;
    }
    if ((((float)param_3 < *(float *)(psVar9 + 0x1a2)) &&
        ((((sVar5 = psVar9[400], sVar5 == 0 || (sVar5 == 3)) || (sVar5 == 5)) || (sVar5 == 6)))) &&
       ((psVar13 == (short *)0x0 || (*(float *)(psVar13 + 0x3a) < *(float *)(psVar9 + 0x1a2))))) {
      psVar13 = psVar9 + 0x168;
    }
    if (((float)param_3 < *(float *)(psVar9 + 0x1f2)) &&
       ((((sVar5 = psVar9[0x1e0], sVar5 == 0 || (sVar5 == 3)) || ((sVar5 == 5 || (sVar5 == 6)))) &&
        ((psVar13 == (short *)0x0 || (*(float *)(psVar13 + 0x3a) < *(float *)(psVar9 + 0x1f2)))))))
    {
      psVar13 = psVar9 + 0x1b8;
    }
    if ((((float)param_3 < *(float *)(psVar9 + 0x242)) &&
        ((((sVar5 = psVar9[0x230], sVar5 == 0 || (sVar5 == 3)) || (sVar5 == 5)) || (sVar5 == 6))))
       && ((psVar13 == (short *)0x0 || (*(float *)(psVar13 + 0x3a) < *(float *)(psVar9 + 0x242)))))
    {
      psVar13 = psVar9 + 0x208;
    }
    psVar9 = psVar9 + 0x280;
  } while ((int)psVar9 < 0xc7f1a8);
  if (psVar13 == (short *)0x0) {
    return (short *)0x0;
  }
  psVar13[0x28] = 0x101;
LAB_00725498:
  *(float **)(psVar13 + 0x3a) = param_3;
  if ((*(int *)(psVar13 + 0x2a) != param_1) || (psVar13[0x28] != sVar6)) {
    if (*(int *)(psVar13 + 0x2a) != 0) {
      psVar13[0x2a] = 0;
      psVar13[0x2b] = 0;
      psVar13[0x30] = 0;
      psVar13[0x31] = 0;
      *(undefined1 *)(psVar13 + 0x29) = 0;
      *(undefined1 *)((int)psVar13 + 0x53) = 0;
      psVar13[0x28] = 0x101;
      uVar1 = *(undefined4 *)(*(int *)(psVar13 + 0x24) + 4);
      FUN_00749dc0(*(int *)(psVar13 + 0x24));
      FUN_007f05a0(uVar1);
      psVar13[0x24] = 0;
      psVar13[0x25] = 0;
    }
    psVar13[0x42] = 30000;
    if ((sVar6 == 5) || (sVar6 == 6)) {
      fVar14 = (float10)fsin((float10)_DAT_00c7c700 * (float10)_DAT_008595ec);
      pfVar2[2] = (float)(fVar14 * (float10)_DAT_00858c24 + (float10)pfVar2[2]);
    }
    FUN_0059af40(*pfVar2,pfVar2[1],pfVar2[2]);
    FUN_00722230(param_1,param_2,param_4,param_5,param_6,param_7,param_8,param_9,param_10,param_11);
    if (sVar6 == 1) {
      cVar3 = FUN_006e8580(*(undefined4 *)(psVar13 + 0x18),*(undefined4 *)(psVar13 + 0x1a),
                           *(undefined4 *)(psVar13 + 0x1c),&local_58,0,0);
      if ((cVar3 == '\0') || (local_58 < *(float *)(psVar13 + 0x1c))) {
        FUN_00724d40(local_50,local_4c,local_48,param_4);
      }
      else {
        *(float *)(psVar13 + 0x1c) = local_58;
      }
    }
    FUN_0059bbb0();
    if ((((sVar6 == 0) || (sVar6 == 3)) || (sVar6 == 5)) || (sVar6 == 6)) {
      if (_DAT_00858fe8 <= (float)param_3) {
        *(float *)(psVar13 + 0x34) = param_4;
      }
      else if ((float)param_3 <= _DAT_00858c80) {
        *(float *)(psVar13 + 0x34) = param_4 - param_4 * _DAT_00858c24;
      }
      else {
        *(float *)(psVar13 + 0x34) =
             param_4 - (_DAT_00858fe8 - (float)param_3) * param_4 * _DAT_008717a8;
      }
    }
    if (sVar6 != 3) {
      if (param_4 + _DAT_00858ccc <= (float)param_3) {
        *(undefined1 *)((int)psVar13 + 0x5b) = (undefined1)param_8;
      }
      else if ((float)param_3 <= param_4 + _DAT_00858624) {
        uVar4 = FUN_00821b40();
        *(undefined1 *)((int)psVar13 + 0x5b) = uVar4;
      }
      else {
        uVar4 = FUN_00821b40();
        *(undefined1 *)((int)psVar13 + 0x5b) = uVar4;
      }
    }
    *(undefined4 *)(psVar13 + 0x3c) = param_12;
    *(undefined4 *)(psVar13 + 0x3e) = param_13;
    *(undefined4 *)(psVar13 + 0x40) = param_14;
    *(undefined1 *)(psVar13 + 0x29) = 1;
    return psVar13;
  }
  if ((sVar6 == 0) || (sVar6 == 5)) {
    fVar11 = *(float *)(*(int *)(psVar13 + 0x24) + 0x28);
    if (((*(float *)(psVar13 + 0x4c) * *(float *)(psVar13 + 0x4c) +
          *(float *)(psVar13 + 0x4a) * *(float *)(psVar13 + 0x4a) +
          *(float *)(psVar13 + 0x48) * *(float *)(psVar13 + 0x48) < _DAT_00858fc4) ||
        (1999 < (uint)(DAT_00b7cb84 - *(int *)(psVar13 + 0x4e)))) &&
       (((*(int *)(psVar13 + 0x4e) = DAT_00b7cb84, *(float *)(psVar13 + 0x48) != *pfVar2 ||
         (*(float *)(psVar13 + 0x4a) != pfVar2[1])) || (*(float *)(psVar13 + 0x4c) != pfVar2[2]))))
    {
      *(float *)(psVar13 + 0x48) = *pfVar2;
      *(float *)(psVar13 + 0x4a) = pfVar2[1];
      *(float *)(psVar13 + 0x4c) = pfVar2[2];
      local_34 = pfVar2[1];
      local_38 = *pfVar2;
      local_44 = *pfVar2;
      local_40 = pfVar2[1];
      local_3c = pfVar2[2];
      local_30 = pfVar2[2] - _DAT_00858ce8;
      cVar3 = FUN_0056ba00(&local_38,&local_44,local_2c,local_54,1,0,0,0,0,0,0,0);
      if (cVar3 == '\0') {
        psVar13[0x46] = -0x100;
        psVar13[0x47] = 0x477f;
      }
      else {
        *(undefined4 *)(psVar13 + 0x46) = local_24;
      }
    }
    if (*(float *)(psVar13 + 0x46) < _DAT_008729e8) {
      param_4 = param_4 * _DAT_00858b8c;
      pfVar2[2] = *(float *)(psVar13 + 0x46) - fVar11 * _DAT_00858b1c;
    }
    if (sVar6 != 5) goto LAB_00725622;
LAB_00725628:
    fVar14 = (float10)fsin((float10)_DAT_00c7c700 * (float10)_DAT_008595ec);
    fVar11 = _DAT_00858c24;
    if (*(float *)(psVar13 + 0x46) < _DAT_008729e8) {
      fVar11 = _DAT_00858fcc;
    }
    pfVar2[2] = (float)(fVar14 * (float10)fVar11 + (float10)pfVar2[2]);
  }
  else {
LAB_00725622:
    if (sVar6 == 6) goto LAB_00725628;
  }
  if ((((sVar6 == 0) || (sVar6 == 3)) || (sVar6 == 5)) || (sVar6 == 6)) {
    if (_DAT_00858fe8 <= (float)param_3) {
      *(float *)(psVar13 + 0x34) = param_4;
    }
    else if ((float)param_3 <= _DAT_00858c80) {
      *(float *)(psVar13 + 0x34) = param_4 - param_4 * _DAT_00858c24;
    }
    else {
      *(float *)(psVar13 + 0x34) =
           param_4 - (_DAT_00858fe8 - (float)param_3) * param_4 * _DAT_008717a8;
    }
  }
  if (sVar6 != 3) {
    if (param_4 + _DAT_00858ccc <= (float)param_3) {
      *(undefined1 *)((int)psVar13 + 0x5b) = (undefined1)param_8;
    }
    else if ((float)param_3 <= param_4 + _DAT_00858624) {
      uVar4 = FUN_00821b40();
      *(undefined1 *)((int)psVar13 + 0x5b) = uVar4;
    }
    else {
      uVar4 = FUN_00821b40();
      *(undefined1 *)((int)psVar13 + 0x5b) = uVar4;
    }
  }
  fVar14 = (float10)fsin((float10)_DAT_00859ef8);
  *(float *)(psVar13 + 0x36) =
       (float)((float10)*(float *)(psVar13 + 0x34) -
              fVar14 * (float10)*(float *)(psVar13 + 0x34) * (float10)param_10);
  if (psVar13[0x2f] != 0) {
    local_44 = *(float *)(psVar13 + 0x18);
    local_40 = *(float *)(psVar13 + 0x1a);
    local_3c = *(float *)(psVar13 + 0x1c);
    FUN_0059b390((float)(int)psVar13[0x2f] * DAT_00b7cb5c * _DAT_008595ec);
    *(float *)(psVar13 + 0x18) = local_44;
    *(float *)(psVar13 + 0x1a) = local_40;
    sVar5 = FUN_00821b40();
    if ((psVar13[0x42] != sVar5) || (sVar5 = FUN_00821b40(), psVar13[0x43] != sVar5)) {
      *(float *)(psVar13 + 0x1c) = local_3c;
    }
  }
  if (((sVar6 == 0) || (sVar6 == 1)) || ((sVar6 == 5 || (sVar6 == 6)))) {
    *(float *)(psVar13 + 0x18) = *pfVar2;
    *(float *)(psVar13 + 0x1a) = pfVar2[1];
    sVar5 = FUN_00821b40();
    fVar14 = extraout_ST0;
    if ((psVar13[0x42] != sVar5) ||
       (sVar5 = FUN_00821b40(), fVar14 = extraout_ST0_00, psVar13[0x43] != sVar5)) {
      *(float *)(psVar13 + 0x1c) = (float)fVar14;
    }
  }
  if ((sVar6 == 4) || (sVar6 == 2)) {
    *(float *)(psVar13 + 0x18) = *pfVar2;
    *(float *)(psVar13 + 0x1a) = pfVar2[1];
    if ((sVar6 != 2) || (param_15 == '\0')) {
      *(float *)(psVar13 + 0x1c) = pfVar2[2];
      goto LAB_007258be;
    }
    sVar6 = FUN_00821b40();
    if ((psVar13[0x42] != sVar6) || (sVar6 = FUN_00821b40(), psVar13[0x43] != sVar6)) {
      *(float *)(psVar13 + 0x1c) = pfVar2[2];
    }
    param_4 = 10.0;
    fVar11 = pfVar2[2];
    fVar12 = pfVar2[1];
    fVar15 = *pfVar2;
  }
  else {
LAB_007258be:
    if (sVar6 != 1) goto LAB_00725921;
    cVar3 = FUN_006e8580(*(undefined4 *)(psVar13 + 0x18),*(undefined4 *)(psVar13 + 0x1a),
                         *(undefined4 *)(psVar13 + 0x1c),&local_58,0,0);
    fVar11 = local_48;
    fVar12 = local_4c;
    fVar15 = local_50;
    if ((cVar3 != '\0') && (*(float *)(psVar13 + 0x1c) <= local_58)) {
      *(float *)(psVar13 + 0x1c) = local_58;
      goto LAB_00725921;
    }
  }
  FUN_00724d40(fVar15,fVar12,fVar11,param_4);
LAB_00725921:
  *(undefined4 *)(psVar13 + 0x3e) = param_13;
  *(undefined4 *)(psVar13 + 0x3c) = param_12;
  *(undefined4 *)(psVar13 + 0x40) = param_14;
  *(undefined1 *)(psVar13 + 0x29) = 1;
  return psVar13;
}



/* function 00725c00 FUN_00725c00 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00725c00(short *param_1)

{
  float fVar1;
  float fVar2;
  bool bVar3;
  short sVar4;
  uint uVar5;
  char cVar6;
  float *pfVar7;
  float local_54;
  uint local_50;
  float fStack_4c;
  float fStack_48;
  uint local_44;
  uint local_40;
  float local_3c;
  float local_38;
  float local_34;
  undefined4 uStack_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_10;
  undefined1 local_c [12];
  
  switch(*param_1) {
  case 0:
  case 1:
  case 2:
    pfVar7 = (float *)(param_1 + 8);
    local_50 = CONCAT31(local_50._1_3_,1);
    cVar6 = FUN_006e8580(*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 10),
                         *(undefined4 *)(param_1 + 0xc),&local_54,0,0);
    if ((cVar6 != '\0') && (*(float *)(param_1 + 0xc) <= local_54)) {
      *(float *)(param_1 + 0xc) = local_54;
      local_50 = local_50 & 0xffffff00;
    }
    local_40 = (uint)*(byte *)((int)param_1 + 9);
    local_44 = (uint)*(byte *)(param_1 + 5);
    sVar4 = param_1[4];
    local_3c = *pfVar7;
    local_38 = *(float *)(param_1 + 10);
    bVar3 = false;
    local_34 = *(float *)(param_1 + 0xc) + _DAT_00858b3c;
    if (*param_1 == 1) {
      (**(code **)(DAT_00c97b24 + 0x20))(1,*DAT_00c7c718);
      (**(code **)(DAT_00c97b24 + 0x20))(8,0);
      (**(code **)(DAT_00c97b24 + 0x20))(6,1);
      (**(code **)(DAT_00c97b24 + 0x20))(0xc,1);
      (**(code **)(DAT_00c97b24 + 0x20))(2,1);
      cVar6 = FUN_0070ce30(&local_3c,&uStack_30,&fStack_48,&fStack_4c,0,1);
      if (cVar6 != '\0') {
        FUN_0070d000(uStack_30,local_2c,local_28,
                     fStack_48 * *(float *)(param_1 + 0x16) * _DAT_00858b8c,
                     fStack_4c * *(float *)(param_1 + 0x16) * _DAT_00858b8c,(char)param_1[4],
                     *(undefined1 *)((int)param_1 + 9),(char)param_1[5],0xff,
                     _DAT_00858624 / local_28,*(undefined1 *)((int)param_1 + 0xb),0,0);
      }
      (**(code **)(DAT_00c97b24 + 0x20))(1,0);
      (**(code **)(DAT_00c97b24 + 0x20))(8,1);
      (**(code **)(DAT_00c97b24 + 0x20))(6,1);
      (**(code **)(DAT_00c97b24 + 0x20))(0xc,0);
    }
    else {
      bVar3 = true;
    }
    FUN_00725120(*(undefined4 *)(param_1 + 2),2,pfVar7,*(float *)(param_1 + 0x16) * _DAT_00858ce8,
                 (char)sVar4,local_40,local_44,0x80,param_1[6],*(undefined4 *)(param_1 + 0x14),1,0,0
                 ,0,local_50);
    if ((bVar3) && (*param_1 == 0)) {
      FUN_00721140(*pfVar7,*(undefined4 *)(param_1 + 10),*(undefined4 *)(param_1 + 0xc),
                   *(float *)(param_1 + 0x16) * _DAT_008652dc,0xff,0x40,0x40,0xff,
                   -*(float *)(param_1 + 0xe),-*(float *)(param_1 + 0x10),
                   -*(float *)(param_1 + 0x12));
      return;
    }
    break;
  case 3:
    pfVar7 = (float *)FUN_0056e010(local_c,0xffffffff);
    fVar1 = *pfVar7 - *(float *)(param_1 + 8);
    fVar1 = SQRT(fVar1 * fVar1 +
                 (pfVar7[1] - *(float *)(param_1 + 10)) * (pfVar7[1] - *(float *)(param_1 + 10)) +
                 (pfVar7[2] - *(float *)(param_1 + 0xc)) * (pfVar7[2] - *(float *)(param_1 + 0xc)));
    fVar2 = *(float *)(param_1 + 0x16) + *(float *)(param_1 + 0x16);
    if (fVar2 < fVar1 != (fVar2 == fVar1)) {
      FUN_00725120(*(undefined4 *)(param_1 + 2),4,param_1 + 8,*(undefined4 *)(param_1 + 0x16),
                   (char)param_1[4],*(undefined1 *)((int)param_1 + 9),(char)param_1[5],
                   *(undefined1 *)((int)param_1 + 0xb),param_1[6],*(undefined4 *)(param_1 + 0x14),
                   param_1[7],*(undefined4 *)(param_1 + 0xe),*(undefined4 *)(param_1 + 0x10),
                   *(undefined4 *)(param_1 + 0x12),0);
      return;
    }
    break;
  case 6:
    local_50 = 1;
    do {
      uVar5 = local_50;
      fVar1 = (float)(int)local_50;
      local_54 = *(float *)(param_1 + 0x1a);
      local_2c = fVar1 * *(float *)(param_1 + 0x10);
      local_28 = fVar1 * *(float *)(param_1 + 0x12);
      local_10 = local_28 * local_54;
      local_3c = fVar1 * *(float *)(param_1 + 0xe) * local_54 + *(float *)(param_1 + 8);
      local_38 = local_2c * local_54 + *(float *)(param_1 + 10);
      local_34 = local_10 + *(float *)(param_1 + 0xc);
      local_24 = local_3c;
      local_20 = local_38;
      local_1c = local_34;
      FUN_00725120(*(undefined4 *)(param_1 + 2),4,&local_24,*(undefined4 *)(param_1 + 0x16),
                   (char)param_1[4],*(undefined1 *)((int)param_1 + 9),(char)param_1[5],
                   *(char *)((int)param_1 + 0xb) + (char)local_50 * -0x10,param_1[6],
                   *(undefined4 *)(param_1 + 0x14),param_1[7],*(undefined4 *)(param_1 + 0xe),
                   *(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x12),0);
      local_50 = uVar5 + 1;
    } while ((int)local_50 < 4);
  case 4:
  case 5:
  case 7:
  case 8:
    FUN_00725120(*(undefined4 *)(param_1 + 2),4,param_1 + 8,*(undefined4 *)(param_1 + 0x16),
                 (char)param_1[4],*(undefined1 *)((int)param_1 + 9),(char)param_1[5],
                 *(undefined1 *)((int)param_1 + 0xb),param_1[6],*(undefined4 *)(param_1 + 0x14),
                 param_1[7],*(undefined4 *)(param_1 + 0xe),*(undefined4 *)(param_1 + 0x10),
                 *(undefined4 *)(param_1 + 0x12),0);
  }
  return;
}



/* function 00576b70 FUN_00576b70 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00576b70(int param_1)

{
  char cVar1;
  int iVar2;
  bool bVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  if ((((((((*(char *)(param_1 + 0x5c) == '\0') ||
           (cVar1 = *(char *)(param_1 + 0x15d), cVar1 == ')')) || (cVar1 == '\x10')) ||
         (cVar1 == '\x16')) &&
        (((FUN_0053fb70(*(undefined1 *)(param_1 + 0xea)), DAT_00b733a8 != 0 && (DAT_00b73138 == 0))
         && ((DAT_00a43088 != '\x01' &&
             ((DAT_00b6f065 == '\0' || (*(char *)(param_1 + 0x34) != '\0')))))))) ||
       (*(char *)(param_1 + 0x32) != '\0')) || (*(char *)(param_1 + 0x33) != '\0')) &&
     (cVar1 = FUN_00506ff0(), cVar1 == '\0')) {
    if ((*(char *)(param_1 + 0x15d) == '\x12') || (*(char *)(param_1 + 0x15d) == '\x0e'))
    goto LAB_00576fcd;
    if (((*(char *)(param_1 + 0x35) == '\0') || (*(char *)(param_1 + 0x33) == '\0')) &&
       (*(char *)(param_1 + 0x60) == '\0')) {
      FUN_00506ea0(0,0,0x3f800000);
      FUN_00507750();
    }
    *(bool *)(param_1 + 0x5c) = *(char *)(param_1 + 0x5c) == '\0';
    if (*(char *)(param_1 + 0x32) != '\0') {
      *(undefined1 *)(param_1 + 0x5c) = 0;
    }
    if (*(char *)(param_1 + 0x33) != '\0') {
      *(undefined1 *)(param_1 + 0x5c) = 1;
    }
    if (*(char *)(param_1 + 0x5c) == '\0') {
      FUN_00506f70(0,0);
      FUN_00506ea0(0x23,0,0x3f800000);
      if (-1 < *(char *)(param_1 + 0x30)) {
        FUN_00580750(*(char *)(param_1 + 0x30));
        *(undefined1 *)(param_1 + 0x30) = 0x9d;
      }
      uVar5 = 1;
      uVar4 = 0;
      FUN_0053fb70(*(undefined1 *)(param_1 + 0xea),0,1);
      FUN_00541a70(uVar4,uVar5);
      FUN_0053fb70(*(undefined1 *)(param_1 + 0xea));
      FUN_0053f1e0();
      FUN_0053fb70(*(undefined1 *)(param_1 + 0xea));
      FUN_00541bd0();
      cVar1 = FUN_00745ca0();
      if (cVar1 != '\0') {
        FUN_00746f70();
        FUN_007469a0(1);
      }
      *(undefined4 *)(param_1 + 4) = 0x43160000;
      FUN_0057c660();
      *(undefined4 *)(param_1 + 0xf0) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined1 *)(param_1 + 0x1ae8) = 0;
      *(undefined1 *)(param_1 + 0x32) = 0;
      *(undefined1 *)(param_1 + 0x33) = 0;
      *(undefined1 *)(param_1 + 0x1b09) = 0;
      *(undefined1 *)(param_1 + 0x5f) = 0;
      FUN_00574630();
      FUN_00561b00();
      FUN_00561b10();
      iVar2 = FUN_0053fb70(*(undefined1 *)(param_1 + 0xea));
      *(undefined1 *)(iVar2 + 0x117) = 1;
      iVar2 = FUN_0053fb70(*(undefined1 *)(param_1 + 0xea));
      *(undefined4 *)(iVar2 + 0x120) = 0;
      iVar2 = FUN_0053fb70(1);
      *(undefined4 *)(iVar2 + 0x120) = 0;
      FUN_00747200((float)*(int *)(param_1 + 0x3c) * _DAT_00863a44,1);
      if (*(char *)(param_1 + 0xf4) != '\0') {
        iVar2 = FUN_0056e210(0xffffffff);
        if ((*(int *)(*(char *)(iVar2 + 0x718) * 0x1c + 0x5a0 + iVar2) != 0x2b) ||
           (*(uint *)((*(char *)(iVar2 + 0x718) + 0x34) * 0x1c + iVar2) <= DAT_00b7cb84)) {
          FUN_0050bf00(0,0,0);
          thunk_FUN_0040116d(0,0);
          FUN_0050b5d0();
          thunk_FUN_0040116d(0x3e4ccccd,1);
        }
      }
      *(undefined1 *)(param_1 + 0xf4) = 0;
      iVar2 = FUN_0053fb70(*(undefined1 *)(param_1 + 0xea));
      *(undefined2 *)(iVar2 + 0x10e) = DAT_00ba827c;
    }
    else if (*(char *)(param_1 + 0xf4) == '\0') {
      FUN_0053d690(0,0,0,0,0,0,0xff);
      FUN_0053d840();
      FUN_0053d690(0,0,0,0,0,0,0xff);
      FUN_0053d840();
      iVar2 = FUN_0053fb70(*(undefined1 *)(param_1 + 0xea));
      DAT_00ba827c = *(undefined2 *)(iVar2 + 0x10e);
      iVar2 = FUN_0053fb70(*(undefined1 *)(param_1 + 0xea));
      *(undefined2 *)(iVar2 + 0x10e) = 1;
      uVar5 = 1;
      uVar4 = 0;
      FUN_0053fb70(*(undefined1 *)(param_1 + 0xea),0,1);
      FUN_00541a70(uVar4,uVar5);
      FUN_0053fb70(*(undefined1 *)(param_1 + 0xea));
      FUN_0053f1e0();
      FUN_0053fb70(*(undefined1 *)(param_1 + 0xea));
      FUN_00541bd0();
      cVar1 = FUN_00745ca0();
      if (cVar1 != '\0') {
        FUN_00746f70();
        FUN_007469a0(0);
      }
      FUN_005744d0();
      FUN_00572ec0();
      FUN_00747200((float)*(int *)(param_1 + 0x3c) * _DAT_00863a44,1);
    }
  }
  if (*(char *)(param_1 + 0x5f) != '\0') {
    FUN_0053d690(0,0,0,0,0,0,0xff);
    FUN_0053d840();
    FUN_0053d690(0,0,0,0,0,0,0xff);
    FUN_0053d840();
    FUN_00506ea0(0,0,0x3f800000);
    FUN_00507750();
    iVar2 = FUN_0053fb70(*(undefined1 *)(param_1 + 0xea));
    DAT_00ba827c = *(undefined2 *)(iVar2 + 0x10e);
    iVar2 = FUN_0053fb70(*(undefined1 *)(param_1 + 0xea));
    *(undefined2 *)(iVar2 + 0x10e) = 1;
    *(undefined1 *)(param_1 + 0x5f) = 0;
    *(undefined1 *)(param_1 + 0x5c) = 1;
    *(undefined1 *)(param_1 + 0xf4) = 1;
    cVar1 = FUN_00745ca0();
    if (cVar1 != '\0') {
      FUN_00746f70();
      FUN_007469a0(0);
    }
    FUN_005744d0();
    FUN_00572ec0();
    bVar3 = DAT_0096918c != '\0';
    *(undefined4 *)(param_1 + 0x54) = 0;
    if (bVar3) {
      *(undefined1 *)(param_1 + 0x33) = 0;
      *(undefined1 *)(param_1 + 0x32) = 0;
      *(undefined1 *)(param_1 + 0x15d) = 0x16;
      return;
    }
    *(undefined1 *)(param_1 + 0x15d) = 0x10;
  }
  *(undefined1 *)(param_1 + 0x33) = 0;
LAB_00576fcd:
  *(undefined1 *)(param_1 + 0x32) = 0;
  return;
}



/* function 0057b440 FUN_0057b440 */

void __fastcall FUN_0057b440(int param_1)

{
  if (*(char *)(param_1 + 0x5c) != '\0') {
    FUN_00573cf0(*(undefined1 *)(param_1 + 0x5b));
    FUN_0057fd70();
    FUN_00578d60();
    FUN_00730740(1);
    FUN_007305e0(1);
  }
  FUN_00576b70();
  return;
}


