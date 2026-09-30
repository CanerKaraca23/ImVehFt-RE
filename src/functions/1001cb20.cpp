#include <cstdint>

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "FUN_1001cb20 requires the MSVC x86 x87 ABI."
#endif

void __cdecl __87except(int, int*, std::uint16_t*);

// Ghidra shows this entry setting up the 0x20-byte __87except argument block,
// then branching into the shared handler tail at 0x1001cb40. Reproduce that
// frame explicitly: __87except reads both the status block and saved ST(0) at
// fixed offsets, and the handler tail restores the caller's x87 control word.
__declspec(naked) long double __fastcall FUN_1001cb20(
    std::uint32_t,
    int,
    std::uint16_t,
    std::uint32_t,
    std::uint32_t,
    std::uint32_t,
    std::uint32_t,
    std::uint32_t)
{
    __asm
    {
        push ebp
        mov ebp, esp
        sub esp, 20h

        mov dword ptr [ebp - 20h], eax
        mov eax, dword ptr [ebp + 18h]
        mov dword ptr [ebp - 10h], eax
        mov eax, dword ptr [ebp + 1Ch]
        mov dword ptr [ebp - 0Ch], eax

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
