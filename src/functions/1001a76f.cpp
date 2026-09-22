#include <cstdint>

extern "C" std::uint32_t DAT_1003a37c;
extern "C" std::uint32_t DAT_10029490;

extern "C" int __cdecl __get_printf_count_output(void)
{
    return static_cast<unsigned int>(
        DAT_1003a37c == (DAT_10029490 | 1u));
}