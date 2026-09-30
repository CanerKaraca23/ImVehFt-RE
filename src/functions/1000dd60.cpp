#include "imvehft_image_aliases.hpp"
#include <cstdint>
#include "gta_sa_address_access.hpp"

using VoidCallback = void (__cdecl*)();
using ResultCallback = std::uint32_t (__cdecl*)();

#define DAT_1003c39c IMVEHFT_GLOBAL_AT(std::int32_t, IVF_IMAGE_ADDRESS_1003C39C)

std::uint32_t __stdcall FUN_1000dd60()
{
    const std::int32_t iVar2 = DAT_1003c39c;
    auto* base = reinterpret_cast<std::uint8_t*>(
        static_cast<std::uintptr_t>(iVar2));

    auto* puVar1 = *reinterpret_cast<std::uint32_t**>(base + 0x1c);

    for (auto* puVar3 = *reinterpret_cast<std::uint32_t**>(base + 0x18);
         puVar3 != puVar1;
         puVar3 = puVar3 + 1)
    {
        if (*puVar3 != 0U)
        {
            VoidCallback callback = reinterpret_cast<VoidCallback>(
                static_cast<std::uintptr_t>(*puVar3));
            callback();
        }
    }

    std::uint32_t local_8;
    const std::uint32_t callbackAddress =
        *reinterpret_cast<std::uint32_t*>(base + 0x10);

    if (callbackAddress == 0U)
    {
        local_8 = 0U;
    }
    else
    {
        ResultCallback callback = reinterpret_cast<ResultCallback>(
            static_cast<std::uintptr_t>(callbackAddress));
        local_8 = callback();
    }

    puVar1 = *reinterpret_cast<std::uint32_t**>(base + 0x2c);

    for (auto* puVar3 = *reinterpret_cast<std::uint32_t**>(base + 0x28);
         puVar3 != puVar1;
         puVar3 = puVar3 + 1)
    {
        if (*puVar3 != 0U)
        {
            VoidCallback callback = reinterpret_cast<VoidCallback>(
                static_cast<std::uintptr_t>(*puVar3));
            callback();
        }
    }

    return local_8;
}
