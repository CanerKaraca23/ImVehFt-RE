#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
struct _EXCEPTION_POINTERS;

extern "C" int __cdecl __XcptFilter(unsigned long _ExceptionNum, _EXCEPTION_POINTERS* _ExceptionPtr);

extern "C" int __cdecl ___CppXcptFilter(
    unsigned long _ExceptionNum,
    _EXCEPTION_POINTERS* _ExceptionPtr)
{
    if (_ExceptionNum == 0xE06D7363UL) {
        return __XcptFilter(0xE06D7363UL, _ExceptionPtr);
    }

    return 0;
}