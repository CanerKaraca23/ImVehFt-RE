#include <cstdint>

extern "C" std::uintptr_t DAT_1003c420[];
extern "C" void __cdecl __unlock_fhandle(int file_handle);

extern "C" __declspec(naked) void __stdcall FUN_10018a8b()
{
    __asm {
        cmp dword ptr [ebp-1Ch], edi
        jz sopen_unlock_done
        cmp dword ptr [ebp-20h], edi
        jz sopen_unlock_handle
        mov eax, dword ptr [esi]
        mov ecx, eax
        sar ecx, 5
        and eax, 1Fh
        shl eax, 6
        mov ecx, dword ptr [ecx*4 + DAT_1003c420]
        lea eax, [ecx + eax + 4]
        and byte ptr [eax], 0FEh

    sopen_unlock_handle:
        push dword ptr [esi]
        call __unlock_fhandle
        pop ecx

    sopen_unlock_done:
        ret
    }
}
