#include <cstdint>
#include <windows.h>

extern "C" void __cdecl __SEH_prolog4(...);
extern "C" void __stdcall __SEH_epilog4();

extern "C" int* __cdecl __errno();
extern "C" unsigned long* __cdecl ___doserrno();
extern "C" void __stdcall FUN_1001189f();
extern "C" void __cdecl ___lock_fhandle(int _FileHandle);
extern "C" intptr_t __cdecl __get_osfhandle(int _FileHandle);
extern "C" void __stdcall FUN_10019c08();

extern "C" std::uint32_t DAT_1003c418;
extern "C" std::uint8_t* DAT_1003c420[];

extern "C" int __cdecl __commit(int _FileHandle)
{
    __SEH_prolog4();

    int* piVar1;
    HANDLE hFile;
    BOOL BVar2;
    unsigned long* puVar3;
    int iVar4;
    DWORD local_20;

    if (_FileHandle == -2) {
        piVar1 = __errno();
        *piVar1 = 9;
    }
    else {
        if ((-1 < _FileHandle) &&
            (static_cast<std::uint32_t>(_FileHandle) < DAT_1003c418)) {
            iVar4 = (_FileHandle & 0x1fU) * 0x40;

            if ((*(DAT_1003c420[_FileHandle >> 5] + iVar4 + 4) & 1) != 0) {
                ___lock_fhandle(_FileHandle);

                if ((*(DAT_1003c420[_FileHandle >> 5] + iVar4 + 4) & 1) != 0) {
                    hFile = reinterpret_cast<HANDLE>(
                        __get_osfhandle(_FileHandle));

                    BVar2 = FlushFileBuffers(hFile);

                    if (BVar2 == 0) {
                        local_20 = GetLastError();
                    }
                    else {
                        local_20 = 0;
                    }

                    if (local_20 == 0) {
                        FUN_10019c08();
                        __SEH_epilog4();
                        return static_cast<int>(local_20);
                    }

                    puVar3 = ___doserrno();
                    *puVar3 = local_20;
                }

                piVar1 = __errno();
                *piVar1 = 9;
                local_20 = 0xffffffff;

                FUN_10019c08();
                __SEH_epilog4();
                return static_cast<int>(local_20);
            }
        }

        piVar1 = __errno();
        *piVar1 = 9;
        FUN_1001189f();
    }

    __SEH_epilog4();
    return -1;
}