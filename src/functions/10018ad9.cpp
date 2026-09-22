#include <cstddef>
#include <cstdint>

using uchar = unsigned char;

struct _LocaleUpdate
{
    std::uint32_t unknown_00; // offset 0x00
    std::int32_t  local_18;   // offset 0x04
    std::int32_t  local_14;   // offset 0x08
    char          local_10;   // offset 0x0c
    std::uint8_t  padding_0d[3];

    explicit _LocaleUpdate(_locale_t locale);
};

static_assert(sizeof(_LocaleUpdate) == 0x10);
static_assert(offsetof(_LocaleUpdate, local_18) == 0x04);
static_assert(offsetof(_LocaleUpdate, local_14) == 0x08);
static_assert(offsetof(_LocaleUpdate, local_10) == 0x0c);

extern "C" int __cdecl _strnicmp(
    char* str1,
    char* str2,
    std::size_t max_count);

extern "C" int* __cdecl __errno();

extern "C" void __stdcall FUN_1001189f();

int __cdecl __mbsnbicmp_l(
    uchar* _Str1,
    uchar* _Str2,
    std::size_t _MaxCount,
    _locale_t _Locale)
{
    std::size_t sVar1;
    uchar* puVar2;
    int iVar3;
    int* piVar4;
    std::uint32_t uVar5;
    uchar* pbVar6;
    std::uint16_t local_c;
    std::uint16_t local_8;

    _LocaleUpdate local_1c(_Locale);

    auto* local_18 = reinterpret_cast<std::uint8_t*>(
        static_cast<std::uintptr_t>(local_1c.local_18));

    auto* local_14 = reinterpret_cast<std::uint8_t*>(
        static_cast<std::uintptr_t>(local_1c.local_14));

    if (_MaxCount == 0)
    {
        if (local_1c.local_10 != '\0')
        {
            *reinterpret_cast<std::uint32_t*>(local_14 + 0x70) &=
                0xfffffffdU;
        }

        iVar3 = 0;
    }
    else if (*reinterpret_cast<std::int32_t*>(local_18 + 8) == 0)
    {
        iVar3 = _strnicmp(
            reinterpret_cast<char*>(_Str1),
            reinterpret_cast<char*>(_Str2),
            _MaxCount);

        if (local_1c.local_10 != '\0')
        {
            *reinterpret_cast<std::uint32_t*>(local_14 + 0x70) &=
                0xfffffffdU;
        }
    }
    else if (_Str1 == nullptr)
    {
        piVar4 = __errno();
        *piVar4 = 0x16;
        FUN_1001189f();

        if (local_1c.local_10 != '\0')
        {
            *reinterpret_cast<std::uint32_t*>(local_14 + 0x70) &=
                0xfffffffdU;
        }

        iVar3 = 0x7fffffff;
    }
    else
    {
        if (_Str2 != nullptr)
        {
            do
            {
                uVar5 = static_cast<std::uint32_t>(*_Str1);
                sVar1 = _MaxCount - 1;
                puVar2 = _Str1 + 1;

                if ((local_18[uVar5 + 0x1d] & 4) == 0)
                {
                    if ((local_18[uVar5 + 0x1d] & 0x10) != 0)
                    {
                        uVar5 = static_cast<std::uint32_t>(
                            local_18[uVar5 + 0x11d]);
                    }

                    local_c = static_cast<std::uint16_t>(uVar5);
                    _Str1 = puVar2;

                LAB_10018c2c:
                    uVar5 = static_cast<std::uint32_t>(*_Str2);
                    pbVar6 = _Str2 + 1;

                    if ((local_18[uVar5 + 0x1d] & 4) == 0)
                    {
                        if ((local_18[uVar5 + 0x1d] & 0x10) != 0)
                        {
                            uVar5 = static_cast<std::uint32_t>(
                                local_18[uVar5 + 0x11d]);
                        }

                        goto LAB_10018c9c;
                    }

                    if (sVar1 == 0)
                    {
                    LAB_10018c42:
                        _MaxCount = sVar1;
                        local_8 = 0;
                    }
                    else
                    {
                        sVar1 = _MaxCount - 2;

                        if (*pbVar6 == 0)
                        {
                            goto LAB_10018c42;
                        }

                        local_8 = static_cast<std::uint16_t>(
                            (static_cast<std::uint16_t>(*_Str2) << 8) |
                            static_cast<std::uint16_t>(*pbVar6));

                        pbVar6 = _Str2 + 2;
                        _MaxCount = sVar1;

                        if ((local_8 < *reinterpret_cast<std::uint16_t*>(
                                           local_18 + 0x10)) ||
                            (*reinterpret_cast<std::uint16_t*>(
                                 local_18 + 0x12) < local_8))
                        {
                            if ((*reinterpret_cast<std::uint16_t*>(
                                     local_18 + 0x16) <= local_8) &&
                                (local_8 <= *reinterpret_cast<std::uint16_t*>(
                                               local_18 + 0x18)))
                            {
                                local_8 = static_cast<std::uint16_t>(
                                    local_8 +
                                    *reinterpret_cast<std::int16_t*>(
                                        local_18 + 0x1a));
                            }
                        }
                        else
                        {
                            local_8 = static_cast<std::uint16_t>(
                                local_8 +
                                *reinterpret_cast<std::int16_t*>(
                                    local_18 + 0x14));
                        }
                    }
                }
                else
                {
                    if (sVar1 != 0)
                    {
                        if (*puVar2 == 0)
                        {
                            local_c = 0;
                            _Str1 = puVar2;
                        }
                        else
                        {
                            local_c = static_cast<std::uint16_t>(
                                (static_cast<std::uint16_t>(*_Str1) << 8) |
                                static_cast<std::uint16_t>(*puVar2));

                            _Str1 = _Str1 + 2;

                            if ((local_c < *reinterpret_cast<std::uint16_t*>(
                                               local_18 + 0x10)) ||
                                (*reinterpret_cast<std::uint16_t*>(
                                     local_18 + 0x12) < local_c))
                            {
                                if ((*reinterpret_cast<std::uint16_t*>(
                                         local_18 + 0x16) <= local_c) &&
                                    (local_c <=
                                     *reinterpret_cast<std::uint16_t*>(
                                         local_18 + 0x18)))
                                {
                                    local_c = static_cast<std::uint16_t>(
                                        local_c +
                                        *reinterpret_cast<std::int16_t*>(
                                            local_18 + 0x1a));
                                }
                            }
                            else
                            {
                                local_c = static_cast<std::uint16_t>(
                                    local_c +
                                    *reinterpret_cast<std::int16_t*>(
                                        local_18 + 0x14));
                            }
                        }

                        goto LAB_10018c2c;
                    }

                    uVar5 = static_cast<std::uint32_t>(*_Str2);

                    if ((local_18[uVar5 + 0x1d] & 4) != 0)
                    {
                    LAB_10018cb6:
                        if (local_1c.local_10 != '\0')
                        {
                            *reinterpret_cast<std::uint32_t*>(
                                local_14 + 0x70) &= 0xfffffffdU;
                        }

                        return 0;
                    }

                    local_c = 0;
                    pbVar6 = _Str2;
                    _Str1 = puVar2;

                LAB_10018c9c:
                    local_8 = static_cast<std::uint16_t>(uVar5);
                    _MaxCount = sVar1;
                }

                if (local_8 != local_c)
                {
                    iVar3 =
                        ((0U - static_cast<std::uint32_t>(local_8 < local_c)) &
                         2U) -
                        1U;

                    if (local_1c.local_10 == '\0')
                    {
                        return iVar3;
                    }

                    *reinterpret_cast<std::uint32_t*>(
                        local_14 + 0x70) &= 0xfffffffdU;

                    return iVar3;
                }

                if ((local_c == 0) || (_MaxCount == 0))
                {
                    goto LAB_10018cb6;
                }
            }
            while (true);
        }

        piVar4 = __errno();
        *piVar4 = 0x16;
        FUN_1001189f();

        if (local_1c.local_10 != '\0')
        {
            *reinterpret_cast<std::uint32_t*>(local_14 + 0x70) &=
                0xfffffffdU;
        }

        iVar3 = 0x7fffffff;
    }

    return iVar3;
}