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
extern "C" void __cdecl FUN_10017cd2(int lock_number);
extern "C" void __stdcall LeaveCriticalSection(void* critical_section);

void __cdecl __unlock_file(FILE* _File)
{
    if ((reinterpret_cast<FILE*>(0x100291cf) < _File) &&
        (_File < reinterpret_cast<FILE*>(0x10029431)))
    {
        _File->_flag = _File->_flag & 0xffff7fff;

        FUN_10017cd2(
            (static_cast<int>(
                 reinterpret_cast<std::uintptr_t>(&_File[-0x80148f]._file)) >>
             5) +
            0x10);

        return;
    }

    LeaveCriticalSection(
        reinterpret_cast<void*>(
            reinterpret_cast<std::uint8_t*>(_File) + 0x20));
}