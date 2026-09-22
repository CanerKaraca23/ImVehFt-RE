#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" unsigned int DAT_10023090[];
extern "C" wchar_t* UNK_10023094[];

extern "C" wchar_t* __cdecl __GET_RTERRMSG(int param_1)
{
    unsigned int uVar1 = 0;

    do
    {
        if (static_cast<unsigned int>(param_1) == DAT_10023090[uVar1 * 2])
        {
            return UNK_10023094[uVar1 * 2];
        }

        uVar1 = uVar1 + 1;
    } while (uVar1 < 0x16);

    return nullptr;
}