#include <cstdarg>

#include <cstddef>
#include <corecrt.h>
#include <cstdint>
using longlong = std::int64_t;
using uint = std::uint32_t;
using ulonglong = std::uint64_t;
using undefined = unsigned char;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined4 = std::uint32_t;
using undefined8 = std::uint64_t;
extern "C" int* __cdecl __errno(void);
struct _iobuf {
    char* _ptr;
    int _cnt;
    char* _base;
    int _flag;
    int _file;
    int _charbuf;
    int _bufsiz;
    char* _tmpfname;
};
using FILE = _iobuf;
static_assert(offsetof(_iobuf, _ptr) == 0x00);
static_assert(offsetof(_iobuf, _cnt) == 0x04);
static_assert(offsetof(_iobuf, _base) == 0x08);
static_assert(offsetof(_iobuf, _flag) == 0x0c);
static_assert(sizeof(_iobuf) == 0x20);
int* __cdecl __errno();
extern "C" void __stdcall FUN_1001189f();
int __cdecl __output_l(FILE*, char*, _locale_t, va_list*);
int __cdecl __flsbuf(int, FILE*);

int __cdecl _sprintf(char* _Dest, char* _Format, ...)
{
    int* piVar1;
    int iVar2;
    char** ppcVar3;
    FILE local_24;
    va_list argList;

    local_24._ptr = (char*)0x0;
    ppcVar3 = (char**)&local_24._cnt;

    for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1)
    {
        *ppcVar3 = (char*)0x0;
        ppcVar3 = ppcVar3 + 1;
    }

    if ((_Format == (char*)0x0) || (_Dest == (char*)0x0))
    {
        piVar1 = __errno();
        *piVar1 = 0x16;
        FUN_1001189f();
        iVar2 = -1;
    }
    else
    {
        local_24._base = _Dest;
        local_24._ptr = _Dest;
        local_24._cnt = 0x7fffffff;
        local_24._flag = 0x42;

        va_start(argList, _Format);
        iVar2 = __output_l(&local_24, _Format, (_locale_t)0x0, &argList);
        va_end(argList);

        local_24._cnt = local_24._cnt + -1;

        if (local_24._cnt < 0)
        {
            __flsbuf(0, &local_24);
        }
        else
        {
            *local_24._ptr = '\0';
        }
    }

    return iVar2;
}