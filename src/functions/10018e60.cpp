#include <Windows.h>



extern "C" void __cdecl __global_unwind2(PVOID param_1)
{
    RtlUnwind(param_1, (PVOID)0x10018e78, (PEXCEPTION_RECORD)0x0, (PVOID)0x0);
}