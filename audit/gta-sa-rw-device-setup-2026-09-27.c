/* Temporary bounded Ghidra decompilation; not original source. */

/* entry 0x00801D50; bounded CFG instructions=73; body bytes=169 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint * BOUNDED_00801D50(uint *param_1,uint param_2)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  puVar1 = (uint *)param_1[4];
  uVar2 = param_1[2];
  while( true ) {
    if (puVar1 == param_1 + 4) {
      return (uint *)0x0;
    }
    uVar3 = (int)puVar1 + uVar2 + 8;
    if ((uVar3 <= param_2) && (param_2 <= param_1[1] * *param_1 + uVar3)) break;
    puVar1 = (uint *)*puVar1;
  }
  uVar3 = (param_2 - uVar3) / *param_1;
  uVar5 = uVar3 >> 3;
  *(byte *)((int)puVar1 + uVar5 + 8) =
       *(byte *)((int)puVar1 + uVar5 + 8) &
       ~(byte)(0x80 >> ((char)uVar3 + (char)uVar5 * -8 & 0x1fU));
  if ((param_1[6] & 2) != 0) {
    iVar4 = 0;
    uVar3 = 0;
    if (uVar2 != 0) {
      do {
        iVar4 = iVar4 + (uint)*(byte *)(uVar3 + 8 + (int)puVar1);
        uVar3 = uVar3 + 1;
      } while (uVar3 < uVar2);
      if (iVar4 != 0) {
        return param_1;
      }
    }
    *(uint *)puVar1[1] = *puVar1;
    *(uint *)(*puVar1 + 4) = puVar1[1];
    (**(code **)(_DAT_00c97b24 + 0x138))(puVar1);
  }
  return param_1;
}



/* entry 0x00801E00; bounded CFG instructions=57; body bytes=138 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int BOUNDED_00801E00(int *param_1)

{
  int *piVar1;
  uint uVar2;
  int *piVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  int iStack_4;
  
  iStack_4 = 0;
  uVar2 = param_1[2];
  piVar1 = param_1 + 4;
  piVar4 = (int *)param_1[4];
joined_r0x00801e1a:
  do {
    if (piVar4 == piVar1) {
      return *param_1 * iStack_4;
    }
    iVar6 = 0;
    *(int *)piVar4[1] = *piVar4;
    *(int *)(*piVar4 + 4) = piVar4[1];
    piVar3 = (int *)*piVar4;
    uVar5 = 0;
    if (uVar2 != 0) {
      do {
        iVar6 = iVar6 + (uint)*(byte *)(uVar5 + 8 + (int)piVar4);
        uVar5 = uVar5 + 1;
      } while (uVar5 < uVar2);
      if (iVar6 != 0) {
        iVar6 = *piVar1;
        piVar4[1] = (int)piVar1;
        *piVar4 = iVar6;
        *(int **)(*piVar1 + 4) = piVar4;
        *piVar1 = (int)piVar4;
        piVar4 = piVar3;
        goto joined_r0x00801e1a;
      }
    }
    (**(code **)(_DAT_00c97b24 + 0x138))(piVar4);
    iStack_4 = iStack_4 + 1;
    piVar4 = piVar3;
  } while( true );
}



/* entry 0x00801E90; bounded CFG instructions=100; body bytes=254 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * BOUNDED_00801E90(int *param_1,code *param_2,undefined4 param_3)

{
  byte bVar1;
  uint uVar2;
  int *piVar3;
  uint uVar4;
  int *piVar5;
  int *piVar6;
  uint uVar7;
  int *piVar8;
  
  uVar2 = param_1[2];
  piVar5 = (int *)param_1[4];
  if ((int *)param_1[4] == param_1 + 4) {
    return param_1;
  }
  do {
    piVar3 = (int *)(**(code **)(_DAT_00c97b24 + 0x134))(uVar2,0x10000);
    if (piVar3 == (int *)0x0) {
      return (int *)0x0;
    }
    piVar6 = piVar5 + 2;
    piVar8 = piVar3;
    for (uVar4 = uVar2 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *piVar8 = *piVar6;
      piVar6 = piVar6 + 1;
      piVar8 = piVar8 + 1;
    }
    for (uVar4 = uVar2 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(char *)piVar8 = (char)*piVar6;
      piVar6 = (int *)((int)piVar6 + 1);
      piVar8 = (int *)((int)piVar8 + 1);
    }
    uVar4 = 0;
    piVar6 = (int *)*piVar5;
    if (uVar2 != 0) {
      do {
        bVar1 = *(byte *)(uVar4 + (int)piVar3);
        if (bVar1 != 0) {
          uVar7 = 0;
          do {
            if ((bVar1 & (byte)(0x80 >> ((byte)uVar7 & 0x1f))) != 0) {
              (*param_2)(((int)piVar5 + uVar2 + param_1[3] + 7 & ~(param_1[3] - 1U)) +
                         (uVar7 + uVar4 * 8) * *param_1,param_3);
            }
            uVar7 = uVar7 + 1;
          } while (uVar7 < 8);
        }
        uVar4 = uVar4 + 1;
      } while (uVar4 < uVar2);
    }
    (**(code **)(_DAT_00c97b24 + 0x138))(piVar3);
    piVar5 = piVar6;
  } while (piVar6 != param_1 + 4);
  return param_1;
}



/* entry 0x008020F0; bounded CFG instructions=106; body bytes=312 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void BOUNDED_008020F0(void)

{
  byte *pbVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  
  piVar4 = _DAT_00c9a604;
  piVar5 = _DAT_00c9a634;
  while (_DAT_00c9a604 = piVar4, _DAT_00c9a634 = piVar5, piVar4 != (int *)&DAT_00c9a604) {
    piVar3 = piVar4 + -7;
    piVar5 = piVar4 + -3;
    *(int *)piVar4[1] = *piVar4;
    *(int *)(*piVar4 + 4) = piVar4[1];
    piVar2 = (int *)*piVar5;
    while (piVar2 != piVar5) {
      *(int *)piVar2[1] = *piVar2;
      *(int *)(*piVar2 + 4) = piVar2[1];
      (**(code **)(_DAT_00c97b24 + 0x138))(piVar2);
      piVar2 = (int *)*piVar5;
    }
    pbVar1 = (byte *)(piVar4 + -1);
    piVar4 = _DAT_00c9a604;
    piVar5 = _DAT_00c9a634;
    if ((*pbVar1 & 1) == 0) {
      if ((_DAT_00c9a634 == piVar3) || (_DAT_00c9a634 == (int *)0x0)) {
        (**(code **)(_DAT_00c97b24 + 0x138))(piVar3);
        piVar4 = _DAT_00c9a604;
        piVar5 = _DAT_00c9a634;
      }
      else {
        (**(code **)(_DAT_00c97b24 + 0x148))(_DAT_00c9a634,piVar3);
        piVar4 = _DAT_00c9a604;
        piVar5 = _DAT_00c9a634;
      }
    }
  }
  *(int *)piVar5[8] = piVar5[7];
  piVar4 = piVar5 + 4;
  *(int *)(piVar5[7] + 4) = piVar5[8];
  piVar3 = (int *)*piVar4;
  while (piVar3 != piVar4) {
    *(int *)piVar3[1] = *piVar3;
    *(int *)(*piVar3 + 4) = piVar3[1];
    (**(code **)(_DAT_00c97b24 + 0x138))(piVar3);
    piVar3 = (int *)*piVar4;
  }
  if ((*(byte *)(piVar5 + 6) & 1) == 0) {
    if ((_DAT_00c9a634 != piVar5) && (_DAT_00c9a634 != (int *)0x0)) {
      (**(code **)(_DAT_00c97b24 + 0x148))(_DAT_00c9a634,piVar5);
      _DAT_00c9a634 = (int *)0x0;
      _DAT_00c9a630 = 0;
      return;
    }
    (**(code **)(_DAT_00c97b24 + 0x138))(piVar5);
  }
  _DAT_00c9a634 = (int *)0x0;
  _DAT_00c9a630 = 0;
  return;
}



/* entry 0x008026E0; bounded CFG instructions=30; body bytes=87 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * BOUNDED_008026E0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)
           (**(code **)(_DAT_00c97b24 + 0x144))
                     (*(undefined4 *)(_DAT_00c9a65c + _DAT_00c97b24),0x30018);
  if (puVar1 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  puVar1[1] = param_1;
  puVar1[2] = param_2;
  puVar1[3] = param_3;
  puVar1[5] = 0;
  puVar1[6] = 0;
  *puVar1 = 0;
  func_0x008086e0(0x8e2670,puVar1);
  return puVar1;
}



/* entry 0x00802740; bounded CFG instructions=28; body bytes=86 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 BOUNDED_00802740(uint *param_1)

{
  if ((*param_1 & 1) != 0) {
    (**(code **)(_DAT_00c97b24 + 0x138))(param_1[5]);
    param_1[5] = 0;
    param_1[6] = 0;
    *param_1 = *param_1 & 0xfffffffe;
  }
  func_0x00808740(0x8e2670,param_1);
  (**(code **)(_DAT_00c97b24 + 0x148))(*(undefined4 *)(_DAT_00c9a65c + _DAT_00c97b24),param_1);
  return 1;
}



/* entry 0x008027A0; bounded CFG instructions=77; body bytes=188 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint * BOUNDED_008027A0(uint *param_1)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  uVar2 = param_1[3];
  if ((uVar2 == 4) || (uVar2 == 8)) {
    bVar1 = true;
    iVar3 = (1 << ((byte)uVar2 & 0x1f)) << 2;
  }
  else {
    bVar1 = false;
    iVar3 = 0;
  }
  uVar2 = ((int)(uVar2 + 7) >> 3) * param_1[1] + 3 & 0xfffffffc;
  iVar4 = param_1[2] * uVar2;
  param_1[4] = uVar2;
  iVar3 = iVar4 + iVar3;
  uVar2 = (**(code **)(_DAT_00c97b24 + 0x134))(iVar3,0x30018);
  param_1[5] = uVar2;
  if (uVar2 == 0) {
    uStack_8 = 1;
    uStack_4 = func_0x008088d0(0x80000013,iVar3);
    func_0x00808820(&uStack_8);
    return (uint *)0x0;
  }
  if (bVar1) {
    param_1[6] = uVar2 + iVar4;
    *param_1 = *param_1 | 1;
    return param_1;
  }
  param_1[6] = 0;
  *param_1 = *param_1 | 1;
  return param_1;
}


