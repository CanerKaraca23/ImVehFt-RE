/* Full-analysis function mapping; decompilation is not original source. */

/* function 007f0360 FUN_007f0360 */

void FUN_007f0360(undefined1 *param_1)

{
  undefined1 *puVar1;
  
  puVar1 = param_1 + 0x90;
  *param_1 = 0;
  *(undefined1 **)(param_1 + 0x94) = puVar1;
  param_1[1] = 0;
  *(undefined1 **)puVar1 = puVar1;
  param_1[2] = 0;
  param_1[3] = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x24) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x10) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0x20003;
  *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
  *(undefined4 *)(param_1 + 100) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x50) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 0x58) = 0;
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x74) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0;
  *(undefined4 *)(param_1 + 0x68) = 0;
  *(undefined4 *)(param_1 + 0x88) = 0;
  *(undefined4 *)(param_1 + 0x84) = 0;
  *(undefined4 *)(param_1 + 0x80) = 0;
  *(undefined4 *)(param_1 + 0x5c) = 0x20003;
  *(undefined4 *)(param_1 + 0x98) = 0;
  *(undefined4 *)(param_1 + 0x9c) = 0;
  *(undefined1 **)(param_1 + 0xa0) = param_1;
  FUN_008086e0(&DAT_008e2270,param_1);
  return;
}



/* function 007f0410 FUN_007f0410 */

int FUN_007f0410(void)

{
  int iVar1;
  
  iVar1 = (**(code **)(DAT_00c97b24 + 0x144))(*(undefined4 *)(DAT_00c9796c + DAT_00c97b24),0x3000e);
  if (iVar1 == 0) {
    return 0;
  }
  FUN_007f0360(iVar1);
  return iVar1;
}


