#include <cstdint>

extern std::uint8_t* PTR_vftable_10037728;
extern std::uint8_t** DAT_1003c3b4;

extern std::uint32_t* DAT_10037750;
extern std::uint32_t* DAT_10037754;
extern std::uint32_t* DAT_10037758;

struct __single_inheritance FUN_1000b260_this {
    void __thiscall FUN_1000b260(std::uint32_t param_1, int param_2, int param_3, int param_4, int param_5);
};

extern "C" void __stdcall FUN_1000cfe0();

void __stdcall FUN_1000b3a0(std::uint32_t param_1)
{
    if (DAT_1003c3b4 == nullptr)
    {
        DAT_1003c3b4 = &PTR_vftable_10037728;

        using Initializer = decltype(&FUN_1000b260_this::FUN_1000b260);
static_assert(sizeof(Initializer) == sizeof(void*));
const Initializer initializer = *reinterpret_cast<Initializer*>(
    reinterpret_cast<std::uintptr_t>(PTR_vftable_10037728) + 4u);
(reinterpret_cast<FUN_1000b260_this*>(&PTR_vftable_10037728)->*initializer)(

            0x58aa2d,
            0,
            0,
            0,
            0);
    }

    if ((&param_1 < DAT_10037754) && (DAT_10037750 <= &param_1))
    {
        const std::int32_t index =
            static_cast<std::int32_t>(
                reinterpret_cast<std::uintptr_t>(&param_1) -
                reinterpret_cast<std::uintptr_t>(DAT_10037750)) >>
            2;

        if (DAT_10037754 == DAT_10037758)
        {
            FUN_1000cfe0();
        }

        if (DAT_10037754 != nullptr)
        {
            *DAT_10037754 = DAT_10037750[index];
        }

        DAT_10037754 = DAT_10037754 + 1;
        return;
    }

    if (DAT_10037754 == DAT_10037758)
    {
        FUN_1000cfe0();
    }

    if (DAT_10037754 != nullptr)
    {
        *DAT_10037754 = param_1;
    }

    DAT_10037754 = DAT_10037754 + 1;
}