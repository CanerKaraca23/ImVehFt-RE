#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __cdecl __FF_MSGBANNER(void);
extern "C" void __cdecl __NMSG_WRITE(int message);
extern "C" __declspec(noreturn) void __cdecl __exit(int code);

extern "C" void __cdecl __amsg_exit(int param_1)
{
    __FF_MSGBANNER();
    __NMSG_WRITE(param_1);
    __exit(0xff);
}