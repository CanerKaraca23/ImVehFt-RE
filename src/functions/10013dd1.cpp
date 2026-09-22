
#include <cstddef>
#include <corecrt.h>
#include <cstdint>
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
extern "C" int __cdecl flsall(int);
extern "C" int __cdecl __flush(FILE* _File);
extern "C" int __cdecl __fileno(FILE* _File);
extern "C" int __cdecl __commit(int _FileHandle);

extern "C" int __cdecl __fflush_nolock(FILE* _File)
{
    if (_File == nullptr)
    {
        return flsall(0);
    }

    int result = __flush(_File);

    if (result != 0)
    {
        return -1;
    }

    if ((_File->_flag & 0x4000U) == 0U)
    {
        return 0;
    }

    result = __fileno(_File);
    result = __commit(result);

    return 0U - static_cast<unsigned int>(result != 0);
}