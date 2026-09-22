#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern unsigned long DAT_1002226c[8];

extern "C" __declspec(noreturn) void __stdcall RaiseException(
    unsigned long,
    unsigned long,
    unsigned long,
    unsigned long*);

extern "C" __declspec(noreturn) void __stdcall __CxxThrowException_8(
    unsigned long param_1,
    unsigned char* param_2)
{
    unsigned long frame[8];

    unsigned long* source = DAT_1002226c;
    unsigned long* destination = frame;

    for (int i = 8; i != 0; i = i - 1)
    {
        *destination = *source;
        source = source + 1;
        destination = destination + 1;
    }

    frame[6] = param_1;
    frame[7] = static_cast<unsigned long>(
        reinterpret_cast<unsigned long>(param_2));

    if ((param_2 != 0) && ((*param_2 & 8u) != 0))
    {
        frame[5] = 0x1994000u;
    }

    RaiseException(frame[0], frame[1], frame[4], &frame[5]);
}