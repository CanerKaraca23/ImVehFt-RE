#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
using longlong = std::int64_t;
using ulonglong = std::uint64_t;
using undefined = unsigned char;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined4 = std::uint32_t;
using undefined8 = std::uint64_t;
extern "C" int* __cdecl __errno(void);
extern "C" void __stdcall FUN_1001189f(void);
struct _LocaleUpdate
{
    std::uint32_t locinfo;       // offset 0x00
    std::uint32_t local_10;      // offset 0x04, multibyte-info pointer
    std::uint32_t local_c;       // offset 0x08, per-thread-data pointer
    std::uint8_t local_8;        // offset 0x0c, update/cleanup flag
    _LocaleUpdate(_locale_t locale);
};
static_assert(offsetof(_LocaleUpdate, locinfo) == 0x00);
static_assert(offsetof(_LocaleUpdate, local_10) == 0x04);
static_assert(offsetof(_LocaleUpdate, local_c) == 0x08);
static_assert(offsetof(_LocaleUpdate, local_8) == 0x0c);
static_assert(sizeof(_LocaleUpdate) == 0x10);
extern "C" int __cdecl strncmp(char*, char*, std::size_t);
extern "C" int __cdecl __mbsnbcmp_l(
    unsigned char* _Str1,
    unsigned char* _Str2,
    std::size_t _MaxCount,
    _locale_t _Locale)
{
    if (_MaxCount == 0)
        return 0;

    _LocaleUpdate local_14(_Locale);

    const std::int32_t local_10 = local_14.local_10;
    const std::int32_t local_c = local_14.local_c;
    const std::uint8_t local_8 = local_14.local_8;

    int iVar2;
    std::size_t sVar1;
    std::uint16_t uVar4;
    std::uint32_t uVar5;
    unsigned char* pbVar6;
    unsigned char* pbVar7;

    if (*reinterpret_cast<const std::int32_t*>(
            static_cast<std::uintptr_t>(
                static_cast<std::uint32_t>(local_10)) + 8u) == 0)
    {
        iVar2 = strncmp(
            reinterpret_cast<char*>(_Str1),
            reinterpret_cast<char*>(_Str2),
            _MaxCount);

        if (local_8 != 0)
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(
                    static_cast<std::uint32_t>(local_c)) + 0x70u) &=
                0xfffffffdU;
    }
    else if (_Str1 == nullptr)
    {
        *__errno() = 0x16;
        FUN_1001189f();

        if (local_8 != 0)
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(
                    static_cast<std::uint32_t>(local_c)) + 0x70u) &=
                0xfffffffdU;

        iVar2 = 0x7fffffff;
    }
    else
    {
        if (_Str2 != nullptr)
        {
            do
            {
                uVar5 = static_cast<std::uint32_t>(*_Str1);
                sVar1 = _MaxCount - 1;
                pbVar6 = _Str1 + 1;

                if ((*reinterpret_cast<const std::uint8_t*>(
                         static_cast<std::uintptr_t>(
                             static_cast<std::uint32_t>(local_10)) +
                         0x1dU + uVar5) & 4u) == 0)
                {
                    uVar4 = static_cast<std::uint16_t>(uVar5);
                    uVar5 = static_cast<std::uint32_t>(*_Str2);
                    pbVar7 = _Str2 + 1;

                    if ((*reinterpret_cast<const std::uint8_t*>(
                             static_cast<std::uintptr_t>(
                                 static_cast<std::uint32_t>(local_10)) +
                             0x1dU + uVar5) & 4u) != 0)
                    {
                        if (sVar1 != 0)
                        {
                            sVar1 = _MaxCount - 2;

                            if (*pbVar7 != 0)
                            {
                                uVar5 =
                                    (static_cast<std::uint32_t>(*_Str2) << 8) |
                                    static_cast<std::uint32_t>(*pbVar7);
                                pbVar7 = _Str2 + 2;
                                goto LAB_10018e18;
                            }
                        }

                        _MaxCount = sVar1;
                        uVar5 = 0;
                        sVar1 = _MaxCount;
                    }
                }
                else
                {
                    if (sVar1 != 0)
                    {
                        if (*pbVar6 == 0)
                            uVar5 = 0;
                        else
                        {
                            uVar5 =
                                (static_cast<std::uint32_t>(*_Str1) << 8) |
                                static_cast<std::uint32_t>(*pbVar6);
                            pbVar6 = _Str1 + 2;
                        }

                        goto LAB_10018dea;
                    }

                    uVar5 = static_cast<std::uint32_t>(*_Str2);
                    uVar4 = 0;
                    pbVar7 = _Str2;

                    if ((*reinterpret_cast<const std::uint8_t*>(
                             static_cast<std::uintptr_t>(
                                 static_cast<std::uint32_t>(local_10)) +
                             0x1dU + uVar5) & 4u) != 0)
                        goto LAB_10018dbf;
                }

LAB_10018dea:
                uVar4 = static_cast<std::uint16_t>(uVar5);
                uVar5 = static_cast<std::uint32_t>(*_Str2);
                pbVar7 = _Str2 + 1;

                if ((*reinterpret_cast<const std::uint8_t*>(
                         static_cast<std::uintptr_t>(
                             static_cast<std::uint32_t>(local_10)) +
                         0x1dU + uVar5) & 4u) != 0)
                {
                    if (sVar1 != 0)
                    {
                        sVar1 = _MaxCount - 2;

                        if (*pbVar7 != 0)
                        {
                            uVar5 =
                                (static_cast<std::uint32_t>(*_Str2) << 8) |
                                static_cast<std::uint32_t>(*pbVar7);
                            pbVar7 = _Str2 + 2;
                            goto LAB_10018e18;
                        }
                    }

                    _MaxCount = sVar1;
                    uVar5 = 0;
                    sVar1 = _MaxCount;
                }

LAB_10018e18:
                _MaxCount = sVar1;

                if (static_cast<std::uint16_t>(uVar5) != uVar4)
                {
                    iVar2 =
                        ((0U - static_cast<std::uint32_t>(
                              static_cast<std::uint16_t>(uVar5) < uVar4)) &
                         2U) -
                        1U;

                    if (local_8 == 0)
                        return iVar2;

                    *reinterpret_cast<std::uint32_t*>(
                        static_cast<std::uintptr_t>(
                            static_cast<std::uint32_t>(local_c)) + 0x70u) &=
                        0xfffffffdU;

                    return iVar2;
                }

                if (uVar4 == 0)
                    goto LAB_10018dbf;

                _Str1 = pbVar6;
                _Str2 = pbVar7;

                if (_MaxCount == 0)
                    goto LAB_10018dbf;
            }
            while (true);
        }

        *__errno() = 0x16;
        FUN_1001189f();

        if (local_8 != 0)
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(
                    static_cast<std::uint32_t>(local_c)) + 0x70u) &=
                0xfffffffdU;

        iVar2 = 0x7fffffff;
    }

    return iVar2;

LAB_10018dbf:
    if (local_8 != 0)
        *reinterpret_cast<std::uint32_t*>(
            static_cast<std::uintptr_t>(
                static_cast<std::uint32_t>(local_c)) + 0x70u) &=
            0xfffffffdU;

    return 0;
}