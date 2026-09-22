#include <cstdint>

extern "C" void __cdecl FUN_1001ca2e(void);
extern "C" std::uint16_t DAT_100258e8;
extern "C" void DAT_100258ea(void);
extern "C" void DAT_100258b0(void);
extern "C" std::uint32_t DAT_1003c404;
extern "C" void DAT_10039580(void);
extern "C" std::uint32_t __stdcall FUN_1001c9bc(void);
extern "C" void __fastcall __math_exit(void*, int, std::uint32_t, std::uint32_t, std::uint32_t);
extern "C" void __fastcall __startOneArgErrorHandling(void*, int, std::uint16_t, std::uint32_t, std::uint32_t, std::uint32_t);

extern "C" __declspec(naked) std::uint32_t __cdecl FUN_1001b508(
    int , std::uint32_t )
{
    __asm {
        push edx
        fstcw word ptr [esp]
        jz L_cos_zero_flag
        cmp word ptr [esp], 027fh
        jz L_cos_fcos
        fldcw word ptr [DAT_100258e8]
L_cos_fcos:
        fcos
        fstsw ax
        sahf
        jp L_cos_reduce
L_cos_check_errno:
        cmp dword ptr [DAT_1003c404], 0
        jz L_cos_errno_ok
        jmp FUN_1001ca2e
    L_cos_errno_ok:
        mov edx, 012h
        lea ecx, DAT_10039580
        jmp __math_exit
L_cos_reduce:
        fld tbyte ptr [DAT_100258ea]
        fxch
L_cos_fprem:
        fprem1
        fstsw ax
        sahf
        jp L_cos_fprem
        fstp st(1)
        fcos
        jmp L_cos_check_errno
L_cos_call_finite:
        call FUN_1001c9bc
        jmp L_cos_report
L_cos_zero_flag:
        test eax, 0fffffh
        jnz L_cos_call_finite
        cmp dword ptr [esp + 8], 0
        jnz L_cos_call_finite
        fstp st(0)
        fld tbyte ptr [DAT_100258b0]
        mov eax, 1
L_cos_report:
        cmp dword ptr [DAT_1003c404], 0
        jz L_cos_report_ok
        jmp FUN_1001ca2e
    L_cos_report_ok:
        mov edx, 012h
        lea ecx, DAT_10039580
        call __startOneArgErrorHandling
        pop edx
        ret


    }
}