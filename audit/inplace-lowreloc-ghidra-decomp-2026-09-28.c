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



/* function 10013a72 _EH4_CallFilterFunc */

/* Library Function - Single Match
    @_EH4_CallFilterFunc@8
   
   Library: Visual Studio 2010 Release */

void __fastcall _EH4_CallFilterFunc(undefined *param_1)

{
  (*(code *)param_1)();
  return;
}



/* function 10018090 __ValidateImageBase */

/* Library Function - Single Match
    __ValidateImageBase
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release */

BOOL __cdecl __ValidateImageBase(PBYTE pImageBase)

{
  if ((*(short *)pImageBase == 0x5a4d) &&
     (*(int *)(pImageBase + *(int *)(pImageBase + 0x3c)) == 0x4550)) {
    return (uint)((short)*(int *)((int)(pImageBase + *(int *)(pImageBase + 0x3c)) + 0x18) == 0x10b);
  }
  return 0;
}



/* function 100180d0 __FindPESection */

/* Library Function - Single Match
    __FindPESection
   
   Library: Visual Studio 2010 Release */

PIMAGE_SECTION_HEADER __cdecl __FindPESection(PBYTE pImageBase,DWORD_PTR rva)

{
  int iVar1;
  PIMAGE_SECTION_HEADER p_Var2;
  uint uVar3;
  
  iVar1 = *(int *)(pImageBase + 0x3c);
  uVar3 = 0;
  p_Var2 = (PIMAGE_SECTION_HEADER)
           (pImageBase + *(ushort *)(pImageBase + iVar1 + 0x14) + 0x18 + iVar1);
  if (*(ushort *)(pImageBase + iVar1 + 6) != 0) {
    do {
      if ((p_Var2->VirtualAddress <= rva) &&
         (rva < (p_Var2->Misc).PhysicalAddress + p_Var2->VirtualAddress)) {
        return p_Var2;
      }
      uVar3 = uVar3 + 1;
      p_Var2 = p_Var2 + 1;
    } while (uVar3 < *(ushort *)(pImageBase + iVar1 + 6));
  }
  return (PIMAGE_SECTION_HEADER)0x0;
}



/* function 10018f94 FUN_10018f94 */

void FUN_10018f94(void)

{
  code *in_EAX;
  
  (*in_EAX)();
  return;
}



/* function 1001ad68 _wcslen */

/* Library Function - Single Match
    _wcslen
   
   Libraries: Visual Studio 2010 Release, Visual Studio 2012 Release, Visual Studio 2015 Release,
   Visual Studio 2019 Release */

size_t __cdecl _wcslen(wchar_t *_Str)

{
  wchar_t wVar1;
  wchar_t *pwVar2;
  
  pwVar2 = _Str;
  do {
    wVar1 = *pwVar2;
    pwVar2 = pwVar2 + 1;
  } while (wVar1 != L'\0');
  return ((int)pwVar2 - (int)_Str >> 1) - 1;
}



/* function 1001b220 __alloca_probe */

/* WARNING: This is an inlined function */
/* Library Function - Single Match
    __chkstk
   
   Library: Visual Studio 2010 Release */

void __alloca_probe(void)

{
  undefined1 *in_EAX;
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 unaff_retaddr;
  undefined1 auStack_4 [4];
  
  puVar2 = (undefined4 *)((int)&stack0x00000000 - (int)in_EAX & ~-(uint)(&stack0x00000000 < in_EAX))
  ;
  for (puVar1 = (undefined4 *)((uint)auStack_4 & 0xfffff000); puVar2 < puVar1;
      puVar1 = puVar1 + -0x400) {
  }
  *puVar2 = unaff_retaddr;
  return;
}



/* function 1001b266 __alloca_probe_8 */

/* WARNING: This is an inlined function */
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */
/* Library Function - Single Match
    __alloca_probe_8
   
   Library: Visual Studio */

uint __alloca_probe_8(void)

{
  uint in_EAX;
  uint uVar1;
  
  uVar1 = 4 - in_EAX & 7;
  return in_EAX + uVar1 | -(uint)CARRY4(in_EAX,uVar1);
}



/* function 1001b65a _JumpToContinuation */

/* Library Function - Single Match
    void __stdcall _JumpToContinuation(void *,struct EHRegistrationNode *)
   
   Libraries: Visual Studio 2005 Release, Visual Studio 2008 Release, Visual Studio 2010 Release */

void _JumpToContinuation(void *param_1,EHRegistrationNode *param_2)

