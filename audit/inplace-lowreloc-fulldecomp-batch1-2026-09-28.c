/* Full-analysis function mapping; decompilation is not original source. */

/* function 10003fe0 FUN_10003fe0 */

void __cdecl FUN_10003fe0(int param_1,int param_2)

{
  *(byte *)(param_1 + 2) = -(param_2 != 0) & 4;
  return;
}



/* function 100099e0 FUN_100099e0 */

void __cdecl FUN_100099e0(undefined *param_1)

{
  (*(code *)param_1)();
  return;
}



/* function 10010120 FUN_10010120 */

void __cdecl FUN_10010120(undefined4 param_1,undefined4 param_2)

{
  (*(code *)0x53cc70)(param_1,param_2);
  return;
}



/* function 10010140 FUN_10010140 */

void FUN_10010140(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  (*(code *)0x4041c0)(param_1,param_2,param_3,param_4);
  return;
}



/* function 10010170 FUN_10010170 */

void FUN_10010170(void)

{
  (*(code *)0x7281e0)();
  return;
}



/* function 10010180 FUN_10010180 */

void FUN_10010180(void)

{
  (*(code *)0x7170c0)(0xff,0xff,0xff,0xff);
  return;
}



/* function 10011650 _strlen */

/* Library Function - Single Match
    _strlen
   
   Library: Visual Studio */

size_t __cdecl _strlen(char *_Str)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  
  puVar2 = (uint *)_Str;
  do {
    if (((uint)puVar2 & 3) == 0) goto LAB_10011680;
    uVar1 = *puVar2;
    puVar2 = (uint *)((int)puVar2 + 1);
  } while ((char)uVar1 != '\0');
LAB_100116b3:
  return (size_t)((int)puVar2 + (-1 - (int)_Str));
LAB_10011680:
  do {
    do {
      puVar3 = puVar2;
      puVar2 = puVar3 + 1;
    } while (((*puVar3 ^ 0xffffffff ^ *puVar3 + 0x7efefeff) & 0x81010100) == 0);
    uVar1 = *puVar3;
    if ((char)uVar1 == '\0') {
      return (int)puVar3 - (int)_Str;
    }
    if ((char)(uVar1 >> 8) == '\0') {
      return (size_t)((int)puVar3 + (1 - (int)_Str));
    }
    if ((uVar1 & 0xff0000) == 0) {
      return (size_t)((int)puVar3 + (2 - (int)_Str));
    }
  } while ((uVar1 & 0xff000000) != 0);
  goto LAB_100116b3;
}



/* function 10012e65 __SEH_epilog4 */

/* WARNING: This is an inlined function */
/* Library Function - Single Match
    __SEH_epilog4
   
   Library: Visual Studio */

void __SEH_epilog4(void)

{
  undefined4 *unaff_EBP;
  undefined4 unaff_retaddr;
  
  ExceptionList = (void *)unaff_EBP[-4];
  *unaff_EBP = unaff_retaddr;
  return;
}


