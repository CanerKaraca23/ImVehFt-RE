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
int __cdecl __flush(FILE*);
void __cdecl __freebuf(FILE * _File);
int __cdecl __fileno(FILE * _File);
int __cdecl __close(int _FileHandle);
void __cdecl _free(void * _Memory);
int __cdecl _fclose_nolock(FILE* _File)
{
    int result = -1;

    if (_File == nullptr)
    {
        int* error_number = __errno();
        *error_number = 0x16;
        FUN_1001189f();
        result = -1;
    }
    else
    {
        if ((_File->_flag & 0x83) != 0)
        {
            result = __flush(_File);
            __freebuf(_File);

            int file_descriptor = __fileno(_File);
            file_descriptor = __close(file_descriptor);

            if (file_descriptor < 0)
            {
                result = -1;
            }
            else if (_File->_tmpfname != nullptr)
            {
                _free(_File->_tmpfname);
                _File->_tmpfname = nullptr;
            }
        }

        _File->_flag = 0;
    }

    return result;
}