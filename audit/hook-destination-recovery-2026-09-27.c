
/* target 0x10004B10; hook sites 0x0053BFCC:0XE8 */

void HOOK_DEST_10004B10(void)

{
  uRam1003a6c6 = 0;
  if (sRam10037508 == -1) {
    sRam10037508 = sRam00c81320;
    return;
  }
  if (sRam10037508 != sRam00c81320) {
    if ((((sRam00c81320 == 8) || (sRam00c81320 == 9)) || (sRam00c81320 == 0x10)) ||
       (sRam00c81320 == 0x13)) {
      if (((sRam10037508 != 8) && (sRam10037508 != 9)) &&
         ((sRam10037508 != 0x10 && (sRam10037508 != 0x13)))) {
        uRam1003a6c6 = 1;
      }
    }
    else if (((sRam10037508 == 8) || (sRam10037508 == 9)) ||
            ((sRam10037508 == 0x10 || (sRam10037508 == 0x13)))) {
      uRam1003a6c6 = 2;
      sRam10037508 = sRam00c81320;
      return;
    }
  }
  sRam10037508 = sRam00c81320;
  return;
}



/* target 0x10008780; hook sites 0x005D5BC7:0XE9 */

void HOOK_DEST_10008780(void)

{
  uRam1003c200 = (*(code *)0x7cf9b0)(0x1003bc80);
  (*(code *)0x8042c0)(uRam1003c200,4,0x1003bbb8,0x1003c204,0x1003bc28,0x1003bc10);
  uRam1003bd94 = (*(code *)0x7fb230)(uRam1003bbb8,uRam1003c204,uRam1003bc28,uRam1003bc10);
  (*(code *)0x804290)(uRam1003bd94,uRam1003c200);
  (*(code *)0x802740)(uRam1003c200);
  uRam1003c1f0 = (*(code *)0x7f37c0)(uRam1003bd94);
  (*(code *)0x5d5bea)();
  return;
}



/* target 0x10008830; hook sites 0x005D5C1E:0XE9 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void HOOK_DEST_10008830(void)

{
  int in_EAX;
  int unaff_EBP;
  
  iRam1003bc18 = unaff_EBP;
  iRam1003c1f0 = in_EAX;
  if (iRam1003c1f4 == 1) {
    *(undefined4 *)(in_EAX + 0x10) = _UNK_1002496c;
    *(undefined4 *)(in_EAX + 0x14) = _UNK_10024970;
    *(undefined4 *)(in_EAX + 0x18) = _UNK_10024974;
    *(undefined4 *)(in_EAX + 0x1c) = _UNK_10024978;
    *(undefined1 *)(in_EAX + 0x20) = UNK_1002497c;
    *(int *)(iRam1003bc18 * 4 + 0x1003c1a8) = iRam1003c1f0;
  }
  else if (iRam1003c1f4 == 2) {
    *(undefined4 *)(in_EAX + 0x10) = _UNK_10024980;
    *(undefined4 *)(in_EAX + 0x14) = _UNK_10024984;
    *(undefined4 *)(in_EAX + 0x18) = _UNK_10024988;
    *(undefined4 *)(in_EAX + 0x1c) = _UNK_1002498c;
    *(undefined1 *)(in_EAX + 0x20) = UNK_10024990;
    *(int *)(iRam1003bc18 * 4 + 0x1003bbc0) = iRam1003c1f0;
  }
  else if (iRam1003c1f4 == 3) {
    *(undefined4 *)(in_EAX + 0x10) = _UNK_10024994;
    *(undefined4 *)(in_EAX + 0x14) = _UNK_10024998;
    *(undefined4 *)(in_EAX + 0x18) = _UNK_1002499c;
    *(undefined4 *)(in_EAX + 0x1c) = _UNK_100249a0;
    *(undefined1 *)(in_EAX + 0x20) = UNK_100249a4;
    *(int *)(iRam1003bc18 * 4 + 0x1003bc30) = iRam1003c1f0;
  }
  (*(code *)0x5d5c37)();
  return;
}



/* target 0x10008940; hook sites 0x005D5AD1:0XE9 */

void HOOK_DEST_10008940(void)

