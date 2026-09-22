#include <cstdint>
#include <windows.h>

extern "C" intptr_t __cdecl __get_osfhandle(int _FileHandle);
extern "C" int* __cdecl __errno();
extern "C" void __cdecl __dosmaperr(unsigned long _Error);
extern "C" std::uint8_t* DAT_1003c420[];

extern "C" long __cdecl __lseek_nolock(
    int _FileHandle,
    long _Offset,
    int _Origin)
{
    HANDLE hFile;
    int* piVar2;
    DWORD DVar3;
    unsigned long uVar4;
    std::uint8_t* pbVar1;

    hFile = reinterpret_cast<HANDLE>(__get_osfhandle(_FileHandle));

    if (hFile == reinterpret_cast<HANDLE>(static_cast<std::uintptr_t>(0xffffffffu)))
    {
        piVar2 = __errno();
        *piVar2 = 9;
        DVar3 = 0xffffffffu;
    }
    else
    {
        DVar3 = ::SetFilePointer(
            hFile,
            static_cast<LONG>(_Offset),
            nullptr,
            static_cast<DWORD>(_Origin));

        if (DVar3 == 0xffffffffu)
        {
            uVar4 = static_cast<unsigned long>(::GetLastError());
        }
        else
        {
            uVar4 = 0;
        }

        if (uVar4 == 0)
        {
            pbVar1 =
                DAT_1003c420[_FileHandle >> 5] +
                4 +
                (_FileHandle & 0x1fU) * 0x40;

            *pbVar1 = *pbVar1 & 0xfd;
        }
        else
        {
            __dosmaperr(uVar4);
            DVar3 = 0xffffffffu;
        }
    }

    return static_cast<long>(DVar3);
}