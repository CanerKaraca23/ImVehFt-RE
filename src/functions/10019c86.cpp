#include <cstddef>
#include <cstdint>
#include <malloc.h>

#include <corecrt.h>
using longlong = std::int64_t;
using ulonglong = std::uint64_t;
using undefined = unsigned char;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined4 = std::uint32_t;
using undefined8 = std::uint64_t;
extern "C" void* __cdecl _malloc(std::size_t);
using LPCWSTR = const wchar_t*;
using LPWSTR = wchar_t*;
extern "C" int __stdcall MultiByteToWideChar(unsigned int, unsigned long, const char*, int, LPWSTR, int);
extern "C" int __stdcall LCMapStringW(unsigned long, unsigned long, LPCWSTR, int, LPWSTR, int);
extern "C" int __stdcall WideCharToMultiByte(unsigned int, unsigned long, LPCWSTR, int, char*, int, const char*, int*);

struct pthreadlocinfo
{
    std::uint32_t reserved_00;
    std::uint32_t lc_codepage;
};
struct pthreadmbcinfo;
struct localeinfo_struct
{
    pthreadlocinfo* locinfo;
    pthreadmbcinfo* mbcinfo;
};
static_assert(offsetof(pthreadlocinfo, lc_codepage) == 0x04);
static_assert(offsetof(localeinfo_struct, mbcinfo) == 0x04);
extern "C" void __cdecl __freea(void*);

int __cdecl __crtLCMapStringA_stat(
    localeinfo_struct* param_1,
    unsigned long param_2,
    unsigned long param_3,
    char* param_4,
    int param_5,
    char* param_6,
    int param_7,
    int param_8,
    int param_9)
{
    unsigned int uVar1;
    bool bVar2;
    char* pcVar3;
    int iVar4;
    unsigned int cchWideChar;
    unsigned int* puVar5;
    LPCWSTR lpDestStr;
    int iVar6;
    LPCWSTR local_10;
    unsigned int local_c;

    pcVar3 = param_4;
    iVar6 = param_5;

    if (0 < param_5)
    {
        do
        {
            iVar6 = iVar6 + -1;

            if (*pcVar3 == '\0')
                goto LAB_10019cb6;

            pcVar3 = pcVar3 + 1;
        }
        while (iVar6 != 0);

        iVar6 = -1;

    LAB_10019cb6:
        iVar6 = param_5 - iVar6;
        iVar4 = iVar6 + -1;
        bVar2 = iVar4 < param_5;
        param_5 = iVar4;

        if (bVar2)
            param_5 = iVar6;
    }

    local_c = 0;

    if (param_8 == 0)
        param_8 = param_1->locinfo->lc_codepage;

    cchWideChar = MultiByteToWideChar(
        param_8,
        (unsigned int)(param_9 != 0) * 8 + 1,
        param_4,
        param_5,
        nullptr,
        0);

    if (cchWideChar == 0)
        return 0;

    if ((static_cast<int>(cchWideChar) < 1) ||
        (0xffffffe0u / cchWideChar < 2))
    {
        local_10 = nullptr;
    }
    else
    {
        uVar1 = cchWideChar * 2 + 8;

        if (uVar1 < 0x401)
        {
            unsigned char* stack0xffffffe0 =
                static_cast<unsigned char*>(_alloca(uVar1));

            puVar5 = reinterpret_cast<unsigned int*>(stack0xffffffe0);
            local_10 = reinterpret_cast<LPCWSTR>(stack0xffffffe0);

            unsigned char* stack0x00000000 =
                stack0xffffffe0 + 0x20;

            if (stack0x00000000 !=
                reinterpret_cast<unsigned char*>(0x20))
            {
                local_10 = reinterpret_cast<LPCWSTR>(puVar5 + 2);
            }
        }
        else
        {
            puVar5 = static_cast<unsigned int*>(_malloc(uVar1));
            local_10 = nullptr;

            if (puVar5 != nullptr)
            {
                *puVar5 = 0xdddd;
                local_10 = reinterpret_cast<LPCWSTR>(puVar5 + 2);
            }
        }
    }

    if (local_10 == nullptr)
        return 0;

    iVar6 = MultiByteToWideChar(
        param_8,
        1,
        param_4,
        param_5,
        const_cast<LPWSTR>(local_10),
        cchWideChar);

    if ((iVar6 != 0) &&
        (local_c = LCMapStringW(
             param_2,
             param_3,
             local_10,
             cchWideChar,
             nullptr,
             0),
         local_c != 0))
    {
        if ((param_3 & 0x400) == 0)
        {
            if ((static_cast<int>(local_c) < 1) ||
                (0xffffffe0u / local_c < 2))
            {
                lpDestStr = nullptr;
            }
            else
            {
                uVar1 = local_c * 2 + 8;

                if (uVar1 < 0x401)
                {
                    unsigned char* stack0xffffffe8 =
                        static_cast<unsigned char*>(_alloca(uVar1));

                    unsigned char* stack0x00000000 =
                        stack0xffffffe8 - 0x18;

                    if (stack0x00000000 ==
                        reinterpret_cast<unsigned char*>(0x20))
                    {
                        goto LAB_10019e4f;
                    }

                    lpDestStr =
                        reinterpret_cast<LPCWSTR>(stack0xffffffe8);
                }
                else
                {
                    lpDestStr =
                        static_cast<LPCWSTR>(_malloc(uVar1));

                    if (lpDestStr != nullptr)
                    {
                        const_cast<LPWSTR>(lpDestStr)[0] = L'\xdddd';
                        const_cast<LPWSTR>(lpDestStr)[1] = L'\0';
                        lpDestStr = lpDestStr + 4;
                    }
                }
            }

            if (lpDestStr != nullptr)
            {
                iVar6 = LCMapStringW(
                    param_2,
                    param_3,
                    local_10,
                    cchWideChar,
                    const_cast<LPWSTR>(lpDestStr),
                    local_c);

                if (iVar6 != 0)
                {
                    if (param_7 == 0)
                    {
                        param_7 = 0;
                        param_6 = nullptr;
                    }

                    local_c = WideCharToMultiByte(
                        param_8,
                        0,
                        lpDestStr,
                        local_c,
                        param_6,
                        param_7,
                        nullptr,
                        nullptr);
                }

                __freea(const_cast<LPWSTR>(lpDestStr));
            }
        }
        else if ((param_7 != 0) &&
                 (static_cast<int>(local_c) <= param_7))
        {
            LCMapStringW(
                param_2,
                param_3,
                local_10,
                cchWideChar,
                reinterpret_cast<LPWSTR>(param_6),
                param_7);
        }
    }

LAB_10019e4f:
    __freea(const_cast<LPWSTR>(local_10));
    return local_c;
}