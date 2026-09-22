#include <cstddef>
#include <cstdint>
#include <corecrt.h>
using undefined1 = std::uint8_t;
using undefined4 = std::uint32_t;
using uint = std::uint32_t;
using undefined = unsigned char;
using longlong = std::int64_t;
using ulonglong = std::uint64_t;
using undefined2 = std::uint16_t;
using undefined8 = std::uint64_t;
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
struct localeinfo_struct;
extern "C" std::uint32_t __cdecl __cftof2_l();
static __declspec(naked) std::uint32_t __cdecl CallCftof2ThiscallAbi(
    void*, int, std::size_t, char, localeinfo_struct*)
{
    __asm {
        push ebp
        mov ebp, esp
        mov ecx, dword ptr [ebp + 08h]
        push dword ptr [ebp + 18h]
        push dword ptr [ebp + 14h]
        push dword ptr [ebp + 10h]
        push dword ptr [ebp + 0ch]
        call __cftof2_l
        add esp, 10h
        mov esp, ebp
        pop ebp
        ret
    }
}
extern "C" std::uint32_t DAT_10029490;
extern "C" int* __cdecl FUN_1001dd12(
    std::uint32_t, std::uint32_t, int*, char*, std::size_t);
extern "C" errno_t __cdecl __fptostr(char*, std::size_t, int, _strflt*);
extern "C" void __stdcall FUN_1001189f(void);
extern "C" int* __cdecl __errno(void);
struct localeinfo_struct; // opaque Ghidra-signature pointer type; no fields accessed here
errno_t __cdecl __cftof_l(
    undefined4* param_1,
    undefined1* param_2,
    int param_3,
    size_t param_4,
    localeinfo_struct* param_5)
{
    int* piVar1;
    size_t sizeInBytes;
    errno_t result;
    _strflt local_30;
    char local_20[24];
    uint stackCookie;

    stackCookie = DAT_10029490 ^ reinterpret_cast<uint>(&stackCookie);

    result = 0x16;

    FUN_1001dd12(
        param_1[0],
        param_1[1],
        &local_30.sign,
        local_20,
        0x16);

    if (param_2 == nullptr)
    {
        piVar1 = __errno();
        *piVar1 = 0x16;
        FUN_1001189f();
    }
    else if (param_3 == 0)
    {
        piVar1 = __errno();
        *piVar1 = 0x16;
        FUN_1001189f();
    }
    else
    {
        sizeInBytes = 0xffffffff;

        if (param_3 != -1)
        {
            sizeInBytes = param_3 - static_cast<uint>(local_30.sign == 0x2d);
        }

        result = __fptostr(
            reinterpret_cast<char*>(param_2 + (local_30.sign == 0x2d)),
            sizeInBytes,
            static_cast<int>(local_30.decpt + param_4),
            &local_30);

        if (result == 0)
        {
            result = CallCftof2ThiscallAbi(
                param_2,
                param_3,
                param_4,
                '\0',
                param_5);
        }
        else
        {
            *param_2 = 0;
        }
    }

    __security_check_cookie(stackCookie);
    return result;
}