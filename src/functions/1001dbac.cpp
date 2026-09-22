#include <cstddef>
#include <cstdint>
#include <corecrt.h>
using longlong = std::int64_t;
using ulonglong = std::uint64_t;
using undefined = unsigned char;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined4 = std::uint32_t;
using undefined8 = std::uint64_t;
extern "C" int* __cdecl __errno(void);
extern "C" void __stdcall FUN_1001189f(void);
extern "C" std::size_t __cdecl _strlen(const char*);
struct _strflt { char sign; std::uint8_t reserved_01[3]; std::int32_t decpt; std::uint32_t reserved_08; char* mantissa; };
using STRFLT = _strflt*;
static_assert(offsetof(_strflt, sign) == 0x00);
static_assert(offsetof(_strflt, decpt) == 0x04);
static_assert(offsetof(_strflt, mantissa) == 0x0c);
static_assert(sizeof(_strflt) == 0x10);
extern "C" void* __cdecl FID_conflict__memcpy(void*, const void*, std::size_t);

errno_t __cdecl __fptostr(
    char* _Buf,
    std::size_t _SizeInBytes,
    int _Digits,
    STRFLT _PtFlt)
{
    char* pcVar6 = _PtFlt->mantissa;

    if ((_Buf == nullptr) || (_SizeInBytes == 0))
    {
        int* piVar1 = __errno();
        errno_t eVar7 = 0x16;
        *piVar1 = 0x16;
        FUN_1001189f();
        return eVar7;
    }

    *_Buf = '\0';

    int iVar2 = 0;
    if (0 < _Digits)
    {
        iVar2 = _Digits;
    }

    if ((static_cast<unsigned int>(iVar2) + 1U) < _SizeInBytes)
    {
        char* _Str = _Buf + 1;
        *_Buf = '0';

        char* pcVar3 = _Str;
        for (; 0 < _Digits; _Digits = _Digits + -1)
        {
            char cVar5 = *pcVar6;
            if (cVar5 == '\0')
            {
                cVar5 = '0';
            }
            else
            {
                pcVar6 = pcVar6 + 1;
            }

            *pcVar3 = cVar5;
            pcVar3 = pcVar3 + 1;
        }

        *pcVar3 = '\0';

        if ((-1 < _Digits) && ('4' < *pcVar6))
        {
            while (pcVar3 = pcVar3 + -1, *pcVar3 == '9')
            {
                *pcVar3 = '0';
            }

            *pcVar3 = *pcVar3 + '\x01';
        }

        if (*_Buf == '1')
        {
            _PtFlt->decpt = _PtFlt->decpt + 1;
        }
        else
        {
            std::size_t sVar4 = _strlen(_Str);
            FID_conflict__memcpy(_Buf, _Str, sVar4 + 1);
        }

        return 0;
    }

    int* piVar1 = __errno();
    errno_t eVar7 = 0x22;
    *piVar1 = 0x22;
    FUN_1001189f();
    return eVar7;
}