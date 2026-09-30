#include "imvehft_image_aliases.hpp"
#include <cstdint>

extern "C" void __cdecl __SEH_prolog4(std::uint32_t scope_table, int frame_size);
extern "C" void __stdcall __SEH_epilog4();
extern "C" std::int32_t __stdcall __CRT_INIT_12(
    std::uint32_t,
    std::int32_t,
    std::int32_t);
extern "C" std::int32_t __stdcall FUN_10001db0(
    std::uint32_t,
    std::int32_t,
    std::uint32_t);

#pragma comment(linker, "/alternatename:@___DllMainCRTStartup@12=@___DllMainCRTStartup@8")

extern "C" __declspec(naked) std::int32_t __fastcall ___DllMainCRTStartup(
    std::int32_t,
    std::int32_t)
{
    __asm {
        push 0Ch
        push OFFSET IVF_RELOC_TARGET_100282A8
        call __SEH_prolog4
        mov edi, ecx
        mov esi, edx
        mov ebx, dword ptr [ebp + 8]
        xor eax, eax
        inc eax
        mov dword ptr [ebp - 1Ch], eax
        test esi, esi
        jnz dllmain_not_detach
        cmp dword ptr [IVF_RELOC_TARGET_100399F0], edx
        jz dllmain_return_false
    dllmain_not_detach:
        and dword ptr [ebp - 4], 0
        cmp esi, eax
        jz dllmain_attach
        cmp esi, 2
        jnz dllmain_call_user
    dllmain_attach:
        mov eax, dword ptr [IVF_RELOC_TARGET_10022268]
        test eax, eax
        jz dllmain_check_crt
        push edi
        push esi
        push ebx
        call eax
        mov dword ptr [ebp - 1Ch], eax
    dllmain_check_crt:
        cmp dword ptr [ebp - 1Ch], 0
        jz dllmain_cleanup_false
        push edi
        push esi
        push ebx
        call __CRT_INIT_12
        mov dword ptr [ebp - 1Ch], eax
        test eax, eax
        jz dllmain_cleanup_false
    dllmain_call_user:
        push edi
        push esi
        push ebx
        call FUN_10001db0
        mov dword ptr [ebp - 1Ch], eax
        cmp esi, 1
        jnz dllmain_detach_check
        test eax, eax
        jnz dllmain_detach_check
        push edi
        push eax
        push ebx
        call FUN_10001db0
        push edi
        push 0
        push ebx
        call __CRT_INIT_12
        mov eax, dword ptr [IVF_RELOC_TARGET_10022268]
        test eax, eax
        jz dllmain_detach_check
        push edi
        push 0
        push ebx
        call eax
    dllmain_detach_check:
        test esi, esi
        jz dllmain_call_crt_term
        cmp esi, 3
        jnz dllmain_success
    dllmain_call_crt_term:
        push edi
        push esi
        push ebx
        call __CRT_INIT_12
        test eax, eax
        jnz dllmain_check_user_term
        and dword ptr [ebp - 1Ch], eax
    dllmain_check_user_term:
        cmp dword ptr [ebp - 1Ch], 0
        jz dllmain_success
        mov eax, dword ptr [IVF_RELOC_TARGET_10022268]
        test eax, eax
        jz dllmain_success
        push edi
        push esi
        push ebx
        call eax
        mov dword ptr [ebp - 1Ch], eax
    dllmain_success:
        mov dword ptr [ebp - 4], 0FFFFFFFEh
        mov eax, dword ptr [ebp - 1Ch]
        jmp dllmain_epilog
    dllmain_cleanup_false:
        mov dword ptr [ebp - 4], 0FFFFFFFEh
    dllmain_return_false:
        xor eax, eax
    dllmain_epilog:
        call __SEH_epilog4
        ret
    }
}
