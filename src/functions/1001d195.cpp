#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" __declspec(naked) void __stdcall FUN_1001d195(void)
{
    __asm {
        mov eax, dword ptr [ebp - 24h]
        mov dword ptr [edi - 4], eax
        push dword ptr [ebp - 28h]
        mov eax, 1001B98Ch
        call eax
        add esp, 4
        mov eax, 10014DF0h
        call eax
        mov ecx, dword ptr [ebp - 2Ch]
        mov dword ptr [eax + 88h], ecx
        mov eax, 10014DF0h
        call eax
        mov ecx, dword ptr [ebp - 30h]
        mov dword ptr [eax + 8Ch], ecx
        cmp dword ptr [esi], 0E06D7363h
        jne done
        cmp dword ptr [esi + 10h], 3
        jne done
        mov eax, dword ptr [esi + 14h]
        cmp eax, 19930520h
        je check_state
        cmp eax, 19930521h
        je check_state
        cmp eax, 19930522h
        jne done
    check_state:
        cmp dword ptr [ebp - 34h], 0
        jne done
        cmp dword ptr [ebp - 1Ch], 0
        je done
        push dword ptr [esi + 18h]
        mov eax, 1001B965h
        call eax
        add esp, 4
        test eax, eax
        jz done
        push dword ptr [ebp + 10h]
        push esi
        mov eax, 1001CF2Dh
        call eax
        add esp, 8
    done:
        ret
    }
}