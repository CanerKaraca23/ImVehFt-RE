#include <cstdint>
#include <windows.h>

extern "C" void __cdecl __SEH_prolog4(std::uint32_t, int);
extern "C" void __stdcall __SEH_epilog4();

struct PtdLocaleInfoView { LONG refcount; };
struct PtdMbInfoView { LONG refcount; };
struct PtdInitView
{
    std::uint8_t reserved_00[0x08];
    int _terrno;
    std::uint8_t reserved_0c[0x08];
    std::uint32_t _holdrand;
    std::uint8_t reserved_18[0x44];
    std::uint32_t* _pxcptacttab;
    std::uint8_t reserved_60[0x08];
    PtdMbInfoView* ptmbcinfo;
    PtdLocaleInfoView* ptlocinfo;
    int _ownlocale;
    std::uint8_t reserved_74[0x4c];
    struct { std::uint8_t _cachein[0x94]; } _setloc_data;
};
static_assert(offsetof(PtdInitView, _terrno) == 0x08);
static_assert(offsetof(PtdInitView, _holdrand) == 0x14);
static_assert(offsetof(PtdInitView, _pxcptacttab) == 0x5c);
static_assert(offsetof(PtdInitView, ptmbcinfo) == 0x68);
static_assert(offsetof(PtdInitView, ptlocinfo) == 0x6c);
static_assert(offsetof(PtdInitView, _ownlocale) == 0x70);
static_assert(offsetof(PtdInitView, _setloc_data) == 0xc0);
static_assert(offsetof(PtdInitView, _setloc_data) + 0x08 == 0xc8);
static_assert(offsetof(PtdInitView, _setloc_data) + 0x8b == 0x14b);
using _ptiddata = PtdInitView*;
using pthreadmbcinfo = PtdMbInfoView*;
using pthreadlocinfo = PtdLocaleInfoView*;

extern "C" std::uint32_t DAT_10022770;
extern "C" PtdMbInfoView DAT_100294A0;
extern "C" PtdLocaleInfoView* PTR_DAT_10029C08;

extern "C" void __cdecl __lock(int);
extern "C" void __stdcall FUN_10014D65();
extern "C" void __stdcall FUN_10014D6E();
extern "C" void __cdecl ___addlocaleref(LONG*);

extern "C" void __cdecl __initptd(_ptiddata _Ptd, pthreadlocinfo _Locale)
{
    __SEH_prolog4(0x100283d0, 0x08);

    GetModuleHandleW(L"KERNEL32.DLL");

    _Ptd->_pxcptacttab = &DAT_10022770;
    _Ptd->_terrno = 0;
    _Ptd->_holdrand = 1;
    _Ptd->_ownlocale = 1;

    *(reinterpret_cast<std::uint8_t*>(_Ptd->_setloc_data._cachein) + 8) = 0x43;
    *(reinterpret_cast<std::uint8_t*>(_Ptd->_setloc_data._cachein) + 0x8b) = 0x43;

    _Ptd->ptmbcinfo = &DAT_100294A0;

    __lock(0xD);
    InterlockedIncrement(&_Ptd->ptmbcinfo->refcount);
    FUN_10014D65();

    __lock(0xC);

    _Ptd->ptlocinfo = _Locale;
    if (_Locale == nullptr)
    {
        _Ptd->ptlocinfo = PTR_DAT_10029C08;
    }

    ___addlocaleref(&_Ptd->ptlocinfo->refcount);
    FUN_10014D6E();

    __SEH_epilog4();
}