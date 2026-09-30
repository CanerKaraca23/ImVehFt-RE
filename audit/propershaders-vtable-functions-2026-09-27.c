/* Temporary bounded Ghidra decompilation; not original source. */

/* entry 0x100851CF; bounded CFG instructions=29; body bytes=97 */

void __fastcall BOUNDED_100851CF(undefined4 param_1)

{
  int *piVar1;
  undefined4 in_EAX;
  int unaff_EBP;
  undefined4 *unaff_FS_OFFSET;
  
  *(undefined **)(unaff_EBP + -200) = &UNK_1017a0dc;
  *(undefined4 *)(unaff_EBP + -0xa4) = in_EAX;
  *(undefined4 *)(unaff_EBP + -4) = 4;
  func_0x10085930(param_1);
  piVar1 = *(int **)(unaff_EBP + -0xa4);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x10))(piVar1 != (int *)(unaff_EBP + -200));
  }
  *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0xc);
  func_0x100a4f7d();
  return;
}



/* entry 0x10085930; bounded CFG instructions=146; body bytes=525 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall BOUNDED_10085930(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  int *unaff_FS_OFFSET;
  undefined4 uStack_1c;
  int iStack_18;
  undefined4 uStack_14;
  int iStack_10;
  undefined *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &DAT_100d4785;
  iStack_10 = *unaff_FS_OFFSET;
  uVar3 = _DAT_101940c0 ^ (uint)&stack0xfffffffc;
  *unaff_FS_OFFSET = (int)&iStack_10;
  uStack_14 = param_1;
  if ((*(int *)(*(int *)(unaff_FS_OFFSET[0xb] + __tls_index * 4) + 4) < _DAT_101ac47c) &&
     (func_0x100a5391(&DAT_101ac47c,uVar3), _DAT_101ac47c == -1)) {
    _DAT_101ac484 = 0;
    _DAT_101ac488 = 0;
    _DAT_101ac48c = 0;
    uStack_8._0_1_ = 1;
    uStack_8._1_3_ = 0;
    _DAT_101ac490 = 0;
    DAT_101ac494 = '\0';
    _DAT_101ac498 = 0;
    _DAT_101ac49c = 0;
    _DAT_101ac498 = func_0x100a4f8b(0x38);
    *(int *)_DAT_101ac498 = _DAT_101ac498;
    *(int *)(_DAT_101ac498 + 4) = _DAT_101ac498;
    uStack_8 = CONCAT31(uStack_8._1_3_,2);
    _DAT_101ac4a0 = (undefined4 *)0x0;
    _DAT_101ac4a4 = 0;
    _DAT_101ac4a0 = (undefined4 *)func_0x100a4f8b(0x38);
    *_DAT_101ac4a0 = _DAT_101ac4a0;
    _DAT_101ac4a0[1] = _DAT_101ac4a0;
    func_0x100a52c2(&UNK_100d5c00);
    uStack_8 = 0xffffffff;
    func_0x100a5340(&DAT_101ac47c);
  }
  uStack_1c = 0;
  piVar5 = *(int **)(param_3 + 0x24);
  if (piVar5 != (int *)0x0) {
    iVar4 = (**(code **)(*piVar5 + 0xc))();
    iVar4 = func_0x100a691c(iVar4 + 4,0x101966c0);
    if (iVar4 == 0) {
      piVar5 = (int *)(**(code **)(*piVar5 + 0x14))();
    }
    else {
      piVar5 = (int *)0x0;
    }
    puVar2 = _DAT_101ac4a0;
    if (piVar5 != (int *)0x0) {
      iStack_18 = *piVar5;
      param_1 = uStack_14;
      for (puVar1 = (undefined4 *)*_DAT_101ac4a0; uStack_14 = param_1, puVar1 != puVar2;
          puVar1 = (undefined4 *)*puVar1) {
        piVar5 = (int *)puVar1[0xb];
        if (piVar5 != (int *)0x0) {
          iVar4 = (**(code **)(*piVar5 + 0xc))();
          iVar4 = func_0x100a691c(iVar4 + 4,0x101966c0);
          if (iVar4 == 0) {
            piVar5 = (int *)(**(code **)(*piVar5 + 0x14))();
          }
          else {
            piVar5 = (int *)0x0;
          }
          if ((piVar5 != (int *)0x0) && (*piVar5 == iStack_18)) {
            *unaff_FS_OFFSET = iStack_10;
            return uStack_14;
          }
        }
        param_1 = uStack_14;
      }
    }
  }
  if (DAT_101ac494 == '\0') {
    _DAT_101ac490 = 0;
    DAT_101ac494 = '\x01';
    func_0x100860f0(param_3);
  }
  func_0x1007b850(param_3,&uStack_1c);
  *unaff_FS_OFFSET = iStack_10;
  return param_1;
}



/* entry 0x100857E0; bounded CFG instructions=2; body bytes=6 */

