#include <cstddef>

using errno_t = int;
using rsize_t = std::size_t;

extern "C" int* __cdecl __errno();
extern "C" void __stdcall FUN_1001189f();

extern "C" errno_t __cdecl _wcsncpy_s(
    wchar_t* _Dst,
    rsize_t _SizeInWords,
    wchar_t* _Src,
    rsize_t _MaxCount)
{
    wchar_t wVar1;
    int* piVar2;
    wchar_t* pwVar3;
    int iVar4;
    rsize_t rVar5;
    errno_t eStack_14;

    if (_MaxCount == 0) {
        if (_Dst == nullptr) {
            if (_SizeInWords == 0) {
                return 0;
            }
        } else {
            goto LAB_1001acc1;
        }
    } else if (_Dst != nullptr) {
        goto LAB_1001acc1;
    }

    piVar2 = __errno();
    eStack_14 = 0x16;
    *piVar2 = 0x16;
    goto LAB_1001acd2;

LAB_1001acc1:
    if (_SizeInWords != 0) {
        if (_MaxCount == 0) {
            *_Dst = L'\0';
            return 0;
        }

        if (_Src != nullptr) {
            rVar5 = _SizeInWords;

            if (_MaxCount == static_cast<rsize_t>(0xFFFFFFFFu)) {
                iVar4 = static_cast<int>(
                    reinterpret_cast<char*>(_Dst) -
                    reinterpret_cast<char*>(_Src));

                do {
                    wVar1 = *_Src;
                    *reinterpret_cast<wchar_t*>(
                        reinterpret_cast<char*>(_Src) + iVar4) = wVar1;
                    _Src += 1;

                    if (wVar1 == L'\0') {
                        break;
                    }

                    rVar5 -= 1;
                } while (rVar5 != 0);
            } else {
                pwVar3 = _Dst;

                do {
                    wVar1 = *_Src;
                    *pwVar3 = wVar1;
                    pwVar3 += 1;
                    _Src += 1;

                    if ((wVar1 == L'\0') ||
                        ((rVar5 -= 1) == 0)) {
                        break;
                    }

                    _MaxCount -= 1;
                } while (_MaxCount != 0);

                if (_MaxCount == 0) {
                    *pwVar3 = L'\0';
                }
            }

            if (rVar5 != 0) {
                return 0;
            }

            if (_MaxCount == static_cast<rsize_t>(0xFFFFFFFFu)) {
                _Dst[_SizeInWords - 1] = L'\0';
                return 0x50;
            }

            *_Dst = L'\0';
            piVar2 = __errno();
            eStack_14 = 0x22;
            *piVar2 = 0x22;
            goto LAB_1001acd2;
        }

        *_Dst = L'\0';
    }

    piVar2 = __errno();
    eStack_14 = 0x16;
    *piVar2 = 0x16;

LAB_1001acd2:
    FUN_1001189f();
    return eStack_14;
}