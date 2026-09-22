#include <windows.h>

extern "C" void __cdecl ___crtCorExitProcess(int param_1);

extern "C" [[noreturn]] void __cdecl ___crtExitProcess(int param_1)
{
    ___crtCorExitProcess(param_1);
    ExitProcess(static_cast<UINT>(param_1));
}