#include <cstdint>

using BOOL = int;
using DWORD = std::uint32_t;
using HANDLE = void*;

extern HANDLE DAT_10039b90;

extern "C" BOOL __stdcall HeapFree(
    HANDLE heap,
    DWORD flags,
    void* memory);

extern "C" int* __cdecl __errno();
extern "C" DWORD __stdcall GetLastError();
extern "C" int __cdecl __get_errno_from_oserr(DWORD error);

extern "C" void __cdecl _free(void* _Memory)
{
    if (_Memory != nullptr)
    {
        const BOOL result = HeapFree(DAT_10039b90, 0, _Memory);

        if (result == 0)
        {
            int* const errno_value = __errno();
            const DWORD os_error = GetLastError();
            const int errno_result = __get_errno_from_oserr(os_error);
            *errno_value = errno_result;
        }
    }
}