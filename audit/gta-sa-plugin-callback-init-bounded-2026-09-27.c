/* Temporary bounded Ghidra decompilation; not original source. */

/* entry 0x008087D0; bounded CFG instructions=12; body bytes=59 */

undefined4 BOUNDED_008087D0(undefined4 param_1,int param_2)

{
  DAT_00c9a6f4 = DAT_00c9a6f4 + 1;
  DAT_00c9a6f0 = param_2;
  *(undefined4 *)(DAT_00c97b24 + param_2) = 0;
  *(undefined4 *)(DAT_00c97b24 + 4 + DAT_00c9a6f0) = 0x80000000;
  return param_1;
}



/* entry 0x00808810; bounded CFG instructions=5; body bytes=16 */

undefined4 BOUNDED_00808810(undefined4 param_1)

{
  DAT_00c9a6f4 = DAT_00c9a6f4 + -1;
  return param_1;
}



/* entry 0x007EDE90; bounded CFG instructions=128; body bytes=543 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 BOUNDED_007EDE90(undefined4 param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  float fStack_8;
  undefined4 uStack_4;
  
  DAT_00c97934 = param_2;
  *(code **)(DAT_00c97b24 + 8 + param_2) = FUN_007ed730;
  *(undefined1 **)(DAT_00c97b24 + 0xc + DAT_00c97934) = &LAB_007ed670;
  *(code **)(DAT_00c97b24 + 0x10 + DAT_00c97934) = FUN_007ed880;
  *(undefined1 **)(DAT_00c97b24 + 0x14 + DAT_00c97934) = &LAB_007ed7d0;
  iVar1 = (**(code **)(DAT_00c97b24 + 0x134))(0x4000,0x40401);
  if (iVar1 == 0) {
    fStack_8 = 1.4013e-45;
    uStack_4 = FUN_008088d0(0x80000013,0x4000);
    FUN_00808820(&fStack_8);
    return 0;
  }
  fStack_8 = 1.0;
  uVar2 = 0;
  do {
    *(int *)(iVar1 + 0x2000 + uVar2 * 4) = (int)SQRT(fStack_8) + -0x1fc00000;
    fStack_8 = (float)((int)fStack_8 + 0x1000);
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x800);
  uVar2 = 0;
  do {
    *(int *)(iVar1 + uVar2 * 4) = (int)SQRT(fStack_8) + -0x20000000;
    fStack_8 = (float)((int)fStack_8 + 0x1000);
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x800);
  *(int *)(DAT_00c97b24 + DAT_00c97934) = iVar1;
  iVar1 = (**(code **)(DAT_00c97b24 + 0x134))(0x4000,0x40401);
  if (iVar1 == 0) {
    fStack_8 = 1.4013e-45;
    uStack_4 = FUN_008088d0(0x80000013,0x4000);
    FUN_00808820(&fStack_8);
    return 0;
  }
  fStack_8 = 1.0;
  uVar2 = 0;
  do {
    *(int *)(iVar1 + 0x2000 + uVar2 * 4) =
         (int)((float)_DAT_0085a310 / SQRT(fStack_8)) + -0x20000000;
    fStack_8 = (float)((int)fStack_8 + 0x1000);
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x800);
  uVar2 = 0;
  do {
    *(int *)(iVar1 + uVar2 * 4) = (int)((float)_DAT_0085a310 / SQRT(fStack_8)) + -0x1fc00000;
    fStack_8 = (float)((int)fStack_8 + 0x1000);
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x800);
  *(int *)(DAT_00c97b24 + 4 + DAT_00c97934) = iVar1;
  DAT_00c97938 = DAT_00c97938 + 1;
  return param_1;
}



/* entry 0x007EDE20; bounded CFG instructions=27; body bytes=110 */

undefined4 BOUNDED_007EDE20(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(DAT_00c97934 + 4 + DAT_00c97b24);
  if (iVar1 != 0) {
    (**(code **)(DAT_00c97b24 + 0x138))(iVar1);
    *(undefined4 *)(DAT_00c97934 + 4 + DAT_00c97b24) = 0;
  }
  if (*(int *)(DAT_00c97934 + DAT_00c97b24) != 0) {
    (**(code **)(DAT_00c97b24 + 0x138))(*(int *)(DAT_00c97934 + DAT_00c97b24));
    *(undefined4 *)(DAT_00c97934 + DAT_00c97b24) = 0;
  }
  DAT_00c97938 = DAT_00c97938 + -1;
  return param_1;
}



