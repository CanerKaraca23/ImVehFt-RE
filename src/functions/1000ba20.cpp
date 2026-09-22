#include <cstdint>

extern void** DAT_1003c3c4;
extern void* PTR_vftable_10037808;

extern std::uint32_t* DAT_10037830;
extern std::uint32_t* DAT_10037834;
extern std::uint32_t* DAT_10037838;

struct __single_inheritance FUN_1000b8e0_this {
    void __thiscall FUN_1000b8e0(std::uint32_t param_1, int param_2, int param_3, int param_4, int param_5);
};

extern "C" void __stdcall FUN_1000cfe0();

void __stdcall FUN_1000ba20(std::uint32_t param_1)
{
    std::int32_t iVar1;

    if (DAT_1003c3c4 == nullptr)
    {
        DAT_1003c3c4 =
            reinterpret_cast<void**>(&PTR_vftable_10037808);

        using Initializer = decltype(&FUN_1000b8e0_this::FUN_1000b8e0);
static_assert(sizeof(Initializer) == sizeof(void*));
const Initializer initializer = *reinterpret_cast<Initializer*>(
    reinterpret_cast<std::uintptr_t>(PTR_vftable_10037808) + 4u);
(reinterpret_cast<FUN_1000b8e0_this*>(DAT_1003c3c4)->*initializer)(

            0x5bf85u,
            0,
            0,
            0,
            0);
    }

    const auto param_address =
        reinterpret_cast<std::uintptr_t>(&param_1);
    const auto begin_address =
        reinterpret_cast<std::uintptr_t>(DAT_10037830);
    const auto end_address =
        reinterpret_cast<std::uintptr_t>(DAT_10037834);

    if ((param_address < end_address) &&
        (begin_address <= param_address))
    {
        iVar1 = static_cast<std::int32_t>(
            param_address - begin_address
        );

        if (DAT_10037834 == DAT_10037838)
        {
            FUN_1000cfe0();
        }

        if (DAT_10037834 != nullptr)
        {
            *DAT_10037834 = DAT_10037830[iVar1 >> 2];
        }

        DAT_10037834 = DAT_10037834 + 1;
        return;
    }

    if (DAT_10037834 == DAT_10037838)
    {
        FUN_1000cfe0();
    }

    if (DAT_10037834 != nullptr)
    {
        *DAT_10037834 = param_1;
    }

    DAT_10037834 = DAT_10037834 + 1;
}