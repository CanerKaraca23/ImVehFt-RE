#include <cstddef>
#include <cstdint>

struct FILE
{
    unsigned char _reserved[0x0C];
    unsigned int _flag;
};

extern "C" void __cdecl __SEH_prolog4(...);
extern "C" void __cdecl __SEH_epilog4(...);
extern "C" int* __cdecl __errno();
extern "C" void __stdcall FUN_1001189f();
extern "C" unsigned int __cdecl __fileno(FILE*);
extern "C" std::size_t __cdecl _strlen(const char*);
extern "C" void __cdecl __lock_file(FILE*);
extern "C" int __cdecl __stbuf(FILE*);
extern "C" std::size_t __cdecl __fwrite_nolock(
    const void*, std::size_t, std::size_t, FILE*);
extern "C" void __cdecl __ftbuf(int, FILE*);
extern "C" void __stdcall FUN_10010a11();
extern unsigned char DAT_10029450;
extern unsigned char* DAT_1003C420[32];

int __cdecl fputs(char* _Str, FILE* _File)
{
    int* error_number;
    unsigned int file_descriptor;
    size_t count;
    int buffer_flag;
    size_t written;
    int result;
    unsigned char* file_info;

    __SEH_prolog4();

    if ((_Str == nullptr) || (_File == nullptr))
        goto invalid_argument;

    if ((_File->_flag & 0x40) != 0)
        goto write_string;

    file_descriptor = __fileno(_File);
    if ((file_descriptor == 0xFFFFFFFFu) ||
        (file_descriptor == 0xFFFFFFFEu))
    {
        file_info = &DAT_10029450;
    }
    else
    {
        file_info = reinterpret_cast<unsigned char*>(
            (file_descriptor & 0x1Fu) * 0x40u +
            reinterpret_cast<std::uintptr_t>(
                (&DAT_1003C420)[file_descriptor >> 5]));
    }

    if ((file_info[0x24] & 0x7Fu) != 0)
        goto invalid_argument;

    if ((file_descriptor == 0xFFFFFFFFu) ||
        (file_descriptor == 0xFFFFFFFEu))
    {
        file_info = &DAT_10029450;
    }
    else
    {
        file_info = reinterpret_cast<unsigned char*>(
            (file_descriptor & 0x1Fu) * 0x40u +
            reinterpret_cast<std::uintptr_t>(
                (&DAT_1003C420)[file_descriptor >> 5]));
    }

    if ((file_info[0x24] & 0x80u) != 0)
        goto invalid_argument;

write_string:
    count = _strlen(_Str);
    __lock_file(_File);
    buffer_flag = __stbuf(_File);
    written = __fwrite_nolock(_Str, 1, count, _File);
    __ftbuf(buffer_flag, _File);
    FUN_10010a11();
    result = (written == count) - 1;
    __SEH_epilog4();
    return result;

invalid_argument:
    error_number = __errno();
    *error_number = 0x16;
    FUN_1001189f();
    __SEH_epilog4();
    return -1;
}