/* entry 0x0080AA40; bounded CFG instructions=5; body bytes=16 */

undefined4 BOUNDED_0080AA40(undefined4 param_1)

{
  DAT_00c9a728 = DAT_00c9a728 + 1;
  return param_1;
}



/* entry 0x0080AA50; bounded CFG instructions=5; body bytes=16 */

undefined4 BOUNDED_0080AA50(undefined4 param_1)

{
  DAT_00c9a728 = DAT_00c9a728 + -1;
  return param_1;
}



/* entry 0x007F16C0; bounded CFG instructions=45; body bytes=191 */

undefined4 BOUNDED_007F16C0(undefined4 param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  DAT_00c979bc = param_2;
  uVar2 = thunk_FUN_008019b0(0x40,DAT_008e2290,4,DAT_008e2294,&DAT_00c97998,0x4000d);
  *(undefined4 *)(DAT_00c97b24 + DAT_00c979bc) = uVar2;
  if (*(int *)(DAT_00c97b24 + DAT_00c979bc) == 0) {
    return 0;
  }
  *(undefined4 *)(DAT_00c97b24 + 4 + DAT_00c979bc) = 0x20000;
  *(undefined1 **)(DAT_00c97b24 + 8 + DAT_00c979bc) = &LAB_007f12f0;
  puVar1 = (undefined4 *)(DAT_00c97b24 + 0xc + DAT_00c979bc);
  *puVar1 = 0x3c23d70a;
  puVar1[1] = 0x3c23d70a;
  puVar1[2] = 0x3c23d70a;
  DAT_00c979c0 = DAT_00c979c0 + 1;
  return param_1;
}



/* entry 0x007F1660; bounded CFG instructions=16; body bytes=61 */

undefined4 BOUNDED_007F1660(undefined4 param_1)

{
  if (*(int *)(DAT_00c979bc + DAT_00c97b24) != 0) {
    FUN_00801b80(*(int *)(DAT_00c979bc + DAT_00c97b24));
    *(undefined4 *)(DAT_00c979bc + DAT_00c97b24) = 0;
  }
  DAT_00c979c0 = DAT_00c979c0 + -1;
  return param_1;
}



/* entry 0x007EFEF0; bounded CFG instructions=32; body bytes=124 */

undefined4 BOUNDED_007EFEF0(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  DAT_00c9796c = param_2;
  uVar1 = thunk_FUN_008019b0(DAT_008e2270,DAT_008e2288,4,DAT_008e228c,&DAT_00c97974,0x4000e);
  *(undefined4 *)(DAT_00c97b24 + DAT_00c9796c) = uVar1;
  if (*(int *)(DAT_00c97b24 + DAT_00c9796c) == 0) {
    return 0;
  }
  *(int *)(DAT_00c97b24 + 0xbc) = DAT_00c97b24 + 0xbc;
  *(int *)(DAT_00c97b24 + 0xc0) = DAT_00c97b24 + 0xbc;
  DAT_00c97970 = DAT_00c97970 + 1;
  return param_1;
}



/* entry 0x007EFF70; bounded CFG instructions=16; body bytes=61 */

undefined4 BOUNDED_007EFF70(undefined4 param_1)

{
  if (*(int *)(DAT_00c9796c + DAT_00c97b24) != 0) {
    FUN_00801b80(*(int *)(DAT_00c9796c + DAT_00c97b24));
    *(undefined4 *)(DAT_00c9796c + DAT_00c97b24) = 0;
  }
  DAT_00c97970 = DAT_00c97970 + -1;
  return param_1;
}



/* entry 0x007EC780; bounded CFG instructions=26; body bytes=96 */

undefined4 BOUNDED_007EC780(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  DAT_00c9792c = param_2;
  uVar1 = thunk_FUN_008019b0(0x24,DAT_008e2218,4,DAT_008e221c,&DAT_00c97908,0x40404);
  *(undefined4 *)(DAT_00c97b24 + DAT_00c9792c) = uVar1;
  if (*(int *)(DAT_00c97b24 + DAT_00c9792c) == 0) {
    return 0;
  }
  DAT_00c97930 = DAT_00c97930 + 1;
  return param_1;
}



