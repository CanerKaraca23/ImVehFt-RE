#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <windows.h>
#include <stdio.h>
extern "C" DWORD DAT_10029490;
extern "C" DWORD DAT_10029494;

extern "C" void __cdecl ___security_init_cookie(void)
{
    DWORD DVar1;
    DWORD DVar2;
    DWORD DVar3;
    unsigned int uVar4;
    LARGE_INTEGER local_14;
    FILETIME local_c;

    local_c.dwLowDateTime = 0;
    local_c.dwHighDateTime = 0;

    if ((DAT_10029490 == 0xBB40E64E) ||
        ((DAT_10029490 & 0xFFFF0000) == 0))
    {
        GetSystemTimeAsFileTime(&local_c);

        uVar4 = local_c.dwHighDateTime ^ local_c.dwLowDateTime;
        DVar1 = GetCurrentProcessId();
        DVar2 = GetCurrentThreadId();
        DVar3 = GetTickCount();

        QueryPerformanceCounter(&local_14);

        DAT_10029490 =
            uVar4 ^
            DVar1 ^
            DVar2 ^
            DVar3 ^
            local_14.HighPart ^
            local_14.LowPart;

        if (DAT_10029490 == 0xBB40E64E)
        {
            DAT_10029490 = 0xBB40E64F;
        }
        else if ((DAT_10029490 & 0xFFFF0000) == 0)
        {
            DAT_10029490 =
                DAT_10029490 |
                ((DAT_10029490 | 0x4711) << 0x10);
        }
    }

    DAT_10029494 = ~DAT_10029490;
}