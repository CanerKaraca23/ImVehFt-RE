#include <cstdint>

extern std::uint32_t DAT_1003c328;
extern std::uint32_t* DAT_1003c36c;
extern std::uint32_t* DAT_1003c370;
extern std::uint32_t* DAT_1003c374;
extern std::uint32_t* DAT_1003c390;

extern "C" void __stdcall FUN_1000cfe0();

void __stdcall FUN_1000a680(std::uint32_t param_1)
{
    if (DAT_1003c390 == nullptr)
    {
        DAT_1003c390 = &DAT_1003c328;

        reinterpret_cast<void (__cdecl*)(
            std::uint32_t,
            std::uint32_t,
            std::uint32_t,
            std::uint32_t,
            std::uint32_t
        )>(
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(DAT_1003c328) + 4u
            )
        )(0, 0, 0, 0, 0);
    }

    auto* param_address = &param_1;

    if ((param_address < DAT_1003c370) &&
        (DAT_1003c36c <= param_address))
    {
        const std::int32_t iVar1 =
            static_cast<std::int32_t>(
                reinterpret_cast<std::uintptr_t>(param_address)
            ) -
            static_cast<std::int32_t>(
                reinterpret_cast<std::uintptr_t>(DAT_1003c36c)
            );

        if (DAT_1003c370 == DAT_1003c374)
        {
            FUN_1000cfe0();
        }

        if (DAT_1003c370 != nullptr)
        {
            *DAT_1003c370 = DAT_1003c36c[iVar1 >> 2];
        }

        DAT_1003c370 = DAT_1003c370 + 1;
        return;
    }

    if (DAT_1003c370 == DAT_1003c374)
    {
        FUN_1000cfe0();
    }

    if (DAT_1003c370 != nullptr)
    {
        *DAT_1003c370 = param_1;
    }

    DAT_1003c370 = DAT_1003c370 + 1;
}