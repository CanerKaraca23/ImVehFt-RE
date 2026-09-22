#include <cstdint>

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "FUN_1001cb20 requires the MSVC x86 x87 ABI."
#endif

extern "C" void __cdecl __87except(
    int param_2,
    int* local_24,
    std::uint16_t* param_3);

long double __fastcall FUN_1001cb20(
    std::uint32_t param_1,
    int param_2,
    std::uint16_t param_3,
    std::uint32_t param_4,
    std::uint32_t param_5,
    std::uint32_t param_6,
    std::uint32_t param_7,
    std::uint32_t param_8)
{
    int local_24;
    std::uint32_t uStack_20;
    std::uint32_t uStack_1c;
    std::uint32_t uStack_18;
    std::uint32_t local_14;
    std::uint32_t local_10;
    double dStack_c;

    (void)param_4;

    local_14 = param_7;
    local_10 = param_8;

    __asm
    {
        fst dStack_c
    }

    uStack_1c = param_5;
    uStack_18 = param_6;
    uStack_20 = param_1;

    __87except(param_2, &local_24, &param_3);

    return static_cast<long double>(dStack_c);
}