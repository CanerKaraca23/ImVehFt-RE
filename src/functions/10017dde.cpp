#include <cstdint>

extern "C" void* __cdecl __getptd(void);
extern "C" [[noreturn]] void __cdecl _abort(void);
extern "C" void __cdecl __SEH_prolog4(std::uint32_t scope_table, int frame_size);

using terminate_filter = int (__cdecl*)(void*);
using terminate_handler = void (__cdecl*)();

struct terminate_scope_table
{
    std::int32_t gs_cookie_offset;
    std::int32_t gs_cookie_xor_offset;
    std::int32_t eh_cookie_offset;
    std::int32_t eh_cookie_xor_offset;
    std::int32_t enclosing_level;
    terminate_filter filter;
    terminate_handler handler;
};

extern "C" __declspec(naked) int __cdecl terminate_scope_filter(void*)
{
    __asm
    {
        xor eax, eax
        inc eax
        ret
    }
}

extern "C" __declspec(naked) void __cdecl terminate_scope_handler()
{
    __asm
    {
        mov esp, dword ptr [ebp - 18h]
        mov dword ptr [ebp - 4], 0FFFFFFFEh
        call _abort
        int 3
    }
}

static const terminate_scope_table g_terminate_scope_table = {
    -2, 0, -40, 0, -2,
    &terminate_scope_filter,
    &terminate_scope_handler
};

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "terminate requires the MSVC x86 calling environment"
#endif

#pragma warning(disable: 4733)
[[noreturn]] __declspec(naked) void __cdecl terminate()
{
    __asm
    {
        push 8
        push offset g_terminate_scope_table
        call __SEH_prolog4

        call __getptd
        mov eax, dword ptr [eax + 78h]
        test eax, eax
        jz abort_without_state_update
        and dword ptr [ebp - 4], 0
        call eax

        mov dword ptr [ebp - 4], 0FFFFFFFEh

    abort_without_state_update:
        call _abort
        int 3
    }
}
