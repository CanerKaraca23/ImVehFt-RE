#include <cstdint>

struct localeinfo_struct;

extern "C" int __cdecl x_ismbbtype_l(
    localeinfo_struct* locale_info,
    std::uint32_t character,
    int type,
    int mask);

extern "C" int __cdecl __ismbblead(std::uint32_t character)
{
    return x_ismbbtype_l(
        static_cast<localeinfo_struct*>(nullptr),
        character,
        0,
        4);
}