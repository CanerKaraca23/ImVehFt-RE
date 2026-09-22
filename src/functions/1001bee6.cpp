#include <cstddef>
#include <cstdint>
#include <corecrt.h>
using undefined1 = std::uint8_t;
using undefined4 = std::uint32_t;
using undefined8 = std::uint64_t;
using ulonglong = std::uint64_t;
using byte = unsigned char;
using undefined = unsigned char;
using uint = std::uint32_t;
using longlong = std::int64_t;
using undefined2 = std::uint16_t;
extern "C" int* __cdecl __errno(void);
extern "C" void __stdcall FUN_1001189f(void);
struct localeinfo_struct;
struct _LocaleUpdate
{
    localeinfo_struct* locinfo;
    void* mbcinfo;
    void* ptd;
    std::uint8_t updated;
    std::uint8_t padding[3];
    explicit _LocaleUpdate(localeinfo_struct*);
};
static_assert(sizeof(_LocaleUpdate) == 16);
extern "C" errno_t __cdecl __cftoe(double*, char*, size_t, int, int);
extern "C" char* __cdecl strrchr(char*, int);
extern "C" std::uint64_t __fastcall __aullshr(std::uint8_t, std::uint32_t);
extern "C" void* __cdecl _memset(void*, int, size_t);
#include <cstdint>

