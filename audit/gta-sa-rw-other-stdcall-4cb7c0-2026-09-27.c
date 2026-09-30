/* Temporary bounded Ghidra decompilation; not original source. */

/* entry 0x004CB7C0; bounded CFG instructions=176; body bytes=512 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 BOUNDED_004CB7C0(int param_1)

{
  undefined4 *puVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  int unaff_EDI;
  int iVar7;
  
  bVar2 = *(byte *)(param_1 + 0x23);
  if ((bVar2 & 0x60) == 0) {
    *(undefined4 *)(unaff_EDI + 0x18) = *(undefined4 *)(&UNK_0085c670 + (bVar2 & 0xf) * 8);
  }
  else {
    if (((bVar2 & 0xf) != 6) && ((bVar2 & 0xf) != 5)) {
      return 0;
    }
    if (_DAT_00b4e9f8 == 0) {
      _DAT_00b4e9f8 = func_0x00801980(0x404,0x40,4,0x30411);
    }
    iVar3 = (**(code **)(_DAT_00c97b24 + 0x144))(_DAT_00b4e9f8,0x30411);
    *(int *)(unaff_EDI + 4) = iVar3;
    if (iVar3 != 0) {
      if (_DAT_00b4e9e8 == 0) {
        uVar6 = _DAT_00b4e9f0;
        _DAT_00b4e9f0 = _DAT_00b4e9f0 + 1;
      }
      else {
        _DAT_00b4e9e8 = _DAT_00b4e9e8 + -1;
        uVar6 = (uint)*(ushort *)(_DAT_00b4e9f4 + _DAT_00b4e9e8 * 2);
      }
      *(uint *)(iVar3 + 0x400) = uVar6;
    }
    *(undefined4 *)(unaff_EDI + 0x18) = 0x29;
  }
  *(undefined *)(unaff_EDI + 8) = (&UNK_0085c675)[(bVar2 & 0xf) * 8];
  piVar5 = (int *)(param_1 + 0x10);
  puVar1 = (undefined4 *)(param_1 + 0xc);
  func_0x007fed70(puVar1,piVar5,CONCAT11(bVar2,*(undefined1 *)(param_1 + 0x20)));
  if ((*(byte *)(unaff_EDI + 9) & 0xf) == 0) {
    iVar3 = *(int *)(unaff_EDI + 0x18);
    if ((iVar3 < 0x46) || (0x50 < iVar3)) {
      iVar7 = *piVar5;
      iVar4 = func_0x00730510(*puVar1,iVar7,~(bVar2 >> 7) & 1,iVar3);
    }
    else {
      iVar4 = (**(code **)(*_DAT_00c97c28 + 0x5c))(_DAT_00c97c28,*puVar1,*piVar5,1,2,iVar3,0);
      if (iVar4 < 0) goto LAB_004cb943;
      func_0x004cb530(iVar3);
      iVar7 = iVar3;
    }
  }
  else {
    iVar7 = *(int *)(unaff_EDI + 0x18);
    iVar4 = (**(code **)(*_DAT_00c97c28 + 100))
                      (_DAT_00c97c28,*puVar1,~(bVar2 >> 7) & 1,
                       -(uint)((*(byte *)(unaff_EDI + 10) & 0xf) != 0) & 0x400,iVar7,1);
  }
  if (-1 < iVar4) {
    if (*(int *)(unaff_EDI + 4) != 0) {
      piVar5 = (int *)(**(code **)(_DAT_00c97b24 + 0x144))(_DAT_00b4ea00,0x30411);
      *piVar5 = iVar7;
      piVar5[1] = (int)_DAT_00b4e9fc;
      _DAT_00b4e9fc = piVar5;
    }
    return 1;
  }
LAB_004cb943:
  if ((*(int *)(unaff_EDI + 0x18) == 0x29) && (*(int *)(unaff_EDI + 4) != 0)) {
    func_0x004cb730();
    (**(code **)(_DAT_00c97b24 + 0x148))(_DAT_00b4e9f8,*(undefined4 *)(unaff_EDI + 4));
    *(undefined4 *)(unaff_EDI + 4) = 0;
  }
  return 0;
}


