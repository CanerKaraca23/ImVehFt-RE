#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void* __cdecl __getptd_noexit(void);
extern "C" void __cdecl __amsg_exit(int);

extern "C" void* __cdecl __getptd(void)
{
    void* p_Var1 = __getptd_noexit();

    if (p_Var1 == nullptr)
    {
        __amsg_exit(0x10);
    }

    return p_Var1;
}