#include <windows.h>

extern "C" void __cdecl ___crtCorExitProcess(int param_1)
{
    HMODULE hModule = GetModuleHandleW(L"mscoree.dll");

    if (hModule != nullptr)
    {
        FARPROC pFVar1 = GetProcAddress(hModule, "CorExitProcess");

        if (pFVar1 != nullptr)
        {
            reinterpret_cast<void (__stdcall*)(int)>(pFVar1)(param_1);
        }
    }
}