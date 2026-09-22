#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" errno_t __cdecl FID_conflict___sopen_helper(
    char* _Filename,
    int _OpenFlag,
    int _ShareFlag,
    int _PermissionMode,
    int* _FileHandle,
    int _BSecure);

extern "C" errno_t __cdecl __sopen_s(
    int* _FileHandle,
    char* _Filename,
    int _OpenFlag,
    int _ShareFlag,
    int _PermissionMode)
{
    errno_t eVar1 = FID_conflict___sopen_helper(
        _Filename,
        _OpenFlag,
        _ShareFlag,
        _PermissionMode,
        _FileHandle,
        1);

    return eVar1;
}