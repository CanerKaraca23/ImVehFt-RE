/* Temporary bounded Ghidra decompilation; not original source. */

/* entry 0x00749020; bounded CFG instructions=4; body bytes=15 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void BOUNDED_00749020(int param_1)

{
  *(undefined1 *)(_DAT_00c92478 + param_1) = 1;
  return;
}



/* entry 0x00749030; bounded CFG instructions=2; body bytes=5 */

undefined4 BOUNDED_00749030(undefined4 param_1)

{
  return param_1;
}



/* entry 0x00749040; bounded CFG instructions=6; body bytes=21 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void BOUNDED_00749040(int param_1,int param_2)

{
  *(undefined1 *)(_DAT_00c92478 + param_1) = *(undefined1 *)(_DAT_00c92478 + param_2);
  return;
}



/* entry 0x004C9A60; bounded CFG instructions=4; body bytes=19 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void BOUNDED_004C9A60(int param_1)

{
  *(undefined4 *)(_DAT_00b4e9e0 + 0x1c + param_1) = 0;
  return;
}



/* entry 0x004C9A80; bounded CFG instructions=16; body bytes=38 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int BOUNDED_004C9A80(int param_1)

{
  int *piVar1;
  int *piVar2;
  
  piVar1 = (int *)(_DAT_00b4e9e0 + 0x1c + param_1);
  piVar2 = (int *)*piVar1;
  if (piVar2 != (int *)0x0) {
    (**(code **)(*piVar2 + 8))(piVar2);
    *piVar1 = 0;
  }
  return param_1;
}



/* entry 0x0072F9C0; bounded CFG instructions=6; body bytes=19 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void BOUNDED_0072F9C0(int param_1)

{
  if (0 < _DAT_00c87c5c) {
    *(undefined1 *)(_DAT_00c87c5c + param_1) = 0;
  }
  return;
}



/* entry 0x0072F9E0; bounded CFG instructions=2; body bytes=5 */

undefined4 BOUNDED_0072F9E0(undefined4 param_1)

{
  return param_1;
}



/* entry 0x0072F9F0; bounded CFG instructions=14; body bytes=35 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int BOUNDED_0072F9F0(int param_1,int param_2)

{
  func_0x00821f40(_DAT_00c87c5c + param_1,_DAT_00c87c5c + param_2,0x17);
  return param_1;
}



/* entry 0x007321B0; bounded CFG instructions=4; body bytes=18 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void BOUNDED_007321B0(int param_1)

{
  *(undefined4 *)(_DAT_008d6090 + param_1) = 0;
  return;
}



/* entry 0x007321F0; bounded CFG instructions=2; body bytes=5 */

undefined4 BOUNDED_007321F0(undefined4 param_1)

{
  return param_1;
}



/* entry 0x007321D0; bounded CFG instructions=6; body bytes=21 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void BOUNDED_007321D0(int param_1,int param_2)

{
  *(undefined4 *)(_DAT_008d6090 + param_1) = *(undefined4 *)(_DAT_008d6090 + param_2);
  return;
}



/* entry 0x007C4750; bounded CFG instructions=6; body bytes=26 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void BOUNDED_007C4750(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)(_DAT_00c9b8c8 + param_1);
  puVar1[1] = 0;
  *puVar1 = 0xffffffff;
  return;
}



/* entry 0x007C4770; bounded CFG instructions=66; body bytes=188 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint BOUNDED_007C4770(uint param_1)

{
  undefined4 *puVar1;
  uint *puVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  puVar1 = (undefined4 *)(_DAT_00c9b8c8 + param_1);
  puVar2 = (uint *)puVar1[1];
  if (puVar2 != (uint *)0x0) {
    iVar4 = 0;
    if (0 < (int)puVar2[1]) {
      iVar5 = 0;
      do {
        iVar4 = iVar4 + 1;
        *(undefined4 *)(puVar2[4] + 0xc + iVar5) = 0;
        iVar5 = iVar5 + 0x10;
      } while (iVar4 < (int)puVar2[1]);
    }
    uVar3 = puVar2[5];
    if (uVar3 == param_1) {
      if ((*puVar2 & 1) == 0) {
        if ((*puVar2 & 2) == 0) {
          (**(code **)(_DAT_00c97b24 + 0x138))(puVar2[3]);
        }
        (**(code **)(_DAT_00c97b24 + 0x138))(puVar2[4]);
      }
      puVar2[3] = 0;
      puVar2[2] = 0;
      puVar2[4] = 0;
      func_0x007cd590(puVar2[8]);
      (**(code **)(_DAT_00c97b24 + 0x148))(_DAT_00c9b8cc,puVar2);
      if (uVar3 != 0) {
        *(undefined4 *)(_DAT_00c9b8c8 + 4 + uVar3) = 0;
      }
    }
    puVar1[1] = 0;
  }
  *puVar1 = 0xffffffff;
  return param_1;
}



/* entry 0x007C4830; bounded CFG instructions=60; body bytes=154 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int BOUNDED_007C4830(int param_1,int param_2)

{
  undefined4 *puVar1;
  uint *puVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  puVar3 = (undefined4 *)(param_2 + _DAT_00c9b8c8);
  puVar1 = (undefined4 *)(_DAT_00c9b8c8 + param_1);
  *puVar1 = *puVar3;
  puVar2 = (uint *)puVar3[1];
  if ((puVar2 != (uint *)0x0) && ((*puVar2 & 1) == 0)) {
    iVar4 = func_0x007c4c30(puVar2[1],0,0,*puVar2,*(undefined4 *)(puVar2[8] + 0x20));
    iVar6 = 0;
    if (0 < *(int *)(iVar4 + 4)) {
      iVar5 = 0;
      do {
        iVar6 = iVar6 + 1;
        *(undefined4 *)(*(int *)(iVar4 + 0x10) + 0xc + iVar5) = 0;
        *(undefined4 *)(iVar5 + 8 + *(int *)(iVar4 + 0x10)) = *(undefined4 *)(iVar5 + 8 + puVar2[4])
        ;
        *(undefined4 *)(iVar5 + 4 + *(int *)(iVar4 + 0x10)) = *(undefined4 *)(iVar5 + 4 + puVar2[4])
        ;
        *(undefined4 *)(iVar5 + *(int *)(iVar4 + 0x10)) = *(undefined4 *)(iVar5 + puVar2[4]);
        iVar5 = iVar5 + 0x10;
      } while (iVar6 < *(int *)(iVar4 + 4));
    }
    puVar1[1] = iVar4;
    *(int *)(iVar4 + 0x14) = param_1;
  }
  return param_1;
}


