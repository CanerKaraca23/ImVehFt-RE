#include <cstdint>

extern "C" int DAT_1003d550;
extern "C" int __cdecl __setmbcp(int code_page);

extern "C" std::uint32_t __stdcall ___initmbctable(void)
{
    if (DAT_1003d550 == 0)
    {
        __setmbcp(-3);
        DAT_1003d550 = 1;
    }

    return 0;
}