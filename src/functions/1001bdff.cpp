#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
struct _strflt
{
    int sign;       // FUN_1001dd12 stores at +0x00
    int decpt;      // stores at +0x04
    int nchar;      // stores at +0x08
    char* lstring;  // stores at +0x0c
};
static_assert(offsetof(_strflt, sign) == 0x00);
static_assert(offsetof(_strflt, decpt) == 0x04);
static_assert(offsetof(_strflt, nchar) == 0x08);
static_assert(offsetof(_strflt, lstring) == 0x0c);
static_assert(sizeof(_strflt) == 0x10);
struct localeinfo_struct; // opaque Ghidra-signature pointer type; no fields accessed here
#include <cstddef>
#include <cstdint>

extern "C" std::uint32_t DAT_10029490;

extern "C" int* __cdecl FUN_1001dd12(
    std::uint32_t,
    std::uint32_t,
    int*,
    char*,
    std::size_t);

extern "C" int* __cdecl __errno();
extern "C" void __stdcall FUN_1001189f();

extern "C" errno_t __cdecl __fptostr(
    char*,
    std::size_t,
    int,
    _strflt*);

extern "C" int __cdecl FUN_1001bc9e(
    std::uint32_t,
    int,
    int,
    int*,
    char,
    localeinfo_struct*);


void __cdecl __cftoe_l(
    std::uint32_t* param_1,
    std::uint8_t* param_2,
    std::uint32_t param_3,
    int param_4,
    int param_5,
    localeinfo_struct* param_6)
{
    int* piVar1;
    std::size_t sizeInBytes;
    errno_t error;
    _strflt local_30;
    char local_20[24];
    std::uint32_t local_8;

    local_8 = DAT_10029490 ^
        static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(&local_8));

    FUN_1001dd12(
        param_1[0],
        param_1[1],
        &local_30.sign,
        local_20,
        0x16);

    if ((param_2 == nullptr) || (param_3 == 0))
    {
        piVar1 = __errno();
        *piVar1 = 0x16;
        FUN_1001189f();
    }
    else
    {
        if (param_3 == 0xffffffff)
        {
            sizeInBytes = 0xffffffff;
        }
        else
        {
            sizeInBytes =
                (param_3 - (local_30.sign == 0x2d))
                - static_cast<std::uint32_t>(0 < param_4);
        }

        error = __fptostr(
            reinterpret_cast<char*>(
                param_2
                + static_cast<std::uint32_t>(0 < param_4)
                + static_cast<std::uint32_t>(local_30.sign == 0x2d)),
            sizeInBytes,
            param_4 + 1,
            &local_30);

        if (error == 0)
        {
            FUN_1001bc9e(
                param_3,
                param_4,
                param_5,
                &local_30.sign,
                '\0',
                param_6);
        }
        else
        {
            *param_2 = 0;
        }
    }

    __security_check_cookie(
        local_8 ^
        static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(&local_8)));
}