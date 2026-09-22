#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" int DAT_10039a00;

extern "C" int __cdecl __set_error_mode(int mode);
extern "C" void __cdecl __NMSG_WRITE(int message);

extern "C" void __cdecl __FF_MSGBANNER(void)
{
    int iVar1 = __set_error_mode(3);

    if (iVar1 != 1)
    {
        iVar1 = __set_error_mode(3);

        if (iVar1 != 0)
        {
            return;
        }

        if (DAT_10039a00 != 1)
        {
            return;
        }
    }

    __NMSG_WRITE(0xfc);
    __NMSG_WRITE(0xff);
}