#include <cstddef>
#include <cstdint>
#include <corecrt.h>
extern "C" int __cdecl __flsbuf(int, void*);
extern "C" __declspec(naked) void __cdecl write_char(void)
{
    __asm {
        test byte ptr [ecx + 0Ch], 40h
        jz L_15441
        cmp dword ptr [ecx + 8], 0
        jz L_15465
    L_15441:
        dec dword ptr [ecx + 4]
        js L_15451
        mov edx, dword ptr [ecx]
        mov byte ptr [edx], al
        inc dword ptr [ecx]
        movzx eax, al
        jmp L_1545D
    L_15451:
        movsx eax, al
        push ecx
        push eax
        call __flsbuf
        pop ecx
        pop ecx
    L_1545D:
        cmp eax, -1
        jnz L_15465
        or dword ptr [esi], eax
        ret
    L_15465:
        inc dword ptr [esi]
        ret
    }
}