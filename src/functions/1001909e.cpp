#include <cstdint>

extern "C" std::uint32_t DAT_1003c418;
extern "C" std::uint8_t* DAT_1003c420[];

extern "C" int* __cdecl __errno();
extern "C" unsigned long* __cdecl ___doserrno();
extern "C" void __stdcall FUN_1001189f();

extern "C" std::intptr_t __cdecl __get_osfhandle(int _FileHandle)
{
    if (_FileHandle == -2)
    {
        *___doserrno() = 0;
        *__errno() = 9;
    }
    else
    {
        if ((_FileHandle >= 0) &&
            (static_cast<std::uint32_t>(_FileHandle) < DAT_1003c418))
        {
            const std::uint32_t offset =
                (static_cast<std::uint32_t>(_FileHandle) & 0x1fU) * 0x40U;

            std::uint8_t* base = DAT_1003c420[_FileHandle >> 5];

            if ((*(base + 4U + offset) & 1U) != 0U)
            {
                return *reinterpret_cast<std::intptr_t*>(base + offset);
            }
        }

        *___doserrno() = 0;
        *__errno() = 9;
        FUN_1001189f();
    }

    return -1;
}