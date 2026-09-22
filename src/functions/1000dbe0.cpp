#include <cstdint>

extern "C" std::uint32_t DAT_1003c398;

using Callback = void(__stdcall*)();
using ResultCallback = std::uint32_t(__stdcall*)();

std::uint32_t __stdcall FUN_1000dbe0(void)
{
    const std::uint32_t context = DAT_1003c398;

    std::uint32_t* end = reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(context) + 0x1C)));

    for (std::uint32_t* current = reinterpret_cast<std::uint32_t*>(
             static_cast<std::uintptr_t>(
                 *reinterpret_cast<std::uint32_t*>(
                     static_cast<std::uintptr_t>(context) + 0x18)));
         current != end;
         ++current)
    {
        if (*current != 0U)
        {
            Callback callback = reinterpret_cast<Callback>(
                static_cast<std::uintptr_t>(*current));
            callback();
        }
    }

    const std::uint32_t callbackAddress =
        *reinterpret_cast<std::uint32_t*>(
            static_cast<std::uintptr_t>(context) + 0x14);

    std::uint32_t result = 0U;

    if (callbackAddress != 0U)
    {
        ResultCallback callback = reinterpret_cast<ResultCallback>(
            static_cast<std::uintptr_t>(callbackAddress));
        result = callback();
    }

    end = reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(context) + 0x2C)));

    for (std::uint32_t* current = reinterpret_cast<std::uint32_t*>(
             static_cast<std::uintptr_t>(
                 *reinterpret_cast<std::uint32_t*>(
                     static_cast<std::uintptr_t>(context) + 0x28)));
         current != end;
         ++current)
    {
        if (*current != 0U)
        {
            Callback callback = reinterpret_cast<Callback>(
                static_cast<std::uintptr_t>(*current));
            callback();
        }
    }

    return result;
}