#include <cstdint>

extern void** DAT_1003c3a8;
extern void* PTR_vftable_10037680;

extern std::uint32_t* DAT_100376a8;
extern std::uint32_t* DAT_100376ac;
extern std::uint32_t* DAT_100376b0;

struct __single_inheritance FUN_1000aea0_this {
    void __thiscall FUN_1000aea0(std::uint32_t, int, int, int, int);
};

extern "C" void __stdcall FUN_1000cfe0();

void __stdcall FUN_1000af20(std::uint32_t param_1)
{
    if (DAT_1003c3a8 == nullptr)
    {
        DAT_1003c3a8 =
            reinterpret_cast<void**>(&PTR_vftable_10037680);

        using Initializer = decltype(&FUN_1000aea0_this::FUN_1000aea0);
static_assert(sizeof(Initializer) == sizeof(void*));
const Initializer initializer = *reinterpret_cast<Initializer*>(
    reinterpret_cast<std::uintptr_t>(PTR_vftable_10037680) + 4u);
(reinterpret_cast<FUN_1000aea0_this*>(DAT_1003c3a8)->*initializer)(

            0x748cfb,
            0,
            0,
            0,
            0);
    }

    if ((&param_1 < DAT_100376ac) &&
        (DAT_100376a8 <= &param_1))
    {
        const std::int32_t offset =
            static_cast<std::int32_t>(
                reinterpret_cast<std::uintptr_t>(&param_1) -
                reinterpret_cast<std::uintptr_t>(DAT_100376a8)
            );

        if (DAT_100376ac == DAT_100376b0)
        {
            FUN_1000cfe0();
        }

        if (DAT_100376ac != nullptr)
        {
            *DAT_100376ac = DAT_100376a8[offset >> 2];
        }

        DAT_100376ac = DAT_100376ac + 1;
        return;
    }

    if (DAT_100376ac == DAT_100376b0)
    {
        FUN_1000cfe0();
    }

    if (DAT_100376ac != nullptr)
    {
        *DAT_100376ac = param_1;
    }

    DAT_100376ac = DAT_100376ac + 1;
}