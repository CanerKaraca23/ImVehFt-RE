#include <cstdint>

extern "C" void __cdecl __SEH_prolog4();
extern "C" void __cdecl __SEH_epilog4();

extern "C" std::uint32_t* __cdecl ___doserrno();
extern "C" int* __cdecl __errno();
extern "C" void __stdcall FUN_1001189f();
extern "C" void __cdecl ___lock_fhandle(int _FileHandle);
extern "C" std::int64_t __cdecl __lseeki64_nolock(
    int _FileHandle,
    std::int64_t _Offset,
    int _Origin);
extern "C" void __stdcall FUN_1001a765();

extern "C" std::uint32_t DAT_1003c418;
extern "C" std::uint8_t* DAT_1003c420[];

extern "C" std::int64_t __cdecl __lseeki64(
    int _FileHandle,
    std::int64_t _Offset,
    int _Origin)
{
    __SEH_prolog4();

    std::int64_t local_28;

    if (_FileHandle == -2)
    {
        *___doserrno() = 0;
        *__errno() = 9;
        local_28 = -1;
    }
    else
    {
        if ((_FileHandle >= 0) &&
            (static_cast<std::uint32_t>(_FileHandle) < DAT_1003c418))
        {
            const int iVar3 = (_FileHandle & 0x1fU) * 0x40;

            if ((*(DAT_1003c420[_FileHandle >> 5] + 4 + iVar3) & 1) != 0)
            {
                ___lock_fhandle(_FileHandle);

                if ((*(DAT_1003c420[_FileHandle >> 5] + 4 + iVar3) & 1) == 0)
                {
                    *__errno() = 9;
                    *___doserrno() = 0;
                    local_28 = -1;
                }
                else
                {
                    local_28 =
                        __lseeki64_nolock(_FileHandle, _Offset, _Origin);
                }

                FUN_1001a765();
                __SEH_epilog4();
                return local_28;
            }
        }

        *___doserrno() = 0;
        *__errno() = 9;
        FUN_1001189f();
        local_28 = -1;
    }

    __SEH_epilog4();
    return local_28;
}