{
  for (iRam1003bc18 = 0; iRam1003bc18 < 0x10; iRam1003bc18 = iRam1003bc18 + 1) {
    if (*(int *)(iRam1003bc18 * 4 + 0x1003c1a8) != 0) {
      (*(code *)0x7f3820)(*(undefined4 *)(iRam1003bc18 * 4 + 0x1003c1a8));
    }
    if (*(int *)(iRam1003bc18 * 4 + 0x1003bbc0) != 0) {
      (*(code *)0x7f3820)(*(undefined4 *)(iRam1003bc18 * 4 + 0x1003bbc0));
    }
    if (*(int *)(iRam1003bc18 * 4 + 0x1003bc30) != 0) {
      (*(code *)0x7f3820)(*(undefined4 *)(iRam1003bc18 * 4 + 0x1003bc30));
    }
    if (*(int *)(iRam1003bc18 * 4 + 0x1003c208) != 0) {
      func_0x10001730();
    }
    *(undefined4 *)(iRam1003bc18 * 4 + 0x1003c1a8) = 0;
    *(undefined4 *)(iRam1003bc18 * 4 + 0x1003bbc0) = 0;
    *(undefined4 *)(iRam1003bc18 * 4 + 0x1003bc30) = 0;
    *(undefined4 *)(iRam1003bc18 * 4 + 0x1003c208) = 0;
  }
  if (iRam1003bd90 != 0) {
    func_0x10001730();
  }
  if (iRam1003bbb4 != 0) {
    func_0x10001730();
  }
  if (iRam1003bc7c != 0) {
    func_0x10001730();
  }
  if (iRam1003bc1c != 0) {
    func_0x10001730();
  }
  if (iRam1003bc08 != 0) {
    func_0x10001730();
  }
  if (iRam1003c1f8 != 0) {
    func_0x10001730();
  }
  iRam1003bd90 = 0;
  iRam1003bbb4 = 0;
  iRam1003bc7c = 0;
  iRam1003bc1c = 0;
  iRam1003bc08 = 0;
  iRam1003c1f8 = 0;
  if (iRam1003bd9c != 0) {
    (*(code *)0x7f3820)(iRam1003bd9c);
  }
  if (iRam1003bda0 != 0) {
    (*(code *)0x7f3820)(iRam1003bda0);
  }
  if (iRam1003bda4 != 0) {
    (*(code *)0x7f3820)(iRam1003bda4);
  }
  iRam1003bd9c = 0;
  iRam1003bda0 = 0;
  iRam1003bda4 = 0;
  (*(code *)0x5d5af6)();
  return;
}



/* target 0x10007F90; hook sites 0x006E198E:0XE9 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void HOOK_DEST_10007F90(void)

{
  int unaff_ESI;
  
  iRam1003bd88 = unaff_ESI;
  iRam1003bd84 = func_0x10008e00();
  if ((((float)_UNK_10024f88 < *(float *)(iRam1003bd88 + 0x4a0)) &&
      (*(int *)(iRam1003bd88 + 0x460) != 0)) &&
     (*(char *)(*(int *)(iRam1003bd84 + 0x28) + 0x325) == '\0')) {
    (*(code *)0x6e19a1)();
    return;
  }
  (*(code *)0x6e19c8)();
  return;
}



/* target 0x10007F50; hook sites 0x006E18DA:0XE9 */

void HOOK_DEST_10007F50(void)

{
  (*(code *)0x6e18eb)();
  return;
}



/* target 0x10007F70; hook sites 0x006E1A2D:0XE9 */

void HOOK_DEST_10007F70(void)

{
  byte unaff_BH;
  
  if ((unaff_BH & 0x41) == 0) {
    func_0x10003200();
  }
  (*(code *)0x6e1a32)();
  return;
}



/* target 0x10003E40; hook sites 0x006FDED6:0XE8 */

void HOOK_DEST_10003E40(void)

{
  (*(code *)0x7fb230)(0x100,0x40,0x20,0x504);
  return;
}



/* target 0x10003030; hook sites 0x006AB350:0XE9 */

void HOOK_DEST_10003030(void)

{
  int iVar1;
  int unaff_ESI;
  
  iRam1003bc2c = unaff_ESI;
  iVar1 = func_0x10004a60((int)*(short *)(unaff_ESI + 0x22));
  if (iVar1 != 0) {
    (*(code *)0x6abc71)();
    return;
  }
  (*(code *)0x6ab35a)();
  return;
}



/* target 0x10003060; hook sites 0x006F3AED:0XE8 */

undefined8 __fastcall HOOK_DEST_10003060(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  int unaff_ESI;
  
  iRam1003bc2c = unaff_ESI;
  if (*(int *)(unaff_ESI + 0x594) != 0xb) {
    *(byte *)(unaff_ESI + 0x428) = *(byte *)(unaff_ESI + 0x428) & 0xef;
  }
  return CONCAT44(param_2,in_EAX);
}



/* target 0x10003080; hook sites 0x006F3973:0XE8 */

undefined8 __fastcall HOOK_DEST_10003080(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  int unaff_ESI;
  
  iRam1003bc2c = unaff_ESI;
  if (*(int *)(unaff_ESI + 0x594) != 0xb) {
    *(byte *)(unaff_ESI + 0x4a8) = *(byte *)(unaff_ESI + 0x4a8) & 0xe7;
    *(byte *)(iRam1003bc2c + 0x428) = *(byte *)(iRam1003bc2c + 0x428) & 0xbf;
  }
  return CONCAT44(param_2,in_EAX);
}



/* target 0x100031E0; hook sites 0x006E27E6:0XE9 */

void HOOK_DEST_100031E0(void)

{
  undefined4 unaff_ESI;
  
  uRam1003bc14 = unaff_ESI;
  func_0x10003130();
  (*(code *)0x6e27eb)();
  return;
}


