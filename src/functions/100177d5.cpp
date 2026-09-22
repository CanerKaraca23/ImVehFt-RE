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
extern "C" int __cdecl __fileno(FILE* _File);
extern "C" int* __cdecl __errno();
extern "C" void __stdcall FUN_1001189f();
extern "C" void __cdecl __getbuf(FILE* _File);

extern "C" unsigned char DAT_10029450[];
extern "C" unsigned char* DAT_1003c420[];

extern "C" int __cdecl __ungetc_nolock(int _Ch, FILE* _File)
{
    char* pcVar1;
    std::uint32_t uVar2;
    int* piVar3;
    unsigned char* puVar4;

    if ((_File->_flag & 0x40) == 0) {
        uVar2 = static_cast<std::uint32_t>(__fileno(_File));

        if ((uVar2 == 0xffffffffU) || (uVar2 == 0xfffffffeU)) {
            puVar4 = DAT_10029450;
        } else {
            puVar4 = DAT_1003c420[static_cast<int>(uVar2) >> 5] +
                     ((uVar2 & 0x1fU) * 0x40U);
        }

        if ((puVar4[0x24] & 0x7fU) == 0) {
            if ((uVar2 == 0xffffffffU) || (uVar2 == 0xfffffffeU)) {
                puVar4 = DAT_10029450;
            } else {
                puVar4 = DAT_1003c420[static_cast<int>(uVar2) >> 5] +
                         ((uVar2 & 0x1fU) * 0x40U);
            }

            if ((puVar4[0x24] & 0x80U) == 0) {
                goto accepted_stream;
            }
        }

        piVar3 = __errno();
        *piVar3 = 0x16;
        FUN_1001189f();
    } else {
    accepted_stream:
        if (_Ch != -1) {
            uVar2 = static_cast<std::uint32_t>(_File->_flag);

            if (((uVar2 & 1U) != 0) ||
                ((static_cast<char>(uVar2) < 0) &&
                 ((uVar2 & 2U) == 0))) {
                if (_File->_base == nullptr) {
                    __getbuf(_File);
                }

                if (_File->_ptr == _File->_base) {
                    if (_File->_cnt != 0) {
                        return -1;
                    }

                    _File->_ptr = _File->_ptr + 1;
                }

                _File->_ptr = _File->_ptr - 1;
                pcVar1 = _File->_ptr;

                if ((_File->_flag & 0x40) == 0) {
                    *pcVar1 = static_cast<char>(_Ch);
                } else if (*pcVar1 != static_cast<char>(_Ch)) {
                    _File->_ptr = pcVar1 + 1;
                    return -1;
                }

                _File->_cnt = _File->_cnt + 1;
                _File->_flag = (_File->_flag & 0xffffffefU) | 1;
                return _Ch & 0xff;
            }
        }
    }

    return -1;
}