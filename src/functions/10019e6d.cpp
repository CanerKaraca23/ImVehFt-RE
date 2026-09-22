#include <cstddef>
#include <cstdint>
using LPCWSTR = const wchar_t*;
using LPCSTR = const char*;
using LPSTR = char*;
using DWORD = unsigned long;
using BOOL = int;
struct pthreadlocinfo;
struct pthreadmbcinfo;
struct localeinfo_struct { pthreadlocinfo* locinfo; pthreadmbcinfo* mbcinfo; };
struct _ptiddata { std::uint8_t _reserved_00[0x68]; pthreadmbcinfo* ptmbcinfo; pthreadlocinfo* ptlocinfo; std::uint32_t _ownlocale; };
static_assert(offsetof(_ptiddata, _ownlocale) == 0x70);
struct _LocaleUpdate { pthreadlocinfo* locinfo; pthreadmbcinfo* mbcinfo; _ptiddata* ptd; std::uint8_t updated; explicit _LocaleUpdate(_locale_t); };
static_assert(offsetof(_LocaleUpdate, ptd) == 0x08);
static_assert(offsetof(_LocaleUpdate, updated) == 0x0c);
static_assert(sizeof(_LocaleUpdate) == 0x10);
extern "C" int __cdecl __crtLCMapStringA_stat(localeinfo_struct*, unsigned long, unsigned long, char*, int, char*, int, int, int);

int __cdecl ___crtLCMapStringA(
    _locale_t _Plocinfo,
    LPCWSTR _LocaleName,
    DWORD _DwMapFlag,
    LPCSTR _LpSrcStr,
    int _CchSrc,
    LPSTR _LpDestStr,
    int _CchDest,
    int _Code_page,
    BOOL _BError)
{
    int iVar1;
    _LocaleUpdate local_14(_Plocinfo);

    iVar1 = __crtLCMapStringA_stat(
        reinterpret_cast<localeinfo_struct*>(&local_14),
        static_cast<unsigned long>(
            reinterpret_cast<std::uintptr_t>(_LocaleName)),
        _DwMapFlag,
        const_cast<char*>(_LpSrcStr),
        _CchSrc,
        _LpDestStr,
        _CchDest,
        _Code_page,
        _BError);

    if (local_14.updated != 0)
    {
        local_14.ptd->_ownlocale &= 0xfffffffdU;
    }

    return iVar1;
}