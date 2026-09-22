#include <cstdint>

#include <cstddef>
#include <corecrt.h>
using longlong = std::int64_t;
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
extern "C" int* __cdecl __errno();
extern "C" void __stdcall FUN_1001189f();
extern "C" void __cdecl __getbuf(FILE* _File);
extern "C" int __cdecl __fileno(FILE* _File);
extern "C" int __cdecl __read(int file_handle, void* buffer, unsigned int count);

extern "C" std::uint8_t DAT_10029450;
extern "C" std::uint8_t* DAT_1003c420[];

int __cdecl __filbuf(FILE* _File)
{
    std::uint8_t bVar1;
    int* piVar2;
    int iVar3;
    std::uint32_t uVar4;
    std::uint8_t* puVar5;
    char* _DstBuf;

    if (_File == nullptr)
    {
        piVar2 = __errno();
        *piVar2 = 0x16;
        FUN_1001189f();
    }
    else
    {
        uVar4 = static_cast<std::uint32_t>(_File->_flag);

        if (((uVar4 & 0x83U) != 0U) && ((uVar4 & 0x40U) == 0U))
        {
            if ((uVar4 & 2U) == 0U)
            {
                _File->_flag = static_cast<int>(uVar4 | 1U);

                if ((uVar4 & 0x10cU) == 0U)
                {
                    __getbuf(_File);
                }
                else
                {
                    _File->_ptr = _File->_base;
                }

                uVar4 = static_cast<std::uint32_t>(_File->_bufsiz);
                _DstBuf = _File->_base;

                iVar3 = __fileno(_File);
                iVar3 = __read(iVar3, _DstBuf, uVar4);
                _File->_cnt = iVar3;

                if ((iVar3 != 0) && (iVar3 != -1))
                {
                    if ((static_cast<std::uint32_t>(_File->_flag) & 0x82U) == 0U)
                    {
                        iVar3 = __fileno(_File);

                        if ((iVar3 == -1) ||
                            ((iVar3 = __fileno(_File)), (iVar3 == -2)))
                        {
                            puVar5 = &DAT_10029450;
                        }
                        else
                        {
                            iVar3 = __fileno(_File);
                            uVar4 = static_cast<std::uint32_t>(__fileno(_File));

                            puVar5 = DAT_1003c420[iVar3 >> 5] +
                                      ((uVar4 & 0x1fU) * 0x40U);
                        }

                        if ((puVar5[4] & 0x82U) == 0x82U)
                        {
                            _File->_flag = _File->_flag | 0x2000;
                        }
                    }

                    if ((_File->_bufsiz == 0x200) &&
                        ((static_cast<std::uint32_t>(_File->_flag) & 8U) != 0U) &&
                        ((static_cast<std::uint32_t>(_File->_flag) & 0x400U) == 0U))
                    {
                        _File->_bufsiz = 0x1000;
                    }

                    _File->_cnt = _File->_cnt + -1;
                    bVar1 = static_cast<std::uint8_t>(*_File->_ptr);
                    _File->_ptr = _File->_ptr + 1;

                    return static_cast<unsigned int>(bVar1);
                }

                _File->_flag =
                    _File->_flag |
                    ((0U - static_cast<std::uint32_t>(iVar3 != 0) & 0x10U) + 0x10U);
                _File->_cnt = 0;
            }
            else
            {
                _File->_flag = static_cast<int>(uVar4 | 0x20U);
            }
        }
    }

    return -1;
}