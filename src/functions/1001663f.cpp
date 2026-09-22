#include <cstdint>

extern "C" void __cdecl __SEH_prolog4();
extern "C" void __cdecl __SEH_epilog4();

extern "C" unsigned long* __cdecl ___doserrno();
extern "C" int* __cdecl __errno();
extern "C" void __cdecl ___lock_fhandle(int _FileHandle);
extern "C" int __cdecl __read_nolock(
    int _FileHandle,
    void* _DstBuf,
    unsigned int _MaxCharCount);
extern "C" void __stdcall FUN_1001189f();
extern "C" void __stdcall FUN_1001672d();

extern "C" unsigned int DAT_1003c418;
extern "C" unsigned char* DAT_1003c420[];

extern "C" int __cdecl __read(
    int _FileHandle,
    void* _DstBuf,
    unsigned int _MaxCharCount)
{
    __SEH_prolog4();

    if (_FileHandle == -2)
    {
        *___doserrno() = 0;
        *__errno() = 9;

        __SEH_epilog4();
        return -1;
    }

    if ((-1 < _FileHandle) &&
        (static_cast<unsigned int>(_FileHandle) < DAT_1003c418))
    {
        const int offset = (_FileHandle & 0x1fU) * 0x40;

        if ((*(DAT_1003c420[_FileHandle >> 5] + 4 + offset) & 1) != 0)
        {
            if (_MaxCharCount < 0x80000000U)
            {
                ___lock_fhandle(_FileHandle);

                int result;
                if ((*(DAT_1003c420[_FileHandle >> 5] + 4 + offset) & 1) == 0)
                {
                    *__errno() = 9;
                    *___doserrno() = 0;
                    result = -1;
                }
                else
                {
                    result = __read_nolock(
                        _FileHandle,
                        _DstBuf,
                        _MaxCharCount);
                }

                FUN_1001672d();
                __SEH_epilog4();
                return result;
            }

            *___doserrno() = 0;
            *__errno() = 0x16;
            goto LAB_1001668d;
        }
    }

    *___doserrno() = 0;
    *__errno() = 9;

LAB_1001668d:
    FUN_1001189f();

    __SEH_epilog4();
    return -1;
}