#include <cstdint>

using errno_t = int;
using rsize_t = std::uint32_t;

extern "C" int* __cdecl __errno();
extern "C" void __stdcall FUN_1001189f();

errno_t __cdecl strncpy_s(
    char* _Dst,
    rsize_t _SizeInBytes,
    char* _Src,
    rsize_t _MaxCount)
{
    char cVar1;
    int* piVar2;
    char* pcVar3;
    int iVar4;
    rsize_t rVar5;
    errno_t eStack_14;

    if (_MaxCount == 0) {
        if (_Dst == nullptr) {
            if (_SizeInBytes == 0) {
                return 0;
            }
        } else {
        LAB_10010cfc:
            if (_SizeInBytes != 0) {
                if (_MaxCount == 0) {
                    *_Dst = '\0';
                    return 0;
                }

                if (_Src != nullptr) {
                    rVar5 = _SizeInBytes;

                    if (_MaxCount == 0xffffffffu) {
                        iVar4 = static_cast<int>(
                            reinterpret_cast<std::intptr_t>(_Dst) -
                            reinterpret_cast<std::intptr_t>(_Src));

                        do {
                            cVar1 = *_Src;
                            _Src[iVar4] = cVar1;
                            _Src = _Src + 1;
                            if (cVar1 == '\0') {
                                break;
                            }
                            rVar5 = rVar5 - 1;
                        } while (rVar5 != 0);
                    } else {
                        pcVar3 = _Dst;
                        do {
                            cVar1 = pcVar3[static_cast<int>(
                                reinterpret_cast<std::intptr_t>(_Src) -
                                reinterpret_cast<std::intptr_t>(_Dst))];
                            *pcVar3 = cVar1;
                            pcVar3 = pcVar3 + 1;
                            if ((cVar1 == '\0') ||
                                ((rVar5 = rVar5 - 1), rVar5 == 0)) {
                                break;
                            }
                            _MaxCount = _MaxCount - 1;
                        } while (_MaxCount != 0);

                        if (_MaxCount == 0) {
                            *pcVar3 = '\0';
                        }
                    }

                    if (rVar5 != 0) {
                        return 0;
                    }
                    if (_MaxCount == 0xffffffffu) {
                        _Dst[_SizeInBytes - 1] = '\0';
                        return 0x50;
                    }

                    *_Dst = '\0';
                    piVar2 = __errno();
                    eStack_14 = 0x22;
                    *piVar2 = 0x22;
                    goto LAB_10010d0d;
                }

                *_Dst = '\0';
            }
        }
    } else if (_Dst != nullptr) {
        goto LAB_10010cfc;
    }

    piVar2 = __errno();
    eStack_14 = 0x16;
    *piVar2 = 0x16;

LAB_10010d0d:
    FUN_1001189f();
    return eStack_14;
}