undefined4 BOUNDED_100857E0(void)

{
  return 0x10196d50;
}



/* entry 0x10085850; bounded CFG instructions=6; body bytes=16 */

void BOUNDED_10085850(undefined4 *param_1)

{
  *param_1 = &UNK_1017a0dc;
  return;
}



/* entry 0x100A4F7D; bounded CFG instructions=60; body bytes=265 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall BOUNDED_100A4F7D(int param_1)

{
  code *pcVar1;
  uint uVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar3;
  undefined4 unaff_EBX;
  undefined4 unaff_EBP;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  undefined2 in_ES;
  undefined2 in_CS;
  undefined2 in_SS;
  undefined2 in_DS;
  undefined2 in_FS;
  undefined2 in_GS;
  byte bVar4;
  byte bVar5;
  byte in_AF;
  byte bVar6;
  byte bVar7;
  byte in_TF;
  byte in_IF;
  byte bVar8;
  byte in_NT;
  byte in_AC;
  byte in_VIF;
  byte in_VIP;
  byte in_ID;
  ulonglong uVar9;
  undefined4 unaff_retaddr;
  
  if (param_1 == _DAT_101940c0) {
    return;
  }
  uVar9 = IsProcessorFeaturePresent(0x17);
  uVar2 = (uint)uVar9;
  bVar4 = 0;
  bVar8 = 0;
  bVar7 = (int)uVar2 < 0;
  bVar6 = uVar2 == 0;
  bVar5 = (POPCOUNT(uVar2 & 0xff) & 1U) == 0;
  uVar9 = uVar9 & 0xffffffff00000000;
  uVar3 = extraout_ECX;
  if (!(bool)bVar6) {
    pcVar1 = (code *)swi(0x29);
    uVar9 = (*pcVar1)();
    uVar3 = extraout_ECX_00;
  }
  _DAT_1019c428 = (undefined4)(uVar9 >> 0x20);
  _DAT_1019c430 = (undefined4)uVar9;
  _DAT_1019c440 =
       (uint)(in_NT & 1) * 0x4000 | (uint)(bVar8 & 1) * 0x800 | (uint)(in_IF & 1) * 0x200 |
       (uint)(in_TF & 1) * 0x100 | (uint)(bVar7 & 1) * 0x80 | (uint)(bVar6 & 1) * 0x40 |
       (uint)(in_AF & 1) * 0x10 | (uint)(bVar5 & 1) * 4 | (uint)(bVar4 & 1) |
       (uint)(in_ID & 1) * 0x200000 | (uint)(in_VIP & 1) * 0x100000 | (uint)(in_VIF & 1) * 0x80000 |
       (uint)(in_AC & 1) * 0x40000;
  _DAT_1019c444 = &stack0x00000004;
  _DAT_1019c380 = 0x10001;
  _DAT_1019c330 = 0xc0000409;
  _DAT_1019c334 = 1;
  _DAT_1019c340 = 1;
  uRam1019c344 = 2;
  _DAT_1019c33c = unaff_retaddr;
  _DAT_1019c40c = in_GS;
  _DAT_1019c410 = in_FS;
  _DAT_1019c414 = in_ES;
  _DAT_1019c418 = in_DS;
  _DAT_1019c41c = unaff_EDI;
  _DAT_1019c420 = unaff_ESI;
  _DAT_1019c424 = unaff_EBX;
  _DAT_1019c42c = uVar3;
  _DAT_1019c434 = unaff_EBP;
  _DAT_1019c438 = unaff_retaddr;
  _DAT_1019c43c = in_CS;
  _DAT_1019c448 = in_SS;
  func_0x100a5571(&UNK_100f82ac);
  return;
}


