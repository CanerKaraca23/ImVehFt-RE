#include <cstdint>

extern void* DAT_1003c3ac;
extern std::uint8_t PTR_vftable_100376b8[];

extern std::uint32_t* DAT_100376e0;
extern std::uint32_t* DAT_100376e4;
extern std::uint32_t* DAT_100376e8;

struct __single_inheritance FUN_1000afe0_this {
    void __thiscall FUN_1000afe0(std::uint32_t param_1, int param_2, int param_3, int param_4, int param_5);
};

extern "C" void __stdcall FUN_1000cfe0();

void __stdcall FUN_1000b060(std::uint32_t param_1)
{
    if (DAT_1003c3ac == nullptr)
    {
        DAT_1003c3ac = &PTR_vftable_100376b8;

        using Initializer = decltype(&FUN_1000afe0_this::FUN_1000afe0);
static_assert(sizeof(Initializer) == sizeof(void*));
const Initializer initializer = *reinterpret_cast<Initializer*>(
    reinterpret_cast<std::uintptr_t>(PTR_vftable_100376b8) + 4u);
(reinterpret_cast<FUN_1000afe0_this*>(DAT_1003c3ac)->*initializer)(

            0x748e09u,
            0x748e48,
            0,
            0,
            0);
    }

    const std::uintptr_t parameter_address =
        reinterpret_cast<std::uintptr_t>(&param_1);

    if ((parameter_address <
         reinterpret_cast<std::uintptr_t>(DAT_100376e4)) &&
        (reinterpret_cast<std::uintptr_t>(DAT_100376e0) <=
         parameter_address))
    {
        const std::int32_t index =
            static_cast<std::int32_t>(parameter_address) -
            static_cast<std::int32_t>(
                reinterpret_cast<std::uintptr_t>(DAT_100376e0));

        if (DAT_100376e4 == DAT_100376e8)
        {
            FUN_1000cfe0();
        }

        if (DAT_100376e4 != nullptr)
        {
            *DAT_100376e4 = DAT_100376e0[index >> 2];
        }

        DAT_100376e4 = DAT_100376e4 + 1;
        return;
    }

    if (DAT_100376e4 == DAT_100376e8)
    {
        FUN_1000cfe0();
    }

    if (DAT_100376e4 != nullptr)
    {
        *DAT_100376e4 = param_1;
    }

    DAT_100376e4 = DAT_100376e4 + 1;
}