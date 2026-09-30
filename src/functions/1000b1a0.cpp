#include "imvehft_image_aliases.hpp"
#include <cstdint>
#include "gta_sa_address_access.hpp"

#define DAT_1003c3b0 IMVEHFT_GLOBAL_AT(void**, IVF_IMAGE_ADDRESS_1003C3B0)
#define DAT_10037718 IMVEHFT_GLOBAL_AT(std::uint32_t*, IVF_IMAGE_ADDRESS_10037718)
#define DAT_1003771c IMVEHFT_GLOBAL_AT(std::uint32_t*, IVF_IMAGE_ADDRESS_1003771C)
#define DAT_10037720 IMVEHFT_GLOBAL_AT(std::uint32_t*, IVF_IMAGE_ADDRESS_10037720)
extern "C" void __stdcall FUN_1000cfe0();

using VtableFunction =
    void (__thiscall*)(void*, std::uint32_t, int, int, int, int);

void __stdcall FUN_1000b1a0(std::uint32_t param_1)
{
    if (DAT_1003c3b0 == nullptr)
    {
        DAT_1003c3b0 = reinterpret_cast<void**>(IVF_IMAGE_ADDRESS_100376F0);

        const auto vtable_entry = *reinterpret_cast<VtableFunction*>(
            reinterpret_cast<std::uintptr_t>(
                IMVEHFT_GLOBAL_AT(void*, IVF_IMAGE_ADDRESS_100376F0)) + 4u);
        vtable_entry(
            reinterpret_cast<void*>(IVF_IMAGE_ADDRESS_100376F0),
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
