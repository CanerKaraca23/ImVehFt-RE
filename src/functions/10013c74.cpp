#include <cstdint>

extern std::uint32_t DAT_1003c418;
extern std::uint8_t* DAT_1003c420;

extern "C" unsigned long* __cdecl ___doserrno();
extern "C" int* __cdecl __errno();
extern "C" void __stdcall FUN_1001189f();
extern "C" void __cdecl ___lock_fhandle(int _FileHandle);
extern "C" int __cdecl __close_nolock(int _FileHandle);
extern "C" void __stdcall FUN_10013d30();

extern "C" int __cdecl __close(int _FileHandle)
{
    unsigned long* puVar1;
    int* piVar2;
    int iVar3;
    int local_20;

    if (_FileHandle == -2)
    {
        puVar1 = ___doserrno();
        *puVar1 = 0;

        piVar2 = __errno();
        *piVar2 = 9;
    }
    else
    {
        if ((-1 < _FileHandle) &&
            (static_cast<std::uint32_t>(_FileHandle) < DAT_1003c418))
        {
            iVar3 = (_FileHandle & 0x1fU) * 0x40;

            if ((*(reinterpret_cast<std::uint8_t**>(&DAT_1003c420)[_FileHandle >> 5]
                    + 4 + iVar3) & 1U) != 0)
            {
                ___lock_fhandle(_FileHandle);

                if ((*(reinterpret_cast<std::uint8_t**>(&DAT_1003c420)[_FileHandle >> 5]
                        + 4 + iVar3) & 1U) == 0)
                {
                    piVar2 = __errno();
                    *piVar2 = 9;
                    local_20 = -1;
                }
                else
                {
                    local_20 = __close_nolock(_FileHandle);
                }

                FUN_10013d30();
                return local_20;
            }
        }

        puVar1 = ___doserrno();
        *puVar1 = 0;

        piVar2 = __errno();
        *piVar2 = 9;

        FUN_1001189f();
    }

    return -1;
}