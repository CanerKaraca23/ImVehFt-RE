#include <cstdint>

extern std::int32_t DAT_1003c248;
extern std::int32_t _DAT_00b74494;
extern std::uint32_t _DAT_00b7cb84;
extern std::int32_t DAT_1003bc18;



extern "C" std::int32_t __stdcall FUN_10009360();

void __stdcall FUN_10005670()
{
    std::int32_t in_EAX;
    __asm mov in_EAX, eax
    std::int32_t iVar1;
    std::int32_t iVar2;
    std::int32_t iVar3;
    std::int8_t cVar4;

    iVar3 = DAT_1003c248;
    iVar2 = FUN_10009360();

    iVar3 =
        *reinterpret_cast<std::int32_t*>(
            *reinterpret_cast<std::int32_t*>(iVar2 + 0x48) +
            ((in_EAX - _DAT_00b74494) / 0xA18) * 4) +
        iVar3;

    if ((*reinterpret_cast<std::uint8_t*>(in_EAX + 0x42D) & 0x80) == 0)
    {
        if (*reinterpret_cast<std::int8_t*>(iVar3 + 0x21) != 0)
        {
            DAT_1003bc18 = 0;

            if (*reinterpret_cast<std::int16_t*>(
                    *reinterpret_cast<std::int32_t*>(
                        *reinterpret_cast<std::int32_t*>(iVar3 + 0x28) + 0x350) +
                    4) != 0)
            {
                do
                {
                    *reinterpret_cast<std::uint8_t*>(
                        *reinterpret_cast<std::int32_t*>(iVar3 + 0x28) +
                        0x35D + DAT_1003bc18 * 0x14) = 0;

                    DAT_1003bc18 = DAT_1003bc18 + 1;
                }
                while (DAT_1003bc18 <
                       static_cast<std::int32_t>(
                           *reinterpret_cast<std::uint16_t*>(
                               *reinterpret_cast<std::int32_t*>(
                                   *reinterpret_cast<std::int32_t*>(iVar3 + 0x28) +
                                   0x350) +
                               4)));
            }

            *reinterpret_cast<std::uint8_t*>(iVar3 + 0x21) = 0;
            return;
        }
    }
    else
    {
        if (*reinterpret_cast<std::int8_t*>(iVar3 + 0x21) == 0)
        {
            DAT_1003bc18 = 0;

            if (*reinterpret_cast<std::int16_t*>(
                    *reinterpret_cast<std::int32_t*>(
                        *reinterpret_cast<std::int32_t*>(iVar3 + 0x28) + 0x350) +
                    4) != 0)
            {
                do
                {
                    *reinterpret_cast<std::uint8_t*>(
                        *reinterpret_cast<std::int32_t*>(iVar3 + 0x28) +
                        (DAT_1003bc18 * 5 + 0xD7) * 4) = 0xFF;

                    DAT_1003bc18 = DAT_1003bc18 + 1;
                }
                while (DAT_1003bc18 <
                       static_cast<std::int32_t>(
                           *reinterpret_cast<std::uint16_t*>(
                               *reinterpret_cast<std::int32_t*>(
                                   *reinterpret_cast<std::int32_t*>(iVar3 + 0x28) +
                                   0x350) +
                               4)));
            }

            *reinterpret_cast<std::uint8_t*>(iVar3 + 0x21) = 1;
        }

        DAT_1003bc18 = 0;

        if (*reinterpret_cast<std::int16_t*>(
                *reinterpret_cast<std::int32_t*>(
                    *reinterpret_cast<std::int32_t*>(iVar3 + 0x28) + 0x350) +
                4) != 0)
        {
            do
            {
                *reinterpret_cast<std::uint8_t*>(
                    *reinterpret_cast<std::int32_t*>(iVar3 + 0x28) +
                    0x35E + DAT_1003bc18 * 0x14) = 0;

                DAT_1003bc18 = DAT_1003bc18 + 1;
            }
            while (DAT_1003bc18 <
                   static_cast<std::int32_t>(
                       *reinterpret_cast<std::uint16_t*>(
                           *reinterpret_cast<std::int32_t*>(
                               *reinterpret_cast<std::int32_t*>(iVar3 + 0x28) +
                               0x350) +
                           4)));
        }

        DAT_1003bc18 = 0;

        if (*reinterpret_cast<std::int16_t*>(
                *reinterpret_cast<std::int32_t*>(
                    *reinterpret_cast<std::int32_t*>(iVar3 + 0x28) + 0x350) +
                4) != 0)
        {
            do
            {
                iVar2 =
                    *reinterpret_cast<std::int32_t*>(iVar3 + 0x28) +
                    0x354 + DAT_1003bc18 * 0x14;

                if (*reinterpret_cast<std::int8_t*>(
                        *reinterpret_cast<std::int32_t*>(iVar3 + 0x28) +
                        0x35E + DAT_1003bc18 * 0x14) == 0)
                {
                    if (*reinterpret_cast<std::int8_t*>(iVar2 + 8) == -1)
                    {
                        *reinterpret_cast<std::uint32_t*>(iVar2 + 0x10) =
                            _DAT_00b7cb84;

                        *reinterpret_cast<std::uint8_t*>(iVar2 + 8) = 0;

                        *reinterpret_cast<std::uint8_t*>(iVar2 + 9) =
                            *reinterpret_cast<std::uint8_t*>(
                                *reinterpret_cast<std::int32_t*>(iVar2 + 0xC) + 2);
                    }

                    iVar1 = *reinterpret_cast<std::int32_t*>(iVar2 + 0xC);

                    if (*reinterpret_cast<std::int8_t*>(iVar1 + 3) == 0)
                    {
                        *reinterpret_cast<std::uint8_t*>(iVar2 + 9) = 1;
                    }
                    else if (static_cast<std::uint32_t>(
                                 *reinterpret_cast<std::int32_t*>(
                                     *reinterpret_cast<std::int32_t*>(iVar1 + 4) +
                                     *reinterpret_cast<std::int8_t*>(iVar2 + 8) * 4) +
                                 *reinterpret_cast<std::uint32_t*>(iVar2 + 0x10)) <=
                             _DAT_00b7cb84)
                    {
                        cVar4 =
                            static_cast<std::int8_t>(
                                *reinterpret_cast<std::int8_t*>(iVar2 + 8) + 1);

                        *reinterpret_cast<std::int8_t*>(iVar2 + 8) = cVar4;

                        *reinterpret_cast<bool*>(iVar2 + 9) =
                            *reinterpret_cast<std::int8_t*>(iVar2 + 9) == 0;

                        if (static_cast<std::int32_t>(
                                *reinterpret_cast<std::uint8_t*>(iVar1 + 3)) <=
                            static_cast<std::int32_t>(cVar4))
                        {
                            *reinterpret_cast<std::uint8_t*>(iVar2 + 8) = 0xFF;
                        }
                    }

                    *reinterpret_cast<std::uint8_t*>(iVar2 + 10) = 1;
                }

                DAT_1003bc18 = DAT_1003bc18 + 1;
            }
            while (DAT_1003bc18 <
                   static_cast<std::int32_t>(
                       *reinterpret_cast<std::uint16_t*>(
                           *reinterpret_cast<std::int32_t*>(
                               *reinterpret_cast<std::int32_t*>(iVar3 + 0x28) +
                               0x350) +
                           4)));
        }
    }
}

