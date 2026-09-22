#include <cstdint>

extern "C" __declspec(naked) void __cdecl FUN_100099e0(
    void*, void*, std::uint32_t)
{
    __asm
    {
        mov eax, dword ptr [esp + 8]
        mov ecx, dword ptr [eax]
        mov edx, dword ptr [esp + 4]
        call edx
        ret
    }
}