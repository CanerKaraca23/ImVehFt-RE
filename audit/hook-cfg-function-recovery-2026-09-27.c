/* Temporary Ghidra CFG-bounded decompilation; not original source. */

/* target 0x10004B10; bounded CFG instructions=40; body bytes 146 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void HOOK_CFG_10004B10(void)

{
  DAT_1003a6c6 = 0;
  if (_DAT_10037508 == -1) {
    _DAT_10037508 = _DAT_00c81320;
    return;
  }
  if (_DAT_10037508 != _DAT_00c81320) {
    if ((((_DAT_00c81320 == 8) || (_DAT_00c81320 == 9)) || (_DAT_00c81320 == 0x10)) ||
       (_DAT_00c81320 == 0x13)) {
      if (((_DAT_10037508 != 8) && (_DAT_10037508 != 9)) &&
         ((_DAT_10037508 != 0x10 && (_DAT_10037508 != 0x13)))) {
        DAT_1003a6c6 = 1;
      }
    }
    else if (((_DAT_10037508 == 8) || (_DAT_10037508 == 9)) ||
            ((_DAT_10037508 == 0x10 || (_DAT_10037508 == 0x13)))) {
      DAT_1003a6c6 = 2;
      _DAT_10037508 = _DAT_00c81320;
      return;
    }
  }
  _DAT_10037508 = _DAT_00c81320;
  return;
}



/* target 0x10008780; bounded CFG instructions=50; body bytes 176 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void HOOK_CFG_10008780(void)

{
  _DAT_1003c200 = (*(code *)0x7cf9b0)(0x1003bc80);
  (*(code *)0x8042c0)(_DAT_1003c200,4,&DAT_1003bbb8,&DAT_1003c204,&DAT_1003bc28,&DAT_1003bc10);
  _DAT_1003bd94 = (*(code *)0x7fb230)(_DAT_1003bbb8,_DAT_1003c204,_DAT_1003bc28,_DAT_1003bc10);
  (*(code *)0x804290)(_DAT_1003bd94,_DAT_1003c200);
  (*(code *)0x802740)(_DAT_1003c200);
  _DAT_1003c1f0 = (*(code *)0x7f37c0)(_DAT_1003bd94);
  (*(code *)0x5d5bea)();
  return;
}



/* target 0x10008830; bounded CFG instructions=61; body bytes 271 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void HOOK_CFG_10008830(void)

{
  int in_EAX;
  int unaff_EBP;
  
  _DAT_1003bc18 = unaff_EBP;
  _DAT_1003c1f0 = in_EAX;
  if (_DAT_1003c1f4 == 1) {
    *(undefined4 *)(in_EAX + 0x10) = _DAT_1002496c;
    *(undefined4 *)(in_EAX + 0x14) = _DAT_10024970;
    *(undefined4 *)(in_EAX + 0x18) = _DAT_10024974;
    *(undefined4 *)(in_EAX + 0x1c) = _DAT_10024978;
    *(undefined1 *)(in_EAX + 0x20) = DAT_1002497c;
    *(int *)(_DAT_1003bc18 * 4 + 0x1003c1a8) = _DAT_1003c1f0;
  }
  else if (_DAT_1003c1f4 == 2) {
    *(undefined4 *)(in_EAX + 0x10) = _DAT_10024980;
    *(undefined4 *)(in_EAX + 0x14) = _DAT_10024984;
    *(undefined4 *)(in_EAX + 0x18) = _DAT_10024988;
    *(undefined4 *)(in_EAX + 0x1c) = _DAT_1002498c;
    *(undefined1 *)(in_EAX + 0x20) = DAT_10024990;
    *(int *)(_DAT_1003bc18 * 4 + 0x1003bbc0) = _DAT_1003c1f0;
  }
  else if (_DAT_1003c1f4 == 3) {
    *(undefined4 *)(in_EAX + 0x10) = _DAT_10024994;
    *(undefined4 *)(in_EAX + 0x14) = _DAT_10024998;
    *(undefined4 *)(in_EAX + 0x18) = _DAT_1002499c;
    *(undefined4 *)(in_EAX + 0x1c) = _DAT_100249a0;
    *(undefined1 *)(in_EAX + 0x20) = DAT_100249a4;
    *(int *)(_DAT_1003bc18 * 4 + 0x1003bc30) = _DAT_1003c1f0;
  }
  (*(code *)0x5d5c37)();
  return;
}



/* target 0x10008940; bounded CFG instructions=105; body bytes 555 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void HOOK_CFG_10008940(void)

{
  for (_DAT_1003bc18 = 0; _DAT_1003bc18 < 0x10; _DAT_1003bc18 = _DAT_1003bc18 + 1) {
    if (*(int *)(_DAT_1003bc18 * 4 + 0x1003c1a8) != 0) {
      (*(code *)0x7f3820)(*(undefined4 *)(_DAT_1003bc18 * 4 + 0x1003c1a8));
    }
    if (*(int *)(_DAT_1003bc18 * 4 + 0x1003bbc0) != 0) {
      (*(code *)0x7f3820)(*(undefined4 *)(_DAT_1003bc18 * 4 + 0x1003bbc0));
    }
    if (*(int *)(_DAT_1003bc18 * 4 + 0x1003bc30) != 0) {
      (*(code *)0x7f3820)(*(undefined4 *)(_DAT_1003bc18 * 4 + 0x1003bc30));
    }
    if (*(int *)(_DAT_1003bc18 * 4 + 0x1003c208) != 0) {
      func_0x10001730();
    }
    *(undefined4 *)(_DAT_1003bc18 * 4 + 0x1003c1a8) = 0;
    *(undefined4 *)(_DAT_1003bc18 * 4 + 0x1003bbc0) = 0;
    *(undefined4 *)(_DAT_1003bc18 * 4 + 0x1003bc30) = 0;
    *(undefined4 *)(_DAT_1003bc18 * 4 + 0x1003c208) = 0;
  }
  if (_DAT_1003bd90 != 0) {
    func_0x10001730();
  }
  if (_DAT_1003bbb4 != 0) {
    func_0x10001730();
  }
  if (_DAT_1003bc7c != 0) {
    func_0x10001730();
  }
  if (_DAT_1003bc1c != 0) {
    func_0x10001730();
  }
  if (_DAT_1003bc08 != 0) {
    func_0x10001730();
  }
  if (_DAT_1003c1f8 != 0) {
    func_0x10001730();
  }
  _DAT_1003bd90 = 0;
  _DAT_1003bbb4 = 0;
  _DAT_1003bc7c = 0;
  _DAT_1003bc1c = 0;
  _DAT_1003bc08 = 0;
  _DAT_1003c1f8 = 0;
  if (_DAT_1003bd9c != 0) {
    (*(code *)0x7f3820)(_DAT_1003bd9c);
  }
  if (_DAT_1003bda0 != 0) {
    (*(code *)0x7f3820)(_DAT_1003bda0);
  }
  if (_DAT_1003bda4 != 0) {
    (*(code *)0x7f3820)(_DAT_1003bda4);
  }
  _DAT_1003bd9c = 0;
  _DAT_1003bda0 = 0;
  _DAT_1003bda4 = 0;
  (*(code *)0x5d5af6)();
  return;
}



/* target 0x10007F90; bounded CFG instructions=25; body bytes 97 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void HOOK_CFG_10007F90(void)

{
  int unaff_ESI;
  
  _DAT_1003bd88 = unaff_ESI;
  _DAT_1003bd84 = func_0x10008e00();
  if ((((float)_DAT_10024f88 < *(float *)(_DAT_1003bd88 + 0x4a0)) &&
      (*(int *)(_DAT_1003bd88 + 0x460) != 0)) &&
     (*(char *)(*(int *)(_DAT_1003bd84 + 0x28) + 0x325) == '\0')) {
    (*(code *)0x6e19a1)();
    return;
  }
  (*(code *)0x6e19c8)();
  return;
}



/* target 0x10007F50; bounded CFG instructions=6; body bytes 20 */

