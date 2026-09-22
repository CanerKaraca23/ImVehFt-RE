#include <cstdint>

extern "C" std::uint32_t __stdcall __hw_cw()
{
    std::uint32_t ebx_value;

#if defined(_MSC_VER) && defined(_M_IX86)
    __asm mov ebx_value, ebx
#elif defined(__GNUC__) || defined(__clang__)
    static_assert(sizeof(std::uint32_t) == sizeof(unsigned int));
    __asm__ volatile("movl %%ebx, %0" : "=r"(ebx_value));
#else
#error "__hw_cw requires a supported x86 target exposing the incoming EBX register"
#endif

    std::uint32_t result =
        static_cast<std::uint32_t>((ebx_value & 0x10u) != 0u);

    if ((ebx_value & 8u) != 0u) {
        result |= 4u;
    }
    if ((ebx_value & 4u) != 0u) {
        result |= 8u;
    }
    if ((ebx_value & 2u) != 0u) {
        result |= 0x10u;
    }
    if ((ebx_value & 1u) != 0u) {
        result |= 0x20u;
    }
    if ((ebx_value & 0x80000u) != 0u) {
        result |= 2u;
    }

    const std::uint32_t control = ebx_value & 0x300u;
    if (control != 0u) {
        if (control == 0x100u) {
            result |= 0x400u;
        } else if (control == 0x200u) {
            result |= 0x800u;
        } else if (control == 0x300u) {
            result |= 0xC00u;
        }
    }

    if ((ebx_value & 0x30000u) == 0u) {
        result |= 0x300u;
    } else if ((ebx_value & 0x30000u) == 0x10000u) {
        result |= 0x200u;
    }

    if ((ebx_value & 0x40000u) != 0u) {
        result |= 0x1000u;
    }

    return result;
}