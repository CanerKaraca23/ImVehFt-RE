#include <cstdint>

extern std::uint32_t* PTR_vftable_10037798;

extern std::uint32_t** DAT_1003c3bc;
extern std::uint32_t* DAT_100377c0;
extern std::uint32_t* DAT_100377c4;
extern std::uint32_t* DAT_100377c8;

struct __single_inheritance FUN_1000b5a0_this {
    void __thiscall FUN_1000b5a0(std::uint32_t, int, int, int, int);
};

extern "C" void __stdcall FUN_1000cfe0();

void __stdcall FUN_1000b620(std::uint32_t param_1)
{
    if (DAT_1003c3bc == nullptr)
    {
        DAT_1003c3bc =
            reinterpret_cast<std::uint32_t**>(&PTR_vftable_10037798);

        using Initializer = decltype(&FUN_1000b5a0_this::FUN_1000b5a0);
static_assert(sizeof(Initializer) == sizeof(void*));
const Initializer initializer = *reinterpret_cast<Initializer*>(
    reinterpret_cast<std::uintptr_t>(PTR_vftable_10037798) + 4u);
(reinterpret_cast<FUN_1000b5a0_this*>(DAT_1003c3bc)->*initializer)(

            0x46937b,
            0,
            0,
            0,
            0);
    }

    if ((&param_1 < DAT_100377c4) &&
        (DAT_100377c0 <= &param_1))
    {
        const std::int32_t offset =
            static_cast<std::int32_t>(
                reinterpret_cast<std::uintptr_t>(&param_1) -
                reinterpret_cast<std::uintptr_t>(DAT_100377c0));

        if (DAT_100377c4 == DAT_100377c8)
        {
            FUN_1000cfe0();
        }

        if (DAT_100377c4 != nullptr)
        {
            *DAT_100377c4 = DAT_100377c0[offset >> 2];
        }

        DAT_100377c4 = DAT_100377c4 + 1;
        return;
    }

    if (DAT_100377c4 == DAT_100377c8)
    {
        FUN_1000cfe0();
    }

    if (DAT_100377c4 != nullptr)
    {
        *DAT_100377c4 = param_1;
    }

    DAT_100377c4 = DAT_100377c4 + 1;
}