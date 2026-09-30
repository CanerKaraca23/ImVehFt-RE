#include <cstdint>

extern "C" void __cdecl __unlock_fhandle(int _Filehandle);

extern "C" __declspec(naked) void __stdcall FUN_1001a765(void)
{
    __asm {
        push dword ptr [ebp + 8]
        call __unlock_fhandle
        pop ecx
        ret
    }
}
