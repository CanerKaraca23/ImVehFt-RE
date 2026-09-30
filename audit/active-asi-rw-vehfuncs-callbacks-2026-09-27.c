/* Full-analysis function mapping; decompilation is not original source. */

/* function 10022420 FUN_10022420 */

void __cdecl FUN_10022420(int param_1)

{
  byte *pbVar1;
  int iVar2;
  
  iVar2 = DAT_10113590;
  *(undefined4 *)(DAT_10113590 + 4 + param_1) = 0;
  *(undefined4 *)(iVar2 + param_1) = 0;
  pbVar1 = (byte *)(iVar2 + 9 + param_1);
  *pbVar1 = *pbVar1 & 0xf8;
  *(undefined1 *)(iVar2 + 8 + param_1) = 0x9c;
  return;
}



/* function 10022450 FUN_10022450 */

int __cdecl FUN_10022450(int param_1)

{
  if (*(LPVOID *)(DAT_10113590 + param_1) != (LPVOID)0x0) {
    FUN_100513ef(*(LPVOID *)(DAT_10113590 + param_1));
  }
  return param_1;
}



/* function 10022480 FUN_10022480 */

undefined4 __cdecl FUN_10022480(undefined4 param_1)

{
  return param_1;
}


