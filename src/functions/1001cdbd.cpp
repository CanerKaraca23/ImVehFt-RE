#include <cstddef>
#include <cstdint>

struct TidDataProcessingThrowView
{
    std::uint8_t reserved_00[0x90];
    int ProcessingThrow;
};

using _ptiddata = TidDataProcessingThrowView*;

static_assert(offsetof(TidDataProcessingThrowView, ProcessingThrow) == 0x90);

extern "C" TidDataProcessingThrowView* __cdecl __getptd(void);

unsigned int __cdecl ___FrameUnwindFilter(unsigned int* param_1)
{
    extern void __cdecl terminate();

    const int exception_code =
        *reinterpret_cast<const int*>(
            static_cast<unsigned long>(*param_1));

    if ((exception_code == -0x1fbcbcae) ||
        (exception_code == -0x1fbcb0b3))
    {
        _ptiddata p_Var2 = __getptd();

        if (0 < p_Var2->ProcessingThrow)
        {
            p_Var2 = __getptd();
            p_Var2->ProcessingThrow =
                p_Var2->ProcessingThrow + -1;
        }
    }
    else if (exception_code == -0x1f928c9d)
    {
        _ptiddata p_Var2 = __getptd();
        p_Var2->ProcessingThrow = 0;
        terminate();
    }

    return 0;
}