/* Full-analysis function mapping; decompilation is not original source. */

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


