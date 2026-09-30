/* Full-analysis function mapping; decompilation is not original source. */

/* function 007d61a0 FUN_007d61a0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_007d61a0(int param_1)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  float10 fVar6;
  float10 fVar7;
  ushort uVar8;
  byte *pbVar9;
  int iVar10;
  int iVar11;
  byte bVar12;
  int iVar13;
  uint uVar14;
  double dVar15;
  double dVar16;
  undefined2 local_44;
  undefined2 local_40;
  int local_34;
  byte local_30;
  double local_28;
  double local_20;
  double local_18;
  double local_10;
  
  uVar14 = *(uint *)(param_1 + 0x70);
  bVar1 = *(byte *)(param_1 + 0x126);
  if (((uVar14 & 0x100) != 0) && ((uVar14 & 0x1000) != 0)) {
    if ((bVar1 & 2) != 0) {
      if (bVar1 == 3) {
        pbVar9 = (byte *)((uint)*(byte *)(param_1 + 0x138) * 3 + *(int *)(param_1 + 0x114));
        *(ushort *)(param_1 + 0x13a) = (ushort)*pbVar9;
        *(ushort *)(param_1 + 0x13c) = (ushort)pbVar9[1];
        uVar8 = (ushort)pbVar9[2];
        goto LAB_007d627e;
      }
      goto switchD_007d61ef_caseD_3;
    }
    switch(*(undefined1 *)(param_1 + 0x127)) {
    case 1:
      uVar8 = *(short *)(param_1 + 0x140) * 0xff;
      break;
    case 2:
      uVar8 = *(short *)(param_1 + 0x140) * 0x55;
      break;
    default:
      goto switchD_007d61ef_caseD_3;
    case 4:
      uVar8 = *(short *)(param_1 + 0x140) * 0x11;
      break;
    case 8:
    case 0x10:
      uVar8 = *(ushort *)(param_1 + 0x140);
      *(ushort *)(param_1 + 0x13c) = uVar8;
      *(ushort *)(param_1 + 0x13a) = uVar8;
      goto LAB_007d627e;
    }
    *(ushort *)(param_1 + 0x140) = uVar8;
    *(ushort *)(param_1 + 0x13c) = uVar8;
    *(ushort *)(param_1 + 0x13a) = uVar8;
LAB_007d627e:
    *(ushort *)(param_1 + 0x13e) = uVar8;
  }
switchD_007d61ef_caseD_3:
  *(undefined4 *)(param_1 + 0x142) = *(undefined4 *)(param_1 + 0x138);
  *(undefined4 *)(param_1 + 0x146) = *(undefined4 *)(param_1 + 0x13c);
  *(undefined2 *)(param_1 + 0x14a) = *(undefined2 *)(param_1 + 0x140);
  if ((uVar14 & 0x602000) == 0) {
    if (((char)uVar14 < '\0') && (bVar1 == 3)) {
      bVar12 = *(byte *)(param_1 + 0x13a);
      bVar3 = *(byte *)(param_1 + 0x13c);
      local_40 = CONCAT11(bVar3,bVar12);
      uVar8 = *(ushort *)(param_1 + 0x11a);
      bVar4 = *(byte *)(param_1 + 0x13e);
      iVar10 = 0;
      if (uVar8 != 0) {
        pbVar9 = (byte *)(*(int *)(param_1 + 0x114) + 2);
        do {
          bVar5 = *(byte *)(iVar10 + *(int *)(param_1 + 0x188));
          if (bVar5 == 0) {
            *(undefined2 *)(pbVar9 + -2) = local_40;
            *pbVar9 = bVar4;
          }
          else if (bVar5 != 0xff) {
            uVar14 = (0xff - (uint)bVar5) * (uint)bVar12 + 0x80 + (uint)pbVar9[-2] * (uint)bVar5 &
                     0xffff;
            pbVar9[-2] = (byte)((uVar14 >> 8) + uVar14 >> 8);
            uVar14 = (uint)*(byte *)(*(int *)(param_1 + 0x188) + iVar10);
            uVar14 = (0xff - uVar14) * (uint)bVar3 + 0x80 + pbVar9[-1] * uVar14 & 0xffff;
            pbVar9[-1] = (byte)((uVar14 >> 8) + uVar14 >> 8);
            uVar14 = (uint)*(byte *)(*(int *)(param_1 + 0x188) + iVar10);
            uVar14 = (0xff - uVar14) * (uint)bVar4 + 0x80 + *pbVar9 * uVar14 & 0xffff;
            *pbVar9 = (byte)((uVar14 >> 8) + uVar14 >> 8);
          }
          iVar10 = iVar10 + 1;
          pbVar9 = pbVar9 + 3;
        } while (iVar10 < (int)(uint)uVar8);
      }
    }
    goto LAB_007d67e8;
  }
  FUN_007da080(param_1);
  if (-1 < *(char *)(param_1 + 0x70)) {
    if (bVar1 == 3) {
      uVar14 = (uint)*(ushort *)(param_1 + 0x118);
      if (uVar14 != 0) {
        pbVar9 = (byte *)(*(int *)(param_1 + 0x114) + 2);
        do {
          pbVar9[-2] = *(byte *)((uint)pbVar9[-2] + *(int *)(param_1 + 0x164));
          pbVar9[-1] = *(byte *)((uint)pbVar9[-1] + *(int *)(param_1 + 0x164));
          uVar14 = uVar14 - 1;
          *pbVar9 = *(byte *)((uint)*pbVar9 + *(int *)(param_1 + 0x164));
          pbVar9 = pbVar9 + 3;
        } while (uVar14 != 0);
      }
    }
    goto LAB_007d67e8;
  }
  if (bVar1 != 3) {
    cVar2 = *(char *)(param_1 + 0x130);
    local_18 = 1.0;
    uVar14 = (1 << (*(byte *)(param_1 + 0x127) & 0x1f)) - 1;
    local_28 = 1.0;
    if (cVar2 == '\x01') {
      local_18 = (double)*(float *)(param_1 + 0x160);
      local_28 = 1.0;
    }
    else if (cVar2 == '\x02') {
      local_18 = (double)((float)_DAT_0085a310 / *(float *)(param_1 + 0x15c));
      local_28 = (double)((float)_DAT_0085a310 /
                         (*(float *)(param_1 + 0x160) * *(float *)(param_1 + 0x15c)));
    }
    else if (cVar2 == '\x03') {
      local_18 = (double)((float)_DAT_0085a310 / *(float *)(param_1 + 0x134));
      local_28 = (double)((float)_DAT_0085a310 /
                         (*(float *)(param_1 + 0x160) * *(float *)(param_1 + 0x134)));
    }
    dVar16 = _DAT_0085a310 / (double)uVar14;
    if ((bVar1 & 2) == 0) {
      dVar15 = _pow((double)*(ushort *)(param_1 + 0x140) * dVar16,local_18);
      local_20._0_2_ =
           (undefined2)
           (int)ROUND((float)((float10)dVar15 * (float10)uVar14 + (float10)_DAT_00859060));
      *(undefined2 *)(param_1 + 0x14a) = local_20._0_2_;
      dVar16 = _pow((double)*(ushort *)(param_1 + 0x140) * dVar16,local_28);
      local_20._0_2_ =
           (undefined2)
           (int)ROUND((float)((float10)dVar16 * (float10)uVar14 + (float10)_DAT_00859060));
      *(undefined2 *)(param_1 + 0x140) = local_20._0_2_;
    }
    else {
      dVar15 = _pow((double)*(ushort *)(param_1 + 0x13a) * dVar16,local_18);
      local_20._0_2_ =
           (undefined2)
           (int)ROUND((float)((float10)dVar15 * (float10)uVar14 + (float10)_DAT_00859060));
      *(undefined2 *)(param_1 + 0x144) = local_20._0_2_;
      dVar15 = _pow((double)*(ushort *)(param_1 + 0x13c) * dVar16,local_18);
      local_20._0_2_ =
           (undefined2)
           (int)ROUND((float)((float10)dVar15 * (float10)uVar14 + (float10)_DAT_00859060));
      *(undefined2 *)(param_1 + 0x146) = local_20._0_2_;
      dVar15 = _pow((double)*(ushort *)(param_1 + 0x13e) * dVar16,local_18);
      local_20._0_2_ =
           (undefined2)
           (int)ROUND((float)((float10)dVar15 * (float10)uVar14 + (float10)_DAT_00859060));
      *(undefined2 *)(param_1 + 0x148) = local_20._0_2_;
      dVar15 = _pow((double)*(ushort *)(param_1 + 0x13a) * dVar16,local_28);
      local_20._0_2_ =
           (undefined2)
           (int)ROUND((float)((float10)dVar15 * (float10)uVar14 + (float10)_DAT_00859060));
      *(undefined2 *)(param_1 + 0x13a) = local_20._0_2_;
      dVar15 = _pow((double)*(ushort *)(param_1 + 0x13c) * dVar16,local_28);
      local_20._0_2_ =
           (undefined2)
           (int)ROUND((float)((float10)dVar15 * (float10)uVar14 + (float10)_DAT_00859060));
      *(undefined2 *)(param_1 + 0x13c) = local_20._0_2_;
      dVar16 = _pow((double)*(ushort *)(param_1 + 0x13e) * dVar16,local_28);
      local_20._0_2_ =
           (undefined2)
           (int)ROUND((float)((float10)dVar16 * (float10)uVar14 + (float10)_DAT_00859060));
      *(undefined2 *)(param_1 + 0x13e) = local_20._0_2_;
    }
    goto LAB_007d67e8;
  }
  iVar10 = *(int *)(param_1 + 0x114);
  uVar8 = *(ushort *)(param_1 + 0x118);
  cVar2 = *(char *)(param_1 + 0x130);
  if (cVar2 == '\x02') {
    iVar13 = *(int *)(param_1 + 0x164);
    bVar12 = *(byte *)((uint)*(ushort *)(param_1 + 0x13e) + iVar13);
    local_44 = CONCAT11(*(undefined1 *)((uint)*(ushort *)(param_1 + 0x13c) + iVar13),
                        *(undefined1 *)(iVar13 + (uint)*(ushort *)(param_1 + 0x13a)));
    iVar13 = *(int *)(param_1 + 0x16c);
    local_40._0_1_ = *(byte *)(iVar13 + (uint)*(ushort *)(param_1 + 0x13a));
    local_20._0_1_ = *(byte *)(iVar13 + (uint)*(ushort *)(param_1 + 0x13c));
    local_28._0_1_ = *(byte *)(iVar13 + (uint)*(ushort *)(param_1 + 0x13e));
  }
  else {
    if (cVar2 == '\x01') {
      local_10 = (double)*(float *)(param_1 + 0x160);
LAB_007d63b9:
      local_20 = 1.0;
    }
    else if (cVar2 == '\x02') {
      local_10 = (double)((float)_DAT_0085a310 / *(float *)(param_1 + 0x15c));
      local_20 = (double)((float)_DAT_0085a310 /
                         (*(float *)(param_1 + 0x160) * *(float *)(param_1 + 0x15c)));
    }
    else {
      if (cVar2 != '\x03') {
        local_10 = 1.0;
        goto LAB_007d63b9;
      }
      local_10 = (double)((float)_DAT_0085a310 / *(float *)(param_1 + 0x134));
      local_20 = (double)((float)_DAT_0085a310 /
                         (*(float *)(param_1 + 0x160) * *(float *)(param_1 + 0x134)));
    }
    if (_DAT_00859068 <= ABS(local_20 - _DAT_0085a310)) {
      dVar16 = _pow((double)*(ushort *)(param_1 + 0x13a) * _DAT_00883250,local_20);
      fVar7 = (float10)_DAT_00883248;
      fVar6 = (float10)_DAT_00859060;
      dVar15 = _pow((double)*(ushort *)(param_1 + 0x13c) * _DAT_00883250,local_20);
      local_28._0_1_ =
           (byte)(int)ROUND((float)((float10)dVar15 * (float10)_DAT_00883248 +
                                   (float10)_DAT_00859060));
      local_44 = CONCAT11(local_28._0_1_,(char)(int)ROUND((float)((float10)dVar16 * fVar7 + fVar6)))
      ;
      dVar16 = _pow((double)*(ushort *)(param_1 + 0x13e) * _DAT_00883250,local_20);
      local_40._0_1_ =
           (byte)(int)ROUND((float)((float10)dVar16 * (float10)_DAT_00883248 +
                                   (float10)_DAT_00859060));
      bVar12 = (byte)local_40;
    }
    else {
      local_44 = CONCAT11(*(undefined1 *)(param_1 + 0x13c),*(undefined1 *)(param_1 + 0x13a));
      bVar12 = *(byte *)(param_1 + 0x13e);
    }
    dVar16 = _pow((double)*(ushort *)(param_1 + 0x13a) * _DAT_00883250,local_10);
    local_40._0_1_ =
         (byte)(int)ROUND((float)((float10)dVar16 * (float10)_DAT_00883248 + (float10)_DAT_00859060)
                         );
    dVar16 = _pow((double)*(ushort *)(param_1 + 0x13c) * _DAT_00883250,local_10);
    local_20._0_1_ =
         (byte)(int)ROUND((float)((float10)dVar16 * (float10)_DAT_00883248 + (float10)_DAT_00859060)
                         );
    dVar16 = _pow((double)*(ushort *)(param_1 + 0x13e) * _DAT_00883250,local_10);
    local_28._0_1_ =
         (byte)(int)ROUND((float)((float10)dVar16 * (float10)_DAT_00883248 + (float10)_DAT_00859060)
                         );
  }
  iVar13 = 0;
  if (uVar8 != 0) {
    pbVar9 = (byte *)(iVar10 + 2);
    do {
      if ((iVar13 < (int)(uint)*(ushort *)(param_1 + 0x11a)) &&
         (bVar3 = *(byte *)(iVar13 + *(int *)(param_1 + 0x188)), bVar3 != 0xff)) {
        if (bVar3 == 0) {
          *(undefined2 *)(pbVar9 + -2) = local_44;
          *pbVar9 = bVar12;
        }
        else {
          uVar14 = (uint)*(byte *)((uint)pbVar9[-2] + *(int *)(param_1 + 0x16c)) * (uint)bVar3 +
                   0x80 + (0xff - (uint)bVar3) * (uint)(byte)local_40 & 0xffff;
          pbVar9[-2] = *(byte *)(((int)((uVar14 >> 8) + uVar14) >> 8 & 0xffU) +
                                *(int *)(param_1 + 0x168));
          uVar14 = (uint)*(byte *)(*(int *)(param_1 + 0x188) + iVar13);
          uVar14 = *(byte *)((uint)pbVar9[-1] + *(int *)(param_1 + 0x16c)) * uVar14 + 0x80 +
                   (0xff - uVar14) * (uint)local_20._0_1_ & 0xffff;
          pbVar9[-1] = *(byte *)(((int)((uVar14 >> 8) + uVar14) >> 8 & 0xffU) +
                                *(int *)(param_1 + 0x168));
          uVar14 = (uint)*(byte *)(*(int *)(param_1 + 0x188) + iVar13);
          uVar14 = *(byte *)((uint)*pbVar9 + *(int *)(param_1 + 0x16c)) * uVar14 + 0x80 +
                   (0xff - uVar14) * (uint)local_28._0_1_ & 0xffff;
          *pbVar9 = *(byte *)(((int)((uVar14 >> 8) + uVar14) >> 8 & 0xffU) +
                             *(int *)(param_1 + 0x168));
        }
      }
      else {
        pbVar9[-2] = *(byte *)((uint)pbVar9[-2] + *(int *)(param_1 + 0x164));
        pbVar9[-1] = *(byte *)((uint)pbVar9[-1] + *(int *)(param_1 + 0x164));
        *pbVar9 = *(byte *)((uint)*pbVar9 + *(int *)(param_1 + 0x164));
      }
      iVar13 = iVar13 + 1;
      pbVar9 = pbVar9 + 3;
    } while (iVar13 < (int)(uint)uVar8);
  }
LAB_007d67e8:
  if (((*(byte *)(param_1 + 0x70) & 8) != 0) && (bVar1 == 3)) {
    iVar13 = 8 - (uint)*(byte *)(param_1 + 0x17c);
    iVar10 = 8 - (uint)*(byte *)(param_1 + 0x17d);
    local_34 = 8 - (uint)*(byte *)(param_1 + 0x17e);
    if ((iVar13 < 0) || (8 < iVar13)) {
      iVar13 = 0;
    }
    if ((iVar10 < 0) || (8 < iVar10)) {
      iVar10 = 0;
    }
    if ((local_34 < 0) || (8 < local_34)) {
      local_34 = 0;
    }
    if (*(ushort *)(param_1 + 0x118) != 0) {
      iVar11 = 0;
      uVar14 = (uint)*(ushort *)(param_1 + 0x118);
      do {
        pbVar9 = (byte *)(*(int *)(param_1 + 0x114) + iVar11);
        *pbVar9 = *pbVar9 >> ((byte)iVar13 & 0x1f);
        local_30 = (byte)iVar10;
        pbVar9 = (byte *)(*(int *)(param_1 + 0x114) + 1 + iVar11);
        *pbVar9 = *pbVar9 >> (local_30 & 0x1f);
        pbVar9 = (byte *)(*(int *)(param_1 + 0x114) + 2 + iVar11);
        iVar11 = iVar11 + 3;
        *pbVar9 = *pbVar9 >> ((byte)local_34 & 0x1f);
        uVar14 = uVar14 - 1;
      } while (uVar14 != 0);
    }
  }
  return;
}


