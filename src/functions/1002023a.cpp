#include <bit>
#include <cstdint>

extern "C" void __cdecl FUN_1002049a();

extern "C" long double __cdecl FUN_10020775(
    std::uint32_t low,
    std::uint32_t high,
    int* exponent);

extern double _DAT_10024f88;
extern double _DAT_100399b8;
extern double _DAT_100399c8;

extern "C" bool __cdecl __handle_exc(
    std::uint32_t param_1,
    double* param_2,
    std::uint32_t param_3)
{
    double dVar1;
    double dVar2;
    bool bVar3;
    double dVar4;
    std::uint32_t uVar5;
    bool bVar6;
    long double fVar7;
    std::uint32_t local_18;
    std::uint8_t bStack_14;
    std::uint8_t uStack_13;
    std::uint16_t uStack_12;
    int local_c;
    std::uint32_t local_8;

    uVar5 = param_1 & 0x1Fu;
    bVar3 = true;
    local_8 = uVar5;

    if (((param_1 & 8u) != 0) && ((param_3 & 1u) != 0)) {
        FUN_1002049a();
        uVar5 = param_1 & 0x17u;
        goto LAB_100203fc;
    }

    if (((param_1 & 4u) != 0) && ((param_3 & 4u) != 0)) {
        FUN_1002049a();
        uVar5 = param_1 & 0x1Bu;
        goto LAB_100203fc;
    }

    if (((param_1 & 1u) == 0) || ((param_3 & 8u) == 0)) {
        if (((param_1 & 2u) == 0) || ((param_3 & 0x10u) == 0)) {
            goto LAB_100203fc;
        }

        bVar6 = (param_1 & 0x10u) != 0;

        if (*param_2 != 0.0) {
            std::uint64_t input_bits;
            input_bits = std::bit_cast<std::uint64_t>(*param_2);

            fVar7 = FUN_10020775(
                static_cast<std::uint32_t>(input_bits),
                static_cast<std::uint32_t>(input_bits >> 32),
                &local_c);

            dVar2 = static_cast<double>(fVar7);

            std::uint64_t bits;
            bits = std::bit_cast<std::uint64_t>(dVar2);

            local_18 = static_cast<std::uint32_t>(bits);
            bStack_14 = static_cast<std::uint8_t>(bits >> 32);
            uStack_13 = static_cast<std::uint8_t>(bits >> 40);
            uStack_12 = static_cast<std::uint16_t>(bits >> 48);

            local_c = local_c - 0x600;

            if (local_c < -0x432) {
                dVar2 = dVar2 * _DAT_10024f88;
                bVar6 = bVar3;

                bits = std::bit_cast<std::uint64_t>(dVar2);
                local_18 = static_cast<std::uint32_t>(bits);
                bStack_14 = static_cast<std::uint8_t>(bits >> 32);
                uStack_13 = static_cast<std::uint8_t>(bits >> 40);
                uStack_12 = static_cast<std::uint16_t>(bits >> 48);
            } else {
                uStack_12 = static_cast<std::uint16_t>(
                    (uStack_12 & 0x0Fu) | 0x10u);

                if (local_c < -0x3FD) {
                    local_c = -0x3FD - local_c;

                    do {
                        if (((local_18 & 1u) != 0) && (!bVar6)) {
                            bVar6 = bVar3;
                        }

                        local_18 = local_18 >> 1;

                        if ((bStack_14 & 1u) != 0) {
                            local_18 = local_18 | 0x80000000u;
                        }

                        const std::uint32_t upper =
                            (static_cast<std::uint32_t>(uStack_12) << 16) |
                            (static_cast<std::uint32_t>(uStack_13) << 8) |
                            static_cast<std::uint32_t>(bStack_14);

                        uVar5 = upper >> 1;
                        bStack_14 = static_cast<std::uint8_t>(uVar5);
                        uStack_13 = static_cast<std::uint8_t>(uVar5 >> 8);
                        uStack_12 = static_cast<std::uint16_t>(uStack_12 >> 1);

                        local_c = local_c - 1;
                    } while (local_c != 0);
                }

                if (dVar2 < 0.0) {
                    const std::uint64_t magnitude =
                        (static_cast<std::uint64_t>(uStack_12) << 48) |
                        (static_cast<std::uint64_t>(uStack_13) << 40) |
                        (static_cast<std::uint64_t>(bStack_14) << 32) |
                        static_cast<std::uint64_t>(local_18);

                    dVar2 = -std::bit_cast<double>(magnitude);

                    bits = std::bit_cast<std::uint64_t>(dVar2);
                    local_18 = static_cast<std::uint32_t>(bits);
                    bStack_14 = static_cast<std::uint8_t>(bits >> 32);
                    uStack_13 = static_cast<std::uint8_t>(bits >> 40);
                    uStack_12 = static_cast<std::uint16_t>(bits >> 48);
                }
            }

            const std::uint64_t result_bits =
                (static_cast<std::uint64_t>(uStack_12) << 48) |
                (static_cast<std::uint64_t>(uStack_13) << 40) |
                (static_cast<std::uint64_t>(bStack_14) << 32) |
                static_cast<std::uint64_t>(local_18);

            *param_2 = std::bit_cast<double>(result_bits);
            bVar3 = bVar6;
        }

        if (bVar3) {
            FUN_1002049a();
        }

        uVar5 = local_8 & 0xFFFFFFFDu;
        local_8 = uVar5;
        goto LAB_100203fc;
    }

    FUN_1002049a();

    uVar5 = param_3 & 0xC00u;
    dVar2 = _DAT_100399b8;
    dVar4 = _DAT_100399b8;

    if (uVar5 == 0) {
        dVar1 = *param_2;

        if (dVar1 <= 0.0) {
            dVar2 = -dVar4;
        }

        *param_2 = dVar2;
    } else {
        if (uVar5 == 0x400u) {
            dVar1 = *param_2;
            dVar2 = _DAT_100399c8;

            if (dVar1 <= 0.0) {
                dVar2 = -dVar4;
            }

            *param_2 = dVar2;
        } else {
            dVar4 = _DAT_100399c8;

            if (uVar5 == 0x800u) {
                dVar1 = *param_2;

                if (dVar1 <= 0.0) {
                    dVar2 = -dVar4;
                }

                *param_2 = dVar2;
            } else if (uVar5 == 0xC00u) {
                dVar1 = *param_2;
                dVar2 = _DAT_100399c8;

                if (dVar1 <= 0.0) {
                    dVar2 = -dVar4;
                }

                *param_2 = dVar2;
            }
        }
    }

    uVar5 = param_1 & 0x1Eu;

LAB_100203fc:
    if (((param_1 & 0x10u) != 0) && ((param_3 & 0x20u) != 0)) {
        FUN_1002049a();
        uVar5 = uVar5 & 0xFFFFFFEFu;
    }

    return uVar5 == 0;
}
