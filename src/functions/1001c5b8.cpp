#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>

extern "C" [[noreturn]] void __cdecl __invoke_watson(
    wchar_t* param_1, wchar_t* param_2, wchar_t* param_3,
    unsigned int param_4, std::uintptr_t param_5);

extern "C" errno_t __cdecl __controlfp_s(unsigned int* _CurrentState, unsigned int _NewValue, unsigned int _Mask);

extern "C" __declspec(naked) void __stdcall __setdefaultprecision(void)
{
    __asm
    {
        mov edi, edi
        push esi
        push 30000h
        push 10000h
        xor esi, esi
        push esi
        call __controlfp_s
        add esp, 0Ch
        test eax, eax
        jz success
        push esi
        push esi
        push esi
        push esi
        push esi
        call __invoke_watson

    success:
        pop esi
        ret
    }
}
