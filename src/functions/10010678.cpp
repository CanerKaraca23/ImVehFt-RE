#include <cstddef>
#include <cstdint>
#include <cstdio>

using EH4Funclet = void (__cdecl*)();

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

extern "C" void __stdcall FUN_1001072a();
extern "C" int* __cdecl __errno();
extern "C" void __stdcall FUN_1001189f();
FILE* __cdecl __getstream();
FILE* __cdecl __openfile(
    char*, char*, int, FILE*);
extern "C" void __cdecl __local_unwind4(
    void*, int, int);
extern "C" void __stdcall __SEH_epilog4();
extern "C" void __cdecl __SEH_prolog4(std::uint32_t scope_table, int frame_size);
extern std::uint32_t DAT_10029490;

static const EH4ScopeTable fsopen_scope_table = {
    -2, 0, -44, 0,
    { -2, nullptr, reinterpret_cast<EH4Funclet>(&FUN_1001072a) },
};

__declspec(naked) FILE* __cdecl __fsopen(char*, char*, int)
{
    __asm {
        push 0Ch
        push OFFSET fsopen_scope_table
        call __SEH_prolog4
        xor ebx, ebx
        mov dword ptr [ebp-1Ch], ebx
        xor eax, eax
        mov edi, dword ptr [ebp+8]
        cmp edi, ebx
        setnz al
        cmp eax, ebx
        jnz fsopen_mode_check

    fsopen_invalid:
        call __errno
        mov dword ptr [eax], 16h
        call FUN_1001189f
        xor eax, eax
        jmp fsopen_epilog

    fsopen_mode_check:
        xor eax, eax
        mov esi, dword ptr [ebp+0Ch]
        cmp esi, ebx
        setnz al
        cmp eax, ebx
        jz fsopen_invalid
        xor eax, eax
        cmp byte ptr [esi], bl
        setnz al
        cmp eax, ebx
        jz fsopen_invalid
        call __getstream
        mov dword ptr [ebp+8], eax
        cmp eax, ebx
        jnz fsopen_stream_ready
        call __errno
        mov dword ptr [eax], 18h
        xor eax, eax
        jmp fsopen_epilog

    fsopen_stream_ready:
        mov dword ptr [ebp-4], ebx
        cmp byte ptr [edi], bl
        jnz fsopen_open
        call __errno
        mov dword ptr [eax], 16h
        push -2
        lea eax, [ebp-10h]
        push eax
        push OFFSET DAT_10029490
        call __local_unwind4
        add esp, 0Ch
        xor eax, eax
        jmp fsopen_epilog

    fsopen_open:
        push eax
        push dword ptr [ebp+10h]
        push esi
        push edi
        call __openfile
        add esp, 10h
        mov dword ptr [ebp-1Ch], eax
        mov dword ptr [ebp-4], 0FFFFFFFEh
        call FUN_1001072a
        mov eax, dword ptr [ebp-1Ch]

    fsopen_epilog:
        call __SEH_epilog4
        ret
    }
}
