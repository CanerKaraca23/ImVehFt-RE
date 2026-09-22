#include <cstdint>

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "FUN_100073f0 requires the MSVC x86 target"
#endif

extern float DAT_10024EB0;

extern "C" long double __fastcall FUN_1001b380(void*);
extern "C" long double __fastcall FUN_1001b4b0(void*);

using UnknownFunction_00707390 = void (__cdecl*)(
    std::uint32_t,
    std::uint32_t,
    std::uint32_t,
    float,
    float,
    float,
    float,
    std::uint32_t,
    std::uint32_t,
    void*);

extern "C" void __fastcall FUN_100073f0(
    void* param_1,
    std::uint32_t param_2,
    std::uint32_t param_3,
    float param_4,
    float param_5,
    std::uint32_t param_6,
    std::uint32_t param_7,
    std::uint32_t param_8)
{
    (void)param_6;
    (void)param_7;

    const std::uint32_t uVar5 = 1;

    const long double result_1001B380_0 = FUN_1001b380(param_1);
    void* extraout_ECX;
    __asm mov extraout_ECX, ecx

    const float fVar4 =
        static_cast<float>(result_1001B380_0) *
        param_4 *
        static_cast<float>(DAT_10024EB0);

    const long double result_1001B4B0_0 = FUN_1001b4b0(extraout_ECX);
    void* extraout_ECX_00;
    __asm mov extraout_ECX_00, ecx

    const float fVar3 =
        static_cast<float>(result_1001B4B0_0) *
        param_4 *
        static_cast<float>(DAT_10024EB0);

    const long double result_1001B380_1 = FUN_1001b380(extraout_ECX_00);
    void* extraout_ECX_01;
    __asm mov extraout_ECX_01, ecx

    const float fVar2 =
        static_cast<float>(result_1001B380_1) *
        param_5 *
        static_cast<float>(DAT_10024EB0);

    const long double result_1001B4B0_1 = FUN_1001b4b0(extraout_ECX_01);

    const float fVar1 =
        static_cast<float>(result_1001B4B0_1) *
        param_5 *
        static_cast<float>(DAT_10024EB0);

    reinterpret_cast<UnknownFunction_00707390>(0x00707390)(
        2,
        param_8,
        param_3,
        fVar1,
        fVar2,
        fVar3,
        fVar4,
        uVar5,
        param_2,
        param_1);
}