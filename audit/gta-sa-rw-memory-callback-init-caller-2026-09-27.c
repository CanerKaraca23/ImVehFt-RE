/* Full-analysis function mapping; decompilation is not original source. */

/* function 00619c90 FUN_00619c90 */

undefined4 FUN_00619c90(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  undefined4 local_4;
  
  uVar1 = FUN_00745510(0,0x400000);
  iVar2 = FUN_007f3170(uVar1);
  if (iVar2 != 0) {
    FUN_0053ec10(3,0);
    FUN_00745520();
    iVar2 = FUN_0053ec10(9,0);
    if ((iVar2 == 2) || (iVar2 != 0)) {
      iVar2 = FUN_0053ec10(4,0);
      if ((iVar2 == 2) || (iVar2 != 0)) {
        local_4 = param_1;
        iVar2 = FUN_007f2f70(&local_4);
        if (iVar2 != 0) {
          uVar3 = FUN_0053ec10(0x17,param_1);
          if (uVar3 == 2) {
            iVar2 = FUN_00746190();
            uVar3 = (uint)(iVar2 != 0);
          }
          if (uVar3 != 0) {
            iVar2 = FUN_007f2e70();
            if (iVar2 != 0) {
              FUN_0053ec10(10,0);
              thunk_FUN_007f9c30();
              FUN_007f3530(1);
              FUN_007f3560(0);
              return 1;
            }
          }
          FUN_007f2f00();
        }
        FUN_007f3130();
        return 0;
      }
    }
  }
  return 0;
}


