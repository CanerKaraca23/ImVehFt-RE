#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <windows.h>
#include <stdio.h>
extern "C" int* __cdecl __errno(void);
extern "C" void __stdcall FUN_1001189f(void);
extern "C" unsigned long* __cdecl ___doserrno(void);
extern "C" void __cdecl __dosmaperr(unsigned long);
extern "C" int __cdecl _isleadbyte(int);
extern "C" int __cdecl _mbtowc(wchar_t*, const char*, unsigned int);
extern "C" wchar_t __cdecl __putwch_nolock(wchar_t);
struct localeinfo_struct
{
    std::uint8_t reserved[0x14];
    struct { wchar_t* wlocale; } lc_category[1];
};
struct _ptiddata
{
    std::uint8_t reserved[0x6c];
    localeinfo_struct* ptlocinfo;
};
extern "C" _ptiddata* __cdecl __getptd(void);
extern std::uint32_t DAT_10029490;
extern std::uint8_t* DAT_1003c420[];
extern "C" void __cdecl __alloca_probe(void);
extern "C" long long __cdecl __lseeki64_nolock(int, long long, int);
extern "C" int __cdecl __isatty(int);
struct CRT_FILE_DESCRIPTOR
{
    HANDLE handle;
    std::uint32_t flags;
    std::uint8_t reserved_08[0x1c];
    std::uint8_t text_mode;
    std::uint8_t reserved_25[0x0f];
    char pending_lead_byte;
    std::uint8_t reserved_35[3];
    std::uint32_t pending_lead_count;
    std::uint8_t reserved_3c[4];
};
static_assert(offsetof(CRT_FILE_DESCRIPTOR, flags) == 0x04);
static_assert(offsetof(CRT_FILE_DESCRIPTOR, text_mode) == 0x24);
static_assert(offsetof(CRT_FILE_DESCRIPTOR, pending_lead_byte) == 0x34);
static_assert(offsetof(CRT_FILE_DESCRIPTOR, pending_lead_count) == 0x38);
static_assert(sizeof(CRT_FILE_DESCRIPTOR) == 0x40);
extern "C" int __cdecl __write_nolock(
    int _FileHandle,
    void* _Buf,
    unsigned int _MaxCharCount)
{
    char cVar1;
    WCHAR WVar3;
    wchar_t wVar4;
    int iVar7;
    int iVar14;
    int iVar15;
    int unaff_EBX = 0; // Ghidra ASM pushes zero as the CRT seek origin.
    std::uint8_t** piVar6 = nullptr;
    CRT_FILE_DESCRIPTOR* file = nullptr;
    unsigned int uVar11;
    unsigned int uVar13;
    unsigned short uVar16;
    unsigned int local_1ae8 = 0;
    WCHAR* local_1ae4 = nullptr;
    DWORD local_1adc = 0;
    WCHAR* local_1ad8 = nullptr;
    int local_1ad4 = 0;
    WCHAR* local_1ad0 = static_cast<WCHAR*>(_Buf);
    unsigned int local_1acc = 0;
    char local_1ac5 = 0;
    unsigned int local_1ac4 = 0;
    DWORD local_1ac0 = 0;
    WCHAR local_1abc[852];
    CHAR local_1414[3416];
    WCHAR local_6bc[854];
    unsigned short local_10 = 0;
    int result = -1;

    std::uint32_t local_8 =
        DAT_10029490 ^
        static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(&local_8) & 0xfffffffcU);

    __alloca_probe();

    if (_MaxCharCount == 0)
    {
        result = 0;
        goto epilogue;
    }

    if (_Buf == nullptr)
    {
        *___doserrno() = 0;
        *__errno() = 0x16;
        FUN_1001189f();
        goto epilogue;
    }

    piVar6 = &DAT_1003c420[_FileHandle >> 5];
    iVar15 = (_FileHandle & 0x1fU) * 0x40;

    file = reinterpret_cast<CRT_FILE_DESCRIPTOR*>(
        *piVar6 + iVar15);

    local_1ac5 =
        static_cast<char>(static_cast<char>(file->text_mode) * '\x02') >> 1;

    if ((local_1ac5 == '\x02' || local_1ac5 == '\x01') &&
        ((~_MaxCharCount & 1U) == 0))
    {
        *___doserrno() = 0;
        *__errno() = 0x16;
        FUN_1001189f();
        goto epilogue;
    }

    if ((file->flags & 0x20U) != 0)
        __lseeki64_nolock(_FileHandle, 0x200000000LL, unaff_EBX);

    iVar7 = __isatty(_FileHandle);

    if (iVar7 != 0 && (file->flags & 0x80U) != 0)
    {
        _ptiddata* p_Var8 = __getptd();
        wchar_t* pwVar2 = p_Var8->ptlocinfo->lc_category[0].wlocale;

        if (GetConsoleMode(
                file->handle,
                reinterpret_cast<LPDWORD>(&local_1ae4)) != 0 &&
            !(pwVar2 == nullptr && local_1ac5 == '\0'))
        {
            local_1ae4 = reinterpret_cast<WCHAR*>(
                static_cast<std::uintptr_t>(GetConsoleCP()));
            local_1ad8 = nullptr;
            local_1ac4 = 0;
            WCHAR* pWVar12 = local_1ad0;

            do
            {
                if (local_1ac5 == '\0')
                {
                    cVar1 = static_cast<char>(*pWVar12);
                    local_1ae8 = static_cast<unsigned int>(cVar1 == '\n');

                    if (file->pending_lead_count == 0)
                    {
                        iVar7 = _isleadbyte(
                            static_cast<int>(
                                (static_cast<std::uint32_t>(
                                     static_cast<std::int32_t>(cVar1 >> 7))
                                 << 16) |
                                static_cast<std::uint16_t>(
                                    static_cast<std::int16_t>(cVar1))));

                        if (iVar7 == 0)
                        {
                            uVar16 = 1;
                            iVar7 = _mbtowc(
                                reinterpret_cast<wchar_t*>(&local_1ac0),
                                reinterpret_cast<char*>(pWVar12),
                                uVar16);

                            if (iVar7 == -1)
                                break;
                        }
                        else
                        {
                            if (reinterpret_cast<char*>(
                                    static_cast<std::int32_t>(
                                        reinterpret_cast<std::uintptr_t>(
                                            local_1ad0)) +
                                    (_MaxCharCount -
                                     static_cast<std::int32_t>(
                                         reinterpret_cast<std::uintptr_t>(
                                             pWVar12)))) <
                                reinterpret_cast<char*>(2))
                            {
                                local_1acc = local_1acc + 1;
                                file->pending_lead_byte =
                                    static_cast<char>(*pWVar12);
                                file->pending_lead_count = 1;
                                break;
                            }

                            iVar7 = _mbtowc(
                                reinterpret_cast<wchar_t*>(&local_1ac0),
                                reinterpret_cast<char*>(pWVar12),
                                2);

                            if (iVar7 == -1)
                                break;

                            pWVar12 = reinterpret_cast<WCHAR*>(
                                reinterpret_cast<char*>(pWVar12) + 1);
                            local_1ac4 = local_1ac4 + 1;
                        }
                    }
                    else
                    {
                        *reinterpret_cast<unsigned char*>(&local_10) =
                            static_cast<unsigned char>(
                                file->pending_lead_byte);
                        file->pending_lead_count = 0;

                        uVar16 = 2;
                        *reinterpret_cast<unsigned char*>(
                            reinterpret_cast<char*>(&local_10) + 1) =
                            static_cast<unsigned char>(cVar1);

                        iVar7 = _mbtowc(
                            reinterpret_cast<wchar_t*>(&local_1ac0),
                            reinterpret_cast<char*>(&local_10),
                            uVar16);

                        if (iVar7 == -1)
                            break;
                    }

                    pWVar12 = reinterpret_cast<WCHAR*>(
                        reinterpret_cast<char*>(pWVar12) + 1);
                    local_1ac4 = local_1ac4 + 1;

                    DWORD count = WideCharToMultiByte(
                        static_cast<UINT>(
                            reinterpret_cast<std::uintptr_t>(local_1ae4)),
                        0,
                        reinterpret_cast<LPCWSTR>(&local_1ac0),
                        1,
                        reinterpret_cast<LPSTR>(&local_10),
                        5,
                        nullptr,
                        nullptr);

                    if (count == 0)
                        break;

                    if (WriteFile(
                            file->handle,
                            &local_10,
                            count,
                            reinterpret_cast<LPDWORD>(&local_1ad8),
                            nullptr) == 0)
                        goto LAB_100199c7;

                    local_1acc = local_1ac4 + local_1ad4;

                    if (static_cast<int>(
                            reinterpret_cast<std::uintptr_t>(local_1ad8)) <
                        static_cast<int>(count))
                        break;

                    if (local_1ae8 != 0)
                    {
                        *reinterpret_cast<unsigned char*>(&local_10) = '\r';

                        if (WriteFile(
                                file->handle,
                                &local_10,
                                1,
                                reinterpret_cast<LPDWORD>(&local_1ad8),
                                nullptr) == 0)
                            goto LAB_100199c7;

                        if (static_cast<int>(
                                reinterpret_cast<std::uintptr_t>(
                                    local_1ad8)) < 1)
                            break;

                        local_1ad4 = local_1ad4 + 1;
                        local_1acc = local_1acc + 1;
                    }
                }
                else
                {
                    if (local_1ac5 == '\x01' || local_1ac5 == '\x02')
                    {
                        local_1ac0 = static_cast<DWORD>(
                            static_cast<unsigned short>(*pWVar12));
                        local_1ae8 = static_cast<unsigned int>(
                            local_1ac0 == 10);
                        pWVar12 = pWVar12 + 1;
                        local_1ac4 = local_1ac4 + 2;

                        wVar4 = __putwch_nolock(
                            static_cast<wchar_t>(local_1ac0));

                        if (wVar4 != static_cast<wchar_t>(local_1ac0))
                            goto LAB_100199c7;

                        local_1acc = local_1acc + 2;

                        if (local_1ae8 != 0)
                        {
                            local_1ac0 = 0xd;
                            wVar4 = __putwch_nolock(L'\r');

                            if (wVar4 != static_cast<wchar_t>(local_1ac0))
                                goto LAB_100199c7;

                            local_1acc = local_1acc + 1;
                            local_1ad4 = local_1ad4 + 1;
                        }
                    }
                }
            }
            while (local_1ac4 < _MaxCharCount);

            goto finish;
        }
    }

    if ((file->flags & 0x80U) == 0)
    {
        if (WriteFile(
                file->handle,
                local_1ad0,
                _MaxCharCount,
                &local_1adc,
                nullptr) == 0)
            goto LAB_100199c7;

        local_1ac0 = 0;
        local_1acc = local_1adc;
        goto finish;
    }

    local_1ac0 = 0;

    if (local_1ac5 == '\0')
    {
        WCHAR* pWVar12 = local_1ad0;
        WCHAR* pWVar10 = nullptr;

        do
        {
            uVar13 = 0;
            uVar11 = static_cast<unsigned int>(
                reinterpret_cast<char*>(pWVar12) -
                reinterpret_cast<char*>(local_1ad0));
            pWVar10 = local_1abc;

            do
            {
                if (_MaxCharCount <= uVar11)
                    break;

                WVar3 = *pWVar12;
                pWVar12 = reinterpret_cast<WCHAR*>(
                    reinterpret_cast<char*>(pWVar12) + 1);
                uVar11 = uVar11 + 1;

                if (static_cast<char>(WVar3) == '\n')
                {
                    local_1ad4 = local_1ad4 + 1;
                    *reinterpret_cast<char*>(pWVar10) = '\r';
                    pWVar10 = reinterpret_cast<WCHAR*>(
                        reinterpret_cast<char*>(pWVar10) + 1);
                    uVar13 = uVar13 + 1;
                }

                *reinterpret_cast<char*>(pWVar10) =
                    static_cast<char>(WVar3);
                pWVar10 = reinterpret_cast<WCHAR*>(
                    reinterpret_cast<char*>(pWVar10) + 1);
                uVar13 = uVar13 + 1;
                local_1ae4 = pWVar12;
            }
            while (uVar13 < 0x13ff);

            if (WriteFile(
                    file->handle,
                    local_1abc,
                    static_cast<DWORD>(
                        reinterpret_cast<char*>(pWVar10) -
                        reinterpret_cast<char*>(local_1abc)),
                    &local_1adc,
                    nullptr) == 0)
                goto LAB_100199c7;

            local_1acc = local_1acc + local_1adc;
        }
        while (
            static_cast<int>(
                reinterpret_cast<char*>(pWVar10) -
                reinterpret_cast<char*>(local_1abc)) <=
                static_cast<int>(local_1adc) &&
            static_cast<unsigned int>(
                reinterpret_cast<char*>(pWVar12) -
                reinterpret_cast<char*>(local_1ad0)) < _MaxCharCount);

        goto finish;
    }

    if (local_1ac5 == '\x02')
    {
        WCHAR* pWVar12 = local_1ad0;
        WCHAR* pWVar10 = nullptr;

        do
        {
            local_1ac4 = 0;
            uVar11 = static_cast<unsigned int>(
                reinterpret_cast<char*>(pWVar12) -
                reinterpret_cast<char*>(local_1ad0));
            pWVar10 = local_1abc;

            do
            {
                if (_MaxCharCount <= uVar11)
                    break;

                WVar3 = *pWVar12;
                pWVar12 = pWVar12 + 1;
                uVar11 = uVar11 + 2;

                if (WVar3 == L'\n')
                {
                    local_1ad4 = local_1ad4 + 2;
                    *pWVar10 = L'\r';
                    pWVar10 = pWVar10 + 1;
                    local_1ac4 = local_1ac4 + 2;
                }

                local_1ac4 = local_1ac4 + 2;
                *pWVar10 = WVar3;
                pWVar10 = pWVar10 + 1;
                local_1ae4 = pWVar12;
            }
            while (local_1ac4 < 0x13fe);

            if (WriteFile(
                    file->handle,
                    local_1abc,
                    static_cast<DWORD>(
                        reinterpret_cast<char*>(pWVar10) -
                        reinterpret_cast<char*>(local_1abc)),
                    &local_1adc,
                    nullptr) == 0)
                goto LAB_100199c7;

            local_1acc = local_1acc + local_1adc;
        }
        while (
            static_cast<int>(
                reinterpret_cast<char*>(pWVar10) -
                reinterpret_cast<char*>(local_1abc)) <=
                static_cast<int>(local_1adc) &&
            static_cast<unsigned int>(
                reinterpret_cast<char*>(pWVar12) -
                reinterpret_cast<char*>(local_1ad0)) < _MaxCharCount);

        goto finish;
    }

    local_1ad8 = local_1ad0;

    do
    {
        local_1ac4 = 0;
        uVar11 = static_cast<unsigned int>(
            reinterpret_cast<char*>(local_1ad8) -
            reinterpret_cast<char*>(local_1ad0));
        WCHAR* pWVar12 = local_6bc;

        do
        {
            if (_MaxCharCount <= uVar11)
                break;

            WVar3 = *local_1ad8;
            local_1ad8 = local_1ad8 + 1;
            uVar11 = uVar11 + 2;

            if (WVar3 == L'\n')
            {
                *pWVar12 = L'\r';
                pWVar12 = pWVar12 + 1;
                local_1ac4 = local_1ac4 + 2;
            }

            local_1ac4 = local_1ac4 + 2;
            *pWVar12 = WVar3;
            pWVar12 = pWVar12 + 1;
        }
        while (local_1ac4 < 0x6a8);

        iVar14 = 0;
        iVar7 = WideCharToMultiByte(
            0xfde9,
            0,
            local_6bc,
            (static_cast<int>(
                 reinterpret_cast<std::uintptr_t>(pWVar12)) -
             static_cast<int>(
                 reinterpret_cast<std::uintptr_t>(local_6bc))) / 2,
            local_1414,
            0xd55,
            nullptr,
            nullptr);

        if (iVar7 == 0)
            goto LAB_100199c7;

        do
        {
            if (WriteFile(
                    file->handle,
                    local_1414 + iVar14,
                    iVar7 - iVar14,
                    &local_1adc,
                    nullptr) == 0)
            {
                local_1ac0 = GetLastError();
                break;
            }

            iVar14 = iVar14 + local_1adc;
        }
        while (iVar14 < iVar7);
    }
    while (
        iVar7 <= iVar14 &&
        (local_1acc =
             static_cast<unsigned int>(
                 reinterpret_cast<char*>(local_1ad8) -
                 reinterpret_cast<char*>(local_1ad0)),
         local_1acc < _MaxCharCount));

finish:
    if (local_1acc != 0)
    {
        result = static_cast<int>(local_1acc) - local_1ad4;
        goto epilogue;
    }

    if (local_1ac0 != 0)
    {
        if (local_1ac0 == 5)
        {
            *__errno() = 9;
            *___doserrno() = 5;
            goto epilogue;
        }

        __dosmaperr(local_1ac0);
        goto epilogue;
    }

    if ((file->flags & 0x40U) != 0 &&
        static_cast<char>(*local_1ad0) == '\x1a')
    {
        result = 0;
        goto epilogue;
    }

    *__errno() = 0x1c;
    *___doserrno() = 0;
    goto epilogue;

LAB_100199c7:
    local_1ac0 = GetLastError();
    goto finish;

epilogue:
    __security_check_cookie(local_8);
    return result;
}