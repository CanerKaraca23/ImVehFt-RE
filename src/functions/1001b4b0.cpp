#include <cstdint>

extern "C" std::uint32_t DAT_1003c40c;

extern "C" void __fastcall FUN_1001cb80(void* param_1);
extern "C" std::uint32_t __cdecl FUN_1001ca18(
    std::uint32_t param_1,
    std::uint32_t param_2);
extern "C" std::uint32_t __cdecl FUN_1001b508(
    std::int32_t param_1,
    std::uint32_t param_2);

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "FUN_1001b4b0 requires the target's 32-bit x87 execution environment"
#endif

extern "C" extern "C" void __fastcall FUN_1001b4b0(void* param_1)
{
    std::uint16_t fpu_control_word;
    std::uint32_t mxcsr;

    __asm
    {
        fnstcw fpu_control_word
        stmxcsr mxcsr
    }

    if ((DAT_1003c40c != 0) &&
        ((mxcsr & 0x7f80u) == 0x1f80u &&
         (fpu_control_word & 0x007fu) == 0x007fu))
    {
        FUN_1001cb80(param_1);
        return;
    }

    double value;

    __asm
    {
        fst qword ptr [value]
    }

    union
    {
        double value;
        std::uint64_t bits;
    } converted{value};

    FUN_1001ca18(
        static_cast<std::uint32_t>(converted.bits),
        static_cast<std::uint32_t>(converted.bits >> 0x20));

    FUN_1001b508(
        static_cast<std::int32_t>(converted.bits),
        static_cast<std::uint32_t>(converted.bits >> 0x20));
}