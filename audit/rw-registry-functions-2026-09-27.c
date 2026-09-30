/* Temporary bounded Ghidra decompilation; not original source. */

/* entry 0x007F3BB0; bounded CFG instructions=14; body bytes=39 */

void BOUNDED_007F3BB0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5)

{
  func_0x008084a0(0x8e23cc,param_1,param_2,param_3,param_4,param_5);
  return;
}



/* entry 0x007FB0B0; bounded CFG instructions=14; body bytes=39 */

void BOUNDED_007FB0B0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5)

{
  func_0x008084a0(0x8e2518,param_1,param_2,param_3,param_4,param_5);
  return;
}



/* entry 0x007F1260; bounded CFG instructions=14; body bytes=39 */

void BOUNDED_007F1260(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5)

{
  func_0x008084a0(0x8e2270,param_1,param_2,param_3,param_4,param_5);
  return;
}



/* entry 0x00804540; bounded CFG instructions=8; body bytes=16 */

void BOUNDED_00804540(void)

{
  func_0x00802740();
  return;
}



/* entry 0x008046A0; bounded CFG instructions=31; body bytes=58 */

uint BOUNDED_008046A0(void)

{
  char *pcVar1;
  uint in_EAX;
  int iVar2;
  int unaff_EBX;
  uint unaff_EDI;
  
  pcVar1 = (char *)(unaff_EBX + -0x3f7af73c);
  *pcVar1 = *pcVar1 + (char)in_EAX;
  if (*pcVar1 == '\0') {
    return in_EAX;
  }
  iVar2 = func_0x0080a4a0();
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = func_0x00808b40(0x8e23cc);
  return -(uint)(iVar2 != 0) & unaff_EDI;
}



/* entry 0x00804830; bounded CFG instructions=48; body bytes=127 */

uint __thiscall
BOUNDED_00804830(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined8 param_4)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = func_0x007f3ac0(&stack0x0000009f,param_1);
  if (uVar1 == 0) {
    func_0x00808c10(0x8e23cc);
    func_0x007f3530();
    func_0x007f3560();
    return 0;
  }
  if (*(int *)(uVar1 + 0x54) == 1) {
    *(uint *)(uVar1 + 0x50) = param_4._3_4_ & 0xffff;
  }
  func_0x007f3530();
  func_0x007f3560();
  iVar2 = func_0x00808980(0x8e23cc);
  return -(uint)(iVar2 != 0) & uVar1;
}



/* entry 0x008049A0; bounded CFG instructions=27; body bytes=67 */

void __thiscall BOUNDED_008049A0(int param_1)

{
  uint in_EAX;
  int iVar1;
  int in_stack_00000010;
  int *in_stack_00000014;
  
  iVar1 = (**(code **)(param_1 + 0xac))(in_EAX | 0x57);
  if (iVar1 == 0) {
    in_stack_00000014[1] = 0;
    return;
  }
  *in_stack_00000014 = *in_stack_00000014 + in_stack_00000010 + 0xc;
  iVar1 = func_0x00808b00(0x8e23cc);
  *in_stack_00000014 = *in_stack_00000014 + iVar1 + 0xc;
  return;
}



/* entry 0x00804B70; bounded CFG instructions=75; body bytes=177 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int BOUNDED_00804B70(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  
  iVar1 = param_1;
  iVar3 = (**(code **)(_DAT_00c97b24 + 0xac))(&param_1,param_1,0);
  if (iVar3 == 0) {
    param_2[1] = 0;
    return 0;
  }
  iVar3 = func_0x00808b00(0x8e23cc,iVar1);
  puVar2 = param_2;
  param_1 = param_1 + 0xc + iVar3;
  iVar3 = func_0x007ed270(*param_2,0x15,param_1,0x36003,0xffff);
  if (iVar3 == 0) {
    puVar2[1] = 0;
    return 0;
  }
  iVar3 = (**(code **)(_DAT_00c97b24 + 0xb4))(*puVar2,iVar1,param_1);
  if (iVar3 == 0) {
    puVar2[1] = 0;
    return 0;
  }
  iVar3 = func_0x00808b40(0x8e23cc,*puVar2,iVar1);
  if (iVar3 == 0) {
    puVar2[1] = 0;
    return 0;
  }
  return iVar1;
}



/* entry 0x00804D30; bounded CFG instructions=88; body bytes=264 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 BOUNDED_00804D30(void)

{
  uint *in_EAX;
  int iVar1;
  undefined4 unaff_ESI;
  bool bVar2;
  bool bVar3;
  uint in_stack_00000010;
  int in_stack_00000014;
  undefined4 in_stack_00000018;
  undefined4 in_stack_0000001c;
  short in_stack_00000024;
  
  bVar3 = (int)in_EAX + *in_EAX == 0;
  bVar2 = CARRY4((uint)in_EAX,*in_EAX);
  while (bVar2 || bVar3) {
    iVar1 = (**(code **)(_DAT_00c97b24 + 0xb0))();
    if ((iVar1 == 0) || (in_stack_00000014 == 0)) {
LAB_00804da3:
      func_0x007f3730();
      func_0x007f36a0();
      return 0;
    }
    iVar1 = func_0x00808980(0x8e23cc);
    if (iVar1 == 0) goto LAB_00804da3;
    func_0x007f3980();
    if (in_stack_00000024 == 0) {
      in_stack_00000024 = -1;
      iVar1 = func_0x00808980(0x8e23e4);
      if (iVar1 != 0) {
        return unaff_ESI;
      }
      goto LAB_00804da3;
    }
    in_stack_00000024 = in_stack_00000024 + -1;
    iVar1 = func_0x007ed2d0();
    if (iVar1 == 0) goto LAB_00804da3;
    if (in_stack_00000010 < 0x34000) break;
    bVar3 = in_stack_00000010 == 0x36003;
    bVar2 = in_stack_00000010 < 0x36003;
  }
  func_0x007f3730();
  func_0x007f36a0();
  in_stack_00000018 = 1;
  in_stack_0000001c = func_0x008088d0(0x80000004);
  func_0x00808820(&stack0x00000018);
  return 0;
}


