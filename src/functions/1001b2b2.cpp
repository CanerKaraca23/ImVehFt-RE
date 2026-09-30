#include <cstdint>

using PVOID = void*;

struct _EXCEPTION_RECORD;
using PEXCEPTION_RECORD = _EXCEPTION_RECORD*;

extern "C" void* _imp__RtlUnwind;
#pragma comment(linker, "/alternatename:__imp__RtlUnwind=__imp__RtlUnwind@16")

// Keep this recovered IAT thunk distinct from the SDK/import-library
// RtlUnwind symbol so both the thunk and KERNEL32 import can be linked.
extern "C" __declspec(naked) void __stdcall ImVehFt_Recovered_RtlUnwind(
    PVOID ,
    PVOID ,
    PEXCEPTION_RECORD ,
    PVOID )
{
    __asm
    {
        jmp dword ptr [_imp__RtlUnwind]
    }
}
