#include <cstdint>

extern std::uint32_t DAT_1003b700[];
extern std::uint16_t DAT_1003bd8c;

std::uint32_t* __cdecl FUN_10004a60(int param_1)
{
    std::uint16_t index = 0;

    if (param_1 != -1 && DAT_1003bd8c != 0)
    {
        do
        {
            if (static_cast<int>(DAT_1003b700[static_cast<std::uint32_t>(index) * 3]) == param_1)
            {
                return &DAT_1003b700[static_cast<std::uint32_t>(index) * 3];
            }

            index = static_cast<std::uint16_t>(index + 1);
        }
        while (index < DAT_1003bd8c);
    }

    return nullptr;
}