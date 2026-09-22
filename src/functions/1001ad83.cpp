#include <cstddef>
#include <cstdint>

using errno_t = int;
using rsize_t = std::size_t;

extern "C" int* __cdecl __errno();
extern "C" void __stdcall FUN_1001189f();

extern "C" errno_t __cdecl _wcscpy_s(
    wchar_t* _Dst,
    rsize_t _SizeInWords,
    wchar_t* _Src)
{
    wchar_t wVar1;
    int* piVar2;
    int iVar3;
    errno_t eStack_10;

    if ((_Dst != nullptr) && (_SizeInWords != 0)) {
        if (_Src != nullptr) {
            iVar3 =
                static_cast<int>(reinterpret_cast<std::uintptr_t>(_Dst)) -
                static_cast<int>(reinterpret_cast<std::uintptr_t>(_Src));

            do {
                wVar1 = *_Src;

                *reinterpret_cast<wchar_t*>(
                    reinterpret_cast<std::uintptr_t>(_Src) +
                    static_cast<std::intptr_t>(iVar3)) = wVar1;

                _Src = _Src + 1;

                if (wVar1 == L'\0') {
                    break;
                }

                _SizeInWords = _SizeInWords - 1;
            } while (_SizeInWords != 0);

            if (_SizeInWords != 0) {
                return 0;
            }

            *_Dst = L'\0';

            piVar2 = __errno();
            eStack_10 = 0x22;
            *piVar2 = 0x22;
            goto LAB_1001ada2;
        }

        *_Dst = L'\0';
    }

    piVar2 = __errno();
    eStack_10 = 0x16;
    *piVar2 = 0x16;

LAB_1001ada2:
    FUN_1001189f();
    return eStack_10;
}