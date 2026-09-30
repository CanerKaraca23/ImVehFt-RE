/* Full-analysis function mapping; decompilation is not original source. */

/* function 004c8c90 FUN_004c8c90 */

void FUN_004c8c90(int param_1)

{
  DAT_00b4e3e9 = *(byte *)(param_1 + 0x584) & 1;
  DAT_00b4e3e8 = *(byte *)(param_1 + 0x584) >> 1 & 1;
  DAT_00b4e3eb = *(byte *)(param_1 + 0x584) >> 2 & 1;
  DAT_00b4e3ea = *(byte *)(param_1 + 0x584) >> 3 & 1;
  return;
}



/* function 004c8430 FUN_004c8430 */

void FUN_004c8430(undefined4 param_1)

{
  undefined4 *local_4;
  
  local_4 = &DAT_00b4dbe8;
  FUN_00749b70(param_1,FUN_004c83e0,&local_4);
  *local_4 = 0;
  return;
}



/* function 004c83e0 FUN_004c83e0 */

int FUN_004c83e0(int param_1,undefined4 param_2)

{
  uint uVar1;
  
  if ((*(byte *)(param_1 + 2) & 4) != 0) {
    uVar1 = FUN_00732370(param_1);
    if ((uVar1 & 0x1000) != 0) {
      FUN_0074c790(*(undefined4 *)(param_1 + 0x18),&LAB_004c83b0,param_2);
    }
    FUN_0074c790(*(undefined4 *)(param_1 + 0x18),&LAB_004c8220,param_2);
  }
  return param_1;
}


