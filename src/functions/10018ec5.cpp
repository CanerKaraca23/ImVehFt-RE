#include <cstdint>

extern "C" void __stdcall __NLG_Notify(unsigned int);
extern "C" void __stdcall FUN_10018f94();
extern "C" void __fastcall __security_check_cookie(std::uintptr_t);
extern "C" std::uintptr_t DAT_10029490;
extern "C" void __cdecl __local_unwind2(int, unsigned int);

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "__local_unwind2 requires the MSVC x86 calling environment"
#endif

#pragma warning(disable: 4733)
extern "C" __declspec(naked) int __cdecl
ImVehFt_Recovered_ExceptionHandler_10018e80()
{
    __asm
    {
        mov ecx, dword ptr [esp + 4]
        test dword ptr [ecx + 4], 6
        mov eax, 1
        je handler_return

        mov eax, dword ptr [esp + 14h]
        mov ecx, dword ptr [eax - 4]
        xor ecx, eax
        call __security_check_cookie

        push ebp
        mov ebp, dword ptr [eax + 10h]
        mov edx, dword ptr [eax + 28h]
        push edx
        mov edx, dword ptr [eax + 24h]
        push edx
        call __local_unwind2
        add esp, 8
        pop ebp

        mov eax, dword ptr [esp + 8]
        mov edx, dword ptr [esp + 10h]
        mov dword ptr [edx], eax
        mov eax, 3

    handler_return:
        ret
    }
}

extern "C" __declspec(naked) void __cdecl
__local_unwind2(int, unsigned int)
{
    __asm
    {
        push ebx
        push esi
        push edi
        mov eax, dword ptr [esp + 10h]
        push ebp
        push eax
        push -2
        push offset ImVehFt_Recovered_ExceptionHandler_10018e80
        push dword ptr fs:[0]
        mov eax, dword ptr [DAT_10029490]
        xor eax, esp
        push eax
        lea eax, dword ptr [esp + 4]
        mov dword ptr fs:[0], eax

    unwind_loop:
        mov eax, dword ptr [esp + 28h]
        mov ebx, dword ptr [eax + 8]
        mov esi, dword ptr [eax + 0Ch]
        cmp esi, -1
        je unwind_done
        cmp dword ptr [esp + 2Ch], -1
        je process_unwind_entry
        cmp esi, dword ptr [esp + 2Ch]
        jbe unwind_done

    process_unwind_entry:
        lea esi, dword ptr [esi + esi*2]
        mov ecx, dword ptr [ebx + esi*4]
        mov dword ptr [esp + 0Ch], ecx
        mov dword ptr [eax + 0Ch], ecx
        cmp dword ptr [ebx + esi*4 + 4], 0
        jne unwind_next
        push 101h
        mov eax, dword ptr [ebx + esi*4 + 8]
        call __NLG_Notify
        mov eax, dword ptr [ebx + esi*4 + 8]
        call FUN_10018f94

    unwind_next:
        jmp unwind_loop

    unwind_done:
        mov ecx, dword ptr [esp + 4]
        mov dword ptr fs:[0], ecx
        add esp, 18h
        pop edi
        pop esi
        pop ebx
        ret
    }
}
