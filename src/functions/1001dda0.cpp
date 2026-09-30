#include <cstdint>

extern "C" __declspec(naked) std::uint64_t __stdcall __alldvrm(
    std::uint32_t,
    std::uint32_t,
    std::uint32_t,
    std::uint32_t)
{
    __asm {
        push edi
        push esi
        push ebp
        xor edi, edi
        xor ebp, ebp
        mov eax, dword ptr [esp + 14h]
        or eax, eax
        jge dividend_nonnegative
        inc edi
        inc ebp
        mov edx, dword ptr [esp + 10h]
        neg eax
        neg edx
        sbb eax, 0
        mov dword ptr [esp + 14h], eax
        mov dword ptr [esp + 10h], edx

    dividend_nonnegative:
        mov eax, dword ptr [esp + 1Ch]
        or eax, eax
        jge divisor_nonnegative
        inc edi
        mov edx, dword ptr [esp + 18h]
        neg eax
        neg edx
        sbb eax, 0
        mov dword ptr [esp + 1Ch], eax
        mov dword ptr [esp + 18h], edx

    divisor_nonnegative:
        or eax, eax
        jnz signed_divisor_nonzero
        mov ecx, dword ptr [esp + 18h]
        mov eax, dword ptr [esp + 14h]
        xor edx, edx
        div ecx
        mov ebx, eax
        mov eax, dword ptr [esp + 10h]
        div ecx
        mov esi, eax
        mov eax, ebx
        mul dword ptr [esp + 18h]
        mov ecx, eax
        mov eax, esi
        mul dword ptr [esp + 18h]
        add edx, ecx
        jmp signed_quotient_ready

    signed_divisor_nonzero:
        mov ebx, eax
        mov ecx, dword ptr [esp + 18h]
        mov edx, dword ptr [esp + 14h]
        mov eax, dword ptr [esp + 10h]
    normalize_signed_divisor:
        shr ebx, 1
        rcr ecx, 1
        shr edx, 1
        rcr eax, 1
        or ebx, ebx
        jnz normalize_signed_divisor
        div ecx
        mov esi, eax
        mul dword ptr [esp + 1Ch]
        mov ecx, eax
        mov eax, dword ptr [esp + 18h]
        mul esi
        add edx, ecx
        jc correct_signed_quotient
        cmp edx, dword ptr [esp + 14h]
        ja correct_signed_quotient
        jc signed_quotient_remainder_ready
        cmp eax, dword ptr [esp + 10h]
        jbe signed_quotient_remainder_ready

    correct_signed_quotient:
        dec esi
        sub eax, dword ptr [esp + 18h]
        sbb edx, dword ptr [esp + 1Ch]

    signed_quotient_remainder_ready:
        xor ebx, ebx

    signed_quotient_ready:
        sub eax, dword ptr [esp + 10h]
        sbb edx, dword ptr [esp + 14h]
        dec ebp
        jns remainder_nonnegative
        neg edx
        neg eax
        sbb edx, 0

    remainder_nonnegative:
        mov ecx, edx
        mov edx, ebx
        mov ebx, ecx
        mov ecx, eax
        mov eax, esi
        dec edi
        jnz quotient_nonnegative
        neg edx
        neg eax
        sbb edx, 0

    quotient_nonnegative:
        pop ebp
        pop esi
        pop edi
        ret 10h
    }
}
