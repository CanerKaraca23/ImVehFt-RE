using float10 = long double;

// The 0x1001c5f0 Ghidra body calls this same XMM0/ECX entry through its
// C-decorated symbol. Route that spelling to the verified naked thiscall body.
#pragma comment(linker, "/alternatename:_FUN_1001c60e=?FUN_1001c60e@ReagentMathFunction@@QAEOXZ")

extern double DAT_10025010, DAT_10025850, DAT_10025858, DAT_10025870;
extern double _DAT_10025890;
extern double _DAT_10025810, _DAT_10025820, _DAT_10025830, _DAT_10025840;
extern double _DAT_10025860, _DAT_10025878;
extern double _UNK_10025828, _UNK_10025838, _UNK_10025848, _UNK_10025868;

extern "C" void __fastcall FUN_1001b3cf(void*, void*, int);

struct ReagentMathFunction
{
    float10 __thiscall FUN_1001c60e();
};

__declspec(naked) float10 ReagentMathFunction::FUN_1001c60e()
{
    __asm {
        pextrw eax, xmm0, 3
        and ax, 07fffh
        sub ax, 03030h
        cmp ax, 010c5h
        ja L_range

        movlpd xmm1, qword ptr [DAT_10025850]
        mulsd xmm1, xmm0
        movlpd xmm2, qword ptr [DAT_10025858]
        cvtsd2si edx, xmm1
        addsd xmm1, xmm2
        movlpd xmm3, qword ptr [DAT_10025870]
        subsd xmm1, xmm2
        movapd xmm2, xmmword ptr [_DAT_10025860]
        mulsd xmm3, xmm1
        unpcklpd xmm1, xmm1
        add edx, 01c7600h
        movsd xmm4, xmm0
        and edx, 03fh
        movapd xmm5, xmmword ptr [_DAT_10025840]
        lea eax, DAT_10025010
        shl edx, 5
        add eax, edx
        mulpd xmm2, xmm1
        subsd xmm0, xmm3
        mulsd xmm1, qword ptr [_DAT_10025878]
        subsd xmm4, xmm3
        movlpd xmm7, qword ptr [eax + 8]
        unpcklpd xmm0, xmm0
        movsd xmm3, xmm4
        subsd xmm4, xmm2
        mulpd xmm5, xmm0
        subpd xmm0, xmm2
        movapd xmm6, xmmword ptr [_DAT_10025820]
        mulsd xmm7, xmm4
        subsd xmm3, xmm4
        mulpd xmm5, xmm0
        mulpd xmm0, xmm0
        subsd xmm3, xmm2
        movapd xmm2, xmmword ptr [eax]
        subsd xmm1, xmm3
        movlpd xmm3, qword ptr [eax + 018h]
        addsd xmm2, xmm3
        subsd xmm7, xmm2
        mulsd xmm2, xmm4
        mulpd xmm6, xmm0
        mulsd xmm3, xmm4
        mulpd xmm2, xmm0
        mulpd xmm0, xmm0
        addpd xmm5, xmmword ptr [_DAT_10025830]
        mulsd xmm4, qword ptr [eax]
        addpd xmm6, xmmword ptr [_DAT_10025810]
        mulpd xmm5, xmm0
        movsd xmm0, xmm3
        addsd xmm3, qword ptr [eax + 8]
        mulsd xmm1, xmm7
        movsd xmm7, xmm4
        addsd xmm4, xmm3
        addpd xmm6, xmm5
        movlpd xmm5, qword ptr [eax + 8]
        subsd xmm5, xmm3
        subsd xmm3, xmm4
        addsd xmm1, qword ptr [eax + 010h]
        mulpd xmm6, xmm2
        addsd xmm5, xmm0
        addsd xmm3, xmm7
        addsd xmm1, xmm5
        addsd xmm1, xmm3
        addsd xmm1, xmm6
        unpckhpd xmm6, xmm6
        addsd xmm1, xmm6
        sub esp, 10h
        addsd xmm4, xmm1
        movlpd qword ptr [esp + 4], xmm4
        fld qword ptr [esp + 4]
        add esp, 10h
        ret

    L_range:
        jg L_exception
        sub esp, 10h
        shr ax, 4
        cmp ax, 0cfdh
        jnz L_return_input
        mulsd xmm0, qword ptr [_DAT_10025890]
        movlpd qword ptr [esp + 4], xmm0
        fld qword ptr [esp + 4]
        add esp, 10h
        ret

    L_return_input:
        movlpd xmm3, qword ptr [DAT_10025850 + 030h]
        mulsd xmm3, xmm0
        subsd xmm3, xmm0
        mulsd xmm3, qword ptr [DAT_10025850 + 038h]
        movlpd qword ptr [esp + 4], xmm0
        fld qword ptr [esp + 4]
        add esp, 10h
        ret

    L_exception:
        jmp FUN_1001b3cf
    }
}
