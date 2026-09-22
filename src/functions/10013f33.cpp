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
using uint = std::uint32_t;
using longlong = std::int64_t;
using ulonglong = std::uint64_t;
using undefined = unsigned char;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined4 = std::uint32_t;
using undefined8 = std::uint64_t;
extern int _DAT_10039a40;
extern int DAT_10039a50;

extern "C" int __cdecl __fileno(FILE* _File);
extern "C" int __cdecl __isatty(int _FileHandle);
extern "C" void** __stdcall FUN_1001301f();
extern "C" void* __cdecl __malloc_crt(std::size_t _Size);

extern "C" int __cdecl __stbuf(FILE* _File)
{
    int file_descriptor = __fileno(_File);
    file_descriptor = __isatty(file_descriptor);

    if (file_descriptor == 0) {
        return 0;
    }

    void** stream_table = FUN_1001301f();
    int stream_index;

    if (_File == reinterpret_cast<FILE*>(stream_table + 8)) {
        stream_index = 0;
    }
    else {
        stream_table = FUN_1001301f();

        if (_File != reinterpret_cast<FILE*>(stream_table + 0x10)) {
            return 0;
        }

        stream_index = 1;
    }

    _DAT_10039a40 = _DAT_10039a40 + 1;

    if ((_File->_flag & 0x10cU) != 0) {
        return 0;
    }

    int* buffer = &DAT_10039a50 + stream_index;
    char* buffer_pointer = nullptr;

    if (*buffer == 0) {
        void* allocated_buffer = __malloc_crt(0x1000);
        *buffer = static_cast<int>(
            reinterpret_cast<std::uintptr_t>(allocated_buffer));

        if (allocated_buffer == nullptr) {
            _File->_base = reinterpret_cast<char*>(&_File->_charbuf);
            _File->_ptr = reinterpret_cast<char*>(&_File->_charbuf);
            _File->_bufsiz = 2;
            _File->_cnt = 2;
            goto LAB_10013fbc;
        }
    }

    buffer_pointer = reinterpret_cast<char*>(
        static_cast<std::uintptr_t>(*buffer));

    _File->_base = buffer_pointer;
    _File->_ptr = buffer_pointer;
    _File->_bufsiz = 0x1000;
    _File->_cnt = 0x1000;

LAB_10013fbc:
    _File->_flag = _File->_flag | 0x1102;
    return 1;
}