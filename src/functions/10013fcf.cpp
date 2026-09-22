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
using longlong = std::int64_t;
using uint = std::uint32_t;
using ulonglong = std::uint64_t;
using undefined = unsigned char;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined4 = std::uint32_t;
using undefined8 = std::uint64_t;
extern "C" int __cdecl __flush(FILE* _File);

extern "C" void __cdecl __ftbuf(int _Flag, FILE* _File)
{
    if ((_Flag != 0) && ((_File->_flag & 0x1000U) != 0)) {
        __flush(_File);
        _File->_flag = _File->_flag & 0xffffeeff;
        _File->_bufsiz = 0;
        _File->_ptr = (char*)0x0;
        _File->_base = (char*)0x0;
    }

    return;
}