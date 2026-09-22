#include <cstdint>

extern "C" int* __cdecl __errno(void);
extern "C" void __stdcall FUN_1001189f(void);

extern std::uint32_t DAT_1003c418;
extern char* DAT_1003c420[];

extern "C" int __cdecl __isatty(int _FileHandle)
{
    if (_FileHandle == -2)
    {
        int* piVar1 = __errno();
        *piVar1 = 9;
    }
    else
    {
        if ((_FileHandle >= 0) &&
            (static_cast<std::uint32_t>(_FileHandle) < DAT_1003c418))
        {
            return static_cast<int>(
                       *reinterpret_cast<char*>(
                           DAT_1003c420[_FileHandle >> 5] +
                           4 +
                           (_FileHandle & 0x1fU) * 0x40)) &
                   0x40;
        }

        int* piVar1 = __errno();
        *piVar1 = 9;
        FUN_1001189f();
    }

    return 0;
}