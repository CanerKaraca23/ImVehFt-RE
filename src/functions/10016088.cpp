#include <cstddef>
#include <cstdint>
#include <windows.h>

extern "C" std::uint32_t DAT_1003c418;
extern "C" std::uint8_t* DAT_1003c420[];
extern "C" std::uint8_t DAT_10029c30[256];
extern "C" int unaff_EDI;

extern "C" unsigned long* __cdecl ___doserrno();
extern "C" int* __cdecl __errno();
extern "C" void __stdcall FUN_1001189f();
extern "C" void* __cdecl __malloc_crt(std::size_t);
extern "C" long long __cdecl __lseeki64_nolock(int, long long, int);
extern "C" void __cdecl __dosmaperr(unsigned long);
extern "C" void __cdecl _free(void*);

extern "C" int __cdecl __read_nolock(
    int _FileHandle,
    void* _DstBuf,
    std::uint32_t _MaxCharCount)
{
    std::uint32_t uVar1 = _MaxCharCount;
    std::uint8_t bVar2;
    std::int16_t sVar3;
    std::uint32_t uVar6;
    BOOL BVar8;
    unsigned long uVar10;
    std::uint8_t* pbVar7;
    std::uint8_t* pbVar11;
    int iVar12;
    long long lVar15;
    // The assembly fallback writes CR (0x0D); the LF branch overrides it with 0x0A.
    std::uint16_t uVar16 = 0x0d;
    std::uint32_t local_1c = 0;
    int local_18 = -2;
    std::uint8_t* local_14 = nullptr;
    std::uint8_t* local_10 = nullptr;
    std::uint16_t local_c = 0;
    char local_6 = 0;
    char local_5 = 0;

    if (_FileHandle == -2) {
        *___doserrno() = 0;
        *__errno() = 9;
        return -1;
    }

    if ((_FileHandle < 0) ||
        (DAT_1003c418 <= static_cast<std::uint32_t>(_FileHandle))) {
        *___doserrno() = 0;
        *__errno() = 9;
        FUN_1001189f();
        return -1;
    }

    std::uint8_t* file =
        DAT_1003c420[_FileHandle >> 5] +
        ((_FileHandle & 0x1fU) * 0x40U);

    std::uint8_t& flags = file[4];
    std::uint8_t& pending_05 = file[5];
    std::uint8_t& multibyte_type = file[0x24];
    std::uint8_t& pending_25 = file[0x25];
    std::uint8_t& pending_26 = file[0x26];

    if ((flags & 1) == 0) {
        *___doserrno() = 0;
        *__errno() = 9;
        goto LAB_10016187;
    }

    if (_MaxCharCount >= 0x80000000U)
        goto LAB_10016175;

    if ((_MaxCharCount == 0) || ((flags & 2) != 0))
        return 0;

    if (_DstBuf == nullptr)
        goto LAB_10016175;

    local_6 = static_cast<char>(
        static_cast<signed char>(multibyte_type * '\x02') >> 1);

    if (local_6 == '\x01') {
        if ((~_MaxCharCount & 1U) == 0)
            goto LAB_10016175;

        uVar6 = _MaxCharCount >> 1;
        _MaxCharCount = 4;

        if (3 < uVar6)
            _MaxCharCount = uVar6;

        local_14 = static_cast<std::uint8_t*>(
            __malloc_crt(_MaxCharCount));

        if (local_14 == nullptr) {
            *__errno() = 0x0c;
            *___doserrno() = 8;
            return -1;
        }

        lVar15 = __lseeki64_nolock(
            _FileHandle,
            0x100000000LL,
            unaff_EDI);

        *reinterpret_cast<std::uint32_t*>(file + 0x28) =
            static_cast<std::uint32_t>(lVar15);
        *reinterpret_cast<std::uint32_t*>(file + 0x2c) =
            static_cast<std::uint32_t>(
                static_cast<std::uint64_t>(lVar15) >> 32);
    }
    else {
        if (local_6 == '\x02') {
            if ((~_MaxCharCount & 1U) == 0)
                goto LAB_10016175;

            _MaxCharCount &= 0xfffffffeU;
        }

        local_14 = static_cast<std::uint8_t*>(_DstBuf);
    }

    pbVar11 = local_14;
    pbVar7 = pbVar11;
    uVar6 = _MaxCharCount;

    if (((flags & 0x48) != 0) &&
        (pending_05 != 10) &&
        (_MaxCharCount != 0)) {
        uVar6 = _MaxCharCount - 1;
        *pbVar11 = pending_05;
        pbVar7 = pbVar11 + 1;
        local_10 = reinterpret_cast<std::uint8_t*>(1);
        pending_05 = 10;

        if ((local_6 != '\0') &&
            (pending_25 != 10) &&
            (uVar6 != 0)) {
            *pbVar7 = pending_25;
            pbVar7 = pbVar11 + 2;
            uVar6 = _MaxCharCount - 2;
            local_10 = reinterpret_cast<std::uint8_t*>(2);
            pending_25 = 10;

            if ((local_6 == '\x01') &&
                (pending_26 != 10) &&
                (uVar6 != 0)) {
                *pbVar7 = pending_26;
                pbVar7 = pbVar11 + 3;
                uVar6 = _MaxCharCount - 3;
                local_10 = reinterpret_cast<std::uint8_t*>(3);
                pending_26 = 10;
            }
        }
    }

    _MaxCharCount = uVar6;

    BVar8 = ReadFile(
        reinterpret_cast<HANDLE>(
            *reinterpret_cast<std::uintptr_t*>(file)),
        pbVar7,
        _MaxCharCount,
        reinterpret_cast<LPDWORD>(&local_1c),
        nullptr);

    if ((BVar8 == 0) ||
        (static_cast<std::int32_t>(local_1c) < 0) ||
        (_MaxCharCount < local_1c)) {
        uVar10 = GetLastError();

        if (uVar10 != 5) {
            if (uVar10 == 0x6d) {
                local_18 = 0;
                goto LAB_10016494;
            }

            goto LAB_10016489;
        }

        *__errno() = 9;
        *___doserrno() = 5;
    }
    else {
        local_10 = reinterpret_cast<std::uint8_t*>(
            reinterpret_cast<std::uintptr_t>(local_10) + local_1c);

        pbVar7 = file + 4;

        if ((*pbVar7 & 0x80) == 0)
            goto LAB_10016494;

        if (local_6 == '\x02') {
            if ((local_1c == 0) ||
                (*reinterpret_cast<std::int16_t*>(pbVar11) != 10))
                *pbVar7 &= 0xfb;
            else
                *pbVar7 |= 4;

            local_10 = local_14 +
                reinterpret_cast<std::uintptr_t>(local_10);
            _MaxCharCount = reinterpret_cast<std::uintptr_t>(local_14);
            pbVar11 = local_14;

            if (local_14 < local_10) {
                do {
                    sVar3 = *reinterpret_cast<std::int16_t*>(
                        _MaxCharCount);

                    if (sVar3 == 0x1a) {
                        if ((*pbVar7 & 0x40) == 0)
                            *pbVar7 |= 2;
                        else {
                            *reinterpret_cast<std::uint16_t*>(pbVar11) =
                                *reinterpret_cast<std::uint16_t*>(
                                    _MaxCharCount);
                            pbVar11 += 2;
                        }
                        break;
                    }

                    if (sVar3 == 0x0d) {
                        if (_MaxCharCount < reinterpret_cast<std::uintptr_t>(local_10) - 2u) {
                            if (*reinterpret_cast<std::int16_t*>(
                                    _MaxCharCount + 2) == 10) {
                                uVar1 = _MaxCharCount + 4;
                                goto LAB_10016534;
                            }

LAB_100165c7:
                            _MaxCharCount += 2;
                            uVar16 = 0xd;
                            goto LAB_100165c9;
                        }

                        uVar1 = _MaxCharCount + 2;

                        BVar8 = ReadFile(
                            reinterpret_cast<HANDLE>(
                                *reinterpret_cast<std::uintptr_t*>(file)),
                            &local_c,
                            2,
                            reinterpret_cast<LPDWORD>(&local_1c),
                            nullptr);

                        if (((BVar8 == 0) &&
                             (GetLastError() != 0)) ||
                            (local_1c == 0))
                            goto LAB_100165c7;

                        if ((file[4] & 0x48) == 0) {
                            if ((pbVar11 == local_14) &&
                                (local_c == 10))
                                goto LAB_10016534;

                            __lseeki64_nolock(
                                _FileHandle,
                                0x1ffffffffLL,
                                unaff_EDI);

                            if (local_c == 10)
                                goto LAB_100165d0;

                            goto LAB_100165c7;
                        }

                        if (local_c == 10) {
LAB_10016534:
                            _MaxCharCount = uVar1;
                            uVar16 = 10;
                            goto LAB_100165c9;
                        }

                        pbVar11[0] = 0xd;
                        pbVar11[1] = 0;
                        pending_05 = static_cast<std::uint8_t>(local_c);
                        pending_25 = static_cast<std::uint8_t>(local_c >> 8);
                        pending_26 = 10;
                        _MaxCharCount = uVar1;

LAB_100165c9:
                        *reinterpret_cast<std::uint16_t*>(pbVar11) = uVar16;
                    }
                    else {
                        *reinterpret_cast<std::uint16_t*>(pbVar11) =
                            static_cast<std::uint16_t>(sVar3);
                        uVar1 = _MaxCharCount + 2;
                    }

                    pbVar11 += 2;

LAB_100165d0:
                    _MaxCharCount = uVar1;
                }
                while (_MaxCharCount < reinterpret_cast<std::uintptr_t>(local_10));
            }

            local_10 = reinterpret_cast<std::uint8_t*>(
                reinterpret_cast<std::uintptr_t>(pbVar11) -
                reinterpret_cast<std::uintptr_t>(local_14));

            goto LAB_10016494;
        }

        if ((local_1c == 0) || (*pbVar11 != 10))
            *pbVar7 &= 0xfb;
        else
            *pbVar7 |= 4;

        local_10 = local_14 +
            reinterpret_cast<std::uintptr_t>(local_10);
        _MaxCharCount = reinterpret_cast<std::uintptr_t>(local_14);
        pbVar11 = local_14;

        if (local_14 < local_10) {
            do {
                bVar2 = *reinterpret_cast<std::uint8_t*>(
                    _MaxCharCount);

                if (bVar2 == 0x1a) {
                    if ((file[4] & 0x40) == 0)
                        file[4] |= 2;
                    else {
                        *pbVar11 =
                            *reinterpret_cast<std::uint8_t*>(
                                _MaxCharCount);
                        pbVar11++;
                    }
                    break;
                }

                if (bVar2 == 0xd) {
                    if (_MaxCharCount < reinterpret_cast<std::uintptr_t>(local_10) - 1u) {
                        if (*reinterpret_cast<std::uint8_t*>(
                                _MaxCharCount + 1) == '\n') {
                            uVar6 = _MaxCharCount + 2;
                            goto LAB_10016314;
                        }

LAB_1001638b:
                        _MaxCharCount++;
                        *pbVar11 = 0xd;
                    }
                    else {
                        uVar6 = _MaxCharCount + 1;

                        BVar8 = ReadFile(
                            reinterpret_cast<HANDLE>(
                                *reinterpret_cast<std::uintptr_t*>(file)),
                            &local_5,
                            1,
                            reinterpret_cast<LPDWORD>(&local_1c),
                            nullptr);

                        if (((BVar8 == 0) &&
                             (GetLastError() != 0)) ||
                            (local_1c == 0))
                            goto LAB_1001638b;

                        if ((file[4] & 0x48) == 0) {
                            if ((pbVar11 == local_14) &&
                                (local_5 == '\n'))
                                goto LAB_10016314;

                            __lseeki64_nolock(
                                _FileHandle,
                                0x1ffffffffLL,
                                unaff_EDI);

                            if (local_5 == '\n')
                                goto LAB_1001638f;

                            goto LAB_1001638b;
                        }

                        if (local_5 == '\n') {
LAB_10016314:
                            _MaxCharCount = uVar6;
                            *pbVar11 = 10;
                        }
                        else {
                            *pbVar11 = 0xd;
                            pending_05 = static_cast<std::uint8_t>(local_5);
                            _MaxCharCount = uVar6;
                        }
                    }

                    pbVar11++;
                    uVar6 = _MaxCharCount;
                }
                else {
                    *pbVar11 = bVar2;
                    pbVar11++;
                    uVar6 = _MaxCharCount + 1;
                }

LAB_1001638f:
                _MaxCharCount = uVar6;
            }
            while (_MaxCharCount < reinterpret_cast<std::uintptr_t>(local_10));
        }

        local_10 = reinterpret_cast<std::uint8_t*>(
            reinterpret_cast<std::uintptr_t>(pbVar11) -
            reinterpret_cast<std::uintptr_t>(local_14));

        if ((local_6 != '\x01') || (local_10 == nullptr))
            goto LAB_10016494;

        bVar2 = pbVar11[-1];

        if (static_cast<char>(bVar2) < '\0') {
            iVar12 = 1;
            pbVar11--;

            while ((DAT_10029c30[bVar2] == 0) &&
                   (iVar12 < 5) &&
                   (local_14 <= pbVar11)) {
                pbVar11--;
                bVar2 = *pbVar11;
                iVar12++;
            }

            if (DAT_10029c30[*pbVar11] == 0) {
                *__errno() = 0x2a;
                goto LAB_10016490;
            }

            if (static_cast<char>(DAT_10029c30[*pbVar11]) + 1 ==
                iVar12) {
                pbVar11 += iVar12;
            }
            else if ((file[4] & 0x48) == 0) {
                __lseeki64_nolock(
                    _FileHandle,
                    0x100000000LL |
                        static_cast<std::uint32_t>(
                            -iVar12 >> 0x1f),
                    unaff_EDI);
            }
            else {
                pbVar7 = pbVar11 + 1;
                pending_05 = *pbVar11;

                if (1 < iVar12) {
                    pending_25 = *pbVar7;
                    pbVar7++;
                }

                if (iVar12 == 3) {
                    pending_26 = *pbVar7;
                    pbVar7++;
                }

                pbVar11 = pbVar7 - iVar12;
            }
        }

        iVar12 = static_cast<int>(
            reinterpret_cast<std::uintptr_t>(pbVar11) -
            reinterpret_cast<std::uintptr_t>(local_14));

        local_10 = reinterpret_cast<std::uint8_t*>(
            MultiByteToWideChar(
                0xfde9,
                0,
                reinterpret_cast<LPCSTR>(local_14),
                iVar12,
                reinterpret_cast<LPWSTR>(_DstBuf),
                uVar1 >> 1));

        if (local_10 != nullptr) {
            bool bVar14 =
                local_10 != reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(iVar12));

            local_10 = reinterpret_cast<std::uint8_t*>(
                reinterpret_cast<std::uintptr_t>(local_10) * 2);

            *reinterpret_cast<std::uint32_t*>(file + 0x30) =
                static_cast<std::uint32_t>(bVar14);

            goto LAB_10016494;
        }

        uVar10 = GetLastError();
    }

LAB_10016489:
    __dosmaperr(uVar10);

LAB_10016490:
    local_18 = -1;

LAB_10016494:
    if (local_14 != _DstBuf)
        _free(local_14);

    if (local_18 == -2)
        return static_cast<int>(
            reinterpret_cast<std::uintptr_t>(local_10));

    return local_18;

LAB_10016175:
    *___doserrno() = 0;
    *__errno() = 0x16;

LAB_10016187:
    FUN_1001189f();
    return -1;
}