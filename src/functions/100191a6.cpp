#include <Windows.h>
#include <cstdint>

extern "C" std::uint8_t* DAT_1003c420[];

extern "C" void __cdecl __unlock_fhandle(int _Filehandle)
{
    LeaveCriticalSection(
        reinterpret_cast<LPCRITICAL_SECTION>(
            DAT_1003c420[_Filehandle >> 5] +
            0x0cU +
            (_Filehandle & 0x1fU) * 0x40U));
}