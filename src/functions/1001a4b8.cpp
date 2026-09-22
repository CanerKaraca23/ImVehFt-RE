#include <cstddef>
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
struct __locale_category
{
    std::uint8_t* locale;
    const void* wlocale;
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
    std::uint32_t ownlocale;
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
static_assert(offsetof(__ptiddata_impl, ownlocale) == 0x70);
static_assert(offsetof(_LocaleUpdate, locinfo) == 0x00);
static_assert(offsetof(_LocaleUpdate, mbcinfo) == 0x04);
static_assert(offsetof(_LocaleUpdate, ptd) == 0x08);
static_assert(offsetof(_LocaleUpdate, updated) == 0x0c);
static_assert(sizeof(_LocaleUpdate) == 0x10);
extern "C" int __cdecl __isleadbyte_l(int, void*);
extern "C" BOOL __cdecl ___crtGetStringTypeA(
    void*, DWORD, LPCSTR, int, LPWORD, int, BOOL);

#include <cstdint>

int __cdecl __isctype_l(int _C, int _Type, _locale_t _Locale)
{
    int iVar1;
    BOOL BVar2;
    CHAR CVar3;

    CHAR local_c;
    CHAR local_b;
    std::uint8_t local_a;
    std::uint16_t local_8[2];

    alignas(_LocaleUpdate) std::uint8_t locale_update_storage[sizeof(_LocaleUpdate)];
    _LocaleUpdate* local_1c = new (locale_update_storage) _LocaleUpdate(_Locale);

    if (static_cast<std::uint32_t>(_C) + 1U < 0x101U)
    {
        local_8[0] = *reinterpret_cast<std::uint16_t*>(
            local_1c->locinfo->lc_category[0].locale + _C * 2);
    }
    else
    {
        iVar1 = __isleadbyte_l((_C >> 8) & 0xff, local_1c);
        CVar3 = static_cast<CHAR>(_C);

        if (iVar1 == 0)
        {
            local_b = '\0';
            iVar1 = 1;
            local_c = CVar3;
        }
        else
        {
            _C = (_C & 0xffffff00) |
                 static_cast<int>(
                     static_cast<std::uint8_t>(
                         static_cast<std::uint32_t>(_C) >> 8));
            local_c = static_cast<CHAR>(_C);
            local_a = 0;
            iVar1 = 2;
            local_b = CVar3;
        }

        BVar2 = ___crtGetStringTypeA(
            local_1c,
            1,
            &local_c,
            iVar1,
            local_8,
            local_1c->locinfo->lc_codepage,
            static_cast<BOOL>(reinterpret_cast<std::uintptr_t>(
                local_1c->locinfo->lc_category[0].wlocale)));

        if (BVar2 == 0)
        {
            if (local_1c->updated != 0)
            {
                local_1c->ptd->ownlocale &= 0xfffffffdu;
            }

            return 0;
        }
    }

    if (local_1c->updated != 0)
    {
        local_1c->ptd->ownlocale &= 0xfffffffdu;
    }

    return static_cast<std::uint32_t>(local_8[0]) &
           static_cast<std::uint32_t>(_Type);
}