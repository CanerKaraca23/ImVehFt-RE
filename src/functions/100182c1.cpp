#include <Windows.h>
#include <cstdint>
#include <cstddef>

extern "C" std::uintptr_t DAT_1003c420[];
extern "C" std::uint8_t DAT_10039a0c;

extern "C" int __cdecl FUN_1001b1a5(std::uint32_t*);
extern "C" unsigned long* __cdecl ___doserrno();
extern "C" int* __cdecl __errno();
extern "C" void __stdcall FUN_1001189f();
extern "C" std::uint32_t __cdecl __alloc_osfhnd();
extern "C" void __cdecl __dosmaperr(DWORD);
extern "C" void __cdecl __set_osfhnd(int, std::intptr_t);
extern "C" long __cdecl __lseek_nolock(int, long, int);
extern "C" int __cdecl __close_nolock(int);
extern "C" int __cdecl __read_nolock(int, void*, unsigned int);
extern "C" int __cdecl __chsize_nolock(int, std::int64_t);
extern "C" std::int64_t __cdecl __lseeki64_nolock(int, std::int64_t, int);
extern "C" int __cdecl __write(int, const void*, unsigned int);
extern "C" void __cdecl __free_osfhnd(int);
extern "C" void __cdecl __invoke_watson(
    const wchar_t*, const wchar_t*, const wchar_t*, unsigned int,
    std::uintptr_t);

