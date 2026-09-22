#include <bit>
#include <cstdint>

extern "C" long double __cdecl __set_exp(
    std::uint64_t value,
    short exponent);

extern "C" void __cdecl FUN_10020775(
    std::uint32_t param_1,
    std::uint32_t param_2,
    int* param_3)
{
    std::uint16_t uVar1;
    bool bVar2;
    int iVar3;
    int extraout_EDX;

    const std::uint64_t value =
        (static_cast<std::uint64_t>(param_2) << 32) |
        static_cast<std::uint64_t>(param_1);

    if (std::bit_cast<double>(value) == 0.0)
    {
        iVar3 = 0;
    }
    else if (((param_2 & 0x7ff00000U) == 0U) &&
             (((param_2 & 0x000fffffU) != 0U) || (param_1 != 0U)))
    {
        if (0.0 <= std::bit_cast<double>(value))
        {
            bVar2 = false;
        }
        else
        {
            bVar2 = true;
        }

        while ((param_2 & 0x00100000U) == 0U)
        {
            iVar3 = static_cast<int>(param_2 << 1);
            param_2 = param_2 << 1;

            if ((param_1 & 0x80000000U) != 0U)
            {
                param_2 =
                    (param_2 & 0xffff0000U) |
                    static_cast<std::uint16_t>(param_2 | 1U);
            }

            param_1 = param_1 << 1;
        }

        uVar1 = static_cast<std::uint16_t>((param_2 >> 16) & 0xffefU);
        param_2 =
            (param_2 & 0x0000ffffU) |
            (static_cast<std::uint32_t>(uVar1) << 16);

        if (bVar2)
        {
            param_2 = param_2 | 0x80000000U;
        }

        const std::uint64_t normalized_value =
            (static_cast<std::uint64_t>(param_2) << 32) |
            static_cast<std::uint64_t>(param_1);

        (void)__set_exp(normalized_value, 0);

#if defined(_MSC_VER) && defined(_M_IX86)
        __asm
        {
            mov extraout_EDX, edx
        }
#else
#error "This reversal requires the target x86 ABI to capture EDX after __set_exp."
#endif

        iVar3 = extraout_EDX;
    }
    else
    {
        (void)__set_exp(value, 0);
        iVar3 = static_cast<int>(
            ((param_2 >> 20) & 0x7ffU) - 0x3feU);
    }

    *param_3 = iVar3;
}