/* entry 0x007EC7E0; bounded CFG instructions=13; body bytes=43 */

undefined4 BOUNDED_007EC7E0(undefined4 param_1)

{
  if (*(int *)(DAT_00c9792c + DAT_00c97b24) != 0) {
    FUN_00801b80(*(int *)(DAT_00c9792c + DAT_00c97b24));
  }
  DAT_00c97930 = DAT_00c97930 + -1;
  return param_1;
}



/* entry 0x007EE110; bounded CFG instructions=27; body bytes=100 */

undefined4 BOUNDED_007EE110(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  DAT_00c97960 = param_2;
  uVar1 = thunk_FUN_008019b0(DAT_008e222c,DAT_008e2244,4,DAT_008e2248,&DAT_00c9793c,0x40005);
  *(undefined4 *)(DAT_00c97b24 + DAT_00c97960) = uVar1;
  if (*(int *)(DAT_00c97b24 + DAT_00c97960) == 0) {
    return 0;
  }
  DAT_00c97964 = DAT_00c97964 + 1;
  return param_1;
}



/* entry 0x007EE0B0; bounded CFG instructions=16; body bytes=61 */

undefined4 BOUNDED_007EE0B0(undefined4 param_1)

{
  if (*(int *)(DAT_00c97960 + DAT_00c97b24) != 0) {
    FUN_00801b80(*(int *)(DAT_00c97960 + DAT_00c97b24));
    *(undefined4 *)(DAT_00c97960 + DAT_00c97b24) = 0;
  }
  DAT_00c97964 = DAT_00c97964 + -1;
  return param_1;
}



/* entry 0x00802280; bounded CFG instructions=144; body bytes=608 */

undefined4 BOUNDED_00802280(undefined4 param_1,int param_2)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  
  DAT_00c9a65c = param_2;
  uVar2 = thunk_FUN_008019b0(DAT_008e2670,DAT_008e2688,4,DAT_008e268c,&DAT_00c9a664,0x40018);
  *(undefined4 *)(DAT_00c97b24 + DAT_00c9a65c) = uVar2;
  if (*(int *)(DAT_00c97b24 + DAT_00c9a65c) == 0) {
    return 0;
  }
  uVar2 = thunk_FUN_008019b0(0x34,DAT_008e2688,4,DAT_008e2694,&DAT_00c9a638,0x40406);
  *(undefined4 *)(DAT_00c97b24 + 0x218 + DAT_00c9a65c) = uVar2;
  if (*(int *)(DAT_00c97b24 + 0x218 + DAT_00c9a65c) == 0) {
    FUN_00801b80(*(undefined4 *)(DAT_00c97b24 + DAT_00c9a65c));
    *(undefined4 *)(DAT_00c97b24 + DAT_00c9a65c) = 0;
    return 0;
  }
  *(undefined4 *)(DAT_00c97b24 + 8 + DAT_00c9a65c) = 0x100;
  uVar2 = (**(code **)(DAT_00c97b24 + 0x134))
                    (*(undefined4 *)(DAT_00c97b24 + 8 + DAT_00c9a65c),&DAT_01040406);
  *(undefined4 *)(DAT_00c97b24 + 4 + DAT_00c9a65c) = uVar2;
  puVar1 = *(undefined1 **)(DAT_00c97b24 + 4 + DAT_00c9a65c);
  if (puVar1 == (undefined1 *)0x0) {
    FUN_00801b80(*(undefined4 *)(DAT_00c97b24 + 0x218 + DAT_00c9a65c));
    *(undefined4 *)(DAT_00c97b24 + 0x218 + DAT_00c9a65c) = 0;
    FUN_00801b80(*(undefined4 *)(DAT_00c97b24 + DAT_00c9a65c));
    *(undefined4 *)(DAT_00c97b24 + DAT_00c9a65c) = 0;
    return 0;
  }
  *puVar1 = 0;
  DAT_00c9a660 = DAT_00c9a660 + 1;
  FUN_00803fe0(0x3f800000);
  *(undefined4 *)(DAT_00c97b24 + 0x21c + DAT_00c9a65c) = 0;
  *(undefined4 *)(DAT_00c97b24 + 0x214 + DAT_00c9a65c) = 0x100;
  uVar2 = (**(code **)(DAT_00c97b24 + 0x134))
                    (*(undefined4 *)(DAT_00c97b24 + 0x214 + DAT_00c9a65c),&DAT_01040018);
  *(undefined4 *)(DAT_00c97b24 + 0x210 + DAT_00c9a65c) = uVar2;
  if (*(int *)(DAT_00c97b24 + 0x210 + DAT_00c9a65c) == 0) {
    (**(code **)(DAT_00c97b24 + 0x138))(*(undefined4 *)(DAT_00c97b24 + 4 + DAT_00c9a65c));
    *(undefined4 *)(DAT_00c97b24 + 4 + DAT_00c9a65c) = 0;
    *(undefined4 *)(DAT_00c97b24 + 8 + DAT_00c9a65c) = 0;
    FUN_00801b80(*(undefined4 *)(DAT_00c97b24 + 0x218 + DAT_00c9a65c));
    *(undefined4 *)(DAT_00c97b24 + 0x218 + DAT_00c9a65c) = 0;
    FUN_00801b80(*(undefined4 *)(DAT_00c97b24 + DAT_00c9a65c));
    *(undefined4 *)(DAT_00c97b24 + DAT_00c9a65c) = 0;
    return 0;
  }
  return param_1;
}



