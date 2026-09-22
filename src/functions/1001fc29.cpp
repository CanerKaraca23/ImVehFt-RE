#include <cstdint>

extern "C" volatile std::uint32_t DAT_1003c414;

extern "C" std::uint32_t __stdcall __hw_cw();
extern "C" std::uint32_t __fastcall ___hw_cw_sse2(
    std::uint32_t,
    std::uint32_t);
extern "C" void __cdecl ___set_fpsr_sse2(std::uint32_t);

std::uint32_t __cdecl __control87(
    std::uint32_t _NewValue,
    std::uint32_t _Mask)
{
    std::uint16_t in_FPUControlWord;

#if defined(_MSC_VER) && defined(_M_IX86)
    __asm {
        fnstcw in_FPUControlWord
    }
#elif defined(__i386__)
    asm volatile("fnstcw %0" : "=m"(in_FPUControlWord));
#else
#error "__control87 requires x86 FPU instructions"
#endif

    std::uint32_t uVar5 = 0;

    if ((in_FPUControlWord & 1) != 0)
        uVar5 = 0x10;
    if ((in_FPUControlWord & 4) != 0)
        uVar5 = uVar5 | 8;
    if ((in_FPUControlWord & 8) != 0)
        uVar5 = uVar5 | 4;
    if ((in_FPUControlWord & 0x10) != 0)
        uVar5 = uVar5 | 2;
    if ((in_FPUControlWord & 0x20) != 0)
        uVar5 = uVar5 | 1;
    if ((in_FPUControlWord & 2) != 0)
        uVar5 = uVar5 | 0x80000;

    const std::uint16_t uVar1 = in_FPUControlWord & 0xc00;

    if ((in_FPUControlWord & 0xc00) != 0) {
        if (uVar1 == 0x400)
            uVar5 = uVar5 | 0x100;
        else if (uVar1 == 0x800)
            uVar5 = uVar5 | 0x200;
        else if (uVar1 == 0xc00)
            uVar5 = uVar5 | 0x300;
    }

    if ((in_FPUControlWord & 0x300) == 0)
        uVar5 = uVar5 | 0x20000;
    else if ((in_FPUControlWord & 0x300) == 0x200)
        uVar5 = uVar5 | 0x10000;

    if ((in_FPUControlWord & 0x1000) != 0)
        uVar5 = uVar5 | 0x40000;

    std::uint32_t uVar2 = ~_Mask & uVar5 | _NewValue & _Mask;

    if (uVar2 != uVar5) {
        uVar5 = __hw_cw();
        uVar2 = 0;

        if ((uVar5 & 1) != 0)
            uVar2 = 0x10;
        if ((uVar5 & 4) != 0)
            uVar2 = uVar2 | 8;
        if ((uVar5 & 8) != 0)
            uVar2 = uVar2 | 4;
        if ((uVar5 & 0x10) != 0)
            uVar2 = uVar2 | 2;
        if ((uVar5 & 0x20) != 0)
            uVar2 = uVar2 | 1;
        if ((uVar5 & 2) != 0)
            uVar2 = uVar2 | 0x80000;

        const std::uint32_t uVar3 = uVar5 & 0xc00;

        if (uVar3 != 0) {
            if (uVar3 == 0x400)
                uVar2 = uVar2 | 0x100;
            else if (uVar3 == 0x800)
                uVar2 = uVar2 | 0x200;
            else if (uVar3 == 0xc00)
                uVar2 = uVar2 | 0x300;
        }

        if ((uVar5 & 0x300) == 0)
            uVar2 = uVar2 | 0x20000;
        else if ((uVar5 & 0x300) == 0x200)
            uVar2 = uVar2 | 0x10000;

        if ((uVar5 & 0x1000) != 0)
            uVar2 = uVar2 | 0x40000;
    }

    uVar5 = 0;

    if (DAT_1003c414 != 0) {
        std::uint32_t MXCSR;

#if defined(_MSC_VER) && defined(_M_IX86)
        __asm {
            stmxcsr MXCSR
        }
#elif defined(__i386__)
        asm volatile("stmxcsr %0" : "=m"(MXCSR));
#else
#error "__control87 requires x86 SSE instructions"
#endif

        if (static_cast<std::int8_t>(MXCSR) < 0)
            uVar5 = 0x10;
        if ((MXCSR & 0x200) != 0)
            uVar5 = uVar5 | 8;
        if ((MXCSR & 0x400) != 0)
            uVar5 = uVar5 | 4;
        if ((MXCSR & 0x800) != 0)
            uVar5 = uVar5 | 2;
        if ((MXCSR & 0x1000) != 0)
            uVar5 = uVar5 | 1;
        if ((MXCSR & 0x100) != 0)
            uVar5 = uVar5 | 0x80000;

        std::uint32_t uVar3 = MXCSR & 0x6000;

        if (uVar3 != 0) {
            if (uVar3 == 0x2000)
                uVar5 = uVar5 | 0x100;
            else if (uVar3 == 0x4000)
                uVar5 = uVar5 | 0x200;
            else if (uVar3 == 0x6000)
                uVar5 = uVar5 | 0x300;
        }

        std::uint32_t uVar4 = MXCSR & 0x8040;

        if (uVar4 == 0x40)
            uVar5 = uVar5 | 0x2000000;
        else if (uVar4 == 0x8000)
            uVar5 = uVar5 | 0x3000000;
        else if (uVar4 == 0x8040)
            uVar5 = uVar5 | 0x1000000;

        uVar4 = ~(_Mask & 0x308031f) & uVar5 |
                _Mask & 0x308031f & _NewValue;

        if (uVar4 != uVar5) {
            uVar5 = ___hw_cw_sse2(uVar3, uVar4);
            ___set_fpsr_sse2(uVar5);

#if defined(_MSC_VER) && defined(_M_IX86)
            __asm {
                stmxcsr MXCSR
            }
#elif defined(__i386__)
            asm volatile("stmxcsr %0" : "=m"(MXCSR));
#endif

            uVar5 = 0;

            if (static_cast<std::int8_t>(MXCSR) < 0)
                uVar5 = 0x10;
            if ((MXCSR & 0x200) != 0)
                uVar5 = uVar5 | 8;
            if ((MXCSR & 0x400) != 0)
                uVar5 = uVar5 | 4;
            if ((MXCSR & 0x800) != 0)
                uVar5 = uVar5 | 2;
            if ((MXCSR & 0x1000) != 0)
                uVar5 = uVar5 | 1;
            if ((MXCSR & 0x100) != 0)
                uVar5 = uVar5 | 0x80000;

            uVar3 = MXCSR & 0x6000;

            if (uVar3 != 0) {
                if (uVar3 == 0x2000)
                    uVar5 = uVar5 | 0x100;
                else if (uVar3 == 0x4000)
                    uVar5 = uVar5 | 0x200;
                else if (uVar3 == 0x6000)
                    uVar5 = uVar5 | 0x300;
            }

            uVar3 = MXCSR & 0x8040;

            if (uVar3 == 0x40)
                uVar5 = uVar5 | 0x2000000;
            else if (uVar3 == 0x8000)
                uVar5 = uVar5 | 0x3000000;
            else if (uVar3 == 0x8040)
                uVar5 = uVar5 | 0x1000000;
        }

        uVar3 = uVar5 ^ uVar2;
        uVar2 = uVar5 | uVar2;

        if ((uVar3 & 0x8031f) != 0)
            uVar2 = uVar2 | 0x80000000;
    }

    return uVar2;
}