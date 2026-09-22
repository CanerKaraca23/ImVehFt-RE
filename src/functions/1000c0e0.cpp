#include <cstdint>

extern void** DAT_1003c3d8;
extern std::uint32_t* DAT_10037980;
extern std::uint32_t* DAT_10037984;
extern std::uint32_t* DAT_10037988;
extern void* PTR_vftable_10037958;

extern "C" void __stdcall FUN_1000cfe0();

using FUN_1000c060_t = void(__thiscall*)(
    void*,
    std::uint32_t,
    int,
    int,
    int,
    int
);

void __stdcall FUN_1000c0e0(std::uint32_t param_1)
{
    int iVar1;

    if (DAT_1003c3d8 == nullptr)
    {
        DAT_1003c3d8 =
            reinterpret_cast<void**>(&PTR_vftable_10037958);

        FUN_1000c060_t FUN_1000c060 =
            *reinterpret_cast<FUN_1000c060_t*>(
                reinterpret_cast<std::uintptr_t>(
                    PTR_vftable_10037958) + 4u);

        FUN_1000c060(DAT_1003c3d8, 0x5e8052u, 0, 0, 0, 0);
    }

    if ((&param_1 < DAT_10037984) &&
        (DAT_10037980 <= &param_1))
    {
        iVar1 = static_cast<int>(
            static_cast<std::int32_t>(
                reinterpret_cast<std::uintptr_t>(&param_1)) -
            static_cast<std::int32_t>(
                reinterpret_cast<std::uintptr_t>(DAT_10037980)));

        if (DAT_10037984 == DAT_10037988)
        {
            FUN_1000cfe0();
        }

        if (DAT_10037984 != nullptr)
        {
            *DAT_10037984 = DAT_10037980[iVar1 >> 2];
        }

        DAT_10037984 = DAT_10037984 + 1;
        return;
    }

    if (DAT_10037984 == DAT_10037988)
    {
        FUN_1000cfe0();
    }

    if (DAT_10037984 != nullptr)
    {
        *DAT_10037984 = param_1;
    }

    DAT_10037984 = DAT_10037984 + 1;
}