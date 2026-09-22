#include <cstdint>

#include <cstddef>
#include <corecrt.h>
using longlong = std::int64_t;
using ulonglong = std::uint64_t;
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
using undefined = unsigned char;

extern "C" int __cdecl __fileno(FILE* _File);
extern "C" int* __cdecl __errno();
extern "C" undefined** __stdcall FUN_1001301f();
extern "C" int __cdecl __isatty(int _FileHandle);
extern "C" void __cdecl __getbuf(FILE* _File);
extern "C" unsigned int __cdecl __write(
    int _FileHandle,
    const void* _Buffer,
    unsigned int _Count);
extern "C" long long __cdecl __lseeki64(
    int _FileHandle,
    long long _Offset,
    int _Origin);

extern "C" undefined DAT_10029450;
extern "C" undefined* DAT_1003c420[];

extern "C" int __cdecl __flsbuf(int _Ch, FILE* _File)
{
    int unaff_EDI;
    __asm mov unaff_EDI, edi

    FILE* _File_00 = _File;
    _File = reinterpret_cast<FILE*>(__fileno(_File));

    unsigned int uVar6 = _File_00->_flag;

    if ((uVar6 & 0x82U) == 0) {
        *__errno() = 9;
        _File_00->_flag = _File_00->_flag | 0x20;
        return -1;
    }

    if ((uVar6 & 0x40U) != 0) {
        *__errno() = 0x22;
        _File_00->_flag = _File_00->_flag | 0x20;
        return -1;
    }

    if ((uVar6 & 1U) != 0) {
        _File_00->_cnt = 0;

        if ((uVar6 & 0x10U) == 0) {
            _File_00->_flag = uVar6 | 0x20;
            return -1;
        }

        _File_00->_ptr = _File_00->_base;
        _File_00->_flag = uVar6 & 0xfffffffeU;
    }

    uVar6 = _File_00->_flag;
    _File_00->_flag = (uVar6 & 0xffffffefU) | 2U;
    _File_00->_cnt = 0;

    unsigned int local_8 = 0;
    undefined** ppuVar3;

    if ((uVar6 & 0x10cU) == 0) {
        ppuVar3 = FUN_1001301f();

        if ((_File_00 != reinterpret_cast<FILE*>(ppuVar3 + 8) &&
             (ppuVar3 = FUN_1001301f(),
              _File_00 != reinterpret_cast<FILE*>(ppuVar3 + 0x10))) ||
            __isatty(reinterpret_cast<int>(_File)) == 0) {
            __getbuf(_File_00);
        }
    }

    if ((_File_00->_flag & 0x108U) == 0) {
        uVar6 = 1;
        local_8 = __write(reinterpret_cast<int>(_File), &_Ch, 1);
    } else {
        char* _Buf = _File_00->_base;
        char* pcVar1 = _File_00->_ptr;

        _File_00->_ptr = _Buf + 1;
        uVar6 = static_cast<unsigned int>(
            reinterpret_cast<int>(pcVar1) -
            reinterpret_cast<int>(_Buf));
        _File_00->_cnt = _File_00->_bufsiz + -1;

        if (static_cast<int>(uVar6) < 1) {
            undefined* puVar5;

            if (_File == reinterpret_cast<FILE*>(0xffffffff) ||
                _File == reinterpret_cast<FILE*>(0xfffffffe)) {
                puVar5 = &DAT_10029450;
            } else {
                puVar5 = reinterpret_cast<undefined*>(
                    reinterpret_cast<std::uintptr_t>(
                        DAT_1003c420[reinterpret_cast<int>(_File) >> 5]) +
                    ((reinterpret_cast<unsigned int>(_File) & 0x1fU) * 0x40U));
            }

            if ((puVar5[4] & 0x20U) != 0 &&
                __lseeki64(
                    reinterpret_cast<int>(_File),
                    0x200000000LL,
                    unaff_EDI) == -1) {
                _File_00->_flag = _File_00->_flag | 0x20;
                return -1;
            }
        } else {
            local_8 = __write(reinterpret_cast<int>(_File), _Buf, uVar6);
        }

        *_File_00->_base = static_cast<char>(_Ch);
    }

    if (local_8 == uVar6) {
        return _Ch & 0xff;
    }

    _File_00->_flag = _File_00->_flag | 0x20;
    return -1;
}