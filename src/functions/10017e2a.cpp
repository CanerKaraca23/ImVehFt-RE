#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void* DAT_1003a318;

extern "C" void* __stdcall DecodePointer(void* Ptr);
extern "C" [[noreturn]] void __cdecl terminate(void);

extern "C" void __cdecl _inconsistency(void)
{
    using Handler = void (__cdecl*)();

    Handler handler = reinterpret_cast<Handler>(
        DecodePointer(DAT_1003a318));

    if (handler != nullptr) {
        (*handler)();
    }

    terminate();
}