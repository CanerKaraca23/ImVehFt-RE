/* Full-analysis function mapping; decompilation is not original source. */

/* function 00553aa0 FUN_00553aa0 */

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



/* function 00553d00 FUN_00553d00 */

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



/* function 00732b40 FUN_00732b40 */

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


