#include <cstdint>

extern "C" double DAT_10024e68;
extern "C" double DAT_10024e70;
extern "C" double DAT_10024e78;

#if defined(_MSC_VER) && defined(_M_IX86)
extern "C" __declspec(naked) void __stdcall FUN_10008d20()
{
    __asm {
        push ebp
        mov ebp, esp
        sub esp, 8
        fld dword ptr [eax + 10h]
        sub esp, 8
        fstp dword ptr [ebp - 8]
        fld dword ptr [eax + 14h]
        mov eax, 53cc70h
        fstp dword ptr [ebp - 4]
        fld dword ptr [ebp - 4]
        fstp dword ptr [esp + 4]
        fld dword ptr [ebp - 8]
        fstp dword ptr [esp]
        call eax
        fmul qword ptr [DAT_10024e78]
        add esp, 8
        fsub qword ptr [DAT_10024e70]
        fstp dword ptr [ebp - 4]
        fldz
        fld dword ptr [ebp - 4]
        fcom
        fnstsw ax
        test ah, 5
        jp short nonnegative_or_unordered
        fld qword ptr [DAT_10024e68]
        jmp short add_period

    add_period_again:
        fxch
    add_period:
        fadd st(1), st(0)
        fxch
        fstp dword ptr [ebp - 4]
        fld dword ptr [ebp - 4]
        fcom st(2)
        fnstsw ax
        test ah, 5
        jnp short add_period_again
        fstp st(2)
        fstp st(0)
        mov esp, ebp
        pop ebp
        ret

    nonnegative_or_unordered:
        fstp st(1)
        mov esp, ebp
        pop ebp
        ret
    }
}
#else
#error "FUN_10008d20 requires the MSVC x86 inline assembler."
#endif
