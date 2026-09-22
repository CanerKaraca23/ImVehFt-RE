#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void __cdecl FUN_10003fe0(int param_1, int param_2)
{
    *reinterpret_cast<unsigned char*>(param_1 + 2) =
        static_cast<unsigned char>(-(param_2 != 0) & 4);
}