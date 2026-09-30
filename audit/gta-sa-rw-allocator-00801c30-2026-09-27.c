/* Temporary bounded Ghidra decompilation; not original source. */

/* entry 0x00801C30; bounded CFG instructions=107; body bytes=286 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint BOUNDED_00801C30(int *param_1,undefined4 param_2)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  int *piVar6;
  uint uVar7;
  byte bVar8;
  uint uVar9;
  int *piVar10;
  int *piVar11;
  
  piVar4 = param_1;
  uVar5 = 0;
  piVar6 = (int *)param_1[4];
  uVar2 = param_1[2];
  if (piVar6 != param_1 + 4) {
    do {
      if (uVar5 != 0) {
        return uVar5;
      }
      param_1 = (int *)piVar4[1];
      uVar9 = 0;
      if (uVar2 != 0) {
        do {
          bVar1 = *(byte *)(uVar9 + 8 + (int)piVar6);
          if (bVar1 == 0xff) {
            param_1 = (int *)((int)param_1 + -8);
          }
          else {
            uVar7 = 0;
            do {
              if (param_1 == (int *)0x0) break;
              bVar8 = (byte)(0x80 >> ((byte)uVar7 & 0x1f));
              if ((bVar1 & bVar8) == 0) {
                *(byte *)(uVar9 + 8 + (int)piVar6) = bVar1 | bVar8;
                uVar5 = ((int)piVar6 + uVar2 + piVar4[3] + 7 & ~(piVar4[3] - 1U)) +
                        (uVar7 + uVar9 * 8) * *piVar4;
                if (uVar5 != 0) goto LAB_00801ccb;
                break;
              }
              uVar7 = uVar7 + 1;
              param_1 = (int *)((int)param_1 + -1);
            } while (uVar7 < 8);
          }
          uVar9 = uVar9 + 1;
        } while (uVar9 < uVar2);
      }
LAB_00801ccb:
      piVar6 = (int *)*piVar6;
    } while (piVar6 != piVar4 + 4);
    if (uVar5 != 0) {
      return uVar5;
    }
  }
  piVar10 = piVar4 + 4;
  piVar6 = (int *)(**(code **)(_DAT_00c97b24 + 0x134))
                            (piVar4[1] * *piVar4 + piVar4[3] + 7 + uVar2,param_2);
  uVar5 = 0;
  if (piVar6 != (int *)0x0) {
    piVar11 = piVar6 + 2;
    for (uVar5 = uVar2 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *piVar11 = 0;
      piVar11 = piVar11 + 1;
    }
    for (uVar5 = uVar2 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined1 *)piVar11 = 0;
      piVar11 = (int *)((int)piVar11 + 1);
    }
    iVar3 = *piVar10;
    piVar6[1] = (int)piVar10;
    *piVar6 = iVar3;
    *(int **)(*piVar10 + 4) = piVar6;
    *piVar10 = (int)piVar6;
    *(undefined1 *)(piVar6 + 2) = 0x80;
    uVar5 = (int)piVar6 + uVar2 + piVar4[3] + 7 & ~(piVar4[3] - 1U);
  }
  return uVar5;
}


