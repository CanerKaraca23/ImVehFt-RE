#include <cstdint>

extern void** DAT_1003c3dc;
extern std::uint32_t* DAT_100379b8;
extern std::uint32_t* DAT_100379bc;
extern std::uint32_t* DAT_100379c0;
extern void* PTR_vftable_10037990;

struct __single_inheritance FUN_1000c1a0_this {
    void __thiscall FUN_1000c1a0(std::uint32_t param_1, int param_2, int param_3, int param_4, int param_5);
};

extern "C" void __stdcall FUN_1000cfe0();

void __stdcall FUN_1000c220(std::uint32_t param_1)
{
    int iVar1;

    if (DAT_1003c3dc == nullptr)
    {
        DAT_1003c3dc =
            reinterpret_cast<void**>(&PTR_vftable_10037990);

        using Initializer = decltype(&FUN_1000c1a0_this::FUN_1000c1a0);
static_assert(sizeof(Initializer) == sizeof(void*));
const Initializer initializer = *reinterpret_cast<Initializer*>(
    reinterpret_cast<std::uintptr_t>(PTR_vftable_10037990) + 4u);
(reinterpret_cast<FUN_1000c1a0_this*>(DAT_1003c3dc)->*initializer)(

            0x5e880c,
            0,
            0,
            0,
            0);
    }

    if ((&param_1 < DAT_100379bc) &&
        (DAT_100379b8 <= &param_1))
    {
        iVar1 =
            static_cast<int>(
                reinterpret_cast<std::uintptr_t>(&param_1) -
                reinterpret_cast<std::uintptr_t>(DAT_100379b8)
            );

        if (DAT_100379bc == DAT_100379c0)
        {
            FUN_1000cfe0();
        }

        if (DAT_100379bc != nullptr)
        {
            *DAT_100379bc = DAT_100379b8[iVar1 >> 2];
        }

        DAT_100379bc = DAT_100379bc + 1;
        return;
    }

    if (DAT_100379bc == DAT_100379c0)
    {
        FUN_1000cfe0();
    }

    if (DAT_100379bc != nullptr)
    {
        *DAT_100379bc = param_1;
    }

    DAT_100379bc = DAT_100379bc + 1;
}