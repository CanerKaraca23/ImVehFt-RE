#include <cstdint>

using UnresolvedCallback = void (__cdecl*)();

using UnresolvedFunction =
    void (__cdecl*)(
        std::uint32_t,
        UnresolvedCallback,
        std::uint32_t);

extern "C" void __cdecl FUN_10003fe0(int, int);

extern "C" std::uint32_t __cdecl FUN_10003fb0(
    std::uint32_t param_1,
    std::uint32_t param_2)
{
    reinterpret_cast<UnresolvedFunction>(
        static_cast<std::uintptr_t>(0x7F1200u))(
            param_1,
            reinterpret_cast<UnresolvedCallback>(FUN_10003fe0),
            param_2);

    reinterpret_cast<UnresolvedFunction>(
        static_cast<std::uintptr_t>(0x7F0DC0u))(
            param_1,
            reinterpret_cast<UnresolvedCallback>(FUN_10003fb0),
            param_2);

    return param_1;
}