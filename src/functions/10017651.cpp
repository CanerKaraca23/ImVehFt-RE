#include <cstddef>
#include <cstdint>
#include <new>

struct pthreadlocinfo;
struct pthreadmbcinfo;

struct localeinfo_struct
{
    pthreadlocinfo* locinfo;
    pthreadmbcinfo* mbcinfo;
};

struct _ptiddata
{
    std::uint8_t reserved_00[0x68];
    pthreadmbcinfo* ptmbcinfo;
    pthreadlocinfo* ptlocinfo;
    std::uint32_t ownlocale;
};

struct _LocaleUpdate
{
    pthreadlocinfo* locinfo;
    pthreadmbcinfo* mbcinfo;
    _ptiddata* ptd;
    std::uint8_t updated;
    _LocaleUpdate(localeinfo_struct* locale);
};

extern "C" int __cdecl __isctype_l(
    int c,
    int mask,
    localeinfo_struct* locale_info);

extern "C" int __cdecl __isdigit_l(int c, void* locale)
{
    alignas(_LocaleUpdate) std::uint8_t local_storage[sizeof(_LocaleUpdate)];
    auto* local = reinterpret_cast<_LocaleUpdate*>(local_storage);
    ::new (static_cast<void*>(local)) _LocaleUpdate(
        reinterpret_cast<localeinfo_struct*>(locale));

    const auto locinfo = reinterpret_cast<std::uintptr_t>(local->locinfo);
    const auto locale_name_length = *reinterpret_cast<const std::int32_t*>(
        locinfo + 0xac);

    std::uint32_t result;
    if (locale_name_length <= 1)
    {
        const auto ctype_table = *reinterpret_cast<const std::uintptr_t*>(
            locinfo + 0xc8);
        result = *reinterpret_cast<const std::uint16_t*>(
            ctype_table + static_cast<std::intptr_t>(c) * 2) & 4U;
    }
    else
    {
        result = static_cast<std::uint32_t>(
            __isctype_l(c, 4, reinterpret_cast<localeinfo_struct*>(local)));
    }

    if (local->updated != 0)
    {
        local->ptd->ownlocale &= ~2U;
    }

    return static_cast<int>(result);
}