#include <cstdint>

extern void** DAT_1003c3e0;
extern std::uint32_t* DAT_100379f0;
extern std::uint32_t* DAT_100379f4;
extern std::uint32_t* DAT_100379f8;
extern void* PTR_vftable_100379c8;

struct __single_inheritance FUN_1000c2e0_this {
    void __thiscall FUN_1000c2e0(std::uint32_t param_1, int param_2, int param_3, int param_4, int param_5);
};

extern "C" void __stdcall FUN_1000cfe0();

void __stdcall FUN_1000c360(std::uint32_t param_1)
{
    int iVar1;

    if (DAT_1003c3e0 == nullptr)
    {
        DAT_1003c3e0 = &PTR_vftable_100379c8;

        using InitFunction = decltype(&FUN_1000c2e0_this::FUN_1000c2e0);
        const InitFunction init = *reinterpret_cast<InitFunction*>(
            reinterpret_cast<std::uintptr_t>(PTR_vftable_100379c8) + 4u);

        static_assert(sizeof(InitFunction) == sizeof(void*));
(reinterpret_cast<FUN_1000c2e0_this*>(DAT_1003c3e0)->*init)(
 0x57c324u, 0, 0, 0, 0);
    }

    if ((&param_1 < DAT_100379f4) && (DAT_100379f0 <= &param_1))
    {
        iVar1 = static_cast<int>(
            reinterpret_cast<std::uintptr_t>(&param_1) -
            reinterpret_cast<std::uintptr_t>(DAT_100379f0));

        if (DAT_100379f4 == DAT_100379f8)
        {
            FUN_1000cfe0();
        }

        if (DAT_100379f4 != nullptr)
        {
            *DAT_100379f4 = DAT_100379f0[iVar1 >> 2];
        }

        DAT_100379f4 = DAT_100379f4 + 1;
        return;
    }

    if (DAT_100379f4 == DAT_100379f8)
    {
        FUN_1000cfe0();
    }

    if (DAT_100379f4 != nullptr)
    {
        *DAT_100379f4 = param_1;
    }

    DAT_100379f4 = DAT_100379f4 + 1;
}