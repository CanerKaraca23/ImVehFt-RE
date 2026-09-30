/* Ghidra full-analysis xref callers; not original source. */

/* caller 00748f70 FUN_00748f70 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00748f70(void)

{
  int iVar1;
  
  iVar1 = FUN_007f2bb0(0,0x127,&LAB_00749000,&LAB_00749010);
  if (iVar1 < 0) {
    return 0;
  }
  DAT_00c92478 = FUN_007f3bb0(1,0x127,&LAB_00749020,&LAB_00749030,&LAB_00749040);
  if (DAT_00c92478 < 0) {
    return 0;
  }
  _DAT_00c9247c = FUN_00804550(0x127,&LAB_00749060,&LAB_007490b0,&LAB_007490f0);
  if (_DAT_00c9247c < 0) {
    return 0;
  }
  FUN_007fde60(DAT_00c92478);
  return 1;
}



/* caller 004c9ab0 FUN_004c9ab0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004c9ab0(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  DAT_00b4e9e0 = FUN_007fb0b0(0x24,0x40c,&LAB_004c9a60,&LAB_004c9a80,0);
  if (DAT_00b4e9e0 < 0) {
    return 0;
  }
  puVar2 = &DAT_00b4e7e0;
  for (iVar1 = 0x80; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  DAT_00b4e830 = 0;
  DAT_00b4e831 = 0x18;
  _DAT_00b4e832 = 0;
  DAT_00b4e834 = 1;
  DAT_00b4e835 = 0x20;
  _DAT_00b4e836 = 0x500;
  DAT_00b4e838 = 0;
  DAT_00b4e839 = 0x20;
  _DAT_00b4e83a = 0x600;
  DAT_00b4e83c = 0;
  DAT_00b4e83d = 0x10;
  _DAT_00b4e83e = 0x200;
  DAT_00b4e840 = 0;
  DAT_00b4e841 = 0x10;
  _DAT_00b4e842 = 0xa00;
  DAT_00b4e844 = 1;
  DAT_00b4e845 = 0x10;
  _DAT_00b4e846 = 0x100;
  DAT_00b4e848 = 1;
  DAT_00b4e849 = 0x10;
  _DAT_00b4e84a = 0x300;
  DAT_00b4e84c = 0;
  DAT_00b4e84d = 8;
  _DAT_00b4e84e = 0;
  DAT_00b4e850 = 1;
  DAT_00b4e851 = 8;
  _DAT_00b4e852 = 0;
  DAT_00b4e854 = 1;
  DAT_00b4e855 = 0x10;
  _DAT_00b4e856 = 0;
  DAT_00b4e858 = 0;
  DAT_00b4e859 = 0x10;
  _DAT_00b4e85a = 0;
  DAT_00b4e85c = 1;
  DAT_00b4e85d = 0x20;
  _DAT_00b4e85e = 0;
  DAT_00b4e860 = 1;
  DAT_00b4e861 = 0x20;
  _DAT_00b4e862 = 0;
  DAT_00b4e864 = 0;
  DAT_00b4e865 = 0x20;
  _DAT_00b4e866 = 0;
  DAT_00b4e868 = 0;
  DAT_00b4e869 = 0x20;
  _DAT_00b4e86a = 0;
  DAT_00b4e86c = 1;
  DAT_00b4e86d = 0x20;
  _DAT_00b4e86e = 0;
  DAT_00b4e870 = 1;
  DAT_00b4e871 = 0x40;
  _DAT_00b4e872 = 0;
  DAT_00b4e880 = 1;
  DAT_00b4e881 = 0x10;
  _DAT_00b4e882 = 0;
  DAT_00b4e884 = 0;
  DAT_00b4e885 = 8;
  _DAT_00b4e886 = 0x2000;
  DAT_00b4e8a8 = 0;
  DAT_00b4e8a9 = 8;
  _DAT_00b4e8aa = 0x400;
  DAT_00b4e8ac = 1;
  DAT_00b4e8ad = 0x10;
  _DAT_00b4e8ae = 0;
  DAT_00b4e8b0 = 1;
  DAT_00b4e8b1 = 8;
  _DAT_00b4e8b2 = 0;
  DAT_00b4e8d0 = 0;
  DAT_00b4e8d1 = 0x10;
  _DAT_00b4e8d2 = 0;
  DAT_00b4e8d4 = 0;
  DAT_00b4e8d5 = 0x10;
  _DAT_00b4e8d6 = 0;
  _DAT_00b4e8fa = 0x700;
  _DAT_00b4e906 = 0x700;
  _DAT_00b4e922 = 0x700;
  _DAT_00b4e8fe = 0x900;
  _DAT_00b4e90e = 0x900;
  _DAT_00b4e916 = 0x900;
  _DAT_00b4e91e = 0x900;
  _DAT_00b4e92a = 0x900;
  _DAT_00b4e92e = 0x900;
  DAT_00b4e8d8 = 0;
  _DAT_00b4e8da = 0;
  DAT_00b4e8dc = 0;
  _DAT_00b4e8de = 0;
  DAT_00b4e8e0 = 0;
  _DAT_00b4e8e2 = 0;
  _DAT_00b4e8ee = 0;
  DAT_00b4e8f8 = 0;
  DAT_00b4e8fc = 0;
  DAT_00b4e904 = 0;
  DAT_00b4e90c = 0;
  DAT_00b4e914 = 0;
  DAT_00b4e91c = 0;
  DAT_00b4e920 = 0;
  DAT_00b4e928 = 0;
  DAT_00b4e92c = 0;
  DAT_00b4e924 = 0;
  _DAT_00b4e926 = 0;
  DAT_00b4e998 = 0;
  _DAT_00b4e99a = 0;
  DAT_00b4e99c = 0;
  _DAT_00b4e99e = 0;
  DAT_00b4e9a0 = 0;
  _DAT_00b4e9a2 = 0;
  _DAT_00b4e9a6 = 0;
  DAT_00b4e9a8 = 0;
  _DAT_00b4e9aa = 0;
  DAT_00b4e9ac = 0;
  _DAT_00b4e9ae = 0;
  _DAT_00b4e9b2 = 0;
  DAT_00b4e9b4 = 0;
  _DAT_00b4e9b6 = 0;
  DAT_00b4e8d9 = 0x20;
  DAT_00b4e8dd = 0x20;
  DAT_00b4e8e1 = 0x20;
  DAT_00b4e8ec = 1;
  DAT_00b4e8ed = 0x20;
  DAT_00b4e8f9 = 0x10;
  DAT_00b4e8fd = 0x20;
  DAT_00b4e905 = 0x10;
  DAT_00b4e90d = 0x20;
  DAT_00b4e915 = 0x20;
  DAT_00b4e91d = 0x20;
  DAT_00b4e921 = 0x10;
  DAT_00b4e929 = 0x20;
  DAT_00b4e92d = 0x20;
  DAT_00b4e925 = 0x10;
  DAT_00b4e999 = 0x40;
  DAT_00b4e99d = 0x10;
  DAT_00b4e9a1 = 0x20;
  DAT_00b4e9a4 = 1;
  DAT_00b4e9a5 = 0x40;
  DAT_00b4e9a9 = 0x20;
  DAT_00b4e9ad = 0x40;
  DAT_00b4e9b0 = 1;
  DAT_00b4e9b1 = 0x80;
  DAT_00b4e9b5 = 0x10;
  return 1;
}



/* caller 0072fab0 FUN_0072fab0 */

