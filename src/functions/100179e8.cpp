#include <cstddef>
#include <cstdint>

struct _LocaleUpdate
{
    std::uint32_t locinfo;
    std::uint32_t mbcinfo;
    std::uint32_t ptd;
    std::uint8_t updated;

    _LocaleUpdate(_locale_t locale);
};

static_assert(offsetof(_LocaleUpdate, locinfo) == 0x00);
static_assert(offsetof(_LocaleUpdate, mbcinfo) == 0x04);
static_assert(offsetof(_LocaleUpdate, ptd) == 0x08);
static_assert(offsetof(_LocaleUpdate, updated) == 0x0c);
static_assert(sizeof(_LocaleUpdate) == 0x10);

extern "C" int __cdecl __isleadbyte_l(int _C, _locale_t _Locale)
{
    _LocaleUpdate local_14(_Locale);

    const std::uint16_t uVar1 = *reinterpret_cast<const std::uint16_t*>(
        static_cast<std::uintptr_t>(local_14.locinfo) +
        200u +
        (static_cast<unsigned int>(_C) & 0xffu) * 2u);

    if (local_14.updated != 0)
    {
        *reinterpret_cast<std::uint32_t*>(
            static_cast<std::uintptr_t>(local_14.ptd) + 0x70u) &=
            0xfffffffdu;
    }

    return uVar1 & 0x8000u;
}
