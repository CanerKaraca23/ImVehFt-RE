/* Full-analysis function mapping; decompilation is not original source. */

/* function 0072f420 FUN_0072f420 */

void FUN_0072f420(size_t param_1)

{
  _malloc(param_1);
  return;
}



/* function 0072f430 _free */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */

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



/* function 0072f440 FUN_0072f440 */

void FUN_0072f440(undefined4 param_1,undefined4 param_2)

{
  FUN_00824269(param_1,param_2);
  return;
}



/* function 0072f460 FUN_0072f460 */

void FUN_0072f460(size_t param_1,size_t param_2)

{
  _calloc(param_1,param_2);
  return;
}


