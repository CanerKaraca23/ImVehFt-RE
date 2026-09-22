#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" double DAT_10026170;
extern "C" double DAT_10026178;
extern "C" double DAT_10026180[2];
extern "C" double DAT_10026190;
extern "C" double DAT_10026198;
extern "C" double DAT_100261c0;
extern "C" double DAT_10026130[2];
extern "C" double DAT_10026140[2];
extern "C" double DAT_10026150[2];
extern "C" double DAT_10026160[2];
extern "C" void DAT_10025930(void);
extern "C" void FUN_1001b4ff(void);

extern "C" __declspec(naked) long double FUN_1001cb9e(void)
{
    __asm {
        pextrw eax, xmm0, 3
        and ax, 07fffh
        sub ax, 03030h
        cmp ax, 010c5h
        ja L_cb9e_overflow

        movlpd xmm1, qword ptr [DAT_10026170]
        mulsd xmm1, xmm0
        movlpd xmm2, qword ptr [DAT_10026178]
        cvtsd2si edx, xmm1
        addsd xmm1, xmm2
        movlpd xmm3, qword ptr [DAT_10026190]
        subsd xmm1, xmm2
        movapd xmm2, xmmword ptr [DAT_10026180]
        mulsd xmm3, xmm1
        unpcklpd xmm1, xmm1
        add edx, 01c7610h
        movsd xmm4, xmm0
        and edx, 03fh
        movapd xmm5, xmmword ptr [DAT_10026160]
        lea eax, DAT_10025930
        shl edx, 5
        add eax, edx
        mulpd xmm2, xmm1
        subsd xmm0, xmm3
        mulsd xmm1, qword ptr [DAT_10026198]
        subsd xmm4, xmm3
        movlpd xmm7, qword ptr [eax + 8]
        unpcklpd xmm0, xmm0
        movsd xmm3, xmm4
        subsd xmm4, xmm2
        mulpd xmm5, xmm0
        subpd xmm0, xmm2
        movapd xmm6, xmmword ptr [DAT_10026140]
        mulsd xmm7, xmm4
        subsd xmm3, xmm4
        mulpd xmm5, xmm0
        mulpd xmm0, xmm0
        subsd xmm3, xmm2
        movapd xmm2, xmmword ptr [eax]
        subsd xmm1, xmm3
        movlpd xmm3, qword ptr [eax + 18h]
        addsd xmm2, xmm3
        subsd xmm7, xmm2
        mulsd xmm2, xmm4
        mulpd xmm6, xmm0
        mulsd xmm3, xmm4
        mulpd xmm2, xmm0
        mulpd xmm0, xmm0
        addpd xmm5, xmmword ptr [DAT_10026150]
        mulsd xmm4, qword ptr [eax]
        addpd xmm6, xmmword ptr [DAT_10026130]
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
        addsd xmm1, qword ptr [eax + 10h]
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

    L_cb9e_overflow:
        jg L_cb9e_fallback
        pextrw eax, xmm0, 3
        and ax, 07fffh
        pinsrw xmm0, eax, 3
        sub esp, 10h
        movlpd xmm1, qword ptr [DAT_100261c0]
        subsd xmm1, xmm0
        movlpd qword ptr [esp + 4], xmm1
        fld qword ptr [esp + 4]
        add esp, 10h
        ret

    L_cb9e_fallback:
        jmp FUN_1001b4ff
    }
}
