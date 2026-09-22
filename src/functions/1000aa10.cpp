#include <cstdint>

extern void** PTR_vftable_100375a0;
extern void** DAT_1003c398;
extern std::uint32_t* DAT_100375c8;
extern std::uint32_t* DAT_100375cc;
extern std::uint32_t* DAT_100375d0;

struct __single_inheritance FUN_1000a8c0_this {
    void __thiscall FUN_1000a8c0(std::uint32_t param_1, int param_2, int param_3, int param_4, int param_5);
};

extern "C" void __stdcall FUN_1000cfe0();

void __stdcall FUN_1000aa10(std::uint32_t param_1)
{
    if (DAT_1003c398 == nullptr)
    {
        DAT_1003c398 =
            reinterpret_cast<void**>(&PTR_vftable_100375a0);

        using Initializer = decltype(&FUN_1000a8c0_this::FUN_1000a8c0);

        const Initializer initializer =
            *reinterpret_cast<Initializer*>(
                reinterpret_cast<std::uintptr_t>(
                    PTR_vftable_100375a0) + 4u);

        static_assert(sizeof(Initializer) == sizeof(void*));
(reinterpret_cast<FUN_1000a8c0_this*>(DAT_1003c398)->*initializer)(

            0x440a0d,
            0x53bcc9,
            0x53be8d,
            0x53bfc7,
            0x618f05);
    }

    auto* param_address = &param_1;

    if ((param_address < DAT_100375cc) &&
        (DAT_100375c8 <= param_address))
    {
        const std::int32_t index =
            static_cast<std::int32_t>(
                static_cast<std::uint32_t>(
                    reinterpret_cast<std::uintptr_t>(param_address)) -
                static_cast<std::uint32_t>(
                    reinterpret_cast<std::uintptr_t>(DAT_100375c8)));

        if (DAT_100375cc == DAT_100375d0)
        {
            FUN_1000cfe0();
        }

        if (DAT_100375cc != nullptr)
        {
            *DAT_100375cc = DAT_100375c8[index >> 2];
        }

        DAT_100375cc = DAT_100375cc + 1;
        return;
    }

    if (DAT_100375cc == DAT_100375d0)
    {
        FUN_1000cfe0();
    }

    if (DAT_100375cc != nullptr)
    {
        *DAT_100375cc = param_1;
    }

    DAT_100375cc = DAT_100375cc + 1;
}