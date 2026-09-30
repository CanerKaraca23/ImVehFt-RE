/* Temporary bounded Ghidra decompilation; not original source. */

/* entry 0x10001770; bounded CFG instructions=79; body bytes=212 */

void BOUNDED_10001770(void)

{
  undefined4 uStack_10;
  undefined1 auStack_c [4];
  undefined4 uStack_8;
  
  uStack_8 = 0xe8;
  VirtualProtect(0x5b388d,1,0x40,&uStack_10);
  uRam005b388d = (undefined1)uStack_8;
  VirtualProtect(0x5b388d,1,uStack_10,auStack_c);
  VirtualProtect(0x5b388e,4,0x40,&uStack_10);
  uRam005b388e = 0xfa4e00e;
  VirtualProtect(0x5b388e,4,uStack_10,auStack_c);
  uStack_8 = 0xe8;
  VirtualProtect(0x731e09,1,0x40,&uStack_10);
  uRam00731e09 = (undefined1)uStack_8;
  VirtualProtect(0x731e09,1,uStack_10,auStack_c);
  VirtualProtect(0x731e0a,4,0x40,&uStack_10);
  uRam00731e0a = 0xf8cfa92;
  VirtualProtect(0x731e0a,4,uStack_10,auStack_c);
  return;
}


