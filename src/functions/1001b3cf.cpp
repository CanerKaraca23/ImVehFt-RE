#include <cstdint>

extern "C" void __cdecl FUN_1001ca2e(void);
extern "C" std::uint16_t DAT_100258e8;
extern "C" void DAT_100258ea(void);
extern "C" void DAT_100258b0(void);
extern "C" std::uint32_t DAT_1003c404;
extern "C" void DAT_10039570(void);
extern "C" std::uint32_t __stdcall FUN_1001c9bc(void);
extern "C" void __fastcall __math_exit(void*, int, std::uint32_t, std::uint32_t, std::uint32_t);
extern "C" void __fastcall __startOneArgErrorHandling(void*, int, std::uint16_t, std::uint32_t, std::uint32_t, std::uint32_t);

extern "C" std::uint32_t __fastcall __fload_withFB(void*, void*);

extern "C" __declspec(naked) std::uint32_t __fastcall FUN_1001b3cf(
    void* , void* , int )
{
    __asm {
        lea edx, [esp + 4]
        call __fload_withFB
        push edx
        fstcw word ptr [esp]
        jz L_sin_zero_flag
        cmp word ptr [esp], 027fh
        jz L_sin_fsin
        fldcw word ptr [DAT_100258e8]
L_sin_fsin:
        fsin
        fstsw ax
        sahf
        jp L_sin_reduce
L_sin_check_errno:
        cmp dword ptr [DAT_1003c404], 0
        jz L_sin_errno_ok
        jmp FUN_1001ca2e
    L_sin_errno_ok:
        mov edx, 01eh
        lea ecx, DAT_10039570
        jmp __math_exit
L_sin_reduce:
        fld tbyte ptr [DAT_100258ea]
        fxch
L_sin_fprem:
        fprem1
        fstsw ax
        sahf
        jp L_sin_fprem
        fstp st(1)
        fsin
        jmp L_sin_check_errno
L_sin_call_finite:
        call FUN_1001c9bc
        jmp L_sin_report
L_sin_zero_flag:
        test eax, 0fffffh
        jnz L_sin_call_finite
        cmp dword ptr [esp + 8], 0
        jnz L_sin_call_finite
        fstp st(0)
        fld tbyte ptr [DAT_100258b0]
        mov eax, 1
L_sin_report:
        cmp dword ptr [DAT_1003c404], 0
        jz L_sin_report_ok
        jmp FUN_1001ca2e
    L_sin_report_ok:
        mov edx, 01eh
        lea ecx, DAT_10039570
        call __startOneArgErrorHandling
        pop edx
        ret


    }
}