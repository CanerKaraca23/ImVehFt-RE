#include <cstdint>

struct __crt_locale_data
{
    int lc_codepage;
};

struct localeinfo_struct
{
    __crt_locale_data* locinfo;
};

extern "C" int __cdecl MultiByteToWideChar(
    unsigned int,
    unsigned int,
    char*,
    int,
    wchar_t*,
    int);

extern "C" int __cdecl GetStringTypeW(
    unsigned long,
    const wchar_t*,
    int,
    std::uint16_t*);

extern "C" void* __cdecl _malloc(unsigned int);
extern "C" void* __cdecl _memset(void*, int, unsigned int);
extern "C" void __cdecl __freea(void*);
extern "C" void __cdecl __alloca_probe_16(unsigned int);

extern "C" std::uint8_t stack0xffffffe8[];
extern "C" std::uint8_t stack0x00000000[];

int __cdecl __crtGetStringTypeA_stat(
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

    unsigned int size;
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
        return 0;

    if (static_cast<int>(cchWideChar) > 0 &&
        cchWideChar < 0x7ffffff1u)
    {
        size = cchWideChar * 2u + 8u;

        if (size < 0x401u)
        {
            __alloca_probe_16(size);

            puVar1 = reinterpret_cast<std::uint32_t*>(stack0xffffffe8);
            lpWideCharStr = reinterpret_cast<wchar_t*>(stack0xffffffe8);

            if (stack0x00000000 ==
                reinterpret_cast<std::uint8_t*>(0x18))
            {
                goto LAB_10019f47;
            }
        }
        else
        {
            puVar1 = static_cast<std::uint32_t*>(_malloc(size));
            lpWideCharStr = nullptr;

            if (puVar1 == nullptr)
                goto LAB_10019f47;

            *puVar1 = 0xddddu;
        }

        lpWideCharStr = reinterpret_cast<wchar_t*>(puVar1 + 2);
    }

LAB_10019f47:
    if (lpWideCharStr == nullptr)
        return 0;

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

    // __security_check_cookie is compiler-generated instrumentation.
    return result;
}