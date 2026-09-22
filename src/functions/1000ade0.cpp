#include <cstdint>

extern "C" void** DAT_1003c3a4;
extern "C" void* PTR_vftable_10037648;

extern "C" std::uint32_t* DAT_10037670;
extern "C" std::uint32_t* DAT_10037674;
extern "C" std::uint32_t* DAT_10037678;

extern "C" void __stdcall FUN_1000cfe0();

using VtableFunction = void (__cdecl *)(
    std::uint32_t,
    std::uint32_t,
    std::uint32_t,
    std::uint32_t,
    std::uint32_t);

void __stdcall FUN_1000ade0(std::uint32_t param_1)
{
    if (DAT_1003c3a4 == nullptr)
    {
        DAT_1003c3a4 =
            reinterpret_cast<void**>(&PTR_vftable_10037648);

        const auto vtable_entry =
            *reinterpret_cast<VtableFunction*>(
                reinterpret_cast<std::uintptr_t>(
                    PTR_vftable_10037648) + 4u);

        vtable_entry(0x53bc21u, 0u, 0u, 0u, 0u);
    }

    const auto parameter_address =
        static_cast<std::int32_t>(
            reinterpret_cast<std::uintptr_t>(&param_1));

    const auto begin_address =
        static_cast<std::int32_t>(
            reinterpret_cast<std::uintptr_t>(DAT_10037670));

    const auto end_address =
        static_cast<std::int32_t>(
            reinterpret_cast<std::uintptr_t>(DAT_10037674));

    if ((parameter_address < end_address) &&
        (begin_address <= parameter_address))
    {
        const std::int32_t offset =
            parameter_address - begin_address;

        if (DAT_10037674 == DAT_10037678)
        {
            FUN_1000cfe0();
        }

        if (DAT_10037674 != nullptr)
        {
            *DAT_10037674 =
                DAT_10037670[offset >> 2];
        }

        DAT_10037674 = DAT_10037674 + 1;
        return;
    }

    if (DAT_10037674 == DAT_10037678)
    {
        FUN_1000cfe0();
    }

    if (DAT_10037674 != nullptr)
    {
        *DAT_10037674 = param_1;
    }

    DAT_10037674 = DAT_10037674 + 1;
}