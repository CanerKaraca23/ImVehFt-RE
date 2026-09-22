#include <cstddef>
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
extern std::uint32_t _DAT_10039a40;
extern "C" char* __cdecl __malloc_crt(std::size_t);

void __cdecl __getbuf(FILE* _File)
{
    _DAT_10039a40 = _DAT_10039a40 + 1;

    char* pcVar1 = static_cast<char*>(__malloc_crt(0x1000));

    _File->_base = pcVar1;

    if (pcVar1 == nullptr)
    {
        _File->_flag = _File->_flag | 4;
        _File->_base = reinterpret_cast<char*>(&_File->_charbuf);
        _File->_bufsiz = 2;
    }
    else
    {
        _File->_flag = _File->_flag | 8;
        _File->_bufsiz = 0x1000;
    }

    _File->_cnt = 0;
    _File->_ptr = _File->_base;
}