/* entry 0x008024E0; bounded CFG instructions=77; body bytes=313 */

undefined4 BOUNDED_008024E0(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(DAT_00c9a65c + 0x210 + DAT_00c97b24);
  if (iVar1 != 0) {
    (**(code **)(DAT_00c97b24 + 0x138))(iVar1);
    *(undefined4 *)(DAT_00c9a65c + 0x210 + DAT_00c97b24) = 0;
    *(undefined4 *)(DAT_00c9a65c + 0x214 + DAT_00c97b24) = 0;
  }
  iVar1 = *(int *)(DAT_00c9a65c + 4 + DAT_00c97b24);
  if (iVar1 != 0) {
    (**(code **)(DAT_00c97b24 + 0x138))(iVar1);
    *(undefined4 *)(DAT_00c9a65c + 4 + DAT_00c97b24) = 0;
    *(undefined4 *)(DAT_00c9a65c + 8 + DAT_00c97b24) = 0;
  }
  iVar1 = *(int *)(DAT_00c9a65c + 0x21c + DAT_00c97b24);
  while (iVar1 != 0) {
    *(undefined4 *)(DAT_00c9a65c + 0x21c + DAT_00c97b24) = *(undefined4 *)(iVar1 + 0x30);
    (**(code **)(DAT_00c97b24 + 0x148))(*(undefined4 *)(DAT_00c9a65c + 0x218 + DAT_00c97b24),iVar1);
    iVar1 = *(int *)(DAT_00c9a65c + 0x21c + DAT_00c97b24);
  }
  iVar1 = *(int *)(DAT_00c9a65c + 0x218 + DAT_00c97b24);
  if (iVar1 != 0) {
    FUN_00801b80(iVar1);
    *(undefined4 *)(DAT_00c9a65c + 0x218 + DAT_00c97b24) = 0;
  }
  if (*(int *)(DAT_00c9a65c + DAT_00c97b24) != 0) {
    FUN_00801b80(*(int *)(DAT_00c9a65c + DAT_00c97b24));
    *(undefined4 *)(DAT_00c9a65c + DAT_00c97b24) = 0;
  }
  DAT_00c9a660 = DAT_00c9a660 + -1;
  return param_1;
}



/* entry 0x007FB370; bounded CFG instructions=68; body bytes=272 */

