#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" __declspec(safebuffers) std::uint64_t __fastcall __aullshr(void)
{
    std::uint32_t eax_value;
    std::uint32_t edx_value;
    std::uint8_t shift_count;

    __asm {
        mov eax_value, eax
        mov edx_value, edx
        mov shift_count, cl
    }

    if (shift_count >= 0x40)
        return 0;

    if (shift_count < 0x20)
    {
        const std::uint32_t shift = shift_count & 0x1f;
        if (shift_count == 0)
            return (static_cast<std::uint64_t>(edx_value) << 32) | eax_value;

        return (static_cast<std::uint64_t>(edx_value >> shift) << 32)
             | (eax_value >> shift | edx_value << (0x20 - shift));
    }

    return static_cast<std::uint64_t>(edx_value >> (shift_count & 0x1f));
}