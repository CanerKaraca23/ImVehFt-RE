#include <cstdint>

extern "C" std::uint32_t DAT_1003c40c;
extern "C" void __fastcall FUN_1001c5f0(void* param_1);
extern "C" std::uint32_t __cdecl FUN_1001ca18(
    std::uint32_t param_1,
    std::uint32_t param_2);
extern "C" std::uint32_t __cdecl FUN_1001b3d8(
    std::int32_t param_1,
    std::uint32_t param_2);

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "FUN_1001b380 requires the MSVC x86 x87 calling environment"
#endif

extern "C" __declspec(naked) void __fastcall FUN_1001b380(void*)
{
    __asm
    {
        cmp dword ptr [DAT_1003c40c], 0
        jz  L_fallback

        sub esp, 8
        stmxcsr dword ptr [esp + 4]
        mov eax, dword ptr [esp + 4]
        and eax, 0x7f80
        cmp eax, 0x1f80
        jnz L_restore_probe_stack

        fnstcw word ptr [esp]
        mov ax, word ptr [esp]
        and ax, 0x7f
        cmp ax, 0x7f

    L_restore_probe_stack:
        lea esp, [esp + 8]
        jnz L_fallback
        jmp FUN_1001c5f0

    L_fallback:
        sub esp, 0xc
        fst qword ptr [esp]
        call FUN_1001ca18
        call FUN_1001b3d8
        add esp, 0xc
        ret
    }
}
