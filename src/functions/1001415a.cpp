#include <cstddef>
#include <cstdarg>

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
extern "C" int* __cdecl __errno(void);
extern "C" void __stdcall FUN_1001189f(void);
extern "C" int __cdecl __output_l(
    FILE* _File,
    const char* _Format,
    _locale_t _Locale,
    va_list _ArgList);
extern "C" int __cdecl __flsbuf(int _Character, FILE* _File);

extern "C" int __cdecl FUN_1001415a(
    char* _DstBuf,
    std::size_t _MaxCount,
    const char* _Format,
    _locale_t _Locale,
    va_list _ArgList)
{
    FILE local_24{};

    if (_Format == nullptr) {
        *__errno() = 0x16;
        FUN_1001189f();
        return -1;
    }

    if ((_MaxCount != 0) && (_DstBuf == nullptr)) {
        *__errno() = 0x16;
        FUN_1001189f();
        return -1;
    }

    local_24._cnt = 0x7fffffff;
    if (_MaxCount < 0x80000000U) {
        local_24._cnt = static_cast<int>(_MaxCount);
    }

    local_24._flag = 0x42;
    local_24._base = _DstBuf;
    local_24._ptr = _DstBuf;

    int result = __output_l(
        &local_24,
        _Format,
        _Locale,
        _ArgList);

    if (_DstBuf != nullptr) {
        local_24._cnt = local_24._cnt - 1;

        if (local_24._cnt < 0) {
            __flsbuf(0, &local_24);
        }
        else {
            *local_24._ptr = '\0';
        }
    }

    return result;
}