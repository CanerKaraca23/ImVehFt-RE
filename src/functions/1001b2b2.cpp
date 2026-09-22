#include <cstdint>

using PVOID = void*;

struct _EXCEPTION_RECORD;
using PEXCEPTION_RECORD = _EXCEPTION_RECORD*;

// The original function is an unresolved indirect jump thunk.
// The indirect target/IAT slot could not be recovered from the supplied evidence.
extern "C" void* const DAT_RtlUnwind_IndirectTarget;

extern "C" __declspec(naked) void __stdcall RtlUnwind(
    PVOID ,
    PVOID ,
    PEXCEPTION_RECORD ,
    PVOID )
{
    __asm
    {
        jmp dword ptr [DAT_RtlUnwind_IndirectTarget]
    }
}