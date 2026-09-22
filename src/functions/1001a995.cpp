#include <cstdint>

extern "C" void* __fastcall __VEC_memzero(
    void* param_1,
    std::uint32_t param_2)
{
    struct Vector128
    {
        std::uint32_t words[4];
    };

    void* original = param_1;
    auto* current = static_cast<std::uint8_t*>(param_1);

    if ((reinterpret_cast<std::uintptr_t>(current) & 0x0Fu) != 0) {
        const std::uint32_t alignment =
            0x10u - static_cast<std::uint32_t>(
                         reinterpret_cast<std::uintptr_t>(current) & 0x0Fu);

        param_2 -= alignment;

        for (std::uint32_t count = alignment & 3u; count != 0; --count) {
            *current = 0;
            current += 1;
        }

        for (std::uint32_t count = alignment >> 2; count != 0; --count) {
            *reinterpret_cast<std::uint32_t*>(current) = 0;
            current += 4;
        }
    }

    for (std::uint32_t count = param_2 >> 7; count != 0; --count) {
        *reinterpret_cast<Vector128*>(current) = Vector128{};
        current += 16;
        *reinterpret_cast<Vector128*>(current) = Vector128{};
        current += 16;
        *reinterpret_cast<Vector128*>(current) = Vector128{};
        current += 16;
        *reinterpret_cast<Vector128*>(current) = Vector128{};
        current += 16;
        *reinterpret_cast<Vector128*>(current) = Vector128{};
        current += 16;
        *reinterpret_cast<Vector128*>(current) = Vector128{};
        current += 16;
        *reinterpret_cast<Vector128*>(current) = Vector128{};
        current += 16;
        *reinterpret_cast<Vector128*>(current) = Vector128{};
        current += 16;
    }

    if ((param_2 & 0x7Fu) != 0) {
        for (std::uint32_t count = (param_2 & 0x7Fu) >> 4;
             count != 0;
             --count) {
            *reinterpret_cast<Vector128*>(current) = Vector128{};
            current += 16;
        }

        if ((param_2 & 0x0Fu) != 0) {
            for (std::uint32_t count = (param_2 & 0x0Fu) >> 2;
                 count != 0;
                 --count) {
                *reinterpret_cast<std::uint32_t*>(current) = 0;
                current += 4;
            }

            for (std::uint32_t count = param_2 & 3u;
                 count != 0;
                 --count) {
                *current = 0;
                current += 1;
            }
        }
    }

    return original;
}