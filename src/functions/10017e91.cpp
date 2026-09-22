#include <cstdint>

extern "C" std::uint32_t DAT_1002280c;

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "siglookup requires the original 32-bit MSVC x86 ABI with incoming EDX"
#endif

extern "C" std::uint32_t __cdecl siglookup(std::uint32_t param_1)
{
    std::uint32_t edx_value;

    __asm
    {
        mov edx_value, edx
    }

    std::uint32_t current = param_1;
    const std::uint32_t end = DAT_1002280c * 0xC + param_1;

    do
    {
        if (*reinterpret_cast<std::int32_t*>(
                static_cast<std::uintptr_t>(current) + 4u) ==
            static_cast<std::int32_t>(edx_value))
        {
            break;
        }

        current += 0xC;
    }
    while (current < end);

    if (end <= current ||
        *reinterpret_cast<std::int32_t*>(
            static_cast<std::uintptr_t>(current) + 4u) !=
        static_cast<std::int32_t>(edx_value))
    {
        current = 0;
    }

    return current;
}