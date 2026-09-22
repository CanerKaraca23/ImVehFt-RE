#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
// Ghidra 12.1.3 instruction-for-instruction x86 reconstruction.
// The EH prolog receives its frame size on the stack and its scope-table
// address in EAX; a normal C++ call cannot express that custom entry ABI.
extern "C" void __cdecl __EH_prolog3_catch(void);
extern "C" void __cdecl __getptd(void);
extern "C" void __cdecl _inconsistency(void);
extern "C" void __stdcall FUN_10017e17(void);
extern "C" void __cdecl terminate(void);

extern "C" __declspec(naked) void __stdcall FUN_1001d026(void)
{
    __asm {
        push 4
        mov eax, 10020852h
        call __EH_prolog3_catch
        call __getptd
        cmp dword ptr [eax + 94h], 0
        jz no_inconsistency
        call _inconsistency
    no_inconsistency:
        and dword ptr [ebp - 4], 0
        call FUN_10017e17
        or dword ptr [ebp - 4], 0ffffffffh
        call terminate
    }
}