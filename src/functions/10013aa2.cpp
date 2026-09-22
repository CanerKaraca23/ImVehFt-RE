#include <Windows.h>



extern "C" void __fastcall _EH4_GlobalUnwind2(
    PVOID param_1,
    PEXCEPTION_RECORD param_2)
{
    RtlUnwind(
        param_1,
        reinterpret_cast<PVOID>(0x10013AB6),
        param_2,
        nullptr);
}