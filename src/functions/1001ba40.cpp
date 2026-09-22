#include <cstdint>

extern "C" volatile std::uint32_t DAT_1003c414;

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "FUN_1001ba40 requires MSVC x86 inline-assembly support."
#endif

extern "C" __declspec(naked) std::uint64_t __fastcall FUN_1001ba40(
    std::uint32_t,
    std::uint32_t)
{
    __asm
    {
        cmp dword ptr [DAT_1003c414], 0
        jz custom_rounding_path

        push ebp
        mov ebp, esp
        sub esp, 8
        and esp, 0fffffff8h
        fstp qword ptr [esp]
        _emit 0xf2
        _emit 0x0f
        _emit 0x2c
        _emit 0x04
        _emit 0x24
        leave
        ret

    custom_rounding_path:
        push ebp
        mov ebp, esp
        sub esp, 20h
        and esp, 0fffffff0h
        fld st(0)
        fst dword ptr [esp + 18h]
        fistp qword ptr [esp + 10h]
        fild qword ptr [esp + 10h]
        mov edx, dword ptr [esp + 18h]
        mov eax, dword ptr [esp + 10h]
        test eax, eax
        jz zero_low_word
        fsubp st(1), st(0)
        test edx, edx
        jns nonnegative_input

        fstp dword ptr [esp]
        mov ecx, dword ptr [esp]
        xor ecx, 80000000h
        add ecx, 7fffffffh
        adc eax, 0
        mov edx, dword ptr [esp + 14h]
        adc edx, 0
        jmp rounding_done

    nonnegative_input:
        fstp dword ptr [esp]
        mov ecx, dword ptr [esp]
        add ecx, 7fffffffh
        sbb eax, 0
        mov edx, dword ptr [esp + 14h]
        sbb edx, 0
        jmp rounding_done

    zero_low_word:
        mov edx, dword ptr [esp + 14h]
        test edx, 7fffffffh
        jnz zero_word_residual
        fstp dword ptr [esp + 18h]
        fstp dword ptr [esp + 18h]
        leave
        ret

    zero_word_residual:
        fsubp st(1), st(0)
        test edx, edx
        jns nonnegative_input
        fstp dword ptr [esp]
        mov ecx, dword ptr [esp]
        xor ecx, 80000000h
        add ecx, 7fffffffh
        adc eax, 0
        mov edx, dword ptr [esp + 14h]
        adc edx, 0
        jmp rounding_done

    rounding_done:
        leave
        ret
    }
}