undefined4 BOUNDED_007FB370(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  DAT_00c980d8 = param_2;
  puVar3 = (undefined4 *)(DAT_00c97b24 + 0x2c + param_2);
  for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  *(undefined4 *)(DAT_00c97b24 + 0x38 + DAT_00c980d8) = 0;
  *(undefined4 *)(DAT_00c97b24 + 0x3c + DAT_00c980d8) = 0;
  *(undefined4 *)(DAT_00c97b24 + 0x40 + DAT_00c980d8) = 0;
  *(undefined1 *)(DAT_00c97b24 + 0x4d + DAT_00c980d8) = 0x80;
  *(undefined4 *)(DAT_00c97b24 + 0x30 + DAT_00c980d8) = 0;
  *(undefined4 *)(DAT_00c97b24 + 0x34 + DAT_00c980d8) = 0;
  *(undefined1 *)(DAT_00c97b24 + 0x4c + DAT_00c980d8) = 0;
  *(undefined4 *)(DAT_00c97b24 + 0x28 + DAT_00c980d8) = 0;
  *(int *)(DAT_00c97b24 + DAT_00c980d8) = DAT_00c97b24 + 0x2c + DAT_00c980d8;
  uVar1 = thunk_FUN_008019b0(DAT_008e2518,DAT_008e2530,4,DAT_008e2534,&DAT_00c980b4,0x40407);
  *(undefined4 *)(DAT_00c97b24 + 0x60 + DAT_00c980d8) = uVar1;
  if (*(int *)(DAT_00c97b24 + 0x60 + DAT_00c980d8) == 0) {
    return 0;
  }
  DAT_00c980dc = DAT_00c980dc + 1;
  return param_1;
}



/* entry 0x007FB310; bounded CFG instructions=16; body bytes=63 */

undefined4 BOUNDED_007FB310(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(DAT_00c980d8 + 0x60 + DAT_00c97b24);
  if (iVar1 != 0) {
    FUN_00801b80(iVar1);
    *(undefined4 *)(DAT_00c980d8 + 0x60 + DAT_00c97b24) = 0;
  }
  DAT_00c980dc = DAT_00c980dc + -1;
  return param_1;
}



/* entry 0x007F3EA0; bounded CFG instructions=114; body bytes=471 */

undefined4 BOUNDED_007F3EA0(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  DAT_00c97b4c = param_2;
  uVar1 = thunk_FUN_008019b0(DAT_008e23cc,DAT_008e23fc,4,DAT_008e2400,&DAT_00c97b54,0x40006);
  *(undefined4 *)(DAT_00c97b24 + 8 + DAT_00c97b4c) = uVar1;
  if (*(int *)(DAT_00c97b24 + 8 + DAT_00c97b4c) == 0) {
    return 0;
  }
  uVar1 = thunk_FUN_008019b0(DAT_008e23e4,DAT_008e2404,4,DAT_008e2408,&DAT_00c97b28,0x40408);
  *(undefined4 *)(DAT_00c97b24 + 0xc + DAT_00c97b4c) = uVar1;
  iVar2 = DAT_00c97b24 + DAT_00c97b4c;
  if (*(int *)(iVar2 + 0xc) == 0) {
    FUN_00801b80(*(undefined4 *)(iVar2 + 8));
    *(undefined4 *)(DAT_00c97b24 + 8 + DAT_00c97b4c) = 0;
    return 0;
  }
  *(int *)iVar2 = iVar2;
  *(int *)(DAT_00c97b24 + DAT_00c97b4c + 4) = DAT_00c97b24 + DAT_00c97b4c;
  DAT_00c97b50 = DAT_00c97b50 + 1;
  DAT_00c97b78 = FUN_007f3600();
  *(undefined4 *)(DAT_00c97b24 + 0x10 + DAT_00c97b4c) = DAT_00c97b78;
  if (*(int *)(DAT_00c97b24 + 0x10 + DAT_00c97b4c) == 0) {
    FUN_00801b80(*(undefined4 *)(DAT_00c97b24 + 0xc + DAT_00c97b4c));
    *(undefined4 *)(DAT_00c97b24 + 0xc + DAT_00c97b4c) = 0;
    FUN_00801b80(*(undefined4 *)(DAT_00c97b24 + 8 + DAT_00c97b4c));
    *(undefined4 *)(DAT_00c97b24 + 8 + DAT_00c97b4c) = 0;
    return 0;
  }
  *(undefined4 *)(DAT_00c97b24 + 0x1c + DAT_00c97b4c) = 0;
  *(undefined4 *)(DAT_00c97b24 + 0x20 + DAT_00c97b4c) = 0;
  *(undefined1 **)(DAT_00c97b24 + 0x18 + DAT_00c97b4c) = &LAB_007f53d0;
  *(undefined1 **)(DAT_00c97b24 + 0x14 + DAT_00c97b4c) = &LAB_007f40f0;
  *(undefined1 **)(DAT_00c97b24 + 0x2c + DAT_00c97b4c) = &LAB_007f5140;
  *(code **)(DAT_00c97b24 + 0x30 + DAT_00c97b4c) = FUN_007f4080;
  *(undefined4 *)(DAT_00c97b24 + 0x24 + DAT_00c97b4c) = 0;
  *(undefined2 *)(DAT_00c97b24 + 0x28 + DAT_00c97b4c) = 0;
  return param_1;
}



