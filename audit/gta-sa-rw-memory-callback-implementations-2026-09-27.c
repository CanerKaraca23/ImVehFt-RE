/* Full-analysis function mapping; decompilation is not original source. */

/* function 00801d50 FUN_00801d50 */

uint * FUN_00801d50(uint *param_1,uint param_2)

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
    (**(code **)(DAT_00c97b24 + 0x138))(puVar1);
  }
  return param_1;
}



/* function 00745510 FUN_00745510 */

undefined ** FUN_00745510(void)

{
  return &PTR_FUN_008d6228;
}


