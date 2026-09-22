#include <cstdint>

extern void** DAT_1003c39c;
extern void* PTR_vftable_100375d8;
extern std::uint32_t* DAT_10037600;
extern std::uint32_t* DAT_10037604;
extern std::uint32_t* DAT_10037608;

struct __single_inheritance FUN_1000aae0_this {
    void __thiscall FUN_1000aae0(std::uint32_t, int, int, int, int);
};

extern "C" void __stdcall FUN_1000cfe0();

void __stdcall FUN_1000ab60(std::uint32_t param_1)
{
    if (DAT_1003c39c == nullptr)
    {
        DAT_1003c39c =
            reinterpret_cast<void**>(&PTR_vftable_100375d8);

        using Initializer = decltype(&FUN_1000aae0_this::FUN_1000aae0);
static_assert(sizeof(Initializer) == sizeof(void*));
const Initializer initializer = *reinterpret_cast<Initializer*>(
    reinterpret_cast<std::uintptr_t>(PTR_vftable_100375d8) + 4u);
(reinterpret_cast<FUN_1000aae0_this*>(DAT_1003c39c)->*initializer)(

            0x53EA03u,
            0,
            0,
            0,
            0);
    }

    auto* param_address = reinterpret_cast<std::uint32_t*>(&param_1);

    if ((param_address < DAT_10037604) &&
        (DAT_10037600 <= param_address))
    {
        const std::int32_t index =
            static_cast<std::int32_t>(
                reinterpret_cast<std::uintptr_t>(param_address)
            ) -
            static_cast<std::int32_t>(
                reinterpret_cast<std::uintptr_t>(DAT_10037600)
            );

        if (DAT_10037604 == DAT_10037608)
        {
            FUN_1000cfe0();
        }

        if (DAT_10037604 != nullptr)
        {
            *DAT_10037604 = DAT_10037600[index >> 2];
        }

        DAT_10037604 = DAT_10037604 + 1;
        return;
    }

    if (DAT_10037604 == DAT_10037608)
    {
        FUN_1000cfe0();
    }

    if (DAT_10037604 != nullptr)
    {
        *DAT_10037604 = param_1;
    }

    DAT_10037604 = DAT_10037604 + 1;
}