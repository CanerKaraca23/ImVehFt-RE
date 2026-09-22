#include <cstdint>

extern void** DAT_1003c3d4;
extern std::uint32_t* DAT_10037948;
extern std::uint32_t* DAT_1003794c;
extern std::uint32_t* DAT_10037950;
extern void* PTR_vftable_10037920;

struct __single_inheritance FUN_1000bf20_this {
    void __thiscall FUN_1000bf20(std::uint32_t param_1, int param_2, int param_3, int param_4, int param_5);
};

extern "C" void __stdcall FUN_1000cfe0();

void __stdcall FUN_1000bfa0(std::uint32_t param_1)
{
    int iVar1;

    if (DAT_1003c3d4 == nullptr)
    {
        DAT_1003c3d4 =
            reinterpret_cast<void**>(&PTR_vftable_10037920);

        using Initializer = decltype(&FUN_1000bf20_this::FUN_1000bf20);
static_assert(sizeof(Initializer) == sizeof(void*));
const Initializer initializer = *reinterpret_cast<Initializer*>(
    reinterpret_cast<std::uintptr_t>(PTR_vftable_10037920) + 4u);
(reinterpret_cast<FUN_1000bf20_this*>(DAT_1003c3d4)->*initializer)(

            0x6e2d35,
            0,
            0,
            0,
            0);
    }

    if ((&param_1 < DAT_1003794c) &&
        (DAT_10037948 <= &param_1))
    {
        iVar1 = static_cast<int>(
            reinterpret_cast<std::uintptr_t>(&param_1) -
            reinterpret_cast<std::uintptr_t>(DAT_10037948)
        );

        if (DAT_1003794c == DAT_10037950)
        {
            FUN_1000cfe0();
        }

        if (DAT_1003794c != nullptr)
        {
            *DAT_1003794c = DAT_10037948[iVar1 >> 2];
        }

        DAT_1003794c = DAT_1003794c + 1;
        return;
    }

    if (DAT_1003794c == DAT_10037950)
    {
        FUN_1000cfe0();
    }

    if (DAT_1003794c != nullptr)
    {
        *DAT_1003794c = param_1;
    }

    DAT_1003794c = DAT_1003794c + 1;
}