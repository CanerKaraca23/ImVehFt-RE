#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __lock(int lock_id);

extern "C" void __stdcall FUN_10012b9c(void)
{
    __lock(8);
}