#include <cstdint>

extern void** DAT_1003c3c0;
extern void* PTR_vftable_100377d0;

extern std::uint32_t* DAT_100377f8;
extern std::uint32_t* DAT_100377fc;
extern std::uint32_t* DAT_10037800;

struct __single_inheritance FUN_1000b6e0_this {
    void __thiscall FUN_1000b6e0(std::uint32_t param_1, int param_2, int param_3, int param_4, int param_5);
};

extern "C" void __stdcall FUN_1000cfe0();

void __stdcall FUN_1000b820(std::uint32_t param_1)
{
    std::int32_t iVar1;

    if (DAT_1003c3c0 == nullptr)
    {
        DAT_1003c3c0 =
            reinterpret_cast<void**>(&PTR_vftable_100377d0);

        using Initializer = decltype(&FUN_1000b6e0_this::FUN_1000b6e0);
static_assert(sizeof(Initializer) == sizeof(void*));
const Initializer initializer = *reinterpret_cast<Initializer*>(
    reinterpret_cast<std::uintptr_t>(PTR_vftable_100377d0) + 4u);
(reinterpret_cast<FUN_1000b6e0_this*>(DAT_1003c3c0)->*initializer)(

            0x53e4ffu,
            0,
            0,
            0,
            0);
    }

    const std::uintptr_t paramAddress =
        reinterpret_cast<std::uintptr_t>(&param_1);
    const std::uintptr_t beginAddress =
        reinterpret_cast<std::uintptr_t>(DAT_100377f8);
    const std::uintptr_t endAddress =
        reinterpret_cast<std::uintptr_t>(DAT_100377fc);

    if ((paramAddress < endAddress) &&
        (beginAddress <= paramAddress))
    {
        iVar1 = static_cast<std::int32_t>(
            paramAddress - beginAddress
        );

        if (DAT_100377fc == DAT_10037800)
        {
            FUN_1000cfe0();
        }

        if (DAT_100377fc != nullptr)
        {
            *DAT_100377fc = DAT_100377f8[iVar1 >> 2];
        }

        DAT_100377fc = DAT_100377fc + 1;
        return;
    }

    if (DAT_100377fc == DAT_10037800)
    {
        FUN_1000cfe0();
    }

    if (DAT_100377fc != nullptr)
    {
        *DAT_100377fc = param_1;
    }

    DAT_100377fc = DAT_100377fc + 1;
}