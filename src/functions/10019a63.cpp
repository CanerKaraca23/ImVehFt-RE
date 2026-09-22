#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" unsigned long* __cdecl ___doserrno();
extern "C" int* __cdecl __errno();
extern "C" void __stdcall FUN_1001189f();
extern "C" void __cdecl ___lock_fhandle(int _FileHandle);
extern "C" int __cdecl __write_nolock(
    int _FileHandle,
    void* _Buf,
    unsigned int _MaxCharCount);
extern "C" void __stdcall FUN_10019b2f();

extern "C" unsigned int DAT_1003c418;
extern "C" unsigned char* DAT_1003c420[];

extern "C" int __cdecl __write(
    int _FileHandle,
    void* _Buf,
    unsigned int _MaxCharCount)
{
    unsigned long* puVar1;
    int* piVar2;
    int iVar3;
    int local_20;

    if (_FileHandle == -2) {
        puVar1 = ___doserrno();
        *puVar1 = 0;
        piVar2 = __errno();
        *piVar2 = 9;
    }
    else {
        if ((-1 < _FileHandle) &&
            ((unsigned int)_FileHandle < DAT_1003c418)) {
            iVar3 = (_FileHandle & 0x1fU) * 0x40;

            if ((*(unsigned char*)(
                     DAT_1003c420[_FileHandle >> 5] + 4 + iVar3) & 1) != 0) {
                ___lock_fhandle(_FileHandle);

                if ((*(unsigned char*)(
                         DAT_1003c420[_FileHandle >> 5] + 4 + iVar3) & 1) == 0) {
                    piVar2 = __errno();
                    *piVar2 = 9;
                    puVar1 = ___doserrno();
                    *puVar1 = 0;
                    local_20 = -1;
                }
                else {
                    local_20 = __write_nolock(
                        _FileHandle,
                        _Buf,
                        _MaxCharCount);
                }

                FUN_10019b2f();
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