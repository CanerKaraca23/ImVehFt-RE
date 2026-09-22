#include <cstddef>
#include <cstdint>
#include <corecrt.h>
using longlong = std::int64_t;
using uint = std::uint32_t;
using ulonglong = std::uint64_t;
using undefined = unsigned char;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined4 = std::uint32_t;
using undefined8 = std::uint64_t;
extern "C" int* __cdecl __errno(void);
extern "C" void __stdcall FUN_1001189f(void);
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
void __cdecl __lock_file(FILE*);
int __cdecl _fclose_nolock(FILE * _File);
void __cdecl __unlock_file(FILE * _File);
int __cdecl fclose(FILE* _File)
{
    int* error_number;
    int result = -1;

    if (_File == nullptr)
    {
        error_number = __errno();
        *error_number = 0x16;
        FUN_1001189f();
        result = -1;
    }
    else if ((_File->_flag & 0x40) == 0)
    {
        __lock_file(_File);
        result = _fclose_nolock(_File);
        __unlock_file(_File);
    }
    else
    {
        _File->_flag = 0;
    }

    return result;
}