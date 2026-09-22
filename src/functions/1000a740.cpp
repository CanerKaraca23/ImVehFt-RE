#include <cstdint>

extern std::uint32_t* DAT_1003c390;
extern std::uint32_t  DAT_1003c328;
extern std::uint32_t* DAT_1003c37c;
extern std::uint32_t* DAT_1003c380;
extern std::uint32_t* DAT_1003c384;

extern "C" void __stdcall FUN_1000cfe0();

void __stdcall FUN_1000a740(std::uint32_t param_1)
{
    if (DAT_1003c390 == nullptr)
    {
        DAT_1003c390 = &DAT_1003c328;

        reinterpret_cast<void(__cdecl*)(int, int, int, int, int)>(
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(DAT_1003c328) + 4u
            )
        )(0, 0, 0, 0, 0);
    }

    auto* param_address = &param_1;

    if ((param_address < DAT_1003c380) &&
        (DAT_1003c37c <= param_address))
    {
        const std::int32_t iVar1 =
            static_cast<std::int32_t>(
                reinterpret_cast<std::uintptr_t>(param_address) -
                reinterpret_cast<std::uintptr_t>(DAT_1003c37c)
            );

        if (DAT_1003c380 == DAT_1003c384)
        {
            FUN_1000cfe0();
        }

        if (DAT_1003c380 != nullptr)
        {
            *DAT_1003c380 = DAT_1003c37c[iVar1 >> 2];
        }

        DAT_1003c380 = DAT_1003c380 + 1;
        return;
    }

    if (DAT_1003c380 == DAT_1003c384)
    {
        FUN_1000cfe0();
    }

    if (DAT_1003c380 != nullptr)
    {
        *DAT_1003c380 = param_1;
    }

    DAT_1003c380 = DAT_1003c380 + 1;
}