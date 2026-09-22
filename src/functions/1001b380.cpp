#include <cstdint>
#include <cstring>
#include <intrin.h>

extern "C" std::uint32_t DAT_1003c40c;

extern "C" void __fastcall FUN_1001c5f0(void* param_1);
extern "C" std::uint32_t __cdecl FUN_1001ca18(
    std::uint32_t param_1,
    std::uint32_t param_2);
extern "C" std::uint32_t __cdecl FUN_1001b3d8(
    std::int32_t param_1,
    std::uint32_t param_2);

extern "C" void __fastcall FUN_1001b380(void* param_1)
{
    std::uint16_t fpu_control_word;
    double value;

#if defined(_MSC_VER) && defined(_M_IX86)
    __asm
    {
        fnstcw fpu_control_word
    }
#else
#error "FUN_1001b380 requires x86 inline assembly to access the incoming x87 state."
#endif

    if (DAT_1003c40c != 0 &&
        ((_mm_getcsr() & 0x7f80u) == 0x1f80u) &&
        ((fpu_control_word & 0x7fu) == 0x7fu))
    {
        FUN_1001c5f0(param_1);
        return;
    }

#if defined(_MSC_VER) && defined(_M_IX86)
    __asm
    {
        fstp value
    }
#endif

    std::uint64_t bits;
    std::memcpy(&bits, &value, sizeof(bits));

    FUN_1001ca18(
        static_cast<std::uint32_t>(bits),
        static_cast<std::uint32_t>(bits >> 32));

    FUN_1001b3d8(
        static_cast<std::int32_t>(static_cast<std::uint32_t>(bits)),
        static_cast<std::uint32_t>(bits >> 32));
}