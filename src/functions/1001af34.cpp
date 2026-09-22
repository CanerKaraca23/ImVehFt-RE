#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <windows.h>
#include <stdio.h>
using longlong = std::int64_t;
using ulonglong = std::uint64_t;
using undefined = unsigned char;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined4 = std::uint32_t;
using undefined8 = std::uint64_t;
extern "C" int* __cdecl __errno(void);
extern "C" std::intptr_t __cdecl __get_osfhandle(int);
extern "C" unsigned long* __cdecl ___doserrno(void);
extern "C" int __cdecl __setmode_nolock(int, int);
extern "C" int __cdecl __write_nolock(int, void*, unsigned int);
extern "C" long long __cdecl __lseeki64_nolock(int, long long, int);
int __cdecl __chsize_nolock(int _FileHandle, long long _Size)
{
    int iVar1;
    HANDLE pvVar2;
    LPVOID _Buf;
    int* piVar3;
    int iVar4;
    unsigned int uVar5;
    unsigned long* puVar6;
    BOOL BVar7;
    unsigned int uVar8;
    int iVar9;
    bool bVar10;
    bool bVar11;
    unsigned long long uVar12;
    long long lVar13;
    DWORD DVar14;
    SIZE_T dwBytes;
    unsigned int local_14 = 0;
    unsigned int local_10 = 0;

    uVar12 = static_cast<unsigned long long>(
        __lseeki64_nolock(_FileHandle, 0LL, 1));

    if (uVar12 == 0xffffffffffffffffULL)
        goto LAB_1001afbc;

    lVar13 = __lseeki64_nolock(
        _FileHandle, 0LL, 2);

    iVar4 = static_cast<int>(
        static_cast<unsigned long long>(lVar13) >> 0x20);

    if (lVar13 == -1)
        goto LAB_1001afbc;

    uVar8 = static_cast<unsigned int>(_Size) -
            static_cast<unsigned int>(lVar13);

    uVar5 = static_cast<unsigned int>(
        static_cast<unsigned int>(_Size) <
        static_cast<unsigned int>(lVar13));

    iVar1 = static_cast<int>(
        static_cast<unsigned int>(_Size) -
        static_cast<unsigned int>(iVar4));

    iVar9 = static_cast<int>(
        static_cast<unsigned int>(iVar1) - uVar5);

    {
        const unsigned int lhs1 = static_cast<unsigned int>(_Size);
        const unsigned int rhs1 = static_cast<unsigned int>(iVar4);
        const unsigned int result1 = lhs1 - rhs1;
        const bool overflow1 =
            ((lhs1 ^ rhs1) & 0x80000000U) != 0 &&
            ((lhs1 ^ result1) & 0x80000000U) != 0;

        const unsigned int lhs2 = static_cast<unsigned int>(iVar1);
        const unsigned int rhs2 = uVar5;
        const unsigned int result2 = lhs2 - rhs2;
        const bool overflow2 =
            ((lhs2 ^ rhs2) & 0x80000000U) != 0 &&
            ((lhs2 ^ result2) & 0x80000000U) != 0;

        if ((iVar9 < 0) ||
            ((iVar9 == 0 || (overflow1 != overflow2 && (uVar8 == 0))))) {
            if ((iVar9 < 1) && (iVar9 < 0)) {
                lVar13 = __lseeki64_nolock(
                    _FileHandle,
                    _Size,
                    0);

                if (lVar13 == -1)
                    goto LAB_1001afbc;

                pvVar2 = reinterpret_cast<HANDLE>(
                    static_cast<std::uintptr_t>(
                        __get_osfhandle(_FileHandle)));

                BVar7 = SetEndOfFile(pvVar2);
                local_14 = static_cast<unsigned int>((BVar7 != 0) - 1);
                local_10 = static_cast<unsigned int>(
                    static_cast<int>(local_14) >> 0x1f);

                if ((local_14 & local_10) == 0xffffffffU) {
                    piVar3 = __errno();
                    *piVar3 = 0x0d;

                    puVar6 = ___doserrno();
                    DVar14 = GetLastError();
                    *puVar6 = DVar14;

                    goto LAB_1001b0ba;
                }
            }
        } else {
            dwBytes = 0x1000;
            DVar14 = 8;
            pvVar2 = GetProcessHeap();
            _Buf = HeapAlloc(pvVar2, DVar14, dwBytes);

            if (_Buf == nullptr) {
                piVar3 = __errno();
                *piVar3 = 0x0c;
                goto LAB_1001afbc;
            }

            iVar4 = __setmode_nolock(_FileHandle, 0x8000);

            while (true) {
                uVar5 = uVar8;

                if ((-1 < iVar9) &&
                    ((0 < iVar9) || (0xfff < uVar8))) {
                    uVar5 = 0x1000;
                }

                uVar5 = __write_nolock(_FileHandle, _Buf, uVar5);

                if (uVar5 == 0xffffffffU)
                    break;

                bVar10 = uVar8 < uVar5;
                uVar8 = uVar8 - uVar5;

                {
                    const unsigned int lhs =
                        static_cast<unsigned int>(iVar9);
                    const unsigned int rhs =
                        static_cast<unsigned int>(
                            static_cast<int>(uVar5) >> 31);
                    const unsigned int result = lhs - rhs;

                    bVar11 =
                        ((lhs ^ rhs) & 0x80000000U) != 0 &&
                        ((lhs ^ result) & 0x80000000U) != 0;
                }

                iVar1 = static_cast<int>(
                    static_cast<unsigned int>(iVar9) -
                    static_cast<unsigned int>(
                        static_cast<int>(uVar5) >> 31));

                iVar9 = static_cast<int>(
                    static_cast<unsigned int>(iVar1) -
                    static_cast<unsigned int>(bVar10));

                {
                    const unsigned int lhs =
                        static_cast<unsigned int>(iVar1);
                    const unsigned int rhs =
                        static_cast<unsigned int>(bVar10);
                    const unsigned int result = lhs - rhs;
                    const bool overflow =
                        ((lhs ^ rhs) & 0x80000000U) != 0 &&
                        ((lhs ^ result) & 0x80000000U) != 0;

                    if ((iVar9 < 0) ||
                        ((iVar9 == 0 ||
                          (bVar11 != overflow && (uVar8 == 0))))) {
                        goto LAB_1001b00e;
                    }
                }
            }

            puVar6 = ___doserrno();

            if (*puVar6 == 5) {
                piVar3 = __errno();
                *piVar3 = 0x0d;
            }

            local_14 = 0xffffffffU;
            local_10 = 0xffffffffU;

LAB_1001b00e:
            __setmode_nolock(_FileHandle, iVar4);

            DVar14 = 0;
            pvVar2 = GetProcessHeap();
            HeapFree(pvVar2, DVar14, _Buf);

LAB_1001b0ba:
            if ((local_14 & local_10) == 0xffffffffU)
                goto LAB_1001afbc;
        }
    }

    lVar13 = __lseeki64_nolock(
        _FileHandle,
        static_cast<long long>(uVar12),
        0);

    if (lVar13 != -1)
        return 0;

LAB_1001afbc:
    piVar3 = __errno();
    return *piVar3;
}