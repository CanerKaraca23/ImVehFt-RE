#include <cstdint>

extern std::uint8_t PTR_vftable_100376f0;
extern void** DAT_1003c3b0;

extern std::uint32_t* DAT_10037718;
extern std::uint32_t* DAT_1003771c;
extern std::uint32_t* DAT_10037720;

extern "C" void FUN_1000b120();
extern "C" void __stdcall FUN_1000cfe0();

using FUN_1000b120_t =
    void (__thiscall*)(void*, std::uint32_t, int, int, int, int);

void __stdcall FUN_1000b1a0(std::uint32_t param_1)
{
    if (DAT_1003c3b0 == nullptr)
    {
        DAT_1003c3b0 =
            reinterpret_cast<void**>(&PTR_vftable_100376f0);

        reinterpret_cast<FUN_1000b120_t>(&FUN_1000b120)(
            DAT_1003c3b0,
            0x53e981,
            0,
            0,
            0,
            0);
    }

    const auto parameter_address =
        reinterpret_cast<std::uintptr_t>(&param_1);

    if ((parameter_address <
         reinterpret_cast<std::uintptr_t>(DAT_1003771c)) &&
        (reinterpret_cast<std::uintptr_t>(DAT_10037718) <=
         parameter_address))
    {
        const int offset =
            static_cast<int>(
                parameter_address -
                reinterpret_cast<std::uintptr_t>(DAT_10037718));

        if (DAT_1003771c == DAT_10037720)
        {
            FUN_1000cfe0();
        }

        if (DAT_1003771c != nullptr)
        {
            *DAT_1003771c = DAT_10037718[offset >> 2];
        }

        DAT_1003771c = DAT_1003771c + 1;
        return;
    }

    if (DAT_1003771c == DAT_10037720)
    {
        FUN_1000cfe0();
    }

    if (DAT_1003771c != nullptr)
    {
        *DAT_1003771c = param_1;
    }

    DAT_1003771c = DAT_1003771c + 1;
}