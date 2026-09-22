#include <cstdint>

extern "C" void __cdecl ___mtold12(
    char* param_1,
    int param_2,
    std::uint32_t* param_3)
{
    std::uint32_t uVar7 = 0;
    std::int16_t local_8 = 0x404E;
    std::uint32_t* puVar4 = param_3;

    param_3[0] = 0;
    param_3[1] = 0;
    param_3[2] = 0;

    if (param_2 != 0)
    {
        param_3 = nullptr;

        do
        {
            const std::uint32_t uVar9 = puVar4[0];
            const std::uint32_t uVar8 = puVar4[1];
            const std::uint32_t uVar1 = puVar4[2];

            bool carry = false;

            const std::uint32_t uVar5 =
                (uVar7 * 2U | uVar9 >> 31) * 2U |
                (uVar9 & 0x7FFFFFFFU) >> 30;

            const std::uint32_t shifted = uVar9 * 4U;

            uVar7 =
                ((static_cast<std::uint32_t>(
                      reinterpret_cast<std::uintptr_t>(param_3)) *
                  2U) |
                 (uVar7 >> 31)) *
                    2U |
                ((uVar7 & 0x7FFFFFFFU) >> 30);

            std::uint32_t low = uVar9 + shifted;

            puVar4[0] = shifted;
            puVar4[1] = uVar5;
            puVar4[2] = uVar7;

            if ((low < shifted) || (low < uVar9))
                carry = true;

            puVar4[0] = low;

            std::uint32_t middle = uVar5;

            if (carry)
            {
                carry = false;
                middle = uVar5 + 1U;

                if ((middle < uVar5) || (middle == 0))
                    carry = true;

                puVar4[1] = middle;

                if (carry)
                {
                    uVar7 = uVar7 + 1U;
                    puVar4[2] = uVar7;
                }
            }

            const std::uint32_t previous_middle = middle;

            carry = false;
            middle = previous_middle + uVar8;

            if ((middle < previous_middle) || (middle < uVar8))
                carry = true;

            puVar4[1] = middle;

            if (carry)
            {
                uVar7 = uVar7 + 1U;
                puVar4[2] = uVar7;
            }

            param_3 = reinterpret_cast<std::uint32_t*>(
                ((uVar7 + uVar1) * 2U) | (middle >> 31));

            const std::uint32_t doubled_low = low * 2U;
            const std::uint32_t doubled_middle =
                middle * 2U | (low >> 31);

            puVar4[2] = static_cast<std::uint32_t>(
                reinterpret_cast<std::uintptr_t>(param_3));
            puVar4[0] = doubled_low;
            puVar4[1] = doubled_middle;

            const std::uint32_t digit = static_cast<std::uint32_t>(
                static_cast<std::int32_t>(
                    static_cast<signed char>(*param_1)));

            uVar7 = doubled_low + digit;
            carry = false;

            if ((uVar7 < doubled_low) || (uVar7 < digit))
                carry = true;

            puVar4[0] = uVar7;
            uVar7 = doubled_middle;

            if (carry)
            {
                uVar7 = uVar7 + 1U;
                carry = false;

                if ((uVar7 < doubled_middle) || (uVar7 == 0))
                    carry = true;

                puVar4[1] = uVar7;

                if (carry)
                {
                    param_3 = reinterpret_cast<std::uint32_t*>(
                        (static_cast<std::uint32_t>(
                             reinterpret_cast<std::uintptr_t>(param_3))) +
                        1U);
                    puVar4[2] = static_cast<std::uint32_t>(
                        reinterpret_cast<std::uintptr_t>(param_3));
                }
            }

            param_2 = param_2 - 1;
            param_1 = param_1 + 1;

            puVar4[1] = uVar7;
            puVar4[2] = static_cast<std::uint32_t>(
                reinterpret_cast<std::uintptr_t>(param_3));
        }
        while (param_2 != 0);
    }

    if (puVar4[2] == 0)
    {
        uVar7 = puVar4[1];

        std::uint32_t upper;
        do
        {
            local_8 = static_cast<std::int16_t>(local_8 - 0x10);

            upper = uVar7 >> 16;
            uVar7 = (uVar7 << 16) | (puVar4[0] >> 16);

            puVar4[1] = uVar7;
            puVar4[0] = puVar4[0] << 16;
        }
        while (upper == 0);

        puVar4[2] = upper;
    }

    uVar7 = puVar4[2];

    if ((uVar7 & 0x8000U) == 0)
    {
        std::uint32_t middle = puVar4[1];
        std::uint32_t shifted_high;

        do
        {
            local_8 = static_cast<std::int16_t>(local_8 - 1);

            shifted_high = uVar7 * 2U;
            uVar7 = shifted_high | (middle >> 31);
            middle = middle * 2U | (puVar4[0] >> 31);

            puVar4[0] = puVar4[0] * 2U;
            puVar4[1] = middle;
            puVar4[2] = uVar7;
        }
        while ((shifted_high & 0x8000U) == 0);
    }

    *reinterpret_cast<std::int16_t*>(
        reinterpret_cast<std::uint8_t*>(puVar4) + 10) = local_8;
}