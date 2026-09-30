/* Full-analysis function mapping; decompilation is not original source. */

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


