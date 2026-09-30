/* Full-analysis function mapping; decompilation is not original source. */

/* function 007f2e70 FUN_007f2e70 */

undefined4 FUN_007f2e70(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_00c97b24 + 0x10;
  iVar2 = FUN_007f2ab0(iVar1,2,0,0,0);
  if (iVar2 != 0) {
    iVar2 = FUN_008086e0(&DAT_008e2298,DAT_00c97b24);
    if (iVar2 != 0) {
      FUN_00803fe0(*(undefined4 *)(DAT_00c97b24 + 0x10));
      FUN_007f2ab0(iVar1,0x11,0,0,0);
      *(undefined4 *)(DAT_00c97b24 + 0x150) = 3;
      return 1;
    }
    FUN_007f2ab0(iVar1,3,0,0,0);
  }
  return 0;
}



/* function 007f3130 FUN_007f3130 */

bool FUN_007f3130(void)

{
  bool bVar1;
  
  bVar1 = DAT_00c97b20 == 0;
  if (bVar1) {
    FUN_00808320();
    FUN_00804240();
    FUN_008020f0();
    *(undefined4 *)(DAT_00c97b24 + 0x150) = 0;
  }
  return bVar1;
}



/* function 007f9c20 FUN_007f9c20 */

undefined4 * FUN_007f9c20(void)

{
  return &DAT_008e2498;
}



/* function 00804240 FUN_00804240 */

void FUN_00804240(void)

{
  return;
}



/* function 00808320 FUN_00808320 */

undefined4 FUN_00808320(void)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  if (DAT_00c9a6e4 != 0) {
    FUN_00801e90(DAT_00c9a6e4,&LAB_008083f0,DAT_00c9a6e4);
    if (*(undefined1 **)(DAT_00c97b24 + 0x144) != &LAB_00801c30) {
      uVar4 = 0;
      if (DAT_00c9a6ec != 0) {
        do {
          iVar3 = *(int *)(*(int *)(DAT_00c9a6e8 + uVar4 * 4) + 0x10);
          if (iVar3 != 0) {
            puVar1 = *(undefined4 **)(iVar3 + 0x38);
            do {
              iVar2 = *(int *)(iVar3 + 0x30);
              (**(code **)(DAT_00c97b24 + 0x148))(0,iVar3);
              iVar3 = iVar2;
            } while (iVar2 != 0);
            if ((puVar1 != (undefined4 *)0x0) && (puVar1[4] != 0)) {
              puVar1[4] = 0;
              *puVar1 = puVar1[1];
              puVar1[5] = 0;
            }
          }
          uVar4 = uVar4 + 1;
        } while (uVar4 < DAT_00c9a6ec);
      }
      if (DAT_00c9a6e8 != 0) {
        (**(code **)(DAT_00c97b24 + 0x138))(DAT_00c9a6e8);
        DAT_00c9a6e8 = 0;
      }
    }
    FUN_00801b80(DAT_00c9a6e4);
    DAT_00c9a6e4 = 0;
  }
  return 1;
}


