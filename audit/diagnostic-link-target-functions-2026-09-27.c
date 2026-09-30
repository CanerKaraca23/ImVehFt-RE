/* Full-analysis function mapping; decompilation is not original source. */

/* function 100022d0 FUN_100022d0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_100022d0(undefined4 param_1,undefined4 param_2)

{
  UINT UVar1;
  char *pcVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 uVar3;
  undefined4 extraout_ECX_05;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 extraout_EDX_04;
  undefined4 uVar4;
  undefined4 extraout_EDX_05;
  DWORD local_10;
  DWORD local_c;
  DWORD local_8;
  DWORD local_4;
  
  FUN_100014f0(param_1,param_2,
               (byte *)"This file was created by ImVehFt.asi\nCurrent plugin version: 2.1.1\n");
  FUN_100014f0(extraout_ECX,extraout_EDX,(byte *)"Reading ImVehFt.ini...");
  FUN_100262b0((char *)0x1003a6c8,0x200,0x1003a8c8);
  FUN_100263e0((char *)0x1003a6c8,0x200,0x1008549c);
  UVar1 = GetPrivateProfileIntA("MAIN","SAMP_fix",0,(LPCSTR)0x1003a6c8);
  cRam1003aef1 = UVar1 != 0;
  FUN_100262b0((char *)0x1003a6c8,0x200,0x1003a8c8);
  FUN_100263e0((char *)0x1003a6c8,0x200,0x1008549c);
  UVar1 = GetPrivateProfileIntA("MAIN","disable_beam_shape",1,(LPCSTR)0x1003a6c8);
  cRam1003a6c7 = UVar1 != 0;
  FUN_100262b0((char *)0x1003a6c8,0x200,0x1003a8c8);
  FUN_100263e0((char *)0x1003a6c8,0x200,0x1008549c);
  URam1003aed8 = GetPrivateProfileIntA("MAIN","turnlights_delay",500,(LPCSTR)0x1003a6c8);
  iRam1003bc70 = URam1003aed8 * 2;
  FUN_100262b0((char *)0x1003a6c8,0x200,0x1003a8c8);
  FUN_100263e0((char *)0x1003a6c8,0x200,0x1008549c);
  URam1003bc04 = GetPrivateProfileIntA("CONTROL","key_fog",0x4a,(LPCSTR)0x1003a6c8);
  FUN_100262b0((char *)0x1003a6c8,0x200,0x1003a8c8);
  FUN_100263e0((char *)0x1003a6c8,0x200,0x1008549c);
  URam1003bc24 = GetPrivateProfileIntA("CONTROL","key_turnl_l",0x5a,(LPCSTR)0x1003a6c8);
  FUN_100262b0((char *)0x1003a6c8,0x200,0x1003a8c8);
  FUN_100263e0((char *)0x1003a6c8,0x200,0x1008549c);
  URam1003bc0c = GetPrivateProfileIntA("CONTROL","key_turnl_r",0x43,(LPCSTR)0x1003a6c8);
  FUN_100262b0((char *)0x1003a6c8,0x200,0x1003a8c8);
  FUN_100263e0((char *)0x1003a6c8,0x200,0x1008549c);
  URam1003bbbc = GetPrivateProfileIntA("CONTROL","key_turnl_2",0x58,(LPCSTR)0x1003a6c8);
  FUN_100262b0((char *)0x1003a6c8,0x200,0x1003a8c8);
  FUN_100263e0((char *)0x1003a6c8,0x200,0x1008549c);
  URam1003b6fc = GetPrivateProfileIntA("CONTROL","key_turnl_0",0x10,(LPCSTR)0x1003a6c8);
  FUN_100262b0((char *)0x1003a6c8,0x200,0x1003a8c8);
  FUN_100263e0((char *)0x1003a6c8,0x200,0x1008549c);
  URam1003bc74 = GetPrivateProfileIntA("CONTROL","key_headlight",0x47,(LPCSTR)0x1003a6c8);
  FUN_100014f0(extraout_ECX_00,extraout_EDX_00,(byte *)"Finished.");
  FUN_100014f0(extraout_ECX_01,extraout_EDX_01,(byte *)"Making ImVehFt memory patches...");
  VirtualProtect(&DAT_004c8415,4,0x40,&local_4);
  _DAT_004c8415 = FUN_10007f70;
  VirtualProtect(&DAT_004c8415,4,local_4,&local_8);
  local_8 = 0xe8;
  VirtualProtect(&DAT_006d6617,1,0x40,&local_10);
  DAT_006d6617 = (undefined1)local_8;
  VirtualProtect(&DAT_006d6617,1,local_10,&local_c);
  VirtualProtect(&DAT_006d6618,4,0x40,&local_10);
  _DAT_006d6618 = 0xf930eb4;
  VirtualProtect(&DAT_006d6618,4,local_10,&local_c);
  local_8 = 0xe8;
  VirtualProtect(&DAT_005b8ffd,1,0x40,&local_10);
  DAT_005b8ffd = (undefined1)local_8;
  VirtualProtect(&DAT_005b8ffd,1,local_10,&local_c);
  VirtualProtect(&DAT_005b8ffe,4,0x40,&local_10);
  _DAT_005b8ffe = 0xfa4f13e;
  VirtualProtect(&DAT_005b8ffe,4,local_10,&local_c);
  local_8 = 0xe8;
  VirtualProtect(&DAT_006d6494,1,0x40,&local_10);
  DAT_006d6494 = (undefined1)local_8;
  VirtualProtect(&DAT_006d6494,1,local_10,&local_c);
  VirtualProtect(&DAT_006d6495,4,0x40,&local_10);
  _DAT_006d6495 = 0xf92ec47;
  VirtualProtect(&DAT_006d6495,4,local_10,&local_c);
  local_8 = 0xe8;
  VirtualProtect(&DAT_0053bfcc,1,0x40,&local_10);
  DAT_0053bfcc = (undefined1)local_8;
  VirtualProtect(&DAT_0053bfcc,1,local_10,&local_c);
  VirtualProtect(&DAT_0053bfcd,4,0x40,&local_10);
  _DAT_0053bfcd = 0xfac8b3f;
  VirtualProtect(&DAT_0053bfcd,4,local_10,&local_c);
  local_8 = 0xe8;
  VirtualProtect(&DAT_006d6a58,1,0x40,&local_10);
  DAT_006d6a58 = (undefined1)local_8;
  VirtualProtect(&DAT_006d6a58,1,local_10,&local_c);
  VirtualProtect(&DAT_006d6a59,4,0x40,&local_10);
  _DAT_006d6a59 = 0xf92d863;
  VirtualProtect(&DAT_006d6a59,4,local_10,&local_c);
  FUN_1000a9f0(3);
  local_8 = 0xe9;
  VirtualProtect(&DAT_005d5bc7,1,0x40,&local_10);
  DAT_005d5bc7 = (undefined1)local_8;
  VirtualProtect(&DAT_005d5bc7,1,local_10,&local_c);
  VirtualProtect(&DAT_005d5bc8,4,0x40,&local_10);
  _DAT_005d5bc8 = 0xfa32bb4;
  VirtualProtect(&DAT_005d5bc8,4,local_10,&local_c);
  local_8 = 0xe9;
  VirtualProtect(&DAT_005d5c1e,1,0x40,&local_10);
  DAT_005d5c1e = (undefined1)local_8;
  VirtualProtect(&DAT_005d5c1e,1,local_10,&local_c);
  VirtualProtect(&DAT_005d5c1f,4,0x40,&local_10);
  _DAT_005d5c1f = 0xfa32c0d;
  VirtualProtect(&DAT_005d5c1f,4,local_10,&local_c);
  local_8 = 0xe9;
  VirtualProtect(&DAT_005d5ad1,1,0x40,&local_10);
  DAT_005d5ad1 = (undefined1)local_8;
  VirtualProtect(&DAT_005d5ad1,1,local_10,&local_c);
  VirtualProtect(&DAT_005d5ad2,4,0x40,&local_10);
  _DAT_005d5ad2 = 0xfa32e6a;
  VirtualProtect(&DAT_005d5ad2,4,local_10,&local_c);
  local_8 = 0xe9;
  VirtualProtect(&DAT_006e198e,1,0x40,&local_10);
  DAT_006e198e = (undefined1)local_8;
  VirtualProtect(&DAT_006e198e,1,local_10,&local_c);
  VirtualProtect(&DAT_006e198f,4,0x40,&local_10);
  _DAT_006e198f = 0xf9265fd;
  VirtualProtect(&DAT_006e198f,4,local_10,&local_c);
  local_8 = 0xe9;
  VirtualProtect(&DAT_006e18da,1,0x40,&local_10);
  DAT_006e18da = (undefined1)local_8;
  VirtualProtect(&DAT_006e18da,1,local_10,&local_c);
  VirtualProtect(&DAT_006e18db,4,0x40,&local_10);
  _DAT_006e18db = 0xf926671;
  VirtualProtect(&DAT_006e18db,4,local_10,&local_c);
  local_8 = 0xe9;
  VirtualProtect(&DAT_006e1a2d,1,0x40,&local_10);
  DAT_006e1a2d = (undefined1)local_8;
  VirtualProtect(&DAT_006e1a2d,1,local_10,&local_c);
  VirtualProtect(&DAT_006e1a2e,4,0x40,&local_10);
  _DAT_006e1a2e = 0xf92653e;
  VirtualProtect(&DAT_006e1a2e,4,local_10,&local_c);
  VirtualProtect(&DAT_005d5bfd,3,0x40,&local_10);
  _DAT_005d5bfd = 0x9090;
  DAT_005d5bff = 0x90;
  VirtualProtect(&DAT_005d5bfd,3,local_10,&local_c);
  VirtualProtect(&DAT_005d5d3d,5,0x40,&local_10);
  _DAT_005d5d3d = 0x90909090;
  DAT_005d5d41 = 0x90;
  VirtualProtect(&DAT_005d5d3d,5,local_10,&local_c);
  VirtualProtect(&DAT_006e18e5,6,0x40,&local_10);
  _DAT_006e18e5 = 0x90909090;
  _DAT_006e18e9 = 0x9090;
  VirtualProtect(&DAT_006e18e5,6,local_10,&local_c);
  VirtualProtect(&DAT_006e28e7,5,0x40,&local_10);
  _DAT_006e28e7 = 0x90909090;
  DAT_006e28eb = 0x90;
  VirtualProtect(&DAT_006e28e7,5,local_10,&local_c);
  VirtualProtect(&DAT_006e1d4f,1,0x40,&local_10);
  DAT_006e1d4f = 2;
  VirtualProtect(&DAT_006e1d4f,1,local_10,&local_c);
  VirtualProtect(&DAT_004c900d,5,0x40,&local_10);
  _DAT_004c900d = 0x90909090;
  DAT_004c9011 = 0x90;
  VirtualProtect(&DAT_004c900d,5,local_10,&local_c);
  VirtualProtect(&DAT_0085c5f4,4,0x40,&local_10);
  _DAT_0085c5f4 = FUN_10009030;
  VirtualProtect(&DAT_0085c5f4,4,local_10,&local_c);
  VirtualProtect(&DAT_004c9148,4,0x40,&local_10);
  _DAT_004c9148 = &LAB_100091f0;
  VirtualProtect(&DAT_004c9148,4,local_10,&local_c);
  if (cRam1003aef1 == '\0') {
    VirtualProtect(&DAT_006fdf47,1,0x40,&local_10);
    DAT_006fdf47 = 3;
    VirtualProtect(&DAT_006fdf47,1,local_10,&local_c);
    local_8 = 0xe8;
    VirtualProtect(&DAT_006fded6,1,0x40,&local_10);
    DAT_006fded6 = (undefined1)local_8;
    VirtualProtect(&DAT_006fded6,1,local_10,&local_c);
    VirtualProtect(&DAT_006fded7,4,0x40,&local_10);
    _DAT_006fded7 = 0xf905f65;
    VirtualProtect(&DAT_006fded7,4,local_10,&local_c);
    local_8 = 0xe8;
    VirtualProtect(&DAT_006fdf10,1,0x40,&local_10);
    DAT_006fdf10 = (undefined1)local_8;
    VirtualProtect(&DAT_006fdf10,1,local_10,&local_c);
    VirtualProtect(&DAT_006fdf11,4,0x40,&local_10);
    _DAT_006fdf11 = 0xf90602b;
    VirtualProtect(&DAT_006fdf11,4,local_10,&local_c);
    FUN_1000a9f0(8);
  }
  local_8 = 0xe9;
  VirtualProtect(&DAT_006ab350,1,0x40,&local_10);
  DAT_006ab350 = (undefined1)local_8;
  VirtualProtect(&DAT_006ab350,1,local_10,&local_c);
  VirtualProtect(&DAT_006ab351,4,0x40,&local_10);
  _DAT_006ab351 = 0xf957cdb;
  VirtualProtect(&DAT_006ab351,4,local_10,&local_c);
  VirtualProtect(&DAT_006ab355,5,0x40,&local_10);
  _DAT_006ab355 = 0x90909090;
  DAT_006ab359 = 0x90;
  VirtualProtect(&DAT_006ab355,5,local_10,&local_c);
  FUN_1000a9f0(7);
  local_8 = 0xe8;
  VirtualProtect(&DAT_006f3aed,1,0x40,&local_10);
  DAT_006f3aed = (undefined1)local_8;
  VirtualProtect(&DAT_006f3aed,1,local_10,&local_c);
  VirtualProtect(&DAT_006f3aee,4,0x40,&local_10);
  _DAT_006f3aee = 0xf90f56e;
  VirtualProtect(&DAT_006f3aee,4,local_10,&local_c);
  VirtualProtect(&DAT_006f3af2,1,0x40,&local_10);
  DAT_006f3af2 = 0x90;
  VirtualProtect(&DAT_006f3af2,1,local_10,&local_c);
  local_8 = 0xe8;
  VirtualProtect(&DAT_006f3973,1,0x40,&local_10);
  DAT_006f3973 = (undefined1)local_8;
  VirtualProtect(&DAT_006f3973,1,local_10,&local_c);
  VirtualProtect(&DAT_006f3974,4,0x40,&local_10);
  _DAT_006f3974 = 0xf90f708;
  VirtualProtect(&DAT_006f3974,4,local_10,&local_c);
  VirtualProtect(&DAT_006f3978,7,0x40,&local_10);
  _DAT_006f3978 = 0x90909090;
  _DAT_006f397c = 0x9090;
  DAT_006f397e = 0x90;
  VirtualProtect(&DAT_006f3978,7,local_10,&local_c);
  local_8 = 0xe8;
  VirtualProtect(&DAT_006e174b,1,0x40,&local_10);
  DAT_006e174b = (undefined1)local_8;
  VirtualProtect(&DAT_006e174b,1,local_10,&local_c);
  VirtualProtect(&DAT_006e174c,4,0x40,&local_10);
  _DAT_006e174c = 0xf921cb0;
  VirtualProtect(&DAT_006e174c,4,local_10,&local_c);
  local_8 = 0xe8;
  VirtualProtect(&DAT_006e175e,1,0x40,&local_10);
  DAT_006e175e = (undefined1)local_8;
  VirtualProtect(&DAT_006e175e,1,local_10,&local_c);
  VirtualProtect(&DAT_006e175f,4,0x40,&local_10);
  _DAT_006e175f = 0xf921c9d;
  VirtualProtect(&DAT_006e175f,4,local_10,&local_c);
  local_8 = 0xe8;
  VirtualProtect(&DAT_006e173c,1,0x40,&local_10);
  DAT_006e173c = (undefined1)local_8;
  VirtualProtect(&DAT_006e173c,1,local_10,&local_c);
  VirtualProtect(&DAT_006e173d,4,0x40,&local_10);
  _DAT_006e173d = 0xf921f1f;
  VirtualProtect(&DAT_006e173d,4,local_10,&local_c);
  local_8 = 0xe8;
  VirtualProtect(&DAT_006e1773,1,0x40,&local_10);
  DAT_006e1773 = (undefined1)local_8;
  VirtualProtect(&DAT_006e1773,1,local_10,&local_c);
  VirtualProtect(&DAT_006e1774,4,0x40,&local_10);
  _DAT_006e1774 = 0xf921ee8;
  VirtualProtect(&DAT_006e1774,4,local_10,&local_c);
  local_8 = 0xe9;
  VirtualProtect(&DAT_006e27e6,1,0x40,&local_10);
  DAT_006e27e6 = (undefined1)local_8;
  VirtualProtect(&DAT_006e27e6,1,local_10,&local_c);
  VirtualProtect(&DAT_006e27e7,4,0x40,&local_10);
  _DAT_006e27e7 = 0xf9209f5;
  VirtualProtect(&DAT_006e27e7,4,local_10,&local_c);
  if (cRam1003a6c7 != '\0') {
    VirtualProtect(&DAT_006a2ed3,0xc,0x40,&local_10);
    _DAT_006a2ed3 = 0x90909090;
    _DAT_006a2ed7 = 0x90909090;
    _DAT_006a2edb = 0x90909090;
    VirtualProtect(&DAT_006a2ed3,0xc,local_10,&local_c);
    VirtualProtect(&DAT_006a2eeb,0xc,0x40,&local_10);
    _DAT_006a2eeb = 0x90909090;
    _DAT_006a2eef = 0x90909090;
    _DAT_006a2ef3 = 0x90909090;
    VirtualProtect(&DAT_006a2eeb,0xc,local_10,&local_c);
    VirtualProtect(&DAT_006bde73,0x12,0x40,&local_10);
    _DAT_006bde73 = 0x90909090;
    _DAT_006bde77 = 0x90909090;
    _DAT_006bde7b = 0x90909090;
    _DAT_006bde7f = 0x90909090;
    _DAT_006bde83 = 0x9090;
    VirtualProtect(&DAT_006bde73,0x12,local_10,&local_c);
  }
  local_8 = 0xe8;
  VirtualProtect(&DAT_006e0df7,1,0x40,&local_10);
  DAT_006e0df7 = (undefined1)local_8;
  VirtualProtect(&DAT_006e0df7,1,local_10,&local_c);
  VirtualProtect(&DAT_006e0df8,4,0x40,&local_10);
  _DAT_006e0df8 = 0xf922544;
  VirtualProtect(&DAT_006e0df8,4,local_10,&local_c);
  FUN_100014f0(extraout_ECX_02,extraout_EDX_02,(byte *)"Finished.");
  pcVar2 = FUN_1000a990();
  uVar3 = extraout_ECX_03;
  uVar4 = extraout_EDX_03;
  if (pcVar2 == (char *)0x0) {
    FUN_100017f0();
    FUN_10001f00();
    uVar3 = extraout_ECX_04;
    uVar4 = extraout_EDX_04;
  }
  FUN_100014f0(uVar3,uVar4,(byte *)"Registering vehicle plugin...");
  uRam1003c248 = FUN_1000ab60(&LAB_10009280,FUN_100092b0);
  FUN_100014f0(extraout_ECX_05,extraout_EDX_05,(byte *)"Finished (registered vehicle plugin %d)");
  return;
}



/* function 10007280 FUN_10007280 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall
FUN_10007280(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,char param_5,
            byte param_6,byte param_7,undefined4 param_8,byte param_9,float param_10,char param_11,
            float param_12,char param_13)

{
  int iVar1;
  double dVar2;
  undefined4 uVar3;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  float10 fVar4;
  double dVar5;
  float fVar6;
  undefined8 uVar7;
  undefined1 local_f0 [64];
  undefined4 local_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 local_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 local_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 local_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 local_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  float local_20;
  undefined1 local_1c [4];
  float local_18;
  float local_10;
  undefined1 local_c;
  undefined1 local_b;
  undefined1 local_9;
  uint local_8;
  
  local_8 = DAT_1009f100 ^ (uint)&stack0xfffffffc;
  if ((param_10 <= 0.0) && (param_12 <= 0.0)) goto LAB_10007633;
  if (param_11 == '\0') {
    local_70 = *(undefined4 *)(param_3 + 0x10);
    uStack_6c = *(undefined4 *)(param_3 + 0x14);
    uStack_68 = *(undefined4 *)(param_3 + 0x18);
    uStack_64 = *(undefined4 *)(param_3 + 0x1c);
    local_60 = *(undefined4 *)(param_3 + 0x20);
    uStack_5c = *(undefined4 *)(param_3 + 0x24);
    uStack_58 = *(undefined4 *)(param_3 + 0x28);
    uStack_54 = *(undefined4 *)(param_3 + 0x2c);
    local_50 = *(undefined4 *)(param_3 + 0x30);
    uStack_4c = *(undefined4 *)(param_3 + 0x34);
    uStack_48 = *(undefined4 *)(param_3 + 0x38);
    uStack_44 = *(undefined4 *)(param_3 + 0x3c);
    local_40 = *(undefined4 *)(param_3 + 0x40);
    uStack_3c = *(undefined4 *)(param_3 + 0x44);
    uStack_38 = *(undefined4 *)(param_3 + 0x48);
    uStack_34 = *(undefined4 *)(param_3 + 0x4c);
  }
  else {
    (*(code *)0x7f18b0)(&local_70,(undefined4 *)(param_3 + 0x10),*(int *)(param_3 + 4) + 0x10);
  }
  local_b0 = *(undefined4 *)(param_3 + 0x50);
  uStack_ac = *(undefined4 *)(param_3 + 0x54);
  uStack_a8 = *(undefined4 *)(param_3 + 0x58);
  uStack_a4 = *(undefined4 *)(param_3 + 0x5c);
  local_a0 = *(undefined4 *)(param_3 + 0x60);
  uStack_9c = *(undefined4 *)(param_3 + 100);
  uStack_98 = *(undefined4 *)(param_3 + 0x68);
  uStack_94 = *(undefined4 *)(param_3 + 0x6c);
  local_90 = *(undefined4 *)(param_3 + 0x70);
  uStack_8c = *(undefined4 *)(param_3 + 0x74);
  uStack_88 = *(undefined4 *)(param_3 + 0x78);
  uStack_84 = *(undefined4 *)(param_3 + 0x7c);
  local_80 = *(undefined4 *)(param_3 + 0x80);
  uStack_7c = *(undefined4 *)(param_3 + 0x84);
  uStack_78 = *(undefined4 *)(param_3 + 0x88);
  uStack_74 = *(undefined4 *)(param_3 + 0x8c);
  (*(code *)0x40fe60)(local_1c,param_4,&local_80);
  (*(code *)0x59c910)();
  (*(code *)0x7f2070)(local_f0,&local_b0);
  uVar7 = (*(code *)0x59c790)(local_1c,local_f0,local_1c);
  param_2 = (undefined4)((ulonglong)uVar7 >> 0x20);
  if (0.0 < param_10) {
    if ((param_13 == '\x03') || (param_13 == '\x04')) {
      if ((DAT_1009e5b4 <= local_18) || (local_18 <= DAT_1009e5b8)) {
LAB_10007444:
        param_10 = (float)param_9;
      }
      else {
        if (local_18 < 0.0) {
          local_18 = local_18 * _DAT_1009fb40;
        }
        param_10 = ((float)((double)param_9 + _DAT_100855c0) +
                   (float)((double)param_9 + _DAT_100855c0)) * local_18;
      }
      FUN_1001ba40();
    }
    else if (param_13 != '\x02') {
      if (param_13 != '\0') {
        local_18 = local_18 * _DAT_1009fb40;
      }
      if (0.0 < local_18) goto LAB_10007444;
      goto LAB_1000747a;
    }
    (*(code *)0x6fc580)((int)uVar7 + param_5 + 0xff00);
    param_2 = extraout_EDX;
  }
LAB_1000747a:
  if (0.0 < param_12) {
    if (param_13 != '\x03') {
      if ((param_13 == '\x02') || (param_13 == '\x04')) {
        local_20 = 1.0;
        param_10 = DAT_1009fdc8;
      }
      else {
        local_20 = DAT_1009e5a4;
        param_10 = DAT_100a04a0;
      }
    }
    local_2c = 0;
    local_24 = 0;
    dVar5 = (double)DAT_1009ee7c;
    dVar2 = *(double *)(&DAT_100855c0 + (DAT_1009ee7c >> 0x1f) * -8);
    local_28 = DAT_1009e56c;
    (*(code *)0x54eef0)(local_1c,1,&local_b0,&local_2c);
    uVar3 = DAT_1009e560;
    fVar6 = _DAT_00c812a8;
    if (_DAT_00c812a8 < DAT_1009e59c) {
      fVar6 = DAT_1009e598;
    }
    iVar1 = (int)ROUND((float)param_7 * fVar6 * _DAT_1009fb28);
    local_c = (undefined1)iVar1;
    local_b = (undefined1)((uint)iVar1 >> 8);
    local_10 = (float)(int)ROUND((float)param_6 * _DAT_1009fb28 * fVar6);
    local_9 = local_10._0_1_;
    fVar4 = (float10)FUN_10009260();
    fVar6 = param_12 - (float)(dVar5 + dVar2);
    local_10 = fVar6 * local_20;
    (*(code *)&LAB_100073ec_4)(local_1c,local_10,fVar6,DAT_1009fb4c + (float)fVar4,uVar3,param_10);
    param_2 = extraout_EDX_00;
  }
LAB_10007633:
  FUN_100182e0(local_8 ^ (uint)&stack0xfffffffc,param_2);
  return;
}



/* function 10007670 FUN_10007670 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall
FUN_10007670(undefined4 param_1,undefined4 param_2,int param_3,int param_4,undefined4 param_5,
            char param_6,uint param_7,uint param_8,undefined4 param_9,char param_10,char param_11,
            byte param_12,char param_13)

{
  float10 fVar1;
  float fVar2;
  float fVar3;
  uint extraout_ECX;
  uint uVar4;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 uVar5;
  ushort in_FPUControlWord;
  float10 fVar6;
  float fVar7;
  float fVar8;
  longlong lVar9;
  undefined4 local_f4 [3];
  undefined8 local_e8;
  float local_e0;
  undefined1 local_dc [4];
  ushort local_d8;
  float local_d0;
  undefined4 local_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 local_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 local_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 local_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 local_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 local_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 local_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined1 local_2c [20];
  undefined1 local_18 [16];
  uint local_8;
  
  local_8 = DAT_1009f100 ^ (uint)&stack0xfffffffc;
  if ((param_13 != '\0') || (param_11 != '\0')) {
    if (param_10 == '\0') {
      local_cc = *(undefined4 *)(param_3 + 0x10);
      uStack_c8 = *(undefined4 *)(param_3 + 0x14);
      uStack_c4 = *(undefined4 *)(param_3 + 0x18);
      uStack_c0 = *(undefined4 *)(param_3 + 0x1c);
      local_bc = *(undefined4 *)(param_3 + 0x20);
      uStack_b8 = *(undefined4 *)(param_3 + 0x24);
      uStack_b4 = *(undefined4 *)(param_3 + 0x28);
      uStack_b0 = *(undefined4 *)(param_3 + 0x2c);
      local_ac = *(undefined4 *)(param_3 + 0x30);
      uStack_a8 = *(undefined4 *)(param_3 + 0x34);
      uStack_a4 = *(undefined4 *)(param_3 + 0x38);
      uStack_a0 = *(undefined4 *)(param_3 + 0x3c);
    }
    else {
      (*(code *)0x7f18b0)(&local_cc,(undefined4 *)(param_3 + 0x10),*(int *)(param_3 + 4) + 0x10);
    }
    local_9c = *(undefined4 *)(param_3 + 0x50);
    uStack_98 = *(undefined4 *)(param_3 + 0x54);
    uStack_94 = *(undefined4 *)(param_3 + 0x58);
    uStack_90 = *(undefined4 *)(param_3 + 0x5c);
    local_8c = *(undefined4 *)(param_3 + 0x60);
    uStack_88 = *(undefined4 *)(param_3 + 100);
    uStack_84 = *(undefined4 *)(param_3 + 0x68);
    uStack_80 = *(undefined4 *)(param_3 + 0x6c);
    local_7c = *(undefined4 *)(param_3 + 0x70);
    uStack_78 = *(undefined4 *)(param_3 + 0x74);
    uStack_74 = *(undefined4 *)(param_3 + 0x78);
    uStack_70 = *(undefined4 *)(param_3 + 0x7c);
    local_6c = *(undefined4 *)(param_3 + 0x80);
    uStack_68 = *(undefined4 *)(param_3 + 0x84);
    uStack_64 = *(undefined4 *)(param_3 + 0x88);
    uStack_60 = *(undefined4 *)(param_3 + 0x8c);
    (*(code *)0x40fe60)(local_dc,param_5,local_2c);
    (*(code *)0x59c910)();
    (*(code *)0x7f2070)(&local_6c,&local_9c);
    (*(code *)0x59c790)(local_dc,&local_6c,local_dc);
    uVar4 = extraout_ECX & 0xffffff00 | (uint)param_12;
    param_2 = extraout_EDX;
    if (param_13 != '\0') {
      if (param_12 == 2) {
        local_d0 = (float)(int)param_13 / _DAT_1009fb58 - _DAT_1009e5a8;
        (*(code *)0x6fc580)((int)param_6 + param_4 + 0xff00,param_4,param_7,param_8,param_9,0x50,
                            local_18,local_d0,DAT_1009e5ac,1,0,1,0,0,0,0,DAT_1009e5b4,0,DAT_1009e5b0
                            ,0,0);
        uVar4 = 2;
        param_2 = extraout_EDX_00;
      }
      else {
        if (param_12 != 0) {
          local_e0 = local_e0 * _DAT_1009fb40;
        }
        if (_DAT_100855b4 < local_e0) {
          local_d0 = (float)(int)param_13 / _DAT_1009fb58 - _DAT_1009e5a8;
          lVar9 = FUN_1001d360(uVar4,(int)param_13);
          (*(code *)0x6fc580)((int)param_6 + param_4 + 0xff00,param_4,param_7,param_8,param_9,
                              (uint)lVar9 & 0xff,local_18,local_d0,DAT_1009e5ac,1,0,1,0,0,0,0,
                              DAT_1009e5b4,0,DAT_1009e5b0,0,0);
          uVar4 = (uint)param_12;
          param_2 = extraout_EDX_01;
        }
      }
    }
    if (param_11 != '\0') {
      local_d0 = DAT_1009e5a4;
      uVar5 = DAT_1009fd20;
      fVar8 = DAT_1009e5a4;
      if ((char)uVar4 == '\x02') {
        uVar5 = DAT_100a04f0;
        fVar8 = _DAT_10085918;
      }
      local_f4[0] = 0;
      fVar7 = (float)(int)(char)(param_11 + -1) * _DAT_1009e5a0 + _DAT_1009e5a0;
      (*(code *)0x54eef0)(local_dc,1,&local_9c,local_f4);
      local_d0 = _DAT_00c812a8;
      if (_DAT_00c812a8 < DAT_1009e59c) {
        local_d0 = DAT_1009e598;
      }
      local_d8 = in_FPUControlWord | 0xc00;
      fVar2 = (float)((double)(param_8 & 0xff) + _DAT_100855c0) * local_d0 * _DAT_1009fb28;
      fVar3 = _DAT_1009fb28 * (float)((double)(param_7 & 0xff) + _DAT_100855c0) * local_d0;
      local_e8 = (double)DAT_1009fb50;
      fVar6 = (float10)FUN_10009260();
      fVar1 = (float10)local_e8;
      local_e8 = (double)CONCAT44((float)(fVar6 + fVar1),(undefined4)local_e8);
      FUN_10007af0((void *)((int)ROUND(fVar2) & 0xff),(int)ROUND(fVar3) & 0xff,local_dc,
                   fVar8 * fVar7,fVar7,(float)(fVar6 + fVar1),DAT_1009e568,uVar5);
      param_2 = extraout_EDX_02;
    }
  }
  FUN_100182e0(local_8 ^ (uint)&stack0xfffffffc,param_2);
  return;
}



/* function 10007c00 FUN_10007c00 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl FUN_10007c00(int param_1)

{
  uint uVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  uint uVar5;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  longlong lVar6;
  undefined4 local_8;
  
  iVar2 = DAT_1009fcdc;
  iVar4 = FUN_100097d0();
  iVar4 = *(int *)(*(int *)(iVar4 + 0x48) + ((param_1 - *_DAT_00b74494) / 0xa18) * 4);
  uVar1 = *(uint *)(iVar4 + 4 + iVar2);
  iVar4 = iVar4 + iVar2;
  iVar2 = *(int *)(param_1 + 0x594);
  DAT_1009fc1c = *(uint *)(iVar4 + 8);
  DAT_1009fc20 = *(uint *)(iVar4 + 0xc);
  DAT_1009fc24 = *(uint *)(iVar4 + 0x10);
  _DAT_1009fdb8 = *(undefined4 *)(iVar4 + 0x14);
  DAT_1009fd86 = *(undefined1 *)(iVar4 + 0x18);
  DAT_1009fdb4 = uVar1 & 0xff | (*(byte *)(param_1 + 0x584) & 0xffff01 | (uVar1 >> 0x10) << 8) << 8;
  if ((((iVar2 == 0) || (iVar2 == 1)) || (iVar2 == 2)) || (local_8 = _DAT_1009fdb8, iVar2 == 0xb)) {
    cVar3 = (*(code *)0x6c2130)(1);
    local_8 = extraout_EDX;
    if (cVar3 != '\0') {
      DAT_1009fdb4 = DAT_1009fdb4 & 0xffff0000 | 0x200;
      DAT_1009fc20 = DAT_1009fc20 & 0xffffff | 0x2000000;
      DAT_1009fc24 = DAT_1009fc24 & 0xffffff | 0x2000000;
    }
  }
  DAT_1009fdb4 = (DAT_1009fdb4 >> 8 & 0xff) << 8 |
                 DAT_1009fdb4 & 0xffff0000 | *(byte *)(param_1 + 0x584) >> 1 & 0xffffff01;
  if (((iVar2 == 0) || (iVar2 == 1)) || (iVar2 == 0xb)) {
    cVar3 = (*(code *)0x6c2130)(0);
    local_8 = extraout_EDX_00;
    if (cVar3 != '\0') {
      DAT_1009fdb4 = DAT_1009fdb4 & 0xffffff02 | 2;
      uVar5 = DAT_1009fc20 & 0xffffff02;
      uVar1 = DAT_1009fc20 >> 0x18;
      DAT_1009fc20._3_1_ = (undefined1)(uVar5 >> 0x18);
      DAT_1009fc20 = CONCAT22(CONCAT11(DAT_1009fc20._3_1_,(char)uVar1),(short)uVar5) & 0xff02ffff |
                     0x20002;
    }
  }
  DAT_1009fdb4 = DAT_1009fdb4 & 0xffffff | (*(byte *)(param_1 + 0x584) & 4) << 0x16;
  if (((iVar2 == 0) || (iVar2 == 1)) || ((iVar2 == 2 || (iVar2 == 0xb)))) {
    cVar3 = (*(code *)0x6c2130)(2);
    local_8 = extraout_EDX_01;
    if (cVar3 != '\0') {
      DAT_1009fdb4 = DAT_1009fdb4 & 0xffffff | 0x2000000;
      DAT_1009fc24 = DAT_1009fc24 & 0xffffff | 0x2000000;
      DAT_1009fc1c = DAT_1009fc1c & 0xffffff | 0x2000000;
    }
  }
  DAT_1009fdb4 = DAT_1009fdb4 & 0xffff |
                 ((DAT_1009fdb4 >> 0x18) << 0xb | *(byte *)(param_1 + 0x584) & 0x7f808) << 0xd;
  if (((iVar2 == 0) || (iVar2 == 1)) || (iVar2 == 0xb)) {
    cVar3 = (*(code *)0x6c2130)(3);
    local_8 = extraout_EDX_02;
    if (cVar3 != '\0') {
      DAT_1009fdb4 = DAT_1009fdb4 & 0xff02ffff | 0x20000;
      uVar5 = DAT_1009fc1c & 0xffffff02 | 2;
      DAT_1009fc24 = DAT_1009fc24 & 0xffffff02 | 2;
      uVar1 = DAT_1009fc1c >> 0x18;
      DAT_1009fc1c = CONCAT13((char)uVar1,(int3)uVar5);
      DAT_1009fc1c = CONCAT22(DAT_1009fc1c._2_2_,(short)uVar5);
      DAT_1009fc1c = DAT_1009fc1c & 0xff02ffff | 0x20000;
    }
  }
  DAT_1009fdbc = (int)*(short *)(param_1 + 0x22);
  _DAT_1009fc68 = *(undefined4 *)(param_1 + 0x4b0);
  DAT_100a0500 = param_1;
  lVar6 = FUN_1001d360(DAT_1009fdbc,local_8);
  _DAT_1009fdc4 = (uint)lVar6 & 0xf;
  FUN_100069a0(param_1);
  FUN_100070a0(param_1);
  FUN_10007110();
  FUN_10007190();
  FUN_10005df0(param_1);
  return param_1;
}



/* function 10007f70 FUN_10007f70 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_10007f70(uint *param_1,int *param_2)

{
  byte *pbVar1;
  uint *puVar2;
  float *pfVar3;
  float *pfVar4;
  byte bVar5;
  char cVar6;
  int iVar7;
  undefined1 *puVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  undefined4 *puVar12;
  uint *extraout_EDX;
  uint *puVar13;
  uint *puVar14;
  byte *pbVar15;
  uint uVar16;
  bool bVar17;
  float fVar18;
  undefined8 uVar19;
  char *pcVar20;
  int local_38;
  int local_34;
  byte *local_30;
  byte *local_2c;
  undefined1 local_28 [4];
  char acStack_24 [32];
  uint local_4;
  
  pbVar15 = DAT_100a0500;
  local_4 = DAT_1009f100 ^ (uint)&local_38;
  local_34 = 0;
  local_38 = DAT_1009fcdc;
  if (DAT_100a0500 != (byte *)0x0) {
    iVar7 = FUN_100097d0();
    local_34 = *(int *)(*(int *)(iVar7 + 0x48) + (((int)pbVar15 - *_DAT_00b74494) / 0xa18) * 4) +
               local_38;
  }
  pbVar15 = (byte *)0x0;
  local_2c = (byte *)*param_1;
  uVar16 = param_1[1] & 0xffffff;
  local_38 = *(int *)(*_DAT_00c8800c +
                     *(short *)(*(int *)(DAT_1009fd1c + DAT_1009fdbc * 4) + 10) * 0xc);
  if (local_2c != (byte *)0x0) {
    pbVar15 = *(byte **)(local_2c + DAT_100a0460 + 8);
  }
  local_28 = (undefined1  [4])uVar16;
  if (((_DAT_00b4e47c != 0) && (local_2c != (byte *)0x0)) && (local_2c[0x10] == 0x23)) {
    *(uint **)*param_2 = param_1;
    *(uint *)(*param_2 + 4) = *param_1;
    *param_2 = *param_2 + 8;
    uVar16 = _DAT_00b4e47c;
    if (pbVar15 != (byte *)0x0) {
      uVar16 = FUN_10002020(_DAT_00b4e47c);
    }
    *param_1 = uVar16;
    puVar14 = param_1 + 1;
    *(uint **)*param_2 = puVar14;
    iVar7 = *param_2;
    *(uint *)(iVar7 + 4) = *puVar14;
    *param_2 = *param_2 + 8;
    *puVar14 = *puVar14 | 0xffffff;
    FUN_100182e0(local_4 ^ (uint)&local_38,iVar7);
    return;
  }
  _DAT_1009fc3c = 0;
  if (local_2c != (byte *)0x0) {
    if (pbVar15 == (byte *)0x0) {
      pbVar15 = local_2c + 0x10;
      iVar7 = -(int)pbVar15;
      do {
        if (*pbVar15 != pbVar15[(int)("?vehiclegrunge256" + iVar7 + 1)]) goto LAB_100080e4;
        if (*pbVar15 == 0) break;
        pbVar1 = pbVar15 + 1;
        if (*pbVar1 != pbVar15[(int)("?vehiclegrunge256" + iVar7 + 2)]) goto LAB_100080e4;
        pbVar15 = pbVar15 + 2;
      } while (*pbVar1 != 0);
      (*(code *)0x74dbc0)(param_1,*(undefined4 *)(DAT_1009fc64 + DAT_100a04b0 * 4));
LAB_100080e4:
      local_30 = (byte *)(*param_1 + 0x10);
      pbVar15 = local_30;
      do {
        if (*pbVar15 != pbVar15[(int)"vehiclegrunge512" + -(int)local_30]) {
LAB_10008132:
          pbVar15 = local_30;
          goto LAB_10008140;
        }
        if (*pbVar15 == 0) break;
        pbVar1 = pbVar15 + 1;
        if (*pbVar1 != pbVar15[(int)("vehiclegrunge512" + -(int)local_30 + 1)]) goto LAB_10008132;
        pbVar15 = pbVar15 + 2;
      } while (*pbVar1 != 0);
      pbVar15 = (byte *)0x0;
      (*(code *)0x74dbc0)(param_1,*(undefined4 *)(DAT_1009fc38 + DAT_100a04b0 * 4));
    }
    else {
      *(uint **)*param_2 = param_1;
      *(uint *)(*param_2 + 4) = *param_1;
      *param_2 = *param_2 + 8;
      uVar10 = FUN_10002020(*param_1);
      *param_1 = uVar10;
    }
  }
  goto LAB_100082c4;
  while( true ) {
    pbVar1 = pbVar15 + 1;
    if (*pbVar1 != pbVar15[(int)("vehiclegrunge_iv" + -(int)local_30 + 1)]) goto LAB_1000817b;
    pbVar15 = pbVar15 + 2;
    if (*pbVar1 == 0) break;
LAB_10008140:
    if (*pbVar15 != pbVar15[(int)"vehiclegrunge_iv" + -(int)local_30]) {
LAB_1000817b:
      pbVar15 = local_30;
      goto LAB_10008184;
    }
    if (*pbVar15 == 0) break;
  }
  pbVar15 = (byte *)0x0;
  (*(code *)0x74dbc0)(param_1,*(undefined4 *)(DAT_1009fc54 + DAT_100a04b0 * 4));
  goto LAB_100082c4;
  while( true ) {
    bVar5 = pbVar15[1];
    bVar17 = bVar5 < pbVar15[(int)("tyrewall_dirt_1" + -(int)local_30 + 1)];
    if (bVar5 != pbVar15[(int)("tyrewall_dirt_1" + -(int)local_30 + 1)]) goto LAB_100081c3;
    pbVar15 = pbVar15 + 2;
    if (bVar5 == 0) break;
LAB_10008184:
    bVar5 = *pbVar15;
    bVar17 = bVar5 < pbVar15[(int)"tyrewall_dirt_1" + -(int)local_30];
    if (bVar5 != pbVar15[(int)"tyrewall_dirt_1" + -(int)local_30]) {
LAB_100081c3:
      pbVar15 = (byte *)((-(uint)bVar17 & 0xfffffffe) + 1);
      if (((DAT_1009fc07 == '\0') && (DAT_100a0500 != (byte *)0x0)) &&
         (*(char *)(local_34 + 0x20) != '\0')) {
        iVar7 = _strncmp((char *)local_30,"plateback1",10);
        if (iVar7 == 0) {
          *(uint **)*param_2 = param_1;
          *(uint *)(*param_2 + 4) = *param_1;
          puVar14 = param_1 + 3;
          *param_2 = *param_2 + 8;
          *param_1 = DAT_100a04c0;
          *(uint **)*param_2 = puVar14;
          *(uint *)(*param_2 + 4) = *puVar14;
          *param_2 = *param_2 + 8;
          *puVar14 = DAT_1009eeac;
          pbVar15 = (byte *)0x0;
        }
        else {
          iVar7 = _strncmp((char *)(*param_1 + 0x10),"plateback2",10);
          pbVar15 = (byte *)0x0;
          if ((iVar7 == 0) ||
             (pbVar15 = (byte *)_strncmp((char *)(*param_1 + 0x10),"plateback3",10),
             pbVar15 == (byte *)0x0)) {
            puVar14 = param_1 + 3;
            *(uint **)*param_2 = param_1;
            *(uint *)(*param_2 + 4) = *param_1;
            *param_2 = *param_2 + 8;
            *param_1 = DAT_100a04c0;
            *(uint **)*param_2 = puVar14;
            *(uint *)(*param_2 + 4) = *puVar14;
            *param_2 = *param_2 + 8;
            *puVar14 = DAT_1009eeac;
          }
        }
      }
      goto LAB_100082c4;
    }
    if (bVar5 == 0) break;
  }
  pbVar15 = (byte *)0x0;
  (*(code *)0x74dbc0)(param_1,*(undefined4 *)(DAT_1009fc6c + DAT_100a04b0 * 4));
LAB_100082c4:
  if ((local_38 == 0) || (iVar7 = (*(code *)0x7f39f0)(local_38,"vehiclelights"), iVar7 == 0)) {
    pbVar15 = _DAT_00b4e68c;
  }
  if ((local_2c == pbVar15) || (local_2c == _DAT_00b4e68c)) {
    iVar7 = 0;
    do {
      iVar9 = iVar7;
      if (uVar16 == (&DAT_1009e91c)[iVar7]) break;
      iVar7 = iVar7 + 1;
      iVar9 = -1;
    } while (iVar7 < 0x12);
    puVar14 = param_1 + 1;
    *(uint **)*param_2 = puVar14;
    *(uint *)(*param_2 + 4) = *puVar14;
    *param_2 = *param_2 + 8;
    *puVar14 = *puVar14 | 0xffffff;
    pbVar15 = DAT_100a0500;
    iVar7 = DAT_1009fcdc;
    local_2c = DAT_100a0500;
    if (iVar9 == -1) {
      iVar11 = FUN_100097d0();
      local_34 = DAT_1009fcdc;
      local_30 = DAT_100a0500;
      iVar9 = (int)local_2c - *_DAT_00b74494 >> 0x1f;
      puVar14 = (uint *)(((int)local_2c - *_DAT_00b74494) / 0xa18 + iVar9);
      if (*(int *)(*(int *)(*(int *)(*(int *)(iVar11 + 0x48) + ((int)puVar14 - iVar9) * 4) + 0x28 +
                           iVar7) + 0x350) == 0) goto LAB_1000883e;
      uVar16 = 0xff;
      if (local_28 != (undefined1  [4])0xff) {
        do {
          uVar16 = uVar16 - 1;
          if ((int)uVar16 < 0xf0) goto LAB_1000883e;
        } while (local_28 != (undefined1  [4])uVar16);
      }
      iVar7 = FUN_100097d0();
      puVar14 = param_1 + 1;
      iVar9 = *(int *)(*(int *)(iVar7 + 0x48) + (((int)local_30 - *_DAT_00b74494) / 0xa18) * 4) +
              local_34;
      *(uint **)*param_2 = puVar14;
      *(uint *)(*param_2 + 4) = *puVar14;
      *param_2 = *param_2 + 8;
      iVar7 = *(int *)(iVar9 + 0x34);
      *(undefined2 *)puVar14 = *(undefined2 *)(iVar7 + 8);
      *(undefined1 *)((int)param_1 + 6) = *(undefined1 *)(iVar7 + 10);
      if (*(char *)(iVar9 + 0x31) == '\0') goto LAB_1000883e;
      puVar14 = param_1 + 3;
      pfVar3 = (float *)(param_1 + 5);
      pfVar4 = (float *)(param_1 + 4);
      *(uint **)*param_2 = puVar14;
      *(uint *)(*param_2 + 4) = *puVar14;
      iVar7 = *param_2;
      *param_2 = iVar7 + 8;
      *(float **)(iVar7 + 8) = pfVar3;
      *(float *)(*param_2 + 4) = *pfVar3;
      iVar7 = *param_2;
      *param_2 = iVar7 + 8;
      *(float **)(iVar7 + 8) = pfVar4;
      *(float *)(*param_2 + 4) = *pfVar4;
      *param_2 = *param_2 + 8;
      *puVar14 = DAT_1009ee9c;
      fVar18 = (float)DAT_1009fc74;
      if (DAT_1009fc74 < 0) {
        fVar18 = fVar18 + DAT_1009e594;
      }
      *pfVar4 = fVar18;
      fVar18 = (float)DAT_1009fc78;
      if (DAT_1009fc78 < 0) {
        fVar18 = fVar18 + DAT_1009e594;
      }
      *pfVar3 = fVar18;
      uVar16 = *param_1;
      pcVar20 = (char *)(uVar16 + 0x10);
      do {
        cVar6 = *pcVar20;
        pcVar20[(int)(acStack_24 + -(int)(uVar16 + 0x10))] = cVar6;
        pcVar20 = pcVar20 + 1;
      } while (cVar6 != '\0');
      puVar12 = (undefined4 *)(local_28 + 3);
      do {
        pcVar20 = (char *)((int)puVar12 + 1);
        puVar12 = (undefined4 *)((int)puVar12 + 1);
      } while (*pcVar20 != '\0');
      goto LAB_1000880d;
    }
    if (*(char *)(iVar9 + 0x100a0470) == '\0') goto LAB_1000883e;
    if (*(char *)(iVar9 + 0x100a0470) != '\x02') {
      puVar14 = param_1 + 3;
      *(uint **)*param_2 = param_1;
      *(uint *)(*param_2 + 4) = *param_1;
      iVar7 = *param_2;
      *param_2 = iVar7 + 8;
      *(uint **)(iVar7 + 8) = puVar14;
      *(uint *)(*param_2 + 4) = *puVar14;
      iVar7 = *param_2;
      *param_2 = iVar7 + 8;
      *(uint **)(iVar7 + 8) = param_1 + 5;
      puVar13 = param_1 + 4;
      *(uint *)(*param_2 + 4) = param_1[5];
      iVar7 = *param_2;
      *param_2 = iVar7 + 8;
      *(uint **)(iVar7 + 8) = puVar13;
      *(uint *)(*param_2 + 4) = *puVar13;
      *param_2 = *param_2 + 8;
      if (local_38 != 0) {
        uVar19 = (*(code *)0x7f39f0)(local_38,"vehiclelights_on");
        puVar13 = (uint *)((ulonglong)uVar19 >> 0x20);
        if ((int)uVar19 != 0) goto LAB_1000865e;
      }
      pbVar15 = _DAT_00b4e690;
LAB_1000865e:
      *param_1 = (uint)pbVar15;
      *puVar14 = DAT_1009eeac;
      param_1[4] = 0;
      param_1[5] = 0;
      FUN_100182e0(local_4 ^ (uint)&local_38,puVar13);
      return;
    }
    if (local_38 == 0) goto LAB_1000883e;
    pcVar20 = "vehiclelights_dam";
  }
  else {
    if (uVar16 == 0xff3c) {
      iVar7 = *DAT_1009e5f4;
LAB_10008347:
      puVar14 = param_1 + 1;
      *(uint **)*param_2 = puVar14;
      *(uint *)(*param_2 + 4) = *puVar14;
      *param_2 = *param_2 + 8;
      if (((DAT_100a0500 != (byte *)0x0) && (iVar9 = *(int *)(local_34 + 0x30), iVar9 != 0)) &&
         (iVar7 < (int)(uint)*(byte *)(local_34 + 0x2c))) {
        *(undefined1 *)puVar14 = *(undefined1 *)(iVar9 + iVar7 * 4);
        *(undefined1 *)((int)param_1 + 5) = *(undefined1 *)(iVar9 + 1 + iVar7 * 4);
        *(undefined1 *)((int)param_1 + 6) = *(undefined1 *)(iVar9 + 2 + iVar7 * 4);
        FUN_100182e0(local_4 ^ (uint)&local_38,puVar14);
        return;
      }
      puVar8 = (undefined1 *)(*(code *)0x447090)(iVar7);
      *(undefined1 *)(param_1 + 1) = *puVar8;
      iVar9 = (*(code *)0x447090)(iVar7);
      *(undefined1 *)((int)param_1 + 5) = *(undefined1 *)(iVar9 + 1);
      uVar19 = (*(code *)0x447090)(iVar7);
      *(undefined1 *)((int)param_1 + 6) = *(undefined1 *)((int)uVar19 + 2);
      FUN_100182e0(local_4 ^ (uint)&local_38,(int)((ulonglong)uVar19 >> 0x20));
      return;
    }
    if (uVar16 == 0xaf00ff) {
      iVar7 = DAT_1009e5f4[1];
      goto LAB_10008347;
    }
    if (uVar16 == 0xffff00) {
      iVar7 = DAT_1009e5f4[2];
      goto LAB_10008347;
    }
    if (uVar16 == 0xff00ff) {
      iVar7 = DAT_1009e5f4[3];
      goto LAB_10008347;
    }
    if (uVar16 == 0xff1200) {
      puVar14 = param_1 + 1;
      *(uint **)*param_2 = puVar14;
      *(uint *)(*param_2 + 4) = *puVar14;
      *param_2 = *param_2 + 8;
      if (DAT_100a0490 != '\0') {
        *puVar14 = *puVar14 | 0xffffff;
        FUN_100182e0(local_4 ^ (uint)&local_38,puVar14);
        return;
      }
      *(undefined1 *)((int)param_1 + 7) = 0;
      FUN_100182e0(local_4 ^ (uint)&local_38,puVar14);
      return;
    }
    if (uVar16 == 0xff1000) {
      puVar14 = param_1 + 1;
      *(uint **)*param_2 = puVar14;
      *(uint *)(*param_2 + 4) = *puVar14;
      *param_2 = *param_2 + 8;
      *puVar14 = *puVar14 | 0xffffff;
      if (DAT_100a0480 == '\0') goto LAB_1000883e;
      puVar14 = param_1 + 3;
      puVar13 = param_1 + 5;
      *(uint **)*param_2 = puVar14;
      *(uint *)(*param_2 + 4) = *puVar14;
      iVar7 = *param_2;
      *param_2 = iVar7 + 8;
      *(uint **)(iVar7 + 8) = puVar13;
      *(uint *)(*param_2 + 4) = *puVar13;
      *param_2 = *param_2 + 8;
      *puVar14 = DAT_1009eeac;
      *puVar13 = 0;
      uVar16 = *param_1;
      pcVar20 = (char *)(uVar16 + 0x10);
      do {
        cVar6 = *pcVar20;
        pcVar20[(int)(acStack_24 + -(int)(uVar16 + 0x10))] = cVar6;
        pcVar20 = pcVar20 + 1;
      } while (cVar6 != '\0');
      puVar12 = (undefined4 *)(local_28 + 3);
      do {
        pcVar20 = (char *)((int)puVar12 + 1);
        puVar12 = (undefined4 *)((int)puVar12 + 1);
      } while (*pcVar20 != '\0');
    }
    else {
      iVar7 = FUN_100092d0();
      puVar14 = extraout_EDX;
      if (*(int *)(*(int *)(iVar7 + 0x28) + 0x350) == 0) goto LAB_1000883e;
      uVar10 = 0xff;
      iVar7 = 0;
      if (uVar16 != 0xff) {
        do {
          uVar10 = uVar10 - 1;
          iVar7 = iVar7 + 1;
          if ((int)uVar10 < 0xf0) goto LAB_1000883e;
        } while (uVar16 != uVar10);
      }
      iVar9 = FUN_100092d0();
      puVar14 = param_1 + 1;
      iVar9 = *(int *)(iVar9 + 0x28);
      *(uint **)*param_2 = puVar14;
      *(uint *)(*param_2 + 4) = *puVar14;
      *param_2 = *param_2 + 8;
      iVar11 = *(int *)(iVar9 + 0x360 + iVar7 * 0x14);
      *(undefined2 *)puVar14 = *(undefined2 *)(iVar11 + 8);
      *(undefined1 *)((int)param_1 + 6) = *(undefined1 *)(iVar11 + 10);
      if (*(char *)(iVar9 + 0x35d + iVar7 * 0x14) == '\0') goto LAB_1000883e;
      puVar14 = param_1 + 3;
      puVar13 = param_1 + 5;
      puVar2 = param_1 + 4;
      *(uint **)*param_2 = puVar14;
      *(uint *)(*param_2 + 4) = *puVar14;
      iVar7 = *param_2;
      *param_2 = iVar7 + 8;
      *(uint **)(iVar7 + 8) = puVar13;
      *(uint *)(*param_2 + 4) = *puVar13;
      iVar7 = *param_2;
      *param_2 = iVar7 + 8;
      *(uint **)(iVar7 + 8) = puVar2;
      *(uint *)(*param_2 + 4) = *puVar2;
      *param_2 = *param_2 + 8;
      uVar16 = DAT_1009eeac;
      *puVar2 = 0;
      *puVar13 = 0;
      *puVar14 = uVar16;
      uVar16 = *param_1;
      pcVar20 = (char *)(uVar16 + 0x10);
      do {
        cVar6 = *pcVar20;
        pcVar20[(int)(acStack_24 + -(int)(uVar16 + 0x10))] = cVar6;
        pcVar20 = pcVar20 + 1;
      } while (cVar6 != '\0');
      puVar12 = (undefined4 *)(local_28 + 3);
      do {
        pcVar20 = (char *)((int)puVar12 + 1);
        puVar12 = (undefined4 *)((int)puVar12 + 1);
      } while (*pcVar20 != '\0');
    }
LAB_1000880d:
    *puVar12 = DAT_1009ee6c;
    pcVar20 = acStack_24;
  }
  uVar19 = (*(code *)0x7f39f0)(local_38,pcVar20);
  puVar14 = (uint *)((ulonglong)uVar19 >> 0x20);
  if ((uint)uVar19 != 0) {
    *(uint **)*param_2 = param_1;
    puVar14 = (uint *)*param_2;
    puVar14[1] = *param_1;
    *param_2 = *param_2 + 8;
    *param_1 = (uint)uVar19;
  }
LAB_1000883e:
  FUN_100182e0(local_4 ^ (uint)&local_38,puVar14);
  return;
}


