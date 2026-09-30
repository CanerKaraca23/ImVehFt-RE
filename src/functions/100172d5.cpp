#include <cstdint>

extern "C" std::uintptr_t DAT_10029490;
extern "C" [[noreturn]] void __cdecl ___report_gsfailure();

extern "C" __declspec(naked) void __fastcall __security_check_cookie(std::uintptr_t)
{
    __asm
    {
        cmp ecx, dword ptr [DAT_10029490]
        jne security_check_cookie_failure
        rep ret

    security_check_cookie_failure:
        jmp ___report_gsfailure
    }
}
