#include <cstddef>
#include <cstdint>
#include <corecrt.h>
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
using uint = std::uint32_t;
using longlong = std::int64_t;
using ulonglong = std::uint64_t;
using undefined = unsigned char;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined4 = std::uint32_t;
using undefined8 = std::uint64_t;
extern "C" int* __cdecl __errno(void);
extern "C" void __stdcall FUN_1001189f(void);
extern std::uint32_t DAT_1003a334;
extern std::uint32_t _DAT_10039a40;
extern "C" int __cdecl __mbsnbcmp(const unsigned char*, const unsigned char*, std::size_t);
extern "C" int __cdecl __mbsnbicmp(const unsigned char*, const unsigned char*, std::size_t);
extern "C" int __cdecl __sopen_s(int*, char*, int, int, int);

FILE* __cdecl __openfile(
    char* _Filename,
    char* _Mode,
    int _ShFlag,
    FILE* _File)
{
    char cVar1;
    bool bVar2;
    bool bVar3;
    bool bVar4;
    bool bVar5;
    unsigned char uVar6;
    int* piVar7;
    int iVar8;
    int eVar9;
    unsigned int _OpenFlag;
    char* pcVar10;
    unsigned char* puVar11;
    unsigned char* puVar12;
    unsigned int local_8;

    _OpenFlag = 0;
    bVar4 = false;
    bVar3 = false;
    bVar5 = false;

    for (pcVar10 = _Mode; *pcVar10 == ' '; pcVar10 = pcVar10 + 1)
    {
    }

    cVar1 = *pcVar10;

    if (cVar1 == 'a')
    {
        _OpenFlag = 0x109;
        goto LAB_10013613;
    }
    else
    {
        if (cVar1 != 'r')
        {
            if (cVar1 != 'w')
            {
                piVar7 = __errno();
                *piVar7 = 0x16;
                FUN_1001189f();
                return nullptr;
            }

            _OpenFlag = 0x301;

LAB_10013613:
            local_8 = DAT_1003a334 | 2;
        }
        else
        {
            local_8 = DAT_1003a334 | 1;
        }
    }

    bVar2 = true;
    puVar11 = reinterpret_cast<unsigned char*>(pcVar10 + 1);
    uVar6 = *puVar11;

    if (uVar6 != '\0')
    {
        do
        {
            if (!bVar2)
            {
                break;
            }

            if (static_cast<char>(uVar6) < 'T')
            {
                if (uVar6 == 'S')
                {
                    if (bVar3)
                    {
                        goto LAB_1001373d;
                    }

                    bVar3 = true;
                    _OpenFlag = _OpenFlag | 0x20;
                }
                else if (uVar6 != ' ')
                {
                    if (uVar6 == '+')
                    {
                        if ((_OpenFlag & 2) != 0)
                        {
                            goto LAB_1001373d;
                        }

                        _OpenFlag = _OpenFlag & 0xfffffffe | 2;
                        local_8 = local_8 & 0xfffffffc | 0x80;
                    }
                    else if (uVar6 == ',')
                    {
                        bVar5 = true;

LAB_1001373d:
                        bVar2 = false;
                    }
                    else if (uVar6 == 'D')
                    {
                        if ((_OpenFlag & 0x40) != 0)
                        {
                            goto LAB_1001373d;
                        }

                        _OpenFlag = _OpenFlag | 0x40;
                    }
                    else if (uVar6 == 'N')
                    {
                        _OpenFlag = _OpenFlag | 0x80;
                    }
                    else
                    {
                        if (uVar6 != 'R')
                        {
                            goto LAB_100137f2;
                        }

                        if (bVar3)
                        {
                            goto LAB_1001373d;
                        }

                        bVar3 = true;
                        _OpenFlag = _OpenFlag | 0x10;
                    }
                }
            }
            else if (uVar6 == 'T')
            {
                if ((_OpenFlag & 0x1000) != 0)
                {
                    goto LAB_1001373d;
                }

                _OpenFlag = _OpenFlag | 0x1000;
            }
            else if (uVar6 == 'b')
            {
                if ((_OpenFlag & 0xc000) != 0)
                {
                    goto LAB_1001373d;
                }

                _OpenFlag = _OpenFlag | 0x8000;
            }
            else if (uVar6 == 'c')
            {
                if (bVar4)
                {
                    goto LAB_1001373d;
                }

                local_8 = local_8 | 0x4000;
                bVar4 = true;
            }
            else if (uVar6 == 'n')
            {
                if (bVar4)
                {
                    goto LAB_1001373d;
                }

                local_8 = local_8 & 0xffffbfff;
                bVar4 = true;
            }
            else
            {
                if (uVar6 != 't')
                {
                    goto LAB_100137f2;
                }

                if ((_OpenFlag & 0xc000) != 0)
                {
                    goto LAB_1001373d;
                }

                _OpenFlag = _OpenFlag | 0x4000;
            }

            puVar11 = puVar11 + 1;
            uVar6 = *puVar11;
        }
        while (uVar6 != '\0');

        if (bVar5)
        {
            for (; *puVar11 == ' '; puVar11 = puVar11 + 1)
            {
            }

            iVar8 = __mbsnbcmp(
                reinterpret_cast<unsigned char*>(const_cast<char*>("ccs")),
                puVar11,
                3);

            if (iVar8 != 0)
            {
                goto LAB_100137f2;
            }

            puVar11 = puVar11 + 3;

            for (; *puVar11 == ' '; puVar11 = puVar11 + 1)
            {
            }

            if (*puVar11 != '=')
            {
                goto LAB_100137f2;
            }

            do
            {
                puVar12 = puVar11;
                puVar11 = puVar12 + 1;
            }
            while (*puVar11 == ' ');

            iVar8 = __mbsnbicmp(
                puVar11,
                reinterpret_cast<unsigned char*>(
                    const_cast<char*>("UTF-8")),
                5);

            if (iVar8 == 0)
            {
                puVar11 = puVar12 + 6;
                _OpenFlag = _OpenFlag | 0x40000;
            }
            else
            {
                iVar8 = __mbsnbicmp(
                    puVar11,
                    reinterpret_cast<unsigned char*>(
                        const_cast<char*>("UTF-16LE")),
                    8);

                if (iVar8 == 0)
                {
                    puVar11 = puVar12 + 9;
                    _OpenFlag = _OpenFlag | 0x20000;
                }
                else
                {
                    iVar8 = __mbsnbicmp(
                        puVar11,
                        reinterpret_cast<unsigned char*>(
                            const_cast<char*>("UNICODE")),
                        7);

                    if (iVar8 != 0)
                    {
                        goto LAB_100137f2;
                    }

                    puVar11 = puVar12 + 8;
                    _OpenFlag = _OpenFlag | 0x10000;
                }
            }
        }
    }

    for (; *puVar11 == ' '; puVar11 = puVar11 + 1)
    {
    }

    if (*puVar11 == '\0')
    {
        eVar9 = __sopen_s(
            reinterpret_cast<int*>(&_Mode),
            _Filename,
            _OpenFlag,
            _ShFlag,
            0x180);

        if (eVar9 != 0)
        {
            return nullptr;
        }

        _DAT_10039a40 = _DAT_10039a40 + 1;
        _File->_flag = local_8;
        _File->_cnt = 0;
        _File->_ptr = nullptr;
        _File->_base = nullptr;
        _File->_tmpfname = nullptr;
        _File->_file = reinterpret_cast<int>(_Mode);

        return _File;
    }

LAB_100137f2:
    piVar7 = __errno();
    *piVar7 = 0x16;
    FUN_1001189f();
    return nullptr;
}