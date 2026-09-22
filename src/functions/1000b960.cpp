#include <cstdint>

extern void** DAT_1003c3c4;
extern void* PTR_vftable_10037808;

extern std::uint32_t* DAT_10037820;
extern std::uint32_t* DAT_10037824;
extern std::uint32_t* DAT_10037828;

extern "C" void __stdcall FUN_1000cfe0();

using FUN_1000b8e0 = void(__cdecl*)(
    std::uint32_t,
    int,
    int,
    int,
    int
);

void __stdcall FUN_1000b960(std::uint32_t param_1)
{
    if (DAT_1003c3c4 == nullptr)
    {
        DAT_1003c3c4 =
            reinterpret_cast<void**>(&PTR_vftable_10037808);

        auto FUN_1000b8e0 =
            *reinterpret_cast<::FUN_1000b8e0*>(
                reinterpret_cast<std::uintptr_t>(
                    PTR_vftable_10037808) + 4u);

        FUN_1000b8e0(0x5bf85b, 0, 0, 0, 0);
    }

    if ((&param_1 < DAT_10037824) &&
        (DAT_10037820 <= &param_1))
    {
        const std::int32_t iVar1 =
            static_cast<std::int32_t>(
                reinterpret_cast<std::uintptr_t>(&param_1)) -
            static_cast<std::int32_t>(
                reinterpret_cast<std::uintptr_t>(DAT_10037820));

        if (DAT_10037824 == DAT_10037828)
        {
            FUN_1000cfe0();
        }

        if (DAT_10037824 != nullptr)
        {
            *DAT_10037824 = DAT_10037820[iVar1 >> 2];
        }

        DAT_10037824 = DAT_10037824 + 1;
        return;
    }

    if (DAT_10037824 == DAT_10037828)
    {
        FUN_1000cfe0();
    }

    if (DAT_10037824 != nullptr)
    {
        *DAT_10037824 = param_1;
    }

    DAT_10037824 = DAT_10037824 + 1;
    return;
}