static std::uint64_t shift64(std::uint8_t shift, std::uint32_t low,
                             std::uint32_t high)
{
    const std::uint64_t bits = (static_cast<std::uint64_t>(high) << 32) | low;
    return shift >= 64 ? 0 : bits >> shift;
}
int __cdecl __cftoa_l(
    double* param_1,
    undefined1* param_2,
    std::uint32_t param_3,
    size_t param_4,
    int param_5,
    localeinfo_struct* param_6)
{
    std::uint16_t uVar1;
    int* piVar2;
    size_t sizeInBytes;
    errno_t eVar3;
    char* pcVar4;
    char* pcVar5;
    std::uint32_t uVar6;
    std::uint32_t uVar7;
    std::uint32_t division_remainder;
    short sVar8;
    int unaff_EBX = 0;
    char* pcVar9;
    char* pcVar10;
    bool bVar11;
    ulonglong uVar12;
    undefined8 uVar13;
    int iVar14;
    _LocaleUpdate local_28(param_6);
    std::uint32_t local_18;
    undefined4 local_14;
    std::uint32_t local_10;
    std::uint32_t local_c;
    int local_8;

    local_18 = 0x3ff;
    local_8 = 0x30;


    const auto divide_capture_remainder = [](
        std::uint32_t dividend_low,
        std::uint32_t dividend_high,
        std::uint32_t divisor_low,
        std::uint32_t divisor_high,
        std::uint32_t* remainder_low)
    {
        const std::uint64_t dividend_bits =
            (static_cast<std::uint64_t>(dividend_high) << 32) | dividend_low;
        const std::uint64_t divisor_bits =
            (static_cast<std::uint64_t>(divisor_high) << 32) | divisor_low;
        const auto dividend = static_cast<std::int64_t>(dividend_bits);
        const auto divisor = static_cast<std::int64_t>(divisor_bits);
        const auto quotient = dividend / divisor;
        const auto remainder = dividend % divisor;
        *remainder_low = static_cast<std::uint32_t>(remainder);
        return static_cast<std::uint64_t>(quotient);
    };


    if (static_cast<int>(param_4) < 0)
        param_4 = 0;

    if (param_2 == nullptr || param_3 == 0)
    {
        piVar2 = __errno();
        iVar14 = 0x16;
        *piVar2 = iVar14;

        iVar14 = 0x1001bf29;
        FUN_1001189f();

        if (local_28.updated != '\0')
            *reinterpret_cast<std::uint32_t*>(static_cast<std::byte*>(local_28.ptd) + 0x70) &=
                0xfffffffd;

        return iVar14;
    }

    *param_2 = 0;

    if (param_3 <= param_4 + 0xb)
    {
        piVar2 = __errno();
        iVar14 = 0x22;
        *piVar2 = iVar14;

        iVar14 = 0x1001bf29;
        FUN_1001189f();

        if (local_28.updated != '\0')
            *reinterpret_cast<std::uint32_t*>(static_cast<std::byte*>(local_28.ptd) + 0x70) &=
                0xfffffffd;

        return iVar14;
    }

    local_10 = *reinterpret_cast<std::uint32_t*>(param_1);
    const std::uint64_t value_bits =
        *reinterpret_cast<const std::uint64_t*>(param_1);

    if (((*reinterpret_cast<std::uint32_t*>(
              reinterpret_cast<char*>(param_1) + 4) >> 0x14) & 0x7ff) == 0x7ff)
    {
        if (param_3 == 0xffffffff)
            sizeInBytes = 0xffffffff;
        else
            sizeInBytes = param_3 - 2;

        eVar3 = __cftoe(
            param_1,
            reinterpret_cast<char*>(param_2 + 2),
            sizeInBytes,
            static_cast<int>(param_4),
            0);

        if (eVar3 != 0)
        {
            *param_2 = 0;

            if (local_28.updated == '\0')
                return unaff_EBX;

            *reinterpret_cast<std::uint32_t*>(static_cast<std::byte*>(local_28.ptd) + 0x70) &=
                0xfffffffd;

            return unaff_EBX;
        }

        if (param_2[2] == '-')
        {
            *param_2 = 0x2d;
            param_2 = param_2 + 1;
        }

        *param_2 = 0x30;
        param_2[1] = static_cast<undefined1>(
            ((param_5 == 0) - 1U & 0xe0) + 0x78);

        pcVar4 = strrchr(
            reinterpret_cast<char*>(param_2 + 2),
            0x65);

        if (pcVar4 != nullptr)
        {
            *pcVar4 = static_cast<char>(
                ((param_5 == 0) - 1U & 0xe0) + 0x70);
            pcVar4[3] = '\0';
        }

        if (local_28.updated == '\0')
            return unaff_EBX;

        *reinterpret_cast<std::uint32_t*>(static_cast<std::byte*>(local_28.ptd) + 0x70) &=
            0xfffffffd;

        return unaff_EBX;
    }

    if ((*reinterpret_cast<std::uint32_t*>(
             reinterpret_cast<char*>(param_1) + 4) &
         0x80000000) != 0)
    {
        *param_2 = 0x2d;
        param_2 = param_2 + 1;
    }

    *param_2 = 0x30;
    param_2[1] = static_cast<undefined1>(
        ((param_5 == 0) - 1U & 0xe0) + 0x78);

    sVar8 = static_cast<short>(
        (-(std::uint16_t)(param_5 != 0) & 0xffe0) + 0x27);

    if ((value_bits & 0x7ff0000000000000ULL) == 0)
    {
        param_2[2] = 0x30;

        if (*reinterpret_cast<int*>(param_1) == 0 &&
            (value_bits & 0xfffff00000000ULL) == 0)
        {
            local_18 = 0;
        }
        else
        {
            local_18 = 0x3fe;
        }
    }
    else
    {
        param_2[2] = 0x31;
    }

    pcVar10 = reinterpret_cast<char*>(param_2 + 3);
    pcVar4 = reinterpret_cast<char*>(param_2 + 4);

    if (param_4 == 0)
    {
        *pcVar10 = '\0';
    }
    else
    {
        *pcVar10 = *reinterpret_cast<char*>(
            **reinterpret_cast<undefined4**>(reinterpret_cast<std::uintptr_t>(local_28.locinfo) + 0xbc));
    }

    if ((value_bits & 0xfffff00000000ULL) != 0 ||
        (local_c = 0, *reinterpret_cast<int*>(param_1) != 0))
    {
        local_10 = 0;
        local_c = 0xf0000;

        do
        {
            if (static_cast<int>(param_4) < 1)
                break;

            uVar12 = shift64(
                static_cast<std::uint8_t>(local_8),
                *reinterpret_cast<std::uint32_t*>(param_1) & local_10,
                *reinterpret_cast<std::uint32_t*>(
                    reinterpret_cast<char*>(param_1) + 4) &
                local_c &
                0xfffff);

            uVar1 = static_cast<short>(uVar12) + 0x30;

            if (0x39 < uVar1)
                uVar1 = uVar1 + sVar8;

            local_8 = local_8 - 4;
            *pcVar4 = static_cast<char>(uVar1);

            local_10 = local_10 >> 4 | local_c << 0x1c;
            local_c = local_c >> 4;
            pcVar4 = pcVar4 + 1;
            param_4 = param_4 - 1;
        }
        while (-1 < static_cast<short>(local_8));

        if (-1 < static_cast<short>(local_8))
        {
            uVar12 = shift64(
                static_cast<std::uint8_t>(local_8),
                *reinterpret_cast<std::uint32_t*>(param_1) & local_10,
                *reinterpret_cast<std::uint32_t*>(
                    reinterpret_cast<char*>(param_1) + 4) &
                local_c &
                0xfffff);

            pcVar9 = pcVar4;

            if (8 < static_cast<std::uint16_t>(uVar12))
            {
                while (true)
                {
                    pcVar5 = pcVar9 - 1;

                    if (*pcVar5 != 'f' && *pcVar5 != 'F')
                        break;

                    *pcVar5 = '0';
                    pcVar9 = pcVar5;
                }

                if (pcVar5 == pcVar10)
                {
                    pcVar9[-2] = pcVar9[-2] + '\x01';
                }
                else if (*pcVar5 == '9')
                {
                    *pcVar5 = static_cast<char>(sVar8) + ':';
                }
                else
                {
                    *pcVar5 = *pcVar5 + '\x01';
                }
            }
        }
    }

    if (static_cast<int>(param_4) > 0)
    {
        _memset(pcVar4, 0x30, param_4);
        pcVar4 = pcVar4 + param_4;
    }

    if (*pcVar10 == '\0')
        pcVar4 = pcVar10;

    *pcVar4 = static_cast<char>(
        ((param_5 == 0) - 1U & 0xe0) + 0x70);

    uVar12 = shift64(
        0x34,
        *reinterpret_cast<std::uint32_t*>(param_1),
        *reinterpret_cast<std::uint32_t*>(
            reinterpret_cast<char*>(param_1) + 4));

    uVar6 = static_cast<std::uint32_t>(uVar12 & 0x7ff);
    uVar7 = uVar6 - local_18;
    uVar6 = 0U - static_cast<std::uint32_t>(uVar6 < local_18);

    if (static_cast<int>(uVar6) < 0)
    {
        pcVar4[1] = '-';
        bVar11 = uVar7 != 0;
        uVar7 = 0U - uVar7;
        uVar6 = 0U - (uVar6 + static_cast<std::uint32_t>(bVar11));
    }
    else
    {
        pcVar4[1] = '+';
    }

    pcVar9 = pcVar4 + 2;
    *pcVar9 = '0';
    pcVar10 = pcVar9;

    if (static_cast<int>(uVar6) < 0 ||
        (static_cast<int>(uVar6) < 1 && uVar7 < 1000))
    {
        if (static_cast<int>(uVar6) >= 0 &&
            (static_cast<int>(uVar6) > 0 || uVar7 > 99))
        {
            uVar13 = divide_capture_remainder(uVar7, uVar6, 100, 0, &division_remainder);
            local_14 = static_cast<undefined4>(
                static_cast<ulonglong>(uVar13) >> 0x20);

            *pcVar10 = static_cast<char>(uVar13) + '0';
            pcVar10 = pcVar10 + 1;
            uVar6 = 0;
            uVar7 = division_remainder;
        }
    }
    else
    {
        uVar13 = divide_capture_remainder(uVar7, uVar6, 1000, 0, &division_remainder);
        local_14 = static_cast<undefined4>(
            static_cast<ulonglong>(uVar13) >> 0x20);

        *pcVar9 = static_cast<char>(uVar13) + '0';
        pcVar10 = pcVar4 + 3;
        uVar6 = 0;
        uVar7 = division_remainder;

        if (pcVar10 == pcVar9)
        {
            if (static_cast<int>(uVar6) >= 0 &&
                (static_cast<int>(uVar6) > 0 || uVar7 > 99))
            {
                uVar13 = divide_capture_remainder(uVar7, uVar6, 100, 0, &division_remainder);
                local_14 = static_cast<undefined4>(
                    static_cast<ulonglong>(uVar13) >> 0x20);

                *pcVar10 = static_cast<char>(uVar13) + '0';
                pcVar10 = pcVar10 + 1;
                uVar6 = 0;
                uVar7 = division_remainder;
            }
        }
    }

    if (pcVar10 != pcVar9 ||
        (static_cast<int>(uVar6) >= 0 &&
         (static_cast<int>(uVar6) > 0 || uVar7 > 9)))
    {
        uVar13 = divide_capture_remainder(uVar7, uVar6, 10, 0, &division_remainder);

        *pcVar10 = static_cast<char>(uVar13) + '0';
        pcVar10 = pcVar10 + 1;
        uVar7 = division_remainder;
    }

    *pcVar10 = static_cast<char>(uVar7) + '0';
    pcVar10[1] = '\0';

    if (local_28.updated == '\0')
        return unaff_EBX;

    *reinterpret_cast<std::uint32_t*>(static_cast<std::byte*>(local_28.ptd) + 0x70) &=
        0xfffffffd;

    return unaff_EBX;
}