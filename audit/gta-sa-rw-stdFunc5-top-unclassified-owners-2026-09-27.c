/* Full-analysis function mapping; decompilation is not original source. */

/* function 0077c8d2 FUN_0077c8d2 */

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_0077c8d2(int param_1,uint *param_2,uint *param_3)

{
  byte *pbVar1;
  double dVar2;
  int iVar3;
  int *piVar4;
  uint *puVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  int iVar8;
  uint *puVar9;
  uint uVar10;
  uint *puVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  int iVar15;
  bool bVar16;
  undefined8 uVar17;
  ulonglong uVar18;
  longlong lVar19;
  char *pcVar20;
  uint *local_a4;
  uint *local_a0;
  undefined4 local_9c;
  uint uStack_98;
  uint local_94;
  uint *local_90;
  uint *local_8c;
  int local_88;
  undefined4 local_84;
  undefined4 local_80;
  uint local_7c;
  uint *local_78;
  int local_74;
  uint *local_70 [10];
  uint local_48 [2];
  uint *local_40;
  uint *local_3c;
  uint *local_38;
  uint *local_34;
  uint *local_30;
  uint *local_2c;
  uint *local_28;
  uint *local_24;
  uint *local_20;
  uint *local_1c;
  uint *local_18;
  uint *local_14;
  uint *local_10;
  uint *local_c;
  uint *local_8;
  
  if (param_2 == (uint *)0x0) {
    if (param_3 != (uint *)0x0) {
      return 0x80004005;
    }
    return 0;
  }
  if (*(int *)((int)param_2 + 4) != 0xc) {
    return 0x80004005;
  }
  local_8 = (uint *)(*(int *)((int)param_2 + 0x14) * *(int *)((int)param_2 + 0x18));
  puVar11 = *(uint **)((int)param_2 + 0x20);
  local_c = (uint *)0x0;
  local_2c = (uint *)0x0;
  local_14 = (uint *)0x0;
  local_28 = (uint *)0x0;
  local_30 = (uint *)0x0;
  local_10 = (uint *)0x0;
  local_20 = (uint *)0x0;
  local_8c = (uint *)0x0;
  local_90 = (uint *)0x0;
  if ((puVar11 != (uint *)0x0) && (puVar11[1] == 0xc)) {
    local_c = (uint *)(puVar11[6] * puVar11[5]);
    local_10 = puVar11;
  }
  puVar11 = *(uint **)((int)param_2 + 0x24);
  if ((puVar11 != (uint *)0x0) && (puVar11[1] == 0xc)) {
    local_2c = (uint *)(puVar11[6] * puVar11[5]);
    local_20 = puVar11;
  }
  if (((local_10 != (uint *)0x0) &&
      (local_14 = operator_new((int)local_c << 2), local_14 == (uint *)0x0)) ||
     ((local_20 != (uint *)0x0 &&
      (local_28 = operator_new((int)local_2c << 2), local_28 == (uint *)0x0)))) goto LAB_0077e4fb;
  if (*(int *)((int)param_2 + 0x28) == 0) {
    if ((local_20 != (uint *)0x0) && (iVar3 = FUN_0077c8d2(local_20), iVar3 < 0)) goto LAB_0077e7bf;
    if (local_10 != (uint *)0x0) {
      uVar17 = CONCAT44(local_14,local_10);
      goto LAB_0077c9f8;
    }
  }
  else {
    if ((local_10 != (uint *)0x0) && (iVar3 = FUN_0077c8d2(local_10), iVar3 < 0)) goto LAB_0077e7bf;
    if (local_20 != (uint *)0x0) {
      uVar17 = CONCAT44(local_28,local_20);
LAB_0077c9f8:
      iVar3 = FUN_0077c8d2(uVar17);
      if (iVar3 < 0) goto LAB_0077e7bf;
    }
  }
  puVar11 = local_8;
  puVar5 = param_3;
  switch(*(undefined4 *)((int)param_2 + 0x1c)) {
  case 0:
  case 1:
    if (local_10 == (uint *)0x0) {
      iVar3 = FUN_0077e869(*(undefined4 *)((int)param_2 + 0x20),param_3,local_8);
      goto LAB_0077ce22;
    }
    if (param_3 == (uint *)0x0) goto LAB_0077e7bf;
    if (local_c == (uint *)0x1) {
      puVar11 = (uint *)0x0;
      if (local_8 != (uint *)0x0) {
        do {
          param_3[(int)puVar11] = *local_14;
          puVar11 = (uint *)((int)puVar11 + 1);
        } while (puVar11 < local_8);
      }
    }
    else {
      puVar9 = local_8;
      puVar11 = local_14;
      if ((local_8 == local_c) ||
         ((uVar14 = *(uint *)((int)param_2 + 0x14), uVar14 == 1 && (local_8 < local_c))))
      goto code_r0x0077e053;
      if ((local_10[5] < uVar14) || (local_10[6] < *(uint *)((int)param_2 + 0x18)))
      goto LAB_0077e7bf;
      uVar12 = 0;
      if (uVar14 != 0) {
        do {
          iVar15 = local_10[6] * uVar12;
          iVar3 = *(int *)((int)param_2 + 0x18);
          iVar8 = iVar3 * uVar12;
          uVar12 = uVar12 + 1;
          puVar11 = local_14 + iVar15;
          puVar5 = param_3 + iVar8;
          for (; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar5 = *puVar11;
            puVar11 = puVar11 + 1;
            puVar5 = puVar5 + 1;
          }
        } while (uVar12 < *(uint *)((int)param_2 + 0x14));
      }
    }
    goto LAB_0077ca5a;
  case 2:
    if (local_10 == (uint *)0x0) goto LAB_0077e7bf;
    local_c = (uint *)((int)local_8 << 2);
    local_28 = operator_new((uint)local_c);
    if (local_28 != (uint *)0x0) {
      puVar5 = (uint *)0x0;
      if (puVar11 != (uint *)0x0) {
        do {
          local_28[(int)puVar5] = *(uint *)(param_1 + 0x20);
          puVar5 = (uint *)((int)puVar5 + 1);
        } while (puVar5 < puVar11);
      }
LAB_0077cc60:
      iVar3 = FUN_00773e3b(param_2,(uint)local_8 & 0xffffff | 0x24000000,local_14,local_14,local_28,
                           0);
      if ((iVar3 < 0) || (param_3 == (uint *)0x0)) goto LAB_0077e7bf;
      puVar11 = local_14;
      puVar5 = param_3;
      for (uVar14 = (uint)local_c >> 2; uVar14 != 0; uVar14 = uVar14 - 1) {
        *puVar5 = *puVar11;
        puVar11 = puVar11 + 1;
        puVar5 = puVar5 + 1;
      }
      for (uVar14 = (uint)local_c & 3; uVar14 != 0; uVar14 = uVar14 - 1) {
        *(char *)puVar5 = (char)*puVar11;
        puVar11 = (uint *)((int)puVar11 + 1);
        puVar5 = (uint *)((int)puVar5 + 1);
      }
      goto LAB_0077ca5a;
    }
    break;
  case 3:
    if (local_10 == (uint *)0x0) goto LAB_0077e7bf;
    local_c = (uint *)((int)local_8 << 2);
    local_28 = operator_new((uint)local_c);
    if (local_28 != (uint *)0x0) {
      puVar5 = (uint *)0x0;
      if (puVar11 != (uint *)0x0) {
        do {
          local_28[(int)puVar5] = *(uint *)(param_1 + 0x28);
          puVar5 = (uint *)((int)puVar5 + 1);
        } while (puVar5 < puVar11);
      }
      goto LAB_0077cc60;
    }
    break;
  case 4:
    if ((local_10 == (uint *)0x0) || (param_3 == (uint *)0x0)) goto LAB_0077e7bf;
    local_30 = operator_new((int)local_8 * 0xc);
    if (local_30 == (uint *)0x0) break;
    uVar14 = 0;
    puVar5 = local_30;
    do {
      local_70[uVar14] = puVar5;
      uVar14 = uVar14 + 1;
      puVar5 = puVar5 + (int)puVar11;
    } while (uVar14 < 3);
    iVar3 = FUN_00773063(local_70[0],local_8);
    if (((iVar3 < 0) || (iVar3 = FUN_00773063(local_70[1],local_8), iVar3 < 0)) ||
       ((iVar3 = FUN_00773063(local_70[2],local_8), iVar3 < 0 ||
        (iVar3 = FUN_00773063(param_3,local_8), iVar3 < 0)))) goto LAB_0077e7bf;
    local_c = (uint *)((uint)local_8 & 0xffffff);
    local_10 = (uint *)((uint)local_c | 0x11000000);
    iVar3 = FUN_00773e3b(param_2,local_10,local_70[0],local_14,0,0);
    if ((iVar3 < 0) ||
       (iVar3 = FUN_00773e3b(param_2,(uint)local_c | 0x21000000,local_70[1],local_14,local_70[0],4),
       iVar3 < 0)) goto LAB_0077e7bf;
    iVar3 = FUN_00773e3b(param_2,local_10,local_70[2],local_70[1],0,8);
    puVar11 = local_70[2];
    puVar9 = local_c;
joined_r0x0077d1c0:
    local_c = puVar9;
    if (iVar3 < 0) goto LAB_0077e7bf;
    goto LAB_0077ce0f;
  case 5:
    if (((local_10 == (uint *)0x0) || (param_3 == (uint *)0x0)) ||
       (iVar3 = FUN_00773063(param_3,local_8), iVar3 < 0)) goto LAB_0077e7bf;
    uVar18 = 0;
    puVar9 = (uint *)((uint)local_8 & 0xffffff | 0x11000000);
    puVar11 = local_14;
    goto LAB_0077ce18;
  case 6:
    if ((local_10 == (uint *)0x0) || (param_3 == (uint *)0x0)) goto LAB_0077e7bf;
    iVar3 = FUN_00773063(param_3,local_8);
    puVar11 = local_14;
joined_r0x0077e15b:
    if (iVar3 < 0) goto LAB_0077e7bf;
    uVar18 = 0;
    puVar9 = (uint *)((uint)local_8 & 0xffffff | 0x10000000);
    goto LAB_0077ce18;
  case 7:
    if (((local_10 == (uint *)0x0) || (local_20 == (uint *)0x0)) ||
       ((param_3 == (uint *)0x0 || (iVar3 = FUN_00773063(param_3,local_8), iVar3 < 0))))
    goto LAB_0077e7bf;
    puVar9 = (uint *)((uint)local_8 & 0xffffff);
    puVar11 = local_28;
LAB_0077d5fc:
    uVar18 = ZEXT48(puVar11);
    puVar9 = (uint *)((uint)puVar9 | 0x25000000);
    puVar11 = local_14;
    goto LAB_0077ce18;
  case 8:
    if (((local_10 == (uint *)0x0) || (local_20 == (uint *)0x0)) || (param_3 == (uint *)0x0))
    goto LAB_0077e7bf;
    local_30 = operator_new((int)local_8 << 2);
    if (local_30 != (uint *)0x0) {
      iVar3 = FUN_00773063(local_30,local_8);
      if ((iVar3 < 0) || (iVar3 = FUN_00773063(param_3,local_8), iVar3 < 0)) goto LAB_0077e7bf;
      local_c = (uint *)((uint)local_8 & 0xffffff);
      iVar3 = FUN_00773e3b(param_2,(uint)local_c | 0x12000000,local_30,local_28,0,0);
      puVar9 = local_c;
      puVar11 = local_30;
      if (iVar3 < 0) goto LAB_0077e7bf;
      goto LAB_0077d5fc;
    }
    break;
  case 9:
    if (((local_10 == (uint *)0x0) || (local_20 == (uint *)0x0)) || (param_3 == (uint *)0x0))
    goto LAB_0077e7bf;
    puVar5 = operator_new((int)local_8 * 0xc);
    local_30 = puVar5;
    if (puVar5 != (uint *)0x0) {
      uVar14 = 0;
      do {
        local_70[uVar14] = puVar5;
        uVar14 = uVar14 + 1;
        puVar5 = puVar5 + (int)puVar11;
      } while (uVar14 < 3);
      uVar14 = 0;
      do {
        uVar17 = FUN_00773063(local_70[uVar14],local_8);
        if ((int)uVar17 < 0) goto LAB_0077e7bf;
        uVar14 = (int)((ulonglong)uVar17 >> 0x20) + 1;
      } while (uVar14 < 3);
      iVar3 = FUN_00773063(param_3,local_8);
      if (iVar3 < 0) goto LAB_0077e7bf;
      local_c = (uint *)((uint)local_8 & 0xffffff);
      iVar3 = FUN_00773e3b(param_2,(uint)local_c | 0x12000000,local_70[0],local_28,0,0);
      if (iVar3 < 0) goto LAB_0077e7bf;
      local_1c = (uint *)((uint)local_c | 0x25000000);
      iVar3 = FUN_00773e3b(param_2,local_1c,local_70[1],local_14,local_70[0],0);
      if ((iVar3 < 0) ||
         (iVar3 = FUN_00773e3b(param_2,(uint)local_c | 0x13000000,local_70[2],local_70[1],0,4),
         iVar3 < 0)) goto LAB_0077e7bf;
      uVar18 = ZEXT48(local_70[2]);
      puVar9 = local_1c;
      puVar11 = local_28;
      goto LAB_0077ce18;
    }
    break;
  case 10:
    if ((((local_10 == (uint *)0x0) || (local_20 == (uint *)0x0)) || (param_3 == (uint *)0x0)) ||
       (iVar3 = FUN_00773063(param_3,local_8), iVar3 < 0)) goto LAB_0077e7bf;
    puVar9 = (uint *)((uint)local_8 & 0xffffff);
    puVar11 = local_28;
LAB_0077cedb:
    uVar18 = ZEXT48(puVar11);
    puVar9 = (uint *)((uint)puVar9 | 0x24000000);
    puVar11 = local_14;
    goto LAB_0077ce18;
  case 0xb:
    if (((local_10 == (uint *)0x0) || (local_20 == (uint *)0x0)) || (param_3 == (uint *)0x0))
    goto LAB_0077e7bf;
    local_30 = operator_new((int)local_8 << 2);
    if (local_30 != (uint *)0x0) {
      iVar3 = FUN_00773063(local_30,local_8);
      if ((iVar3 < 0) || (iVar3 = FUN_00773063(param_3,local_8), iVar3 < 0)) goto LAB_0077e7bf;
      local_c = (uint *)((uint)local_8 & 0xffffff);
      iVar3 = FUN_00773e3b(param_2,(uint)local_c | 0x11000000,local_30,local_28,0,0);
      puVar9 = local_c;
      puVar11 = local_30;
      if (iVar3 < 0) goto LAB_0077e7bf;
      goto LAB_0077cedb;
    }
    break;
  case 0xc:
    if (((local_10 == (uint *)0x0) || (local_20 == (uint *)0x0)) || (param_3 == (uint *)0x0))
    goto LAB_0077e7bf;
    iVar3 = FUN_00773063(param_3,local_8);
    puVar11 = local_14;
    puVar5 = local_28;
    goto joined_r0x0077cfe5;
  case 0xd:
    if (((local_10 == (uint *)0x0) || (local_20 == (uint *)0x0)) || (param_3 == (uint *)0x0))
    goto LAB_0077e7bf;
    iVar3 = FUN_00773063(param_3,local_8);
    puVar11 = local_28;
    puVar5 = local_14;
joined_r0x0077cfe5:
    if (iVar3 < 0) goto LAB_0077e7bf;
    puVar9 = (uint *)((uint)local_8 & 0xffffff);
LAB_0077cffe:
    uVar18 = CONCAT44(0x2000017,puVar5);
    puVar9 = (uint *)((uint)puVar9 | 0x22000000);
    goto LAB_0077ce18;
  case 0xe:
    if (((local_10 == (uint *)0x0) || (local_20 == (uint *)0x0)) || (param_3 == (uint *)0x0))
    goto LAB_0077e7bf;
    iVar3 = FUN_00773063(param_3,local_8);
    local_70[1] = local_14;
    puVar11 = local_28;
    goto joined_r0x0077d06f;
  case 0xf:
    if (((local_10 == (uint *)0x0) || (local_20 == (uint *)0x0)) || (param_3 == (uint *)0x0))
    goto LAB_0077e7bf;
    iVar3 = FUN_00773063(param_3,local_8);
    local_70[1] = local_28;
    puVar11 = local_14;
joined_r0x0077d06f:
    if (iVar3 < 0) goto LAB_0077e7bf;
    puVar9 = (uint *)((uint)local_8 & 0xffffff);
LAB_0077ce0f:
    uVar18 = CONCAT44(0x2000017,local_70[1]);
    puVar9 = (uint *)((uint)puVar9 | 0x23000000);
LAB_0077ce18:
    iVar3 = FUN_00773e3b(param_2,puVar9,param_3,puVar11,uVar18);
LAB_0077ce22:
    if (iVar3 < 0) goto LAB_0077e7bf;
LAB_0077ca5a:
    if (param_3 == (uint *)0x0) goto LAB_0077e7bf;
    uVar14 = (int)local_8 << 2;
    local_8c = operator_new(uVar14);
    if ((local_8c != (uint *)0x0) && (local_90 = operator_new(uVar14), local_90 != (uint *)0x0)) {
      FUN_0077429f(*(undefined4 *)((int)param_2 + 0x10),local_8c);
      local_20 = (uint *)0x0;
      local_70[3] = (uint *)0x0;
      local_78 = (uint *)0x0;
      if (local_8 == (uint *)0x0) goto LAB_0077e7bf;
      local_70[4] = (uint *)((int)param_3 - (int)local_8c);
      local_2c = (uint *)((int)local_8c - (int)local_90);
      local_34 = local_90;
      do {
        pbVar1 = (byte *)((int)local_2c + (int)local_34);
        piVar4 = (int *)FUN_007850ce();
        if (piVar4 == (int *)0x0) {
          pcVar20 = "internal error: result register invalid";
          goto LAB_0077e7af;
        }
        iVar3 = *(int *)(*(int *)(param_1 + 8) + 0x4c);
        if (iVar3 == *piVar4) {
LAB_0077e313:
          *local_34 = 0;
        }
        else if (((*pbVar1 & 1) == 0) || ((*(byte *)(piVar4 + 6) & 1) != 0)) {
          if ((iVar3 == *piVar4) || (((*pbVar1 & 2) == 0 || ((*(byte *)(piVar4 + 6) & 2) != 0))))
          goto LAB_0077e313;
          local_70[3] = (uint *)((int)local_70[3] + 1);
          *local_34 = 2;
        }
        else {
          local_20 = (uint *)((int)local_20 + 1);
          *local_34 = 1;
        }
        puVar11 = local_20;
        local_78 = (uint *)((int)local_78 + 1);
        local_34 = local_34 + 1;
      } while (local_78 < local_8);
      if (local_20 != (uint *)0x0) {
        if (local_30 != (uint *)0x0) {
                    /* WARNING: Subroutine does not return */
          _free(local_30);
        }
        local_30 = operator_new((int)local_20 << 4);
        if (local_30 == (uint *)0x0) break;
        uVar14 = 0;
        puVar5 = local_30;
        do {
          local_48[uVar14] = (uint)puVar5;
          uVar14 = uVar14 + 1;
          puVar5 = puVar5 + (int)puVar11;
        } while (uVar14 < 4);
        iVar3 = FUN_00773063(local_48[1],local_20);
        if (((iVar3 < 0) || (iVar3 = FUN_00773063(local_40,local_20), iVar3 < 0)) ||
           (iVar3 = FUN_00773063(local_3c,local_20), iVar3 < 0)) goto LAB_0077e7bf;
        local_2c = (uint *)local_48[0];
        local_18 = (uint *)((int)local_90 - (int)param_3);
        local_1c = local_8;
        puVar11 = param_3;
        do {
          FUN_007850ce();
          if (*(int *)((int)local_18 + (int)puVar11) == 1) {
            *local_2c = *puVar11;
            local_2c = local_2c + 1;
          }
          puVar11 = puVar11 + 1;
          local_1c = (uint *)((int)local_1c + -1);
        } while (local_1c != (uint *)0x0);
        local_1c = (uint *)((uint)local_20 & 0xffffff);
        local_70[2] = (uint *)((uint)local_1c | 0x11000000);
        iVar3 = FUN_00773e3b(param_2,local_70[2],local_48[1],local_48[0],0,0);
        if (((iVar3 < 0) ||
            (iVar3 = FUN_00773e3b(param_2,(uint)local_1c | 0x21000000,local_40,local_48[0],
                                  local_48[1],4), iVar3 < 0)) ||
           ((iVar3 = FUN_00773e3b(param_2,local_70[2],local_3c,local_40,0,8), iVar3 < 0 ||
            (iVar3 = FUN_00773e3b(param_2,(uint)local_1c | 0x22000000,local_48[0],local_3c,local_40,
                                  0x2000017), iVar3 < 0)))) goto LAB_0077e7bf;
        local_2c = (uint *)local_48[0];
        local_1c = local_8;
        puVar11 = param_3;
        do {
          FUN_007850ce();
          if (*(int *)((int)puVar11 + (int)local_18) == 1) {
            uVar14 = *local_2c;
            local_2c = local_2c + 1;
            *puVar11 = uVar14;
          }
          puVar11 = puVar11 + 1;
          local_1c = (uint *)((int)local_1c + -1);
        } while (local_1c != (uint *)0x0);
      }
      puVar11 = local_70[3];
      if (local_70[3] != (uint *)0x0) {
        if (local_30 != (uint *)0x0) {
                    /* WARNING: Subroutine does not return */
          _free(local_30);
        }
        local_30 = operator_new((int)local_70[3] * 0x24);
        if (local_30 == (uint *)0x0) break;
        uVar14 = 0;
        puVar5 = local_30;
        do {
          local_70[uVar14 + 5] = puVar5;
          uVar14 = uVar14 + 1;
          puVar5 = puVar5 + (int)puVar11;
        } while (uVar14 < 9);
        local_2c = local_70[5];
        local_18 = (uint *)((int)local_90 - (int)param_3);
        local_1c = local_8;
        puVar11 = param_3;
        do {
          FUN_007850ce();
          puVar5 = local_2c;
          if (*(int *)((int)puVar11 + (int)local_18) == 2) {
            local_2c = local_2c + 1;
            *puVar5 = *puVar11;
          }
          puVar11 = puVar11 + 1;
          local_1c = (uint *)((int)local_1c + -1);
        } while (local_1c != (uint *)0x0);
        uVar14 = 1;
        do {
          uVar17 = FUN_00773063(local_70[uVar14 + 5],local_70[3]);
          if ((int)uVar17 < 0) goto LAB_0077e7bf;
          uVar14 = (int)((ulonglong)uVar17 >> 0x20) + 1;
        } while (uVar14 < 9);
        local_24 = (uint *)((uint)local_70[3] & 0xffffff);
        iVar3 = FUN_00773e3b(param_2,(uint)local_24 | 0x13000000,local_70[6],local_70[5],0,0x14);
        if (iVar3 < 0) goto LAB_0077e7bf;
        local_1c = (uint *)((uint)local_24 | 0x11000000);
        iVar3 = FUN_00773e3b(param_2,local_1c,local_70[7],local_70[6],0,0x18);
        if (iVar3 < 0) goto LAB_0077e7bf;
        uStack_98 = (uint)local_24 | 0x24000000;
        iVar3 = FUN_00773e3b(param_2,uStack_98,local_70[8],local_70[7],local_70[5],2);
        if ((iVar3 < 0) ||
           (iVar3 = FUN_00773e3b(param_2,local_1c,local_70[9],local_70[5],0,0), iVar3 < 0))
        goto LAB_0077e7bf;
        local_70[2] = (uint *)((uint)local_24 | 0x22000000);
        iVar3 = FUN_00773e3b(param_2,local_70[2],local_48[0],local_70[5],local_70[9],0x2000017);
        if ((iVar3 < 0) ||
           ((((iVar3 = FUN_00773e3b(param_2,local_1c,local_48[1],local_70[6],0,0), iVar3 < 0 ||
              (iVar3 = FUN_00773e3b(param_2,local_70[2],local_40,local_48[1],local_70[6],0x2000017),
              iVar3 < 0)) ||
             (iVar3 = FUN_00773e3b(param_2,(uint)local_24 | 0x25000000,local_3c,local_48[0],local_40
                                   ,0x2000017), iVar3 < 0)) ||
            (iVar3 = FUN_00773e3b(param_2,uStack_98,local_70[5],local_70[8],local_3c,2), iVar3 < 0))
           )) goto LAB_0077e7bf;
        param_2 = local_70[5];
        local_1c = local_8;
        puVar11 = param_3;
        do {
          FUN_007850ce();
          if (*(int *)((int)puVar11 + (int)local_18) == 2) {
            uVar14 = *param_2;
            param_2 = param_2 + 1;
            *puVar11 = uVar14;
          }
          puVar11 = puVar11 + 1;
          local_1c = (uint *)((int)local_1c + -1);
        } while (local_1c != (uint *)0x0);
      }
      if (local_8 != (uint *)0x0) {
        local_70[4] = (uint *)((int)param_3 - (int)local_8c);
        param_3 = local_8;
        puVar11 = local_8c;
        do {
          local_1c = puVar11;
          iVar3 = FUN_007850ce();
          uVar14 = *puVar11;
          uVar12 = *(uint *)(iVar3 + 0x18);
          *(uint *)(iVar3 + 0x18) = uVar14 & 0xf1ffffff | uVar12;
          uVar13 = *puVar11 & 0xe000000;
          uVar10 = uVar12 & 0xe000000;
          if ((uVar12 & 0xe000000) == 0) {
            uVar10 = uVar13;
          }
          if (*(int *)(iVar3 + 0x40) == 0) {
            if (uVar13 <= uVar10) {
LAB_0077e788:
              uVar10 = uVar13;
            }
          }
          else if (uVar10 <= uVar13) goto LAB_0077e788;
          puVar11 = local_1c + 1;
          param_3 = (uint *)((int)param_3 + -1);
          *(uint *)(iVar3 + 0x18) = uVar14 & 0xf1ffffff | uVar12 & 0xf1ffffff | uVar10;
          local_1c = puVar11;
        } while (param_3 != (uint *)0x0);
      }
      goto LAB_0077e7bf;
    }
    break;
  case 0x10:
    if ((local_10 == (uint *)0x0) || ((local_20 == (uint *)0x0 || (param_3 == (uint *)0x0))))
    goto LAB_0077e7bf;
    local_30 = operator_new((int)local_8 * 0x14);
    if (local_30 != (uint *)0x0) {
      uVar14 = 0;
      puVar5 = local_30;
      do {
        local_48[uVar14 - 1] = (uint)puVar5;
        uVar14 = uVar14 + 1;
        puVar5 = puVar5 + (int)puVar11;
      } while (uVar14 < 5);
      iVar3 = FUN_00773063(local_30,(int)local_8 * 5);
      if ((iVar3 < 0) || (iVar3 = FUN_00773063(param_3,local_8), iVar3 < 0)) goto LAB_0077e7bf;
      local_c = (uint *)((uint)local_8 & 0xffffff);
      local_10 = (uint *)((uint)local_c | 0x11000000);
      iVar3 = FUN_00773e3b(param_2,local_10,local_70[9],local_28,0,0);
      if ((iVar3 < 0) ||
         (((iVar3 = FUN_00773e3b(param_2,(uint)local_c | 0x24000000,local_48[0],local_14,local_70[9]
                                 ,0), iVar3 < 0 ||
           (iVar3 = FUN_00773e3b(param_2,local_10,local_48[1],local_48[0],0,0), iVar3 < 0)) ||
          (iVar3 = FUN_00773e3b(param_2,(uint)local_c | 0x21000000,local_40,local_48[0],local_48[1],
                                4), iVar3 < 0)))) goto LAB_0077e7bf;
      iVar3 = FUN_00773e3b(param_2,local_10,local_3c,local_40,0,8);
      local_70[1] = local_40;
      puVar11 = local_3c;
      puVar9 = local_c;
      goto joined_r0x0077d1c0;
    }
    break;
  case 0x11:
    if (((local_10 == (uint *)0x0) || (local_20 == (uint *)0x0)) || (param_3 == (uint *)0x0))
    goto LAB_0077e7bf;
    local_30 = operator_new((int)local_8 * 0x14);
    if (local_30 == (uint *)0x0) break;
    uVar14 = 0;
    puVar5 = local_30;
    do {
      local_48[uVar14 - 1] = (uint)puVar5;
      uVar14 = uVar14 + 1;
      puVar5 = puVar5 + (int)puVar11;
    } while (uVar14 < 5);
    iVar3 = FUN_00773063(local_30,(int)local_8 * 5);
    if ((iVar3 < 0) || (iVar3 = FUN_00773063(param_3,local_8), iVar3 < 0)) goto LAB_0077e7bf;
    local_c = (uint *)((uint)local_8 & 0xffffff);
    local_10 = (uint *)((uint)local_c | 0x11000000);
    iVar3 = FUN_00773e3b(param_2,local_10,local_70[9],local_28,0,0);
    if ((iVar3 < 0) ||
       (iVar3 = FUN_00773e3b(param_2,(uint)local_c | 0x24000000,local_48[0],local_14,local_70[9],0),
       iVar3 < 0)) goto LAB_0077e7bf;
LAB_0077d3b6:
    iVar3 = FUN_00773e3b(param_2,local_10,local_48[1],local_48[0],0);
    if (iVar3 < 0) goto LAB_0077e7bf;
    uVar14 = (uint)local_c | 0x21000000;
    puVar11 = (uint *)local_48[0];
LAB_0077d575:
    iVar3 = FUN_00773e3b(param_2,uVar14,local_40,puVar11,CONCAT44(4,local_48[1]));
    if ((iVar3 < 0) ||
       (iVar3 = FUN_00773e3b(param_2,local_10,local_3c,local_40,0,8), puVar9 = local_c,
       puVar11 = local_3c, puVar5 = local_40, iVar3 < 0)) goto LAB_0077e7bf;
    goto LAB_0077cffe;
  case 0x12:
    if (((local_10 == (uint *)0x0) || (local_20 == (uint *)0x0)) || (param_3 == (uint *)0x0))
    goto LAB_0077e7bf;
    local_30 = operator_new((int)local_8 << 4);
    if (local_30 != (uint *)0x0) {
      uVar14 = 0;
      puVar5 = local_30;
      do {
        local_48[uVar14] = (uint)puVar5;
        uVar14 = uVar14 + 1;
        puVar5 = puVar5 + (int)puVar11;
      } while (uVar14 < 4);
      iVar3 = FUN_00773063(local_48[0],local_8);
      if (((iVar3 < 0) || (iVar3 = FUN_00773063(local_48[1],local_8), iVar3 < 0)) ||
         ((iVar3 = FUN_00773063(local_40,local_8), iVar3 < 0 ||
          ((iVar3 = FUN_00773063(local_3c,local_8), iVar3 < 0 ||
           (iVar3 = FUN_00773063(param_3,local_8), iVar3 < 0)))))) goto LAB_0077e7bf;
      local_c = (uint *)((uint)local_8 & 0xffffff);
      iVar3 = FUN_00773e3b(param_2,(uint)local_c | 0x25000000,local_48[0],local_14,local_28,0);
      if (iVar3 < 0) goto LAB_0077e7bf;
      local_10 = (uint *)((uint)local_c | 0x11000000);
      goto LAB_0077d3b6;
    }
    break;
  case 0x13:
    if (((local_10 == (uint *)0x0) || (local_20 == (uint *)0x0)) || (param_3 == (uint *)0x0))
    goto LAB_0077e7bf;
    local_30 = operator_new((int)local_8 * 0x18);
    if (local_30 != (uint *)0x0) {
      uVar14 = 0;
      puVar5 = local_30;
      do {
        local_70[uVar14 + 8] = puVar5;
        uVar14 = uVar14 + 1;
        puVar5 = puVar5 + (int)puVar11;
      } while (uVar14 < 6);
      iVar3 = FUN_00773063(local_70[8],local_8);
      if (((((iVar3 < 0) || (iVar3 = FUN_00773063(local_70[9],local_8), iVar3 < 0)) ||
           ((iVar3 = FUN_00773063(local_48[0],local_8), iVar3 < 0 ||
            ((iVar3 = FUN_00773063(local_48[1],local_8), iVar3 < 0 ||
             (iVar3 = FUN_00773063(local_40,local_8), iVar3 < 0)))))) ||
          (iVar3 = FUN_00773063(local_3c,local_8), iVar3 < 0)) ||
         (iVar3 = FUN_00773063(param_3,local_8), iVar3 < 0)) goto LAB_0077e7bf;
      local_c = (uint *)((uint)local_8 & 0xffffff);
      local_10 = (uint *)((uint)local_c | 0x11000000);
      iVar3 = FUN_00773e3b(param_2,local_10,local_70[8],local_14,0,0);
      if (iVar3 < 0) goto LAB_0077e7bf;
      local_1c = (uint *)((uint)local_c | 0x21000000);
      iVar3 = FUN_00773e3b(param_2,local_1c,local_70[9],local_14,local_70[8],4);
      if (((iVar3 < 0) ||
          (iVar3 = FUN_00773e3b(param_2,local_10,local_48[0],local_28,0,0), iVar3 < 0)) ||
         (iVar3 = FUN_00773e3b(param_2,local_1c,local_48[1],local_28,local_48[0],4), iVar3 < 0))
      goto LAB_0077e7bf;
      uVar14 = (uint)local_c | 0x24000000;
      puVar11 = local_70[9];
      goto LAB_0077d575;
    }
    break;
  case 0x14:
    if ((local_10 == (uint *)0x0) || (local_20 == (uint *)0x0)) goto LAB_0077e7bf;
    if (local_8 != (uint *)0x0) {
      piVar4 = (int *)FUN_007850ce();
      if ((piVar4 != (int *)0x0) && (*(int *)(*(int *)(param_1 + 8) + 0x4c) == *piVar4))
      goto LAB_0077cbd4;
LAB_0077cbfe:
      puVar9 = local_8;
      puVar11 = local_14;
      if (param_3 == (uint *)0x0) goto LAB_0077e7bf;
code_r0x0077e053:
      for (; puVar9 != (uint *)0x0; puVar9 = (uint *)((int)puVar9 + -1)) {
        *puVar5 = *puVar11;
        puVar11 = puVar11 + 1;
        puVar5 = puVar5 + 1;
      }
    }
    goto LAB_0077ca5a;
  case 0x15:
    if ((local_10 == (uint *)0x0) || (local_20 == (uint *)0x0)) goto LAB_0077e7bf;
    if (local_8 != (uint *)0x0) {
LAB_0077cbd4:
      iVar3 = FUN_00773e3b(param_2,(uint)local_8 & 0xffffff | 0x10000000,local_14,local_28,0,0);
      if (iVar3 < 0) goto LAB_0077e7bf;
      goto LAB_0077cbfe;
    }
    goto LAB_0077ca5a;
  case 0x16:
    if (local_20 == (uint *)0x0) goto LAB_0077e7bf;
    if (local_c != (uint *)0x0) {
      iVar3 = FUN_007732ad(*local_28,local_70 + 1);
      if (iVar3 < 0) {
        if (local_8 == local_c) goto LAB_0077cbfe;
        iVar3 = FUN_00776527(local_10[4],local_14,local_c);
        puVar11 = local_14;
        if (iVar3 < 0) goto LAB_0077e7bf;
        local_88 = 1;
        local_18 = (uint *)0x0;
        if (local_c != (uint *)0x0) {
          do {
            FUN_007850ce();
            iVar3 = FUN_007850b8();
            if ((*(byte *)(iVar3 + 4) & 0x20) == 0) {
              local_88 = 0;
              break;
            }
            local_18 = (uint *)((int)local_18 + 1);
          } while (local_18 < local_c);
        }
        local_34 = (uint *)0x1;
        local_74 = 1;
        if (local_88 == 0) {
          local_34 = (uint *)0x1;
          local_74 = 0;
LAB_0077d8e9:
          if ((local_34 == (uint *)0x0) && (local_74 == 0)) {
LAB_0077da5b:
            FUN_00773c7b(param_1,param_2,0xdac);
            goto LAB_0077e7bf;
          }
        }
        else {
          local_38 = local_8;
          if (local_8 < local_c) {
            local_24 = puVar11;
            do {
              local_18 = (uint *)FUN_007850ce();
              puVar5 = (uint *)FUN_007850ce();
              if (((*local_18 != *puVar5) || (local_18[2] != puVar5[2])) ||
                 (local_18[1] != puVar5[1])) {
                local_34 = (uint *)0x0;
              }
              if ((*local_18 != *puVar5) || (local_18[3] != puVar5[3])) {
                local_74 = 0;
              }
              local_38 = (uint *)((int)local_38 + 1);
              local_24 = local_24 + 1;
            } while (local_38 < local_c);
            goto LAB_0077d8e9;
          }
        }
        local_7c = 0xffffffff;
        local_20 = (uint *)0x1;
        if (local_34 == (uint *)0x0) {
          local_1c = (uint *)FUN_007850ce();
          iVar3 = FUN_007850ce();
          local_7c = local_1c[1];
          local_20 = (uint *)(*(int *)(iVar3 + 8) - local_1c[2]);
          local_18 = (uint *)0x0;
          if (local_c != (uint *)0x0) {
            do {
              piVar4 = (int *)FUN_007850ce();
              if ((piVar4[1] != local_7c) ||
                 ((*(byte *)(*(int *)(*(int *)(*(int *)(param_1 + 8) + 0x10) + *piVar4 * 4) + 5) & 2
                  ) == 0)) goto LAB_0077da5b;
              local_18 = (uint *)((int)local_18 + 1);
            } while (local_18 < local_c);
          }
          local_18 = (uint *)((int)local_8 * 2);
          if (local_18 < local_c) {
            local_38 = puVar11 + (int)local_8;
            local_24 = puVar11;
            do {
              uStack_98 = FUN_007850ce();
              local_1c = (uint *)FUN_007850ce();
              local_94 = FUN_007850ce();
              if (local_1c[2] - *(int *)(uStack_98 + 8) != *(int *)(local_94 + 8) - local_1c[2])
              goto LAB_0077da5b;
              local_18 = (uint *)((int)local_18 + 1);
              local_24 = local_24 + 1;
              local_38 = local_38 + 1;
            } while (local_18 < local_c);
          }
          local_18 = (uint *)0x1;
          if ((uint *)0x1 < local_8) {
            local_24 = puVar11 + (int)local_8 + 1;
            do {
              local_1c = (uint *)FUN_007850ce();
              iVar3 = FUN_007850ce();
              if (local_20 != (uint *)(*(int *)(iVar3 + 8) - local_1c[2])) goto LAB_0077da5b;
              local_18 = (uint *)((int)local_18 + 1);
              local_24 = local_24 + 1;
            } while (local_18 < local_8);
          }
        }
        else if (local_88 == 0) {
          local_20 = (uint *)((uint)local_c / (uint)local_8 + 3 >> 2);
        }
        if (param_3 == (uint *)0x0) goto LAB_0077e7bf;
        if ((local_20 == (uint *)0x1) && ((*(byte *)(*(int *)(param_1 + 8) + 0x92) & 0x80) != 0)) {
          local_70[3] = (uint *)*local_28;
        }
        else {
          dVar2 = (double)(int)local_20;
          if ((int)local_20 < 0) {
            dVar2 = dVar2 + _DAT_00872618;
          }
          local_1c = (uint *)FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,dVar2);
          local_84 = 0xffffffff;
          local_80 = 0xffffffff;
          local_74 = -1;
          local_70[3] = (uint *)0xffffffff;
          iVar3 = FUN_00773e3b(param_2,0x13000001,&local_84,local_28,0,4);
          if ((((iVar3 < 0) ||
               (iVar3 = FUN_00773e3b(param_2,0x11000001,&local_80,&local_84,0,8), iVar3 < 0)) ||
              (iVar3 = FUN_00773e3b(param_2,0x24000001,&local_74,&local_80,local_28,2), iVar3 < 0))
             || (iVar3 = FUN_00773e3b(param_2,0x25000001,local_70 + 3,&local_74,&local_1c,2),
                iVar3 < 0)) goto LAB_0077e7bf;
        }
        if (local_7c != 0xffffffff) {
          puVar6 = (undefined4 *)FUN_007850ce();
          *puVar6 = *(undefined4 *)(*(int *)(param_1 + 8) + 0x60);
          local_84 = 0xffffffff;
          local_80 = 0xffffffff;
          local_74 = -1;
          local_a4 = (uint *)0xffffffff;
          iVar3 = FUN_00773e3b(param_2,0x13000001,&local_84,&local_7c,0,4);
          if (((iVar3 < 0) ||
              (iVar3 = FUN_00773e3b(param_2,0x11000001,&local_80,&local_84,0,8), iVar3 < 0)) ||
             ((iVar3 = FUN_00773e3b(param_2,0x24000001,&local_74,&local_80,&local_7c,2), iVar3 < 0
              || (iVar3 = FUN_00773e3b(param_2,0x24000001,&local_a4,&local_74,local_70 + 3,0),
                 iVar3 < 0)))) goto LAB_0077e7bf;
          local_70[3] = local_a4;
        }
        if (*(int *)(*(int *)(param_1 + 8) + 0x74) == 0) {
          local_38 = local_70[3];
        }
        else {
          local_38 = (uint *)0xffffffff;
          iVar3 = FUN_00773e3b(param_2,0x10000001,&local_38,local_70 + 3,0,
                               -((uint *)0x1 < local_20) & 2);
          if (iVar3 < 0) goto LAB_0077e7bf;
          puVar6 = (undefined4 *)FUN_007850ce();
          *puVar6 = *(undefined4 *)(*(int *)(param_1 + 8) + 100);
        }
        local_20 = (uint *)((uint)local_c / (uint)local_8);
        if (local_34 == (uint *)0x0) {
          local_18 = (uint *)0x0;
          if (local_8 != (uint *)0x0) {
            local_78 = (uint *)((int)param_3 - (int)local_14);
            local_34 = local_14;
            do {
              puVar6 = (undefined4 *)((int)local_78 + (int)local_34);
              uVar7 = FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x60),0,0,0);
              *puVar6 = uVar7;
              local_1c = (uint *)FUN_007850ce();
              iVar3 = FUN_007850ce();
              if (iVar3 == 0) goto LAB_0077e4fb;
              FUN_0078572c();
              *(undefined4 *)(iVar3 + 0x20) = 0xffffffff;
              *(uint **)(iVar3 + 4) = local_38;
              *(undefined4 *)(iVar3 + 0x18) = 0x1f;
              if (local_20 != (uint *)0x0) {
                local_24 = local_34;
                local_2c = local_20;
                do {
                  iVar8 = FUN_007850ce();
                  *(uint *)(iVar3 + 0x18) = *(uint *)(iVar3 + 0x18) & *(uint *)(iVar8 + 0x18);
                  local_24 = local_24 + (int)local_8;
                  local_2c = (uint *)((int)local_2c + -1);
                } while (local_2c != (uint *)0x0);
              }
              local_18 = (uint *)((int)local_18 + 1);
              local_34 = local_34 + 1;
            } while (local_18 < local_8);
          }
        }
        else {
          iVar3 = FUN_00773063(param_3,local_8);
          puVar11 = local_20;
          if (iVar3 < 0) goto LAB_0077e7bf;
          local_30 = operator_new((int)local_20 << 3);
          if (local_30 == (uint *)0x0) break;
          local_1c = local_30 + (int)puVar11;
          local_2c = (uint *)0x0;
          if (local_8 != (uint *)0x0) {
            local_78 = (uint *)((int)param_3 - (int)local_14);
            local_34 = local_14;
            do {
              puVar11 = local_20;
              local_18 = (uint *)0x1f;
              if (local_88 == 0) {
                local_70[4] = (uint *)0x0;
                if (local_20 != (uint *)0x0) {
                  local_10 = local_34;
                  do {
                    iVar3 = FUN_007850ce();
                    local_18 = (uint *)((uint)local_18 & *(uint *)(iVar3 + 0x18));
                    local_30[(int)local_70[4]] = *local_10;
                    local_10 = local_10 + (int)local_8;
                    local_70[4] = (uint *)((int)local_70[4] + 1);
                  } while (local_70[4] < local_20);
                }
              }
              else {
                local_48[0] = 0;
                local_48[1] = 0;
                local_40 = (uint *)0x0;
                local_3c = (uint *)0x0;
                if (local_20 != (uint *)0x0) {
                  local_c = (uint *)((int)local_8 << 2);
                  local_70[4] = local_20;
                  puVar11 = local_34;
                  do {
                    iVar3 = FUN_007850ce();
                    local_18 = (uint *)((uint)local_18 & *(uint *)(iVar3 + 0x18));
                    uVar14 = *puVar11;
                    puVar11 = (uint *)((int)puVar11 + (int)local_c);
                    local_70[4] = (uint *)((int)local_70[4] + -1);
                    local_30[*(int *)(iVar3 + 0xc)] = uVar14;
                    local_48[*(int *)(iVar3 + 0xc)] = 1;
                  } while (local_70[4] != (uint *)0x0);
                }
                puVar11 = (uint *)0x0;
                iVar3 = (int)local_48 - (int)local_30;
                local_24 = (uint *)((int)local_30 - (int)local_48);
                local_10 = (uint *)0x0;
                puVar5 = local_30;
                do {
                  if (*(int *)(iVar3 + (int)puVar5) != 0) {
                    *(uint *)((int)local_48 + (int)(local_24 + (int)puVar11)) = *puVar5;
                    local_48[(int)puVar11] = (uint)local_10;
                    puVar11 = (uint *)((int)puVar11 + 1);
                  }
                  local_10 = (uint *)((int)local_10 + 1);
                  puVar5 = puVar5 + 1;
                } while (local_10 < &DAT_00000004);
              }
              local_94 = (int)puVar11 + 3U >> 2;
              puVar5 = (uint *)&DAT_00000004;
              if (puVar11 < &DAT_00000004) {
                puVar5 = puVar11;
              }
              uStack_98 = FUN_00784ecf(&DAT_00879a40,0x3a9,local_94 * (int)local_20,puVar5);
              if (uStack_98 == 0xffffffff) goto LAB_0077e4fb;
              local_24 = (uint *)0x0;
              if (local_20 != (uint *)0x0) {
                local_c = (uint *)((int)local_8 << 2);
                local_70[4] = (uint *)0x0;
                local_a0 = local_34;
                do {
                  local_70[2] = (uint *)FUN_007850ce();
                  local_10 = (uint *)0x0;
                  if (puVar11 != (uint *)0x0) {
                    do {
                      if (local_88 == 0) {
                        bVar16 = local_24 == local_10;
                      }
                      else {
                        bVar16 = local_48[(int)local_10] == local_70[2][3];
                      }
                      if (bVar16) {
                        uVar17 = 0x3ff0000000000000;
                      }
                      else {
                        uVar17 = 0;
                      }
                      iVar3 = FUN_00784f26(uStack_98,((uint)local_10 >> 2) + (int)local_70[4],
                                           (uint)local_10 & 3,uVar17);
                      if (iVar3 == -1) goto LAB_0077e4fb;
                      local_10 = (uint *)((int)local_10 + 1);
                    } while (local_10 < puVar11);
                  }
                  local_a0 = (uint *)((int)local_a0 + (int)local_c);
                  local_24 = (uint *)((int)local_24 + 1);
                  local_70[4] = (uint *)((int)local_70[4] + local_94);
                } while (local_24 < local_20);
              }
              local_10 = (uint *)0x0;
              if (puVar11 != (uint *)0x0) {
                do {
                  uVar14 = FUN_00784f26(uStack_98,(uint)local_10 >> 2,(uint)local_10 & 3,0);
                  local_1c[(int)local_10] = uVar14;
                  iVar3 = FUN_007850ce();
                  if (iVar3 == 0) goto LAB_0077e4fb;
                  local_10 = (uint *)((int)local_10 + 1);
                  *(uint **)(iVar3 + 4) = local_38;
                  *(undefined4 *)(iVar3 + 0x18) = 0x2000017;
                } while (local_10 < puVar11);
              }
              iVar3 = FUN_00773e3b(param_2,(uint)puVar11 & 0xffffff | 0x30000000,
                                   (int)local_78 + (int)local_34,local_30,local_1c,local_18);
              if (iVar3 < 0) goto LAB_0077e7bf;
              local_2c = (uint *)((int)local_2c + 1);
              local_34 = local_34 + 1;
            } while (local_2c < local_8);
          }
        }
        goto LAB_0077ca5a;
      }
      iVar3 = __ftol();
      puVar11 = (uint *)(iVar3 * (int)local_8);
      if (puVar11 < local_c) {
        if (param_3 == (uint *)0x0) goto LAB_0077e7bf;
        goto LAB_0077e047;
      }
    }
    lVar19 = 0x87ac1400000db0;
    goto LAB_0077e7b1;
  case 0x17:
    if ((local_10 == (uint *)0x0) || (iVar3 = *(int *)((int)param_2 + 0x24), iVar3 == 0))
    goto LAB_0077e7bf;
    if (*(int *)(iVar3 + 4) == 0xd) {
      if ((*(int *)(iVar3 + 0x10) != 2) || (param_3 == (uint *)0x0)) goto LAB_0077e7bf;
      puVar11 = *(uint **)(iVar3 + 0x18);
LAB_0077e047:
      puVar9 = local_8;
      puVar11 = local_14 + (int)puVar11;
      goto code_r0x0077e053;
    }
    if ((*(int *)(iVar3 + 4) != 1) || (param_3 == (uint *)0x0)) goto LAB_0077e7bf;
    puVar11 = (uint *)0x0;
    if (local_8 != (uint *)0x0) {
      do {
        param_3[(int)puVar11] = local_14[*(int *)(*(int *)(iVar3 + 8) + 0x18)];
        iVar3 = *(int *)(iVar3 + 0xc);
        puVar11 = (uint *)((int)puVar11 + 1);
      } while (puVar11 < local_8);
    }
    goto LAB_0077ca5a;
  case 0x18:
    if (((local_10 == (uint *)0x0) || (local_20 == (uint *)0x0)) || (param_3 == (uint *)0x0))
    goto LAB_0077e7bf;
    local_30 = operator_new((int)local_8 << 4);
    if (local_30 != (uint *)0x0) {
      uVar14 = 0;
      puVar5 = local_30;
      do {
        local_48[uVar14] = (uint)puVar5;
        uVar14 = uVar14 + 1;
        puVar5 = puVar5 + (int)puVar11;
      } while (uVar14 < 4);
      local_24 = (uint *)0x0;
      if (puVar11 != (uint *)0x0) {
        local_2c = local_28 + (int)puVar11;
        local_70[2] = (uint *)((int)local_14 - (int)local_28);
        local_1c = (uint *)(local_48[0] - (int)local_28);
        puVar11 = local_28;
        do {
          iVar3 = FUN_007732ad(*(undefined4 *)((int)local_70[2] + (int)puVar11),&local_9c);
          if (iVar3 < 0) break;
          if ((double)CONCAT44(uStack_98,local_9c) == 0.0) {
            uVar14 = *local_2c;
          }
          else {
            uVar14 = *puVar11;
          }
          local_24 = (uint *)((int)local_24 + 1);
          local_2c = local_2c + 1;
          *(uint *)((int)local_1c + (int)puVar11) = uVar14;
          puVar11 = puVar11 + 1;
        } while (local_24 < local_8);
      }
      if (local_24 == local_8) {
        iVar3 = FUN_00773063(param_3,local_8);
        puVar11 = (uint *)local_48[0];
        goto joined_r0x0077e15b;
      }
      iVar3 = FUN_00773063(local_48[0],local_8);
      if (((iVar3 < 0) || (iVar3 = FUN_00773063(local_48[1],local_8), iVar3 < 0)) ||
         ((iVar3 = FUN_00773063(local_40,local_8), iVar3 < 0 ||
          (iVar3 = FUN_00773063(local_3c,local_8), iVar3 < 0)))) goto LAB_0077e7bf;
      local_c = (uint *)((uint)local_8 & 0xffffff);
      local_10 = (uint *)((uint)local_c | 0x11000000);
      iVar3 = FUN_00773e3b(param_2,local_10,local_48[0],local_14,0,0);
      if (((iVar3 < 0) ||
          (iVar3 = FUN_00773e3b(param_2,(uint)local_c | 0x21000000,local_48[1],local_14,local_48[0],
                                4), iVar3 < 0)) ||
         ((iVar3 = FUN_00773e3b(param_2,local_10,local_40,local_48[1],0,8), iVar3 < 0 ||
          (iVar3 = FUN_00773e3b(param_2,(uint)local_c | 0x22000000,local_3c,local_40,local_48[1],
                                0x2000017), iVar3 < 0)))) goto LAB_0077e7bf;
      iVar3 = FUN_00775982(param_2,param_3,local_28 + (int)local_8,local_28,local_3c);
      goto LAB_0077ce22;
    }
    break;
  case 0x19:
    iVar3 = FUN_00773b61(*(undefined4 *)((int)param_2 + 0x20),local_70 + 2);
    if (iVar3 == 0) {
      FUN_00773c7b(param_1,param_2,0xdb6,"function \'%s\' missing implementation");
      goto LAB_0077e7bf;
    }
    *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) + 1;
    iVar3 = FUN_0077be0f(local_70[2],iVar3,*(undefined4 *)((int)param_2 + 0x24),param_3,0,0);
    *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) + -1;
    goto LAB_0077ce22;
  case 0x1a:
    iVar3 = FUN_00776904(param_2);
    goto LAB_0077ce22;
  default:
    pcVar20 = "internal error: unrecognized expression";
LAB_0077e7af:
    lVar19 = ZEXT48(pcVar20) << 0x20;
    param_2 = (uint *)0x0;
LAB_0077e7b1:
    FUN_00773c7b(param_1,param_2,lVar19);
    goto LAB_0077e7bf;
  }
LAB_0077e4fb:
  FUN_00773c7b(param_1,param_2,0);
LAB_0077e7bf:
                    /* WARNING: Subroutine does not return */
  _free(local_14);
}



/* function 0078d961 FUN_0078d961 */

/* WARNING: Type propagation algorithm not settling */

void __fastcall FUN_0078d961(int *param_1)

{
  uint *puVar1;
  int iVar2;
  undefined4 uVar3;
  uint *puVar4;
  int *piVar5;
  uint *puVar6;
  int *piVar7;
  void *pvVar8;
  undefined4 *puVar9;
  uint *puVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  bool bVar15;
  undefined8 uVar16;
  ulonglong uVar17;
  longlong lVar18;
  int aiStack_cc [4];
  int aiStack_bc [4];
  int aiStack_ac [4];
  uint local_9c [4];
  uint local_8c [8];
  int local_6c [4];
  undefined1 local_5c [16];
  int local_4c;
  uint local_48;
  undefined4 *local_44;
  uint *local_40;
  int *local_3c;
  uint *local_38;
  int *local_34;
  int *local_30;
  uint *local_2c;
  uint *local_28;
  uint *local_24;
  uint *local_20;
  int *local_1c;
  uint *local_18;
  int *local_14;
  uint *local_10;
  uint *local_c;
  uint *local_8;
  
  puVar1 = local_8c + 4;
  local_8 = (uint *)0x0;
  FUN_0078937f();
  local_18 = (uint *)0x0;
  local_44 = (undefined4 *)0x0;
  if (param_1[2] != 0) {
    puVar9 = (undefined4 *)param_1[5];
    iVar12 = param_1[2];
    do {
      if ((param_1[0x18] == *(int *)*puVar9) &&
         (puVar4 = (uint *)((int *)*puVar9)[2], local_18 <= puVar4)) {
        local_18 = (uint *)((int)puVar4 + 1);
      }
      puVar9 = puVar9 + 1;
      iVar12 = iVar12 + -1;
    } while (iVar12 != 0);
  }
  if ((*(byte *)(param_1 + 0x24) & 1) != 0) {
    local_2c = (uint *)param_1[3];
    local_20 = (uint *)0x0;
    if ((uint *)param_1[3] != (uint *)0x0) {
      do {
        iVar12 = *(int *)(param_1[6] + (int)local_20 * 4);
        iVar2 = FUN_00785538();
        if (((iVar2 == 0) && (*(uint *)(iVar12 + 0xc) != 0)) &&
           ((*(byte *)(*(int *)(param_1[4] +
                               **(int **)(param_1[5] + **(int **)(iVar12 + 0x10) * 4) * 4) + 4) &
            0x10) != 0)) {
          uVar11 = 0;
          bVar15 = *(int *)(iVar12 + 4) == 0;
          if (*(int *)(iVar12 + 4) != 0) {
            local_14 = *(int **)(iVar12 + 8);
            do {
              if (uVar11 != *(uint *)(*(int *)(param_1[5] + *local_14 * 4) + 0xc)) break;
              local_14 = local_14 + 1;
              uVar11 = uVar11 + 1;
            } while (uVar11 < *(uint *)(iVar12 + 4));
            bVar15 = uVar11 == *(uint *)(iVar12 + 4);
          }
          if (!bVar15) {
            iVar2 = FUN_00784f82(*(uint *)(iVar12 + 0xc) & 0xffffff | 0x10000000,0xffffffff,
                                 0xffffffff);
            if (iVar2 == -1) goto LAB_0078ed18;
            local_14 = *(int **)(param_1[6] + iVar2 * 4);
            FUN_007854e4();
            local_10 = (uint *)0x0;
            if (*(int *)(iVar12 + 0xc) != 0) {
              do {
                iVar2 = (int)local_10 * 4;
                *(undefined4 *)(iVar2 + local_14[4]) =
                     *(undefined4 *)(iVar2 + *(int *)(iVar12 + 0x10));
                uVar3 = FUN_00784f26(param_1[0x18],local_18,local_10,0);
                *(undefined4 *)(iVar2 + *(int *)(iVar12 + 0x10)) = uVar3;
                *(undefined4 *)(iVar2 + local_14[2]) =
                     *(undefined4 *)(iVar2 + *(int *)(iVar12 + 0x10));
                if (*(int *)(iVar2 + local_14[2]) == -1) goto LAB_0078ed18;
                local_10 = (uint *)((int)local_10 + 1);
                *(undefined4 *)(*(int *)(param_1[5] + *(int *)(iVar2 + local_14[2]) * 4) + 0x18) =
                     *(undefined4 *)
                      (*(int *)(param_1[5] + *(int *)(iVar2 + local_14[4]) * 4) + 0x18);
              } while (local_10 < *(uint **)(iVar12 + 0xc));
            }
            local_18 = (uint *)((int)local_18 + 1);
            local_8 = (uint *)0x1;
          }
        }
        local_20 = (uint *)((int)local_20 + 1);
      } while (local_20 < local_2c);
    }
  }
  if (((*(byte *)((int)param_1 + 0x93) & 2) != 0) && (local_c = (uint *)0x0, param_1[3] != 0)) {
    do {
      local_20 = *(uint **)(param_1[6] + (int)local_c * 4);
      iVar12 = FUN_007855e7();
      if (iVar12 != 0) {
        local_14 = (int *)0x1;
        uVar16 = CONCAT44(&local_1c,1);
        while( true ) {
          local_24 = (uint *)FUN_007854fe(uVar16);
          if (local_24 == (uint *)0x0) break;
          puVar4 = (uint *)0x0;
          if (local_24 != (uint *)0x0) {
            do {
              if (*(uint **)(*(int *)(param_1[5] + local_1c[(int)puVar4] * 4) + 0xc) != puVar4)
              break;
              puVar4 = (uint *)((int)puVar4 + 1);
            } while (puVar4 < local_24);
          }
          if (puVar4 != local_24) {
            puVar4 = (uint *)FUN_00784f82((uint)local_24 & 0xffffff | 0x10000000,0xffffffff,
                                          0xffffffff);
            local_2c = puVar4;
            if (puVar4 == (uint *)0xffffffff) goto LAB_0078ed18;
            iVar12 = *(int *)(param_1[6] + (int)puVar4 * 4);
            FUN_007854e4();
            local_10 = (uint *)0x0;
            if (local_24 != (uint *)0x0) {
              do {
                puVar4 = local_10;
                iVar13 = (int)local_10 * 4;
                *(int *)(iVar13 + *(int *)(iVar12 + 8)) = local_1c[(int)local_10];
                iVar2 = FUN_00784f26(param_1[0x18],local_18,local_10,0);
                local_1c[(int)puVar4] = iVar2;
                *(int *)(iVar13 + *(int *)(iVar12 + 0x10)) = local_1c[(int)puVar4];
                iVar2 = *(int *)(iVar13 + *(int *)(iVar12 + 0x10));
                if (iVar2 == -1) goto LAB_0078ed18;
                local_10 = (uint *)((int)local_10 + 1);
                *(undefined4 *)(*(int *)(param_1[5] + iVar2 * 4) + 0x18) =
                     *(undefined4 *)
                      (*(int *)(param_1[5] + *(int *)(iVar13 + *(int *)(iVar12 + 8)) * 4) + 0x18);
                puVar4 = local_2c;
              } while (local_10 < local_24);
            }
            for (; local_c < puVar4; puVar4 = (uint *)((int)puVar4 + -1)) {
              puVar9 = (undefined4 *)(param_1[6] + (int)puVar4 * 4);
              *puVar9 = puVar9[-1];
            }
            local_c = (uint *)((int)local_c + 1);
            local_18 = (uint *)((int)local_18 + 1);
            *(int *)(param_1[6] + (int)puVar4 * 4) = iVar12;
            local_8 = (uint *)0x1;
          }
          local_14 = (int *)((int)local_14 + 1);
          uVar16 = CONCAT44(&local_1c,local_14);
        }
      }
      local_c = (uint *)((int)local_c + 1);
    } while (local_c < (uint *)param_1[3]);
  }
  local_c = (uint *)0x0;
  if (param_1[3] != 0) {
    do {
      local_20 = *(uint **)(param_1[6] + (int)local_c * 4);
      if ((*local_20 & 0xff000000) == 0x34000000) {
        if (local_20[1] == 4) {
          piVar5 = (int *)local_20[2];
          iVar12 = param_1[5];
          local_2c = *(uint **)(iVar12 + *piVar5 * 4);
          if ((((*(byte *)(*(int *)(param_1[4] + *local_2c * 4) + 5) & 1) == 0) &&
              (local_2c[3] == 0)) &&
             ((*(int *)(*(int *)(iVar12 + piVar5[1] * 4) + 0xc) == 1 &&
              ((*(int *)(*(int *)(iVar12 + piVar5[2] * 4) + 0xc) == 2 &&
               (*(int *)(*(int *)(iVar12 + piVar5[3] * 4) + 0xc) == 3)))))) goto LAB_0078ddf4;
        }
        puVar4 = (uint *)FUN_00784f82(0x10000004,0xffffffff,0xffffffff);
        local_2c = puVar4;
        iVar12 = FUN_00784f82(0x34000004,0xffffffff,0xffffffff);
        if ((puVar4 == (uint *)0xffffffff) || (iVar12 == -1)) goto LAB_0078ed18;
        iVar2 = *(int *)(param_1[6] + (int)puVar4 * 4);
        local_14 = *(int **)(param_1[6] + iVar12 * 4);
        FUN_007854e4();
        FUN_007854e4();
        local_8 = (uint *)0x0;
        do {
          if (local_8 < (uint *)local_20[1]) {
            uVar3 = *(undefined4 *)(local_20[2] + (int)local_8 * 4);
          }
          else {
            uVar3 = *(undefined4 *)((local_20[2] - 4) + (int)local_20[1] * 4);
          }
          iVar13 = (int)local_8 * 4;
          *(undefined4 *)(iVar13 + *(int *)(iVar2 + 8)) = uVar3;
          uVar3 = FUN_00784f26(param_1[0x18],local_18,local_8,0);
          *(undefined4 *)(iVar13 + local_14[2]) = uVar3;
          *(undefined4 *)(iVar13 + *(int *)(iVar2 + 0x10)) = *(undefined4 *)(iVar13 + local_14[2]);
          iVar12 = *(int *)(iVar13 + *(int *)(iVar2 + 0x10));
          if (iVar12 == -1) goto LAB_0078ed18;
          local_8 = (uint *)((int)local_8 + 1);
          *(undefined4 *)(*(int *)(param_1[5] + iVar12 * 4) + 0x18) =
               *(undefined4 *)
                (*(int *)(param_1[5] + *(int *)(iVar13 + *(int *)(iVar2 + 8)) * 4) + 0x18);
          puVar4 = local_2c;
        } while (local_8 < &DAT_00000004);
        for (; local_c < puVar4; puVar4 = (uint *)((int)puVar4 + -1)) {
          puVar9 = (undefined4 *)(param_1[6] + (int)puVar4 * 4);
          *puVar9 = puVar9[-1];
        }
        *(int *)(param_1[6] + (int)local_c * 4) = iVar2;
        puVar4 = (uint *)((int)local_c + 1);
        local_c = puVar4;
        FUN_00784bd1();
        param_1[3] = param_1[3] + -1;
        local_18 = (uint *)((int)local_18 + 1);
        *(int **)(param_1[6] + (int)puVar4 * 4) = local_14;
        local_8 = (uint *)0x1;
      }
LAB_0078ddf4:
      local_c = (uint *)((int)local_c + 1);
    } while (local_c < (uint *)param_1[3]);
  }
  if ((*(byte *)(param_1 + 0x24) & 6) != 0) {
    local_1c = (int *)0x0;
    if (param_1[3] != 0) {
      do {
        puVar4 = *(uint **)(param_1[6] + (int)local_1c * 4);
        local_40 = puVar4;
        if (((*puVar4 & 0xff000000) == 0x10000000) &&
           (iVar12 = param_1[5],
           (*(byte *)(*(int *)(param_1[4] + **(int **)(iVar12 + *(int *)puVar4[4] * 4) * 4) + 4) &
           0x10) == 0)) {
          local_10 = (uint *)0x0;
          if (puVar4[3] != 0) {
            local_2c = *(uint **)(*(int *)(iVar12 + *(int *)puVar4[2] * 4) + 0x2c);
            local_14 = (int *)puVar4[2];
            do {
              if (local_2c != *(uint **)(*(int *)(iVar12 + *local_14 * 4) + 0x2c)) break;
              local_10 = (uint *)((int)local_10 + 1);
              local_14 = local_14 + 1;
            } while (local_10 < (uint *)puVar4[3]);
          }
          if (local_10 != (uint *)puVar4[3]) {
            puVar6 = (uint *)puVar4[1];
            local_c = (uint *)0x0;
            local_8 = (uint *)0x0;
            if (puVar6 != (uint *)0x0) {
              do {
                piVar5 = (int *)(puVar4[2] + (int)local_8 * 4);
                iVar12 = *piVar5;
                if (iVar12 != -1) {
                  local_28 = *(uint **)(*(int *)(param_1[5] + iVar12 * 4) + 0x2c);
                  uVar11 = 0;
                  if (local_8 < puVar6) {
                    local_20 = (uint *)((int)puVar6 - (int)local_8);
                    local_14 = piVar5;
                    do {
                      if ((*local_14 != -1) &&
                         (local_28 == *(uint **)(*(int *)(param_1[5] + *local_14 * 4) + 0x2c))) {
                        uVar11 = uVar11 + 1;
                      }
                      local_14 = local_14 + 1;
                      local_20 = (uint *)((int)local_20 + -1);
                    } while (local_20 != (uint *)0x0);
                  }
                  iVar12 = FUN_00784f82(uVar11 & 0xffffff | 0x10000000,0xffffffff,0xffffffff);
                  if (iVar12 == -1) goto LAB_0078ed18;
                  piVar5 = *(int **)(param_1[6] + iVar12 * 4);
                  local_30 = piVar5;
                  FUN_007854e4();
                  local_c = (uint *)((int)local_c + 1);
                  local_10 = local_8;
                  if (local_8 < (uint *)puVar4[1]) {
                    local_20 = (uint *)0x0;
                    do {
                      iVar12 = (int)local_10 * 4;
                      if ((*(int *)(iVar12 + puVar4[2]) != -1) &&
                         (local_28 ==
                          *(uint **)(*(int *)(param_1[5] + *(int *)(iVar12 + puVar4[2]) * 4) + 0x2c)
                         )) {
                        *(undefined4 *)((int)local_20 + piVar5[4]) =
                             *(undefined4 *)(iVar12 + puVar4[4]);
                        *(undefined4 *)((int)local_20 + local_30[2]) =
                             *(undefined4 *)(iVar12 + puVar4[2]);
                        *(undefined4 *)(iVar12 + puVar4[2]) = 0xffffffff;
                        local_20 = local_20 + 1;
                        piVar5 = local_30;
                      }
                      local_10 = (uint *)((int)local_10 + 1);
                    } while (local_10 < (uint *)puVar4[1]);
                  }
                }
                local_8 = (uint *)((int)local_8 + 1);
                puVar6 = (uint *)puVar4[1];
              } while (local_8 < puVar6);
              if (local_c != (uint *)0x0) {
                puVar6 = (uint *)(param_1[6] + (param_1[3] - (int)local_c) * 4);
                puVar10 = puVar1;
                for (puVar4 = local_c; puVar4 != (uint *)0x0; puVar4 = (uint *)((int)puVar4 + -1)) {
                  *puVar10 = *puVar6;
                  puVar6 = puVar6 + 1;
                  puVar10 = puVar10 + 1;
                }
              }
            }
            piVar5 = (int *)(param_1[3] + -1);
            if (local_1c < piVar5) {
              iVar12 = ((int)piVar5 - (int)local_c) * 4;
              do {
                puVar9 = (undefined4 *)(param_1[6] + iVar12);
                iVar12 = iVar12 + -4;
                piVar5 = (int *)((int)piVar5 + -1);
                *(undefined4 *)(param_1[6] + (int)piVar5 * 4) = *puVar9;
              } while (local_1c < piVar5);
            }
            puVar4 = (uint *)0x0;
            if (local_c != (uint *)0x0) {
              iVar12 = (int)local_1c << 2;
              do {
                *(uint *)(iVar12 + param_1[6]) = puVar1[(int)puVar4];
                puVar4 = (uint *)((int)puVar4 + 1);
                iVar12 = iVar12 + 4;
              } while (puVar4 < local_c);
            }
            FUN_00784bd1();
            param_1[3] = param_1[3] + -1;
            local_1c = (int *)((int)local_1c + -1 + (int)local_c);
            local_8 = (uint *)0x1;
          }
        }
        local_1c = (int *)((int)local_1c + 1);
      } while (local_1c < (int *)param_1[3]);
    }
    local_1c = (int *)0x0;
    if (param_1[3] != 0) {
      do {
        puVar4 = *(uint **)((int)local_1c * 4 + param_1[6]);
        local_2c = puVar4;
        if ((*puVar4 & 0xff000000) == 0x10000000) {
          iVar12 = param_1[5];
          if ((*(byte *)(*(int *)(param_1[4] + **(int **)(iVar12 + *(int *)puVar4[4] * 4) * 4) + 4)
              & 0x10) == 0) {
            puVar10 = (uint *)0x0;
            local_10 = (uint *)0x0;
            local_c = (uint *)0x0;
            puVar6 = (uint *)0x0;
            if (puVar4[3] != 0) {
              local_34 = (int *)puVar4[2];
              local_14 = (int *)((int)puVar4[4] - (int)local_34);
              do {
                local_20 = *(uint **)(*(int *)(iVar12 + *local_34 * 4) + 0xc);
                if (*(uint **)(*(int *)(iVar12 + *(int *)((int)local_14 + (int)local_34) * 4) + 0xc)
                    == local_20) {
                  puVar10 = (uint *)((int)puVar10 + 1);
                }
                local_24 = (uint *)0x0;
                if (local_c != (uint *)0x0) {
                  local_38 = (uint *)puVar4[2];
                  do {
                    if (*(uint **)(*(int *)(iVar12 + *local_38 * 4) + 0xc) == local_20) {
                      local_10 = (uint *)((int)local_10 + 1);
                      break;
                    }
                    local_24 = (uint *)((int)local_24 + 1);
                    local_38 = local_38 + 1;
                  } while (local_24 < local_c);
                }
                local_c = (uint *)((int)local_c + 1);
                puVar6 = (uint *)puVar4[3];
                local_34 = local_34 + 1;
              } while (local_c < puVar6);
            }
            if (((puVar10 != puVar6) && ((uint *)((int)local_10 + 1) != puVar6)) &&
               (((uint *)0x1 < puVar10 || (local_10 != (uint *)0x0)))) {
              local_c = (uint *)0x0;
              if ((uint *)0x1 < puVar10) {
                iVar12 = FUN_00784f82((uint)puVar10 & 0xffffff | 0x10000000,0xffffffff,0xffffffff);
                if (iVar12 == -1) goto LAB_0078ed18;
                local_20 = *(uint **)(param_1[6] + iVar12 * 4);
                FUN_007854e4();
                local_c = (uint *)0x1;
                local_10 = (uint *)0x0;
                if (puVar4[3] != 0) {
                  local_28 = (uint *)0x0;
                  do {
                    iVar12 = (int)local_10 * 4;
                    if (*(int *)(*(int *)(param_1[5] + *(int *)(iVar12 + puVar4[4]) * 4) + 0xc) ==
                        *(int *)(*(int *)(param_1[5] + *(int *)(iVar12 + puVar4[2]) * 4) + 0xc)) {
                      *(int *)((int)local_28 + local_20[4]) = *(int *)(iVar12 + puVar4[4]);
                      *(undefined4 *)((int)local_28 + local_20[2]) =
                           *(undefined4 *)(iVar12 + puVar4[2]);
                      *(undefined4 *)(iVar12 + puVar4[2]) = 0xffffffff;
                      local_28 = local_28 + 1;
                    }
                    local_10 = (uint *)((int)local_10 + 1);
                  } while (local_10 < (uint *)puVar4[3]);
                }
              }
              puVar6 = (uint *)puVar4[1];
              local_8 = (uint *)0x0;
              if (puVar6 != (uint *)0x0) {
                do {
                  piVar5 = (int *)(puVar4[2] + (int)local_8 * 4);
                  iVar12 = *piVar5;
                  if (iVar12 != -1) {
                    local_28 = *(uint **)(*(int *)(param_1[5] + iVar12 * 4) + 0xc);
                    uVar11 = 0;
                    if (local_8 < puVar6) {
                      local_20 = (uint *)((int)puVar6 - (int)local_8);
                      local_34 = piVar5;
                      do {
                        if ((*local_34 != -1) &&
                           (local_28 == *(uint **)(*(int *)(param_1[5] + *local_34 * 4) + 0xc))) {
                          uVar11 = uVar11 + 1;
                        }
                        local_34 = local_34 + 1;
                        local_20 = (uint *)((int)local_20 + -1);
                      } while (local_20 != (uint *)0x0);
                    }
                    iVar12 = FUN_00784f82(uVar11 & 0xffffff | 0x10000000,0xffffffff,0xffffffff);
                    if (iVar12 == -1) goto LAB_0078ed18;
                    piVar5 = *(int **)(param_1[6] + iVar12 * 4);
                    local_30 = piVar5;
                    FUN_007854e4();
                    local_c = (uint *)((int)local_c + 1);
                    local_10 = local_8;
                    if (local_8 < (uint *)puVar4[1]) {
                      local_20 = (uint *)0x0;
                      do {
                        iVar12 = (int)local_10 * 4;
                        if ((*(int *)(iVar12 + puVar4[2]) != -1) &&
                           (local_28 ==
                            *(uint **)(*(int *)(param_1[5] + *(int *)(iVar12 + puVar4[2]) * 4) + 0xc
                                      ))) {
                          *(undefined4 *)((int)local_20 + piVar5[4]) =
                               *(undefined4 *)(iVar12 + puVar4[4]);
                          *(undefined4 *)((int)local_20 + local_30[2]) =
                               *(undefined4 *)(iVar12 + puVar4[2]);
                          *(undefined4 *)(iVar12 + puVar4[2]) = 0xffffffff;
                          local_20 = local_20 + 1;
                          piVar5 = local_30;
                        }
                        local_10 = (uint *)((int)local_10 + 1);
                      } while (local_10 < (uint *)puVar4[1]);
                    }
                  }
                  local_8 = (uint *)((int)local_8 + 1);
                  puVar6 = (uint *)puVar4[1];
                } while (local_8 < puVar6);
              }
              if (local_c != (uint *)0x0) {
                puVar6 = (uint *)(param_1[6] + (param_1[3] - (int)local_c) * 4);
                puVar10 = puVar1;
                for (puVar4 = local_c; puVar4 != (uint *)0x0; puVar4 = (uint *)((int)puVar4 + -1)) {
                  *puVar10 = *puVar6;
                  puVar6 = puVar6 + 1;
                  puVar10 = puVar10 + 1;
                }
              }
              piVar5 = (int *)(param_1[3] + -1);
              if (local_1c < piVar5) {
                iVar12 = ((int)piVar5 - (int)local_c) * 4;
                do {
                  puVar9 = (undefined4 *)(param_1[6] + iVar12);
                  iVar12 = iVar12 + -4;
                  piVar5 = (int *)((int)piVar5 + -1);
                  *(undefined4 *)(param_1[6] + (int)piVar5 * 4) = *puVar9;
                } while (local_1c < piVar5);
              }
              puVar4 = (uint *)0x0;
              if (local_c != (uint *)0x0) {
                iVar12 = (int)local_1c << 2;
                do {
                  *(uint *)(iVar12 + param_1[6]) = puVar1[(int)puVar4];
                  puVar4 = (uint *)((int)puVar4 + 1);
                  iVar12 = iVar12 + 4;
                } while (puVar4 < local_c);
              }
              FUN_00784bd1();
              param_1[3] = param_1[3] + -1;
              local_1c = (int *)((int)local_1c + -1 + (int)local_c);
              local_8 = (uint *)0x1;
            }
          }
        }
        local_1c = (int *)((int)local_1c + 1);
      } while (local_1c < (int *)param_1[3]);
    }
  }
  if (local_8 != (uint *)0x0) {
    FUN_0078937f();
  }
  puVar4 = local_18;
  local_44 = operator_new((int)local_18 << 2);
  if (local_44 == (undefined4 *)0x0) {
LAB_0078ed18:
    local_14 = (int *)0x8007000e;
  }
  else {
    puVar9 = local_44;
    for (uVar11 = (uint)puVar4 & 0x3fffffff; uVar11 != 0; uVar11 = uVar11 - 1) {
      *puVar9 = 0;
      puVar9 = puVar9 + 1;
    }
    uVar11 = 0;
    for (iVar12 = 0; iVar12 != 0; iVar12 = iVar12 + -1) {
      *(undefined1 *)puVar9 = 0;
      puVar9 = (undefined4 *)((int)puVar9 + 1);
    }
    if (param_1[2] != 0) {
      do {
        piVar5 = *(int **)(param_1[5] + uVar11 * 4);
        piVar5[0x10] = 0;
        if (param_1[0x18] == *piVar5) {
          if ((uint)local_44[piVar5[2]] <= (uint)piVar5[3]) {
            local_44[piVar5[2]] = piVar5[3] + 1;
          }
        }
        uVar11 = uVar11 + 1;
      } while (uVar11 < (uint)param_1[2]);
    }
    puVar4 = (uint *)param_1[3];
    while (puVar4 != (uint *)0x0) {
      local_20 = (uint *)((int)puVar4 + -1);
      puVar6 = *(uint **)(param_1[6] + (int)local_20 * 4);
      iVar12 = FUN_00785538();
      puVar4 = local_20;
      if (iVar12 == 0) {
        uVar11 = *puVar6;
        uVar14 = uVar11 & 0xffffff;
        if (puVar6[3] != 0) {
          iVar12 = FUN_0078557b();
          if (iVar12 == 0) {
            iVar12 = FUN_007855b1();
            if (iVar12 == 0) {
              iVar12 = FUN_007855c3();
              if (iVar12 == 0) {
                iVar12 = FUN_007855d5();
                if (iVar12 == 0) goto LAB_0078e4f2;
                FUN_007892a0(puVar6[4],local_5c,uVar14,1);
                FUN_007892a0(puVar6[2],local_5c,uVar14,0);
                FUN_007892a0(puVar6[2] + puVar6[3] * 4,local_5c,uVar14,0);
                uVar14 = puVar6[2] + puVar6[3] * 8;
              }
              else {
                FUN_007892a0(puVar6[4],local_5c,uVar14,1);
                FUN_007892a0(puVar6[2],local_5c,uVar14,0);
                uVar14 = puVar6[2] + puVar6[3] * 4;
              }
              uVar17 = (ulonglong)uVar11 & 0xffffffff00ffffff;
            }
            else {
              FUN_007892a0(puVar6[4],local_5c,uVar14,1);
              uVar17 = (ulonglong)uVar11 & 0xffffffff00ffffff;
              uVar14 = puVar6[2];
            }
          }
          else {
            uVar17 = CONCAT44(1,uVar11) & 0xffffffff00ffffff;
            uVar14 = puVar6[4];
          }
          FUN_007892a0(uVar14,local_5c,uVar17);
        }
LAB_0078e4f2:
        local_6c[0] = 0;
        local_6c[1] = 0;
        local_6c[2] = 0;
        local_6c[3] = 0;
        iVar12 = FUN_00785545();
        if (iVar12 != 0) {
          iVar12 = param_1[5];
          local_30 = *(int **)(iVar12 + *(int *)puVar6[4] * 4);
          uVar11 = *(uint *)(*(int *)(param_1[4] + *local_30 * 4) + 4);
          if ((((uVar11 & 4) == 0) &&
              ((((*(byte *)(param_1 + 0x24) & 1) == 0 || ((uVar11 & 0x10) == 0)) &&
               (param_1[0x18] == **(int **)(iVar12 + *(int *)puVar6[2] * 4))))) &&
             (local_8 = (uint *)0x0, puVar6[1] != 0)) {
            local_34 = (int *)((int)puVar6[2] - (int)local_6c);
            local_2c = (uint *)(param_1[0xd] & 8);
            do {
              iVar2 = *(int *)(iVar12 + *(int *)((int)local_6c + (int)(local_34 + (int)local_8)) * 4
                              );
              iVar13 = *(int *)(param_1[6] + *(int *)(iVar2 + 0x2c) * 4);
              if (((local_2c != (uint *)0x0) && (local_30[0x11] != 0)) &&
                 ((iVar2 = *(int *)(iVar2 + 0x44), iVar2 != 0 && (local_30[0x11] != iVar2)))) break;
              local_28 = *(uint **)(iVar13 + 0xc);
              local_10 = (uint *)0x0;
              if (local_28 != (uint *)0x0) {
                piVar5 = *(int **)(iVar13 + 0x10);
                do {
                  iVar2 = *(int *)(iVar12 + *piVar5 * 4);
                  if ((local_20 != *(uint **)(iVar2 + 0x38)) ||
                     (local_20 != *(uint **)(iVar2 + 0x3c))) break;
                  local_10 = (uint *)((int)local_10 + 1);
                  piVar5 = piVar5 + 1;
                } while (local_10 < local_28);
              }
              if (local_10 == local_28) {
                local_6c[(int)local_8] = 1;
              }
              local_8 = (uint *)((int)local_8 + 1);
            } while (local_8 < (uint *)puVar6[1]);
          }
        }
        iVar12 = FUN_007855b1();
        if ((iVar12 == 0) && (iVar12 = FUN_007855c3(), iVar12 == 0)) {
          iVar12 = FUN_007855d5();
          uVar11 = 0;
          if (iVar12 != 0) goto LAB_0078e623;
          do {
            local_9c[uVar11] = uVar11;
            uVar11 = uVar11 + 1;
          } while (uVar11 < 4);
        }
        else {
LAB_0078e623:
          local_10 = (uint *)0x0;
          if (puVar6[3] != 0) {
            uVar11 = puVar6[4];
            iVar12 = param_1[5];
            do {
              iVar2 = (int)local_10 * 4;
              puVar4 = local_9c + (int)local_10;
              local_10 = (uint *)((int)local_10 + 1);
              *puVar4 = *(uint *)(*(int *)(iVar12 + *(int *)(uVar11 + iVar2) * 4) + 0xc);
            } while (local_10 < (uint *)puVar6[3]);
          }
        }
        local_28 = (uint *)0x0;
        lVar18 = ZEXT48(&local_1c) << 0x20;
        while( true ) {
          local_24 = (uint *)FUN_007854fe(lVar18);
          if (local_24 == (uint *)0x0) break;
          local_8c[0] = 0;
          local_8c[1] = 0;
          local_8c[2] = 0;
          local_c = (uint *)0x0;
          local_30 = (int *)0x0;
          local_8c[3] = 0;
          local_8 = (uint *)0x0;
          if (local_24 == (uint *)0x0) {
LAB_0078e856:
            iVar12 = FUN_00785545();
            uVar11 = 0;
            if (iVar12 == 0) {
              do {
                if ((uint *)local_8c[uVar11] == local_24) {
                  local_c = (uint *)0x1;
                  break;
                }
                uVar11 = uVar11 + 1;
              } while (uVar11 < 4);
              if (local_c != (uint *)0x0) goto LAB_0078e8bb;
            }
            if ((local_30 != (int *)local_44[*(int *)(*(int *)(param_1[5] + *local_1c * 4) + 8)]) &&
               (uVar11 = 0, puVar6[3] != 0)) {
              do {
                if (local_6c[uVar11] == 0) {
                  local_c = (uint *)0x1;
                  break;
                }
                uVar11 = uVar11 + 1;
              } while (uVar11 < puVar6[3]);
              if (local_c != (uint *)0x0) goto LAB_0078e8bb;
            }
            local_8 = (uint *)0x0;
            if (local_24 != (uint *)0x0) {
              do {
                if (local_6c[(int)local_8] == 0) {
                  puVar9 = *(undefined4 **)(param_1[5] + local_1c[(int)local_8] * 4);
                  if (local_8c[puVar9[3]] == 1) {
                    aiStack_ac[(int)local_8] = local_1c[(int)local_8];
                    puVar9[3] = local_9c[(int)local_8];
                  }
                  else {
                    iVar12 = FUN_00784f26(*puVar9,puVar9[2],local_9c[(int)local_8],0);
                    aiStack_ac[(int)local_8] = iVar12;
                    if (iVar12 == -1) goto LAB_0078ed18;
                    local_3c = (int *)(iVar12 << 2);
                    FUN_007857c5();
                    *(undefined4 *)(*(int *)((int)local_3c + param_1[5]) + 0x18) = puVar9[6];
                    local_44[puVar9[2]] = local_44[puVar9[2]] + 1;
                    local_8c[puVar9[3]] = local_8c[puVar9[3]] - 1;
                  }
                }
                else {
                  aiStack_ac[(int)local_8] = *(int *)(puVar6[4] + (int)local_8 * 4);
                }
                local_8 = (uint *)((int)local_8 + 1);
              } while (local_8 < local_24);
            }
            local_10 = (uint *)0x0;
            if (local_24 != (uint *)0x0) {
              do {
                local_38 = *(uint **)(param_1[5] + local_1c[(int)local_10] * 4);
                if (local_38[0x10] == 0) {
                  local_18 = (uint *)0x0;
                  for (puVar4 = local_10; puVar10 = local_18, puVar4 < local_24;
                      puVar4 = (uint *)((int)puVar4 + 1)) {
                    iVar12 = *(int *)(param_1[5] + local_1c[(int)puVar4] * 4);
                    if (local_38[0xb] == *(uint *)(iVar12 + 0x2c)) {
                      local_18 = (uint *)((int)local_18 + 1);
                      aiStack_bc[(int)puVar10] = local_1c[(int)puVar4];
                      aiStack_cc[(int)puVar10] = aiStack_ac[(int)puVar4];
                      *(undefined4 *)(iVar12 + 0x40) = 1;
                    }
                  }
                  puVar4 = *(uint **)(param_1[6] + local_38[0xb] * 4);
                  iVar12 = FUN_007855b1();
                  if (((iVar12 != 0) || (iVar12 = FUN_007855c3(), iVar12 != 0)) ||
                     (iVar12 = FUN_007855d5(), iVar12 != 0)) {
                    local_8 = (uint *)0x0;
                    if (local_18 != (uint *)0x0) {
                      piVar5 = (int *)puVar4[3];
                      do {
                        local_14 = (int *)0x0;
                        if (piVar5 != (int *)0x0) {
                          piVar7 = (int *)puVar4[4];
                          do {
                            if (*piVar7 == aiStack_bc[(int)local_8]) {
                              puVar1[(int)local_8] = (uint)local_14;
                              break;
                            }
                            local_14 = (int *)((int)local_14 + 1);
                            piVar5 = (int *)puVar4[3];
                            piVar7 = piVar7 + 1;
                          } while (local_14 < piVar5);
                        }
                        local_8 = (uint *)((int)local_8 + 1);
                      } while (local_8 < local_18);
                    }
                    pvVar8 = operator_new(0x38);
                    if (pvVar8 == (void *)0x0) {
                      local_c = (uint *)0x0;
                    }
                    else {
                      local_c = (uint *)FUN_007851ab();
                    }
                    if (local_c == (uint *)0x0) goto LAB_0078ed18;
                    iVar12 = FUN_007855b1();
                    puVar10 = local_18;
                    if (iVar12 == 0) {
                      iVar12 = FUN_007855c3();
                      if (iVar12 == 0) {
                        puVar10 = (uint *)((int)local_18 * 3);
                      }
                      else {
                        puVar10 = (uint *)((int)local_18 * 2);
                      }
                    }
                    local_14 = (int *)FUN_00785202((*puVar4 ^ (uint)local_18) & 0xffffff ^ *puVar4,
                                                   puVar10,local_18,0);
                    if (-1 < (int)local_14) {
                      local_14 = (int *)FUN_007854e4();
                      if (-1 < (int)local_14) {
                        local_8 = (uint *)0x0;
                        if (local_18 != (uint *)0x0) {
                          local_3c = (int *)((int)local_18 * 3);
                          local_40 = (uint *)((int)local_18 << 3);
                          local_30 = (int *)((int)local_18 << 2);
                          do {
                            *(int *)(local_c[4] + (int)local_8 * 4) = aiStack_cc[(int)local_8];
                            *(undefined4 *)(local_c[2] + (int)local_8 * 4) =
                                 *(undefined4 *)(puVar4[2] + puVar1[(int)local_8] * 4);
                            if ((uint)((int)local_18 * 2) <= local_c[1]) {
                              *(undefined4 *)((int)local_30 + local_c[2]) =
                                   *(undefined4 *)
                                    (puVar4[2] + (puVar4[3] + puVar1[(int)local_8]) * 4);
                            }
                            if ((int *)((int)local_18 * 3) <= (int *)local_c[1]) {
                              *(undefined4 *)((int)local_40 + local_c[2]) =
                                   *(undefined4 *)
                                    (puVar4[2] + (puVar1[(int)local_8] + puVar4[3] * 2) * 4);
                            }
                            local_8 = (uint *)((int)local_8 + 1);
                            local_30 = local_30 + 1;
                            local_40 = local_40 + 1;
                          } while (local_8 < local_18);
                        }
                        if (*(int *)(param_1[6] + local_38[0xb] * 4) != 0) {
                          FUN_00784bd1();
                        }
                        *(uint **)(param_1[6] + local_38[0xb] * 4) = local_c;
                        goto LAB_0078ec06;
                      }
                    }
                    FUN_00784bd1();
                    goto LAB_0078e3d0;
                  }
                  local_14 = (int *)0x0;
                  if (puVar4[3] != 0) {
                    do {
                      local_3c = (int *)(puVar4[4] + (int)local_14 * 4);
                      puVar10 = (uint *)0x0;
                      do {
                        if (*local_3c == local_1c[(int)puVar10]) {
                          *local_3c = aiStack_ac[(int)puVar10];
                          break;
                        }
                        puVar10 = (uint *)((int)puVar10 + 1);
                      } while (puVar10 < local_24);
                      local_14 = (int *)((int)local_14 + 1);
                    } while (local_14 < (int *)puVar4[3]);
                  }
                }
LAB_0078ec06:
                local_10 = (uint *)((int)local_10 + 1);
              } while (local_10 < local_24);
            }
            puVar4 = (uint *)0x0;
            if (local_24 != (uint *)0x0) {
              do {
                local_1c[(int)puVar4] = aiStack_ac[(int)puVar4];
                piVar5 = local_1c + (int)puVar4;
                puVar4 = (uint *)((int)puVar4 + 1);
                *(undefined4 *)(*(int *)(param_1[5] + *piVar5 * 4) + 0x40) = 1;
              } while (puVar4 < local_24);
            }
          }
          else {
            do {
              local_14 = *(int **)(param_1[5] + local_1c[(int)local_8] * 4);
              if ((param_1[0x18] != *local_14) || (iVar12 = local_14[0xb], iVar12 == -1)) break;
              if (local_14[0x10] != 0) {
                local_c = (uint *)0x1;
              }
              uVar11 = local_8c[local_14[3]];
              if (uVar11 == 0) {
                local_30 = (int *)((int)local_30 + 1);
              }
              local_8c[local_14[3]] = uVar11 + 1;
              puVar4 = *(uint **)(param_1[6] + iVar12 * 4);
              local_40 = puVar4;
              iVar12 = FUN_007855b1();
              if (((iVar12 == 0) && (iVar12 = FUN_007855c3(), iVar12 == 0)) &&
                 (iVar12 = FUN_007855d5(), iVar12 == 0)) {
                if ((puVar4[3] < 2) || (local_8 == (uint *)local_14[3])) {
                  iVar12 = local_14[3];
LAB_0078e829:
                  if (local_8c[iVar12] < 2) goto LAB_0078e832;
                }
                local_c = (uint *)0x1;
              }
              else {
                if ((local_14[0x10] != 0) &&
                   (local_48 = local_9c[(int)local_8], local_48 != local_14[3])) {
                  local_2c = (uint *)puVar4[3];
                  local_38 = (uint *)0xffffffff;
                  local_10 = (uint *)0xffffffff;
                  local_18 = (uint *)0x0;
                  if (local_2c != (uint *)0x0) {
                    local_3c = local_1c + (int)local_8;
                    local_34 = (int *)puVar4[4];
                    local_4c = *local_3c;
                    do {
                      if (local_4c == *local_34) {
                        local_38 = local_18;
                      }
                      if (local_48 == *(uint *)(*(int *)(param_1[5] + *local_34 * 4) + 0xc)) {
                        local_10 = local_18;
                      }
                      local_18 = (uint *)((int)local_18 + 1);
                      local_34 = local_34 + 1;
                    } while (local_18 < local_2c);
                    if ((local_38 != (uint *)0xffffffff) && (local_10 != (uint *)0xffffffff)) {
                      uVar11 = puVar4[2];
                      local_4c = (int)local_10 * 4;
                      if (((*(int *)(uVar11 + (int)local_38 * 4) == *(int *)(uVar11 + local_4c)) &&
                          ((local_48 = (int)local_2c * 2, puVar4[1] < local_48 ||
                           (puVar4 = local_40,
                           *(int *)(uVar11 + (int)((int)local_38 + (int)local_2c) * 4) ==
                           *(int *)(uVar11 + (int)((int)local_10 + (int)local_2c) * 4))))) &&
                         ((puVar4[1] < (uint)((int)local_2c * 3) ||
                          (puVar4 = local_40,
                          *(int *)(uVar11 + (int)((int)local_38 + local_48) * 4) ==
                          *(int *)(uVar11 + (int)((int)local_10 + local_48) * 4))))) {
                        *local_3c = *(int *)(local_4c + puVar4[4]);
                      }
                    }
                  }
                }
                iVar12 = (**(code **)(*param_1 + 0x20))();
                if (iVar12 != 0) {
                  iVar12 = local_14[3];
                  goto LAB_0078e829;
                }
              }
LAB_0078e832:
              local_8 = (uint *)((int)local_8 + 1);
            } while (local_8 < local_24);
            if (local_8 < local_24) {
              local_c = (uint *)0x1;
            }
            if (local_c == (uint *)0x0) goto LAB_0078e856;
LAB_0078e8bb:
            local_6c[0] = 0;
            local_6c[1] = 0;
            local_6c[2] = 0;
            local_6c[3] = 0;
          }
          local_28 = (uint *)((int)local_28 + 1);
          lVar18 = CONCAT44(&local_1c,local_28);
        }
        iVar12 = FUN_00785545();
        puVar4 = local_20;
        if (iVar12 != 0) {
          uVar11 = 0;
          local_28 = (uint *)0x0;
          if (puVar6[3] != 0) {
            do {
              if (local_6c[(int)local_28] == 0) {
                *(undefined4 *)(puVar6[4] + uVar11 * 4) =
                     *(undefined4 *)(puVar6[4] + (int)local_28 * 4);
                *(undefined4 *)(puVar6[2] + uVar11 * 4) =
                     *(undefined4 *)(puVar6[2] + (int)local_28 * 4);
                uVar11 = uVar11 + 1;
              }
              else {
                iVar12 = uVar11 * 4;
                local_3c = *(int **)(param_1[5] + *(int *)(iVar12 + puVar6[4]) * 4);
                if (local_3c[0x11] == 0) {
                  local_3c[0x11] =
                       *(int *)(*(int *)(param_1[5] + *(int *)(iVar12 + puVar6[2]) * 4) + 0x44);
                  *(undefined4 *)(*(int *)(param_1[5] + *(int *)(iVar12 + puVar6[4]) * 4) + 0x48) =
                       *(undefined4 *)
                        (*(int *)(param_1[5] + *(int *)(iVar12 + puVar6[2]) * 4) + 0x48);
                }
              }
              local_28 = (uint *)((int)local_28 + 1);
            } while (local_28 < (uint *)puVar6[3]);
          }
          *puVar6 = -(uint)(uVar11 != 0) & (uVar11 & 0xffffff | 0x10000000);
          puVar6[1] = uVar11;
          puVar6[3] = uVar11;
        }
      }
    }
    local_14 = (int *)0x0;
  }
LAB_0078e3d0:
                    /* WARNING: Subroutine does not return */
  _free(local_44);
}



/* function 007a17e5 FUN_007a17e5 */

int * __fastcall FUN_007a17e5(int param_1)

{
  int *piVar1;
  uint *puVar2;
  void *pvVar3;
  undefined4 uVar4;
  int *piVar5;
  undefined1 *puVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint *puVar10;
  int *piVar11;
  undefined4 *puVar12;
  uint *puVar13;
  uint uVar14;
  int *piVar15;
  uint *puVar16;
  undefined4 *puVar17;
  bool bVar18;
  undefined8 uVar19;
  undefined4 auStack_1f4 [24];
  int local_194 [32];
  undefined4 local_114 [24];
  undefined4 local_b4 [6];
  int local_9c [6];
  uint local_84 [6];
  uint local_6c [6];
  int *local_54;
  uint local_50;
  uint *local_4c;
  int *local_48;
  uint *local_44;
  uint *local_40;
  int *local_3c;
  uint *local_38;
  int *local_34;
  int local_30;
  int *local_2c;
  int *local_28;
  uint *local_24;
  int *local_20;
  int *local_1c;
  int *local_18;
  uint *local_14;
  int *local_10;
  uint *local_c;
  int *local_8;
  
  iVar8 = 6;
  puVar13 = local_84;
  for (iVar7 = iVar8; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar13 = 0;
    puVar13 = puVar13 + 1;
  }
  puVar12 = local_114;
  for (iVar7 = 0x18; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  puVar13 = local_6c;
  for (iVar7 = iVar8; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar13 = 0;
    puVar13 = puVar13 + 1;
  }
  piVar11 = local_9c;
  for (iVar7 = iVar8; iVar7 != 0; iVar7 = iVar7 + -1) {
    *piVar11 = 0;
    piVar11 = piVar11 + 1;
  }
  puVar12 = local_b4;
  for (; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  uVar9 = 0;
  local_30 = 0;
  if (*(int *)(param_1 + 8) != 0) {
    do {
      piVar11 = *(int **)(*(int *)(param_1 + 0x14) + uVar9 * 4);
      if (*piVar11 == *(int *)(param_1 + 0x60)) {
        piVar11[2] = -1;
      }
      uVar9 = uVar9 + 1;
    } while (uVar9 < *(uint *)(param_1 + 8));
  }
  local_14 = (uint *)0x0;
  if (*(int *)(param_1 + 0x88) != 0) {
    do {
      local_30 = 0;
      if (*(int *)(param_1 + 0x140) == 0) goto LAB_007a2024;
      puVar13 = *(uint **)(*(int *)(param_1 + 0x144) + (int)local_14 * 4);
      if ((((puVar13 != (uint *)0x0) && (uVar9 = *puVar13, uVar9 != 0)) &&
          ((uVar9 & 0xff000000) != 0xe1000000)) && ((uVar9 & 0xff000000) != 0x34000000)) {
        piVar15 = (int *)(uVar9 & 0xffffff);
        piVar11 = *(int **)(*(int *)(param_1 + 0x14) + *(int *)(puVar13[2] + (int)piVar15 * 4) * 4);
        local_20 = piVar15;
        if (((*(byte *)((int)piVar11 + 0x22) & 0xf) != 0) && (*piVar11 == *(int *)(param_1 + 0x60)))
        {
          pvVar3 = operator_new(0x38);
          if (pvVar3 == (void *)0x0) {
            local_30 = 0;
          }
          else {
            local_30 = FUN_007851ab();
          }
          if (local_30 == 0) {
            return (int *)0x8007000e;
          }
          local_8 = (int *)FUN_00785202((uint)piVar15 | 0x10000000,piVar15,piVar15,0);
          if ((int)local_8 < 0) goto LAB_007a2a30;
          local_10 = (int *)0x0;
          if (piVar15 != (int *)0x0) {
            iVar7 = (*puVar13 & 0xffffff) << 2;
            do {
              local_1c = *(int **)(*(int *)(param_1 + 0x14) + *(int *)(iVar7 + puVar13[2]) * 4);
              *(int *)(*(int *)(local_30 + 8) + (int)local_10 * 4) = *(int *)(iVar7 + puVar13[2]);
              uVar4 = FUN_00784f26(*(undefined4 *)(param_1 + 0x60),0xffffffff,local_1c[3],0);
              *(undefined4 *)(*(int *)(local_30 + 0x10) + (int)local_10 * 4) = uVar4;
              *(undefined4 *)(iVar7 + puVar13[2]) =
                   *(undefined4 *)(*(int *)(local_30 + 0x10) + (int)local_10 * 4);
              *(undefined4 *)
               (*(int *)(*(int *)(param_1 + 0x14) + *(int *)(iVar7 + puVar13[2]) * 4) + 0x20) = 0;
              local_10 = (int *)((int)local_10 + 1);
              iVar7 = iVar7 + 4;
            } while (local_10 < local_20);
          }
          iVar7 = local_30;
          local_30 = 0;
          piVar11 = (int *)(param_1 + 0x134);
          *(int *)(*(int *)(param_1 + 0x140) + *piVar11 * 4) = iVar7;
          *piVar11 = *piVar11 + 1;
        }
      }
      local_14 = (uint *)((int)local_14 + 1);
    } while (local_14 < *(uint **)(param_1 + 0x88));
  }
  local_30 = 0;
  if ((*(int *)(param_1 + 0x140) != 0) && (local_18 = (int *)0x0, *(int *)(param_1 + 0x134) != 0)) {
    local_28 = (int *)0x0;
    do {
      piVar11 = local_28;
      puVar13 = *(uint **)((int)local_28 + *(int *)(param_1 + 0x140));
      local_38 = puVar13;
      if (((puVar13 != (uint *)0x0) && (uVar9 = *puVar13 & 0xff000000, uVar9 != 0)) &&
         (uVar9 != 0x34000000)) {
        if (((uVar9 == 0x40000000) || (uVar9 == 0x44000000)) ||
           ((uVar9 == 0x48000000 || ((uVar9 == 0x4c000000 || (uVar9 == 0xe1000000)))))) {
          local_2c = (int *)0x0;
          local_1c = (int *)0x0;
          local_10 = (int *)0x0;
          if (*(int *)(param_1 + 0x138) != 0) {
LAB_007a1c7b:
            local_14 = (uint *)0x0;
            puVar13 = *(uint **)(*(int *)(param_1 + 0x144) + (int)local_10 * 4);
            puVar16 = (uint *)(*puVar13 & 0xffffff);
            local_34 = (int *)(uint)(local_10 < *(int **)(param_1 + 0x88));
            local_4c = puVar16;
            if (puVar16 == (uint *)0x0) goto LAB_007a1dbc;
            local_c = (uint *)0x0;
            local_54 = (int *)(puVar13[1] / (uint)puVar16);
            if (local_38[3] != 0) {
              local_44 = *(uint **)(*(int *)(*(int *)(param_1 + 0x140) + (int)local_28) + 0xc);
              do {
                if (local_34 < local_54) {
                  local_8 = (int *)((int)puVar16 * (int)local_34 * 4);
                  local_20 = (int *)((int)local_54 - (int)local_34);
                  do {
                    if (puVar16 != (uint *)0x0) {
                      local_50 = *(uint *)(local_38[4] + (int)local_c * 4);
                      puVar10 = (uint *)(puVar13[2] + (int)local_8);
                      local_40 = puVar16;
                      do {
                        local_24 = *(uint **)(*(int *)(param_1 + 0x14) + *puVar10 * 4);
                        if ((*puVar10 == local_50) || (local_24[9] == local_50)) {
                          *(undefined4 *)((int)local_b4 + (int)local_28) = 1;
                          puVar2 = local_4c;
                          if ((local_18 < local_10) &&
                             (**(int **)((int)local_28 + *(int *)(param_1 + 0x144)) != 0)) {
                            local_1c = (int *)0x1;
                            local_14 = local_38;
                          }
                          else if ((*(int **)(param_1 + 0x88) <= local_10) && (local_24[3] == 3)) {
                            local_9c[(uint)local_18 % 6] = 1;
                            puVar16 = puVar2;
                          }
                        }
                        puVar10 = puVar10 + 1;
                        local_40 = (uint *)((int)local_40 + -1);
                      } while (local_40 != (uint *)0x0);
                    }
                    local_8 = local_8 + (int)puVar16;
                    local_20 = (int *)((int)local_20 + -1);
                  } while (local_20 != (int *)0x0);
                }
                local_c = (uint *)((int)local_c + 1);
              } while (local_c < local_44);
            }
            if (local_1c == (int *)0x0) goto LAB_007a1dbc;
            piVar11 = (int *)(*puVar13 & 0xffffff);
            local_1c = piVar11;
            pvVar3 = operator_new(0x38);
            if (pvVar3 == (void *)0x0) {
              local_30 = 0;
            }
            else {
              local_30 = FUN_007851ab();
            }
            if (local_30 == 0) {
              return (int *)0x8007000e;
            }
            local_8 = (int *)FUN_00785202((uint)piVar11 | 0x10000000,piVar11,piVar11,0);
            if (-1 < (int)local_8) {
              puVar12 = *(undefined4 **)(local_30 + 0x10);
              for (piVar11 = local_1c; piVar11 != (int *)0x0; piVar11 = (int *)((int)piVar11 + -1))
              {
                *puVar12 = 0xffffffff;
                puVar12 = puVar12 + 1;
              }
              local_10 = (int *)0x0;
              puVar16 = local_14;
              if (puVar13[1] != 0) {
                do {
                  local_8 = (int *)0x0;
                  if (puVar16[3] != 0) {
                    do {
                      iVar7 = *(int *)(puVar16[4] + (int)local_8 * 4);
                      if (iVar7 == *(int *)(puVar13[2] + (int)local_10 * 4)) {
                        iVar8 = ((uint)local_10 % (uint)local_1c) * 4;
                        piVar11 = *(int **)(iVar8 + *(int *)(local_30 + 0x10));
                        if (piVar11 == (int *)0xffffffff) {
                          piVar11 = (int *)FUN_00784f26(*(undefined4 *)(param_1 + 0x60),0xffffffff,
                                                        *(undefined4 *)
                                                         (*(int *)(*(int *)(param_1 + 0x14) +
                                                                  iVar7 * 4) + 0xc),0);
                        }
                        local_20 = piVar11;
                        if (piVar11 == (int *)0xffffffff) {
                          return (int *)0x8007000e;
                        }
                        *(int **)(puVar13[2] + (int)local_10 * 4) = piVar11;
                        *(undefined4 *)(iVar8 + *(int *)(local_30 + 8)) =
                             *(undefined4 *)(local_14[4] + (int)local_8 * 4);
                        *(int **)(iVar8 + *(int *)(local_30 + 0x10)) = piVar11;
                        *(undefined4 *)
                         (*(int *)(*(int *)(param_1 + 0x14) + (int)piVar11 * 4) + 0x20) = 0;
                        puVar16 = local_14;
                      }
                      local_8 = (int *)((int)local_8 + 1);
                    } while (local_8 < (int *)puVar16[3]);
                  }
                  local_10 = (int *)((int)local_10 + 1);
                } while (local_10 < puVar13[1]);
              }
              *(int *)(*(int *)(param_1 + 0x140) + *(int *)(param_1 + 0x134) * 4) = local_30;
              *(int *)(param_1 + 0x134) = *(int *)(param_1 + 0x134) + 1;
              local_30 = 0;
              goto LAB_007a1f16;
            }
            goto LAB_007a2a30;
          }
LAB_007a1f16:
          piVar11 = local_28;
          local_10 = (int *)0x0;
          local_c = (uint *)0x0;
          if (*(int *)(*(int *)(*(int *)(param_1 + 0x140) + (int)local_28) + 0xc) != 0) {
            local_48 = local_18;
            do {
              iVar7 = *(int *)(*(int *)(param_1 + 0x14) +
                              *(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0x140) + (int)piVar11) +
                                               0x10) + (int)local_c * 4) * 4);
              *(int **)(iVar7 + 8) = local_18;
              local_8 = (int *)FUN_007a0837(*(int *)(param_1 + 0x140),
                                            (undefined1 *)((int)local_18 + 1),
                                            *(undefined4 *)(param_1 + 0x134),
                                            *(undefined4 *)
                                             (*(int *)(*(int *)((int)piVar11 +
                                                               *(int *)(param_1 + 0x140)) + 0x10) +
                                             (int)local_c * 4),iVar7,&local_3c);
              piVar15 = (int *)FUN_007a0837(*(undefined4 *)(param_1 + 0x144),0,
                                            *(undefined4 *)(param_1 + 0x138),
                                            *(undefined4 *)
                                             (*(int *)(*(int *)(*(int *)(param_1 + 0x140) +
                                                               (int)piVar11) + 0x10) +
                                             (int)local_c * 4),iVar7,&local_3c);
              if (local_10 < piVar15) {
                local_10 = piVar15;
              }
              piVar5 = local_8;
              if (local_3c != (int *)0x0) {
                piVar5 = (int *)0xffffffff;
              }
              if (local_2c < piVar5) {
                local_2c = piVar5;
              }
              puVar6 = (undefined1 *)(*(int *)(iVar7 + 0xc) + (int)piVar11);
              local_c = (uint *)((int)local_c + 1);
              local_114[(int)puVar6] = piVar15;
              iVar7 = *(int *)(*(int *)(param_1 + 0x140) + (int)piVar11);
              auStack_1f4[(int)puVar6] = piVar5;
            } while (local_c < *(uint **)(iVar7 + 0xc));
          }
          piVar15 = local_48;
          local_84[(int)local_48] = (uint)local_2c;
          local_6c[(int)piVar15] = (uint)local_10;
        }
        else {
          local_38 = (uint *)0x0;
          local_34 = (int *)0x0;
          if (puVar13[3] != 0) {
            local_24 = *(uint **)(*(int *)(*(int *)(param_1 + 0x140) + (int)local_28) + 0xc);
            piVar15 = (int *)puVar13[4];
            do {
              if (*(int *)(*(int *)(*(int *)(param_1 + 0x14) + *piVar15 * 4) + 8) == -1) {
                local_38 = (uint *)0x1;
              }
              else {
                local_34 = (int *)0x1;
              }
              piVar15 = piVar15 + 1;
              local_24 = (uint *)((int)local_24 + -1);
            } while (local_24 != (uint *)0x0);
            if (local_34 != (int *)0x0) {
              if (local_38 == (uint *)0x0) goto LAB_007a200a;
              uVar19 = 0x880ed8000012c8;
              uVar4 = 0;
              goto LAB_007a2960;
            }
          }
          local_14 = (uint *)0x0;
          FUN_007a08b2(*(undefined4 *)(param_1 + 0x140),(undefined1 *)((int)local_18 + 1),
                       *(undefined4 *)(param_1 + 0x134),puVar13[4],puVar13[3],local_194,&local_14);
          iVar7 = *(int *)((int)piVar11 + *(int *)(param_1 + 0x140));
          FUN_007a08b2(*(undefined4 *)(param_1 + 0x144),0,*(undefined4 *)(param_1 + 0x138),
                       *(undefined4 *)(iVar7 + 0x10),*(undefined4 *)(iVar7 + 0xc),local_194,
                       &local_14);
          local_28 = (int *)0x0;
          do {
            piVar15 = local_28;
            iVar7 = *(int *)((int)piVar11 + *(int *)(param_1 + 0x140));
            local_8 = (int *)FUN_007a10f3(local_28,*(undefined4 *)(param_1 + 0x144),
                                          *(undefined4 *)(param_1 + 0x138),
                                          *(undefined4 *)(iVar7 + 0x10),*(undefined4 *)(iVar7 + 0xc)
                                         );
            if ((int)local_8 < 0) {
              return local_8;
            }
            if (((int *)local_84[(int)piVar15] <= local_18) && (local_8 == (int *)0x0)) break;
            piVar15 = (int *)((int)piVar15 + 1);
            local_28 = piVar15;
          } while (piVar15 < &DAT_00000006);
          if (piVar15 == (int *)&DAT_00000006) {
            iVar7 = *(int *)(param_1 + 0x140);
            goto LAB_007a2942;
          }
          local_2c = (int *)0x0;
          local_c = (uint *)0x0;
          if (local_14 != (uint *)0x0) {
            local_48 = piVar15;
            do {
              iVar7 = local_194[(int)local_c];
              iVar8 = *(int *)(*(int *)(param_1 + 0x14) + iVar7 * 4);
              *(int **)(iVar8 + 8) = local_28;
              local_8 = (int *)FUN_007a0837(*(undefined4 *)(param_1 + 0x140),
                                            (undefined1 *)((int)local_18 + 1),
                                            *(undefined4 *)(param_1 + 0x134),iVar7,iVar8,&local_3c);
              piVar5 = (int *)FUN_007a0837(*(undefined4 *)(param_1 + 0x144),0,
                                           *(undefined4 *)(param_1 + 0x138),local_194[(int)local_c],
                                           iVar8,&local_3c);
              piVar15 = local_28;
              if (local_10 < piVar5) {
                local_10 = piVar5;
              }
              if ((*(int **)(param_1 + 0x88) <= piVar5) && (*(int *)(iVar8 + 0xc) == 3)) {
                local_9c[(int)local_28] = 1;
              }
              if (local_3c != (int *)0x0) {
                local_b4[(int)piVar15] = 1;
              }
              if ((local_10 != (int *)0x0) || (local_3c != (int *)0x0)) {
                local_8 = (int *)0xffffffff;
              }
              piVar1 = local_8;
              if (local_2c < local_8) {
                local_2c = local_8;
              }
              iVar7 = *(int *)(iVar8 + 0xc) + (int)piVar15 * 4;
              local_c = (uint *)((int)local_c + 1);
              local_114[iVar7] = piVar5;
              bVar18 = local_c < local_14;
              auStack_1f4[iVar7] = piVar1;
              piVar15 = local_28;
            } while (bVar18);
          }
          local_84[(int)piVar15] = (uint)local_2c;
          local_6c[(int)piVar15] = (uint)local_10;
          FUN_007a0a92();
        }
      }
LAB_007a200a:
      local_18 = (int *)((int)local_18 + 1);
      local_28 = piVar11 + 1;
    } while (local_18 < *(int **)(param_1 + 0x134));
  }
LAB_007a2024:
  if ((*(int *)(param_1 + 0x144) != 0) && (local_18 = (int *)0x0, *(int *)(param_1 + 0x138) != 0)) {
    do {
      piVar11 = local_18;
      iVar7 = (int)local_18 * 4;
      puVar13 = *(uint **)(iVar7 + *(int *)(param_1 + 0x144));
      if (puVar13 != (uint *)0x0) {
        puVar6 = (undefined1 *)(*puVar13 & 0xff000000);
        if ((puVar6 != (undefined1 *)0x0) && (puVar6 != (undefined1 *)0x34000000)) {
          if ((((puVar6 == (undefined1 *)0x40000000) ||
               (((((puVar6 == (undefined1 *)0x44000000 || (puVar6 == (undefined1 *)0x48000000)) ||
                  (puVar6 == (undefined1 *)0x4c000000)) ||
                 ((puVar6 == (undefined1 *)0xe3000000 || (puVar6 == (undefined1 *)0xe5000000)))) ||
                (puVar6 == (undefined1 *)0xe1000000)))) ||
              (((puVar6 == (undefined1 *)0xe6000000 || (puVar6 == (undefined1 *)0xe7000000)) ||
               (puVar6 == &DAT_e8000000)))) ||
             (((puVar6 == (undefined1 *)0xea000000 || (puVar6 == (undefined1 *)0xe9000000)) ||
              (puVar6 == (undefined1 *)0xeb000000)))) {
            local_8 = (int *)0x0;
            local_c = (uint *)0x0;
            if (puVar13[3] != 0) {
              do {
                iVar8 = *(int *)(*(int *)(param_1 + 0x14) +
                                *(int *)((int)local_c * 4 +
                                        *(int *)(*(int *)(*(int *)(param_1 + 0x144) + iVar7) + 0x10)
                                        ) * 4);
                local_48 = local_18;
                if ((*(uint *)(param_1 + 0x30) & 0xffff) != 0x104) {
                  local_48 = (int *)((int)local_18 + 2);
                }
                *(int **)(iVar8 + 8) = local_48;
                piVar11 = (int *)FUN_007a0837(*(int *)(param_1 + 0x144),
                                              (undefined1 *)((int)local_18 + 1),
                                              *(undefined4 *)(param_1 + 0x138),
                                              *(undefined4 *)
                                               (*(int *)(*(int *)(iVar7 + *(int *)(param_1 + 0x144))
                                                        + 0x10) + (int)local_c * 4),iVar8,&local_3c)
                ;
                if (local_8 < piVar11) {
                  local_8 = piVar11;
                }
                local_c = (uint *)((int)local_c + 1);
                local_114[*(int *)(iVar8 + 0xc) + (int)local_48 * 4] = piVar11;
              } while (local_c < *(uint **)(*(int *)(*(int *)(param_1 + 0x144) + iVar7) + 0xc));
            }
            local_6c[(int)local_48] = (uint)local_8;
          }
          else if ((puVar6 != (undefined1 *)0xe2000000) && (puVar6 != (undefined1 *)0xe4000000)) {
            if ((*(uint *)(param_1 + 0x30) & 0xffff) == 0x101) {
              uVar9 = *puVar13 & 0xffffff;
              local_44 = (uint *)(puVar13[1] / uVar9);
              local_40 = (uint *)0x0;
              local_38 = (uint *)0x0;
              if (local_44 != (uint *)0x0) {
                local_20 = (int *)puVar13[2];
                local_1c = (int *)(uVar9 * 4);
                do {
                  local_14 = (uint *)0x0;
                  piVar15 = *(int **)(*(int *)(param_1 + 0x14) + *local_20 * 4);
                  if (local_38 != (uint *)0x0) {
                    local_34 = (int *)puVar13[2];
                    do {
                      piVar5 = *(int **)(*(int *)(param_1 + 0x14) + *local_34 * 4);
                      if (((*piVar15 == *piVar5) && (piVar15[1] == piVar5[1])) &&
                         (piVar15[2] == piVar5[2])) break;
                      local_14 = (uint *)((int)local_14 + 1);
                      local_34 = local_34 + uVar9;
                    } while (local_14 < local_38);
                  }
                  if (((local_38 == local_14) && (*piVar15 == *(int *)(param_1 + 0x60))) &&
                     (1 < (uint)piVar15[2])) {
                    local_40 = (uint *)((int)local_40 + 1);
                  }
                  local_20 = local_20 + uVar9;
                  local_38 = (uint *)((int)local_38 + 1);
                } while (local_38 < local_44);
                if ((uint *)0x2 < local_40) {
                  iVar7 = *(int *)(param_1 + 0x144);
LAB_007a2942:
                  iVar7 = *(int *)(iVar7 + (int)local_18 * 4);
LAB_007a2953:
                  uVar19 = 0x880e80000011a9;
                  uVar4 = *(undefined4 *)(iVar7 + 0x34);
LAB_007a2960:
                  FUN_007899a1(param_1,uVar4,uVar19);
                  return (int *)0x80004005;
                }
              }
            }
            local_24 = (uint *)0x0;
            local_20 = (int *)0x0;
            if (puVar13[3] != 0) {
              local_1c = *(int **)(*(int *)(*(int *)(param_1 + 0x144) + (int)local_18 * 4) + 0xc);
              piVar15 = (int *)puVar13[4];
              do {
                if (*(int *)(*(int *)(*(int *)(param_1 + 0x14) + *piVar15 * 4) + 8) == -1) {
                  local_24 = (uint *)0x1;
                }
                else {
                  local_20 = (int *)0x1;
                }
                piVar15 = piVar15 + 1;
                local_1c = (int *)((int)local_1c + -1);
              } while (local_1c != (int *)0x0);
              if (local_20 != (int *)0x0) {
                if (local_24 != (uint *)0x0) {
                  FUN_007899a1(param_1,0,0x12c9,"internal error: unvectorized register found");
                  return (int *)0x80004005;
                }
                goto LAB_007a2808;
              }
            }
            local_14 = (uint *)0x0;
            FUN_007a08b2(*(undefined4 *)(param_1 + 0x144),(undefined1 *)((int)local_18 + 1),
                         *(undefined4 *)(param_1 + 0x138),puVar13[4],puVar13[3],local_194,&local_14)
            ;
            piVar15 = local_18;
            local_1c = (int *)0xffffffff;
            local_20 = (int *)0xffffffff;
            local_44 = (uint *)(*(uint *)(param_1 + 0x30) & 0xffff);
            if (((local_44 == (uint *)0x102) || (local_44 == (uint *)0x103)) &&
               (piVar5 = *(int **)(*(int *)(param_1 + 0x144) + (int)piVar11 * 4),
               *piVar5 == 0x30000004)) {
              piVar5 = (int *)piVar5[2];
              piVar1 = *(int **)(*(int *)(param_1 + 0x14) + *piVar5 * 4);
              if (*piVar1 == *(int *)(param_1 + 0x60)) {
                local_1c = (int *)piVar1[2];
              }
              piVar5 = *(int **)(*(int *)(param_1 + 0x14) + piVar5[4] * 4);
              if (*piVar5 == *(int *)(param_1 + 0x60)) {
                local_20 = (int *)piVar5[2];
              }
            }
            puVar13 = *(uint **)(*(int *)(param_1 + 0x144) + (int)piVar11 * 4);
            uVar9 = *puVar13;
            if ((((uVar9 & 0xffffff) == 1) && ((uVar9 & 0xff000000) != 0x30000000)) &&
               ((local_14 == (uint *)0x1 &&
                (*(int *)(*(int *)(*(int *)(param_1 + 0x14) + local_194[0] * 4) + 0xc) == 3)))) {
              local_28 = (int *)0x0;
              puVar12 = local_114 + 3;
              do {
                if ((piVar11 < (int *)local_6c[(int)local_28]) && ((int *)*puVar12 <= piVar11))
                break;
                local_28 = (int *)((int)local_28 + 1);
                puVar12 = puVar12 + 4;
              } while (local_28 < &DAT_00000006);
              if (local_28 == (int *)&DAT_00000006) goto LAB_007a233d;
            }
            else {
LAB_007a233d:
              local_28 = (int *)0x0;
              do {
                if ((((int *)local_6c[(int)local_28] <= piVar11) && (local_28 != local_1c)) &&
                   (local_28 != local_20)) break;
                local_28 = (int *)((int)local_28 + 1);
              } while (local_28 < &DAT_00000006);
              if (local_28 == (int *)&DAT_00000006) {
                iVar7 = *(int *)(*(int *)(param_1 + 0x144) + (int)piVar11 * 4);
                goto LAB_007a2953;
              }
            }
            local_20 = (int *)0x0;
            if ((((uVar9 & 0xff000000) == 0x30000000) && (local_44 < (uint *)0x104)) &&
               (puVar13[3] == 1)) {
              FUN_007a0acc(*(undefined4 *)(param_1 + 0x144),(undefined1 *)((int)local_18 + 1),
                           *(undefined4 *)(param_1 + 0x138),puVar13[4],1,&local_2c,&local_4c,
                           &local_44);
              if (local_4c != (uint *)0x0) {
                local_2c = (int *)&DAT_00000004;
              }
              bVar18 = local_2c < &DAT_00000004;
              if (bVar18) {
                local_2c = (int *)0x3;
              }
              if (!bVar18 && local_2c != (int *)&DAT_00000004) {
                local_2c = (int *)&DAT_00000004;
              }
              pvVar3 = operator_new(0x38);
              if (pvVar3 == (void *)0x0) {
                local_c = (uint *)0x0;
              }
              else {
                local_c = (uint *)FUN_007851ab();
              }
              if (local_c == (uint *)0x0) {
                return (int *)0x8007000e;
              }
              puVar12 = *(undefined4 **)((int)piVar15 * 4 + *(int *)(param_1 + 0x144));
              local_8 = (int *)FUN_00785202(*puVar12,puVar12[1],local_2c,0);
              if ((int)local_8 < 0) {
                return local_8;
              }
              local_8 = (int *)FUN_007854e4();
              puVar13 = local_c;
              if ((int)local_8 < 0) {
                return local_8;
              }
              puVar12 = *(undefined4 **)
                         (*(int *)(*(int *)(param_1 + 0x144) + (int)local_18 * 4) + 8);
              puVar17 = (undefined4 *)local_c[2];
              for (uVar9 = local_c[1] & 0x3fffffff; uVar9 != 0; uVar9 = uVar9 - 1) {
                *puVar17 = *puVar12;
                puVar12 = puVar12 + 1;
                puVar17 = puVar17 + 1;
              }
              for (iVar7 = 0; iVar7 != 0; iVar7 = iVar7 + -1) {
                *(undefined1 *)puVar17 = *(undefined1 *)puVar12;
                puVar12 = (undefined4 *)((int)puVar12 + 1);
                puVar17 = (undefined4 *)((int)puVar17 + 1);
              }
              iVar7 = *(int *)(*(int *)(param_1 + 0x144) + (int)local_18 * 4);
              piVar11 = *(int **)(iVar7 + 0xc);
              local_1c = piVar11;
              puVar16 = *(uint **)(iVar7 + 0x10);
              puVar10 = local_84 + 2;
              for (; piVar11 != (int *)0x0; piVar11 = (int *)((int)piVar11 + -1)) {
                *puVar10 = *puVar16;
                puVar16 = puVar16 + 1;
                puVar10 = puVar10 + 1;
              }
              if (iVar7 != 0) {
                FUN_00784bd1();
                puVar13 = local_c;
              }
              *(uint **)((int)local_18 * 4 + *(int *)(param_1 + 0x144)) = puVar13;
              piVar11 = (int *)0x0;
              local_8 = (int *)0x0;
              local_34 = (int *)0x0;
              if (local_1c != (int *)0x0) {
                do {
                  local_10 = (int *)0x0;
                  if (*(int *)(param_1 + 8) != 0) {
                    do {
                      iVar7 = *(int *)(*(int *)(param_1 + 0x14) + (int)local_10 * 4);
                      piVar15 = (int *)(local_84 + 2)[(int)local_34];
                      if ((local_10 == piVar15) || (*(int **)(iVar7 + 0x24) == piVar15)) {
                        piVar15 = (int *)0x0;
                        piVar11 = local_18;
                        if (local_2c != (int *)0x0) {
                          do {
                            uVar4 = FUN_00784f26(*(undefined4 *)(param_1 + 0x60),local_28,piVar15,0)
                            ;
                            *(undefined4 *)(local_c[4] + (int)piVar15 * 4) = uVar4;
                            iVar8 = *(int *)(local_c[4] + (int)piVar15 * 4);
                            if (iVar8 == -1) {
                              return (int *)0x8007000e;
                            }
                            iVar8 = *(int *)(*(int *)(param_1 + 0x14) + iVar8 * 4);
                            *(undefined4 *)(iVar8 + 0x2c) = *(undefined4 *)(iVar7 + 0x2c);
                            *(undefined4 *)(iVar8 + 0x38) = *(undefined4 *)(iVar7 + 0x38);
                            *(undefined4 *)(iVar8 + 0x3c) = *(undefined4 *)(iVar7 + 0x3c);
                            piVar15 = (int *)((int)piVar15 + 1);
                            *(undefined4 *)(iVar8 + 0x20) = *(undefined4 *)(iVar7 + 0x20);
                            piVar11 = local_18;
                          } while (piVar15 < local_2c);
                        }
                        while( true ) {
                          piVar11 = (int *)((int)piVar11 + 1);
                          local_3c = piVar11;
                          if (*(int **)(param_1 + 0x138) <= piVar11) break;
                          puVar13 = *(uint **)(*(int *)(param_1 + 0x144) + (int)piVar11 * 4);
                          uVar9 = *puVar13 & 0xffffff;
                          local_44 = (uint *)(puVar13[1] / uVar9);
                          local_38 = (uint *)0x0;
                          if (local_44 != (uint *)0x0) {
                            local_40 = (uint *)0x0;
                            do {
                              if (uVar9 < 3) {
                                if (uVar9 == 1) {
                                  puVar12 = (undefined4 *)(puVar13[2] + (int)local_38 * 4);
                                  if ((int *)*puVar12 == local_10) {
                                    if (local_2c == (int *)&DAT_00000004) {
                                      uVar4 = ((undefined4 *)local_c[4])[3];
                                    }
                                    else {
                                      uVar4 = *(undefined4 *)local_c[4];
                                    }
                                    *puVar12 = uVar4;
                                    if (local_8 < piVar11) {
                                      local_8 = piVar11;
                                    }
                                  }
                                }
                                else {
                                  uVar14 = 0;
                                  if (uVar9 != 0) {
                                    local_24 = local_40;
                                    do {
                                      if ((*(int **)(puVar13[2] + (int)local_24) == local_10) &&
                                         (*(undefined4 *)(puVar13[2] + (int)local_24) =
                                               *(undefined4 *)(local_c[4] + uVar14 * 4),
                                         local_8 < piVar11)) {
                                        local_8 = piVar11;
                                      }
                                      local_24 = local_24 + 1;
                                      uVar14 = uVar14 + 1;
                                    } while (uVar14 < uVar9);
                                  }
                                }
                              }
                              else {
                                uVar14 = 0;
                                if (uVar9 != 0) {
                                  local_24 = local_40;
                                  do {
                                    if ((*(int **)(puVar13[2] + (int)local_24) == local_10) &&
                                       (*(undefined4 *)(puVar13[2] + (int)local_24) =
                                             *(undefined4 *)(local_c[4] + uVar14 * 4),
                                       local_8 < piVar11)) {
                                      local_8 = piVar11;
                                    }
                                    local_24 = local_24 + 1;
                                    uVar14 = uVar14 + 1;
                                  } while (uVar14 < uVar9);
                                }
                              }
                              local_38 = (uint *)((int)local_38 + 1);
                              local_40 = local_40 + uVar9;
                            } while (local_38 < local_44);
                          }
                        }
                        local_20 = (int *)0x1;
                        piVar11 = local_8;
                      }
                      local_10 = (int *)((int)local_10 + 1);
                    } while (local_10 < *(int **)(param_1 + 8));
                  }
                  local_34 = (int *)((int)local_34 + 1);
                } while (local_34 < local_1c);
              }
              piVar15 = local_28;
              if ((int *)local_6c[(int)local_28] < piVar11) {
                local_6c[(int)local_28] = (uint)piVar11;
              }
              if ((int *)local_114[(int)piVar15 * 4] < piVar11) {
                local_114[(int)piVar15 * 4] = piVar11;
              }
              if ((int *)local_114[(int)piVar15 * 4 + 1] < piVar11) {
                local_114[(int)piVar15 * 4 + 1] = piVar11;
              }
              if ((int *)local_114[(int)piVar15 * 4 + 2] < piVar11) {
                local_114[(int)piVar15 * 4 + 2] = piVar11;
              }
              if ((int *)local_114[(int)piVar15 * 4 + 3] < piVar11) {
                local_114[(int)piVar15 * 4 + 3] = piVar11;
              }
              if (local_20 != (int *)0x0) goto LAB_007a2808;
            }
            piVar11 = local_28;
            local_8 = (int *)0x0;
            if (local_14 == (uint *)0x0) {
              **(undefined4 **)((int)local_18 * 4 + *(int *)(param_1 + 0x144)) = 0;
            }
            else {
              local_c = (uint *)0x0;
              if (local_14 != (uint *)0x0) {
                do {
                  iVar7 = local_194[(int)local_c];
                  iVar8 = *(int *)(*(int *)(param_1 + 0x14) + iVar7 * 4);
                  *(int **)(iVar8 + 8) = piVar11;
                  piVar15 = (int *)FUN_007a0837(*(undefined4 *)(param_1 + 0x144),
                                                (undefined1 *)((int)local_18 + 1),
                                                *(undefined4 *)(param_1 + 0x138),iVar7,iVar8,
                                                &local_3c);
                  if (local_8 < piVar15) {
                    local_8 = piVar15;
                  }
                  local_c = (uint *)((int)local_c + 1);
                  local_114[*(int *)(iVar8 + 0xc) + (int)piVar11 * 4] = piVar15;
                } while (local_c < local_14);
              }
              if ((int *)local_6c[(int)piVar11] < local_8) {
                local_6c[(int)piVar11] = (uint)local_8;
              }
              FUN_007a0a92();
            }
          }
        }
      }
LAB_007a2808:
      local_18 = (int *)((int)local_18 + 1);
    } while (local_18 < *(int **)(param_1 + 0x138));
  }
  iVar7 = 0;
  uVar9 = 0;
  do {
    if (local_9c[uVar9] != 0) {
      iVar7 = iVar7 + 1;
    }
    uVar9 = uVar9 + 1;
  } while (uVar9 < 6);
  if ((*(int *)(param_1 + 0x140) != 0) && (iVar7 != 0)) {
    local_8 = (int *)FUN_007a126a(local_6c,local_b4,iVar7);
    if ((int)local_8 < 0) {
      return local_8;
    }
    local_14 = (uint *)0x0;
    local_20 = *(int **)(param_1 + 0x138);
    local_24 = local_6c;
    do {
      iVar7 = 0;
      if (local_9c[(int)local_14] != 0) {
        if (0x1ff < *(uint *)(param_1 + 0x134)) {
          return (int *)0x8007000e;
        }
        if (0x1ff < *(uint *)(param_1 + 0x138)) {
          return (int *)0x8007000e;
        }
        local_1c = (int *)FUN_00784f26(*(undefined4 *)(param_1 + 0x60),local_14,3,0);
        if (local_1c == (int *)0xffffffff) {
          return (int *)0x8007000e;
        }
        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x14) + (int)local_1c * 4) + 0x20) = 0;
        pvVar3 = operator_new(0x38);
        if (pvVar3 != (void *)0x0) {
          iVar7 = FUN_007851ab();
        }
        if (iVar7 == 0) {
          return (int *)0x8007000e;
        }
        local_8 = (int *)FUN_00785202(0x10000001,1,1,0);
        if ((int)local_8 < 0) {
          return local_8;
        }
        uVar9 = *local_24;
        **(uint **)(iVar7 + 0x10) = uVar9;
        **(undefined4 **)(iVar7 + 8) = local_1c;
        *(int *)(*(int *)(param_1 + 0x140) + *(int *)(param_1 + 0x134) * 4) = iVar7;
        *(int *)(param_1 + 0x134) = *(int *)(param_1 + 0x134) + 1;
        pvVar3 = operator_new(0x38);
        if (pvVar3 == (void *)0x0) {
          iVar7 = 0;
        }
        else {
          iVar7 = FUN_007851ab();
        }
        if (iVar7 == 0) {
          return (int *)0x8007000e;
        }
        local_8 = (int *)FUN_00785202(0x10000001,1,1,0);
        if ((int)local_8 < 0) {
          return local_8;
        }
        **(undefined4 **)(iVar7 + 0x10) = local_1c;
        **(uint **)(iVar7 + 8) = uVar9;
        *(int *)(*(int *)(param_1 + 0x144) + *(int *)(param_1 + 0x138) * 4) = iVar7;
        *(int *)(param_1 + 0x138) = *(int *)(param_1 + 0x138) + 1;
        local_24 = local_24 + 1;
      }
      local_14 = (uint *)((int)local_14 + 1);
    } while (local_14 < &DAT_00000006);
    for (piVar11 = *(int **)(param_1 + 0x88); piVar11 < local_20;
        piVar11 = (int *)((int)piVar11 + 1)) {
      if (0x1ff < *(uint *)(param_1 + 0x138)) {
        return (int *)0x8007000e;
      }
      *(undefined4 *)(*(int *)(param_1 + 0x144) + *(uint *)(param_1 + 0x138) * 4) =
           *(undefined4 *)(*(int *)(param_1 + 0x144) + (int)piVar11 * 4);
      *(int *)(param_1 + 0x138) = *(int *)(param_1 + 0x138) + 1;
      *(undefined4 *)(*(int *)(param_1 + 0x144) + (int)piVar11 * 4) = 0;
    }
  }
  if (((*(int *)(param_1 + 0x140) == 0) || ((*(uint *)(param_1 + 0x30) & 0xffff) != 0x104)) ||
     (local_8 = (int *)FUN_007a1774(), -1 < (int)local_8)) {
    local_8 = (int *)0x0;
LAB_007a2a30:
    if (local_30 != 0) {
      FUN_00784bd1();
    }
  }
  return local_8;
LAB_007a1dbc:
  local_10 = (int *)((int)local_10 + 1);
  if (*(int **)(param_1 + 0x138) <= local_10) goto LAB_007a1f16;
  goto LAB_007a1c7b;
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



/* function 007a71cb FUN_007a71cb */

/* WARNING: Type propagation algorithm not settling */

int __fastcall FUN_007a71cb(int param_1)

{
  uint *puVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  void *pvVar6;
  int *piVar7;
  int *piVar8;
  undefined4 *puVar9;
  uint uVar10;
  int *piVar11;
  bool bVar12;
  undefined4 uVar13;
  int local_b4 [12];
  uint local_84 [9];
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  uint local_54 [9];
  uint local_30;
  int local_2c;
  int local_28;
  int *local_24;
  int *local_20;
  int *local_1c;
  int *local_18;
  int local_14;
  int *local_10;
  int *local_c;
  int *local_8;
  
  local_2c = 0;
  local_28 = 0;
  puVar1 = *(uint **)(param_1 + 0x98);
  piVar7 = (int *)(*puVar1 & 0xff000000);
  if (piVar7 == (int *)0x0) {
    return 0;
  }
  local_18 = (int *)(*puVar1 & 0xffffff);
  local_54[8] = puVar1[1];
  local_10 = (int *)(local_54[8] / (uint)local_18);
  local_30 = local_54[8] % (uint)local_18;
  if (((piVar7 == (int *)0x30000000) || (piVar7 == (int *)0x35000000)) ||
     (piVar7 == (int *)0xfa000000)) {
    bVar12 = true;
  }
  else {
    bVar12 = false;
  }
  local_20 = piVar7;
  if (((piVar7 == (int *)0x44000000) || (piVar7 == (int *)0x48000000)) ||
     ((piVar7 == (int *)0x4c000000 || (piVar7 == (int *)0x34000000)))) {
    iVar4 = FUN_0078506d(puVar1);
    if (iVar4 < 0) {
      return iVar4;
    }
    **(undefined4 **)(param_1 + 0x98) = 0;
    goto LAB_007a7bc9;
  }
  if (bVar12) {
    if ((piVar7 == (int *)0x35000000) || (piVar7 == (int *)0xfa000000)) {
      iVar4 = FUN_0078506d(puVar1);
      if (-1 < iVar4) {
        **(undefined4 **)(param_1 + 0x98) = 0;
        return iVar4;
      }
      return iVar4;
    }
    if (**(int **)(*(int *)(param_1 + 0x14) + *(int *)puVar1[4] * 4) == *(int *)(param_1 + 0x5c)) {
      uVar13 = 0x12d1;
LAB_007a7915:
      FUN_007899a1(param_1,puVar1[0xd],uVar13,
                   "internal error: write to output with instruction other than mov");
      return -0x7fffbffb;
    }
    local_8 = (int *)0x0;
    if (local_10 != (int *)0x0) {
      local_c = local_b4;
      local_14 = 0;
      do {
        piVar8 = local_c;
        piVar3 = local_18;
        bVar12 = local_18 != (int *)0x0;
        piVar7 = local_c + 1;
        *local_c = -1;
        *piVar7 = -1;
        piVar8[2] = -1;
        piVar8[3] = -1;
        if (bVar12) {
          piVar7 = (int *)(puVar1[2] + local_14);
          local_20 = piVar3;
          do {
            *piVar8 = *(int *)(*(int *)(*(int *)(param_1 + 0x14) + *piVar7 * 4) + 0xc);
            piVar7 = piVar7 + 1;
            piVar8 = piVar8 + 1;
            local_20 = (int *)((int)local_20 + -1);
          } while (local_20 != (int *)0x0);
        }
        local_1c = (int *)0x0;
        puVar9 = &DAT_008dd010;
        while (iVar4 = FUN_007a6ed9(local_c,puVar9), iVar4 == 0) {
          local_1c = local_1c + 4;
          puVar9 = puVar9 + 4;
          if ((int *)0x7f < local_1c) {
            iVar4 = FUN_007a6f5a(&local_28,local_18,local_10);
            if (iVar4 < 0) goto LAB_007a7bd9;
            if (local_28 != 0) {
              iVar4 = FUN_00784e17(local_28);
              if (iVar4 < 0) goto LAB_007a7bd9;
              local_28 = 0;
            }
            pvVar6 = operator_new(0x38);
            if (pvVar6 == (void *)0x0) {
              iVar5 = 0;
            }
            else {
              iVar5 = FUN_007851ab();
            }
            if (iVar5 == 0) goto LAB_007a7b92;
            iVar4 = FUN_00785202(0x25000001,2,1,0);
            if ((iVar4 < 0) || (iVar4 = FUN_007854e4(*(undefined4 *)(param_1 + 0x98)), iVar4 < 0))
            goto LAB_007a7bd9;
            **(undefined4 **)(iVar5 + 0x10) = **(undefined4 **)(*(int *)(param_1 + 0x98) + 0x10);
            **(undefined4 **)(iVar5 + 8) = **(undefined4 **)(*(int *)(param_1 + 0x98) + 8);
            local_54[8] = (int)local_18 * 4;
            *(undefined4 *)(*(int *)(iVar5 + 8) + 4) =
                 *(undefined4 *)(local_54[8] + *(int *)(*(int *)(param_1 + 0x98) + 8));
            iVar4 = FUN_00784e17(iVar5);
            if (iVar4 < 0) goto LAB_007a7bd9;
            local_8 = (int *)0x1;
            if (local_18 < (int *)0x2) goto LAB_007a7a1c;
            local_c = (int *)(local_54[8] + 4);
            goto LAB_007a7ace;
          }
        }
        local_8 = (int *)((int)local_8 + 1);
        local_c = local_c + 4;
        local_14 = local_14 + (int)local_18 * 4;
      } while (local_8 < local_10);
    }
    iVar4 = FUN_0078506d(puVar1);
    if (iVar4 < 0) {
      return iVar4;
    }
LAB_007a7a1c:
    **(undefined4 **)(param_1 + 0x98) = 0;
LAB_007a7a25:
    iVar4 = 0;
  }
  else {
    local_8 = (int *)0x0;
    if (local_10 != (int *)0x0) {
      local_14 = 0;
      local_1c = local_b4;
      local_30 = (int)local_18 << 2;
      do {
        piVar2 = local_18;
        piVar8 = local_1c;
        bVar12 = local_18 != (int *)0x0;
        piVar3 = local_1c + 1;
        *local_1c = -1;
        *piVar3 = -1;
        piVar8[2] = -1;
        piVar8[3] = -1;
        if (bVar12) {
          local_c = (int *)puVar1[4];
          piVar3 = (int *)(puVar1[2] + local_14);
          local_24 = piVar2;
          do {
            iVar4 = *piVar3;
            iVar5 = *local_c;
            local_c = local_c + 1;
            piVar3 = piVar3 + 1;
            local_24 = (int *)((int)local_24 + -1);
            bVar12 = local_24 != (int *)0x0;
            local_b4[*(int *)(*(int *)(*(int *)(param_1 + 0x14) + iVar5 * 4) + 0xc) +
                     (int)local_8 * 4] =
                 *(int *)(*(int *)(*(int *)(param_1 + 0x14) + iVar4 * 4) + 0xc);
            piVar7 = local_20;
          } while (bVar12);
        }
        local_8 = (int *)((int)local_8 + 1);
        local_14 = local_14 + local_30;
        local_1c = local_1c + 4;
      } while (local_8 < local_10);
    }
    piVar3 = *(int **)(*(int *)(param_1 + 0x14) + *(int *)puVar1[4] * 4);
    if (*piVar3 != *(int *)(param_1 + 0x5c)) {
      local_8 = (int *)0x0;
      if (local_10 != (int *)0x0) {
        local_c = local_b4;
        do {
          puVar9 = &DAT_008dd010;
          uVar10 = 0;
          while (iVar4 = FUN_007a6ed9(local_c,puVar9), iVar4 == 0) {
            uVar10 = uVar10 + 0x10;
            puVar9 = puVar9 + 4;
            if (0x7f < uVar10) {
              local_c = (int *)0x1;
              goto LAB_007a7492;
            }
          }
          local_8 = (int *)((int)local_8 + 1);
          local_c = local_c + 4;
        } while (local_8 < local_10);
      }
LAB_007a7600:
      iVar4 = FUN_0078506d(*(undefined4 *)(param_1 + 0x98));
      if (iVar4 < 0) goto LAB_007a7bc9;
      goto LAB_007a7a1c;
    }
    if (piVar7 != (int *)0x10000000) {
      uVar13 = 0x12cf;
      goto LAB_007a7915;
    }
    local_20 = *(int **)(*(int *)(param_1 + 0x14) + *(int *)puVar1[2] * 4);
    local_30 = piVar3[0x14] & 0xff;
    if (local_30 == 1) {
      if (local_54[8] != 4) {
        FUN_007899a1(param_1,0,0x12d0,
                     "internal error: compiler emittimg multiple movs to output registers");
        return -0x7fffbffb;
      }
      piVar7 = (int *)FUN_007a6ed9(local_b4,&DAT_008dd050);
    }
    else {
      if (local_30 != 2) {
        return -0x7fffbffb;
      }
      uVar10 = 0;
      local_24 = (int *)0x0;
      puVar9 = &DAT_008dd010;
      do {
        iVar4 = FUN_007a6ed9(local_b4,puVar9);
        if (iVar4 != 0) {
          local_24 = (int *)0x1;
          piVar7 = local_24;
          break;
        }
        uVar10 = uVar10 + 0x10;
        puVar9 = puVar9 + 4;
        piVar7 = local_24;
      } while (uVar10 < 0x40);
    }
    local_c = (int *)(uint)(piVar7 == (int *)0x0);
    if (((local_c == (int *)0x0) && ((*(byte *)((int)local_20 + 0x22) & 0xf) == 0)) ||
       (iVar4 = FUN_007a70d4(&local_2c,local_18), -1 < iVar4)) {
      local_84[0] = 0;
      local_84[1] = 0;
      local_84[2] = 0;
      local_84[3] = 0;
      iVar4 = FUN_007a6f06(local_b4,local_84);
      if ((iVar4 != 0) || ((local_30 == 2 && (local_b4[0] == 0)))) {
        iVar4 = FUN_007af2f0(local_84,local_10,local_18);
        if (-1 < iVar4) {
          **(undefined4 **)(param_1 + 0x98) = 0;
          if (local_2c == 0) {
            return iVar4;
          }
          iVar4 = FUN_00784e17(local_2c);
          if (-1 < iVar4) {
            return iVar4;
          }
        }
        goto LAB_007a7bc9;
      }
LAB_007a7492:
      if (local_c == (int *)0x0) goto LAB_007a7600;
      iVar4 = FUN_007a6f5a(&local_28,local_18,local_10);
      if (iVar4 < 0) goto LAB_007a7bc9;
      if (local_28 != 0) {
        iVar4 = FUN_00784e17(local_28);
        if (iVar4 < 0) goto LAB_007a7bc9;
        local_28 = 0;
      }
      local_1c = (int *)0x0;
      local_20 = (int *)0x0;
      if (local_18 == (int *)&DAT_00000004) {
        local_14 = 1;
        uVar10 = 0;
        do {
          if (local_14 == 0) break;
          local_14 = 0;
          local_84[0] = 0;
          local_84[1] = 0;
          local_84[2] = 0;
          local_84[3] = 0;
          local_84[4] = 0xffffffff;
          local_84[5] = 0xffffffff;
          local_84[6] = 0xffffffff;
          local_84[7] = 0xffffffff;
          local_84[uVar10] = 0xffffffff;
          local_84[uVar10 + 4] = 0;
          if (local_10 == (int *)0x0) {
LAB_007a761c:
            iVar4 = FUN_007af2f0(local_84,local_10,4);
            if ((iVar4 < 0) || (iVar4 = FUN_007af2f0(local_84 + 4,local_10,4), iVar4 < 0))
            goto LAB_007a7bc9;
            goto LAB_007a78be;
          }
          piVar7 = local_b4;
          local_24 = local_10;
          do {
            iVar4 = FUN_007a6f06(piVar7,local_84);
            if ((iVar4 == 0) || (iVar4 = FUN_007a6f06(piVar7,local_84), iVar4 == 0)) {
              local_14 = 1;
            }
            piVar7 = piVar7 + 4;
            local_24 = (int *)((int)local_24 + -1);
          } while (local_24 != (int *)0x0);
          local_24 = (int *)0x0;
          if (local_14 == 0) goto LAB_007a761c;
          uVar10 = uVar10 + 1;
        } while (uVar10 < 4);
        local_14 = 1;
        local_8 = (int *)0x0;
        do {
          if (local_14 == 0) break;
          local_c = (int *)0x0;
          do {
            piVar3 = local_8;
            piVar7 = local_c;
            if (local_c != local_8) {
              local_84[0] = 0;
              local_84[1] = 0;
              local_84[2] = 0;
              local_84[3] = 0;
              local_84[4] = 0xffffffff;
              local_84[5] = 0xffffffff;
              local_84[6] = 0xffffffff;
              local_84[7] = 0xffffffff;
              local_84[(int)local_8] = 0xffffffff;
              local_84[(int)piVar7] = 0xffffffff;
              local_84[(int)(piVar3 + 1)] = 0;
              local_84[(int)(piVar7 + 1)] = 0;
              local_14 = 0;
              local_30 = 0;
              if (local_10 != (int *)0x0) {
                piVar7 = local_b4;
                local_24 = local_10;
                do {
                  iVar4 = FUN_007a6f06(piVar7,local_84);
                  iVar5 = FUN_007a6f06(piVar7,local_84 + 4);
                  if (iVar4 == 0) {
                    local_30 = 1;
LAB_007a7659:
                    local_14 = 1;
                  }
                  else if (iVar5 == 0) goto LAB_007a7659;
                  piVar7 = piVar7 + 4;
                  local_24 = (int *)((int)local_24 + -1);
                } while (local_24 != (int *)0x0);
                if (local_14 != 0) {
                  if (local_30 == 0) {
                    local_84[8] = local_84[0];
                    uStack_60 = local_84[1];
                    uStack_5c = local_84[2];
                    uStack_58 = local_84[3];
                    local_54[0] = 0xffffffff;
                    local_54[1] = 0xffffffff;
                    local_54[2] = 0xffffffff;
                    local_54[3] = 0xffffffff;
                    local_54[4] = 0xffffffff;
                    local_54[5] = 0xffffffff;
                    local_54[6] = 0xffffffff;
                    local_54[7] = 0xffffffff;
                    local_54[(int)local_8] = 0;
                    local_54[(int)(local_c + 1)] = 0;
                    local_20 = (int *)0x1;
                  }
                  goto LAB_007a76ad;
                }
              }
              local_1c = (int *)0x1;
              break;
            }
LAB_007a76ad:
            local_c = (int *)((int)local_c + 1);
          } while (local_c < &DAT_00000004);
          local_8 = (int *)((int)local_8 + 1);
        } while (local_8 < &DAT_00000004);
        if (local_1c == (int *)0x0) {
          if (local_20 == (int *)0x0) goto LAB_007a7869;
          local_1c = (int *)0x1;
          iVar4 = FUN_007af2f0(local_84 + 8,local_10,4);
          if ((-1 < iVar4) && (iVar4 = FUN_007af2f0(local_54,local_10,4), -1 < iVar4)) {
            uVar13 = 4;
            puVar1 = local_54;
            goto LAB_007a784f;
          }
        }
        else {
          iVar4 = FUN_007af2f0(local_84,local_10,4);
          if (-1 < iVar4) {
            uVar13 = 4;
LAB_007a784c:
            puVar1 = local_84;
LAB_007a784f:
            iVar4 = FUN_007af2f0(puVar1 + 4,local_10,uVar13);
            if (-1 < iVar4) {
              if (local_1c == (int *)0x0) goto LAB_007a7869;
              goto LAB_007a78be;
            }
          }
        }
        goto LAB_007a7bc9;
      }
      if (local_18 == (int *)0x3) {
        local_20 = (int *)0xffffffff;
        piVar7 = (int *)0x0;
        do {
          if (local_b4[(int)piVar7] == -1) {
            local_20 = piVar7;
          }
          piVar7 = (int *)((int)piVar7 + 1);
        } while (piVar7 < &DAT_00000004);
        local_8 = (int *)0x0;
        do {
          if (local_1c != (int *)0x0) goto LAB_007a7830;
          piVar7 = (int *)0x0;
          do {
            piVar8 = local_8;
            piVar3 = local_20;
            if (local_1c != (int *)0x0) break;
            if (((piVar7 != local_8) && (piVar7 != local_20)) && (local_8 != local_20)) {
              local_84[0] = 0xffffffff;
              local_84[1] = 0xffffffff;
              local_84[2] = 0xffffffff;
              local_84[3] = 0xffffffff;
              local_84[4] = 0;
              local_84[5] = 0;
              local_84[6] = 0;
              local_84[7] = 0;
              uVar10 = (int)local_8 * 4;
              local_84[(int)local_8] = 0;
              piVar2 = local_10;
              piVar11 = (int *)0x0;
              local_84[(int)piVar7] = 0;
              local_54[8] = uVar10;
              local_84[(int)(piVar8 + 1)] = 0xffffffff;
              local_84[(int)(piVar7 + 1)] = 0xffffffff;
              local_84[(int)(piVar3 + 1)] = 0xffffffff;
              local_14 = 0;
              if (piVar2 != (int *)0x0) {
                local_c = local_b4;
                do {
                  if (local_14 != 0) goto LAB_007a7812;
                  iVar4 = FUN_007a6f06(local_c,local_84);
                  if (iVar4 == 0) {
                    local_14 = 1;
                  }
                  local_c = local_c + 4;
                  piVar11 = (int *)((int)piVar11 + 1);
                } while (piVar11 < local_10);
                if (local_14 != 0) goto LAB_007a7812;
              }
              local_1c = (int *)0x1;
            }
LAB_007a7812:
            piVar7 = (int *)((int)piVar7 + 1);
          } while (piVar7 < &DAT_00000004);
          local_8 = (int *)((int)local_8 + 1);
        } while (local_8 < &DAT_00000004);
        if (local_1c != (int *)0x0) {
LAB_007a7830:
          iVar4 = FUN_007af2f0(local_84,local_10,3);
          if (-1 < iVar4) {
            uVar13 = 3;
            goto LAB_007a784c;
          }
          goto LAB_007a7bc9;
        }
      }
LAB_007a7869:
      local_8 = (int *)0x0;
      if (local_18 != (int *)0x0) {
        do {
          piVar3 = local_10;
          piVar7 = local_18;
          local_84[0] = 0xffffffff;
          local_84[1] = 0xffffffff;
          local_84[2] = 0xffffffff;
          local_84[3] = 0xffffffff;
          local_84[*(int *)(*(int *)(*(int *)(param_1 + 0x14) +
                                    *(int *)(*(int *)(*(int *)(param_1 + 0x98) + 0x10) +
                                            (int)local_8 * 4) * 4) + 0xc)] = 0;
          iVar4 = FUN_007af2f0(local_84,piVar3,piVar7);
          if (iVar4 < 0) goto LAB_007a7bc9;
          local_8 = (int *)((int)local_8 + 1);
        } while (local_8 < local_18);
      }
LAB_007a78be:
      if (local_2c != 0) {
        iVar4 = FUN_00784e17(local_2c);
        if (iVar4 < 0) goto LAB_007a7bc9;
        local_2c = 0;
      }
      **(undefined4 **)(param_1 + 0x98) = 0;
      goto LAB_007a7a25;
    }
  }
LAB_007a7bc9:
  if (local_2c != 0) {
    FUN_00784bd1(1);
  }
LAB_007a7bd9:
  if (local_28 != 0) {
    FUN_00784bd1(1);
  }
  return iVar4;
  while( true ) {
    iVar4 = FUN_00785202(0xf5000001,3,1,0);
    if ((iVar4 < 0) || (iVar4 = FUN_007854e4(*(undefined4 *)(param_1 + 0x98)), iVar4 < 0))
    goto LAB_007a7bd9;
    **(undefined4 **)(iVar5 + 0x10) = **(undefined4 **)(*(int *)(param_1 + 0x98) + 0x10);
    **(undefined4 **)(iVar5 + 8) =
         *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x98) + 8) + (int)local_8 * 4);
    *(undefined4 *)(*(int *)(iVar5 + 8) + 4) =
         *(undefined4 *)((int)local_c + *(int *)(*(int *)(param_1 + 0x98) + 8));
    *(undefined4 *)(*(int *)(iVar5 + 8) + 8) = **(undefined4 **)(*(int *)(param_1 + 0x98) + 0x10);
    iVar4 = FUN_00784e17(iVar5);
    if (iVar4 < 0) goto LAB_007a7bd9;
    local_8 = (int *)((int)local_8 + 1);
    local_c = local_c + 1;
    if (local_18 <= local_8) break;
LAB_007a7ace:
    pvVar6 = operator_new(0x38);
    if (pvVar6 == (void *)0x0) {
      iVar5 = 0;
    }
    else {
      iVar5 = FUN_007851ab();
    }
    if (iVar5 == 0) goto LAB_007a7b92;
  }
  goto LAB_007a7a1c;
LAB_007a7b92:
  iVar4 = -0x7ff8fff2;
  goto LAB_007a7bd9;
}



/* function 0078ed33 FUN_0078ed33 */

void __fastcall FUN_0078ed33(int param_1)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  void *pvVar4;
  int iVar5;
  int *piVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int *piVar10;
  undefined4 *puVar11;
  uint *puVar12;
  int *piVar13;
  undefined4 *puVar14;
  int *piVar15;
  uint *puVar16;
  int local_ac [4];
  int local_9c;
  int local_98 [4];
  int local_88 [4];
  int local_78;
  undefined4 *local_74;
  int local_70 [4];
  undefined4 local_60;
  uint *local_5c;
  uint local_58;
  int local_54 [4];
  int *local_44;
  uint *local_40;
  uint local_3c;
  int *local_38;
  int *local_34;
  int *local_30;
  int *local_2c;
  uint local_28;
  uint *local_24;
  int *local_20;
  uint local_1c;
  int *local_18;
  int *local_14;
  int *local_10;
  uint *local_c;
  int *local_8;
  
  uVar3 = 0;
  if ((*(byte *)(param_1 + 0x34) & 8) != 0) {
    return;
  }
  local_60 = 0;
  if (*(int *)(param_1 + 4) != 0) {
    do {
      iVar9 = uVar3 * 4;
      uVar3 = uVar3 + 1;
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x10) + iVar9) + 0x10) = 0;
    } while (uVar3 < *(uint *)(param_1 + 4));
  }
  uVar3 = 0;
  if (*(int *)(param_1 + 8) != 0) {
    do {
      piVar6 = *(int **)(*(int *)(param_1 + 0x14) + uVar3 * 4);
      iVar9 = *piVar6;
      if (*(int *)(param_1 + 0x4c) != iVar9) {
        iVar9 = *(int *)(*(int *)(param_1 + 0x10) + iVar9 * 4);
        if ((((*(uint *)(iVar9 + 4) & 2) != 0) && ((*(uint *)(iVar9 + 4) & 0x200) == 0)) &&
           (uVar7 = piVar6[2] + 1, *(uint *)(iVar9 + 0x10) < uVar7)) {
          *(uint *)(iVar9 + 0x10) = uVar7;
        }
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(uint *)(param_1 + 8));
  }
  uVar3 = 0;
  if (*(int *)(param_1 + 4) != 0) {
    piVar6 = *(int **)(param_1 + 0x10);
    iVar9 = *(int *)(param_1 + 4);
    do {
      uVar3 = uVar3 + *(int *)(*piVar6 + 0x10);
      piVar6 = piVar6 + 1;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
  }
  local_74 = operator_new(uVar3 << 2);
  if (local_74 != (undefined4 *)0x0) {
    puVar11 = local_74;
    for (uVar3 = uVar3 & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar11 = 0;
      puVar11 = puVar11 + 1;
    }
    for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
      *(undefined1 *)puVar11 = 0;
      puVar11 = (undefined4 *)((int)puVar11 + 1);
    }
    uVar3 = 0;
    iVar9 = 0;
    if (*(int *)(param_1 + 4) != 0) {
      iVar5 = *(int *)(param_1 + 0x10);
      do {
        iVar5 = *(int *)(iVar5 + uVar3 * 4);
        *(uint *)(iVar5 + 0x1c) = -(uint)(*(int *)(iVar5 + 0x10) != 0) & (uint)(local_74 + iVar9);
        iVar5 = *(int *)(param_1 + 0x10);
        iVar9 = iVar9 + *(int *)(*(int *)(iVar5 + uVar3 * 4) + 0x10);
        uVar3 = uVar3 + 1;
      } while (uVar3 < *(uint *)(param_1 + 4));
    }
    uVar3 = 0;
    if (*(int *)(param_1 + 8) != 0) {
      do {
        piVar6 = *(int **)(*(int *)(param_1 + 0x14) + uVar3 * 4);
        if ((*(int *)(param_1 + 0x4c) != *piVar6) &&
           (iVar9 = *(int *)(*(int *)(*(int *)(param_1 + 0x10) + *piVar6 * 4) + 0x1c), iVar9 != 0))
        {
          puVar12 = (uint *)(iVar9 + piVar6[2] * 4);
          if (*puVar12 < piVar6[3] + 1U) {
            *puVar12 = piVar6[3] + 1U;
          }
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 < *(uint *)(param_1 + 8));
    }
    if ((*(uint *)(param_1 + 0x90) & 6) == 0) {
      FUN_0078937f();
      local_18 = (int *)0x0;
      if (*(int *)(param_1 + 0xc) != 0) {
        do {
          iVar9 = *(int *)(param_1 + 0x18);
          local_14 = *(int **)(iVar9 + (int)local_18 * 4);
          if (*local_14 == 0x24000001) {
            piVar6 = *(int **)(*(int *)(param_1 + 0x14) + *(int *)local_14[2] * 4);
            piVar15 = *(int **)(*(int *)(param_1 + 0x14) + ((int *)local_14[2])[1] * 4);
            if (((*(byte *)(*(int *)(*(int *)(param_1 + 0x10) + *piVar6 * 4) + 4) & 2) != 0) &&
               ((*(byte *)(*(int *)(*(int *)(param_1 + 0x10) + *piVar15 * 4) + 4) & 2) != 0)) {
              piVar6 = *(int **)(iVar9 + piVar6[0xb] * 4);
              piVar15 = *(int **)(iVar9 + piVar15[0xb] * 4);
              local_30 = piVar15;
              local_2c = piVar6;
              if (((*piVar6 == 0x25000001) || (iVar9 = FUN_00785569(), iVar9 != 0)) &&
                 ((*piVar15 == 0x25000001 || (iVar9 = FUN_00785569(), iVar9 != 0)))) {
                local_40 = (uint *)((uint)piVar15[1] >> 1);
                uVar3 = (uint)piVar6[1] >> 1;
                local_10 = (int *)((int)local_40 + uVar3);
                if (((int *)((~*(uint *)(param_1 + 0x90) & 0x20 | 0x40) >> 5) <= local_10) &&
                   (local_10 < (int *)0x5)) {
                  iVar9 = *(int *)(*(int *)(param_1 + 0x14) + *(int *)piVar6[4] * 4);
                  if ((((local_18 == *(int **)(iVar9 + 0x38)) &&
                       (local_18 == *(int **)(iVar9 + 0x3c))) &&
                      (iVar9 = *(int *)(*(int *)(param_1 + 0x14) + *(int *)piVar15[4] * 4),
                      local_18 == *(int **)(iVar9 + 0x38))) && (local_18 == *(int **)(iVar9 + 0x3c))
                     ) {
                    local_20 = (int *)local_2c[2];
                    piVar6 = local_20;
                    piVar15 = local_70;
                    for (uVar7 = uVar3 & 0x3fffffff; piVar10 = local_30, uVar7 != 0;
                        uVar7 = uVar7 - 1) {
                      *piVar15 = *piVar6;
                      piVar6 = piVar6 + 1;
                      piVar15 = piVar15 + 1;
                    }
                    for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
                      *(char *)piVar15 = (char)*piVar6;
                      piVar6 = (int *)((int)piVar6 + 1);
                      piVar15 = (int *)((int)piVar15 + 1);
                    }
                    local_44 = (int *)piVar10[2];
                    local_3c = (int)local_40 << 2;
                    piVar6 = local_44;
                    piVar15 = local_70 + uVar3;
                    for (uVar7 = (uint)local_40 & 0x3fffffff; piVar10 = local_20, uVar7 != 0;
                        uVar7 = uVar7 - 1) {
                      *piVar15 = *piVar6;
                      piVar6 = piVar6 + 1;
                      piVar15 = piVar15 + 1;
                    }
                    for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
                      *(char *)piVar15 = (char)*piVar6;
                      piVar6 = (int *)((int)piVar6 + 1);
                      piVar15 = (int *)((int)piVar15 + 1);
                    }
                    piVar6 = piVar10 + uVar3;
                    piVar15 = local_88;
                    for (uVar7 = uVar3 & 0x3fffffff; piVar10 = local_44, uVar7 != 0;
                        uVar7 = uVar7 - 1) {
                      *piVar15 = *piVar6;
                      piVar6 = piVar6 + 1;
                      piVar15 = piVar15 + 1;
                    }
                    for (iVar9 = 0; uVar7 = local_3c, iVar9 != 0; iVar9 = iVar9 + -1) {
                      *(char *)piVar15 = (char)*piVar6;
                      piVar6 = (int *)((int)piVar6 + 1);
                      piVar15 = (int *)((int)piVar15 + 1);
                    }
                    piVar6 = (int *)((int)piVar10 + local_3c);
                    piVar15 = local_88 + uVar3;
                    local_34 = (int *)(uVar3 * 4);
                    for (uVar8 = local_3c >> 2; piVar13 = local_10, piVar10 = local_14, uVar8 != 0;
                        uVar8 = uVar8 - 1) {
                      *piVar15 = *piVar6;
                      piVar6 = piVar6 + 1;
                      piVar15 = piVar15 + 1;
                    }
                    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
                      *(char *)piVar15 = (char)*piVar6;
                      piVar6 = (int *)((int)piVar6 + 1);
                      piVar15 = (int *)((int)piVar15 + 1);
                    }
                    iVar9 = FUN_00788a64(local_70,piVar13,0,0,piVar10,0xffffffff);
                    if ((iVar9 == 0) ||
                       (iVar9 = FUN_00788a64(local_88,local_10,0,0,local_14,0xffffffff), iVar9 == 0)
                       ) {
                      piVar15 = local_34;
                      piVar6 = (int *)local_2c[2];
                      piVar10 = piVar6;
                      piVar13 = local_54;
                      for (uVar3 = (uint)local_34 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
                        *piVar13 = *piVar10;
                        piVar10 = piVar10 + 1;
                        piVar13 = piVar13 + 1;
                      }
                      for (uVar3 = (uint)piVar15 & 3; uVar7 = local_3c, uVar3 != 0;
                          uVar3 = uVar3 - 1) {
                        *(char *)piVar13 = (char)*piVar10;
                        piVar10 = (int *)((int)piVar10 + 1);
                        piVar13 = (int *)((int)piVar13 + 1);
                      }
                      local_44 = (int *)local_30[2];
                      puVar11 = (undefined4 *)((int)local_44 + local_3c);
                      puVar14 = (undefined4 *)((int)local_54 + (int)local_34);
                      for (uVar3 = local_3c >> 2; piVar15 = local_34, uVar3 != 0; uVar3 = uVar3 - 1)
                      {
                        *puVar14 = *puVar11;
                        puVar11 = puVar11 + 1;
                        puVar14 = puVar14 + 1;
                      }
                      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
                        *(undefined1 *)puVar14 = *(undefined1 *)puVar11;
                        puVar11 = (undefined4 *)((int)puVar11 + 1);
                        puVar14 = (undefined4 *)((int)puVar14 + 1);
                      }
                      piVar6 = (int *)((int)piVar6 + (int)piVar15);
                      piVar10 = local_98;
                      for (uVar3 = (uint)piVar15 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
                        *piVar10 = *piVar6;
                        piVar6 = piVar6 + 1;
                        piVar10 = piVar10 + 1;
                      }
                      for (uVar3 = (uint)piVar15 & 3; uVar7 = local_3c, uVar3 != 0;
                          uVar3 = uVar3 - 1) {
                        *(char *)piVar10 = (char)*piVar6;
                        piVar6 = (int *)((int)piVar6 + 1);
                        piVar10 = (int *)((int)piVar10 + 1);
                      }
                      piVar6 = local_44;
                      piVar15 = (int *)((int)local_98 + (int)piVar15);
                      for (uVar3 = local_3c >> 2; piVar13 = local_10, piVar10 = local_14, uVar3 != 0
                          ; uVar3 = uVar3 - 1) {
                        *piVar15 = *piVar6;
                        piVar6 = piVar6 + 1;
                        piVar15 = piVar15 + 1;
                      }
                      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
                        *(char *)piVar15 = (char)*piVar6;
                        piVar6 = (int *)((int)piVar6 + 1);
                        piVar15 = (int *)((int)piVar15 + 1);
                      }
                      iVar9 = FUN_00788a64(local_54,piVar13,0,0,piVar10,0xffffffff);
                      if ((iVar9 == 0) ||
                         (iVar9 = FUN_00788a64(local_98,local_10,0,0,local_14,0xffffffff),
                         iVar9 == 0)) goto LAB_0078f1b0;
                      local_34 = (int *)0x1;
                    }
                    else {
                      local_34 = (int *)0x0;
                    }
                    pvVar4 = operator_new(0x38);
                    if (pvVar4 == (void *)0x0) {
                      local_38 = (int *)0x0;
                    }
                    else {
                      local_38 = (int *)FUN_007851ab();
                    }
                    piVar6 = local_38;
                    if (local_38 == (int *)0x0) goto LAB_0078fa68;
                    iVar9 = FUN_00785202((uint)local_10 & 0xffffff | 0x30000000,(int)local_10 * 2,1,
                                         0);
                    if ((iVar9 < 0) || (iVar9 = FUN_007854e4(local_14), iVar9 < 0))
                    goto LAB_0078f269;
                    *(undefined4 *)piVar6[4] = *(undefined4 *)local_14[4];
                    piVar6 = local_70;
                    if (local_34 != (int *)0x0) {
                      piVar6 = local_54;
                    }
                    piVar15 = (int *)local_38[2];
                    for (uVar3 = (uint)local_10 & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
                      *piVar15 = *piVar6;
                      piVar6 = piVar6 + 1;
                      piVar15 = piVar15 + 1;
                    }
                    for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
                      *(char *)piVar15 = (char)*piVar6;
                      piVar6 = (int *)((int)piVar6 + 1);
                      piVar15 = (int *)((int)piVar15 + 1);
                    }
                    piVar6 = local_88;
                    if (local_34 != (int *)0x0) {
                      piVar6 = local_98;
                    }
                    piVar15 = (int *)(local_38[2] + (int)local_10 * 4);
                    for (uVar3 = (uint)local_10 & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
                      *piVar15 = *piVar6;
                      piVar6 = piVar6 + 1;
                      piVar15 = piVar15 + 1;
                    }
                    for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
                      *(char *)piVar15 = (char)*piVar6;
                      piVar6 = (int *)((int)piVar6 + 1);
                      piVar15 = (int *)((int)piVar15 + 1);
                    }
                    *(int **)(*(int *)(param_1 + 0x18) + (int)local_18 * 4) = local_38;
                    FUN_00784bd1(1);
                    *local_2c = 0;
                    *local_30 = 0;
                  }
                }
              }
            }
          }
LAB_0078f1b0:
          local_18 = (int *)((int)local_18 + 1);
        } while (local_18 < *(int **)(param_1 + 0xc));
      }
    }
    FUN_0078937f();
    local_18 = (int *)0x0;
    if (*(int *)(param_1 + 0xc) != 0) {
      do {
        puVar12 = *(uint **)(*(int *)(param_1 + 0x18) + (int)local_18 * 4);
        local_40 = puVar12;
        iVar9 = FUN_007855b1();
        if ((((iVar9 != 0) || (iVar9 = FUN_007855c3(), iVar9 != 0)) ||
            (iVar9 = FUN_007855d5(), iVar9 != 0)) &&
           ((iVar9 = FUN_00785545(), iVar9 != 0 || ((*(byte *)(param_1 + 0x90) & 6) == 0)))) {
          iVar9 = *(int *)(param_1 + 0x14);
          local_9c = **(int **)(iVar9 + *(int *)puVar12[4] * 4);
          local_3c = *(uint *)(*(int *)(*(int *)(param_1 + 0x10) + local_9c * 4) + 0x1c);
          if (local_3c != 0) {
            local_34 = *(int **)(param_1 + 0xc);
            local_38 = (int *)0x0;
            if (puVar12[1] != 0) {
              local_2c = (int *)puVar12[2];
              local_20 = (int *)puVar12[1];
              do {
                iVar5 = *local_2c;
                while (iVar5 != -1) {
                  piVar6 = *(int **)(iVar9 + iVar5 * 4);
                  if (((*(byte *)(*(int *)(*(int *)(param_1 + 0x10) + *piVar6 * 4) + 4) & 2) != 0)
                     && (local_38 < (int *)(piVar6[0xb] + 1))) {
                    local_38 = (int *)(piVar6[0xb] + 1);
                  }
                  iVar5 = piVar6[1];
                }
                local_2c = local_2c + 1;
                local_20 = (int *)((int)local_20 + -1);
              } while (local_20 != (int *)0x0);
            }
            local_44 = local_34;
            if (puVar12[3] != 0) {
              local_20 = (int *)puVar12[3];
              piVar6 = (int *)puVar12[4];
              do {
                piVar15 = *(int **)(iVar9 + *piVar6 * 4);
                if ((int *)piVar15[0xe] < local_44) {
                  local_44 = (int *)piVar15[0xe];
                }
                while (piVar15[1] != -1) {
                  piVar15 = *(int **)(iVar9 + piVar15[1] * 4);
                  if (((*(byte *)(*(int *)(*(int *)(param_1 + 0x10) + *piVar15 * 4) + 4) & 2) != 0)
                     && (local_38 < (int *)(piVar15[0xb] + 1))) {
                    local_38 = (int *)(piVar15[0xb] + 1);
                  }
                }
                piVar6 = piVar6 + 1;
                local_20 = (int *)((int)local_20 + -1);
              } while (local_20 != (int *)0x0);
            }
            local_14 = local_38;
LAB_0078f7bb:
            if (local_14 < local_44) {
              if (local_18 == local_14) goto LAB_0078f7b5;
              local_5c = *(uint **)(*(int *)(param_1 + 0x18) + (int)local_14 * 4);
              local_c = local_5c;
              puVar12 = local_40;
              if (local_18 < local_14) {
                local_c = local_40;
                puVar12 = local_5c;
              }
              local_24 = puVar12;
              if (((*local_c ^ *puVar12) & 0xff000000) != 0) goto LAB_0078f7b5;
              piVar6 = *(int **)(*(int *)(param_1 + 0x14) + *(int *)local_c[4] * 4);
              puVar11 = *(undefined4 **)(*(int *)(param_1 + 0x14) + *(int *)puVar12[4] * 4);
              local_10 = (int *)*puVar11;
              if ((local_10 != (int *)*piVar6) || (puVar11[1] != piVar6[1])) goto LAB_0078f7b5;
              local_78 = local_c[1] + puVar12[1];
              local_30 = (int *)local_c[3];
              local_28 = puVar12[3];
              local_1c = (int)local_30 + local_28;
              if (4 < local_1c) goto LAB_0078f7b5;
              local_2c = (int *)puVar11[2];
              local_20 = (int *)piVar6[2];
              if ((local_2c != local_20) &&
                 ((((*(byte *)(param_1 + 0x90) & 6) != 0 ||
                   ((*(byte *)(*(int *)(*(int *)(param_1 + 0x10) + (int)local_10 * 4) + 4) & 0x10)
                    != 0)) ||
                  (4 < (uint)(*(int *)(local_3c + (int)local_20 * 4) +
                             *(int *)(local_3c + (int)local_2c * 4)))))) goto LAB_0078f7b5;
              local_8 = local_18;
              if (local_14 <= local_18) {
                local_8 = local_14;
              }
              iVar9 = FUN_00785545();
              if ((iVar9 == 0) && (iVar9 = FUN_00785557(), iVar9 == 0)) {
                iVar9 = FUN_007855b1();
                piVar15 = local_8;
                puVar12 = local_c;
                piVar6 = local_30;
                if (iVar9 == 0) {
                  iVar9 = FUN_007855c3();
                  piVar6 = local_30;
                  if (iVar9 == 0) {
                    iVar9 = FUN_007855d5();
                    piVar15 = local_30;
                    piVar6 = local_34;
                    if (iVar9 != 0) {
                      iVar9 = (int)local_30 * 4;
                      piVar6 = (int *)local_c[2];
                      piVar10 = local_54;
                      for (uVar3 = (uint)local_30 & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
                        *piVar10 = *piVar6;
                        piVar6 = piVar6 + 1;
                        piVar10 = piVar10 + 1;
                      }
                      for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
                        *(char *)piVar10 = (char)*piVar6;
                        piVar6 = (int *)((int)piVar6 + 1);
                        piVar10 = (int *)((int)piVar10 + 1);
                      }
                      local_10 = (int *)local_24[2];
                      piVar6 = local_10;
                      piVar10 = local_54 + (int)piVar15;
                      for (uVar3 = local_28 & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
                        *piVar10 = *piVar6;
                        piVar6 = piVar6 + 1;
                        piVar10 = piVar10 + 1;
                      }
                      for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
                        *(char *)piVar10 = (char)*piVar6;
                        piVar6 = (int *)((int)piVar6 + 1);
                        piVar10 = (int *)((int)piVar10 + 1);
                      }
                      piVar6 = (int *)(local_c[2] + iVar9);
                      piVar10 = local_70;
                      for (uVar3 = (uint)piVar15 & 0x3fffffff; piVar13 = local_10, uVar3 != 0;
                          uVar3 = uVar3 - 1) {
                        *piVar10 = *piVar6;
                        piVar6 = piVar6 + 1;
                        piVar10 = piVar10 + 1;
                      }
                      for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
                        *(char *)piVar10 = (char)*piVar6;
                        piVar6 = (int *)((int)piVar6 + 1);
                        piVar10 = (int *)((int)piVar10 + 1);
                      }
                      piVar6 = piVar13 + local_28;
                      piVar10 = local_70 + (int)piVar15;
                      for (uVar3 = local_28 & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
                        *piVar10 = *piVar6;
                        piVar6 = piVar6 + 1;
                        piVar10 = piVar10 + 1;
                      }
                      uVar3 = local_c[2];
                      for (iVar9 = 0; piVar13 = local_8, puVar12 = local_c, iVar9 != 0;
                          iVar9 = iVar9 + -1) {
                        *(char *)piVar10 = (char)*piVar6;
                        piVar6 = (int *)((int)piVar6 + 1);
                        piVar10 = (int *)((int)piVar10 + 1);
                      }
                      piVar6 = (int *)(uVar3 + (int)local_30 * 8);
                      piVar10 = local_ac;
                      for (uVar7 = (uint)piVar15 & 0x3fffffff; uVar3 = local_28, uVar7 != 0;
                          uVar7 = uVar7 - 1) {
                        *piVar10 = *piVar6;
                        piVar6 = piVar6 + 1;
                        piVar10 = piVar10 + 1;
                      }
                      for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
                        *(char *)piVar10 = (char)*piVar6;
                        piVar6 = (int *)((int)piVar6 + 1);
                        piVar10 = (int *)((int)piVar10 + 1);
                      }
                      piVar6 = local_10 + uVar3 * 2;
                      piVar15 = local_ac + (int)piVar15;
                      for (uVar7 = uVar3 & 0x3fffffff; uVar3 = local_1c, uVar7 != 0;
                          uVar7 = uVar7 - 1) {
                        *piVar15 = *piVar6;
                        piVar6 = piVar6 + 1;
                        piVar15 = piVar15 + 1;
                      }
                      for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
                        *(char *)piVar15 = (char)*piVar6;
                        piVar6 = (int *)((int)piVar6 + 1);
                        piVar15 = (int *)((int)piVar15 + 1);
                      }
                      iVar5 = FUN_00788a64(local_54,uVar3,0,0,puVar12,piVar13);
                      local_58 = FUN_00788a64(local_70,local_1c,0,0,local_c,local_8);
                      iVar9 = FUN_00788a64(local_ac,local_1c,0,0,local_c,local_8);
                      piVar6 = local_34;
                      if ((iVar5 != 0) && (local_58 != 0)) goto LAB_0078f71c;
                    }
                  }
                  else {
                    uVar3 = (int)local_30 * 4;
                    piVar15 = (int *)local_c[2];
                    piVar10 = local_54;
                    for (uVar7 = (uint)local_30 & 0x3fffffff; puVar12 = local_24, uVar7 != 0;
                        uVar7 = uVar7 - 1) {
                      *piVar10 = *piVar15;
                      piVar15 = piVar15 + 1;
                      piVar10 = piVar10 + 1;
                    }
                    for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
                      *(char *)piVar10 = (char)*piVar15;
                      piVar15 = (int *)((int)piVar15 + 1);
                      piVar10 = (int *)((int)piVar10 + 1);
                    }
                    local_10 = (int *)puVar12[2];
                    piVar15 = local_10;
                    piVar10 = local_54 + (int)local_30;
                    local_30 = (int *)(local_28 << 2);
                    for (uVar7 = local_28 & 0x3fffffff; uVar7 != 0; uVar7 = uVar7 - 1) {
                      *piVar10 = *piVar15;
                      piVar15 = piVar15 + 1;
                      piVar10 = piVar10 + 1;
                    }
                    uVar7 = local_c[2];
                    for (iVar9 = 0; piVar13 = local_8, puVar12 = local_c, iVar9 != 0;
                        iVar9 = iVar9 + -1) {
                      *(char *)piVar10 = (char)*piVar15;
                      piVar15 = (int *)((int)piVar15 + 1);
                      piVar10 = (int *)((int)piVar10 + 1);
                    }
                    piVar15 = (int *)(uVar7 + uVar3);
                    piVar10 = local_70;
                    for (uVar8 = (uint)piVar6 & 0x3fffffff; piVar2 = local_10, uVar8 != 0;
                        uVar8 = uVar8 - 1) {
                      *piVar10 = *piVar15;
                      piVar15 = piVar15 + 1;
                      piVar10 = piVar10 + 1;
                    }
                    for (iVar9 = 0; piVar1 = local_30, iVar9 != 0; iVar9 = iVar9 + -1) {
                      *(char *)piVar10 = (char)*piVar15;
                      piVar15 = (int *)((int)piVar15 + 1);
                      piVar10 = (int *)((int)piVar10 + 1);
                    }
                    piVar15 = (int *)((int)piVar2 + (int)local_30);
                    piVar6 = local_70 + (int)piVar6;
                    local_58 = uVar3;
                    for (uVar7 = (uint)local_30 >> 2; uVar3 = local_1c, uVar7 != 0;
                        uVar7 = uVar7 - 1) {
                      *piVar6 = *piVar15;
                      piVar15 = piVar15 + 1;
                      piVar6 = piVar6 + 1;
                    }
                    for (uVar7 = (uint)piVar1 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
                      *(char *)piVar6 = (char)*piVar15;
                      piVar15 = (int *)((int)piVar15 + 1);
                      piVar6 = (int *)((int)piVar6 + 1);
                    }
                    iVar9 = FUN_00788a64(local_54,uVar3,0,0,puVar12,piVar13);
                    iVar5 = FUN_00788a64(local_70,local_1c,0,0,local_c,local_8);
                    if ((iVar9 != 0) && (iVar5 != 0)) goto LAB_0078f776;
                    iVar9 = FUN_00785609();
                    uVar3 = local_58;
                    piVar6 = local_34;
                    if (iVar9 != 0) {
                      piVar6 = (int *)local_c[2];
                      piVar15 = local_98;
                      for (uVar7 = local_58 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
                        *piVar15 = *piVar6;
                        piVar6 = piVar6 + 1;
                        piVar15 = piVar15 + 1;
                      }
                      for (uVar7 = uVar3 & 3; piVar10 = local_30, uVar7 != 0; uVar7 = uVar7 - 1) {
                        *(char *)piVar15 = (char)*piVar6;
                        piVar6 = (int *)((int)piVar6 + 1);
                        piVar15 = (int *)((int)piVar15 + 1);
                      }
                      local_10 = (int *)local_24[2];
                      puVar11 = (undefined4 *)((int)local_10 + (int)local_30);
                      puVar14 = (undefined4 *)((int)local_98 + uVar3);
                      for (uVar7 = (uint)local_30 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
                        *puVar14 = *puVar11;
                        puVar11 = puVar11 + 1;
                        puVar14 = puVar14 + 1;
                      }
                      uVar7 = local_c[2];
                      for (uVar8 = (uint)piVar10 & 3; piVar6 = local_8, puVar12 = local_c,
                          uVar8 != 0; uVar8 = uVar8 - 1) {
                        *(undefined1 *)puVar14 = *(undefined1 *)puVar11;
                        puVar11 = (undefined4 *)((int)puVar11 + 1);
                        puVar14 = (undefined4 *)((int)puVar14 + 1);
                      }
                      piVar15 = (int *)(uVar7 + uVar3);
                      piVar10 = local_88;
                      for (uVar8 = uVar3 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
                        *piVar10 = *piVar15;
                        piVar15 = piVar15 + 1;
                        piVar10 = piVar10 + 1;
                      }
                      for (uVar7 = uVar3 & 3; piVar13 = local_30, uVar7 != 0; uVar7 = uVar7 - 1) {
                        *(char *)piVar10 = (char)*piVar15;
                        piVar15 = (int *)((int)piVar15 + 1);
                        piVar10 = (int *)((int)piVar10 + 1);
                      }
                      piVar15 = local_10;
                      piVar10 = (int *)((int)local_88 + uVar3);
                      for (uVar7 = (uint)local_30 >> 2; uVar3 = local_1c, uVar7 != 0;
                          uVar7 = uVar7 - 1) {
                        *piVar10 = *piVar15;
                        piVar15 = piVar15 + 1;
                        piVar10 = piVar10 + 1;
                      }
                      for (uVar7 = (uint)piVar13 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
                        *(char *)piVar10 = (char)*piVar15;
                        piVar15 = (int *)((int)piVar15 + 1);
                        piVar10 = (int *)((int)piVar10 + 1);
                      }
                      iVar9 = FUN_00788a64(local_98,uVar3,0,0,puVar12,piVar6);
                      iVar5 = FUN_00788a64(local_88,local_1c,0,0,local_c,local_8);
                      piVar6 = local_34;
                      if ((iVar9 != 0) && (iVar5 != 0)) {
                        local_28 = 1;
                        goto LAB_0078f77a;
                      }
                    }
                  }
                }
                else {
                  piVar10 = (int *)local_c[2];
                  piVar13 = local_54;
                  for (uVar3 = (uint)local_30 & 0x3fffffff; puVar16 = local_24, uVar3 != 0;
                      uVar3 = uVar3 - 1) {
                    *piVar13 = *piVar10;
                    piVar10 = piVar10 + 1;
                    piVar13 = piVar13 + 1;
                  }
                  for (iVar9 = 0; uVar3 = local_1c, iVar9 != 0; iVar9 = iVar9 + -1) {
                    *(char *)piVar13 = (char)*piVar10;
                    piVar10 = (int *)((int)piVar10 + 1);
                    piVar13 = (int *)((int)piVar13 + 1);
                  }
                  piVar10 = (int *)puVar16[2];
                  piVar6 = local_54 + (int)piVar6;
                  for (uVar7 = local_28; uVar7 != 0; uVar7 = uVar7 - 1) {
                    *piVar6 = *piVar10;
                    piVar10 = piVar10 + 1;
                    piVar6 = piVar6 + 1;
                  }
                  iVar9 = FUN_00788a64(local_54,uVar3,0,0,puVar12,piVar15);
LAB_0078f71c:
                  piVar6 = local_34;
                  if (iVar9 != 0) goto LAB_0078f776;
                }
LAB_0078f7b0:
                while (piVar6 < *(int **)(param_1 + 0xc)) {
                  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + -1;
                  if (*(int *)(*(int *)(param_1 + 0x18) + *(int *)(param_1 + 0xc) * 4) != 0) {
                    FUN_00784bd1(1);
                  }
                }
                goto LAB_0078f7b5;
              }
              piVar13 = local_30;
              local_10 = (int *)puVar12[2];
              piVar15 = *(int **)(*(int *)(param_1 + 0x14) + *local_10 * 4);
              piVar10 = *(int **)(*(int *)(param_1 + 0x14) + *(int *)local_c[2] * 4);
              piVar6 = local_34;
              if (((*piVar15 != *piVar10) || (piVar15[1] != piVar10[1])) ||
                 (piVar15[2] != piVar10[2])) goto LAB_0078f7b0;
              piVar6 = (int *)local_c[2];
              piVar15 = local_54;
              for (uVar3 = (uint)local_30 & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
                *piVar15 = *piVar6;
                piVar6 = piVar6 + 1;
                piVar15 = piVar15 + 1;
              }
              for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
                *(char *)piVar15 = (char)*piVar6;
                piVar6 = (int *)((int)piVar6 + 1);
                piVar15 = (int *)((int)piVar15 + 1);
              }
              piVar6 = local_10;
              piVar15 = local_54 + (int)piVar13;
              for (uVar3 = local_28; uVar3 != 0; uVar3 = uVar3 - 1) {
                *piVar15 = *piVar6;
                piVar6 = piVar6 + 1;
                piVar15 = piVar15 + 1;
              }
LAB_0078f776:
              local_28 = 0;
LAB_0078f77a:
              if ((local_2c != local_20) &&
                 (piVar6 = local_34,
                 4 < (uint)(*(int *)(local_3c + (int)local_20 * 4) +
                           *(int *)(local_3c + (int)local_2c * 4)))) goto LAB_0078f7b0;
              pvVar4 = operator_new(0x38);
              if (pvVar4 == (void *)0x0) {
                local_8 = (int *)0x0;
              }
              else {
                local_8 = (int *)FUN_007851ab();
              }
              puVar12 = local_24;
              if (local_8 == (int *)0x0) break;
              iVar9 = FUN_00785202((*local_24 ^ local_1c) & 0xffffff ^ *local_24,local_78,local_1c,0
                                  );
              if ((-1 < iVar9) && (iVar9 = FUN_007854e4(puVar12), -1 < iVar9)) {
                if (local_2c != local_20) {
                  uVar3 = 0;
                  if (*(int *)(param_1 + 8) != 0) {
                    do {
                      piVar6 = *(int **)(*(int *)(param_1 + 0x14) + uVar3 * 4);
                      if ((local_9c == *piVar6) && (local_2c == (int *)piVar6[2])) {
                        piVar6[2] = (int)local_20;
                        piVar6[3] = piVar6[3] + *(int *)(local_3c + (int)local_20 * 4);
                      }
                      uVar3 = uVar3 + 1;
                    } while (uVar3 < *(uint *)(param_1 + 8));
                  }
                  piVar6 = (int *)(local_3c + (int)local_20 * 4);
                  piVar15 = (int *)(local_3c + (int)local_2c * 4);
                  *piVar6 = *piVar6 + *piVar15;
                  *piVar15 = 0;
                }
                puVar11 = (undefined4 *)local_c[4];
                puVar14 = (undefined4 *)local_8[4];
                for (uVar3 = local_c[3] & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
                  *puVar14 = *puVar11;
                  puVar11 = puVar11 + 1;
                  puVar14 = puVar14 + 1;
                }
                for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
                  *(undefined1 *)puVar14 = *(undefined1 *)puVar11;
                  puVar11 = (undefined4 *)((int)puVar11 + 1);
                  puVar14 = (undefined4 *)((int)puVar14 + 1);
                }
                puVar11 = (undefined4 *)local_24[4];
                puVar14 = (undefined4 *)(local_8[4] + local_c[3] * 4);
                for (uVar3 = local_24[3] & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
                  *puVar14 = *puVar11;
                  puVar11 = puVar11 + 1;
                  puVar14 = puVar14 + 1;
                }
                for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
                  *(undefined1 *)puVar14 = *(undefined1 *)puVar11;
                  puVar11 = (undefined4 *)((int)puVar11 + 1);
                  puVar14 = (undefined4 *)((int)puVar14 + 1);
                }
                iVar9 = FUN_007855b1();
                if (iVar9 != 0) {
                  piVar6 = local_54;
                  piVar15 = (int *)local_8[2];
                  for (uVar3 = local_1c; uVar3 != 0; uVar3 = uVar3 - 1) {
                    *piVar15 = *piVar6;
                    piVar6 = piVar6 + 1;
                    piVar15 = piVar15 + 1;
                  }
                }
                iVar9 = FUN_007855c3();
                if (iVar9 == 0) {
                  iVar9 = FUN_007855d5();
                  if (iVar9 != 0) {
                    piVar6 = local_54;
                    piVar15 = (int *)local_8[2];
                    for (uVar3 = local_1c & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
                      *piVar15 = *piVar6;
                      piVar6 = piVar6 + 1;
                      piVar15 = piVar15 + 1;
                    }
                    for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
                      *(char *)piVar15 = (char)*piVar6;
                      piVar6 = (int *)((int)piVar6 + 1);
                      piVar15 = (int *)((int)piVar15 + 1);
                    }
                    piVar6 = local_70;
                    piVar15 = (int *)(local_8[2] + local_1c * 4);
                    for (uVar3 = local_1c & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
                      *piVar15 = *piVar6;
                      piVar6 = piVar6 + 1;
                      piVar15 = piVar15 + 1;
                    }
                    for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
                      *(char *)piVar15 = (char)*piVar6;
                      piVar6 = (int *)((int)piVar6 + 1);
                      piVar15 = (int *)((int)piVar15 + 1);
                    }
                    uVar3 = local_1c << 2;
                    piVar6 = local_ac;
                    piVar15 = (int *)(local_8[2] + local_1c * 8);
                    goto LAB_0078f973;
                  }
                }
                else {
                  piVar6 = local_54;
                  if (local_28 != 0) {
                    piVar6 = local_98;
                  }
                  uVar3 = local_1c * 4;
                  piVar15 = (int *)local_8[2];
                  for (uVar7 = local_1c & 0x3fffffff; uVar7 != 0; uVar7 = uVar7 - 1) {
                    *piVar15 = *piVar6;
                    piVar6 = piVar6 + 1;
                    piVar15 = piVar15 + 1;
                  }
                  for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
                    *(char *)piVar15 = (char)*piVar6;
                    piVar6 = (int *)((int)piVar6 + 1);
                    piVar15 = (int *)((int)piVar15 + 1);
                  }
                  piVar6 = local_70;
                  if (local_28 != 0) {
                    piVar6 = local_88;
                  }
                  piVar15 = (int *)(local_8[2] + uVar3);
LAB_0078f973:
                  for (uVar3 = uVar3 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
                    *piVar15 = *piVar6;
                    piVar6 = piVar6 + 1;
                    piVar15 = piVar15 + 1;
                  }
                  for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
                    *(char *)piVar15 = (char)*piVar6;
                    piVar6 = (int *)((int)piVar6 + 1);
                    piVar15 = (int *)((int)piVar15 + 1);
                  }
                }
                if (local_5c != (uint *)0x0) {
                  FUN_00784bd1(1);
                }
                local_3c = (int)local_14 * 4;
                *(int **)(local_3c + *(int *)(param_1 + 0x18)) = local_8;
                *local_40 = 0;
                local_40[1] = 0;
                local_40[3] = 0;
                if (local_34 < *(int **)(param_1 + 0xc)) {
                  local_5c = (uint *)((int)*(int **)(param_1 + 0xc) - (int)local_34);
                  local_20 = (int *)((int)local_5c * 4);
                  local_40 = operator_new((uint)local_20);
                  if (local_40 != (uint *)0x0) {
                    puVar12 = (uint *)(*(int *)(param_1 + 0x18) + (int)local_34 * 4);
                    puVar16 = local_40;
                    for (uVar3 = (uint)local_20 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
                      *puVar16 = *puVar12;
                      puVar12 = puVar12 + 1;
                      puVar16 = puVar16 + 1;
                    }
                    for (uVar3 = (uint)local_20 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
                      *(char *)puVar16 = (char)*puVar12;
                      puVar12 = (uint *)((int)puVar12 + 1);
                      puVar16 = (uint *)((int)puVar16 + 1);
                    }
                    _memmove((void *)(*(int *)(param_1 + 0x18) +
                                     (int)((int)local_5c + (int)local_14) * 4),
                             (void *)(local_3c + *(int *)(param_1 + 0x18)),
                             ((int)local_34 - (int)local_14) * 4);
                    puVar12 = local_40;
                    puVar16 = (uint *)(*(int *)(param_1 + 0x18) + local_3c);
                    for (uVar3 = (uint)local_20 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
                      *puVar16 = *puVar12;
                      puVar12 = puVar12 + 1;
                      puVar16 = puVar16 + 1;
                    }
                    for (uVar3 = (uint)local_20 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
                      *(char *)puVar16 = (char)*puVar12;
                      puVar12 = (uint *)((int)puVar12 + 1);
                      puVar16 = (uint *)((int)puVar16 + 1);
                    }
                    /* WARNING: Subroutine does not return */
                    _free(local_40);
                  }
                  break;
                }
                FUN_0078937f();
                local_18 = (int *)((int)local_38 - 1);
                local_60 = 1;
                goto LAB_0078fa4f;
              }
              goto LAB_0078f269;
            }
          }
        }
LAB_0078fa4f:
        local_18 = (int *)((int)local_18 + 1);
      } while (local_18 < *(int **)(param_1 + 0xc));
    }
  }
LAB_0078fa68:
                    /* WARNING: Subroutine does not return */
  _free(local_74);
LAB_0078f7b5:
  local_14 = (int *)((int)local_14 + 1);
  goto LAB_0078f7bb;
LAB_0078f269:
  FUN_00784bd1(1);
  goto LAB_0078fa68;
}



/* function 007a316c FUN_007a316c */

/* WARNING: Type propagation algorithm not settling */

int __thiscall FUN_007a316c(int param_1,int *param_2,uint param_3,int param_4,uint param_5)

{
  uint *puVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  int *piVar5;
  void *pvVar6;
  uint uVar7;
  int *piVar8;
  int iVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined8 uVar12;
  ulonglong uVar13;
  uint auStack_88 [6];
  uint auStack_70 [6];
  uint local_58;
  uint local_4c [4];
  uint auStack_3c [4];
  int local_2c;
  uint local_28;
  uint local_24;
  uint local_20;
  int *local_1c;
  uint *local_18;
  int *local_14;
  uint local_10;
  int *local_c;
  uint local_8;
  
  local_28 = 0;
  local_4c[0] = 0;
  local_4c[1] = 0;
  local_4c[2] = 0;
  if (param_3 != 0) {
    local_1c = param_2;
    do {
      puVar1 = (uint *)*local_1c;
      if (puVar1 != (uint *)0x0) {
        uVar3 = *puVar1 & 0xffffff;
        uVar7 = *puVar1 & 0xff000000;
        uVar4 = uVar3;
        if (uVar7 == 0x40000000) {
          uVar4 = 1;
        }
        if ((uVar4 == param_5) && (uVar7 != 0x34000000)) {
          local_10 = 0;
          local_8 = 0;
          if (param_5 != 0) {
            local_c = (int *)(puVar1[2] + uVar3 * 4);
            do {
              piVar5 = (int *)FUN_007a2a55(*(undefined4 *)(param_1 + 0x140),
                                           *(undefined4 *)(param_1 + 0x134),local_c,1,0);
              uVar4 = local_8;
              local_14 = piVar5;
              auStack_88[local_8 + 3] = (uint)piVar5;
              if ((piVar5 == (int *)0x0) || (*piVar5 != 0x30000003)) {
                local_10 = 1;
              }
              else {
                FUN_007a2b4b(*(undefined4 *)(param_1 + 0x140),*(undefined4 *)(param_1 + 0x134),
                             local_14,auStack_70 + uVar4 + 0xd,auStack_70 + uVar4,auStack_88 + uVar4
                             ,0,0);
                local_18 = auStack_70 + uVar4 + 6;
                FUN_007a2b4b(param_4,4,local_14,local_18,auStack_70 + uVar4 + 3,auStack_3c + 3,1,0);
                if (((auStack_88[uVar4] == 0) || (*local_18 != local_58)) || (auStack_3c[3] == 0)) {
                  local_10 = 1;
                }
              }
              local_8 = local_8 + 1;
              local_c = local_c + 1;
            } while (local_8 < param_5);
            if (local_10 != 0) goto LAB_007a36c5;
          }
          local_8 = 0;
          if (param_5 != 0) {
            do {
              uVar4 = local_8;
              local_18 = *(uint **)(param_1 + 0x88);
              if (local_18 < *(uint **)(param_1 + 0x138)) {
                local_14 = (int *)(*(int *)(param_1 + 0x144) + (int)local_18 * 4);
                do {
                  local_c = (int *)*local_14;
                  if (((local_c != (int *)0x0) &&
                      (puVar1 = (uint *)*local_1c, puVar1 != (uint *)0x0)) && (*local_c != 0)) {
                    local_10 = *puVar1 & 0xffffff;
                    local_20 = puVar1[1];
                    if (*puVar1 == 0xef000003) {
                      local_20 = 6;
                    }
                    if (local_10 < local_20) {
                      uVar3 = local_c[1];
                      do {
                        local_24 = 0;
                        if (uVar3 != 0) {
                          iVar9 = *(int *)(puVar1[2] + local_10 * 4);
                          piVar5 = (int *)local_c[2];
                          piVar8 = local_c;
                          do {
                            if ((*piVar5 == iVar9) ||
                               (piVar8 = local_c,
                               *(int *)(*(int *)(*(int *)(param_1 + 0x14) + *piVar5 * 4) + 0x24) ==
                               iVar9)) {
                              uVar12 = 0x8811b8000011ac;
                              iVar9 = piVar8[0xd];
                              goto LAB_007a370a;
                            }
                            local_24 = local_24 + 1;
                            uVar3 = local_c[1];
                            piVar5 = piVar5 + 1;
                            piVar8 = local_c;
                          } while (local_24 < uVar3);
                        }
                        local_10 = local_10 + 1;
                      } while (local_10 < local_20);
                    }
                  }
                  local_14 = local_14 + 1;
                  local_18 = (uint *)((int)local_18 + 1);
                } while (local_18 < *(uint **)(param_1 + 0x138));
              }
              if ((local_8 != 0) &&
                 ((auStack_70[local_8 + 0xc] <= local_58 ||
                  (auStack_70[local_8 + 0xd] != auStack_70[local_8 + 0xc] + 1)))) {
                uVar13 = CONCAT44(*(undefined4 *)(param_1 + 0x30),
                                  "unable to match texm* because source inputs are not in appropriate texture coordinates. See ps_1_% assembly reference for more information"
                                 ) & 0xffffffffff;
                uVar11 = 0x11ad;
                uVar10 = 0;
                goto LAB_007a3770;
              }
              if (*(int *)(*(int *)(*(int *)(param_1 + 0x14) +
                                   *(int *)(*(int *)(auStack_88[local_8 + 3] + 8) +
                                           auStack_70[local_8] * 4) * 4) + 0x20) != 0) {
                uVar12 = 0x8810d0000011ae;
LAB_007a3746:
                iVar9 = 0;
                goto LAB_007a370a;
              }
              iVar9 = *(int *)(*(int *)(*(int *)(param_1 + 0x14) +
                                       *(int *)(*(int *)(auStack_88[local_8 + 3] + 8) +
                                               auStack_70[local_8 + 3] * 4) * 4) + 0x20);
              if ((iVar9 != 0) && (iVar9 != 0x60000)) {
                uVar12 = 0x881080000011af;
                goto LAB_007a3746;
              }
              pvVar6 = operator_new(0x38);
              if (pvVar6 == (void *)0x0) {
                uVar3 = 0;
              }
              else {
                uVar3 = FUN_007851ab();
              }
              auStack_70[uVar4 + 9] = uVar3;
              if (uVar3 == 0) {
                iVar9 = -0x7ff8fff2;
                goto LAB_007a36da;
              }
              if (local_8 == param_5 - 1) {
                if (*(int *)*local_1c == -0x10fffffd) {
                  if (param_5 != 3) {
LAB_007a3750:
                    iVar9 = 1;
                    goto LAB_007a36da;
                  }
                  uVar12 = 4;
                  uVar10 = 9;
                  iVar9 = -0x15fffffd;
                }
                else if (*(int *)*local_1c == -0x11fffffd) {
                  if (param_5 != 3) goto LAB_007a3750;
                  uVar12 = 4;
                  uVar10 = 6;
                  iVar9 = -0x16fffffd;
                }
                else {
                  uVar12 = 4;
                  uVar10 = 6;
                  if (param_5 != 1) {
                    iVar9 = ((param_5 != 3) - 1 & 0x2000000) + 0xe3000003;
                    goto LAB_007a3494;
                  }
                  iVar9 = -0x14fffffd;
                }
              }
              else {
                uVar12 = 0;
                iVar9 = ((param_5 != 3) - 1 & 0x2000000) + 0xe2000003;
LAB_007a3494:
                uVar10 = 6;
              }
              iVar9 = FUN_00785202(iVar9,uVar10,uVar12);
              if (iVar9 < 0) goto LAB_007a36da;
              local_8 = local_8 + 1;
            } while (local_8 < param_5);
          }
          local_8 = 0;
          if (param_5 != 0) {
            do {
              local_14 = (int *)0x0;
              uVar4 = auStack_70[local_8 + 9];
              local_24 = auStack_88[local_8 + 3];
              local_10 = auStack_88[local_8];
              local_20 = auStack_70[local_8 + 3] << 2;
              local_18 = (uint *)(auStack_70[local_8] << 2);
              uVar3 = 0xc;
              do {
                *(undefined4 *)((uVar3 - 0xc) + *(int *)(uVar4 + 8)) =
                     *(undefined4 *)((int)local_18 + *(int *)(local_24 + 8));
                *(undefined4 *)(uVar3 + *(int *)(uVar4 + 8)) =
                     *(undefined4 *)(local_20 + *(int *)(local_24 + 8));
                local_4c[3] = *(undefined4 *)
                               (*(int *)(param_1 + 0x14) +
                               *(int *)((uVar3 - 0xc) + *(int *)(uVar4 + 8)) * 4);
                local_2c = *(int *)(*(int *)(param_1 + 0x14) +
                                   *(int *)(uVar3 + *(int *)(uVar4 + 8)) * 4);
                iVar9 = FUN_00784f26(*(undefined4 *)(param_1 + 0x58),0,0,0);
                local_c = *(int **)(*(int *)(param_1 + 0x14) + iVar9 * 4);
                *(int *)(uVar3 + *(int *)(uVar4 + 8)) = iVar9;
                FUN_0078572c();
                local_2c = *(int *)(local_2c + 0x20);
                FUN_0078572c();
                local_c[3] = (int)local_14;
                local_c[8] = local_2c;
                if ((*(int *)*local_1c == -0x10fffffd) && (local_8 == param_5 - 1)) {
                  *(undefined4 *)(uVar3 + 0xc + *(int *)(uVar4 + 8)) =
                       *(undefined4 *)(uVar3 + 0xc + ((int *)*local_1c)[2]);
                }
                local_14 = (int *)((int)local_14 + 1);
                local_18 = local_18 + 1;
                local_20 = local_20 + 4;
                uVar3 = uVar3 + 4;
              } while (uVar3 < 0x18);
              local_8 = local_8 + 1;
            } while (local_8 < param_5);
          }
          uVar4 = auStack_70[param_5 + 8];
          uVar3 = 0;
          do {
            *(undefined4 *)(uVar3 + *(int *)(uVar4 + 0x10)) =
                 *(undefined4 *)(uVar3 + *(int *)(*local_1c + 0x10));
            uVar3 = uVar3 + 4;
          } while (uVar3 < 0x10);
          uVar4 = 0;
          if (param_5 != 0) {
            do {
              if (*(int *)(param_4 + auStack_70[uVar4 + 0xd] * 4) != 0) goto LAB_007a3713;
              uVar4 = uVar4 + 1;
            } while (uVar4 < param_5);
          }
          piVar5 = *(int **)(*(int *)(param_1 + 0x14) + **(int **)(*local_1c + 8) * 4);
          iVar9 = *(int *)(*(int *)(param_1 + 0x10) + *piVar5 * 4);
          uVar4 = *(uint *)(iVar9 + 4);
          if ((uVar4 & 0x40) == 0) {
            uVar12 = 0x881054000012cc;
            iVar9 = 0;
LAB_007a370a:
            FUN_007899a1(param_1,iVar9,uVar12);
LAB_007a3713:
            iVar9 = -0x7fffbffb;
            goto LAB_007a36da;
          }
          if ((uVar4 & 0x420) == 0) {
            piVar5[2] = auStack_70[param_5 + 0xc];
          }
          else if (auStack_70[param_5 + 0xc] != piVar5[2]) {
            if ((*(byte *)(iVar9 + 5) & 4) == 0) {
              pcVar2 = "cannot bind sampler to sampler array, sampler must be bound to %i";
            }
            else {
              pcVar2 = "cannot bind sampler to user specified stage, sampler must be bound to %i";
            }
            uVar13 = CONCAT44(auStack_70[param_5 + 0xc],pcVar2);
            uVar11 = 0x11a3;
            uVar10 = *(undefined4 *)(param_2[local_28] + 0x34);
LAB_007a3770:
            FUN_007899a1(param_1,uVar10,uVar11,uVar13);
            goto LAB_007a3713;
          }
          local_8 = 0;
          piVar5 = local_1c;
          if (param_5 != 0) {
            do {
              iVar9 = local_8 + 0xd;
              uVar4 = auStack_70[local_8 + 9];
              auStack_70[local_8 + 9] = 0;
              *(uint *)(param_4 + auStack_70[iVar9] * 4) = uVar4;
              if (*piVar5 != 0) {
                FUN_00784bd1();
                piVar5 = local_1c;
              }
              *piVar5 = 0;
              local_8 = local_8 + 1;
            } while (local_8 < param_5);
          }
        }
      }
LAB_007a36c5:
      local_28 = local_28 + 1;
      local_1c = local_1c + 1;
    } while (local_28 < param_3);
  }
  iVar9 = 0;
LAB_007a36da:
  uVar4 = 0;
  do {
    if (auStack_70[uVar4 + 9] != 0) {
      FUN_00784bd1();
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < 3);
  return iVar9;
}



/* function 00776904 FUN_00776904 */

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00776904(int param_1,int *******param_2,int *******param_3)

{
  int *****pppppiVar1;
  float10 fVar2;
  float10 fVar3;
  undefined3 uVar4;
  void *pvVar5;
  int iVar6;
  int *****pppppiVar7;
  undefined4 uVar8;
  int *******pppppppiVar9;
  undefined4 *puVar10;
  int ******ppppppiVar11;
  uint uVar12;
  uint uVar13;
  int ******ppppppiVar14;
  int *******pppppppiVar15;
  int iVar16;
  int *piVar17;
  int *******pppppppiVar18;
  undefined8 uVar19;
  ulonglong uVar20;
  longlong lVar21;
  undefined4 local_1e8 [3];
  undefined1 local_1dc [12];
  undefined1 local_1d0 [12];
  undefined1 local_1c4 [12];
  undefined4 local_1b8 [3];
  undefined1 local_1ac [12];
  undefined1 local_1a0 [12];
  undefined1 local_194 [12];
  undefined4 local_188 [3];
  undefined1 local_17c [12];
  undefined1 local_170 [12];
  undefined1 local_164 [12];
  undefined4 local_158;
  int local_154;
  undefined4 local_150;
  undefined4 uStack_14c;
  undefined4 uStack_148;
  int ******local_144;
  int ******local_140;
  int ******local_13c;
  int ******local_138;
  int ******local_134;
  int ******local_130;
  int ******local_12c;
  int ******local_128;
  int ******local_124;
  int ******local_120;
  int ******local_11c;
  int ******local_118;
  int ******local_114;
  int ******local_110;
  int ******local_10c;
  undefined1 local_108 [4];
  undefined1 local_104 [4];
  int local_100 [2];
  int ******local_f8 [3];
  int local_ec [3];
  int *******local_e0;
  uint local_dc;
  int local_d8;
  undefined4 *local_d4;
  int local_d0;
  int local_cc;
  int ******local_c8;
  int *******local_c4;
  int ******local_c0;
  int ******local_bc;
  int *local_b8;
  int ******local_b4;
  int ******local_b0;
  int ******local_ac;
  int ******local_a8;
  int ******local_a4 [9];
  int *******local_80;
  int ******local_7c;
  int ******local_78;
  int ******local_74;
  int local_70;
  int *******local_6c;
  int *******local_68;
  int *******local_64;
  int *******local_60;
  int ******local_5c;
  int *******local_58;
  int *******local_54 [4];
  undefined3 local_44;
  undefined1 uStack_41;
  undefined4 local_40;
  undefined4 local_3c;
  int *******local_38;
  int *local_34;
  int *******local_30;
  int ******local_2c [2];
  int *******local_24;
  int ******local_20;
  int *******local_1c;
  int *******local_18;
  int **local_14;
  undefined4 local_10;
  int *******local_c;
  undefined4 local_8;
  
  if (param_2 == (int *******)0x0) {
    if (param_3 != (int *******)0x0) {
      return 0x80004005;
    }
    return 0;
  }
  if (*(int *)((int)param_2 + 4) != 0xc) {
    return 0x80004005;
  }
  local_8 = (int *******)(*(int *)((int)param_2 + 0x14) * *(int *)((int)param_2 + 0x18));
  local_154 = *(int *)((int)param_2 + 0x24);
  if (*(int *)((int)param_2 + 0x1c) != 0x1a) {
    return 0x80004005;
  }
  local_158 = *(undefined4 *)(param_1 + 0x1c);
  local_20 = (int ******)0x0;
  local_1c = (int *******)0x0;
  local_18 = (int *******)0x0;
  local_14 = (int **)0x0;
  local_bc = (int ******)0x0;
  local_b8 = (int *)0x0;
  local_b4 = (int ******)0x0;
  local_b0 = (int ******)0x0;
  local_54[0] = (int *******)0x0;
  local_54[1] = (int *******)0x0;
  local_54[2] = (int *******)0x0;
  local_54[3] = (int *******)0x0;
  local_40 = *(int ********)(local_154 + 8);
  local_c = (int *******)0x0;
  if (local_40 != (int *******)0x0) {
    iVar16 = 0;
    do {
      ppppppiVar11 = local_40[2];
      if (ppppppiVar11 != (int ******)0x0) {
        pppppiVar7 = ppppppiVar11[6];
        pppppiVar1 = ppppppiVar11[5];
        *(int *)((int)&local_bc + iVar16) = (int)pppppiVar7 * (int)pppppiVar1;
        *(int *******)((int)&local_20 + iVar16) = ppppppiVar11;
        pvVar5 = operator_new((int)pppppiVar7 * (int)pppppiVar1 * 4);
        *(void **)((int)local_54 + iVar16) = pvVar5;
        if ((pvVar5 == (void *)0x0) || (iVar6 = FUN_0077c8d2(), iVar6 < 0)) goto LAB_0077bc80;
      }
      local_40 = (int *******)local_40[3];
      iVar16 = iVar16 + 4;
    } while (local_40 != (int *******)0x0);
  }
  pppppppiVar15 = local_8;
  ppppppiVar11 = local_bc;
  pppppppiVar9 = param_3;
  uVar4 = (undefined3)local_8;
  switch(*(undefined4 *)(*(int *)(*(int *)((int)param_2 + 0x20) + 8) + 0x18)) {
  case 0:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      local_c = operator_new((int)local_8 << 2);
      pppppppiVar9 = local_8;
      if (((local_c == (int *******)0x0) || (iVar16 = FUN_00773063(local_c,local_8), iVar16 < 0)) ||
         (iVar16 = FUN_00773063(param_3,pppppppiVar9), iVar16 < 0)) goto LAB_0077bc80;
      uVar12 = (uint)pppppppiVar9 & 0xffffff;
      iVar16 = FUN_00773e3b(param_2,uVar12 | 0x11000000,local_c,local_54[0],0,0);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = CONCAT44(4,local_c);
      pppppppiVar18 = (int *******)(uVar12 | 0x21000000);
      pppppppiVar9 = param_3;
      pppppppiVar15 = local_54[0];
      goto LAB_0077b3b5;
    }
    break;
  case 1:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      lVar21 = CONCAT44(local_8,param_3);
      pppppppiVar9 = (int *******)0x0;
LAB_00776e6f:
      iVar16 = FUN_00774c33(param_2,local_54[0],pppppppiVar9,lVar21);
      goto LAB_0077b3bf;
    }
    break;
  case 2:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      if (local_bc == (int ******)0x1) {
        *param_3 = (int ******)0xffffffff;
        local_40 = (int *******)0xffffffff;
        local_38 = (int *******)0xffffffff;
        iVar16 = FUN_00773e3b(param_2,0x11000001,&local_40,local_54[0],0,0);
        if ((iVar16 < 0) ||
           (iVar16 = FUN_00773e3b(param_2,0x21000001,&local_38,local_54[0],&local_40,4), iVar16 < 0)
           ) goto LAB_0077bc80;
        pppppppiVar18 = (int *******)&local_38;
        pppppppiVar15 = (int *******)&local_40;
        pppppppiVar9 = param_3;
      }
      else {
        if (local_bc != (int ******)0x2) {
          local_c = operator_new((int)local_bc << 4);
          if (local_c == (int *******)0x0) goto LAB_0077bc80;
          uVar12 = 0;
          pppppppiVar9 = local_c;
          do {
            (&local_20)[uVar12] = (int ******)pppppppiVar9;
            uVar12 = uVar12 + 1;
            pppppppiVar9 = pppppppiVar9 + (int)ppppppiVar11;
          } while (uVar12 < 4);
          iVar16 = FUN_00773063(local_20,ppppppiVar11);
          if ((((iVar16 < 0) || (iVar16 = FUN_00773063(local_1c,ppppppiVar11), iVar16 < 0)) ||
              (iVar16 = FUN_00773063(local_18,ppppppiVar11), iVar16 < 0)) ||
             (iVar16 = FUN_00773063(local_14,ppppppiVar11), iVar16 < 0)) goto LAB_0077bc80;
          local_40 = (int *******)CONCAT13(0x11,(int3)ppppppiVar11);
          local_3c = (int *******)0xffffffff;
          local_64 = (int *******)0xffffffff;
          *param_3 = (int ******)0xffffffff;
          local_38 = (int *******)((uint)ppppppiVar11 & 0xffffff);
          iVar16 = FUN_00773e3b(param_2,local_40,local_20,local_54[0],0,0);
          if ((((iVar16 < 0) ||
               (iVar16 = FUN_00773e3b(param_2,(uint)ppppppiVar11 & 0xffffff | 0x21000000,local_1c,
                                      local_54[0],local_20,4), iVar16 < 0)) ||
              ((iVar16 = FUN_00773e3b(param_2,local_40,local_18,local_1c,0,8), iVar16 < 0 ||
               ((iVar16 = FUN_00773e3b(param_2,(uint)local_38 | 0x23000000,local_14,local_18,
                                       local_1c,0x2000017), iVar16 < 0 ||
                (iVar16 = FUN_00773e3b(param_2,(uint)local_38 | 0x30000000,&local_3c,local_14,
                                       local_14,6), iVar16 < 0)))))) ||
             (iVar16 = FUN_00773e3b(param_2,0x11000001,&local_64,&local_3c,0,10), iVar16 < 0))
          goto LAB_0077bc80;
          uVar20 = CONCAT44(0x2000017,&local_3c);
          pppppppiVar18 = (int *******)0x23000001;
          pppppppiVar9 = param_3;
          pppppppiVar15 = (int *******)&local_64;
          goto LAB_0077b3b5;
        }
        local_78 = (int ******)0xffffffff;
        local_74 = (int ******)0xffffffff;
        local_5c = (int ******)0xffffffff;
        local_58 = (int *******)0xffffffff;
        *param_3 = (int ******)0xffffffff;
        local_40 = (int *******)0xffffffff;
        local_38 = (int *******)0xffffffff;
        iVar16 = FUN_00773e3b(param_2,0x11000002,&local_78,local_54[0],0,0);
        if ((((iVar16 < 0) ||
             (iVar16 = FUN_00773e3b(param_2,0x21000002,&local_5c,local_54[0],&local_78,4),
             iVar16 < 0)) ||
            (iVar16 = FUN_00773e3b(param_2,0x25000001,&local_40,&local_5c,&local_58,4), iVar16 < 0))
           || (iVar16 = FUN_00773e3b(param_2,0x11000001,&local_38,&local_40,0,8), iVar16 < 0))
        goto LAB_0077bc80;
        pppppppiVar18 = (int *******)&local_40;
        pppppppiVar15 = (int *******)&local_38;
        pppppppiVar9 = param_3;
      }
LAB_00776e33:
      uVar20 = CONCAT44(0x2000017,pppppppiVar18);
      pppppppiVar18 = (int *******)0x22000001;
      goto LAB_0077b3b5;
    }
    break;
  case 3:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      param_3 = (int *******)0xffffffff;
      local_38 = (int *******)0xffffffff;
      *pppppppiVar9 = (int ******)0xffffffff;
      iVar16 = FUN_00773e3b(param_2,(uint)local_bc & 0xffffff | 0x30000000,&param_3,local_54[0],
                            local_54[0],4);
      if ((iVar16 < 0) ||
         (iVar16 = FUN_00773e3b(param_2,0x11000001,&local_38,&param_3,0,8), iVar16 < 0))
      goto LAB_0077bc80;
      pppppppiVar18 = (int *******)&param_3;
      pppppppiVar15 = (int *******)&local_38;
      goto LAB_00776e33;
    }
    break;
  case 4:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      lVar21 = ZEXT48(local_8) << 0x20;
      pppppppiVar9 = param_3;
      goto LAB_00776e6f;
    }
    break;
  case 5:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar19 = CONCAT44(local_8,param_3);
      pppppppiVar9 = (int *******)0x0;
LAB_00776ef2:
      iVar16 = FUN_0077514f(param_2,local_54[0],pppppppiVar9,uVar19);
      goto LAB_0077b3bf;
    }
    break;
  case 6:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar19 = CONCAT44(local_8,param_3);
      pppppppiVar9 = local_54[1];
      goto LAB_00776ef2;
    }
    break;
  case 7:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      local_c = operator_new((int)local_8 << 3);
      if (local_c == (int *******)0x0) goto LAB_0077bc80;
      local_38 = local_c + (int)local_8;
      uVar19 = FUN_00773063(local_c,local_8);
      if ((((int)uVar19 < 0) ||
          (iVar16 = FUN_00773063((int)((ulonglong)uVar19 >> 0x20),local_8), iVar16 < 0)) ||
         (iVar16 = FUN_00773063(param_3,local_8), iVar16 < 0)) goto LAB_0077bc80;
      pppppppiVar18 = (int *******)((uint)local_8 & 0xffffff);
      iVar16 = FUN_00773e3b(param_2,(uint)pppppppiVar18 | 0x11000000,local_c,local_54[0],0,0);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar8 = 0x14;
      uVar12 = (uint)pppppppiVar18 | 0x13000000;
LAB_00776faf:
      iVar16 = FUN_00773e3b(param_2,uVar12,local_38,local_c,0,uVar8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = CONCAT44(2,local_38);
      pppppppiVar15 = local_54[0];
LAB_0077a5d2:
      pppppppiVar18 = (int *******)((uint)pppppppiVar18 | 0x24000000);
      pppppppiVar9 = param_3;
      goto LAB_0077b3b5;
    }
    break;
  case 8:
    if ((((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0)) ||
       (local_18 == (int *******)0x0)) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      local_c = operator_new((int)local_8 << 2);
      if (((local_c == (int *******)0x0) || (iVar16 = FUN_00773063(local_c,local_8), iVar16 < 0)) ||
         (iVar16 = FUN_00773063(param_3,local_8), iVar16 < 0)) goto LAB_0077bc80;
      uVar12 = (uint)local_8 & 0xffffff;
      iVar16 = FUN_00773e3b(param_2,uVar12 | 0x21000000,local_c,local_54[0],local_54[1],0);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_54[2]);
      pppppppiVar15 = local_c;
LAB_0077a895:
      pppppppiVar18 = (int *******)(uVar12 | 0x20000000);
      pppppppiVar9 = param_3;
      goto LAB_0077b3b5;
    }
    break;
  case 9:
    if (((int *******)local_20 == (int *******)0x0) ||
       (local_c = operator_new((int)local_bc << 3), local_c == (int *******)0x0)) goto LAB_0077bc80;
    uVar12 = 0;
    pppppppiVar9 = local_c;
    do {
      (&local_5c)[uVar12] = (int ******)pppppppiVar9;
      uVar12 = uVar12 + 1;
      pppppppiVar9 = pppppppiVar9 + (int)ppppppiVar11;
    } while (uVar12 < 2);
    ppppppiVar14 = (int ******)0x0;
    if (ppppppiVar11 != (int ******)0x0) {
      do {
        local_58[(int)ppppppiVar14] = *(int *******)(param_1 + 0x2c);
        ppppppiVar14 = (int ******)((int)ppppppiVar14 + 1);
      } while (ppppppiVar14 < ppppppiVar11);
    }
    uVar19 = FUN_00773063(local_5c,ppppppiVar11);
    if ((int)uVar19 < 0) goto LAB_0077bc80;
    iVar16 = FUN_00773e3b(param_2,(uint)ppppppiVar11 & 0xffffff | 0x25000000,local_5c,local_54[0],
                          (int)((ulonglong)uVar19 >> 0x20),0);
    if (iVar16 < 0) goto LAB_0077bc80;
    uVar20 = 0;
    pppppppiVar18 = (int *******)((uint)ppppppiVar11 & 0xffffff | 0x34000000);
    pppppppiVar9 = (int *******)0x0;
    pppppppiVar15 = (int *******)local_5c;
    goto LAB_0077b3b5;
  case 10:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      lVar21 = CONCAT44(local_8,param_3);
      pppppppiVar9 = (int *******)0x0;
      goto LAB_0077aaa9;
    }
    break;
  case 0xb:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      fVar3 = (float10)log2((float10)_DAT_0086f990);
      uVar8 = FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,
                           (double)((float10)_DAT_0085a310 / ((float10)0.6931471805599453 * fVar3)))
      ;
      local_58 = (int *******)
                 FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,_DAT_00859060);
      local_c = operator_new((int)local_8 * 0x1c);
      if (local_c == (int *******)0x0) goto LAB_0077bc80;
      uVar12 = 0;
      pppppppiVar9 = local_c;
      do {
        local_2c[uVar12] = (int ******)pppppppiVar9;
        uVar12 = uVar12 + 1;
        pppppppiVar9 = pppppppiVar9 + (int)local_8;
      } while (uVar12 < 7);
      if (local_8 != (int *******)0x0) {
        pppppppiVar9 = (int *******)local_14;
        pppppppiVar15 = local_8;
        do {
          *(undefined4 *)(((int)local_18 - (int)local_14) + (int)pppppppiVar9) = uVar8;
          *pppppppiVar9 = (int ******)local_58;
          pppppppiVar9 = pppppppiVar9 + 1;
          pppppppiVar15 = (int *******)((int)pppppppiVar15 + -1);
        } while (pppppppiVar15 != (int *******)0x0);
      }
      iVar16 = FUN_00773063(local_2c[0],local_8);
      if (((((iVar16 < 0) || (iVar16 = FUN_00773063(local_2c[1],local_8), iVar16 < 0)) ||
           (iVar16 = FUN_00773063(local_24,local_8), iVar16 < 0)) ||
          ((iVar16 = FUN_00773063(local_20,local_8), iVar16 < 0 ||
           (iVar16 = FUN_00773063(local_1c,local_8), iVar16 < 0)))) ||
         (iVar16 = FUN_00773063(param_3,local_8), iVar16 < 0)) goto LAB_0077bc80;
      uVar12 = (uint)local_8 & 0xffffff;
      uVar4 = (undefined3)local_8;
      local_8 = (int *******)CONCAT13(0x25,(undefined3)local_8);
      iVar16 = FUN_00773e3b(param_2,local_8,local_2c[0],local_54[0],local_18,0);
      if (iVar16 < 0) goto LAB_0077bc80;
      local_3c = (int *******)CONCAT13(0x14,uVar4);
      iVar16 = FUN_00773e3b(param_2,local_3c,local_2c[1],local_2c[0],0,4);
      if (((iVar16 < 0) ||
          (iVar16 = FUN_00773e3b(param_2,uVar12 | 0x11000000,local_24,local_2c[0],0,0), iVar16 < 0))
         || ((iVar16 = FUN_00773e3b(param_2,local_3c,local_20,local_24,0,4), iVar16 < 0 ||
             (iVar16 = FUN_00773e3b(param_2,uVar12 | 0x24000000,local_1c,local_2c[1],local_20,4),
             iVar16 < 0)))) goto LAB_0077bc80;
      uVar8 = 4;
LAB_0077ace6:
      uVar20 = CONCAT44(uVar8,local_14);
      pppppppiVar18 = local_8;
      pppppppiVar9 = param_3;
      pppppppiVar15 = local_1c;
      goto LAB_0077b3b5;
    }
    break;
  case 0xc:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      local_60 = (int *******)local_54[0][1];
      local_5c = local_54[0][2];
      local_58 = (int *******)*local_54[0];
      local_c8 = local_54[1][2];
      local_c4 = (int *******)*local_54[1];
      local_c0 = local_54[1][1];
      local_144 = local_54[0][2];
      local_140 = *local_54[0];
      local_13c = local_54[0][1];
      local_7c = local_54[1][1];
      local_78 = local_54[1][2];
      local_74 = *local_54[1];
      local_1c = (int *******)0xffffffff;
      local_18 = (int *******)0xffffffff;
      local_14 = (int **)0xffffffff;
      local_150 = 0xffffffff;
      uStack_14c = 0xffffffff;
      uStack_148 = 0xffffffff;
      local_b8 = (int *)0xffffffff;
      local_b4 = (int ******)0xffffffff;
      local_b0 = (int ******)0xffffffff;
      *param_3 = (int ******)0xffffffff;
      param_3[1] = (int ******)0xffffffff;
      param_3[2] = (int ******)0xffffffff;
      pppppppiVar18 = (int *******)((uint)local_8 & 0xffffff);
      local_8 = (int *******)CONCAT13(0x25,(undefined3)local_8);
      iVar16 = FUN_00773e3b(param_2,local_8,&local_1c,&local_60,&local_c8,0);
      if (((iVar16 < 0) ||
          (iVar16 = FUN_00773e3b(param_2,local_8,&local_150,&local_144,&local_7c,0), iVar16 < 0)) ||
         (iVar16 = FUN_00773e3b(param_2,(uint)pppppppiVar18 | 0x11000000,&local_b8,&local_150,0,0),
         iVar16 < 0)) goto LAB_0077bc80;
      uVar20 = ZEXT48(&local_b8);
      pppppppiVar15 = (int *******)&local_1c;
      goto LAB_0077a5d2;
    }
    break;
  case 0xd:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = 0;
      pppppppiVar18 = (int *******)((uint)local_8 & 0xffffff | 0x1c000000);
      pppppppiVar9 = param_3;
      pppppppiVar15 = local_54[0];
      goto LAB_0077b3b5;
    }
    break;
  case 0xe:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = 0;
      pppppppiVar18 = (int *******)((uint)local_8 & 0xffffff | 0x1d000000);
      pppppppiVar9 = param_3;
      pppppppiVar15 = local_54[0];
      goto LAB_0077b3b5;
    }
    break;
  case 0xf:
    uVar19 = _DAT_0087aa30;
    goto joined_r0x00779fe5;
  case 0x10:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      if (local_bc != (int ******)0x1) {
        ppppppiVar11 = (int ******)local_20[5];
        if (ppppppiVar11 == (int ******)0x2) {
          local_c8 = (int ******)0xffffffff;
          local_c4 = (int *******)0xffffffff;
          local_c0 = (int ******)0xffffffff;
          iVar16 = FUN_00773063(param_3,local_8);
          if (iVar16 < 0) goto LAB_0077bc80;
          local_78 = *local_54[0];
          local_5c = local_54[0][3];
          local_74 = local_54[0][1];
          local_58 = (int *******)local_54[0][2];
          iVar16 = FUN_00773e3b(param_2,0x25000002,&local_c8,&local_78,&local_5c,0);
          if ((iVar16 < 0) ||
             (iVar16 = FUN_00773e3b(param_2,0x11000001,&local_c0,&local_c4,0,0), iVar16 < 0))
          goto LAB_0077bc80;
          uVar20 = ZEXT48(&local_c0);
          pppppppiVar15 = &local_c8;
          goto LAB_00779e06;
        }
        if (ppppppiVar11 == (int ******)0x3) {
          local_150 = 0xffffffff;
          uStack_14c = 0xffffffff;
          uStack_148 = 0xffffffff;
          local_1c = (int *******)0xffffffff;
          local_18 = (int *******)0xffffffff;
          local_14 = (int **)0xffffffff;
          local_b8 = (int *)0xffffffff;
          local_b4 = (int ******)0xffffffff;
          local_b0 = (int ******)0xffffffff;
          local_144 = (int ******)0xffffffff;
          local_140 = (int ******)0xffffffff;
          local_13c = (int ******)0xffffffff;
          iVar16 = FUN_00773063(param_3,local_8);
          pppppppiVar9 = local_54[0];
          if (iVar16 < 0) goto LAB_0077bc80;
          local_60 = (int *******)local_54[0][4];
          local_5c = local_54[0][7];
          local_58 = (int *******)local_54[0][1];
          local_7c = local_54[0][8];
          local_78 = local_54[0][2];
          local_74 = local_54[0][5];
          iVar16 = FUN_00773e3b(param_2,0x25000003,&local_150,&local_60,&local_7c,0);
          if (iVar16 < 0) goto LAB_0077bc80;
          local_60 = (int *******)pppppppiVar9[7];
          local_5c = pppppppiVar9[1];
          local_58 = (int *******)pppppppiVar9[4];
          local_7c = pppppppiVar9[5];
          local_78 = pppppppiVar9[8];
          local_74 = pppppppiVar9[2];
          iVar16 = FUN_00773e3b(param_2,0x25000003,&local_1c,&local_60,&local_7c,0);
          if (((iVar16 < 0) ||
              (iVar16 = FUN_00773e3b(param_2,0x11000003,&local_b8,&local_1c,0,0), iVar16 < 0)) ||
             (iVar16 = FUN_00773e3b(param_2,0x24000003,&local_144,&local_150,&local_b8,0),
             iVar16 < 0)) goto LAB_0077bc80;
          local_60 = (int *******)*pppppppiVar9;
          local_5c = pppppppiVar9[3];
          local_58 = (int *******)pppppppiVar9[6];
          uVar20 = ZEXT48(&local_60);
          pppppppiVar18 = (int *******)0x30000003;
          pppppppiVar9 = param_3;
          pppppppiVar15 = &local_144;
        }
        else {
          if (ppppppiVar11 != (int ******)0x4) break;
          uVar19 = CONCAT44(local_8,param_3);
          iVar6 = 0xc;
          puVar10 = local_1b8;
          for (iVar16 = iVar6; iVar16 != 0; iVar16 = iVar16 + -1) {
            *puVar10 = 0xffffffff;
            puVar10 = puVar10 + 1;
          }
          puVar10 = local_1e8;
          for (iVar16 = iVar6; iVar16 != 0; iVar16 = iVar16 + -1) {
            *puVar10 = 0xffffffff;
            puVar10 = puVar10 + 1;
          }
          puVar10 = local_188;
          for (iVar16 = iVar6; iVar16 != 0; iVar16 = iVar16 + -1) {
            *puVar10 = 0xffffffff;
            puVar10 = puVar10 + 1;
          }
          piVar17 = local_100 + 2;
          for (; iVar6 != 0; iVar6 = iVar6 + -1) {
            *piVar17 = -1;
            piVar17 = piVar17 + 1;
          }
          local_20 = (int ******)0xffffffff;
          local_1c = (int *******)0xffffffff;
          local_18 = (int *******)0xffffffff;
          local_14 = (int **)0xffffffff;
          iVar16 = FUN_00773063(uVar19);
          pppppppiVar9 = local_54[0];
          if (iVar16 < 0) goto LAB_0077bc80;
          local_ac = local_54[0][10];
          local_a8 = local_54[0][0xe];
          local_a4[0] = local_54[0][6];
          local_a4[1] = local_54[0][0xe];
          local_a4[2] = local_54[0][2];
          local_a4[3] = local_54[0][10];
          local_a4[4] = local_54[0][6];
          local_a4[5] = local_54[0][0xe];
          local_a4[6] = local_54[0][2];
          local_a4[7] = local_54[0][10];
          local_a4[8] = local_54[0][2];
          local_80 = (int *******)local_54[0][6];
          local_138 = local_54[0][0xf];
          local_134 = local_54[0][7];
          local_130 = local_54[0][0xb];
          local_12c = local_54[0][0xb];
          local_128 = local_54[0][0xf];
          local_124 = local_54[0][3];
          local_120 = local_54[0][0xf];
          local_11c = local_54[0][3];
          local_118 = local_54[0][7];
          local_114 = local_54[0][7];
          local_110 = local_54[0][0xb];
          local_10c = local_54[0][3];
          iVar16 = FUN_00773e3b(param_2,0x25000003,local_1b8,&local_ac,&local_138,0);
          if ((((iVar16 < 0) ||
               (iVar16 = FUN_00773e3b(param_2,0x25000003,local_1ac,local_a4 + 1,&local_12c,0),
               iVar16 < 0)) ||
              (iVar16 = FUN_00773e3b(param_2,0x25000003,local_1a0,local_a4 + 4,&local_120,0),
              iVar16 < 0)) ||
             (iVar16 = FUN_00773e3b(param_2,0x25000003,local_194,local_a4 + 7,&local_114,0),
             iVar16 < 0)) goto LAB_0077bc80;
          local_ac = pppppppiVar9[0xe];
          local_a8 = pppppppiVar9[6];
          local_a4[0] = pppppppiVar9[10];
          local_a4[1] = pppppppiVar9[10];
          local_a4[2] = pppppppiVar9[0xe];
          local_a4[3] = pppppppiVar9[2];
          local_a4[4] = pppppppiVar9[0xe];
          local_a4[5] = pppppppiVar9[2];
          local_a4[6] = pppppppiVar9[6];
          local_a4[7] = pppppppiVar9[6];
          local_a4[8] = pppppppiVar9[10];
          local_80 = (int *******)pppppppiVar9[2];
          local_138 = pppppppiVar9[0xb];
          local_134 = pppppppiVar9[0xf];
          local_130 = pppppppiVar9[7];
          local_12c = pppppppiVar9[0xf];
          local_128 = pppppppiVar9[3];
          local_124 = pppppppiVar9[0xb];
          local_120 = pppppppiVar9[7];
          local_11c = pppppppiVar9[0xf];
          local_118 = pppppppiVar9[3];
          local_114 = pppppppiVar9[0xb];
          local_110 = pppppppiVar9[3];
          local_10c = pppppppiVar9[7];
          iVar16 = FUN_00773e3b(param_2,0x25000003,local_1e8,&local_ac,&local_138,0);
          if (((((iVar16 < 0) ||
                (iVar16 = FUN_00773e3b(param_2,0x25000003,local_1dc,local_a4 + 1,&local_12c,0),
                iVar16 < 0)) ||
               ((iVar16 = FUN_00773e3b(param_2,0x25000003,local_1d0,local_a4 + 4,&local_120,0),
                iVar16 < 0 ||
                ((iVar16 = FUN_00773e3b(param_2,0x25000003,local_1c4,local_a4 + 7,&local_114,0),
                 iVar16 < 0 ||
                 (iVar16 = FUN_00773e3b(param_2,0x11000003,local_188,local_1e8,0,0), iVar16 < 0)))))
               ) || (iVar16 = FUN_00773e3b(param_2,0x11000003,local_17c,local_1dc,0,0), iVar16 < 0))
             || ((((iVar16 = FUN_00773e3b(param_2,0x11000003,local_170,local_1d0,0,0), iVar16 < 0 ||
                   (iVar16 = FUN_00773e3b(param_2,0x11000003,local_164,local_1c4,0,0), iVar16 < 0))
                  || (iVar16 = FUN_00773e3b(param_2,0x24000003,local_100 + 2,local_1b8,local_188,0),
                     iVar16 < 0)) ||
                 (((iVar16 = FUN_00773e3b(param_2,0x24000003,local_100 + 5,local_1ac,local_17c,0),
                   iVar16 < 0 ||
                   (iVar16 = FUN_00773e3b(param_2,0x24000003,&local_e0,local_1a0,local_170,0),
                   iVar16 < 0)) ||
                  (iVar16 = FUN_00773e3b(param_2,0x24000003,&local_d4,local_194,local_164,0),
                  iVar16 < 0)))))) goto LAB_0077bc80;
          local_ac = pppppppiVar9[5];
          local_a8 = pppppppiVar9[9];
          local_a4[0] = pppppppiVar9[0xd];
          local_a4[1] = pppppppiVar9[1];
          local_a4[2] = pppppppiVar9[9];
          local_a4[3] = pppppppiVar9[0xd];
          local_a4[4] = pppppppiVar9[1];
          local_a4[5] = pppppppiVar9[5];
          local_a4[6] = pppppppiVar9[0xd];
          local_a4[7] = pppppppiVar9[1];
          local_a4[8] = pppppppiVar9[5];
          local_80 = (int *******)pppppppiVar9[9];
          iVar16 = FUN_00773e3b(param_2,0x30000003,&local_20,local_100 + 2,&local_ac,0);
          if (((iVar16 < 0) ||
              (iVar16 = FUN_00773e3b(param_2,0x30000003,&local_1c,local_100 + 5,local_a4 + 1,0),
              iVar16 < 0)) ||
             ((iVar16 = FUN_00773e3b(param_2,0x30000003,&local_18,&local_e0,local_a4 + 4,0),
              iVar16 < 0 ||
              (iVar16 = FUN_00773e3b(param_2,0x30000003,&local_14,&local_d4,local_a4 + 7,0),
              iVar16 < 0)))) goto LAB_0077bc80;
          local_ac = *pppppppiVar9;
          local_a8 = pppppppiVar9[4];
          local_a4[0] = pppppppiVar9[8];
          local_a4[1] = pppppppiVar9[0xc];
          uVar20 = ZEXT48(&local_ac);
          pppppppiVar18 = (int *******)0x30000004;
          pppppppiVar9 = param_3;
          pppppppiVar15 = &local_20;
        }
        goto LAB_0077b3b5;
      }
      *param_3 = *local_54[0];
    }
    break;
  case 0x11:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      local_c = operator_new((int)local_bc * 8 + 4);
      if (local_c == (int *******)0x0) goto LAB_0077bc80;
      uVar12 = 0;
      pppppppiVar9 = local_c;
      do {
        (&local_60)[uVar12] = pppppppiVar9;
        uVar12 = uVar12 + 1;
        pppppppiVar9 = pppppppiVar9 + (int)ppppppiVar11;
      } while (uVar12 < 3);
      iVar16 = FUN_00773063(local_60,ppppppiVar11);
      if ((iVar16 < 0) || (iVar16 = FUN_00773063(local_5c,ppppppiVar11), iVar16 < 0))
      goto LAB_0077bc80;
      *local_58 = (int ******)0xffffffff;
      *param_3 = (int ******)0xffffffff;
      uVar12 = (uint)ppppppiVar11 & 0xffffff;
      iVar16 = FUN_00773e3b(param_2,uVar12 | 0x11000000,local_60,local_54[1],0,0);
      if ((iVar16 < 0) ||
         (iVar16 = FUN_00773e3b(param_2,uVar12 | 0x24000000,local_5c,local_54[0],local_60,0),
         iVar16 < 0)) goto LAB_0077bc80;
      iVar16 = FUN_00773e3b(param_2,uVar12 | 0x30000000,local_58,local_5c,local_5c,4);
      pppppppiVar15 = local_58;
joined_r0x0077afba:
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = 0x400000000;
      pppppppiVar18 = (int *******)((uint)local_8 & 0xffffff | 0x16000000);
      pppppppiVar9 = param_3;
      goto LAB_0077b3b5;
    }
    break;
  case 0x12:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_54[1]);
      pppppppiVar18 = (int *******)((uint)local_bc & 0xffffff | 0x30000000);
      pppppppiVar9 = param_3;
      pppppppiVar15 = local_54[0];
      goto LAB_0077b3b5;
    }
    break;
  case 0x13:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    if (param_3 == (int *******)0x0) break;
    local_30 = *(int ********)(param_1 + 0x20);
    local_2c[0] = local_54[0][1];
    local_2c[1] = local_54[0][2];
    local_1c = (int *******)local_54[1][1];
    local_14 = (int **)local_54[1][3];
    local_24 = local_30;
    local_20 = (int ******)local_30;
    local_18 = local_30;
    iVar16 = FUN_00773063(param_3,local_8);
    if (iVar16 < 0) goto LAB_0077bc80;
    uVar20 = ZEXT48(&local_20);
    pppppppiVar15 = (int *******)&local_30;
    goto LAB_0077a055;
  case 0x14:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      fVar3 = (float10)log2((float10)_DAT_0086f990);
      pppppiVar7 = (int *****)
                   FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,
                                (double)((float10)_DAT_0085a310 /
                                        ((float10)0.6931471805599453 * fVar3)));
      local_c = operator_new((int)local_8 * 0xc);
      if (local_c == (int *******)0x0) goto LAB_0077bc80;
      uVar12 = 0;
      pppppppiVar9 = local_c;
      do {
        (&local_c8)[uVar12] = (int ******)pppppppiVar9;
        uVar12 = uVar12 + 1;
        pppppppiVar9 = pppppppiVar9 + (int)local_8;
      } while (uVar12 < 3);
      pppppppiVar9 = local_8;
      ppppppiVar11 = local_c8;
      if (local_8 != (int *******)0x0) {
        for (; pppppppiVar9 != (int *******)0x0;
            pppppppiVar9 = (int *******)((int)pppppppiVar9 + -1)) {
          *ppppppiVar11 = pppppiVar7;
          ppppppiVar11 = ppppppiVar11 + 1;
        }
      }
      iVar16 = FUN_00773063(local_c4,local_8);
      if ((iVar16 < 0) || (iVar16 = FUN_00773063(param_3,local_8), iVar16 < 0)) goto LAB_0077bc80;
      uVar12 = (uint)local_8 & 0xffffff;
      iVar16 = FUN_00773e3b(param_2,uVar12 | 0x25000000,local_c4,local_54[0],local_c8,0);
      pppppppiVar15 = local_c4;
joined_r0x00779fca:
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = 0x400000000;
      pppppppiVar18 = (int *******)(uVar12 | 0x14000000);
      pppppppiVar9 = param_3;
      goto LAB_0077b3b5;
    }
    break;
  case 0x15:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = 0x400000000;
      pppppppiVar18 = (int *******)((uint)local_8 & 0xffffff | 0x14000000);
      pppppppiVar9 = param_3;
      pppppppiVar15 = local_54[0];
      goto LAB_0077b3b5;
    }
    break;
  case 0x16:
    if ((((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0)) ||
       (local_18 == (int *******)0x0)) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      uVar12 = (uint)local_8 & 0xffffff;
      local_38 = (int *******)0xffffffff;
      local_64 = (int *******)0xffffffff;
      iVar16 = FUN_00773e3b(param_2,uVar12 | 0x30000000,&local_38,local_54[1],local_54[2],0);
      if (((iVar16 < 0) ||
          (iVar16 = FUN_00773e3b(param_2,0x23000001,&local_64,&local_38,param_1 + 0x24,0x2000017),
          pppppppiVar9 = local_8, iVar16 < 0)) ||
         (local_c = operator_new((int)local_8 << 4), local_c == (int *******)0x0))
      goto LAB_0077bc80;
      uVar13 = 0;
      pppppppiVar15 = local_c;
      do {
        (&local_20)[uVar13] = (int ******)pppppppiVar15;
        uVar13 = uVar13 + 1;
        pppppppiVar15 = pppppppiVar15 + (int)pppppppiVar9;
      } while (uVar13 < 4);
      pppppppiVar15 = (int *******)0x0;
      if (pppppppiVar9 != (int *******)0x0) {
        do {
          local_14[(int)pppppppiVar15] = (int *)local_64;
          pppppppiVar15 = (int *******)((int)pppppppiVar15 + 1);
        } while (pppppppiVar15 < pppppppiVar9);
      }
      iVar16 = FUN_00773063(local_20,pppppppiVar9);
      if ((((iVar16 < 0) || (iVar16 = FUN_00773063(local_1c,local_8), iVar16 < 0)) ||
          (iVar16 = FUN_00773063(local_18,local_8), iVar16 < 0)) ||
         ((iVar16 = FUN_00773063(param_3,local_8), iVar16 < 0 ||
          (iVar16 = FUN_00773e3b(param_2,uVar12 | 0x11000000,local_20,local_54[0],0,0), iVar16 < 0))
         )) goto LAB_0077bc80;
      _local_44 = (int *******)CONCAT13(0x24,uVar4);
      iVar16 = FUN_00773e3b(param_2,_local_44,local_1c,local_20,local_20,0);
      if ((iVar16 < 0) ||
         (iVar16 = FUN_00773e3b(param_2,uVar12 | 0x25000000,local_18,local_1c,local_14,0),
         iVar16 < 0)) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_18);
      pppppppiVar18 = _local_44;
      pppppppiVar9 = param_3;
      pppppppiVar15 = local_54[0];
      goto LAB_0077b3b5;
    }
    break;
  case 0x17:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      local_c = operator_new((int)local_8 << 3);
      if (local_c == (int *******)0x0) goto LAB_0077bc80;
      local_38 = local_c + (int)local_8;
      uVar19 = FUN_00773063(local_c,local_8);
      if ((((int)uVar19 < 0) ||
          (iVar16 = FUN_00773063((int)((ulonglong)uVar19 >> 0x20),local_8), iVar16 < 0)) ||
         (iVar16 = FUN_00773063(param_3,local_8), iVar16 < 0)) goto LAB_0077bc80;
      pppppppiVar18 = (int *******)((uint)local_8 & 0xffffff);
      iVar16 = FUN_00773e3b(param_2,(uint)pppppppiVar18 | 0x13000000,local_c,local_54[0],0,0x14);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar8 = 0x18;
      uVar12 = (uint)pppppppiVar18 | 0x11000000;
      goto LAB_00776faf;
    }
    break;
  case 0x18:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      pppppppiVar9 = operator_new((int)local_8 * 0xc);
      local_c = pppppppiVar9;
      if (pppppppiVar9 == (int *******)0x0) goto LAB_0077bc80;
      uVar12 = 0;
      do {
        (&local_60)[uVar12] = pppppppiVar9;
        uVar12 = uVar12 + 1;
        pppppppiVar9 = pppppppiVar9 + (int)local_8;
      } while (uVar12 < 3);
      uVar12 = 0;
      do {
        uVar19 = FUN_00773063((&local_60)[uVar12],local_8);
        if ((int)uVar19 < 0) goto LAB_0077bc80;
        uVar12 = (int)((ulonglong)uVar19 >> 0x20) + 1;
      } while (uVar12 < 3);
      iVar16 = FUN_00773063(param_3,local_8);
      pppppppiVar9 = local_8;
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar12 = (uint)local_8 & 0xffffff;
      iVar16 = FUN_00773e3b(param_2,uVar12 | 0x12000000,local_60,local_54[1],0,0);
      if (iVar16 < 0) goto LAB_0077bc80;
      local_8._0_3_ = SUB43(pppppppiVar9,0);
      local_8 = (int *******)CONCAT13(0x25,(undefined3)local_8);
      iVar16 = FUN_00773e3b(param_2,local_8,local_5c,local_54[0],local_60,0);
      if ((iVar16 < 0) ||
         (iVar16 = FUN_00773e3b(param_2,uVar12 | 0x13000000,local_58,local_5c,0,4), iVar16 < 0))
      goto LAB_0077bc80;
      uVar20 = ZEXT48(local_58);
      pppppppiVar18 = local_8;
      pppppppiVar9 = param_3;
      pppppppiVar15 = local_54[1];
      goto LAB_0077b3b5;
    }
    break;
  case 0x19:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = 0;
      pppppppiVar18 = (int *******)((uint)local_8 & 0xffffff | 0x13000000);
      pppppppiVar9 = param_3;
      pppppppiVar15 = local_54[0];
      goto LAB_0077b3b5;
    }
    break;
  case 0x1a:
    if ((((int *******)local_20 == (int *******)0x0) ||
        (local_54[1] = operator_new((int)local_8 * 4), local_54[1] == (int *******)0x0)) ||
       (local_c = operator_new((int)local_8 * 0x28), local_c == (int *******)0x0))
    goto LAB_0077bc80;
    uVar12 = 0;
    pppppppiVar9 = local_c;
    do {
      local_a4[uVar12] = (int ******)pppppppiVar9;
      uVar12 = uVar12 + 1;
      pppppppiVar9 = pppppppiVar9 + (int)pppppppiVar15;
    } while (uVar12 < 10);
    iVar16 = FUN_00773063(local_a4[0],local_8);
    if (((((iVar16 < 0) || (iVar16 = FUN_00773063(local_a4[1],local_8), iVar16 < 0)) ||
         ((iVar16 = FUN_00773063(local_a4[2],local_8), iVar16 < 0 ||
          ((iVar16 = FUN_00773063(local_a4[3],local_8), iVar16 < 0 ||
           (iVar16 = FUN_00773063(local_a4[4],local_8), iVar16 < 0)))))) ||
        (iVar16 = FUN_00773063(local_a4[5],local_8), iVar16 < 0)) ||
       (((iVar16 = FUN_00773063(local_a4[6],local_8), iVar16 < 0 ||
         (iVar16 = FUN_00773063(local_a4[7],local_8), iVar16 < 0)) ||
        (iVar16 = FUN_00773063(local_54[1],local_8), iVar16 < 0)))) goto LAB_0077bc80;
    uVar12 = (uint)local_8 & 0xffffff;
    local_10._0_3_ = SUB43(local_8,0);
    uVar4 = (undefined3)local_10;
    local_10 = (int *******)CONCAT13(0x11,(undefined3)local_10);
    iVar16 = FUN_00773e3b(param_2,local_10,local_a4[0],local_54[0],0,0);
    if (((iVar16 < 0) ||
        (iVar16 = FUN_00773e3b(param_2,uVar12 | 0x21000000,local_a4[1],local_a4[0],local_54[0],4),
        iVar16 < 0)) ||
       ((iVar16 = FUN_00773e3b(param_2,local_10,local_a4[2],local_a4[1],0,8), iVar16 < 0 ||
        (iVar16 = FUN_00773e3b(param_2,uVar12 | 0x23000000,local_a4[3],local_a4[2],local_a4[1],
                               0x2000017), iVar16 < 0)))) goto LAB_0077bc80;
    _local_44 = (int *******)CONCAT13(0x24,uVar4);
    iVar16 = FUN_00773e3b(param_2,_local_44,local_a4[4],local_a4[3],local_a4[1],4);
    if ((((iVar16 < 0) ||
         (iVar16 = FUN_00773e3b(param_2,uVar12 | 0x15000000,local_a4[5],local_a4[4],0,0), iVar16 < 0
         )) || (iVar16 = FUN_00773e3b(param_2,local_10,local_a4[6],local_a4[5],0,0), iVar16 < 0)) ||
       ((iVar16 = FUN_00773e3b(param_2,uVar12 | 0x13000000,local_a4[7],local_a4[6],0,0x14),
        iVar16 < 0 ||
        (iVar16 = FUN_00773e3b(param_2,_local_44,local_54[1],local_a4[5],local_a4[7],2), iVar16 < 0)
        ))) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      iVar16 = FUN_00773063(local_a4[8],local_8);
      if ((((iVar16 < 0) || (iVar16 = FUN_00773063(local_80,local_8), iVar16 < 0)) ||
          (iVar16 = FUN_00773063(param_3,local_8), iVar16 < 0)) ||
         (iVar16 = FUN_00773e3b(param_2,uVar12 | 0x14000000,local_a4[8],local_54[1],0,4), iVar16 < 0
         )) goto LAB_0077bc80;
      iVar16 = FUN_00773e3b(param_2,uVar12 | 0x12000000,local_80,local_a4[8],0,4);
      pppppppiVar15 = local_54[0];
      pppppppiVar9 = local_80;
      goto joined_r0x00779ed9;
    }
    break;
  case 0x1b:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      local_c = operator_new((int)local_8 * 0x18);
      if (local_c == (int *******)0x0) goto LAB_0077bc80;
      uVar12 = 0;
      pppppppiVar9 = local_c;
      do {
        local_2c[uVar12 + 1] = (int ******)pppppppiVar9;
        uVar12 = uVar12 + 1;
        pppppppiVar9 = pppppppiVar9 + (int)local_8;
      } while (uVar12 < 6);
      iVar16 = FUN_00773063(local_2c[1],local_8);
      if ((((iVar16 < 0) || (iVar16 = FUN_00773063(local_24,local_8), iVar16 < 0)) ||
          (iVar16 = FUN_00773063(local_20,local_8), iVar16 < 0)) ||
         (((iVar16 = FUN_00773063(local_1c,local_8), iVar16 < 0 ||
           (iVar16 = FUN_00773063(local_18,local_8), iVar16 < 0)) ||
          ((iVar16 = FUN_00773063(local_14,local_8), iVar16 < 0 ||
           (iVar16 = FUN_00773063(param_3,local_8), pppppppiVar9 = local_8, iVar16 < 0))))))
      goto LAB_0077bc80;
      pppppppiVar18 = (int *******)((uint)local_8 & 0xffffff);
      iVar16 = FUN_00773e3b(param_2,(uint)pppppppiVar18 | 0x1c000000,local_2c[1],local_54[0],0,0);
      if (iVar16 < 0) goto LAB_0077bc80;
      local_10._0_3_ = SUB43(pppppppiVar9,0);
      uVar4 = (undefined3)local_10;
      local_10 = (int *******)CONCAT13(0x11,(undefined3)local_10);
      iVar16 = FUN_00773e3b(param_2,local_10,local_24,local_2c[1],0,0);
      if (iVar16 < 0) goto LAB_0077bc80;
      local_40 = (int *******)CONCAT13(0x21,uVar4);
      iVar16 = FUN_00773e3b(param_2,local_40,local_20,local_24,local_2c[1],4);
      if (((iVar16 < 0) ||
          (iVar16 = FUN_00773e3b(param_2,(uint)pppppppiVar18 | 0x1d000000,local_1c,local_54[0],0,0),
          iVar16 < 0)) ||
         ((iVar16 = FUN_00773e3b(param_2,local_10,local_18,local_1c,0,0), iVar16 < 0 ||
          (iVar16 = FUN_00773e3b(param_2,local_40,local_14,local_18,local_1c,4), iVar16 < 0))))
      goto LAB_0077bc80;
      uVar20 = CONCAT44(4,local_14);
      pppppppiVar15 = (int *******)local_20;
      goto LAB_0077a5d2;
    }
    break;
  case 0x1c:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      local_c = operator_new((int)local_8 * 0x14);
      if (local_c == (int *******)0x0) goto LAB_0077bc80;
      uVar12 = 0;
      pppppppiVar9 = local_c;
      do {
        (&local_24)[uVar12] = pppppppiVar9;
        uVar12 = uVar12 + 1;
        pppppppiVar9 = pppppppiVar9 + (int)local_8;
      } while (uVar12 < 5);
      iVar16 = FUN_00773063(local_24,local_8);
      if (((((iVar16 < 0) || (iVar16 = FUN_00773063(local_20,local_8), iVar16 < 0)) ||
           (iVar16 = FUN_00773063(local_1c,local_8), iVar16 < 0)) ||
          ((iVar16 = FUN_00773063(local_18,local_8), iVar16 < 0 ||
           (iVar16 = FUN_00773063(local_14,local_8), iVar16 < 0)))) ||
         (iVar16 = FUN_00773063(param_3,local_8), iVar16 < 0)) goto LAB_0077bc80;
      local_3c = (int *******)((uint)local_8 & 0xffffff);
      local_10 = (int *******)((uint)local_3c | 0x11000000);
      iVar16 = FUN_00773e3b(param_2,local_10,local_24,local_54[0],0,0x40);
      if ((iVar16 < 0) ||
         (iVar16 = FUN_00773e3b(param_2,(uint)local_3c | 0x24000000,local_20,local_54[0],local_24,
                                0x40), iVar16 < 0)) goto LAB_0077bc80;
LAB_00778af3:
      iVar16 = FUN_00773e3b(param_2,local_10,local_1c,local_20,0x4000000000);
      if ((iVar16 < 0) ||
         ((iVar16 = FUN_00773e3b(param_2,(uint)local_3c | 0x21000000,local_18,local_1c,local_20,0x40
                                ), iVar16 < 0 ||
          (iVar16 = FUN_00773e3b(param_2,local_10,local_14,local_18,0,0x40),
          pppppppiVar18 = local_3c, pppppppiVar15 = (int *******)local_14, pppppppiVar9 = local_18,
          iVar16 < 0)))) goto LAB_0077bc80;
LAB_0077b020:
      uVar20 = CONCAT44(0x2000017,pppppppiVar9);
      pppppppiVar18 = (int *******)((uint)pppppppiVar18 | 0x23000000);
      pppppppiVar9 = param_3;
      goto LAB_0077b3b5;
    }
    break;
  case 0x1d:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      local_c = operator_new((int)local_8 << 4);
      if (local_c == (int *******)0x0) goto LAB_0077bc80;
      uVar12 = 0;
      pppppppiVar9 = local_c;
      do {
        (&local_20)[uVar12] = (int ******)pppppppiVar9;
        uVar12 = uVar12 + 1;
        pppppppiVar9 = pppppppiVar9 + (int)local_8;
      } while (uVar12 < 4);
      iVar16 = FUN_00773063(local_20,local_8);
      if (((iVar16 < 0) || (iVar16 = FUN_00773063(local_1c,local_8), iVar16 < 0)) ||
         ((iVar16 = FUN_00773063(local_18,local_8), iVar16 < 0 ||
          ((iVar16 = FUN_00773063(local_14,local_8), iVar16 < 0 ||
           (iVar16 = FUN_00773063(param_3,local_8), iVar16 < 0)))))) goto LAB_0077bc80;
      local_3c = (int *******)((uint)local_8 & 0xffffff);
      iVar16 = FUN_00773e3b(param_2,(uint)local_3c | 0x12000000,local_20,local_54[0],0,0x40);
      if (iVar16 < 0) goto LAB_0077bc80;
      local_10 = (int *******)((uint)local_3c | 0x11000000);
      goto LAB_00778af3;
    }
    break;
  case 0x1e:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      local_c = operator_new((int)local_8 * 0x14);
      if (local_c == (int *******)0x0) goto LAB_0077bc80;
      uVar12 = 0;
      pppppppiVar9 = local_c;
      do {
        (&local_24)[uVar12] = pppppppiVar9;
        uVar12 = uVar12 + 1;
        pppppppiVar9 = pppppppiVar9 + (int)local_8;
      } while (uVar12 < 5);
      iVar16 = FUN_00773063(local_24,local_8);
      if ((((iVar16 < 0) || (iVar16 = FUN_00773063(local_20,local_8), iVar16 < 0)) ||
          ((iVar16 = FUN_00773063(local_1c,local_8), iVar16 < 0 ||
           ((iVar16 = FUN_00773063(local_18,local_8), iVar16 < 0 ||
            (iVar16 = FUN_00773063(local_14,local_8), iVar16 < 0)))))) ||
         (iVar16 = FUN_00773063(param_3,local_8), iVar16 < 0)) goto LAB_0077bc80;
      local_3c = (int *******)((uint)local_8 & 0xffffff);
      local_10 = (int *******)((uint)local_3c | 0x11000000);
      iVar16 = FUN_00773e3b(param_2,local_10,local_24,local_54[0],0,0x40);
      if (((iVar16 < 0) ||
          (iVar16 = FUN_00773e3b(param_2,(uint)local_3c | 0x21000000,local_20,local_54[0],local_24,
                                 0x40), iVar16 < 0)) ||
         (iVar16 = FUN_00773e3b(param_2,local_10,local_1c,local_20,0,0x40), iVar16 < 0))
      goto LAB_0077bc80;
      local_58 = (int *******)((uint)local_3c | 0x23000000);
      iVar16 = FUN_00773e3b(param_2,local_58,local_18,local_20,local_1c,0x2000017);
      if ((iVar16 < 0) ||
         (iVar16 = FUN_00773e3b(param_2,local_10,local_14,local_18,0,0x1a), iVar16 < 0))
      goto LAB_0077bc80;
      uVar20 = CONCAT44(0x2000017,local_18);
      pppppppiVar18 = local_58;
      pppppppiVar9 = param_3;
      pppppppiVar15 = (int *******)local_14;
      goto LAB_0077b3b5;
    }
    break;
  case 0x1f:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      local_c = operator_new((int)local_8 << 2);
      if (((local_c == (int *******)0x0) || (iVar16 = FUN_00773063(local_c,local_8), iVar16 < 0)) ||
         (iVar16 = FUN_00773063(param_3,local_8), iVar16 < 0)) goto LAB_0077bc80;
      uVar12 = (uint)local_8 & 0xffffff;
      iVar16 = FUN_00773e3b(param_2,uVar12 | 0x14000000,local_c,local_54[1],0,4);
      pppppppiVar15 = local_54[0];
      pppppppiVar9 = local_c;
joined_r0x00779ed9:
      local_54[0] = pppppppiVar15;
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = ZEXT48(pppppppiVar9);
      goto LAB_0077b118;
    }
    break;
  case 0x20:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      if (local_bc == (int ******)0x1) {
        param_3 = (int *******)0xffffffff;
        *pppppppiVar9 = (int ******)0xffffffff;
        iVar16 = FUN_00773e3b(param_2,0x11000001,&param_3,local_54[0],0,0);
        if (iVar16 < 0) goto LAB_0077bc80;
        uVar20 = CONCAT44(4,&param_3);
        pppppppiVar18 = (int *******)0x21000001;
        pppppppiVar15 = local_54[0];
      }
      else {
        param_3 = (int *******)0xffffffff;
        uVar19 = FUN_00773063(pppppppiVar9,local_8);
        if (((int)uVar19 < 0) ||
           (iVar16 = FUN_00773e3b(param_2,(uint)((ulonglong)uVar19 >> 0x20) & 0xffffff | 0x30000000,
                                  &param_3,local_54[0],local_54[0],4), iVar16 < 0))
        goto LAB_0077bc80;
        uVar20 = 0x400000000;
        pppppppiVar18 = (int *******)0x16000001;
        pppppppiVar15 = (int *******)&param_3;
      }
      goto LAB_0077b3b5;
    }
    break;
  case 0x21:
    if ((((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0)) ||
       (local_18 == (int *******)0x0)) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      iVar16 = FUN_00775982(param_2,param_3,local_54[0],local_54[1],local_54[2]);
      goto LAB_0077b3bf;
    }
    break;
  case 0x22:
    if (((((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0)) ||
        (local_18 == (int *******)0x0)) || (local_8 != (int *******)&DAT_00000004))
    goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      if ((*(byte *)(*(int *)(param_1 + 8) + 0x90) & 0x40) == 0) {
        local_c = operator_new(0x20);
        if (local_c == (int *******)0x0) goto LAB_0077bc80;
        uVar12 = 0;
        do {
          (&local_30)[uVar12] = local_c + uVar12;
          uVar12 = uVar12 + 1;
        } while (uVar12 < 8);
        pppppppiVar9 = local_c;
        for (iVar16 = 8; iVar16 != 0; iVar16 = iVar16 + -1) {
          *pppppppiVar9 = (int ******)0xffffffff;
          pppppppiVar9 = pppppppiVar9 + 1;
        }
        *param_3 = (int ******)0xffffffff;
        param_3[1] = (int ******)0xffffffff;
        param_3[2] = (int ******)0xffffffff;
        param_3[3] = (int ******)0xffffffff;
        iVar16 = FUN_00773e3b(param_2,0x11000001,local_30,local_54[0],0,0);
        if (((((iVar16 < 0) ||
              (iVar16 = FUN_00773e3b(param_2,0x22000001,local_2c[0],local_30,local_54[0],0x2000017),
              iVar16 < 0)) ||
             ((iVar16 = FUN_00773e3b(param_2,0x25000001,param_3 + 1,local_2c[0],local_54[0],0),
              iVar16 < 0 ||
              ((iVar16 = FUN_00773e3b(param_2,0x11000001,local_2c[1],local_54[1],0,0), iVar16 < 0 ||
               (iVar16 = FUN_00773e3b(param_2,0x22000001,local_24,local_2c[1],local_54[1],0x2000017)
               , iVar16 < 0)))))) ||
            (iVar16 = FUN_00773e3b(param_2,0x25000001,local_20,local_2c[0],local_24,0x2000017),
            iVar16 < 0)) ||
           ((((iVar16 = FUN_00773e3b(param_2,0x15000001,local_1c,local_54[1],0,0), iVar16 < 0 ||
              (iVar16 = FUN_00773e3b(param_2,0x25000001,local_18,local_54[2],local_1c,0), iVar16 < 0
              )) || (iVar16 = FUN_00773e3b(param_2,0x14000001,local_14,local_18,0,4), iVar16 < 0))
            || ((iVar16 = FUN_00773e3b(param_2,0x25000001,param_3 + 2,local_20,local_14,4),
                iVar16 < 0 ||
                (iVar16 = FUN_00773e3b(param_2,0x10000001,param_3,param_1 + 0x20,0,0x2000017),
                iVar16 < 0)))))) goto LAB_0077bc80;
        uVar20 = 0x200001700000000;
        pppppppiVar18 = (int *******)0x10000001;
        pppppppiVar9 = param_3 + 3;
        pppppppiVar15 = (int *******)(param_1 + 0x20);
      }
      else {
        local_20 = *local_54[0];
        local_1c = (int *******)*local_54[1];
        local_18 = (int *******)*local_54[2];
        local_14 = (int **)*local_54[2];
        *param_3 = (int ******)0xffffffff;
        param_3[1] = (int ******)0xffffffff;
        param_3[2] = (int ******)0xffffffff;
        uVar20 = 0;
        param_3[3] = (int ******)0xffffffff;
        pppppppiVar18 = (int *******)0x33000004;
        pppppppiVar15 = &local_20;
      }
      goto LAB_0077b3b5;
    }
    break;
  case 0x23:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      fVar3 = (float10)log2((float10)_DAT_0086f990);
      ppppppiVar11 = (int ******)
                     FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,
                                  (double)((float10)0.6931471805599453 * fVar3));
      local_c = operator_new((int)local_8 << 3);
      if (local_c == (int *******)0x0) goto LAB_0077bc80;
      uVar12 = 0;
      pppppppiVar9 = local_c;
      do {
        (&local_5c)[uVar12] = (int ******)pppppppiVar9;
        uVar12 = uVar12 + 1;
        pppppppiVar9 = pppppppiVar9 + (int)local_8;
      } while (uVar12 < 2);
LAB_0077914c:
      pppppppiVar9 = local_8;
      pppppppiVar15 = (int *******)local_5c;
      if (local_8 != (int *******)0x0) {
        for (; pppppppiVar9 != (int *******)0x0;
            pppppppiVar9 = (int *******)((int)pppppppiVar9 + -1)) {
          *pppppppiVar15 = ppppppiVar11;
          pppppppiVar15 = pppppppiVar15 + 1;
        }
      }
      iVar16 = FUN_00773063(local_58,local_8);
      if ((iVar16 < 0) || (iVar16 = FUN_00773063(param_3,local_8), iVar16 < 0)) goto LAB_0077bc80;
      uVar12 = (uint)local_8 & 0xffffff;
      iVar16 = FUN_00773e3b(param_2,uVar12 | 0x15000000,local_58,local_54[0],0,0);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_58);
      pppppppiVar15 = (int *******)local_5c;
      goto LAB_0077b118;
    }
    break;
  case 0x24:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      fVar3 = (float10)log2((float10)_DAT_0086f990);
      fVar2 = (float10)log2((float10)_DAT_00859ea8);
      ppppppiVar11 = (int ******)
                     FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,
                                  (double)(((float10)0.6931471805599453 * fVar3) /
                                          ((float10)0.6931471805599453 * fVar2)));
      local_c = operator_new((int)local_8 << 3);
      if (local_c == (int *******)0x0) goto LAB_0077bc80;
      uVar12 = 0;
      pppppppiVar9 = local_c;
      do {
        (&local_5c)[uVar12] = (int ******)pppppppiVar9;
        uVar12 = uVar12 + 1;
        pppppppiVar9 = pppppppiVar9 + (int)local_8;
      } while (uVar12 < 2);
      goto LAB_0077914c;
    }
    break;
  case 0x25:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = 0;
      pppppppiVar18 = (int *******)((uint)local_8 & 0xffffff | 0x15000000);
      pppppppiVar9 = param_3;
      pppppppiVar15 = local_54[0];
      goto LAB_0077b3b5;
    }
    break;
  case 0x26:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_54[1]);
      pppppppiVar18 = (int *******)((uint)local_8 & 0xffffff | 0x21000000);
      pppppppiVar9 = param_3;
      pppppppiVar15 = local_54[0];
      goto LAB_0077b3b5;
    }
    break;
  case 0x27:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_54[1]);
      pppppppiVar18 = (int *******)((uint)local_8 & 0xffffff | 0x20000000);
      pppppppiVar9 = param_3;
      pppppppiVar15 = local_54[0];
      goto LAB_0077b3b5;
    }
    break;
  case 0x28:
    if ((((int *******)local_20 == (int *******)0x0) ||
        (local_54[1] = operator_new((int)local_8 * 4), local_54[1] == (int *******)0x0)) ||
       (local_c = operator_new((int)local_8 * 0x24), local_c == (int *******)0x0))
    goto LAB_0077bc80;
    uVar12 = 0;
    pppppppiVar9 = local_c;
    do {
      (&local_34)[uVar12] = (int *)pppppppiVar9;
      uVar12 = uVar12 + 1;
      pppppppiVar9 = pppppppiVar9 + (int)pppppppiVar15;
    } while (uVar12 < 9);
    iVar16 = FUN_00773063(local_34,local_8);
    if ((((iVar16 < 0) || (iVar16 = FUN_00773063(local_30,local_8), iVar16 < 0)) ||
        ((iVar16 = FUN_00773063(local_2c[0],local_8), iVar16 < 0 ||
         ((iVar16 = FUN_00773063(local_2c[1],local_8), iVar16 < 0 ||
          (iVar16 = FUN_00773063(local_24,local_8), iVar16 < 0)))))) ||
       ((iVar16 = FUN_00773063(local_20,local_8), iVar16 < 0 ||
        (((iVar16 = FUN_00773063(local_1c,local_8), iVar16 < 0 ||
          (iVar16 = FUN_00773063(local_18,local_8), iVar16 < 0)) ||
         (iVar16 = FUN_00773063(local_54[1],local_8), pppppppiVar9 = local_8, iVar16 < 0))))))
    goto LAB_0077bc80;
    pppppppiVar15 = (int *******)((uint)local_8 & 0xffffff);
    local_3c = pppppppiVar15;
    iVar16 = FUN_00773e3b(param_2,(uint)pppppppiVar15 | 0x13000000,local_34,local_54[0],0,0x14);
    if (iVar16 < 0) goto LAB_0077bc80;
    local_10._0_3_ = SUB43(pppppppiVar9,0);
    local_10 = (int *******)CONCAT13(0x11,(undefined3)local_10);
    iVar16 = FUN_00773e3b(param_2,local_10,local_30,local_34,0,0x18);
    if (iVar16 < 0) goto LAB_0077bc80;
    _local_44 = (int *******)((uint)pppppppiVar15 | 0x24000000);
    iVar16 = FUN_00773e3b(param_2,_local_44,local_2c[0],local_30,local_54[0],2);
    if ((iVar16 < 0) ||
       (iVar16 = FUN_00773e3b(param_2,local_10,local_2c[1],local_54[0],0,0), iVar16 < 0))
    goto LAB_0077bc80;
    local_38 = (int *******)((uint)local_3c | 0x22000000);
    iVar16 = FUN_00773e3b(param_2,local_38,local_24,local_54[0],local_2c[1],0x2000017);
    if ((((iVar16 < 0) ||
         ((iVar16 = FUN_00773e3b(param_2,local_10,local_20,local_34,0,0), iVar16 < 0 ||
          (iVar16 = FUN_00773e3b(param_2,local_38,local_1c,local_20,local_34,0x2000017), iVar16 < 0)
          ))) || (iVar16 = FUN_00773e3b(param_2,(uint)local_3c | 0x25000000,local_18,local_24,
                                        local_1c,0x2000017), iVar16 < 0)) ||
       (iVar16 = FUN_00773e3b(param_2,_local_44,local_54[1],local_2c[0],local_18,2), iVar16 < 0))
    goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      iVar16 = FUN_00773063(local_14,local_8);
      if (((iVar16 < 0) || (iVar16 = FUN_00773063(param_3,local_8), iVar16 < 0)) ||
         (iVar16 = FUN_00773e3b(param_2,local_10,local_14,local_54[1],0,2), iVar16 < 0))
      goto LAB_0077bc80;
      uVar20 = CONCAT44(0x10,local_14);
      pppppppiVar18 = _local_44;
      pppppppiVar9 = param_3;
      pppppppiVar15 = local_54[0];
      goto LAB_0077b3b5;
    }
    break;
  case 0x29:
  case 0x2a:
  case 0x2b:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      local_c = operator_new((int)local_8 << 2);
      if (local_c == (int *******)0x0) goto LAB_0077bc80;
      pppppppiVar9 = (int *******)0x0;
      if (local_8 != (int *******)0x0) {
        do {
          local_c[(int)pppppppiVar9] = *local_54[0];
          pppppppiVar9 = (int *******)((int)pppppppiVar9 + 1);
        } while (pppppppiVar9 < local_8);
      }
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_54[1]);
      pppppppiVar15 = local_c;
      goto LAB_0077a055;
    }
    break;
  case 0x2c:
  case 0x2f:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    if (param_3 == (int *******)0x0) break;
    local_c = operator_new((int)local_8 << 2);
    if (local_c == (int *******)0x0) goto LAB_0077bc80;
    pppppppiVar9 = (int *******)0x0;
    if (local_8 != (int *******)0x0) {
      do {
        local_c[(int)pppppppiVar9] = *local_54[1];
        pppppppiVar9 = (int *******)((int)pppppppiVar9 + 1);
      } while (pppppppiVar9 < local_8);
    }
    goto LAB_0077a036;
  case 0x2d:
  case 0x2e:
  case 0x30:
  case 0x31:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    if (param_3 == (int *******)0x0) break;
    pppppppiVar9 = (int *******)local_20[4];
    local_58 = pppppppiVar9;
    if ((pppppppiVar9 == (int *******)0x0) || (pppppppiVar9[1] != (int ******)0x8))
    goto LAB_0077bc80;
    if (pppppppiVar9[4] != (int ******)0x1) {
      FUN_0078283c(2,pppppppiVar9[5],pppppppiVar9[6],pppppppiVar9[7],0x400);
      iVar16 = FUN_00776527(&local_12c,local_54[0],local_bc);
      if (-1 < iVar16) {
        local_10 = (int *******)pppppppiVar9[6];
        local_3c = (int *******)pppppppiVar9[7];
        FUN_00782878();
        goto LAB_0077976b;
      }
LAB_007797e1:
      FUN_00782878();
      goto LAB_0077bc80;
    }
    iVar16 = FUN_00776527(pppppppiVar9,local_54[0],local_bc);
    if (iVar16 < 0) goto LAB_0077bc80;
    local_10 = (int *******)pppppppiVar9[6];
    local_3c = (int *******)pppppppiVar9[7];
LAB_0077976b:
    ppppppiVar11 = local_1c[4];
    if ((ppppppiVar11 == (int ******)0x0) || (ppppppiVar11[1] != (int *****)0x8)) goto LAB_0077bc80;
    if (ppppppiVar11[4] == (int *****)0x1) {
      iVar16 = FUN_00776527(ppppppiVar11,local_54[1],local_b8);
      if (iVar16 < 0) goto LAB_0077bc80;
      local_40 = (int *******)ppppppiVar11[7];
      pppppppiVar9 = (int *******)ppppppiVar11[6];
      _local_44 = pppppppiVar9;
    }
    else {
      FUN_0078283c(2,ppppppiVar11[5],ppppppiVar11[6],ppppppiVar11[7],0x800);
      iVar16 = FUN_00776527(local_a4 + 1,local_54[1],local_b8);
      if (iVar16 < 0) goto LAB_007797e1;
      local_40 = (int *******)ppppppiVar11[6];
      pppppppiVar9 = (int *******)ppppppiVar11[7];
      _local_44 = pppppppiVar9;
      FUN_00782878();
    }
    if ((local_3c != local_40) || (local_8 != (int *******)((int)pppppppiVar9 * (int)local_10)))
    goto LAB_0077bc80;
    iVar16 = FUN_00773877(local_54[0],local_58[4],local_10,local_3c);
    if (iVar16 == 0) {
      local_c = operator_new((int)local_10 * 0x14);
      if (local_c == (int *******)0x0) goto LAB_0077bc80;
      uVar12 = 0;
      pppppppiVar9 = local_c;
      do {
        (&local_24)[uVar12] = pppppppiVar9;
        uVar12 = uVar12 + 1;
        pppppppiVar9 = pppppppiVar9 + (int)local_10;
      } while (uVar12 < 5);
      local_8 = (int *******)0x0;
      if (_local_44 != (int *******)0x0) {
        local_6c = param_3;
        do {
          param_3 = (int *******)0x0;
          if (local_40 != (int *******)0x0) {
            do {
              if (local_10 != (int *******)0x0) {
                local_58 = (int *******)((int)local_3c * 4);
                pppppppiVar9 = local_54[0] + (int)param_3;
                local_38 = local_10;
                pppppppiVar15 = (int *******)local_20;
                do {
                  ppppppiVar11 = *pppppppiVar9;
                  pppppppiVar9 = pppppppiVar9 + (int)local_3c;
                  *(int *******)(((int)local_24 - (int)local_20) + (int)pppppppiVar15) =
                       ppppppiVar11;
                  *pppppppiVar15 = local_54[1][(int)((int)param_3 * (int)_local_44 + (int)local_8)];
                  pppppppiVar15 = pppppppiVar15 + 1;
                  local_38 = (int *******)((int)local_38 + -1);
                } while (local_38 != (int *******)0x0);
              }
              iVar16 = FUN_00773063(local_18,local_10);
              if (iVar16 < 0) goto LAB_0077bc80;
              uVar12 = (uint)local_10 & 0xffffff;
              iVar16 = FUN_00773e3b(param_2,uVar12 | 0x25000000,local_18,local_24,local_20,0);
              if ((iVar16 < 0) ||
                 ((pppppppiVar9 = local_18, param_3 != (int *******)0x0 &&
                  ((iVar16 = FUN_00773063(local_14,local_10), iVar16 < 0 ||
                   (iVar16 = FUN_00773e3b(param_2,uVar12 | 0x24000000,local_14,local_1c,local_18,0),
                   pppppppiVar9 = (int *******)local_14, iVar16 < 0)))))) goto LAB_0077bc80;
              pppppppiVar15 = local_1c;
              for (uVar12 = (uint)local_10 & 0x3fffffff; uVar12 != 0; uVar12 = uVar12 - 1) {
                *pppppppiVar15 = *pppppppiVar9;
                pppppppiVar9 = pppppppiVar9 + 1;
                pppppppiVar15 = pppppppiVar15 + 1;
              }
              param_3 = (int *******)((int)param_3 + 1);
              for (iVar16 = 0; iVar16 != 0; iVar16 = iVar16 + -1) {
                *(undefined1 *)pppppppiVar15 = *(undefined1 *)pppppppiVar9;
                pppppppiVar9 = (int *******)((int)pppppppiVar9 + 1);
                pppppppiVar15 = (int *******)((int)pppppppiVar15 + 1);
              }
            } while (param_3 < local_40);
          }
          pppppppiVar15 = (int *******)0x0;
          pppppppiVar9 = local_6c;
          if (local_10 != (int *******)0x0) {
            do {
              *pppppppiVar9 = local_1c[(int)pppppppiVar15];
              pppppppiVar15 = (int *******)((int)pppppppiVar15 + 1);
              pppppppiVar9 = pppppppiVar9 + (int)_local_44;
            } while (pppppppiVar15 < local_10);
          }
          local_8 = (int *******)((int)local_8 + 1);
          local_6c = local_6c + 1;
        } while (local_8 < _local_44);
      }
    }
    else {
      iVar16 = FUN_0077395f(local_54[1],ppppppiVar11[4],local_40,pppppppiVar9);
      if (iVar16 == 0) {
        local_c = operator_new((int)pppppppiVar9 * 0x14);
        if (local_c == (int *******)0x0) goto LAB_0077bc80;
        uVar12 = 0;
        pppppppiVar9 = local_c;
        do {
          (&local_24)[uVar12] = pppppppiVar9;
          uVar12 = uVar12 + 1;
          pppppppiVar9 = pppppppiVar9 + (int)_local_44;
        } while (uVar12 < 5);
        local_68 = (int *******)0x0;
        if (local_10 != (int *******)0x0) {
          local_38 = (int *******)0x0;
          local_64 = param_3;
          do {
            param_3 = (int *******)0x0;
            if (local_3c != (int *******)0x0) {
              do {
                if (_local_44 != (int *******)0x0) {
                  pppppppiVar9 = local_54[1] + (int)param_3 * (int)_local_44;
                  local_6c = _local_44;
                  pppppppiVar15 = (int *******)local_20;
                  do {
                    *(int *******)(((int)local_24 - (int)local_20) + (int)pppppppiVar15) =
                         local_54[0][(int)((int)local_38 + (int)param_3)];
                    *pppppppiVar15 = *pppppppiVar9;
                    pppppppiVar9 = pppppppiVar9 + 1;
                    pppppppiVar15 = pppppppiVar15 + 1;
                    local_6c = (int *******)((int)local_6c + -1);
                  } while (local_6c != (int *******)0x0);
                }
                iVar16 = FUN_00773063(local_18,_local_44);
                if (iVar16 < 0) goto LAB_0077bc80;
                uVar12 = (uint)_local_44 & 0xffffff;
                iVar16 = FUN_00773e3b(param_2,uVar12 | 0x25000000,local_18,local_24,local_20,0);
                if ((iVar16 < 0) ||
                   ((pppppppiVar9 = local_18, param_3 != (int *******)0x0 &&
                    ((iVar16 = FUN_00773063(local_14,_local_44), iVar16 < 0 ||
                     (iVar16 = FUN_00773e3b(param_2,uVar12 | 0x24000000,local_14,local_1c,local_18,0
                                           ), pppppppiVar9 = (int *******)local_14, iVar16 < 0))))))
                goto LAB_0077bc80;
                pppppppiVar15 = local_1c;
                for (uVar12 = (uint)_local_44 & 0x3fffffff; uVar12 != 0; uVar12 = uVar12 - 1) {
                  *pppppppiVar15 = *pppppppiVar9;
                  pppppppiVar9 = pppppppiVar9 + 1;
                  pppppppiVar15 = pppppppiVar15 + 1;
                }
                param_3 = (int *******)((int)param_3 + 1);
                for (iVar16 = 0; iVar16 != 0; iVar16 = iVar16 + -1) {
                  *(undefined1 *)pppppppiVar15 = *(undefined1 *)pppppppiVar9;
                  pppppppiVar9 = (int *******)((int)pppppppiVar9 + 1);
                  pppppppiVar15 = (int *******)((int)pppppppiVar15 + 1);
                }
              } while (param_3 < local_3c);
            }
            pppppppiVar15 = (int *******)0x0;
            pppppppiVar9 = local_64;
            if (_local_44 != (int *******)0x0) {
              do {
                *pppppppiVar9 = local_1c[(int)pppppppiVar15];
                pppppppiVar15 = (int *******)((int)pppppppiVar15 + 1);
                pppppppiVar9 = pppppppiVar9 + 1;
              } while (pppppppiVar15 < _local_44);
            }
            local_38 = (int *******)((int)local_38 + (int)local_3c);
            local_68 = (int *******)((int)local_68 + 1);
            local_64 = local_64 + (int)_local_44;
          } while (local_68 < local_10);
        }
      }
      else {
        local_c = operator_new((int)local_b8 << 2);
        if (local_c == (int *******)0x0) goto LAB_0077bc80;
        if (local_40 != (int *******)0x0) {
          local_6c = local_54[1];
          local_64 = local_40;
          local_68 = local_c;
          do {
            if (_local_44 != (int *******)0x0) {
              local_38 = _local_44;
              pppppppiVar9 = local_6c;
              pppppppiVar15 = local_68;
              do {
                *pppppppiVar15 = *pppppppiVar9;
                pppppppiVar9 = pppppppiVar9 + 1;
                pppppppiVar15 = pppppppiVar15 + (int)local_40;
                local_38 = (int *******)((int)local_38 + -1);
              } while (local_38 != (int *******)0x0);
              local_38 = (int *******)0x0;
            }
            local_68 = local_68 + 1;
            local_6c = local_6c + (int)_local_44;
            local_64 = (int *******)((int)local_64 + -1);
          } while (local_64 != (int *******)0x0);
        }
        uVar19 = FUN_00773063(param_3,local_8);
        if ((int)uVar19 < 0) goto LAB_0077bc80;
        local_38 = (int *******)0x0;
        if (local_10 != (int *******)0x0) {
          local_70 = (int)_local_44 << 2;
          local_74 = (int ******)((int)local_3c << 2);
          local_8 = local_54[0];
          pppppppiVar9 = _local_44;
          local_64 = (int *******)((ulonglong)uVar19 >> 0x20);
          do {
            local_6c = (int *******)0x0;
            if (pppppppiVar9 != (int *******)0x0) {
              uVar12 = (uint)local_3c & 0xffffff;
              local_58 = (int *******)((int)local_40 << 2);
              param_3 = local_64;
              local_68 = local_c;
              do {
                iVar16 = FUN_00773e3b(param_2,uVar12 | 0x30000000,param_3,local_8,local_68,0);
                if (iVar16 < 0) goto LAB_0077bc80;
                local_68 = (int *******)((int)local_68 + (int)local_58);
                local_6c = (int *******)((int)local_6c + 1);
                param_3 = param_3 + 1;
                pppppppiVar9 = _local_44;
              } while (local_6c < _local_44);
            }
            local_8 = (int *******)((int)local_8 + (int)local_74);
            local_38 = (int *******)((int)local_38 + 1);
            local_64 = (int *******)((int)local_64 + local_70);
          } while (local_38 < local_10);
        }
      }
    }
    break;
  case 0x32:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      *param_3 = (int ******)0xffffffff;
      uVar20 = 0x1000000000;
      pppppppiVar18 = (int *******)((uint)local_bc & 0xffffff | 0x35000000);
      pppppppiVar15 = local_54[0];
      goto LAB_0077b3b5;
    }
    break;
  case 0x33:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      if (local_8 != (int *******)0x1) {
        uVar12 = (uint)local_8 & 0xffffff;
        local_38 = (int *******)0xffffffff;
        local_64 = (int *******)0xffffffff;
        local_68 = (int *******)0xffffffff;
        iVar16 = FUN_00773e3b(param_2,uVar12 | 0x30000000,&local_38,local_54[0],local_54[0],4);
        if (((iVar16 < 0) ||
            (iVar16 = FUN_00773e3b(param_2,0x16000001,&local_64,&local_38,0,4), iVar16 < 0)) ||
           ((iVar16 = FUN_00773e3b(param_2,0x12000001,&local_68,&local_64,0,4), iVar16 < 0 ||
            (local_c = operator_new((int)local_8 << 2), local_c == (int *******)0x0))))
        goto LAB_0077bc80;
        pppppppiVar9 = (int *******)0x0;
        if (local_8 != (int *******)0x0) {
          do {
            local_c[(int)pppppppiVar9] = (int ******)local_68;
            pppppppiVar9 = (int *******)((int)pppppppiVar9 + 1);
          } while (pppppppiVar9 < local_8);
        }
        iVar16 = FUN_00773063(param_3,local_8);
        pppppppiVar15 = local_54[0];
        pppppppiVar9 = local_c;
        goto joined_r0x00779ed9;
      }
      local_c = operator_new(0x10);
      if (local_c == (int *******)0x0) goto LAB_0077bc80;
      uVar12 = 0;
      do {
        (&local_20)[uVar12] = (int ******)(local_c + uVar12);
        uVar12 = uVar12 + 1;
      } while (uVar12 < 4);
      iVar16 = FUN_00773063(local_20,1);
      if (((iVar16 < 0) || (iVar16 = FUN_00773063(local_1c,1), iVar16 < 0)) ||
         (((iVar16 = FUN_00773063(local_18,1), iVar16 < 0 ||
           ((((iVar16 = FUN_00773063(local_14,1), iVar16 < 0 ||
              (iVar16 = FUN_00773063(param_3,1), iVar16 < 0)) ||
             (iVar16 = FUN_00773e3b(param_2,0x11000001,local_20,local_54[0],0,0), iVar16 < 0)) ||
            ((iVar16 = FUN_00773e3b(param_2,0x22000001,local_1c,local_20,local_54[0],0x2000017),
             iVar16 < 0 ||
             (iVar16 = FUN_00773e3b(param_2,0x22000001,local_18,local_54[0],local_20,0x2000017),
             iVar16 < 0)))))) ||
          (iVar16 = FUN_00773e3b(param_2,0x11000001,local_14,local_18,0,0x1a), iVar16 < 0))))
      goto LAB_0077bc80;
      uVar20 = CONCAT44(0x12,local_14);
      pppppppiVar15 = local_1c;
LAB_00779e06:
      pppppppiVar18 = (int *******)0x24000001;
      pppppppiVar9 = param_3;
      goto LAB_0077b3b5;
    }
    break;
  case 0x34:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      local_c = operator_new((int)local_8 << 3);
      if (local_c == (int *******)0x0) goto LAB_0077bc80;
      uVar12 = 0;
      pppppppiVar9 = local_c;
      do {
        (&local_5c)[uVar12] = (int ******)pppppppiVar9;
        uVar12 = uVar12 + 1;
        pppppppiVar9 = pppppppiVar9 + (int)local_8;
      } while (uVar12 < 2);
      iVar16 = FUN_00773063(local_5c,local_8);
      if (((iVar16 < 0) || (iVar16 = FUN_00773063(local_58,local_8), iVar16 < 0)) ||
         (iVar16 = FUN_00773063(param_3,local_8), iVar16 < 0)) goto LAB_0077bc80;
      uVar12 = (uint)local_8 & 0xffffff;
      iVar16 = FUN_00773e3b(param_2,uVar12 | 0x15000000,local_5c,local_54[0],0,0);
      if (iVar16 < 0) goto LAB_0077bc80;
      iVar16 = FUN_00773e3b(param_2,uVar12 | 0x25000000,local_58,local_54[1],local_5c,0);
      pppppppiVar15 = local_58;
      goto joined_r0x00779fca;
    }
    break;
  case 0x35:
    uVar19 = _DAT_0087aa28;
joined_r0x00779fe5:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      ppppppiVar11 = (int ******)
                     FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,uVar19);
      local_c = operator_new((int)local_8 << 2);
      if (local_c == (int *******)0x0) goto LAB_0077bc80;
      pppppppiVar9 = local_8;
      pppppppiVar15 = local_c;
      if (local_8 != (int *******)0x0) {
        for (; pppppppiVar9 != (int *******)0x0;
            pppppppiVar9 = (int *******)((int)pppppppiVar9 + -1)) {
          *pppppppiVar15 = ppppppiVar11;
          pppppppiVar15 = pppppppiVar15 + 1;
        }
      }
LAB_0077a036:
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_c);
      pppppppiVar15 = local_54[0];
LAB_0077a055:
      pppppppiVar18 = (int *******)((uint)local_8 & 0xffffff | 0x25000000);
      pppppppiVar9 = param_3;
      goto LAB_0077b3b5;
    }
    break;
  case 0x36:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      pppppppiVar18 = (int *******)((uint)local_8 & 0xffffff);
      local_38 = (int *******)0xffffffff;
      local_64 = (int *******)0xffffffff;
      local_68 = (int *******)0xffffffff;
      iVar16 = FUN_00773e3b(param_2,(uint)pppppppiVar18 | 0x30000000,&local_38,local_54[0],
                            local_54[1],0);
      if ((((iVar16 < 0) ||
           (iVar16 = FUN_00773e3b(param_2,0x24000001,&local_64,&local_38,&local_38,0), iVar16 < 0))
          || (iVar16 = FUN_00773e3b(param_2,0x11000001,&local_68,&local_64,0,0), iVar16 < 0)) ||
         (local_c = operator_new((int)local_8 << 3), local_c == (int *******)0x0))
      goto LAB_0077bc80;
      uVar12 = 0;
      pppppppiVar9 = local_c;
      do {
        (&local_5c)[uVar12] = (int ******)pppppppiVar9;
        uVar12 = uVar12 + 1;
        pppppppiVar9 = pppppppiVar9 + (int)local_8;
      } while (uVar12 < 2);
      pppppppiVar9 = (int *******)0x0;
      if (local_8 != (int *******)0x0) {
        do {
          local_5c[(int)pppppppiVar9] = (int *****)local_68;
          pppppppiVar9 = (int *******)((int)pppppppiVar9 + 1);
        } while (pppppppiVar9 < local_8);
      }
      iVar16 = FUN_00773063(local_58,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar19 = FUN_00773063(param_3,local_8);
      if (((int)uVar19 < 0) ||
         (iVar16 = FUN_00773e3b(param_2,(uint)pppppppiVar18 | 0x25000000,local_58,local_54[1],
                                (int)((ulonglong)uVar19 >> 0x20),0), iVar16 < 0)) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_54[0]);
      pppppppiVar15 = local_58;
      goto LAB_0077a5d2;
    }
    break;
  case 0x37:
    if ((((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0)) ||
       (local_18 == (int *******)0x0)) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      local_40 = (int *******)0xffffffff;
      uVar19 = FUN_00773063(&local_6c,1);
      if ((int)uVar19 < 0) goto LAB_0077bc80;
      uVar19 = FUN_00773063(local_104,(int)((ulonglong)uVar19 >> 0x20));
      if ((int)uVar19 < 0) goto LAB_0077bc80;
      uVar19 = FUN_00773063(&stack0xffffffbc,(int)((ulonglong)uVar19 >> 0x20));
      if ((int)uVar19 < 0) goto LAB_0077bc80;
      uVar19 = FUN_00773063(&local_10,(int)((ulonglong)uVar19 >> 0x20));
      if ((int)uVar19 < 0) goto LAB_0077bc80;
      uVar19 = FUN_00773063(&local_38,(int)((ulonglong)uVar19 >> 0x20));
      if ((int)uVar19 < 0) goto LAB_0077bc80;
      uVar19 = FUN_00773063(&local_64,(int)((ulonglong)uVar19 >> 0x20));
      if ((int)uVar19 < 0) goto LAB_0077bc80;
      uVar19 = FUN_00773063(local_108,(int)((ulonglong)uVar19 >> 0x20));
      if ((int)uVar19 < 0) goto LAB_0077bc80;
      uVar19 = FUN_00773063(&local_68,(int)((ulonglong)uVar19 >> 0x20));
      if ((int)uVar19 < 0) goto LAB_0077bc80;
      uVar19 = FUN_00773063(&local_74,(int)((ulonglong)uVar19 >> 0x20));
      if ((int)uVar19 < 0) goto LAB_0077bc80;
      uVar19 = FUN_00773063(&local_70,(int)((ulonglong)uVar19 >> 0x20));
      if (((int)uVar19 < 0) ||
         (iVar16 = FUN_00773063(&local_58,(int)((ulonglong)uVar19 >> 0x20)), iVar16 < 0))
      goto LAB_0077bc80;
      local_3c = (int *******)((uint)local_8 & 0xffffff);
      iVar16 = FUN_00773e3b(param_2,(uint)local_3c | 0x30000000,&local_40,local_54[0],local_54[1],0)
      ;
      if (((iVar16 < 0) ||
          (((((iVar16 = FUN_00773e3b(param_2,0x25000001,&local_6c,&local_40,&local_40,4), iVar16 < 0
              || (iVar16 = FUN_00773e3b(param_2,0x25000001,local_104,local_54[2],local_54[2],4),
                 iVar16 < 0)) ||
             (iVar16 = FUN_00773e3b(param_2,0x11000001,&stack0xffffffbc,&local_6c,0,8), iVar16 < 0))
            || ((iVar16 = FUN_00773e3b(param_2,0x24000001,&local_10,param_1 + 0x20,&stack0xffffffbc,
                                       0), iVar16 < 0 ||
                (iVar16 = FUN_00773e3b(param_2,0x25000001,&local_38,local_104,&local_10,0),
                iVar16 < 0)))) ||
           (iVar16 = FUN_00773e3b(param_2,0x23000001,&local_64,&local_38,param_1 + 0x24,0x2000017),
           iVar16 < 0)))) ||
         ((((iVar16 = FUN_00773e3b(param_2,0x25000001,local_108,&local_38,&local_64,4), iVar16 < 0
            || (iVar16 = FUN_00773e3b(param_2,0x25000001,&local_68,local_54[2],&local_64,0),
               iVar16 < 0)) ||
           (iVar16 = FUN_00773e3b(param_2,0x25000001,&local_74,&local_68,&local_40,0), iVar16 < 0))
          || (((iVar16 = FUN_00773e3b(param_2,0x16000001,&local_70,local_108,0,4), iVar16 < 0 ||
               (iVar16 = FUN_00773e3b(param_2,0x24000001,&local_58,&local_74,&local_70,0),
               iVar16 < 0)) ||
              (local_c = operator_new((int)local_8 * 0x14), local_c == (int *******)0x0))))))
      goto LAB_0077bc80;
      uVar12 = 0;
      pppppppiVar9 = local_c;
      do {
        (&local_24)[uVar12] = pppppppiVar9;
        uVar12 = uVar12 + 1;
        pppppppiVar9 = pppppppiVar9 + (int)local_8;
      } while (uVar12 < 5);
      if (local_8 != (int *******)0x0) {
        pppppppiVar9 = (int *******)local_14;
        pppppppiVar15 = local_8;
        do {
          *(int ********)(((int)local_18 - (int)local_14) + (int)pppppppiVar9) = local_68;
          *pppppppiVar9 = (int ******)local_58;
          pppppppiVar9 = pppppppiVar9 + 1;
          pppppppiVar15 = (int *******)((int)pppppppiVar15 + -1);
        } while (pppppppiVar15 != (int *******)0x0);
      }
      iVar16 = FUN_00773063(local_24,local_8);
      if (((iVar16 < 0) || (iVar16 = FUN_00773063(local_20,local_8), iVar16 < 0)) ||
         ((iVar16 = FUN_00773063(local_1c,local_8), iVar16 < 0 ||
          (iVar16 = FUN_00773063(param_3,local_8), pppppppiVar18 = local_3c, iVar16 < 0))))
      goto LAB_0077bc80;
      local_8 = (int *******)((uint)local_3c | 0x25000000);
      iVar16 = FUN_00773e3b(param_2,local_8,local_24,local_18,local_54[0],0);
      if (((iVar16 < 0) ||
          (iVar16 = FUN_00773e3b(param_2,local_8,local_20,local_14,local_54[1],0), iVar16 < 0)) ||
         (iVar16 = FUN_00773e3b(param_2,(uint)pppppppiVar18 | 0x11000000,local_1c,local_20,0,0),
         iVar16 < 0)) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_1c);
      pppppppiVar15 = local_24;
      goto LAB_0077a5d2;
    }
    break;
  case 0x38:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      ppppppiVar11 = (int ******)
                     FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,_DAT_00859060);
      local_c = operator_new((int)local_8 << 4);
      if (local_c == (int *******)0x0) goto LAB_0077bc80;
      uVar12 = 0;
      pppppppiVar9 = local_c;
      do {
        (&local_20)[uVar12] = (int ******)pppppppiVar9;
        uVar12 = uVar12 + 1;
        pppppppiVar9 = pppppppiVar9 + (int)local_8;
      } while (uVar12 < 4);
      pppppppiVar9 = local_8;
      pppppppiVar15 = (int *******)local_14;
      if (local_8 != (int *******)0x0) {
        for (; pppppppiVar9 != (int *******)0x0;
            pppppppiVar9 = (int *******)((int)pppppppiVar9 + -1)) {
          *pppppppiVar15 = ppppppiVar11;
          pppppppiVar15 = pppppppiVar15 + 1;
        }
      }
      iVar16 = FUN_00773063(local_20,local_8);
      if ((((iVar16 < 0) || (iVar16 = FUN_00773063(local_1c,local_8), iVar16 < 0)) ||
          (iVar16 = FUN_00773063(local_18,local_8), iVar16 < 0)) ||
         (iVar16 = FUN_00773063(param_3,local_8), iVar16 < 0)) goto LAB_0077bc80;
      uVar12 = (uint)local_8 & 0xffffff;
      local_44 = SUB43(local_8,0);
      _local_44 = (int *******)CONCAT13(0x24,local_44);
      iVar16 = FUN_00773e3b(param_2,_local_44,local_20,local_54[0],local_14,0);
      if (((iVar16 < 0) ||
          (iVar16 = FUN_00773e3b(param_2,uVar12 | 0x13000000,local_1c,local_20,0,0x14), iVar16 < 0))
         || (iVar16 = FUN_00773e3b(param_2,uVar12 | 0x11000000,local_18,local_1c,0,0x18), iVar16 < 0
            )) goto LAB_0077bc80;
      uVar20 = CONCAT44(2,local_18);
      pppppppiVar18 = _local_44;
      pppppppiVar9 = param_3;
      pppppppiVar15 = (int *******)local_20;
      goto LAB_0077b3b5;
    }
    break;
  case 0x39:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      local_c = operator_new((int)local_8 << 2);
      if (((local_c == (int *******)0x0) || (iVar16 = FUN_00773063(local_c,local_8), iVar16 < 0)) ||
         (iVar16 = FUN_00773063(param_3,local_8), iVar16 < 0)) goto LAB_0077bc80;
      uVar12 = (uint)local_8 & 0xffffff;
      iVar16 = FUN_00773e3b(param_2,uVar12 | 0x16000000,local_c,local_54[0],0,4);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = 0x400000000;
      pppppppiVar18 = (int *******)(uVar12 | 0x12000000);
      pppppppiVar9 = param_3;
      pppppppiVar15 = local_c;
      goto LAB_0077b3b5;
    }
    break;
  case 0x3a:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      local_c = operator_new((int)local_8 * 0xc);
      if (local_c == (int *******)0x0) goto LAB_0077bc80;
      uVar12 = 0;
      pppppppiVar9 = local_c;
      do {
        (&local_60)[uVar12] = pppppppiVar9;
        uVar12 = uVar12 + 1;
        pppppppiVar9 = pppppppiVar9 + (int)local_8;
      } while (uVar12 < 3);
      if (local_8 != (int *******)0x0) {
        pppppppiVar9 = (int *******)local_5c;
        pppppppiVar15 = local_8;
        do {
          *(undefined4 *)(((int)local_60 - (int)local_5c) + (int)pppppppiVar9) =
               *(undefined4 *)(param_1 + 0x24);
          *pppppppiVar9 = *(int *******)(param_1 + 0x20);
          pppppppiVar9 = pppppppiVar9 + 1;
          pppppppiVar15 = (int *******)((int)pppppppiVar15 + -1);
        } while (pppppppiVar15 != (int *******)0x0);
      }
      iVar16 = FUN_00773063(local_58,local_8);
      if ((iVar16 < 0) || (iVar16 = FUN_00773063(param_3,local_8), iVar16 < 0)) goto LAB_0077bc80;
      uVar12 = (uint)local_8 & 0xffffff;
      iVar16 = FUN_00773e3b(param_2,uVar12 | 0x21000000,local_58,local_54[0],local_60,4);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = CONCAT44(0x14,local_5c);
      pppppppiVar15 = local_58;
      goto LAB_0077a895;
    }
    break;
  case 0x3b:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      local_c = operator_new((int)local_8 << 4);
      if (local_c == (int *******)0x0) goto LAB_0077bc80;
      uVar12 = 0;
      pppppppiVar9 = local_c;
      do {
        (&local_20)[uVar12] = (int ******)pppppppiVar9;
        uVar12 = uVar12 + 1;
        pppppppiVar9 = pppppppiVar9 + (int)local_8;
      } while (uVar12 < 4);
      iVar16 = FUN_00773063(local_20,local_8);
      if (((iVar16 < 0) || (iVar16 = FUN_00773063(local_1c,local_8), iVar16 < 0)) ||
         ((iVar16 = FUN_00773063(local_18,local_8), iVar16 < 0 ||
          ((iVar16 = FUN_00773063(local_14,local_8), iVar16 < 0 ||
           (iVar16 = FUN_00773063(param_3,local_8), iVar16 < 0)))))) goto LAB_0077bc80;
      local_3c = (int *******)((uint)local_8 & 0xffffff);
      local_10 = (int *******)((uint)local_3c | 0x11000000);
      iVar16 = FUN_00773e3b(param_2,local_10,local_20,local_54[0],0,0);
      if (iVar16 < 0) goto LAB_0077bc80;
      local_38 = (int *******)((uint)local_3c | 0x22000000);
      iVar16 = FUN_00773e3b(param_2,local_38,local_1c,local_20,local_54[0],0x2000017);
      if (((iVar16 < 0) ||
          (iVar16 = FUN_00773e3b(param_2,local_38,local_18,local_54[0],local_20,0x2000017),
          iVar16 < 0)) ||
         (iVar16 = FUN_00773e3b(param_2,local_10,local_14,local_18,0,0x1a), iVar16 < 0))
      goto LAB_0077bc80;
      uVar20 = CONCAT44(0x12,local_14);
      pppppppiVar18 = (int *******)((uint)local_3c | 0x24000000);
      pppppppiVar9 = param_3;
      pppppppiVar15 = local_1c;
      goto LAB_0077b3b5;
    }
    break;
  case 0x3c:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      lVar21 = ZEXT48(local_8) << 0x20;
      pppppppiVar9 = param_3;
      goto LAB_0077aaa9;
    }
    break;
  case 0x3d:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    uVar12 = (int)local_bc << 2;
    local_54[1] = operator_new(uVar12);
    if ((local_54[1] == (int *******)0x0) ||
       (local_54[2] = operator_new(uVar12), local_54[2] == (int *******)0x0)) goto LAB_0077bc80;
    uVar19 = FUN_00773063(local_54[1],ppppppiVar11);
    if ((int)uVar19 < 0) goto LAB_0077bc80;
    uVar19 = FUN_00773063((int)((ulonglong)uVar19 >> 0x20),ppppppiVar11);
    if ((int)uVar19 < 0) goto LAB_0077bc80;
    lVar21 = CONCAT44(ppppppiVar11,(int)((ulonglong)uVar19 >> 0x20));
    pppppppiVar9 = local_54[1];
LAB_0077aaa9:
    iVar16 = FUN_00774678(param_2,local_54[0],pppppppiVar9,lVar21);
    goto LAB_0077b3bf;
  case 0x3e:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      fVar3 = (float10)log2((float10)_DAT_0086f990);
      uVar8 = FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,
                           (double)((float10)_DAT_0085a310 / ((float10)0.6931471805599453 * fVar3)))
      ;
      local_58 = (int *******)
                 FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,_DAT_00859060);
      local_c = operator_new((int)local_8 << 5);
      if (local_c == (int *******)0x0) goto LAB_0077bc80;
      uVar12 = 0;
      pppppppiVar9 = local_c;
      do {
        (&local_30)[uVar12] = pppppppiVar9;
        uVar12 = uVar12 + 1;
        pppppppiVar9 = pppppppiVar9 + (int)local_8;
      } while (uVar12 < 8);
      if (local_8 != (int *******)0x0) {
        pppppppiVar9 = (int *******)local_14;
        pppppppiVar15 = local_8;
        do {
          *(undefined4 *)(((int)local_18 - (int)local_14) + (int)pppppppiVar9) = uVar8;
          *pppppppiVar9 = (int ******)local_58;
          pppppppiVar9 = pppppppiVar9 + 1;
          pppppppiVar15 = (int *******)((int)pppppppiVar15 + -1);
        } while (pppppppiVar15 != (int *******)0x0);
      }
      iVar16 = FUN_00773063(local_30,local_8);
      if (((iVar16 < 0) || (iVar16 = FUN_00773063(local_2c[0],local_8), iVar16 < 0)) ||
         ((((iVar16 = FUN_00773063(local_2c[1],local_8), iVar16 < 0 ||
            ((iVar16 = FUN_00773063(local_24,local_8), iVar16 < 0 ||
             (iVar16 = FUN_00773063(local_20,local_8), iVar16 < 0)))) ||
           (iVar16 = FUN_00773063(local_1c,local_8), iVar16 < 0)) ||
          (iVar16 = FUN_00773063(param_3,local_8), iVar16 < 0)))) goto LAB_0077bc80;
      uVar12 = (uint)local_8 & 0xffffff;
      uVar4 = (undefined3)local_8;
      local_8 = (int *******)CONCAT13(0x25,(undefined3)local_8);
      iVar16 = FUN_00773e3b(param_2,local_8,local_30,local_54[0],local_18,0);
      if (iVar16 < 0) goto LAB_0077bc80;
      local_3c = (int *******)CONCAT13(0x14,uVar4);
      iVar16 = FUN_00773e3b(param_2,local_3c,local_2c[0],local_30,0,4);
      if (iVar16 < 0) goto LAB_0077bc80;
      local_10 = (int *******)CONCAT13(0x11,uVar4);
      iVar16 = FUN_00773e3b(param_2,local_10,local_2c[1],local_30,0,0);
      if ((((iVar16 < 0) ||
           (iVar16 = FUN_00773e3b(param_2,local_3c,local_24,local_2c[1],0,4), iVar16 < 0)) ||
          (iVar16 = FUN_00773e3b(param_2,local_10,local_20,local_24,0,8), iVar16 < 0)) ||
         (iVar16 = FUN_00773e3b(param_2,uVar12 | 0x24000000,local_1c,local_2c[0],local_20,0),
         iVar16 < 0)) goto LAB_0077bc80;
      uVar8 = 0;
      goto LAB_0077ace6;
    }
    break;
  case 0x3f:
    if ((((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0)) ||
       (local_18 == (int *******)0x0)) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      local_74 = (int ******)
                 FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,_DAT_0087a8a8);
      local_70 = FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,_DAT_0086f988);
      pppppppiVar9 = operator_new((int)local_8 * 0x38);
      local_c = pppppppiVar9;
      if (pppppppiVar9 == (int *******)0x0) goto LAB_0077bc80;
      uVar12 = 0;
      do {
        local_100[uVar12] = (int)pppppppiVar9;
        uVar12 = uVar12 + 1;
        pppppppiVar9 = pppppppiVar9 + (int)local_8;
      } while (uVar12 < 0xe);
      uVar12 = 0;
      do {
        uVar19 = FUN_00773063(local_100[uVar12],local_8);
        if ((int)uVar19 < 0) goto LAB_0077bc80;
        uVar12 = (int)((ulonglong)uVar19 >> 0x20) + 1;
      } while (uVar12 < 10);
      if (local_8 != (int *******)0x0) {
        local_58 = local_8;
        puVar10 = local_d4;
        do {
          *(undefined4 *)((local_d8 - (int)local_d4) + (int)puVar10) =
               *(undefined4 *)(param_1 + 0x24);
          *puVar10 = *(undefined4 *)(param_1 + 0x20);
          *(int *******)((local_d0 - (int)local_d4) + (int)puVar10) = local_74;
          *(int *)((local_cc - (int)local_d4) + (int)puVar10) = local_70;
          puVar10 = puVar10 + 1;
          local_58 = (int *******)((int)local_58 + -1);
        } while (local_58 != (int *******)0x0);
      }
      iVar16 = FUN_00773063(param_3,local_8);
      pppppppiVar9 = local_8;
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar12 = (uint)local_8 & 0xffffff;
      iVar16 = FUN_00773e3b(param_2,uVar12 | 0x11000000,local_100[0],local_54[0],0,0);
      if (iVar16 < 0) goto LAB_0077bc80;
      local_44 = SUB43(pppppppiVar9,0);
      uVar4 = local_44;
      _local_44 = (int *******)CONCAT13(0x24,local_44);
      iVar16 = FUN_00773e3b(param_2,_local_44,local_100[1],local_54[1],local_100[0],0);
      if (((iVar16 < 0) ||
          (iVar16 = FUN_00773e3b(param_2,_local_44,local_f8[0],local_54[2],local_100[0],0),
          iVar16 < 0)) ||
         (iVar16 = FUN_00773e3b(param_2,uVar12 | 0x12000000,local_f8[1],local_100[1],0,0),
         iVar16 < 0)) goto LAB_0077bc80;
      local_8 = (int *******)CONCAT13(0x25,uVar4);
      iVar16 = FUN_00773e3b(param_2,local_8,local_f8[2],local_f8[0],local_f8[1],0);
      if (((iVar16 < 0) ||
          (iVar16 = FUN_00773e3b(param_2,uVar12 | 0x21000000,local_ec[0],local_f8[2],local_d8,4),
          iVar16 < 0)) ||
         ((iVar16 = FUN_00773e3b(param_2,uVar12 | 0x20000000,local_ec[1],local_ec[0],local_d4,0x14),
          iVar16 < 0 ||
          (((iVar16 = FUN_00773e3b(param_2,local_8,local_ec[2],local_ec[1],local_d0,8), iVar16 < 0
            || (iVar16 = FUN_00773e3b(param_2,_local_44,local_e0,local_ec[2],local_cc,0), iVar16 < 0
               )) || (iVar16 = FUN_00773e3b(param_2,local_8,local_dc,local_ec[1],local_ec[1],0x14),
                     iVar16 < 0)))))) goto LAB_0077bc80;
      uVar20 = (ulonglong)local_dc;
      pppppppiVar18 = local_8;
      pppppppiVar9 = param_3;
      pppppppiVar15 = local_e0;
      goto LAB_0077b3b5;
    }
    break;
  case 0x40:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      iVar16 = FUN_00773063(param_3,local_8);
      pppppppiVar15 = local_54[0];
      goto joined_r0x0077afba;
    }
    break;
  case 0x41:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      pppppppiVar18 = (int *******)((uint)local_8 & 0xffffff);
      pppppppiVar15 = local_54[1];
      pppppppiVar9 = local_54[0];
      goto LAB_0077b020;
    }
    break;
  case 0x42:
    if (((int *******)local_20 == (int *******)0x0) ||
       (local_c = operator_new((int)local_8 * 0xc), local_c == (int *******)0x0)) goto LAB_0077bc80;
    uVar12 = 0;
    pppppppiVar9 = local_c;
    do {
      (&local_60)[uVar12] = pppppppiVar9;
      uVar12 = uVar12 + 1;
      pppppppiVar9 = pppppppiVar9 + (int)local_8;
    } while (uVar12 < 3);
    iVar16 = FUN_00773063(local_60,local_8);
    if ((((iVar16 < 0) || (iVar16 = FUN_00773063(local_5c,local_8), iVar16 < 0)) ||
        (iVar16 = FUN_00773063(local_58,local_8), iVar16 < 0)) ||
       ((iVar16 = FUN_00773063(param_3,local_8), iVar16 < 0 ||
        (iVar16 = FUN_00774678(param_2,local_54[0],local_60,local_5c), iVar16 < 0))))
    goto LAB_0077bc80;
    uVar12 = (uint)local_8 & 0xffffff;
    iVar16 = FUN_00773e3b(param_2,uVar12 | 0x12000000,local_58,local_5c,0,0);
    if (iVar16 < 0) goto LAB_0077bc80;
    uVar20 = ZEXT48(local_58);
    pppppppiVar15 = local_60;
LAB_0077b118:
    pppppppiVar18 = (int *******)(uVar12 | 0x25000000);
    pppppppiVar9 = param_3;
LAB_0077b3b5:
    iVar16 = FUN_00773e3b(param_2,pppppppiVar18,pppppppiVar9,pppppppiVar15,uVar20);
LAB_0077b3bf:
    if (iVar16 < 0) goto LAB_0077bc80;
    break;
  case 0x43:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      fVar3 = (float10)log2((float10)_DAT_0086f990);
      ppppppiVar11 = (int ******)
                     FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,
                                  (double)((float10)_DAT_0085a310 /
                                          ((float10)0.6931471805599453 * fVar3)));
      local_c = operator_new((int)local_8 * 0x24);
      if (local_c == (int *******)0x0) goto LAB_0077bc80;
      uVar12 = 0;
      pppppppiVar9 = local_c;
      do {
        (&local_34)[uVar12] = (int *)pppppppiVar9;
        uVar12 = uVar12 + 1;
        pppppppiVar9 = pppppppiVar9 + (int)local_8;
      } while (uVar12 < 9);
      pppppppiVar9 = local_8;
      pppppppiVar15 = (int *******)local_14;
      if (local_8 != (int *******)0x0) {
        for (; pppppppiVar9 != (int *******)0x0;
            pppppppiVar9 = (int *******)((int)pppppppiVar9 + -1)) {
          *pppppppiVar15 = ppppppiVar11;
          pppppppiVar15 = pppppppiVar15 + 1;
        }
      }
      iVar16 = FUN_00773063(local_34,local_8);
      if (((((iVar16 < 0) || (iVar16 = FUN_00773063(local_30,local_8), iVar16 < 0)) ||
           ((iVar16 = FUN_00773063(local_2c[0],local_8), iVar16 < 0 ||
            ((iVar16 = FUN_00773063(local_2c[1],local_8), iVar16 < 0 ||
             (iVar16 = FUN_00773063(local_24,local_8), iVar16 < 0)))))) ||
          (iVar16 = FUN_00773063(local_20,local_8), iVar16 < 0)) ||
         (((iVar16 = FUN_00773063(local_1c,local_8), iVar16 < 0 ||
           (iVar16 = FUN_00773063(local_18,local_8), iVar16 < 0)) ||
          (iVar16 = FUN_00773063(param_3,local_8), iVar16 < 0)))) goto LAB_0077bc80;
      uVar12 = (uint)local_8 & 0xffffff;
      uVar4 = (undefined3)local_8;
      local_8 = (int *******)CONCAT13(0x25,(undefined3)local_8);
      iVar16 = FUN_00773e3b(param_2,local_8,local_34,local_54[0],local_14,0);
      if (iVar16 < 0) goto LAB_0077bc80;
      local_3c = (int *******)CONCAT13(0x14,uVar4);
      iVar16 = FUN_00773e3b(param_2,local_3c,local_30,local_34,0,4);
      if (iVar16 < 0) goto LAB_0077bc80;
      local_10 = (int *******)CONCAT13(0x11,uVar4);
      iVar16 = FUN_00773e3b(param_2,local_10,local_2c[0],local_34,0,0);
      if (((iVar16 < 0) ||
          (iVar16 = FUN_00773e3b(param_2,local_3c,local_2c[1],local_2c[0],0,4), iVar16 < 0)) ||
         (iVar16 = FUN_00773e3b(param_2,local_10,local_24,local_2c[1],0,8), iVar16 < 0))
      goto LAB_0077bc80;
      _local_44 = (int *******)CONCAT13(0x24,uVar4);
      iVar16 = FUN_00773e3b(param_2,_local_44,local_20,local_30,local_24,0);
      if (((iVar16 < 0) ||
          (iVar16 = FUN_00773e3b(param_2,_local_44,local_1c,local_30,local_2c[1],4), iVar16 < 0)) ||
         (iVar16 = FUN_00773e3b(param_2,uVar12 | 0x12000000,local_18,local_1c,0,4), iVar16 < 0))
      goto LAB_0077bc80;
      uVar20 = ZEXT48(local_18);
      pppppppiVar18 = local_8;
      pppppppiVar9 = param_3;
      pppppppiVar15 = (int *******)local_20;
      goto LAB_0077b3b5;
    }
    break;
  case 0x44:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      uVar12 = 0;
      do {
        (&local_20)[uVar12] = *local_54[0];
        (&local_18)[uVar12] = (int *******)*local_54[1];
        uVar12 = uVar12 + 1;
      } while (uVar12 < 2);
      local_58 = (int *******)*local_54[1];
      FUN_00776527(0,&local_58,1);
      iVar16 = *(int *)(param_1 + 8);
      ppppppiVar11 = (*(int ********)(iVar16 + 0x14))[(int)local_18];
      if (((*(byte *)(*(int *)(*(int *)(iVar16 + 0x10) + (int)*ppppppiVar11 * 4) + 4) & 8) != 0) &&
         (ppppppiVar11[3] == (int *****)0x0)) {
        local_40 = (int *******)0x0;
        pppppppiVar9 = *(int ********)(iVar16 + 0x14);
        if (*(int *)(iVar16 + 8) != 0) {
          do {
            local_38 = pppppppiVar9;
            ppppppiVar14 = *local_38;
            if ((((*ppppppiVar11 == *ppppppiVar14) && (ppppppiVar11[1] == ppppppiVar14[1])) &&
                (ppppppiVar11[2] == ppppppiVar14[2])) && (ppppppiVar14[3] == (int *****)0x1)) {
              local_14 = (int **)local_40;
              break;
            }
            local_40 = (int *******)((int)local_40 + 1);
            local_38 = local_38 + 1;
            pppppppiVar9 = local_38;
          } while (local_40 < *(int ********)(*(int *)(param_1 + 8) + 8));
        }
        if (local_40 == *(int ********)(iVar16 + 8)) {
          FUN_00773cf1(param_1,param_2,0xdb5);
        }
      }
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = ZEXT48(&local_18);
      pppppppiVar18 = (int *******)0x40000002;
      pppppppiVar9 = param_3;
      pppppppiVar15 = &local_20;
      goto LAB_0077b3b5;
    }
    break;
  case 0x45:
    if (((((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0)) ||
        (local_18 == (int *******)0x0)) || ((int *******)local_14 == (int *******)0x0))
    goto LAB_0077bc80;
    uVar12 = 0;
    if (param_3 != (int *******)0x0) {
      do {
        (&local_30)[uVar12] = (int *******)*local_54[0];
        local_2c[uVar12 + 1] = *local_54[1];
        (&local_20)[uVar12] = *local_54[2];
        uVar13 = uVar12 + 1;
        (&local_18)[uVar12] = (int *******)*local_54[3];
        uVar12 = uVar13;
      } while (uVar13 < 2);
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_2c + 1);
      pppppppiVar18 = (int *******)0x41000002;
      pppppppiVar9 = param_3;
      pppppppiVar15 = (int *******)&local_30;
      goto LAB_0077b3b5;
    }
    break;
  case 0x46:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    uVar12 = 0;
    if (param_3 != (int *******)0x0) {
      do {
        (&local_20)[uVar12] = *local_54[0];
        uVar12 = uVar12 + 1;
      } while (uVar12 < 4);
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_54[1]);
      pppppppiVar18 = (int *******)0x42000004;
      pppppppiVar9 = param_3;
      pppppppiVar15 = &local_20;
      goto LAB_0077b3b5;
    }
    break;
  case 0x47:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    uVar12 = 0;
    if (param_3 != (int *******)0x0) {
      do {
        (&local_20)[uVar12] = *local_54[0];
        uVar12 = uVar12 + 1;
      } while (uVar12 < 4);
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_54[1]);
      pppppppiVar18 = (int *******)0x43000004;
      pppppppiVar9 = param_3;
      pppppppiVar15 = &local_20;
      goto LAB_0077b3b5;
    }
    break;
  case 0x48:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    uVar12 = 0;
    if (param_3 != (int *******)0x0) {
      do {
        (&local_5c)[uVar12] = *local_54[0];
        uVar12 = uVar12 + 1;
      } while (uVar12 < 2);
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_54[1]);
      pppppppiVar18 = (int *******)0x44000002;
      pppppppiVar9 = param_3;
      pppppppiVar15 = &local_5c;
      goto LAB_0077b3b5;
    }
    break;
  case 0x49:
    if (((((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0)) ||
        (local_18 == (int *******)0x0)) || ((int *******)local_14 == (int *******)0x0))
    goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      local_40 = (int *******)((int)local_54[2] - (int)local_54[1]);
      local_74 = (int ******)((int)&local_20 - (int)local_54[1]);
      local_3c = (int *******)((int)local_54[3] - (int)local_54[1]);
      local_70 = (int)&local_18 - (int)local_54[1];
      local_58 = (int *******)0x2;
      pppppppiVar9 = local_54[1];
      do {
        *(int *******)(((int)&local_30 - (int)local_54[1]) + (int)pppppppiVar9) = *local_54[0];
        *(int *******)((int)local_2c + (4U - (int)local_54[1]) + (int)pppppppiVar9) = *pppppppiVar9;
        *(undefined4 *)((int)local_74 + (int)pppppppiVar9) =
             *(undefined4 *)((int)local_40 + (int)pppppppiVar9);
        *(undefined4 *)(local_70 + (int)pppppppiVar9) =
             *(undefined4 *)((int)local_3c + (int)pppppppiVar9);
        pppppppiVar9 = pppppppiVar9 + 1;
        local_58 = (int *******)((int)local_58 + -1);
      } while (local_58 != (int *******)0x0);
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_2c + 1);
      pppppppiVar18 = (int *******)0x45000002;
      pppppppiVar9 = param_3;
      pppppppiVar15 = (int *******)&local_30;
      goto LAB_0077b3b5;
    }
    break;
  case 0x4a:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    uVar12 = 0;
    if (param_3 != (int *******)0x0) {
      do {
        (&local_20)[uVar12] = *local_54[0];
        uVar12 = uVar12 + 1;
      } while (uVar12 < 4);
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_54[1]);
      pppppppiVar18 = (int *******)0x46000004;
      pppppppiVar9 = param_3;
      pppppppiVar15 = &local_20;
      goto LAB_0077b3b5;
    }
    break;
  case 0x4b:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    uVar12 = 0;
    if (param_3 != (int *******)0x0) {
      do {
        (&local_20)[uVar12] = *local_54[0];
        uVar12 = uVar12 + 1;
      } while (uVar12 < 4);
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_54[1]);
      pppppppiVar18 = (int *******)0x47000004;
      pppppppiVar9 = param_3;
      pppppppiVar15 = &local_20;
      goto LAB_0077b3b5;
    }
    break;
  case 0x4c:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    uVar12 = 0;
    if (param_3 != (int *******)0x0) {
      do {
        (&local_1c)[uVar12] = (int *******)*local_54[0];
        uVar12 = uVar12 + 1;
      } while (uVar12 < 3);
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_54[1]);
      pppppppiVar18 = (int *******)0x48000003;
      pppppppiVar9 = param_3;
      pppppppiVar15 = (int *******)&local_1c;
      goto LAB_0077b3b5;
    }
    break;
  case 0x4d:
    if (((((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0)) ||
        (local_18 == (int *******)0x0)) || ((int *******)local_14 == (int *******)0x0))
    goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      local_40 = (int *******)((int)local_54[2] - (int)local_54[1]);
      local_74 = (int ******)((int)&local_e0 - (int)local_54[1]);
      local_3c = (int *******)((int)local_54[3] - (int)local_54[1]);
      iVar16 = 8 - (int)local_54[1];
      iVar6 = 0x14 - (int)local_54[1];
      local_70 = (int)&local_d4 - (int)local_54[1];
      local_58 = (int *******)0x3;
      pppppppiVar9 = local_54[1];
      do {
        ppppppiVar11 = local_74;
        *(int *******)((int)local_100 + iVar16 + (int)pppppppiVar9) = *local_54[0];
        *(int *******)((int)local_100 + iVar6 + (int)pppppppiVar9) = *pppppppiVar9;
        *(undefined4 *)((int)ppppppiVar11 + (int)pppppppiVar9) =
             *(undefined4 *)((int)pppppppiVar9 + (int)local_40);
        *(undefined4 *)(local_70 + (int)pppppppiVar9) =
             *(undefined4 *)((int)pppppppiVar9 + (int)local_3c);
        pppppppiVar9 = pppppppiVar9 + 1;
        local_58 = (int *******)((int)local_58 + -1);
      } while (local_58 != (int *******)0x0);
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_100 + 5);
      pppppppiVar18 = (int *******)0x49000003;
      pppppppiVar9 = param_3;
      pppppppiVar15 = (int *******)(local_100 + 2);
      goto LAB_0077b3b5;
    }
    break;
  case 0x4e:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    uVar12 = 0;
    if (param_3 != (int *******)0x0) {
      do {
        (&local_20)[uVar12] = *local_54[0];
        uVar12 = uVar12 + 1;
      } while (uVar12 < 4);
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_54[1]);
      pppppppiVar18 = (int *******)0x4a000004;
      pppppppiVar9 = param_3;
      pppppppiVar15 = &local_20;
      goto LAB_0077b3b5;
    }
    break;
  case 0x4f:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    uVar12 = 0;
    if (param_3 != (int *******)0x0) {
      do {
        (&local_20)[uVar12] = *local_54[0];
        uVar12 = uVar12 + 1;
      } while (uVar12 < 4);
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_54[1]);
      pppppppiVar18 = (int *******)0x4b000004;
      pppppppiVar9 = param_3;
      pppppppiVar15 = &local_20;
      goto LAB_0077b3b5;
    }
    break;
  case 0x50:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    uVar12 = 0;
    if (param_3 != (int *******)0x0) {
      do {
        (&local_1c)[uVar12] = (int *******)*local_54[0];
        uVar12 = uVar12 + 1;
      } while (uVar12 < 3);
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_54[1]);
      pppppppiVar18 = (int *******)0x4c000003;
      pppppppiVar9 = param_3;
      pppppppiVar15 = (int *******)&local_1c;
      goto LAB_0077b3b5;
    }
    break;
  case 0x51:
    if (((((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0)) ||
        (local_18 == (int *******)0x0)) || ((int *******)local_14 == (int *******)0x0))
    goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      local_40 = (int *******)((int)local_54[2] - (int)local_54[1]);
      local_74 = (int ******)((int)&local_e0 - (int)local_54[1]);
      local_3c = (int *******)((int)local_54[3] - (int)local_54[1]);
      iVar16 = 8 - (int)local_54[1];
      iVar6 = 0x14 - (int)local_54[1];
      local_70 = (int)&local_d4 - (int)local_54[1];
      local_58 = (int *******)0x3;
      pppppppiVar9 = local_54[1];
      do {
        ppppppiVar11 = local_74;
        *(int *******)((int)pppppppiVar9 + (int)local_100 + iVar16) = *local_54[0];
        *(int *******)((int)pppppppiVar9 + (int)local_100 + iVar6) = *pppppppiVar9;
        *(undefined4 *)((int)pppppppiVar9 + (int)ppppppiVar11) =
             *(undefined4 *)((int)pppppppiVar9 + (int)local_40);
        *(undefined4 *)((int)pppppppiVar9 + local_70) =
             *(undefined4 *)((int)pppppppiVar9 + (int)local_3c);
        pppppppiVar9 = pppppppiVar9 + 1;
        local_58 = (int *******)((int)local_58 + -1);
      } while (local_58 != (int *******)0x0);
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_100 + 5);
      pppppppiVar18 = (int *******)0x4d000003;
      pppppppiVar9 = param_3;
      pppppppiVar15 = (int *******)(local_100 + 2);
      goto LAB_0077b3b5;
    }
    break;
  case 0x52:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    uVar12 = 0;
    if (param_3 != (int *******)0x0) {
      do {
        (&local_20)[uVar12] = *local_54[0];
        uVar12 = uVar12 + 1;
      } while (uVar12 < 4);
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_54[1]);
      pppppppiVar18 = (int *******)0x4e000004;
      pppppppiVar9 = param_3;
      pppppppiVar15 = &local_20;
      goto LAB_0077b3b5;
    }
    break;
  case 0x53:
    if (((int *******)local_20 == (int *******)0x0) || (local_1c == (int *******)0x0))
    goto LAB_0077bc80;
    uVar12 = 0;
    if (param_3 != (int *******)0x0) {
      do {
        (&local_20)[uVar12] = *local_54[0];
        uVar12 = uVar12 + 1;
      } while (uVar12 < 4);
      iVar16 = FUN_00773063(param_3,local_8);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = ZEXT48(local_54[1]);
      pppppppiVar18 = (int *******)0x4f000004;
      pppppppiVar9 = param_3;
      pppppppiVar15 = &local_20;
      goto LAB_0077b3b5;
    }
    break;
  case 0x54:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if ((param_3 != (int *******)0x0) &&
       (local_40 = (int *******)0x0, (int ******)local_20[6] != (int ******)0x0)) {
      ppppppiVar11 = (int ******)local_20[5];
      do {
        ppppppiVar14 = (int ******)0x0;
        if (ppppppiVar11 != (int ******)0x0) {
          do {
            param_3[(int)(*(int *)((int)param_2 + 0x18) * (int)local_40 + (int)ppppppiVar14)] =
                 local_54[0][(int)((int)local_20[6] * (int)ppppppiVar14 + (int)local_40)];
            ppppppiVar11 = (int ******)local_20[5];
            ppppppiVar14 = (int ******)((int)ppppppiVar14 + 1);
          } while (ppppppiVar14 < ppppppiVar11);
        }
        local_40 = (int *******)((int)local_40 + 1);
      } while (local_40 < local_20[6]);
    }
    break;
  case 0x55:
    if ((int *******)local_20 == (int *******)0x0) goto LAB_0077bc80;
    if (param_3 != (int *******)0x0) {
      local_20 = (int ******)
                 FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,_DAT_0087a9c8);
      local_bc = local_54[0][2];
      local_b8 = (int *)local_54[0][1];
      local_b4 = *local_54[0];
      local_b0 = local_54[0][3];
      local_1c = (int *******)local_20;
      local_18 = (int *******)local_20;
      local_14 = (int **)local_20;
      iVar16 = FUN_00773063(param_3,4);
      if (iVar16 < 0) goto LAB_0077bc80;
      uVar20 = CONCAT44(6,&local_20);
      pppppppiVar18 = (int *******)0x25000004;
      pppppppiVar9 = param_3;
      pppppppiVar15 = &local_bc;
      goto LAB_0077b3b5;
    }
    break;
  default:
    FUN_00773c7b(param_1,param_2,0xdac,"intrinsic function \'%s\' is not yet implemented");
    goto LAB_0077bc80;
  }
  iVar16 = *(int *)(local_154 + 0xc);
  if (iVar16 != 0) {
    param_2 = (int *******)local_54;
    do {
      if (*(int *)(iVar16 + 8) != 0) {
        *(int *******)(param_1 + 0x1c) = *param_2;
        iVar6 = FUN_0077c8d2(*(undefined4 *)(iVar16 + 8));
        if (iVar6 < 0) break;
      }
      iVar16 = *(int *)(iVar16 + 0xc);
      param_2 = param_2 + 1;
    } while (iVar16 != 0);
  }
LAB_0077bc80:
  *(undefined4 *)(param_1 + 0x1c) = local_158;
                    /* WARNING: Subroutine does not return */
  _free(local_54[0]);
}



/* function 0079e3be FUN_0079e3be */

/* WARNING: Type propagation algorithm not settling */

int __fastcall FUN_0079e3be(int *param_1)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  int *piVar8;
  int *piVar9;
  undefined4 uVar10;
  int local_b0 [12];
  int local_80;
  int local_7c [9];
  int iStack_58;
  int iStack_54;
  int iStack_50;
  int local_4c [9];
  int *local_28;
  int *local_24;
  int *local_20;
  int *local_1c;
  int *local_18;
  int *local_14;
  int *local_10;
  int *local_c;
  int *local_8;
  
  puVar1 = *(uint **)((int)param_1 + 0x98);
  uVar7 = *puVar1;
  local_1c = (int *)(uVar7 & 0xffffff);
  if ((puVar1 == (uint *)0x0) || (uVar7 == 0)) {
    return 0;
  }
  local_c = (int *)(puVar1[1] / (uint)local_1c);
  local_18 = (int *)0x0;
  local_20 = param_1;
  if (((uVar7 & 0xff000000) == 0x30000000) || ((int *)puVar1[3] != local_1c)) {
    iVar6 = FUN_0078506d(puVar1);
    if (-1 < iVar6) {
      **(undefined4 **)((int)param_1 + 0x98) = 0;
      return 0;
    }
    return iVar6;
  }
  local_4c[8] = 0;
  if (((*(uint *)((int)param_1 + 0x30) & 0xffff) != 0x104) &&
     (iVar6 = FUN_0079dfaf(puVar1), iVar6 != 0)) {
    iVar6 = *(int *)(*(int *)((int)param_1 + 0x98) + 0xc);
    if (iVar6 != 0) {
      piVar8 = *(int **)(*(int *)((int)param_1 + 0x98) + 0x10);
      do {
        if (*(int *)(*(int *)(*(int *)((int)param_1 + 0x14) + *piVar8 * 4) + 0xc) == 3) {
          local_18 = (int *)0x1;
          local_4c[8] = 1;
        }
        piVar8 = piVar8 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
  }
  local_14 = (int *)0x0;
  if (local_c != (int *)0x0) {
    local_28 = (int *)0x0;
    local_8 = local_b0;
    do {
      piVar9 = local_8;
      piVar8 = local_8 + 1;
      *local_8 = -1;
      local_10 = (int *)0x0;
      *piVar8 = -1;
      piVar9[2] = -1;
      piVar9[3] = -1;
      local_7c[0] = -1;
      local_7c[1] = -1;
      local_7c[2] = -1;
      local_7c[3] = -1;
      if (local_1c != (int *)0x0) {
        iVar6 = *(int *)((int)param_1 + 0x98);
        iVar2 = *(int *)((int)param_1 + 0x14);
        iVar3 = *(int *)((int)param_1 + 0x10);
        local_24 = local_28;
        do {
          piVar8 = *(int **)(iVar2 + *(int *)((int)local_24 + *(int *)(iVar6 + 8)) * 4);
          iVar4 = *(int *)(*(int *)(iVar2 + *(int *)(*(int *)(iVar6 + 0x10) + (int)local_10 * 4) * 4
                                   ) + 0xc);
          if ((*(byte *)(*(int *)(iVar3 + *piVar8 * 4) + 4) & 0x80) == 0) {
            local_b0[iVar4 + (int)local_14 * 4] = piVar8[3];
          }
          else {
            local_b0[iVar4 + (int)local_14 * 4] = iVar4;
          }
          local_7c[iVar4] = 0;
          local_10 = (int *)((int)local_10 + 1);
          local_24 = local_24 + 1;
          param_1 = local_20;
        } while (local_10 < local_1c);
      }
      iVar6 = FUN_0079df56(local_8,local_7c,5);
      if (iVar6 == 0) {
        local_18 = (int *)0x1;
      }
      local_14 = (int *)((int)local_14 + 1);
      local_8 = local_8 + 4;
      local_28 = local_28 + (int)local_1c;
    } while (local_14 < local_c);
  }
  uVar7 = 0;
  if (local_18 == (int *)0x0) {
    iVar6 = FUN_0078506d(*(undefined4 *)((int)param_1 + 0x98));
LAB_0079e93b:
    if (iVar6 < 0) {
      return iVar6;
    }
    goto LAB_0079e93f;
  }
  local_14 = (int *)0x0;
  local_20 = (int *)0x0;
  if (local_1c == (int *)&DAT_00000004) {
    local_8 = (int *)0x1;
    do {
      if (local_8 == (int *)0x0) break;
      local_7c[0] = 0;
      local_7c[1] = 0;
      local_7c[2] = 0;
      local_7c[3] = 0;
      local_7c[4] = 0xffffffff;
      local_7c[5] = 0xffffffff;
      local_7c[6] = 0xffffffff;
      local_7c[7] = 0xffffffff;
      local_7c[uVar7] = -1;
      local_7c[uVar7 + 4] = 0;
      local_8 = (int *)0x0;
      if (local_c != (int *)0x0) {
        piVar8 = local_b0;
        local_18 = local_c;
        do {
          iVar6 = FUN_0079df56(piVar8,local_7c,5);
          if ((iVar6 == 0) || (iVar6 = FUN_0079df56(piVar8,local_7c,5), iVar6 == 0)) {
            local_8 = (int *)0x1;
          }
          piVar8 = piVar8 + 4;
          local_18 = (int *)((int)local_18 + -1);
        } while (local_18 != (int *)0x0);
      }
      if ((local_4c[8] != 0) && (uVar7 != 3)) {
        local_8 = (int *)0x1;
      }
      if (local_8 == (int *)0x0) {
        iVar6 = FUN_007af2f0(local_7c,local_c,4);
        if (iVar6 < 0) {
          return iVar6;
        }
        iVar6 = FUN_007af2f0(local_7c + 4,local_c,4);
        goto LAB_0079e93b;
      }
      uVar7 = uVar7 + 1;
    } while (uVar7 < 4);
    local_8 = (int *)0x1;
    local_10 = (int *)0x0;
    do {
      if (local_8 == (int *)0x0) break;
      local_18 = (int *)0x0;
      do {
        piVar9 = local_10;
        piVar8 = local_18;
        if (local_18 != local_10) {
          local_7c[0] = 0;
          local_7c[1] = 0;
          local_7c[2] = 0;
          local_7c[3] = 0;
          local_7c[4] = 0xffffffff;
          local_7c[5] = 0xffffffff;
          local_7c[6] = 0xffffffff;
          local_7c[7] = 0xffffffff;
          local_7c[(int)local_10] = -1;
          piVar5 = local_c;
          local_7c[(int)piVar8] = -1;
          local_7c[(int)(piVar9 + 1)] = 0;
          local_7c[(int)(piVar8 + 1)] = 0;
          local_8 = (int *)0x0;
          local_24 = (int *)0x0;
          if (piVar5 != (int *)0x0) {
            piVar9 = local_b0;
            local_28 = local_c;
            do {
              local_80 = FUN_0079df56(piVar9,local_7c,5);
              iVar6 = FUN_0079df56(piVar9,local_7c + 4,5);
              if (local_80 == 0) {
                local_24 = (int *)0x1;
LAB_0079e6a8:
                local_8 = (int *)0x1;
              }
              else if (iVar6 == 0) goto LAB_0079e6a8;
              piVar9 = piVar9 + 4;
              local_28 = (int *)((int)local_28 + -1);
            } while (local_28 != (int *)0x0);
          }
          if (local_4c[8] != 0) {
            local_8 = (int *)0x1;
          }
          if (local_8 == (int *)0x0) {
            local_14 = (int *)0x1;
            break;
          }
          if ((local_24 == (int *)0x0) && ((local_4c[8] == 0 || (local_7c[3] != 0)))) {
            local_7c[8] = local_7c[0];
            iStack_58 = local_7c[1];
            iStack_54 = local_7c[2];
            iStack_50 = local_7c[3];
            local_4c[0] = -1;
            local_4c[1] = 0xffffffff;
            local_4c[2] = 0xffffffff;
            local_4c[3] = 0xffffffff;
            local_4c[4] = 0xffffffff;
            local_4c[5] = 0xffffffff;
            local_4c[6] = 0xffffffff;
            local_4c[7] = 0xffffffff;
            local_4c[(int)local_10] = 0;
            local_4c[(int)(local_18 + 1)] = 0;
            local_20 = (int *)0x1;
            piVar8 = local_18;
          }
        }
        local_18 = (int *)((int)piVar8 + 1);
      } while (local_18 < &DAT_00000004);
      local_10 = (int *)((int)local_10 + 1);
    } while (local_10 < &DAT_00000004);
    if (local_14 == (int *)0x0) {
      if (local_20 == (int *)0x0) goto LAB_0079e8e6;
      local_14 = (int *)0x1;
      iVar6 = FUN_007af2f0(local_7c + 8,local_c,4);
      if (iVar6 < 0) {
        return iVar6;
      }
      iVar6 = FUN_007af2f0(local_4c,local_c,4);
      if (iVar6 < 0) {
        return iVar6;
      }
      uVar10 = 4;
      piVar8 = local_4c;
    }
    else {
      iVar6 = FUN_007af2f0(local_7c,local_c,4);
      if (iVar6 < 0) {
        return iVar6;
      }
      uVar10 = 4;
LAB_0079e8ca:
      piVar8 = local_7c;
    }
    iVar6 = FUN_007af2f0(piVar8 + 4,local_c,uVar10);
    if (iVar6 < 0) {
      return iVar6;
    }
    if (local_14 != (int *)0x0) goto LAB_0079e93f;
  }
  else if (local_1c == (int *)0x3) {
    local_20 = (int *)0xffffffff;
    piVar8 = (int *)0x0;
    do {
      if (local_b0[(int)piVar8] == -1) {
        local_20 = piVar8;
      }
      piVar8 = (int *)((int)piVar8 + 1);
    } while (piVar8 < &DAT_00000004);
    local_10 = (int *)0x0;
    do {
      if (local_14 != (int *)0x0) goto LAB_0079e8b0;
      piVar8 = (int *)0x0;
      do {
        piVar5 = local_10;
        piVar9 = local_20;
        if (local_14 != (int *)0x0) break;
        if (((piVar8 != local_10) && (piVar8 != local_20)) && (local_10 != local_20)) {
          local_7c[0] = -1;
          local_7c[1] = -1;
          local_7c[2] = -1;
          local_7c[3] = -1;
          local_7c[4] = 0;
          local_7c[5] = 0;
          local_7c[6] = 0;
          local_7c[7] = 0;
          local_7c[(int)local_10] = 0;
          local_7c[(int)piVar8] = 0;
          local_7c[(int)(piVar5 + 1)] = -1;
          local_7c[(int)(piVar8 + 1)] = -1;
          local_7c[(int)(piVar9 + 1)] = -1;
          piVar9 = (int *)0x0;
          local_8 = (int *)0x0;
          if (local_c != (int *)0x0) {
            local_18 = local_b0;
            do {
              if (local_8 != (int *)0x0) break;
              iVar6 = FUN_0079df56(local_18,local_7c,5);
              if (iVar6 == 0) {
                local_8 = (int *)0x1;
              }
              local_18 = local_18 + 4;
              piVar9 = (int *)((int)piVar9 + 1);
            } while (piVar9 < local_c);
          }
          if ((local_7c[3] == 0) &&
             ((((local_7c[0] == 0 || (local_7c[1] == 0)) || (local_7c[2] == 0)) &&
              (local_4c[8] != 0)))) {
            local_8 = (int *)0x1;
          }
          if (local_8 == (int *)0x0) {
            local_14 = (int *)0x1;
          }
        }
        piVar8 = (int *)((int)piVar8 + 1);
      } while (piVar8 < &DAT_00000004);
      local_10 = (int *)((int)local_10 + 1);
    } while (local_10 < &DAT_00000004);
    if (local_14 != (int *)0x0) {
LAB_0079e8b0:
      iVar6 = FUN_007af2f0(local_7c,local_c,3);
      if (iVar6 < 0) {
        return iVar6;
      }
      uVar10 = 3;
      goto LAB_0079e8ca;
    }
  }
LAB_0079e8e6:
  piVar8 = (int *)0x0;
  if (local_1c != (int *)0x0) {
    do {
      piVar5 = local_c;
      piVar9 = local_1c;
      local_7c[0] = -1;
      local_7c[1] = 0xffffffff;
      local_7c[2] = 0xffffffff;
      local_7c[3] = 0xffffffff;
      local_7c[*(int *)(*(int *)(*(int *)((int)param_1 + 0x14) +
                                *(int *)(*(int *)(*(int *)((int)param_1 + 0x98) + 0x10) +
                                        (int)piVar8 * 4) * 4) + 0xc)] = 0;
      iVar6 = FUN_007af2f0(local_7c,piVar5,piVar9);
      if (iVar6 < 0) {
        return iVar6;
      }
      piVar8 = (int *)((int)piVar8 + 1);
    } while (piVar8 < local_1c);
  }
LAB_0079e93f:
  **(undefined4 **)((int)param_1 + 0x98) = 0;
  return 0;
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



/* function 00793567 FUN_00793567 */

undefined4 __thiscall FUN_00793567(int param_1,int param_2,int *param_3,int *param_4,int *param_5)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  uint *puVar4;
  uint *puVar5;
  void *pvVar6;
  undefined4 *puVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int *piVar11;
  byte *pbVar12;
  uint uVar13;
  bool bVar14;
  undefined1 local_168 [16];
  int local_158;
  uint local_150;
  int local_14c;
  int local_12c [30];
  int aiStack_b4 [5];
  undefined1 local_a0 [20];
  undefined4 local_8c;
  undefined1 local_7c [20];
  uint local_68;
  uint local_58 [16];
  int local_18;
  undefined **local_14;
  undefined **local_10;
  int *local_c;
  uint local_8;
  
  if (param_4 != (int *)0x0) {
    *param_4 = 0;
  }
  if (param_5 != (int *)0x0) {
    *param_5 = 0;
  }
  uVar9 = 0;
  uVar13 = (uint)param_3;
  if (param_3 != (int *)0x0) {
    do {
      iVar3 = *(int *)(uVar13 + 8);
      if ((((iVar3 == 0) || (*(int *)(iVar3 + 4) != 0xc)) || (*(int *)(iVar3 + 0x10) == 0)) ||
         (*(int *)(*(int *)(iVar3 + 0x10) + 4) != 8)) break;
      uVar13 = *(uint *)(uVar13 + 0xc);
      uVar9 = uVar9 + 1;
    } while (uVar13 != 0);
    if ((uVar13 != 0) || (4 < uVar9)) {
      return 1;
    }
  }
  local_18 = 0;
  local_c = &DAT_0087b45c;
  local_10 = (undefined **)0x0;
  local_58[0xf] = param_1;
  do {
    pbVar12 = (byte *)local_c[-10];
    pbVar2 = *(byte **)(param_2 + 8);
    do {
      bVar1 = *pbVar2;
      bVar14 = bVar1 < *pbVar12;
      if (bVar1 != *pbVar12) {
LAB_00793603:
        iVar3 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
        goto LAB_00793608;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar2[1];
      bVar14 = bVar1 < pbVar12[1];
      if (bVar1 != pbVar12[1]) goto LAB_00793603;
      pbVar2 = pbVar2 + 2;
      pbVar12 = pbVar12 + 2;
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_00793608:
    if (iVar3 == 0) {
      local_58[5] = 0xffffffff;
      local_58[6] = 0xffffffff;
      local_58[7] = 0xffffffff;
      local_58[8] = 0xffffffff;
      local_58[9] = 0xffffffff;
      local_58[10] = 0x1d;
      local_58[0xb] = 0x1d;
      local_58[0xc] = 0x1d;
      local_58[0xd] = 0x1d;
      local_58[0xe] = 0x1d;
      local_58[0] = 5;
      local_58[1] = 5;
      local_58[2] = 5;
      local_58[3] = 5;
      local_58[4] = 5;
      FUN_00782811();
      FUN_00782811();
      local_14 = (undefined **)0x1;
      local_8 = (uint)param_3;
      piVar11 = local_c;
      if (param_3 == (int *)0x0) {
LAB_007936db:
        piVar11 = local_c;
        if (local_c[-9] != 0) {
          if (local_58[local_c[-8]] == 5) {
            local_58[local_c[-8]] = *(uint *)local_c[-7];
          }
          if (local_58[piVar11[-6] + 10] == 0x1d) {
            local_58[piVar11[-6] + 10] = *(uint *)piVar11[-5];
          }
        }
        local_8 = 0;
        piVar11 = local_c + -5;
        do {
          puVar4 = (uint *)piVar11[-2];
          puVar5 = local_58 + local_8;
          uVar13 = *puVar5;
          if (uVar13 == 5) {
            if (puVar4 != (uint *)0x0) {
              *puVar5 = *puVar4;
            }
          }
          else {
            if ((uVar13 == 0) && ((uVar9 = *puVar4, uVar9 == 1 || (uVar9 == 2)))) {
              *puVar5 = uVar9;
            }
            else {
              for (; (*puVar4 != 5 && (uVar13 != *puVar4)); puVar4 = puVar4 + 1) {
              }
            }
            if (*puVar4 == 5) break;
          }
          puVar5 = (uint *)*piVar11;
          uVar13 = local_58[local_8 + 10];
          puVar4 = puVar5;
          if (uVar13 == 0x1d) {
            if (puVar5 != (uint *)0x0) {
              uVar13 = *puVar5;
LAB_00793851:
              local_58[local_8 + 10] = uVar13;
            }
          }
          else {
            for (; (*puVar4 != 0x1d && (uVar13 != *puVar4)); puVar4 = puVar4 + 1) {
            }
            if (*puVar4 == 0x1d) {
              uVar13 = *puVar5;
              goto LAB_00793851;
            }
          }
          if (local_58[local_8 + 5] == 0xffffffff) {
            local_58[local_8 + 5] = 1;
          }
          local_8 = local_8 + 1;
          piVar11 = piVar11 + 8;
        } while (local_8 < 5);
        if (local_8 == 5) {
          FUN_00782878();
          FUN_00782878();
          break;
        }
      }
      else {
        do {
          if (piVar11[-2] == 0) break;
          iVar3 = *(int *)(*(int *)(local_8 + 8) + 0x10);
          iVar8 = *piVar11;
          uVar13 = local_58[iVar8];
          if ((uVar13 == 5) ||
             ((uVar13 == 0 && ((*(int *)(iVar3 + 0x10) == 1 || (*(int *)(iVar3 + 0x10) == 2)))))) {
            local_58[iVar8] = *(uint *)(iVar3 + 0x10);
            aiStack_b4[iVar8] = piVar11[1];
          }
          else {
            if (*(uint *)(iVar3 + 0x10) == 0) {
              if ((uVar13 == 0) || (uVar13 == 1)) goto LAB_00793756;
              bVar14 = uVar13 == 2;
            }
            else {
              bVar14 = *(uint *)(iVar3 + 0x10) == uVar13;
            }
            if (!bVar14) break;
          }
LAB_00793756:
          iVar8 = piVar11[2];
          uVar13 = local_58[iVar8 + 10];
          if (uVar13 == 0x1d) {
            local_58[iVar8 + 10] = *(uint *)(iVar3 + 0x14);
            aiStack_b4[iVar8] = piVar11[3];
          }
          else {
            local_8c = *(undefined4 *)(iVar3 + 0x14);
            local_68 = uVar13;
            iVar8 = FUN_00792cd0(local_7c,local_a0,local_58 + piVar11[2] + 10);
            if (iVar8 < 0) break;
          }
          iVar8 = *(int *)(iVar3 + 0x10);
          if (iVar8 != 0) {
            uVar13 = piVar11[4];
            if ((int)uVar13 < 0) {
              if (*(uint *)(iVar3 + 0x18) < local_58[~uVar13 + 5]) {
                local_58[~uVar13 + 5] = *(uint *)(iVar3 + 0x18);
              }
            }
            else if (*(uint *)(iVar3 + 0x18) < uVar13) break;
            if (iVar8 != 0) {
              uVar13 = piVar11[5];
              if ((int)uVar13 < 0) {
                if (*(uint *)(iVar3 + 0x1c) < local_58[~uVar13 + 5]) {
                  local_58[~uVar13 + 5] = *(uint *)(iVar3 + 0x1c);
                }
              }
              else if (*(uint *)(iVar3 + 0x1c) < uVar13) break;
            }
          }
          if (((*(byte *)(piVar11 + -1) & 0x20) != 0) && (iVar3 = FUN_0079270f(iVar3), iVar3 != 0))
          break;
          local_8 = *(uint *)(local_8 + 0xc);
          local_14 = (undefined **)((int)local_14 + 1);
          piVar11 = piVar11 + 8;
        } while (local_8 != 0);
        if ((local_8 == 0) &&
           ((&DAT_00000004 < local_14 || (local_c[(int)local_14 * 8 + -10] == 0))))
        goto LAB_007936db;
      }
      FUN_00782878();
      FUN_00782878();
    }
    local_18 = local_18 + 1;
    local_10 = local_10 + 0x29;
    local_c = local_c + 0x29;
  } while (local_10 < (undefined **)0x31f8);
  if (local_18 == 0x4e) {
    return 1;
  }
  if (param_4 != (int *)0x0) {
    iVar3 = 5;
    do {
      FUN_00782811();
      iVar8 = local_18;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    uVar13 = 0;
    puVar5 = &local_150;
    puVar4 = (uint *)(&DAT_0087b44c + local_18 * 0xa4);
    do {
      if (puVar4[-6] == 0) break;
      uVar9 = puVar4[-5];
      if (uVar9 != 0) {
        puVar5[-2] = local_58[puVar4[-4]];
        puVar5[-1] = local_58[puVar4[-2] + 10];
        uVar10 = *puVar4;
        if ((int)uVar10 < 0) {
          uVar10 = local_58[~uVar10 + 5];
        }
        *puVar5 = uVar10;
        uVar10 = puVar4[1];
        if ((int)uVar10 < 0) {
          uVar10 = local_58[~uVar10 + 5];
        }
        puVar5[1] = uVar10;
        puVar5[2] = uVar9 & 0xc00;
        if ((uVar13 == 0) || ((uVar9 & 0x20) == 0)) {
          puVar5[2] = uVar9 & 0xc00 | 0x200;
        }
      }
      uVar13 = uVar13 + 1;
      puVar4 = puVar4 + 8;
      puVar5 = puVar5 + 9;
    } while (uVar13 < 5);
    if ((((local_158 == 1) || (local_158 == 2)) && (local_14c == 1)) && (local_150 == 1)) {
      local_158 = 0;
    }
    pvVar6 = operator_new(0x40);
    if (pvVar6 == (void *)0x0) {
      puVar7 = (undefined4 *)0x0;
    }
    else {
      puVar7 = (undefined4 *)FUN_00782904();
    }
    if (puVar7 == (undefined4 *)0x0) {
LAB_007939cb:
      FUN_0079353d(local_168,0x24,5,FUN_00782878);
      return 0x8007000e;
    }
    if ((&DAT_0087b438)[iVar8 * 0x29] != 0) {
      iVar3 = FUN_007828c3();
      puVar7[8] = iVar3;
      if (iVar3 == 0) {
LAB_00793b9d:
        (**(code **)*puVar7)(1);
        goto LAB_007939cb;
      }
    }
    param_3 = puVar7 + 9;
    if ((&PTR_DAT_0087b454)[iVar8 * 0x29] != (undefined *)0x0) {
      piVar11 = local_12c;
      local_10 = &PTR_DAT_0087b454 + iVar8 * 0x29;
      do {
        local_14 = local_10;
        pvVar6 = operator_new(0x14);
        if (pvVar6 == (void *)0x0) {
          iVar3 = 0;
        }
        else {
          iVar3 = FUN_00781fab(0,0,"Decls");
        }
        *param_3 = iVar3;
        if (iVar3 == 0) goto LAB_00793b9d;
        pvVar6 = operator_new(0x30);
        if (pvVar6 == (void *)0x0) {
          iVar3 = 0;
        }
        else {
          iVar3 = FUN_0078249a(1,0,0,0);
        }
        local_58[0xf] = iVar3;
        if (iVar3 == 0) goto LAB_00793b9d;
        *(int *)(*param_3 + 8) = iVar3;
        pvVar6 = operator_new(0x30);
        if (pvVar6 == (void *)0x0) {
          iVar8 = 0;
        }
        else {
          iVar8 = FUN_0078219e(param_2);
        }
        *(int *)(iVar3 + 0x14) = iVar8;
        if (iVar8 == 0) goto LAB_00793b9d;
        *(undefined **)(iVar8 + 0x18) = *local_10;
        pvVar6 = operator_new(0x3c);
        if (pvVar6 == (void *)0x0) {
          iVar3 = 0;
        }
        else {
          iVar3 = FUN_00782b9f();
        }
        if (iVar3 == 0) goto LAB_00793b9d;
        *(int *)(local_58[0xf] + 0x18) = iVar3;
        *(undefined4 *)(iVar3 + 0x10) = 0xffffffff;
        *(int *)(iVar3 + 0x14) = piVar11[1] * *piVar11;
        *(undefined4 *)(iVar3 + 0x18) = 2;
        *(undefined **)(iVar3 + 0x1c) = local_10[1];
        iVar8 = FUN_007828c3();
        *(int *)(iVar3 + 0x20) = iVar8;
        if (iVar8 == 0) goto LAB_00793b9d;
        param_3 = (int *)(*param_3 + 0xc);
        local_14 = local_14 + 8;
        piVar11 = piVar11 + 9;
        local_10 = local_14;
      } while (*local_14 != (undefined *)0x0);
    }
    *param_4 = (int)puVar7;
    FUN_0079353d(local_168,0x24,5,FUN_00782878);
  }
  iVar3 = local_18;
  iVar8 = 0;
  if (param_5 == (int *)0x0) {
    return 0;
  }
  pvVar6 = operator_new(0x14);
  if (pvVar6 != (void *)0x0) {
    iVar8 = FUN_00781fab(0,0,"Values");
  }
  if (iVar8 != 0) {
    pvVar6 = operator_new(0x40);
    if (pvVar6 == (void *)0x0) {
      iVar3 = 0;
    }
    else {
      iVar3 = FUN_00783256(2,*(undefined4 *)(&DAT_0087b430 + iVar3 * 0xa4),param_2);
    }
    *(int *)(iVar8 + 8) = iVar3;
    if (iVar3 != 0) {
      *param_5 = iVar8;
      return 0;
    }
  }
  if ((param_4 != (int *)0x0) && ((undefined4 *)*param_4 != (undefined4 *)0x0)) {
    (*(code *)**(undefined4 **)*param_4)(1);
  }
  return 0x8007000e;
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



/* function 00774678 FUN_00774678 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall
FUN_00774678(int param_1,undefined4 param_2,int param_3,undefined4 *param_4,undefined4 *param_5,
            uint param_6)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 *puVar13;
  uint uVar14;
  undefined4 uVar15;
  uint uVar16;
  undefined8 uVar17;
  undefined4 *local_7c [16];
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  undefined4 *local_10;
  undefined4 *local_c;
  uint local_8;
  
  local_10 = (undefined4 *)0x0;
  if ((*(byte *)(*(int *)(param_1 + 8) + 0x91) & 1) == 0) {
    uVar16 = -(uint)(param_4 != (undefined4 *)0x0) & param_6;
    uVar2 = -(uint)(param_5 != (undefined4 *)0x0) & param_6;
    local_8 = uVar2 + uVar16;
    uVar3 = FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,_DAT_0087a8a0);
    uVar4 = FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,_DAT_00862e38);
    uVar5 = FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,_DAT_00859060);
    uVar6 = FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,_DAT_0087a898);
    uVar7 = FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,_DAT_0087a890);
    uVar8 = FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,_DAT_0087a888);
    uVar9 = FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,_DAT_0087a880);
    uVar10 = FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,_DAT_0087a878);
    uVar11 = FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,_DAT_0087a870);
    uVar12 = FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,_DAT_0087a868);
    local_10 = operator_new(local_8 * 0x6c);
    if (local_10 != (undefined4 *)0x0) {
      uVar14 = 0;
      puVar13 = local_10;
      do {
        local_7c[uVar14] = puVar13;
        uVar14 = uVar14 + 1;
        puVar13 = puVar13 + local_8;
      } while (uVar14 < 0x1b);
      uVar14 = 0;
      do {
        uVar17 = FUN_00773063(local_7c[uVar14],local_8);
        if ((int)uVar17 < 0) goto LAB_00774c1d;
        uVar14 = (int)((ulonglong)uVar17 >> 0x20) + 1;
      } while (uVar14 < 0xf);
      param_6 = 0;
      if (local_8 != 0) {
        local_c = (undefined4 *)(param_3 + uVar16 * -4);
        puVar13 = local_7c[0xf];
        do {
          if (param_6 < uVar16) {
            uVar15 = *(undefined4 *)((int)puVar13 + ((int)param_4 - (int)local_7c[0xf]));
          }
          else {
            uVar15 = *(undefined4 *)(((int)param_5 - param_3) + (int)local_c);
          }
          *puVar13 = uVar15;
          *(undefined4 *)((int)puVar13 + (local_3c - (int)local_7c[0xf])) = uVar3;
          uVar15 = uVar4;
          if (uVar16 <= param_6) {
            uVar15 = uVar5;
          }
          *(undefined4 *)((int)puVar13 + (local_38 - (int)local_7c[0xf])) = uVar15;
          *(undefined4 *)((int)puVar13 + (local_34 - (int)local_7c[0xf])) = uVar6;
          *(undefined4 *)((int)puVar13 + (local_30 - (int)local_7c[0xf])) = uVar7;
          *(undefined4 *)((int)puVar13 + (local_2c - (int)local_7c[0xf])) = uVar8;
          *(undefined4 *)((int)puVar13 + (local_28 - (int)local_7c[0xf])) = uVar9;
          *(undefined4 *)((int)puVar13 + (local_24 - (int)local_7c[0xf])) = uVar10;
          *(undefined4 *)((int)puVar13 + (local_20 - (int)local_7c[0xf])) = uVar11;
          *(undefined4 *)((int)puVar13 + (local_1c - (int)local_7c[0xf])) = uVar12;
          *(undefined4 *)((int)puVar13 + (local_18 - (int)local_7c[0xf])) =
               *(undefined4 *)(param_1 + 0x20);
          if (param_6 < uVar16) {
            uVar15 = *(undefined4 *)((int)puVar13 + (param_3 - (int)local_7c[0xf]));
          }
          else {
            uVar15 = *local_c;
          }
          param_6 = param_6 + 1;
          local_c = local_c + 1;
          *(undefined4 *)((int)puVar13 + (local_14 - (int)local_7c[0xf])) = uVar15;
          puVar13 = puVar13 + 1;
        } while (param_6 < local_8);
      }
      local_c = (undefined4 *)(local_8 & 0xffffff);
      param_3 = CONCAT13(0x25,(int3)local_8);
      iVar1 = FUN_00773e3b(param_2,param_3,local_7c[0],local_14,local_3c,0);
      if (-1 < iVar1) {
        local_8 = (uint)local_c | 0x24000000;
        iVar1 = FUN_00773e3b(param_2,local_8,local_7c[1],local_7c[0],local_38,0);
        if ((((((((-1 < iVar1) &&
                 (iVar1 = FUN_00773e3b(param_2,(uint)local_c | 0x13000000,local_7c[2],local_7c[1],0,
                                       0x14), -1 < iVar1)) &&
                (iVar1 = FUN_00773e3b(param_2,param_3,local_7c[3],local_7c[2],local_34,4),
                -1 < iVar1)) &&
               ((iVar1 = FUN_00773e3b(param_2,local_8,local_7c[4],local_7c[3],local_30,0),
                -1 < iVar1 &&
                (iVar1 = FUN_00773e3b(param_2,param_3,local_7c[5],local_7c[4],local_7c[4],4),
                -1 < iVar1)))) &&
              ((iVar1 = FUN_00773e3b(param_2,param_3,local_7c[6],local_7c[5],local_2c,0), -1 < iVar1
               && ((iVar1 = FUN_00773e3b(param_2,local_8,local_7c[7],local_7c[6],local_28,0),
                   -1 < iVar1 &&
                   (iVar1 = FUN_00773e3b(param_2,param_3,local_7c[8],local_7c[5],local_7c[7],0),
                   -1 < iVar1)))))) &&
             (iVar1 = FUN_00773e3b(param_2,local_8,local_7c[9],local_7c[8],local_24,0), -1 < iVar1))
            && (((iVar1 = FUN_00773e3b(param_2,param_3,local_7c[10],local_7c[5],local_7c[9],0),
                 -1 < iVar1 &&
                 (iVar1 = FUN_00773e3b(param_2,local_8,local_7c[0xb],local_7c[10],local_20,0),
                 -1 < iVar1)) &&
                (iVar1 = FUN_00773e3b(param_2,param_3,local_7c[0xc],local_7c[5],local_7c[0xb],0),
                -1 < iVar1)))) &&
           (((iVar1 = FUN_00773e3b(param_2,local_8,local_7c[0xd],local_7c[0xc],local_1c,0),
             -1 < iVar1 &&
             (iVar1 = FUN_00773e3b(param_2,param_3,local_7c[0xe],local_7c[5],local_7c[0xd],0),
             -1 < iVar1)) &&
            (iVar1 = FUN_00773e3b(param_2,local_8,local_7c[0xf],local_7c[0xe],local_18,0x10),
            -1 < iVar1)))) {
          puVar13 = local_7c[0xf];
          for (uVar14 = uVar16 & 0x3fffffff; uVar14 != 0; uVar14 = uVar14 - 1) {
            *param_4 = *puVar13;
            puVar13 = puVar13 + 1;
            param_4 = param_4 + 1;
          }
          for (iVar1 = 0; iVar1 != 0; iVar1 = iVar1 + -1) {
            *(undefined1 *)param_4 = *(undefined1 *)puVar13;
            puVar13 = (undefined4 *)((int)puVar13 + 1);
            param_4 = (undefined4 *)((int)param_4 + 1);
          }
          puVar13 = local_7c[0xf] + uVar16;
          for (; uVar2 != 0; uVar2 = uVar2 - 1) {
            *param_5 = *puVar13;
            puVar13 = puVar13 + 1;
            param_5 = param_5 + 1;
          }
        }
      }
    }
  }
  else if (((param_4 == (undefined4 *)0x0) ||
           (iVar1 = FUN_00773e3b(param_2,param_6 & 0xffffff | 0x17000000,param_4,param_3,0,0x10),
           -1 < iVar1)) && (param_5 != (undefined4 *)0x0)) {
    FUN_00773e3b(param_2,param_6 & 0xffffff | 0x18000000,param_5,param_3,0,0x10);
  }
LAB_00774c1d:
                    /* WARNING: Subroutine does not return */
  _free(local_10);
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



/* function 0079e025 FUN_0079e025 */

int __fastcall FUN_0079e025(int param_1)

{
  undefined8 uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  uint *puVar4;
  int iVar5;
  int *piVar6;
  uint uVar7;
  void *pvVar8;
  uint *puVar9;
  undefined4 uVar10;
  uint *puVar11;
  int iVar12;
  bool bVar13;
  int local_ec [20];
  uint local_9c [12];
  int local_6c [4];
  undefined4 local_5c [4];
  int local_4c;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint *local_30;
  uint local_2c;
  int local_28;
  int *local_24;
  uint local_20;
  uint *local_1c;
  int local_18;
  int local_14;
  uint local_10;
  int *local_c;
  int local_8;
  
  local_8 = 0;
  local_14 = 0;
  local_34 = *(uint *)(param_1 + 0x88);
  local_38 = *(uint *)(param_1 + 0x138);
  bVar13 = local_34 < *(uint *)(param_1 + 0x138);
  do {
    local_14 = 0;
    if (!bVar13) {
      iVar12 = 0;
LAB_0079e391:
      if (local_8 != 0) {
        FUN_00784bd1();
      }
LAB_0079e39f:
      if (local_14 != 0) {
        FUN_00784bd1();
      }
      return iVar12;
    }
    puVar11 = *(uint **)(*(int *)(param_1 + 0x144) + local_34 * 4);
    local_30 = puVar11;
    if ((puVar11 != (uint *)0x0) && (*puVar11 != 0)) {
      local_10 = *puVar11 & 0xffffff;
      local_3c = puVar11[1] / local_10;
      local_20 = 0;
      if (local_3c != 0) {
        local_18 = 0;
        local_1c = local_9c;
        do {
          puVar4 = local_1c;
          puVar9 = local_1c + 1;
          *local_1c = 0xffffffff;
          *puVar9 = 0xffffffff;
          puVar4[2] = 0xffffffff;
          puVar4[3] = 0xffffffff;
          local_ec[0] = -1;
          local_ec[1] = 0xffffffff;
          local_ec[2] = 0xffffffff;
          local_ec[3] = 0xffffffff;
          local_28 = 0;
          local_2c = 0;
          if (local_10 == 0) {
LAB_0079e185:
            iVar12 = FUN_0079df56(local_1c,local_ec,2);
            if (iVar12 == 0) {
              local_4c = FUN_00784f26(*(undefined4 *)(param_1 + 0x60),0,3,0);
              if (local_4c == -1) goto LAB_0079e3b7;
              *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x14) + local_4c * 4) + 0x20) = 0;
              pvVar8 = operator_new(0x38);
              if (pvVar8 == (void *)0x0) {
                local_8 = 0;
              }
              else {
                local_8 = FUN_007851ab();
              }
              if (local_8 == 0) goto LAB_0079e3b7;
              iVar12 = FUN_00785202(0x30000003,6,1,0);
              if ((iVar12 < 0) || (iVar12 = FUN_007854e4(), iVar12 < 0)) goto LAB_0079e391;
              puVar2 = *(undefined4 **)
                        (*(int *)(param_1 + 0x14) + *(int *)(local_18 + puVar11[2]) * 4);
              local_24 = (int *)puVar2[3];
              local_c = (int *)0x0;
              do {
                if (local_c == local_24) {
                  uVar10 = *(undefined4 *)(param_1 + 0x200);
                }
                else {
                  uVar10 = *(undefined4 *)(param_1 + 0x1fc);
                }
                uVar1 = *(undefined8 *)(puVar2 + 4);
                uVar3 = *puVar2;
                local_5c[(int)local_c] = uVar10;
                iVar12 = FUN_00784f26(uVar3,0,local_c,uVar1);
                local_6c[(int)local_c] = iVar12;
                if (iVar12 == -1) goto LAB_0079e3b7;
                local_28 = *(int *)(*(int *)(param_1 + 0x14) + iVar12 * 4);
                FUN_0078572c();
                local_c = (int *)((int)local_c + 1);
                *(undefined4 *)(local_28 + 0x24) = *(undefined4 *)(local_18 + puVar11[2]);
              } while (local_c < (int *)0x3);
              puVar2 = *(undefined4 **)(local_8 + 8);
              *puVar2 = local_5c[0];
              puVar2[1] = local_5c[1];
              puVar2[2] = local_5c[2];
              iVar12 = *(int *)(local_8 + 8);
              *(int *)(iVar12 + 0xc) = local_6c[0];
              *(int *)(iVar12 + 0x10) = local_6c[1];
              *(int *)(iVar12 + 0x14) = local_6c[2];
              **(int **)(local_8 + 0x10) = local_4c;
              iVar12 = local_18;
              for (uVar7 = local_10; uVar7 != 0; uVar7 = uVar7 - 1) {
                *(int *)(iVar12 + local_30[2]) = local_4c;
                iVar12 = iVar12 + 4;
              }
              if (0x1ff < *(uint *)(param_1 + 0x138)) goto LAB_0079e3b7;
              *(int *)(*(int *)(param_1 + 0x144) + *(uint *)(param_1 + 0x138) * 4) = local_8;
              *(int *)(param_1 + 0x138) = *(int *)(param_1 + 0x138) + 1;
              local_8 = 0;
              puVar11 = local_30;
            }
          }
          else {
            local_24 = (int *)(*puVar11 & 0xff000000);
            piVar6 = (int *)(puVar11[2] + local_18);
            do {
              local_c = *(int **)(*(int *)(param_1 + 0x14) + *piVar6 * 4);
              uVar7 = local_2c;
              if ((local_24 != (int *)0x30000000) && (local_10 == puVar11[3])) {
                uVar7 = *(uint *)(*(int *)(*(int *)(param_1 + 0x14) +
                                          *(int *)(puVar11[4] + local_2c * 4) * 4) + 0xc);
              }
              iVar12 = uVar7 + local_20 * 4;
              if ((*(byte *)(*(int *)(*(int *)(param_1 + 0x10) + *local_c * 4) + 4) & 0x80) == 0) {
                local_9c[iVar12] = local_c[3];
              }
              else {
                local_9c[iVar12] = uVar7;
              }
              if (uVar7 == 3) {
                local_28 = 1;
              }
              local_ec[uVar7] = 0;
              local_2c = local_2c + 1;
              piVar6 = piVar6 + 1;
            } while (local_2c < local_10);
            if (((local_28 == 0) || (bVar13 = true, local_10 != 1)) ||
               ((local_24 == (int *)0x30000000 && (puVar11[3] == 1)))) goto LAB_0079e185;
            uVar7 = 0;
            puVar9 = local_1c;
            do {
              if ((*puVar9 != *(uint *)((int)&DAT_008dcfd0 + uVar7)) &&
                 (*(int *)((int)local_ec + uVar7) != -1)) {
                bVar13 = false;
              }
              uVar7 = uVar7 + 4;
              puVar9 = puVar9 + 1;
            } while (uVar7 < 0x10);
            if (!bVar13) goto LAB_0079e185;
          }
          local_20 = local_20 + 1;
          local_1c = local_1c + 4;
          local_18 = local_18 + local_10 * 4;
        } while (local_20 < local_3c);
      }
      pvVar8 = operator_new(0x38);
      if (pvVar8 == (void *)0x0) {
        local_14 = 0;
      }
      else {
        local_14 = FUN_007851ab();
      }
      if (local_14 != 0) {
        iVar12 = FUN_0078543d();
        iVar5 = local_14;
        if (iVar12 < 0) goto LAB_0079e39f;
        if (*(uint *)(param_1 + 0x138) < 0x200) {
          local_14 = 0;
          *(int *)(*(int *)(param_1 + 0x144) + *(uint *)(param_1 + 0x138) * 4) = iVar5;
          *(int *)(param_1 + 0x138) = *(int *)(param_1 + 0x138) + 1;
          *puVar11 = 0;
          goto LAB_0079e37f;
        }
      }
LAB_0079e3b7:
      iVar12 = -0x7ff8fff2;
      goto LAB_0079e391;
    }
LAB_0079e37f:
    local_34 = local_34 + 1;
    bVar13 = local_34 < local_38;
  } while( true );
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



/* function 00774c33 FUN_00774c33 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall
FUN_00774c33(int param_1,undefined4 param_2,int param_3,int param_4,int param_5,uint param_6)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  void *pvVar8;
  uint *puVar9;
  undefined8 uVar10;
  int local_80 [20];
  uint *local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  void *local_14;
  uint local_10;
  uint local_c;
  undefined4 local_8;
  
  local_14 = (void *)0x0;
  if ((*(byte *)(*(int *)(param_1 + 8) + 0x91) & 1) == 0) {
    local_10 = FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,_DAT_0087a8c8);
    local_c = FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,_DAT_0087a8c0);
    uVar3 = FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,_DAT_0087a8b8);
    uVar4 = FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,_DAT_0087a8b0);
    uVar5 = FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,_DAT_0087a8a8);
    uVar6 = FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,_DAT_00866b80);
    uVar7 = FUN_00784f26(*(undefined4 *)(*(int *)(param_1 + 8) + 0x50),0,0,_DAT_0086f418);
    local_14 = operator_new(param_6 * 0x6c);
    if (local_14 == (void *)0x0) goto LAB_00774cad;
    uVar2 = 0;
    pvVar8 = local_14;
    do {
      local_80[uVar2] = (int)pvVar8;
      uVar2 = uVar2 + 1;
      pvVar8 = (void *)((int)pvVar8 + param_6 * 4);
    } while (uVar2 < 0x1b);
    uVar2 = 0;
    do {
      uVar10 = FUN_00773063(local_80[uVar2],param_6);
      if ((int)uVar10 < 0) goto LAB_00774cad;
      uVar2 = (int)((ulonglong)uVar10 >> 0x20) + 1;
    } while (uVar2 < 0x13);
    if (param_6 != 0) {
      local_8 = param_6;
      puVar9 = local_30;
      do {
        *(undefined4 *)((local_80[0x13] - (int)local_30) + (int)puVar9) =
             *(undefined4 *)(param_1 + 0x20);
        *puVar9 = local_10;
        *(uint *)((local_2c - (int)local_30) + (int)puVar9) = local_c;
        *(undefined4 *)((local_28 - (int)local_30) + (int)puVar9) = uVar3;
        *(undefined4 *)((local_24 - (int)local_30) + (int)puVar9) = uVar4;
        *(undefined4 *)((local_20 - (int)local_30) + (int)puVar9) = uVar5;
        *(undefined4 *)((local_1c - (int)local_30) + (int)puVar9) = uVar6;
        *(undefined4 *)((local_18 - (int)local_30) + (int)puVar9) = uVar7;
        puVar9 = puVar9 + 1;
        local_8 = local_8 - 1;
      } while (local_8 != 0);
    }
    uVar2 = param_6 & 0xffffff;
    local_8 = CONCAT13(0x11,(int3)param_6);
    iVar1 = FUN_00773e3b(param_2,local_8,local_80[0],param_3,0,0);
    if (((iVar1 < 0) ||
        (iVar1 = FUN_00773e3b(param_2,uVar2 | 0x21000000,local_80[1],param_3,local_80[0],4),
        iVar1 < 0)) ||
       (iVar1 = FUN_00773e3b(param_2,local_8,local_80[2],local_80[1],0,8), iVar1 < 0))
    goto LAB_00774cad;
    local_c = uVar2 | 0x24000000;
    iVar1 = FUN_00773e3b(param_2,local_c,local_80[3],local_80[2],local_80[0x13],0);
    if ((iVar1 < 0) ||
       (iVar1 = FUN_00773e3b(param_2,uVar2 | 0x16000000,local_80[4],local_80[3],0,4), iVar1 < 0))
    goto LAB_00774cad;
    local_10 = uVar2 | 0x25000000;
    iVar1 = FUN_00773e3b(param_2,local_10,local_80[5],local_30,local_80[1],0);
    if (((((iVar1 < 0) ||
          ((iVar1 = FUN_00773e3b(param_2,local_c,local_80[6],local_80[5],local_2c,0), iVar1 < 0 ||
           (iVar1 = FUN_00773e3b(param_2,local_10,local_80[7],local_80[6],local_80[1],0), iVar1 < 0)
           ))) || (iVar1 = FUN_00773e3b(param_2,local_c,local_80[8],local_80[7],local_28,0),
                  iVar1 < 0)) ||
        ((((iVar1 = FUN_00773e3b(param_2,local_10,local_80[9],local_80[8],local_80[1],0), iVar1 < 0
           || (iVar1 = FUN_00773e3b(param_2,local_c,local_80[10],local_80[9],local_24,0), iVar1 < 0)
           ) || (iVar1 = FUN_00773e3b(param_2,local_10,local_80[0xb],local_80[10],local_80[4],0),
                iVar1 < 0)) ||
         ((iVar1 = FUN_00773e3b(param_2,local_10,local_80[0xc],local_80[0xb],local_20,0), iVar1 < 0
          || (iVar1 = FUN_00773e3b(param_2,local_c,local_80[0xd],local_80[0xc],local_1c,0),
             iVar1 < 0)))))) ||
       (((iVar1 = FUN_00773e3b(param_2,uVar2 | 0x22000000,local_80[0xe],param_3,local_80[0],
                               0x2000017), iVar1 < 0 ||
         ((iVar1 = FUN_00773e3b(param_2,local_10,local_80[0xf],local_80[0xd],local_80[0xe],0),
          iVar1 < 0 ||
          (iVar1 = FUN_00773e3b(param_2,local_c,local_80[0x10],local_80[0xb],local_80[0xf],4),
          iVar1 < 0)))) ||
        ((iVar1 = FUN_00773e3b(param_2,local_8,local_80[0x11],local_80[0x10],0,8), iVar1 < 0 ||
         ((iVar1 = FUN_00773e3b(param_2,local_c,local_80[0x12],local_80[0x11],local_18,0), iVar1 < 0
          || (((param_4 != 0 &&
               (iVar1 = FUN_00773e3b(param_2,uVar2 | 0x10000000,param_4,local_80[0x12],0,0),
               iVar1 < 0)) || (param_5 == 0)))))))))) goto LAB_00774cad;
    uVar2 = uVar2 | 0x10000000;
    param_3 = local_80[0x10];
  }
  else {
    if (((param_4 != 0) &&
        (iVar1 = FUN_00773e3b(param_2,param_6 & 0xffffff | 0x19000000,param_4,param_3,0,0),
        iVar1 < 0)) || (param_5 == 0)) goto LAB_00774cad;
    uVar2 = param_6 & 0xffffff | 0x1a000000;
  }
  FUN_00773e3b(param_2,uVar2,param_5,param_3,0x400000000);
LAB_00774cad:
                    /* WARNING: Subroutine does not return */
  _free(local_14);
}


