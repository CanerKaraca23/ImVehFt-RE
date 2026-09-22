#include <cstddef>
#include <cstdint>
#include <windows.h>

struct threadmbcinfostruct;

extern "C" std::uint32_t DAT_10029490;

extern "C" void __fastcall __security_check_cookie(
    std::uintptr_t stack_cookie);

extern "C" void* __cdecl _memset(
    void* destination,
    int value,
    std::size_t size);

extern "C" BOOL __cdecl ___crtGetStringTypeA(
    _locale_t,
    DWORD,
    LPCSTR,
    int,
    LPWORD,
    int,
    BOOL);

extern "C" int __cdecl ___crtLCMapStringA(
    _locale_t,
    LPCWSTR,
    DWORD,
    LPCSTR,
    int,
    LPSTR,
    int,
    int,
    BOOL);

void __cdecl setSBUpLow(threadmbcinfostruct* param_1)
{
    auto* const base = reinterpret_cast<std::uint8_t*>(param_1);

    const std::uintptr_t stack_cookie =
        static_cast<std::uintptr_t>(DAT_10029490) ^
        reinterpret_cast<std::uintptr_t>(&stack_cookie);

    _cpinfo local_51c;
    WORD local_508[256];
    CHAR local_308[256];
    CHAR local_208[256];
    CHAR local_108[256];

    const UINT code_page =
        *reinterpret_cast<const UINT*>(base + 0x04);

    const BOOL locale_flag =
        *reinterpret_cast<const BOOL*>(base + 0x0c);

    const LPCWSTR locale_name =
        *reinterpret_cast<const LPCWSTR*>(base + 0x0c);

    auto* const mbctype =
        reinterpret_cast<BYTE*>(base + 0x1d);

    auto* const mbcasemap =
        reinterpret_cast<CHAR*>(base + 0x11d);

    if (GetCPInfo(code_page, &local_51c) == 0)
    {
        std::uint32_t index = 0;

        do
        {
            CHAR* const map_entry = mbcasemap + index;

            if (index >= 0x41 && index < 0x5b)
            {
                BYTE* const type_entry = mbctype + index;
                *type_entry = static_cast<BYTE>(*type_entry | 0x10);

                const CHAR mapped =
                    static_cast<CHAR>(index) + ' ';

                *map_entry = mapped;
            }
            else
            {
                CHAR mapped;
                if (index >= 0x61 && index < 0x7b)
                {
                    BYTE* const type_entry = mbctype + index;
                    *type_entry = static_cast<BYTE>(*type_entry | 0x20);

                    mapped = static_cast<CHAR>(index) - 0x20;

                    goto LAB_1001442c_with_value;
                }

                *map_entry = '\0';
                goto LAB_1001442c_done;

            LAB_1001442c_with_value:
                *map_entry = mapped;
            }

        LAB_1001442c_done:
            index = index + 1;
        }
        while (index < 0x100);
    }
    else
    {
        std::uint32_t index = 0;

        do
        {
            local_108[index] = static_cast<CHAR>(index);
            index = index + 1;
        }
        while (index < 0x100);

        local_108[0] = ' ';

        if (local_51c.LeadByte[0] != 0)
        {
            BYTE* lead_byte = local_51c.LeadByte + 1;

            do
            {
                const std::uint32_t first =
                    static_cast<std::uint32_t>(local_51c.LeadByte[0]);

                if (first <= *lead_byte)
                {
                    _memset(
                        local_108 + first,
                        0x20,
                        (*lead_byte - first) + 1);
                }

                local_51c.LeadByte[0] = lead_byte[1];
                lead_byte = lead_byte + 2;
            }
            while (local_51c.LeadByte[0] != 0);
        }

        ___crtGetStringTypeA(
            static_cast<_locale_t>(nullptr),
            1,
            local_108,
            0x100,
            local_508,
            static_cast<int>(code_page),
            locale_flag);

        ___crtLCMapStringA(
            static_cast<_locale_t>(nullptr),
            locale_name,
            0x100,
            local_108,
            0x100,
            local_208,
            0x100,
            static_cast<int>(code_page),
            0);

        ___crtLCMapStringA(
            static_cast<_locale_t>(nullptr),
            locale_name,
            0x200,
            local_108,
            0x100,
            local_308,
            0x100,
            static_cast<int>(code_page),
            0);

        index = 0;

        do
        {
            CHAR mapped;
            BYTE* type_entry;

            if ((local_508[index] & 1) == 0)
            {
                if ((local_508[index] & 2) != 0)
                {
                    type_entry = mbctype + index;
                    *type_entry = static_cast<BYTE>(*type_entry | 0x20);

                    mapped = local_308[index];
                    goto LAB_100143cf;
                }

                mbcasemap[index] = '\0';
            }
            else
            {
                type_entry = mbctype + index;
                *type_entry = static_cast<BYTE>(*type_entry | 0x10);

                mapped = local_208[index];

            LAB_100143cf:
                mbcasemap[index] = mapped;
            }

            index = index + 1;
        }
        while (index < 0x100);
    }

    __security_check_cookie(stack_cookie);
}