/* entry 0x007F3D00; bounded CFG instructions=103; body bytes=340 */

undefined4 BOUNDED_007F3D00(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  
  iVar4 = *(int *)(DAT_00c97b4c + 0x24 + DAT_00c97b24);
  if (iVar4 != 0) {
    (**(code **)(DAT_00c97b24 + 0x138))(iVar4);
    *(undefined4 *)(DAT_00c97b4c + 0x24 + DAT_00c97b24) = 0;
    *(undefined2 *)(DAT_00c97b4c + 0x28 + DAT_00c97b24) = 0;
  }
  puVar2 = DAT_00c97b78;
  puVar3 = (undefined4 *)(DAT_00c97b4c + DAT_00c97b24);
  if ((puVar3[2] != 0) && (puVar3[3] != 0)) {
    for (puVar1 = (undefined4 *)*puVar3; puVar1 != puVar3; puVar1 = (undefined4 *)*puVar1) {
      if (puVar1 + -4 == DAT_00c97b78) {
        if ((undefined4 *)puVar3[4] == DAT_00c97b78) {
          puVar3[4] = 0;
        }
        puVar3 = (undefined4 *)puVar2[2];
        goto joined_r0x007f3d91;
      }
    }
  }
  goto LAB_007f3def;
  while( true ) {
    puVar1 = (undefined4 *)*puVar3;
    iVar4 = FUN_007f3820(puVar3 + -2,0);
    puVar3 = puVar1;
    if (iVar4 == 0) break;
joined_r0x007f3d91:
    if (puVar3 == puVar2 + 2) break;
  }
  FUN_00808740(&DAT_008e23e4,puVar2);
  *(undefined4 *)puVar2[5] = puVar2[4];
  *(undefined4 *)(puVar2[4] + 4) = puVar2[5];
  (**(code **)(DAT_00c97b24 + 0x148))(*(undefined4 *)(DAT_00c97b4c + 0xc + DAT_00c97b24),puVar2);
  DAT_00c97b78 = (undefined4 *)0x0;
LAB_007f3def:
  iVar4 = *(int *)(DAT_00c97b4c + 8 + DAT_00c97b24);
  if (iVar4 != 0) {
    FUN_00801b80(iVar4);
    *(undefined4 *)(DAT_00c97b4c + 8 + DAT_00c97b24) = 0;
  }
  iVar4 = *(int *)(DAT_00c97b4c + 0xc + DAT_00c97b24);
  if (iVar4 != 0) {
    FUN_00801b80(iVar4);
    *(undefined4 *)(DAT_00c97b4c + 0xc + DAT_00c97b24) = 0;
  }
  DAT_00c97b50 = DAT_00c97b50 + -1;
  return param_1;
}



/* entry 0x00807C40; bounded CFG instructions=8; body bytes=25 */

uint BOUNDED_00807C40(uint param_1,undefined4 param_2)

{
  int iVar1;
  
  DAT_00c9bc60 = param_2;
  iVar1 = FUN_00804fe0();
  return -(uint)(iVar1 != 0) & param_1;
}



/* entry 0x00807C60; bounded CFG instructions=3; body bytes=10 */

undefined4 BOUNDED_00807C60(undefined4 param_1)

{
  FUN_00804f60();
  return param_1;
}



/* entry 0x0080A780; bounded CFG instructions=26; body bytes=96 */

undefined4 BOUNDED_0080A780(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  DAT_00c9a6f8 = param_2;
  uVar1 = thunk_FUN_008019b0(0x21,DAT_008e26d8,4,DAT_008e26dc,&DAT_00c9a700,0x40412);
  *(undefined4 *)(DAT_00c97b24 + DAT_00c9a6f8) = uVar1;
  if (*(int *)(DAT_00c97b24 + DAT_00c9a6f8) == 0) {
    return 0;
  }
  DAT_00c9a6fc = DAT_00c9a6fc + 1;
  return param_1;
}



