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
extern "C" unsigned int __cdecl __filbuf(FILE* stream);

extern "C" unsigned int __fastcall __inc(
    std::uint32_t ,
    FILE* param_2)
{
    param_2->_cnt = param_2->_cnt + -1;

    if (-1 < param_2->_cnt)
    {
        const unsigned char value = *param_2->_ptr;
        param_2->_ptr = param_2->_ptr + 1;
        return static_cast<unsigned int>(value);
    }

    return __filbuf(param_2);
}