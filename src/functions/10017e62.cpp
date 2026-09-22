#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void* DAT_1003a318;

extern "C" void* __stdcall EncodePointer(void* Ptr);
extern "C" [[noreturn]] void __cdecl terminate(void);

extern "C" void __stdcall FUN_10017e62(void)
{
    DAT_1003a318 = EncodePointer(
        reinterpret_cast<void*>(terminate));
}