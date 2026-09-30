using PVOID = void*;
struct _EXCEPTION_RECORD;
using PEXCEPTION_RECORD = _EXCEPTION_RECORD*;

extern "C" void __stdcall ImVehFt_Recovered_RtlUnwind(
    PVOID,
    PVOID,
    PEXCEPTION_RECORD,
    PVOID);

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "__global_unwind2 requires the MSVC x86 calling environment"
#endif

#pragma warning(disable: 4733)
extern "C" __declspec(naked) void __cdecl __global_unwind2(PVOID)
{
    __asm
    {
        push ebp
        mov ebp, esp
        push ebx
        push esi
        push edi
        push ebp
        push 0
        push 0
        push offset unwind_continuation
        push dword ptr [ebp + 8]
        call ImVehFt_Recovered_RtlUnwind

    unwind_continuation:
        pop ebp
        pop edi
        pop esi
        pop ebx
        mov esp, ebp
        pop ebp
        ret
    }
}