extern "C" int __cdecl FUN_100182c1(
    std::uint32_t* param_1,
    LPCSTR param_2,
    std::uint32_t param_3,
    int param_4,
    std::uint8_t param_5)
{
    int unaff_EDI;
    __asm mov unaff_EDI, edi

    std::uint8_t bVar2;
    std::uint32_t file_handle = 0;
    int iVar3;
    std::uint32_t uVar4;
    unsigned long* puVar5;
    DWORD DVar7;
    long lVar8;
    int iVar9;
    HANDLE pvVar10;
    std::uint8_t bVar11;
    bool bVar12;
    std::int64_t lVar13;
    int iVar14;

    SECURITY_ATTRIBUTES local_34{};
    std::uint32_t local_28;
    HANDLE local_24;
    std::uint32_t local_20;
    DWORD local_1c;
    std::uint32_t local_18;
    std::uint32_t local_14;
    std::uint32_t local_10;
    int local_c;
    char local_8;
    std::uint8_t local_7;
    std::uint8_t local_6;
    std::uint8_t local_5;

    bVar12 = (param_3 & 0x80) == 0;
    local_28 = 0;
    local_6 = 0;
    local_c = 0;
    local_34.nLength = 0xc;
    local_34.lpSecurityDescriptor = nullptr;
    local_5 = bVar12 ? 0 : 0x10;
    local_34.bInheritHandle = static_cast<BOOL>(bVar12);

    iVar3 = FUN_1001b1a5(&local_28);
    if (iVar3 != 0)
        __invoke_watson(nullptr, nullptr, nullptr, 0, 0);

    if (((param_3 & 0x8000) == 0) &&
        (((param_3 & 0x74000) != 0) || (local_28 != 0x8000)))
        local_5 = local_5 | 0x80;

    uVar4 = param_3 & 3;
    if (uVar4 == 0)
        local_10 = 0x80000000;
    else
    {
        if (uVar4 == 1)
        {
            if (((param_3 & 8) == 0) || ((param_3 & 0x70000) == 0))
            {
                local_10 = 0x40000000;
                goto LAB_10018383;
            }
        }
        else if (uVar4 != 2)
            goto LAB_10018343;

        local_10 = 0xc0000000;
    }

LAB_10018383:
    if (param_4 == 0x10)
        local_18 = 0;
    else if (param_4 == 0x20)
        local_18 = 1;
    else if (param_4 == 0x30)
        local_18 = 2;
    else if (param_4 == 0x40)
        local_18 = 3;
    else
    {
        if (param_4 != 0x80)
        {
LAB_10018343:
            *___doserrno() = 0;
            file_handle = 0xffffffff;
            *__errno() = 0x16;
            FUN_1001189f();
            return 0x16;
        }

        local_18 = static_cast<std::uint32_t>(local_10 == 0x80000000);
    }

    uVar4 = param_3 & 0x700;
    if (uVar4 < 0x401)
    {
        if ((uVar4 == 0x400) || (uVar4 == 0))
            local_1c = 3;
        else if (uVar4 == 0x100)
            local_1c = 4;
        else
        {
            if (uVar4 == 0x200)
                goto LAB_10018445;
            if (uVar4 != 0x300)
                goto LAB_10018425;
            local_1c = 2;
        }
    }
    else
    {
        if (uVar4 != 0x500)
        {
            if (uVar4 == 0x600)
            {
LAB_10018445:
                local_1c = 5;
                goto LAB_10018455;
            }

            if (uVar4 != 0x700)
            {
LAB_10018425:
                *___doserrno() = 0;
                file_handle = 0xffffffff;
                *__errno() = 0x16;
                FUN_1001189f();
                return 0x16;
            }
        }

        local_1c = 1;
    }

LAB_10018455:
    local_14 = 0x80;

    if (((param_3 & 0x100) != 0) &&
        (-1 < static_cast<char>(
            static_cast<std::uint8_t>(~DAT_10039a0c) & param_5)))
        local_14 = 1;

    if ((param_3 & 0x40) != 0)
    {
        local_14 = local_14 | 0x4000000;
        local_10 = local_10 | 0x10000;
        local_18 = local_18 | 4;
    }

    if ((param_3 & 0x1000) != 0)
        local_14 = local_14 | 0x100;

    if ((param_3 & 0x20) == 0)
    {
        if ((param_3 & 0x10) != 0)
            local_14 = local_14 | 0x10000000;
    }
    else
        local_14 = local_14 | 0x8000000;

    file_handle = __alloc_osfhnd();

    if (file_handle == 0xffffffff)
    {
        *___doserrno() = 0;
        file_handle = 0xffffffff;
        *__errno() = 0x18;
        return *__errno();
    }

    *param_1 = 1;

    local_24 = CreateFileA(
        param_2, local_10, local_18, &local_34,
        local_1c, local_14, nullptr);

    if (local_24 == INVALID_HANDLE_VALUE)
    {
        if (((local_10 & 0xc0000000) == 0xc0000000) &&
            ((param_3 & 1) != 0))
        {
            local_10 = local_10 & 0x7fffffff;
            local_24 = CreateFileA(
                param_2, local_10, local_18, &local_34,
                local_1c, local_14, nullptr);

            if (local_24 != INVALID_HANDLE_VALUE)
                goto LAB_1001857d;
        }

        *reinterpret_cast<std::uint8_t*>(
            DAT_1003c420[static_cast<int>(file_handle) >> 5] +
            4 + (file_handle & 0x1f) * 0x40) &=
            0xfe;

        DVar7 = GetLastError();
        __dosmaperr(DVar7);
        goto LAB_1001856e;
    }

LAB_1001857d:
    DVar7 = GetFileType(local_24);

    if (DVar7 == 0)
    {
        *reinterpret_cast<std::uint8_t*>(
            DAT_1003c420[static_cast<int>(file_handle) >> 5] +
            4 + (file_handle & 0x1f) * 0x40) &=
            0xfe;

        DVar7 = GetLastError();
        __dosmaperr(DVar7);
        CloseHandle(local_24);

        if (DVar7 == 0)
            *__errno() = 0xd;

        goto LAB_1001856e;
    }

    if (DVar7 == 2)
        local_5 = local_5 | 0x40;
    else if (DVar7 == 3)
        local_5 = local_5 | 8;

    __set_osfhnd(
        static_cast<int>(file_handle),
        reinterpret_cast<std::intptr_t>(local_24));

    bVar11 = local_5 | 1;

    *reinterpret_cast<std::uint8_t*>(
        DAT_1003c420[static_cast<int>(file_handle) >> 5] +
        4 + (file_handle & 0x1f) * 0x40) = bVar11;

    *reinterpret_cast<std::uint8_t*>(
        DAT_1003c420[static_cast<int>(file_handle) >> 5] +
        0x24 + (file_handle & 0x1f) * 0x40) &=
        0x80;

    local_7 = local_5 & 0x48;

    if (local_7 == 0)
    {
        bVar2 = local_5 & 0x80;
        local_5 = bVar11;

        if (bVar2 == 0)
            goto LAB_100188e3;

        if ((param_3 & 2) == 0)
            goto LAB_100186b1;

        lVar8 = __lseek_nolock(static_cast<int>(file_handle), -1, 2);

        if (lVar8 == -1)
        {
            puVar5 = ___doserrno();
            bVar11 = local_5;

            if (*puVar5 == 0x83)
                goto LAB_100186b1;
        }
        else
        {
            local_8 = '\0';
            iVar3 = __read_nolock(
                static_cast<int>(file_handle), &local_8, 1);

            if ((((iVar3 != 0) || (local_8 != '\x1a')) ||
                (iVar3 = __chsize_nolock(
                    static_cast<int>(file_handle),
                    static_cast<std::int64_t>(
                        (static_cast<std::uint64_t>(
                            static_cast<std::uint32_t>(unaff_EDI)) << 32) |
                        static_cast<std::uint32_t>(lVar8 >> 0x1f))),
                    iVar3 != -1)) &&
                (lVar8 = __lseek_nolock(
                    static_cast<int>(file_handle), 0, 0),
                    bVar11 = local_5,
                    lVar8 != -1))
                goto LAB_100186b1;
        }

LAB_10018662:
        __close_nolock(static_cast<int>(file_handle));
        goto LAB_1001856e;
    }

LAB_100186b1:
    local_5 = bVar11;

    if ((local_5 & 0x80) != 0)
    {
        if ((param_3 & 0x74000) == 0)
        {
            if ((local_28 & 0x74000) == 0)
                param_3 = param_3 | 0x4000;
            else
                param_3 = param_3 | local_28 & 0x74000;
        }

        uVar4 = param_3 & 0x74000;

        if (uVar4 == 0x4000)
            local_6 = 0;
        else if ((uVar4 == 0x10000) || (uVar4 == 0x14000))
        {
            if ((param_3 & 0x301) == 0x301)
                goto LAB_10018720;
        }
        else if ((uVar4 == 0x20000) || (uVar4 == 0x24000))
        {
LAB_10018720:
            local_6 = 2;
        }
        else if ((uVar4 == 0x40000) || (uVar4 == 0x44000))
            local_6 = 1;

        if (((param_3 & 0x70000) != 0) &&
            (local_20 = 0, (local_5 & 0x40) == 0))
        {
            uVar4 = local_10 & 0xc0000000;

            if (uVar4 == 0x40000000)
            {
                if (local_1c == 0)
                    goto LAB_100188e3;

                if (2 < local_1c)
                {
                    if (local_1c < 5)
                    {
                        lVar13 = __lseeki64_nolock(
                            static_cast<int>(file_handle),
                            0x200000000LL,
                            unaff_EDI);

                        if (lVar13 == 0)
                            goto LAB_10018788;

                        lVar13 = __lseeki64_nolock(
                            static_cast<int>(file_handle),
                            0,
                            unaff_EDI);

                        uVar4 = static_cast<std::uint32_t>(lVar13) &
                            static_cast<std::uint32_t>(
                                static_cast<std::uint64_t>(lVar13) >> 32);

                        goto LAB_1001884d;
                    }

LAB_1001877f:
                    if (local_1c != 5)
                        goto LAB_100188e3;
                }

LAB_10018788:
                iVar3 = 0;

                if (local_6 == 1)
                {
                    local_20 = 0xbfbbef;
                    iVar14 = 3;
                }
                else
                {
                    if (local_6 != 2)
                        goto LAB_100188e3;

                    local_20 = 0xfeff;
                    iVar14 = 2;
                }

                do
                {
                    iVar9 = __write(
                        static_cast<int>(file_handle),
                        reinterpret_cast<std::uint8_t*>(&local_20) + iVar3,
                        iVar14 - iVar3);

                    if (iVar9 == -1)
                        goto LAB_10018662;

                    iVar3 = iVar3 + iVar9;
                }
                while (iVar3 < iVar14);
            }
            else
            {
                if (uVar4 != 0x80000000)
                {
                    if ((uVar4 == 0xc0000000) && (local_1c != 0))
                    {
                        if (2 < local_1c)
                        {
                            if (4 < local_1c)
                                goto LAB_1001877f;

                            lVar13 = __lseeki64_nolock(
                                static_cast<int>(file_handle),
                                0x200000000LL,
                                unaff_EDI);

                            if (lVar13 != 0)
                            {
                                lVar13 = __lseeki64_nolock(
                                    static_cast<int>(file_handle),
                                    0,
                                    unaff_EDI);

                                if (lVar13 == -1)
                                    goto LAB_10018662;

                                goto LAB_100187d3;
                            }
                        }

                        goto LAB_10018788;
                    }

                    goto LAB_100188e3;
                }

LAB_100187d3:
                iVar3 = __read_nolock(
                    static_cast<int>(file_handle), &local_20, 3);

                if (iVar3 == -1)
                    goto LAB_10018662;

                if (iVar3 == 2)
                {
LAB_1001885a:
                    if ((local_20 & 0xffff) == 0xfffe)
                    {
                        __close_nolock(static_cast<int>(file_handle));
                        *__errno() = 0x16;
                        return 0x16;
                    }

                    if ((local_20 & 0xffff) == 0xfeff)
                    {
                        lVar8 = __lseek_nolock(
                            static_cast<int>(file_handle), 2, 0);

                        if (lVar8 == -1)
                            goto LAB_10018662;

                        local_6 = 2;
                        goto LAB_100188e3;
                    }
                }
                else if (iVar3 == 3)
                {
                    if (local_20 == 0xbfbbef)
                    {
                        local_6 = 1;
                        goto LAB_100188e3;
                    }

                    goto LAB_1001885a;
                }

                uVar4 = static_cast<std::uint32_t>(
                    __lseek_nolock(
                        static_cast<int>(file_handle), 0, 0));

LAB_1001884d:
                if (uVar4 == 0xffffffff)
                    goto LAB_10018662;
            }
        }
    }

LAB_100188e3:
    *reinterpret_cast<std::uint8_t*>(
        DAT_1003c420[static_cast<int>(file_handle) >> 5] +
        0x24 + (file_handle & 0x1f) * 0x40) =
        *reinterpret_cast<std::uint8_t*>(
            DAT_1003c420[static_cast<int>(file_handle) >> 5] +
            0x24 + (file_handle & 0x1f) * 0x40) ^
        ((*reinterpret_cast<std::uint8_t*>(
            DAT_1003c420[static_cast<int>(file_handle) >> 5] +
            0x24 + (file_handle & 0x1f) * 0x40) ^ local_6) & 0x7f);

    *reinterpret_cast<std::uint8_t*>(
        DAT_1003c420[static_cast<int>(file_handle) >> 5] +
        0x24 + (file_handle & 0x1f) * 0x40) =
        static_cast<std::uint8_t>(param_3 >> 0x10) << 7 |
        *reinterpret_cast<std::uint8_t*>(
            DAT_1003c420[static_cast<int>(file_handle) >> 5] +
            0x24 + (file_handle & 0x1f) * 0x40) & 0x7f;

    if ((local_7 == 0) && ((param_3 & 8) != 0))
        *reinterpret_cast<std::uint8_t*>(
            DAT_1003c420[static_cast<int>(file_handle) >> 5] +
            4 + (file_handle & 0x1f) * 0x40) |= 0x20;

    if ((local_10 & 0xc0000000) != 0xc0000000)
        return local_c;

    if ((param_3 & 1) == 0)
        return local_c;

    CloseHandle(local_24);

    pvVar10 = CreateFileA(
        param_2,
        local_10 & 0x7fffffff,
        local_18,
        &local_34,
        3,
        local_14,
        nullptr);

    if (pvVar10 != INVALID_HANDLE_VALUE)
    {
        *reinterpret_cast<HANDLE*>(
            DAT_1003c420[static_cast<int>(file_handle) >> 5] +
            (file_handle & 0x1f) * 0x40) = pvVar10;
        return local_c;
    }

    DVar7 = GetLastError();
    __dosmaperr(DVar7);

    *reinterpret_cast<std::uint8_t*>(
        DAT_1003c420[static_cast<int>(file_handle) >> 5] +
        4 + (file_handle & 0x1f) * 0x40) &=
        0xfe;

    __free_osfhnd(file_handle);

LAB_1001856e:
    return *__errno();
}