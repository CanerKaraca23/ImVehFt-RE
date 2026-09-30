#include <cstdint>

extern "C" double DAT_10024eb8;
extern "C" double DAT_10024e70;
extern "C" double DAT_10024eb0;

extern "C" void __fastcall FUN_1001b380(void*);
extern "C" void __fastcall FUN_1001b4b0(void*);

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "FUN_100073f0 requires the MSVC x86 x87 calling environment"
#endif

extern "C" __declspec(naked) void __fastcall FUN_100073f0(
    void*,
    std::uint32_t,
    std::uint32_t,
    float,
    float,
    std::uint32_t,
    std::uint32_t,
    std::uint32_t)
{
    __asm
    {
        push ebp
        mov ebp, esp
        sub esp, 8

        fld float ptr [ebp + 0x14]
        push 1
        fld st(0)
        push 0
        fld double ptr [DAT_10024eb8]
        push ecx
        fmul st(0), st(1)
        fxch
        fstp float ptr [ebp + 0x14]
        fxch
        fadd double ptr [DAT_10024e70]
        fmulp st(1), st(0)
        fstp float ptr [ebp - 4]

        fld1
        fstp float ptr [esp]
        fld float ptr [ebp + 0x18]
        push 0
        push ecx
        fstp float ptr [esp]
        fld float ptr [ebp + 0x14]
        push eax
        push ecx
        push edx
        push 1
        call FUN_1001b380
        fstp float ptr [ebp - 8]

        fld float ptr [ebp - 8]
        push ecx
        fmul float ptr [ebp + 0xc]
        fmul double ptr [DAT_10024eb0]
        fstp float ptr [ebp - 8]
        fld float ptr [ebp - 8]
        fstp float ptr [esp]
        fld float ptr [ebp + 0x14]
        call FUN_1001b4b0
        fstp float ptr [ebp + 0x14]

        fld float ptr [ebp + 0x14]
        push ecx
        fmul float ptr [ebp + 0xc]
        fmul double ptr [DAT_10024eb0]
        fstp float ptr [ebp + 0xc]
        fld float ptr [ebp + 0xc]
        fstp float ptr [esp]
        fld float ptr [ebp - 4]
        call FUN_1001b380
        fstp float ptr [ebp + 0xc]

        fld float ptr [ebp + 0xc]
        push ecx
        fmul float ptr [ebp + 0x10]
        fmul double ptr [DAT_10024eb0]
        fstp float ptr [ebp + 0xc]
        fld float ptr [ebp + 0xc]
        fstp float ptr [esp]
        fld float ptr [ebp - 4]
        call FUN_1001b4b0
        fstp float ptr [ebp + 0xc]

        fld float ptr [ebp + 0xc]
        mov eax, dword ptr [ebp + 8]
        fmul float ptr [ebp + 0x10]
        push ecx
        mov ecx, dword ptr [ebp + 0x1c]
        mov edx, 0x00707390
        fmul double ptr [DAT_10024eb0]
        fstp float ptr [ebp + 0xc]
        fld float ptr [ebp + 0xc]
        fstp float ptr [esp]
        push eax
        push ecx
        push 2
        call edx
        add esp, 0x40

        mov esp, ebp
        pop ebp
        ret
    }
}
