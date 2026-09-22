#include <cstdint>

extern void** DAT_1003c3d0;
extern std::uint32_t* DAT_10037910;
extern std::uint32_t* DAT_10037914;
extern std::uint32_t* DAT_10037918;
extern void* PTR_vftable_100378e8;

struct __single_inheritance FUN_1000bde0_this {
    void __thiscall FUN_1000bde0(std::uint32_t param_1, int param_2, int param_3, int param_4, int param_5);
};

extern "C" void __stdcall FUN_1000cfe0();

void __stdcall FUN_1000be60(std::uint32_t param_1)
{
    int iVar1;

    if (DAT_1003c3d0 == nullptr)
    {
        DAT_1003c3d0 = reinterpret_cast<void**>(&PTR_vftable_100378e8);
        using Initializer = decltype(&FUN_1000bde0_this::FUN_1000bde0);
static_assert(sizeof(Initializer) == sizeof(void*));
const Initializer initializer = *reinterpret_cast<Initializer*>(
    reinterpret_cast<std::uintptr_t>(PTR_vftable_100378e8) + 4u);
(reinterpret_cast<FUN_1000bde0_this*>(DAT_1003c3d0)->*initializer)(
 0x6d5f2f, 0, 0, 0, 0);
    }

    if ((&param_1 < DAT_10037914) && (DAT_10037910 <= &param_1))
    {
        iVar1 =
            static_cast<int>(reinterpret_cast<std::uintptr_t>(&param_1)) -
            static_cast<int>(reinterpret_cast<std::uintptr_t>(DAT_10037910));

        if (DAT_10037914 == DAT_10037918)
        {
            FUN_1000cfe0();
        }

        if (DAT_10037914 != nullptr)
        {
            *DAT_10037914 = DAT_10037910[iVar1 >> 2];
        }

        DAT_10037914 = DAT_10037914 + 1;
        return;
    }

    if (DAT_10037914 == DAT_10037918)
    {
        FUN_1000cfe0();
    }

    if (DAT_10037914 != nullptr)
    {
        *DAT_10037914 = param_1;
    }

    DAT_10037914 = DAT_10037914 + 1;
}