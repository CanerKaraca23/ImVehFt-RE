#include <windows.h>
#include <cwchar>

#include <cstddef>
#include <corecrt.h>
#include <cstdint>
using longlong = std::int64_t;
using uint = std::uint32_t;
using ulonglong = std::uint64_t;
using undefined = unsigned char;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined4 = std::uint32_t;
using undefined8 = std::uint64_t;
extern "C" HANDLE DAT_10029f10;
extern "C" void __cdecl ___initconout();

extern "C" wint_t __cdecl __putwch_nolock(wchar_t _WCh)
{
    DWORD local_8;

    if (DAT_10029f10 == reinterpret_cast<HANDLE>(static_cast<std::intptr_t>(-2))) {
        ___initconout();
    }

    if (DAT_10029f10 != reinterpret_cast<HANDLE>(static_cast<std::intptr_t>(-1))) {
        if (WriteConsoleW(DAT_10029f10, &_WCh, 1, &local_8, nullptr) != FALSE) {
            return _WCh;
        }
    }

    return static_cast<wint_t>(0xffff);
}