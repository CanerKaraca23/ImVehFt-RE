#include <cstddef>
#include <cstdint>

using EH4Funclet = void (__cdecl*)();
using errno_t = int;

struct EH4ScopeRecord
{
    std::int32_t enclosing_level;
    EH4Funclet filter;
    EH4Funclet handler;
};

struct EH4ScopeTable
{
    std::int32_t gs_cookie_offset;
    std::int32_t gs_cookie_xor_offset;
    std::int32_t eh_cookie_offset;
    std::int32_t eh_cookie_xor_offset;
    EH4ScopeRecord record;
};

static_assert(sizeof(void*) == 4);
static_assert(sizeof(EH4ScopeRecord) == 12);
static_assert(offsetof(EH4ScopeTable, record) == 0x10);
static_assert(sizeof(EH4ScopeTable) == 0x1c);

extern "C" void __stdcall sopen_scope_cleanup_handler();
extern "C" void __stdcall FUN_10018a8b();
extern "C" int __cdecl __errno();
extern "C" void __stdcall FUN_1001189f();
extern "C" void __cdecl FUN_100182c1(
    std::uint32_t*, char*, std::uint32_t, int, std::uint8_t);
extern "C" void __stdcall __SEH_epilog4();
extern "C" void __cdecl __SEH_prolog4(std::uint32_t scope_table, int frame_size);

static const EH4ScopeTable sopen_scope_table = {
    -2, 0, -52, 0,
    { -2, nullptr, reinterpret_cast<EH4Funclet>(&sopen_scope_cleanup_handler) },
};

extern "C" __declspec(naked) void __stdcall sopen_scope_cleanup_handler()
{
    __asm {
        xor edi, edi
        mov esi, dword ptr [ebp+18h]
        jmp FUN_10018a8b
    }
}

extern "C" __declspec(naked) errno_t __cdecl FID_conflict___sopen_helper(
    char*, int, int, int, int*, int)
{
    __asm {
        push 14h
        push OFFSET sopen_scope_table
        call __SEH_prolog4
        xor edi, edi
        mov dword ptr [ebp-1Ch], edi
        xor eax, eax
        mov esi, dword ptr [ebp+18h]
        cmp esi, edi
        setnz al
        cmp eax, edi
        jnz sopen_filehandle_ready

    sopen_invalid:
        call __errno
        push 16h
        pop esi
        mov dword ptr [eax], esi
        call FUN_1001189f
        mov eax, esi
        jmp sopen_epilog

    sopen_filehandle_ready:
        or dword ptr [esi], 0FFFFFFFFh
        xor eax, eax
        cmp dword ptr [ebp+8], edi
        setnz al
        cmp eax, edi
        jz sopen_invalid
        cmp dword ptr [ebp+1Ch], edi
        jz sopen_attempt
        mov eax, dword ptr [ebp+14h]
        and eax, 0FFFFFE7Fh
        neg eax
        sbb eax, eax
        inc eax
        jz sopen_invalid

    sopen_attempt:
        mov dword ptr [ebp-4], edi
        push dword ptr [ebp+14h]
        push dword ptr [ebp+10h]
        push dword ptr [ebp+0Ch]
        push dword ptr [ebp+8]
        lea eax, [ebp-1Ch]
        push eax
        mov eax, esi
        call FUN_100182c1
        add esp, 14h
        mov dword ptr [ebp-20h], eax
        mov dword ptr [ebp-4], 0FFFFFFFEh
        call FUN_10018a8b
        mov eax, dword ptr [ebp-20h]
        cmp eax, edi
        jz sopen_epilog
        or dword ptr [esi], 0FFFFFFFFh

    sopen_epilog:
        call __SEH_epilog4
        ret
    }
}
