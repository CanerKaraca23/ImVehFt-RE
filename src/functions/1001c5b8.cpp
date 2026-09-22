#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __cdecl __invoke_watson(wchar_t* param_1, wchar_t* param_2, wchar_t* param_3, unsigned int param_4, std::uintptr_t param_5);

extern "C" errno_t __cdecl __controlfp_s(unsigned int* _CurrentState, unsigned int _NewValue, unsigned int _Mask);

void __stdcall __setdefaultprecision(void)
{
    errno_t result = __controlfp_s(
        static_cast<unsigned int*>(nullptr),
        0x10000u,
        0x30000u);

    if (result != 0)
    {
        __invoke_watson(
            static_cast<wchar_t*>(nullptr),
            static_cast<wchar_t*>(nullptr),
            static_cast<wchar_t*>(nullptr),
            0u,
            0u);
    }
}