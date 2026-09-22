#include <cstdint>

extern "C" void __cdecl FUN_1001ca18(std::uint32_t low_word, std::uint32_t high_word);
extern "C" void __cdecl FUN_1001b5bd(std::uint32_t low_word, std::uint32_t high_word);

extern "C" __declspec(naked) void __stdcall FUN_1001b5a0(void)
{
    __asm {
        sub esp, 0ch
        fst qword ptr [esp]
        call FUN_1001ca18
        call FUN_1001b5bd
        add esp, 0ch
        ret
    }
}