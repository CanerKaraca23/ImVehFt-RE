/* Full-analysis function mapping; decompilation is not original source. */

/* function 10001ad0 FUN_10001ad0 */

void __cdecl FUN_10001ad0(int param_1)

{
  int iVar1;
  
  iVar1 = DAT_1003aacc;
  *(undefined4 *)(DAT_1003aacc + param_1) = 1;
  *(undefined4 *)(iVar1 + 4 + param_1) = 0;
  *(undefined4 *)(iVar1 + 8 + param_1) = 0;
  *(undefined4 *)(iVar1 + 0xc + param_1) = 0;
  return;
}



/* function 10001b00 FUN_10001b00 */

int __cdecl FUN_10001b00(int param_1)

{
  int iVar1;
  
  if ((param_1 != 0) && (iVar1 = *(int *)(DAT_1003aacc + 0xc + param_1), iVar1 != 0)) {
    (*(code *)0x7f3820)(iVar1);
  }
  return param_1;
}



/* function 10001b30 FUN_10001b30 */

int __cdecl FUN_10001b30(int param_1,int param_2)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar3 = DAT_1003aacc;
  puVar1 = (undefined4 *)(DAT_1003aacc + param_1);
  *puVar1 = *(undefined4 *)(DAT_1003aacc + param_2);
  puVar1[1] = *(undefined4 *)(iVar3 + 4 + param_2);
  puVar1[2] = *(undefined4 *)(iVar3 + 8 + param_2);
  if ((param_2 != 0) && (piVar2 = *(int **)(iVar3 + 0xc + param_2), piVar2 != (int *)0x0)) {
    iVar3 = *piVar2;
    uVar4 = (*(code *)0x7fb230)(*(undefined4 *)(iVar3 + 0xc),*(undefined4 *)(iVar3 + 0x10),0,5);
    uVar4 = (*(code *)0x7f37c0)(uVar4);
    puVar1[3] = uVar4;
  }
  return param_1;
}



/* function 100018a0 FUN_100018a0 */

int __cdecl FUN_100018a0(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  undefined1 local_10 [4];
  int local_c;
  short local_8 [2];
  
  iVar1 = (*(code *)0x7ed2d0)(param_1,1,&local_c,local_10);
  if ((iVar1 != 0) && (iVar1 = (*(code *)0x7ec9d0)(param_1,local_8,local_c), iVar1 == local_c)) {
    iVar1 = (*(code *)0x7f3600)();
    if (iVar1 != 0) {
      if (local_8[0] == 0) {
        return iVar1;
      }
      local_8[0] = local_8[0] + -1;
      iVar2 = (*(code *)0x730e60)(param_1);
      while (iVar2 != 0) {
        (*(code *)0x7f3980)(iVar1,iVar2);
        if (local_8[0] == 0) {
          (*(code *)0x7f3730)(iVar1,FUN_10001980,iVar1);
          return iVar1;
        }
        local_8[0] = local_8[0] + -1;
        iVar2 = (*(code *)0x730e60)(param_1);
      }
      (*(code *)0x7f3730)(iVar1,0x730e50,0);
      (*(code *)0x7f36a0)(iVar1);
    }
    return 0;
  }
  return 0;
}


