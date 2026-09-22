#include <cstddef>
#include <cstdint>
#include <corecrt.h>
extern "C" int* __cdecl __errno(void);
extern "C" void __cdecl write_char(void);
extern "C" __declspec(naked) void __cdecl write_string(void)
{
    __asm {
        mov edi, edi
        push ebp
        mov ebp, esp
        push ecx
        push ebx
        push esi
        mov esi, eax
        mov ebx, ecx
        call __errno
        test byte ptr [edi + 0Ch], 40h
        mov eax, dword ptr [eax]
        mov dword ptr [ebp - 4], eax
        jz L_1548E
        cmp dword ptr [edi + 8], 0
        jnz L_1548E
        add dword ptr [esi], ebx
        jmp L_154D8
    L_1548E:
        call __errno
        and dword ptr [eax], 0
        jmp L_154C0
    L_15498:
        mov eax, dword ptr [ebp + 8]
        mov al, byte ptr [eax]
        mov ecx, edi
        dec ebx
        call write_char
        inc dword ptr [ebp + 8]
        cmp dword ptr [esi], -1
        jnz L_154C0
        call __errno
        cmp dword ptr [eax], 2Ah
        jnz L_154C4
        mov ecx, edi
        mov al, 3Fh
        call write_char
    L_154C0:
        test ebx, ebx
        jg L_15498
    L_154C4:
        call __errno
        cmp dword ptr [eax], 0
        jnz L_154D8
        call __errno
        mov ecx, dword ptr [ebp - 4]
        mov dword ptr [eax], ecx
    L_154D8:
        pop esi
        pop ebx
        leave
        ret
    }
}