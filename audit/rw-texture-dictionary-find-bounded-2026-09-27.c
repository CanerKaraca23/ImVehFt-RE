/* Temporary bounded Ghidra decompilation; not original source. */

/* entry 0x007F39F0; bounded CFG instructions=54; body bytes=115 */

undefined4 * BOUNDED_007F39F0(int param_1,char *param_2)

{
  undefined4 *puVar1;
  char cVar2;
  char cVar3;
  char *pcVar4;
  char *pcVar5;
  
  puVar1 = *(undefined4 **)(param_1 + 8);
  do {
    if (puVar1 == (undefined4 *)(param_1 + 8)) {
      return (undefined4 *)0x0;
    }
    pcVar4 = (char *)(puVar1 + 2);
    if (pcVar4 != (char *)0x0) {
      cVar2 = *pcVar4;
      for (pcVar5 = param_2; (cVar2 != '\0' && (cVar3 = *pcVar5, cVar3 != '\0'));
          pcVar5 = pcVar5 + 1) {
        if (('`' < cVar2) && (cVar2 < '{')) {
          cVar2 = cVar2 + -0x20;
        }
        if (('`' < cVar3) && (cVar3 < '{')) {
          cVar3 = cVar3 + -0x20;
        }
        if (cVar2 != cVar3) goto LAB_007f3a52;
        cVar2 = pcVar4[1];
        pcVar4 = pcVar4 + 1;
      }
      if (*pcVar4 == *pcVar5) {
        return puVar1 + -2;
      }
    }
LAB_007f3a52:
    puVar1 = (undefined4 *)*puVar1;
  } while( true );
}


