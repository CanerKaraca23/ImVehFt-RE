#include <cstdint>

extern void** DAT_1003c3c8;
extern void* PTR_vftable_10037878;

extern std::uint32_t* DAT_100378a0;
extern std::uint32_t* DAT_100378a4;
extern std::uint32_t* DAT_100378a8;

struct __single_inheritance FUN_1000bb60_this {
    void __thiscall FUN_1000bb60(std::uint32_t param_1, int param_2, int param_3, int param_4, int param_5);
};

extern "C" void __stdcall FUN_1000cfe0();

void __stdcall FUN_1000bbe0(std::uint32_t param_1)
{
    if (DAT_1003c3c8 == nullptr)
    {
        DAT_1003c3c8 =
            reinterpret_cast<void**>(&PTR_vftable_10037878);

        using Initializer = decltype(&FUN_1000bb60_this::FUN_1000bb60);
static_assert(sizeof(Initializer) == sizeof(void*));
const Initializer initializer = *reinterpret_cast<Initializer*>(
    reinterpret_cast<std::uintptr_t>(PTR_vftable_10037878) + 4u);
(reinterpret_cast<FUN_1000bb60_this*>(DAT_1003c3c8)->*initializer)(

            0x53e293u,
            0,
            0,
            0,
            0);
    }

    if ((&param_1 < DAT_100378a4) &&
        (DAT_100378a0 <= &param_1))
    {
        const int iVar1 =
            static_cast<int>(
                reinterpret_cast<std::uintptr_t>(&param_1) -
                reinterpret_cast<std::uintptr_t>(DAT_100378a0));

        if (DAT_100378a4 == DAT_100378a8)
        {
            FUN_1000cfe0();
        }

        if (DAT_100378a4 != nullptr)
        {
            *DAT_100378a4 = DAT_100378a0[iVar1 >> 2];
        }

        DAT_100378a4 = DAT_100378a4 + 1;
        return;
    }

    if (DAT_100378a4 == DAT_100378a8)
    {
        FUN_1000cfe0();
    }

    if (DAT_100378a4 != nullptr)
    {
        *DAT_100378a4 = param_1;
    }

    DAT_100378a4 = DAT_100378a4 + 1;
}