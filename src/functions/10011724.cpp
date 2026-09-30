#include <cstddef>
#include <cstdint>
#include <windows.h>

#pragma comment(linker, "/alternatename:_DAT_1002207C=__imp__IsDebuggerPresent@0")
#pragma comment(linker, "/alternatename:_DAT_10022078=__imp__SetUnhandledExceptionFilter@4")
#pragma comment(linker, "/alternatename:_DAT_10022074=__imp__UnhandledExceptionFilter@4")

extern "C" void __stdcall FUN_100172cd();
extern "C" void* __cdecl _memset(void*, int, std::size_t);
extern "C" std::uint32_t DAT_10029490;
extern "C" std::uint32_t DAT_1002207C;
extern "C" std::uint32_t DAT_10022078;
extern "C" std::uint32_t DAT_10022074;
extern "C" void __fastcall __security_check_cookie(std::uintptr_t);

extern "C" __declspec(naked) void __cdecl __call_reportfault(
    int,
    DWORD,
    DWORD)
{
    __asm {
        mov     edi, edi
        push    ebp
        mov     ebp, esp
        sub     esp, 328h
        mov     eax, dword ptr [DAT_10029490]
        xor     eax, ebp
        mov     dword ptr [ebp-4], eax
        push    ebx
        mov     ebx, dword ptr [ebp+8]
        push    edi
        cmp     ebx, -1
        jz      reportfault_skip_initial_hook
        push    ebx
        call    FUN_100172cd
        pop     ecx
reportfault_skip_initial_hook:
        and     dword ptr [ebp-320h], 0
        push    4Ch
        lea     eax, dword ptr [ebp-31Ch]
        push    0
        push    eax
        call    _memset
        lea     eax, dword ptr [ebp-320h]
        mov     dword ptr [ebp-328h], eax
        lea     eax, dword ptr [ebp-2D0h]
        add     esp, 0Ch
        mov     dword ptr [ebp-324h], eax
        mov     dword ptr [ebp-220h], eax
        mov     dword ptr [ebp-224h], ecx
        mov     dword ptr [ebp-228h], edx
        mov     dword ptr [ebp-22Ch], ebx
        mov     dword ptr [ebp-230h], esi
        mov     dword ptr [ebp-234h], edi
        mov     word ptr [ebp-208h], ss
        mov     word ptr [ebp-214h], cs
        mov     word ptr [ebp-238h], ds
        mov     word ptr [ebp-23Ch], es
        mov     word ptr [ebp-240h], fs
        mov     word ptr [ebp-244h], gs
        pushfd
        pop     dword ptr [ebp-210h]
        mov     eax, dword ptr [ebp+4]
        lea     ecx, dword ptr [ebp+4]
        mov     dword ptr [ebp-20Ch], ecx
        mov     dword ptr [ebp-2D0h], 10001h
        mov     dword ptr [ebp-218h], eax
        mov     ecx, dword ptr [ecx-4]
        mov     dword ptr [ebp-21Ch], ecx
        mov     ecx, dword ptr [ebp+0Ch]
        mov     dword ptr [ebp-320h], ecx
        mov     ecx, dword ptr [ebp+10h]
        mov     dword ptr [ebp-31Ch], ecx
        mov     dword ptr [ebp-314h], eax
        call    dword ptr [DAT_1002207C]
        push    0
        mov     edi, eax
        call    dword ptr [DAT_10022078]
        lea     eax, dword ptr [ebp-328h]
        push    eax
        call    dword ptr [DAT_10022074]
        test    eax, eax
        jnz     reportfault_after_filter
        test    edi, edi
        jnz     reportfault_after_filter
        cmp     ebx, -1
        jz      reportfault_after_filter
        push    ebx
        call    FUN_100172cd
        pop     ecx
reportfault_after_filter:
        mov     ecx, dword ptr [ebp-4]
        pop     edi
        xor     ecx, ebp
        pop     ebx
        call    __security_check_cookie
        leave
        ret
    }
}
