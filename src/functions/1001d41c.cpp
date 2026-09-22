#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>

extern "C" void __cdecl ___BuildCatchObject(int, int*, std::uint32_t*, std::uint8_t*);
extern "C" void __cdecl __SEH_prolog4(unsigned int, int);
extern "C" void __stdcall __SEH_epilog4(void);
extern "C" std::uint32_t* __cdecl __CreateFrameInfo(std::uint32_t*, std::uint32_t);
struct _tiddata;
extern "C" _tiddata* __cdecl __getptd(void);
extern "C" void* __cdecl _CallCatchBlock2(void*, void*, void*, int, unsigned long);
extern "C" void __stdcall FUN_1001d195(void);
extern "C" void __stdcall _UnwindNestedFrames(void*, void*);
extern "C" void __cdecl ___FrameUnwindToState(int, void*, int, int);
extern "C" void* __cdecl CallCatchBlock();
extern "C" void __stdcall _JumpToContinuation(void*, void*);

extern "C" __declspec(naked) void __cdecl CatchIt()
{
    __asm {
        mov edi, edi
        push ebp
        mov ebp, esp
        cmp dword ptr [ebp + 18h], 0
        je catchit_no_build
        push dword ptr [ebp + 18h]
        push ebx
        push esi
        push dword ptr [ebp + 8]
        call ___BuildCatchObject
        add esp, 10h
    catchit_no_build:
        cmp dword ptr [ebp + 20h], 0
        jne catchit_has_catchable
        push esi
        jmp catchit_unwind_nested
    catchit_has_catchable:
        push dword ptr [ebp + 20h]
    catchit_unwind_nested:
        push dword ptr [ebp + 8]
        call _UnwindNestedFrames
        push dword ptr [edi]
        push dword ptr [ebp + 14h]
        push dword ptr [ebp + 10h]
        push esi
        call ___FrameUnwindToState
        mov eax, dword ptr [edi + 4]
        push 100h
        inc eax
        push dword ptr [ebp + 1Ch]
        push dword ptr [ebp + 14h]
        mov dword ptr [esi + 8], eax
        push dword ptr [ebp + 0Ch]
        mov ecx, dword ptr [ebx + 0Ch]
        push esi
        push dword ptr [ebp + 8]
        call CallCatchBlock
        add esp, 28h
        test eax, eax
        je catchit_done
        push esi
        push eax
        call _JumpToContinuation
    catchit_done:
        pop ebp
        ret
    }
}

