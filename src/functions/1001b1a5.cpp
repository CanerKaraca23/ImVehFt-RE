#include <cstdint>

extern "C" int* __cdecl __errno();
extern "C" void __stdcall FUN_1001189f();

extern "C" std::uint32_t DAT_1003a6bc;

extern "C" std::uint32_t __cdecl FUN_1001b1a5(std::uint32_t* param_1)
{
    int* piVar1;

    if (param_1 == nullptr) {
        piVar1 = __errno();
        *piVar1 = 0x16;
        FUN_1001189f();
        return 0x16;
    }

    *param_1 = DAT_1003a6bc;
    return 0;
}