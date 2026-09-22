#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __cdecl __NLG_Notify(int);

extern "C" __declspec(naked) void __fastcall _EH4_TransferToHandler(
    void* ,
    void* )
{
    __asm {
        mov ebp, edx
        mov esi, ecx
        mov eax, ecx
        push 1
        call __NLG_Notify
        xor eax, eax
        xor ebx, ebx
        xor ecx, ecx
        xor edx, edx
        xor edi, edi
        jmp esi
    }
}
