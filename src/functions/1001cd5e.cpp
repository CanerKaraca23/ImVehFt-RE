#include <cstdint>

extern "C" int __cdecl _strcmp(char* str1, char* str2);

std::uint32_t __cdecl ___TypeMatch(
    std::uint8_t* param_1,
    std::uint8_t* param_2,
    std::uint32_t* param_3)
{
    int type_info = *reinterpret_cast<int*>(param_1 + 4);

    if ((type_info == 0) ||
        (*reinterpret_cast<char*>(type_info + 8) == '\0'))
    {
        return 1;
    }

    if (type_info == *reinterpret_cast<int*>(param_2 + 4))
    {
        if ((((*param_2 & 2U) == 0U) || ((*param_1 & 8U) != 0U)) &&
            (((*param_3 & 1U) == 0U) || ((*param_1 & 1U) != 0U)) &&
            (((*param_3 & 2U) == 0U) || ((*param_1 & 2U) != 0U)))
        {
            return 1;
        }

        return 0;
    }

    type_info = _strcmp(
        reinterpret_cast<char*>(type_info + 8),
        reinterpret_cast<char*>(
            *reinterpret_cast<int*>(param_2 + 4) + 8));

    if (type_info == 0)
    {
        if ((((*param_2 & 2U) == 0U) || ((*param_1 & 8U) != 0U)) &&
            (((*param_3 & 1U) == 0U) || ((*param_1 & 1U) != 0U)) &&
            (((*param_3 & 2U) == 0U) || ((*param_1 & 2U) != 0U)))
        {
            return 1;
        }
    }

    return 0;
}