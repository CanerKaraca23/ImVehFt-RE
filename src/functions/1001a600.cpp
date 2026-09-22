#include <cstdint>
#include <windows.h>

extern "C" intptr_t __cdecl __get_osfhandle(int _FileHandle);
extern "C" int* __cdecl __errno();
extern "C" void __cdecl __dosmaperr(unsigned long _Error);

extern "C" std::uint8_t* DAT_1003c420[];

extern "C" long long __cdecl __lseeki64_nolock(
    int _FileHandle,
    long long _Offset,
    int _Origin)
{
    LONG distance_high = static_cast<LONG>(
        static_cast<std::uint64_t>(_Offset) >> 32);

    const HANDLE hFile = reinterpret_cast<HANDLE>(
        __get_osfhandle(_FileHandle));

    DWORD result;

    if (hFile == reinterpret_cast<HANDLE>(
                     static_cast<std::intptr_t>(-1)))
    {
        *__errno() = 9;
        result = 0xffffffffu;
        distance_high = -1;
    }
    else
    {
        result = ::SetFilePointer(
            hFile,
            static_cast<LONG>(_Offset),
            &distance_high,
            static_cast<DWORD>(_Origin));

        if (result == 0xffffffffu)
        {
            const DWORD error = ::GetLastError();

            if (error != 0)
            {
                __dosmaperr(error);

                const std::uint64_t combined =
                    (static_cast<std::uint64_t>(
                         static_cast<std::uint32_t>(-1))
                     << 32) |
                    static_cast<std::uint32_t>(0xffffffffu);

                return static_cast<long long>(combined);
            }
        }

        std::uint8_t* const file_info =
            DAT_1003c420[_FileHandle >> 5] +
            4 +
            (_FileHandle & 0x1fU) * 0x40;

        *file_info = static_cast<std::uint8_t>(*file_info & 0xfdU);
    }

    const std::uint64_t combined =
        (static_cast<std::uint64_t>(
             static_cast<std::uint32_t>(distance_high))
         << 32) |
        static_cast<std::uint32_t>(result);

    return static_cast<long long>(combined);
}