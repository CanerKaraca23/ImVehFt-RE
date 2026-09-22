#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" unsigned char DAT_10029d30;

extern "C" int __stdcall FUN_10017ec8(void);
extern "C" int __cdecl _raise(int _Signal);
extern "C" void __cdecl __call_reportfault(
    int nDbgHookCode,
    unsigned long dwExceptionCode,
    unsigned long dwExceptionFlags);
extern "C" [[noreturn]] void __cdecl __exit(int _Code);

extern "C" [[noreturn]] void __cdecl _abort(void)
{
    int iVar1 = FUN_10017ec8();

    if (iVar1 != 0)
    {
        _raise(0x16);
    }

    if ((DAT_10029d30 & 2) != 0)
    {
        __call_reportfault(3, 0x40000015UL, 1UL);
    }

    __exit(3);
}