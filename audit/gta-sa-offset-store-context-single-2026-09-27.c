/* Temporary bounded Ghidra decompilation; not original source. */

/* entry 0x00749C50; bounded CFG instructions=68; body bytes=201 */

/* WARNING: Removing unreachable block (ram,0x00749cd2) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 * BOUNDED_00749C50(void)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  
  puVar2 = (undefined1 *)
           (**(code **)(_DAT_00c97b24 + 0x144))
                     (*(undefined4 *)(_DAT_00c924ac + _DAT_00c97b24),0x30014);
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = 1;
    puVar2[1] = 0;
    *(undefined4 *)(puVar2 + 4) = 0;
    *(undefined **)(puVar2 + 0x10) = &UNK_00749d20;
    *(undefined4 *)(puVar2 + 0x14) = 0;
    puVar2[2] = 5;
    puVar2[3] = 1;
    func_0x00804ef0(puVar2,0);
    *(undefined4 *)(puVar2 + 0x18) = 0;
    puVar2[3] = puVar2[3] | 1;
    *(undefined4 *)(puVar2 + 0x28) = 0;
    *(undefined4 *)(puVar2 + 0x1c) = 0;
    *(undefined4 *)(puVar2 + 0x20) = 0;
    *(undefined4 *)(puVar2 + 0x24) = 0;
    *(undefined4 *)(puVar2 + 0x38) = 0;
    *(undefined4 *)(puVar2 + 0x2c) = 0;
    *(undefined4 *)(puVar2 + 0x30) = 0;
    *(undefined4 *)(puVar2 + 0x34) = 0;
    *(undefined **)(puVar2 + 0x48) = &UNK_007491c0;
    *(undefined4 *)(puVar2 + 0x54) = 0x3f800000;
    *(undefined4 *)(puVar2 + 0x58) = 0x3f800000;
    puVar1 = puVar2 + 100;
    *(undefined2 *)(puVar2 + 0x50) = 0;
    *(undefined2 *)(puVar2 + 0x52) = 0;
    *(undefined4 *)(puVar2 + 0x5c) = 0;
    *(undefined4 *)(puVar2 + 0x4c) = 3;
    *(undefined4 *)(puVar2 + 0x44) = 0;
    *(undefined4 *)(puVar2 + 0x40) = 0;
    *(undefined4 *)(puVar2 + 0x3c) = 0;
    *(undefined4 *)(puVar2 + 0x6c) = 0;
    *(undefined1 **)puVar1 = puVar1;
    *(undefined1 **)(puVar2 + 0x68) = puVar1;
    func_0x008086e0(0x8d624c,puVar2);
    return puVar2;
  }
  return (undefined1 *)0x0;
}


