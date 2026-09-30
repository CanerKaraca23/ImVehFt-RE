#include <cstdio>

#pragma comment(linker, "/alternatename:?fopen@@YAPAU_iobuf@@PAD0@Z=_fopen")

extern FILE* __cdecl __fsopen(char* _Filename, char* _Mode, int _ShFlag);

extern "C" FILE* __cdecl fopen(const char* _Filename, const char* _Mode)
{
    FILE* pFVar1 = __fsopen(
        const_cast<char*>(_Filename),
        const_cast<char*>(_Mode),
        0x40);
    return pFVar1;
}
