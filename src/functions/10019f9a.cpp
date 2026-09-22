#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <windows.h>
#include <stdio.h>
struct __localeinfo;
struct localeinfo_struct
{
    __localeinfo* locinfo;
    void* mbcinfo;
};
struct __ptiddata_impl
{
    std::uint8_t reserved_00[0x70];
    std::uint32_t _Field_0x70;
};
struct _LocaleUpdate
{
    __localeinfo* _Ptdlocinfo;          // Ghidra: this+0x00, ptd->ptlocinfo
    void* _Unknown04;                  // Ghidra: this+0x04, ptd->ptmbcinfo
    __ptiddata_impl* _Locinfo;         // Ghidra: this+0x08, ptd
    std::uint8_t _Updated;             // Ghidra: this+0x0c
    std::uint8_t reserved_0d[3];
    _LocaleUpdate(_locale_t locale);
};
static_assert(offsetof(localeinfo_struct, locinfo) == 0x00);
static_assert(offsetof(localeinfo_struct, mbcinfo) == 0x04);
static_assert(offsetof(__ptiddata_impl, _Field_0x70) == 0x70);
static_assert(offsetof(_LocaleUpdate, _Ptdlocinfo) == 0x00);
static_assert(offsetof(_LocaleUpdate, _Unknown04) == 0x04);
static_assert(offsetof(_LocaleUpdate, _Locinfo) == 0x08);
static_assert(offsetof(_LocaleUpdate, _Updated) == 0x0c);
static_assert(sizeof(_LocaleUpdate) == 0x10);
extern "C" int __cdecl __crtGetStringTypeA_stat(
    localeinfo_struct*, unsigned long, char*, int, unsigned short*, int, int, int);

BOOL __cdecl ___crtGetStringTypeA(
    _locale_t _Plocinfo,
    DWORD _DWInfoType,
    LPCSTR _LpSrcStr,
    int _CchSrc,
    LPWORD _LpCharType,
    int _Code_page,
    BOOL _BError)
{
    _LocaleUpdate _LocaleUpdateObject(_Plocinfo);

    const int _Result = __crtGetStringTypeA_stat(
        reinterpret_cast<localeinfo_struct*>(&_LocaleUpdateObject),
        _DWInfoType,
        const_cast<char*>(_LpSrcStr),
        _CchSrc,
        _LpCharType,
        _Code_page,
        _BError,
        static_cast<int>(
            reinterpret_cast<std::uintptr_t>(
                _LocaleUpdateObject._Ptdlocinfo)));

    if (_LocaleUpdateObject._Updated != 0)
    {
        _LocaleUpdateObject._Locinfo->_Field_0x70 &=
            0xfffffffdU;
    }

    return _Result;
}