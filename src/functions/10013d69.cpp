
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
extern "C" int __cdecl __fileno(FILE* _File);
extern "C" unsigned int __cdecl __write(
    int _FileHandle,
    const char* _Buffer,
    unsigned int _Count);

extern "C" int __cdecl __flush(FILE* _File)
{
    int result = 0;

    if (((static_cast<unsigned char>(_File->_flag) & 3U) == 2U) &&
        ((_File->_flag & 0x108U) != 0U))
    {
        char* buffer = _File->_base;
        unsigned int count =
            static_cast<unsigned int>(
                static_cast<int>(_File->_ptr - buffer));

        if (static_cast<int>(count) > 0)
        {
            unsigned int requested = count;
            int fileHandle = __fileno(_File);
            unsigned int written = __write(fileHandle, buffer, requested);

            if (written == count)
            {
                if (static_cast<signed char>(_File->_flag) < 0)
                    _File->_flag &= 0xFFFFFFFDU;
            }
            else
            {
                _File->_flag |= 0x20U;
                result = -1;
            }
        }
    }

    _File->_cnt = 0;
    _File->_ptr = _File->_base;

    return result;
}