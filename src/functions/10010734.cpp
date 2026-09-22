#include <cstdio>

extern FILE* __cdecl __fsopen(char* _Filename, char* _Mode, int _ShFlag);

FILE* __cdecl fopen(char* _Filename, char* _Mode)
{
    FILE* pFVar1 = __fsopen(_Filename, _Mode, 0x40);
    return pFVar1;
}