void HOOK_CFG_10007F50(void)

{
  (*(code *)0x6e18eb)();
  return;
}



/* target 0x10007F70; bounded CFG instructions=5; body bytes 17 */

void HOOK_CFG_10007F70(void)

{
  byte unaff_BH;
  
  if ((unaff_BH & 0x41) == 0) {
    func_0x10003200();
  }
  (*(code *)0x6e1a32)();
  return;
}



/* target 0x10003E40; bounded CFG instructions=8; body bytes 25 */

void HOOK_CFG_10003E40(void)

{
  (*(code *)0x7fb230)(0x100,0x40,0x20,0x504);
  return;
}



/* target 0x10003030; bounded CFG instructions=13; body bytes 48 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void HOOK_CFG_10003030(void)

{
  int iVar1;
  int unaff_ESI;
  
  _DAT_1003bc2c = unaff_ESI;
  iVar1 = func_0x10004a60((int)*(short *)(unaff_ESI + 0x22));
  if (iVar1 != 0) {
    (*(code *)0x6abc71)();
    return;
  }
  (*(code *)0x6ab35a)();
  return;
}



/* target 0x10003060; bounded CFG instructions=8; body bytes 30 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall HOOK_CFG_10003060(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  int unaff_ESI;
  
  _DAT_1003bc2c = unaff_ESI;
  if (*(int *)(unaff_ESI + 0x594) != 0xb) {
    *(byte *)(unaff_ESI + 0x428) = *(byte *)(unaff_ESI + 0x428) & 0xef;
  }
  return CONCAT44(param_2,in_EAX);
}



/* target 0x10003080; bounded CFG instructions=10; body bytes 42 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall HOOK_CFG_10003080(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  int unaff_ESI;
  
  _DAT_1003bc2c = unaff_ESI;
  if (*(int *)(unaff_ESI + 0x594) != 0xb) {
    *(byte *)(unaff_ESI + 0x4a8) = *(byte *)(unaff_ESI + 0x4a8) & 0xe7;
    *(byte *)(_DAT_1003bc2c + 0x428) = *(byte *)(_DAT_1003bc2c + 0x428) & 0xbf;
  }
  return CONCAT44(param_2,in_EAX);
}



/* target 0x100031E0; bounded CFG instructions=6; body bytes 22 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void HOOK_CFG_100031E0(void)

{
  undefined4 unaff_ESI;
  
  _DAT_1003bc14 = unaff_ESI;
  func_0x10003130();
  (*(code *)0x6e27eb)();
  return;
}


