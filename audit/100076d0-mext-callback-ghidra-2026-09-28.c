/* Full-analysis function mapping; decompilation is not original source. */

/* function 10001db0 FUN_10001db0 */

undefined4 FUN_10001db0(undefined4 param_1,int param_2)

{
  HMODULE hModule;
  char *pcVar1;
  
  if (param_2 == 1) {
    hModule = GetModuleHandleA("ImVehFt.asi");
    GetModuleFileNameA(hModule,&DAT_1003a8c8,0x200);
    pcVar1 = _strrchr(&DAT_1003a8c8,0x5c);
    if (pcVar1 != (char *)0x0) {
      pcVar1 = _strrchr(&DAT_1003a8c8,0x5c);
      pcVar1[1] = '\0';
    }
    DAT_1003a6c5 = 1;
    DAT_1003a6c0 = FUN_10001520();
    DAT_1003a6c4 = 1;
    FUN_1000a560(6);
    FUN_1000a560(0xf);
    return 1;
  }
  if ((param_2 == 0) && (DAT_1003a6c4 != '\0')) {
    DAT_1003a6c4 = '\0';
    _fclose(DAT_1003a6c0);
  }
  return 1;
}



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



/* function 1000a560 FUN_1000a560 */

void __fastcall FUN_1000a560(int param_1)

{
                    /* WARNING: Could not recover jumptable at 0x1000a560. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)(&PTR_LAB_1000a618)[param_1])();
  return;
}



/* function 1000b4e0 FUN_1000b4e0 */

void FUN_1000b4e0(undefined4 param_1)

{
  int iVar1;
  
  if (DAT_1003c3b8 == (undefined **)0x0) {
    DAT_1003c3b8 = &PTR_vftable_10037760;
    (**(code **)(PTR_vftable_10037760 + 4))(0x53eca1,0,0,0,0);
  }
  if ((&param_1 < DAT_1003778c) && (DAT_10037788 <= &param_1)) {
    iVar1 = (int)&param_1 - (int)DAT_10037788;
    if (DAT_1003778c == DAT_10037790) {
      FUN_1000cfe0();
    }
    if (DAT_1003778c != (undefined4 *)0x0) {
      *DAT_1003778c = DAT_10037788[iVar1 >> 2];
    }
    DAT_1003778c = DAT_1003778c + 1;
    return;
  }
  if (DAT_1003778c == DAT_10037790) {
    FUN_1000cfe0();
  }
  if (DAT_1003778c != (undefined4 *)0x0) {
    *DAT_1003778c = param_1;
  }
  DAT_1003778c = DAT_1003778c + 1;
  return;
}


