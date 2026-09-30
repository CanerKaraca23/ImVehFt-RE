using PVOID = void*;
struct _EXCEPTION_RECORD;
using PEXCEPTION_RECORD = _EXCEPTION_RECORD*;

extern "C" void __stdcall ImVehFt_Recovered_RtlUnwind(
    PVOID,
    PVOID,
    PEXCEPTION_RECORD,
    PVOID);

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "_EH4_GlobalUnwind2 requires the MSVC x86 calling environment"
#endif

#pragma warning(disable: 4733)
extern "C" __declspec(naked) void __fastcall _EH4_GlobalUnwind2(
    PVOID,
    PEXCEPTION_RECORD)
{
    __asm
    {
        push ebp
        mov ebp, esp
        push ebx
        push esi
        push edi
        push 0
        push edx
        push offset unwind_continuation
        push ecx
        call ImVehFt_Recovered_RtlUnwind

    unwind_continuation:
        pop edi
        pop esi
        pop ebx
        pop ebp
        ret
    }
}
