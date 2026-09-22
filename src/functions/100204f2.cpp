#include <cstdint>
#include <immintrin.h>

extern std::uint32_t DAT_1003c414;
extern std::uint32_t DAT_100396f4;

extern "C" void __cdecl ___set_fpsr_sse2(unsigned int param_1)
{
    if (DAT_1003c414 != 0)
    {
        if (((param_1 & 0x40U) == 0) || (DAT_100396f4 == 0))
        {
            _mm_setcsr(param_1 & 0xFFFFFFBFU);
        }
        else
        {
            _mm_setcsr(param_1);
        }
    }

    return;
}