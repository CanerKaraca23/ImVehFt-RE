#include <cstdint>

extern void** DAT_1003c398;
extern void* PTR_vftable_100375a0;
extern std::uint32_t* DAT_100375b8;
extern std::uint32_t* DAT_100375bc;
extern std::uint32_t* DAT_100375c0;

struct __single_inheritance FUN_1000a8c0_this {
    void __thiscall FUN_1000a8c0(std::uint32_t param_1, std::int32_t param_2, std::int32_t param_3, std::int32_t param_4, std::int32_t param_5);
};

extern "C" void __stdcall FUN_1000cfe0();

void __stdcall FUN_1000a940(std::uint32_t param_1)
{
    if (DAT_1003c398 == nullptr)
    {
        DAT_1003c398 =
            reinterpret_cast<void**>(&PTR_vftable_100375a0);

        using Initializer = decltype(&FUN_1000a8c0_this::FUN_1000a8c0);
static_assert(sizeof(Initializer) == sizeof(void*));
const Initializer initializer = *reinterpret_cast<Initializer*>(
    reinterpret_cast<std::uintptr_t>(PTR_vftable_100375a0) + 4u);
(reinterpret_cast<FUN_1000a8c0_this*>(DAT_1003c398)->*initializer)(

            0x440A0D,
            0x53BCC9,
            0x53BE8D,
            0x53BFC7,
            0x618F05);
    }

    const auto parameter_address =
        reinterpret_cast<std::uintptr_t>(&param_1);

    const auto begin_address =
        reinterpret_cast<std::uintptr_t>(DAT_100375b8);

    const auto end_address =
        reinterpret_cast<std::uintptr_t>(DAT_100375bc);

    if ((parameter_address < end_address) &&
        (begin_address <= parameter_address))
    {
        const std::int32_t index =
            static_cast<std::int32_t>(parameter_address) -
            static_cast<std::int32_t>(begin_address);

        if (DAT_100375bc == DAT_100375c0)
        {
            FUN_1000cfe0();
        }

        if (DAT_100375bc != nullptr)
        {
            *DAT_100375bc = DAT_100375b8[index >> 2];
        }

        DAT_100375bc = DAT_100375bc + 1;
        return;
    }

    if (DAT_100375bc == DAT_100375c0)
    {
        FUN_1000cfe0();
    }

    if (DAT_100375bc != nullptr)
    {
        *DAT_100375bc = param_1;
    }

    DAT_100375bc = DAT_100375bc + 1;
}