#include <cstdint>

extern "C" void __cdecl __87except();

// This CRT helper receives its 80-bit argument in ST(0), and returns the
// preserved value in ST(0). Ghidra's `float10` is not a source-level MSVC
// type, so model the original x87 ABI explicitly instead of substituting
// `long double` (which is 64-bit under the MSVC ABI).
extern "C" __declspec(naked) void __fastcall __startOneArgErrorHandling()
{
    __asm
    {
        push ebp
        mov ebp, esp
        sub esp, 20h
        mov dword ptr [ebp - 20h], eax
        fstp qword ptr [ebp - 8]
        mov dword ptr [ebp - 1Ch], ecx
        mov eax, dword ptr [ebp + 10h]
        mov ecx, dword ptr [ebp + 14h]
        mov dword ptr [ebp - 18h], eax
        mov dword ptr [ebp - 14h], ecx
        lea eax, [ebp + 8]
        lea ecx, [ebp - 20h]
        push eax
        push ecx
        push edx
        call __87except
        add esp, 0Ch
        fld qword ptr [ebp - 8]
        cmp word ptr [ebp + 8], 027Fh
        je restore_frame
        fldcw word ptr [ebp + 8]

    restore_frame:
        leave
        ret
    }
}
