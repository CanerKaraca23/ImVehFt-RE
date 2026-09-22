#include <cstdint>

extern void* PTR_vftable_100377d0;
extern void** DAT_1003c3c0;

extern std::uint32_t* DAT_100377e8;
extern std::uint32_t* DAT_100377ec;
extern std::uint32_t* DAT_100377f0;

struct __single_inheritance FUN_1000b6e0_this {
    void __thiscall FUN_1000b6e0(std::uint32_t param_1, int param_2, int param_3, int param_4, int param_5);
};

extern "C" void __stdcall FUN_1000cfe0();

void __stdcall FUN_1000b760(std::uint32_t param_1)
{
    if (DAT_1003c3c0 == nullptr)
    {
        DAT_1003c3c0 = &PTR_vftable_100377d0;

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

    if ((&param_1 < DAT_100377ec) &&
        (DAT_100377e8 <= &param_1))
    {
        const std::int32_t index =
            static_cast<std::int32_t>(
                reinterpret_cast<std::uintptr_t>(&param_1) -
                reinterpret_cast<std::uintptr_t>(DAT_100377e8)
            );

        if (DAT_100377ec == DAT_100377f0)
        {
            FUN_1000cfe0();
        }

        if (DAT_100377ec != nullptr)
        {
            *DAT_100377ec = DAT_100377e8[index >> 2];
        }

        DAT_100377ec = DAT_100377ec + 1;
        return;
    }

    if (DAT_100377ec == DAT_100377f0)
    {
        FUN_1000cfe0();
    }

    if (DAT_100377ec != nullptr)
    {
        *DAT_100377ec = param_1;
    }

    DAT_100377ec = DAT_100377ec + 1;
}