/* entry 0x0080A7E0; bounded CFG instructions=13; body bytes=43 */

undefined4 BOUNDED_0080A7E0(undefined4 param_1)

{
  if (*(int *)(DAT_00c9a6f8 + DAT_00c97b24) != 0) {
    FUN_00801b80(*(int *)(DAT_00c9a6f8 + DAT_00c97b24));
  }
  DAT_00c9a6fc = DAT_00c9a6fc + -1;
  return param_1;
}



/* entry 0x007EFE20; bounded CFG instructions=47; body bytes=166 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 BOUNDED_007EFE20(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  DAT_00c9c078 = param_2;
  _DAT_00c97968 = (undefined4 *)(DAT_00c97b24 + param_2);
  DAT_00c9c07c = DAT_00c9c07c + 1;
  puVar2 = _DAT_00c97968;
  for (iVar1 = 0x1d; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  iVar1 = FUN_0080a0a0(DAT_00c97b24 + 0x1c + DAT_00c9c078);
  if (iVar1 != 0) {
    iVar1 = FUN_0080a1a0(DAT_00c97b24 + 0x20 + DAT_00c9c078);
    if (iVar1 != 0) {
      return param_1;
    }
  }
  FUN_0080a140(DAT_00c97b24 + 0x20 + DAT_00c9c078);
  FUN_0080a110(DAT_00c97b24 + 0x1c + DAT_00c9c078);
  DAT_00c9c07c = DAT_00c9c07c + -1;
  return 0;
}



/* entry 0x007EFDE0; bounded CFG instructions=16; body bytes=61 */

undefined4 BOUNDED_007EFDE0(undefined4 param_1)

{
  FUN_0080a140(DAT_00c9c078 + 0x20 + DAT_00c97b24);
  FUN_0080a110(DAT_00c9c078 + 0x1c + DAT_00c97b24);
  DAT_00c9c07c = DAT_00c9c07c + -1;
  return param_1;
}



/* entry 0x00807C90; bounded CFG instructions=74; body bytes=240 */

undefined4 BOUNDED_00807C90(undefined4 param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  DAT_00c9bc58 = param_2;
  iVar4 = *(int *)(DAT_00c97b24 + 0x154);
  piVar3 = (int *)(DAT_00c97b24 + param_2);
  if (iVar4 == 0) {
    piVar3[3] = 0;
  }
  else {
    iVar5 = (**(code **)(DAT_00c97b24 + 0x134))(iVar4,0x4040b);
    piVar3[3] = iVar5;
    if (iVar5 == 0) {
      uStack_10 = 1;
      uStack_c = FUN_008088d0(0x80000013);
      FUN_00808820(&uStack_10);
      return 0;
    }
    iVar5 = FUN_0080ffe0(iVar5,iVar4);
    if (iVar5 == 0) {
      (**(code **)(DAT_00c97b24 + 0x138))(piVar3[3]);
      uStack_8 = 1;
      uStack_4 = FUN_008088d0(0xc,0);
      FUN_00808820(&uStack_8);
      return 0;
    }
  }
  piVar1 = piVar3 + 4;
  piVar2 = piVar3 + 6;
  piVar3[5] = (int)piVar1;
  piVar3[7] = (int)piVar2;
  *piVar1 = (int)piVar1;
  *piVar2 = (int)piVar2;
  piVar3[9] = (int)piVar1;
  piVar3[8] = (int)piVar2;
  *piVar3 = iVar4;
  piVar3[1] = 0;
  piVar3[2] = 0;
  DAT_00c9bc5c = DAT_00c9bc5c + 1;
  return param_1;
}



/* entry 0x00807D80; bounded CFG instructions=20; body bytes=86 */

undefined4 BOUNDED_00807D80(undefined4 param_1)

{
  FUN_008081f0();
  FUN_00810030(*(undefined4 *)(DAT_00c9bc58 + 0xc + DAT_00c97b24));
  (**(code **)(DAT_00c97b24 + 0x138))(*(undefined4 *)(DAT_00c9bc58 + 0xc + DAT_00c97b24));
  *(undefined4 *)(DAT_00c9bc58 + 0xc + DAT_00c97b24) = 0;
  DAT_00c9bc5c = DAT_00c9bc5c + -1;
  return param_1;
}