{
  ExceptionList = *(void **)ExceptionList;
                    /* WARNING: Could not recover jumptable at 0x1001b685. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*param_1)();
  return;
}



/* function 1001b68c FID_conflict:_CallMemberFunction1 */

/* Library Function - Multiple Matches With Different Base Names
    void __stdcall _CallMemberFunction1(void *,void *,void *)
    void __stdcall _CallMemberFunction2(void *,void *,void *,int)
   
   Libraries: Visual Studio 2005 Release, Visual Studio 2008 Release, Visual Studio 2010 Release */

void FID_conflict__CallMemberFunction1(undefined4 param_1,undefined *UNRECOVERED_JUMPTABLE)

{
  LOCK();
  UNLOCK();
                    /* WARNING: Could not recover jumptable at 0x1001b691. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)UNRECOVERED_JUMPTABLE)();
  return;
}



/* function 1001c9a5 FUN_1001c9a5 */

void FUN_1001c9a5(void)

{
  return;
}



/* function 1001c9d5 __fload_withFB */

/* Library Function - Single Match
    __fload_withFB
   
   Library: Visual Studio */

uint __fastcall __fload_withFB(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_2 + 4) & 0x7ff00000;
  if (uVar1 != 0x7ff00000) {
    return uVar1;
  }
  return *(uint *)(param_2 + 4);
}



/* function 1001ca18 FUN_1001ca18 */

uint __cdecl FUN_1001ca18(undefined4 param_1,uint param_2)

{
  if ((param_2 & 0x7ff00000) != 0x7ff00000) {
    return param_2 & 0x7ff00000;
  }
  return param_2;
}



/* function 1001cf82 ___AdjustPointer */

/* Library Function - Single Match
    ___AdjustPointer
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release */

int __cdecl ___AdjustPointer(int param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = *param_2 + param_1;
  if (-1 < param_2[1]) {
    iVar1 = iVar1 + *(int *)(*(int *)(param_2[1] + param_1) + param_2[2]) + param_2[1];
  }
  return iVar1;
}



/* function 1001e073 _ValidateRead */

/* Library Function - Single Match
    int __cdecl _ValidateRead(void const *,unsigned int)
   
   Library: Visual Studio 2010 Release */

int __cdecl _ValidateRead(void *param_1,uint param_2)

{
  return (uint)(param_1 != (void *)0x0);
}



/* function 1001fb89 ___hw_cw_sse2 */

/* Library Function - Single Match
    ___hw_cw_sse2
   
   Library: Visual Studio 2010 Release */

uint __fastcall ___hw_cw_sse2(undefined4 param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = 0;
  if ((param_2 & 0x10) != 0) {
    uVar1 = 0x80;
  }
  if ((param_2 & 8) != 0) {
    uVar1 = uVar1 | 0x200;
  }
  if ((param_2 & 4) != 0) {
    uVar1 = uVar1 | 0x400;
  }
  if ((param_2 & 2) != 0) {
    uVar1 = uVar1 | 0x800;
  }
  if ((param_2 & 1) != 0) {
    uVar1 = uVar1 | 0x1000;
  }
  if ((param_2 & 0x80000) != 0) {
    uVar1 = uVar1 | 0x100;
  }
  uVar2 = param_2 & 0x300;
  if (uVar2 != 0) {
    if (uVar2 == 0x100) {
      uVar1 = uVar1 | 0x2000;
    }
    else if (uVar2 == 0x200) {
      uVar1 = uVar1 | 0x4000;
    }
    else if (uVar2 == 0x300) {
      uVar1 = uVar1 | 0x6000;
    }
  }
  uVar2 = param_2 & 0x3000000;
  if (uVar2 == 0x1000000) {
    uVar1 = uVar1 | 0x8040;
  }
  else {
    if (uVar2 == 0x2000000) {
      return uVar1 | 0x40;
    }
    if (uVar2 == 0x3000000) {
      return uVar1 | 0x8000;
    }
  }
  return uVar1;
}



/* function 1002044b FUN_1002044b */

undefined4 FUN_1002044b(void)

{
  return 0;
}



/* function 1002044e __statfp */

/* Library Function - Single Match
    __statfp
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release */

int __statfp(void)

{
  short in_FPUStatusWord;
  
  return (int)in_FPUStatusWord;
}



/* function 1002045e __clrfp */

/* Library Function - Single Match
    __clrfp
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release */

int __clrfp(void)

{
  short in_FPUStatusWord;
  
  return (int)in_FPUStatusWord;
}



/* function 1002046f __ctrlfp */

/* Library Function - Single Match
    __ctrlfp
   
   Library: Visual Studio 2010 Release */

int __ctrlfp(void)

{
  short in_FPUControlWord;
  
  return (int)in_FPUControlWord;
}



/* function 10020564 ___mtold12 */

/* Library Function - Single Match
    ___mtold12
   
   Library: Visual Studio 2010 Release */

void __cdecl ___mtold12(char *param_1,int param_2,uint *param_3)

{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  uint *puVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  short local_8;
  
  puVar4 = param_3;
  uVar7 = 0;
  local_8 = 0x404e;
  *param_3 = 0;
  param_3[1] = 0;
  param_3[2] = 0;
  if (param_2 != 0) {
    param_3 = (uint *)0x0;
    do {
      uVar2 = *puVar4;
      uVar9 = *puVar4;
      uVar8 = puVar4[1];
      uVar1 = puVar4[2];
      bVar3 = false;
      uVar5 = (uVar7 * 2 | uVar2 >> 0x1f) * 2 | (uVar2 & 0x7fffffff) >> 0x1e;
      uVar2 = uVar2 * 4;
      uVar7 = ((int)param_3 * 2 | uVar7 >> 0x1f) * 2 | (uVar7 & 0x7fffffff) >> 0x1e;
      uVar6 = uVar9 + uVar2;
      *puVar4 = uVar2;
      puVar4[1] = uVar5;
      puVar4[2] = uVar7;
      if ((uVar6 < uVar2) || (uVar6 < uVar9)) {
        bVar3 = true;
      }
      *puVar4 = uVar6;
      uVar9 = uVar5;
      if (bVar3) {
        bVar3 = false;
        uVar9 = uVar5 + 1;
        if ((uVar9 < uVar5) || (uVar9 == 0)) {
          bVar3 = true;
        }
        puVar4[1] = uVar9;
        if (bVar3) {
          uVar7 = uVar7 + 1;
          puVar4[2] = uVar7;
        }
      }
      bVar3 = false;
      uVar2 = uVar9 + uVar8;
      if ((uVar2 < uVar9) || (uVar2 < uVar8)) {
        bVar3 = true;
      }
      puVar4[1] = uVar2;
      if (bVar3) {
        uVar7 = uVar7 + 1;
        puVar4[2] = uVar7;
      }
      bVar3 = false;
      param_3 = (uint *)((uVar7 + uVar1) * 2 | uVar2 >> 0x1f);
      uVar9 = uVar6 * 2;
      uVar8 = uVar2 * 2 | uVar6 >> 0x1f;
      puVar4[2] = (uint)param_3;
      *puVar4 = uVar9;
      puVar4[1] = uVar8;
      uVar7 = uVar9 + (int)*param_1;
      if ((uVar7 < uVar9) || (uVar7 < (uint)(int)*param_1)) {
        bVar3 = true;
      }
      *puVar4 = uVar7;
      uVar7 = uVar8;
      if (bVar3) {
        uVar7 = uVar8 + 1;
        bVar3 = false;
        if ((uVar7 < uVar8) || (uVar7 == 0)) {
          bVar3 = true;
        }
        puVar4[1] = uVar7;
        if (bVar3) {
          param_3 = (uint *)((int)param_3 + 1);
          puVar4[2] = (uint)param_3;
        }
      }
      param_2 = param_2 + -1;
      param_1 = param_1 + 1;
      puVar4[1] = uVar7;
      puVar4[2] = (uint)param_3;
    } while (param_2 != 0);
  }
  if (puVar4[2] == 0) {
    uVar7 = puVar4[1];
    do {
      local_8 = local_8 + -0x10;
      uVar9 = uVar7 >> 0x10;
      uVar7 = uVar7 << 0x10 | *puVar4 >> 0x10;
      puVar4[1] = uVar7;
      *puVar4 = *puVar4 << 0x10;
    } while (uVar9 == 0);
    puVar4[2] = uVar9;
  }
  uVar7 = puVar4[2];
  if ((uVar7 & 0x8000) == 0) {
    uVar9 = puVar4[1];
    do {
      local_8 = local_8 + -1;
      uVar8 = uVar7 * 2;
      uVar7 = uVar8 | uVar9 >> 0x1f;
      uVar9 = uVar9 * 2 | *puVar4 >> 0x1f;
      *puVar4 = *puVar4 * 2;
      puVar4[1] = uVar9;
      puVar4[2] = uVar7;
    } while ((uVar8 & 0x8000) == 0);
  }
  *(short *)((int)puVar4 + 10) = local_8;
  return;
}


