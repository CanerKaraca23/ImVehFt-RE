#include <cstddef>

using PVOID = void*;

extern "C" PVOID __stdcall EncodePointer(PVOID pointer);

extern "C" void __stdcall FUN_10014c40()
{
    (void)EncodePointer(nullptr);
}