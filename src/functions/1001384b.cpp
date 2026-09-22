#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <windows.h>
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
extern "C" void __stdcall FUN_10013975();

#include <Windows.h>
#include <cstddef>
#include <cstdint>

#if defined(_WIN64)
#error This function requires the 32-bit MSVC ABI.
#endif

struct CRTStreamBlock_0x38
{
    FILE stream;
    CRITICAL_SECTION critical_section;
};

FILE* __cdecl __getstream(void)
{
    extern int DAT_1003d540;
    extern CRTStreamBlock_0x38** DAT_1003c520;

    extern void __cdecl __SEH_prolog4(std::uint32_t, int);
    extern void __stdcall __SEH_epilog4();
    extern void __cdecl __lock(int);
    extern int __cdecl __mtinitlocknum(int);
    extern void __cdecl __lock_file2(int, void*);
    extern void __cdecl __unlock_file2(int, void*);
    extern void* __cdecl __malloc_crt(std::size_t);
    extern void __cdecl _free(void*);

    static_assert(sizeof(void*) == 4);
    static_assert(offsetof(CRTStreamBlock_0x38, critical_section) == 0x20);
    static_assert(sizeof(CRTStreamBlock_0x38) == 0x38);

    __SEH_prolog4(0, 0);

    FILE* pFVar6 = nullptr;
    __lock(1);

    FILE* _File = pFVar6;
    int _Index = 0;
    do
    {

        if (DAT_1003d540 <= _Index)
        {
            goto LAB_10013944;
        }

        CRTStreamBlock_0x38** stream_slot = &DAT_1003c520[_Index];

        if (*stream_slot == nullptr)
        {
            void* pvVar4 = __malloc_crt(0x38);
            *stream_slot = static_cast<CRTStreamBlock_0x38*>(pvVar4);

            if (pvVar4 != nullptr)
            {
                BOOL BVar5 = InitializeCriticalSectionAndSpinCount(
                    &(*stream_slot)->critical_section,
                    4000);

                if (BVar5 == 0)
                {
                    _free(*stream_slot);
                    *stream_slot = nullptr;
                }
                else
                {
                    EnterCriticalSection(&(*stream_slot)->critical_section);
                    _File = &(*stream_slot)->stream;
                    _File->_flag = 0;
                }
            }

            goto LAB_10013944;
        }

        std::uint32_t uVar2 =
            static_cast<std::uint32_t>((*stream_slot)->stream._flag);

        if (((uVar2 & 0x83U) == 0) && ((uVar2 & 0x8000U) == 0))
        {
            if ((_Index - 3U < 0x11U) &&
                (__mtinitlocknum(_Index + 0x10) == 0))
            {
                goto LAB_10013944;
            }

            __lock_file2(_Index, *stream_slot);
            _File = &(*stream_slot)->stream;

            if ((_File->_flag & 0x83) == 0)
            {
                goto LAB_10013944;
            }

            __unlock_file2(_Index, _File);
        }

        _Index = _Index + 1;
    }
    while (true);

LAB_10013944:
    if (_File != nullptr)
    {
        _File->_flag = _File->_flag & 0x8000;
        _File->_cnt = 0;
        _File->_base = nullptr;
        _File->_ptr = nullptr;
        _File->_tmpfname = nullptr;
        _File->_file = -1;
    }

    FUN_10013975();
    __SEH_epilog4();
    return _File;
}