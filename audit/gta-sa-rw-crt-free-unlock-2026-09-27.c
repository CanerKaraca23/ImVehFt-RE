/* Full-analysis function mapping; decompilation is not original source. */

/* function 00824192 FUN_00824192 */

void FUN_00824192(void)

{
  FUN_0082ad12(4);
  return;
}



/* function 0082413f _free */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    _free
   
   Library: Visual Studio 2003 Release */

void __cdecl _free(void *_Memory)

{
  int iVar1;
  
  if (_Memory != (void *)0x0) {
    if (DAT_00c9c2f8 == 3) {
      __lock(4);
      iVar1 = ___sbh_find_block(_Memory);
      if (iVar1 != 0) {
        ___sbh_free_block(iVar1,_Memory);
      }
      FUN_00824192();
      if (iVar1 != 0) {
        return;
      }
    }
    HeapFree(DAT_00c9c2f4,0,_Memory);
  }
  return;
}


