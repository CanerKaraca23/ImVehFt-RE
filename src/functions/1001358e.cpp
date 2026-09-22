
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

int __cdecl __fileno(FILE* _File)
{
    if (_File == nullptr)
    {
        int* piVar1 = __errno();
        *piVar1 = 0x16;
        FUN_1001189f();
        return -1;
    }

    return _File->_file;
}