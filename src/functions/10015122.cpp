#include <cstddef>
#include <cstdint>
#include <new>

#include <corecrt.h>
#include <Windows.h>
using longlong = std::int64_t;
using ulonglong = std::uint64_t;
using undefined = unsigned char;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined4 = std::uint32_t;
using undefined8 = std::uint64_t;
extern "C" int* __cdecl __errno(void);
struct __locale_category
{
    std::uint8_t* locale;
    std::uint8_t* wlocale;
};
struct __localeinfo
{
    std::uint8_t reserved_00[0x14];
    std::uint32_t lc_codepage;
    std::uint8_t reserved_18[0x88];
    std::uint32_t locale_name[4];
    std::uint8_t reserved_b0[0x18];
    __locale_category lc_category[1];
};
struct __ptiddata_impl
{
    std::uint8_t reserved_00[0x70];
    std::uint32_t _ownlocale;
};
struct _LocaleUpdate
{
    __localeinfo* locinfo;
    void* mbcinfo;
    __ptiddata_impl* ptd;
    std::uint8_t updated;
    _LocaleUpdate(_locale_t locale);
};
static_assert(offsetof(__localeinfo, lc_codepage) == 0x14);
static_assert(offsetof(__localeinfo, locale_name) == 0xa0);
static_assert(offsetof(__localeinfo, lc_category) == 0xc8);
static_assert(offsetof(__localeinfo, lc_category[0].wlocale) == 0xcc);
static_assert(offsetof(__ptiddata_impl, _ownlocale) == 0x70);
static_assert(offsetof(_LocaleUpdate, locinfo) == 0x00);
static_assert(offsetof(_LocaleUpdate, mbcinfo) == 0x04);
static_assert(offsetof(_LocaleUpdate, ptd) == 0x08);
static_assert(offsetof(_LocaleUpdate, updated) == 0x0c);
static_assert(sizeof(_LocaleUpdate) == 0x10);
extern "C" int __cdecl __isctype_l(int, int, void*);
extern "C" int __cdecl __isleadbyte_l(int, void*);
extern "C" int __cdecl ___crtLCMapStringA(
    void*, const void*, std::uint32_t, const char*, int, char*, int, int, int);

extern "C" int __cdecl __tolower_l(int _C, _locale_t _Locale)
{
    int iVar1 = _C;
    unsigned int uVar2;
    int iVar3;
    int* piVar4;
    CHAR CVar5;
    
    unsigned char local_c;
    // The conversion API writes this byte whenever its returned count exceeds one.
    unsigned char local_b = 0;
    CHAR local_8;
    CHAR local_7;
    unsigned char local_6;

    alignas(_LocaleUpdate) std::uint8_t locale_update_storage[sizeof(_LocaleUpdate)];
    _LocaleUpdate* local_1c = new (locale_update_storage) _LocaleUpdate(_Locale);

    if (static_cast<unsigned int>(_C) < 0x100U) {
        if (static_cast<int>(local_1c->locinfo->locale_name[3]) < 2) {
            uVar2 =
                *reinterpret_cast<unsigned short*>(
                    local_1c->locinfo->lc_category[0].locale + (_C * 2)) &
                1U;
        } else {
            uVar2 = __isctype_l(_C, 1, local_1c);
        }

        if (uVar2 == 0) {
            goto LAB_10015183;
        }

        uVar2 = static_cast<unsigned int>(
            *reinterpret_cast<unsigned char*>(
                local_1c->locinfo->lc_category[0].wlocale + _C));
    } else {
        CVar5 = static_cast<CHAR>(_C);

        if ((static_cast<int>(local_1c->locinfo->locale_name[3]) < 2) ||
            ((iVar3 = __isleadbyte_l(
                  (_C >> 8) & 0xff,
                  local_1c),
              iVar3 == 0))) {
            piVar4 = __errno();
            *piVar4 = 0x2a;
            local_7 = '\0';
            iVar3 = 1;
            local_8 = CVar5;
        } else {
            local_8 = static_cast<CHAR>(
                (static_cast<unsigned int>(_C) >> 8) & 0xff);
            local_6 = 0;
            iVar3 = 2;
            local_7 = CVar5;
        }

        iVar3 = ___crtLCMapStringA(
            local_1c,
            local_1c->locinfo->lc_category[0].wlocale,
            0x100,
            &local_8,
            iVar3,
            reinterpret_cast<LPSTR>(&local_c),
            3,
            local_1c->locinfo->lc_codepage,
            1);

        if (iVar3 == 0) {
            goto LAB_10015183;
        }

        uVar2 = static_cast<unsigned int>(local_c);

        if (iVar3 != 1) {
            uVar2 =
                (static_cast<unsigned int>(local_c) << 8) |
                static_cast<unsigned int>(local_b);
        }
    }

    if (local_1c->updated != 0) {
        local_1c->ptd->_ownlocale &= 0xfffffffdu;
    }

    return static_cast<int>(uVar2);

LAB_10015183:
    if (local_1c->updated == 0) {
        return iVar1;
    }

    local_1c->ptd->_ownlocale &= 0xfffffffdu;

    return iVar1;
}