#include <cstdint>

extern "C" void __cdecl __local_unwind4(
    std::uint32_t* frame,
    int target_state,
    std::uint32_t value);

extern "C" void __stdcall __seh_longjmp_unwind4_4(int param_1)
{
    const auto base = static_cast<std::uintptr_t>(
        static_cast<std::uint32_t>(param_1));

    __local_unwind4(
        *reinterpret_cast<std::uint32_t**>(base + 0x28),
        *reinterpret_cast<int*>(base + 0x18),
        *reinterpret_cast<std::uint32_t*>(base + 0x1C));
}