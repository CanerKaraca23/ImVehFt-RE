#include <cstdint>

using HANDLE = void*;
using UINT = std::uint32_t;
using DWORD = std::uint32_t;

extern "C" void __cdecl __call_reportfault(
    int nDbgHookCode,
    DWORD dwExceptionCode,
    DWORD dwExceptionFlags);

extern "C" HANDLE __stdcall GetCurrentProcess();

extern "C" int __stdcall TerminateProcess(
    HANDLE hProcess,
    UINT uExitCode);

void __cdecl __invoke_watson(
    wchar_t* ,
    wchar_t* ,
    wchar_t* ,
    std::uint32_t ,
    std::uintptr_t )
{
    HANDLE hProcess;
    UINT uExitCode;

    __call_reportfault(2, 0xC0000417u, 1);

    uExitCode = 0xC0000417u;
    hProcess = GetCurrentProcess();
    TerminateProcess(hProcess, uExitCode);
    return;
}