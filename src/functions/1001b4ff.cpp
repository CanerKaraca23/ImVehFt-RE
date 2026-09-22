#include <cstdint>

extern "C" std::uint32_t __fastcall __fload_withFB(void* this_ptr, int* value);

extern "C" __declspec(naked) std::uint32_t FUN_1001b4ff(void)
{
    __asm {
        lea edx, [esp + 4]
        call __fload_withFB
    }
}
