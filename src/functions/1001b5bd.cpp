#include <cstdint>

extern "C" void __cdecl FUN_1001ca2e(void);
extern "C" std::uint32_t DAT_1003c404;
extern "C" unsigned char DAT_100258b0(void);
extern "C" void DAT_10039590(void);

extern "C" std::uint32_t __cdecl FUN_1001c9a5(void);
extern "C" std::uint32_t __stdcall FUN_1001c9bc(void);
extern "C" void __fastcall __math_exit(
    const void*, int, std::uint32_t, std::uint32_t, std::uint32_t);
extern "C" void __fastcall __startOneArgErrorHandling(
    const void*, int, std::uint16_t, std::uint32_t, std::uint32_t, std::uint32_t);

// CRT math-error path. It consumes incoming ZF/EAX and the x87 stack, so keep
// the original x86 register, stack, and x87 side effects explicit.
extern "C" __declspec(naked) std::uint32_t __cdecl FUN_1001b5bd(
    std::uint32_t, std::uint32_t)
{
    __asm {
        push edx
        fstcw word ptr [esp]
        mov eax, dword ptr [esp + 0ch]
        jz incoming_zf_set

        cmp word ptr [esp], 027fh
        jz control_word_ready
        call FUN_1001c9a5

    control_word_ready:
        test eax, 080000000h
        jnz classify_argument
        fsqrt

    sqrt_result:
        cmp dword ptr [DAT_1003c404], 0
        jz L_sqrt_errno_ok
        jmp FUN_1001ca2e
    L_sqrt_errno_ok:
        mov edx, 5
        lea ecx, dword ptr DAT_10039590
        jmp __math_exit

    classify_argument:
        test eax, 07ff00000h
        jnz domain_result
        test eax, 0000fffffh
        jnz domain_result
        cmp dword ptr [esp + 8], 0
        jnz domain_result
        jmp sqrt_result

    call_domain_classifier:
        call FUN_1001c9bc
        jmp error_handler

    incoming_zf_set:
        test eax, 0000fffffh
        jnz call_domain_classifier
        cmp dword ptr [esp + 8], 0
        jnz call_domain_classifier
        and eax, 080000000h
        jz sqrt_result

    domain_result:
        fstp st(0)
        fld tbyte ptr [DAT_100258b0]
        mov eax, 1

    error_handler:
        cmp dword ptr [DAT_1003c404], 0
        jz L_sqrt_report_ok
        jmp FUN_1001ca2e
    L_sqrt_report_ok:
        mov edx, 5
        lea ecx, dword ptr DAT_10039590
        call __startOneArgErrorHandling
        pop edx
        ret


    }
}
