#include "imvehft_image_aliases.hpp"
#include <cstdint>

extern "C" {
    void __cdecl __SEH_prolog4(std::uint32_t scope_table, int frame_size);
    void __stdcall __SEH_epilog4(void);
    int __cdecl __heap_init(void);
    int __cdecl __mtinit(void);
    void __stdcall __RTC_Initialize(void);
    char* __cdecl ___crtGetEnvironmentStringsA(void);
    int __cdecl __ioinit(void);
    int __cdecl __setargv(void);
    int __stdcall FUN_100168fe(void);
    int __cdecl __cinit(int);
    void __cdecl __ioterm(void);
    void __cdecl __mtterm(void);
    void __cdecl __heap_term(void);
    void __cdecl __cexit(void);
    void __stdcall FUN_10011032(void);
    void* __stdcall ___set_flsgetvalue(void);
    void* __cdecl __calloc_crt(std::uint32_t, std::uint32_t);
    void __cdecl __initptd(void*, void*);
    void __cdecl _free(void*);
    void __cdecl __freeptd(void*);
}

extern "C" __declspec(naked) std::uint32_t __stdcall __CRT_INIT_12(
    std::uint32_t,
    int,
    int)
{
    __asm {
        push 8
        push OFFSET IVF_RELOC_TARGET_10028288
        call __SEH_prolog4
        mov eax, dword ptr [ebp + 0Ch]
        cmp eax, 1
        jne crt_non_attach
        call __heap_init
        test eax, eax
        jne crt_heap_initialized
    crt_return_false:
        xor eax, eax
        jmp crt_epilog
    crt_heap_initialized:
        call __mtinit
        test eax, eax
        jne crt_runtime_ready
    crt_heap_cleanup:
        call __heap_term
        jmp crt_return_false
    crt_runtime_ready:
        call __RTC_Initialize
        call dword ptr [IVF_RELOC_TARGET_10022068]
        mov dword ptr [IVF_RELOC_TARGET_1003D558], eax
        call ___crtGetEnvironmentStringsA
        mov dword ptr [IVF_RELOC_TARGET_100399F4], eax
        call __ioinit
        test eax, eax
        jns crt_io_ready
    crt_mt_cleanup:
        call __mtterm
        jmp crt_heap_cleanup
    crt_io_ready:
        call __setargv
        test eax, eax
        js crt_init_cleanup
        call FUN_100168fe
        test eax, eax
        js crt_init_cleanup
        push 0
        call __cinit
        pop ecx
        test eax, eax
        jnz crt_init_cleanup
        inc dword ptr [IVF_RELOC_TARGET_100399F0]
        jmp crt_return_true
    crt_init_cleanup:
        call __ioterm
        jmp crt_mt_cleanup
    crt_non_attach:
        xor edi, edi
        cmp eax, edi
        jne crt_thread_event
        cmp dword ptr [IVF_RELOC_TARGET_100399F0], edi
        jle crt_return_false
        dec dword ptr [IVF_RELOC_TARGET_100399F0]
        mov dword ptr [ebp - 4], edi
        cmp dword ptr [IVF_RELOC_TARGET_10039A38], edi
        jne crt_detach_cleanup
        call __cexit
    crt_detach_cleanup:
        cmp dword ptr [ebp + 10h], edi
        jne crt_detach_finish
        call __ioterm
        call __mtterm
        call __heap_term
    crt_detach_finish:
        mov dword ptr [ebp - 4], 0FFFFFFFEh
        call FUN_10011032
        jmp crt_return_true
    crt_thread_event:
        cmp eax, 2
        jne crt_thread_detach
        call ___set_flsgetvalue
        push 214h
        push 1
        call __calloc_crt
        pop ecx
        pop ecx
        mov esi, eax
        cmp esi, edi
        je crt_return_false
        push esi
        push dword ptr [IVF_RELOC_TARGET_10029C0C]
        push dword ptr [IVF_RELOC_TARGET_10039A7C]
        call dword ptr [IVF_RELOC_TARGET_10022060]
        call eax
        test eax, eax
        je crt_free_thread_data
        push edi
        push esi
        call __initptd
        pop ecx
        pop ecx
        call dword ptr [IVF_RELOC_TARGET_10022064]
        mov dword ptr [esi], eax
        or dword ptr [esi + 4], 0FFFFFFFFh
        jmp crt_return_true
    crt_free_thread_data:
        push esi
        call _free
        pop ecx
        jmp crt_return_false
    crt_thread_detach:
        cmp eax, 3
        jne crt_return_true
        push edi
        call __freeptd
        pop ecx
    crt_return_true:
        xor eax, eax
        inc eax
    crt_epilog:
        call __SEH_epilog4
        ret 0Ch
    }
}
