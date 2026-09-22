#include <cstdint>

extern int __cdecl strncmp(char* str1, char* str2, std::uint32_t max_count);
extern std::uint32_t __cdecl FUN_10003e60(
    std::uint32_t param_1,
    std::int32_t param_2,
    std::uint32_t param_3,
    std::int32_t param_4);

extern char s_ImVehFt_1003757c[];

void __cdecl FUN_10003f40(
    char* param_1,
    std::int32_t param_2,
    std::uint32_t param_3,
    std::int32_t param_4)
{
    if (strncmp(param_1, const_cast<char*>(" ZAZ "), 5) == 0)
    {
        param_1 = s_ImVehFt_1003757c;
    }

    FUN_10003e60(
        static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(param_1)),
        param_2,
        param_3,
        param_4);
}