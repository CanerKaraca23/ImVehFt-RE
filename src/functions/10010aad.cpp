#include <cstdint>

#include <cstddef>
#include <corecrt.h>
using longlong = std::int64_t;
using ulonglong = std::uint64_t;
using undefined = unsigned char;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined4 = std::uint32_t;
using undefined8 = std::uint64_t;
extern "C" void __stdcall FUN_1001189f(void);
extern "C" int* __cdecl __errno(void);
using rsize_t = std::size_t;
using errno_t = int;
errno_t __cdecl strcat_s(char* _Dst, rsize_t _SizeInBytes, char* _Src)
{
    char cVar1;
    int* piVar2;
    char* pcVar3;
    int iVar4;
    errno_t eStack_10;

    if ((_Dst != nullptr) && (_SizeInBytes != 0))
    {
        pcVar3 = _Dst;

        if (_Src != nullptr)
        {
            do
            {
                if (*pcVar3 == '\0')
                {
                    break;
                }

                pcVar3 = pcVar3 + 1;
                _SizeInBytes = _SizeInBytes - 1;
            }
            while (_SizeInBytes != 0);

            if (_SizeInBytes != 0)
            {
                iVar4 =
                    static_cast<int>(reinterpret_cast<std::uintptr_t>(pcVar3)) -
                    static_cast<int>(reinterpret_cast<std::uintptr_t>(_Src));

                do
                {
                    cVar1 = *_Src;
                    _Src[iVar4] = cVar1;
                    _Src = _Src + 1;

                    if (cVar1 == '\0')
                    {
                        break;
                    }

                    _SizeInBytes = _SizeInBytes - 1;
                }
                while (_SizeInBytes != 0);

                if (_SizeInBytes != 0)
                {
                    return 0;
                }

                *_Dst = '\0';
                piVar2 = __errno();
                eStack_10 = 0x22;
                *piVar2 = 0x22;
                goto LAB_10010acc;
            }
        }

        *_Dst = '\0';
    }

    piVar2 = __errno();
    eStack_10 = 0x16;
    *piVar2 = 0x16;

LAB_10010acc:
    FUN_1001189f();
    return eStack_10;
}