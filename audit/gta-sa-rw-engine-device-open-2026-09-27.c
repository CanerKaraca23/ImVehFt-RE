/* Full-analysis function mapping; decompilation is not original source. */

/* function 008086e0 FUN_008086e0 */

int FUN_008086e0(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = *(undefined4 **)(param_1 + 0x10);
  while( true ) {
    if (puVar1 == (undefined4 *)0x0) {
      return param_1;
    }
    iVar2 = (*(code *)puVar1[8])(param_2,*puVar1,puVar1[1]);
    if (iVar2 == 0) break;
    puVar1 = (undefined4 *)puVar1[0xc];
  }
  for (puVar1 = (undefined4 *)puVar1[0xd]; puVar1 != (undefined4 *)0x0;
      puVar1 = (undefined4 *)puVar1[0xd]) {
    (*(code *)puVar1[9])(param_2,*puVar1,puVar1[1]);
  }
  return 0;
}



/* function 00803fe0 FUN_00803fe0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00803fe0(float param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  undefined4 local_1c;
  undefined1 local_10;
  undefined1 local_c;
  
  *(float *)(DAT_00c9a65c + 0x20c + DAT_00c97b24) = param_1;
  fVar1 = _DAT_00858624 / param_1;
  local_1c = 1;
  *(undefined1 *)(DAT_00c9a65c + 0xc + DAT_00c97b24) = 0;
  *(undefined1 *)(DAT_00c9a65c + 0x10c + DAT_00c97b24) = 0;
  do {
    fVar2 = (float)local_1c * _DAT_00859a3c;
    dVar3 = _pow((double)fVar2,(double)fVar1);
    local_10 = (undefined1)(int)ROUND((float)dVar3 * _DAT_00859aac + _DAT_00858b8c);
    *(undefined1 *)(DAT_00c9a65c + DAT_00c97b24 + 0xc + local_1c) = local_10;
    dVar3 = _pow((double)fVar2,(double)param_1);
    local_c = (undefined1)(int)ROUND((float)dVar3 * _DAT_00859aac + _DAT_00858b8c);
    *(undefined1 *)(DAT_00c9a65c + DAT_00c97b24 + 0x10c + local_1c) = local_c;
    local_1c = local_1c + 1;
  } while (local_1c < 0x100);
  return 1;
}



/* function 007f2ab0 FUN_007f2ab0 */

uint FUN_007f2ab0(int param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4,int param_5)

{
  uint uVar1;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  uVar1 = (**(code **)(param_1 + 4))(param_2,param_3,param_4,param_5);
  if (uVar1 != 0) {
    return uVar1;
  }
  switch(param_2) {
  case 0xd:
    *param_3 = 1;
    return 1;
  case 0xe:
    uVar1 = (uint)(param_5 == 0);
    if (uVar1 == 0) goto switchD_007f2ae7_default;
    (**(code **)(DAT_00c97b24 + 0xf8))(param_3,s_Only_rendering_sub_system_008e23b0);
    break;
  case 0xf:
    *param_3 = 0;
    return 1;
  case 0x10:
    uVar1 = (uint)(param_5 == 0);
    break;
  case 0x11:
  case 0x12:
    return 1;
  default:
    goto switchD_007f2ae7_default;
  }
  if (uVar1 != 0) {
    return uVar1;
  }
switchD_007f2ae7_default:
  uStack_8 = 1;
  uStack_4 = FUN_008088d0(0x18,param_2);
  FUN_00808820(&uStack_8);
  return 0;
}


