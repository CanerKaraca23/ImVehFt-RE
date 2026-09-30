#include <cstdint>

extern "C" __declspec(naked) std::uint64_t __stdcall __aulldvrm(
    std::uint32_t,
    std::uint32_t,
    std::uint32_t,
    std::uint32_t)
{
    __asm {
        push esi
        mov eax, dword ptr [esp + 14h]
        or eax, eax
        jnz divisor_nonzero
        mov ecx, dword ptr [esp + 10h]
        mov eax, dword ptr [esp + 0Ch]
        xor edx, edx
        div ecx
        mov ebx, eax
        mov eax, dword ptr [esp + 08h]
        div ecx
        mov esi, eax
        mov eax, ebx
        mul dword ptr [esp + 10h]
        mov ecx, eax
        mov eax, esi
        mul dword ptr [esp + 10h]
        add edx, ecx
        jmp quotient_ready

    divisor_nonzero:
        mov ecx, eax
        mov ebx, dword ptr [esp + 10h]
        mov edx, dword ptr [esp + 0Ch]
        mov eax, dword ptr [esp + 08h]
    normalize_divisor:
        shr ecx, 1
        rcr ebx, 1
        shr edx, 1
        rcr eax, 1
        or ecx, ecx
        jnz normalize_divisor
        div ebx
        mov esi, eax
        mul dword ptr [esp + 14h]
        mov ecx, eax
        mov eax, dword ptr [esp + 10h]
        mul esi
        add edx, ecx
        jc correct_quotient
        cmp edx, dword ptr [esp + 0Ch]
        ja correct_quotient
        jc quotient_remainder_ready
        cmp eax, dword ptr [esp + 08h]
        jbe quotient_remainder_ready

    correct_quotient:
        dec esi
        sub eax, dword ptr [esp + 10h]
        sbb edx, dword ptr [esp + 14h]

    quotient_remainder_ready:
        xor ebx, ebx

    quotient_ready:
        sub eax, dword ptr [esp + 08h]
        sbb edx, dword ptr [esp + 0Ch]
        neg edx
        neg eax
        sbb edx, 0
        mov ecx, edx
        mov edx, ebx
        mov ebx, ecx
        mov ecx, eax
        mov eax, esi
        pop esi
        ret 10h
    }
}
