#include <cstdint>

#include <cstddef>
#include <corecrt.h>
using longlong = std::int64_t;
using uint = std::uint32_t;
using ulonglong = std::uint64_t;
using undefined = unsigned char;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined4 = std::uint32_t;
using undefined8 = std::uint64_t;
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
extern "C" void __cdecl __SEH_prolog4();
extern "C" int* __cdecl __errno();
extern "C" void __stdcall FUN_1001189f();
extern "C" void __cdecl __lock_file(FILE* _File);
extern "C" unsigned int __cdecl __fileno(FILE* _File);
extern "C" unsigned int __cdecl __filbuf(FILE* _File);
extern "C" void __stdcall FUN_10010670();
extern "C" void __cdecl __SEH_epilog4();

extern unsigned char DAT_10029450;
extern unsigned char* DAT_1003c420[];

char* __cdecl fgets(char* _Buf, int _MaxCount, FILE* _File)
{
    __SEH_prolog4();

    int* piVar1;
    unsigned int uVar2;
    unsigned char* puVar3;
    char* pcVar4;
    char* local_20 = _Buf;

    if ((((_Buf == nullptr) && (_MaxCount != 0)) ||
         (_MaxCount < 0)) ||
        (_File == nullptr))
    {
        piVar1 = __errno();
        *piVar1 = 0x16;
        FUN_1001189f();
    }
    else if (_MaxCount != 0)
    {
        __lock_file(_File);

        if ((_File->_flag & 0x40) == 0)
        {
            uVar2 = __fileno(_File);

            if ((uVar2 == 0xffffffff) || (uVar2 == 0xfffffffe))
            {
                puVar3 = &DAT_10029450;
            }
            else
            {
                puVar3 =
                    DAT_1003c420[static_cast<int>(uVar2) >> 5] +
                    ((uVar2 & 0x1f) * 0x40);
            }

            if ((puVar3[0x24] & 0x7f) == 0)
            {
                if ((uVar2 == 0xffffffff) || (uVar2 == 0xfffffffe))
                {
                    puVar3 = &DAT_10029450;
                }
                else
                {
                    puVar3 =
                        DAT_1003c420[static_cast<int>(uVar2) >> 5] +
                        ((uVar2 & 0x1f) * 0x40);
                }

                if ((puVar3[0x24] & 0x80) == 0)
                    goto LAB_10010618;
            }

            piVar1 = __errno();
            *piVar1 = 0x16;
            FUN_1001189f();
            local_20 = nullptr;
        }

    LAB_10010618:
        pcVar4 = _Buf;

        if (local_20 != nullptr)
        {
            do
            {
                _MaxCount = _MaxCount + -1;

                if (_MaxCount == 0)
                    break;

                piVar1 = &_File->_cnt;
                *piVar1 = *piVar1 + -1;

                if (*piVar1 < 0)
                {
                    uVar2 = __filbuf(_File);
                }
                else
                {
                    uVar2 = static_cast<unsigned int>(
                        static_cast<unsigned char>(*_File->_ptr));
                    _File->_ptr = _File->_ptr + 1;
                }

                if (uVar2 == 0xffffffff)
                {
                    if (pcVar4 == _Buf)
                    {
                        local_20 = nullptr;
                        goto LAB_10010658;
                    }

                    break;
                }

                *pcVar4 = static_cast<char>(uVar2);
                pcVar4 = pcVar4 + 1;
            }
            while (static_cast<char>(uVar2) != '\n');

            *pcVar4 = '\0';
        }

    LAB_10010658:
        FUN_10010670();
        __SEH_epilog4();
        return local_20;
    }

    __SEH_epilog4();
    return nullptr;
}