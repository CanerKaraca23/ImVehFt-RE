/* Temporary bounded Ghidra decompilation; not original source. */

/* entry 0x100076D0; bounded CFG instructions=761; body bytes=2174 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * BOUNDED_100076D0(int *param_1,int *param_2)

{
  uint *puVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  float *pfVar5;
  float *pfVar6;
  byte bVar7;
  char cVar8;
  float fVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  char *pcVar13;
  uint uVar14;
  int iVar15;
  undefined1 *puVar16;
  int iVar17;
  byte *pbVar18;
  byte *pbVar19;
  byte *pbVar20;
  undefined4 *puVar21;
  bool bVar22;
  char acStack_34 [32];
  int iStack_14;
  float fStack_10;
  int iStack_c;
  int iStack_8;
  
  iVar15 = _DAT_1003c248;
  iVar12 = _DAT_1003c1fc;
  if (_DAT_1003c1fc != 0) {
    iVar10 = func_0x10009360();
    iStack_c = *(int *)(*(int *)(iVar10 + 0x48) + ((iVar12 - *_DAT_00b74494) / 0xa18) * 4) + iVar15;
  }
  iStack_14 = *param_1;
  puVar1 = (uint *)(param_1 + 1);
  uVar11 = param_1[1] & 0xffffff;
  iVar12 = 0;
  iStack_8 = *(int *)(*_DAT_00c8800c +
                     *(short *)(*(int *)(_DAT_1003759c + _DAT_1003aef4 * 4) + 10) * 0xc);
  if (iStack_14 != 0) {
    iVar12 = *(int *)(_DAT_1003aacc + 8 + iStack_14);
  }
  if (((_DAT_00b4e47c != 0) && (iStack_14 != 0)) && (*(char *)(iStack_14 + 0x10) == '#')) {
    *(int **)*param_2 = param_1;
    *(int *)(*param_2 + 4) = *param_1;
    *param_2 = *param_2 + 8;
    if (iVar12 == 0) {
      *param_1 = _DAT_00b4e47c;
    }
    else {
      iVar12 = func_0x10001fb0(_DAT_00b4e47c,_DAT_1003c1ec / (float)_DAT_10024f08);
      *param_1 = iVar12;
    }
    *(uint **)*param_2 = puVar1;
    *(uint *)(*param_2 + 4) = *puVar1;
    *param_2 = *param_2 + 8;
    *puVar1 = *puVar1 | 0xffffff;
    return param_1;
  }
  _DAT_1003bc00 = 0;
  if (iStack_14 != 0) {
    if (iVar12 == 0) {
      pbVar19 = &UNK_1002496c;
      pbVar18 = (byte *)(iStack_14 + 0x10);
      do {
        bVar7 = *pbVar18;
        bVar22 = bVar7 < *pbVar19;
        if (bVar7 != *pbVar19) {
LAB_10007845:
          iVar12 = (1 - (uint)bVar22) - (uint)(bVar22 != 0);
          goto LAB_1000784a;
        }
        if (bVar7 == 0) break;
        bVar7 = pbVar18[1];
        bVar22 = bVar7 < pbVar19[1];
        if (bVar7 != pbVar19[1]) goto LAB_10007845;
        pbVar18 = pbVar18 + 2;
        pbVar19 = pbVar19 + 2;
      } while (bVar7 != 0);
      iVar12 = 0;
LAB_1000784a:
      if (iVar12 == 0) {
        (*(code *)0x74dbc0)(param_1,*(undefined4 *)(_DAT_1003bc78 * 4 + 0x1003c1a8));
      }
      pbVar19 = (byte *)(*param_1 + 0x10);
      pbVar20 = &UNK_10024980;
      pbVar18 = pbVar19;
      do {
        bVar7 = *pbVar18;
        bVar22 = bVar7 < *pbVar20;
        if (bVar7 != *pbVar20) {
LAB_10007892:
          iVar12 = (1 - (uint)bVar22) - (uint)(bVar22 != 0);
          goto LAB_10007897;
        }
        if (bVar7 == 0) break;
        bVar7 = pbVar18[1];
        bVar22 = bVar7 < pbVar20[1];
        if (bVar7 != pbVar20[1]) goto LAB_10007892;
        pbVar18 = pbVar18 + 2;
        pbVar20 = pbVar20 + 2;
      } while (bVar7 != 0);
      iVar12 = 0;
LAB_10007897:
      if (iVar12 == 0) {
        (*(code *)0x74dbc0)(param_1,*(undefined4 *)(_DAT_1003bc78 * 4 + 0x1003bbc0));
      }
      else {
        pbVar20 = &UNK_10024994;
        pbVar18 = pbVar19;
        do {
          bVar7 = *pbVar18;
          bVar22 = bVar7 < *pbVar20;
          if (bVar7 != *pbVar20) {
LAB_100078e0:
            iVar12 = (1 - (uint)bVar22) - (uint)(bVar22 != 0);
            goto LAB_100078e5;
          }
          if (bVar7 == 0) break;
          bVar7 = pbVar18[1];
          bVar22 = bVar7 < pbVar20[1];
          if (bVar7 != pbVar20[1]) goto LAB_100078e0;
          pbVar18 = pbVar18 + 2;
          pbVar20 = pbVar20 + 2;
        } while (bVar7 != 0);
        iVar12 = 0;
LAB_100078e5:
        if (iVar12 == 0) {
          (*(code *)0x74dbc0)(param_1,*(undefined4 *)(_DAT_1003bc78 * 4 + 0x1003bc30));
        }
        else {
          pbVar20 = &UNK_100249a8;
          pbVar18 = pbVar19;
          do {
            bVar7 = *pbVar18;
            bVar22 = bVar7 < *pbVar20;
            if (bVar7 != *pbVar20) {
LAB_10007930:
              iVar12 = (1 - (uint)bVar22) - (uint)(bVar22 != 0);
              goto LAB_10007935;
            }
            if (bVar7 == 0) break;
            bVar7 = pbVar18[1];
            bVar22 = bVar7 < pbVar20[1];
            if (bVar7 != pbVar20[1]) goto LAB_10007930;
            pbVar18 = pbVar18 + 2;
            pbVar20 = pbVar20 + 2;
          } while (bVar7 != 0);
          iVar12 = 0;
LAB_10007935:
          if (iVar12 == 0) {
            (*(code *)0x74dbc0)(param_1,*(undefined4 *)(_DAT_1003bc78 * 4 + 0x1003c208));
          }
          else if (((DAT_1003aef1 == '\0') && (_DAT_1003c1fc != 0)) &&
                  (*(char *)(iStack_c + 0x20) != '\0')) {
            iVar12 = func_0x10010d8b(pbVar19,&UNK_100249b8,10);
            if (iVar12 == 0) {
              *(int **)*param_2 = param_1;
              *(int *)(*param_2 + 4) = *param_1;
              *param_2 = *param_2 + 8;
              *param_1 = _DAT_1003bd9c;
            }
            else {
              iVar12 = func_0x10010d8b(*param_1 + 0x10,&UNK_100249c4,10);
              if ((iVar12 != 0) &&
                 (iVar12 = func_0x10010d8b(*param_1 + 0x10,&UNK_100249d0,10), iVar12 != 0))
              goto LAB_10007a09;
              *(int **)*param_2 = param_1;
              *(int *)(*param_2 + 4) = *param_1;
              *param_2 = *param_2 + 8;
              *param_1 = _DAT_1003bd9c;
            }
            piVar2 = param_1 + 3;
            *(int **)*param_2 = piVar2;
            *(int *)(*param_2 + 4) = *piVar2;
            *param_2 = *param_2 + 8;
            *piVar2 = _DAT_10024f94;
          }
        }
      }
    }
    else {
      fStack_10 = _DAT_1003c1ec / (float)_DAT_10024f08;
      *(int **)*param_2 = param_1;
      *(int *)(*param_2 + 4) = *param_1;
      *param_2 = *param_2 + 8;
      iVar12 = func_0x10001fb0(*param_1,fStack_10);
      *param_1 = iVar12;
    }
  }
LAB_10007a09:
  if ((iStack_8 == 0) || (iVar12 = (*(code *)0x7f39f0)(iStack_8,&UNK_100249dc), iVar12 == 0)) {
    iVar12 = _DAT_00b4e68c;
  }
  if ((iStack_14 == iVar12) || (iStack_14 == _DAT_00b4e68c)) {
    iVar12 = 0;
    do {
      iVar15 = iVar12;
      if (uVar11 == *(uint *)(iVar12 * 4 + 0x100374c0)) break;
      iVar12 = iVar12 + 1;
      iVar15 = -1;
    } while (iVar12 < 0x12);
    puVar1 = (uint *)(param_1 + 1);
    *(uint **)*param_2 = puVar1;
    *(uint *)(*param_2 + 4) = *puVar1;
    *param_2 = *param_2 + 8;
    *puVar1 = *puVar1 | 0xffffff;
    iVar12 = _DAT_1003c1fc;
    if (iVar15 != -1) {
      if (*(char *)(iVar15 + 0x1003aedc) == '\0') {
        return param_1;
      }
      if (*(char *)(iVar15 + 0x1003aedc) != '\x02') {
        *(int **)*param_2 = param_1;
        *(int *)(*param_2 + 4) = *param_1;
        *param_2 = *param_2 + 8;
        piVar2 = param_1 + 3;
        *(int **)*param_2 = piVar2;
        *(int *)(*param_2 + 4) = *piVar2;
        *param_2 = *param_2 + 8;
        *(int **)*param_2 = param_1 + 5;
        *(int *)(*param_2 + 4) = param_1[5];
        *param_2 = *param_2 + 8;
        *(int **)*param_2 = param_1 + 4;
        *(int *)(*param_2 + 4) = param_1[4];
        *param_2 = *param_2 + 8;
        if ((iStack_8 == 0) || (iVar12 = (*(code *)0x7f39f0)(iStack_8,&UNK_100249ec), iVar12 == 0))
        {
          iVar12 = _DAT_00b4e690;
        }
        iVar15 = _DAT_10024f94;
        *param_1 = iVar12;
        *piVar2 = iVar15;
        param_1[4] = 0;
        param_1[5] = 0;
        return param_1;
      }
      if (iStack_8 == 0) {
        return param_1;
      }
      iVar12 = (*(code *)0x7f39f0)(iStack_8,&UNK_10024a00);
      goto LAB_10007f2e;
    }
    iStack_14 = _DAT_1003c248;
    iVar17 = func_0x10009360();
    iVar10 = _DAT_1003c248;
    iVar15 = _DAT_1003c1fc;
    if (*(int *)(*(int *)(*(int *)(*(int *)(iVar17 + 0x48) + ((iVar12 - *_DAT_00b74494) / 0xa18) * 4
                                  ) + 0x28 + iStack_14) + 0x350) == 0) {
      return param_1;
    }
    iStack_c = 0;
    uVar14 = 0xff;
    while (uVar11 != uVar14) {
      uVar14 = uVar14 - 1;
      iStack_c = iStack_c + 1;
      if ((int)uVar14 < 0xf0) {
        return param_1;
      }
    }
    iVar12 = func_0x10009360();
    iVar12 = *(int *)(*(int *)(*(int *)(iVar12 + 0x48) + ((iVar15 - *_DAT_00b74494) / 0xa18) * 4) +
                      0x28 + iVar10) + 0x354 + iStack_c * 0x14;
    piVar2 = param_1 + 1;
    *(int **)*param_2 = piVar2;
    *(int *)(*param_2 + 4) = *piVar2;
    *param_2 = *param_2 + 8;
    iVar15 = *(int *)(iVar12 + 0xc);
    *(undefined2 *)piVar2 = *(undefined2 *)(iVar15 + 8);
    *(undefined1 *)((int)param_1 + 6) = *(undefined1 *)(iVar15 + 10);
    if (*(char *)(iVar12 + 9) == '\0') {
      return param_1;
    }
    piVar2 = param_1 + 3;
    *(int **)*param_2 = piVar2;
    *(int *)(*param_2 + 4) = *piVar2;
    *param_2 = *param_2 + 8;
    pfVar5 = (float *)(param_1 + 5);
    *(float **)*param_2 = pfVar5;
    *(float *)(*param_2 + 4) = *pfVar5;
    *param_2 = *param_2 + 8;
    pfVar6 = (float *)(param_1 + 4);
    *(float **)*param_2 = pfVar6;
    *(float *)(*param_2 + 4) = *pfVar6;
    *param_2 = *param_2 + 8;
    *piVar2 = _DAT_10024f90;
    fVar9 = (float)_DAT_1003c250;
    if (_DAT_1003c250 < 0) {
      fVar9 = fVar9 + _DAT_10024e90;
    }
    *pfVar6 = fVar9;
    fVar9 = (float)_DAT_1003c254;
    if (_DAT_1003c254 < 0) {
      fVar9 = fVar9 + _DAT_10024e90;
    }
    *pfVar5 = fVar9;
    pcVar13 = (char *)(*param_1 + 0x10);
    iVar12 = -(int)pcVar13;
    do {
      cVar8 = *pcVar13;
      pcVar13[(int)(acStack_34 + iVar12)] = cVar8;
      pcVar13 = pcVar13 + 1;
    } while (cVar8 != '\0');
    puVar21 = (undefined4 *)&stack0xffffffcb;
    do {
      pcVar13 = (char *)((int)puVar21 + 1);
      puVar21 = (undefined4 *)((int)puVar21 + 1);
    } while (*pcVar13 != '\0');
  }
  else {
    if (uVar11 == 0xff3c) {
      iVar12 = (int)*_DAT_10037594;
LAB_10007c3a:
      piVar2 = param_1 + 1;
      *(int **)*param_2 = piVar2;
      *(int *)(*param_2 + 4) = *piVar2;
      *param_2 = *param_2 + 8;
      if (((_DAT_1003c1fc != 0) && (*(int *)(iStack_c + 0x30) != 0)) &&
         (iVar12 < (int)(uint)*(byte *)(iStack_c + 0x2c))) {
        *(undefined1 *)piVar2 = *(undefined1 *)(*(int *)(iStack_c + 0x30) + iVar12 * 4);
        *(undefined1 *)((int)param_1 + 5) =
             *(undefined1 *)(*(int *)(iStack_c + 0x30) + 1 + iVar12 * 4);
        *(undefined1 *)((int)param_1 + 6) =
             *(undefined1 *)(*(int *)(iStack_c + 0x30) + 2 + iVar12 * 4);
        return param_1;
      }
      puVar16 = (undefined1 *)(*(code *)0x447090)(iVar12);
      *(undefined1 *)(param_1 + 1) = *puVar16;
      iVar15 = (*(code *)0x447090)(iVar12);
      *(undefined1 *)((int)param_1 + 5) = *(undefined1 *)(iVar15 + 1);
      iVar12 = (*(code *)0x447090)(iVar12);
      *(undefined1 *)((int)param_1 + 6) = *(undefined1 *)(iVar12 + 2);
      return param_1;
    }
    if (uVar11 == 0xaf00ff) {
      iVar12 = (int)_DAT_10037594[1];
      goto LAB_10007c3a;
    }
    if (uVar11 == 0xffff00) {
      iVar12 = (int)_DAT_10037594[2];
      goto LAB_10007c3a;
    }
    if (uVar11 == 0xff00ff) {
      iVar12 = (int)_DAT_10037594[3];
      goto LAB_10007c3a;
    }
    if (uVar11 == 0xff1200) {
      puVar1 = (uint *)(param_1 + 1);
      *(uint **)*param_2 = puVar1;
      *(uint *)(*param_2 + 4) = *puVar1;
      *param_2 = *param_2 + 8;
      if (DAT_1003aef0 == '\0') {
        *(undefined1 *)((int)param_1 + 7) = 0;
        return param_1;
      }
      *puVar1 = *puVar1 | 0xffffff;
      return param_1;
    }
    if (uVar11 == 0xff1000) {
      puVar1 = (uint *)(param_1 + 1);
      *(uint **)*param_2 = puVar1;
      *(uint *)(*param_2 + 4) = *puVar1;
      *param_2 = *param_2 + 8;
      *puVar1 = *puVar1 | 0xffffff;
      if (DAT_1003aeec == '\0') {
        return param_1;
      }
      piVar2 = param_1 + 3;
      *(int **)*param_2 = piVar2;
      *(int *)(*param_2 + 4) = *piVar2;
      *param_2 = *param_2 + 8;
      piVar3 = param_1 + 5;
      *(int **)*param_2 = piVar3;
      *(int *)(*param_2 + 4) = *piVar3;
      *param_2 = *param_2 + 8;
      *piVar2 = _DAT_10024f94;
      pcVar13 = (char *)(*param_1 + 0x10);
      *piVar3 = 0;
      iVar12 = -(int)pcVar13;
      do {
        cVar8 = *pcVar13;
        pcVar13[(int)(acStack_34 + iVar12)] = cVar8;
        pcVar13 = pcVar13 + 1;
      } while (cVar8 != '\0');
      puVar21 = (undefined4 *)&stack0xffffffcb;
      do {
        pcVar13 = (char *)((int)puVar21 + 1);
        puVar21 = (undefined4 *)((int)puVar21 + 1);
      } while (*pcVar13 != '\0');
    }
    else {
      iVar12 = func_0x10008e00();
      if (*(int *)(*(int *)(iVar12 + 0x28) + 0x350) == 0) {
        return param_1;
      }
      uVar14 = 0xff;
      iVar12 = 0;
      while (uVar11 != uVar14) {
        uVar14 = uVar14 - 1;
        iVar12 = iVar12 + 1;
        if ((int)uVar14 < 0xf0) {
          return param_1;
        }
      }
      iVar15 = func_0x10008e00();
      iVar12 = *(int *)(iVar15 + 0x28) + 0x354 + iVar12 * 0x14;
      piVar2 = param_1 + 1;
      *(int **)*param_2 = piVar2;
      *(int *)(*param_2 + 4) = *piVar2;
      *param_2 = *param_2 + 8;
      iVar15 = *(int *)(iVar12 + 0xc);
      *(undefined2 *)piVar2 = *(undefined2 *)(iVar15 + 8);
      *(undefined1 *)((int)param_1 + 6) = *(undefined1 *)(iVar15 + 10);
      if (*(char *)(iVar12 + 9) == '\0') {
        return param_1;
      }
      piVar2 = param_1 + 3;
      *(int **)*param_2 = piVar2;
      *(int *)(*param_2 + 4) = *piVar2;
      *param_2 = *param_2 + 8;
      piVar3 = param_1 + 5;
      *(int **)*param_2 = piVar3;
      *(int *)(*param_2 + 4) = *piVar3;
      *param_2 = *param_2 + 8;
      piVar4 = param_1 + 4;
      *(int **)*param_2 = piVar4;
      *(int *)(*param_2 + 4) = *piVar4;
      *param_2 = *param_2 + 8;
      *piVar2 = _DAT_10024f94;
      pcVar13 = (char *)(*param_1 + 0x10);
      *piVar4 = 0;
      iVar12 = -(int)pcVar13;
      *piVar3 = 0;
      do {
        cVar8 = *pcVar13;
        pcVar13[(int)(acStack_34 + iVar12)] = cVar8;
        pcVar13 = pcVar13 + 1;
      } while (cVar8 != '\0');
      puVar21 = (undefined4 *)&stack0xffffffcb;
      do {
        pcVar13 = (char *)((int)puVar21 + 1);
        puVar21 = (undefined4 *)((int)puVar21 + 1);
      } while (*pcVar13 != '\0');
    }
  }
  iVar12 = iStack_8;
  *puVar21 = _DAT_10024a14;
  iVar12 = (*(code *)0x7f39f0)(iVar12,acStack_34);
LAB_10007f2e:
  if (iVar12 != 0) {
    *(int **)*param_2 = param_1;
    *(int *)(*param_2 + 4) = *param_1;
    *param_2 = *param_2 + 8;
    *param_1 = iVar12;
  }
  return param_1;
}


