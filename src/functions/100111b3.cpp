#include <cstdint>

extern "C" void ___security_init_cookie();

extern "C" int __fastcall ___DllMainCRTStartup(
    std::int32_t param_1,
    std::int32_t param_2,
    std::uint32_t param_3);

__declspec(naked) void __stdcall entry(
    std::uint32_t,
    std::int32_t,
    std::int32_t)
{
    __asm {
        mov     edi, edi
        push    ebp
        mov     ebp, esp
        cmp     dword ptr [ebp + 0Ch], 1
        jne     skip_cookie_init
        call    ___security_init_cookie
    skip_cookie_init:
        push    dword ptr [ebp + 8]
        mov     ecx, dword ptr [ebp + 10h]
        mov     edx, dword ptr [ebp + 0Ch]
        call    ___DllMainCRTStartup
        pop     ecx
        pop     ebp
        ret     0Ch
    }
}