bool FUN_0072fab0(void)

{
  DAT_00c87c5c = FUN_007f1260(0x18,0x253f2fe,&LAB_0072f9c0,&LAB_0072f9e0,&LAB_0072f9f0);
  FUN_00807580(0x253f2fe,&LAB_0072fa50,&LAB_0072fa20,&LAB_0072fa80);
  return DAT_00c87c5c != -1;
}



/* caller 00732e30 FUN_00732e30 */

undefined4 FUN_00732e30(void)

{
  DAT_008d608c = FUN_0074bda0(4,0x253f200,&LAB_00732150,&LAB_007321a0,&LAB_00732170);
  DAT_008d6090 = FUN_007f1260(4,0x253f202,&LAB_007321b0,&LAB_007321f0,&LAB_007321d0);
  DAT_008d6094 = FUN_0074bdd0(8,0x253f201,&LAB_00732e10,&LAB_00732220,&LAB_00732200);
  if ((DAT_008d608c != -1) && (DAT_008d6094 != -1)) {
    return 1;
  }
  return 0;
}



/* caller 007c4600 FUN_007c4600 */

undefined4 FUN_007c4600(void)

{
  int iVar1;
  
  iVar1 = FUN_007f2bb0(0,0x11e,&LAB_007c4670,&LAB_007c4720);
  if (-1 < iVar1) {
    DAT_00c9b8c8 = FUN_007f1260(8,0x11e,&LAB_007c4750,&LAB_007c4770,&LAB_007c4830);
    iVar1 = FUN_00807580(0x11e,&LAB_007c4a00,&LAB_007c48d0,&LAB_007c4bf0);
    if ((-1 < iVar1) && (-1 < DAT_00c9b8c8)) {
      return 1;
    }
  }
  return 0;
}


