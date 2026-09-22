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
extern void* PTR_DAT_100291d0;
extern std::uint8_t DAT_10029430;

extern "C" void __cdecl __lock(int lock_number);
extern "C" void __stdcall EnterCriticalSection(void* critical_section);

void __cdecl __lock_file(FILE* _File)
{
    if ((_File < reinterpret_cast<FILE*>(&PTR_DAT_100291d0)) ||
        (reinterpret_cast<FILE*>(&DAT_10029430) < _File))
    {
        EnterCriticalSection(reinterpret_cast<void*>(_File + 1));
    }
    else
    {
        __lock((static_cast<int>(
                    reinterpret_cast<std::uintptr_t>(&_File[-0x80148f]._file)) >>
                5) +
               0x10);

        _File->_flag = _File->_flag | 0x8000;
    }
}