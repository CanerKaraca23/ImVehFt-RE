#include <cstdint>
#include "gta_sa_address_access.hpp"

#pragma warning(disable : 4733) // Intentional Win32 SEH-chain registration, reproduced from Ghidra evidence.

extern std::int32_t DAT_1003bd90;
extern float _DAT_10024f70;
extern float _DAT_10024f78;
extern float _DAT_10024f80;

extern "C" std::int32_t __stdcall FUN_10001630();
extern "C" std::uint32_t __stdcall FUN_10010140(float, float, float, float);
extern "C" std::uint32_t __stdcall FUN_10010180();
extern "C" void __cdecl IVF_EH_HANDLER_10020848();

__declspec(naked) void __stdcall FUN_10008000()
{
    __asm {
        push ebp
        mov ebp, esp
        push -1
        push offset IVF_EH_HANDLER_10020848
        mov eax, fs:[0]
        push eax
        mov fs:[0], esp
        sub esp, 20h

        mov eax, 727230h
        lea ecx, [ebp - 10h]
        call eax

        mov dword ptr [ebp - 4], 0

        mov ecx, 00ba67a4h
        cmp byte ptr [ecx], 0
        jz cleanup
        mov ecx, 00ba677ah
        cmp byte ptr [ecx], 0
        jnz cleanup
        mov ecx, 00ba68a4h
        cmp byte ptr [ecx], 0
        jz cleanup
        mov ecx, 00ba68a5h
        mov al, byte ptr [ecx]
        cmp al, 22h
        jz active
        cmp al, 29h
        jnz cleanup

    active:
        mov eax, dword ptr [DAT_1003bd90]
        test eax, eax
        jz initialize
        push esi
        push edi
        lea esi, [ebp - 1ch]
        mov dword ptr [ebp - 10h], eax
        call FUN_10010180

        // Preserve the original x87 instruction order and its intermediate
        // stack precision.  The Ghidra body performs mixed float/double
        // operations whose exact result is not equivalent to rewritten SSE
        // float expressions.
        mov ecx, 00c17048h
        fild dword ptr [ecx]
        sub esp, 10h
        lea esi, [ebp - 2ch]
        fstp dword ptr [ebp - 14h]
        mov edi, eax
        fld dword ptr [ebp - 14h]
        fld qword ptr [_DAT_10024f80]
        fmul st(0), st(1)
        fld qword ptr [_DAT_10024f78]
        fmul st(0), st(1)
        mov ecx, 00c17044h
        fild dword ptr [ecx]
        fstp dword ptr [ebp - 18h]
        fld st(2)
        fmul qword ptr [_DAT_10024f70]
        fmulp st(1), st(0)
        fld st(2)
        fsub st(0), st(2)
        fstp dword ptr [ebp - 14h]
        fld dword ptr [ebp - 14h]
        fstp dword ptr [esp + 0ch]
        fld dword ptr [ebp - 18h]
        fld st(0)
        fsubrp st(3), st(0)
        fxch st(2)
        fstp dword ptr [ebp - 18h]
        fld dword ptr [ebp - 18h]
        fstp dword ptr [esp + 8]
        fsub st(2), st(0)
        fxch st(2)
        fstp dword ptr [ebp - 18h]
        fld dword ptr [ebp - 18h]
        fstp dword ptr [esp + 4]
        fsubrp st(1), st(0)
        fstp dword ptr [ebp - 18h]
        fld dword ptr [ebp - 18h]
        fstp dword ptr [esp]

        call FUN_10010140
        push edi
        push eax
        mov edx, 728350h
        lea ecx, [ebp - 10h]
        call edx
        pop edi
        pop esi
        jmp cleanup

    initialize:
        call FUN_10001630
        mov dword ptr [DAT_1003bd90], eax

    cleanup:
        mov dword ptr [ebp - 4], -1
        mov eax, 7281e0h
        lea ecx, [ebp - 10h]
        call eax

        mov ecx, dword ptr [ebp - 0Ch]
        mov fs:[0], ecx
        mov esp, ebp
        pop ebp
        ret
    }
}
