#include <cstddef>
#include <windows.h>

extern "C" void __stdcall FUN_100172cd();
extern "C" void* __cdecl _memset(void*, int, std::size_t);

extern "C" void __cdecl __call_reportfault(
    int nDbgHookCode,
    DWORD dwExceptionCode,
    DWORD dwExceptionFlags)
{
    BOOL debuggerPresent;
    LONG filterResult;
    EXCEPTION_POINTERS exceptionPointers;
    EXCEPTION_RECORD exceptionRecord;
    DWORD contextMarker;

    if (nDbgHookCode != -1)
    {
        FUN_100172cd();
    }

    exceptionRecord.ExceptionCode = 0;
    _memset(&exceptionRecord.ExceptionFlags, 0, 0x4c);

    exceptionPointers.ExceptionRecord = &exceptionRecord;
    exceptionPointers.ContextRecord =
        reinterpret_cast<PCONTEXT>(&contextMarker);

    contextMarker = 0x10001;
    exceptionRecord.ExceptionCode = dwExceptionCode;
    exceptionRecord.ExceptionFlags = dwExceptionFlags;

    debuggerPresent = IsDebuggerPresent();
    SetUnhandledExceptionFilter(nullptr);
    filterResult = UnhandledExceptionFilter(&exceptionPointers);

    if (((filterResult == 0) && (debuggerPresent == 0)) &&
        (nDbgHookCode != -1))
    {
        FUN_100172cd();
    }

    // Compiler-injected __security_check_cookie call is emitted by MSVC
    // for the stack-protected function and is not represented as source logic.
}