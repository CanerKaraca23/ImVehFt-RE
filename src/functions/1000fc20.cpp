#include <cstdint>

using Callback = void (__cdecl*)(std::uint32_t);
using ReturnCallback = std::uint32_t (__cdecl*)();

extern std::uint8_t* DAT_1003c3dc;

std::uint32_t __stdcall FUN_1000fc20(std::uint32_t param_1)
{
    std::uint8_t* const instance = DAT_1003c3dc;

    Callback* end = *reinterpret_cast<Callback**>(instance + 0x1c);

    for (Callback* current =
             *reinterpret_cast<Callback**>(instance + 0x18);
         current != end;
         ++current)
    {
        if (*current != nullptr)
        {
            (*current)(param_1);
        }
    }

    const ReturnCallback callback =
        *reinterpret_cast<ReturnCallback*>(instance + 0x04);

    const std::uint32_t result =
        callback != nullptr ? callback() : 0U;

    end = *reinterpret_cast<Callback**>(instance + 0x2c);

    for (Callback* current =
             *reinterpret_cast<Callback**>(instance + 0x28);
         current != end;
         ++current)
    {
        if (*current != nullptr)
        {
            (*current)(param_1);
        }
    }

    return result;
}