#include <cstdint>
extern "C" void FUN_10010b1a(void);
extern "C" std::uint32_t DAT_10039a58;
extern "C" std::uint32_t DAT_100220c8;
extern "C" std::uint32_t DAT_100220c4;

extern "C" __declspec(naked) int __cdecl getSystemCP(int )
{
    __asm {
        mov edi, edi
        push ebp
        mov ebp, esp
        sub esp, 10h
        push ebx
        xor ebx, ebx
        push ebx
        lea ecx, [ebp - 10h]
        call FUN_10010b1a
        mov dword ptr [DAT_10039a58], ebx
        cmp esi, -2
        jnz L_14527
        mov dword ptr [DAT_10039a58], 1
        call dword ptr [DAT_100220c8]
    L_14519:
        cmp byte ptr [ebp - 4], bl
        jz L_14563
        mov ecx, dword ptr [ebp - 8]
        and dword ptr [ecx + 70h], 0FFFFFFFDh
        jmp L_14563
    L_14527:
        cmp esi, -3
        jnz L_1453E
        mov dword ptr [DAT_10039a58], 1
        call dword ptr [DAT_100220c4]
        jmp L_14519
    L_1453E:
        cmp esi, -4
        jnz L_14555
        mov eax, dword ptr [ebp - 10h]
        mov eax, dword ptr [eax + 4]
        mov dword ptr [DAT_10039a58], 1
        jmp L_14519
    L_14555:
        cmp byte ptr [ebp - 4], bl
        jz L_14561
        mov eax, dword ptr [ebp - 8]
        and dword ptr [eax + 70h], 0FFFFFFFDh
    L_14561:
        mov eax, esi
    L_14563:
        pop ebx
        leave
        ret
    }
}