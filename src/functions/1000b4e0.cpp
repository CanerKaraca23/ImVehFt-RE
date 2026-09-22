#include <cstdint>

extern void** DAT_1003c3b8;
extern std::uint32_t* DAT_10037788;
extern std::uint32_t* DAT_1003778c;
extern std::uint32_t* DAT_10037790;
extern std::uint8_t PTR_vftable_10037760[];

extern "C" void __stdcall FUN_1000cfe0();

void __stdcall FUN_1000b4e0(std::uint32_t param_1)
{
    if (DAT_1003c3b8 == nullptr)
    {
        DAT_1003c3b8 =
            reinterpret_cast<void**>(&PTR_vftable_10037760);

        using InitializeFunction =
            void(__thiscall*)(void*, std::uint32_t, int, int, int, int);

        const auto initialize =
            *reinterpret_cast<InitializeFunction*>(
                PTR_vftable_10037760 + 4);

        initialize(DAT_1003c3b8, 0x53eca1u, 0, 0, 0, 0);
    }

    if ((&param_1 < DAT_1003778c) &&
        (DAT_10037788 <= &param_1))
    {
        const std::int32_t offset =
            static_cast<std::int32_t>(
                static_cast<std::uint32_t>(
                    reinterpret_cast<std::uintptr_t>(&param_1))) -
            static_cast<std::int32_t>(
                static_cast<std::uint32_t>(
                    reinterpret_cast<std::uintptr_t>(DAT_10037788)));

        if (DAT_1003778c == DAT_10037790)
        {
            FUN_1000cfe0();
        }

        if (DAT_1003778c != nullptr)
        {
            *DAT_1003778c = DAT_10037788[offset >> 2];
        }

        DAT_1003778c = DAT_1003778c + 1;
        return;
    }

    if (DAT_1003778c == DAT_10037790)
    {
        FUN_1000cfe0();
    }

    if (DAT_1003778c != nullptr)
    {
        *DAT_1003778c = param_1;
    }

    DAT_1003778c = DAT_1003778c + 1;
}