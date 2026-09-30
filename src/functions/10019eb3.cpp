#include <cstdint>

extern "C" std::uint32_t DAT_10029490;
extern "C" void __fastcall __security_check_cookie(std::uintptr_t);

struct __crt_locale_data
{
    int lc_codepage;
};

struct localeinfo_struct
{
    __crt_locale_data* locinfo;
};

extern "C" int __stdcall MultiByteToWideChar(
    unsigned int,
    unsigned int,
    char*,
    int,
    wchar_t*,
    int);

extern "C" int __stdcall GetStringTypeW(
    unsigned long,
    const wchar_t*,
    int,
    std::uint16_t*);

extern "C" void* __cdecl _malloc(unsigned int);
extern "C" void* __cdecl _memset(void*, int, unsigned int);
extern "C" void __cdecl __freea(void*);
extern "C" void __stdcall __alloca_probe_16(void);

extern "C" int __cdecl __crtGetStringTypeA_stat(
    localeinfo_struct* param_1,
    unsigned long param_2,
    char* param_3,
    int param_4,
    std::uint16_t* param_5,
    int param_6,
    int param_7,
    int param_8)
{
    (void)param_8;

    std::uintptr_t stack_cookie = DAT_10029490 ^
        reinterpret_cast<std::uintptr_t>(&stack_cookie);

    unsigned int allocation_size;
    unsigned int cchWideChar;
    std::uint32_t* puVar1;
    int cchSrc;
    wchar_t* lpWideCharStr = nullptr;
    int result = 0;

    if (param_6 == 0)
        param_6 = param_1->locinfo->lc_codepage;

    cchWideChar = static_cast<unsigned int>(
        MultiByteToWideChar(
            static_cast<unsigned int>(param_6),
            static_cast<unsigned int>((param_7 != 0) * 8 + 1),
            param_3,
            param_4,
            nullptr,
            0));

    if (cchWideChar == 0)
        goto cleanup;

    if (static_cast<int>(cchWideChar) > 0 &&
        cchWideChar < 0x7ffffff1u)
    {
        allocation_size = cchWideChar * 2u + 8u;

        if (allocation_size < 0x401u)
        {
            __asm {
                mov eax, allocation_size
                call __alloca_probe_16
                mov puVar1, esp
            }

            lpWideCharStr = nullptr;
            if (puVar1 == nullptr)
            {
                goto LAB_10019f47;
            }

            *puVar1 = 0xccccu;
            lpWideCharStr = reinterpret_cast<wchar_t*>(puVar1 + 2);
        }
        else
        {
            puVar1 = static_cast<std::uint32_t*>(_malloc(allocation_size));
            lpWideCharStr = nullptr;

            if (puVar1 == nullptr)
                goto LAB_10019f47;

            *puVar1 = 0xddddu;
        }

        if (allocation_size >= 0x401u)
            lpWideCharStr = reinterpret_cast<wchar_t*>(puVar1 + 2);
    }

LAB_10019f47:
    if (lpWideCharStr == nullptr)
        goto cleanup;

    _memset(lpWideCharStr, 0, cchWideChar * 2u);

    cchSrc = MultiByteToWideChar(
        static_cast<unsigned int>(param_6),
        1u,
        param_3,
        param_4,
        lpWideCharStr,
        static_cast<int>(cchWideChar));

    if (cchSrc != 0)
    {
        result = GetStringTypeW(
            param_2,
            lpWideCharStr,
            cchSrc,
            param_5);
    }

    __freea(lpWideCharStr);

cleanup:
    __security_check_cookie(
        stack_cookie ^ reinterpret_cast<std::uintptr_t>(&stack_cookie));
    return result;
}
