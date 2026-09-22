#include <cstdint>

extern "C" __declspec(naked)
std::uint32_t __fastcall __NLG_Notify1(std::uint32_t )
{
    __asm
    {
        mov dword ptr ds:0x10029E98, ecx
        mov dword ptr ds:0x10029E94, eax
        mov dword ptr ds:0x10029E9C, ebp
        ret
    }
}