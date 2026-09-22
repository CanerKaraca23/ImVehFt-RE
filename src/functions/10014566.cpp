#include <cstddef>
#include <cstdint>

using BYTE = std::uint8_t;
using BOOL = int;

struct _cpinfo
{
    std::uint32_t MaxCharSize;
    BYTE DefaultChar[2];
    BYTE LeadByte[12];
};

extern std::uint32_t DAT_10029490;
extern std::uint32_t DAT_100298d0[];
extern BYTE DAT_100298cc[];
extern BYTE DAT_100298e0[];
extern int DAT_10039a58;

extern "C" int __cdecl getSystemCP(void);

static int __cdecl getSystemCP_from_esi(int code_page)
{
    int result;
    __asm {
        push esi
        mov esi, code_page
        call getSystemCP
        mov result, eax
        pop esi
    }
    return result;
}


extern "C" void __cdecl setSBCS(void*);
extern "C" int __cdecl CPtoLCID(int);
extern "C" void __cdecl setSBUpLow(void*);
extern "C" BOOL __stdcall IsValidCodePage(std::uint32_t);
extern "C" BOOL __stdcall GetCPInfo(std::uint32_t, _cpinfo*);
extern "C" void* __cdecl _memset(void*, int, std::size_t);
extern "C" void __fastcall __security_check_cookie(std::uintptr_t);

extern int extraout_ECX;                  // Unresolved decompiler register value.
extern std::uint32_t extraout_EDX;       // Unresolved decompiler register value.

extern "C" std::uint32_t __cdecl
__setmbcp_nolock(std::uint32_t param_1, int param_2)
{
    const std::uint32_t stack_cookie = DAT_10029490 ^
        static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(&stack_cookie));
    std::uint32_t result = 0;

    const std::uint32_t system_code_page = static_cast<std::uint32_t>(
        getSystemCP_from_esi(static_cast<int>(param_1)));

    if (system_code_page != 0)
    {
        std::uint32_t table_index = 0;

        for (std::uint32_t table_offset = 0;
             table_offset < 0xF0;
             table_offset += 0x30, ++table_index)
        {
            if (DAT_100298d0[table_offset / sizeof(std::uint32_t)] ==
                system_code_page)
            {
                _memset(reinterpret_cast<void*>(param_2 + 0x1C), 0, 0x101);

                std::uint32_t range_table = 0;
                BYTE* row = DAT_100298e0 + table_index * 0x30;

                do
                {
                    for (; row[0] != 0 && row[1] != 0; row += 2)
                    {
                        BYTE upper = row[1];

                        for (std::uint32_t value = row[0];
                             value <= upper;
                             ++value)
                        {
                            auto* mbctype =
                                reinterpret_cast<BYTE*>(param_2 + 0x1D + value);

                            *mbctype |= DAT_100298cc[range_table];
                            upper = row[1];
                        }
                    }

                    ++range_table;
                    row = DAT_100298e0 + table_index * 0x30 +
                          range_table * 8;
                }
                while (range_table < 4);

                *reinterpret_cast<std::uint32_t*>(param_2 + 0x04) =
                    system_code_page;
                *reinterpret_cast<std::uint32_t*>(param_2 + 0x08) = 1;
                *reinterpret_cast<int*>(param_2 + 0x0C) =
                    CPtoLCID(static_cast<int>(param_1));

                auto* destination =
                    reinterpret_cast<std::uint16_t*>(param_2 + 0x10);

                // The source offset is unresolved in the supplied decompilation.
                auto* source = reinterpret_cast<std::uint16_t*>(
                    reinterpret_cast<BYTE*>(DAT_100298d0) +
                    0x04 + extraout_ECX);

                for (int count = 6; count != 0; --count)
                    *destination++ = *source++;

                setSBUpLow(reinterpret_cast<void*>(param_2));
                result = 0;
                goto finish;
            }
        }

        if (system_code_page == 65000 ||
            system_code_page == 0xFDE9 ||
            IsValidCodePage(system_code_page & 0xFFFF) == 0)
        {
            result = 0xFFFFFFFF;
            goto finish;
        }

        _cpinfo cp_info{};

        if (GetCPInfo(system_code_page, &cp_info) != 0)
        {
            _memset(reinterpret_cast<void*>(param_2 + 0x1C), 0, 0x101);

            *reinterpret_cast<std::uint32_t*>(param_2 + 0x04) =
                system_code_page;
            *reinterpret_cast<std::uint32_t*>(param_2 + 0x0C) = 0;

            if (cp_info.MaxCharSize < 2)
            {
                *reinterpret_cast<std::uint32_t*>(param_2 + 0x08) = 0;
            }
            else
            {
                if (cp_info.LeadByte[0] != 0)
                {
                    BYTE* lead_byte = cp_info.LeadByte + 1;

                    do
                    {
                        const BYTE end = *lead_byte;
                        if (end == 0)
                            break;

                        for (std::uint32_t value = lead_byte[-1];
                             value <= end;
                             ++value)
                        {
                            auto* mbctype =
                                reinterpret_cast<BYTE*>(param_2 + 0x1D + value);

                            *mbctype |= 4;
                        }

                        lead_byte += 2;
                    }
                    while (lead_byte[0] != 0);
                }

                auto* mbctype =
                    reinterpret_cast<BYTE*>(param_2 + 0x1E);

                for (int count = 0xFE; count != 0; --count)
                    *mbctype++ |= 8;

                *reinterpret_cast<int*>(param_2 + 0x0C) =
                    CPtoLCID(static_cast<int>(param_1));

                // Unresolved decompiler register value.
                *reinterpret_cast<std::uint32_t*>(param_2 + 0x08) =
                    extraout_EDX;
            }

            *reinterpret_cast<std::uint32_t*>(param_2 + 0x10) = 0;
            *reinterpret_cast<std::uint32_t*>(param_2 + 0x14) = 0;
            *reinterpret_cast<std::uint32_t*>(param_2 + 0x18) = 0;

            setSBUpLow(reinterpret_cast<void*>(param_2));
            result = 0;
            goto finish;
        }

        if (DAT_10039a58 == 0)
        {
            result = 0xFFFFFFFF;
            goto finish;
        }
    }

    setSBCS(reinterpret_cast<void*>(param_2));
    result = 0;

finish:
    __security_check_cookie(
        stack_cookie ^ static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(&stack_cookie)));
    return result;
}
