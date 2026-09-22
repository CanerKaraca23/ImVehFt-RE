#include <cstdint>
#include <windows.h>

extern "C" intptr_t __cdecl __get_osfhandle(int file_handle);
extern "C" void __cdecl __free_osfhnd(int file_handle);
extern "C" void __cdecl __dosmaperr(unsigned long error_code);

extern std::uint8_t* DAT_1003c420;

extern "C" int __cdecl __close_nolock(int _FileHandle)
{
    intptr_t iVar1;
    intptr_t iVar2;
    HANDLE hObject;
    BOOL BVar3;
    DWORD DVar4 = 0;
    int iVar5;

    iVar1 = __get_osfhandle(_FileHandle);

    if (iVar1 != -1)
    {
        if (((_FileHandle == 1) &&
             ((*(std::uint8_t*)(DAT_1003c420 + 0x84) & 1U) != 0)) ||
            ((_FileHandle == 2) &&
             ((*(std::uint8_t*)(DAT_1003c420 + 0x44) & 1U) != 0)))
        {
            iVar1 = __get_osfhandle(2);
            iVar2 = __get_osfhandle(1);

            if (iVar2 == iVar1)
                goto close_complete;
        }

        hObject = reinterpret_cast<HANDLE>(__get_osfhandle(_FileHandle));
        BVar3 = CloseHandle(hObject);

        if (BVar3 == 0)
        {
            DVar4 = GetLastError();
            goto release_handle;
        }
    }

close_complete:
    DVar4 = 0;

release_handle:
    __free_osfhnd(_FileHandle);

    reinterpret_cast<std::uint8_t**>(&DAT_1003c420)[_FileHandle >> 5]
        [4 + (_FileHandle & 0x1fU) * 0x40] = 0;

    if (DVar4 == 0)
    {
        iVar5 = 0;
    }
    else
    {
        __dosmaperr(DVar4);
        iVar5 = -1;
    }

    return iVar5;
}