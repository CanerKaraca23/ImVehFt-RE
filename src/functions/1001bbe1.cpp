extern "C" __declspec(naked) int __cdecl __positive(double*)
{
    __asm {
        mov edi, edi
        push ebp
        mov ebp, esp
        fldz
        mov eax, dword ptr [ebp + 8]
        fcomp qword ptr [eax]
        fnstsw ax
        test ah, 41h
        jp not_positive
        xor eax, eax
        inc eax
        pop ebp
        ret
    not_positive:
        xor eax, eax
        pop ebp
        ret
    }
}
