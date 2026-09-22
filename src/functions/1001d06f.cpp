#include <cstddef>
#include <cstdint>
#include <corecrt.h>
using byte = std::uint8_t;
#include <stdio.h>
#include <cstddef>
#include <cstdint>

extern "C" void __cdecl __SEH_prolog4();
extern "C" unsigned int* __cdecl __CreateFrameInfo(unsigned int*, unsigned int);
extern "C" void* __cdecl __getptd();
extern "C" void* __cdecl _CallCatchBlock2(void*, void*, void*, int, unsigned long);
extern "C" void __cdecl FrameUnwindToState_1001ce0c();
extern "C" void __stdcall FUN_1001d195();
extern "C" void __stdcall __SEH_epilog4();
extern "C" void __cdecl CallCatchBlock_filter_experiment();
extern "C" void __cdecl CallCatchBlock_catch_experiment();
extern "C" void __cdecl CallCatchBlock_cleanup_experiment();
extern "C" void __cdecl CallCatchBlock_normal_epilog_experiment();
extern "C" void __cdecl EHFilter_1001cee8_experiment();

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
    EH4ScopeRecord records[2];
};

static_assert(sizeof(void*) == 4);
static_assert(sizeof(EH4ScopeRecord) == 12);
static_assert(offsetof(EH4ScopeTable, records) == 0x10);
static_assert(sizeof(EH4ScopeTable) == 0x28);

extern "C" const EH4ScopeTable CallCatchBlock_scope_table_experiment = {
    -2, 0, -76, 0,
    {
        { -2, nullptr, &CallCatchBlock_cleanup_experiment },
        {  0, &CallCatchBlock_filter_experiment, &CallCatchBlock_catch_experiment },
    },
};

extern "C" __declspec(naked) void* __cdecl CallCatchBlock(
    void*, void*, void*, void*, void*, int, unsigned long)
{
    __asm {
        push 2Ch
        push offset CallCatchBlock_scope_table_experiment
        call __SEH_prolog4

        mov ebx, ecx
        mov edi, dword ptr [ebp + 0Ch]
        mov esi, dword ptr [ebp + 08h]
        mov dword ptr [ebp - 1Ch], ebx
        and dword ptr [ebp - 34h], 0
        mov eax, dword ptr [edi - 4]
        mov dword ptr [ebp - 24h], eax
        push dword ptr [esi + 18h]
        lea eax, [ebp - 3Ch]
        push eax
        call __CreateFrameInfo
        pop ecx
        pop ecx
        mov dword ptr [ebp - 28h], eax
        call __getptd
        mov eax, dword ptr [eax + 88h]
        mov dword ptr [ebp - 2Ch], eax
        call __getptd
        mov eax, dword ptr [eax + 8Ch]
        mov dword ptr [ebp - 30h], eax
        call __getptd
        mov dword ptr [eax + 88h], esi
        call __getptd
        mov ecx, dword ptr [ebp + 10h]
        mov dword ptr [eax + 8Ch], ecx
        and dword ptr [ebp - 4], 0
        xor eax, eax
        inc eax
        mov dword ptr [ebp + 10h], eax
        mov dword ptr [ebp - 4], eax
        push dword ptr [ebp + 1Ch]
        push dword ptr [ebp + 18h]
        push ebx
        push dword ptr [ebp + 14h]
        push edi
        call _CallCatchBlock2
        add esp, 14h
        mov dword ptr [ebp - 1Ch], eax
        and dword ptr [ebp - 4], 0
        jmp CallCatchBlock_normal_epilog_experiment
    }
}

extern "C" __declspec(naked) void __cdecl CallCatchBlock_filter_experiment()
{
    __asm {
        mov eax, dword ptr [ebp - 14h]
        call EHFilter_1001cee8_experiment
        ret
    }
}

extern "C" __declspec(naked) void __cdecl CallCatchBlock_catch_experiment()
{
    __asm {
        mov esp, dword ptr [ebp - 18h]
        call __getptd
        and dword ptr [eax + 20Ch], 0
        mov esi, dword ptr [ebp + 14h]
        mov edi, dword ptr [ebp + 0Ch]
        cmp dword ptr [esi + 4], 80h
        jg use_full_exception_code
        movsx ecx, byte ptr [edi + 8]
        jmp have_exception_code

    use_full_exception_code:
        mov ecx, dword ptr [edi + 8]

    have_exception_code:
        mov ebx, dword ptr [esi + 10h]
        and dword ptr [ebp - 20h], 0

    try_map_loop:
        mov eax, dword ptr [ebp - 20h]
        cmp eax, dword ptr [esi + 0Ch]
        jae frame_unwind
        imul eax, eax, 14h
        mov edx, dword ptr [eax + ebx + 4]
        cmp ecx, edx
        jle next_try_entry
        cmp ecx, dword ptr [eax + ebx + 8]
        jg next_try_entry
        mov eax, dword ptr [esi + 8]
        mov ecx, dword ptr [eax + edx*8 + 8]

    frame_unwind:
        push ecx
        push esi
        push 0
        push edi
        call FrameUnwindToState_1001ce0c
        add esp, 10h
        and dword ptr [ebp - 1Ch], 0
        and dword ptr [ebp - 4], 0
        mov esi, dword ptr [ebp + 8]
        jmp CallCatchBlock_normal_epilog_experiment

    next_try_entry:
        inc dword ptr [ebp - 20h]
        jmp try_map_loop
    }
}

extern "C" __declspec(naked) void __cdecl CallCatchBlock_cleanup_experiment()
{
    __asm {
        mov edi, dword ptr [ebp + 0Ch]
        mov esi, dword ptr [ebp + 8]
        jmp FUN_1001d195
    }
}

extern "C" __declspec(naked) void __cdecl CallCatchBlock_normal_epilog_experiment()
{
    __asm {
        mov dword ptr [ebp - 4], 0FFFFFFFEh
        mov dword ptr [ebp + 10h], 0
        call FUN_1001d195
        mov eax, dword ptr [ebp - 1Ch]
        call __SEH_epilog4
        ret
    }
}

extern "C" __declspec(naked) void __cdecl EHFilter_1001cee8_experiment()
{
    __asm {
        mov eax, dword ptr [eax]
        cmp dword ptr [eax], 0E06D7363h
        jne reject_exception
        cmp dword ptr [eax + 10h], 3
        jne reject_exception
        mov ecx, dword ptr [eax + 14h]
        cmp ecx, 19930520h
        je accept_exception
        cmp ecx, 19930521h
        je accept_exception
        cmp ecx, 19930522h
        jne reject_exception

    accept_exception:
        cmp dword ptr [eax + 1Ch], 0
        jne reject_exception
        call __getptd
        xor ecx, ecx
        inc ecx
        mov dword ptr [eax + 20Ch], ecx
        mov eax, ecx
        ret

    reject_exception:
        xor eax, eax
        ret
    }
}
