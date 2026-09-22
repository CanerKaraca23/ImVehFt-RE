#include <cstddef>
#include <cstdint>

extern "C" int* __cdecl __errno(void);
extern "C" void __stdcall FUN_1001189f(void);
using undefined1 = std::uint8_t;
using undefined4 = std::uint32_t;
using undefined = unsigned char;
using uint = std::uint32_t;

struct localeinfo_struct;
struct _strflt
{
    int sign;
    int decpt;
    std::uint32_t reserved_08;
    char* mantissa;
};

static_assert(offsetof(_strflt, sign) == 0);
static_assert(offsetof(_strflt, decpt) == 4);
static_assert(offsetof(_strflt, mantissa) == 0x0c);
static_assert(sizeof(_strflt) == 0x10);

struct Cftof2Thiscall
{
    std::uint32_t __thiscall __cftof2_l(
        std::uint32_t, std::size_t, char, localeinfo_struct*);
};

extern "C" std::uint32_t DAT_10029490;
extern "C" int* __cdecl FUN_1001dd12(
    std::uint32_t, std::uint32_t, int*, char*, std::size_t);
extern "C" int __cdecl __fptostr(char*, std::size_t, int, _strflt*);
extern "C" int __cdecl FUN_1001bc9e(
    std::uint32_t, int, int, int*, char, localeinfo_struct*);

void __cdecl __cftog_l(
    undefined4* param_1,
    undefined1* param_2,
    uint param_3,
    size_t param_4,
    int param_5,
    localeinfo_struct* param_6)
{
    char* pcVar1;
    int* piVar2;
    errno_t eVar3;
    size_t sizeInBytes;
    int iVar4;
    char* pcVar5;
    _strflt local_30;
    char local_20[24];
    uint stackCookie;

    stackCookie = DAT_10029490 ^ reinterpret_cast<uint>(&stackCookie);

    FUN_1001dd12(
        param_1[0],
        param_1[1],
        &local_30.sign,
        local_20,
        0x16);

    if ((param_2 == nullptr) || (param_3 == 0))
    {
        piVar2 = __errno();
        *piVar2 = 0x16;
        FUN_1001189f();
    }
    else
    {
        iVar4 = local_30.decpt + -1;

        if (param_3 == 0xffffffff)
        {
            sizeInBytes = 0xffffffff;
        }
        else
        {
            sizeInBytes = param_3 - (local_30.sign == 0x2d);
        }

        char* output = reinterpret_cast<char*>(param_2);
        eVar3 = __fptostr(
            output + (local_30.sign == 0x2d),
            sizeInBytes,
            param_4,
            &local_30);

        if (eVar3 == 0)
        {
            local_30.decpt = local_30.decpt + -1;

            if ((local_30.decpt < -4) ||
                ((int)param_4 <= local_30.decpt))
            {
                FUN_1001bc9e(
                    param_3,
                    param_4,
                    param_5,
                    &local_30.sign,
                    '\x01',
                    param_6);
            }
            else
            {
                pcVar1 = output + (local_30.sign == 0x2d);

                if (iVar4 < local_30.decpt)
                {
                    do
                    {
                        pcVar5 = pcVar1;
                        pcVar1 = pcVar5 + 1;
                    }
                    while (*pcVar5 != '\0');

                    pcVar5[-1] = '\0';
                }

                reinterpret_cast<Cftof2Thiscall*>(param_2)->__cftof2_l(
                    param_3,
                    param_4,
                    '\x01',
                    param_6);
            }
        }
        else
        {
            *param_2 = 0;
        }
    }

    __security_check_cookie(stackCookie);
}