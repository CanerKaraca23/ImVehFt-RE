#include <cstdint>

extern const std::uint32_t DAT_10029060[];

extern "C" int __cdecl __get_errno_from_oserr(std::uint32_t param_1)
{
    std::uint32_t index = 0;

    do
    {
        if (param_1 == DAT_10029060[index * 2])
        {
            return reinterpret_cast<const std::int32_t*>(
                &DAT_10029060[index * 2 + 1])[0];
        }

        ++index;
    }
    while (index < 0x2d);

    if (param_1 - 0x13 < 0x12)
    {
        return 0xd;
    }

    return ((0U - static_cast<std::uint32_t>(0xe < param_1 - 0xbc)) & 0xeU) + 8U;
}