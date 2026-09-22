#include <cstdint>

using abi32_uint = std::uint32_t;
using abi32_ptr = abi32_uint*;

abi32_ptr __cdecl FUN_10016846(abi32_ptr param_1)
{
    abi32_uint in_EAX;
    abi32_uint uVar1;
    abi32_uint uVar3;
    abi32_uint uVar4;
    abi32_uint uVar7;
    abi32_ptr puVar5;
    char cVar2;
    char cVar6;

#if defined(_MSC_VER) && defined(_M_IX86)
    __asm mov in_EAX, eax
#elif defined(__GNUC__) && defined(__i386__)
    asm volatile("movl %%eax, %0" : "=r"(in_EAX));
#else
#error "FUN_10016846 requires access to the incoming 32-bit EAX register"
#endif

    cVar6 = static_cast<char>(in_EAX);

    while ((reinterpret_cast<std::uintptr_t>(param_1) & 3u) != 0)
    {
        uVar7 = *param_1;

        if (static_cast<char>(uVar7) == cVar6)
            return param_1;

        param_1 = reinterpret_cast<abi32_ptr>(
            reinterpret_cast<std::uintptr_t>(param_1) + 1u);

        if (static_cast<char>(uVar7) == '\0')
            return nullptr;
    }

    uVar7 = in_EAX | (in_EAX << 8);

    for (;;)
    {
        for (;;)
        {
            uVar1 = *param_1;
            uVar4 = uVar1 ^ ((uVar7 << 16) | uVar7);
            uVar3 = uVar1 ^ 0xffffffffu ^ (uVar1 + 0x7efefeffu);
            puVar5 = param_1 + 1;

            if (((uVar4 ^ 0xffffffffu ^
                  (uVar4 + 0x7efefeffu)) & 0x81010100u) != 0)
                break;

            param_1 = puVar5;

            if ((uVar3 & 0x81010100u) != 0)
            {
                if ((uVar3 & 0x01010100u) != 0)
                    return nullptr;

                if (((uVar1 + 0x7efefeffu) & 0x80000000u) == 0)
                    return nullptr;
            }
        }

        uVar1 = *param_1;

        if (static_cast<char>(uVar1) == cVar6)
            return param_1;

        if (static_cast<char>(uVar1) == '\0')
            return nullptr;

        cVar2 = static_cast<char>(uVar1 >> 8);

        if (cVar2 == cVar6)
            return reinterpret_cast<abi32_ptr>(
                reinterpret_cast<std::uintptr_t>(param_1) + 1u);

        if (cVar2 == '\0')
            return nullptr;

        cVar2 = static_cast<char>(uVar1 >> 16);

        if (cVar2 == cVar6)
            return reinterpret_cast<abi32_ptr>(
                reinterpret_cast<std::uintptr_t>(param_1) + 2u);

        if (cVar2 == '\0')
            break;

        cVar2 = static_cast<char>(uVar1 >> 24);

        if (cVar2 == cVar6)
            return reinterpret_cast<abi32_ptr>(
                reinterpret_cast<std::uintptr_t>(param_1) + 3u);

        param_1 = puVar5;

        if (cVar2 == '\0')
            return nullptr;
    }

    return nullptr;
}